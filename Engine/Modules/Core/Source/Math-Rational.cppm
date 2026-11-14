/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Rational;

import std;

export namespace PonyEngine::Math
{
	/// @brief Rational.
	/// @tparam T Numerator type.
	/// @tparam U Denominator type.
	template<std::integral T, std::integral U = T>
	class Rational final
	{
	public:
		/// @brief Creates a rational where both numerator and denominator are zero.
		[[nodiscard("Pure constructor")]]
		constexpr Rational() noexcept;
		/// @brief Creates a rational.
		/// @param numerator Numerator.
		/// @param denominator Denominator.
		[[nodiscard("Pure constructor")]]
		constexpr Rational(T numerator, U denominator) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Rational(const Rational& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Rational(Rational&& other) noexcept = default;

		constexpr ~Rational() noexcept = default;

		/// @brief Gets the numerator.
		/// @return Numerator.
		[[nodiscard("Pure function")]]
		constexpr T& Numerator() noexcept;
		/// @brief Gets the numerator.
		/// @return Numerator.
		[[nodiscard("Pure function")]]
		constexpr const T& Numerator() const noexcept;
		/// @brief Gets the denominator.
		/// @return Denominator.
		[[nodiscard("Pure function")]]
		constexpr U& Denominator() noexcept;
		/// @brief Gets the denominator.
		/// @return Denominator.
		[[nodiscard("Pure function")]]
		constexpr const U& Denominator() const noexcept;

		/// @brief Checks if the rational is finite.
		/// @return @a True if it's finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsFinite() const noexcept;

		/// @brief Converts the rational to a floating point value.
		/// @tparam F Floating point type.
		/// @return Floating point value.
		template<std::floating_point F = double> [[nodiscard("Pure function")]]
		constexpr F AsFloat() const noexcept;

		/// @brief Casts the rational to another rational.
		/// @tparam T1 Target numerator type.
		/// @tparam U1 Target denominator type.
		template<std::integral T1, std::integral U1 = T1> [[nodiscard("Pure operator")]]
		explicit constexpr operator Rational<T1, U1>() const noexcept;

		constexpr Rational& operator =(const Rational& other) noexcept = default;
		constexpr Rational& operator =(Rational&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Rational& other) const noexcept = default;

	private:
		T numerator; ///< Numerator.
		U denominator; ///< Denominator.
	};
}

namespace PonyEngine::Math
{
	template<std::integral T, std::integral U>
	constexpr Rational<T, U>::Rational() noexcept :
		numerator{0},
		denominator{0}
	{
	}

	template<std::integral T, std::integral U>
	constexpr Rational<T, U>::Rational(const T numerator, const U denominator) noexcept :
		numerator{numerator},
		denominator{denominator}
	{
	}

	template<std::integral T, std::integral U>
	constexpr T& Rational<T, U>::Numerator() noexcept
	{
		return numerator;
	}

	template<std::integral T, std::integral U>
	constexpr const T& Rational<T, U>::Numerator() const noexcept
	{
		return numerator;
	}

	template<std::integral T, std::integral U>
	constexpr U& Rational<T, U>::Denominator() noexcept
	{
		return denominator;
	}

	template<std::integral T, std::integral U>
	constexpr const U& Rational<T, U>::Denominator() const noexcept
	{
		return denominator;
	}

	template<std::integral T, std::integral U>
	constexpr bool Rational<T, U>::IsFinite() const noexcept
	{
		return denominator != U{0};
	}

	template<std::integral T, std::integral U>
	template<std::floating_point F>
	constexpr F Rational<T, U>::AsFloat() const noexcept
	{
		return static_cast<F>(numerator) / static_cast<F>(denominator);
	}

	template<std::integral T, std::integral U>
	template<std::integral T1, std::integral U1>
	constexpr Rational<T, U>::operator Rational<T1, U1>() const noexcept
	{
		return Rational<T1, U1>(static_cast<T1>(numerator), static_cast<U1>(denominator));
	}
}
