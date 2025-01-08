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

export module Application.Windows:Logger;

import <array>;
import <exception>;
import <format>;
import <memory>;
import <typeinfo>;

import PonyDebug.Log.Windows.Impl;

export namespace Application::Windows
{
	/// @brief Pony Engine logger for Windows wrapper.
	class Logger final
	{
	public:
		/// @brief Creates a @p Logger.
		[[nodiscard("Pure constructor")]]
		Logger();
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;

		~Logger() noexcept;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		PonyDebug::Log::ILogger& AppLogger() noexcept;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		const PonyDebug::Log::ILogger& AppLogger() const noexcept;

		Logger& operator =(const Logger&) = delete;
		Logger& operator =(Logger&&) = delete;

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
		static PonyDebug::Log::Windows::OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger();
		/// @brief Creates a file sub-logger.
		/// @return Created file sub-logger.
		[[nodiscard("Pure function")]]
		static PonyDebug::Log::FileSubLoggerData CreateFileSubLogger();

		std::unique_ptr<PonyDebug::Log::Logger> logger; ///< Logger.
		std::array<std::unique_ptr<PonyDebug::Log::SubLogger>, 3> subLoggers; ///< Sub-loggers.
	};
}

namespace Application::Windows
{
	Logger::Logger() :
		logger{CreateLogger().logger},
		subLoggers
		{
			CreateConsoleSubLogger().subLogger,
			CreateOutputDebugStringSubLogger().subLogger,
			CreateFileSubLogger().subLogger
		}
	{
		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Add sub-loggers.");
		for (std::unique_ptr<PonyDebug::Log::SubLogger>& subLogger : subLoggers)
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Debug, "Add '{}' sub-logger.", typeid(*subLogger).name());
			logger->AddSubLogger(*subLogger);
		}
		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Sub-loggers added.");
	}

	Logger::~Logger() noexcept
	{
		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Remove sub-loggers.");
		for (auto it = subLoggers.crbegin(); it != subLoggers.crend(); ++it)
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Debug, "Remove '{}' sub-logger.", typeid(**it).name());
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
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Destroy '{}' sub-logger.", typeid(**it).name());
			it->reset();
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Sub-logger destroyed.");
		}
		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Sub-loggers destroyed.");

		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Destroy '{}' logger.", typeid(*logger).name());
		logger.reset();
		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Logger destroyed.");
	}

	PonyDebug::Log::ILogger& Logger::AppLogger() noexcept
	{
		return *logger;
	}

	const PonyDebug::Log::ILogger& Logger::AppLogger() const noexcept
	{
		return *logger;
	}

	PonyDebug::Log::LoggerData Logger::CreateLogger()
	{
		try
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Create logger.");
			PonyDebug::Log::LoggerData logger = PonyDebug::Log::CreateLogger(PonyDebug::Log::LoggerParams{});
			assert(logger.logger && "The logger is nullptr.");
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "'{}' logger created.", typeid(*logger.logger).name());

			return logger;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On creating logger.");

			throw;
		}
	}

	PonyDebug::Log::ConsoleSubLoggerData Logger::CreateConsoleSubLogger()
	{
		try
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Create console sub-logger.");
			PonyDebug::Log::ConsoleSubLoggerData consoleSubLogger = PonyDebug::Log::CreateConsoleSubLogger(PonyDebug::Log::ConsoleSubLoggerParams{});
			assert(consoleSubLogger.subLogger && "The console sub-logger is nullptr.");
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "'{}' console sub-logger created.", typeid(*consoleSubLogger.subLogger).name());

			return consoleSubLogger;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On creating console sub-logger.");

			throw;
		}
	}

	PonyDebug::Log::Windows::OutputDebugStringSubLoggerData Logger::CreateOutputDebugStringSubLogger()
	{
		try
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Create output debug string sub-logger.");
			PonyDebug::Log::Windows::OutputDebugStringSubLoggerData outputDebugStringSubLogger = PonyDebug::Log::Windows::CreateOutputDebugStringSubLogger(PonyDebug::Log::Windows::OutputDebugStringSubLoggerParams{});
			assert(outputDebugStringSubLogger.subLogger && "The output debug string sub-logger is nullptr.");
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "'{}' output debug string sub-logger created.", typeid(*outputDebugStringSubLogger.subLogger).name());

			return outputDebugStringSubLogger;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On creating output debug string sub-logger.");

			throw;
		}
	}

	PonyDebug::Log::FileSubLoggerData Logger::CreateFileSubLogger()
	{
		try
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Create file sub-logger.");
			const auto params = PonyDebug::Log::FileSubLoggerParams{.logPath = "Log.log"};
			PonyDebug::Log::FileSubLoggerData fileSubLogger = PonyDebug::Log::CreateFileSubLogger(params);
			assert(fileSubLogger.subLogger && "The file sub-logger is nullptr.");
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, "'{}' file sub-logger created.", typeid(*fileSubLogger.subLogger).name());

			return fileSubLogger;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On creating file sub-logger.");

			throw;
		}
	}
}
