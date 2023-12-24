/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyEngine.Math.Vector3;
import PonyEngine.Math.Common;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PonyEngineTests
{
	TEST_CLASS(MathTests)
	{
	public:
		TEST_METHOD(SignTest)
		{
			signed char c = 0;
			Assert::AreEqual((signed char)(0), PonyEngine::Math::Sign(c));

			c = -3;
			Assert::AreEqual((signed char)(-1), PonyEngine::Math::Sign(c));

			c = 5;
			Assert::AreEqual(signed char(1), PonyEngine::Math::Sign(c));

			unsigned short s = 0;
			Assert::AreEqual((unsigned short)(0), PonyEngine::Math::Sign(s));

			s = 2;
			Assert::AreEqual((unsigned short)(1), PonyEngine::Math::Sign(s));

			signed int i = 0;
			Assert::AreEqual(0, PonyEngine::Math::Sign(i));

			i = -20;
			Assert::AreEqual(-1, PonyEngine::Math::Sign(i));

			i = 100;
			Assert::AreEqual(1, PonyEngine::Math::Sign(i));

			float f = 0.f;
			Assert::AreEqual(0.f, PonyEngine::Math::Sign(f));

			f = -42.f;
			Assert::AreEqual(-1.f, PonyEngine::Math::Sign(f));

			f = 50.f;
			Assert::AreEqual(1.f, PonyEngine::Math::Sign(f));
		}

		TEST_METHOD(Vector3ConstructorsTest)
		{
			auto defaultFloatVector = PonyEngine::Math::Vector3<float>();
			Assert::AreEqual(float(), defaultFloatVector.x);
			Assert::AreEqual(float(), defaultFloatVector.y);
			Assert::AreEqual(float(), defaultFloatVector.z);

			float x = 4.f;
			float y = -14.f;
			float z = 7.f;

			auto floatVector = PonyEngine::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, floatVector.x);
			Assert::AreEqual(y, floatVector.y);
			Assert::AreEqual(z, floatVector.z);

			PonyEngine::Math::Vector3<float> copiedFloatVector = floatVector;
			Assert::AreEqual(x, copiedFloatVector.x);
			Assert::AreEqual(y, copiedFloatVector.y);
			Assert::AreEqual(z, copiedFloatVector.z);

			PonyEngine::Math::Vector3<float> movedFloatVector = std::move(floatVector);
			Assert::AreEqual(x, movedFloatVector.x);
			Assert::AreEqual(y, movedFloatVector.y);
			Assert::AreEqual(z, movedFloatVector.z);
		}

		TEST_METHOD(Vector3MagnitudeTest)
		{
			float x = 7.f;
			float y = -17.f;
			float z = -43.f;
			float magnitudeSquare = pow(x, 2.f) + pow(y, 2.f) + pow(z, 2.f);
			float magnitude = sqrt(magnitudeSquare);
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);

			Assert::AreEqual(magnitudeSquare, vector.MagnitudeSquared());
			Assert::AreEqual(magnitude, vector.Magnitude());
		}

		TEST_METHOD(Vector3NormalizationTest)
		{
			float x = -5.f;
			float y = 15.f;
			float z = 7.f;
			float magnitudeSquare = pow(x, 2.f) + pow(y, 2.f) + pow(z, 2.f);
			float magnitude = sqrt(magnitudeSquare);
			float normX = x / magnitude;
			float normY = y / magnitude;
			float normZ = z / magnitude;
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			auto normVector = vector.Normalized();

			Assert::AreEqual(normX, normVector.x);
			Assert::AreEqual(normY, normVector.y);
			Assert::AreEqual(normZ, normVector.z);

			vector.Normalize();
			Assert::AreEqual(normVector.x, vector.x);
			Assert::AreEqual(normVector.y, vector.y);
			Assert::AreEqual(normVector.z, vector.z);
		}

		TEST_METHOD(Vector3AssignmentTest)
		{
			PonyEngine::Math::Vector3<float> left, central, right;
			float x = 8.f;
			float y = 22.f;
			float z = -98.f;

			left = central = right = PonyEngine::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, left.x);
			Assert::AreEqual(x, central.x);
			Assert::AreEqual(x, right.x);
			Assert::AreEqual(y, left.y);
			Assert::AreEqual(y, central.y);
			Assert::AreEqual(y, right.y);
			Assert::AreEqual(z, left.z);
			Assert::AreEqual(z, central.z);
			Assert::AreEqual(z, right.z);

			float x1 = 6.f;
			float y1 = -90.f;
			float z1 = 32.f;
			right = PonyEngine::Math::Vector3<float>(x1, y1, z1);
			left = central += right;
			Assert::AreEqual(x + x1, left.x);
			Assert::AreEqual(y + y1, left.y);
			Assert::AreEqual(z + z1, left.z);
			Assert::AreEqual(x + x1, central.x);
			Assert::AreEqual(y + y1, central.y);
			Assert::AreEqual(z + z1, central.z);

			left = central = PonyEngine::Math::Vector3<float>(x, y, z);
			right = PonyEngine::Math::Vector3<float>(x1, y1, z1);
			left = central -= right;
			Assert::AreEqual(x - x1, left.x);
			Assert::AreEqual(y - y1, left.y);
			Assert::AreEqual(z - z1, left.z);
			Assert::AreEqual(x - x1, central.x);
			Assert::AreEqual(y - y1, central.y);
			Assert::AreEqual(z - z1, central.z);

			left = central = PonyEngine::Math::Vector3<float>(x, y, z);
			float multiplier = 3.f;
			left = central *= multiplier;
			Assert::AreEqual(x * multiplier, left.x);
			Assert::AreEqual(y * multiplier, left.y);
			Assert::AreEqual(z * multiplier, left.z);
			Assert::AreEqual(x * multiplier, central.x);
			Assert::AreEqual(y * multiplier, central.y);
			Assert::AreEqual(z * multiplier, central.z);

			left = central = PonyEngine::Math::Vector3<float>(x, y, z);
			left = central /= multiplier;
			Assert::AreEqual(x / multiplier, left.x);
			Assert::AreEqual(y / multiplier, left.y);
			Assert::AreEqual(z / multiplier, left.z);
			Assert::AreEqual(x / multiplier, central.x);
			Assert::AreEqual(y / multiplier, central.y);
			Assert::AreEqual(z / multiplier, central.z);
		}

		TEST_METHOD(Vector3DotTest)
		{
			float x = 5.f;
			float y = -1.f;
			float z = -15.f;
			float x1 = 14.f;
			float y1 = 100.f;
			float z1 = -2.f;
			float dot = x * x1 + y * y1 + z * z1;
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			auto vector1 = PonyEngine::Math::Vector3<float>(x1, y1, z1);

			float vectorDot = PonyEngine::Math::Dot(vector, vector1);
			Assert::AreEqual(dot, vectorDot);
		}

		TEST_METHOD(Vector3CrossTest)
		{
			float x = 5.f;
			float y = -1.f;
			float z = -15.f;
			float x1 = 14.f;
			float y1 = 100.f;
			float z1 = -2.f;
			auto cross = PonyEngine::Math::Vector3<float>(y * z1 - z * y1, z * x1 - x * z1, x * y1 - y * x1);
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			auto vector1 = PonyEngine::Math::Vector3<float>(x1, y1, z1);

			auto vectorCross = PonyEngine::Math::Cross(vector, vector1);
			Assert::AreEqual(cross.x, vectorCross.x);
			Assert::AreEqual(cross.y, vectorCross.y);
			Assert::AreEqual(cross.z, vectorCross.z);
		}

		TEST_METHOD(Vector3EqualityOperatorsTest)
		{
			float x = 10.f;
			float y = 15.f;
			float z = -7.f;
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			auto vector1 = PonyEngine::Math::Vector3<float>(x, y, z);
			Assert::IsTrue(vector == vector1);
			Assert::IsFalse(vector != vector1);

			vector1.z *= 2.f;
			Assert::IsFalse(vector == vector1);
			Assert::IsTrue(vector != vector1);

			vector1.z = z;
			vector1.y *= 3.f;
			Assert::IsFalse(vector == vector1);
			Assert::IsTrue(vector != vector1);

			vector1.y = y;
			vector1.x *= 0.5f;
			Assert::IsFalse(vector == vector1);
			Assert::IsTrue(vector != vector1);

			vector.y *= 3.5f;
			Assert::IsFalse(vector == vector1);
			Assert::IsTrue(vector != vector1);

			vector.z *= 0.2f;
			Assert::IsFalse(vector == vector1);
			Assert::IsTrue(vector != vector1);

			vector = vector1;
			Assert::IsTrue(vector == vector1);
			Assert::IsFalse(vector != vector1);
		}

		TEST_METHOD(Vector3ComputationOperatorsTest)
		{
			float x = 90.f;
			float y = 100.f;
			float z = -80.f;
			float x1 = -75.f;
			float y1 = 60.f;
			float z1 = -95.f;
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			auto vector1 = PonyEngine::Math::Vector3<float>(x1, y1, z1);

			auto vector2 = vector + vector1;
			Assert::AreEqual(x + x1, vector2.x);
			Assert::AreEqual(y + y1, vector2.y);
			Assert::AreEqual(z + z1, vector2.z);

			vector2 = vector - vector1;
			Assert::AreEqual(x - x1, vector2.x);
			Assert::AreEqual(y - y1, vector2.y);
			Assert::AreEqual(z - z1, vector2.z);

			float multiplier = 3.3f;
			vector2 = vector * multiplier;
			Assert::AreEqual(x * multiplier, vector2.x);
			Assert::AreEqual(y * multiplier, vector2.y);
			Assert::AreEqual(z * multiplier, vector2.z);

			vector2 = multiplier * vector;
			Assert::AreEqual(x * multiplier, vector2.x);
			Assert::AreEqual(y * multiplier, vector2.y);
			Assert::AreEqual(z * multiplier, vector2.z);

			vector2 = vector / multiplier;
			Assert::AreEqual(x / multiplier, vector2.x);
			Assert::AreEqual(y / multiplier, vector2.y);
			Assert::AreEqual(z / multiplier, vector2.z);

			vector2 = vector * vector1;
			Assert::AreEqual(x * x1, vector2.x);
			Assert::AreEqual(y * y1, vector2.y);
			Assert::AreEqual(z * z1, vector2.z);

			vector2 = vector / vector1;
			Assert::AreEqual(x / x1, vector2.x);
			Assert::AreEqual(y / y1, vector2.y);
			Assert::AreEqual(z / z1, vector2.z);
		}
	};
}
