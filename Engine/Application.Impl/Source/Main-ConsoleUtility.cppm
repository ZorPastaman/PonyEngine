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

export module PonyEngine.Application.Impl:ConsoleUtility;

import std;

import PonyEngine.Log;

export namespace PonyEngine::Application
{
	/// @brief Log to standard console.
	/// @param logType Log type.
	/// @param message Message.
	void LogToConsole(Log::LogType logType, std::string_view message) noexcept;
}

namespace PonyEngine::Application
{
	/// @brief Chooses a console output stream by the @p logType.
	/// @param logType Log type.
	/// @return Chosen stream.
	[[nodiscard("Pure function")]]
	std::ostream& ChooseConsoleStream(Log::LogType logType) noexcept;

	void LogToConsole(const Log::LogType logType, const std::string_view message) noexcept
	{
#if PONY_ENGINE_CONSOLE_LOG
		try
		{
			ChooseConsoleStream(logType) << message;
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
#endif
	}

	std::ostream& ChooseConsoleStream(const Log::LogType logType) noexcept
	{
		switch (logType)
		{
		case Log::LogType::Verbose:
		case Log::LogType::Debug:
		case Log::LogType::Info:
			return std::cout;
		case Log::LogType::Warning:
			return std::clog;
		case Log::LogType::Error:
		case Log::LogType::Exception:
			return std::cerr;
		default: [[unlikely]]
			assert(false && "Invalid log type.");
			return std::cerr;
		}
	}
}
