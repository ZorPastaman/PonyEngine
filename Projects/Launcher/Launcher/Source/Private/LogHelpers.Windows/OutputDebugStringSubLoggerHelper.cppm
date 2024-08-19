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

export module LogHelper.Windows:OutputDebugStringSubLoggerHelper;

import <stdexcept>;

import PonyEngine.Log.Windows.Implementation;

export namespace LogHelper
{
	/// @brief Creates an output debug string sub-logger.
	///	@return Created output debug string sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger();
	/// @brief Creates and sets up an output debug string sub-logger.
	///	@return Created and set up output debug string sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::OutputDebugStringSubLoggerData CreateAndSetupOutputDebugStringSubLogger();
}

namespace LogHelper
{
	PonyEngine::Log::OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger()
	{
		PonyEngine::Log::OutputDebugStringSubLoggerData outputDebugStringSubLoggerData = PonyEngine::Log::CreateOutputDebugStringSubLogger();
		if (!outputDebugStringSubLoggerData.subLogger)
		{
			throw std::logic_error("The output debug string sub-logger is nullptr.");
		}

		return outputDebugStringSubLoggerData;
	}

	PonyEngine::Log::OutputDebugStringSubLoggerData CreateAndSetupOutputDebugStringSubLogger()
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Create Windows output debug string sub-logger.");
		PonyEngine::Log::OutputDebugStringSubLoggerData outputDebugStringSubLoggerData = CreateOutputDebugStringSubLogger();
		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "'{}' output debug string sub-logger created.", outputDebugStringSubLoggerData.subLogger->Name());

		return outputDebugStringSubLoggerData;
	}
}
