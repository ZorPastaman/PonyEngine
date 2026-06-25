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

export module PonyEngine.Resource.Impl:LoadableResource;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	class LoadableResource final : public ILoadableResource
	{
	public:
		[[nodiscard("Pure constructor")]]
		LoadableResource(struct ResourceID id, ResourceType type, const std::shared_ptr<ILoadableResourceData>& data) noexcept;
		LoadableResource(const LoadableResource&) = delete;
		LoadableResource(LoadableResource&&) = delete;

		~LoadableResource() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual struct ResourceID ResourceID() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual ResourceType Type() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual std::size_t Size() const noexcept override;
		[[nodiscard("Must be used")]] 
		virtual std::shared_ptr<ILoadRequest> Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback) const override;

		LoadableResource& operator =(const LoadableResource&) = delete;
		LoadableResource& operator =(LoadableResource&&) = delete;

	private:
		struct ResourceID id;
		ResourceType type;
		std::shared_ptr<ILoadableResourceData> data;
	};
}

namespace PonyEngine::Resource
{
	LoadableResource::LoadableResource(const struct ResourceID id, const ResourceType type, const std::shared_ptr<ILoadableResourceData>& data) noexcept :
		id(id),
		type(type),
		data(data)
	{
		assert(data && "The data is nullptr.");
	}

	struct ResourceID LoadableResource::ResourceID() const noexcept
	{
		return id;
	}

	ResourceType LoadableResource::Type() const noexcept
	{
		return type;
	}

	std::size_t LoadableResource::Size() const noexcept
	{
		return data->Size();
	}

	std::shared_ptr<ILoadRequest> LoadableResource::Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback) const
	{
		return data->Load(params, callback);
	}
}
