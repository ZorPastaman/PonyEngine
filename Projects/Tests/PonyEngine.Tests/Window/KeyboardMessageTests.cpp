/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <string>;

import PonyEngine.Window;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Window
{
	TEST_CLASS(KeyboardMessageTests)
	{
		TEST_METHOD(ContructorTest)
		{
			const auto keyCode = PonyEngine::Window::KeyboardKeyCode::G;
			const bool isDown = true;
			const PonyEngine::Window::KeyboardMessage message(keyCode, isDown);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(keyCode), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(message.GetKeyCode()));
			Assert::AreEqual(isDown, message.GetIsDown());
		}

		TEST_METHOD(ToStringTest)
		{
			const auto keyCode = PonyEngine::Window::KeyboardKeyCode::G;
			const bool isDown = true;
			const PonyEngine::Window::KeyboardMessage message(keyCode, isDown);
			Assert::AreEqual("(KeyCode: G, IsDown: true)", message.ToString().c_str());
			std::ostringstream ss;
			ss << message;
			Assert::AreEqual("(KeyCode: G, IsDown: true)", ss.str().c_str());
		}
	};
}
