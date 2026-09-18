/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.File:IFileService;

import std;

import :FileParams;
import :IFile;

export namespace PonyEngine::File
{
	/// @brief File service.
	class IFileService
	{
		PONY_INTERFACE_BODY(IFileService)

		/// @brief Opens a file.
		/// @param path File path. Must be valid.
		/// @param params File parameters.
		/// @return File.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IFile> OpenFile(std::filesystem::path path, FileParams params) = 0;
	};
}
