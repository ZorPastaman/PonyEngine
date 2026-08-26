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

export module PonyEngine.Resource.Pack.Impl:FilePackMountRequest;

import std;

import PonyEngine.Application;
import PonyEngine.File;
import PonyEngine.Resource.Pack;

export namespace PonyEngine::Resource::Pack
{
	class FilePackMountRequest final : public IPackMountRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		FilePackMountRequest(enum AccessType accessType, std::shared_ptr<File::IFile> manifestFile, std::shared_ptr<File::IFile> dataFile, std::size_t dataFileSize,
			std::shared_ptr<Application::IBuffer> manifestBuffer, std::shared_ptr<Application::IBuffer> dataBuffer) noexcept;

		[[nodiscard("Pure function")]]
		virtual PackMountRequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual PackHandle Pack() const override;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		[[nodiscard("Pure function")]]
		bool IsCancelRequested() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<const std::byte> ManifestBuffer() const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::byte> DataBuffer() const noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<File::IFile>& DataFile() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t DataFileSize() const noexcept;

		void SetManifestRequest(const std::shared_ptr<File::IReadRequest>& manifestRequest) noexcept;
		void SetDataRequest(const std::shared_ptr<File::IReadRequest>& dataRequest) noexcept;

		[[nodiscard("Pure function")]]
		std::uint8_t ReadRequestCount() const noexcept;
		std::uint8_t DecrementRequestCount() noexcept;

		[[nodiscard("Pure function")]]
		bool HasManifestException() const noexcept;
		[[nodiscard("Pure function")]]
		const std::exception_ptr& ManifestException() const noexcept;
		void ManifestException(const std::exception_ptr& exception) noexcept;
		[[nodiscard("Pure function")]]
		bool HasDataException() const noexcept;
		[[nodiscard("Pure function")]]
		const std::exception_ptr& DataException() const noexcept;
		void DataException(const std::exception_ptr& exception) noexcept;

		[[nodiscard("Pure function")]]
		enum AccessType AccessType() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<const CollectionResource> CollectionResources() const noexcept;
		void CollectionResources(std::span<const CollectionResource> collectionResources);

		[[nodiscard("Pure function")]]
		std::span<const std::pair<std::size_t, std::size_t>> Ranges() const noexcept;
		void Ranges(std::span<const std::pair<std::size_t, std::size_t>> ranges);

		void SetSuccess(PackHandle packHandle) noexcept;
		void SetFailure(const std::exception_ptr& exception) noexcept;
		void SetCanceled() noexcept;

	private:
		PackHandle packHandle;
		std::exception_ptr exception;
		std::atomic<PackMountRequestStatus> status;

		std::atomic_bool cancelRequested;
		std::atomic_uint8_t readRequestCount;
		std::atomic_bool hasManifestException;
		std::atomic_bool hasDataException;

		enum AccessType accessType;
		std::shared_ptr<File::IFile> manifestFile;
		std::shared_ptr<Application::IBuffer> manifestBuffer;
		std::shared_ptr<File::IReadRequest> manifestReadRequest;
		std::shared_ptr<File::IFile> dataFile;
		std::size_t dataFileSize;
		std::shared_ptr<Application::IBuffer> dataBuffer;
		std::shared_ptr<File::IReadRequest> dataReadRequest;

		std::exception_ptr manifestException;
		std::exception_ptr dataException;

		std::vector<CollectionResource> collectionResources;
		std::vector<std::pair<std::size_t, std::size_t>> ranges;
	};
}

namespace PonyEngine::Resource::Pack
{
	FilePackMountRequest::FilePackMountRequest(const enum AccessType accessType, std::shared_ptr<File::IFile> manifestFile, std::shared_ptr<File::IFile> dataFile, const std::size_t dataFileSize,
		std::shared_ptr<Application::IBuffer> manifestBuffer, std::shared_ptr<Application::IBuffer> dataBuffer) noexcept :
		status(PackMountRequestStatus::Pending),
		cancelRequested(false),
		readRequestCount(1uz + (dataBuffer != nullptr)),
		hasManifestException(false),
		hasDataException(false),
		accessType{accessType},
		manifestFile(std::move(manifestFile)),
		manifestBuffer(std::move(manifestBuffer)),
		dataFile(std::move(dataFile)),
		dataFileSize(dataFileSize),
		dataBuffer(std::move(dataBuffer))
	{
	}

	PackMountRequestStatus FilePackMountRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	PackHandle FilePackMountRequest::Pack() const
	{
		if (status.load(std::memory_order::acquire) != PackMountRequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return packHandle;
	}

	const std::exception_ptr& FilePackMountRequest::Exception() const
	{
		if (status.load(std::memory_order::acquire) != PackMountRequestStatus::Failure) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	void FilePackMountRequest::Cancel()
	{
		cancelRequested.store(true, std::memory_order::relaxed);
		manifestReadRequest->Cancel();
		if (dataReadRequest)
		{
			dataReadRequest->Cancel();
		}
	}

	void FilePackMountRequest::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == PackMountRequestStatus::Pending)
		{
			status.wait(PackMountRequestStatus::Pending, std::memory_order::acquire);
		}
	}

	bool FilePackMountRequest::IsCancelRequested() const noexcept
	{
		return cancelRequested.load(std::memory_order::relaxed);
	}

	std::span<const std::byte> FilePackMountRequest::ManifestBuffer() const noexcept
	{
		return manifestBuffer->Span();
	}

	std::span<const std::byte> FilePackMountRequest::DataBuffer() const noexcept
	{
		return dataBuffer->Span();
	}

	const std::shared_ptr<File::IFile>& FilePackMountRequest::DataFile() const noexcept
	{
		return dataFile;
	}

	std::size_t FilePackMountRequest::DataFileSize() const noexcept
	{
		return dataFileSize;
	}

	void FilePackMountRequest::SetManifestRequest(const std::shared_ptr<File::IReadRequest>& manifestRequest) noexcept
	{
		manifestReadRequest = manifestRequest;
	}

	void FilePackMountRequest::SetDataRequest(const std::shared_ptr<File::IReadRequest>& dataRequest) noexcept
	{
		dataReadRequest = dataRequest;
	}

	std::uint8_t FilePackMountRequest::ReadRequestCount() const noexcept
	{
		return readRequestCount.load(std::memory_order::relaxed);
	}

	std::uint8_t FilePackMountRequest::DecrementRequestCount() noexcept
	{
		return readRequestCount.fetch_sub(1uz, std::memory_order::relaxed);
	}

	bool FilePackMountRequest::HasManifestException() const noexcept
	{
		return hasManifestException.load(std::memory_order::acquire);
	}

	const std::exception_ptr& FilePackMountRequest::ManifestException() const noexcept
	{
		return manifestException;
	}

	void FilePackMountRequest::ManifestException(const std::exception_ptr& exception) noexcept
	{
		assert(!hasManifestException.load(std::memory_order::relaxed) && "Manifest exception is already set.");

		manifestException = exception;
		hasManifestException.store(true, std::memory_order::release);
	}

	bool FilePackMountRequest::HasDataException() const noexcept
	{
		return hasDataException.load(std::memory_order::acquire);
	}

	const std::exception_ptr& FilePackMountRequest::DataException() const noexcept
	{
		return dataException;
	}

	void FilePackMountRequest::DataException(const std::exception_ptr& exception) noexcept
	{
		assert(!hasDataException.load(std::memory_order::relaxed) && "Data exception is already set.");

		dataException = exception;
		hasDataException.store(true, std::memory_order::release);
	}

	enum AccessType FilePackMountRequest::AccessType() const noexcept
	{
		return accessType;
	}

	std::span<const CollectionResource> FilePackMountRequest::CollectionResources() const noexcept
	{
		return collectionResources;
	}

	void FilePackMountRequest::CollectionResources(const std::span<const CollectionResource> collectionResources)
	{
		this->collectionResources.assign_range(collectionResources);
	}

	std::span<const std::pair<std::size_t, std::size_t>> FilePackMountRequest::Ranges() const noexcept
	{
		return ranges;
	}

	void FilePackMountRequest::Ranges(const std::span<const std::pair<std::size_t, std::size_t>> ranges)
	{
		this->ranges.assign_range(ranges);
	}

	void FilePackMountRequest::SetSuccess(const PackHandle packHandle) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == PackMountRequestStatus::Pending && "Invalid status.");

		this->packHandle = packHandle;
		status.store(PackMountRequestStatus::Success, std::memory_order::release);
		status.notify_all();
	}

	void FilePackMountRequest::SetFailure(const std::exception_ptr& exception) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == PackMountRequestStatus::Pending && "Invalid status.");

		this->exception = exception;
		status.store(PackMountRequestStatus::Failure, std::memory_order::release);
		status.notify_all();
	}

	void FilePackMountRequest::SetCanceled() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == PackMountRequestStatus::Pending && "Invalid status.");

		status.store(PackMountRequestStatus::Canceled, std::memory_order::release);
		status.notify_all();
	}
}
