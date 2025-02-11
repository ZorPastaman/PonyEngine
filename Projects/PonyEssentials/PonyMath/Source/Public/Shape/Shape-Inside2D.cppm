/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Inside2D;

import <concepts>;

import PonyMath.Core;

import :Line2D;
import :Ray2D;
import :Rect;
import :Segment2D;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr bool IsInside(const Segment2D<T>& small, const Rect<T>& large) noexcept;

	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Value type.
	/// @param small Small rect.
	/// @param large Large rect.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Rect<T>& small, const Rect<T>& large) noexcept;
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr bool IsInside(const Segment2D<T>& small, const Rect<T>& large) noexcept
	{
		return large.Contains(small.Point0()) && large.Contains(small.Point1());
	}

	template<Core::Arithmetic T>
	constexpr bool IsInside(const Rect<T>& small, const Rect<T>& large) noexcept
	{
		return large.MinX() <= small.MinX() && large.MinY() <= small.MinY() && large.MaxX() >= small.MaxX() && large.MaxY() >= small.MaxY();
	}
}
