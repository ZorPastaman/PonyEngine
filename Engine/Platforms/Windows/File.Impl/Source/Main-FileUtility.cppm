/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.File.Impl.Windows:FileUtility;

import PonyEngine.File;

export namespace PonyEngine::File
{
	/// @brief Converts the engine file access to a WinAPI file access.
	/// @param access Engine file access.
	/// @return WinAPI file access.
	[[nodiscard("Pure function")]]
	DWORD ToDesiredAccess(FileAccess access) noexcept;
	/// @brief Converts the engine file open mode to a WinAPI file open mode.
	/// @param access Engine file access.
	/// @param openMode Engine file open mode.
	/// @return WinAPI file open mode.
	[[nodiscard("Pure function")]]
	DWORD ToCreationDisposition(FileAccess access, FileOpenMode openMode);
	/// @brief Converts the engine file flags to a WinAPI file flags.
	/// @param flags Engine file flags.
	/// @return WinAPI file flags.
	[[nodiscard("Pure function")]]
	DWORD ToFlags(FileFlag flags) noexcept;
}

namespace PonyEngine::File
{
	DWORD ToDesiredAccess(const FileAccess access) noexcept
	{
		DWORD desiredAccess = 0u;
		if (Any(FileAccess::Read, access))
		{
			desiredAccess |= GENERIC_READ;
		}
		if (Any(FileAccess::Write, access))
		{
			desiredAccess |= GENERIC_WRITE;
		}

		return desiredAccess;
	}

	DWORD ToCreationDisposition(const FileAccess access, const FileOpenMode openMode)
	{
		if (Any(FileOpenMode::Truncate, openMode) && None(FileAccess::Write, access)) [[unlikely]]
		{
			throw std::invalid_argument("Truncate open mode without write file access");
		}

		if (All(FileAccess::Read, access))
		{
			return OPEN_EXISTING;
		}

		if (Any(FileAccess::Write, access))
		{
			return Any(FileOpenMode::Truncate, openMode)
				? CREATE_ALWAYS
				: OPEN_ALWAYS;
		}

		throw std::invalid_argument("Invalid access");
	}

	DWORD ToFlags(const FileFlag flags) noexcept
	{
		DWORD answer = 0u;
		if (Any(FileFlag::SequentialScan, flags))
		{
			answer |= FILE_FLAG_SEQUENTIAL_SCAN;
		}
		if (Any(FileFlag::RandomAccess, flags))
		{
			answer |= FILE_FLAG_RANDOM_ACCESS;
		}
		if (Any(FileFlag::DeleteOnClose, flags))
		{
			answer |= FILE_FLAG_DELETE_ON_CLOSE;
		}
		if (Any(FileFlag::WriteThrough, flags))
		{
			answer |= FILE_FLAG_WRITE_THROUGH;
		}

		return answer;
	}
}
