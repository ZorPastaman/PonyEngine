/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.EngineParams;

import PonyEngine.LoggerParams;

namespace PonyEngine
{
	/// <summary>
	/// Holds parameters to set an engine.
	/// </summary>
	export struct EngineParams final
	{
	public:
		LoggerParams loggerParams;
	};
}
