/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

export module PonyEngine.File.Impl.Windows:FileUtility;

import std;

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
		constexpr std::array<std::pair<FileAccess, DWORD>, 2> map
		{
			std::pair(FileAccess::Read, GENERIC_READ),
			std::pair(FileAccess::Write, GENERIC_WRITE)
		};

		DWORD desiredAccess = 0u;
		for (const auto [flag, nativeFlag] : map)
		{
			desiredAccess |= Any(flag, access) ? nativeFlag : 0;
		}

		return desiredAccess;
	}

	DWORD ToCreationDisposition(const FileAccess access, const FileOpenMode openMode)
	{
		if (Any(FileOpenMode::Truncate, openMode) && None(FileAccess::Write, access)) [[unlikely]]
		{
			throw std::invalid_argument("Truncate open mode without write file access");
		}

		if (Any(FileAccess::Write, access))
		{
			return Any(FileOpenMode::Truncate, openMode)
				? CREATE_ALWAYS
				: OPEN_ALWAYS;
		}

		if (Any(FileAccess::Read, access))
		{
			return OPEN_EXISTING;
		}

		throw std::invalid_argument("Invalid access");
	}

	DWORD ToFlags(const FileFlag flags) noexcept
	{
		constexpr std::array<std::pair<FileFlag, DWORD>, 4> map
		{
			std::pair(FileFlag::SequentialScan, FILE_FLAG_SEQUENTIAL_SCAN),
			std::pair(FileFlag::RandomAccess, FILE_FLAG_RANDOM_ACCESS),
			std::pair(FileFlag::DeleteOnClose, FILE_FLAG_DELETE_ON_CLOSE),
			std::pair(FileFlag::WriteThrough, FILE_FLAG_WRITE_THROUGH),
		};

		DWORD answer = FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED;
		for (const auto [flag, nativeFlag] : map)
		{
			answer |= Any(flag, flags) ? nativeFlag : 0;
		}

		return answer;
	}
}
