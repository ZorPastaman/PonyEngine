/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Impl:CachedResourceRequest;

import std;

import PonyEngine.Resource;

import :ResourceInfo;
import :ResourceData;
import :ResourceRequestResult;

export namespace PonyEngine::Resource
{
	/// @brief Resource request that is used when the resource is already loaded and still in memory.
	class CachedResourceRequest final : public IResourceRequest
	{
	public:
		/// @brief Creates a cached resource request.
		/// @param info Resource info. Mustn't be nullptr.
		/// @param data Resource data. Mustn't be nullptr.
		/// @param mainResource Main resource. Mustn't be nullptr.
		[[nodiscard("Pure constructor")]]
		CachedResourceRequest(const std::shared_ptr<const ResourceInfo>& info, const std::shared_ptr<const ResourceData>& data, 
			const std::shared_ptr<const void>& mainResource);
		CachedResourceRequest(const CachedResourceRequest&) = delete;
		CachedResourceRequest(CachedResourceRequest&&) = delete;

		~CachedResourceRequest() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual struct ResourceID ResourceID() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsTypeOf(std::span<const std::type_index> types) const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual ResourceRequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<const IResourceRequestResult> Result() const override;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		CachedResourceRequest& operator =(const CachedResourceRequest&) = delete;
		CachedResourceRequest& operator =(CachedResourceRequest&&) = delete;

	private:
		struct ResourceID id; ///< Resource ID.
		std::shared_ptr<const ResourceRequestResult> result; ///< Load result.
	};
}

namespace PonyEngine::Resource
{
	CachedResourceRequest::CachedResourceRequest(const std::shared_ptr<const ResourceInfo>& info, const std::shared_ptr<const ResourceData>& data,
		const std::shared_ptr<const void>& mainResource) :
		id(info->id),
		result(std::make_shared<ResourceRequestResult>(info, data, mainResource))
	{
	}

	struct ResourceID CachedResourceRequest::ResourceID() const noexcept
	{
		return id;
	}

	bool CachedResourceRequest::IsTypeOf(const std::span<const std::type_index> types) const noexcept
	{
		return result->IsTypeOf(types);
	}

	ResourceRequestStatus CachedResourceRequest::Status() const noexcept
	{
		return ResourceRequestStatus::Success;
	}

	std::shared_ptr<const IResourceRequestResult> CachedResourceRequest::Result() const
	{
		return result;
	}

	const std::exception_ptr& CachedResourceRequest::Exception() const
	{
		throw std::logic_error("Invalid status");
	}

	void CachedResourceRequest::Cancel()
	{
	}

	void CachedResourceRequest::Wait() const noexcept
	{
	}
}
