/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:ActionId;

import std;

export namespace PonyEngine::Input
{
	/// @brief Action ID.
	struct ActionId final
	{
		std::uint64_t hash = 0ull; ///< Action hash.
	};
}

export
{
	template<>
	struct std::hash<PonyEngine::Input::ActionId> final
	{
		[[nodiscard("Pure function")]]
		size_t operator()(const PonyEngine::Input::ActionId actionId) const noexcept
		{
			return std::hash<std::uint64_t>()(actionId.hash);
		}
	};
}
