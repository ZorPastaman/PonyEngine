/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module EngineLoop;

import PonyEngine.Core;
import PonyEngine.Core.Implementation;

import :EngineParams;
import :Game;

namespace Game
{
	static PonyEngine::Core::IEngine* CreateEngine()
	{
		PonyEngine::Core::EngineParams engineParams = GetEngineParams();
		return PonyEngine::Core::CreateEngine(engineParams);
	}

	static void DestroyEngine(PonyEngine::Core::IEngine* engine)
	{
		PonyEngine::Core::DestroyEngine(engine);
	}

	export int EngineLoop()
	{
		PonyEngine::Core::IEngine* engine = CreateEngine();

		Begin(*engine);

		while (engine->IsRunning())
		{
			PreTick(*engine);
			engine->Tick();
			PostTick(*engine);
		}

		End(*engine);

		int exitCode = engine->GetExitCode();

		Game::DestroyEngine(engine);

		return exitCode;
	}
}
