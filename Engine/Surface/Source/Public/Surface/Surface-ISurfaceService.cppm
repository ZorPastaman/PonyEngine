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
import :SurfaceStyle;

export namespace PonyEngine::Surface
{
	/// @brief Surface service.
	class ISurfaceService
	{
		INTERFACE_BODY(ISurfaceService)

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

		/// @brief Gets an absolute client position.
		/// @param positionMode Position mode.
		/// @return Absolute client position.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> PositionAbsolute(SurfacePositionMode positionMode = SurfacePositionMode::LeftTopCorner) const = 0;
		/// @brief Gets a relative client position.
		/// @param positionMode Position mode.
		/// @return Relative client position.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<float> PositionRelative(SurfacePositionMode positionMode = SurfacePositionMode::LeftTopCorner) const = 0;
		/// @brief Sets an absolute client position.
		/// @param position Absolute client position.
		/// @param positionMode Position mode.
		/// @remark If the platform doesn't support client positions, the function does nothing.
		virtual void PositionAbsolute(const Math::Vector2<std::int32_t>& position, SurfacePositionMode positionMode = SurfacePositionMode::LeftTopCorner) = 0;
		/// @brief Sets a relative client position.
		/// @param position Relative client position.
		/// @param positionMode Position mode.
		/// @remark If the platform doesn't support client positions, the function does nothing.
		virtual void PositionRelative(const Math::Vector2<float>& position, SurfacePositionMode positionMode = SurfacePositionMode::LeftTopCorner) = 0;

		/// @brief Gets an absolute client size.
		/// @return Absolute client size.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> SizeAbsolute() const = 0;
		/// @brief Gets an absolute client size.
		/// @return Absolute client size.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<float> SizeRelative() const = 0;
		/// @brief Sets an absolute client size.
		/// @param size Absolute client size.
		/// @remark If the platform doesn't support client sizes, the function does nothing.
		virtual void SizeAbsolute(const Math::Vector2<std::int32_t>& size) = 0;
		/// @brief Sets a relative client size.
		/// @param size Relative client size.
		/// @remark If the platform doesn't support client sizes, the function does nothing.
		virtual void SizeRelative(const Math::Vector2<float>& size) = 0;

		/// @brief Gets a surface style.
		/// @return Surface style.
		[[nodiscard("Pure function")]]
		virtual SurfaceStyle Style() const = 0;
		/// @brief Sets a surface style.
		/// @param style Surface style.
		/// @rematk If the platform doesn't support a style flag, it'll be ignored.
		virtual void Style(SurfaceStyle style) = 0;

		/// @brief Gets if the surface is visible.
		/// @return @a True if it's visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsVisible() const = 0;
		/// @brief Sets the surface visibility.
		/// @param isVisible Should the surface become visible?
		/// @remark If the platform doesn't support a surface visibility, the function does nothing.
		virtual void Visible(bool isVisible) = 0;

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

		/// @brief Gets a minimal client size.
		/// @return Minimal client size.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> MinimalSize() const = 0;
	};
}
