/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyEngine.Time;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Time
{
	TEST_CLASS(FrameTimeFrameRateConversionTests)
	{
		TEST_METHOD(ConvertTest)
		{
			Assert::AreEqual(0.f, PonyEngine::Time::ConvertFrameRateFrameTime(-2.f));
			Assert::AreEqual(0.f, PonyEngine::Time::ConvertFrameRateFrameTime(0.f));
			Assert::AreEqual(1.f / 60.f, PonyEngine::Time::ConvertFrameRateFrameTime(60.f));
		}
	};
}
