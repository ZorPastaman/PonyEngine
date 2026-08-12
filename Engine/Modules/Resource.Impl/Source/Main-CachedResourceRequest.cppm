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

export namespace PonyEngine::Resource
{
	class CachedResourceRequest final : public IResourceRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		CachedResourceRequest(struct ResourceID id, std::span<const std::type_index> outputTypes, 
			std::shared_ptr<const void>&& mainResource, std::span<const void* const> resources);

		[[nodiscard("Pure function")]] 
		virtual struct ResourceID ResourceID() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsTypeOf(std::span<const std::type_index> types) const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<const void> Resource(std::type_index type) const override;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		virtual void AddObserver(IResourceRequestObserver& observer) const override;
		virtual void RemoveObserver(IResourceRequestObserver& observer) const override;

	private:
		struct ResourceID id;

		std::vector<std::type_index> outputTypes;
		std::shared_ptr<const void> mainResource;
		std::vector<const void*> resources;

		mutable std::vector<IResourceRequestObserver*> observers;
		mutable std::mutex observerMutex;
	};
}

namespace PonyEngine::Resource
{
	CachedResourceRequest::CachedResourceRequest(const struct ResourceID id, const std::span<const std::type_index> outputTypes,
		std::shared_ptr<const void>&& mainResource, const std::span<const void* const> resources) :
		id(id),
		outputTypes(outputTypes.cbegin(), outputTypes.cend()),
		mainResource(std::move(mainResource)),
		resources(resources.cbegin(), resources.cend())
	{
	}

	struct ResourceID CachedResourceRequest::ResourceID() const noexcept
	{
		return id;
	}

	bool CachedResourceRequest::IsTypeOf(const std::span<const std::type_index> types) const noexcept
	{
		for (const std::type_index type : types)
		{
			if (!std::ranges::contains(outputTypes, type))
			{
				return false;
			}
		}

		return true;
	}

	RequestStatus CachedResourceRequest::Status() const noexcept
	{
		return RequestStatus::Success;
	}

	std::shared_ptr<const void> CachedResourceRequest::Resource(const std::type_index type) const
	{
		for (std::size_t i = 0uz; i < outputTypes.size(); ++i)
		{
			if (outputTypes[i] == type)
			{
				return std::shared_ptr<const void>(mainResource, resources[i]);
			}
		}

		throw std::invalid_argument("Invalid type");
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

	void CachedResourceRequest::AddObserver(IResourceRequestObserver& observer) const
	{
		const auto lock = std::lock_guard(observerMutex);

		observers.push_back(&observer);
		observer.OnStatusChanged(*this);
	}

	void CachedResourceRequest::RemoveObserver(IResourceRequestObserver& observer) const
	{
		const auto lock = std::lock_guard(observerMutex);

		if (const auto position = std::ranges::find(observers, &observer); position != observers.cend()) [[likely]]
		{
			observers.erase(position);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Observer wasn't added");
		}
	}
}
