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

import PonyEngine.Input;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(HandleTests)
	{
		TEST_METHOD(HandleHashTest)
		{
			constexpr std::size_t id = 125;
			const auto handle = PonyEngine::Input::Handle{.id = id};
			Assert::AreEqual(id, PonyEngine::Input::HandleHash()(handle));
		}
	};
}
