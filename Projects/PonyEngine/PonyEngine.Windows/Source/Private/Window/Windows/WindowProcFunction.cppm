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

export module PonyEngine.Window.Windows.Implementation:WindowProcFunction;

import <format>;
import <stdexcept>;

import :IWindowProc;

namespace PonyEngine::Window
{
	/// @brief Registers a window proc manager to use a correct window proc. The used window class must point to @p WindowProc function from this file.
	/// @param hWnd Window handle.
	/// @param windowProc Window proc manager.
	export void RegisterWindowProc(HWND hWnd, IWindowProc* windowProc);
	/// @brief Unregister a previous registered window proc manager.
	/// @param hWnd Window handle.
	export void UnregisterWindowProc(HWND hWnd);

	/// @brief Process windowProc messages.
	/// @details Actually, it translates invocations to a corresponding @p IWindowProc.
	///          It's needed because WinAPI doesn't take pointers to member functions.
	/// @param hWnd Window handler.
	/// @param uMsg Window message.
	/// @param wParam WParam.
	/// @param lParam LParam.
	/// @return Process result.
	export LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void RegisterWindowProc(const HWND hWnd, IWindowProc* const windowProc)
	{
		SetLastError(DWORD{0});

		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowProc))) [[likely]]
		{
			if (const DWORD errorCode = GetLastError()) [[unlikely]]
			{
				throw std::logic_error(std::format("Error on registering a window proc. Error code: '{}'.", errorCode));
			}
		}
	}

	void UnregisterWindowProc(const HWND hWnd)
	{
		SetLastError(DWORD{0});

		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, LONG_PTR{NULL})) [[unlikely]]
		{
			if (const DWORD errorCode = GetLastError()) [[likely]]
			{
				throw std::logic_error(std::format("Error on unregistering a window proc. Error code: '{}'.", errorCode));
			}
		}
	}

	LRESULT CALLBACK WindowProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		SetLastError(DWORD{0});

		IWindowProc* const windowProc = reinterpret_cast<IWindowProc*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (windowProc != nullptr) [[likely]]
		{
			return windowProc->WindowProc(uMsg, wParam, lParam);
		}

		if (const DWORD errorCode = GetLastError()) [[unlikely]]
		{
			throw std::logic_error(std::format("Error on a window proc. Error code: '{}'.", errorCode));
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}