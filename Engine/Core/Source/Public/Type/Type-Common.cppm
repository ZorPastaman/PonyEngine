/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Type:Common;

import std;

export namespace PonyEngine::Type
{
	/// @brief The concept is satisfied if @p T is an arithmetic type.
	template<typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;
	/// @brief The concept is satisfied if @p T is a signed type.
	template<typename T>
	concept Signed = std::is_signed_v<T>;
	/// @brief The concept is satisfied if @p T is an unsigned type.
	template<typename T>
	concept Unsigned = std::is_unsigned_v<T>;

	/// @brief The expression is @a true if @a sizeof(T) is greater than @a sizeof(U); @a false otherwise.
	/// @tparam T Left type.
	/// @tparam U Right type.
	template<typename T, typename U>
	constexpr bool IsGreater = sizeof(T) > sizeof(U);
	/// @brief The expression is @a true if @a sizeof(T) is less than @a sizeof(U); @a false otherwise.
	/// @tparam T Left type.
	/// @tparam U Right type.
	template<typename T, typename U>
	constexpr bool IsLess = sizeof(T) < sizeof(U);
	/// @brief The expression is @a true if @a sizeof(T) is equal @a sizeof(U); @a false otherwise.
	/// @tparam T Left type.
	/// @tparam U Right type.
	template<typename T, typename U>
	constexpr bool IsEqual = sizeof(T) == sizeof(U);

	/// @brief It's @a double if @a sizeof(T) is greater than @a sizeof(float) and @a float otherwise.
	/// @tparam T Input type.
	template<typename T>
	using FloatingBySize = std::conditional_t<IsGreater<T, double>, long double, std::conditional_t<IsGreater<T, float>, double, float>>;
}
