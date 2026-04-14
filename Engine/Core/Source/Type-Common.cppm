/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Type:Common;

import std;

export namespace PonyEngine::Type
{
	/// @brief The concept is satisfied if @p T is an arithmetic type.
	template<typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;
	/// @brief The concept is satisfied if @p T is a signed type.
	template<typename T>
	concept Signed = std::is_signed_v<T>;
	/// @brief The concept is satisfied if @p T is an unsigned type.
	template<typename T>
	concept Unsigned = std::is_unsigned_v<T>;
}
