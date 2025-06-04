/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <exception>

export module PonyEngine.Application:EmptyLogger;

import PonyEngine.Log;

export namespace PonyEngine::Application
{
	/// @brief Logger that does nothing.
	class EmptyLogger final : public Log::ILogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		EmptyLogger() noexcept = default;
		EmptyLogger(const EmptyLogger&) = delete;
		EmptyLogger(EmptyLogger&&) = delete;

		~EmptyLogger() noexcept = default;

		virtual void Log(Log::LogType logType, const Log::LogInput& logInput) const noexcept override;
		virtual void LogException(const std::exception& exception, const Log::LogInput& logInput) const noexcept override;

		EmptyLogger& operator =(const EmptyLogger&) = delete;
		EmptyLogger& operator =(EmptyLogger&&) = delete;
	};
}

namespace PonyEngine::Application
{
	void EmptyLogger::Log(Log::LogType logType, const Log::LogInput& logInput) const noexcept
	{
	}

	void EmptyLogger::LogException(const std::exception& exception, const Log::LogInput& logInput) const noexcept
	{
	}
}
