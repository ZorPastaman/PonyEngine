/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Type/Enum.h"

export module PonyEngine.Surface:SurfaceFeature;

import std;

namespace PonyEngine::Surface
{
	/// @brief Surface feature names.
	std::array<std::string_view, 5> SurfaceFeatureNames
	{
		"Fullscreen Style",
		"Window Style",
		"Client Rect",
		"Title",
		"Hardware Cursor"
	};
}

export namespace PonyEngine::Surface
{
	/// @brief Surface feature.
	enum class SurfaceFeature : std::uint8_t
	{
		FullscreenStyle = 1 << 0, ///< Supports fullscreen rectangle style.
		WindowStyle = 1 << 1, ///< Supports window rectangle style.
		ClientRect = 1 << 2, ///< Supports client rectangle control (move, resize, etc.).
		Title = 1 << 3, ///< Supports title control.
		HardwareCursor = 1 << 4, ///< Supports hardware cursor control. If not, the virtual cursor must be used.
		All = FullscreenStyle | WindowStyle | ClientRect | Title | HardwareCursor
	};

	PONY_ENUM_MASK_FEATURES(SurfaceFeature)
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::Surface::SurfaceFeature, PonyEngine::Surface::SurfaceFeatureNames)
}
