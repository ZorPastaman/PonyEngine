/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl:Windows.LoggerManager;

import std;

import :Console;
import :LoggerManager;

import :Windows.Console;

export namespace PonyEngine::Application::Windows
{
	class LoggerManager final : public Application::LoggerManager
	{
	public:
		[[nodiscard("Pure constuctor")]]
		LoggerManager(IApplicationContext& application, const std::shared_ptr<Log::ILogger>& defaultLogger) noexcept;
		LoggerManager(const LoggerManager&) = delete;
		LoggerManager(LoggerManager&&) = delete;

		virtual ~LoggerManager() noexcept override = default;

		virtual void LogToConsole(Log::LogType logType, std::string_view message) const noexcept override;

		LoggerManager& operator =(const LoggerManager&) = delete;
		LoggerManager& operator =(LoggerManager&&) = delete;
	};
}

namespace PonyEngine::Application::Windows
{
	LoggerManager::LoggerManager(IApplicationContext& application, const std::shared_ptr<Log::ILogger>& defaultLogger) noexcept :
		Application::LoggerManager(application, defaultLogger)
	{
	}

	void LoggerManager::LogToConsole(const Log::LogType logType, const std::string_view message) const noexcept
	{
		Application::LogToConsole(logType, message);
		LogToOutputDebugString(message);
	}
}
