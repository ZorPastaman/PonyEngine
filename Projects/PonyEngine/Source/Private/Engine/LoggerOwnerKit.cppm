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
	/// <summary>
	/// Holds pointers to a logger and its entries which lifetimes are controlled by an engine.
	/// </summary>
	export struct LoggerOwnerKit final
	{
	public:
		std::vector<Debug::ILoggerEntry*> loggerEntries;
		Debug::ILogger* logger = nullptr;
	};
}
