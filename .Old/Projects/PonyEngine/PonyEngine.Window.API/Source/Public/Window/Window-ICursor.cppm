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

export module PonyEngine.Window:ICursor;

import <cstdint>;
import <optional>;

import PonyMath.Core;
import PonyMath.Shape;

export namespace PonyEngine::Window
{
	/// @brief Cursor.
	class ICursor
	{
		INTERFACE_BODY(ICursor)

		/// @brief Gets a cursor position in screen space.
		/// @return Cursor position.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Vector2<std::int32_t> CursorPosition() const = 0;
		/// @brief Sets a cursor position in screen space.
		/// @param position Cursor position to set.
		virtual void CursorPosition(const PonyMath::Core::Vector2<std::int32_t>& position) = 0;

		/// @brief Gets if the cursor is visible.
		/// @note The function gets an internal state that is applied only when the window is active.
		/// @return @a True if the cursor is visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsVisible() const noexcept = 0;
		/// @brief Sets if the cursor is visible.
		/// @note The function sets an internal state that is applied only when the window is active.
		/// @param isVisible True if the cursor is visible; @a false otherwise.
		virtual void IsVisible(bool isVisible) = 0;

		/// @brief Gets the cursor clipping rect.
		/// @return Cursor clipping rect. It's a normalized rect. If it's nullopt, the cursor isn't clipped.
		[[nodiscard("Pure function")]]
		virtual const std::optional<PonyMath::Shape::Rect<float>>& ClippingRect() const noexcept = 0;
		/// @brief Sets the cursor clipping rect.
		/// @param clippingRect Cursor clipping rect to set. It must be a normalized rect. If it's nullopt, the cursor isn't clipped.
		virtual void ClippingRect(const std::optional<PonyMath::Shape::Rect<float>>& clippingRect) = 0;
	};
}
