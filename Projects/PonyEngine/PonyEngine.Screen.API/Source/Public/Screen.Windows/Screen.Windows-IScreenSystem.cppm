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

export module PonyEngine.Screen.Windows:IScreenSystem;

import PonyEngine.Screen;

export namespace PonyEngine::Screen::Windows
{
	/// @brief Windows screen system.
	class IScreenSystem : public Screen::IScreenSystem
	{
		INTERFACE_BODY(IScreenSystem)
	};
}
