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

export module PonyEngine.Application:AppLogger;

import std;

import PonyEngine.Log;

import :DefaultLogger;

export namespace PonyEngine::Application
{
	/// @brief Application logger.
	class AppLogger final
	{
	public:
		[[nodiscard("Pure constructor")]]
		AppLogger();
		AppLogger(const AppLogger&) = delete;
		AppLogger(AppLogger&&) = delete;

		~AppLogger() noexcept = default;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		Log::ILogger& Logger() const noexcept;
		/// @brief Sets a new logger.
		/// @param logger Logger to set. Mustn't be nullptr.
		void Logger(const std::shared_ptr<Log::ILogger>& logger);

		AppLogger& operator =(const AppLogger&) = delete;
		AppLogger& operator =(AppLogger&&) = delete;

	private:
		std::shared_ptr<Log::ILogger> logger; ///< Current logger.
	};
}

namespace PonyEngine::Application
{
	AppLogger::AppLogger() :
		logger(std::make_shared<DefaultLogger>())
	{
	}

	Log::ILogger& AppLogger::Logger() const noexcept
	{
		return *logger;
	}

	void AppLogger::Logger(const std::shared_ptr<Log::ILogger>& logger)
	{
		if (!logger) [[unlikely]]
		{
			throw std::invalid_argument("Logger is nullptr.");
		}

		this->logger = logger;
		PONY_LOG(*this->logger, Log::LogType::Info, "Application logger changed to '{}'.", typeid(*logger).name());
	}
}
