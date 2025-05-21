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

export module PonyEngine.Render.Detail:RootSignatureDirtyFlag;

import <array>;
import <bit>;
import <cstdint>;
import <ostream>;
import <string>;
import <string_view>;
import <type_traits>;

namespace PonyEngine::Render
{
	/// @brief Root signature dirty flag names.
	constexpr std::array<std::string_view, 2> RootSignatureDirtyFlagNames
	{
		"Name",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Root signature dirty flag.
	enum class RootSignatureDirtyFlag : std::uint8_t
	{
		None = 0,
		Name = 1 << 0,
		All = Name
	};

	ENUM_MASK_FEATURES(RootSignatureDirtyFlag, RootSignatureDirtyFlagNames)
}
