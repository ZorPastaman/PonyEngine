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

export namespace PonyEngine::Window
{
	/// @brief Windows window parameters.
	struct WindowsWindowParams final
	{
		DWORD style = DWORD{0}; ///< Window style.
		DWORD extendedStyle = DWORD{0}; ///< Extended window style.
		int showCmd = SW_NORMAL; ///< Window showCmd.
	};
}
