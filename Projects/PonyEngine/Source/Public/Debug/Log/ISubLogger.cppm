/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log:ISubLogger;

import :LogEntry;

namespace PonyEngine::Debug::Log
{
	/// @brief SubLogger interface.
	/// @details The sub-logger writes received logs to something.
	export class ISubLogger
	{
	public:
		virtual ~ISubLogger() = default;

		/// @brief Logs the @p logEntry to something.
		/// @param logEntry Log entry to log.
		virtual void Log(const LogEntry& logEntry) noexcept = 0;
	};
}
