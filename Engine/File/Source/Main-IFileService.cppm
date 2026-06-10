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

import :FileParams;
import :IFile;

export namespace PonyEngine::File
{
	/// @brief File service.
	class IFileService
	{
		PONY_INTERFACE_BODY(IFileService)

		/// @brief Opens a file.
		/// @param params File parameters.
		/// @return File.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IFile> OpenFile(const FileParams& params) = 0;
	};
}
