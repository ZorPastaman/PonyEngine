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

import PonyEngine.Async;
import PonyEngine.Resource.Pack;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Pack mount request.
	class PackMountRequest : public IPackMountRequest
	{
	public:
		/// @brief Creates a pack mount request.
		/// @param accessType Access type.
		/// @param manifest Pack manifest.
		/// @param manifestSize Pack manifest size.
		/// @param dataBuffer Pack data. If it's nullptr, the request count will be 1, otherwise it'll be 2.
		/// @param dataSize Pack data size.
		/// @param callback Callback.
		[[nodiscard("Pure constructor")]]
		PackMountRequest(enum AccessType accessType, const std::byte* manifest, std::size_t manifestSize, std::shared_ptr<std::byte[]> dataBuffer, std::size_t dataSize, 
			std::move_only_function<void(const IPackMountRequest&) noexcept> callback) noexcept;
		PackMountRequest(const PackMountRequest&) = delete;
		PackMountRequest(PackMountRequest&&) = delete;

		virtual ~PackMountRequest() = default;

		[[nodiscard("Pure function")]] 
		virtual Async::RequestStatus Status() const noexcept override final;
		[[nodiscard("Pure function")]] 
		virtual PackHandle Pack() const override final;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override final;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override final;

		/// @brief Checks if the request has a file source.
		/// @return @a True if it's a file source; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsFileSource() const noexcept;

		/// @brief Gets the access type.
		/// @return Access type.
		[[nodiscard("Pure function")]]
		enum AccessType AccessType() const noexcept;

		/// @brief Gets the manifest size.
		/// @return Manifest size.
		[[nodiscard("Pure function")]]
		std::size_t ManifestSize() const noexcept;
		/// @brief Gets the manifest view.
		/// @return Manifest view.
		[[nodiscard("Pure function")]]
		std::span<const std::byte> Manifest() const noexcept;
		/// @brief Gets the data buffer.
		/// @return Data buffer.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<std::byte[]>& DataBuffer() const noexcept;
		/// @brief Gets the data size.
		/// @return Data size.
		[[nodiscard("Pure function")]]
		std::size_t DataSize() const noexcept;
		/// @brief Gets the data.
		/// @return Data.
		[[nodiscard("Pure function")]]
		std::span<std::byte> Data() const noexcept;

		/// @brief Checks if the cancel was requested.
		/// @return @a True if it was requested; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsCancelRequested() const noexcept;
		/// @brief Gets the read request count.
		/// @return Read request count.
		[[nodiscard("Pure function")]]
		std::uint8_t ReadRequestCount() const noexcept;
		/// @brief Decrements the read request count.
		/// @return @a True if it's reached 0; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool DecrementRequestCount() noexcept;

		/// @brief Checks if the request has a manifest exception.
		/// @return @a True if it has; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasManifestException() const noexcept;
		/// @brief Gets the manifest track exception.
		/// @return Manifest track exception.
		[[nodiscard("Pure function")]]
		const std::exception_ptr& ManifestException() const noexcept;
		/// @brief Sets the manifest track exception.
		/// @param exception Manifest track exception.
		void ManifestException(std::exception_ptr exception) noexcept;
		/// @brief Checks if the request has a data exception.
		/// @return @a True if it has; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasDataException() const noexcept;
		/// @brief Gets the data track exception.
		/// @return Data track exception.
		[[nodiscard("Pure function")]]
		const std::exception_ptr& DataException() const noexcept;
		/// @brief Sets the data track exception.
		/// @param exception Data track exception.
		void DataException(std::exception_ptr exception) noexcept;

		/// @brief Gets the collection resources.
		/// @return Collection resources.
		[[nodiscard("Pure function")]]
		std::vector<CollectionResource>& CollectionResources() noexcept;
		/// @brief Gets the collection resources.
		/// @return Collection resources.
		[[nodiscard("Pure function")]]
		std::span<const CollectionResource> CollectionResources() const noexcept;
		/// @brief Gets the ranges.
		/// @return Ranges.
		[[nodiscard("Pure function")]]
		std::vector<std::pair<std::size_t, std::size_t>>& Ranges() noexcept;
		/// @brief Gets the ranges.
		/// @return Ranges.
		[[nodiscard("Pure function")]]
		std::span<const std::pair<std::size_t, std::size_t>> Ranges() const noexcept;

		/// @brief Sets the status to success.
		/// @param packHandle Pack handle.
		void SetSuccess(PackHandle packHandle) noexcept;
		/// @brief Sets the status to failure.
		/// @param exception Exception.
		void SetFailure(std::exception_ptr exception) noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;

		PackMountRequest& operator =(const PackMountRequest&) = delete;
		PackMountRequest& operator =(PackMountRequest&&) = delete;

	private:
		/// @brief Invokes a callback if it's not nullptr.
		void InvokeCallback() noexcept;

		const std::byte* manifest; ///< Manifest.
		std::size_t manifestSize; ///< Manifest size.
		std::shared_ptr<std::byte[]> dataBuffer; ///< Data buffer.
		std::size_t dataSize; ///< Data size.

		PackHandle packHandle; ///< Pack handle.
		std::exception_ptr exception; ///< Exception.
		std::atomic<Async::RequestStatus> status; ///< Status.

		enum AccessType accessType; ///< Access type.

		std::atomic_bool cancelRequested; ///< Is the cancel requested?
		std::atomic_uint8_t readRequestCount; ///< Read request count.
		std::atomic_bool hasManifestException; ///< Does it have a manifest track exception?
		std::atomic_bool hasDataException; ///< Does it have a data track exception?

		std::exception_ptr manifestException; ///< Manifest track exception.
		std::exception_ptr dataException; ///< Data track exception.

		std::vector<CollectionResource> collectionResources; ///< Collection resources.
		std::vector<std::pair<std::size_t, std::size_t>> ranges; ///< Ranges.

		std::move_only_function<void(const IPackMountRequest&) noexcept> callback; ///< Callback.
	};
}

namespace PonyEngine::Resource::Pack
{
	PackMountRequest::PackMountRequest(const enum AccessType accessType, const std::byte* const manifest, const std::size_t manifestSize, 
		std::shared_ptr<std::byte[]> dataBuffer, const std::size_t dataSize, std::move_only_function<void(const IPackMountRequest&) noexcept> callback) noexcept :
		manifest{manifest},
		manifestSize{manifestSize},
		dataBuffer(std::move(dataBuffer)),
		dataSize{dataSize},
		status(Async::RequestStatus::Pending),
		accessType{accessType},
		cancelRequested(false),
		readRequestCount(1uz + (dataBuffer != nullptr)),
		hasManifestException(false),
		hasDataException(false),
		callback(std::move(callback))
	{
	}

	Async::RequestStatus PackMountRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	PackHandle PackMountRequest::Pack() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return packHandle;
	}

	const std::exception_ptr& PackMountRequest::Exception() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Failure) [[unlikely]]
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
		while (status.load(std::memory_order::acquire) == Async::RequestStatus::Pending)
		{
			status.wait(Async::RequestStatus::Pending, std::memory_order::acquire);
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
		return manifestSize;
	}

	std::span<const std::byte> PackMountRequest::Manifest() const noexcept
	{
		return std::span<const std::byte>(manifest, manifestSize);
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
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		this->packHandle = packHandle;
		status.store(Async::RequestStatus::Success, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void PackMountRequest::SetFailure(std::exception_ptr exception) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		this->exception = std::move(exception);
		status.store(Async::RequestStatus::Failure, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void PackMountRequest::SetCanceled() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		status.store(Async::RequestStatus::Canceled, std::memory_order::release);
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
