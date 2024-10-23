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

export module PonyEngine.Window.Windows.Implementation;

export import PonyEngine.Window.Windows.Factory;

import PonyDebug.Log;

import PonyEngine.Core;

import :WindowsWindowSystemFactory;
import :WindowsWindowSystemFactoryDestroyer;

export namespace PonyEngine::Window
{
	/// @brief Creates a window system for Windows factory.
	/// @param application Application.
	/// @param params Window system for Windows factory parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsWindowSystemFactoryData CreateWindowsWindowFactory(Core::IApplication& application, const WindowsWindowSystemFactoryParams& params);
}

namespace PonyEngine::Window
{
	auto DefaultWindowsWindowSystemFactoryDestroyer = WindowsWindowSystemFactoryDestroyer(); ///< Default window system for Windows factory destroyer.

	WindowsWindowSystemFactoryData CreateWindowsWindowFactory(Core::IApplication& application, const WindowsWindowSystemFactoryParams& params)
	{
		IWindowsWindowSystemFactory* const factory = new WindowsWindowSystemFactory(application, params.windowsClassParams);

		return WindowsWindowSystemFactoryData{.systemFactory = Core::SystemFactoryUniquePtr(*factory, DefaultWindowsWindowSystemFactoryDestroyer)};
	}
}
