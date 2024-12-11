/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <functional>

import PonyEngine.Input;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(ActionConversionTests)
	{
		TEST_METHOD(FloatToBoolTest)
		{
			bool value = false;
			std::function<void(float)> floatToBool = PonyEngine::Input::FloatToBoolAction([&](const bool val) { value = val; });
			floatToBool(0.f);
			Assert::IsFalse(value);

			floatToBool(0.3f);
			Assert::IsTrue(value);

			floatToBool(-0.1f);
			Assert::IsFalse(value);

			floatToBool(-0.3f);
			Assert::IsTrue(value);

			floatToBool(0.2f);
			Assert::IsFalse(value);

			floatToBool = PonyEngine::Input::FloatToBoolAction([&](const bool val) { value = val; }, 1.f, PonyEngine::Input::ComparisonMode::Less);
			floatToBool(0.7f);
			Assert::IsTrue(value);
			floatToBool(1.f);
			Assert::IsFalse(value);
			floatToBool(1.f);
			Assert::IsFalse(value);

			floatToBool = PonyEngine::Input::FloatToBoolAction([&](const bool val) { value = val; }, 2.f, PonyEngine::Input::ComparisonMode::LessOrEqual);
			floatToBool(1.7f);
			Assert::IsTrue(value);
			floatToBool(2.2f);
			Assert::IsFalse(value);
			floatToBool(2.f);
			Assert::IsTrue(value);

			floatToBool = PonyEngine::Input::FloatToBoolAction([&](const bool val) { value = val; }, 2.f, PonyEngine::Input::ComparisonMode::GreaterOrEqual);
			floatToBool(1.7f);
			Assert::IsFalse(value);
			floatToBool(2.2f);
			Assert::IsTrue(value);
			floatToBool(2.f);
			Assert::IsTrue(value);
		}

		TEST_METHOD(BoolToEventTest)
		{
			bool value = false;
			std::function<void(bool)> boolToEvent = PonyEngine::Input::BoolToEventAction([&] { value = true; });
			boolToEvent(true);
			Assert::IsTrue(value);
			value = false;
			boolToEvent(false);
			Assert::IsFalse(value);

			boolToEvent = PonyEngine::Input::BoolToEventAction([&] { value = true; }, false);
			boolToEvent(false);
			Assert::IsTrue(value);
			value = false;
			boolToEvent(true);
			Assert::IsFalse(value);
		}
	};
}
