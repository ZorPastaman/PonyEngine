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
import <array>;
import <cmath>;
import <concepts>;
import <cstddef>;
import <cstdint>;
import <limits>;
import <span>;

import PonyMath.Core;

import :AABB;
import :OBB;
import :Plane;
import :Ray3D;

export namespace PonyMath::Shape
{
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param ray Ray.
	/// @param plane Plane.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray3D<T>& ray, const Plane<T>& plane, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param ray Ray.
	/// @param aabb Axis-aligned bounding box.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray3D<T>& ray, const AABB<T>& aabb, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param ray Ray.
	/// @param obb Oriented bounding box.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray3D<T>& ray, const OBB<T>& obb, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;

	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param left Left plane.
	/// @param right Right plane.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Plane<T>& left, const Plane<T>& right) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param plane Plane.
	/// @param ray Ray.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Plane<T>& plane, const Ray3D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param plane Plane.
	/// @param aabb Axis-aligned bounding box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Plane<T>& plane, const AABB<T>& aabb) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param plane Plane.
	/// @param obb Oriented bounding box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Plane<T>& plane, const OBB<T>& obb) noexcept;

	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param left Left axis-aligned bounding box.
	/// @param right Right axis-aligned bounding box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const AABB<T>& left, const AABB<T>& right) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param aabb Axis-aligned bounding box.
	/// @param ray Ray.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const AABB<T>& aabb, const Ray3D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param aabb Axis-aligned bounding box.
	/// @param plane Plane.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const AABB<T>& aabb, const Plane<T>& plane) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param aabb Axis-aligned bounding box.
	/// @param obb Oriented bounding box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const AABB<T>& aabb, const OBB<T>& obb) noexcept;

	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param left Left oriented bounding box.
	/// @param right Right oriented bounding box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const OBB<T>& left, const OBB<T>& right) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param obb Oriented bounding box.
	/// @param ray Ray.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const OBB<T>& obb, const Ray3D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param obb Oriented bounding box.
	/// @param plane Plane.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const OBB<T>& obb, const Plane<T>& plane) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param obb Oriented bounding box.
	/// @param aabb Axis-aligned bounding box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const OBB<T>& obb, const AABB<T>& aabb) noexcept;
}

namespace PonyMath::Shape
{
	/// @brief Checks if the @p plane intersects a convex shape described with the @p corners.
	/// @tparam T Component type.
	/// @param plane Plane.
	/// @param corners Convex shape corners.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Plane<T>& plane, std::span<const Core::Vector3<T>> corners) noexcept;

	/// @brief Checks if a box intersects a convex shape described with the @p corners using separating axis theorem.
	/// @note It's one normal step of the theorem. The calling function must call other steps.
	/// @tparam T Component type.
	/// @tparam CornerCount Corner count.
	/// @param center Box center.
	/// @param extents Box extents.
	/// @param axes Box axes.
	/// @param corners Convex shape corners.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t CornerCount> [[nodiscard("Pure function")]]
	bool CheckSat(const Core::Vector3<T>& center, const Core::Vector3<T>& extents, std::span<const Core::Vector3<T>, 3> axes, std::span<const Core::Vector3<T>, CornerCount> corners);
	/// @brief Checks if convex shapes described with corners are intersecting using separating axis theorem.
	/// @note It's one cross step of the theorem. The calling function must call other steps.
	/// @tparam T Component type.
	/// @tparam LeftCornerCount Left shape corner count.
	/// @tparam RightCornerCount Right shape corner count.
	/// @param leftAxes Left shape axes.
	/// @param rightAxes Right shape axes.
	/// @param leftCorners Left shape corners.
	/// @param rightCorners Right shape corners.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t LeftCornerCount, std::size_t RightCornerCount> [[nodiscard("Pure function")]]
	bool CheckSat(std::span<const Core::Vector3<T>> leftAxes, std::span<const Core::Vector3<T>> rightAxes, 
		std::span<const Core::Vector3<T>, LeftCornerCount> leftCorners, std::span<const Core::Vector3<T>, RightCornerCount> rightCorners);

	template<std::floating_point T>
	bool AreIntersecting(const Ray3D<T>& ray, const Plane<T>& plane, const T maxDistance) noexcept
	{
		const T distance = plane.Distance(ray.Origin());
		const T dot = Core::Dot(plane.Normal(), ray.Direction());

		return std::signbit(distance) != std::signbit(dot) && std::abs(distance) > T{0.0001} && std::abs(dot) > T{0.0001} &&
			-distance / dot < maxDistance;
	}

	template<std::floating_point T>
	bool AreIntersecting(const Ray3D<T>& ray, const AABB<T>& aabb, const T maxDistance) noexcept
	{
		T tMin = T{0};
		T tMax = maxDistance;

		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			const T min = aabb.Min(i) - ray.Origin()[i];
			const T max = aabb.Max(i) - ray.Origin()[i];
			const T direction = ray.Direction()[i];
			if (std::abs(direction) < T{0.0001}) [[unlikely]]
			{
				if (std::signbit(min) == std::signbit(max) && std::abs(min) > T{0} && std::abs(max) > T{0})
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
	bool AreIntersecting(const Ray3D<T>& ray, const OBB<T>& obb, const T maxDistance) noexcept
	{
		const Core::Matrix3x3<T> inverseRotation = Core::Matrix3x3<T>(obb.Axes()).Transpose();
		const Core::Vector3<T> origin = inverseRotation * (ray.Origin() - obb.Center());
		const Core::Vector3<T> direction = inverseRotation * ray.Direction();
		const Ray3D<T> rotatedRay = Ray3D<T>(origin, direction);
		const AABB<T> aabb = AABB<T>(Core::Vector3<T>::Predefined::Zero, obb.Extents());

		return AreIntersecting(rotatedRay, aabb, maxDistance);
	}

	template<std::floating_point T>
	bool AreIntersecting(const Plane<T>& left, const Plane<T>& right) noexcept
	{
		return std::abs(Core::Dot(left.Normal(), right.Normal())) < T{0.9999};
	}

	template<std::floating_point T>
	bool AreIntersecting(const Plane<T>& plane, const Ray3D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, plane, maxDistance);
	}

	template<std::floating_point T>
	bool AreIntersecting(const Plane<T>& plane, const AABB<T>& aabb) noexcept
	{
		const std::array<Core::Vector3<T>, AABB<T>::CornerCount> corners = aabb.Corners();

		return AreIntersecting(plane, std::span<const Core::Vector3<float>>(corners.data(), corners.size()));
	}

	template<std::floating_point T>
	bool AreIntersecting(const Plane<T>& plane, const OBB<T>& obb) noexcept
	{
		const std::array<Core::Vector3<T>, OBB<T>::CornerCount> corners = obb.Corners();

		return AreIntersecting(plane, std::span<const Core::Vector3<float>>(corners.data(), corners.size()));
	}

	template<Core::Arithmetic T>
	bool AreIntersecting(const AABB<T>& left, const AABB<T>& right) noexcept
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
	bool AreIntersecting(const AABB<T>& aabb, const Ray3D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, aabb, maxDistance);
	}

	template<std::floating_point T>
	bool AreIntersecting(const AABB<T>& aabb, const Plane<T>& plane) noexcept
	{
		return AreIntersecting(plane, aabb);
	}

	template<std::floating_point T>
	bool AreIntersecting(const AABB<T>& aabb, const OBB<T>& obb) noexcept
	{
		const std::array<Core::Vector3<T>, AABB<T>::CornerCount> aabbCorners = aabb.Corners();
		const std::array<Core::Vector3<T>, OBB<T>::CornerCount> obbCorners = obb.Corners();

		return CheckSat<T, OBB<T>::CornerCount>(aabb.Center(), aabb.Extents(), AABB<T>::Axes, obbCorners) &&
			CheckSat<T, AABB<T>::CornerCount>(obb.Center(), obb.Extents(), obb.Axes(), aabbCorners) &&
			CheckSat<T, AABB<T>::CornerCount, OBB<T>::CornerCount>(AABB<T>::Axes, obb.Axes(), aabbCorners, obbCorners);
	}

	template<std::floating_point T>
	bool AreIntersecting(const OBB<T>& left, const OBB<T>& right) noexcept
	{
		const std::array<Core::Vector3<T>, OBB<T>::CornerCount> leftCorners = left.Corners();
		const std::array<Core::Vector3<T>, OBB<T>::CornerCount> rightCorners = right.Corners();

		return CheckSat<T, OBB<T>::CornerCount>(left.Center(), left.Extents(), left.Axes(), rightCorners) &&
			CheckSat<T, OBB<T>::CornerCount>(right.Center(), right.Extents(), right.Axes(), leftCorners) &&
			CheckSat<T, OBB<T>::CornerCount, OBB<T>::CornerCount>(left.Axes(), right.Axes(), leftCorners, rightCorners);
	}

	template<std::floating_point T>
	bool AreIntersecting(const OBB<T>& obb, const Ray3D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, obb, maxDistance);
	}

	template<std::floating_point T>
	bool AreIntersecting(const OBB<T>& obb, const Plane<T>& plane) noexcept
	{
		return AreIntersecting(plane, obb);
	}

	template<std::floating_point T>
	bool AreIntersecting(const OBB<T>& obb, const AABB<T>& aabb) noexcept
	{
		return AreIntersecting(aabb, obb);
	}

	template<std::floating_point T>
	bool AreIntersecting(const Plane<T>& plane, const std::span<const Core::Vector3<T>> corners) noexcept
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
	bool CheckSat(const Core::Vector3<T>& center, const Core::Vector3<T>& extents, const std::span<const Core::Vector3<T>, 3> axes, const std::span<const Core::Vector3<T>, CornerCount> corners)
	{
		for (std::size_t axisIndex = 0; axisIndex < Core::Vector3<T>::ComponentCount; ++axisIndex)
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
	bool CheckSat(const std::span<const Core::Vector3<T>> leftAxes, const std::span<const Core::Vector3<T>> rightAxes, 
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
