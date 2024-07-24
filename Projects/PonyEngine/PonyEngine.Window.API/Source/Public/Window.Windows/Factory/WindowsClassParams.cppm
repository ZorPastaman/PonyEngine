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

export module PonyEngine.Window.Windows.Factory:WindowsClassParams;

import <string>;

export namespace PonyEngine::Window
{
	/// @brief Windows class parameters. They are used in RegisterClass() function.
	struct WindowsClassParams final
	{
		std::wstring name = L"Pony Engine Class"; ///< Class name. Must be unique.
		HICON icon = NULL; ///< Class icon. The default icon is used if it's NULL.
		HCURSOR cursor = NULL; ///< Class cursor. The default cursor is used if it's NULL.
		UINT style = UINT{0}; ///< Class style;
	};
}

