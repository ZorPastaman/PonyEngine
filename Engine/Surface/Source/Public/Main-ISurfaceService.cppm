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
		PONY_INTERFACE_BODY(ISurfaceService)

		/// @brief Gets the supported features.
		/// @return Supported features.
		/// @note This function may be called on any thread and concurrently with any other function.
		[[nodiscard("Pure function")]]
		virtual SurfaceFeature SupportedFeatures() const noexcept = 0;

		/// @brief Gets the rectangle style.
		/// @return Rectangle style.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure function")]]
		virtual Surface::RectStyle RectStyle() const noexcept = 0;
		/// @brief Sets the rectangle style.
		/// @param rectStyle Rectangle style.
		/// @remark The final style may be different from the requested one, depending on the platform capabilities.
		/// @note Must be called on a main thread only.
		virtual void RectStyle(const Surface::RectStyle& rectStyle) = 0;

		/// @brief Gets a screen resolution.
		/// @return Screen resolution.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure funtion")]]
		virtual Math::Vector2<std::int32_t> ScreenResolution() const = 0;
		/// @brief Gets a client rectangle.
		/// @return Client rectangle.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure function")]]
		virtual Math::CornerRect<std::int32_t> ClientRect() const = 0;
		/// @brief Sets a client rectangle.
		/// @param clientRect Client rectangle.
		/// @remark If the platform doesn't support client rectangles, the function throws.
		/// @note Must be called on a main thread only.
		virtual void ClientRect(const Math::CornerRect<std::int32_t>& clientRect) = 0;
		/// @brief Gets a client rectangle minimal size.
		/// @return Client rectangle minimal size.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure funtion")]]
		virtual Math::Vector2<std::int32_t> MinimalSize() const = 0;
		/// @brief Sets a client rectangle minimal size.
		/// @param minimalSize Client rectangle minimal size.
		/// @remark If the platform doesn't support client rectangles, the function throws.
		/// @note Must be called on a main thread only.
		virtual void MinimalSize(const Math::Vector2<std::int32_t>& minimalSize) = 0;

		/// @brief Checks if the surface is alive.
		/// @return @a True if the surface is alive; @a false otherwise.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure funtion")]]
		virtual bool IsAlive() const = 0;
		/// @brief Checks if the surface is active.
		/// @return @a True if the surface is active; @a false otherwise.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure funtion")]]
		virtual bool IsActive() const = 0;
		/// @brief Checks if the surface is in focus.
		/// @return @a True if the surface is in focus; @a false otherwise.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure funtion")]]
		virtual bool IsInFocus() const = 0;

		/// @brief Gets a client title.
		/// @return Client title.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure function")]]
		virtual std::string_view Title() const = 0;
		/// @brief Sets a client title.
		/// @param title Client title.
		/// @remark If the platform doesn't support client titles, the function throws.
		/// @note Must be called on a main thread only.
		virtual void Title(std::string_view title) = 0;

		/// @brief Gets if a cursor is controlled as visible.
		/// @return @a True if a cursor is controlled visible; @a false otherwise.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure function")]]
		virtual bool CursorVisibility() const = 0;
		/// @brief Sets if a cursor is controlled as visible.
		/// @param visible Should cursor be visible?
		/// @note Must be called on a main thread only.
		virtual void CursorVisibility(bool visible) = 0;
		/// @brief Gets a cursor clipping rectangle.
		/// @return Cursor clipping rectangle in client rectangle normalized coordinates.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure function")]]
		virtual std::optional<Math::CornerRect<float>> CursorClippingRect() const = 0;
		/// @brief Sets a cursor clipping rectangle.
		/// @param clippingRect Cursor clipping rectangle in client rectangle normalized coordinates.
		/// @note Must be called on a main thread only.
		virtual void CursorClippingRect(const std::optional<Math::CornerRect<float>>& clippingRect) = 0;
		/// @brief Gets a cursor position.
		/// @return Cursor position in screen coordinates.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> CursorPosition() const = 0;
		/// @brief Gets if a cursor is visible.
		/// @return @a True if a cursor is visible; @a false otherwise.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure function")]]
		virtual bool IsCursorVisible() const = 0;

		/// @brief Converts the client point to a screen point.
		/// @param clientPoint Client point.
		/// @return Screen point.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ClientToScreen(const Math::Vector2<std::int32_t>& clientPoint) const = 0;
		/// @brief Converts the screen point to a client point.
		/// @param screenPoint Screen point.
		/// @return Client point.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ScreenToClient(const Math::Vector2<std::int32_t>& screenPoint) const = 0;

		/// @brief Adds the observer.
		/// @param observer Observer.
		/// @note Must be called on a main thread only.
		virtual void AddObserver(ISurfaceObserver& observer) = 0;
		/// @brief Removes the observer.
		/// @param observer Observer.
		/// @note Must be called on a main thread only.
		virtual void RemoveObserver(ISurfaceObserver& observer) noexcept = 0;
	};
}
