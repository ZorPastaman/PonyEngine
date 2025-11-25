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

import :IReadStream;
import :IWriteStream;
import :ReadMode;
import :WriteMode;

export namespace PonyEngine::File
{
	/// @brief File service.
	class IFileService
	{
		INTERFACE_BODY(IFileService)

		/// @brief Gets a path to the executable.
		/// @return Path to the executable.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& ExecutableFile() const noexcept = 0;
		/// @brief Gets an executable directory.
		/// @return Executable directory.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& ExecutableDirectory() const noexcept = 0;
		/// @brief Gets a root directory.
		/// @return Root directory.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& RootDirectory() const noexcept = 0;
		/// @brief Gets a local data directory.
		/// @return Local data directory.
		/// @remark The directory isn't created automatically.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& LocalDataDirectory() const noexcept = 0;
		/// @brief Gets a user data directory.
		/// @return User data directory.
		/// @remark The directory isn't created automatically.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& UserDataDirectory() const noexcept = 0;
		/// @brief Gets a temporal data directory.
		/// @return Temporal data directory.
		/// @remark The directory isn't created automatically.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& TempDataDirectory() const noexcept = 0;

		/// @brief Opens a read stream for the file at the given path.
		/// @param filePath File path.
		/// @param mode Read mode.
		/// @return Read stream.
		/// @note The function throws if a write stream is opened for the same file.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IReadStream> OpenReadStream(const std::filesystem::path& filePath, ReadMode mode) = 0;
		/// @brief Opens a write stream for the file at the given path.
		/// @param filePath File path.
		/// @param mode Write mode.
		/// @return Write stream.
		/// @note The function throws if any stream is opened for the same file.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IWriteStream> OpenWriteStream(const std::filesystem::path& filePath, WriteMode mode) = 0;
	};
}
