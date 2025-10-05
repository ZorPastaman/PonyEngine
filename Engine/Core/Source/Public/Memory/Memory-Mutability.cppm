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

export module PonyEngine.Memory:Mutability;

import std;

namespace PonyEngine::Memory
{
	/// @brief Mutability names.
	constexpr std::array<std::string_view, 2> MutabilityNames
	{
		"Constant",
		"Volatile",
	};
}

export namespace PonyEngine::Memory
{
	/// @brief Mutability.
	enum class Mutability : std::uint8_t
	{
		None = 0,
		Constant = 1 << 0,
		Volatile = 1 << 1,
		All = Constant | Volatile
	};

	ENUM_MASK_FEATURES(Mutability, MutabilityNames)
}

export
{
	ENUM_MASK_FORMATTER(PonyEngine::Memory, Mutability)
}
