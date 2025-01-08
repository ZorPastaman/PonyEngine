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

export module PonyEngine.Input:InputSystemFactory;

import PonyEngine.Core;

export namespace PonyEngine::Input
{
	/// @brief Input system factory.
	class InputSystemFactory : public Core::ISystemFactory
	{
		BASE_BODY(InputSystemFactory)
	};
}
