/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Type:Variant;

import std;

export namespace PonyEngine::Type
{
	/// @brief Overload helper.
	/// @tparam Ts Types.
	template<typename... Ts>
	struct Overload : Ts...
	{
		using Ts::operator()...;
	};
	/// @brief Overload helper.
	/// @tparam Ts Types.
	/// @return Return value.
	template<typename... Ts>
	Overload(Ts...) -> Overload<Ts...>;
}
