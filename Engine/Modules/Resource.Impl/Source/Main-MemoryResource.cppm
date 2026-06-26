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

export module PonyEngine.Resource.Impl:MemoryResource;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	class MemoryResource final : public IMemoryResource
	{
	public:
		[[nodiscard("Pure constructor")]]
		MemoryResource(struct ResourceID id, ResourceType type, const std::shared_ptr<IMemoryResourceData>& data) noexcept;
		[[nodiscard("Pure constructor")]]
		MemoryResource(struct ResourceID id, ResourceType type, std::shared_ptr<IMemoryResourceData>&& data) noexcept;
		MemoryResource(const MemoryResource&) = delete;
		MemoryResource(MemoryResource&&) = delete;

		~MemoryResource() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual struct ResourceID ResourceID() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ResourceType Type() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual std::span<const std::byte> Memory() const noexcept override;

		MemoryResource& operator =(const MemoryResource&) = delete;
		MemoryResource& operator =(MemoryResource&&) = delete;

	private:
		struct ResourceID id;
		ResourceType type;
		std::shared_ptr<IMemoryResourceData> data;
	};
}

namespace PonyEngine::Resource
{
	MemoryResource::MemoryResource(const struct ResourceID id, const ResourceType type, const std::shared_ptr<IMemoryResourceData>& data) noexcept :
		id(id),
		type(type),
		data(data)
	{
		assert(this->data && "The data is nullptr.");
	}

	MemoryResource::MemoryResource(const struct ResourceID id, const ResourceType type, std::shared_ptr<IMemoryResourceData>&& data) noexcept :
		id(id),
		type(type),
		data(std::move(data))
	{
		assert(this->data && "The data is nullptr.");
	}

	struct ResourceID MemoryResource::ResourceID() const noexcept
	{
		return id;
	}

	ResourceType MemoryResource::Type() const noexcept
	{
		return type;
	}

	std::span<const std::byte> MemoryResource::Memory() const noexcept
	{
		return data->Memory();
	}
}
