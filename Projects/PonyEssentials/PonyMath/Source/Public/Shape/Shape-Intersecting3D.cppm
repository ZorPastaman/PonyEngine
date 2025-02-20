/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Intersecting3D;

import <algorithm>;
import <span>;

import PonyMath.Core;

import :AABB;
import :OBB;
import :Plane;
import :Ray3D;

export namespace PonyMath::Shape
{
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const Plane<T>& plane, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const AABB<T>& aabb, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const OBB<T>& obb, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& left, const Plane<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& plane, const Ray3D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& plane, const AABB<T>& aabb) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& plane, const OBB<T>& obb) noexcept;

	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABB<T>& left, const AABB<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABB<T>& aabb, const Ray3D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABB<T>& aabb, const Plane<T>& plane) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABB<T>& aabb, const OBB<T>& obb) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const OBB<T>& left, const OBB<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const OBB<T>& obb, const Ray3D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const OBB<T>& obb, const Plane<T>& plane) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const OBB<T>& obb, const AABB<T>& aabb) noexcept;
}

namespace PonyMath::Shape
{
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& plane, std::span<const Core::Vector3<T>> corners) noexcept;

	template<std::floating_point T, std::size_t CornerCount> [[nodiscard("Pure function")]]
	constexpr bool CheckSat(const Core::Vector3<T>& center, const Core::Vector3<T>& extents, std::span<const Core::Vector3<T>, 3> axes, std::span<const Core::Vector3<T>, CornerCount> corners);
	template<std::floating_point T, std::size_t LeftCornerCount, std::size_t RightCornerCount> [[nodiscard("Pure function")]]
	constexpr bool CheckSat(std::span<const Core::Vector3<T>> leftAxes, std::span<const Core::Vector3<T>> rightAxes, 
		std::span<const Core::Vector3<T>, LeftCornerCount> leftCorners, std::span<const Core::Vector3<T>, RightCornerCount> rightCorners);

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const Plane<T>& plane, const T maxDistance) noexcept
	{
		const T distance = plane.Distance(ray.Origin());
		const T dot = Core::Dot(plane.Normal(), ray.Direction());

		return std::signbit(distance) != std::signbit(dot) && std::abs(distance) > T{0.0001} && std::abs(dot) > T{0.0001} &&
			-distance / dot < maxDistance;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const AABB<T>& aabb, const T maxDistance) noexcept
	{
		T tMin = T{0};
		T tMax = maxDistance;

		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			const T min = aabb.Min(i) - ray.Origin()[i];
			const T max = aabb.Max(i) - ray.Origin()[i];
			const T direction = ray.Direction()[i];
			if (std::abs(direction) < T{0.0001})
			{
				if (min < T{0} && max < T{0} || min > T{0} && max > T{0})
				{
					return false;
				}

				continue;
			}

			const T multiplier = T{1} / direction;
			const Core::Vector2<T> t = Core::Vector2<T>(min, max) * multiplier;
			const auto& [t0, t1] = t.MinMax();

			tMin = std::max(tMin, t0);
			tMax = std::min(tMax, t1);
		}

		return tMin > T{0.0001} && tMin <= tMax;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const OBB<T>& obb, const T maxDistance) noexcept
	{
		const Core::Matrix3x3<T> inverseRotation = Core::RotationMatrix(obb.AxisX(), obb.AxisY(), obb.AxisZ()).Inverse();
		const Core::Vector3<T> origin = inverseRotation * (ray.Origin() - obb.Center());
		const Core::Vector3<T> direction = inverseRotation * ray.Direction();
		const AABB<T> aabb = AABB<T>(Core::Vector3<T>::Predefined::Zero, obb.Extents());

		return AreIntersecting(Ray3D<T>(origin, direction), aabb, maxDistance);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& left, const Plane<T>& right) noexcept
	{
		return std::abs(Core::Dot(left.Normal(), right.Normal())) < T{1};
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& plane, const Ray3D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, plane, maxDistance);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& plane, const AABB<T>& aabb) noexcept
	{
		return AreIntersecting(plane, aabb.Corners());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& plane, const OBB<T>& obb) noexcept
	{
		return AreIntersecting(plane, obb.Corners());
	}

	template<Core::Arithmetic T>
	constexpr bool AreIntersecting(const AABB<T>& left, const AABB<T>& right) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			if (left.Min(i) > right.Max(i) || left.Max(i) < right.Min(i))
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const AABB<T>& aabb, const Ray3D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, aabb, maxDistance);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const AABB<T>& aabb, const Plane<T>& plane) noexcept
	{
		return AreIntersecting(plane, aabb);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const AABB<T>& aabb, const OBB<T>& obb) noexcept
	{
		const std::array<Core::Vector3<T>, 8> aabbCorners = aabb.Corners();
		const std::array<Core::Vector3<T>, 8> obbCorners = obb.Corners();

		return CheckSat(aabb.Center(), aabb.Extents(), AABB<T>::Axes, obbCorners) &&
			CheckSat(obb.Center(), obb.Extents(), obb.Axes(), aabbCorners) &&
			CheckSat(AABB<T>::Axes, obb.Axes(), aabbCorners, obbCorners);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const OBB<T>& left, const OBB<T>& right) noexcept
	{
		const std::array<Core::Vector3<T>, 8> leftCorners = left.Corners();
		const std::array<Core::Vector3<T>, 8> rightCorners = right.Corners();

		return CheckSat(left.Center(), left.Extents(), left.Axes(), rightCorners) &&
			CheckSat(right.Center(), right.Extents(), right.Axes(), leftCorners) &&
			CheckSat(left.Axes(), right.Axes(), leftCorners, rightCorners);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const OBB<T>& obb, const Ray3D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, obb, maxDistance);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const OBB<T>& obb, const Plane<T>& plane) noexcept
	{
		return AreIntersecting(plane, obb);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const OBB<T>& obb, const AABB<T>& aabb) noexcept
	{
		return AreIntersecting(aabb, obb);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& plane, const std::span<const Core::Vector3<T>> corners) noexcept
	{
		for (std::size_t positives = 0, negatives = 0; const Core::Vector3<T>& corner : corners)
		{
			const std::int8_t side = plane.Side(corner);
			positives += side > std::int8_t{0};
			negatives += side < std::int8_t{0};

			if (side == std::int8_t{0} || positives > 0 && negatives > 0)
			{
				return true;
			}
		}

		return false;
	}

	template<std::floating_point T, std::size_t CornerCount>
	constexpr bool CheckSat(const Core::Vector3<T>& center, const Core::Vector3<T>& extents, const std::span<const Core::Vector3<T>, 3> axes, const std::span<const Core::Vector3<T>, CornerCount> corners)
	{
		for (std::size_t axisIndex = 0; axisIndex < 3; ++axisIndex)
		{
			const Core::Vector3<T>& axis = axes[axisIndex];
			const T extent = extents[axisIndex];

			std::array<T, CornerCount> projections;
			for (std::size_t cornerIndex = 0; cornerIndex < CornerCount; ++cornerIndex)
			{
				projections[cornerIndex] = Core::Dot(axis, corners[cornerIndex] - center);
			}

			const auto [min, max] = std::ranges::minmax_element(projections);
			if (*min > extent || *max < -extent)
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T, std::size_t LeftCornerCount, std::size_t RightCornerCount>
	constexpr bool CheckSat(const std::span<const Core::Vector3<T>> leftAxes, const std::span<const Core::Vector3<T>> rightAxes, 
		const std::span<const Core::Vector3<T>, LeftCornerCount> leftCorners, const std::span<const Core::Vector3<T>, RightCornerCount> rightCorners)
	{
		for (const Core::Vector3<T>& leftAxis : leftAxes)
		{
			for (const Core::Vector3<T>& rightAxis : rightAxes)
			{
				const Core::Vector3<T> axis = Core::Cross(leftAxis, rightAxis);

				std::array<T, LeftCornerCount> leftProjections;
				for (std::size_t cornerIndex = 0; cornerIndex < LeftCornerCount; ++cornerIndex)
				{
					leftProjections[cornerIndex] = Core::Dot(axis, leftCorners[cornerIndex]);
				}
				std::array<T, RightCornerCount> rightProjections;
				for (std::size_t cornerIndex = 0; cornerIndex < RightCornerCount; ++cornerIndex)
				{
					rightProjections[cornerIndex] = Core::Dot(axis, rightCorners[cornerIndex]);
				}

				const auto [leftMin, leftMax] = std::ranges::minmax_element(leftProjections);
				const auto [rightMin, rightMax] = std::ranges::minmax_element(rightProjections);
				if (*leftMin > *rightMax || *leftMax < *rightMin)
				{
					return false;
				}
			}
		}

		return true;
	}
}
