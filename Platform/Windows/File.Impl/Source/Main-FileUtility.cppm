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

export namespace PonyEngine::File::Windows
{
	[[nodiscard("Pure function")]]
	DWORD ToDesiredAccess(FileAccess access) noexcept;
	[[nodiscard("Pure function")]]
	DWORD ToCreationDisposition(FileAccess access, FileOpenMode openMode);
	[[nodiscard("Pure function")]]
	DWORD ToFlags(FileFlag flags);
}

namespace PonyEngine::File::Windows
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
#ifndef NDEBUG
		if (Any(FileOpenMode::Truncate, openMode) && None(FileAccess::Write, access)) [[unlikely]]
		{
			throw std::invalid_argument("Truncate open mode without write file access");
		}
#endif

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

	DWORD ToFlags(const FileFlag flags)
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
