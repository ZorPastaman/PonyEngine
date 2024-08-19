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

export module LogHelper:FileSubLoggerHelper;

import <filesystem>;
import <stdexcept>;

import PonyEngine.Log.Implementation;

export namespace LogHelper
{
	/// @brief Creates a file sub-logger.
	///	@param logPath Log file path.
	///	@return Created file sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::FileSubLoggerData CreateFileSubLogger(const std::filesystem::path& logPath);
	/// @brief Creates and sets up a file sub-logger.
	///	@return Created and set up file sub-logger.
	[[nodiscard("Pure function")]]
	PonyEngine::Log::FileSubLoggerData CreateAndSetupFileSubLogger();
}

namespace LogHelper
{
	PonyEngine::Log::FileSubLoggerData CreateFileSubLogger(const std::filesystem::path& logPath)
	{
		PonyEngine::Log::FileSubLoggerData fileSubLoggerData = PonyEngine::Log::CreateFileSubLogger(logPath);
		if (!fileSubLoggerData.subLogger)
		{
			throw std::logic_error("The file sub-logger is nullptr.");
		}

		return fileSubLoggerData;
	}

	PonyEngine::Log::FileSubLoggerData CreateAndSetupFileSubLogger()
	{
		const std::filesystem::path logPath = "Log.log";

		PONY_CONSOLE(PonyEngine::Log::LogType::Debug, "Create file sub-logger.");
		PonyEngine::Log::FileSubLoggerData fileSubLoggerData = CreateFileSubLogger(logPath);
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "'{}' file sub-logger created.", fileSubLoggerData.subLogger->Name());

		return fileSubLoggerData;
	}
}
