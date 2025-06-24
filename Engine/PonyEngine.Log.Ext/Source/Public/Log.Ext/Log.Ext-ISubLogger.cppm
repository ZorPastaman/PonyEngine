/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Log.Extension:ISubLogger;

import std;

import :LogEntry;

export namespace PonyEngine::Log
{
	/// @brief Sub-logger.
	class ISubLogger
	{
		INTERFACE_BODY(ISubLogger)

		/// @brief Begins logging.
		virtual void Begin() = 0;
		/// @brief Ends logging.
		virtual void End() noexcept = 0;

		/// @brief Logs the @p logEntry.
		/// @param logEntry Log entry to log.
		virtual void Log(const LogEntry& logEntry) noexcept = 0;
	};
}
