/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Intersecting2D;

import PonyMath.Core;

import :Rect;

export namespace PonyMath::Shape
{
	/// @brief Checks if two rects are intersecting.
	/// @tparam T Value type.
	/// @param left Left rect.
	/// @param right Right rect.
	/// @return @a True if they intersect; @a false otherwise.
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Rect<T>& left, const Rect<T>& right) noexcept;
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	constexpr bool AreIntersecting(const Rect<T>& left, const Rect<T>& right) noexcept
	{
		return !(left.MinX() > right.MaxX() || left.MaxX() < right.MinX() || left.MinY() > right.MaxY() || left.MaxY() < right.MinY());
	}
}
