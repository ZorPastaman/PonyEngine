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

namespace PonyEngine::Surface
{
	/// @brief Surface parameters.
	struct SurfaceParams final
	{
		std::string title = "Pony Engine Window"; ///< Title.
		/// @brief Surface position. If it's a floating point, it's treated as a relative rect; otherwise, it's an absolute rect.
		std::variant<Math::Vector2<float>, Math::Vector2<std::int32_t>> position = Math::Vector2<std::int32_t>::Zero();
		/// @brief Surface size. If it's a floating point, it's treated as a relative rect; otherwise, it's an absolute rect.
		std::variant<Math::Vector2<float>, Math::Vector2<std::int32_t>> size = Math::Vector2<float>::One();
		SurfacePositionMode positionMode = SurfacePositionMode::LeftTopCorner; ///< Surface position mode.
		Math::ColorRGB<std::uint8_t> backgroundColor = Math::ColorRGB<std::uint8_t>::Black(); ///< Background color.
		SurfaceStyle style = SurfaceStyle::None; ///< Surface style.
		bool hidden = false; ///< Is hidden by default?
	};
}
