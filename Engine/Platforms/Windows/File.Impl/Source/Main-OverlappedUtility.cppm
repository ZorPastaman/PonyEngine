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

export module PonyEngine.File.Impl.Windows:OverlappedUtility;

import std;

export namespace PonyEngine::File
{
	/// @brief Creates an overlapped by the file offset.
	/// @param offset File offset.
	/// @return Overlapped.
	[[nodiscard("Pure function")]]
	OVERLAPPED CreateOverlapped(std::size_t offset) noexcept;
}

namespace PonyEngine::File
{
	OVERLAPPED CreateOverlapped(const std::size_t offset) noexcept
	{
		return OVERLAPPED
		{
			.Offset = static_cast<DWORD>(offset),
			.OffsetHigh = static_cast<DWORD>(offset >> std::numeric_limits<DWORD>::digits)
		};
	}
}
