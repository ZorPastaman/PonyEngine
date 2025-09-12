/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Application:ITickableService;

import :IService;

export namespace PonyEngine::Application
{
	/// @brief Tickable service.
	class ITickableService : public IService
	{
		INTERFACE_BODY(ITickableService)

		/// @brief Ticks the service.
		virtual void Tick() = 0;
	};
}
