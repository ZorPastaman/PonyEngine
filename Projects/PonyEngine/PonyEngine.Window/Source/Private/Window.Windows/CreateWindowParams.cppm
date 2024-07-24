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

export module PonyEngine.Window.Windows.Implementation:CreateWindowParams;

import <string>;

export namespace PonyEngine::Window
{
	/// @brief Window parameters.
	struct CreateWindowParams final
	{
		std::wstring title = L"Pony Engine Window"; ///< Window title.
		DWORD style = DWORD{0}; ///< Window style.
		DWORD extendedStyle = DWORD{0}; ///< Extended window style.
		int horizontalPosition = CW_USEDEFAULT; ///< Horizontal window position.
		int verticalPosition = CW_USEDEFAULT; ///< Vertical window position.
		int width = CW_USEDEFAULT; ///< Window width.
		int height = CW_USEDEFAULT; ///< Window height.
		int cmdShow = SW_SHOWDEFAULT; ///< Window showCmd.
	};
}
