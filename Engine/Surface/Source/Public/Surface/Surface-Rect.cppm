/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Surface:Rect;

import PonyEngine.Math;
import PonyEngine.Type;

export namespace PonyEngine::Surface
{
	/// @brief Rectangle.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	struct Rect final
	{
		Math::Vector2<T> position; ///< Position.
		Math::Vector2<T> size; ///< Size.

		template<Type::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Rect<U>() const noexcept;
	};
}

namespace PonyEngine::Surface
{
	template<Type::Arithmetic T>
	template<Type::Arithmetic U>
	constexpr Rect<T>::operator Rect<U>() const noexcept
	{
		return Rect<U>{.position = static_cast<Math::Vector2<U>>(position), .size = static_cast<Math::Vector2<U>>(size)};
	}
}
