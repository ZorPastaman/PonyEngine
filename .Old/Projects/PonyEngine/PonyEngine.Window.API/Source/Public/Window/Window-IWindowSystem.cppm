/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Window:IWindowSystem;

import <cstdint>;

import PonyMath.Shape;

import :ICursor;
import :ITitleBar;

export namespace PonyEngine::Window
{
	/// @brief Window system.
	class IWindowSystem
	{
		INTERFACE_BODY(IWindowSystem)

		/// @brief Gets the window title bar.
		/// @return Window title bar.
		[[nodiscard("Pure function")]]
		virtual ITitleBar& TitleBar() noexcept = 0;
		/// @brief Gets the window title bar.
		/// @return Window title bar.
		[[nodiscard("Pure function")]]
		virtual const ITitleBar& TitleBar() const noexcept = 0;

		/// @brief Gets the cursor.
		/// @return Cursor.
		[[nodiscard("Pure function")]]
		virtual ICursor& Cursor() noexcept = 0;
		/// @brief Gets the cursor.
		/// @return Cursor.
		[[nodiscard("Pure function")]]
		virtual const ICursor& Cursor() const noexcept = 0;

		/// @brief Checks if the window is visible.
		/// @return @a True if it's visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsVisible() const noexcept = 0;
		/// @brief Shows the window.
		virtual void ShowWindow() = 0;
		/// @brief Hides the window.
		virtual void HideWindow() = 0;

		/// @brief Gets window rect.
		/// @return Window rect.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Shape::Rect<std::int32_t> WindowRect() const = 0;
		/// @brief Gets window client rect.
		/// @return Window client rect.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Shape::Rect<std::int32_t> WindowClientRect() const = 0;

		/// @brief Converts the client point to a screen point.
		/// @param clientPoint Client point.
		/// @return Screen point.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Vector2<std::int32_t> ClientToScreen(const PonyMath::Core::Vector2<std::int32_t>& clientPoint) const = 0;
		/// @brief Converts the screen point to a client point.
		/// @param screenPoint Screen point.
		/// @return Client point.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Vector2<std::int32_t> ScreenToClient(const PonyMath::Core::Vector2<std::int32_t>& screenPoint) const = 0;
	};
}
