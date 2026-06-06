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

export module PonyEngine.File:IFile;

import std;

import :FileAccess;
import :IReadRequest;
import :IWriteRequest;
import :ReadParams;
import :WriteParams;

export namespace PonyEngine::File
{
	class IFile
	{
		PONY_INTERFACE_BODY(IFile)

		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& Path() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual FileAccess Access() const noexcept = 0;

		virtual std::shared_ptr<IReadRequest> Read(const ReadParams& params, const std::function<void(const IReadRequest&)>* callback = nullptr) const = 0;
		virtual std::shared_ptr<IWriteRequest> Write(const WriteParams& params, const std::function<void(const IWriteRequest&)>* callback = nullptr) = 0;
	};
}
