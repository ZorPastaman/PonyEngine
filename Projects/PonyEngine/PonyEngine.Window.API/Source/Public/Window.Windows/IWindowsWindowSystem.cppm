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

export module PonyEngine.Window.Windows:IWindowsWindowSystem;

import PonyEngine.Window;

import :IWindowsMessagePump;
import :IWindowsRawInputManager;
import :IWindowsWindowTitleBar;

export namespace PonyEngine::Window
{
	/// @brief Window system for Windows.
	class IWindowsWindowSystem : public IWindowSystem
	{
		INTERFACE_BODY(IWindowsWindowSystem)

		/// @brief Gets the window title bar.
		/// @return Window title bar.
		[[nodiscard("Pure function")]]
		virtual IWindowsWindowTitleBar& TitleBar() noexcept override = 0;
		/// @brief Gets the window title bar.
		/// @return Window title bar.
		[[nodiscard("Pure function")]]
		virtual const IWindowsWindowTitleBar& TitleBar() const noexcept override = 0;

		/// @brief Gets the message pump.
		/// @return Message pump.
		[[nodiscard("Pure function")]]
		virtual IWindowsMessagePump& MessagePump() noexcept = 0;
		/// @brief Gets the message pump.
		/// @return Message pump.
		[[nodiscard("Pure function")]]
		virtual const IWindowsMessagePump& MessagePump() const noexcept = 0;

		/// @brief Gets the raw input manager.
		/// @return Raw input manager.
		[[nodiscard("Pure function")]]
		virtual IWindowsRawInputManager& RawInputManager() noexcept = 0;
		/// @brief Gets the raw input manager.
		/// @return Raw input manager.
		[[nodiscard("Pure function")]]
		virtual const IWindowsRawInputManager& RawInputManager() const noexcept = 0;

		/// @brief Gets the window handle.
		/// @return Window handle.
		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept = 0;
	};
}
