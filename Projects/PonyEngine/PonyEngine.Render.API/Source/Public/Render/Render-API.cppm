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

export module PonyEngine.Render:API;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render
{
	/// @brief Render API names.
	constexpr std::array<std::string_view, 3> APINames
	{
		"None"
		"Direct3D12",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Render API.
	enum class API : std::uint8_t
	{
		None,
		Direct3D12
	};

	ENUM_VALUE_FEATURES(API, APINames)
}
