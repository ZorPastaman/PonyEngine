/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl:Windows.DefaultLogger;

import :Console;
import :DefaultLogger;

import :Windows.Console;

export namespace PonyEngine::Application::Windows
{
	/// @brief Windows default logger. It logs to a standard console and output debug string.
	class DefaultLogger final : public Application::DefaultLogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		DefaultLogger() noexcept = default;
		DefaultLogger(const DefaultLogger&) = delete;
		DefaultLogger(DefaultLogger&&) = delete;

		virtual ~DefaultLogger() noexcept override = default;

		DefaultLogger operator =(const DefaultLogger&) = delete;
		DefaultLogger operator =(DefaultLogger&&) = delete;

	protected:
		virtual void LogToConsole(Log::LogType logType, std::string_view message) const noexcept override;
	};
}

namespace PonyEngine::Application::Windows
{
	void DefaultLogger::LogToConsole(const Log::LogType logType, const std::string_view message) const noexcept
	{
		Application::LogToConsole(logType, message);
		LogToOutputDebugString(message);
	}
}
