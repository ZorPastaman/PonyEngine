/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.EngineFeatures;

import <vector>;

import PonyEngine.EngineParams;
import PonyEngine.IEngineView;
import PonyEngine.Debug.ILogger;
import PonyEngine.Debug.Logger;
import PonyEngine.Debug.StandardOutputLoggerEntry;
import PonyEngine.LoggerOwnerKit;
import PonyEngine.Factories.IEngineFeatureFactory;

namespace PonyEngine
{
	export LoggerOwnerKit CreateLogger(const EngineParams& params, IEngineView* const engine)
	{
		LoggerOwnerKit answer;

		// TODO: try-catch on factory
		answer.logger = params.loggerFactory != nullptr ? params.loggerFactory->Create(engine) : new Debug::Logger(engine);

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
