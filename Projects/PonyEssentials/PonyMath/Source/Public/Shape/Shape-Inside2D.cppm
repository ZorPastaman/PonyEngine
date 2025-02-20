/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Inside2D;

import <concepts>;

import PonyMath.Core;

import :AABR;
import :OBR;

export namespace PonyMath::Shape
{
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const AABR<T>& small, const AABR<T>& large) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const AABR<T>& small, const OBR<T>& large) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const OBR<T>& small, const OBR<T>& large) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const OBR<T>& small, const AABR<T>& large) noexcept;
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr bool IsInside(std::span<const Core::Vector2<T>> corners, const OBR<T>& large) noexcept;

	template<Core::Arithmetic T>
	constexpr bool IsInside(const AABR<T>& small, const AABR<T>& large) noexcept
	{
		return large.Contains(small.Min()) && large.Contains(small.Max());
	}

	template<std::floating_point T>
	constexpr bool IsInside(const AABR<T>& small, const OBR<T>& large) noexcept
	{
		return IsInside(small.Corners(), large);
	}

	template<std::floating_point T>
	constexpr bool IsInside(const OBR<T>& small, const OBR<T>& large) noexcept
	{
		return IsInside(small.Corners(), large);
	}

	template<std::floating_point T>
	constexpr bool IsInside(const OBR<T>& small, const AABR<T>& large) noexcept
	{
		const std::array<Core::Vector2<T>, 4> corners = small.Corners();
		const Core::Vector2<T> min = Core::Min(corners[0], Core::Min(corners[1], Core::Min(corners[2], corners[3])));
		const Core::Vector2<T> max = Core::Max(corners[0], Core::Max(corners[1], Core::Max(corners[2], corners[3])));

		return large.Contains(min) && large.Contains(max);
	}

	template<std::floating_point T>
	constexpr bool IsInside(std::span<const Core::Vector2<T>> corners, const OBR<T>& large) noexcept
	{
		for (const Core::Vector2<T>& corner : corners)
		{
			if (!large.Contains(corner))
			{
				return false;
			}
		}

		return true;
	}
}
