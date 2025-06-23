/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Main:DefaultLogger;

import std;

import PonyEngine.Core;
import PonyEngine.Log;

export namespace PonyEngine::Main
{
	/// @brief Console logger.
	class DefaultLogger final : public Core::ILogger, private Log::ILogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		DefaultLogger() noexcept = default;
		DefaultLogger(const DefaultLogger&) = delete;
		DefaultLogger(DefaultLogger&&) = delete;

		~DefaultLogger() noexcept = default;

		virtual void Log(Log::LogType logType, const Log::LogInput& logInput) const noexcept override;
		virtual void Log(const std::exception& exception, const Log::LogInput& logInput) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Log::ILogger& PublicLogger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& PublicLogger() const noexcept override;

		DefaultLogger& operator =(const DefaultLogger&) = delete;
		DefaultLogger& operator =(DefaultLogger&&) = delete;
	};
}

namespace PonyEngine::Main
{
	void DefaultLogger::Log(const Log::LogType logType, const Log::LogInput& logInput) const noexcept
	{
		if constexpr (PONY_CONSOLE_LOG_MASK != Log::LogTypeMask::None)
		{
			if (Log::IsInMask(logType, PONY_CONSOLE_LOG_MASK))
			{
				const auto logData = Log::LogData
				{
					.stacktrace = logInput.stacktrace ? *logInput.stacktrace : std::optional<std::basic_stacktrace<std::allocator<std::stacktrace_entry>>>(std::nullopt)
				};
				Log::LogToConsole(logType, logData, logInput.message);
			}
		}
	}

	void DefaultLogger::Log(const std::exception& exception, const Log::LogInput& logInput) const noexcept
	{
		if constexpr (Log::IsInMask(Log::LogType::Exception, PONY_CONSOLE_LOG_MASK))
		{
			const auto logData = Log::LogData
			{
				.stacktrace = logInput.stacktrace ? *logInput.stacktrace : std::optional<std::basic_stacktrace<std::allocator<std::stacktrace_entry>>>(std::nullopt)
			};
			Log::LogToConsole(exception, logData, logInput.message);
		}
	}

	Log::ILogger& DefaultLogger::PublicLogger() noexcept
	{
		return *this;
	}

	const Log::ILogger& DefaultLogger::PublicLogger() const noexcept
	{
		return *this;
	}
}
