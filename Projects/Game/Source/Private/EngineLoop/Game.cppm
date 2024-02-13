/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module EngineLoop:Game;

import <format>;
import <string>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;

namespace Game
{
	export void Begin(PonyEngine::Core::IEngine& engine)
	{
		// Called before first tick

		engine.GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, "Begin");
	}

	export void PreTick(PonyEngine::Core::IEngine& engine)
	{
		// Called before every tick

		engine.GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, std::format("Frame Count Before Tick: {}", engine.GetFrameCount()));
		
	}

	export void PostTick(PonyEngine::Core::IEngine& engine)
	{
		// Called after every tick

		engine.GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, std::format("Frame Count After Tick: {}", engine.GetFrameCount()));
	}

	export void End(PonyEngine::Core::IEngine& engine)
	{
		// Called after last tick

		engine.GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, "End");
	}
}
