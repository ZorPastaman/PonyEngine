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

export module PonyEngine.File:ReadMode;

import std;

namespace PonyEngine::File
{
	/// @brief Read mode names.
	constexpr std::array<std::string_view, 1> ReadModeNames
	{
		"Text"
	};
}

export namespace PonyEngine::File
{
	/// @brief Read mode.
	enum class ReadMode : std::uint8_t
	{
		None = 0,
		Text = 1 << 0, ///< If set, the file is read as a text file; otherwise it's read as a binary file.
		All = Text
	};

	ENUM_MASK_FEATURES(ReadMode, ReadModeNames)
}

export
{
	ENUM_MASK_FORMATTER(PonyEngine::File, ReadMode)
}
