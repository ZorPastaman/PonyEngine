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

namespace PonyEngineTests
{
	TEST_CLASS(MathTests)
	{
	public:
		TEST_METHOD(CompilationTest)
		{
			auto common = PonyEngine::Math::DegToRad<float>;
			auto quaternion = PonyEngine::Math::Quaternion<float>();
			auto vector2 = PonyEngine::Math::Vector2<float>();
			auto vector3 = PonyEngine::Math::Vector3<float>();
			auto vector4 = PonyEngine::Math::Vector4<float>();
		}
	};
}
