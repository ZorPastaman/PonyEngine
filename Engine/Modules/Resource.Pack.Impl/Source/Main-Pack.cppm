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

import :DataAccessWorker;
import :FileDataAccess;
import :FileLoadableDataAccess;
import :MemoryDataAccess;
import :MemoryLoadableDataAccess;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Pack.
	class Pack final : public IResourceProvider
	{
	public:
		/// @brief Creates a pack.
		/// @param worker Data access worker.
		/// @param packDataPath Pack data path. If set to a non-empty value, the pack will provide @p IFileDataAccess.
		/// @param dataFile Data file. If set, the pack will provide @p ILoadableDataAccess.
		/// @param loadedData Loaded pack data. If set, the pack will provide @p ILoadableDataAccess and @p IMemoryDataAccess. It has a priority over the file loadable access.
		/// @param resourceRanges Resource ranges. Must be valid.
		[[nodiscard("Pure constructor")]]
		Pack(DataAccessWorker& worker, std::filesystem::path packDataPath, std::shared_ptr<File::IFile> dataFile,
			std::shared_ptr<const std::byte[]> loadedData, std::vector<std::pair<std::size_t, std::size_t>>&& resourceRanges) noexcept;
		Pack(const Pack&) = delete;
		Pack(Pack&&) = delete;

		~Pack() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<void> GetResourceData(std::size_t index, std::type_index accessType) override;

		Pack& operator =(const Pack&) = delete;
		Pack& operator =(Pack&&) = delete;

	private:
		DataAccessWorker* worker; ///< Data access worker.

		std::filesystem::path packDataPath; ///< Pack data path.
		std::shared_ptr<File::IFile> dataFile; ///< Pack data file.
		std::shared_ptr<const std::byte[]> loadedData; ///< Pack loaded data.

		std::vector<std::pair<std::size_t, std::size_t>> resourceRanges; ///< Resource ranges.
	};
}

namespace PonyEngine::Resource::Pack
{
	Pack::Pack(DataAccessWorker& worker, std::filesystem::path packDataPath, std::shared_ptr<File::IFile> dataFile,
		std::shared_ptr<const std::byte[]> loadedData, std::vector<std::pair<std::size_t, std::size_t>>&& resourceRanges) noexcept :
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
			if (loadedData)
			{
				return worker->CreateMemoryLoadableDataAccess(loadedData, offset, size);
			}
			if (dataFile) [[likely]]
			{
				return worker->CreateFileLoadableDataAccess(dataFile, offset, size);
			}
		}
		else if (accessType == typeid(IFileDataAccess))
		{
			if (!packDataPath.empty()) [[likely]]
			{
				return worker->CreateFileDataAccess(packDataPath, offset, size);
			}
		}
		else if (accessType == typeid(IMemoryDataAccess))
		{
			if (loadedData) [[likely]]
			{
				return worker->CreateMemoryDataAccess(loadedData, offset, size);
			}
		}

		throw std::invalid_argument("Invalid access type");
	}
}
