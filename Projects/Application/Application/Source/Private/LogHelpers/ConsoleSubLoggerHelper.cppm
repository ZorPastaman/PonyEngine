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

export module LogHelpers:ConsoleSubLoggerHelper;

import <stdexcept>;

import PonyEngine.Log.Implementation;

export namespace LogHelpers
{
	/// @brief Creates a console sub-logger.
	/// @param params Console sub-logger parameters.
	///	@return Created console sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::ConsoleSubLoggerData CreateConsoleSubLogger(const PonyEngine::Log::ConsoleSubLoggerParams& params);
	/// @brief Creates and sets up a console sub-logger.
	///	@return Created and set up console sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::ConsoleSubLoggerData CreateAndSetupConsoleSubLogger();

	/// @brief Creates a console sub-logger parameters.
	/// @return Created console sub-logger parameters.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::ConsoleSubLoggerParams CreateConsoleSubLoggerParams();
}

namespace LogHelpers
{
	PonyEngine::Log::ConsoleSubLoggerData CreateConsoleSubLogger(const PonyEngine::Log::ConsoleSubLoggerParams& params)
	{
		PonyEngine::Log::ConsoleSubLoggerData consoleSubLoggerData = PonyEngine::Log::CreateConsoleSubLogger(params);
		if (!consoleSubLoggerData.subLogger)
		{
			throw std::logic_error("The console sub-logger is nullptr.");
		}

		return consoleSubLoggerData;
	}

	PonyEngine::Log::ConsoleSubLoggerData CreateAndSetupConsoleSubLogger()
	{
		const PonyEngine::Log::ConsoleSubLoggerParams params = CreateConsoleSubLoggerParams();

		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Create console sub-logger.");
		PonyEngine::Log::ConsoleSubLoggerData consoleSubLoggerData = LogHelpers::CreateConsoleSubLogger(params);
		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "'{}' console sub-logger created.", consoleSubLoggerData.subLogger->Name());

		return consoleSubLoggerData;
	}

	PonyEngine::Log::ConsoleSubLoggerParams CreateConsoleSubLoggerParams()
	{
		return PonyEngine::Log::ConsoleSubLoggerParams{};
	}
}
