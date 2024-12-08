/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputDeviceData;

import <memory>;

import :InputDevice;

export namespace PonyEngine::Input
{
	/// @brief Input device data.
	struct InputDeviceData final
	{
		std::unique_ptr<InputDevice> inputDevice; ///< Input device.
	};
}
