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
import :LoggerParams;

export namespace PonyDebug::Log
{
	/// @brief Logger.
	class Logger : public ILogger
	{
	public:
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;

		virtual ~Logger() noexcept = default;

		Logger& operator =(const Logger&) = delete;
		Logger& operator =(Logger&&) = delete;

	protected:
		/// @brief Creates a @Logger.
		/// @param params Logger parameters.
		[[nodiscard("Pure constructor")]]
		explicit Logger(const LoggerParams& params) noexcept;
	};
}

namespace PonyDebug::Log
{
	Logger::Logger(const LoggerParams&) noexcept
	{
	}
}
