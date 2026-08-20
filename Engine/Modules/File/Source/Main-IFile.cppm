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
		/// @param callback Callback. Can be nullptr. It will be called on the caller thread or on an io thread. It may be called before the function returns.
		/// @return Read request. Must be destroyed before the file.
		/// @note The file, request, buffer and callback must be kept alive till the finish of the operation.
		/// @note The function is thread-safe.
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<IReadRequest> Read(const ReadParams& params, std::move_only_function<void(const IReadRequest&)> callback = nullptr) = 0;
		/// @brief Makes a write request.
		/// @param params Write parameters.
		/// @param callback Callback. Can be nullptr. It will be called on the caller thread or on an io thread. It may be called before the function returns.
		/// @return Write request. Must be destroyed before the file.
		/// @note The file, request, buffer and observer must be kept alive till the finish of the operation.
		/// @note The function is thread-safe.
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<IWriteRequest> Write(const WriteParams& params, std::move_only_function<void(const IWriteRequest&)> callback = nullptr) = 0;
	};
}
