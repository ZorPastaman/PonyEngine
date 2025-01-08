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

export module PonyEngine.Window.Windows:ICursor;

import PonyEngine.Window;

export namespace PonyEngine::Window::Windows
{
	/// @brief Windows cursor.
	class ICursor : public Window::ICursor
	{
		INTERFACE_BODY(ICursor)
	};
}
