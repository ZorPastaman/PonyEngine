/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Inside;

import PonyMath.Core;

import :Rect;

export namespace PonyMath::Shape
{
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Value type.
	/// @param small Small rect.
	/// @param large Large rect.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Rect<T>& small, const Rect<T>& large) noexcept;
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	constexpr bool IsInside(const Rect<T>& small, const Rect<T>& large) noexcept
	{
		return large.MinX() <= small.MinX() && large.MinY() <= small.MinY() && large.MaxX() >= small.MaxX() && large.MaxY() >= small.MaxY();
	}
}
