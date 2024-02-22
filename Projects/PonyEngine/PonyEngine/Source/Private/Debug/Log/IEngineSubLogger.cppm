/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.Implementation:IEngineSubLogger;

import PonyEngine.Debug.Log;

namespace PonyEngine::Debug::Log
{
	export class IEngineSubLogger : public ISubLogger
	{
	public:
		inline virtual ~IEngineSubLogger() noexcept = default;
	};
}
