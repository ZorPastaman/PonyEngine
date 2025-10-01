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
		Math::Rect<std::int32_t> clientRect = Math::Rect<std::int32_t>(Math::Vector2<std::int32_t>(320, 240)); ///< Client rectangle. On platforms that don't support client rectangles, it's ignored.
		Math::Vector2<std::int32_t> minimalClientSize = Math::Vector2<std::int32_t>(640, 480); ///< Minimal size. On platforms that don't support client rectangles, it's ignored.
		Math::ColorRGB<std::uint8_t> backgroundColor = Math::ColorRGB<std::uint8_t>::Black(); ///< Background color.
		SurfaceStyle style = SurfaceStyle::All; ///< Surface style.
		std::optional<Math::Rect<std::int32_t>> cursorClippingRect; ///< Cursor clipping rect. On platforms that don't support cursors, it's ignored.
		bool showCursor = true; ///< Show cursor. On platforms that don't support cursors, it's ignored.
	};
}
