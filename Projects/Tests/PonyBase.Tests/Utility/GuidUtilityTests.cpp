/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <string>

#include "PonyBase/Core/COM/Framework.h"

import PonyBase.GuidUtility;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
	TEST_CLASS(GuidUtilityTests)
	{
		TEST_METHOD(ToStringTest)
		{
			auto guid = GUID{.Data1 = 0xD2DF2879, .Data2 = 0xB16A, .Data3 = 0xBABA};
			*reinterpret_cast<std::uint64_t*>(guid.Data4) = 0x6517BB1B6D4D;

			Assert::AreEqual("D2DF2879-B16A-BABA-6517BB1B6D4D", PonyBase::Utility::ToString(guid).c_str());
		}
	};
}
