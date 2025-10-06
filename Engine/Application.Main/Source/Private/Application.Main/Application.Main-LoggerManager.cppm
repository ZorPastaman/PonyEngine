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

import PonyEngine.Application;
import PonyEngine.Log;

import :DefaultLogger;

export namespace PonyEngine::Application
{
	/// @brief Logger manager.
	class LoggerManager final
	{
	public:
		/// @brief Creates a logger manager.
		/// @param application Application context.
		/// @remark Sets a default logger as a current logger.
		[[nodiscard("Pure constructor")]]
		explicit LoggerManager(IApplicationContext& application);
		LoggerManager(const LoggerManager&) = delete;
		LoggerManager(LoggerManager&&) = delete;

		~LoggerManager() noexcept = default;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		Log::ILogger& Logger() noexcept;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		const Log::ILogger& Logger() const noexcept;

		/// @brief Sets the logger.
		/// @param logger Logger. If nullptr, sets a default logger.
		void Logger(Log::ILogger* logger) noexcept;

		LoggerManager& operator =(const LoggerManager&) = delete;
		LoggerManager& operator =(LoggerManager&&) = delete;

	private:
		IApplicationContext* application; ///< Application context.

		std::unique_ptr<DefaultLogger> defaultLogger; ///< Default logger.
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

	Log::ILogger& LoggerManager::Logger() noexcept
	{
		return *logger;
	}

	const Log::ILogger& LoggerManager::Logger() const noexcept
	{
		return *logger;
	}

	void LoggerManager::Logger(Log::ILogger* const logger) noexcept
	{
		Log::ILogger* const nextLogger = logger ? logger : defaultLogger.get();
		PONY_LOG(*this->logger, Log::LogType::Info, "Setting '{}' logger...", typeid(*nextLogger).name());
		this->logger = nextLogger;
		PONY_LOG(*this->logger, Log::LogType::Info, "Setting '{}' logger done.", typeid(*nextLogger).name());
	}
}
