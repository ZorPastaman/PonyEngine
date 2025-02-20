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
import :Box;

export namespace PonyMath::Shape
{
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const AABB<T>& small, const AABB<T>& large) noexcept;
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const AABB<T>& small, const Core::Quaternion<T>& smallRotation, const AABB<T>& large, const Core::Quaternion<T>& largeRotation) noexcept;

	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Box<T>& small, const Box<T>& large) noexcept;
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Core::Vector3<T>& min, const Core::Vector3<T>& max, const AABB<T>& large) noexcept;
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Core::Vector3<T>& min, const Core::Vector3<T>& max, const Box<T>& large) noexcept;

	template<Core::Arithmetic T>
	constexpr bool IsInside(const AABB<T>& small, const AABB<T>& large) noexcept
	{
		return IsInside(small.Min(), small.Max(), large);
	}

	template<Core::Arithmetic T>
	constexpr bool IsInside(const AABB<T>& small, const Core::Quaternion<T>& smallRotation, const AABB<T>& large, const Core::Quaternion<T>& largeRotation) noexcept
	{
		const std::array<Core::Vector3<T>, 8> smallCorners = small.Corners(smallRotation);
		const AABB<T> simpleLarge = AABB<T>(Core::Vector3<T>::Predefined::Zero, large.Extents());
		const Core::Quaternion<T> largeConjugate = largeRotation.Conjugate();

		for (const Core::Vector3<T>& smallCorner : smallCorners)
		{
			if (!simpleLarge.Contains(largeConjugate * (smallCorner - large.Center())))
			{
				return false;
			}
		}

		return true;
	}

	template<Core::Arithmetic T>
	constexpr bool IsInside(const Box<T>& small, const Box<T>& large) noexcept
	{
		return IsInside(small.Min(), small.Max(), large);
	}

	template<Core::Arithmetic T>
	constexpr bool IsInside(const Core::Vector3<T>& min, const Core::Vector3<T>& max, const AABB<T>& large) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			if (min[i] < large.Min(i) || max[i] > large.Max(i))
			{
				return false;
			}
		}

		return true;
	}

	template<Core::Arithmetic T>
	constexpr bool IsInside(const Core::Vector3<T>& min, const Core::Vector3<T>& max, const Box<T>& large) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			if (min[i] < large.Min(i) || max[i] > large.Max(i))
			{
				return false;
			}
		}

		return true;
	}
}
