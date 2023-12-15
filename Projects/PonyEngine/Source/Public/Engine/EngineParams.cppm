/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.EngineParams;

import <vector>;

import PonyEngine.Debug.ILogger;
import PonyEngine.Debug.ILoggerEntryView;
import PonyEngine.Factories.IEngineFeatureFactory;

namespace PonyEngine
{
	export struct EngineParams final
	{
	public:
		std::vector<Debug::ILoggerEntryView*> loggerEntryViews;
		Factories::IEngineFeatureFactory<Debug::ILogger>* loggerFactory = nullptr;
		bool addStandardOutputLoggerEntry = true;
	};
}
