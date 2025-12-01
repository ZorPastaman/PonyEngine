/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Ext:DeviceData;

import std;

import PonyEngine.RawInput;

export namespace PonyEngine::Input
{
	/// @brief Device data.
	struct DeviceData final
	{
		std::shared_ptr<IDevice> device; ///< Device.
		bool isConnected = true; ///< Is the device connected?
	};
}
