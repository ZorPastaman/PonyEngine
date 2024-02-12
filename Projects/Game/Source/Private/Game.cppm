/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Game;

import <format>;
import <iostream>;
import <memory>;
import <string>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;

namespace Game
{
	export int GameMain()
	{
		PonyEngine::Core::EngineParams engineParams;
		engineParams.loggerParams.addConsoleSubLogger = true;
		auto engine = std::unique_ptr<PonyEngine::Core::IEngine, void(*)(PonyEngine::Core::IEngine*)>(PonyEngine::Core::CreateEngine(engineParams), &PonyEngine::Core::DestroyEngine);

		for (int i = 0; i < 10; ++i)
		{
			std::string message = std::format("Frame Count Before Tick: {}", engine->GetFrameCount());
			engine->GetLogger()->Log(PonyEngine::Debug::Log::LogType::Info, message);
			engine->GetLogger()->Log(PonyEngine::Debug::Log::LogType::Info, std::format("Tick Count: {}", i));
			engine->Tick();
			engine->GetLogger()->Log(PonyEngine::Debug::Log::LogType::Info, std::format("Frame Count After Tick: {}", engine->GetFrameCount()));
		}

		return 0;
	}
}
