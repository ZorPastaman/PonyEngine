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

export module PonyEngine.Window.Windows.Factory:WindowsWindowParams;

import <string>;

import PonyEngine.Math;

export namespace PonyEngine::Window
{
	/// @brief Windows window parameters.
	struct WindowsWindowParams final
	{
		std::wstring title = L"Pony Engine Window"; ///< Window title.
		Math::Vector2<int> position = Math::Vector2<int>(10, 10); ///< Window position (horizontal, vertical).
		Math::Vector2<int> size = Math::Vector2<int>(800, 600); ///< Window size (width, height).
		DWORD style = DWORD{0}; ///< Window style.
		DWORD extendedStyle = DWORD{0}; ///< Extended window style.
		int cmdShow = SW_NORMAL; ///< Window cmdShow.
	};
}
