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

export namespace PonyEngine::Input::Windows
{
	/// @brief Creates a Windows keyboard device factory.
	/// @param application Application context.
	/// @param factoryParams Windows keyboard device factory parameters.
	/// @param deviceParams Windows keyboard device parameters.
	/// @return Windows keyboard device factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT KeyboardDeviceFactoryData CreateKeyboardDeviceFactory(Core::IApplicationContext& application, const KeyboardDeviceFactoryParams& factoryParams, const KeyboardDeviceParams& deviceParams);

	/// @brief Creates a Windows mouse device factory.
	/// @param application Application context.
	/// @param factoryParams Windows mouse device factory parameters.
	/// @param deviceParams Windows mouse device parameters.
	/// @return Windows mouse device factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT MouseDeviceFactoryData CreateMouseDeviceFactory(Core::IApplicationContext& application, const MouseDeviceFactoryParams& factoryParams, const MouseDeviceParams& deviceParams);
}

namespace PonyEngine::Input::Windows
{
	KeyboardDeviceFactoryData CreateKeyboardDeviceFactory(Core::IApplicationContext& application, const KeyboardDeviceFactoryParams& factoryParams, const KeyboardDeviceParams& deviceParams)
	{
		return KeyboardDeviceFactoryData{.inputDeviceFactory = std::make_unique<KeyboardDeviceFactory>(application, factoryParams, deviceParams)};
	}

	MouseDeviceFactoryData CreateMouseDeviceFactory(Core::IApplicationContext& application, const MouseDeviceFactoryParams& factoryParams, const MouseDeviceParams& deviceParams)
	{
		return MouseDeviceFactoryData{.inputDeviceFactory = std::make_unique<MouseDeviceFactory>(application, factoryParams, deviceParams)};
	}
}
