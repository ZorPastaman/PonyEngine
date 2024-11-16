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

export module PonyEngine.Window.Windows.Impl;

export import PonyEngine.Window.Windows;

import <memory>;

import PonyEngine.Core;
import PonyEngine.Window.Windows.Detail;

export namespace PonyEngine::Window
{
	/// @brief Creates a Windows class.
	/// @param application Application context.
	/// @param params Windows class parameters.
	/// @return Windows class.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsClassData CreateWindowsClass(Core::IApplicationContext& application, const WindowsClassParams& params);

	/// @brief Creates a window system for Windows factory.
	/// @param application Application context.
	/// @param factoryParams Window system for Windows factory parameters.
	/// @param systemParams Window system for Windows parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsWindowSystemFactoryData CreateWindowsWindowFactory(Core::IApplicationContext& application, const WindowsWindowSystemFactoryParams& factoryParams, const WindowsWindowSystemParams& systemParams);
}

namespace PonyEngine::Window
{
	WindowsClassData CreateWindowsClass(Core::IApplicationContext& application, const WindowsClassParams& params)
	{
		return WindowsClassData{.windowsClass = std::make_unique<WindowsClassImpl>(application, params)};
	}

	WindowsWindowSystemFactoryData CreateWindowsWindowFactory(Core::IApplicationContext& application, const WindowsWindowSystemFactoryParams& factoryParams, const WindowsWindowSystemParams& systemParams)
	{
		return WindowsWindowSystemFactoryData{.systemFactory = std::make_unique<WindowsWindowSystemFactoryImpl>(application, factoryParams, systemParams)};
	}
}
