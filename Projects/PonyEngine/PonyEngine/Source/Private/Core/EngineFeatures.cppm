/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:EngineFeatures;

import <cassert>;
import <functional>;

import PonyEngine.Core;
import PonyEngine.Debug.Log.Implementation;

import :LoggerOwnerKit;

namespace PonyEngine::Core
{
	/// @brief Creates a logger and its sub-loggers.
	/// @param params Logger parameters.
	/// @param engine Engine that is an owner of the created logger.
	/// @return Struct that holds pointers to a created logger and its sub-loggers.
	export [[nodiscard("Pure function")]] 
	LoggerOwnerKit CreateLogger(const LoggerParams& params, const IEngine& engine);

	LoggerOwnerKit CreateLogger(const LoggerParams& params, const IEngine& engine)
	{
		LoggerOwnerKit answer;
		answer.logger = Debug::Log::CreateLogger(std::bind(&IEngine::GetFrameCount, &engine));

		if (params.addConsoleSubLogger)
		{
			Debug::Log::ISubLogger* const consoleSubLogger = Debug::Log::CreateConsoleSubLogger();
			answer.subLoggers.push_back(consoleSubLogger);
			answer.logger->AddSubLogger(consoleSubLogger);
		}

		if (params.addLogFileSubLogger)
		{
			Debug::Log::ISubLogger* const fileSubLogger = Debug::Log::CreateFileSubLogger(params.logFilePath);
			answer.subLoggers.push_back(fileSubLogger);
			answer.logger->AddSubLogger(fileSubLogger);
		}

		for (Debug::Log::ISubLogger* const subLogger : params.subLoggers)
		{
			assert((subLogger != nullptr));
			answer.logger->AddSubLogger(subLogger);
		}

		return answer;
	}
}
