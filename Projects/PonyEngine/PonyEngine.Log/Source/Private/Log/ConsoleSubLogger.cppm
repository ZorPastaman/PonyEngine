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

export module PonyEngine.Log.Implementation:ConsoleSubLogger;

import <exception>;

import PonyEngine.Log;

export namespace PonyEngine::Log
{
	/// @brief Sub-logger that sends logs to std::cout, std::clog and std::cerr.
	class ConsoleSubLogger final : public ISubLogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		ConsoleSubLogger() noexcept = default;
		ConsoleSubLogger(const ConsoleSubLogger&) = delete;
		ConsoleSubLogger(ConsoleSubLogger&&) = delete;

		~ConsoleSubLogger() noexcept = default;

		virtual void Log(const LogEntry& logEntry) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		ConsoleSubLogger& operator =(const ConsoleSubLogger&) = delete;
		ConsoleSubLogger& operator =(ConsoleSubLogger&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Log::ConsoleSubLogger"; ///< Class name.
	};
}

namespace PonyEngine::Log
{
	void ConsoleSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			ChooseConsoleStream(logEntry.GetLogType()) << logEntry;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On writing to a console.");
		}
	}

	const char* ConsoleSubLogger::GetName() const noexcept
	{
		return StaticName;
	}
}
