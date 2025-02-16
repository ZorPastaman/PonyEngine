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

import :AABR;
import :Line2D;
import :Ray2D;
import :Rect;
import :Segment2D;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr bool IsInside(const Segment2D<T>& small, const Rect<T>& large) noexcept;
	template<std::floating_point T>
	constexpr bool IsInside(const Segment2D<T>& small, const AABR<T>& large) noexcept;
	template<std::floating_point T>
	constexpr bool IsInside(const Segment2D<T>& small, const AABR<T>& large, T angle) noexcept;

	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const AABR<T>& small, const AABR<T>& large) noexcept;
	template<std::floating_point T>
	constexpr bool IsInside(const AABR<T>& small, T smallAngle, const AABR<T>& large, T largeAngle) noexcept;

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
	constexpr bool IsInside(const Core::Vector2<T>& min, const Core::Vector2<T>& max, const AABR<T>& large) noexcept;
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Core::Vector2<T>& min, const Core::Vector2<T>& max, const Rect<T>& large) noexcept;

	template<std::floating_point T>
	constexpr bool IsInside(const Segment2D<T>& small, const Rect<T>& large) noexcept
	{
		const Core::Vector2<T> min = Core::Min(small.Point0(), small.Point1());
		const Core::Vector2<T> max = Core::Max(small.Point0(), small.Point1());

		return IsInside(min, max, large);
	}

	template<std::floating_point T>
	constexpr bool IsInside(const Segment2D<T>& small, const AABR<T>& large) noexcept
	{
		const Core::Vector2<T> min = Core::Min(small.Point0(), small.Point1());
		const Core::Vector2<T> max = Core::Max(small.Point0(), small.Point1());

		return IsInside(min, max, large);
	}

	template<std::floating_point T>
	constexpr bool IsInside(const Segment2D<T>& small, const AABR<T>& large, const T angle) noexcept
	{
		const Core::Matrix2x2<T> inverseRotation = Core::RotationMatrix(-angle);
		const Core::Vector2<T> point0 = inverseRotation * (small.Point0() - large.Center());
		const Core::Vector2<T> point1 = inverseRotation * (small.Point1() - large.Center());
		const AABR<T> aarb = AABR<T>(Core::Vector2<T>::Predefined::Zero, large.Extents());

		return IsInside(Segment2D<T>(point0, point1), aarb);
	}

	template<Core::Arithmetic T>
	constexpr bool IsInside(const AABR<T>& small, const AABR<T>& large) noexcept
	{
		return IsInside(small.Min(), small.Max(), large);
	}

	template<std::floating_point T>
	constexpr bool IsInside(const AABR<T>& small, const T smallAngle, const AABR<T>& large, const T largeAngle) noexcept
	{
		const std::array<Core::Vector2<T>, 4> smallCorners = small.Corners(smallAngle);
		const AABR<T> simpleLarge = AABR<T>(Core::Vector2<T>::Predefined::Zero, large.Extents());
		const Core::Matrix2x2<T> inverseLargeRotation = Core::RotationMatrix(-largeAngle);

		for (const Core::Vector2<T>& smallCorner : smallCorners)
		{
			if (!simpleLarge.Contains(inverseLargeRotation * (smallCorner - large.Center())))
			{
				return false;
			}
		}

		return true;
	}

	template<Core::Arithmetic T>
	constexpr bool IsInside(const Rect<T>& small, const Rect<T>& large) noexcept
	{
		return IsInside(small.Min(), small.Max(), large);
	}

	template<Core::Arithmetic T>
	constexpr bool IsInside(const Core::Vector2<T>& min, const Core::Vector2<T>& max, const AABR<T>& large) noexcept
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
