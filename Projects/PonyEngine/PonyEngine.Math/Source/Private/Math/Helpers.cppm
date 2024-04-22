/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Helpers;

import <type_traits>;

export namespace PonyEngine::Math
{
	/// @brief The expression is @a true if @a sizeof(T) is greater than @a sizeof(U); @a false otherwise.
	/// @tparam T Left type.
	/// @tparam U Right type.
	template <typename T, typename U>
	constexpr bool IsGreaterThan = sizeof(T) > sizeof(U);

	/// @brief It's @a double if @a sizeof(T) is greater than @a sizeof(float) and @a float otherwise.
	/// @tparam T Input type.
	template <typename T>
	using FloatingBySize = std::conditional_t<IsGreaterThan<T, float>, double, float>;
}
