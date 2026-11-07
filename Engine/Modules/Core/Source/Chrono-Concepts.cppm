/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Chrono:Concepts;

import std;

export namespace PonyEngine::Chrono
{
	/// @brief The concept is satisfied if @p T is a clock type.
	template<typename T>
	concept Clock = std::chrono::is_clock_v<T>;
}
