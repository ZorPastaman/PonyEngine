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

import std;

import PonyEngine.Display;
import PonyEngine.Math;

export namespace PonyEngine::Display
{
	/// @brief Display state.
	struct DisplayState final
	{
		std::string sourceName; ///< Display source name.
		std::string targetName; ///< Display target name.
		std::string friendlyTargetName; ///< Display friendly target name.

		Math::Vector2<std::uint32_t> resolution; ///< Display resolution in pixels.
		Math::Rational<std::uint32_t> refreshRate; ///< Display refresh rate.

		Math::Vector2<LONG> position; ///< Display virtual position.

		float sdrWhiteLevel = 0.f; ///< SDR mode white level in nits.
		ColorMode colorMode = ColorMode::SDR; ///< Display active color mode.
		std::uint8_t bitsPerColorChannel = 0u; ///< How many bits per color channel the display supports.

		bool isConnected = false; ///< Is a display connected?
	};
}
