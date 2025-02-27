/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <vector>

import PonyBase.Utility;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
	TEST_CLASS(ContainerTests)
	{
		TEST_METHOD(MoveTest)
		{
			auto vector = std::vector<int> { -2, 5, 6, -8};

			PonyBase::Utility::Move(vector, 2, 2);
			Assert::AreEqual(-2, vector[0]);
			Assert::AreEqual(5, vector[1]);
			Assert::AreEqual(6, vector[2]);
			Assert::AreEqual(-8, vector[3]);

			PonyBase::Utility::Move(vector, 3, 1);
			Assert::AreEqual(-2, vector[0]);
			Assert::AreEqual(-8, vector[1]);
			Assert::AreEqual(5, vector[2]);
			Assert::AreEqual(6, vector[3]);

			PonyBase::Utility::Move(vector, 0, 2);
			Assert::AreEqual(-8, vector[0]);
			Assert::AreEqual(5, vector[1]);
			Assert::AreEqual(-2, vector[2]);
			Assert::AreEqual(6, vector[3]);
		}
	};
}
