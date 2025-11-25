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

export module PonyEngine.File:WriteMode;

import std;

namespace PonyEngine::File
{
	/// @brief Write mode names.
	constexpr std::array<std::string_view, 5> WriteModeNames
	{
		"Text",
		"Append",
		"End",
		"Discard",
		"Read"
	};
}

export namespace PonyEngine::File
{
	/// @brief Write mode.
	enum class WriteMode : std::uint8_t
	{
		None = 0,
		Text = 1 << 0, ///< If set, the file is written as a text file; otherwise it's written as a binary file.
		Append = 1 << 1, ///< If set, data is appended to the end of the file; otherwise data is written from the current position.
		End = 1 << 2, ///< If set, the stream position is moved to the end of the file upon opening.
		Discard = 1 << 3, ///< If set, the file content is discarded upon opening.
		Read = 1 << 4, ///< If set, the file is opened with the read access.
		All = Text | Append | End | Discard | Read
	};

	ENUM_MASK_FEATURES(WriteMode, WriteModeNames)
}

export
{
	ENUM_MASK_FORMATTER(PonyEngine::File, WriteMode)
}
