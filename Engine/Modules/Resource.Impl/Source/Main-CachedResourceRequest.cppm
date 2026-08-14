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
	class CachedResourceRequest final : public IResourceRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		CachedResourceRequest(const std::shared_ptr<const ResourceInfo>& info, const std::shared_ptr<const ResourceData>& data, 
			const std::shared_ptr<const void>& mainResource) noexcept;
		CachedResourceRequest(const CachedResourceRequest&) = delete;
		CachedResourceRequest(CachedResourceRequest&&) = delete;

		~CachedResourceRequest() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual struct ResourceID ResourceID() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsTypeOf(std::span<const std::type_index> types) const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<const IResourceRequestResult> Result() const override;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		CachedResourceRequest& operator =(const CachedResourceRequest&) = delete;
		CachedResourceRequest& operator =(CachedResourceRequest&&) = delete;

	private:
		struct ResourceID id;
		std::shared_ptr<const ResourceRequestResult> result;
	};
}

namespace PonyEngine::Resource
{
	CachedResourceRequest::CachedResourceRequest(const std::shared_ptr<const ResourceInfo>& info, const std::shared_ptr<const ResourceData>& data,
		const std::shared_ptr<const void>& mainResource) noexcept :
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

	RequestStatus CachedResourceRequest::Status() const noexcept
	{
		return RequestStatus::Success;
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
