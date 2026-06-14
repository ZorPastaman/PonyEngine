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
		virtual bool HasContextKey(ContextKey key) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::size_t ContextSize() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::optional<ContextValue> GetContextValue(ContextKey key) const noexcept = 0;
		virtual std::size_t GetContext(std::span<std::pair<ContextKey, ContextValue>> context) const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual ContextKey MakeContextKey(std::string_view key) = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsContextKeyValid(ContextKey key) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view GetContextKeyString(ContextKey key) const = 0;
		[[nodiscard("Pure function")]]
		virtual ContextValue MakeContextValue(std::string_view value) = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsContextValueValid(ContextValue value) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view GetContextValueString(ContextValue value) const = 0;

		[[nodiscard("Pure function")]]
		virtual ResourceAvailability IsResourceAvailable(ResourceID resourceId) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual struct ResourceType ResourceType(ResourceID resourceId) const = 0;

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
