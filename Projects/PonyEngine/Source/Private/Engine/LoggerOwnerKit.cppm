/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.LoggerOwnerKit;

import <vector>;

import PonyEngine.Debug.ILogger;
import PonyEngine.Debug.ILoggerEntry;

namespace PonyEngine
{
	export struct LoggerOwnerKit final
	{
	public:
		Debug::ILogger* logger = nullptr;
		std::vector<Debug::ILoggerEntry*> loggerEntries;
	};
}
