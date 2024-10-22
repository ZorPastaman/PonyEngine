/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen.Windows.Factory:WindowsScreenSystemFactoryData;

import PonyEngine.Core.Factory;

import :IWindowsScreenSystemFactory;

export namespace PonyEngine::Screen
{
	struct WindowsScreenSystemFactoryData final
	{
		Core::SystemFactoryUniquePtr systemFactory; ///< System factory.

		IWindowsScreenSystemFactory* windowsSystemFactory = nullptr; ///< Windows system factory.
	};
}
