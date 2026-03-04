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

export module PonyEngine.RenderDevice:HeapType;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Heap type.
	enum class HeapType : std::uint8_t
	{
		Default,
		Upload,
		Download
	};

	/// @brief Heap type mask.
	enum class HeapTypeMask : std::uint8_t
	{
		None = 0,
		Default = 1 << 0,
		Upload = 1 << 1,
		Download = 1 << 2,
		All = (1 << 3) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(HeapType, HeapTypeMask)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Heap type names.
	constexpr std::array<std::string_view, 3> HeapTypeNames
	{
		"Default",
		"Upload",
		"Download"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::HeapType, PonyEngine::RenderDevice::HeapTypeNames)
	PONY_ENUM_MASK_FORMATTER(PonyEngine::RenderDevice::HeapTypeMask, PonyEngine::RenderDevice::HeapTypeNames)
}
