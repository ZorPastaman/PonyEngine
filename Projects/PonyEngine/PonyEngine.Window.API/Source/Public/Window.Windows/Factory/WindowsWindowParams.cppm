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

import PonyMath.Core;

import PonyEngine.Screen;

export namespace PonyEngine::Window
{
	/// @brief Windows window parameters.
	struct WindowsWindowParams final
	{
		std::wstring title = L"Pony Engine Window"; ///< Window title.
		DWORD style = DWORD{0}; ///< Window style.
		DWORD extendedStyle = DWORD{0}; ///< Extended window style.
		int cmdShow = SW_NORMAL; ///< Window cmdShow.
	};
}
