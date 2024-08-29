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

import PonyEngine.Log;

import :WindowsWindowSystemFactory;
import :WindowsWindowSystemFactoryDestroyer;

export namespace PonyEngine::Window
{
	/// @brief Creates a window for Windows system factory.
	/// @param params Window for Windows system factory parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsWindowSystemFactoryData CreateWindowsWindowFactory(const WindowsWindowSystemFactoryParams& params);
}

namespace PonyEngine::Window
{
	auto DefaultWindowsWindowSystemFactoryDestroyer = WindowsWindowSystemFactoryDestroyer(); ///< Default window for Windows system factory destroyer.

	WindowsWindowSystemFactoryData CreateWindowsWindowFactory(const WindowsWindowSystemFactoryParams& params)
	{
		const auto factory = new WindowsWindowSystemFactory(params.logger, params.windowsClassParams);
		const auto factoryDeleter = Core::SystemFactoryDeleter(DefaultWindowsWindowSystemFactoryDestroyer);

		return WindowsWindowSystemFactoryData
		{
			.systemFactory = Core::SystemFactoryUniquePtr(factory, factoryDeleter),
			.windowsWindowSystemFactory = factory
		};
	}
}
