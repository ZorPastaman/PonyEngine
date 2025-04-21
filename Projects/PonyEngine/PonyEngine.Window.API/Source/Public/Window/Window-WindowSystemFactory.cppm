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

export module PonyEngine.Window:WindowSystemFactory;

import PonyEngine.Core;

export namespace PonyEngine::Window
{
	/// @brief Window system factory.
	class WindowSystemFactory : public Core::ISystemFactory
	{
		SIMPLE_BASE_BODY(WindowSystemFactory)
	};
}
