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

export module PonyEngine.Resource.Pack:AccessType;

import std;

export namespace PonyEngine::Resource::Pack
{
	enum class AccessType : std::uint8_t
	{
		None = 0,
		Loadable = 1 << 0,
		File = 1 << 1,
		Memory = 1 << 2,
		All = (1 << 3) - 1
	};

	PONY_ENUM_MASK_FEATURES(AccessType)
}

namespace PonyEngine::Resource::Pack
{
	constexpr std::array<std::string_view, 3> AccessTypeNames
	{
		"Loadable",
		"File",
		"Memory"
	};
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::Resource::Pack::AccessType, PonyEngine::Resource::Pack::AccessTypeNames)
}
