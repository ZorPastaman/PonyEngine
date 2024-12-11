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

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Window.Windows.Detail:WindowsWindowProc;

import <stdexcept>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import :IWindowsWindowProc;

export namespace PonyEngine::Window
{
	/// @brief Registers a window proc manager to use a correct window proc. The used window class must point to @p WindowProc function from this file.
	/// @param hWnd Window handle.
	/// @param windowProc Window proc manager.
	void RegisterWindowProc(HWND hWnd, IWindowsWindowProc* windowProc);
	/// @brief Unregister a previous registered window proc manager.
	/// @param hWnd Window handle.
	void UnregisterWindowProc(HWND hWnd);

	/// @brief Process windowProc messages.
	/// @details Actually, it translates invocations to a corresponding @p IWindowProc.
	///          It's needed because WinAPI doesn't take pointers to member functions.
	/// @param hWnd Window handler.
	/// @param uMsg Window message.
	/// @param wParam WParam.
	/// @param lParam LParam.
	/// @return Process result.
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}

namespace PonyEngine::Window
{
	void RegisterWindowProc(const HWND hWnd, IWindowsWindowProc* const windowProc)
	{
		SetLastError(DWORD{0});

		if (!SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowProc))) [[likely]]
		{
			if (const DWORD errorCode = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Error on registering window proc. Error code: '0x{:X}'.", errorCode));
			}
		}
	}

	void UnregisterWindowProc(const HWND hWnd)
	{
		SetLastError(DWORD{0});

		if (!SetWindowLongPtrW(hWnd, GWLP_USERDATA, LONG_PTR{NULL})) [[unlikely]]
		{
			if (const DWORD errorCode = GetLastError()) [[likely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Error on unregistering window proc. Error code: '0x{:X}'.", errorCode));
			}
		}
	}

	LRESULT CALLBACK WindowProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		if (uMsg == WM_CREATE)
		{
			if (const auto windowProc = reinterpret_cast<IWindowsWindowProc*>(reinterpret_cast<CREATESTRUCTW*>(lParam)->lpCreateParams)) [[likely]]
			{
				return windowProc->WindowProc(uMsg, wParam, lParam);
			}

			PONY_CONSOLE(PonyDebug::Log::LogType::Error, "Wrong Windows window has been created. No IWindowProc interface found.");

			return -1;
		}

		SetLastError(DWORD{0});

		if (const auto windowProc = reinterpret_cast<IWindowsWindowProc*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA))) [[likely]]
		{
			return windowProc->WindowProc(uMsg, wParam, lParam);
		}

		if (const DWORD errorCode = GetLastError()) [[likely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Error on window proc. Error code: '0x{:X}'.", errorCode));
		}

		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}
}
