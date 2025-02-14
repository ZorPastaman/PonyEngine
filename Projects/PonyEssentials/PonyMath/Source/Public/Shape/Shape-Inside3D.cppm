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

import :Box;
import :Segment3D;

export namespace PonyMath::Shape
{
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Segment3D<T>& small, const Box<T>& large) noexcept;

	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Box<T>& small, const Box<T>& large) noexcept;
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Core::Vector3<T>& min, const Core::Vector3<T>& max, const Box<T>& large) noexcept;

	template<std::floating_point T>
	constexpr bool IsInside(const Segment3D<T>& small, const Box<T>& large) noexcept
	{
		const Core::Vector3<T> min = Core::Min(small.Point0(), small.Point1());
		const Core::Vector3<T> max = Core::Max(small.Point0(), small.Point1());

		return IsInside(min, max, large);
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
