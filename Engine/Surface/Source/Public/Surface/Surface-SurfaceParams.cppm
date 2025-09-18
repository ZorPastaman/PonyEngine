/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Surface:SurfaceParams;

import std;

import PonyEngine.Math;

import :SurfacePositionMode;
import :SurfaceStyle;
import :WindowRect;

namespace PonyEngine::Surface
{
	/// @brief Surface parameters.
	struct SurfaceParams final
	{
		std::string title = "Pony Engine Window"; ///< Title.
		WindowRect rect; ///< Window rect. On platforms that don't support windows, it's ignored.
		Math::Vector2<std::int32_t> minimalSize = Math::Vector2<std::int32_t>(640, 480); ///< Minimal size. On platforms that don't support windows, it's ignored.
		Math::ColorRGB<std::uint8_t> backgroundColor = Math::ColorRGB<std::uint8_t>::Black(); ///< Background color.
		SurfaceStyle style = SurfaceStyle::None; ///< Surface style.
	};
}
