/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.ISubLogger;

import PonyEngine.Debug.Log.LogEntry;

namespace PonyEngine::Debug::Log
{
	export class ISubLogger
	{
	public:
		virtual void Log(const LogEntry& logEntry) noexcept = 0;
	};
}
