/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Utility:Overload;

import std;

export namespace PonyEngine::Utility
{
	/// @brief Overload.
	/// @tparam Ts Types.
	template<typename... Ts>
	struct Overload : Ts...
	{
		using Ts::operator()...;
	};
	/// @brief Overload helper.
	/// @tparam Ts Types.
	/// @return Overload.
	template<typename... Ts>
	Overload(Ts...) -> Overload<Ts...>;
}
