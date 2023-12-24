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
	template<typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	export constexpr inline const float DegToRad = std::numbers::pi_v<float> / 180.f;
	export constexpr inline const float RadToDeg = 180.f / std::numbers::pi_v<float>;

	export template<Arithmetic T>
	constexpr T Sign(const T value) noexcept
	{
		return (T{} < value) - (value < T{});
	}
}
