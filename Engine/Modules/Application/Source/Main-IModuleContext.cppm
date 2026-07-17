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

export module PonyEngine.Application:IModuleContext;

import PonyEngine.Log;

import :IApplication;
import :IService;
import :ITickable;

export namespace PonyEngine::Application
{
	/// @brief Module context. It's a context used by modules.
	class IModuleContext
	{
		PONY_INTERFACE_BODY(IModuleContext)

		/// @brief Gets the application.
		/// @return Application. It's stable and can be saved and used between start-up and shut-down.
		[[nodiscard("Pure function")]]
		virtual IApplication& Application() noexcept = 0;
		/// @brief Gets the application.
		/// @return Application. It's stable and can be saved and used between start-up and shut-down.
		[[nodiscard("Pure function")]]
		virtual const IApplication& Application() const noexcept = 0;

		/// @brief Checks if the engine has a set logger.
		/// @return @a True if it has; @a false otherwise.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual bool HasLogger() const noexcept = 0;
		/// @brief Sets the logger.
		/// @param logger Logger to set. Must be alive till it's unset.
		/// @note Only one logger may be set.
		/// @note The function must be called on a main thread.
		/// @note The function may be called only during start-up.
		virtual void SetLogger(Log::ILogger& logger) = 0;
		/// @brief Unsets the logger.
		/// @param logger Logger to unset. Must be a previously set logger.
		/// @note The function must be called on a main thread.
		/// @note The function may be called only during start-up or shut-down.
		virtual void UnsetLogger(Log::ILogger& logger) = 0;

		/// @brief Adds the service.
		/// @param service Service to add. Must be unique. Must be alive till it's removed.
		/// @note The function must be called on a main thread.
		/// @note The function may be called only during start-up.
		virtual void AddService(IService& service) = 0;
		/// @brief Removes the service.
		/// @param service Service to remove. Must be previously added.
		/// @note The function must be called on a main thread.
		/// @note The function may be called only during start-up or shut-down.
		virtual void RemoveService(IService& service) = 0;

		/// @brief Adds the interface.
		/// @param type Interface type. Must be unique.
		/// @param interface Interface. Mustn't be nullptr. Must be alive till it's removed.
		/// @note The function must be called on a main thread.
		/// @note The function may be called only during start-up.
		virtual void AddInterface(std::type_index type, void* interface) = 0;
		/// @brief Adds the interface.
		/// @tparam T Interface type. Must be unique.
		/// @param interface Interface. Must be alive till it's removed.
		/// @note The function must be called on a main thread.
		/// @note The function may be called only during start-up.
		template<typename T>
		void AddInterface(T& interface);
		/// @brief Removes the interface.
		/// @param type Interface type.
		/// @param interface Interface. Must be a previously added interface.
		/// @note The function must be called on a main thread.
		/// @note The function may be called only during start-up or shut-down.
		virtual void RemoveInterface(std::type_index type, void* interface) = 0;
		/// @brief Removes the interface.
		/// @tparam T Interface type.
		/// @param interface Interface. Must be a previously added interface.
		/// @note The function must be called on a main thread.
		/// @note The function may be called only during start-up or shut-down.
		template<typename T>
		void RemoveInterface(T& interface);

		/// @brief Adds the tickable.
		/// @param tickable Tickable to add. Must be alive till it's removed.
		/// @param order Tickable order.
		/// @note The function must be called on a main thread.
		/// @note The function may be called only during start-up.
		virtual void AddTickable(ITickable& tickable, std::int32_t order) = 0;
		/// @brief Removes the tickable.
		/// @param tickable Tickable. Must be previously added.
		/// @param order Tickable order.
		/// @note The function must be called on a main thread.
		/// @note The function may be called only during start-up or shut-down.
		virtual void RemoveTickable(ITickable& tickable, std::int32_t order) = 0;
	};
}

namespace PonyEngine::Application
{
	template<typename T>
	void IModuleContext::AddInterface(T& interface)
	{
		AddInterface(typeid(T), &interface);
	}

	template<typename T>
	void IModuleContext::RemoveInterface(T& interface)
	{
		RemoveInterface(typeid(T), &interface);
	}
}
