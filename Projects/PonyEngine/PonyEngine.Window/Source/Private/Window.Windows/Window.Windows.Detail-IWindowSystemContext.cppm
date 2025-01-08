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

export module PonyEngine.Window.Windows.Detail:IWindowSystemContext;

import <cstdint>;

import PonyMath.Shape;

import PonyDebug.Log;

import PonyEngine.Window.Windows;

export namespace PonyEngine::Window::Windows
{
	/// @brief Windows window system context.
	class IWindowSystemContext
	{
		INTERFACE_BODY(IWindowSystemContext)

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets the message pump.
		/// @return Message pump.
		[[nodiscard("Pure function")]]
		virtual IMessagePump& MessagePump() noexcept = 0;
		/// @brief Gets the message pump.
		/// @return Message pump.
		[[nodiscard("Pure function")]]
		virtual const IMessagePump& MessagePump() const noexcept = 0;

		/// @brief Gets window rect.
		/// @return Window rect.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Shape::Rect<std::int32_t> WindowRect() const = 0;
		/// @brief Gets window client rect.
		/// @return Window client rect.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Shape::Rect<std::int32_t> WindowClientRect() const = 0;
		/// @brief Gets window rect.
		/// @return Window rect.
		[[nodiscard("Pure function")]]
		virtual RECT WindowRectWindows() const = 0;
		/// @brief Gets window client rect.
		/// @return Window client rect.
		[[nodiscard("Pure function")]]
		virtual RECT WindowClientRectWindows() const = 0;

		/// @brief Gets the window handle.
		/// @return Window handle.
		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept = 0;
	};
}
