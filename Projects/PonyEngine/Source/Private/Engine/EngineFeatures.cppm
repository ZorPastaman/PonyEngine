/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.EngineFeatures;

import PonyEngine.LoggerParams;
import PonyEngine.IEngineView;
import PonyEngine.Debug.Logger;
import PonyEngine.Debug.StandardOutputLoggerEntry;
import PonyEngine.LoggerOwnerKit;

namespace PonyEngine
{
	export LoggerOwnerKit CreateLogger(const LoggerParams& params, IEngineView* const engine)
	{
		LoggerOwnerKit answer;

		answer.logger = params.loggerFactory != nullptr ? params.loggerFactory->Create(engine) : new Debug::Logger(engine);

		for (Factories::IEngineFeatureFactory<Debug::ILoggerEntry>* const entryFactory : params.loggerEntryFactories)
		{
			Debug::ILoggerEntry* const entry = entryFactory->Create(engine);
			answer.loggerEntries.push_back(entry);
			answer.logger->AddLoggerEntry(entry);
		}

		for (Debug::ILoggerEntryView* const entry : params.loggerEntryViews)
		{
			answer.logger->AddLoggerEntry(entry);
		}

		if (params.addStandardOutputLoggerEntry)
		{
			Debug::StandardOutputLoggerEntry* const standardEntry = new Debug::StandardOutputLoggerEntry();
			answer.loggerEntries.push_back(standardEntry);
			answer.logger->AddLoggerEntry(standardEntry);
		}

		return answer;
	}
}
