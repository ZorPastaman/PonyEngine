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
import :FileFlag;
import :IReadHandler;
import :IReadRequest;
import :IWriteHandler;
import :IWriteRequest;
import :ReadParams;
import :WriteParams;

export namespace PonyEngine::File
{
	/// @brief File.
	class IFile
	{
		PONY_INTERFACE_BODY(IFile)

		/// @brief Gets the file path.
		/// @return File path.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& Path() const noexcept = 0;
		/// @brief Gets the file access.
		/// @return File access.
		[[nodiscard("Pure function")]]
		virtual FileAccess Access() const noexcept = 0;
		/// @brief Gets the file flags.
		/// @return File flags.
		[[nodiscard("Pure function")]]
		virtual FileFlag Flags() const noexcept = 0;

		/// @brief Makes a read request.
		/// @param params Read parameters.
		/// @param handler Request handler. May be nullptr.
		/// @return Read request.
		/// @remark The handler may be called on an io thread or on the thread this function was called on if the request is completed immediately.
		/// @remark The handler may be called before this function returns.
		/// @remark The handler mustn't do expensive operations, it should return as fast as possible. If you need to parse data or something else, do it on another thread.
		/// @note The file, request, buffer and the handler must be kept alive till the finish of the operation.
		/// @note The function is thread-safe.
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<IReadRequest> Read(const ReadParams& params, IReadHandler* handler = nullptr) const = 0;
		/// @brief Makes a write request.
		/// @param params Write parameters.
		/// @param handler Request handler. May be nullptr.
		/// @return Write request.
		/// @remark The handler may be called on an io thread or on the thread this function was called on if the request is completed immediately.
		/// @remark The handler may be called before this function returns.
		/// @remark The handler mustn't do expensive operations, it should return as fast as possible. If you need to parse data or something else, do it on another thread.
		/// @note The file, request, buffer and the handler must be kept alive till the finish of the operation.
		/// @note The function is thread-safe.
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<IWriteRequest> Write(const WriteParams& params, IWriteHandler* handler = nullptr) = 0;
	};
}
