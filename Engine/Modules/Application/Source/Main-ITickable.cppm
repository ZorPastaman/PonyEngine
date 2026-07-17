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

export module PonyEngine.Application:ITickable;

export namespace PonyEngine::Application
{
	/// @brief Tickable object.
	class ITickable
	{
		PONY_INTERFACE_BODY(ITickable)

		/// @brief Ticks the object.
		/// @note The function is always called on a main thread.
		virtual void Tick() = 0;
	};
}
