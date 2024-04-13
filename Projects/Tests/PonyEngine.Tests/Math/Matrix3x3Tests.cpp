/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyEngine.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(Matrix3x3Tests)
	{
		TEST_METHOD(Test)
		{
			auto wow = PonyEngine::Math::Matrix3x3<float>()[0];
		}
	};
}
