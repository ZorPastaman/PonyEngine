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
	/// @brief File resource.
	class FileResource final : public IFileResource
	{
	public:
		/// @brief Creates a file resource.
		/// @param id Resource ID.
		/// @param type Resource type.
		/// @param data File resource data.
		[[nodiscard("Pure constructor")]]
		FileResource(struct ResourceID id, ResourceType type, const std::shared_ptr<IFileResourceData>& data) noexcept;
		/// @brief Creates a file resource.
		/// @param id Resource ID.
		/// @param type Resource type.
		/// @param data File resource data.
		[[nodiscard("Pure constructor")]]
		FileResource(struct ResourceID id, ResourceType type, std::shared_ptr<IFileResourceData>&& data) noexcept;
		FileResource(const FileResource&) = delete;
		FileResource(FileResource&&) = delete;

		~FileResource() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual struct ResourceID ResourceID() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ResourceType Type() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& Path() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t Offset() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept override;

		FileResource& operator =(const FileResource&) = delete;
		FileResource& operator =(FileResource&&) = delete;

	private:
		struct ResourceID id; ///< Resource ID.
		ResourceType type; ///< Resource type.
		std::shared_ptr<IFileResourceData> data; ///< Resource data.
	};
}

namespace PonyEngine::Resource
{
	FileResource::FileResource(const struct ResourceID id, const ResourceType type, const std::shared_ptr<IFileResourceData>& data) noexcept :
		id(id),
		type(type),
		data(data)
	{
		assert(this->data && "The data is nullptr.");
	}

	FileResource::FileResource(const struct ResourceID id, const ResourceType type, std::shared_ptr<IFileResourceData>&& data) noexcept :
		id(id),
		type(type),
		data(std::move(data))
	{
		assert(this->data && "The data is nullptr.");
	}

	struct ResourceID FileResource::ResourceID() const noexcept
	{
		return id;
	}

	ResourceType FileResource::Type() const noexcept
	{
		return type;
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
