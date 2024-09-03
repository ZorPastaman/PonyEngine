/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log.Factory:ConsoleSubLoggerData;

import :SubLoggerUniquePtr;

export namespace PonyDebug::Log
{
	/// @brief Console sub-logger data.
	struct ConsoleSubLoggerData final
	{
		SubLoggerUniquePtr subLogger; ///< Sub-logger.
	};
}
