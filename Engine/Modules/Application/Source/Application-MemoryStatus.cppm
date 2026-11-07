/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application:MemoryStatus;

import :MemoryInfo;

export namespace PonyEngine::Application
{
	/// @brief Memory status.
	struct MemoryStatus final
	{
		MemoryInfo physicalMemory; ///< Physical memory info.
		MemoryInfo commitMemory; ///< Commit memory info.
		MemoryInfo virtualMemory; ///< Virtual memory info.
	};
}
