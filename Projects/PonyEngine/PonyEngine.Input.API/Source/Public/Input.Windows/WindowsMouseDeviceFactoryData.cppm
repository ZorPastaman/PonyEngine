/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Windows:WindowsMouseDeviceFactoryData;

import <memory>;

import PonyEngine.Input;

export namespace PonyEngine::Input
{
	/// @brief Windows mouse device factory data.
	struct WindowsMouseDeviceFactoryData final
	{
		std::unique_ptr<InputDeviceFactory> inputDeviceFactory; ///< Windows mouse device factory.
	};
}
