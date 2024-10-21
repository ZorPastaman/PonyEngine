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

export module Application.Windows:WindowsLogger;

import <array>;
import <exception>;

import PonyDebug.Log.Windows.Implementation;

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
		PonyDebug::Log::ILogger& Logger() const noexcept;

		WindowsLogger& operator =(const WindowsLogger&) = delete;
		WindowsLogger& operator =(WindowsLogger&&) = delete;

	private:
		/// @brief Creates a logger.
		/// @return Created logger.
		[[nodiscard("Pure function")]]
		static PonyDebug::Log::LoggerData CreateLogger();

		/// @brief Creates a console sub-logger.
		/// @return Created console sub-logger.
		[[nodiscard("Pure function")]]
		static PonyDebug::Log::ConsoleSubLoggerData CreateConsoleSubLogger();
		/// @brief Creates an output debug string sub-logger.
		/// @return Created output debug string sub-logger.
		[[nodiscard("Pure function")]]
		static PonyDebug::Log::OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger();
		/// @brief Creates a file sub-logger.
		/// @return Created file sub-logger.
		[[nodiscard("Pure function")]]
		static PonyDebug::Log::FileSubLoggerData CreateFileSubLogger();

		PonyDebug::Log::LoggerUniquePtr<PonyDebug::Log::ILogger> logger; ///< Logger.
		std::array<PonyDebug::Log::SubLoggerUniquePtr<PonyDebug::Log::ISubLogger>, 3> subLoggers; ///< Sub-loggers.
	};
}

namespace Application
{
	WindowsLogger::WindowsLogger() :
		logger{CreateLogger().logger},
		subLoggers
		{
			CreateConsoleSubLogger().subLogger,
			static_cast<PonyDebug::Log::SubLoggerUniquePtr<PonyDebug::Log::ISubLogger>>(CreateOutputDebugStringSubLogger().subLogger),
			CreateFileSubLogger().subLogger
		}
	{
		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Add sub-loggers.");
		for (PonyDebug::Log::SubLoggerUniquePtr<PonyDebug::Log::ISubLogger>& subLogger : subLoggers)
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Debug, "Add '{}' sub-logger.", subLogger->Name());
			logger->AddSubLogger(*subLogger);
		}
		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Sub-loggers added.");
	}

	WindowsLogger::~WindowsLogger() noexcept
	{
		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Remove sub-loggers.");
		for (auto it = subLoggers.crbegin(); it != subLoggers.crend(); ++it)
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Debug, "Remove '{}' sub-logger.", (*it)->Name());
			try
			{
				logger->RemoveSubLogger(**it);
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE_E(e, "On removing sub-logger.");
			}
		}
		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Sub-loggers removed.");

		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Destroy sub-loggers.");
		for (auto it = subLoggers.rbegin(); it != subLoggers.rend(); ++it)
		{
			PonyDebug::Log::SubLoggerUniquePtr<PonyDebug::Log::ISubLogger>& subLogger = *it;

			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Destroy '{}' sub-logger.", subLogger->Name());
			subLogger.Reset();
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Sub-logger destroyed.");
		}
		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Sub-loggers destroyed.");

		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Destroy '{}' logger.", logger->Name());
		logger.Reset();
		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Logger destroyed.");
	}

	PonyDebug::Log::ILogger& WindowsLogger::Logger() const noexcept
	{
		return *logger;
	}

	PonyDebug::Log::LoggerData WindowsLogger::CreateLogger()
	{
		try
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Create logger.");
			PonyDebug::Log::LoggerData logger = PonyDebug::Log::CreateLogger(PonyDebug::Log::LoggerParams{});
			assert(logger.logger && "The logger is nullptr.");
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "'{}' logger created.", logger.logger->Name());

			return logger;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On creating logger.");

			throw;
		}
	}

	PonyDebug::Log::ConsoleSubLoggerData WindowsLogger::CreateConsoleSubLogger()
	{
		try
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Create console sub-logger.");
			PonyDebug::Log::ConsoleSubLoggerData consoleSubLogger = PonyDebug::Log::CreateConsoleSubLogger(PonyDebug::Log::ConsoleSubLoggerParams{});
			assert(consoleSubLogger.subLogger && "The console sub-logger is nullptr.");
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "'{}' console sub-logger created.", consoleSubLogger.subLogger->Name());

			return consoleSubLogger;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On creating console sub-logger.");

			throw;
		}
	}

	PonyDebug::Log::OutputDebugStringSubLoggerData WindowsLogger::CreateOutputDebugStringSubLogger()
	{
		try
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Create output debug string sub-logger.");
			PonyDebug::Log::OutputDebugStringSubLoggerData outputDebugStringSubLogger = PonyDebug::Log::CreateOutputDebugStringSubLogger(PonyDebug::Log::OutputDebugStringSubLoggerParams{});
			assert(outputDebugStringSubLogger.subLogger && "The output debug string sub-logger is nullptr.");
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "'{}' output debug string sub-logger created.", outputDebugStringSubLogger.subLogger->Name());

			return outputDebugStringSubLogger;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On creating output debug string sub-logger.");

			throw;
		}
	}

	PonyDebug::Log::FileSubLoggerData WindowsLogger::CreateFileSubLogger()
	{
		try
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Create file sub-logger.");
			const auto params = PonyDebug::Log::FileSubLoggerParams{.logPath = "Log.log"};
			PonyDebug::Log::FileSubLoggerData fileSubLogger = PonyDebug::Log::CreateFileSubLogger(params);
			assert(fileSubLogger.subLogger && "The file sub-logger is nullptr.");
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "'{}' file sub-logger created.", fileSubLogger.subLogger->Name());

			return fileSubLogger;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On creating file sub-logger.");

			throw;
		}
	}
}
