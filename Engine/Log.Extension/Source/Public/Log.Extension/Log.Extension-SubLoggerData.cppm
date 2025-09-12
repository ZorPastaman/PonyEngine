/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Extension:SubLoggerData;

import std;

import :ISubLogger;

export namespace PonyEngine::Log
{
	/// @brief Sub-logger data.
	struct SubLoggerData final
	{
		std::shared_ptr<ISubLogger> subLogger; ///< Sub-logger.
	};
}
