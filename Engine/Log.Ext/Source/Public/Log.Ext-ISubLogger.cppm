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
		/// @param logEntry Log entry to log.
		virtual void Log(const LogEntry& logEntry) noexcept = 0;
	};
}
