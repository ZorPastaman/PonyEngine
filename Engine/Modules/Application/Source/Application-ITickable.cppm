/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Application:ITickable;

export namespace PonyEngine::Application
{
	/// @brief Tickable object.
	class ITickable
	{
		PONY_INTERFACE_BODY(ITickable)

		/// @brief Begins the tickable.
		/// @details It's called once before a first application tick.
		/// @note The function is always called on a main thread.
		virtual void Begin() {}
		/// @brief Ends the tickable.
		/// @details It's called once after a last application tick.
		/// @note The function is always called on a main thread.
		virtual void End() {}
		/// @brief Ticks the tickable.
		/// @note The function is always called on a main thread.
		virtual void Tick() {}
	};
}
