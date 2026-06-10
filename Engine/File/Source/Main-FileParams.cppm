/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.File:FileParams;

import std;

import :FileAccess;
import :FileFlag;
import :FileOpenMode;

export namespace PonyEngine::File
{
	/// @brief File parameters.
	struct FileParams final
	{
		std::filesystem::path path; /// File path. Must be valid.
		FileAccess access = FileAccess::None; ///< File access mode.
		FileOpenMode openMode = FileOpenMode::None; ///< File open mode.
		FileFlag flags = FileFlag::None; ///< File flags.
	};
}
