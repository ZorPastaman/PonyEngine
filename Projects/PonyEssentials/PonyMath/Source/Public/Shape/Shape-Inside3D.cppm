/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Inside3D;

import <concepts>;
import <span>;

import PonyMath.Core;

import :AABB;
import :OBB;

export namespace PonyMath::Shape
{
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const AABB<T>& small, const AABB<T>& large) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const AABB<T>& small, const OBB<T>& large) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const OBB<T>& small, const OBB<T>& large) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const OBB<T>& small, const AABB<T>& large) noexcept;
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr bool IsInside(std::span<const Core::Vector3<T>> corners, const OBB<T>& large) noexcept;

	template<Core::Arithmetic T>
	constexpr bool IsInside(const AABB<T>& small, const AABB<T>& large) noexcept
	{
		return large.Contains(small.Min()) && large.Contains(small.Max());
	}

	template<std::floating_point T>
	constexpr bool IsInside(const AABB<T>& small, const OBB<T>& large) noexcept
	{
		return IsInside(small.Corners(), large);
	}

	template<std::floating_point T>
	constexpr bool IsInside(const OBB<T>& small, const OBB<T>& large) noexcept
	{
		return IsInside(small.Corners(), large);
	}

	template<std::floating_point T>
	constexpr bool IsInside(const OBB<T>& small, const AABB<T>& large) noexcept
	{
		std::array<Core::Vector3<T>, 8> corners = small.Corners();
		Core::Vector3<T> min = Core::Min(corners[0], corners[1]);
		Core::Vector3<T> max = Core::Max(corners[0], corners[1]);
		for (std::size_t i = 2; i < corners.size(); ++i)
		{
			min = Core::Min(min, corners[i]);
			max = Core::Max(max, corners[i]);
		}

		return large.Contains(min) && large.Contains(max);
	}

	template<std::floating_point T>
	constexpr bool IsInside(const std::span<const Core::Vector3<T>> corners, const OBB<T>& large) noexcept
	{
		for (const Core::Vector3<T>& corner : corners)
		{
			if (!large.Contains(corner))
			{
				return false;
			}
		}

		return true;
	}
}
