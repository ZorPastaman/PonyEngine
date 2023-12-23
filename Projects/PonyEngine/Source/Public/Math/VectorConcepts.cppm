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
	concept Addable = requires (T x) 
	{ 
		{ x + x } -> std::same_as<T>;
		{ x - x } -> std::same_as<T>;
	};

	template <typename T, typename U>
	concept BothWaysConvertible = std::convertible_to<T, U>&& std::convertible_to<U, T>;

	export template <typename T>
	concept VectorComponent = std::regular<T> && Addable<T> && BothWaysConvertible<T, float>;
}
