/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Display:DisplayInfo;

import std;

import PonyEngine.Math;

export namespace PonyEngine::Display
{
	/// @brief Display info.
	struct DisplayInfo final
	{
		std::string_view sourceName; ///< Display source name.
		std::string_view targetName; ///< Display target name.
		std::string_view friendlyTargetName; ///< Display friendly target name.

		Math::Vector2<std::uint32_t> resolution; ///< Display resolution in pixels.
		Math::Rational<std::uint32_t> refreshRate; ///< Display refresh rate.
	};
}
