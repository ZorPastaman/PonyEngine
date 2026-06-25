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

		[[nodiscard("Pure function")]]
		virtual ResourceID MakeResourceID(std::string_view resourceId) = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsResourceIDValid(ResourceID resourceId) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view GetResourceIDString(ResourceID resourceId) const = 0;

		[[nodiscard("Pure function")]]
		virtual struct ResourceType MakeResourceType(std::string_view type) = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsResourceTypeValid(struct ResourceType type) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view GetResourceTypeString(struct ResourceType type) const = 0;
	};
}
