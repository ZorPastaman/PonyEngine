/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:Pack;

import std;

import PonyEngine.File;
import PonyEngine.Resource.Pack;

import :FileDataAccess;
import :FileLoadableDataAccess;
import :MemoryDataAccess;
import :MemoryLoadableDataAccess;

export namespace PonyEngine::Resource::Pack
{
	class Pack final : public IResourceProvider
	{
	public:
		[[nodiscard("Pure constructor")]]
		Pack(LoadableDataAccessRequestWorker& worker, std::filesystem::path packDataPath, std::shared_ptr<File::IFile> dataFile, 
			std::shared_ptr<const std::byte[]> loadedData, std::vector<std::pair<std::size_t, std::size_t>>&& resourceRanges);
		Pack(const Pack&) = delete;
		Pack(Pack&&) = delete;

		~Pack() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<void> GetResourceData(std::size_t index, std::type_index accessType) override;

		Pack& operator =(const Pack&) = delete;
		Pack& operator =(Pack&&) = delete;

	private:
		LoadableDataAccessRequestWorker* worker;

		std::filesystem::path packDataPath;
		std::shared_ptr<File::IFile> dataFile;
		std::shared_ptr<const std::byte[]> loadedData;

		std::vector<std::pair<std::size_t, std::size_t>> resourceRanges;
	};
}

namespace PonyEngine::Resource::Pack
{
	Pack::Pack(LoadableDataAccessRequestWorker& worker, std::filesystem::path packDataPath, std::shared_ptr<File::IFile> dataFile,
		std::shared_ptr<const std::byte[]> loadedData, std::vector<std::pair<std::size_t, std::size_t>>&& resourceRanges) :
		worker{&worker},
		packDataPath(std::move(packDataPath)),
		dataFile(std::move(dataFile)),
		loadedData(std::move(loadedData)),
		resourceRanges(std::move(resourceRanges))
	{
	}

	std::shared_ptr<void> Pack::GetResourceData(const std::size_t index, const std::type_index accessType)
	{
		const auto [offset, size] = resourceRanges[index];

		if (accessType == typeid(ILoadableDataAccess))
		{
			if (loadedData) [[likely]]
			{
				return std::make_shared<MemoryLoadableDataAccess>(*worker, loadedData, offset, size);
			}
			if (dataFile) [[likely]]
			{
				return std::make_shared<FileLoadableDataAccess>(*worker, dataFile, offset, size);
			}
		}
		else if (accessType == typeid(IFileDataAccess))
		{
			if (!packDataPath.empty()) [[likely]]
			{
				return std::make_shared<FileDataAccess>(packDataPath, offset, size);
			}
		}
		else if (accessType == typeid(IMemoryDataAccess))
		{
			if (loadedData) [[likely]]
			{
				return std::make_shared<MemoryDataAccess>(loadedData, offset, size);
			}
		}

		throw std::invalid_argument("Invalid access type");
	}
}
