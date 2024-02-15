/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math.Common;

import <cmath>;
import <concepts>;
import <numbers>;
import <type_traits>;

namespace PonyEngine::Math
{
	/// @brief The concept is satisfied if @p T is an arithmetic type.
	export template<typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	/// @brief The expression is @p true if @p sizeof(T) is greater than @p sizeof(U).
	/// @tparam T Left type.
	/// @tparam U Right type.
	template <typename T, typename U>
	constexpr bool IsGreaterThan = sizeof(T) > sizeof(U);

	/// @brief It's @p double if @p sizeof(T) is greater than @p sizeof(float) and @p float otherwise.
	/// @tparam T Input type.
	export template <typename T>
	using FloatingBySize = std::conditional_t<IsGreaterThan<T, float>, double, float>;

	/// @brief It's @p T if @p T is a floating point type; otherwise the type is chosen by @ref FloatingBySize.
	/// @tparam T Input type.
	export template <typename T>
	using ComputationalFor = std::conditional_t<std::is_floating_point_v<T>, T, FloatingBySize<T>>;

	/// @brief Degrees to radians multiplier.
	/// @tparam T Value type.
	export template<std::floating_point T>
	constexpr inline const T DegToRad = std::numbers::pi_v<T> / T{180};
	/// @brief Radians to degrees multiplier.
	/// @tparam T Value type.
	export template<std::floating_point T>
	constexpr inline const T RadToDeg = T{180} / std::numbers::pi_v<T>;

	/// @brief Checks if two floating point values are almost equal with a tolerance value.
	/// @tparam T Floating point type.
	/// @param left First value.
	/// @param right Second value.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the values are almost equal; @a false otherwise.
	export template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr inline bool AreAlmostEqual(const T left, const T right, const T tolerance = T{0.00001}) noexcept;

	/// @brief Signum function.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return @p 1 if @p value is positive, @p -1 if @p value is negative and @p 0 if @p value is @p 0.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Signum(const T value) noexcept;

	/// @brief Rounds a floating point value to an integral value and returns it as an integral value.
	/// @tparam From Input type.
	/// @tparam To Output type.
	/// @param from Input value.
	/// @return Rounded integral.
	export template<std::floating_point From, std::integral To> [[nodiscard("Pure function")]]
	constexpr To RoundToIntegral(const From from) noexcept;
	/// @brief Calls @ref RoundToIntegral if @p From is a floating point type and @p To is an integral type;
	///        otherwise it just does @p static_cast<To>(from).
	/// @tparam From From type.
	/// @tparam To To type.
	/// @param from from value.
	/// @return Rounded or cast value.
	export template<Arithmetic From, Arithmetic To> [[nodiscard("Pure function")]]
	constexpr inline To RoundToIntegralIfPossible(const From from) noexcept;

	template<std::floating_point T>
	constexpr inline bool AreAlmostEqual(const T left, const T right, const T tolerance) noexcept
	{
		return std::abs(left - right) < tolerance;
	}

	template<Arithmetic T>
	constexpr T Signum(const T value) noexcept
	{
		return static_cast<T>(T{} < value) - (value < T{});
	}

	template<std::floating_point From, std::integral To>
	constexpr To RoundToIntegral(const From from) noexcept
	{
		return static_cast<To>(from + From{ 0.5 } - (from < From{ 0 }));
	}

	template<Arithmetic From, Arithmetic To>
	constexpr To RoundToIntegralIfPossible(const From from) noexcept
	{
		if constexpr (std::is_floating_point_v<From> && std::is_integral_v<To>)
		{
			return RoundToIntegral<From, To>(from);
		}
		else
		{
			return static_cast<To>(from);
		}
	}
}
