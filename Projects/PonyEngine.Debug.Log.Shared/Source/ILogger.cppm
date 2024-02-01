/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.ILogger;

import <string>;

import PonyEngine.Debug.Log.ISubLogger;
import PonyEngine.Debug.Log.LogType;

namespace PonyEngine::Debug::Log
{
	export class ILogger
	{
	public:
		virtual void Log(LogType logType, const std::string& message) noexcept = 0;

		virtual void AddSubLogger(ISubLogger* subLogger) = 0;
		virtual void RemoveSubLogger(ISubLogger* subLogger) = 0;
	};
}
