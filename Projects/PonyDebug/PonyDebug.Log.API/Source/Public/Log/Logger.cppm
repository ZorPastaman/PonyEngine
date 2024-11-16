/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:Logger;

import :ILogger;
import :ISubLogger;

export namespace PonyDebug::Log
{
	/// @brief Logger.
	class Logger : public ILogger
	{
	public:
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;

		virtual ~Logger() noexcept = default;

		/// @brief Adds the @p subLogger to the list of sub-loggers.
		/// @param subLogger Sub-logger to add. It mustn't be already added.
		virtual void AddSubLogger(ISubLogger& subLogger) = 0;
		/// @brief Removes the @p subLogger from the list of sub-loggers.
		/// @param subLogger Sub-logger to remove.
		virtual void RemoveSubLogger(ISubLogger& subLogger) = 0;

		Logger& operator =(const Logger&) = delete;
		Logger& operator =(Logger&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		Logger() noexcept = default;
	};
}
