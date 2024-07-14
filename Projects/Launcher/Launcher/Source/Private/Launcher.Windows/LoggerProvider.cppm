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

#include "PonyEngine/Log/Log.h"

export module Launcher.Windows:LoggerProvider;

import <exception>;
import <format>;
import <iostream>;

import PonyEngine.Log;
import PonyEngine.Log.Implementation;

export namespace Launcher
{
	/// @brief Logger provider.
	class LoggerProvider final
	{
	public:
		/// @brief Creates a logger provider.
		[[nodiscard("Pure constructor")]]
		LoggerProvider();
		LoggerProvider(const LoggerProvider&) = delete;
		LoggerProvider(LoggerProvider&&) = delete;

		~LoggerProvider() noexcept;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		PonyEngine::Log::ILogger& GetLogger() const noexcept;

		LoggerProvider& operator =(const LoggerProvider&) = delete;
		LoggerProvider& operator =(LoggerProvider&&) = delete;

	private:
		PonyEngine::Log::LoggerUniquePtr logger; ///< Logger.

		// Set all sub-loggers here.

		PonyEngine::Log::ConsoleSubLoggerUniquePtr consoleSubLogger; ///< Console sub-logger.
		PonyEngine::Log::FileSubLoggerUniquePtr fileSubLogger; ///< File sub-logger.
	};
}

namespace Launcher
{
	LoggerProvider::LoggerProvider()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create logger.");
		logger = PonyEngine::Log::CreateLogger();
		assert((logger && "The logger is nullptr."));
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger created.");

		// Create and add all sub-loggers here.

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create console sub-logger.");
		consoleSubLogger = PonyEngine::Log::CreateConsoleSubLogger();
		assert((consoleSubLogger && "The console sub-logger is nullptr."));
		logger->AddSubLogger(consoleSubLogger.get());
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Console sub-logger created.");

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create file sub-logger.");
		fileSubLogger = PonyEngine::Log::CreateFileSubLogger("Log.log");
		assert((fileSubLogger && "The file sub-logger is nullptr."));
		logger->AddSubLogger(fileSubLogger.get());
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "File sub-logger created.");
	}

	LoggerProvider::~LoggerProvider() noexcept
	{
		// Remove and destroy all sub-loggers here.

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy file sub-logger.");
		try
		{
			logger->RemoveSubLogger(fileSubLogger.get());
		}
		catch (std::exception& e)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Exception, std::format("{} - On removing the file sub-logger.", e.what()).c_str());
		}
		fileSubLogger.reset();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "File sub-logger destroyed.");

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy console sub-logger.");
		try
		{
			logger->RemoveSubLogger(consoleSubLogger.get());
		}
		catch (std::exception& e)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Exception, std::format("{} - On removing the console sub-logger.", e.what()).c_str());
		}
		consoleSubLogger.reset();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Console sub-logger destroyed.");

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy logger.");
		logger.reset();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger destroyed.");
	}

	PonyEngine::Log::ILogger& LoggerProvider::GetLogger() const noexcept
	{
		return *logger;
	}
}
