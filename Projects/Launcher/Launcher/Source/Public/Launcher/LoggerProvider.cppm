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

#include "PonyEngine/Log/LogMacro.h"

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
		PonyEngine::Log::LoggerUniquePtr logger; ///< Logger.

		// Set all sub-loggers here.

		PonyEngine::Log::SubLoggerUniquePtr consoleSubLogger;
		PonyEngine::Log::SubLoggerUniquePtr fileSubLogger;
	};
}

namespace Launcher
{
	LoggerProvider::LoggerProvider()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create a logger.");
		logger = PonyEngine::Log::CreateLogger();
		assert((logger != nullptr));
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger created.");

		// Create and add all sub-loggers here.

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create a console sub-logger.");
		consoleSubLogger = PonyEngine::Log::CreateConsoleSubLogger();
		assert((consoleSubLogger != nullptr));
		logger->AddSubLogger(consoleSubLogger.get());
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Console sub-logger created.");

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create a file sub-logger.");
		fileSubLogger = PonyEngine::Log::CreateFileSubLogger("Log.log");
		assert((fileSubLogger != nullptr));
		logger->AddSubLogger(fileSubLogger.get());
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "File sub-logger created.");
	}

	LoggerProvider::~LoggerProvider() noexcept
	{
		// Remove and destroy all sub-loggers here.

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy a file sub-logger.");
		try
		{
			logger->RemoveSubLogger(fileSubLogger.get());
		}
		catch (std::exception& e)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Exception, std::format("{} - {}", e.what(), "On removing a file sub-logger.").c_str());
		}
		fileSubLogger.reset();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "File sub-logger destroyed.");

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy a console sub-logger.");
		try
		{
			logger->RemoveSubLogger(consoleSubLogger.get());
		}
		catch (std::exception& e)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Exception, std::format("{} - {}", e.what(), "On removing a console sub-logger.").c_str());
		}
		consoleSubLogger.reset();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Console sub-logger destroyed.");

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy a logger.");
		logger.reset();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger destroyed.");
	}

	PonyEngine::Log::ILogger& LoggerProvider::GetLogger() const noexcept
	{
		return *logger;
	}
}
