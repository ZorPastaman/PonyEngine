/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Job:JobHandle;

import std;

export namespace PonyEngine::Job
{
	/// @brief Job handle.
	struct JobHandle final
	{
		std::size_t id = std::numeric_limits<std::size_t>::max(); ///< Job ID.
		std::size_t version = 0uz; ///< Handle version.
	};
}
