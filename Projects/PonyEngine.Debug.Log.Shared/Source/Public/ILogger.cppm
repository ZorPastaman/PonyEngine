/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.ILogger;

import <exception>;
import <string>;

import PonyEngine.Debug.Log.ISubLogger;
import PonyEngine.Debug.Log.LogType;

namespace PonyEngine::Debug::Log
{
	/// @brief Engine logger interface.
	/// @details The logger is an entry point for logs. It translates the logs via its sub-loggers.
	export class ILogger
	{
	public:
		/// @brief Logs via current @p SubLoggers.
		/// @details Don't log exceptions via this.
		/// @param logType Log type. Must be a valid one-bit value.
		/// @param message Log message.
		virtual void Log(LogType logType, const std::string& message) noexcept = 0;
		/// @brief Logs an exception via current @p SubLoggers.
		/// @param exception Exception to log.
		/// @param message Additional message.
		virtual void LogException(const std::exception& exception, const std::string& message = "") noexcept = 0;

		/// @brief Adds the @p subLogger to the list of sub-loggers.
		/// @param subLogger @p SubLogger to add. It mustn't be already added.
		virtual void AddSubLogger(ISubLogger* subLogger) = 0;
		/// @brief Removes the @p subLogger from the list of sub-loggers.
		/// @param subLogger @p SubLogger to remove.
		virtual void RemoveSubLogger(ISubLogger* subLogger) = 0;
	};
}
