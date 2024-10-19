/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:ISubLogger;

import :LogEntry;

export namespace PonyDebug::Log
{
	/// @brief Sub-logger.
	class ISubLogger
	{
	public:
		ISubLogger(const ISubLogger&) = delete;
		ISubLogger(ISubLogger&&) = delete;

		/// @brief Logs the @p logEntry.
		/// @param logEntry Log entry to log.
		virtual void Log(const LogEntry& logEntry) noexcept = 0;

		/// @brief Gets the sub-logger name.
		/// @return Sub-logger name.
		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept = 0;

		ISubLogger& operator =(const ISubLogger&) = delete;
		ISubLogger& operator =(ISubLogger&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ISubLogger() noexcept = default;

		~ISubLogger() noexcept = default;
	};
}
