/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"

export module PonyEngine.Window.Windows:WindowSystemParams;

import <memory>;

import PonyEngine.Window;

import :Class;
import :WindowStyle;

export namespace PonyEngine::Window::Windows
{
	/// @brief Windows window parameters.
	struct WindowSystemParams final : Window::WindowSystemParams
	{
		std::shared_ptr<Class> windowsClass; ///< Windows class. The window class must support @p IMessageHandler that is set in CreateWindow().
		WindowStyle windowsWindowStyle; ///< Windows window style.
		int cmdShow = SW_NORMAL; ///< Window cmdShow.
	};
}
