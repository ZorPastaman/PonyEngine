/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Platform/Windows/Framework.h"
#include "Debug/Log/LogMacro.h"

export module PonyEngine.Window.Windows.Implementation:WindowProc;

import PonyEngine.Debug.Log;

import :WindowsWindow;

namespace PonyEngine::Window
{
	/// @brief Process window messages.
	/// @details Actually, it translates invocations to a corresponding @p WindowsWindow.
	///          It's needed because WinAPI doesn't take pointers to member functions.
	/// @param hWnd Window handler.
	/// @param uMsg Window message.
	/// @param wParam WParam.
	/// @param lParam LParam.
	/// @return Process result.
	export LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT CALLBACK WindowProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		WindowsWindow* const window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (window == nullptr) [[unlikely]]
		{
			PONY_CONSOLE(Debug::Log::LogType::Error, "Window pointer is nullptr. The window window won't receive a command.");
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		return window->WindowProc(uMsg, wParam, lParam);
	}
}
