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

export module PonyEngine.Resource:ResourceAvailability;

import std;

export namespace PonyEngine::Resource
{
	enum class ResourceAvailability : std::uint8_t
	{
		None = 0,
		Loadable = 1 << 0,
		File = 1 << 1,
		Memory = 1 << 2,
		All = (1 << 3) - 1
	};

	PONY_ENUM_MASK_FEATURES(ResourceAvailability)
}

namespace PonyEngine::Resource
{
	constexpr std::array<std::string_view, 3> ResourceAvailabilityNames
	{
		"Loadable",
		"File",
		"Memory"
	};
}

export 
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::Resource::ResourceAvailability, PonyEngine::Resource::ResourceAvailabilityNames)
}
