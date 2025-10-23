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

import PonyEngine.Application.Extension;
import PonyEngine.Log;

import :Console;

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

		virtual void Log(Log::LogType logType, std::string_view message, const Log::LogData& logData = Log::LogData()) const noexcept override;
		virtual void Log(const std::exception& exception, std::string_view message, const Log::LogData& logData = Log::LogData()) const noexcept override;

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

	void DefaultLogger::Log(const Log::LogType logType, const std::string_view message, const Log::LogData& logData) const noexcept
	{
#if PONY_ENGINE_DEFAULT_LOGGER
		if constexpr (PONY_LOG_MASK != Log::LogTypeMask::None)
		{
			if (Log::IsInMask(logType, PONY_LOG_MASK))
			{
				const std::string log = logData.stacktrace
					? Log::LogFormat(logType, message, std::chrono::system_clock::now(), application->FrameCount(), *logData.stacktrace)
					: Log::LogFormat(logType, message, std::chrono::system_clock::now(), application->FrameCount());
				LogToConsole(logType, log);
			}
		}
#endif
	}

	void DefaultLogger::Log(const std::exception& exception, const std::string_view message, const Log::LogData& logData) const noexcept
	{
#if PONY_ENGINE_DEFAULT_LOGGER
		if constexpr (Log::IsInMask(Log::LogType::Exception, PONY_LOG_MASK))
		{
			const std::string log = logData.stacktrace
				? Log::LogFormat(Log::LogType::Exception, exception.what(), message, std::chrono::system_clock::now(), application->FrameCount(), *logData.stacktrace)
				: Log::LogFormat(Log::LogType::Exception, exception.what(), message, std::chrono::system_clock::now(), application->FrameCount());
			LogToConsole(Log::LogType::Exception, log);
		}
#endif
	}
}
