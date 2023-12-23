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
	template<typename T>
	concept Operatable = requires (T x) 
	{
		{ -x } -> std::convertible_to<T>;
		{ x + x } -> std::convertible_to<T>;
		{ x - x } -> std::convertible_to<T>;
		{ x == x } -> std::convertible_to<bool>;
		{ x != x } -> std::convertible_to<bool>;
	};

	template <typename T, typename U>
	concept BothWaysConvertible = std::convertible_to<T, U> && std::convertible_to<U, T>;

	export template <typename T>
	concept VectorComponent = std::regular<T> && Operatable<T> && BothWaysConvertible<T, float>;
}
