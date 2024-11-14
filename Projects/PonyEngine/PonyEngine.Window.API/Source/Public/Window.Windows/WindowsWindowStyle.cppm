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

export module PonyEngine.Window.Windows:WindowsWindowStyle;

export namespace PonyEngine::Window
{
	/// @brief Windows window style.
	struct WindowsWindowStyle final
	{
		DWORD style = WS_POPUP; ///< Window style.
		DWORD extendedStyle = DWORD{0}; ///< Extended window style.
	};
}
