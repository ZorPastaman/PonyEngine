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
import PonyEngine.IEngineView;
import PonyEngine.Debug.Logger;
import PonyEngine.Debug.StandardOutputLoggerEntry;
import PonyEngine.Debug.LogFileLoggerEntry;
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
	export LoggerOwnerKit CreateLogger(const LoggerParams& params, IEngineView* const engine)
	{
		LoggerOwnerKit answer{};

		if (params.loggerFactory != nullptr)
		{
			answer.logger = params.loggerFactory->Create(engine);
			assert((answer.logger != nullptr));
		}
		else
		{
			answer.logger = new Debug::Logger(engine);
		}

		for (Factories::IEngineFeatureFactory<Debug::ILoggerEntry>* const entryFactory : params.loggerEntryFactories)
		{
			assert((entryFactory != nullptr));
			Debug::ILoggerEntry* const entry = entryFactory->Create(engine);
			assert((entry != nullptr));
			answer.loggerEntries.push_back(entry);
			answer.logger->AddLoggerEntry(entry);
		}

		for (Debug::ILoggerEntryView* const entry : params.loggerEntryViews)
		{
			assert((entry != nullptr));
			answer.logger->AddLoggerEntry(entry);
		}

		if (params.addStandardOutputLoggerEntry)
		{
			Debug::StandardOutputLoggerEntry* const standardEntry = new Debug::StandardOutputLoggerEntry();
			answer.loggerEntries.push_back(standardEntry);
			answer.logger->AddLoggerEntry(standardEntry);
		}

		if (params.addLogFileLoggerEntry)
		{
			Debug::LogFileLoggerEntry* const logEntry = new Debug::LogFileLoggerEntry(params.logFilePath);
			answer.loggerEntries.push_back(logEntry);
			answer.logger->AddLoggerEntry(logEntry);
		}

		return answer;
	}
}
