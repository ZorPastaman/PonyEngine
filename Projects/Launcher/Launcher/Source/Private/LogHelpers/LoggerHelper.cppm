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

export module LogHelper:LoggerHelper;

import <stdexcept>;

import PonyEngine.Log.Implementation;

export namespace LogHelper
{
	/// @brief Creates a logger.
	/// @return Created logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::LoggerData CreateLogger();
	/// @brief Creates and sets up a logger.
	/// @return Created logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::LoggerData CreateAndSetupLogger();
}

namespace LogHelper
{
	PonyEngine::Log::LoggerData CreateLogger()
	{
		PonyEngine::Log::LoggerData loggerData = PonyEngine::Log::CreateLogger();
		if (!loggerData.logger)
		{
			throw std::logic_error("The logger is nullptr.");
		}

		return loggerData;
	}

	PonyEngine::Log::LoggerData CreateAndSetupLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Create logger.");
		PonyEngine::Log::LoggerData loggerData = CreateLogger();
		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "'{}' logger created.", loggerData.logger->Name());

		return loggerData;
	}
}
