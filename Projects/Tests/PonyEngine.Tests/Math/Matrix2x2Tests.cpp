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
	TEST_CLASS(Matrix2x2Tests)
	{
		TEST_METHOD(ConstructorTest)
		{
			auto defaultMatrixF = PonyEngine::Math::Matrix2x2<float>();
			Assert::AreEqual(float{}, defaultMatrixF.M00());
			Assert::AreEqual(float{}, defaultMatrixF.M10());
			Assert::AreEqual(float{}, defaultMatrixF.M01());
			Assert::AreEqual(float{}, defaultMatrixF.M11());

			float m00F = 4.f;
			float m10F = -3.f;
			float m01F = 6.f;
			float m11F = 5.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			Assert::AreEqual(m00F, matrixF.M00());
			Assert::AreEqual(m10F, matrixF.M10());
			Assert::AreEqual(m01F, matrixF.M01());
			Assert::AreEqual(m11F, matrixF.M11());

			auto copiedMatrixF = matrixF;
			Assert::AreEqual(m00F, copiedMatrixF.M00());
			Assert::AreEqual(m10F, copiedMatrixF.M10());
			Assert::AreEqual(m01F, copiedMatrixF.M01());
			Assert::AreEqual(m11F, copiedMatrixF.M11());

			auto column0F = PonyEngine::Math::Vector2<float>(m00F, m10F);
			auto column1F = PonyEngine::Math::Vector2<float>(m01F, m11F);
			auto vectorMatrixF = PonyEngine::Math::Matrix2x2<float>(column0F, column1F);
			Assert::AreEqual(m00F, vectorMatrixF.M00());
			Assert::AreEqual(m10F, vectorMatrixF.M10());
			Assert::AreEqual(m01F, vectorMatrixF.M01());
			Assert::AreEqual(m11F, vectorMatrixF.M11());

			auto defaultMatrixI = PonyEngine::Math::Matrix2x2<short>();
			Assert::AreEqual(short{}, defaultMatrixI.M00());
			Assert::AreEqual(short{}, defaultMatrixI.M10());
			Assert::AreEqual(short{}, defaultMatrixI.M01());
			Assert::AreEqual(short{}, defaultMatrixI.M11());

			short m00I = 4;
			short m10I = -3;
			short m01I = 6;
			short m11I = 5;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			Assert::AreEqual(m00I, matrixI.M00());
			Assert::AreEqual(m10I, matrixI.M10());
			Assert::AreEqual(m01I, matrixI.M01());
			Assert::AreEqual(m11I, matrixI.M11());

			auto copiedMatrixI = matrixI;
			Assert::AreEqual(m00I, copiedMatrixI.M00());
			Assert::AreEqual(m10I, copiedMatrixI.M10());
			Assert::AreEqual(m01I, copiedMatrixI.M01());
			Assert::AreEqual(m11I, copiedMatrixI.M11());

			auto column0I = PonyEngine::Math::Vector2<short>(m00I, m10I);
			auto column1I = PonyEngine::Math::Vector2<short>(m01I, m11I);
			auto vectorMatrixI = PonyEngine::Math::Matrix2x2<short>(column0I, column1I);
			Assert::AreEqual(m00I, vectorMatrixI.M00());
			Assert::AreEqual(m10I, vectorMatrixI.M10());
			Assert::AreEqual(m01I, vectorMatrixI.M01());
			Assert::AreEqual(m11I, vectorMatrixI.M11());
		}
	};
}
