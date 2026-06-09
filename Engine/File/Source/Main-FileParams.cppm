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
	struct FileParams final
	{
		std::filesystem::path path;
		FileAccess access = FileAccess::None;
		FileOpenMode openMode = FileOpenMode::None;
		FileFlag flags = FileFlag::None;
	};
}
