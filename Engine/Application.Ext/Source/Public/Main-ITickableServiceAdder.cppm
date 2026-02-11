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

export module PonyEngine.Application.Ext:ITickableServiceAdder;

import std;

import :ITickableService;

export namespace PonyEngine::Application
{
	/// @brief Tickable service adder.
	/// @note All the functions here must be called on a main thread.
	class ITickableServiceAdder
	{
		PONY_INTERFACE_BODY(ITickableServiceAdder)

		/// @brief Adds a tickable service.
		/// @param tickable Tickable service.
		/// @param tickOrder Tick order.
		virtual void Add(ITickableService& tickable, std::int32_t tickOrder) = 0;
	};
}
