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

export module PonyEngine.Application.Main:DefaultLogger;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

export namespace PonyEngine::Application
{
	/// @brief Console logger.
	class DefaultLogger final : public Log::ILogger
	{
	public:
		/// @brief Creates a default logger.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit DefaultLogger(IApplicationContext& application) noexcept;
		DefaultLogger(const DefaultLogger&) = delete;
		DefaultLogger(DefaultLogger&&) = delete;

		~DefaultLogger() noexcept = default;

		virtual void Log(Log::LogType logType, const Log::LogInput& logInput) const noexcept override;
		virtual void Log(const std::exception& exception, const Log::LogInput& logInput) const noexcept override;

		DefaultLogger& operator =(const DefaultLogger&) = delete;
		DefaultLogger& operator =(DefaultLogger&&) = delete;

	private:
		IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Application
{
	DefaultLogger::DefaultLogger(IApplicationContext& application) noexcept :
		application{&application}
	{
	}

	void DefaultLogger::Log(const Log::LogType logType, const Log::LogInput& logInput) const noexcept
	{
		if constexpr (PONY_CONSOLE_LOG_MASK != Log::LogTypeMask::None)
		{
			if (Log::IsInMask(logType, PONY_CONSOLE_LOG_MASK))
			{
				const std::string log = logInput.stacktrace
					? Log::LogFormat(logType, logInput.message, std::chrono::system_clock::now(), application->FrameCount(), *logInput.stacktrace)
					: Log::LogFormat(logType, logInput.message, std::chrono::system_clock::now(), application->FrameCount());
				Log::LogToConsole(logType, log);
			}
		}
	}

	void DefaultLogger::Log(const std::exception& exception, const Log::LogInput& logInput) const noexcept
	{
		if constexpr (Log::IsInMask(Log::LogType::Exception, PONY_CONSOLE_LOG_MASK))
		{
			const std::string log = logInput.stacktrace
				? Log::LogFormat(Log::LogType::Exception, exception.what(), logInput.message, std::chrono::system_clock::now(), application->FrameCount(), *logInput.stacktrace)
				: Log::LogFormat(Log::LogType::Exception, exception.what(), logInput.message, std::chrono::system_clock::now(), application->FrameCount());
			Log::LogToConsole(Log::LogType::Exception, log);
		}
	}
}
