/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Factory:WindowsWindowSystemFactoryParams;

import <functional>;

import PonyEngine.Log;

import :WindowsClassParams;

export namespace PonyEngine::Window
{
	/// @brief Window system for Windows factory parameters.
	struct WindowsWindowSystemFactoryParams final
	{
		std::reference_wrapper<Log::ILogger> logger; ///< Logger.
		WindowsClassParams windowsClassParams; ///< Windows class parameters.
	};
}
