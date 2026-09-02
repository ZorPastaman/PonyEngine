/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Log.Ext:ILogger;

import std;

import :LogEntry;

export namespace PonyEngine::Log
{
	/// @brief Logger.
	class ILogger
	{
		PONY_INTERFACE_BODY(ILogger)

		/// @brief Logs the @p logEntry.
		/// @param formattedMessage Formatted message.
		/// @param logEntry Source data of the log.
		/// @note The function may be called on different threads, but it is guaranteed that it will not be executed concurrently.
		virtual void Log(std::string_view formattedMessage, const LogEntry& logEntry) noexcept = 0;
	};
}
