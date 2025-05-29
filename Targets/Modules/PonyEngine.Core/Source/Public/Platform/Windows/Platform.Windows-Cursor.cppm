/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <stdexcept>;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Platform.Windows:Cursor;

import PonyEngine.Utility;

export namespace PonyEngine::Platform::Windows
{
	/// @brief Gets a default cursor.
	/// @return Default cursor.
	[[nodiscard("Pure function")]]
	HCURSOR DefaultCursor();
}

namespace PonyEngine::Platform::Windows
{
	HCURSOR DefaultCursor()
	{
		const auto cursor = static_cast<HCURSOR>(LoadImageA(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
		if (!cursor)
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to load default cursor. Error code: '0x{:X}'.", GetLastError()));
		}

		return cursor;
	}
}
