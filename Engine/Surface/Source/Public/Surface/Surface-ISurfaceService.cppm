/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Surface:ISurfaceService;

import std;

import PonyEngine.Math;

import :SurfacePositionMode;
import :SurfaceRect;
import :SurfaceStyle;

export namespace PonyEngine::Surface
{
	/// @brief Surface service.
	class ISurfaceService
	{
		INTERFACE_BODY(ISurfaceService)

		/// @brief Rectangle request parameters.
		struct RectRequest final
		{
			bool relativePosition = false; ///< Whether the position is relative or absolute?
			bool relativeSize = false; ///< Whether the size is relative or absolute?
			SurfacePositionMode positionMode = SurfacePositionMode::LeftTopCorner; ///< Position mode.
		};

		/// @brief Gets a screen resolution.
		/// @return Screen resolution.
		[[nodiscard("Pure funtion")]]
		virtual Math::Vector2<std::int32_t> ScreenResolution() const = 0;

		/// @brief Gets a client title.
		/// @return Client title.
		[[nodiscard("Pure function")]]
		virtual std::string_view Title() const = 0;
		/// @brief Sets a client title.
		/// @param title Client title.
		/// @remark If the platform doesn't support client titles, the function does nothing.
		virtual void Title(std::string_view title) = 0;

		/// @brief Gets a surface rectangle.
		/// @param request Rectangle request parameters.
		/// @return Surface rectangle.
		[[nodiscard("Pure function")]]
		virtual SurfaceRect Rect(const RectRequest& request = RectRequest()) const = 0;
		/// @brief Sets a surface rectangle.
		/// @param rect Surface rectangle.
		/// @remark If the platform doesn't support surface rectangles, the function does nothing.
		virtual void Rect(const SurfaceRect& rect) = 0;
		/// @brief Gets the minimal client size.
		/// @return Minimal client size.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> MinimalSize() const = 0;
		/// @brief Sets the minimal client size.
		/// @param size Minimal client size.
		/// @remark If the platform doesn't support surface rectangles, the function does nothing.
		virtual void MinimalSize(const Math::Vector2<std::int32_t>& size) = 0;

		/// @brief Gets a surface style.
		/// @return Surface style.
		[[nodiscard("Pure function")]]
		virtual SurfaceStyle Style() const = 0;
		/// @brief Sets a surface style.
		/// @param style Surface style.
		/// @rematk If the platform doesn't support a style flag, it'll be ignored.
		virtual void Style(SurfaceStyle style) = 0;

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
	};
}
