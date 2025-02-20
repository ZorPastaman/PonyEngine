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
import :Box;
import :Plane;
import :Ray3D;

export namespace PonyMath::Shape
{
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const Plane<T>& plane) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const AABB<T>& aabb) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const AABB<T>& aabb, const Core::Quaternion<T>& rotation) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const Box<T>& box) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& left, const Plane<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& plane, const Ray3D<T>& ray) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& plane, const AABB<T>& aabb) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& plane, const AABB<T>& aabb, const Core::Quaternion<T>& rotation) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& plane, const Box<T>& box) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABB<T>& left, const AABB<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABB<T>& left, const Core::Quaternion<T>& leftRotation, const AABB<T>& right, const Core::Quaternion<T>& rightRotation) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABB<T>& aabb, const Ray3D<T>& ray) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABB<T>& aabb, const Core::Quaternion<T>& rotation, const Ray3D<T>& ray) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABB<T>& aabb, const Plane<T>& plane) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABB<T>& aabb, const Core::Quaternion<T>& rotation, const Plane<T>& plane) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Box<T>& left, const Box<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Box<T>& box, const Ray3D<T>& ray) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Box<T>& box, const Plane<T>& plane) noexcept;
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr bool AreIntersecting(const Core::Vector3<T>& origin, const Core::Vector3<T>& direction, const AABB<T>& aabb, T tMin, T tMax) noexcept;
	template<std::floating_point T>
	constexpr bool AreIntersecting(const Core::Vector3<T>& origin, const Core::Vector3<T>& direction, const Box<T>& box, T tMin, T tMax) noexcept;

	template<std::floating_point T, std::size_t CornerCount>
	constexpr bool AreIntersecting(const Core::Vector3<T>& origin, std::span<const Core::Vector3<T>> edges, std::span<const Core::Vector3<T>, CornerCount> corners) noexcept;
	template<std::floating_point T, std::size_t LeftCornerCount, std::size_t RightCornerCount>
	constexpr bool AreIntersecting(std::span<const Core::Vector3<T>> leftEdges, std::span<const Core::Vector3<T>, LeftCornerCount> leftCorners, 
		std::span<const Core::Vector3<T>> rightEdges, std::span<const Core::Vector3<T>, RightCornerCount> rightCorners) noexcept;

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const Plane<T>& plane) noexcept
	{
		const std::int8_t side = plane.Side(ray.Origin());
		const T dot = Core::Dot(plane.Normal(), ray.Direction());

		return side < std::int8_t{0} && dot > T{0} || side > std::int8_t{0} && dot < T{0};
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const AABB<T>& aabb) noexcept
	{
		return AreIntersecting(ray.Point(), ray.Direction(), aabb, T{0}, std::numeric_limits<T>::infinity());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const AABB<T>& aabb, const Core::Quaternion<T>& rotation) noexcept
	{
		const Core::Quaternion<T> conjugate = rotation.Conjugate();
		const Core::Vector3<T> origin = conjugate * (ray.Origin() - aabb.Center());
		const Core::Vector3<T> direction = conjugate * ray.Direction();
		const AABB<T> simpleAabr = AABR(Core::Vector3<T>::Predefined::Zero, aabb.Extents());

		return AreIntersecting(origin, direction, simpleAabr, T{0}, std::numeric_limits<T>::infinity());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray3D<T>& ray, const Box<T>& box) noexcept
	{
		return AreIntersecting(ray.Origin(), ray.Direction(), box, T{0}, std::numeric_limits<T>::infinity());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& left, const Plane<T>& right) noexcept
	{
		return std::abs(Core::Dot(left.Normal(), right.Normal())) < T{ 1 };
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& plane, const Ray3D<T>& ray) noexcept
	{
		return AreIntersecting(ray, plane);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& plane, const AABB<T>& aabb) noexcept
	{
		for (std::size_t i = 0, positives = 0, negatives = 0; i < Box<T>::CornerCount; ++i)
		{
			const std::int8_t side = plane.Side(aabb.Corner(i));
			positives += side > std::int8_t{0};
			negatives += side < std::int8_t{0};

			if (positives > 0 && negatives > 0)
			{
				return true;
			}
		}

		return false;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& plane, const AABB<T>& aabb, const Core::Quaternion<T>& rotation) noexcept
	{
		const std::array<Core::Vector3<T>, 8> corners = aabb.Corners(rotation);

		for (std::size_t i = 0, positives = 0, negatives = 0; i < 8; ++i)
		{
			const std::int8_t side = plane.Side(corners[i]);
			positives += side > std::int8_t{0};
			negatives += side < std::int8_t{0};

			if (positives > 0 && negatives > 0)
			{
				return true;
			}
		}

		return false;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& plane, const Box<T>& box) noexcept
	{
		for (std::size_t i = 0, positives = 0, negatives = 0; i < Box<T>::CornerCount; ++i)
		{
			const std::int8_t side = plane.Side(box.Corner(i));
			positives += side > std::int8_t{0};
			negatives += side < std::int8_t{0};

			if (positives > 0 && negatives > 0)
			{
				return true;
			}
		}

		return false;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const AABB<T>& left, const AABB<T>& right) noexcept
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
	constexpr bool AreIntersecting(const AABB<T>& left, const Core::Quaternion<T>& leftRotation, const AABB<T>& right, const Core::Quaternion<T>& rightRotation) noexcept
	{
		const std::array<Core::Vector3<T>, 8> leftCorners = left.Corners(leftRotation);
		const std::array<Core::Vector3<T>, 8> rightCorners = right.Corners(rightRotation);
		const std::array<Core::Vector3<T>, 3> leftMainEdges =
		{
			leftCorners[1] - leftCorners[0],
			leftCorners[2] - leftCorners[0],
			leftCorners[4] - leftCorners[0],

		};
		const std::array<Core::Vector3<T>, 3> rightMainEdges =
		{
			rightCorners[1] - rightCorners[0],
			rightCorners[2] - rightCorners[0],
			rightCorners[4] - rightCorners[0]
		};

		return AreIntersecting(leftCorners[0], leftMainEdges, rightCorners) && AreIntersecting(rightCorners[0], rightMainEdges, leftCorners) && 
			AreIntersecting(leftMainEdges, leftCorners, rightMainEdges, rightCorners);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const AABB<T>& aabb, const Ray3D<T>& ray) noexcept
	{
		return AreIntersecting(ray, aabb);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const AABB<T>& aabb, const Core::Quaternion<T>& rotation, const Ray3D<T>& ray) noexcept
	{
		return AreIntersecting(ray, aabb, rotation);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const AABB<T>& aabb, const Plane<T>& plane) noexcept
	{
		return AreIntersecting(plane, aabb);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const AABB<T>& aabb, const Core::Quaternion<T>& rotation, const Plane<T>& plane) noexcept
	{
		return AreIntersecting(plane, aabb, rotation);
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
	constexpr bool AreIntersecting(const Core::Vector3<T>& origin, const Core::Vector3<T>& direction, const AABB<T>& aabb, T tMin, T tMax) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			const T min = aabb.Min(i) - origin[i];
			const T max = aabb.Max(i) - origin[i];
			const T multiplier = T{1} / direction[i];
			const Core::Vector2<T> t = Core::Vector2<T>(min, max) * multiplier;
			const auto& [t0, t1] = t.MinMax();

			tMin = std::max(t0, tMin);
			tMax = std::min(t1, tMax);
		}

		return tMin < tMax;
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

	template<std::floating_point T, std::size_t CornerCount>
	constexpr bool AreIntersecting(const Core::Vector3<T>& origin, const std::span<const Core::Vector3<T>> edges, const std::span<const Core::Vector3<T>, CornerCount> corners) noexcept
	{
		for (const Core::Vector3<T>& edge : edges)
		{
			const T edgeLength = edge.Magnitude();
			const Core::Vector3<T> edgeNormal = edge * (T{1} / edgeLength);
			if (!edgeNormal.IsFinite())
			{
				continue;
			}

			std::array<T, CornerCount> projections;
			for (std::size_t i = 0; i < CornerCount; ++i)
			{
				projections[i] = Core::Dot(edgeNormal, corners[i] - origin);
			}

			const auto [min, max] = std::ranges::minmax_element(projections);
			if (*min >= edgeLength || *max <= T{0})
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T, std::size_t LeftCornerCount, std::size_t RightCornerCount>
	constexpr bool AreIntersecting(const std::span<const Core::Vector3<T>> leftEdges, const std::span<const Core::Vector3<T>, LeftCornerCount> leftCorners, 
		const std::span<const Core::Vector3<T>> rightEdges, const std::span<const Core::Vector3<T>, RightCornerCount> rightCorners) noexcept
	{
		for (const Core::Vector3<T>& leftEdge : leftEdges)
		{
			for (const Core::Vector3<T>& rightEdge : rightEdges)
			{
				const Core::Vector3<T> normal = Core::Cross(leftEdge, rightEdge).Normalized();
				if (!normal.IsFinite())
				{
					continue;
				}

				std::array<float, LeftCornerCount> leftProjections;
				for (std::size_t i = 0; i < LeftCornerCount; ++i)
				{
					leftProjections[i] = Core::Dot(normal, leftCorners[i]);
				}
				std::array<float, RightCornerCount> rightProjections;
				for (std::size_t i = 0; i < RightCornerCount; ++i)
				{
					rightProjections[i] = Core::Dot(normal, rightCorners[i]);
				}

				const auto [leftMin, leftMax] = std::ranges::minmax_element(leftProjections);
				const auto [rightMin, rightMax] = std::ranges::minmax_element(rightProjections);
				if (*leftMin >= *rightMax || *leftMax <= *rightMin)
				{
					return false;
				}
			}
		}

		return true;
	}
}
