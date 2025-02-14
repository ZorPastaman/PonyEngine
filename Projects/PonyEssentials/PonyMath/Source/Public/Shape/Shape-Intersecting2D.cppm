/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Intersecting2D;

import <span>;

import PonyMath.Core;

import :Line2D;
import :Ray2D;
import :Rect;
import :Segment2D;

export namespace PonyMath::Shape
{
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Line2D<T>& left, const Line2D<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Line2D<T>& line, const Ray2D<T>& ray) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Line2D<T>& line, const Segment2D<T>& segment) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Line2D<T>& line, const Rect<T>& rect) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray2D<T>& left, const Ray2D<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const Line2D<T>& line) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const Segment2D<T>& segment) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const Rect<T>& rect) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Segment2D<T>& left, const Segment2D<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Segment2D<T>& segment, const Line2D<T>& line) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Segment2D<T>& segment, const Ray2D<T>& ray) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Segment2D<T>& segment, const Rect<T>& rect) noexcept;

	/// @brief Checks if two rects are intersecting.
	/// @tparam T Value type.
	/// @param left Left rect.
	/// @param right Right rect.
	/// @return @a True if they intersect; @a false otherwise.
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Rect<T>& left, const Rect<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Rect<T>& rect, const Line2D<T>& line) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Rect<T>& rect, const Ray2D<T>& ray) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Rect<T>& rect, const Segment2D<T>& segment) noexcept;
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr bool AreIntersecting(const Core::Vector2<T>& origin, const Core::Vector2<T>& direction, const Rect<T>& rect, T tMin, T tMax) noexcept;

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line2D<T>& left, const Line2D<T>& right) noexcept
	{
		return std::abs(Core::Dot(left.Normal(), right.Normal())) < T{1};
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line2D<T>& line, const Ray2D<T>& ray) noexcept
	{
		const std::int8_t side = line.Side(ray.Origin());
		const T dot = Core::Dot(line.Normal(), ray.Direction());

		return side < std::int8_t{0} && dot > T{0} || side > std::int8_t{0} && dot < T{0};
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line2D<T>& line, const Segment2D<T>& segment) noexcept
	{
		const std::int8_t side = line.Side(segment.Point0());

		return side != std::int8_t{0} && side != line.Side(segment.Point1());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line2D<T>& line, const Rect<T>& rect) noexcept
	{
		for (std::size_t i = 0, positives = 0, negatives = 0; i < Rect<T>::CornerCount; ++i)
		{
			const std::int8_t side = line.Side(rect.Corner(i));
			positives += side > std::int8_t{0};
			negatives += side < std::int8_t{0};

			if (positives > std::int8_t{0} && negatives > std::int8_t{0})
			{
				return true;
			}
		}

		return false;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray2D<T>& left, const Ray2D<T>& right) noexcept
	{
		const Core::Vector2<T> leftToRight = right.Origin() - left.Origin();

		const T u = Core::CrossZ(right.Direction(), leftToRight);
		const T v = Core::CrossZ(left.Direction(), leftToRight);
		const T det = Core::CrossZ(right.Direction(), left.Direction());

		return u > T{0} && v > T{0} && det > T{0} || u < T{0} && v < T{0} && det < T{0};
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const Line2D<T>& line) noexcept
	{
		return AreIntersecting(line, ray);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const Segment2D<T>& segment) noexcept
	{
		const Core::Vector2<T> segmentToRay = ray.Origin() - segment.Point0();
		const Core::Vector2<T> inlineVector = segment.Vector();
		const auto perpendicular = Core::Vector2<T>(-ray.Direction().Y(), ray.Direction().X());

		const T u = Core::CrossZ(inlineVector, segmentToRay);
		const T v = Core::Dot(segmentToRay, perpendicular);
		const T dot = Core::Dot(inlineVector, perpendicular);

		return u > T{0} && v > T{0} && v < dot || u < T{0} && v < T{0} && v > dot;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const Rect<T>& rect) noexcept
	{
		return AreIntersecting(ray.Origin(), ray.Direction(), rect, T{0}, std::numeric_limits<T>::infinity());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Segment2D<T>& left, const Segment2D<T>& right) noexcept
	{
		return AreIntersecting(Line2D<T>(left), right) && AreIntersecting(Line2D<T>(right), left);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Segment2D<T>& segment, const Line2D<T>& line) noexcept
	{
		return AreIntersecting(line, segment);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Segment2D<T>& segment, const Ray2D<T>& ray) noexcept
	{
		return AreIntersecting(ray, segment);
	}                                                              

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Segment2D<T>& segment, const Rect<T>& rect) noexcept
	{
		const Core::Vector2<T> segmentVector = segment.Vector();
		const T length = segmentVector.Magnitude();

		return AreIntersecting(segment.Point0(), segmentVector * (T{1} / length), rect, T{0}, length);
	}

	template<Core::Arithmetic T>
	constexpr bool AreIntersecting(const Rect<T>& left, const Rect<T>& right) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			if (left.Min(i) >= right.Max(i) || left.Max(i) <= right.Min(i))
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Rect<T>& rect, const Line2D<T>& line) noexcept
	{
		return AreIntersecting(line, rect);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Rect<T>& rect, const Ray2D<T>& ray) noexcept
	{
		return AreIntersecting(ray, rect);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Rect<T>& rect, const Segment2D<T>& segment) noexcept
	{
		return AreIntersecting(segment, rect);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Core::Vector2<T>& origin, const Core::Vector2<T>& direction, const Rect<T>& rect, T tMin, T tMax) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			const T min = rect.Min(i) - origin[i];
			const T max = rect.Max(i) - origin[i];
			const T multiplier = T{1} / direction[i];
			const Core::Vector2<T> t = Core::Vector2<T>(min, max) * multiplier;
			const auto& [t0, t1] = t.MinMax();

			tMin = std::max(t0, tMin);
			tMax = std::min(t1, tMax);
		}

		return tMin < tMax;
	}
}
