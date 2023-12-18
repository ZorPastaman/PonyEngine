/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "CppUnitTest.h"

export module PonyEngineTests;

import PonyEngine.EntryPoint;
import PonyEngine.IEngine;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PonyEngineTests
{
	TEST_CLASS(PonyEngineTests)
	{
	public:
		TEST_METHOD(TickFrameCount)
		{
			PonyEngine::IEngine* const engine = PonyEngine::CreateEngine();

			for (size_t i = 0; i < 1000; ++i)
			{
				// Before tick
				size_t expected = i;
				size_t actual = engine->GetFrameCount();
				Assert::AreEqual(expected, actual);

				// After tick
				engine->Tick();
				++expected;
				actual = engine->GetFrameCount();
				Assert::AreEqual(expected, actual);
			}

			delete engine;
		}

		TEST_METHOD(Logger)
		{
			PonyEngine::IEngine* const engine = PonyEngine::CreateEngine();

			delete engine;
		}
	};
}
