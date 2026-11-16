/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

export module PonyEngine.Display.Impl.WinAPI:DisplayState;

import PonyEngine.Math;

export namespace PonyEngine::Display
{
	/// @brief Display state.
	struct DisplayState final
	{
		Math::Vector2<UINT32> resolution; ///< Display resolution in pixels.
		Math::Rational<UINT32> refreshRate; ///< Display refresh rate.

		Math::Vector2<LONG> position; ///< Display virtual position.

		bool isConnected = false; ///< Is a display connected?
	};
}
