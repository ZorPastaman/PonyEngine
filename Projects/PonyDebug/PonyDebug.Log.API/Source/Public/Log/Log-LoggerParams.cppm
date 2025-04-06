/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:LoggerParams;

import <cstddef>;

export namespace PonyDebug::Log
{
	/// @brief Logger parameters.
	struct LoggerParams final
	{
		std::size_t subLoggerCount = 0; ///< Expected number of sub-logger. It's used for preallocating memory and doesn't limit a count of sub-loggers.
	};
}
