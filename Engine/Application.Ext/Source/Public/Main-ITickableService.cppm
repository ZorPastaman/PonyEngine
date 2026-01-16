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

export module PonyEngine.Application.Ext:ITickableService;

export namespace PonyEngine::Application
{
	/// @brief Tickable service.
	class ITickableService
	{
		PONY_INTERFACE_BODY(ITickableService)

		/// @brief Ticks the service.
		virtual void Tick() = 0;
	};
}
