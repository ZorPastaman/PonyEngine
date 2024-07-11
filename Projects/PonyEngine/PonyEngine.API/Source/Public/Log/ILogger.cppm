/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:ILogger;

import <exception>;

import :ISubLogger;
import :LogInput;
import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Logger.
	/// @details The logger is an entry point for logs. It translates logs via its sub-loggers.
	class ILogger
	{
	public:
		ILogger(const ILogger&) noexcept = delete;
		ILogger(ILogger&& other) noexcept = delete;

		/// @brief Logs via the current sub-loggers.
		/// @remark Don't log exceptions via this.
		/// @param logType Log type. Must be a valid one true bit value.
		/// @param logInput Log input.
		virtual void Log(LogType logType, const LogInput& logInput) noexcept = 0;
		/// @brief Logs the exception via the current sub-loggers.
		/// @param exception Exception to log.
		/// @param logInput Log input.
		virtual void LogException(const std::exception& exception, const LogInput& logInput) noexcept = 0;

		/// @brief Adds the @p subLogger to the list of sub-loggers.
		/// @param subLogger Sub-logger to add. It mustn't be nullptr. It mustn't be already added.
		virtual void AddSubLogger(ISubLogger* subLogger) = 0;
		/// @brief Removes the @p subLogger from the list of sub-loggers.
		/// @param subLogger Sub-logger to remove.
		virtual void RemoveSubLogger(ISubLogger* subLogger) = 0;

		/// @brief Gets the logger name.
		/// @return Logger name.
		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept = 0;

		ILogger& operator =(const ILogger& other) noexcept = delete;
		ILogger& operator =(ILogger&& other) noexcept = delete;

	protected:
		ILogger() noexcept = default;

		~ILogger() noexcept = default;
	};
}
