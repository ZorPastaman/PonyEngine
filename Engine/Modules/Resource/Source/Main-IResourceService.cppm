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

import :IResourceRequest;
import :ResourceID;

export namespace PonyEngine::Resource
{
	/// @brief Resource service.
	class IResourceService
	{
		PONY_INTERFACE_BODY(IResourceService)

		/// @brief Checks if the service has a resource with the given ID.
		/// @param resourceId Resource ID.
		/// @return @a True if such a resource is available; @a false otherwise.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual bool HasResource(ResourceID resourceId) const noexcept = 0;
		/// @brief Checks whether the resource is of type @p type.
		/// @param resourceId Resource ID. Must be valid.
		/// @param type The resource type to check against.
		/// @return @a true if the resource is of the specified type; @a false otherwise.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		bool IsResourceTypeOf(ResourceID resourceId, std::type_index type) const;
		/// @brief Checks whether the resource is of types @p types.
		/// @param resourceId Resource ID. Must be valid.
		/// @param types The resource types to check against.
		/// @return @a true if the resource is of the specified types; @a false otherwise.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual bool IsResourceTypeOf(ResourceID resourceId, std::span<const std::type_index> types) const = 0;
		/// @brief Checks whether the resource is of types @p Args.
		/// @tparam Args The resource types to check against.
		/// @param resourceId Resource ID. Must be valid.
		/// @return @a true if the resource is of the specified types; @a false otherwise.
		/// @note The function is thread-safe.
		template<typename... Args> [[nodiscard("Pure function")]]
		bool IsResourceTypeOf(ResourceID resourceId) const;

		/// @brief Loads a resource.
		/// @param resourceId Resource ID. Must be valid.
		/// @return Resource request.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IResourceRequest> LoadResource(ResourceID resourceId) const = 0;
		/// @brief Loads a resource with type check.
		/// @param resourceId Resource ID. Must be valid.
		/// @param type Type that the resource must be type of.
		/// @return Resource request.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		std::shared_ptr<IResourceRequest> LoadResource(ResourceID resourceId, std::type_index type) const;
		/// @brief Loads a resource with type checks.
		/// @param resourceId Resource ID. Must be valid.
		/// @param types Types that the resource must be type of.
		/// @return Resource request.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IResourceRequest> LoadResource(ResourceID resourceId, std::span<const std::type_index> types) const = 0;
		/// @brief Loads a resource with type check.
		/// @tparam Args Types that the resource must be type of.
		/// @param resourceId Resource ID. Must be valid.
		/// @return Resource request.
		/// @note The function is thread-safe.
		template<typename... Args> [[nodiscard("Pure function")]]
		std::shared_ptr<IResourceRequest> LoadResource(ResourceID resourceId) const;

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
	};
}

namespace PonyEngine::Resource
{
	bool IResourceService::IsResourceTypeOf(const ResourceID resourceId, const std::type_index type) const
	{
		return IsResourceTypeOf(resourceId, std::span(&type, 1uz));
	}

	template<typename... Args>
	bool IResourceService::IsResourceTypeOf(const ResourceID resourceId) const
	{
		return IsResourceTypeOf(resourceId, std::array<std::type_index, sizeof...(Args)>{typeid(Args)...});
	}

	std::shared_ptr<IResourceRequest> IResourceService::LoadResource(const ResourceID resourceId, const std::type_index type) const
	{
		return LoadResource(resourceId, std::span(&type, 1uz));
	}

	template<typename... Args>
	std::shared_ptr<IResourceRequest> IResourceService::LoadResource(const ResourceID resourceId) const
	{
		return LoadResource(resourceId, std::array<std::type_index, sizeof...(Args)>{typeid(Args)...});
	}
}
