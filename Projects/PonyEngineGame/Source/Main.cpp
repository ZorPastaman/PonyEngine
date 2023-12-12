/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <iostream>

import PonyEngine.EntryPoint;
import PonyEngine.IEngine;

int main(int argc, char** argv)
{
	std::cout << "Hello World!" << std::endl;
	std::cout << "Arguments:" << std::endl;

	for (int i = 0; i < argc; ++i)
	{
		std::cout << '\t' << argv[i] << std::endl;
	}

	PonyEngine::IEngine* engine = PonyEngine::CreateEngine();

	std::cout << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		std::cout << "Frame Count Before Tick: " << engine->GetFrameCount() << std::endl;
		std::cout << "Tick Count: " << i << std::endl;
		engine->Tick();
		std::cout << "Frame Count After Tick: " << engine->GetFrameCount() << std::endl << std::endl;
	}

	delete engine;

	return 0;
}
