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

export module PonyEngine.Application.Ext:IService;

import :IServiceInterfaceAdder;
import :ITickableServiceAdder;

export namespace PonyEngine::Application
{
	/// @brief Service
	class IService
	{
		PONY_INTERFACE_BODY(IService)

		/// @brief Begins the service.
		/// @details It's called once before a first application tick.
		virtual void Begin() = 0;
		/// @brief Ends the service.
		/// @details It's called once after a last application tick.
		virtual void End() = 0;

		/// @brief Adds tickable services.
		/// @param adder Tickable service adder.
		virtual void AddTickableServices(ITickableServiceAdder& adder) {}
		/// @brief Adds a service interface.
		/// @param adder Service interface adder.
		virtual void AddInterfaces(IServiceInterfaceAdder& adder) {}
	};
}
