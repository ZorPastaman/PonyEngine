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

import PonyEngine.Utility;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
	TEST_CLASS(StringUtilityTests)
	{
	public:
		TEST_METHOD(ConvertWStringToStringTest)
		{
			std::string origin("Pony. Engine, Convert- String!");
			std::wstring wideOrigin(origin.cbegin(), origin.cend());

			std::string converted = PonyEngine::Utility::ConvertToString(wideOrigin);
			Assert::AreEqual(0, origin.compare(converted));
		}
	};
}
