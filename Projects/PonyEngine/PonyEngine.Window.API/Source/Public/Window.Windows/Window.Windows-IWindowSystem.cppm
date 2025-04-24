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

import :IMessagePump;
import :IRawInput;

export namespace PonyEngine::Window::Windows
{
	/// @brief Window system for Windows.
	class IWindowSystem : public Window::IWindowSystem
	{
		INTERFACE_BODY(IWindowSystem)

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
		virtual IRawInput& RawInputManager() noexcept = 0;
		/// @brief Gets the raw input manager.
		/// @return Raw input manager.
		[[nodiscard("Pure function")]]
		virtual const IRawInput& RawInputManager() const noexcept = 0;

		/// @brief Gets the window handle.
		/// @return Window handle.
		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept = 0;
	};
}
