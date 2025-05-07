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

export module PonyEngine.Render:LogicOperation;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render
{
	/// @brief Logic operation names.
	constexpr std::array<std::string_view, 17> LogicOperationNames
	{
		"Noop",
		"Clear",
		"Set",
		"Copy",
		"CopyInverted",
		"Invert",
		"And",
		"AndReverse",
		"AndInverted",
		"Nand",
		"Or",
		"OrReverse",
		"OrInverted",
		"Nor",
		"Xor",
		"Equal",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Logic operation.
	enum class LogicOperation : std::uint8_t
	{
		Noop,
		Clear,
		Set,
		Copy,
		CopyInverted,
		Invert,
		And,
		AndReverse,
		AndInverted,
		Nand,
		Or,
		OrReverse,
		OrInverted,
		Nor,
		Xor,
		Equal
	};

	ENUM_VALUE_FEATURES(LogicOperation, LogicOperationNames)
}
