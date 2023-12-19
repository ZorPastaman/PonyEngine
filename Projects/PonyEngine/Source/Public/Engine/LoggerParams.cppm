/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.LoggerParams;

import <vector>;
import <filesystem>;

import PonyEngine.Debug.ILogger;
import PonyEngine.Debug.ILoggerEntry;
import PonyEngine.Debug.ILoggerEntryView;
import PonyEngine.Factories.IEngineFeatureFactory;

namespace PonyEngine
{
	export struct LoggerParams final
	{
	public:
		std::filesystem::path logFilePath = "Log.log";
		std::vector<Factories::IEngineFeatureFactory<Debug::ILoggerEntry>*> loggerEntryFactories;
		std::vector<Debug::ILoggerEntryView*> loggerEntryViews;
		Factories::IEngineFeatureFactory<Debug::ILogger>* loggerFactory = nullptr;
		bool addStandardOutputLoggerEntry = true;
		bool addLogFileLoggerEntry = true;
	};
}
