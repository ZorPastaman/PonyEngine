/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Linking.h"

export module PonyEngine.Input.Windows.Impl;

export import PonyEngine.Input.Impl;

import <memory>;

import PonyEngine.Input.Windows.Detail;

export namespace PonyEngine::Input
{
	[[nodiscard("Pure function")]] // TODO: Add data and params
	PONY_DLL_EXPORT std::unique_ptr<InputDeviceFactory> CreateWindowsKeyboardDeviceFactory();
}

namespace PonyEngine::Input
{
	std::unique_ptr<InputDeviceFactory> CreateWindowsKeyboardDeviceFactory()
	{
		return std::make_unique<WindowsKeyboardDeviceFactory>();
	}
}
