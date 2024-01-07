/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <numbers>;

import PonyEngine.Math.Vector3;
import PonyEngine.Math.Vector2;
import PonyEngine.Math.Vector4;
import PonyEngine.Math.Quaternion;
import PonyEngine.Math.Common;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PonyEngineTests
{
	TEST_CLASS(MathTests)
	{
	public:
		TEST_METHOD(DegToRadToDegTest)
		{
			Assert::AreEqual(std::numbers::pi_v<double> / 180, PonyEngine::Math::DegToRad<double>);
			Assert::AreEqual(180 / std::numbers::pi_v<double>, PonyEngine::Math::RadToDeg<double>);

			Assert::AreEqual(std::numbers::pi_v<float> / 180, PonyEngine::Math::DegToRad<float>);
			Assert::AreEqual(180 / std::numbers::pi_v<float>, PonyEngine::Math::RadToDeg<float>);
		}

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

			int i = 0;
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

		TEST_METHOD(RoundToIntegralTest)
		{
			signed char charValue = PonyEngine::Math::RoundToIntegralIfPossible<float, unsigned char>(0.3f);
			Assert::AreEqual((signed char)(0), charValue);
			charValue = PonyEngine::Math::RoundToIntegralIfPossible<float, unsigned char>(-0.3f);
			Assert::AreEqual((signed char)(0), charValue);
			charValue = PonyEngine::Math::RoundToIntegralIfPossible<float, unsigned char>(5.7f);
			Assert::AreEqual((signed char)(6), charValue);
			charValue = PonyEngine::Math::RoundToIntegralIfPossible<float, unsigned char>(-5.7f);
			Assert::AreEqual((signed char)(-6), charValue);
			charValue = PonyEngine::Math::RoundToIntegralIfPossible<float, unsigned char>(5.3f);
			Assert::AreEqual((signed char)(5), charValue);
			charValue = PonyEngine::Math::RoundToIntegralIfPossible<float, unsigned char>(-5.3f);
			Assert::AreEqual((signed char)(-5), charValue);

			int intValue = PonyEngine::Math::RoundToIntegralIfPossible<float, int>(0.3f);
			Assert::AreEqual(0, intValue);
			intValue = PonyEngine::Math::RoundToIntegralIfPossible<float, int>(-0.3f);
			Assert::AreEqual(0, intValue);
			intValue = PonyEngine::Math::RoundToIntegralIfPossible<float, int>(5.7f);
			Assert::AreEqual(6, intValue);
			intValue = PonyEngine::Math::RoundToIntegralIfPossible<float, int>(-5.7f);
			Assert::AreEqual(-6, intValue);
			intValue = PonyEngine::Math::RoundToIntegralIfPossible<float, int>(5.3f);
			Assert::AreEqual(5, intValue);
			intValue = PonyEngine::Math::RoundToIntegralIfPossible<float, int>(-5.3f);
			Assert::AreEqual(-5, intValue);

			long longValue = PonyEngine::Math::RoundToIntegralIfPossible<double, long>(0.3);
			Assert::AreEqual((long)0, longValue);
			longValue = PonyEngine::Math::RoundToIntegralIfPossible<double, long>(-0.3);
			Assert::AreEqual((long)0, longValue);
			longValue = PonyEngine::Math::RoundToIntegralIfPossible<double, long>(5.7);
			Assert::AreEqual((long)6, longValue);
			longValue = PonyEngine::Math::RoundToIntegralIfPossible<double, long>(-5.7);
			Assert::AreEqual((long)-6, longValue);
			longValue = PonyEngine::Math::RoundToIntegralIfPossible<double, long>(5.3);
			Assert::AreEqual((long)5, longValue);
			longValue = PonyEngine::Math::RoundToIntegralIfPossible<double, long>(-5.3);
			Assert::AreEqual((long)-5, longValue);
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

			left = central = PonyEngine::Math::Vector3<float>(x, y, z);
			left = central *= right;
			Assert::AreEqual(x * right.x, left.x);
			Assert::AreEqual(y * right.y, left.y);
			Assert::AreEqual(z * right.z, left.z);
			Assert::AreEqual(x * right.x, central.x);
			Assert::AreEqual(y * right.y, central.y);
			Assert::AreEqual(z * right.z, central.z);

			left = central = PonyEngine::Math::Vector3<float>(x, y, z);
			left = central /= right;
			Assert::AreEqual(x / right.x, left.x);
			Assert::AreEqual(y / right.y, left.y);
			Assert::AreEqual(z / right.z, left.z);
			Assert::AreEqual(x / right.x, central.x);
			Assert::AreEqual(y / right.y, central.y);
			Assert::AreEqual(z / right.z, central.z);
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

		TEST_METHOD(Vector3AngleTest)
		{
			auto vector0 = PonyEngine::Math::Vector3<double>(2., 0., 0.);
			auto vector1 = PonyEngine::Math::Vector3<double>(0., 5., 2.);
			double expected = acos(0);
			double actual = PonyEngine::Math::Angle(vector0, vector1);
			Assert::AreEqual(expected, actual);
			expected *= PonyEngine::Math::RadToDeg<double>;
			actual = PonyEngine::Math::AngleDegrees(vector0, vector1);
			Assert::AreEqual(expected, actual);
			expected = acos(0);
			actual = PonyEngine::Math::AngleSigned(vector0, vector1, PonyEngine::Math::Vector3<double>(0., -1., 0.));
			Assert::AreEqual(expected, actual);
			expected = -expected;
			actual = PonyEngine::Math::AngleSigned(vector0, vector1, PonyEngine::Math::Vector3<double>(0., 1., 0.));
			Assert::AreEqual(expected, actual);
			expected *= PonyEngine::Math::RadToDeg<double>;
			actual = PonyEngine::Math::AngleSignedDegrees(vector0, vector1, PonyEngine::Math::Vector3<double>(0., 1., 0.));
			Assert::AreEqual(expected, actual);

			vector0 = PonyEngine::Math::Vector3<double>(5., -3., 1.);
			vector1 = PonyEngine::Math::Vector3<double>(-7., 1., 9.);
			expected = acos(PonyEngine::Math::Dot(vector0, vector1) / (vector0.Magnitude() * vector1.Magnitude()));
			actual = PonyEngine::Math::Angle(vector0, vector1);
			Assert::AreEqual(expected, actual);
			expected *= PonyEngine::Math::RadToDeg<double>;
			actual = PonyEngine::Math::AngleDegrees(vector0, vector1);
			Assert::AreEqual(expected, actual);
			expected = acos(PonyEngine::Math::Dot(vector0, vector1) / (vector0.Magnitude() * vector1.Magnitude()));
			actual = PonyEngine::Math::AngleSigned(vector0, vector1, PonyEngine::Math::Vector3<double>(0., -1., 0.));
			Assert::AreEqual(expected, actual);
			expected = -expected;
			actual = PonyEngine::Math::AngleSigned(vector0, vector1, PonyEngine::Math::Vector3<double>(0., 1., 0.));
			Assert::AreEqual(expected, actual);
			expected *= PonyEngine::Math::RadToDeg<double>;
			actual = PonyEngine::Math::AngleSignedDegrees(vector0, vector1, PonyEngine::Math::Vector3<double>(0., 1., 0.));
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Vector3ProjectTest)
		{
			auto vector0 = PonyEngine::Math::Vector3<float>(3.f, 0.f, 0.f);
			auto vector1 = PonyEngine::Math::Vector3<float>(0.f, 0.f, 3.f);
			float expected = 0.f;
			float actual = PonyEngine::Math::Project(vector0, vector1).Magnitude();
			Assert::AreEqual(expected, actual);

			vector0.Set(-4.f, 2.f, 7.f);
			vector1.Set(3.f, 1.f, 2.f);
			auto expectedVector = PonyEngine::Math::Vector3<float>(6.f/7.f, 2.f/7.f, 4.f/7.f);
			auto actualVector = PonyEngine::Math::Project(vector0, vector1);
			Assert::AreEqual(static_cast<double>(expectedVector.x), static_cast<double>(actualVector.x), 0.0001);
			Assert::AreEqual(static_cast<double>(expectedVector.y), static_cast<double>(actualVector.y), 0.0001);
			Assert::AreEqual(static_cast<double>(expectedVector.z), static_cast<double>(actualVector.z), 0.0001);
			Assert::AreEqual(0., static_cast<double>(PonyEngine::Math::AngleDegrees(actualVector, vector1)), 0.0001);
		}

		TEST_METHOD(Vector3ProjectOnPlaneTest)
		{
			auto vector = PonyEngine::Math::Vector3<float>(2.f, 0.f, 0.f);
			auto normal = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
			auto projection = PonyEngine::Math::ProjectOnPlane(vector, normal);
			Assert::AreEqual(0.f, projection.Magnitude());

			vector.Set(20.f, -30.f, 15.f);
			normal.Set(0.5f, 0.1f, -0.24f);
			normal.Normalize();
			auto expected = vector - normal * PonyEngine::Math::Dot(vector, normal);
			projection = PonyEngine::Math::ProjectOnPlane(vector, normal);
			Assert::AreEqual(static_cast<double>(expected.x), static_cast<double>(projection.x), 0.0001);
			Assert::AreEqual(static_cast<double>(expected.y), static_cast<double>(projection.y), 0.0001);
			Assert::AreEqual(static_cast<double>(expected.z), static_cast<double>(projection.z), 0.0001);
			Assert::AreEqual(90., static_cast<double>(PonyEngine::Math::AngleDegrees(projection, normal)), 0.0001);
		}

		TEST_METHOD(Vector3ReflectTest)
		{
			auto vector = PonyEngine::Math::Vector3<double>(0.5, -0.5, 0.);
			auto normal = PonyEngine::Math::Vector3<double>(0., 1., 0.);
			auto reflection = PonyEngine::Math::Reflect(vector, normal);
			Assert::AreEqual(0.5, reflection.x, 0.0001);
			Assert::AreEqual(0.5, reflection.y, 0.0001);
			Assert::AreEqual(0., reflection.z, 0.0001);

			vector.Set(-14., 39., -1.);
			normal.Set(10., -17., -34.);
			normal.Normalize();
			reflection = PonyEngine::Math::Reflect(vector, normal);
			auto expected = vector - 2 * PonyEngine::Math::Dot(vector, normal) * normal;
			Assert::AreEqual(expected.x, reflection.x, 0.0001);
			Assert::AreEqual(expected.y, reflection.y, 0.0001);
			Assert::AreEqual(expected.z, reflection.z, 0.0001);
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

		TEST_METHOD(Vector3DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Forward == PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Back == PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Up == PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Down == PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Right == PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Left == PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::One == PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Zero == PonyEngine::Math::Vector3<float>(0.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Negative == PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f));

			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Forward == PonyEngine::Math::Vector3<short>(0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Back == PonyEngine::Math::Vector3<short>(0, 0, -1));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Up == PonyEngine::Math::Vector3<short>(0, 1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Down == PonyEngine::Math::Vector3<short>(0, -1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Right == PonyEngine::Math::Vector3<short>(1, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Left == PonyEngine::Math::Vector3<short>(-1, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::One == PonyEngine::Math::Vector3<short>(1, 1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Zero == PonyEngine::Math::Vector3<short>(0, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Negative == PonyEngine::Math::Vector3<short>(-1, -1, -1));

			Assert::IsTrue(PonyEngine::Math::Vector3<unsigned char>::Forward == PonyEngine::Math::Vector3<unsigned char>(0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3<unsigned char>::Up == PonyEngine::Math::Vector3<unsigned char>(0, 1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<unsigned char>::Right == PonyEngine::Math::Vector3<unsigned char>(1, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<unsigned char>::One == PonyEngine::Math::Vector3<unsigned char>(1, 1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3<unsigned char>::Zero == PonyEngine::Math::Vector3<unsigned char>(0, 0, 0));
		}

		TEST_METHOD(Vector3TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyEngine::Math::Vector3<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector3<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyEngine::Math::Vector3<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector3<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyEngine::Math::Vector3<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector3<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector3<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector3<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyEngine::Math::Vector3<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector3<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector3<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector3<double>::ComputationalType>);
		}

		TEST_METHOD(Vector2ConstructorsTest)
		{
			auto defaultFloatVector = PonyEngine::Math::Vector2<float>();
			Assert::AreEqual(float(), defaultFloatVector.x);
			Assert::AreEqual(float(), defaultFloatVector.y);

			float x = 4.f;
			float y = -14.f;

			auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(x, floatVector.x);
			Assert::AreEqual(y, floatVector.y);

			PonyEngine::Math::Vector2<float> copiedFloatVector = floatVector;
			Assert::AreEqual(x, copiedFloatVector.x);
			Assert::AreEqual(y, copiedFloatVector.y);

			PonyEngine::Math::Vector2<float> movedFloatVector = std::move(floatVector);
			Assert::AreEqual(x, movedFloatVector.x);
			Assert::AreEqual(y, movedFloatVector.y);
		}

		TEST_METHOD(Vector2MagnitudeTest)
		{
			float x = 7.f;
			float y = -17.f;
			float magnitudeSquare = pow(x, 2.f) + pow(y, 2.f);
			float magnitude = sqrt(magnitudeSquare);
			auto vector = PonyEngine::Math::Vector2<float>(x, y);

			Assert::AreEqual(magnitudeSquare, vector.MagnitudeSquared());
			Assert::AreEqual(magnitude, vector.Magnitude());
		}

		TEST_METHOD(Vector2NormalizationTest)
		{
			float x = -5.f;
			float y = 15.f;
			float magnitudeSquare = pow(x, 2.f) + pow(y, 2.f);
			float magnitude = sqrt(magnitudeSquare);
			float normX = x / magnitude;
			float normY = y / magnitude;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			auto normVector = vector.Normalized();

			Assert::AreEqual(normX, normVector.x);
			Assert::AreEqual(normY, normVector.y);

			vector.Normalize();
			Assert::AreEqual(normVector.x, vector.x);
			Assert::AreEqual(normVector.y, vector.y);
		}

		TEST_METHOD(Vector2AssignmentTest)
		{
			PonyEngine::Math::Vector2<float> left, central, right;
			float x = 8.f;
			float y = 22.f;

			left = central = right = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(x, left.x);
			Assert::AreEqual(x, central.x);
			Assert::AreEqual(x, right.x);
			Assert::AreEqual(y, left.y);
			Assert::AreEqual(y, central.y);
			Assert::AreEqual(y, right.y);

			float x1 = 6.f;
			float y1 = -90.f;
			right = PonyEngine::Math::Vector2<float>(x1, y1);
			left = central += right;
			Assert::AreEqual(x + x1, left.x);
			Assert::AreEqual(y + y1, left.y);
			Assert::AreEqual(x + x1, central.x);
			Assert::AreEqual(y + y1, central.y);

			left = central = PonyEngine::Math::Vector2<float>(x, y);
			right = PonyEngine::Math::Vector2<float>(x1, y1);
			left = central -= right;
			Assert::AreEqual(x - x1, left.x);
			Assert::AreEqual(y - y1, left.y);
			Assert::AreEqual(x - x1, central.x);
			Assert::AreEqual(y - y1, central.y);

			left = central = PonyEngine::Math::Vector2<float>(x, y);
			float multiplier = 3.f;
			left = central *= multiplier;
			Assert::AreEqual(x * multiplier, left.x);
			Assert::AreEqual(y * multiplier, left.y);
			Assert::AreEqual(x * multiplier, central.x);
			Assert::AreEqual(y * multiplier, central.y);

			left = central = PonyEngine::Math::Vector2<float>(x, y);
			left = central /= multiplier;
			Assert::AreEqual(x / multiplier, left.x);
			Assert::AreEqual(y / multiplier, left.y);
			Assert::AreEqual(x / multiplier, central.x);
			Assert::AreEqual(y / multiplier, central.y);

			left = central = PonyEngine::Math::Vector2<float>(x, y);
			left = central *= right;
			Assert::AreEqual(x * right.x, left.x);
			Assert::AreEqual(y * right.y, left.y);
			Assert::AreEqual(x * right.x, central.x);
			Assert::AreEqual(y * right.y, central.y);

			left = central = PonyEngine::Math::Vector2<float>(x, y);
			left = central /= right;
			Assert::AreEqual(x / right.x, left.x);
			Assert::AreEqual(y / right.y, left.y);
			Assert::AreEqual(x / right.x, central.x);
			Assert::AreEqual(y / right.y, central.y);
		}

		TEST_METHOD(Vector2DotTest)
		{
			float x = 5.f;
			float y = -1.f;
			float x1 = 14.f;
			float y1 = 100.f;
			float dot = x * x1 + y * y1;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			auto vector1 = PonyEngine::Math::Vector2<float>(x1, y1);

			float vectorDot = PonyEngine::Math::Dot(vector, vector1);
			Assert::AreEqual(dot, vectorDot);
		}

		TEST_METHOD(Vector2AngleTest)
		{
			auto vector0 = PonyEngine::Math::Vector2<double>(2., 0.);
			auto vector1 = PonyEngine::Math::Vector2<double>(0., 5.);
			double expected = acos(0);
			double actual = PonyEngine::Math::Angle(vector0, vector1);
			Assert::AreEqual(expected, actual);
			expected *= PonyEngine::Math::RadToDeg<double>;
			actual = PonyEngine::Math::AngleDegrees(vector0, vector1);
			Assert::AreEqual(expected, actual);
			expected = acos(0);
			actual = PonyEngine::Math::AngleSigned(vector0, vector1);
			Assert::AreEqual(expected, actual);
			expected = -expected;
			actual = PonyEngine::Math::AngleSigned(vector1, vector0);
			Assert::AreEqual(expected, actual);
			expected *= PonyEngine::Math::RadToDeg<double>;
			actual = PonyEngine::Math::AngleSignedDegrees(vector1, vector0);
			Assert::AreEqual(expected, actual);

			vector0 = PonyEngine::Math::Vector2<double>(5., -3.);
			vector1 = PonyEngine::Math::Vector2<double>(-7., 1.);
			expected = acos(PonyEngine::Math::Dot(vector0, vector1) / (vector0.Magnitude() * vector1.Magnitude()));
			actual = PonyEngine::Math::Angle(vector0, vector1);
			Assert::AreEqual(expected, actual);
			expected *= PonyEngine::Math::RadToDeg<double>;
			actual = PonyEngine::Math::AngleDegrees(vector0, vector1);
			Assert::AreEqual(expected, actual);
			expected = -acos(PonyEngine::Math::Dot(vector0, vector1) / (vector0.Magnitude() * vector1.Magnitude()));
			actual = PonyEngine::Math::AngleSigned(vector0, vector1);
			Assert::AreEqual(expected, actual);
			expected = -expected;
			actual = PonyEngine::Math::AngleSigned(vector1, vector0);
			Assert::AreEqual(expected, actual);
			expected *= PonyEngine::Math::RadToDeg<double>;
			actual = PonyEngine::Math::AngleSignedDegrees(vector1, vector0);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Vector2ProjectTest)
		{
			auto vector0 = PonyEngine::Math::Vector2<float>(3.f, 0.f);
			auto vector1 = PonyEngine::Math::Vector2<float>(0.f, 6.f);
			float expected = 0.f;
			float actual = PonyEngine::Math::Project(vector0, vector1).Magnitude();
			Assert::AreEqual(expected, actual);

			vector0.Set(-4.f, 2.f);
			vector1.Set(3.f, 1.f);
			auto expectedVector = PonyEngine::Math::Vector2<float>(-3.f, -1.f);
			auto actualVector = PonyEngine::Math::Project(vector0, vector1);
			Assert::AreEqual(static_cast<double>(expectedVector.x), static_cast<double>(actualVector.x), 0.0001);
			Assert::AreEqual(static_cast<double>(expectedVector.y), static_cast<double>(actualVector.y), 0.0001);
			Assert::AreEqual(180., static_cast<double>(PonyEngine::Math::AngleDegrees(actualVector, vector1)), 0.0001);
		}

		TEST_METHOD(Vector2ProjectOnPlaneTest)
		{
			auto vector = PonyEngine::Math::Vector2<float>(2.f, 0.f);
			auto normal = PonyEngine::Math::Vector2<float>(-1.f, 0.f);
			auto projection = PonyEngine::Math::ProjectOnPlane(vector, normal);
			Assert::AreEqual(0.f, projection.Magnitude());

			vector.Set(20.f, -30.f);
			normal.Set(0.5f, 0.1f);
			normal.Normalize();
			auto expected = vector - normal * PonyEngine::Math::Dot(vector, normal);
			projection = PonyEngine::Math::ProjectOnPlane(vector, normal);
			Assert::AreEqual(static_cast<double>(expected.x), static_cast<double>(projection.x), 0.0001);
			Assert::AreEqual(static_cast<double>(expected.y), static_cast<double>(projection.y), 0.0001);
			Assert::AreEqual(90., static_cast<double>(PonyEngine::Math::AngleDegrees(projection, normal)), 0.0001);
		}

		TEST_METHOD(Vector2ReflectTest)
		{
			auto vector = PonyEngine::Math::Vector2<double>(0.5, -0.5);
			auto normal = PonyEngine::Math::Vector2<double>(0., 1.);
			auto reflection = PonyEngine::Math::Reflect(vector, normal);
			Assert::AreEqual(0.5, reflection.x, 0.0001);
			Assert::AreEqual(0.5, reflection.y, 0.0001);

			vector.Set(-14., 39.);
			normal.Set(10., -17.);
			normal.Normalize();
			reflection = PonyEngine::Math::Reflect(vector, normal);
			auto expected = vector - 2 * PonyEngine::Math::Dot(vector, normal) * normal;
			Assert::AreEqual(expected.x, reflection.x, 0.0001);
			Assert::AreEqual(expected.y, reflection.y, 0.0001);
		}

		TEST_METHOD(Vector2EqualityOperatorsTest)
		{
			float x = 10.f;
			float y = 15.f;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			auto vector1 = PonyEngine::Math::Vector2<float>(x, y);
			Assert::IsTrue(vector == vector1);
			Assert::IsFalse(vector != vector1);

			vector1.x *= 0.5f;
			Assert::IsFalse(vector == vector1);
			Assert::IsTrue(vector != vector1);

			vector.y *= 3.5f;
			Assert::IsFalse(vector == vector1);
			Assert::IsTrue(vector != vector1);

			vector.x = x;
			Assert::IsFalse(vector == vector1);
			Assert::IsTrue(vector != vector1);

			vector = vector1;
			Assert::IsTrue(vector == vector1);
			Assert::IsFalse(vector != vector1);
		}

		TEST_METHOD(Vector2ComputationOperatorsTest)
		{
			float x = 90.f;
			float y = 100.f;
			float x1 = -75.f;
			float y1 = 60.f;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			auto vector1 = PonyEngine::Math::Vector2<float>(x1, y1);

			auto vector2 = vector + vector1;
			Assert::AreEqual(x + x1, vector2.x);
			Assert::AreEqual(y + y1, vector2.y);

			vector2 = vector - vector1;
			Assert::AreEqual(x - x1, vector2.x);
			Assert::AreEqual(y - y1, vector2.y);

			float multiplier = 3.3f;
			vector2 = vector * multiplier;
			Assert::AreEqual(x * multiplier, vector2.x);
			Assert::AreEqual(y * multiplier, vector2.y);

			vector2 = multiplier * vector;
			Assert::AreEqual(x * multiplier, vector2.x);
			Assert::AreEqual(y * multiplier, vector2.y);

			vector2 = vector / multiplier;
			Assert::AreEqual(x / multiplier, vector2.x);
			Assert::AreEqual(y / multiplier, vector2.y);

			vector2 = vector * vector1;
			Assert::AreEqual(x * x1, vector2.x);
			Assert::AreEqual(y * y1, vector2.y);

			vector2 = vector / vector1;
			Assert::AreEqual(x / x1, vector2.x);
			Assert::AreEqual(y / y1, vector2.y);
		}

		TEST_METHOD(Vector2DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Up == PonyEngine::Math::Vector2<float>(0.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Down == PonyEngine::Math::Vector2<float>(0.f, -1.f));
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Right == PonyEngine::Math::Vector2<float>(1.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Left == PonyEngine::Math::Vector2<float>(-1.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::One == PonyEngine::Math::Vector2<float>(1.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Zero == PonyEngine::Math::Vector2<float>(0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Negative == PonyEngine::Math::Vector2<float>(-1.f, -1.f));

			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Up == PonyEngine::Math::Vector2<short>(0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Down == PonyEngine::Math::Vector2<short>(0, -1));
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Right == PonyEngine::Math::Vector2<short>(1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Left == PonyEngine::Math::Vector2<short>(-1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::One == PonyEngine::Math::Vector2<short>(1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Zero == PonyEngine::Math::Vector2<short>(0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Negative == PonyEngine::Math::Vector2<short>(-1, -1));

			Assert::IsTrue(PonyEngine::Math::Vector2<unsigned char>::Up == PonyEngine::Math::Vector2<unsigned char>(0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector2<unsigned char>::Right == PonyEngine::Math::Vector2<unsigned char>(1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2<unsigned char>::One == PonyEngine::Math::Vector2<unsigned char>(1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector2<unsigned char>::Zero == PonyEngine::Math::Vector2<unsigned char>(0, 0));
		}

		TEST_METHOD(Vector2TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyEngine::Math::Vector2<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector2<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyEngine::Math::Vector2<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector2<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyEngine::Math::Vector2<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector2<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector2<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector2<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyEngine::Math::Vector2<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector2<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector2<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector2<double>::ComputationalType>);
		}

		TEST_METHOD(Vector4ConstructorsTest)
		{
			auto defaultFloatVector = PonyEngine::Math::Vector4<float>();
			Assert::AreEqual(float(), defaultFloatVector.x);
			Assert::AreEqual(float(), defaultFloatVector.y);
			Assert::AreEqual(float(), defaultFloatVector.z);
			Assert::AreEqual(float(), defaultFloatVector.w);

			float x = 4.f;
			float y = -14.f;
			float z = 7.f;
			float w = -17.f;

			auto floatVector = PonyEngine::Math::Vector4<float>(x, y, z, w);
			Assert::AreEqual(x, floatVector.x);
			Assert::AreEqual(y, floatVector.y);
			Assert::AreEqual(z, floatVector.z);
			Assert::AreEqual(w, floatVector.w);

			PonyEngine::Math::Vector4<float> copiedFloatVector = floatVector;
			Assert::AreEqual(x, copiedFloatVector.x);
			Assert::AreEqual(y, copiedFloatVector.y);
			Assert::AreEqual(z, copiedFloatVector.z);
			Assert::AreEqual(w, copiedFloatVector.w);

			PonyEngine::Math::Vector4<float> movedFloatVector = std::move(floatVector);
			Assert::AreEqual(x, movedFloatVector.x);
			Assert::AreEqual(y, movedFloatVector.y);
			Assert::AreEqual(z, movedFloatVector.z);
			Assert::AreEqual(w, movedFloatVector.w);
		}

		TEST_METHOD(Vector4MagnitudeTest)
		{
			float x = 7.f;
			float y = -17.f;
			float z = -43.f;
			float w = 23.f;
			float magnitudeSquare = pow(x, 2.f) + pow(y, 2.f) + pow(z, 2.f) + pow(w, 2.f);
			float magnitude = sqrt(magnitudeSquare);
			auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);

			Assert::AreEqual(magnitudeSquare, vector.MagnitudeSquared());
			Assert::AreEqual(magnitude, vector.Magnitude());
		}

		TEST_METHOD(Vector4NormalizationTest)
		{
			float x = -5.f;
			float y = 15.f;
			float z = 7.f;
			float w = -5.f;
			float magnitudeSquare = pow(x, 2.f) + pow(y, 2.f) + pow(z, 2.f) + pow(w, 2.f);
			float magnitude = sqrt(magnitudeSquare);
			float normX = x / magnitude;
			float normY = y / magnitude;
			float normZ = z / magnitude;
			float normW = w / magnitude;
			auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);
			auto normVector = vector.Normalized();

			Assert::AreEqual(normX, normVector.x);
			Assert::AreEqual(normY, normVector.y);
			Assert::AreEqual(normZ, normVector.z);
			Assert::AreEqual(normW, normVector.w);

			vector.Normalize();
			Assert::AreEqual(normVector.x, vector.x);
			Assert::AreEqual(normVector.y, vector.y);
			Assert::AreEqual(normVector.z, vector.z);
			Assert::AreEqual(normVector.w, vector.w);
		}

		TEST_METHOD(Vector4AssignmentTest)
		{
			PonyEngine::Math::Vector4<float> left, central, right;
			float x = 8.f;
			float y = 22.f;
			float z = -98.f;
			float w = 3.f;

			left = central = right = PonyEngine::Math::Vector4<float>(x, y, z, w);
			Assert::AreEqual(x, left.x);
			Assert::AreEqual(x, central.x);
			Assert::AreEqual(x, right.x);
			Assert::AreEqual(y, left.y);
			Assert::AreEqual(y, central.y);
			Assert::AreEqual(y, right.y);
			Assert::AreEqual(z, left.z);
			Assert::AreEqual(z, central.z);
			Assert::AreEqual(z, right.z);
			Assert::AreEqual(w, left.w);
			Assert::AreEqual(w, central.w);
			Assert::AreEqual(w, right.w);

			float x1 = 6.f;
			float y1 = -90.f;
			float z1 = 32.f;
			float w1 = -10.f;
			right = PonyEngine::Math::Vector4<float>(x1, y1, z1, w1);
			left = central += right;
			Assert::AreEqual(x + x1, left.x);
			Assert::AreEqual(y + y1, left.y);
			Assert::AreEqual(z + z1, left.z);
			Assert::AreEqual(w + w1, left.w);
			Assert::AreEqual(x + x1, central.x);
			Assert::AreEqual(y + y1, central.y);
			Assert::AreEqual(z + z1, central.z);
			Assert::AreEqual(w + w1, central.w);

			left = central = PonyEngine::Math::Vector4<float>(x, y, z, w);
			right = PonyEngine::Math::Vector4<float>(x1, y1, z1, w1);
			left = central -= right;
			Assert::AreEqual(x - x1, left.x);
			Assert::AreEqual(y - y1, left.y);
			Assert::AreEqual(z - z1, left.z);
			Assert::AreEqual(w - w1, left.w);
			Assert::AreEqual(x - x1, central.x);
			Assert::AreEqual(y - y1, central.y);
			Assert::AreEqual(z - z1, central.z);
			Assert::AreEqual(w - w1, central.w);

			left = central = PonyEngine::Math::Vector4<float>(x, y, z, w);
			float multiplier = 3.f;
			left = central *= multiplier;
			Assert::AreEqual(x * multiplier, left.x);
			Assert::AreEqual(y * multiplier, left.y);
			Assert::AreEqual(z * multiplier, left.z);
			Assert::AreEqual(w * multiplier, left.w);
			Assert::AreEqual(x * multiplier, central.x);
			Assert::AreEqual(y * multiplier, central.y);
			Assert::AreEqual(z * multiplier, central.z);
			Assert::AreEqual(w * multiplier, central.w);

			left = central = PonyEngine::Math::Vector4<float>(x, y, z, w);
			left = central /= multiplier;
			Assert::AreEqual(x / multiplier, left.x);
			Assert::AreEqual(y / multiplier, left.y);
			Assert::AreEqual(z / multiplier, left.z);
			Assert::AreEqual(w / multiplier, left.w);
			Assert::AreEqual(x / multiplier, central.x);
			Assert::AreEqual(y / multiplier, central.y);
			Assert::AreEqual(z / multiplier, central.z);
			Assert::AreEqual(w / multiplier, central.w);

			left = central = PonyEngine::Math::Vector4<float>(x, y, z, w);
			left = central *= right;
			Assert::AreEqual(x * right.x, left.x);
			Assert::AreEqual(y * right.y, left.y);
			Assert::AreEqual(z * right.z, left.z);
			Assert::AreEqual(w * right.w, left.w);
			Assert::AreEqual(x * right.x, central.x);
			Assert::AreEqual(y * right.y, central.y);
			Assert::AreEqual(z * right.z, central.z);
			Assert::AreEqual(w * right.w, central.w);

			left = central = PonyEngine::Math::Vector4<float>(x, y, z, w);
			left = central /= right;
			Assert::AreEqual(x / right.x, left.x);
			Assert::AreEqual(y / right.y, left.y);
			Assert::AreEqual(z / right.z, left.z);
			Assert::AreEqual(w / right.w, left.w);
			Assert::AreEqual(x / right.x, central.x);
			Assert::AreEqual(y / right.y, central.y);
			Assert::AreEqual(z / right.z, central.z);
			Assert::AreEqual(w / right.w, central.w);
		}

		TEST_METHOD(Vector4DotTest)
		{
			float x = 5.f;
			float y = -1.f;
			float z = -15.f;
			float w = 55.f;
			float x1 = 14.f;
			float y1 = 100.f;
			float z1 = -2.f;
			float w1 = -3.f;
			float dot = x * x1 + y * y1 + z * z1 + w * w1;
			auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);
			auto vector1 = PonyEngine::Math::Vector4<float>(x1, y1, z1, w1);

			float vectorDot = PonyEngine::Math::Dot(vector, vector1);
			Assert::AreEqual(dot, vectorDot);
		}

		TEST_METHOD(Vector4ProjectTest)
		{
			auto vector0 = PonyEngine::Math::Vector4<float>(3.f, 0.f, 0.f, 0.f);
			auto vector1 = PonyEngine::Math::Vector4<float>(0.f, 0.f, 3.f, 0.f);
			float expected = 0.f;
			float actual = PonyEngine::Math::Project(vector0, vector1).Magnitude();
			Assert::AreEqual(expected, actual);

			vector0.Set(-4.f, 2.f, 7.f, 1.f);
			vector1.Set(3.f, 1.f, 2.f, 5.f);
			auto expectedVector = vector1 * PonyEngine::Math::Dot(vector0, vector1) / PonyEngine::Math::Dot(vector1, vector1);
			auto actualVector = PonyEngine::Math::Project(vector0, vector1);
			Assert::AreEqual(static_cast<double>(expectedVector.x), static_cast<double>(actualVector.x), 0.0001);
			Assert::AreEqual(static_cast<double>(expectedVector.y), static_cast<double>(actualVector.y), 0.0001);
			Assert::AreEqual(static_cast<double>(expectedVector.z), static_cast<double>(actualVector.z), 0.0001);
			Assert::AreEqual(static_cast<double>(expectedVector.w), static_cast<double>(actualVector.w), 0.0001);
		}

		TEST_METHOD(Vector4EqualityOperatorsTest)
		{
			float x = 10.f;
			float y = 15.f;
			float z = -7.f;
			float w = -15.f;
			auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);
			auto vector1 = PonyEngine::Math::Vector4<float>(x, y, z, w);
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

			vector.z = z;
			vector.w *= -0.5f;
			Assert::IsFalse(vector == vector1);
			Assert::IsTrue(vector != vector1);

			vector = vector1;
			Assert::IsTrue(vector == vector1);
			Assert::IsFalse(vector != vector1);
		}

		TEST_METHOD(Vector4ComputationOperatorsTest)
		{
			float x = 90.f;
			float y = 100.f;
			float z = -80.f;
			float w = -50.f;
			float x1 = -75.f;
			float y1 = 60.f;
			float z1 = -95.f;
			float w1 = 30.f;
			auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);
			auto vector1 = PonyEngine::Math::Vector4<float>(x1, y1, z1, w1);

			auto vector2 = vector + vector1;
			Assert::AreEqual(x + x1, vector2.x);
			Assert::AreEqual(y + y1, vector2.y);
			Assert::AreEqual(z + z1, vector2.z);
			Assert::AreEqual(w + w1, vector2.w);

			vector2 = vector - vector1;
			Assert::AreEqual(x - x1, vector2.x);
			Assert::AreEqual(y - y1, vector2.y);
			Assert::AreEqual(z - z1, vector2.z);
			Assert::AreEqual(w - w1, vector2.w);

			float multiplier = 3.3f;
			vector2 = vector * multiplier;
			Assert::AreEqual(x * multiplier, vector2.x);
			Assert::AreEqual(y * multiplier, vector2.y);
			Assert::AreEqual(z * multiplier, vector2.z);
			Assert::AreEqual(w * multiplier, vector2.w);

			vector2 = multiplier * vector;
			Assert::AreEqual(x * multiplier, vector2.x);
			Assert::AreEqual(y * multiplier, vector2.y);
			Assert::AreEqual(z * multiplier, vector2.z);
			Assert::AreEqual(w * multiplier, vector2.w);

			vector2 = vector / multiplier;
			Assert::AreEqual(x / multiplier, vector2.x);
			Assert::AreEqual(y / multiplier, vector2.y);
			Assert::AreEqual(z / multiplier, vector2.z);
			Assert::AreEqual(w / multiplier, vector2.w);

			vector2 = vector * vector1;
			Assert::AreEqual(x * x1, vector2.x);
			Assert::AreEqual(y * y1, vector2.y);
			Assert::AreEqual(z * z1, vector2.z);
			Assert::AreEqual(w * w1, vector2.w);

			vector2 = vector / vector1;
			Assert::AreEqual(x / x1, vector2.x);
			Assert::AreEqual(y / y1, vector2.y);
			Assert::AreEqual(z / z1, vector2.z);
			Assert::AreEqual(w / w1, vector2.w);
		}

		TEST_METHOD(Vector4DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector4<float>::One == PonyEngine::Math::Vector4<float>(1.f, 1.f, 1.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector4<float>::Zero == PonyEngine::Math::Vector4<float>(0.f, 0.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector4<float>::Negative == PonyEngine::Math::Vector4<float>(-1.f, -1.f, -1.f, -1.f));

			Assert::IsTrue(PonyEngine::Math::Vector4<short>::One == PonyEngine::Math::Vector4<short>(1, 1, 1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector4<short>::Zero == PonyEngine::Math::Vector4<short>(0, 0, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector4<short>::Negative == PonyEngine::Math::Vector4<short>(-1, -1, -1, -1));

			Assert::IsTrue(PonyEngine::Math::Vector4<unsigned char>::One == PonyEngine::Math::Vector4<unsigned char>(1, 1, 1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector4<unsigned char>::Zero == PonyEngine::Math::Vector4<unsigned char>(0, 0, 0, 0));
		}

		TEST_METHOD(Vector4TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyEngine::Math::Vector4<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector4<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyEngine::Math::Vector4<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector4<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyEngine::Math::Vector4<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector4<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector4<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector4<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyEngine::Math::Vector4<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector4<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector4<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector4<double>::ComputationalType>);
		}

		TEST_METHOD(QuaternionTest)
		{
			auto quaternion = PonyEngine::Math::Quaternion<float>::CreateByEuler(PonyEngine::Math::Vector3<float>(400.f, 410.f, 420.f));
			PonyEngine::Math::Vector3<float> vector = quaternion.Euler();
		}
	};
}
