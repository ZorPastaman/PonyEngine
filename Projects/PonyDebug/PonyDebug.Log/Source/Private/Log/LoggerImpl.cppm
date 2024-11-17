/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyDebug/Log/Log.h"

export module PonyDebug.Log.Detail:LoggerImpl;

import <algorithm>;
import <chrono>;
import <format>;
import <exception>;
import <typeinfo>;
import <utility>;
import <vector>;

import PonyDebug.Log;

export namespace PonyDebug::Log
{
	/// @brief Logger implementation.
	/// @details It just resends logs to its sub-loggers.
	class LoggerImpl final : public Logger
	{
	public:
		/// @brief Creates a @p LoggerImpl.
		/// @param params Logger parameters.
		[[nodiscard("Pure constructor")]]
		explicit LoggerImpl(const LoggerParams& params) noexcept;
		LoggerImpl(const LoggerImpl&) = delete;
		LoggerImpl(LoggerImpl&&) noexcept = delete;

		virtual ~LoggerImpl() noexcept override = default;

		virtual void Log(LogType logType, const LogInput& logInput) const noexcept override;
		virtual void LogException(const std::exception& exception, const LogInput& logInput) const noexcept override;

		virtual void AddSubLogger(ISubLogger& subLogger) override;
		virtual void RemoveSubLogger(ISubLogger& subLogger) override;

		LoggerImpl& operator =(const LoggerImpl&) = delete;
		LoggerImpl& operator =(LoggerImpl&&) = delete;

	private:
		std::vector<ISubLogger*> subLoggers; ///< Sub-loggers container.
	};
}

namespace PonyDebug::Log
{
	LoggerImpl::LoggerImpl(const LoggerParams&) noexcept
	{
	}

	void LoggerImpl::Log(const LogType logType, const LogInput& logInput) const noexcept
	{
		const auto logEntry = LogEntry(logInput.message, nullptr, std::chrono::system_clock::now(), logInput.frameCount, logType);

		for (const ISubLogger* const subLogger : subLoggers)
		{
			subLogger->Log(logEntry);
		}
	}

	void LoggerImpl::LogException(const std::exception& exception, const LogInput& logInput) const noexcept
	{
		const auto logEntry = LogEntry(logInput.message, &exception, std::chrono::system_clock::now(), logInput.frameCount, LogType::Exception);

		for (const ISubLogger* const subLogger : subLoggers)
		{
			subLogger->Log(logEntry);
		}
	}

	void LoggerImpl::AddSubLogger(ISubLogger& subLogger)
	{
		assert(std::ranges::find(std::as_const(subLoggers), &subLogger) == subLoggers.cend() && "The sub-logger has already been added.");
		subLoggers.push_back(&subLogger);
		PONY_CONSOLE(LogType::Debug, "'{}' sub-logger added.", typeid(subLogger).name());
	}

	void LoggerImpl::RemoveSubLogger(ISubLogger& subLogger)
	{
		if (const auto position = std::ranges::find(std::as_const(subLoggers), &subLogger); position != subLoggers.cend()) [[likely]]
		{
			subLoggers.erase(position);
			PONY_CONSOLE(LogType::Debug, "'{}' sub-logger removed.", typeid(subLogger).name());
		}
		else [[unlikely]]
		{
			PONY_CONSOLE(LogType::Warning, "Tried to remove not added '{}' sub-logger.", typeid(subLogger).name());
		}
	}
}
