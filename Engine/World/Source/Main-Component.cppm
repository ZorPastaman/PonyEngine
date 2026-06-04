/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World:Component;

import std;

export namespace PonyEngine::World
{
	/// @brief The concept is satisfied for pure data types.
	template<typename T>
	concept Component = std::is_standard_layout_v<T> && std::is_default_constructible_v<T> && std::is_trivially_copyable_v<T> && std::is_trivially_destructible_v<T>;
}
