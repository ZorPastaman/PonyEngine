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

export namespace PonyEngine::Window::Windows
{
	/// @brief Creates a Windows class.
	/// @note The window that uses this class must set a pointer to @p IMessageHandler in CreateWindow() to correctly use this class.
	/// @param application Application context.
	/// @param params Windows class parameters.
	/// @return Windows class.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT ClassData CreateClass(Core::IApplicationContext& application, const ClassParams& params);

	/// @brief Creates a window system for Windows factory.
	/// @note The window class must support @p IMessageHandler that is set in CreateWindow().
	/// @param application Application context.
	/// @param factoryParams Window system for Windows factory parameters.
	/// @param systemParams Window system for Windows parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowSystemFactoryData CreateWindowFactory(Core::IApplicationContext& application, const WindowSystemFactoryParams& factoryParams, const WindowSystemParams& systemParams);
}

namespace PonyEngine::Window::Windows
{
	ClassData CreateClass(Core::IApplicationContext& application, const ClassParams& params)
	{
		return ClassData{.windowsClass = std::make_shared<ClassImpl>(application, params)};
	}

	WindowSystemFactoryData CreateWindowFactory(Core::IApplicationContext& application, const WindowSystemFactoryParams& factoryParams, const WindowSystemParams& systemParams)
	{
		return WindowSystemFactoryData{.systemFactory = std::make_shared<WindowSystemFactoryImpl>(application, factoryParams, systemParams)};
	}
}
