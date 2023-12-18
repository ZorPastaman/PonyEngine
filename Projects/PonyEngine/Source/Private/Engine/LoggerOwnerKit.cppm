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
		std::vector<Debug::ILoggerEntry*> loggerEntries;
		Debug::ILogger* logger = nullptr;
	};
}
