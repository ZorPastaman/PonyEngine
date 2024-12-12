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
#include "PonyBase/Utility/Interface.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Window.Windows:IWindowsMessageHandler;

import <stdexcept>;

import PonyBase.StringUtility;

import PonyDebug.Log;

export namespace PonyEngine::Window
{
	/// @brief Windows message handler.
	class IWindowsMessageHandler
	{
		INTERFACE_BODY(IWindowsMessageHandler)

		/// @brief Handles the message.
		/// @param uMsg Message type.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result code.
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	};

	/// @brief Process window messages.
	/// @details Actually, it translates invocations to a corresponding @p IWindowsWindowMessageHandler.
	///          It's needed because WinAPI doesn't take pointers to member functions.
	///          It's required to set a pointer to @p IWindowsMessageHandler in a CreateWindow() function.
	/// @param hWnd Window handler.
	/// @param uMsg Window message.
	/// @param wParam WParam.
	/// @param lParam LParam.
	/// @return Process result.
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}

namespace PonyEngine::Window
{
	/// @brief Sets a handler pointer.
	/// @param hWnd Window handle.
	/// @param uMsg Window message. Expected to be WM_CREATE.
	/// @param wParam WParam.
	/// @param lParam LParam.
	/// @return Window create result.
	LRESULT SetHandlerPointer(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	/// @brief Unsets a handler pointer.
	/// @param hWnd Window handle.
	/// @param uMsg Window message. Expected to be WM_CREATE.
	/// @param wParam WParam.
	/// @param lParam LParam.
	/// @return Window destroy result.
	LRESULT UnsetHandlerPointer(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

	LRESULT CALLBACK WindowProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		if (uMsg == WM_CREATE) [[unlikely]]
		{
			return SetHandlerPointer(hWnd, uMsg, wParam, lParam);
		}
		if (uMsg == WM_DESTROY) [[unlikely]]
		{
			return UnsetHandlerPointer(hWnd, uMsg, wParam, lParam);
		}

		SetLastError(DWORD{0});

		if (const auto windowProc = reinterpret_cast<IWindowsMessageHandler*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA))) [[likely]]
		{
			return windowProc->HandleMessage(uMsg, wParam, lParam);
		}

		if (const DWORD errorCode = GetLastError()) [[likely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Error on window proc. Error code: '0x{:X}'.", errorCode));
		}

		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	LRESULT SetHandlerPointer(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (const auto windowProc = reinterpret_cast<IWindowsMessageHandler*>(reinterpret_cast<CREATESTRUCTW*>(lParam)->lpCreateParams)) [[likely]]
		{
			SetLastError(DWORD{0});
			if (!SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowProc))) [[likely]]
			{
				if (const DWORD errorCode = GetLastError()) [[unlikely]]
				{
					PONY_CONSOLE(PonyDebug::Log::LogType::Error, PonyBase::Utility::SafeFormat("Error on setting message handler. Error code: '0x{:X}'.", errorCode));

					return -1;
				}
			}

			return windowProc->HandleMessage(uMsg, wParam, lParam);
		}

		PONY_CONSOLE(PonyDebug::Log::LogType::Error, "Wrong Windows window has been created. No IWindowsWindowMessageHandler interface found.");

		return -1;
	}

	LRESULT UnsetHandlerPointer(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (const auto windowProc = reinterpret_cast<IWindowsMessageHandler*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA))) [[likely]]
		{
			SetLastError(DWORD{0});

			if (!SetWindowLongPtrW(hWnd, GWLP_USERDATA, LONG_PTR{NULL})) [[unlikely]]
			{
				if (const DWORD errorCode = GetLastError()) [[likely]]
				{
					PONY_CONSOLE(PonyDebug::Log::LogType::Error, PonyBase::Utility::SafeFormat("Error on unsetting message handler. Error code: '0x{:X}'.", errorCode));
				}
			}

			return windowProc->HandleMessage(uMsg, wParam, lParam);
		}

		PONY_CONSOLE(PonyDebug::Log::LogType::Error, "Wrong Windows window has been destroyed. No IWindowsWindowMessageHandler interface found.");

		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}
}
