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

export module Application.Windows:WindowsLogger;

import <array>;
import <exception>;

import PonyEngine.Log.Windows.Implementation;

export namespace Application
{
	/// @brief Pony Engine logger for Windows wrapper.
	class WindowsLogger final
	{
	public:
		/// @brief Creates a @p WindowsLogger.
		[[nodiscard("Pure constructor")]]
		WindowsLogger();
		WindowsLogger(const WindowsLogger&) = delete;
		WindowsLogger(WindowsLogger&&) = delete;

		~WindowsLogger() noexcept;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		PonyEngine::Log::ILogger& Logger() const noexcept;

		WindowsLogger& operator =(const WindowsLogger&) = delete;
		WindowsLogger& operator =(WindowsLogger&&) = delete;

	private:
		/// @brief Creates a logger.
		/// @return Created logger.
		[[nodiscard("Pure function")]]
		static PonyEngine::Log::LoggerData CreateLogger();

		/// @brief Creates a console sub-logger.
		/// @return Created console sub-logger.
		[[nodiscard("Pure function")]]
		static PonyEngine::Log::ConsoleSubLoggerData CreateConsoleSubLogger();
		/// @brief Creates an output debug string sub-logger.
		/// @return Created output debug string sub-logger.
		[[nodiscard("Pure function")]]
		static PonyEngine::Log::OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger();
		/// @brief Creates a file sub-logger.
		/// @return Created file sub-logger.
		[[nodiscard("Pure function")]]
		static PonyEngine::Log::FileSubLoggerData CreateFileSubLogger();

		PonyEngine::Log::LoggerUniquePtr logger; ///< Logger.
		std::array<PonyEngine::Log::SubLoggerUniquePtr, 3> subLoggers; ///< Sub-loggers.
	};
}

namespace Application
{
	WindowsLogger::WindowsLogger() :
		logger{CreateLogger().logger},
		subLoggers{CreateConsoleSubLogger().subLogger, CreateOutputDebugStringSubLogger().subLogger, CreateFileSubLogger().subLogger}
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Add sub-loggers.");
		for (PonyEngine::Log::SubLoggerUniquePtr& subLogger : subLoggers)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Add '{}' sub-logger.", subLogger->Name());
			logger->AddSubLogger(*subLogger);
		}
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Sub-loggers added.");
	}

	WindowsLogger::~WindowsLogger() noexcept
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Remove sub-loggers.");
		for (auto it = subLoggers.crbegin(); it != subLoggers.crend(); ++it)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Remove '{}' sub-logger.", (*it)->Name());
			try
			{
				logger->RemoveSubLogger(**it);
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE_E(e, "On removing sub-logger.");
			}
		}
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Sub-loggers removed.");

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy sub-loggers.");
		for (auto it = subLoggers.rbegin(); it != subLoggers.rend(); ++it)
		{
			PonyEngine::Log::SubLoggerUniquePtr& subLogger = *it;

			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy '{}' sub-logger.", subLogger->Name());
			subLogger.reset();
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Sub-logger destroyed.");
		}
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Sub-loggers destroyed.");

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy '{}' logger.", logger->Name());
		logger.reset();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger destroyed.");
	}

	PonyEngine::Log::ILogger& WindowsLogger::Logger() const noexcept
	{
		return *logger;
	}

	PonyEngine::Log::LoggerData WindowsLogger::CreateLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create logger.");
		PonyEngine::Log::LoggerData logger = PonyEngine::Log::CreateLogger(PonyEngine::Log::LoggerParams());
		assert(logger.logger && "The logger is nullptr.");
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' logger created.", logger.logger->Name());

		return logger;
	}

	PonyEngine::Log::ConsoleSubLoggerData WindowsLogger::CreateConsoleSubLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create console sub-logger.");
		PonyEngine::Log::ConsoleSubLoggerData consoleSubLogger = PonyEngine::Log::CreateConsoleSubLogger(PonyEngine::Log::ConsoleSubLoggerParams());
		assert(consoleSubLogger.subLogger && "The console sub-logger is nullptr.");
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' console sub-logger created.", consoleSubLogger.subLogger->Name());

		return consoleSubLogger;
	}

	PonyEngine::Log::OutputDebugStringSubLoggerData WindowsLogger::CreateOutputDebugStringSubLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create output debug string sub-logger.");
		PonyEngine::Log::OutputDebugStringSubLoggerData outputDebugStringSubLogger = PonyEngine::Log::CreateOutputDebugStringSubLogger(PonyEngine::Log::OutputDebugStringSubLoggerParams());
		assert(outputDebugStringSubLogger.subLogger && "The output debug string sub-logger is nullptr.");
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' output debug string sub-logger created.", outputDebugStringSubLogger.subLogger->Name());

		return outputDebugStringSubLogger;
	}

	PonyEngine::Log::FileSubLoggerData WindowsLogger::CreateFileSubLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create file sub-logger.");
		const auto params = PonyEngine::Log::FileSubLoggerParams{.logPath = "Log.log"};
		PonyEngine::Log::FileSubLoggerData fileSubLogger = PonyEngine::Log::CreateFileSubLogger(params);
		assert(fileSubLogger.subLogger && "The file sub-logger is nullptr.");
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' file sub-logger created.", fileSubLogger.subLogger->Name());

		return fileSubLogger;
	}
}
