/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

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
		/// @param resourceId Resource ID. Must be valid.
		/// @return @a True if such a resource is available; @a false otherwise.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual bool HasResource(ResourceID resourceId) const = 0;
		/// @brief Checks whether the resource has an interface of type @p type.
		/// @param resourceId Resource ID. Must be valid.
		/// @param type Interface type to check against.
		/// @return @a True if the resource has an interface of the specified type; @a false otherwise.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		bool HasInterface(ResourceID resourceId, std::type_index type) const;
		/// @brief Checks whether the resource has interfaces of types @p types.
		/// @param resourceId Resource ID. Must be valid.
		/// @param types Interface types to check against.
		/// @return @a True if the resource has an interface of the specified type; @a false otherwise.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual bool HasInterfaces(ResourceID resourceId, std::span<const std::type_index> types) const = 0;
		/// @brief Checks whether the resource has interfaces of types @p Args.
		/// @tparam Args Interface types to check against.
		/// @param resourceId Resource ID. Must be valid.
		/// @return @a True if the resource has an interface of the specified type; @a false otherwise.
		/// @note The function is thread-safe.
		template<typename... Args> [[nodiscard("Pure function")]]
		bool HasInterfaces(ResourceID resourceId) const;

		/// @brief Loads a resource.
		/// @param resourceId Resource ID. Must be valid.
		/// @param callback Callback. Can be nullptr.
		/// @return Resource request.
		/// @note The request and the callback must be kept alive till the finish of the request.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		std::shared_ptr<IResourceRequest> LoadResource(ResourceID resourceId, std::move_only_function<void(const IResourceRequest&) noexcept> callback = nullptr) const;
		/// @brief Loads a resource with type check.
		/// @param resourceId Resource ID. Must be valid.
		/// @param interfaceType Interface type that the resource must provide.
		/// @param callback Callback. Can be nullptr.
		/// @return Resource request.
		/// @note The request and the callback must be kept alive till the finish of the request.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		std::shared_ptr<IResourceRequest> LoadResource(ResourceID resourceId, std::type_index interfaceType, 
			std::move_only_function<void(const IResourceRequest&) noexcept> callback = nullptr) const;
		/// @brief Loads a resource with type checks.
		/// @param resourceId Resource ID. Must be valid.
		/// @param interfaceTypes Interface types that the resource must provide.
		/// @param callback Callback. Can be nullptr.
		/// @return Resource request.
		/// @note The request and the callback must be kept alive till the finish of the request.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IResourceRequest> LoadResource(ResourceID resourceId, std::span<const std::type_index> interfaceTypes, 
			std::move_only_function<void(const IResourceRequest&) noexcept> callback = nullptr) const = 0;
		/// @brief Loads a resource with type check.
		/// @tparam Args Interface type that the resource must provide.
		/// @param resourceId Resource ID. Must be valid.
		/// @param callback Callback. Can be nullptr.
		/// @return Resource request.
		/// @note The request and the callback must be kept alive till the finish of the request.
		/// @note The function is thread-safe.
		template<typename... Args> [[nodiscard("Pure function")]]
		std::shared_ptr<IResourceRequest> LoadResource(ResourceID resourceId, std::move_only_function<void(const IResourceRequest&) noexcept> callback = nullptr) const;

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
	bool IResourceService::HasInterface(const ResourceID resourceId, const std::type_index type) const
	{
		return HasInterfaces(resourceId, std::span(&type, 1uz));
	}

	template<typename... Args>
	bool IResourceService::HasInterfaces(const ResourceID resourceId) const
	{
		return HasInterfaces(resourceId, std::array<std::type_index, sizeof...(Args)>{typeid(Args)...});
	}

	std::shared_ptr<IResourceRequest> IResourceService::LoadResource(const ResourceID resourceId, std::move_only_function<void(const IResourceRequest&) noexcept> callback) const
	{
		return LoadResource(resourceId, std::span<const std::type_index>(), std::move(callback));
	}

	std::shared_ptr<IResourceRequest> IResourceService::LoadResource(const ResourceID resourceId, const std::type_index interfaceType, 
		std::move_only_function<void(const IResourceRequest&) noexcept> callback) const
	{
		return LoadResource(resourceId, std::span(&interfaceType, 1uz), std::move(callback));
	}

	template<typename... Args>
	std::shared_ptr<IResourceRequest> IResourceService::LoadResource(const ResourceID resourceId, std::move_only_function<void(const IResourceRequest&) noexcept> callback) const
	{
		return LoadResource(resourceId, std::array<std::type_index, sizeof...(Args)>{typeid(Args)...}, std::move(callback));
	}
}
