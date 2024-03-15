/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Debug.Log.Implementation:ConsoleSubLogger;

import <exception>;
import <iostream>;
import <stdexcept>;
import <string>;

import PonyEngine.Debug.Log;

namespace PonyEngine::Debug::Log
{
	/// @brief Sub-logger that sends logs to std::cout, std::clog and std::cerr.
	export class ConsoleSubLogger final : public ISubLogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		inline ConsoleSubLogger() noexcept = default;
		ConsoleSubLogger(const ConsoleSubLogger&) = delete;
		ConsoleSubLogger(ConsoleSubLogger&&) = delete;

		inline virtual ~ConsoleSubLogger() noexcept = default;

		[[nodiscard("Pure function")]]
		inline virtual const char* GetName() const noexcept override;

		virtual void Log(const LogEntry& logEntry) noexcept override;

		ConsoleSubLogger& operator =(const ConsoleSubLogger&) = delete;
		ConsoleSubLogger& operator =(ConsoleSubLogger&&) = delete;

		static const char* const Name; /// @brief Class name.
	};

	/// @brief Chooses a console output stream by the @p logType.
	/// @param logType Log type.
	/// @return Chosen stream.
	[[nodiscard("Pure function")]]
	static std::ostream& ChooseStream(LogType logType);

	inline const char* ConsoleSubLogger::GetName() const noexcept
	{
		return Name;
	}

	void ConsoleSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			std::ostream& stream = ChooseStream(logEntry.logType);
			stream << logEntry << std::endl;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE(LogType::Exception, std::format("{} - {}.", e.what(), "On writing to a console"));
		}
	}

	static std::ostream& ChooseStream(const LogType logType)
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

	const char* const ConsoleSubLogger::Name = "PonyEngine::Debug::Log::ConsoleSubLogger";
}
