/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Common;

import std;

import PonyEngine.Type;

export namespace PonyEngine::Math
{
	/// @brief Tolerance.
	/// @tparam T Value type.
	template<std::floating_point T>
	struct Tolerance final
	{
		T relative = T{0.00001}; ///< Relative tolerance. Must be positive.
		T absolute = T{0.00000001}; ///< Absolute tolerance. Must be positive.

		/// @brief Casts the tolerance to a tolerance of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Tolerance<U>() const noexcept;
	};

	/// @brief Value range.
	/// @tparam T Value type.
	template<Type::Arithmetic T>
	struct Range final
	{
		T min = T{0}; ///< Minimal value.
		T max = std::numeric_limits<T>::max(); ///< Maximal value.

		/// @brief Casts the range to a range of another type.
		/// @tparam U Target type.
		template<Type::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Range<U>() const noexcept;
	};

	/// @brief Degrees to radians multiplier.
	/// @tparam T Value type.
	template<std::floating_point T>
	constexpr T DegToRad = std::numbers::pi_v<T> / T{180};
	/// @brief Radians to degrees multiplier.
	/// @tparam T Value type.
	template<std::floating_point T>
	constexpr T RadToDeg = T{180} / std::numbers::pi_v<T>;

	/// @brief Gets a floating point type based on the size of the integral type.
	/// @tparam T Integral type.
	template<std::integral T>
	using FloatingFor = std::conditional_t<(sizeof(T) < 4), float, std::conditional_t<(sizeof(T) > 4), long double, double>>;

	/// @brief Checks if the two floating point values are almost equal with the tolerance value.
	/// @tparam T Floating point type.
	/// @param lhs First value.
	/// @param rhs Second value.
	/// @param tolerance Tolerance.
	/// @return @a True if the values are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(T lhs, T rhs, const Tolerance<T>& tolerance = Tolerance<T>{}) noexcept;

	/// @brief Sign function.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return @a 1 if the @p value is positive or zero; @a -1 if the @p value is negative.
	template<Type::Signed T> [[nodiscard("Pure function")]]
	constexpr T Sign(T value) noexcept;
	/// @brief Sign function that returns output as a value of another type.
	/// @tparam To Output type.
	/// @tparam From Value type.
	/// @param value Input.
	/// @return @a 1 if the @p value is positive or zero; @a -1 if the @p value is negative.
	template<Type::Signed To, Type::Signed From> [[nodiscard("Pure function")]]
	constexpr To Sign(From value) noexcept;
	/// @brief Sign function that transforms a @p bool to a value.
	/// @tparam T Output type.
	/// @param value Input.
	/// @return @a 1 if the @p value is @a true; @a -1 if the @p value is @a false.
	template<Type::Signed T> [[nodiscard("Pure function")]]
	constexpr T Sign(bool value) noexcept;
	/// @brief Signum function.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return @a 1 if the @p value is positive, @a -1 if the @p value is negative and 0 if the @p value is 0.
	template<Type::Signed T> [[nodiscard("Pure function")]]
	constexpr T Signum(T value) noexcept;
	/// @brief Signum function that returns output as a value of another type.
	/// @tparam To Output type.
	/// @tparam From Input type.
	/// @param value Input.
	/// @return @a 1 if the @p value is positive, @a -1 if the @p value is negative and 0 if the @p value is 0.
	template<Type::Signed To, Type::Signed From> [[nodiscard("Pure function")]]
	constexpr To Signum(From value) noexcept;

	/// @brief Rounds the floating point value to an integral value and returns it as an integral value.
	/// @tparam From Input type.
	/// @tparam To Output type.
	/// @param from Input value.
	/// @return Rounded integral.
	template<std::unsigned_integral To, std::floating_point From> [[nodiscard("Pure function")]]
	constexpr To RoundToIntegral(From from) noexcept;
	/// @brief Rounds the floating point value to an integral value and returns it as an integral value.
	/// @tparam From Input type.
	/// @tparam To Output type.
	/// @param from Input value.
	/// @return Rounded integral.
	template<std::signed_integral To, std::floating_point From> [[nodiscard("Pure function")]]
	constexpr To RoundToIntegral(From from) noexcept;

	/// @brief Converts the normalized floating point value to a unorm value.
	/// @tparam To Target unorm type.
	/// @tparam From Source floating point type.
	/// @param from Floating point value. Clamped to [0, 1] automatically.
	/// @param range Value range.
	/// @return Unorm value.
	template<std::unsigned_integral To, std::floating_point From> [[nodiscard("Pure function")]]
	constexpr To NormalizedToUnorm(From from, const Range<To>& range = Range<To>{}) noexcept;
	/// @brief Converts the unorm value to a unorm value of another type.
	/// @tparam To Target unorm type.
	/// @tparam From Source unorm type.
	/// @param from Unorm value.
	/// @param fromRange Range of the input value.
	/// @param toRange Range of the output value.
	/// @return Unorm value.
	template<std::unsigned_integral To, std::unsigned_integral From> [[nodiscard("Pure function")]]
	constexpr To UnormToUnorm(From from, const Range<From>& fromRange = Range<From>{}, const Range<To>& toRange = Range<To>{}) noexcept;
	/// @brief Converts the normalized floating point value to a snorm value.
	/// @tparam To Target snorm type.
	/// @tparam From Source floating point type.
	/// @param from Floating point value. Clamped to [-1, 1] automatically.
	/// @param range Value range. Both min and max must be non-negative.
	/// @return Snorm value.
	/// @remark Snorm min value and snorm min value + 1 are treated the same.
	template<std::signed_integral To, std::floating_point From> [[nodiscard("Pure function")]]
	constexpr To NormalizedToSnorm(From from, const Range<To>& range = Range<To>{}) noexcept;
	/// @brief Converts the snorm value to a snorm value of another type.
	/// @tparam To Target snorm type.
	/// @tparam From Source snorm type.
	/// @param from Snorm value.
	/// @param fromRange Range of the input value. Both min and max must be non-negative.
	/// @param toRange Range of the output value. Both min and max must be non-negative.
	/// @return Snorm value.
	/// @remark Snorm min value and snorm min value + 1 are treated the same.
	template<std::signed_integral To, std::signed_integral From> [[nodiscard("Pure function")]]
	constexpr To SnormToSnorm(From from, const Range<From>& fromRange = Range<From>{}, const Range<To>& toRange = Range<To>{}) noexcept;
	/// @brief Converts the unorm value to a normalized floating point value.
	/// @tparam To Target floating point type.
	/// @tparam From Source unorm type.
	/// @param from Unorm value.
	/// @param range Value range.
	/// @return Floating point value.
	template<std::floating_point To, std::unsigned_integral From> [[nodiscard("Pure function")]]
	constexpr To UnormToNormalized(From from, const Range<From>& range = Range<From>{}) noexcept;
	/// @brief Converts the snorm value to a normalized floating point value.
	/// @tparam To Target floating point type.
	/// @tparam From Source snorm type.
	/// @param from Snorm value.
	/// @param range Value range. Both min and max must be non-negative.
	/// @return Floating point value.
	/// @remark Snorm min value and snorm min value + 1 are treated the same.
	template<std::floating_point To, std::signed_integral From> [[nodiscard("Pure function")]]
	constexpr To SnormToNormalized(From from, const Range<From>& range = Range<From>{}) noexcept;

	/// @brief Sums the values and clamps the result to the max value.
	/// @tparam T Value type.
	/// @param lhs Left value.
	/// @param rhs Right value.
	/// @return Sum.
	template<std::unsigned_integral T> [[nodiscard("Pure function")]]
	constexpr T SumClamp(T lhs, T rhs) noexcept;
	/// @brief Subtracts the @p rhs from the @p lhs and clamps the result to zero.
	/// @tparam T Value type.
	/// @param lhs Left value.
	/// @param rhs Right value.
	/// @return Difference.
	template<std::unsigned_integral T> [[nodiscard("Pure function")]]
	constexpr T DifferenceClamp(T lhs, T rhs) noexcept;

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

	/// @brief Computes an absolute value.
	/// @remark In non-constexpr context it just calls std::abs.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return Absolute value.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Abs(T value) noexcept;

	/// @brief Computes a factorial.
	/// @tparam T Value type.
	/// @param n Number of iterations.
	/// @return Factorial of @p n.
	template<std::unsigned_integral T>
	constexpr T Factorial(T n) noexcept;

	/// @brief Checks if the @p value is infinite.
	/// @remark In non-constexpr context it just calls std::isinf.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return @a True if the value is infinite; @a false otherwise.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsInf(T value) noexcept;
	/// @brief Checks if the @p value is nan.
	/// @remark In non-constexpr context it just calls std::isnan.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return @a True if the value is nan; @a false otherwise.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsNan(T value) noexcept;
	/// @brief Checks if the @p value is normal.
	/// @remark In non-constexpr context it just calls std::isnormal.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return @a True if the value is normal; @a false otherwise.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsNormal(T value) noexcept;
	/// @brief Checks if the @p value is finite.
	/// @remark In non-constexpr context it just calls std::isfinite.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return @a True if the value is finite; @a false otherwise.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool IsFinite(T value) noexcept;

	/// @brief Checks if the @p value is even.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return @a True if the value is even; @a false otherwise.
	template<std::integral T> [[nodiscard("Pure function")]]
	constexpr bool IsEven(T value) noexcept;
	/// @brief Checks if the @p value is odd.
	/// @tparam T Value type.
	/// @param value Input.
	/// @return @a True if the value is odd; @a false otherwise.
	template<std::integral T> [[nodiscard("Pure function")]]
	constexpr bool IsOdd(T value) noexcept;
}

namespace PonyEngine::Math
{
	template<std::floating_point T>
	template<std::floating_point U>
	constexpr Tolerance<T>::operator Tolerance<U>() const noexcept
	{
		return Tolerance<U>{.relative = static_cast<U>(relative), .absolute = static_cast<U>(absolute)};
	}


	template<Type::Arithmetic T>
	template<Type::Arithmetic U>
	constexpr Range<T>::operator Range<U>() const noexcept
	{
		return Range<U>{.min = static_cast<U>(min), .max = static_cast<U>(max)};
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const T lhs, const T rhs, const Tolerance<T>& tolerance) noexcept
	{
		return Abs(lhs - rhs) <= std::max(std::max(Abs(lhs), Abs(rhs)) * tolerance.relative, tolerance.absolute);
	}

	template<Type::Signed T>
	constexpr T Sign(const T value) noexcept
	{
		return value < T{0} ? T{-1} : T{1};
	}

	template<Type::Signed To, Type::Signed From>
	constexpr To Sign(const From value) noexcept
	{
		return value < From{0} ? To{-1} : To{1};
	}

	template<Type::Signed T>
	constexpr T Sign(const bool value) noexcept
	{
		return value ? T{1} : T{-1};
	}

	template<Type::Signed T>
	constexpr T Signum(const T value) noexcept
	{
		return static_cast<T>((T{0} < value) - (value < T{0}));
	}

	template<Type::Signed To, Type::Signed From>
	constexpr To Signum(const From value) noexcept
	{
		return static_cast<To>((From{0} < value) - (value < From{0}));
	}

	template <std::unsigned_integral To, std::floating_point From>
	constexpr To RoundToIntegral(const From from) noexcept
	{
		return static_cast<To>(from + From{0.5});
	}

	template<std::signed_integral To, std::floating_point From>
	constexpr To RoundToIntegral(const From from) noexcept
	{
		return static_cast<To>(from + From{0.5} - (from < From{0}));
	}

	template<std::unsigned_integral To, std::floating_point From>
	constexpr To NormalizedToUnorm(const From from, const Range<To>& range) noexcept
	{
		using FloatingUnorm = FloatingFor<To>;
		using Floating = std::conditional_t<sizeof(FloatingUnorm) < sizeof(From), From, FloatingUnorm>;

		const Floating fromValue = static_cast<Floating>(std::clamp(from, From{0}, From{1}));
		const To max = range.max - range.min;
		return range.min + RoundToIntegral<To>(fromValue * max);
	}

	template<std::unsigned_integral To, std::unsigned_integral From>
	constexpr To UnormToUnorm(const From from, const Range<From>& fromRange, const Range<To>& toRange) noexcept
	{
		if constexpr (std::is_same_v<To, From>)
		{
			return from;
		}
		else
		{
			using FromFloating = FloatingFor<From>;
			using ToFloating = FloatingFor<To>;
			using Floating = std::conditional_t<sizeof(FromFloating) < sizeof(ToFloating), ToFloating, FromFloating>;

			return NormalizedToUnorm<To>(UnormToNormalized<Floating>(from, fromRange), toRange);
		}
	}

	template<std::signed_integral To, std::floating_point From>
	constexpr To NormalizedToSnorm(const From from, const Range<To>& range) noexcept
	{
		using ToUnorm = std::make_unsigned_t<To>;

		const To toValue = NormalizedToUnorm<ToUnorm>(Abs(from), static_cast<Range<ToUnorm>>(range));
		return from < From{0} ? -toValue : toValue;
	}

	template<std::signed_integral To, std::signed_integral From>
	constexpr To SnormToSnorm(const From from, const Range<From>& fromRange, const Range<To>& toRange) noexcept
	{
		if constexpr (std::is_same_v<To, From>)
		{
			return from;
		}
		else
		{
			using FromFloating = FloatingFor<From>;
			using ToFloating = FloatingFor<To>;
			using Floating = std::conditional_t<sizeof(FromFloating) < sizeof(ToFloating), ToFloating, FromFloating>;

			return NormalizedToSnorm<To>(SnormToNormalized<Floating>(from, fromRange), toRange);
		}
	}

	template<std::floating_point To, std::unsigned_integral From>
	constexpr To UnormToNormalized(const From from, const Range<From>& range) noexcept
	{
		using FloatingUnorm = FloatingFor<From>;
		using Floating = std::conditional_t<sizeof(FloatingUnorm) < sizeof(To), To, FloatingUnorm>;

		const From numerator = DifferenceClamp(from, range.min);
		const From denominator = range.max - range.min;
		const Floating toValue = static_cast<Floating>(numerator) / denominator;
		return std::clamp(static_cast<To>(toValue), To{0}, To{1});
	}

	template<std::floating_point To, std::signed_integral From>
	constexpr To SnormToNormalized(const From from, const Range<From>& range) noexcept
	{
		using FromUnorm = std::make_unsigned_t<From>;

		const From fromAbs = Abs(std::max(from, static_cast<From>(-std::numeric_limits<From>::max())));
		const To toValue = UnormToNormalized<To>(static_cast<FromUnorm>(fromAbs), static_cast<Range<FromUnorm>>(range));
		return from < From{0} ? -toValue : toValue;
	}

	template<std::unsigned_integral T>
	constexpr T SumClamp(const T lhs, const T rhs) noexcept
	{
		const T result = lhs + rhs;
		return result < lhs ? std::numeric_limits<T>::max() : result;
	}

	template<std::unsigned_integral T>
	constexpr T DifferenceClamp(const T lhs, const T rhs) noexcept
	{
		return lhs < rhs ? T{0} : lhs - rhs;
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

	template<Type::Arithmetic T>
	constexpr T Abs(const T value) noexcept
	{
		if constexpr (std::is_unsigned_v<T>)
		{
			return value;
		}
		else
		{
			if consteval
			{
				return value < T{0} ? -value : value;
			}
			else
			{
				return std::abs(value);
			}
		}
	}

	template<std::unsigned_integral T>
	constexpr T Factorial(const T n) noexcept
	{
		T answer = T{1};
		for (T i = T{1}; i <= n; ++i)
		{
			answer *= i;
		}

		return answer;
	}

	template<Type::Arithmetic T>
	constexpr bool IsInf(const T value) noexcept
	{
		if consteval
		{
			if (std::is_integral_v<T>)
			{
				return IsInf(static_cast<double>(value));
			}

			return Abs(value) == std::numeric_limits<T>::infinity();
		}
		else
		{
			return std::isinf(value);
		}
	}

	template<Type::Arithmetic T>
	constexpr bool IsNan(const T value) noexcept
	{
		if consteval
		{
			if (std::is_integral_v<T>)
			{
				return IsNan(static_cast<double>(value));
			}

			return value != value;
		}
		else
		{
			return std::isnan(value);
		}
	}

	template<Type::Arithmetic T>
	constexpr bool IsNormal(const T value) noexcept
	{
		if consteval
		{
			if (std::is_integral_v<T>)
			{
				return IsNormal(static_cast<double>(value));
			}

			return !IsInf(value) && !IsNan(value) && value != T{0} && Abs(value) >= std::numeric_limits<T>::min();
		}
		else
		{
			return std::isnormal(value);
		}
	}

	template<Type::Arithmetic T>
	constexpr bool IsFinite(const T value) noexcept
	{
		if consteval
		{
			if (std::is_integral_v<T>)
			{
				return IsFinite(static_cast<double>(value));
			}

			return !IsInf(value) && !IsNan(value);
		}
		else
		{
			return std::isfinite(value);
		}
	}

	template<std::integral T>
	constexpr bool IsEven(const T value) noexcept
	{
		return !IsOdd(value);
	}

	template<std::integral T>
	constexpr bool IsOdd(const T value) noexcept
	{
		return value & T{1};
	}
}
