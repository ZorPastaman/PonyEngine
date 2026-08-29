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

export module PonyEngine.Resource.Pack.Impl:PackMountRequest;

import std;

import PonyEngine.Resource.Pack;

export namespace PonyEngine::Resource::Pack
{
	class PackMountRequest : public IPackMountRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		PackMountRequest(enum AccessType accessType, std::span<const std::byte> manifest, std::shared_ptr<std::byte[]> dataBuffer, std::size_t dataSize, 
			std::move_only_function<void(const IPackMountRequest&) noexcept> callback) noexcept;
		PackMountRequest(const PackMountRequest&) = delete;
		PackMountRequest(PackMountRequest&&) = delete;

		virtual ~PackMountRequest() = default;

		[[nodiscard("Pure function")]] 
		virtual PackRequestStatus Status() const noexcept override final;
		[[nodiscard("Pure function")]] 
		virtual PackHandle Pack() const override final;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override final;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override final;

		[[nodiscard("Pure function")]]
		virtual bool IsFileSource() const noexcept;

		[[nodiscard("Pure function")]]
		enum AccessType AccessType() const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t ManifestSize() const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::byte> Manifest() const noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<std::byte[]>& DataBuffer() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t DataSize() const noexcept;
		[[nodiscard("Pure function")]]
		std::span<std::byte> Data() const noexcept;

		[[nodiscard("Pure function")]]
		bool IsCancelRequested() const noexcept;
		[[nodiscard("Pure function")]]
		std::uint8_t ReadRequestCount() const noexcept;
		[[nodiscard("Pure function")]]
		bool DecrementRequestCount() noexcept;

		[[nodiscard("Pure function")]]
		bool HasManifestException() const noexcept;
		[[nodiscard("Pure function")]]
		const std::exception_ptr& ManifestException() const noexcept;
		void ManifestException(std::exception_ptr exception) noexcept;
		[[nodiscard("Pure function")]]
		bool HasDataException() const noexcept;
		[[nodiscard("Pure function")]]
		const std::exception_ptr& DataException() const noexcept;
		void DataException(std::exception_ptr exception) noexcept;

		[[nodiscard("Pure function")]]
		std::vector<CollectionResource>& CollectionResources() noexcept;
		[[nodiscard("Pure function")]]
		std::span<const CollectionResource> CollectionResources() const noexcept;
		[[nodiscard("Pure function")]]
		std::vector<std::pair<std::size_t, std::size_t>>& Ranges() noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::pair<std::size_t, std::size_t>> Ranges() const noexcept;

		void SetSuccess(PackHandle packHandle) noexcept;
		void SetFailure(std::exception_ptr exception) noexcept;
		void SetCanceled() noexcept;

		PackMountRequest& operator =(const PackMountRequest&) = delete;
		PackMountRequest& operator =(PackMountRequest&&) = delete;

	private:
		void InvokeCallback() noexcept;

		std::span<const std::byte> manifest;
		std::shared_ptr<std::byte[]> dataBuffer;
		std::size_t dataSize;

		PackHandle packHandle;
		std::exception_ptr exception;
		std::atomic<PackRequestStatus> status;

		enum AccessType accessType;

		std::atomic_bool cancelRequested;
		std::atomic_uint8_t readRequestCount;
		std::atomic_bool hasManifestException;
		std::atomic_bool hasDataException;

		std::exception_ptr manifestException;
		std::exception_ptr dataException;

		std::vector<CollectionResource> collectionResources;
		std::vector<std::pair<std::size_t, std::size_t>> ranges;

		std::move_only_function<void(const IPackMountRequest&) noexcept> callback;
	};
}

namespace PonyEngine::Resource::Pack
{
	PackMountRequest::PackMountRequest(const enum AccessType accessType, const std::span<const std::byte> manifest, std::shared_ptr<std::byte[]> dataBuffer, const std::size_t dataSize,
		std::move_only_function<void(const IPackMountRequest&) noexcept> callback) noexcept :
		manifest(manifest),
		dataBuffer(std::move(dataBuffer)),
		dataSize{dataSize},
		status(PackRequestStatus::Pending),
		accessType{accessType},
		cancelRequested(false),
		readRequestCount(1uz + (dataBuffer != nullptr)),
		hasManifestException(false),
		hasDataException(false),
		callback(std::move(callback))
	{
	}

	PackRequestStatus PackMountRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	PackHandle PackMountRequest::Pack() const
	{
		if (status.load(std::memory_order::acquire) != PackRequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return packHandle;
	}

	const std::exception_ptr& PackMountRequest::Exception() const
	{
		if (status.load(std::memory_order::acquire) != PackRequestStatus::Failure) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	void PackMountRequest::Cancel()
	{
		cancelRequested.store(true, std::memory_order::relaxed);
	}

	void PackMountRequest::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == PackRequestStatus::Pending)
		{
			status.wait(PackRequestStatus::Pending, std::memory_order::acquire);
		}
	}

	bool PackMountRequest::IsFileSource() const noexcept
	{
		return false;
	}

	enum AccessType PackMountRequest::AccessType() const noexcept
	{
		return accessType;
	}

	std::size_t PackMountRequest::ManifestSize() const noexcept
	{
		return manifest.size();
	}

	std::span<const std::byte> PackMountRequest::Manifest() const noexcept
	{
		return manifest;
	}

	const std::shared_ptr<std::byte[]>& PackMountRequest::DataBuffer() const noexcept
	{
		return dataBuffer;
	}

	std::size_t PackMountRequest::DataSize() const noexcept
	{
		return dataSize;
	}

	std::span<std::byte> PackMountRequest::Data() const noexcept
	{
		return std::span(dataBuffer.get(), dataSize);
	}

	bool PackMountRequest::IsCancelRequested() const noexcept
	{
		return cancelRequested.load(std::memory_order::relaxed);
	}

	std::uint8_t PackMountRequest::ReadRequestCount() const noexcept
	{
		return readRequestCount.load(std::memory_order::relaxed);
	}

	bool PackMountRequest::DecrementRequestCount() noexcept
	{
		return readRequestCount.fetch_sub(1u, std::memory_order::relaxed) == 1u;
	}

	bool PackMountRequest::HasManifestException() const noexcept
	{
		return hasManifestException.load(std::memory_order::acquire);
	}

	const std::exception_ptr& PackMountRequest::ManifestException() const noexcept
	{
		return manifestException;
	}

	void PackMountRequest::ManifestException(std::exception_ptr exception) noexcept
	{
		manifestException = std::move(exception);
		hasManifestException.store(true, std::memory_order::release);
	}

	bool PackMountRequest::HasDataException() const noexcept
	{
		return hasDataException.load(std::memory_order::acquire);
	}

	const std::exception_ptr& PackMountRequest::DataException() const noexcept
	{
		return dataException;
	}

	void PackMountRequest::DataException(std::exception_ptr exception) noexcept
	{
		dataException = std::move(exception);
		hasDataException.store(true, std::memory_order::release);
	}

	std::vector<CollectionResource>& PackMountRequest::CollectionResources() noexcept
	{
		return collectionResources;
	}

	std::span<const CollectionResource> PackMountRequest::CollectionResources() const noexcept
	{
		return collectionResources;
	}

	std::vector<std::pair<std::size_t, std::size_t>>& PackMountRequest::Ranges() noexcept
	{
		return ranges;
	}

	std::span<const std::pair<std::size_t, std::size_t>> PackMountRequest::Ranges() const noexcept
	{
		return ranges;
	}

	void PackMountRequest::SetSuccess(const PackHandle packHandle) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == PackRequestStatus::Pending && "Invalid status.");

		this->packHandle = packHandle;
		status.store(PackRequestStatus::Success, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void PackMountRequest::SetFailure(std::exception_ptr exception) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == PackRequestStatus::Pending && "Invalid status.");

		this->exception = std::move(exception);
		status.store(PackRequestStatus::Failure, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void PackMountRequest::SetCanceled() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == PackRequestStatus::Pending && "Invalid status.");

		status.store(PackRequestStatus::Canceled, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void PackMountRequest::InvokeCallback() noexcept
	{
		if (callback)
		{
			callback(*this);
		}
	}
}
