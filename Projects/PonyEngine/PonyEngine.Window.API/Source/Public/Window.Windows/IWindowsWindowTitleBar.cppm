/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Window.Windows:IWindowsWindowTitleBar;

import PonyEngine.Window;

export namespace PonyEngine::Window
{
	class IWindowsWindowTitleBar : public IWindowTitleBar
	{
		INTERFACE_BODY(IWindowsWindowTitleBar)
	};
}
