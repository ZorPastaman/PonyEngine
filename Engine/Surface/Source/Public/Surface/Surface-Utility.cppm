/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Surface:Utility;

import std;

import PonyEngine.Math;

export namespace PonyEngine::Surface
{
	/// @brief Converts an absolute point to a relative point.
	/// @param point Point.
	/// @param resolution Resolution.
	/// @return Relative point.
	[[nodiscard("Pure function")]]
	constexpr Math::Vector2<float> AbsoluteToRelative(const Math::Vector2<std::int32_t>& point, const Math::Vector2<std::int32_t>& resolution) noexcept;
	/// @brief Converts a relative point to an absolute point.
	/// @param point Point.
	/// @param resolution Resolution.
	/// @return Absolute point.
	[[nodiscard("Pure function")]]
	constexpr Math::Vector2<std::int32_t> RelativeToAbsolute(const Math::Vector2<float>& point, const Math::Vector2<std::int32_t>& resolution) noexcept;
}

namespace PonyEngine::Surface
{
	constexpr Math::Vector2<float> AbsoluteToRelative(const Math::Vector2<std::int32_t>& point, const Math::Vector2<std::int32_t>& resolution) noexcept
	{
		return Math::Divide(static_cast<Math::Vector2<float>>(point), static_cast<Math::Vector2<float>>(resolution));
	}

	constexpr Math::Vector2<std::int32_t> RelativeToAbsolute(const Math::Vector2<float>& point, const Math::Vector2<std::int32_t>& resolution) noexcept
	{
		return Math::RoundToIntegral<std::int32_t>(Math::Multiply(point, static_cast<Math::Vector2<float>>(resolution)));
	}
}
