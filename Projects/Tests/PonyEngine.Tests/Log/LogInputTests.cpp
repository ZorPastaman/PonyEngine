/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cstddef>;

import PonyEngine.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LogInputTests)
	{
	public:
		TEST_METHOD(ConstructorTest)
		{
			const auto message = "Message.";
			constexpr std::size_t frame = 106850;

			const auto logInput = PonyEngine::Log::LogInput(message, frame);
			Assert::AreEqual(message, logInput.GetMessage());
			Assert::AreEqual(frame, logInput.GetFrameCount());
		}
	};
}
