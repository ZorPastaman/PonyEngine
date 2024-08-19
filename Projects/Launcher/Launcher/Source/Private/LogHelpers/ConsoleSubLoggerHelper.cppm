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

export module LogHelper:ConsoleSubLoggerHelper;

import <stdexcept>;

import PonyEngine.Log.Implementation;

export namespace LogHelper
{
	/// @brief Creates a console sub-logger.
	///	@return Created console sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::ConsoleSubLoggerData CreateConsoleSubLogger();
	/// @brief Creates and sets up a console sub-logger.
	///	@return Created and set up console sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::ConsoleSubLoggerData CreateAndSetupConsoleSubLogger();
}

namespace LogHelper
{
	PonyEngine::Log::ConsoleSubLoggerData CreateConsoleSubLogger()
	{
		PonyEngine::Log::ConsoleSubLoggerData consoleSubLoggerData = PonyEngine::Log::CreateConsoleSubLogger();
		if (!consoleSubLoggerData.subLogger)
		{
			throw std::logic_error("The console sub-logger is nullptr.");
		}

		return consoleSubLoggerData;
	}

	PonyEngine::Log::ConsoleSubLoggerData CreateAndSetupConsoleSubLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Create console sub-logger.");
		PonyEngine::Log::ConsoleSubLoggerData consoleSubLoggerData = CreateConsoleSubLogger();
		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "'{}' console sub-logger created.", consoleSubLoggerData.subLogger->Name());

		return consoleSubLoggerData;
	}
}
