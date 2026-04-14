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

export module PonyEngine.RenderDevice:LogicOperation;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class LogicOperation : std::uint8_t
	{
		Noop,
		Clear,
		Set,
		Copy,
		CopyInverted,
		Equivalent,
		Invert,
		And,
		AndReverse,
		AndInverted,
		Nand,
		Or,
		OrReverse,
		OrInverted,
		Xor,
		Nor
	};
}

namespace PonyEngine::RenderDevice
{
	constexpr std::array<std::string_view, 16> LogicOperationNames
	{
		"Noop",
		"Clear",
		"Set",
		"Copy",
		"CopyInverted",
		"Equivalent",
		"Invert",
		"And",
		"AndReverse",
		"AndInverted",
		"Nand",
		"Or",
		"OrReverse",
		"OrInverted",
		"Xor",
		"Nor"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::LogicOperation, PonyEngine::RenderDevice::LogicOperationNames)
}
