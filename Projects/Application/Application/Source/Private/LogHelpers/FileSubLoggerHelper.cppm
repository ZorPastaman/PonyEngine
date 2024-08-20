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

export module LogHelpers:FileSubLoggerHelper;

import <filesystem>;
import <stdexcept>;

import PonyEngine.Log.Implementation;
import PonyEngine.StringUtility;

export namespace LogHelpers
{
	/// @brief Creates a file sub-logger.
	///	@param params File sub-logger parameters.
	///	@return Created file sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::FileSubLoggerData CreateFileSubLogger(const PonyEngine::Log::FileSubLoggerParams& params);
	/// @brief Creates and sets up a file sub-logger.
	///	@return Created and set up file sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::FileSubLoggerData CreateAndSetupFileSubLogger();

	/// @brief Creates a file sub-logger parameters.
	/// @return Created file sub-logger parameters.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::FileSubLoggerParams CreateFileSubLoggerParams();
}

namespace LogHelpers
{
	PonyEngine::Log::FileSubLoggerData CreateFileSubLogger(const PonyEngine::Log::FileSubLoggerParams& params)
	{
		PonyEngine::Log::FileSubLoggerData fileSubLoggerData = PonyEngine::Log::CreateFileSubLogger(params);
		if (!fileSubLoggerData.subLogger)
		{
			throw std::logic_error("The file sub-logger is nullptr.");
		}

		return fileSubLoggerData;
	}

	PonyEngine::Log::FileSubLoggerData CreateAndSetupFileSubLogger()
	{
		const PonyEngine::Log::FileSubLoggerParams params = CreateFileSubLoggerParams();

		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Create file sub-logger. Log file path: '{}'.", PonyEngine::Utility::ConvertToString(params.logPath.c_str()));
		PonyEngine::Log::FileSubLoggerData fileSubLoggerData = LogHelpers::CreateFileSubLogger(params);
		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "'{}' file sub-logger created.", fileSubLoggerData.subLogger->Name());

		return fileSubLoggerData;
	}

	PonyEngine::Log::FileSubLoggerParams CreateFileSubLoggerParams()
	{
		return PonyEngine::Log::FileSubLoggerParams{.logPath = "Log.log"};
	}
}
