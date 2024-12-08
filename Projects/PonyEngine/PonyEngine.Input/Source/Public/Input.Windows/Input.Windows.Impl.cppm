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
export import PonyEngine.Input.Windows;

import <memory>;

import PonyEngine.Core;
import PonyEngine.Input.Windows.Detail;

export namespace PonyEngine::Input
{
	/// @brief Creates a Windows keyboard device factory.
	/// @param application Application context.
	/// @param factoryParams Windows keyboard device factory parameters.
	/// @param deviceParams Windows keyboard device parameters.
	/// @return Windows keyboard device factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsKeyboardDeviceFactoryData CreateWindowsKeyboardDeviceFactory(Core::IApplicationContext& application, const WindowsKeyboardDeviceFactoryParams& factoryParams, const WindowsKeyboardDeviceParams& deviceParams);

	/// @brief Creates a Windows mouse device factory.
	/// @param application Application context.
	/// @param factoryParams Windows mouse device factory parameters.
	/// @param deviceParams Windows mouse device parameters.
	/// @return Windows mouse device factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsMouseDeviceFactoryData CreateWindowsMouseDeviceFactory(Core::IApplicationContext& application, const WindowsMouseDeviceFactoryParams& factoryParams, const WindowsMouseDeviceParams& deviceParams);
}

namespace PonyEngine::Input
{
	WindowsKeyboardDeviceFactoryData CreateWindowsKeyboardDeviceFactory(Core::IApplicationContext& application, const WindowsKeyboardDeviceFactoryParams& factoryParams, const WindowsKeyboardDeviceParams& deviceParams)
	{
		return WindowsKeyboardDeviceFactoryData{.inputDeviceFactory = std::make_unique<WindowsKeyboardDeviceFactory>(application, factoryParams, deviceParams)};
	}

	WindowsMouseDeviceFactoryData CreateWindowsMouseDeviceFactory(Core::IApplicationContext& application, const WindowsMouseDeviceFactoryParams& factoryParams, const WindowsMouseDeviceParams& deviceParams)
	{
		return WindowsMouseDeviceFactoryData{.inputDeviceFactory = std::make_unique<WindowsMouseDeviceFactory>(application, factoryParams, deviceParams)};
	}
}
