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
		std::wstring name; ///< Class name. Must be unique.
		HICON icon; ///< Class icon. The default icon is used if it's NULL.
		HCURSOR cursor; ///< Class cursor. The default cursor is used if it's NULL.
		UINT style; ///< Class style;
	};
}

