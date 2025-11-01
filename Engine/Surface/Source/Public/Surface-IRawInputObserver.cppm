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

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Surface:IRawInputObserver;

import std;

import PonyEngine.Math;

#if PONY_WINDOWS
export namespace PonyEngine::Surface::Windows
{
	/// @brief Window raw input observer.
	class IRawInputObserver
	{
		INTERFACE_BODY(IRawInputObserver)

		/// @brief Observes raw input.
		/// @param input Raw input to observe.
		/// @param eventTime Event time. It's a low resolution time point.
		/// @param cursorPosition Event cursor position in screen coordinates.
		virtual void Observe(const RAWINPUT& input, std::chrono::time_point<std::chrono::steady_clock> eventTime, const Math::Vector2<std::int32_t>& cursorPosition) = 0;
	};
}
#endif
