/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:ConsoleSubLoggerData;

import <memory>;

import :SubLogger;

export namespace PonyDebug::Log
{
	/// @brief Console sub-logger data.
	struct ConsoleSubLoggerData final
	{
		std::shared_ptr<SubLogger> subLogger; ///< Sub-logger.
	};
}
