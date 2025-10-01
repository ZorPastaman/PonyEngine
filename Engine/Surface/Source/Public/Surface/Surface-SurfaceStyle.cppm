/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Enum.h"

export module PonyEngine.Surface:SurfaceStyle;

import std;

namespace PonyEngine::Surface
{
	/// @brief Surface style names.
	constexpr std::array<std::string_view, 8> SurfaceStyleNames
	{
		"Border",
		"Title",
		"Close",
		"Maximize",
		"Minimize",
		"Movable",
		"Resizable",
		"AlwaysOnTop"
	};
}

export namespace PonyEngine::Surface
{
	/// @brief Surface style.
	/// @remark Unsupported styles are just ignored.
	/// @remark Some styles may force other styles on some platforms.
	enum class SurfaceStyle : std::uint8_t
	{
		None = 0,
		Border = 1 << 0, ///< Draw border.
		Title = 1 << 1, ///< Draw title.
		Close = 1 << 2, ///< Draw close button.
		Maximize = 1 << 3, ///< Draw maximize button.
		Minimize = 1 << 4, ///< Draw minimize button.
		Movable = 1 << 5, ///< Movable surface.
		Resizable = 1 << 6, ///< Resizable surface.
		AlwaysOnTop = 1 << 7, ///< Show always on top.
		All = Border | Title | Close | Maximize | Minimize | Movable | Resizable | AlwaysOnTop
	};

	ENUM_MASK_FEATURES(SurfaceStyle, SurfaceStyleNames)
}

export
{
	ENUM_MASK_FORMATTER(PonyEngine::Surface, SurfaceStyle)
}
