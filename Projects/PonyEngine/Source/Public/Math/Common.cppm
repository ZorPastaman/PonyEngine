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

	export constexpr inline const float DegToRad = std::numbers::pi_v<float> / 180.f;
	export constexpr inline const float RadToDeg = 180.f / std::numbers::pi_v<float>;

	export template<Arithmetic T>
	constexpr T Sign(const T value) noexcept
	{
		return (T{} < value) - (value < T{});
	}
}
