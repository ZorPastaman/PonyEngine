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
		Available,
		NotAvailable,
		VariantNotAvailable
	};
}

namespace PonyEngine::Resource
{
	constexpr std::array<std::string_view, 3> ResourceAvailabilityNames
	{
		"Available",
		"NotAvailable",
		"VariantNotAvailable"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::Resource::ResourceAvailability, PonyEngine::Resource::ResourceAvailabilityNames)
}
