/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Text.Impl:CompletedResourceLoadRequest;

import std;

import PonyEngine.Async;
import PonyEngine.Resource.Ext;

import :TextResource;

export namespace PonyEngine::Resource::Text
{
	/// @brief Resource load request that is used when the resource is immediately available.
	class CompletedResourceLoadRequest final : public IResourceLoadRequest
	{
	public:
		/// @brief Creates a completed resource load request.
		/// @param textResource Text resource.
		[[nodiscard("Pure constructor")]]
		explicit CompletedResourceLoadRequest(std::shared_ptr<const TextResource> textResource) noexcept;
		[[nodiscard("Pure constructor")]]
		CompletedResourceLoadRequest(const CompletedResourceLoadRequest& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		CompletedResourceLoadRequest(CompletedResourceLoadRequest&& other) noexcept = default;

		~CompletedResourceLoadRequest() noexcept = default;

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

		CompletedResourceLoadRequest& operator =(const CompletedResourceLoadRequest& other) noexcept = default;
		CompletedResourceLoadRequest& operator =(CompletedResourceLoadRequest&& other) noexcept = default;

	private:
		std::shared_ptr<const TextResource> textResource; ///< Text resource.
		const void* resourceInterface; ///< Resource interface.
	};
}

namespace PonyEngine::Resource::Text
{
	CompletedResourceLoadRequest::CompletedResourceLoadRequest(std::shared_ptr<const TextResource> textResource) noexcept :
		textResource(std::move(textResource)),
		resourceInterface{&this->textResource->View()}
	{
	}

	Async::RequestStatus CompletedResourceLoadRequest::Status() const noexcept
	{
		return Async::RequestStatus::Success;
	}

	std::shared_ptr<const void> CompletedResourceLoadRequest::MainResource() const
	{
		return textResource;
	}

	std::span<const void* const> CompletedResourceLoadRequest::ResourceInterfaces() const
	{
		return std::span(&resourceInterface, 1uz);
	}

	const std::exception_ptr& CompletedResourceLoadRequest::Exception() const
	{
		throw std::logic_error("Invalid status");
	}

	void CompletedResourceLoadRequest::Cancel()
	{
	}

	void CompletedResourceLoadRequest::Wait() const noexcept
	{
	}
}
