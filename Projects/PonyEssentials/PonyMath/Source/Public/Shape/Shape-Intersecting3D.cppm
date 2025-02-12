/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Intersecting3D;

import PonyMath.Core;

import :Box;
import :Frustum;
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
	constexpr bool AreIntersecting(const Line3D<T>& line, const Frustum<T>& frustum) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Plane<T>& plane, const Frustum<T>& frustum) noexcept;
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
	constexpr bool AreIntersecting(const Line3D<T>& line, const Frustum<T>& frustum) noexcept
	{
		for (std::size_t i = 0; i < Frustum<T>::PlaneCount - 1; ++i) // No need to check far plane, its normal is the same as the near plane's
		{
			const Core::Vector3<T> normal = Core::Cross(line.Direction(), frustum.Plane(i).Normal()).Normalized();
			const auto plane = Plane<T>(normal, line.Point());

			if (!AreIntersecting(plane, frustum))
			{
				return false;
			}
		}

		const std::array<Core::Vector3<T>, 8> corners =
		{
			frustum.LeftBottomNear(),
			frustum.RightBottomNear(),
			frustum.LeftTopNear(),
			frustum.RightTopNear(),
			frustum.LeftBottomFar(),
			frustum.RightBottomFar(),
			frustum.LeftTopFar(),
			frustum.RightTopFar()
		};
		const std::array<Core::Vector3<T>, 6> edges = 
		{
			
		};

		return true;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Plane<T>& plane, const Frustum<T>& frustum) noexcept
	{
		const bool side = plane.Side(frustum.Corner(0));

		for (std::size_t i = 1; i < Frustum<T>::CornerCount; ++i)
		{
			if (plane.Side(frustum.Corner(i)) != side)
			{
				return true;
			}
		}

		return false;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Core::Vector3<T>& origin, const Core::Vector3<T>& direction, const Box<T>& box, T tMin, T tMax) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			const T multiplier = T{1} / direction[i];
			const T t0 = (box.Min(i) - origin[i]) * multiplier;
			const T t1 = (box.Max(i) - origin[i]) * multiplier;

			tMin = std::max(tMin, std::min(std::min(t0, t1), tMax));
			tMax = std::min(tMax, std::max(std::max(t0, t1), tMin));
		}

		return tMin < tMax;
	}
}
