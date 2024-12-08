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

export module PonyEngine.Input:InputDeviceFactory;

import :IInputDeviceFactory;

export namespace PonyEngine::Input
{
	/// @brief Input device factory.
	class InputDeviceFactory : public IInputDeviceFactory
	{
		BASE_BODY(InputDeviceFactory)
	};
}
