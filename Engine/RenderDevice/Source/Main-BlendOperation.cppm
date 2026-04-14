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

export module PonyEngine.RenderDevice:BlendOperation;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Blend operation.
	enum class BlendOperation : std::uint8_t
	{
		Add,
		Subtract,
		ReverseSubtract,
		Min,
		Max
	};
}

namespace PonyEngine::RenderDevice
{
	/// @brief Blend operation names.
	constexpr std::array<std::string_view, 5> BlendOperationNames
	{
		"Add",
		"Subtract",
		"ReverseSubtract",
		"Min",
		"Max"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::BlendOperation, PonyEngine::RenderDevice::BlendOperationNames)
}
