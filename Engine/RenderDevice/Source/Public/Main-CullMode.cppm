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

export module PonyEngine.RenderDevice:CullMode;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Cull mode.
	enum class CullMode : std::uint8_t
	{
		NoCulling,
		Front,
		Back
	};
}

namespace PonyEngine::RenderDevice
{
	/// @brief Cull mode names.
	constexpr std::array<std::string_view, 3> CullModeNames
	{
		"NoCulling",
		"Front",
		"Back"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::CullMode, PonyEngine::RenderDevice::CullModeNames)
}
