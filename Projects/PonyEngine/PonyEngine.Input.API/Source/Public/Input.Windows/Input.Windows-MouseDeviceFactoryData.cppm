/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Windows:MouseDeviceFactoryData;

import <memory>;

import PonyEngine.Input;

export namespace PonyEngine::Input::Windows
{
	/// @brief Windows mouse device factory data.
	struct MouseDeviceFactoryData final
	{
		std::unique_ptr<DeviceFactory> inputDeviceFactory; ///< Windows mouse device factory.
	};
}
