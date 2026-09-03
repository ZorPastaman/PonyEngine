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

export module PonyEngine.File:FileAccess;

import std;

export namespace PonyEngine::File
{
	/// @brief File access mode.
	enum class FileAccess : std::uint8_t
	{
		None = 0,
		Read = 1 << 0,
		Write = 1 << 1,
		All = (1 << 2) - 1,
	};

	PONY_ENUM_MASK_FEATURES(FileAccess)
}

namespace PonyEngine::File
{
	/// @brief File access mode names.
	constexpr std::array<std::string_view, 2> FileAccessNames
	{
		"Read",
		"Write"
	};
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::File::FileAccess, PonyEngine::File::FileAccessNames)
}
