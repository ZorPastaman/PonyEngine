/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.File:IFileService;

import std;

import :FileAccess;
import :IFile;

export namespace PonyEngine::File
{
	class IFileService
	{
		PONY_INTERFACE_BODY(IFileService)

		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IFile> OpenFile(const std::filesystem::path& path, FileAccess access, bool truncate = false) = 0;
	};
}
