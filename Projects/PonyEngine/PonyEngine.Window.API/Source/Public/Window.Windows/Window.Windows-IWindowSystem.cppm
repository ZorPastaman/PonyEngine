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
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Window.Windows:IWindowSystem;

import PonyEngine.Window;

import :ICursor;
import :IMessagePump;
import :IRawInputManager;
import :ITitleBar;

export namespace PonyEngine::Window::Windows
{
	/// @brief Window system for Windows.
	class IWindowSystem : public Window::IWindowSystem
	{
		INTERFACE_BODY(IWindowSystem)

		/// @brief Gets the window title bar.
		/// @return Window title bar.
		[[nodiscard("Pure function")]]
		virtual ITitleBar& TitleBar() noexcept override = 0;
		/// @brief Gets the window title bar.
		/// @return Window title bar.
		[[nodiscard("Pure function")]]
		virtual const ITitleBar& TitleBar() const noexcept override = 0;

		/// @brief Gets the cursor.
		/// @return Cursor.
		[[nodiscard("Pure function")]]
		virtual ICursor& Cursor() noexcept override = 0;
		/// @brief Gets the cursor.
		/// @return Cursor.
		[[nodiscard("Pure function")]]
		virtual const ICursor& Cursor() const noexcept override = 0;

		/// @brief Gets the message pump.
		/// @return Message pump.
		[[nodiscard("Pure function")]]
		virtual IMessagePump& MessagePump() noexcept = 0;
		/// @brief Gets the message pump.
		/// @return Message pump.
		[[nodiscard("Pure function")]]
		virtual const IMessagePump& MessagePump() const noexcept = 0;

		/// @brief Gets the raw input manager.
		/// @return Raw input manager.
		[[nodiscard("Pure function")]]
		virtual IRawInputManager& RawInputManager() noexcept = 0;
		/// @brief Gets the raw input manager.
		/// @return Raw input manager.
		[[nodiscard("Pure function")]]
		virtual const IRawInputManager& RawInputManager() const noexcept = 0;

		/// @brief Gets the window handle.
		/// @return Window handle.
		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept = 0;
	};
}
