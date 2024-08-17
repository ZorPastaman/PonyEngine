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

import <exception>;
import <iostream>;
import <stdexcept>;

import PonyEngine.Log.Windows.Implementation;

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
		/// @brief Creates a logger.
		void CreateLogger();
		/// @brief Creates a console sub-logger.
		void CreateConsoleSubLogger();
		/// @brief Creates a Windows output debug string sub-logger.
		void CreateOutputDebugStringSubLogger();
		/// @brief Creates a file sub-logger.
		void CreateFileSubLogger();

		/// @brief Destroys the logger.
		void DestroyLogger() noexcept;
		/// @brief Destroys the console sub-logger.
		void DestroyConsoleSubLogger() noexcept;
		/// @brief Destroys a Windows output debug string sub-logger.
		void DestroyOutputDebugStringSubLogger() noexcept;
		/// @brief Destroys a file sub-logger.
		void DestroyFileSubLogger() noexcept;

		PonyEngine::Log::LoggerUniquePtr logger; ///< Logger.

		// Set all sub-loggers here.

		PonyEngine::Log::ConsoleSubLoggerUniquePtr consoleSubLogger; ///< Console sub-logger.
		PonyEngine::Log::OutputDebugStringSubLoggerUniquePtr outputDebugStringSubLogger; ///< Windows output debug string sub-logger.
		PonyEngine::Log::FileSubLoggerUniquePtr fileSubLogger; ///< File sub-logger.
	};
}

namespace Launcher
{
	WindowsLoggerProvider::WindowsLoggerProvider()
	{
		CreateLogger();

		// Create and add all sub-loggers here.
		CreateConsoleSubLogger();
		CreateOutputDebugStringSubLogger();
		CreateFileSubLogger();
	}

	WindowsLoggerProvider::~WindowsLoggerProvider() noexcept
	{
		// Remove and destroy all sub-loggers here.
		DestroyFileSubLogger();
		DestroyOutputDebugStringSubLogger();
		DestroyConsoleSubLogger();

		DestroyLogger();
	}

	PonyEngine::Log::ILogger& WindowsLoggerProvider::Logger() const noexcept
	{
		return *logger;
	}

	void WindowsLoggerProvider::CreateLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create logger.");
		logger = PonyEngine::Log::CreateLogger();
		if (!logger)
		{
			throw std::logic_error("The logger is nullptr.");
		}
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger created.");
	}

	void WindowsLoggerProvider::CreateConsoleSubLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create console sub-logger.");
		consoleSubLogger = PonyEngine::Log::CreateConsoleSubLogger();
		if (!consoleSubLogger)
		{
			throw std::logic_error("The console sub-logger is nullptr.");
		}
		logger->AddSubLogger(consoleSubLogger.get());
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Console sub-logger created.");
	}

	void WindowsLoggerProvider::CreateOutputDebugStringSubLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create Windows output debug string sub-logger.");
		outputDebugStringSubLogger = PonyEngine::Log::CreateOutputDebugStringSubLogger();
		if (!outputDebugStringSubLogger)
		{
			throw std::logic_error("The output debug string sub-logger is nullptr.");
		}
		logger->AddSubLogger(outputDebugStringSubLogger.get());
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Windows output debug string sub-logger created.");
	}

	void WindowsLoggerProvider::CreateFileSubLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create file sub-logger.");
		fileSubLogger = PonyEngine::Log::CreateFileSubLogger("Log.log");
		if (!fileSubLogger)
		{
			throw std::logic_error("The file sub-logger is nullptr.");
		}
		logger->AddSubLogger(fileSubLogger.get());
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "File sub-logger created.");
	}

	void WindowsLoggerProvider::DestroyLogger() noexcept
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy logger.");
		logger.reset();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger destroyed.");
	}

	void WindowsLoggerProvider::DestroyConsoleSubLogger() noexcept
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy console sub-logger.");
		try
		{
			logger->RemoveSubLogger(consoleSubLogger.get());
		}
		catch (std::exception& e)
		{
			PONY_CONSOLE_E(e, "On removing the console sub-logger.");
		}
		consoleSubLogger.reset();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Console sub-logger destroyed.");
	}

	void WindowsLoggerProvider::DestroyOutputDebugStringSubLogger() noexcept
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy Windows output debug string sub-logger.");
		try
		{
			logger->RemoveSubLogger(outputDebugStringSubLogger.get());
		}
		catch (std::exception& e)
		{
			PONY_CONSOLE_E(e, "On removing the Windows output debug string sub-logger.");
		}
		outputDebugStringSubLogger.reset();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Windows output debug string sub-logger destroyed.");
	}

	void WindowsLoggerProvider::DestroyFileSubLogger() noexcept
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroy file sub-logger.");
		try
		{
			logger->RemoveSubLogger(fileSubLogger.get());
		}
		catch (std::exception& e)
		{
			PONY_CONSOLE_E(e, "On removing the file sub-logger.");
		}
		fileSubLogger.reset();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "File sub-logger destroyed.");
	}
}
