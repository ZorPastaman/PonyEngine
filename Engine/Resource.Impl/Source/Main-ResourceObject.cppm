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

export module PonyEngine.Resource.Impl:ResourceObject;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	class ResourceObject final : public IResource
	{
	public:
		[[nodiscard("Pure constructor")]]
		ResourceObject(struct ResourceID id, ResourceType type, std::span<const std::pair<ContextKey, ContextValue>> requiredContext, 
			const std::shared_ptr<IResourceData>& data) noexcept;
		ResourceObject(const ResourceObject&) = delete;
		ResourceObject(ResourceObject&&) = delete;

		~ResourceObject() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual struct ResourceID ResourceID() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual ResourceType Type() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const std::pair<ContextKey, ContextValue>> RequiredContext() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual std::size_t Size() const noexcept override;
		[[nodiscard("Must be used")]] 
		virtual std::shared_ptr<ILoadRequest> Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback) const override;
		[[nodiscard("Pure function")]] 
		virtual bool IsFileReferenceAvailable() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const FileReference& GetFileReference() const override;
		[[nodiscard("Pure function")]] 
		virtual bool IsMemoryReferenceAvailable() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const MemoryReference& GetMemoryReference() const override;

		ResourceObject& operator =(const ResourceObject&) = delete;
		ResourceObject& operator =(ResourceObject&&) = delete;

	private:
		struct ResourceID id;
		ResourceType type;
		std::vector<std::pair<ContextKey, ContextValue>> requiredContext;
		std::shared_ptr<IResourceData> data;
	};
}

namespace PonyEngine::Resource
{
	struct ResourceID ResourceObject::ResourceID() const noexcept
	{
		return id;
	}

	ResourceObject::ResourceObject(const struct ResourceID id, const ResourceType type, const std::span<const std::pair<ContextKey, ContextValue>> requiredContext,
		const std::shared_ptr<IResourceData>& data) noexcept :
		id(id),
		type(type),
		requiredContext(std::from_range, requiredContext),
		data(data)
	{
		assert(data && "The data is nullptr.");
	}

	ResourceType ResourceObject::Type() const noexcept
	{
		return type;
	}

	std::span<const std::pair<ContextKey, ContextValue>> ResourceObject::RequiredContext() const noexcept
	{
		return requiredContext;
	}

	std::size_t ResourceObject::Size() const noexcept
	{
		return data->Size();
	}

	std::shared_ptr<ILoadRequest> ResourceObject::Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback) const
	{
		return data->Load(params, callback);
	}

	bool ResourceObject::IsFileReferenceAvailable() const noexcept
	{
		return data->IsFileReferenceAvailable();
	}

	const FileReference& ResourceObject::GetFileReference() const
	{
		return data->GetFileReference();
	}

	bool ResourceObject::IsMemoryReferenceAvailable() const noexcept
	{
		return data->IsMemoryReferenceAvailable();
	}

	const MemoryReference& ResourceObject::GetMemoryReference() const
	{
		return data->GetMemoryReference();
	}
}
