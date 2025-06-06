/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <exception>

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Application:DefaultLogger;

import PonyEngine.Log;

export namespace PonyEngine::Application
{
	/// @brief Console logger.
	class DefaultLogger final : public Log::ILogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		DefaultLogger() noexcept = default;
		DefaultLogger(const DefaultLogger&) = delete;
		DefaultLogger(DefaultLogger&&) = delete;

		~DefaultLogger() noexcept = default;

		virtual void Log(Log::LogType logType, const Log::LogInput& logInput) const noexcept override;
		virtual void LogException(const std::exception& exception, const Log::LogInput& logInput) const noexcept override;

		DefaultLogger& operator =(const DefaultLogger&) = delete;
		DefaultLogger& operator =(DefaultLogger&&) = delete;
	};
}

namespace PonyEngine::Application
{
	void DefaultLogger::Log(const Log::LogType logType, const Log::LogInput& logInput) const noexcept
	{
		if constexpr (PONY_CONSOLE_LOG_MASK != Log::LogTypeMask::None)
		{
			if (Log::IsInMask(logType, PONY_CONSOLE_LOG_MASK))
			{
				Log::LogToConsole(logType, logInput.message);
			}
		}
	}

	void DefaultLogger::LogException(const std::exception& exception, const Log::LogInput& logInput) const noexcept
	{
		PONY_CONSOLE_E(exception, logInput.message);
	}
}
