/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.ConsoleSubLogger;

import <iostream>;
import <ostream>;
import <stdexcept>;

import PonyEngine.Debug.Log.ISubLogger;
import PonyEngine.Debug.Log.LogEntry;
import PonyEngine.Debug.Log.LogType;

namespace PonyEngine::Debug::Log
{
	/// <summary>
	/// Logger entry that sends logs to std::cout, std::clog and std::cerr.
	/// </summary>
	export class ConsoleSubLogger final : public ISubLogger
	{
	public:
		ConsoleSubLogger() noexcept = default;
		ConsoleSubLogger(const ConsoleSubLogger&) = delete;
		ConsoleSubLogger(ConsoleSubLogger&&) = delete;

		virtual ~ConsoleSubLogger() noexcept = default;

		virtual void Log(const LogEntry& logEntry) noexcept override;
	};

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
			throw std::invalid_argument("logType is an incorrect value.");
		}
	}

	void ConsoleSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			std::ostream& stream = ChooseStream(logEntry.logType);
			stream << logEntry.message << std::endl;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << " on writing to a console.";
		}
	}
}
