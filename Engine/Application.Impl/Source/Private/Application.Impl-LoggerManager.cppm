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

export module PonyEngine.Application.Impl:LoggerManager;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;

export namespace PonyEngine::Application
{
	/// @brief Logger manager.
	class LoggerManager : private ILoggerContext, private ILoggerModuleContext
	{
	public:
		LoggerManager(const LoggerManager&) = delete;
		LoggerManager(LoggerManager&&) = delete;

		virtual ~LoggerManager() noexcept;

		[[nodiscard("Pure function")]]
		virtual IApplicationContext& Application() noexcept override final;
		[[nodiscard("Pure function")]]
		virtual const IApplicationContext& Application() const noexcept override final;

		[[nodiscard("Must be used to unset")]]
		virtual LoggerHandle SetLogger(const std::function<std::shared_ptr<Log::ILogger>(ILoggerContext&)>& factory) override final;
		virtual void UnsetLogger(LoggerHandle handle) override final;

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

	protected:
		/// @brief Creates a logger manager.
		/// @param application Application context.
		/// @param defaultLogger Default logger.
		/// @remark Sets a default logger as a current logger.
		[[nodiscard("Pure constructor")]]
		LoggerManager(IApplicationContext& application, const std::shared_ptr<Log::ILogger>& defaultLogger) noexcept;

	private:
		IApplicationContext* application; ///< Application context.

		std::shared_ptr<Log::ILogger> defaultLogger; ///< Default logger.
		std::shared_ptr<Log::ILogger> externalLogger; ///< External logger.
		Log::ILogger* logger; ///< Current logger.

		LoggerHandle nextHandle; ///< Next logger handle.
		LoggerHandle currentHandle; ///< Current logger handle.
	};
}

namespace PonyEngine::Application
{
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

	LoggerHandle LoggerManager::SetLogger(const std::function<std::shared_ptr<Log::ILogger>(ILoggerContext&)>& factory)
	{
		if (!nextHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more logger handles available.");
		}

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
		PONY_LOG(*logger, Log::LogType::Info, "External logger set. Logger: '{}'; Handle: '0x{:X}'.", typeid(*externalLogger).name(), currentHandle.id);

		currentHandle = nextHandle;
		++nextHandle.id;

		return currentHandle;
	}

	void LoggerManager::UnsetLogger(const LoggerHandle handle)
	{
		if (application->FlowState() != FlowState::StartingUp && application->FlowState() != FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Logger can be removed only on start-up or shut-down.");
		}
		if (!externalLogger) [[unlikely]]
		{
			throw std::logic_error("No external logger was set.");
		}
		if (currentHandle != handle) [[unlikely]]
		{
			throw std::logic_error("Incorrect handle.");
		}

		PONY_LOG(*logger, Log::LogType::Info, "External logger unset. Logger: '{}'; Handle: '0x{:X}'.", typeid(*externalLogger).name(), handle.id);
		logger = defaultLogger.get();
		currentHandle.id = 0u;
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

	LoggerManager::LoggerManager(IApplicationContext& application, const std::shared_ptr<Log::ILogger>& defaultLogger) noexcept :
		application{&application},
		defaultLogger(defaultLogger),
		logger{defaultLogger.get()},
		nextHandle{.id = 1u},
		currentHandle{.id = 0u}
	{
		assert(this->defaultLogger && "The default logger is nullptr.");
	}
}
