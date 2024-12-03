/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Base.h"

export module PonyEngine.Screen:ScreenSystemFactory;

import PonyEngine.Core;

export namespace PonyEngine::Screen
{
	/// @brief Screen system factory.
	class ScreenSystemFactory : public Core::ISystemFactory
	{
		BASE_BODY(ScreenSystemFactory)
	};
}