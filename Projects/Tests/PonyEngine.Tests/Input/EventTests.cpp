/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyEngine.Input;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(EventTests)
	{
		TEST_METHOD(ConstructorTest)
		{
			auto message = PonyEngine::Input::KeyboardMessage(PonyEngine::Input::KeyboardKeyCode::B, true);
			auto event = PonyEngine::Input::Event(message);
			Assert::IsTrue(message == event.ExpectedMessage());

			const auto copiedEvent = event;
			Assert::IsTrue(message == copiedEvent.ExpectedMessage());

			auto movedEvent = std::move(event);
			Assert::IsTrue(message == movedEvent.ExpectedMessage());
		}

		TEST_METHOD(AssignmentTest)
		{
			auto message = PonyEngine::Input::KeyboardMessage(PonyEngine::Input::KeyboardKeyCode::F, false);
			auto event = PonyEngine::Input::Event(message);

			auto otherMessage = PonyEngine::Input::KeyboardMessage(PonyEngine::Input::KeyboardKeyCode::G, true);
			auto copiedEvent = PonyEngine::Input::Event(otherMessage);
			copiedEvent = event;
			Assert::IsTrue(message == copiedEvent.ExpectedMessage());

			auto movedEvent = PonyEngine::Input::Event(otherMessage);
			movedEvent = std::move(event);
			Assert::IsTrue(message == movedEvent.ExpectedMessage());
		}
	};
}
