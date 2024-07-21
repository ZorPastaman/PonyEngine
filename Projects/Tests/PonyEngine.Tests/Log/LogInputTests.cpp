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

			auto logInput = PonyEngine::Log::LogInput(message, frame);
			Assert::AreEqual(message, logInput.GetMessage());
			Assert::AreEqual(frame, logInput.GetFrameCount());

			auto copiedLogInput = logInput;
			Assert::AreEqual(message, copiedLogInput.GetMessage());
			Assert::AreEqual(frame, copiedLogInput.GetFrameCount());

			auto movedLogInput = std::move(logInput);
			Assert::AreEqual(message, movedLogInput.GetMessage());
			Assert::AreEqual(frame, movedLogInput.GetFrameCount());
		}

		TEST_METHOD(AssignmentTest)
		{
			const auto message = "New Message.";
			constexpr std::size_t frame = 10685;
			auto logInput = PonyEngine::Log::LogInput(message, frame);

			auto copiedLogInput = PonyEngine::Log::LogInput("Hey!", 23);
			copiedLogInput = logInput;
			Assert::AreEqual(message, copiedLogInput.GetMessage());
			Assert::AreEqual(frame, copiedLogInput.GetFrameCount());

			auto movedLogInput = PonyEngine::Log::LogInput("Hey!", 23);
			movedLogInput = std::move(logInput);
			Assert::AreEqual(message, movedLogInput.GetMessage());
			Assert::AreEqual(frame, movedLogInput.GetFrameCount());
		}
	};
}
