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
	template<typename T>
	concept Component = std::is_trivially_copyable_v<T> && std::is_trivially_destructible_v<T>;
}
