/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math.Common;

import <numbers>;
import <type_traits>;
import <concepts>;

namespace PonyEngine::Math
{
	export template<typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	template <typename T, typename U>
	constexpr bool IsGreaterThan = sizeof(T) > sizeof(U);

	export template <typename T>
	using FloatingBySize = std::conditional_t<IsGreaterThan<T, float>, double, float>;

	export template <typename T>
	using ComputationalFor = std::conditional_t<std::floating_point<T>, T, FloatingBySize<T>>;

	export template<std::floating_point T> 
	constexpr inline const T DegToRad = std::numbers::pi_v<T> / T(180);
	export template<std::floating_point T> 
	constexpr inline const T RadToDeg = T(180) / std::numbers::pi_v<T>;

	export template<Arithmetic T>
	constexpr T Sign(const T value) noexcept
	{
		return static_cast<T>(T{} < value) - (value < T{});
	}

	export template<std::floating_point From, std::integral To>
	constexpr To RoundToIntegral(const From from) noexcept
	{
		return static_cast<To>(from + From(0.5) - (from < From(0)));
	}

	export template<Arithmetic From, Arithmetic To>
	constexpr inline To RoundToIntegralIfPossible(const From from) noexcept
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
