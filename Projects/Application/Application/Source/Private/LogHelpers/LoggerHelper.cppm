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

export module LogHelpers:LoggerHelper;

import <stdexcept>;

import PonyEngine.Log.Implementation;

export namespace LogHelpers
{
	/// @brief Creates a logger.
	/// @param params Logger parameters.
	/// @return Created logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::LoggerData CreateLogger(const PonyEngine::Log::LoggerParams& params);
	/// @brief Creates and sets up a logger.
	/// @return Created logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::LoggerData CreateAndSetupLogger();

	/// @brief Creates a logger parameters.
	/// @return Create logger parameters.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::LoggerParams CreateLoggerParams();
}

namespace LogHelpers
{
	PonyEngine::Log::LoggerData CreateLogger(const PonyEngine::Log::LoggerParams& params)
	{
		PonyEngine::Log::LoggerData loggerData = PonyEngine::Log::CreateLogger(params);
		if (!loggerData.logger)
		{
			throw std::logic_error("The logger is nullptr.");
		}

		return loggerData;
	}

	PonyEngine::Log::LoggerData CreateAndSetupLogger()
	{
		const PonyEngine::Log::LoggerParams params = CreateLoggerParams();

		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Create logger.");
		PonyEngine::Log::LoggerData loggerData = LogHelpers::CreateLogger(params);
		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "'{}' logger created.", loggerData.logger->Name());

		return loggerData;
	}

	PonyEngine::Log::LoggerParams CreateLoggerParams()
	{
		return PonyEngine::Log::LoggerParams{};
	}
}
