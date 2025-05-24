/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Enum.h"

export module PonyEngine.Render.Direct3D12:HeapType;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render::Direct3D12
{
	/// @brief Heap type names.
	constexpr std::array<std::string_view, 4> HeapTypeNames
	{
		"Default",
		"Upload",
		"Readback",
		"Unknown"
	};
}

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Heap type.
	enum class HeapType : std::uint8_t
	{
		Default,
		Upload,
		Readback
	};

	ENUM_VALUE_FEATURES(HeapType, HeapTypeNames)
}
