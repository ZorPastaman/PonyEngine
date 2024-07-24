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

import <format>;
import <exception>;
import <iostream>;
import <stdexcept>;
import <string>;

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
	/// @brief Chooses a console output stream by the @p logType.
	/// @param logType Log type.
	/// @return Chosen stream.
	[[nodiscard("Pure function")]]
	std::ostream& ChooseStream(LogType logType);

	void ConsoleSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			std::ostream& stream = ChooseStream(logEntry.GetLogType());
			stream << logEntry << std::endl;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE(LogType::Exception, std::format("{} - On writing to a console.", e.what()));
		}
	}

	const char* ConsoleSubLogger::GetName() const noexcept
	{
		return StaticName;
	}

	std::ostream& ChooseStream(const LogType logType)
	{
		switch (logType)
		{
		case LogType::Verbose:
		case LogType::Debug:
		case LogType::Info:
			return std::cout;
		case LogType::Warning:
			return std::clog;
		case LogType::Error:
		case LogType::Exception:
			return std::cerr;
		default:
			throw std::invalid_argument("logType has an incorrect value.");
		}
	}
}
