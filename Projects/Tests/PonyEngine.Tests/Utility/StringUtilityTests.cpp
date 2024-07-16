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

import PonyEngine.StringUtility;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
	TEST_CLASS(StringUtilityTests)
	{
	public:
		TEST_METHOD(ConvertWStringToStringTest)
		{
			const auto origin = std::string("Pony. Engine, Convert- String!");
			const auto wideOrigin = std::wstring(origin.cbegin(), origin.cend());

			const std::string converted = PonyEngine::Utility::ConvertToString(wideOrigin);
			Assert::AreEqual(0, origin.compare(converted));
		}
	};
}
