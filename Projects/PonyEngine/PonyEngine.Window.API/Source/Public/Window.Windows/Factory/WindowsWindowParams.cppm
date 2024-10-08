/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"

export module PonyEngine.Window.Windows.Factory:WindowsWindowParams;

import <string>;

import PonyBase.Math;
import PonyBase.Screen;

export namespace PonyEngine::Window
{
	/// @brief Windows window parameters.
	struct WindowsWindowParams final
	{
		std::wstring title = L"Pony Engine Window"; ///< Window title.
		PonyBase::Math::Vector2<int> position = PonyBase::Math::Vector2<int>(10, 10); ///< Window position (horizontal, vertical).
		PonyBase::Screen::Resolution<unsigned int> size = PonyBase::Screen::Resolution<unsigned int>(800, 600); ///< Window size (width, height).
		DWORD style = DWORD{0}; ///< Window style.
		DWORD extendedStyle = DWORD{0}; ///< Extended window style.
		int cmdShow = SW_NORMAL; ///< Window cmdShow.
	};
}
