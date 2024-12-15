/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Screen.Windows:IWindowsScreenSystem;

import PonyEngine.Screen;

export namespace PonyEngine::Screen
{
	/// @brief Windows screen system.
	class IWindowsScreenSystem : public IScreenSystem
	{
		INTERFACE_BODY(IWindowsScreenSystem)
	};
}
