/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Resource:IResourceService;

import std;

import :IFileResource;
import :ILoadableResource;
import :IMemoryResource;
import :ResourceAvailability;
import :ResourceID;
import :ResourceType;

export namespace PonyEngine::Resource
{
	/// @brief Resource service.
	class IResourceService
	{
		PONY_INTERFACE_BODY(IResourceService)

		/// @brief Gets a resource availability.
		/// @param resourceId Resource ID.
		/// @return Resource availability.
		[[nodiscard("Pure function")]]
		virtual ResourceAvailability IsResourceAvailable(ResourceID resourceId) const noexcept = 0;
		/// @brief Gets a resource type.
		/// @param resourceId Resource ID.
		/// @return Resource type.
		/// @note The resource must be available.
		[[nodiscard("Pure function")]]
		virtual struct ResourceType ResourceType(ResourceID resourceId) const = 0;
		/// @brief Gets a loadable resource.
		/// @param resourceId Resource ID.
		/// @return Loadable resource.
		/// @note The resource must be available as a loadable resource.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ILoadableResource> GetLoadableResource(ResourceID resourceId) const = 0;
		/// @brief Gets a file resource.
		/// @param resourceId Resource ID.
		/// @return File resource.
		/// @note The resource must be available as a file resource.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IFileResource> GetFileResource(ResourceID resourceId) const = 0;
		/// @brief Gets a memory resource.
		/// @param resourceId Resource ID.
		/// @return Memory resource.
		/// @note The resource must be available as a memory resource.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IMemoryResource> GetMemoryResource(ResourceID resourceId) const = 0;

		/// @brief Makes a resource ID from the resource ID string.
		/// @param resourceId Resource ID string.
		/// @return Resource ID.
		[[nodiscard("Pure function")]]
		virtual ResourceID MakeResourceID(std::string_view resourceId) = 0;
		/// @brief Checks if the resource ID is valid.
		/// @param resourceId Resource ID to check.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsResourceIDValid(ResourceID resourceId) const noexcept = 0;
		/// @brief Gets a resource ID string.
		/// @param resourceId Resource ID. Must be valid.
		/// @return Resource ID string.
		[[nodiscard("Pure function")]]
		virtual std::string_view GetResourceIDString(ResourceID resourceId) const = 0;

		/// @brief Makes a resource type from the resource type string.
		/// @param type Resource type string.
		/// @return Resource type.
		[[nodiscard("Pure function")]]
		virtual struct ResourceType MakeResourceType(std::string_view type) = 0;
		/// @brief Checks if the resource type is valid.
		/// @param type Resource type to check.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsResourceTypeValid(struct ResourceType type) const noexcept = 0;
		/// @brief Gets a resource type string.
		/// @param type Resource type. Must be valid.
		/// @return Resource type string.
		[[nodiscard("Pure function")]]
		virtual std::string_view GetResourceTypeString(struct ResourceType type) const = 0;
	};
}
