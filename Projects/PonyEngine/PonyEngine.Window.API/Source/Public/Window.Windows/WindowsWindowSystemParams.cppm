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

export module PonyEngine.Window.Windows:WindowsWindowSystemParams;

import <memory>;

import PonyEngine.Window;

import :WindowsClass;
import :WindowsWindowStyle;

export namespace PonyEngine::Window
{
	/// @brief Windows window parameters.
	struct WindowsWindowSystemParams final : WindowSystemParams
	{
		std::shared_ptr<WindowsClass> windowsClass; ///< Windows class.
		WindowsWindowStyle windowsWindowStyle; ///< Windows window style.
		int cmdShow = SW_NORMAL; ///< Window cmdShow.
	};
}
