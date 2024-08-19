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

export module Launcher.Windows:WindowsLoggerProvider;

import <array>;
import <exception>;
import <iostream>;

import PonyEngine.Log.Factory;

import LogHelper.Windows;

export namespace Launcher
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

namespace Launcher
{
	WindowsLoggerProvider::WindowsLoggerProvider()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create and set up logger.");
		logger = LogHelper::CreateAndSetupLogger().logger;
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' logger created and set up.", logger->Name());

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create and set up console sub-logger.");
		subLoggers[0] = LogHelper::CreateAndSetupConsoleSubLogger().subLogger;
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' console sub-logger created and set up.", subLoggers[0]->Name());

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create and set up output debug string sub-logger.");
		subLoggers[1] = LogHelper::CreateAndSetupOutputDebugStringSubLogger().subLogger;
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' output debug string sub-logger created and set up.", subLoggers[1]->Name());

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create and set up file sub-logger.");
		subLoggers[2] = LogHelper::CreateAndSetupFileSubLogger().subLogger;
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' file sub-logger created and set up.", subLoggers[2]->Name());

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Add sub-loggers.");
		for (PonyEngine::Log::SubLoggerUniquePtr& subLogger : subLoggers)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Add '{}' sub-logger.", subLogger->Name());
			logger->AddSubLogger(subLogger.get());
			PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Sub-logger added.");
		}
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Sub-loggers added.");
	}

	WindowsLoggerProvider::~WindowsLoggerProvider() noexcept
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Remove sub-loggers.");
		for (PonyEngine::Log::SubLoggerUniquePtr& subLogger : subLoggers)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Remove '{}' sub-logger.", subLogger->Name());
			try
			{
				logger->RemoveSubLogger(subLogger.get());
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE_E(e, "On removing sub-logger.");
			}
			PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Sub-logger removed.");
		}
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Sub-loggers removed.");

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy sub-loggers.");
		for (PonyEngine::Log::SubLoggerUniquePtr& subLogger : subLoggers)
		{
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
}
