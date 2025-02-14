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
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Core::Vector2<T>& min, const Core::Vector2<T>& max, const Rect<T>& large) noexcept;

	template<std::floating_point T>
	constexpr bool IsInside(const Segment2D<T>& small, const Rect<T>& large) noexcept
	{
		const Core::Vector2<T> min = Core::Min(small.Point0(), small.Point1());
		const Core::Vector2<T> max = Core::Max(small.Point0(), small.Point1());

		return IsInside(min, max, large);
	}

	template<Core::Arithmetic T>
	constexpr bool IsInside(const Rect<T>& small, const Rect<T>& large) noexcept
	{
		return IsInside(small.Min(), small.Max(), large);
	}

	template<Core::Arithmetic T>
	constexpr bool IsInside(const Core::Vector2<T>& min, const Core::Vector2<T>& max, const Rect<T>& large) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			if (min[i] < large.Min(i) || max[i] > large.Max(i))
			{
				return false;
			}
		}

		return true;
	}
}
