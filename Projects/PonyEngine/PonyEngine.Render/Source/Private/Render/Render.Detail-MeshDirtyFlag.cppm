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

export module PonyEngine.Render.Detail:MeshDirtyFlag;

import <array>;
import <bit>;
import <cstdint>;
import <ostream>;
import <string>;
import <string_view>;
import <type_traits>;

namespace PonyEngine::Render
{
	/// @brief Mesh dirty flag names.
	constexpr std::array<std::string_view, 3> MeshDirtyFlagNames
	{
		"DataStructure",
		"Name",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Mesh dirty flag.
	enum class MeshDirtyFlag : std::uint8_t
	{
		None = 0,
		DataStructure = 1 << 0,
		Name = 1 << 1,
		All = DataStructure | Name
	};

	ENUM_MASK_FEATURES(MeshDirtyFlag, MeshDirtyFlagNames)
}
