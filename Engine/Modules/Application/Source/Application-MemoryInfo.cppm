/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application:MemoryInfo;

import std;

export namespace PonyEngine::Application
{
	/// @brief Memory info.
	struct MemoryInfo final
	{
		std::uint64_t total = 0ull; ///< Total memory in bytes.
		std::uint64_t available = 0ull; ///< Available memory in bytes.
	};
}
