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

export module PonyEngine.Resource.Text.Impl:OngoingResourceLoadRequest;

import std;

import PonyEngine.Resource.Ext;

import :TextResource;

export namespace PonyEngine::Resource::Text
{
	/// @brief Resource load request that will be loaded via a special process.
	class OngoingResourceLoadRequest final : public IResourceLoadRequest
	{
	public:
		/// @brief Creates an ongoing resource load request.
		/// @param textResource Text resource.
		/// @param callback Callback.
		[[nodiscard("Pure constructor")]]
		OngoingResourceLoadRequest(std::shared_ptr<const TextResource> textResource, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback) noexcept;
		OngoingResourceLoadRequest(const OngoingResourceLoadRequest&) = delete;
		OngoingResourceLoadRequest(OngoingResourceLoadRequest&&) = delete;

		~OngoingResourceLoadRequest() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Async::RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<const void> MainResource() const override;
		[[nodiscard("Pure function")]]
		virtual std::span<const void* const> ResourceInterfaces() const override;
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		/// @brief Gets the request.
		/// @return Request.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<ILoadableDataAccessRequest>& Request() const noexcept;
		/// @brief Sets the request.
		/// @param request Request.
		void Request(std::shared_ptr<ILoadableDataAccessRequest> request) noexcept;

		/// @brief Sets the status to success.
		void SetSuccess() noexcept;
		/// @brief Sets the status to exception.
		/// @param exception Exception.
		void SetException(std::exception_ptr exception) noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;

		OngoingResourceLoadRequest& operator =(const OngoingResourceLoadRequest&) = delete;
		OngoingResourceLoadRequest& operator =(OngoingResourceLoadRequest&&) = delete;

	private:
		/// @brief Invokes the callback if it's not nullptr.
		void InvokeCallback() noexcept;

		std::shared_ptr<const TextResource> textResource; ///< Text resource.
		const void* resourceInterface; ///< Resource interface.

		std::exception_ptr exception; ///< Exception.
		std::atomic<Async::RequestStatus> status; ///< Status.

		std::shared_ptr<ILoadableDataAccessRequest> request; ///< Access request.

		std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback; ///< Callback.
	};
}

namespace PonyEngine::Resource::Text
{
	OngoingResourceLoadRequest::OngoingResourceLoadRequest(std::shared_ptr<const TextResource> textResource, 
		std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback) noexcept :
		textResource(std::move(textResource)),
		resourceInterface{&this->textResource->View()},
		status(Async::RequestStatus::Pending),
		callback(std::move(callback))
	{
	}

	Async::RequestStatus OngoingResourceLoadRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::shared_ptr<const void> OngoingResourceLoadRequest::MainResource() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return textResource;
	}

	std::span<const void* const> OngoingResourceLoadRequest::ResourceInterfaces() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return std::span(&resourceInterface, 1uz);
	}

	const std::exception_ptr& OngoingResourceLoadRequest::Exception() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	void OngoingResourceLoadRequest::Cancel()
	{
		request->Cancel();
	}

	void OngoingResourceLoadRequest::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == Async::RequestStatus::Pending)
		{
			status.wait(Async::RequestStatus::Pending, std::memory_order::acquire);
		}
	}

	const std::shared_ptr<ILoadableDataAccessRequest>& OngoingResourceLoadRequest::Request() const noexcept
	{
		return request;
	}

	void OngoingResourceLoadRequest::Request(std::shared_ptr<ILoadableDataAccessRequest> request) noexcept
	{
		this->request = std::move(request);
	}

	void OngoingResourceLoadRequest::SetSuccess() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		status.store(Async::RequestStatus::Success, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void OngoingResourceLoadRequest::SetException(std::exception_ptr exception) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		this->exception = std::move(exception);

		status.store(Async::RequestStatus::Failure, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void OngoingResourceLoadRequest::SetCanceled() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		status.store(Async::RequestStatus::Canceled, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void OngoingResourceLoadRequest::InvokeCallback() noexcept
	{
		if (callback)
		{
			callback(*this);
		}
	}
}
