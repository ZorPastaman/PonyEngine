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

export module PonyEngine.Platform.Windows:Cursor;

import std;

export namespace PonyEngine::Platform::Windows
{
	/// @brief Gets a default cursor.
	/// @return Default cursor.
	[[nodiscard("Pure function")]]
	HCURSOR GetDefaultCursor();
}

namespace PonyEngine::Platform::Windows
{
	HCURSOR GetDefaultCursor()
	{
		const auto cursor = static_cast<HCURSOR>(LoadImageA(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
		if (!cursor)
		{
			throw std::runtime_error(std::format("Failed to load default cursor: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return cursor;
	}
}
