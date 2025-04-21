/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Windows:KeyboardDeviceFactoryData;

import <memory>;

import PonyEngine.Input;

export namespace PonyEngine::Input::Windows
{
	/// @brief Windows keyboard device factory data.
	struct KeyboardDeviceFactoryData final
	{
		std::unique_ptr<DeviceFactory> inputDeviceFactory; ///< Windows keyboard device factory.
	};
}
