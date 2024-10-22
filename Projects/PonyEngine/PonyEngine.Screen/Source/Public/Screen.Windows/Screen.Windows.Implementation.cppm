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

export module PonyEngine.Screen.Windows.Implementation;

export import PonyEngine.Screen.Windows.Factory;

import PonyEngine.Core.Factory;

import :WindowsScreenSystemFactory;
import :WindowsScreenSystemFactoryDestroyer;

export namespace PonyEngine::Screen
{
	/// @brief Creates a screen system for Windows factory.
	/// @param application Application.
	/// @param params Screen system for Windows factory parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsScreenSystemFactoryData CreateWindowsScreenFactory(Core::IApplication& application, const WindowsScreenSystemFactoryParams& params);
}

namespace PonyEngine::Screen
{
	auto DefaultWindowsScreenSystemFactoryDestroyer = WindowsScreenSystemFactoryDestroyer(); ///< Default window system for Windows factory destroyer.

	WindowsScreenSystemFactoryData CreateWindowsScreenFactory(Core::IApplication& application, const WindowsScreenSystemFactoryParams&)
	{
		const auto factory = new WindowsScreenSystemFactory(application);
		const auto factoryDeleter = Core::SystemFactoryDeleter(DefaultWindowsScreenSystemFactoryDestroyer);

		return WindowsScreenSystemFactoryData
		{
			.systemFactory = Core::SystemFactoryUniquePtr(factory, factoryDeleter),
		};
	}
}
