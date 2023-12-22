/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math.VectorConcepts;

import <concepts>;

namespace PonyEngine::Math
{
	template <typename T>
	constexpr bool IsGreaterThanFloat = sizeof(T) > sizeof(float);

	template <typename T>
	using FloatingTypeBySize = std::conditional_t<IsGreaterThanFloat<T>, double, float>;

	export template <typename T>
	using DefaultComputationalType = std::conditional_t<std::floating_point<T>, T, FloatingTypeBySize<T>>;

	template<typename T>
	concept Addable = requires (T x) 
	{ 
		{ x + x } -> std::same_as<T>;
		{ x - x } -> std::same_as<T>;
	};

	template<typename T>
	concept Multipliable = requires (T x)
	{
		{ x * x } -> std::same_as<T>;
		{ x / x } -> std::same_as<T>;
	};

	export template <typename T>
	concept VectorComponent = std::regular<T> && Addable<T>;

	template <typename T, typename U>
	concept BothWaysConvertible = std::convertible_to<T, U> && std::convertible_to<U, T>;

	template <typename T>
	concept ConvertibleToFloating = std::convertible_to<T, float> || std::convertible_to<T, double> ||
		std::convertible_to<T, long double>;

	export template <typename T, typename VectorComponent>
	concept VectorComponentComputational = std::regular<T> && Multipliable<T> && 
		BothWaysConvertible<T, VectorComponent> && ConvertibleToFloating<T>;
}
