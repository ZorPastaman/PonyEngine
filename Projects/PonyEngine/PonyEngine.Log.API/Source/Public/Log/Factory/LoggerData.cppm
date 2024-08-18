/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Factory:LoggerData;

import <memory>;

import PonyEngine.Log;

import :LoggerDeleter;

export namespace PonyEngine::Log
{
	using LoggerUniquePtr = std::unique_ptr<ILogger, LoggerDeleter>; ///< Logger unique_ptr typedef.

	/// @brief Logger data.
	struct LoggerData final
	{
		LoggerUniquePtr logger; ///< Logger unique_ptr.
	};
}
