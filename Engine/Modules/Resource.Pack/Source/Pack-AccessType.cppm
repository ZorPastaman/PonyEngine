/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Enum.h"

export module PonyEngine.Resource.Pack:AccessType;

import std;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Pack data access type.
	enum class AccessType : std::uint8_t
	{
		None = 0,
		Loadable = 1 << 0, ///< A pack data is available via @p ILoadableDataAccess.
		File = 1 << 1, ///< A pack data is available via @p IFileDataAccess.
		Memory = 1 << 2, ///< A pack data is available via @p IMemoryDataAccess.
		All = (1 << 3) - 1
	};

	PONY_ENUM_MASK_FEATURES(AccessType)
}

namespace PonyEngine::Resource::Pack
{
	/// @brief Pack data access type names.
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
