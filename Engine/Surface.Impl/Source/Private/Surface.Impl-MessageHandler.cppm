/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Object/Body.h"

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Surface.Impl:MessageHandler;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Text;

#if PONY_WINDOWS
export namespace PonyEngine::Surface::Windows
{
	/// @brief Windows message handler.
	class IMessageHandler
	{
		INTERFACE_BODY(IMessageHandler)

		/// @brief Gets the application context.
		/// @return Application context.
		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept = 0;
		/// @brief Gets the application context.
		/// @return Application context.
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept = 0;

		/// @brief Handles the message.
		/// @param uMsg Message type.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result code.
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	};

	/// @brief Process window messages.
	/// @details Actually, it translates invocations to a corresponding @p IMessageHandler.
	///          It's needed because WinAPI doesn't take pointers to member functions.
	///          It's required to set a pointer to @p IMessageHandler in a CreateWindow() function.
	/// @param hWnd Window handler.
	/// @param uMsg Window message.
	/// @param wParam WParam.
	/// @param lParam LParam.
	/// @return Process result.
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::Surface::Windows
{
	std::unordered_map<HWND, IMessageHandler*> WindowHandlers; ///< Window handlers.

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

		if (const auto position = WindowHandlers.find(hWnd); position != WindowHandlers.cend()) [[likely]]
		{
			return position->second->HandleMessage(uMsg, wParam, lParam);
		}

		return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	}

	LRESULT SetHandlerPointer(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		const auto windowProc = reinterpret_cast<IMessageHandler*>(reinterpret_cast<CREATESTRUCTW*>(lParam)->lpCreateParams);
		assert(windowProc && "Wrong Windows window has been created. No IMessageHandler interface found.");

		PONY_LOG(windowProc->Application().Logger(), Log::LogType::Info, "Setting message handler. HWND: '0x{:X}'. Handler: '0x{:X}'.", 
			reinterpret_cast<std::uintptr_t>(hWnd), reinterpret_cast<std::uintptr_t>(windowProc));
		try
		{
			WindowHandlers[hWnd] = windowProc;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(windowProc->Application().Logger(), e, "On setting message handler.");
			return -1;
		}

		return windowProc->HandleMessage(uMsg, wParam, lParam);
	}

	LRESULT UnsetHandlerPointer(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (const auto position = WindowHandlers.find(hWnd); position != WindowHandlers.cend()) [[likely]]
		{
			const LRESULT result = position->second->HandleMessage(uMsg, wParam, lParam);
			PONY_LOG(position->second->Application().Logger(), Log::LogType::Info, "Unsetting message handler. HWND: '0x{:X}'. Handler: '0x{:X}'.",
				reinterpret_cast<std::uintptr_t>(hWnd), reinterpret_cast<std::uintptr_t>(position->second));
			WindowHandlers.erase(position);

			return result;
		}

		assert(false && "Invalid window message.");

		return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	}
}
#endif
