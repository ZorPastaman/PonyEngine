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
	/// @brief Resource availability.
	enum class ResourceAvailability : std::uint8_t
	{
		None = 0, ///< Not available.
		Loadable = 1 << 0, ///< Available as a loadable resource.
		File = 1 << 1, ///< Available as a file resource.
		Memory = 1 << 2, ///< Available as a memory resource.
		All = (1 << 3) - 1
	};

	PONY_ENUM_MASK_FEATURES(ResourceAvailability)
}

namespace PonyEngine::Resource
{
	/// @brief Resource availability names.
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
