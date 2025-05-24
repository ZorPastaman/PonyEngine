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

export module PonyEngine.Render.Core:BufferDirtyFlag;

import <array>;
import <bit>;
import <cstdint>;
import <ostream>;
import <string>;
import <string_view>;
import <type_traits>;

namespace PonyEngine::Render::Core
{
	/// @brief Buffer dirty flag names.
	constexpr std::array<std::string_view, 4> BufferDirtyFlagNames
	{
		"DataStructure",
		"Data"
		"Name",
		"Unknown"
	};
}

export namespace PonyEngine::Render::Core
{
	/// @brief Buffer dirty flag.
	enum class BufferDirtyFlag : std::uint8_t
	{
		None = 0,
		DataStructure = 1 << 0,
		Data = 1 << 1,
		Name = 1 << 2,
		All = DataStructure | Data | Name
	};

	ENUM_MASK_FEATURES(BufferDirtyFlag, BufferDirtyFlagNames)
}
