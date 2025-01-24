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

export module PonyEngine.Input:DeviceFactory;

import :IDeviceFactory;

export namespace PonyEngine::Input
{
	/// @brief Input device factory.
	class DeviceFactory : public IDeviceFactory
	{
		SIMPLE_BASE_BODY(DeviceFactory)
	};
}
