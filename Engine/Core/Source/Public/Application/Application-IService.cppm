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

export module PonyEngine.Application:IService;

export namespace PonyEngine::Application
{
	/// @brief Service
	class IService
	{
		INTERFACE_BODY(IService)

		/// @brief Begins the service.
		/// @details It's called once before a first application tick.
		virtual void Begin() = 0;
		/// @brief Ends the service.
		/// @details It's called once after a last application tick.
		virtual void End() = 0;
	};
}
