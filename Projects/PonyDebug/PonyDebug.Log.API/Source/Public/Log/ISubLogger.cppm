/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyDebug.Log:ISubLogger;

import :LogEntry;

export namespace PonyDebug::Log
{
	/// @brief Sub-logger.
	class ISubLogger
	{
		INTERFACE_BODY(ISubLogger)

		/// @brief Logs the @p logEntry.
		/// @param logEntry Log entry to log.
		virtual void Log(const LogEntry& logEntry) const noexcept = 0;
	};
}
