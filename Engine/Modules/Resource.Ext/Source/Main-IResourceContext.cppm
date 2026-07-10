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

export module PonyEngine.Resource.Ext:IResourceContext;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Resource;

export namespace PonyEngine::Resource
{
	/// @brief Resource service context.
	class IResourceContext
	{
		PONY_INTERFACE_BODY(IResourceContext)

		/// @brief Gets the application context.
		/// @return Application context.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept = 0;
		/// @brief Gets the application context.
		/// @return Application context.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept = 0;

		/// @brief Gets the logger.
		/// @return Logger.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept = 0;

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
