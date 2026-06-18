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

export module PonyEngine.Resource.Impl:FileResource;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	class FileResource final : public IFileResource
	{
	public:
		[[nodiscard("Pure constructor")]]
		FileResource(struct ResourceID id, ResourceType type, std::span<const std::pair<ContextKey, ContextValue>> requiredContext,
			const std::shared_ptr<IFileResourceData>& data) noexcept;
		FileResource(const FileResource&) = delete;
		FileResource(FileResource&&) = delete;

		~FileResource() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual struct ResourceID ResourceID() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ResourceType Type() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::span<const std::pair<ContextKey, ContextValue>> RequiredContext() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& Path() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t Offset() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept override;

		FileResource& operator =(const FileResource&) = delete;
		FileResource& operator =(FileResource&&) = delete;

	private:
		struct ResourceID id;
		ResourceType type;
		std::vector<std::pair<ContextKey, ContextValue>> requiredContext;
		std::shared_ptr<IFileResourceData> data;
	};
}

namespace PonyEngine::Resource
{
	FileResource::FileResource(const struct ResourceID id, const ResourceType type, const std::span<const std::pair<ContextKey, ContextValue>> requiredContext,
		const std::shared_ptr<IFileResourceData>& data) noexcept :
		id(id),
		type(type),
		requiredContext(std::from_range, requiredContext),
		data(data)
	{
		assert(data && "The data is nullptr.");
	}

	struct ResourceID FileResource::ResourceID() const noexcept
	{
		return id;
	}

	ResourceType FileResource::Type() const noexcept
	{
		return type;
	}

	std::span<const std::pair<ContextKey, ContextValue>> FileResource::RequiredContext() const noexcept
	{
		return requiredContext;
	}

	const std::filesystem::path& FileResource::Path() const noexcept
	{
		return data->Path();
	}

	std::size_t FileResource::Offset() const noexcept
	{
		return data->Offset();
	}

	std::size_t FileResource::Size() const noexcept
	{
		return data->Size();
	}
}
