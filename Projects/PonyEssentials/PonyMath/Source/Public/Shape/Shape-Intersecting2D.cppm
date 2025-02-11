/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Intersecting2D;

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
		const T sign = Core::Sign<T>(line.Side(ray.Origin()));

		return Core::Dot(line.Normal(), ray.Direction()) * sign < T{0};
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line2D<T>& line, const Segment2D<T>& segment) noexcept
	{
		return line.Side(segment.Point0()) != line.Side(segment.Point1());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line2D<T>& line, const Rect<T>& rect) noexcept
	{
		const bool side = line.Side(rect.LeftTop());

		return line.Side(rect.RightTop()) != side ||
			line.Side(rect.RightBottom()) != side ||
			line.Side(rect.LeftBottom()) != side;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray2D<T>& left, const Ray2D<T>& right) noexcept
	{
		const T zCross = Core::CrossZ(right, left);
		if (std::abs(zCross) < T{0.0001}) [[unlikely]]
		{
			return false;
		}

		const Core::Vector2<T> delta = right - left;
		const T u = Core::CrossZ(right, delta);
		const T v = Core::CrossZ(left, delta);
		const bool sign = std::signbit(zCross);

		return u != T{0} && v != T{0} && sign == std::signbit(u) && sign == std::signbit(v);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const Line2D<T>& line) noexcept
	{
		return AreIntersecting(line, ray);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const Segment2D<T>& segment) noexcept
	{
		const Core::Vector2<T> inlineVector = segment.Vector();
		const auto perpendicular = Core::Vector2<T>(-ray.Direction().Y(), ray.Direction().X());

		const T dot = Core::Dot(inlineVector, perpendicular);
		const T dotAbs = std::abs(dot);
		if (dotAbs < T{0.0001}) [[unlikely]]
		{
			return false;
		}

		const Core::Vector2<T> segmentToRay = ray.Origin() - segment.Point0();
		const T u = Core::CrossZ(inlineVector, segmentToRay);
		const T v = Core::Dot(segmentToRay, perpendicular);
		const bool sign = std::signbit(dot);

		return u != T{0} && v != T{0} && sign == std::signbit(u) && sign == std::signbit(v) && std::abs(v) < dotAbs;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const Rect<T>& rect) noexcept
	{
		return AreIntersecting(ray.Origin(), ray.Direction(), rect, T{0}, std::numeric_limits<T>::infinity);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Segment2D<T>& left, const Segment2D<T>& right) noexcept
	{
		const auto leftLine = Line2D<T>(left);
		const auto rightLine = Line2D<T>(right);

		return leftLine.Side(right.Point0()) != leftLine.Side(right.Point1()) && rightLine.Side(left.Point0()) != rightLine.Side(right.Point1());
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
		return !(left.MinX() >= right.MaxX() || left.MaxX() <= right.MinX() || left.MinY() >= right.MaxY() || left.MaxY() <= right.MinY());
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
		const Core::Vector2<T> rectMin = rect.Min();
		const Core::Vector2<T> rectMax = rect.Max();
		const auto directionInv = Core::Vector2<T>(T{1} / direction().X(), T{1} / direction().Y());

		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			const T t0 = (rectMin[i] - origin()[i]) * directionInv[i];
			const T t1 = (rectMax[i] - origin()[i]) * directionInv[i];

			tMin = std::max(tMin, std::min(std::min(t0, t1), tMax));
			tMax = std::min(tMax, std::max(std::max(t0, t1), tMin));
		}

		return tMin < tMax;
	}
}
