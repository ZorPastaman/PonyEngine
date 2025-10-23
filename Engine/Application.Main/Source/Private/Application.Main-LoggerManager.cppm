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

export module PonyEngine.Application.Main:LoggerManager;

import std;

import PonyEngine.Application.Extension;
import PonyEngine.Log;

import :DefaultLogger;

export namespace PonyEngine::Application
{
	/// @brief Logger manager.
	class LoggerManager final : private ILoggerContext, private ILoggerModuleContext
	{
	public:
		/// @brief Creates a logger manager.
		/// @param application Application context.
		/// @remark Sets a default logger as a current logger.
		[[nodiscard("Pure constructor")]]
		explicit LoggerManager(IApplicationContext& application);
		LoggerManager(const LoggerManager&) = delete;
		LoggerManager(LoggerManager&&) = delete;

		~LoggerManager() noexcept;

		[[nodiscard("Pure function")]]
		virtual IApplicationContext& Application() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IApplicationContext& Application() const noexcept override;
		virtual void LogToConsole(Log::LogType logType, std::string_view message) const noexcept override;

		[[nodiscard("Must be used to unset")]]
		virtual LoggerHandle SetLogger(const std::function<std::shared_ptr<Log::ILogger>(ILoggerContext&)>& factory) override;
		virtual void UnsetLogger(LoggerHandle handle) override;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		Log::ILogger& Logger() noexcept;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		const Log::ILogger& Logger() const noexcept;

		/// @brief Gets a public logger module context.
		/// @return Public logger module context.
		[[nodiscard("Pure function")]]
		ILoggerModuleContext& PublicLoggerModuleContext() noexcept;
		/// @brief Gets a public logger module context.
		/// @return Public logger module context.
		[[nodiscard("Pure function")]]
		const ILoggerModuleContext& PublicLoggerModuleContext() const noexcept;

		LoggerManager& operator =(const LoggerManager&) = delete;
		LoggerManager& operator =(LoggerManager&&) = delete;

	private:
		IApplicationContext* application; ///< Application context.

		std::unique_ptr<DefaultLogger> defaultLogger; ///< Default logger.
		std::shared_ptr<Log::ILogger> externalLogger; ///< External logger.
		Log::ILogger* logger; ///< Current logger.
	};
}

namespace PonyEngine::Application
{
	LoggerManager::LoggerManager(IApplicationContext& application) :
		application{&application},
		defaultLogger(std::make_unique<DefaultLogger>(*this->application)),
		logger{defaultLogger.get()}
	{
	}

	LoggerManager::~LoggerManager() noexcept
	{
		if (externalLogger) [[unlikely]]
		{
			PONY_LOG(*logger, Log::LogType::Error, "External logger wasn't removed. Logger: '{}'.", typeid(*externalLogger).name())
		}
	}

	IApplicationContext& LoggerManager::Application() noexcept
	{
		return *application;
	}

	const IApplicationContext& LoggerManager::Application() const noexcept
	{
		return *application;
	}

	void LoggerManager::LogToConsole(const Log::LogType logType, const std::string_view message) const noexcept
	{
		Application::LogToConsole(logType, message);
	}

	LoggerHandle LoggerManager::SetLogger(const std::function<std::shared_ptr<Log::ILogger>(ILoggerContext&)>& factory)
	{
		if (application->FlowState() != FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Logger can be added only on start-up.");
		}
		if (externalLogger) [[unlikely]]
		{
			throw std::logic_error("External logger has already been set.");
		}

		const std::shared_ptr<Log::ILogger> newLogger = factory(*this);
		if (!newLogger) [[unlikely]]
		{
			throw std::logic_error("Created logger is nullptr.");
		}

		externalLogger = newLogger;
		logger = externalLogger.get();
		PONY_LOG(*logger, Log::LogType::Info, "External logger set. Logger: '{}'.", typeid(*externalLogger).name());

		return LoggerHandle{.id = externalLogger.get()};
	}

	void LoggerManager::UnsetLogger(const LoggerHandle handle)
	{
		if (application->FlowState() != FlowState::StartingUp && application->FlowState() != FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Logger can be removed only on start-up or shut-down.");
		}
		if (!handle.IsValid()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid handle.");
		}
		if (!externalLogger) [[unlikely]]
		{
			throw std::logic_error("No external logger was set.");
		}
		if (externalLogger.get() != handle.id) [[unlikely]]
		{
			throw std::logic_error("Incorrect handle.");
		}

		PONY_LOG(*logger, Log::LogType::Info, "External logger unset.");
		logger = defaultLogger.get();
		externalLogger = nullptr;
	}

	Log::ILogger& LoggerManager::Logger() noexcept
	{
		return *logger;
	}

	const Log::ILogger& LoggerManager::Logger() const noexcept
	{
		return *logger;
	}

	ILoggerModuleContext& LoggerManager::PublicLoggerModuleContext() noexcept
	{
		return *this;
	}

	const ILoggerModuleContext& LoggerManager::PublicLoggerModuleContext() const noexcept
	{
		return *this;
	}
}
