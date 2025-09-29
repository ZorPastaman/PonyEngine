/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Surface.Main:Utility;

import std;

import PonyEngine.Math;
import PonyEngine.Surface;

export namespace PonyEngine::Surface
{
	/// @brief Calculates a client position delta.
	/// @param position Client position.
	/// @param size Client size.
	/// @param resolution Screen resolution.
	/// @param positionMode Position mode.
	/// @return Client position delta.
	[[nodiscard("Pure function")]]
	constexpr Math::Vector2<std::int32_t> CalculateDelta(const Math::Vector2<std::int32_t>& position, const Math::Vector2<std::int32_t>& size,
		const Math::Vector2<std::int32_t>& resolution, SurfacePositionMode positionMode) noexcept;
	/// @brief Calculates a client position.
	/// @param delta Client position delta.
	/// @param size Client size.
	/// @param resolution Screen resolution.
	/// @param positionMode Position mode.
	/// @return Client position.
	[[nodiscard("Pure function")]]
	constexpr Math::Vector2<std::int32_t> CalculatePosition(const Math::Vector2<std::int32_t>& delta, const Math::Vector2<std::int32_t>& size,
		const Math::Vector2<std::int32_t>& resolution, SurfacePositionMode positionMode) noexcept;
}

namespace PonyEngine::Surface
{
	constexpr Math::Vector2<std::int32_t> CalculateDelta(const Math::Vector2<std::int32_t>& position, const Math::Vector2<std::int32_t>& size, 
		const Math::Vector2<std::int32_t>& resolution, const SurfacePositionMode positionMode) noexcept
	{
		Math::Vector2<std::int32_t> clientPoint;
		Math::Vector2<std::int32_t> screenPoint;

		switch (positionMode)
		{
		case SurfacePositionMode::LeftTopCorner:
			clientPoint = position;
			screenPoint = Math::Vector2<int>::Zero();
			break;
		case SurfacePositionMode::RightTopCorner:
			clientPoint = Math::Vector2<int>(position.X() + size.X(), position.Y());
			screenPoint = Math::Vector2<int>(resolution.X(), 0);
			break;
		case SurfacePositionMode::LeftBottomCorner:
			clientPoint = Math::Vector2<int>(position.X(), position.Y() + size.Y());
			screenPoint = Math::Vector2<int>(0, resolution.Y());
			break;
		case SurfacePositionMode::RightBottomCorner:
			clientPoint = position + size;
			screenPoint = resolution;
			break;
		case SurfacePositionMode::Center:
			clientPoint = position + size / 2;
			screenPoint = resolution / 2;
			break;
		default: [[unlikely]]
			assert(false && "Unexpected position mode.");
			break;
		}

		return clientPoint - screenPoint;
	}

	constexpr Math::Vector2<std::int32_t> CalculatePosition(const Math::Vector2<std::int32_t>& delta, const Math::Vector2<std::int32_t>& size, 
		const Math::Vector2<std::int32_t>& resolution, const SurfacePositionMode positionMode) noexcept
	{
		switch (positionMode)
		{
		case SurfacePositionMode::LeftTopCorner:
			return delta;
		case SurfacePositionMode::RightTopCorner:
			return Math::Vector2<std::int32_t>(resolution.X() + delta.X() - size.X(), delta.Y());
		case SurfacePositionMode::LeftBottomCorner:
			return Math::Vector2<std::int32_t>(delta.X(), resolution.Y() + delta.Y() - size.Y());
		case SurfacePositionMode::RightBottomCorner:
			return resolution + delta - size;
		case SurfacePositionMode::Center:
			return resolution / 2 + delta - size / 2;
		default: [[unlikely]]
			assert(false && "Unexpected position mode.");
			return delta;
		}
	}
}
