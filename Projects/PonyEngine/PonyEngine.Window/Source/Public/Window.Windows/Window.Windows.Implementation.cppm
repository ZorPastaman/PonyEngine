/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Compiler/Linking.h"

export module PonyEngine.Window.Windows.Implementation;

export import PonyEngine.Window.Windows.Factory;

import PonyEngine.Core;
import PonyEngine.Log;

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
		const auto factory = new WindowsWindowSystemFactory(application, params.windowsClassParams);
		const auto factoryDeleter = Core::SystemFactoryDeleter(DefaultWindowsWindowSystemFactoryDestroyer);

		return WindowsWindowSystemFactoryData
		{
			.systemFactory = Core::SystemFactoryUniquePtr(factory, factoryDeleter),
			.windowSystemFactory = factory
		};
	}
}
