/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <format>;

import PonyEngine.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(QuaternionTests)
	{
		TEST_METHOD(QuaternionConstructionTest)
		{
			auto defaultQuaternion = PonyEngine::Math::Quaternion<float>();
			Assert::AreEqual(0.f, defaultQuaternion.X());
			Assert::AreEqual(0.f, defaultQuaternion.Y());
			Assert::AreEqual(0.f, defaultQuaternion.Z());
			Assert::AreEqual(0.f, defaultQuaternion.W());

			float x = 4.f;
			float y = 8.f;
			float z = 10.f;
			float w = -13.f;
			auto setQuaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, setQuaternion.X());
			Assert::AreEqual(y, setQuaternion.Y());
			Assert::AreEqual(z, setQuaternion.Z());
			Assert::AreEqual(w, setQuaternion.W());

			auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);
			auto vectorQuaternion = PonyEngine::Math::Quaternion<float>(vector);
			Assert::AreEqual(x, setQuaternion.X());
			Assert::AreEqual(y, setQuaternion.Y());
			Assert::AreEqual(z, setQuaternion.Z());
			Assert::AreEqual(w, setQuaternion.W());

			PonyEngine::Math::Quaternion<float> copiedQuaternion = vectorQuaternion;
			Assert::AreEqual(x, copiedQuaternion.X());
			Assert::AreEqual(y, copiedQuaternion.Y());
			Assert::AreEqual(z, copiedQuaternion.Z());
			Assert::AreEqual(w, copiedQuaternion.W());

			PonyEngine::Math::Quaternion<float> movedQuaternion = std::move(vectorQuaternion);
			Assert::AreEqual(x, movedQuaternion.X());
			Assert::AreEqual(y, movedQuaternion.Y());
			Assert::AreEqual(z, movedQuaternion.Z());
			Assert::AreEqual(w, movedQuaternion.W());
		}

		TEST_METHOD(DataTest)
		{
			float xf = 4.f;
			float yf = -14.f;
			float zf = 7.f;
			float wf = -6.f;
			auto floatQuaternion = PonyEngine::Math::Quaternion<float>(xf, yf, zf, wf);
			Assert::AreEqual(floatQuaternion.X(), floatQuaternion.Data()[0]);
			Assert::AreEqual(floatQuaternion.Y(), floatQuaternion.Data()[1]);
			Assert::AreEqual(floatQuaternion.Z(), floatQuaternion.Data()[2]);
			Assert::AreEqual(floatQuaternion.W(), floatQuaternion.Data()[3]);
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
			auto conjugate = quaternion.Conjugate();
			Assert::AreEqual(-x, conjugate.X());
			Assert::AreEqual(-y, conjugate.Y());
			Assert::AreEqual(-z, conjugate.Z());
			Assert::AreEqual(w, conjugate.W());

			quaternion.Normalize();
			conjugate = quaternion.Conjugate();
			auto multiplied = quaternion * conjugate;
			Assert::AreEqual(0., static_cast<double>(multiplied.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(multiplied.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(multiplied.Z()), 0.001);
			Assert::AreEqual(1., static_cast<double>(multiplied.W()), 0.001);
		}

		TEST_METHOD(QuaternionNormalizationTest)
		{
			float x = 4.f;
			float y = 3.f;
			float z = 1.f;
			float w = -3.f;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			auto normalized = quaternion.Normalized();
			Assert::AreEqual(0.676, static_cast<double>(normalized.X()), 0.001);
			Assert::AreEqual(0.507, static_cast<double>(normalized.Y()), 0.001);
			Assert::AreEqual(0.169, static_cast<double>(normalized.Z()), 0.001);
			Assert::AreEqual(-0.507, static_cast<double>(normalized.W()), 0.001);

			quaternion.Normalize();
			Assert::AreEqual(normalized.X(), quaternion.X());
			Assert::AreEqual(normalized.Y(), quaternion.Y());
			Assert::AreEqual(normalized.Z(), quaternion.Z());
			Assert::AreEqual(normalized.W(), quaternion.W());
		}

		TEST_METHOD(QuaternionIsFiniteTest)
		{
			auto quaternion = PonyEngine::Math::Quaternion<float>();
			Assert::IsTrue(quaternion.IsFinite());
			float nan = std::numeric_limits<float>::quiet_NaN();
			quaternion = PonyEngine::Math::Quaternion<float>(nan, 0.f, 0.f, 0.f);
			Assert::IsFalse(quaternion.IsFinite());
			quaternion.X() = 0.f;
			quaternion.Y() = nan;
			Assert::IsFalse(quaternion.IsFinite());
			quaternion.Y() = 0.f;
			quaternion.Z() = nan;
			Assert::IsFalse(quaternion.IsFinite());
			quaternion.Z() = 0.f;
			quaternion.W() = nan;
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
			Assert::AreEqual(x, quaternion.X());
			Assert::AreEqual(y, quaternion.Y());
			Assert::AreEqual(z, quaternion.Z());
			Assert::AreEqual(w, quaternion.W());
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

		TEST_METHOD(QuaternionToVector4Test)
		{
			float x = 5.f;
			float y = 1.f;
			float z = -3.f;
			float w = 4.f;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			PonyEngine::Math::Vector4<float> vector = quaternion;
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
			Assert::AreEqual(w, vector.W());
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

			Assert::AreEqual(std::size_t{4}, PonyEngine::Math::Quaternion<float>::ComponentCount);
		}

		TEST_METHOD(QuaternionLerpTest)
		{
			auto vector0 = PonyEngine::Math::Quaternion<float>(-2.f, 2.f, 4.f, 1.f);
			auto vector1 = PonyEngine::Math::Quaternion<float>(2.f, 4.f, -8.f, 3.f);
			auto lerped = PonyEngine::Math::Lerp(vector0, vector1, 0.f);
			Assert::AreEqual(vector0.X(), lerped.X());
			Assert::AreEqual(vector0.Y(), lerped.Y());
			Assert::AreEqual(vector0.Z(), lerped.Z());
			Assert::AreEqual(vector0.W(), lerped.W());

			lerped = PonyEngine::Math::Lerp(vector0, vector1, 1.f);
			Assert::AreEqual(vector1.X(), lerped.X());
			Assert::AreEqual(vector1.Y(), lerped.Y());
			Assert::AreEqual(vector1.Z(), lerped.Z());
			Assert::AreEqual(vector1.W(), lerped.W());

			lerped = PonyEngine::Math::Lerp(vector0, vector1, 0.5f);
			Assert::AreEqual(0.f, lerped.X());
			Assert::AreEqual(3.f, lerped.Y());
			Assert::AreEqual(-2.f, lerped.Z());
			Assert::AreEqual(2.f, lerped.W());

			lerped = PonyEngine::Math::Lerp(vector0, vector1, 2.f);
			Assert::AreEqual(6.f, lerped.X());
			Assert::AreEqual(6.f, lerped.Y());
			Assert::AreEqual(-20.f, lerped.Z());
			Assert::AreEqual(5.f, lerped.W());

			lerped = PonyEngine::Math::Lerp(vector0, vector1, -1.f);
			Assert::AreEqual(-6.f, lerped.X());
			Assert::AreEqual(0.f, lerped.Y());
			Assert::AreEqual(16.f, lerped.Z());
			Assert::AreEqual(-1.f, lerped.W());
		}

		TEST_METHOD(QuaternionSlerpTest)
		{
			auto quaternion0 = PonyEngine::Math::Quaternion<float>(4.f, 4.f, 4.f, 7.f).Normalized();
			auto quaternion1 = PonyEngine::Math::Quaternion<float>(1.f, 1.f, 10.f, 3.f).Normalized();
			auto slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 0.f);
			Assert::AreEqual(static_cast<double>(quaternion0.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.W()), static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 1.f);
			Assert::AreEqual(static_cast<double>(quaternion1.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion1.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion1.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion1.W()), static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 0.5f);
			Assert::AreEqual(0.275, static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(0.275, static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(0.743, static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(0.546, static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion0, 0.5f);
			Assert::AreEqual(static_cast<double>(quaternion0.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.W()), static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion0, 0.f);
			Assert::AreEqual(static_cast<double>(quaternion0.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.W()), static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion0, 1.f);
			Assert::AreEqual(static_cast<double>(quaternion0.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.W()), static_cast<double>(slerped.W()), 0.001);

			quaternion1 = quaternion0.Conjugate();
			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 0.f);
			Assert::AreEqual(static_cast<double>(quaternion0.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.W()), static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 1.f);
			Assert::AreEqual(static_cast<double>(quaternion1.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion1.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion1.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion1.W()), static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 0.5f);
			Assert::AreEqual(0., static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(1., static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternion0, quaternion1, 0.7f);
			Assert::AreEqual(-0.177, static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(-0.177, static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(-0.177, static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(0.952, static_cast<double>(slerped.W()), 0.001);
		}

		TEST_METHOD(QuaternionAreAlmostEqual)
		{
			auto quaternion0 = PonyEngine::Math::Quaternion<float>(1.f, 1.f, 1.f, 1.f);
			auto quaternion1 = quaternion0;

			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(quaternion0, quaternion1));

			quaternion1.X() = std::nextafter(quaternion1.X(), 0.f);
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(quaternion0, quaternion1));

			quaternion1.X() = 0.f;
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(quaternion0, quaternion1, 5.f));

			Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(quaternion0, quaternion1));

			quaternion0.Normalize();
			quaternion1 = quaternion0;

			Assert::IsTrue(PonyEngine::Math::AreAlmostEqualNormalized(quaternion0, quaternion1));

			quaternion1.X() = std::nextafter(quaternion1.X(), 0.f);
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqualNormalized(quaternion0, quaternion1));

			quaternion1.X() = 0.f;
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

			quaternion1.X() += 1.f;
			Assert::IsFalse(quaternion0 == quaternion1);
			Assert::IsTrue(quaternion0 != quaternion1);

			quaternion1.X() = x;
			quaternion1.Y() += 1.f;
			Assert::IsFalse(quaternion0 == quaternion1);
			Assert::IsTrue(quaternion0 != quaternion1);

			quaternion1.Y() = y;
			quaternion1.Z() += 1.f;
			Assert::IsFalse(quaternion0 == quaternion1);
			Assert::IsTrue(quaternion0 != quaternion1);

			quaternion1.Z() = z;
			quaternion1.W() += 1.f;
			Assert::IsFalse(quaternion0 == quaternion1);
			Assert::IsTrue(quaternion0 != quaternion1);
		}

		TEST_METHOD(QuaternionMultiplicationTest)
		{
			auto quaternion0 = PonyEngine::Math::Quaternion<float>(0.5f, 1.f, 2.f, -1.f);
			auto quaternion1 = PonyEngine::Math::Quaternion<float>(-0.7f, 2.f, -5.f, 1.f);
			auto quaternion2 = quaternion0 * quaternion1;
			Assert::AreEqual(-7.8, static_cast<double>(quaternion2.X()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(quaternion2.Y()), 0.001);
			Assert::AreEqual(8.7, static_cast<double>(quaternion2.Z()), 0.001);
			Assert::AreEqual(7.35, static_cast<double>(quaternion2.W()), 0.001);

			quaternion0.Normalize();
			quaternion1.Normalize();
			quaternion2 = quaternion0 * quaternion1;
			Assert::AreEqual(-0.565, static_cast<double>(quaternion2.X()), 0.001);
			Assert::AreEqual(0.007, static_cast<double>(quaternion2.Y()), 0.001);
			Assert::AreEqual(0.630, static_cast<double>(quaternion2.Z()), 0.001);
			Assert::AreEqual(0.532, static_cast<double>(quaternion2.W()), 0.001);

			quaternion2 = PonyEngine::Math::Quaternion<float>::Identity * PonyEngine::Math::Quaternion<float>::Identity;
			Assert::AreEqual(0.f, quaternion2.X());
			Assert::AreEqual(0.f, quaternion2.Y());
			Assert::AreEqual(0.f, quaternion2.Z());
			Assert::AreEqual(1.f, quaternion2.W());
		}

		TEST_METHOD(QuaternionVectorMultiplicationTest)
		{
			auto quaternion = PonyEngine::Math::Quaternion<float>(4.f, 3.f, 1.f, -3.f);
			auto vector = PonyEngine::Math::Vector3<float>(-4.f, 7.f, 8.f);
			auto rotated = quaternion * vector;
			Assert::AreEqual(206., static_cast<double>(rotated.X()), 0.001);
			Assert::AreEqual(-63., static_cast<double>(rotated.Y()), 0.001);
			Assert::AreEqual(-622., static_cast<double>(rotated.Z()), 0.001);

			quaternion.Normalize();
			rotated = quaternion * vector;
			Assert::AreEqual(2., static_cast<double>(rotated.X()), 0.001);
			Assert::AreEqual(5., static_cast<double>(rotated.Y()), 0.001);
			Assert::AreEqual(-10., static_cast<double>(rotated.Z()), 0.001);

			rotated = PonyEngine::Math::Quaternion<float>::Identity * vector;
			Assert::AreEqual(vector.X(), rotated.X());
			Assert::AreEqual(vector.Y(), rotated.Y());
			Assert::AreEqual(vector.Z(), rotated.Z());
		}

		TEST_METHOD(QuaternionAssignmentTest)
		{
			auto quaternion0 = PonyEngine::Math::Quaternion<float>();
			auto quaternion1 = PonyEngine::Math::Quaternion<float>(-0.7f, 2.f, -5.f, 1.f);
			auto quaternion2 = quaternion0 = quaternion1;
			Assert::AreEqual(quaternion1.X(), quaternion0.X());
			Assert::AreEqual(quaternion1.Y(), quaternion0.Y());
			Assert::AreEqual(quaternion1.Z(), quaternion0.Z());
			Assert::AreEqual(quaternion1.W(), quaternion0.W());
			Assert::AreEqual(quaternion2.X(), quaternion0.X());
			Assert::AreEqual(quaternion2.Y(), quaternion0.Y());
			Assert::AreEqual(quaternion2.Z(), quaternion0.Z());
			Assert::AreEqual(quaternion2.W(), quaternion0.W());

			quaternion0 = PonyEngine::Math::Quaternion<float>(4.f, 3.f, 1.f, -3.f);
			quaternion2 = quaternion0 * quaternion1;
			auto quaternion3 = quaternion0 *= quaternion1;
			Assert::AreEqual(quaternion0.X(), quaternion2.X());
			Assert::AreEqual(quaternion0.Y(), quaternion2.Y());
			Assert::AreEqual(quaternion0.Z(), quaternion2.Z());
			Assert::AreEqual(quaternion0.W(), quaternion2.W());
			Assert::AreEqual(quaternion3.X(), quaternion2.X());
			Assert::AreEqual(quaternion3.Y(), quaternion2.Y());
			Assert::AreEqual(quaternion3.Z(), quaternion2.Z());
			Assert::AreEqual(quaternion3.W(), quaternion2.W());
		}

		TEST_METHOD(QuaternionDotTest)
		{
			auto quaternion0 = PonyEngine::Math::Quaternion<float>(2.f, 3.f, -1.f, 7.f);
			auto quaternion1 = PonyEngine::Math::Quaternion<float>(-2.f, -5.f, 2.f, 10.f);
			float expected = quaternion0.X() * quaternion1.X() + quaternion0.Y() * quaternion1.Y() +
				quaternion0.Z() * quaternion1.Z() + quaternion0.W() * quaternion1.W();
			Assert::AreEqual(expected, PonyEngine::Math::Dot(quaternion0, quaternion1));

			Assert::AreEqual(1.f, PonyEngine::Math::Dot(PonyEngine::Math::Quaternion<float>::Identity, PonyEngine::Math::Quaternion<float>::Identity));
		}

		TEST_METHOD(QuaternionAngleTest)
		{
			auto quaternion0 = PonyEngine::Math::Quaternion<double>(3.f, 2.f, -9.f, -6.f).Normalized();
			auto quaternion1 = PonyEngine::Math::Quaternion<double>(1.f, -2.f, -7.f, 3.f).Normalized();
			Assert::AreEqual(2.126, PonyEngine::Math::Angle(quaternion0, quaternion1), 0.001);

			quaternion1 = quaternion0;
			Assert::AreEqual(0., PonyEngine::Math::Angle(quaternion0, quaternion1));
		}

		TEST_METHOD(QuaternionDefaultTest)
		{
			auto identityF = PonyEngine::Math::Quaternion<float>::Identity;
			Assert::AreEqual(0.f, identityF.X());
			Assert::AreEqual(0.f, identityF.Y());
			Assert::AreEqual(0.f, identityF.Y());
			Assert::AreEqual(1.f, identityF.W());

			auto identityD = PonyEngine::Math::Quaternion<double>::Identity;
			Assert::AreEqual(0., identityD.X());
			Assert::AreEqual(0., identityD.Y());
			Assert::AreEqual(0., identityD.Y());
			Assert::AreEqual(1., identityD.W());
		}

		TEST_METHOD(QuaternionValueTypeTest)
		{
			Assert::IsTrue(std::is_same_v<PonyEngine::Math::Quaternion<float>::ValueType, float>);
			Assert::IsTrue(std::is_same_v<PonyEngine::Math::Quaternion<double>::ValueType, double>);
		}

		TEST_METHOD(QuaternionConstexprTest)
		{
#pragma warning(disable:4189)
			constexpr auto vector3 = PonyEngine::Math::Vector3<float>(3.f, 2.f, 1.f);
			constexpr auto vector4 = PonyEngine::Math::Vector4<float>(1.f, 1.f, 1.f, 2.f);
			constexpr auto defaultQuaternion = PonyEngine::Math::Quaternion<float>();
			constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(1.f, 2.f, 3.f, 4.f);
			constexpr auto quaternionV = PonyEngine::Math::Quaternion<float>(vector4);
			constexpr auto copiedQuaternion = quaternion;

			constexpr auto x = quaternion.X();
			constexpr auto y = quaternion.Y();
			constexpr auto z = quaternion.Z();
			constexpr auto w = quaternion.W();

			static constexpr PonyEngine::Math::Quaternion<float> StaticQuaternion(0.f, 1.f, 0.f, 0.f);
			constexpr auto pointer = StaticQuaternion.Data();

			constexpr auto identity = PonyEngine::Math::Quaternion<float>::IdentityConsteval();
			Assert::AreEqual(0.f, identity.X());
			Assert::AreEqual(0.f, identity.Y());
			Assert::AreEqual(0.f, identity.Z());
			Assert::AreEqual(1.f, identity.W());

			constexpr float magnitudeSquared = quaternion.MagnitudeSquared();
			constexpr auto conjugated = quaternion.Conjugate();
			constexpr PonyEngine::Math::Vector4<float> vectorQ = quaternion;

			constexpr float dot = PonyEngine::Math::Dot(quaternion, quaternionV);

			constexpr auto lerped = PonyEngine::Math::Lerp(quaternion, copiedQuaternion, 0.5f);

			constexpr bool areAlmostEqual = PonyEngine::Math::AreAlmostEqual(quaternion, copiedQuaternion);

			constexpr auto component = quaternion[1];

			constexpr bool equal = quaternion == copiedQuaternion;
			constexpr bool notEqual = quaternion != copiedQuaternion;

			constexpr auto rotatedQ = quaternion * copiedQuaternion;
			constexpr auto rotatedV = quaternion * vector3;
#pragma warning(default:4189)
		}
	};
}
