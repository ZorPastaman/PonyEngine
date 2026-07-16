/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Log.Ext:ISubLogger;

import std;

import :LogEntry;

export namespace PonyEngine::Log
{
	/// @brief Sub-logger.
	class ISubLogger
	{
		PONY_INTERFACE_BODY(ISubLogger)

		/// @brief Logs the @p logEntry.
		/// @param formattedMessage Formatted message.
		/// @param logEntry Source data of the log.
		/// @note The function may be called on different threads, but it is guaranteed that it will not be executed concurrently.
		virtual void Log(std::string_view formattedMessage, const LogEntry& logEntry) noexcept = 0;
	};
}
