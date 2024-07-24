/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <format>;
import <ostream>;
import <string>;

import PonyEngine.Input;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(KeyboardMessageTests)
	{
		TEST_METHOD(ToStringTest)
		{
			auto keyCode = PonyEngine::Input::KeyboardKeyCode::C;
			bool isDown = true;
			auto message = PonyEngine::Input::KeyboardMessage{.keyCode = keyCode, .isDown = isDown};
			auto expectedString = std::format("(KeyCode: {}, IsDown: {})", PonyEngine::Input::ToString(keyCode), isDown);

			Assert::AreEqual(expectedString, message.ToString());

			std::ostringstream ss;
			ss << message;
			Assert::AreEqual(expectedString, ss.str());
		}
	};
}
