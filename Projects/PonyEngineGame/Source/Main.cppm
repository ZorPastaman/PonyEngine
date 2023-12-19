/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module EngineMain;

import <iostream>;
import <string>;
import <format>;
import <exception>;

import PonyEngine.EntryPoint;
import PonyEngine.IEngine;
import PonyEngine.Debug.ILoggerView;

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
		engine->GetLogger()->Log(message);
		engine->GetLogger()->Log(std::format("Tick Count: {}", i));
		engine->Tick();
		engine->GetLogger()->Log(std::format("Frame Count After Tick: {}", engine->GetFrameCount()));
	}

	delete engine;

	return 0;
}
