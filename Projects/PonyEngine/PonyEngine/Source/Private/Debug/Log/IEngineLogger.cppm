/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.Implementation:IEngineLogger;

import PonyEngine.Debug.Log;

namespace PonyEngine::Debug::Log
{
	/// @brief Logger used by the engine.
	export class IEngineLogger : public ILogger
	{
	public:
		inline virtual ~IEngineLogger() noexcept = default;
	};
}
