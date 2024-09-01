/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Factory:WindowsWindowSystemFactoryParams;

import :WindowsClassParams;

export namespace PonyEngine::Window
{
	/// @brief Window system for Windows factory parameters.
	struct WindowsWindowSystemFactoryParams final
	{
		WindowsClassParams windowsClassParams; ///< Windows class parameters.
	};
}
