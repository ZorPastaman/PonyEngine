/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.EngineFeatures;

import <cassert>;

import PonyEngine.LoggerParams;
import PonyEngine.IEngine;
import PonyEngine.Debug.Log.Logger;
import PonyEngine.Debug.Log.ConsoleSubLogger;
import PonyEngine.Debug.Log.FileSubLogger;
import PonyEngine.LoggerOwnerKit;

namespace PonyEngine
{
	/// <summary>
	/// Creates a logger and its entries.
	/// </summary>
	/// <param name="params">Logger parameters.</param>
	/// <param name="engine">Engine that is an owner of the created logger.</param>
	/// <returns>
	/// Struct that holds pointers to a created logger and its entries
	/// which lifetimes are controlled by the engine.
	/// </returns>
	export LoggerOwnerKit CreateLogger(const LoggerParams& params, const IEngine& engine)
	{
		LoggerOwnerKit answer;
		answer.logger = new Debug::Log::Logger(&engine);

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
