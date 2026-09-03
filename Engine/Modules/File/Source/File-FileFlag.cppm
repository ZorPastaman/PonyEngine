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

export module PonyEngine.File:FileFlag;

import std;

export namespace PonyEngine::File
{
	/// @brief File flags. May provide some functionality or optimization hints.
	enum class FileFlag : std::uint8_t
	{
		None = 0,
		SequentialScan = 1 << 0, ///< A file will be accessed in the sequential order from begin to end.
		RandomAccess = 1 << 1, ///< A file will be accessed in the random order.
		DeleteOnClose = 1 << 2, ///< A file must be deleted on close.
		WriteThrough = 1 << 3, ///< Write operations must be executed directly to a disk, bypassing a buffer.
		All = (1 << 4) - 1,
	};

	PONY_ENUM_MASK_FEATURES(FileFlag)
}

namespace PonyEngine::File
{
	/// @brief File flag names.
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
