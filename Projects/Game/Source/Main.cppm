/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <format>

export module EngineMain;

import <iostream>;
import <string>;
import <exception>;

import PonyEngine.EngineFactory;
import PonyEngine.IEngine;
import PonyEngine.Debug.Log.ILogger;
import PonyEngine.Debug.Log.LogType;

export int main(int argc, char** argv)
{
	std::cout << "Hello World!" << std::endl;
	std::cout << "Arguments:" << std::endl;

	for (int i = 0; i < argc; ++i)
	{
		std::cout << '\t' << argv[i] << std::endl;
	}

	PonyEngine::IEngine* engine = PonyEngine::CreateEngine();

	for (int i = 0; i < 10; ++i)
	{
		std::string message = std::format("Frame Count Before Tick: {}", engine->GetFrameCount());
		engine->GetLogger()->Log(PonyEngine::Debug::Log::LogType::Info, message);
		engine->GetLogger()->Log(PonyEngine::Debug::Log::LogType::Info, std::format("Tick Count: {}", i));
		engine->Tick();
		engine->GetLogger()->Log(PonyEngine::Debug::Log::LogType::Info, std::format("Frame Count After Tick: {}", engine->GetFrameCount()));
	}

	delete engine;

	return 0;
}
