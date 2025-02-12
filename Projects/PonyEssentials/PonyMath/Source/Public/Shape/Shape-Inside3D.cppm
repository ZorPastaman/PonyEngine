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
	template<std::floating_point T>
	constexpr bool IsInside(const Segment3D<T>& small, const Box<T>& large) noexcept
	{
		return large.Contains(small.Point0()) && large.Contains(small.Point1());
	}

	template<Core::Arithmetic T>
	constexpr bool IsInside(const Box<T>& small, const Box<T>& large) noexcept
	{
		return large.MinX() <= small.MinX() && large.MinY() <= small.MinY() && large.MinZ() <= small.MinZ() && 
			large.MaxX() >= small.MaxX() && large.MaxY() >= small.MaxY() && large.MaxZ() >= small.MaxZ();
	}
}
