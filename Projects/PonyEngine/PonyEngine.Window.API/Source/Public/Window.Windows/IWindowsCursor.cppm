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

export module PonyEngine.Window.Windows:IWindowsCursor;

import PonyEngine.Window;

export namespace PonyEngine::Window
{
	/// @brief Windows cursor.
	class IWindowsCursor : public ICursor
	{
		INTERFACE_BODY(IWindowsCursor)
	};
}
