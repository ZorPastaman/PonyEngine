/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:DeviceData;

import <memory>;

import :Device;

export namespace PonyEngine::Input
{
	/// @brief Input device data.
	struct DeviceData final
	{
		std::unique_ptr<Device> inputDevice; ///< Input device.
	};
}
