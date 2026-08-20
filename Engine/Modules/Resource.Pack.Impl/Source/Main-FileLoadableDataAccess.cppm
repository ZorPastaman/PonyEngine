/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Resource.Pack.Impl:FileLoadableDataAccess;

import std;

import PonyEngine.Math;
import PonyEngine.File;
import PonyEngine.Resource.Ext;

import :LoadableDataAccessRequest;
import :LoadableDataAccessRequestWorker;

export namespace PonyEngine::Resource::Pack
{
	class FileLoadableDataAccess final : public ILoadableDataAccess
	{
	public:
		[[nodiscard("Pure constructor")]]
		FileLoadableDataAccess(const std::shared_ptr<File::IFile>& dataFile, std::size_t offset, std::size_t size, 
			const std::shared_ptr<LoadableDataAccessRequestWorker>& requestBuffer) noexcept;
		FileLoadableDataAccess(const FileLoadableDataAccess&) = delete;
		FileLoadableDataAccess(FileLoadableDataAccess&&) = delete;

		~FileLoadableDataAccess() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::size_t Size() const noexcept override;

		[[nodiscard("Must be used")]] 
		virtual std::shared_ptr<ILoadableDataAccessRequest> Load(std::span<std::byte> buffer, std::size_t offset, ILoadableDataAccessRequestObserver* observer) override;

		FileLoadableDataAccess& operator =(const FileLoadableDataAccess&) = delete;
		FileLoadableDataAccess& operator =(FileLoadableDataAccess&&) = delete;

	private:
		std::shared_ptr<File::IFile> dataFile;
		std::size_t offset;
		std::size_t size;
		
		std::shared_ptr<LoadableDataAccessRequestWorker> requestBuffer;
	};
}

namespace PonyEngine::Resource::Pack
{
	FileLoadableDataAccess::FileLoadableDataAccess(const std::shared_ptr<File::IFile>& dataFile, const std::size_t offset, const std::size_t size,
		const std::shared_ptr<LoadableDataAccessRequestWorker>& requestBuffer) noexcept :
		dataFile(dataFile),
		offset{offset},
		size{size},
		requestBuffer(requestBuffer)
	{
		assert(this->dataFile && "Data file is nullptr.");
		assert(this->requestBuffer && "Request buffer is nullptr.");
	}

	std::size_t FileLoadableDataAccess::Size() const noexcept
	{
		return size;
	}

	std::shared_ptr<ILoadableDataAccessRequest> FileLoadableDataAccess::Load(const std::span<std::byte> buffer, const std::size_t offset, 
		ILoadableDataAccessRequestObserver* const observer)
	{
		if (Math::SumClamp(buffer.size(), offset) > size) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}

		return requestBuffer->CreateRequest(*dataFile, this->offset + offset, buffer, observer);
	}
}
