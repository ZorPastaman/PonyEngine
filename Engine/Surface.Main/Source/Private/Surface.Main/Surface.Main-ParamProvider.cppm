/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Surface.Main:ParamProvider;

import std;

import PonyEngine.Math;

export namespace PonyEngine::Surface
{
	/// @brief Gets a background color.
	/// @return Background color.
	[[nodiscard("Pure function")]]
	constexpr Math::ColorRGB<std::uint8_t> GetBackgroundColor() noexcept;
}

namespace PonyEngine::Surface
{
	constexpr Math::ColorRGB<std::uint8_t> GetBackgroundColor() noexcept
	{
#ifdef PONY_ENGINE_SURFACE_BACKGROUND_COLOR
		return Math::ColorRGB<std::uint8_t>(PONY_ENGINE_SURFACE_BACKGROUND_COLOR);
#else
		return Math::ColorRGB<std::uint8_t>::Black();
#endif
	}
}
