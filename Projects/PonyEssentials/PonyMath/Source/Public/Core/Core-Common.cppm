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
	/// @brief The concept is satisfied if @p T is a signed type.
	template<typename T>
	concept Signed = std::is_signed_v<T>;

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
	template<Signed T> [[nodiscard("Pure function")]]
	constexpr T Sign(T value) noexcept;
	/// @brief Sign function that transforms a @p bool to a value.
	/// @tparam T Output type.
	/// @param value Input.
	/// @return @a 1 if the @p value is @a true; @a -1 if the @p value is @a false.
	template<Signed T> [[nodiscard("Pure function")]]
	constexpr T Sign(bool value) noexcept;
	/// @brief Signum function.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return @a 1 if the @p value is positive, @a -1 if the @p value is negative and 0 if the @p value is 0.
	template<Signed T> [[nodiscard("Pure function")]]
	constexpr T Signum(T value) noexcept;
	/// @brief Signum function that returns output as a value of another type.
	/// @tparam U Output type.
	/// @tparam T Input type.
	/// @param value Input.
	/// @return @a 1 if the @p value is positive, @a -1 if the @p value is negative and 0 if the @p value is 0.
	template<Signed U, Signed T> [[nodiscard("Pure function")]]
	constexpr U Signum(T value) noexcept;

	/// @brief Rounds the floating point value to an integral value and returns it as an integral value.
	/// @tparam From Input type.
	/// @tparam To Output type.
	/// @param from Input value.
	/// @return Rounded integral.
	template<std::floating_point From, std::unsigned_integral To> [[nodiscard("Pure function")]]
	constexpr To RoundToIntegral(From from) noexcept; // TODO: Add tests
	/// @brief Rounds the floating point value to an integral value and returns it as an integral value.
	/// @tparam From Input type.
	/// @tparam To Output type.
	/// @param from Input value.
	/// @return Rounded integral.
	template<std::floating_point From, std::signed_integral To> [[nodiscard("Pure function")]]
	constexpr To RoundToIntegral(From from) noexcept;

	/// @brief Divides the @p numerator by the @p denominator and ceils the result.
	/// @tparam T Value type.
	/// @param numerator Numerator.
	/// @param denominator Denominator. Must be greater than @a 0.
	/// @return Divided and ceiled value.
	template<std::unsigned_integral T> [[nodiscard("Pure function")]]
	constexpr T DivideCeil(T numerator, T denominator) noexcept;
	/// @brief Computes an aligned value.
	/// @tparam T Value type.
	/// @param value Input value.
	/// @param alignment Alignment. Must be a power of 2.
	/// @return Aligned value.
	template<std::unsigned_integral T> [[nodiscard("Pure function")]]
	constexpr T Align(T value, T alignment) noexcept;
}

namespace PonyMath::Core
{
	template<std::floating_point T>
	bool AreAlmostEqual(const T left, const T right, const T tolerance) noexcept
	{
		return std::abs(left - right) <= tolerance;
	}

	template<Signed T>
	constexpr T Sign(const T value) noexcept
	{
		return value < T{0} ? T{-1} : T{1};
	}

	template<Signed T>
	constexpr T Sign(const bool value) noexcept
	{
		return value ? T{1} : T{-1};
	}

	template<Signed T>
	constexpr T Signum(const T value) noexcept
	{
		return static_cast<T>(T{0} < value) - (value < T{0});
	}

	template<Signed U, Signed T>
	constexpr U Signum(const T value) noexcept
	{
		return static_cast<U>(T{0} < value) - (value < T{0});
	}

	template <std::floating_point From, std::unsigned_integral To>
	constexpr To RoundToIntegral(const From from) noexcept
	{
		return static_cast<To>(from + From{0.5});
	}

	template<std::floating_point From, std::signed_integral To>
	constexpr To RoundToIntegral(const From from) noexcept
	{
		return static_cast<To>(from + From{0.5} - (from < From{0}));
	}

	template<std::unsigned_integral T>
	constexpr T DivideCeil(const T numerator, const T denominator) noexcept
	{
		return (numerator + denominator - T{1}) / denominator;
	}

	template<std::unsigned_integral T>
	constexpr T Align(const T value, const T alignment) noexcept
	{
		const T alignmentValue = alignment - T{1};

		return value + alignmentValue & ~alignmentValue;
	}
}
