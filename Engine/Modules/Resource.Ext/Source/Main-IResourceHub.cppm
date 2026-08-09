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

export module PonyEngine.Resource.Ext:IResourceHub;

import std;

import PonyEngine.Resource;

import :IResourceLoader;
import :IResourceProvider;
import :ResourceCollection;
import :CollectionResource;
import :ResourceType;

export namespace PonyEngine::Resource
{
	/// @brief Resource hub.
	class IResourceHub
	{
		PONY_INTERFACE_BODY(IResourceHub)

		/// @brief Registers a resource collection.
		/// @param provider Resource provider. Must be kept alive till the collection is successfully unregistered.
		/// @param resources Collection resources.
		/// @param dataAccessTypes Data access types.
		/// @return Resource collection.
		/// @note The function must be called on a main thread.
		[[nodiscard("Must be used to unregister")]]
		virtual ResourceCollection RegisterCollection(IResourceProvider& provider, std::span<const CollectionResource> resources, 
			std::span<const std::type_index> dataAccessTypes) = 0;
		/// @brief Unregisters the resource collection.
		/// @param provider Resource provider.
		/// @param collection Previously registers resource collection.
		/// @note The function must be called on a main thread.
		virtual void UnregisterCollection(IResourceProvider& provider, ResourceCollection collection) = 0;

		/// @brief Registers the loader.
		/// @param loader Loader. Must be kept alive till it's unregistered.
		/// @param types Resource types.
		/// @note The function must be called on a main thread.
		virtual void RegisterLoader(IResourceLoader& loader, std::span<const ResourceType> types) = 0;
		/// @brief Unregisters the loader.
		/// @param loader Loader.
		/// @note The function must be called on a main thread.
		virtual void UnregisterLoader(IResourceLoader& loader) = 0;

		/// @brief Makes a resource ID from the resource ID string.
		/// @param resourceId Resource ID string.
		/// @return Resource ID.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual ResourceID MakeResourceID(std::string_view resourceId) = 0;
		/// @brief Checks if the resource ID is valid.
		/// @param resourceId Resource ID to check.
		/// @return @a True if it's valid; @a false otherwise.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual bool IsResourceIDValid(ResourceID resourceId) const noexcept = 0;
		/// @brief Gets a resource ID string.
		/// @param resourceId Resource ID. Must be valid.
		/// @return Resource ID string.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view GetResourceIDString(ResourceID resourceId) const = 0;

		/// @brief Makes a resource type from the resource type string.
		/// @param resourceType Resource type string.
		/// @return Resource type.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual ResourceType MakeResourceType(std::string_view resourceType) = 0;
		/// @brief Checks if the resource type is valid.
		/// @param resourceType Resource type to check.
		/// @return @a True if it's valid; @a false otherwise.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual bool IsResourceTypeValid(ResourceType resourceType) const noexcept = 0;
		/// @brief Gets a resource type string.
		/// @param resourceType Resource type. Must be valid.
		/// @return Resource type string.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view GetResourceTypeString(ResourceType resourceType) const = 0;
	};
}
