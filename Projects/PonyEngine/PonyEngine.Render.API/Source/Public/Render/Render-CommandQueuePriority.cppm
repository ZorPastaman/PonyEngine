/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:CommandQueuePriority;

import <cstdint>;

export namespace PonyEngine::Render
{
	/// @brief Command queue priority.
	enum class CommandQueuePriority : std::int32_t
	{
		Normal = 0,
		High = 100,
		Realtime = 10000
	};
}
