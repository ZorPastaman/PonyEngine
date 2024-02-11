/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:EngineFeatures;

import <cassert>;
import <functional>;

import PonyEngine.Debug.Log.ConsoleSubLogger;
import PonyEngine.Debug.Log.FileSubLogger;
import PonyEngine.Debug.Log.Logger;

import :IEngine;
import :LoggerParams;
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
		answer.logger = new Debug::Log::Logger(std::bind(&IEngine::GetFrameCount, &engine));

		for (Debug::Log::ISubLogger* const subLogger : params.subLoggers)
		{
			assert((subLogger != nullptr));
			answer.logger->AddSubLogger(subLogger);
		}

		if (params.addConsoleSubLogger)
		{
			Debug::Log::ConsoleSubLogger* const consoleSubLogger = new Debug::Log::ConsoleSubLogger();
			answer.subLoggers.push_back(consoleSubLogger);
			answer.logger->AddSubLogger(consoleSubLogger);
		}

		if (params.addLogFileSubLogger)
		{
			Debug::Log::FileSubLogger* const logEntry = new Debug::Log::FileSubLogger(params.logFilePath);
			answer.subLoggers.push_back(logEntry);
			answer.logger->AddSubLogger(logEntry);
		}

		return answer;
	}
}
