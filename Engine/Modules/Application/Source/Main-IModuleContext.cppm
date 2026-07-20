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

import :IApplication;
import :ITickable;
import :TickOrder;

export namespace PonyEngine::Application
{
	/// @brief Module context. It's a context used by modules.
	/// @note All the function in the module context must be called only on a main thread.
	class IModuleContext
	{
		PONY_INTERFACE_BODY(IModuleContext)

		/// @brief Gets the application.
		/// @return Application. Its reference is stable and can be used till the module shut-down.
		[[nodiscard("Pure function")]]
		virtual IApplication& Application() noexcept = 0;
		/// @brief Gets the application.
		/// @return Application. Its reference is stable and can be used till the module shut-down.
		[[nodiscard("Pure function")]]
		virtual const IApplication& Application() const noexcept = 0;

		/// @brief Adds the interface.
		/// @param type Interface type. Must be unique.
		/// @param interface Interface. Mustn't be nullptr. Must be alive till it's removed.
		/// @note The function may be called only during start-up.
		virtual void AddInterface(std::type_index type, void* interface) = 0;
		/// @brief Adds the interface.
		/// @tparam T Interface type. Must be unique.
		/// @param interface Interface. Must be alive till it's removed.
		/// @note The function may be called only during start-up.
		template<typename T>
		void AddInterface(T& interface);
		/// @brief Removes the interface.
		/// @param type Interface type.
		/// @param interface Interface. Must be a previously added interface.
		/// @note The function may be called only during start-up or shut-down.
		virtual void RemoveInterface(std::type_index type, void* interface) = 0;
		/// @brief Removes the interface.
		/// @tparam T Interface type.
		/// @param interface Interface. Must be a previously added interface.
		/// @note The function may be called only during start-up or shut-down.
		template<typename T>
		void RemoveInterface(T& interface);

		/// @brief Adds the tickable.
		/// @param tickable Tickable to add. Must be alive till it's removed.
		/// @param tickableOrder Tickable order.
		/// @note The function may be called only during start-up.
		/// @remark The same tickable may be added many times.
		virtual void AddTickable(ITickable& tickable, const TickableOrder& tickableOrder) = 0;
		/// @brief Removes the tickable.
		/// @param tickable Tickable. Must be previously added.
		/// @param tickableOrder Tickable order.
		/// @note The function may be called only during start-up or shut-down.
		virtual void RemoveTickable(ITickable& tickable, const TickableOrder& tickableOrder) = 0;
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
