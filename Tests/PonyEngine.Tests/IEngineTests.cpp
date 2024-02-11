/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyEngine.Core;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PonyEngineTests
{
	TEST_CLASS(IEngineTests)
	{
		TEST_METHOD(FrameCountTest)
		{
			PonyEngine::Core::IEngine* engine = PonyEngine::Core::CreateEngine();

			for (size_t i = 0; i < 100; ++i)
			{
				Assert::AreEqual(i, engine->GetFrameCount());
				engine->Tick();
				Assert::AreEqual(i + 1, engine->GetFrameCount());
			}

			PonyEngine::Core::DestroyEngine(engine);
		}
	};
}
