/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <memory>

export module PonyEngine.Application:AppLogger;

import PonyEngine.Log;

import :EmptyLogger;

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

		AppLogger& operator =(const AppLogger&) = delete;
		AppLogger& operator =(AppLogger&&) = delete;

	private:
		std::shared_ptr<Log::ILogger> logger; ///< Current logger.
	};
}

namespace PonyEngine::Application
{
	AppLogger::AppLogger() :
		logger(std::make_shared<EmptyLogger>())
	{
	}

	Log::ILogger& AppLogger::Logger() const noexcept
	{
		return *logger;
	}
}
