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

export module Application.Windows:WindowsLoggerProvider;

import <array>;
import <exception>;
import <iostream>;

import PonyEngine.Log.Windows.Factory;

import LogHelpers.Windows;

export namespace Application
{
	/// @brief Logger provider for Windows.
	class WindowsLoggerProvider final
	{
	public:
		/// @brief Creates a logger provider.
		[[nodiscard("Pure constructor")]]
		WindowsLoggerProvider();
		WindowsLoggerProvider(const WindowsLoggerProvider&) = delete;
		WindowsLoggerProvider(WindowsLoggerProvider&&) = delete;

		~WindowsLoggerProvider() noexcept;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		PonyEngine::Log::ILogger& Logger() const noexcept;

		WindowsLoggerProvider& operator =(const WindowsLoggerProvider&) = delete;
		WindowsLoggerProvider& operator =(WindowsLoggerProvider&&) = delete;

	private:
		PonyEngine::Log::LoggerUniquePtr logger; ///< Logger.
		std::array<PonyEngine::Log::SubLoggerUniquePtr, 3> subLoggers; ///< Sub-loggers.
	};
}

namespace Application
{
	/// @brief Creates a logger.
	/// @return Created logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::LoggerData CreateLogger();

	/// @brief Creates a console sub-logger.
	/// @return Created console sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::ConsoleSubLoggerData CreateConsoleSubLogger();
	/// @brief Creates an output debug string sub-logger.
	/// @return Created output debug string sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger();
	/// @brief Creates a file sub-logger.
	/// @return Created file sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::FileSubLoggerData CreateFileSubLogger();

	WindowsLoggerProvider::WindowsLoggerProvider() :
		logger{CreateLogger().logger},
		subLoggers{CreateConsoleSubLogger().subLogger, CreateOutputDebugStringSubLogger().subLogger, CreateFileSubLogger().subLogger}
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Add sub-loggers.");
		for (PonyEngine::Log::SubLoggerUniquePtr& subLogger : subLoggers)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Add '{}' sub-logger.", subLogger->Name());
			logger->AddSubLogger(*subLogger.get());
			PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Sub-logger added.");
		}
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Sub-loggers added.");
	}

	WindowsLoggerProvider::~WindowsLoggerProvider() noexcept
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Remove sub-loggers.");
		for (auto it = subLoggers.crbegin(); it != subLoggers.crend(); ++it)
		{
			const PonyEngine::Log::SubLoggerUniquePtr& subLogger = *it;

			PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Remove '{}' sub-logger.", subLogger->Name());
			try
			{
				logger->RemoveSubLogger(*subLogger.get());
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE_E(e, "On removing sub-logger.");
			}
			PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Sub-logger removed.");
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

	PonyEngine::Log::ILogger& WindowsLoggerProvider::Logger() const noexcept
	{
		return *logger;
	}

	PonyEngine::Log::LoggerData CreateLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create and set up logger.");
		PonyEngine::Log::LoggerData logger = LogHelpers::CreateAndSetupLogger();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' logger created and set up.", logger.logger->Name());

		return logger;
	}

	PonyEngine::Log::ConsoleSubLoggerData CreateConsoleSubLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create and set up console sub-logger.");
		PonyEngine::Log::ConsoleSubLoggerData consoleSubLogger = LogHelpers::CreateAndSetupConsoleSubLogger();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' console sub-logger created and set up.", consoleSubLogger.subLogger->Name());

		return consoleSubLogger;
	}

	PonyEngine::Log::OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create and set up output debug string sub-logger.");
		PonyEngine::Log::OutputDebugStringSubLoggerData outputDebugStringSubLogger = LogHelpers::CreateAndSetupOutputDebugStringSubLogger();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' output debug string sub-logger created and set up.", outputDebugStringSubLogger.subLogger->Name());

		return outputDebugStringSubLogger;
	}

	PonyEngine::Log::FileSubLoggerData CreateFileSubLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create and set up file sub-logger.");
		PonyEngine::Log::FileSubLoggerData fileSubLogger = LogHelpers::CreateAndSetupFileSubLogger();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' file sub-logger created and set up.", fileSubLogger.subLogger->Name());

		return fileSubLogger;
	}
}
