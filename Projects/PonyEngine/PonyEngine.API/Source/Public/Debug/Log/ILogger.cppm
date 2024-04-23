/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log:ILogger;

import <exception>;

import PonyEngine.Utility;

import :ISubLogger;
import :LogInput;
import :LogType;

export namespace PonyEngine::Debug::Log
{
	/// @brief Engine logger interface.
	/// @details The logger is an entry point for logs. It translates the logs via its sub-loggers.
	class ILogger : public Utility::INamed
	{
	public:
		/// @brief Logs via current sub-loggers.
		/// @details Don't log exceptions via this.
		/// @param logType Log type. Must be a valid one-bit value.
		/// @param logInput Log input.
		virtual void Log(LogType logType, const LogInput& logInput) noexcept = 0;
		/// @brief Logs an exception via current sub-loggers.
		/// @param exception Exception to log.
		/// @param logInput Log input.
		virtual void LogException(const std::exception& exception, const LogInput& logInput) noexcept = 0;

		/// @brief Adds the @p subLogger to the list of sub-loggers.
		/// @param subLogger Sub-logger to add. It mustn't be nullptr. It mustn't be already added.
		virtual void AddSubLogger(ISubLogger* subLogger) = 0;
		/// @brief Removes the @p subLogger from the list of sub-loggers.
		/// @param subLogger Sub-logger to remove.
		virtual void RemoveSubLogger(ISubLogger* subLogger) = 0;

	protected:
		~ILogger() noexcept = default;
	};
}
