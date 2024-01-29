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
import <cmath>;
import <format>;
import <array>;

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

		TEST_METHOD(Vector2IsFiniteTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Zero.IsFinite());
			float nan = std::numeric_limits<float>::quiet_NaN();
			auto vector = PonyEngine::Math::Vector2<float>(nan, 0.f);
			Assert::IsFalse(vector.IsFinite());
			vector.x = 0.f;
			vector.y = nan;
			Assert::IsFalse(vector.IsFinite());
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
			auto vector0 = PonyEngine::Math::Vector2<double>(3.f, 0.f);
			auto vector1 = PonyEngine::Math::Vector2<double>(0.f, 6.f);
			double expected = 0.;
			double actual = PonyEngine::Math::Project(vector0, vector1).Magnitude();
			Assert::AreEqual(expected, actual);

			vector0.Set(-4., 2.);
			vector1.Set(3., 1.);
			auto expectedVector = PonyEngine::Math::Vector2<double>(-3.f, -1.f);
			auto actualVector = PonyEngine::Math::Project(vector0, vector1);
			Assert::AreEqual(expectedVector.x, actualVector.x, 0.001);
			Assert::AreEqual(expectedVector.y, actualVector.y, 0.001);
			Assert::AreEqual(180., PonyEngine::Math::AngleDegrees(actualVector.Normalized(), vector1.Normalized()), 0.001);
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

		TEST_METHOD(Vector2LerpTest)
		{
			auto vector0 = PonyEngine::Math::Vector2<float>(-2.f, 2.f);
			auto vector1 = PonyEngine::Math::Vector2<float>(2.f, 4.f);
			auto lerped = PonyEngine::Math::Lerp(vector0, vector1, 0.f);
			Assert::AreEqual(vector0.x, lerped.x);
			Assert::AreEqual(vector0.y, lerped.y);

			lerped = PonyEngine::Math::Lerp(vector0, vector1, 1.f);
			Assert::AreEqual(vector1.x, lerped.x);
			Assert::AreEqual(vector1.y, lerped.y);

			lerped = PonyEngine::Math::Lerp(vector0, vector1, 0.5f);
			Assert::AreEqual(0.f, lerped.x);
			Assert::AreEqual(3.f, lerped.y);

			lerped = PonyEngine::Math::Lerp(vector0, vector1, 2.f);
			Assert::AreEqual(6.f, lerped.x);
			Assert::AreEqual(6.f, lerped.y);

			lerped = PonyEngine::Math::Lerp(vector0, vector1, -1.f);
			Assert::AreEqual(-6.f, lerped.x);
			Assert::AreEqual(0.f, lerped.y);
		}

		TEST_METHOD(Vector2AreAlmostEqual)
		{
			auto vector0 = PonyEngine::Math::Vector2<float>(1.f, 1.f);
			auto vector1 = vector0;

			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vector0, vector1));

			vector1.x = std::nextafter(vector1.x, 0.f);
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vector0, vector1));

			vector1.x = 0.f;
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vector0, vector1, 5.f));

			Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(vector0, vector1));
		}

		TEST_METHOD(Vector2AccessOperatorTest)
		{
			float x = 2.f;
			float y = 5.f;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);

			float x1 = 20.f;
			float y1 = 34.f;
			vector[0] = x1;
			vector[1] = y1;
			Assert::AreEqual(x1, vector[0]);
			Assert::AreEqual(y1, vector[1]);

			const auto vectorC = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(x, vectorC[0]);
			Assert::AreEqual(y, vectorC[1]);

			for (size_t i = 0; i < PonyEngine::Math::Vector2<float>::ComponentCount; ++i)
			{
				float num = static_cast<float>(i);
				vector[i] = num;
				Assert::AreEqual(num, vector[i]);
			}
			Assert::AreEqual(static_cast<std::size_t>(2), PonyEngine::Math::Vector2<float>::ComponentCount);
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

		TEST_METHOD(Vector2ToStringTest)
		{
			float x = -2.f;
			float y = 3.f;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			std::string expected = std::format("({}, {})", x, y);
			Assert::AreEqual(expected, vector.ToString());

			std::ostringstream ss;
			ss << vector;
			Assert::AreEqual(expected, ss.str());
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

		TEST_METHOD(Vector2ConstexprTest)
		{
			constexpr auto defaultVector = PonyEngine::Math::Vector2<float>();
			constexpr auto vector = PonyEngine::Math::Vector2<float>(2.f, 3.f);
			constexpr auto copiedVector = vector;
			constexpr auto normal = PonyEngine::Math::Vector2<float>(1.f, 0.f);

			constexpr float magnitudeSquared = vector.MagnitudeSquared();

			constexpr float dot = PonyEngine::Math::Dot(vector, copiedVector);
			constexpr auto project = PonyEngine::Math::Project(vector, normal);
			constexpr auto projectOnPlane = PonyEngine::Math::ProjectOnPlane(vector, normal);
			constexpr auto reflection = PonyEngine::Math::Reflect(vector, normal);

			constexpr bool equal = vector == copiedVector;
			constexpr bool notEqual = vector != copiedVector;

			constexpr auto sum = vector + copiedVector;
			constexpr auto negative = -vector;
			constexpr auto sub = vector - copiedVector;
			constexpr auto multiplied = vector * 2.f;
			constexpr auto multipliedL = 2.f * vector;
			constexpr auto multipliedV = vector * normal;
			constexpr auto divided = vector / 2.f;
			constexpr auto dividedV = vector / copiedVector;
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

		TEST_METHOD(Vector4IsFiniteTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector4<float>::Zero.IsFinite());
			float nan = std::numeric_limits<float>::quiet_NaN();
			auto vector = PonyEngine::Math::Vector4<float>(nan, 0.f, 0.f, 0.f);
			Assert::IsFalse(vector.IsFinite());
			vector.x = 0.f;
			vector.y = nan;
			Assert::IsFalse(vector.IsFinite());
			vector.y = 0.f;
			vector.z = nan;
			Assert::IsFalse(vector.IsFinite());
			vector.z = 0.f;
			vector.w = nan;
			Assert::IsFalse(vector.IsFinite());
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

		TEST_METHOD(Vector4LerpTest)
		{
			auto vector0 = PonyEngine::Math::Vector4<float>(-2.f, 2.f, 4.f, 1.f);
			auto vector1 = PonyEngine::Math::Vector4<float>(2.f, 4.f, -8.f, 3.f);
			auto lerped = PonyEngine::Math::Lerp(vector0, vector1, 0.f);
			Assert::AreEqual(vector0.x, lerped.x);
			Assert::AreEqual(vector0.y, lerped.y);
			Assert::AreEqual(vector0.z, lerped.z);
			Assert::AreEqual(vector0.w, lerped.w);

			lerped = PonyEngine::Math::Lerp(vector0, vector1, 1.f);
			Assert::AreEqual(vector1.x, lerped.x);
			Assert::AreEqual(vector1.y, lerped.y);
			Assert::AreEqual(vector1.z, lerped.z);
			Assert::AreEqual(vector1.w, lerped.w);

			lerped = PonyEngine::Math::Lerp(vector0, vector1, 0.5f);
			Assert::AreEqual(0.f, lerped.x);
			Assert::AreEqual(3.f, lerped.y);
			Assert::AreEqual(-2.f, lerped.z);
			Assert::AreEqual(2.f, lerped.w);

			lerped = PonyEngine::Math::Lerp(vector0, vector1, 2.f);
			Assert::AreEqual(6.f, lerped.x);
			Assert::AreEqual(6.f, lerped.y);
			Assert::AreEqual(-20.f, lerped.z);
			Assert::AreEqual(5.f, lerped.w);

			lerped = PonyEngine::Math::Lerp(vector0, vector1, -1.f);
			Assert::AreEqual(-6.f, lerped.x);
			Assert::AreEqual(0.f, lerped.y);
			Assert::AreEqual(16.f, lerped.z);
			Assert::AreEqual(-1.f, lerped.w);
		}

		TEST_METHOD(Vector4AreAlmostEqual)
		{
			auto vector0 = PonyEngine::Math::Vector4<float>(1.f, 1.f, 1.f, 1.f);
			auto vector1 = vector0;

			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vector0, vector1));

			vector1.x = std::nextafter(vector1.x, 0.f);
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vector0, vector1));

			vector1.x = 0.f;
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vector0, vector1, 5.f));

			Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(vector0, vector1));
		}

		TEST_METHOD(Vector4AccessOperatorTest)
		{
			float x = 2.f;
			float y = 5.f;
			float z = 7.f;
			float w = 9.f;
			auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);
			Assert::AreEqual(z, vector[2]);
			Assert::AreEqual(w, vector[3]);

			float x1 = 20.f;
			float y1 = 34.f;
			float z1 = 55.f;
			float w1 = 77.f;
			vector[0] = x1;
			vector[1] = y1;
			vector[2] = z1;
			vector[3] = w1;
			Assert::AreEqual(x1, vector[0]);
			Assert::AreEqual(y1, vector[1]);
			Assert::AreEqual(z1, vector[2]);
			Assert::AreEqual(w1, vector[3]);

			const auto vectorC = PonyEngine::Math::Vector4<float>(x, y, z, w);
			Assert::AreEqual(x, vectorC[0]);
			Assert::AreEqual(y, vectorC[1]);
			Assert::AreEqual(z, vectorC[2]);
			Assert::AreEqual(w, vectorC[3]);

			for (size_t i = 0; i < PonyEngine::Math::Vector4<float>::ComponentCount; ++i)
			{
				float num = static_cast<float>(i);
				vector[i] = num;
				Assert::AreEqual(num, vector[i]);
			}
			Assert::AreEqual(static_cast<std::size_t>(4), PonyEngine::Math::Vector4<float>::ComponentCount);
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
			Assert::AreEqual(static_cast<double>(x / x1), static_cast<double>(vector2.x), 0.001);
			Assert::AreEqual(static_cast<double>(y / y1), static_cast<double>(vector2.y), 0.001);
			Assert::AreEqual(static_cast<double>(z / z1), static_cast<double>(vector2.z), 0.001);
			Assert::AreEqual(static_cast<double>(w / w1), static_cast<double>(vector2.w), 0.001);
		}

		TEST_METHOD(Vector4ToStringTest)
		{
			float x = 1.f;
			float y = -2.f;
			float z = 3.f;
			float w = -4.f;
			auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);
			std::string expected = std::format("({}, {}, {}, {})", x, y, z, w);
			Assert::AreEqual(expected, vector.ToString());

			std::ostringstream ss;
			ss << vector;
			Assert::AreEqual(expected, ss.str());
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

		TEST_METHOD(Vector4ConstexprTest)
		{
			constexpr auto defaultVector = PonyEngine::Math::Vector4<float>();
			constexpr auto vector = PonyEngine::Math::Vector4<float>(3.f, 1.f, 2.f, 4.f);
			constexpr auto copiedVector = vector;

			constexpr float magnitudeSquared = vector.MagnitudeSquared();

			constexpr float dot = PonyEngine::Math::Dot(vector, copiedVector);
			constexpr auto project = PonyEngine::Math::Project(vector, copiedVector);

			constexpr bool equal = vector == copiedVector;
			constexpr bool notEqual = vector != copiedVector;

			constexpr auto sum = vector + copiedVector;
			constexpr auto negative = -vector;
			constexpr auto sub = vector - copiedVector;
			constexpr auto multiplied = vector * 4.f;
			constexpr auto multipliedL = 4.f * vector;
			constexpr auto multipliedV = vector * copiedVector;
			constexpr auto divided = vector / 4.f;
			constexpr auto dividedV = vector / copiedVector;
		}

		TEST_METHOD(QuaternionConstructionTest)
		{
			auto defaultQuaternion = PonyEngine::Math::Quaternion<float>();
			Assert::AreEqual(0.f, defaultQuaternion.x);
			Assert::AreEqual(0.f, defaultQuaternion.y);
			Assert::AreEqual(0.f, defaultQuaternion.z);
			Assert::AreEqual(0.f, defaultQuaternion.w);

			float x = 4.f;
			float y = 8.f;
			float z = 10.f;
			float w = -13.f;
			auto setQuaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, setQuaternion.x);
			Assert::AreEqual(y, setQuaternion.y);
			Assert::AreEqual(z, setQuaternion.z);
			Assert::AreEqual(w, setQuaternion.w);

			auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);
			auto vectorQuaternion = PonyEngine::Math::Quaternion<float>(vector);
			Assert::AreEqual(x, setQuaternion.x);
			Assert::AreEqual(y, setQuaternion.y);
			Assert::AreEqual(z, setQuaternion.z);
			Assert::AreEqual(w, setQuaternion.w);

			PonyEngine::Math::Quaternion<float> copiedQuaternion = vectorQuaternion;
			Assert::AreEqual(x, copiedQuaternion.x);
			Assert::AreEqual(y, copiedQuaternion.y);
			Assert::AreEqual(z, copiedQuaternion.z);
			Assert::AreEqual(w, copiedQuaternion.w);

			PonyEngine::Math::Quaternion<float> movedQuaternion = std::move(vectorQuaternion);
			Assert::AreEqual(x, movedQuaternion.x);
			Assert::AreEqual(y, movedQuaternion.y);
			Assert::AreEqual(z, movedQuaternion.z);
			Assert::AreEqual(w, movedQuaternion.w);
		}

		TEST_METHOD(QuaternionEulerTest)
		{
			float x = 0.f;
			float y = 0.f;
			float z = 0.f;
			auto quaternion = PonyEngine::Math::Quaternion<float>::CreateByEuler(x, y, z);
			Assert::AreEqual(0.f, quaternion.x);
			Assert::AreEqual(0.f, quaternion.y);
			Assert::AreEqual(0.f, quaternion.z);
			Assert::AreEqual(1.f, quaternion.w);
			auto euler = quaternion.Euler();
			Assert::AreEqual(x, euler.x);
			Assert::AreEqual(y, euler.y);
			Assert::AreEqual(z, euler.z);

			x = 90.f;
			y = 0.f;
			z = 0.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.z), 0.001);

			x = 90.f;
			y = 60.f;
			z = 45.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.701, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.092, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-0.092, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.701, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(90., static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(15., static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(0., static_cast<double>(euler.z), 0.001);

			x = 0.f;
			y = 90.f;
			z = 0.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0., static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.z), 0.001);

			x = 0.f;
			y = 0.f;
			z = 90.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0., static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.z), 0.001);

			x = -90.f;
			y = 0.f;
			z = 0.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.z), 0.001);

			x = -90.f;
			y = -60.f;
			z = -45.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.430, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(-0.561, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-0.561, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.430, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(-90., static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(-105., static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(0., static_cast<double>(euler.z), 0.001);

			x = 0.f;
			y = -90.f;
			z = 0.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0., static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.z), 0.001);

			x = 0.f;
			y = 0.f;
			z = -90.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0., static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.z), 0.001);

			x = 46.f;
			y = 78.f;
			z = 32.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.452, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.473, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-0.039, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.755, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.z), 0.001);

			x = -46.f;
			y = -78.f;
			z = -32.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.132, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(-0.640, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-0.434, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.620, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.z), 0.001);

			x = 146.f;
			y = 178.f;
			z = 132.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.274, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.104, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-0.384, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.876, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(34., static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(-2., static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(-48., static_cast<double>(euler.z), 0.001);

			x = -146.f;
			y = -178.f;
			z = -132.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.260, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(-0.134, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-0.393, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(-0.871, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(-34., static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(2., static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(48., static_cast<double>(euler.z), 0.001);

			x = 200.f;
			y = 220.f;
			z = 265.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.107, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.359, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.669, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.642, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(-20., static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(40., static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(85., static_cast<double>(euler.z), 0.001);

			x = -200.f;
			y = -220.f;
			z = -265.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.348, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.138, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.581, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(-0.722, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(20., static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(-40., static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(-85., static_cast<double>(euler.z), 0.001);

			x = 300.f;
			y = 320.f;
			z = 285.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.192, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.521, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.631, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(-0.541, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(-60., static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(-40., static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(-75., static_cast<double>(euler.z), 0.001);

			x = -300.f;
			y = -320.f;
			z = -285.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.553, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.051, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-0.360, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(-0.750, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(60., static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(40., static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(75., static_cast<double>(euler.z), 0.001);

			x = 400.f;
			y = 500.f;
			z = 600.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.706, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.543, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-0.439, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(-0.118, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(40., static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(140., static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(-120., static_cast<double>(euler.z), 0.001);

			x = -400.f;
			y = -500.f;
			z = -600.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.823, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(-0.340, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.118, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.439, static_cast<double>(quaternion.w), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(-40., static_cast<double>(euler.x), 0.001);
			Assert::AreEqual(-140., static_cast<double>(euler.y), 0.001);
			Assert::AreEqual(120., static_cast<double>(euler.z), 0.001);

			x = 1.f;
			y = 2.f;
			z = 3.f;
			auto quaternion0 = PonyEngine::Math::Quaternion<float>::CreateByEuler(x, y, z);
			auto quaternion1 = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x * PonyEngine::Math::RadToDeg<float>, y * PonyEngine::Math::RadToDeg<float>, z * PonyEngine::Math::RadToDeg<float>);
			auto quaternion2 = PonyEngine::Math::Quaternion<float>::CreateByEuler(PonyEngine::Math::Vector3<float>(x, y, z));
			auto quaternion3 = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(PonyEngine::Math::Vector3<float>(x, y, z) * PonyEngine::Math::RadToDeg<float>);
			Assert::AreEqual(static_cast<double>(quaternion0.x), static_cast<double>(quaternion1.x), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.y), static_cast<double>(quaternion1.y), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.z), static_cast<double>(quaternion1.z), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.w), static_cast<double>(quaternion1.w), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.x), static_cast<double>(quaternion2.x), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.y), static_cast<double>(quaternion2.y), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.z), static_cast<double>(quaternion2.z), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.w), static_cast<double>(quaternion2.w), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.x), static_cast<double>(quaternion3.x), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.y), static_cast<double>(quaternion3.y), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.z), static_cast<double>(quaternion3.z), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.w), static_cast<double>(quaternion3.w), 0.001);

			auto radVector = quaternion0.Euler();
			auto degVector = quaternion0.EulerDegrees();
			Assert::AreEqual(radVector.x * PonyEngine::Math::RadToDeg<float>, degVector.x);
			Assert::AreEqual(radVector.y * PonyEngine::Math::RadToDeg<float>, degVector.y);
			Assert::AreEqual(radVector.z * PonyEngine::Math::RadToDeg<float>, degVector.z);
		}

		TEST_METHOD(QuaternionAxisAngleTest)
		{
			float x = 1.f;
			float y = 2.f;
			float z = 3.f;
			auto axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.x;
			y = axis.y;
			z = axis.z;
			float angle = 1.5f;
			auto quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngle(axis, angle); 
			Assert::AreEqual(0.182, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.364, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.547, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.732, static_cast<double>(quaternion.w), 0.001);
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle * PonyEngine::Math::RadToDeg<float>);
			Assert::AreEqual(0.182, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.364, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.547, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.732, static_cast<double>(quaternion.w), 0.001);
			auto axisAngle = quaternion.AxisAngle();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(axisAngle.first.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(axisAngle.first.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(axisAngle.first.z), 0.001);
			Assert::AreEqual(static_cast<double>(angle), static_cast<double>(axisAngle.second), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(axisAngle.first.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(axisAngle.first.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(axisAngle.first.z), 0.001);
			Assert::AreEqual(static_cast<double>(angle * PonyEngine::Math::RadToDeg<float>), static_cast<double>(axisAngle.second), 0.001);

			x = -x;
			y = -y;
			z = -z;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.x;
			y = axis.y;
			z = axis.z;
			angle = -angle;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngle(axis, angle);
			Assert::AreEqual(0.182, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.364, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.547, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.732, static_cast<double>(quaternion.w), 0.001);
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle * PonyEngine::Math::RadToDeg<float>);
			Assert::AreEqual(0.182, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.364, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.547, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.732, static_cast<double>(quaternion.w), 0.001);
			axisAngle = quaternion.AxisAngle();
			Assert::AreEqual(static_cast<double>(-x), static_cast<double>(axisAngle.first.x), 0.001);
			Assert::AreEqual(static_cast<double>(-y), static_cast<double>(axisAngle.first.y), 0.001);
			Assert::AreEqual(static_cast<double>(-z), static_cast<double>(axisAngle.first.z), 0.001);
			Assert::AreEqual(static_cast<double>(-angle), static_cast<double>(axisAngle.second), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(-x), static_cast<double>(axisAngle.first.x), 0.001);
			Assert::AreEqual(static_cast<double>(-y), static_cast<double>(axisAngle.first.y), 0.001);
			Assert::AreEqual(static_cast<double>(-z), static_cast<double>(axisAngle.first.z), 0.001);
			Assert::AreEqual(static_cast<double>(-angle * PonyEngine::Math::RadToDeg<float>), static_cast<double>(axisAngle.second), 0.001);

			x = -2.f;
			y = 4.f;
			z = 1.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.x;
			y = axis.y;
			z = axis.z;
			angle = 120.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(-0.378, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.756, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.189, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.5, static_cast<double>(quaternion.w), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(axisAngle.first.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(axisAngle.first.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(axisAngle.first.z), 0.001);
			Assert::AreEqual(static_cast<double>(angle), static_cast<double>(axisAngle.second), 0.001);

			x = 3.f;
			y = -4.f;
			z = 3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.x;
			y = axis.y;
			z = axis.z;
			angle = 220.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(0.483, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(-0.644, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.483, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(-0.342, static_cast<double>(quaternion.w), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(axisAngle.first.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(axisAngle.first.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(axisAngle.first.z), 0.001);
			Assert::AreEqual(-140., static_cast<double>(axisAngle.second), 0.001);

			x = 5.f;
			y = 4.f;
			z = -3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.x;
			y = axis.y;
			z = axis.z;
			angle = 300.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(0.354, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.282, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-0.212, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(-0.866, static_cast<double>(quaternion.w), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(axisAngle.first.x), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(axisAngle.first.y), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(axisAngle.first.z), 0.001);
			Assert::AreEqual(-60., static_cast<double>(axisAngle.second), 0.001);

			x = 5.f;
			y = -4.f;
			z = -3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.x;
			y = axis.y;
			z = axis.z;
			angle = -60.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(-0.353, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.283, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.212, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.866, static_cast<double>(quaternion.w), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(-x), static_cast<double>(axisAngle.first.x), 0.001);
			Assert::AreEqual(static_cast<double>(-y), static_cast<double>(axisAngle.first.y), 0.001);
			Assert::AreEqual(static_cast<double>(-z), static_cast<double>(axisAngle.first.z), 0.001);
			Assert::AreEqual(static_cast<double>(-angle), static_cast<double>(axisAngle.second), 0.001);

			x = -5.f;
			y = -4.f;
			z = 3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.x;
			y = axis.y;
			z = axis.z;
			angle = -160.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(0.696, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.557, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-0.418, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(quaternion.w), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(-x), static_cast<double>(axisAngle.first.x), 0.001);
			Assert::AreEqual(static_cast<double>(-y), static_cast<double>(axisAngle.first.y), 0.001);
			Assert::AreEqual(static_cast<double>(-z), static_cast<double>(axisAngle.first.z), 0.001);
			Assert::AreEqual(static_cast<double>(-angle), static_cast<double>(axisAngle.second), 0.001);

			x = -5.f;
			y = -4.f;
			z = -3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.x;
			y = axis.y;
			z = axis.z;
			angle = -260.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(0.542, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.433, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.325, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(-0.643, static_cast<double>(quaternion.w), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(-x), static_cast<double>(axisAngle.first.x), 0.001);
			Assert::AreEqual(static_cast<double>(-y), static_cast<double>(axisAngle.first.y), 0.001);
			Assert::AreEqual(static_cast<double>(-z), static_cast<double>(axisAngle.first.z), 0.001);
			Assert::AreEqual(-100., static_cast<double>(axisAngle.second), 0.001);

			x = 5.f;
			y = 4.f;
			z = 3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.x;
			y = axis.y;
			z = axis.z;
			angle = -300.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(-0.354, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(-0.283, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-0.212, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(-0.866, static_cast<double>(quaternion.w), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(-x), static_cast<double>(axisAngle.first.x), 0.001);
			Assert::AreEqual(static_cast<double>(-y), static_cast<double>(axisAngle.first.y), 0.001);
			Assert::AreEqual(static_cast<double>(-z), static_cast<double>(axisAngle.first.z), 0.001);
			Assert::AreEqual(-60., static_cast<double>(axisAngle.second), 0.001);

			x = 5.f;
			y = 4.f;
			z = 3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.x;
			y = axis.y;
			z = axis.z;
			angle = 0.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(0., static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(1., static_cast<double>(quaternion.w), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::IsTrue(std::isnan(axisAngle.first.x) || axisAngle.first.x == 0.f);
			Assert::IsTrue(std::isnan(axisAngle.first.y) || axisAngle.first.y == 0.f);
			Assert::IsTrue(std::isnan(axisAngle.first.z) || axisAngle.first.z == 0.f);
			Assert::AreEqual(0., static_cast<double>(axisAngle.second), 0.001);
		}

		TEST_METHOD(QuaternionDirectionTest)
		{
			auto from = PonyEngine::Math::Vector3<float>(1.f, 4.f, -3.f).Normalized();
			auto to = PonyEngine::Math::Vector3<float>(-4.f, 2.f, 1.f).Normalized();
			auto quaternion = PonyEngine::Math::Quaternion<float>::CreateByDirection(from, to);
			Assert::AreEqual(0.296, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0.326, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0.533, static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0.722, static_cast<double>(quaternion.w), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>::CreateByDirection(PonyEngine::Math::Vector3<float>::Down, PonyEngine::Math::Vector3<float>::Up);
			Assert::AreEqual(-1., static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.w), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>::CreateByDirection(PonyEngine::Math::Vector3<float>::Left, PonyEngine::Math::Vector3<float>::Right);
			Assert::AreEqual(0., static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(-1., static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.w), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>::CreateByDirection(PonyEngine::Math::Vector3<float>::Down, PonyEngine::Math::Vector3<float>::Down);
			Assert::AreEqual(0., static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(1., static_cast<double>(quaternion.w), 0.001);

			from = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
			auto axis = PonyEngine::Math::Cross(from, PonyEngine::Math::Vector3<float>::Right).Normalized();
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngle(axis, std::acos(std::nextafter(-1.f, 0.f)));
			to = quaternion * from;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByDirection(from, to);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.x), 0.001);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.y), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.z), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.w), 0.001);
		}

		TEST_METHOD(QuaternionMagnutudeTest)
		{
			float x = 4.f;
			float y = 3.f;
			float z = 1.f;
			float w = -3.f;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			float expectedMagnitudeSquared = x * x + y * y + z * z + w * w;
			Assert::AreEqual(expectedMagnitudeSquared, quaternion.MagnitudeSquared());
			Assert::AreEqual(std::sqrt(expectedMagnitudeSquared), quaternion.Magnitude());

			quaternion = PonyEngine::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f);
			Assert::AreEqual(1.f, quaternion.MagnitudeSquared());
			Assert::AreEqual(1.f, quaternion.Magnitude());
		}

		TEST_METHOD(QuaternionConjugationTest)
		{
			float x = 4.f;
			float y = 3.f;
			float z = 1.f;
			float w = -3.f;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			auto conjugated = quaternion.Conjugated();
			Assert::AreEqual(-x, conjugated.x);
			Assert::AreEqual(-y, conjugated.y);
			Assert::AreEqual(-z, conjugated.z);
			Assert::AreEqual(w, conjugated.w);

			quaternion.Conjugate();
			Assert::AreEqual(conjugated.x, quaternion.x);
			Assert::AreEqual(conjugated.y, quaternion.y);
			Assert::AreEqual(conjugated.z, quaternion.z);
			Assert::AreEqual(conjugated.w, quaternion.w);

			quaternion.Normalize();
			conjugated = quaternion.Conjugated();
			auto multiplied = quaternion * conjugated;
			Assert::AreEqual(0., static_cast<double>(multiplied.x), 0.001);
			Assert::AreEqual(0., static_cast<double>(multiplied.y), 0.001);
			Assert::AreEqual(0., static_cast<double>(multiplied.z), 0.001);
			Assert::AreEqual(1., static_cast<double>(multiplied.w), 0.001);
		}

		TEST_METHOD(QuaternionNormalizationTest)
		{
			float x = 4.f;
			float y = 3.f;
			float z = 1.f;
			float w = -3.f;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			auto normalized = quaternion.Normalized();
			Assert::AreEqual(0.676, static_cast<double>(normalized.x), 0.001);
			Assert::AreEqual(0.507, static_cast<double>(normalized.y), 0.001);
			Assert::AreEqual(0.169, static_cast<double>(normalized.z), 0.001);
			Assert::AreEqual(-0.507, static_cast<double>(normalized.w), 0.001);

			quaternion.Normalize();
			Assert::AreEqual(normalized.x, quaternion.x);
			Assert::AreEqual(normalized.y, quaternion.y);
			Assert::AreEqual(normalized.z, quaternion.z);
			Assert::AreEqual(normalized.w, quaternion.w);
		}

		TEST_METHOD(QuaternionIsFiniteTest)
		{
			auto quaternion = PonyEngine::Math::Quaternion<float>();
			Assert::IsTrue(quaternion.IsFinite());
			float nan = std::numeric_limits<float>::quiet_NaN();
			quaternion = PonyEngine::Math::Quaternion<float>(nan, 0.f, 0.f, 0.f);
			Assert::IsFalse(quaternion.IsFinite());
			quaternion.x = 0.f;
			quaternion.y = nan;
			Assert::IsFalse(quaternion.IsFinite());
			quaternion.y = 0.f;
			quaternion.z = nan;
			Assert::IsFalse(quaternion.IsFinite());
			quaternion.z = 0.f;
			quaternion.w = nan;
			Assert::IsFalse(quaternion.IsFinite());
		}

		TEST_METHOD(QuaternionSetTest)
		{
			auto quaternion = PonyEngine::Math::Quaternion<float>::Identity;
			float x = 5.f;
			float y = 1.f;
			float z = -3.f;
			float w = 4.f;
			quaternion.Set(x, y, z, w);
			Assert::AreEqual(x, quaternion.x);
			Assert::AreEqual(y, quaternion.y);
			Assert::AreEqual(z, quaternion.z);
			Assert::AreEqual(w, quaternion.w);
		}

		TEST_METHOD(QuaternionLerpTest)
		{
			auto vector0 = PonyEngine::Math::Quaternion<float>(-2.f, 2.f, 4.f, 1.f);
			auto vector1 = PonyEngine::Math::Quaternion<float>(2.f, 4.f, -8.f, 3.f);
			auto lerped = PonyEngine::Math::Lerp(vector0, vector1, 0.f);
			Assert::AreEqual(vector0.x, lerped.x);
			Assert::AreEqual(vector0.y, lerped.y);
			Assert::AreEqual(vector0.z, lerped.z);
			Assert::AreEqual(vector0.w, lerped.w);

			lerped = PonyEngine::Math::Lerp(vector0, vector1, 1.f);
			Assert::AreEqual(vector1.x, lerped.x);
			Assert::AreEqual(vector1.y, lerped.y);
			Assert::AreEqual(vector1.z, lerped.z);
			Assert::AreEqual(vector1.w, lerped.w);

			lerped = PonyEngine::Math::Lerp(vector0, vector1, 0.5f);
			Assert::AreEqual(0.f, lerped.x);
			Assert::AreEqual(3.f, lerped.y);
			Assert::AreEqual(-2.f, lerped.z);
			Assert::AreEqual(2.f, lerped.w);

			lerped = PonyEngine::Math::Lerp(vector0, vector1, 2.f);
			Assert::AreEqual(6.f, lerped.x);
			Assert::AreEqual(6.f, lerped.y);
			Assert::AreEqual(-20.f, lerped.z);
			Assert::AreEqual(5.f, lerped.w);

			lerped = PonyEngine::Math::Lerp(vector0, vector1, -1.f);
			Assert::AreEqual(-6.f, lerped.x);
			Assert::AreEqual(0.f, lerped.y);
			Assert::AreEqual(16.f, lerped.z);
			Assert::AreEqual(-1.f, lerped.w);
		}

		TEST_METHOD(QuaternionSlerpTest)
		{
			auto quaternion0 = PonyEngine::Math::Quaternion<float>(4.f, 4.f, 4.f, 7.f).Normalized();
			auto quaternion1 = PonyEngine::Math::Quaternion<float>(1.f, 1.f, 10.f, 3.f).Normalized();
			auto slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 0.f);
			Assert::AreEqual(static_cast<double>(quaternion0.x), static_cast<double>(slerped.x), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.y), static_cast<double>(slerped.y), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.z), static_cast<double>(slerped.z), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.w), static_cast<double>(slerped.w), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 1.f);
			Assert::AreEqual(static_cast<double>(quaternion1.x), static_cast<double>(slerped.x), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion1.y), static_cast<double>(slerped.y), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion1.z), static_cast<double>(slerped.z), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion1.w), static_cast<double>(slerped.w), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 0.5f);
			Assert::AreEqual(0.275, static_cast<double>(slerped.x), 0.001);
			Assert::AreEqual(0.275, static_cast<double>(slerped.y), 0.001);
			Assert::AreEqual(0.743, static_cast<double>(slerped.z), 0.001);
			Assert::AreEqual(0.546, static_cast<double>(slerped.w), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion0, 0.5f);
			Assert::AreEqual(static_cast<double>(quaternion0.x), static_cast<double>(slerped.x), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.y), static_cast<double>(slerped.y), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.z), static_cast<double>(slerped.z), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.w), static_cast<double>(slerped.w), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion0, 0.f);
			Assert::AreEqual(static_cast<double>(quaternion0.x), static_cast<double>(slerped.x), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.y), static_cast<double>(slerped.y), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.z), static_cast<double>(slerped.z), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.w), static_cast<double>(slerped.w), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion0, 1.f);
			Assert::AreEqual(static_cast<double>(quaternion0.x), static_cast<double>(slerped.x), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.y), static_cast<double>(slerped.y), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.z), static_cast<double>(slerped.z), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.w), static_cast<double>(slerped.w), 0.001);

			quaternion1 = quaternion0.Conjugated();
			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 0.f);
			Assert::AreEqual(static_cast<double>(quaternion0.x), static_cast<double>(slerped.x), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.y), static_cast<double>(slerped.y), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.z), static_cast<double>(slerped.z), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.w), static_cast<double>(slerped.w), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 1.f);
			Assert::AreEqual(static_cast<double>(quaternion1.x), static_cast<double>(slerped.x), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion1.y), static_cast<double>(slerped.y), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion1.z), static_cast<double>(slerped.z), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion1.w), static_cast<double>(slerped.w), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 0.5f);
			Assert::AreEqual(0., static_cast<double>(slerped.x), 0.001);
			Assert::AreEqual(0., static_cast<double>(slerped.y), 0.001);
			Assert::AreEqual(0., static_cast<double>(slerped.z), 0.001);
			Assert::AreEqual(1., static_cast<double>(slerped.w), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 0.7f);
			Assert::AreEqual(-0.177, static_cast<double>(slerped.x), 0.001);
			Assert::AreEqual(-0.177, static_cast<double>(slerped.y), 0.001);
			Assert::AreEqual(-0.177, static_cast<double>(slerped.z), 0.001);
			Assert::AreEqual(0.952, static_cast<double>(slerped.w), 0.001);
		}

		TEST_METHOD(QuaternionToVector4Test)
		{
			float x = 5.f;
			float y = 1.f;
			float z = -3.f;
			float w = 4.f;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			PonyEngine::Math::Vector4<float> vector = quaternion;
			Assert::AreEqual(x, vector.x);
			Assert::AreEqual(y, vector.y);
			Assert::AreEqual(z, vector.z);
			Assert::AreEqual(w, vector.w);
		}

		TEST_METHOD(QuaternionAccessOperatorTest)
		{
			float x = 2.f;
			float y = 5.f;
			float z = 10.f;
			float w = 3.f;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternion[0]);
			Assert::AreEqual(y, quaternion[1]);
			Assert::AreEqual(z, quaternion[2]);
			Assert::AreEqual(w, quaternion[3]);

			float x1 = 20.f;
			float y1 = 34.f;
			float z1 = 55.f;
			float w1 = 33.f;
			quaternion[0] = x1;
			quaternion[1] = y1;
			quaternion[2] = z1;
			quaternion[3] = w1;
			Assert::AreEqual(x1, quaternion[0]);
			Assert::AreEqual(y1, quaternion[1]);
			Assert::AreEqual(z1, quaternion[2]);
			Assert::AreEqual(w1, quaternion[3]);

			const auto quaternionC = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternionC[0]);
			Assert::AreEqual(y, quaternionC[1]);
			Assert::AreEqual(z, quaternionC[2]);
			Assert::AreEqual(w, quaternionC[3]);

			for (size_t i = 0; i < PonyEngine::Math::Quaternion<float>::ComponentCount; ++i)
			{
				float num = static_cast<float>(i);
				quaternion[i] = num;
				Assert::AreEqual(num, quaternion[i]);
			}
			Assert::AreEqual(static_cast<std::size_t>(4), PonyEngine::Math::Quaternion<float>::ComponentCount);
		}

		TEST_METHOD(QuaternionAreAlmostEqual)
		{
			auto quaternion0 = PonyEngine::Math::Quaternion<float>(1.f, 1.f, 1.f, 1.f);
			auto quaternion1 = quaternion0;

			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(quaternion0, quaternion1));

			quaternion1.x = std::nextafter(quaternion1.x, 0.f);
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(quaternion0, quaternion1));

			quaternion1.x = 0.f;
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(quaternion0, quaternion1, 5.f));

			Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(quaternion0, quaternion1));

			quaternion0.Normalize();
			quaternion1 = quaternion0;

			Assert::IsTrue(PonyEngine::Math::AreAlmostEqualNormalized(quaternion0, quaternion1));

			quaternion1.x = std::nextafter(quaternion1.x, 0.f);
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqualNormalized(quaternion0, quaternion1));

			quaternion1.x = 0.f;
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqualNormalized(quaternion0, quaternion1, 5.f));

			Assert::IsFalse(PonyEngine::Math::AreAlmostEqualNormalized(quaternion0, quaternion1));
		}

		TEST_METHOD(QuaternionEqualityOperatorsTest)
		{
			float x = 3.f;
			float y = 4.f;
			float z = 1.f;
			float w = 2.f;
			auto quaternion0 = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			auto quaternion1 = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::IsTrue(quaternion0 == quaternion1);
			Assert::IsFalse(quaternion0 != quaternion1);

			quaternion1.x += 1.f;
			Assert::IsFalse(quaternion0 == quaternion1);
			Assert::IsTrue(quaternion0 != quaternion1);

			quaternion1.x = x;
			quaternion1.y += 1.f;
			Assert::IsFalse(quaternion0 == quaternion1);
			Assert::IsTrue(quaternion0 != quaternion1);

			quaternion1.y = y;
			quaternion1.z += 1.f;
			Assert::IsFalse(quaternion0 == quaternion1);
			Assert::IsTrue(quaternion0 != quaternion1);

			quaternion1.z = z;
			quaternion1.w += 1.f;
			Assert::IsFalse(quaternion0 == quaternion1);
			Assert::IsTrue(quaternion0 != quaternion1);
		}

		TEST_METHOD(QuaternionMultiplicationTest)
		{
			auto quaternion0 = PonyEngine::Math::Quaternion<float>(0.5f, 1.f, 2.f, -1.f);
			auto quaternion1 = PonyEngine::Math::Quaternion<float>(-0.7f, 2.f, -5.f, 1.f);
			auto quaternion2 = quaternion0 * quaternion1;
			Assert::AreEqual(-7.8, static_cast<double>(quaternion2.x), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(quaternion2.y), 0.001);
			Assert::AreEqual(8.7, static_cast<double>(quaternion2.z), 0.001);
			Assert::AreEqual(7.35, static_cast<double>(quaternion2.w), 0.001);

			quaternion0.Normalize();
			quaternion1.Normalize();
			quaternion2 = quaternion0 * quaternion1;
			Assert::AreEqual(-0.565, static_cast<double>(quaternion2.x), 0.001);
			Assert::AreEqual(0.007, static_cast<double>(quaternion2.y), 0.001);
			Assert::AreEqual(0.630, static_cast<double>(quaternion2.z), 0.001);
			Assert::AreEqual(0.532, static_cast<double>(quaternion2.w), 0.001);

			quaternion2 = PonyEngine::Math::Quaternion<float>::Identity * PonyEngine::Math::Quaternion<float>::Identity;
			Assert::AreEqual(0.f, quaternion2.x);
			Assert::AreEqual(0.f, quaternion2.y);
			Assert::AreEqual(0.f, quaternion2.z);
			Assert::AreEqual(1.f, quaternion2.w);
		}

		TEST_METHOD(QuaternionVectorMultiplicationTest)
		{
			auto quaternion = PonyEngine::Math::Quaternion<float>(4.f, 3.f, 1.f, -3.f);
			auto vector = PonyEngine::Math::Vector3<float>(-4.f, 7.f, 8.f);
			auto rotated = quaternion * vector;
			Assert::AreEqual(206., static_cast<double>(rotated.x), 0.001);
			Assert::AreEqual(-63., static_cast<double>(rotated.y), 0.001);
			Assert::AreEqual(-622., static_cast<double>(rotated.z), 0.001);

			quaternion.Normalize();
			rotated = quaternion * vector;
			Assert::AreEqual(2., static_cast<double>(rotated.x), 0.001);
			Assert::AreEqual(5., static_cast<double>(rotated.y), 0.001);
			Assert::AreEqual(-10., static_cast<double>(rotated.z), 0.001);

			rotated = PonyEngine::Math::Quaternion<float>::Identity * vector;
			Assert::AreEqual(vector.x, rotated.x);
			Assert::AreEqual(vector.y, rotated.y);
			Assert::AreEqual(vector.z, rotated.z);
		}

		TEST_METHOD(QuaternionAssignmentTest)
		{
			auto quaternion0 = PonyEngine::Math::Quaternion<float>();
			auto quaternion1 = PonyEngine::Math::Quaternion<float>(-0.7f, 2.f, -5.f, 1.f);
			auto quaternion2 = quaternion0 = quaternion1;
			Assert::AreEqual(quaternion1.x, quaternion0.x);
			Assert::AreEqual(quaternion1.y, quaternion0.y);
			Assert::AreEqual(quaternion1.z, quaternion0.z);
			Assert::AreEqual(quaternion1.w, quaternion0.w);
			Assert::AreEqual(quaternion2.x, quaternion0.x);
			Assert::AreEqual(quaternion2.y, quaternion0.y);
			Assert::AreEqual(quaternion2.z, quaternion0.z);
			Assert::AreEqual(quaternion2.w, quaternion0.w);

			quaternion0 = PonyEngine::Math::Quaternion<float>(4.f, 3.f, 1.f, -3.f);
			quaternion2 = quaternion0 * quaternion1;
			auto quaternion3 = quaternion0 *= quaternion1;
			Assert::AreEqual(quaternion0.x, quaternion2.x);
			Assert::AreEqual(quaternion0.y, quaternion2.y);
			Assert::AreEqual(quaternion0.z, quaternion2.z);
			Assert::AreEqual(quaternion0.w, quaternion2.w);
			Assert::AreEqual(quaternion3.x, quaternion2.x);
			Assert::AreEqual(quaternion3.y, quaternion2.y);
			Assert::AreEqual(quaternion3.z, quaternion2.z);
			Assert::AreEqual(quaternion3.w, quaternion2.w);
		}

		TEST_METHOD(QuaternionDotTest)
		{
			auto quaternion0 = PonyEngine::Math::Quaternion<float>(2.f, 3.f, -1.f, 7.f);
			auto quaternion1 = PonyEngine::Math::Quaternion<float>(-2.f, -5.f, 2.f, 10.f);
			float expected = quaternion0.x * quaternion1.x + quaternion0.y * quaternion1.y + 
				quaternion0.z * quaternion1.z + quaternion0.w * quaternion1.w;
			Assert::AreEqual(expected, PonyEngine::Math::Dot(quaternion0, quaternion1)); 

			Assert::AreEqual(1.f, PonyEngine::Math::Dot(PonyEngine::Math::Quaternion<float>::Identity, PonyEngine::Math::Quaternion<float>::Identity));
		}

		TEST_METHOD(QuaternionAngleTest)
		{
			auto quaternion0 = PonyEngine::Math::Quaternion<double>(3.f, 2.f, -9.f, -6.f).Normalized();
			auto quaternion1 = PonyEngine::Math::Quaternion<double>(1.f, -2.f, -7.f, 3.f).Normalized();
			Assert::AreEqual(2.126, PonyEngine::Math::Angle(quaternion0, quaternion1), 0.001);
			Assert::AreEqual(121.818, PonyEngine::Math::AngleDegrees(quaternion0, quaternion1), 0.001);

			quaternion1 = quaternion0;
			Assert::AreEqual(0., PonyEngine::Math::Angle(quaternion0, quaternion1));
			Assert::AreEqual(0., PonyEngine::Math::AngleDegrees(quaternion0, quaternion1));
		}

		TEST_METHOD(QuaternionToStringTest)
		{
			float x = -3.f;
			float y = 3.f;
			float z = 2.f;
			float w = -2.f;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			std::string expected = std::format("({}, {}, {}, {})", x, y, z, w);
			Assert::AreEqual(expected, quaternion.ToString());

			std::ostringstream ss;
			ss << quaternion;
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(QuaternionDefaultTest)
		{
			auto identityF = PonyEngine::Math::Quaternion<float>::Identity;
			Assert::AreEqual(0.f, identityF.x);
			Assert::AreEqual(0.f, identityF.y);
			Assert::AreEqual(0.f, identityF.y);
			Assert::AreEqual(1.f, identityF.w);

			auto identityD = PonyEngine::Math::Quaternion<double>::Identity;
			Assert::AreEqual(0., identityD.x);
			Assert::AreEqual(0., identityD.y);
			Assert::AreEqual(0., identityD.y);
			Assert::AreEqual(1., identityD.w);
		}

		TEST_METHOD(QuaternionValueTypeTest)
		{
			Assert::IsTrue(std::is_same_v<PonyEngine::Math::Quaternion<float>::ValueType, float>);
			Assert::IsTrue(std::is_same_v<PonyEngine::Math::Quaternion<double>::ValueType, double>);
		}

		TEST_METHOD(QuaternionConstexprTest)
		{
			constexpr auto vector3 = PonyEngine::Math::Vector3<float>(3.f, 2.f, 1.f);
			constexpr auto vector4 = PonyEngine::Math::Vector4<float>(1.f, 1.f, 1.f, 2.f);
			constexpr auto defaultQuaternion = PonyEngine::Math::Quaternion<float>();
			constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(1.f, 2.f, 3.f, 4.f);
			constexpr auto quaternionV = PonyEngine::Math::Quaternion<float>(vector4);
			constexpr auto copiedQuaternion = quaternion;

			constexpr float magnitudeSquared = quaternion.MagnitudeSquared();
			constexpr auto conjugated = quaternion.Conjugated();
			constexpr PonyEngine::Math::Vector4<float> vectorQ = quaternion;

			constexpr float dot = PonyEngine::Math::Dot(quaternion, quaternionV);

			constexpr bool equal = quaternion == copiedQuaternion;
			constexpr bool notEqual = quaternion != copiedQuaternion;

			constexpr auto rotatedQ = quaternion * copiedQuaternion;
			constexpr auto rotatedV = quaternion * vector3;
		}
	};
}
