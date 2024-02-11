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
	TEST_CLASS(EngineFactoryTests)
	{
		TEST_METHOD(CreateEngineTest)
		{
			auto engine = PonyEngine::Core::CreateEngine();
			Assert::IsNotNull(engine);
			PonyEngine::Core::DestroyEngine(engine);

			PonyEngine::Core::EngineParams params;
			engine = PonyEngine::Core::CreateEngine(params);
			Assert::IsNotNull(engine);
			PonyEngine::Core::DestroyEngine(engine);
		}
	};
}
