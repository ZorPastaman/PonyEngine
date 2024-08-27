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

#include "PonyEngine/Log/Log.h"

export module LogHelpers.Windows:OutputDebugStringSubLoggerHelper;

import PonyEngine.Log.Windows.Implementation;

export namespace LogHelpers
{
	/// @brief Creates an output debug string sub-logger.
	/// @param params Output debug string sub-logger parameters
	///	@return Created output debug string sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger(const PonyEngine::Log::OutputDebugStringSubLoggerParams& params);
	/// @brief Creates and sets up an output debug string sub-logger.
	///	@return Created and set up output debug string sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::OutputDebugStringSubLoggerData CreateAndSetupOutputDebugStringSubLogger();

	/// @brief Creates an output debug string sub-logger parameters.
	/// @return Created output debug string sub-logger parameters.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::OutputDebugStringSubLoggerParams CreateOutputDebugStringSubLoggerParams();
}

namespace LogHelpers
{
	PonyEngine::Log::OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger(const PonyEngine::Log::OutputDebugStringSubLoggerParams& params)
	{
		PonyEngine::Log::OutputDebugStringSubLoggerData outputDebugStringSubLoggerData = PonyEngine::Log::CreateOutputDebugStringSubLogger(params);
		assert(outputDebugStringSubLoggerData.subLogger && "The output debug string sub-logger is nullptr.");

		return outputDebugStringSubLoggerData;
	}

	PonyEngine::Log::OutputDebugStringSubLoggerData CreateAndSetupOutputDebugStringSubLogger()
	{
		const PonyEngine::Log::OutputDebugStringSubLoggerParams params = CreateOutputDebugStringSubLoggerParams();

		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Create Windows output debug string sub-logger.");
		PonyEngine::Log::OutputDebugStringSubLoggerData outputDebugStringSubLoggerData = LogHelpers::CreateOutputDebugStringSubLogger(params);
		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "'{}' output debug string sub-logger created.", outputDebugStringSubLoggerData.subLogger->Name());

		return outputDebugStringSubLoggerData;
	}

	PonyEngine::Log::OutputDebugStringSubLoggerParams CreateOutputDebugStringSubLoggerParams()
	{
		return PonyEngine::Log::OutputDebugStringSubLoggerParams{};
	}
}
