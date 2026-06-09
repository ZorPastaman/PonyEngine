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

export module PonyEngine.File:FileFlag;

import std;

export namespace PonyEngine::File
{
	enum class FileFlag : std::uint8_t
	{
		None = 0,
		SequentialScan = 1 << 0,
		RandomAccess = 1 << 1,
		DeleteOnClose = 1 << 2,
		WriteThrough = 1 << 3,
		All = (1 << 4) - 1,
	};

	PONY_ENUM_MASK_FEATURES(FileFlag)
}

namespace PonyEngine::File
{
	constexpr std::array<std::string_view, 4> FileFlagNames
	{
		"SequentialScan",
		"RandomAccess",
		"DeleteOnClose",
		"WriteThrough"
	};
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::File::FileFlag, PonyEngine::File::FileFlagNames)
}
