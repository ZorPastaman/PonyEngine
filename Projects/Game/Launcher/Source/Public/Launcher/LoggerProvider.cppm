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

#include "Log/LogMacro.h"

export module Launcher:LoggerProvider;

import <exception>;
import <format>;
import <iostream>;
import <string>;

import PonyEngine.Log;
import PonyEngine.Log.Implementation;

export namespace Launcher
{
	/// @brief Logger provider creates and destroys a logger and its sub-loggers.
	class LoggerProvider final
	{
	public:
		/// @brief Creates a logger provider with a logger.
		[[nodiscard("Pure constructor")]]
		LoggerProvider();
		LoggerProvider(const LoggerProvider&) = delete;
		LoggerProvider(LoggerProvider&&) = delete;

		~LoggerProvider() noexcept;

		/// @brief Gets a logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		PonyEngine::Log::ILogger& GetLogger() const noexcept;

		LoggerProvider& operator =(const LoggerProvider&) = delete;
		LoggerProvider& operator =(LoggerProvider&&) = delete;

	private:
		PonyEngine::Log::ILogger* m_logger; ///< Logger.

		// Set all sub-loggers here.

		PonyEngine::Log::ISubLogger* m_consoleSubLogger;
		PonyEngine::Log::ISubLogger* m_fileSubLogger;
	};
}

namespace Launcher
{
	LoggerProvider::LoggerProvider()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create a logger.");
		m_logger = PonyEngine::Log::CreateLogger();
		assert((m_logger != nullptr));
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger created.");

		// Create and add all sub-loggers here.

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create a console sub-logger.");
		m_consoleSubLogger = PonyEngine::Log::CreateConsoleSubLogger();
		assert((m_consoleSubLogger != nullptr));
		m_logger->AddSubLogger(m_consoleSubLogger);
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Console sub-logger created.");

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create a file sub-logger.");
		m_fileSubLogger = PonyEngine::Log::CreateFileSubLogger("Log.log");
		assert((m_fileSubLogger != nullptr));
		m_logger->AddSubLogger(m_fileSubLogger);
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "File sub-logger created.");
	}

	LoggerProvider::~LoggerProvider() noexcept
	{
		// Remove and destroy all sub-loggers here.

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy a file sub-logger.");
		try
		{
			m_logger->RemoveSubLogger(m_fileSubLogger);
		}
		catch (std::exception& e)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Exception, std::format("{} - {}", e.what(), "On removing a file sub-logger.").c_str());
		}
		PonyEngine::Log::DestroyFileSubLogger(m_fileSubLogger);
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "File sub-logger destroyed.");

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy a console sub-logger.");
		try
		{
			m_logger->RemoveSubLogger(m_consoleSubLogger);
		}
		catch (std::exception& e)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Exception, std::format("{} - {}", e.what(), "On removing a console sub-logger.").c_str());
		}
		PonyEngine::Log::DestroyConsoleSubLogger(m_consoleSubLogger);
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Console sub-logger destroyed.");

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy a logger.");
		PonyEngine::Log::DestroyLogger(m_logger);
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger destroyed.");
	}

	PonyEngine::Log::ILogger& LoggerProvider::GetLogger() const noexcept
	{
		return *m_logger;
	}
}
