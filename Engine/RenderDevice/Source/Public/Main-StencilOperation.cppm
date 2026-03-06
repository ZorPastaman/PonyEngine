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

export module PonyEngine.RenderDevice:StencilOperation;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Stencil operation.
	enum class StencilOperation : std::uint8_t
	{
		Keep,
		Zero,
		Replace,
		Invert,
		IncrementAndClamp,
		DecrementAndClamp,
		IncrementAndWrap,
		DecrementAndWrap
	};
}

namespace PonyEngine::RenderDevice
{
	/// @brief Stencil operation names.
	constexpr std::array<std::string_view, 8> StencilOperationNames
	{
		"Keep",
		"Zero",
		"Replace",
		"Invert",
		"IncrementAndClamp",
		"DecrementAndClamp",
		"IncrementAndWrap",
		"DecrementAndWrap"
	};
}

export 
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::StencilOperation, PonyEngine::RenderDevice::StencilOperationNames)
}
