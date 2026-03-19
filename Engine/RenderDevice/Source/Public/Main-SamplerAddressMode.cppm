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

export module PonyEngine.RenderDevice:SamplerAddressMode;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Sampler address mode.
	enum class SamplerAddressMode : std::uint8_t
	{
		Wrap,
		Mirror,
		Clamp
	};
}

namespace PonyEngine::RenderDevice
{
	/// @brief Sampler address mode names.
	constexpr std::array<std::string_view, 3> SamplerAddressModeNames
	{
		"Wrap",
		"Mirror",
		"Clamp"
	};
}

export 
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::SamplerAddressMode, PonyEngine::RenderDevice::SamplerAddressModeNames)
}
