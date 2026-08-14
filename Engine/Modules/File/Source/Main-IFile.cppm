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
import :IReadRequest;
import :IReadRequestObserver;
import :IWriteRequest;
import :IWriteRequestObserver;
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
		/// @param observer Observer. Can be nullptr. It will be called on the caller thread or on an io thread.
		/// @return Read request.
		/// @note The buffer and observer must be kept alive till the finish of the operation.
		/// @note The function is thread-safe.
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<IReadRequest> Read(const ReadParams& params, IReadRequestObserver* observer = nullptr) = 0;
		/// @brief Makes a write request.
		/// @param params Write parameters.
		/// @param observer Observer. Can be nullptr. It will be called on the caller thread or on an io thread.
		/// @return Write request.
		/// @note The buffer and observer must be kept alive till the finish of the operation.
		/// @note The function is thread-safe.
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<IWriteRequest> Write(const WriteParams& params, IWriteRequestObserver* observer = nullptr) = 0;
	};
}
