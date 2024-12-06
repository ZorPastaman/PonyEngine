/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Windows:WindowsKeyboardDeviceFactoryData;

import <memory>;

import PonyEngine.Input;

export namespace PonyEngine::Input
{
	/// @brief Windows keyboard device factory data.
	struct WindowsKeyboardDeviceFactoryData final
	{
		std::unique_ptr<InputDeviceFactory> inputDeviceFactory; ///< Windows keyboard device factory.
	};
}
