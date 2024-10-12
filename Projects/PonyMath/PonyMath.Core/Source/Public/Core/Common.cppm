/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Core:Common;

import <cmath>;
import <concepts>;
import <numbers>;
import <type_traits>;

export namespace PonyMath::Core
{
	/// @brief The concept is satisfied if @p T is an arithmetic type.
	template<typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	/// @brief The expression is @a true if @a sizeof(T) is greater than @a sizeof(U); @a false otherwise.
	/// @tparam T Left type.
	/// @tparam U Right type.
	template<typename T, typename U>
	constexpr bool IsGreaterThan = sizeof(T) > sizeof(U);

	/// @brief It's @a double if @a sizeof(T) is greater than @a sizeof(float) and @a float otherwise.
	/// @tparam T Input type.
	template<typename T>
	using FloatingBySize = std::conditional_t<IsGreaterThan<T, float>, double, float>;

	/// @brief It's @p T if @p T is a floating point type; otherwise the type is chosen by the @p FloatingBySize.
	/// @tparam T Input type.
	template<typename T>
	using ComputationalFor = std::conditional_t<std::is_floating_point_v<T>, T, FloatingBySize<T>>;

	/// @brief Degrees to radians multiplier.
	/// @tparam T Value type.
	template<std::floating_point T>
	constexpr T DegToRad = std::numbers::pi_v<T> / T{180};
	/// @brief Radians to degrees multiplier.
	/// @tparam T Value type.
	template<std::floating_point T>
	constexpr T RadToDeg = T{180} / std::numbers::pi_v<T>;

	/// @brief Checks if the two floating point values are almost equal with the tolerance value.
	/// @tparam T Floating point type.
	/// @param left First value.
	/// @param right Second value.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the values are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(T left, T right, T tolerance = T{0.00001}) noexcept;

	/// @brief Sign function.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return @a 1 if the @p value is positive or zero; @a -1 if the @p value is negative.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Sign(T value) noexcept;
	/// @brief Signum function.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return @a 1 if the @p value is positive, @a -1 if the @p value is negative and 0 if the @p value is 0.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Signum(T value) noexcept;

	/// @brief Rounds the floating point value to an integral value and returns it as an integral value.
	/// @tparam From Input type.
	/// @tparam To Output type.
	/// @param from Input value.
	/// @return Rounded integral.
	template<std::floating_point From, std::integral To> [[nodiscard("Pure function")]]
	constexpr To RoundToIntegral(From from) noexcept;
}

namespace PonyMath::Core
{
	template<std::floating_point T>
	bool AreAlmostEqual(const T left, const T right, const T tolerance) noexcept
	{
		return std::abs(left - right) < tolerance;
	}

	template<Arithmetic T>
	constexpr T Sign(T value) noexcept
	{
		return value < T{0} ? T{-1} : T{1};
	}

	template<Arithmetic T>
	constexpr T Signum(const T value) noexcept
	{
		return static_cast<T>(T{0} < value) - (value < T{0});
	}

	template<std::floating_point From, std::integral To>
	constexpr To RoundToIntegral(const From from) noexcept
	{
		return static_cast<To>(from + From{0.5} - (from < From{0}));
	}
}
