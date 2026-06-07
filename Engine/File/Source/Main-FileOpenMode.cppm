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

export module PonyEngine.File:FileOpenMode;

import std;

export namespace PonyEngine::File
{
	enum class FileOpenMode : std::uint8_t
	{
		None = 0,
		Truncate = 1 << 0,
		All = (1 << 1) - 1
	};

	PONY_ENUM_MASK_FEATURES(FileOpenMode)
}

namespace PonyEngine::File
{
	constexpr std::array<std::string_view, 1> FileOpenModeNames
	{
		"Truncate"
	};
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::File::FileOpenMode, PonyEngine::File::FileOpenModeNames)
}
