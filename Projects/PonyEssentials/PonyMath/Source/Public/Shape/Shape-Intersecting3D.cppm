/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Intersecting3D;

import <span>;

import PonyMath.Core;

import :Box;
import :Line3D;
import :Plane;
import :Ray3D;
import :Segment3D;

export namespace PonyMath::Shape
{
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Line3D<T>& line, const Plane<T>& plane) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Line3D<T>& line, const Box<T>& box) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const Plane<T>& plane) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const Box<T>& box) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Segment3D<T>& segment, const Plane<T>& plane) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Segment3D<T>& segment, const Box<T>& box) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& plane, const Line3D<T>& line) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& plane, const Ray3D<T>& ray) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& left, const Plane<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& plane, const Box<T>& box) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Box<T>& box, const Line3D<T>& line) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Box<T>& box, const Ray3D<T>& ray) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Box<T>& box, const Plane<T>& plane) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Box<T>& left, const Box<T>& right) noexcept;
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr bool AreIntersecting(const Core::Vector3<T>& origin, const Core::Vector3<T>& direction, const Box<T>& box, T tMin, T tMax) noexcept;

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line3D<T>& line, const Plane<T>& plane) noexcept
	{
		return Core::Dot(line.Direction(), plane.Normal()) != T{0};
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line3D<T>& line, const Box<T>& box) noexcept
	{
		return AreIntersecting(line.Point(), line.Direction(), box, -std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const Plane<T>& plane) noexcept
	{
		const std::int8_t side = plane.Side(ray.Origin());
		const T dot = Core::Dot(plane.Normal(), ray.Direction());

		return side < std::int8_t{0} && dot > T{0} || side > std::int8_t{0} && dot < T{0};
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const Box<T>& box) noexcept
	{
		return AreIntersecting(ray.Origin(), ray.Direction(), box, T{0}, std::numeric_limits<T>::infinity());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Segment3D<T>& segment, const Plane<T>& plane) noexcept
	{
		const std::int8_t side = plane.Side(segment.Point0());

		return side != std::int8_t{0} && side != plane.Side(segment.Point1());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Segment3D<T>& segment, const Box<T>& box) noexcept
	{
		const Core::Vector3<T> segmentVector = segment.Vector();
		const T length = segmentVector.Magnitude();

		return AreIntersecting(segment.Point0(), segmentVector * (T{1} / length), box, T{0}, length);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& plane, const Line3D<T>& line) noexcept
	{
		return AreIntersecting(line, plane);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& plane, const Ray3D<T>& ray) noexcept
	{
		return AreIntersecting(ray, plane);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& left, const Plane<T>& right) noexcept
	{
		return std::abs(Core::Dot(left.Normal(), right.Normal())) < T{1};
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& plane, const Box<T>& box) noexcept
	{
		for (std::size_t i = 0, positives = 0, negatives = 0; i < Box<T>::CornerCount; ++i)
		{
			const std::int8_t side = plane.Side(box.Corner(i));
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
	constexpr bool AreIntersecting(const Box<T>& box, const Line3D<T>& line) noexcept
	{
		return AreIntersecting(line, box);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Box<T>& box, const Ray3D<T>& ray) noexcept
	{
		return AreIntersecting(ray, box);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Box<T>& box, const Plane<T>& plane) noexcept
	{
		return AreIntersecting(plane, box);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Box<T>& left, const Box<T>& right) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			if (left.Min(i) >= right.Max(i) || left.Max(i) <= right.Min(i))
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Core::Vector3<T>& origin, const Core::Vector3<T>& direction, const Box<T>& box, T tMin, T tMax) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			const T min = box.Min(i) - origin[i];
			const T max = box.Max(i) - origin[i];
			const T multiplier = T{1} / direction[i];
			const Core::Vector2<T> t = Core::Vector2<T>(min, max) * multiplier;
			const auto& [t0, t1] = t.MinMax();

			tMin = std::max(t0, tMin);
			tMax = std::min(t1, tMax);
		}

		return tMin < tMax;
	}
}
