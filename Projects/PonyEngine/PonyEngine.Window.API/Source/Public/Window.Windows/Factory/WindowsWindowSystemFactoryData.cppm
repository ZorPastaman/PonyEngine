/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Factory:WindowsWindowSystemFactoryData;

import PonyEngine.Core.Factory;

import :IWindowsWindowSystemFactory;

export namespace PonyEngine::Window
{
	/// @brief Window system for Windows factory data.
	struct WindowsWindowSystemFactoryData final
	{
		Core::SystemFactoryUniquePtr<IWindowsWindowSystemFactory> systemFactory; ///< System factory.
	};
}
