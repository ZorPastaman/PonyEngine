/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Surface:ISurfaceService;

import std;

import PonyEngine.Math;

import :ISurfaceObserver;
import :RectStyle;
import :SurfaceFeature;

export namespace PonyEngine::Surface
{
	/// @brief Surface service.
	class ISurfaceService
	{
		INTERFACE_BODY(ISurfaceService)

		/// @brief Gets the supported features.
		/// @return Supported features.
		[[nodiscard("Pure function")]]
		virtual SurfaceFeature SupportedFeatures() const noexcept = 0;

		/// @brief Gets the rectangle style.
		/// @return Rectangle style.
		[[nodiscard("Pure function")]]
		virtual Surface::RectStyle RectStyle() const noexcept = 0;
		/// @brief Sets the rectangle style.
		/// @param rectStyle Rectangle style.
		/// @remark The final style may be different from the requested one, depending on the platform capabilities.
		virtual void RectStyle(const Surface::RectStyle& rectStyle) = 0;

		/// @brief Gets a screen resolution.
		/// @return Screen resolution.
		[[nodiscard("Pure funtion")]]
		virtual Math::Vector2<std::int32_t> ScreenResolution() const = 0;
		/// @brief Gets a client rectangle.
		/// @return Client rectangle.
		[[nodiscard("Pure function")]]
		virtual Math::CornerRect<std::int32_t> ClientRect() const = 0;
		/// @brief Sets a client rectangle.
		/// @param clientRect Client rectangle.
		/// @remark If the platform doesn't support client rectangles, the function throws.
		virtual void ClientRect(const Math::CornerRect<std::int32_t>& clientRect) = 0;
		/// @brief Gets a client rectangle minimal size.
		/// @return Client rectangle minimal size.
		[[nodiscard("Pure funtion")]]
		virtual Math::Vector2<std::int32_t> MinimalSize() const = 0;
		/// @brief Sets a client rectangle minimal size.
		/// @param minimalSize Client rectangle minimal size.
		/// @remark If the platform doesn't support client rectangles, the function throws.
		virtual void MinimalSize(const Math::Vector2<std::int32_t>& minimalSize) = 0;

		/// @brief Checks if the surface is alive.
		/// @return @a True if the surface is alive; @a false otherwise.
		[[nodiscard("Pure funtion")]]
		virtual bool IsAlive() const = 0;
		/// @brief Checks if the surface is active.
		/// @return @a True if the surface is active; @a false otherwise.
		[[nodiscard("Pure funtion")]]
		virtual bool IsActive() const = 0;
		/// @brief Checks if the surface is in focus.
		/// @return @a True if the surface is in focus; @a false otherwise.
		[[nodiscard("Pure funtion")]]
		virtual bool IsInFocus() const = 0;

		/// @brief Gets a client title.
		/// @return Client title.
		[[nodiscard("Pure function")]]
		virtual std::string_view Title() const = 0;
		/// @brief Sets a client title.
		/// @param title Client title.
		/// @remark If the platform doesn't support client titles, the function throws.
		virtual void Title(std::string_view title) = 0;

		/// @brief Gets if a cursor is controlled as visible.
		/// @return @a True if a cursor is controlled visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool CursorVisibility() const = 0;
		/// @brief Sets if a cursor is controlled as visible.
		/// @param visible Should cursor be visible?
		virtual void CursorVisibility(bool visible) = 0;
		/// @brief Gets a cursor clipping rectangle.
		/// @return Cursor clipping rectangle in client rectangle normalized coordinates.
		[[nodiscard("Pure function")]]
		virtual std::optional<Math::CornerRect<float>> CursorClippingRect() const = 0;
		/// @brief Sets a cursor clipping rectangle.
		/// @param clippingRect Cursor clipping rectangle in client rectangle normalized coordinates.
		virtual void CursorClippingRect(const std::optional<Math::CornerRect<float>>& clippingRect) = 0;
		/// @brief Gets a cursor position.
		/// @return Cursor position in screen coordinates.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> CursorPosition() const = 0;
		/// @brief Gets if a cursor is visible.
		/// @return @a True if a cursor is visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsCursorVisible() const = 0;

		/// @brief Converts the client point to a screen point.
		/// @param clientPoint Client point.
		/// @return Screen point.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ClientToScreen(const Math::Vector2<std::int32_t>& clientPoint) const = 0;
		/// @brief Converts the screen point to a client point.
		/// @param screenPoint Screen point.
		/// @return Client point.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ScreenToClient(const Math::Vector2<std::int32_t>& screenPoint) const = 0;

		/// @brief Adds the observer.
		/// @param observer Observer.
		virtual void AddObserver(ISurfaceObserver& observer) = 0;
		/// @brief Removes the observer.
		/// @param observer Observer.
		virtual void RemoveObserver(ISurfaceObserver& observer) noexcept = 0;
	};
}
