/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Surface.Extension:SurfaceParams;

import std;

import PonyEngine.Math;
import PonyEngine.Surface;

export namespace PonyEngine::Surface
{
	/// @brief Surface parameters.
	struct SurfaceParams
	{
		std::string title = "Pony Engine"; ///< Title.
		SurfaceRect rect = SurfaceRect{.position = Math::Vector2<std::int32_t>::Zero(), .size = Math::Vector2<std::int32_t>(640, 480), .positionMode = SurfacePositionMode::Center}; ///< Window rect. On platforms that don't support windows, it's ignored.
		Math::Vector2<std::int32_t> minimalSize = Math::Vector2<std::int32_t>(640, 480); ///< Minimal size. On platforms that don't support windows, it's ignored.
		Math::ColorRGB<std::uint8_t> backgroundColor = Math::ColorRGB<std::uint8_t>::Black(); ///< Background color.
		SurfaceStyle style = SurfaceStyle::All; ///< Surface style.
	};
}
