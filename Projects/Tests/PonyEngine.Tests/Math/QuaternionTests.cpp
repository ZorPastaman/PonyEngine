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
import <numbers>;

import PonyEngine.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(QuaternionTests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Quaternion<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Quaternion<double>::ValueType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{4}, PonyEngine::Math::Quaternion<float>::ComponentCount);
		}

		TEST_METHOD(DefaultConstructorTest)
		{
			auto quaternion = PonyEngine::Math::Quaternion<float>();
			Assert::AreEqual(float{}, quaternion.X());
			Assert::AreEqual(float{}, quaternion.Y());
			Assert::AreEqual(float{}, quaternion.Z());
			Assert::AreEqual(float{}, quaternion.W());
		}

		TEST_METHOD(ConstructorTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternion.X());
			Assert::AreEqual(y, quaternion.Y());
			Assert::AreEqual(z, quaternion.Z());
			Assert::AreEqual(w, quaternion.W());
		}

		TEST_METHOD(ConstructorPointerTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyEngine::Math::Quaternion<float>(std::array<float, 4>{x, y, z, w}.data());
			Assert::AreEqual(x, quaternion.X());
			Assert::AreEqual(y, quaternion.Y());
			Assert::AreEqual(z, quaternion.Z());
			Assert::AreEqual(w, quaternion.W());
		}

		TEST_METHOD(ConstructorVectorTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			constexpr auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);
			PonyEngine::Math::Quaternion<float> quaternion = vector;
			Assert::AreEqual(x, quaternion.X());
			Assert::AreEqual(y, quaternion.Y());
			Assert::AreEqual(z, quaternion.Z());
			Assert::AreEqual(w, quaternion.W());
		}

		TEST_METHOD(CopyConstructorTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			PonyEngine::Math::Quaternion<float> copiedQuaternion = quaternion;
			Assert::AreEqual(x, copiedQuaternion.X());
			Assert::AreEqual(y, copiedQuaternion.Y());
			Assert::AreEqual(z, copiedQuaternion.Z());
			Assert::AreEqual(w, copiedQuaternion.W());
		}

		TEST_METHOD(MoveConstructorTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			PonyEngine::Math::Quaternion<float> copiedQuaternion = std::move(quaternion);
			Assert::AreEqual(x, copiedQuaternion.X());
			Assert::AreEqual(y, copiedQuaternion.Y());
			Assert::AreEqual(z, copiedQuaternion.Z());
			Assert::AreEqual(w, copiedQuaternion.W());
		}

		TEST_METHOD(ComponentAccessTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternion.X());
			Assert::AreEqual(y, quaternion.Y());
			Assert::AreEqual(z, quaternion.Z());
			Assert::AreEqual(w, quaternion.W());

			constexpr auto quaternionC = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternionC.X());
			Assert::AreEqual(y, quaternionC.Y());
			Assert::AreEqual(z, quaternionC.Z());
			Assert::AreEqual(w, quaternionC.W());
		}

		TEST_METHOD(DataTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternion.Data()[0]);
			Assert::AreEqual(y, quaternion.Data()[1]);
			Assert::AreEqual(z, quaternion.Data()[2]);
			Assert::AreEqual(w, quaternion.Data()[3]);

			constexpr auto quaternionC = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternionC.Data()[0]);
			Assert::AreEqual(y, quaternionC.Data()[1]);
			Assert::AreEqual(z, quaternionC.Data()[2]);
			Assert::AreEqual(w, quaternionC.Data()[3]);
		}

		TEST_METHOD(MagnitudeTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(22.f, quaternion.MagnitudeSquared());
			Assert::AreEqual(4.69, static_cast<double>(quaternion.Magnitude()), 0.001);
		}

		TEST_METHOD(ConjugateTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			PonyEngine::Math::Quaternion<float> conjugate = quaternion.Conjugate();
			Assert::AreEqual(-x, conjugate.X());
			Assert::AreEqual(-y, conjugate.Y());
			Assert::AreEqual(-z, conjugate.Z());
			Assert::AreEqual(w, conjugate.W());
		}

		TEST_METHOD(InverseTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			PonyEngine::Math::Quaternion<float> inverse = quaternion.Inverse();
			Assert::AreEqual(-0.182, static_cast<double>(inverse.X()), 0.001);
			Assert::AreEqual(0.045, static_cast<double>(inverse.Y()), 0.001);
			Assert::AreEqual(-0.045, static_cast<double>(inverse.Z()), 0.001);
			Assert::AreEqual(0.091, static_cast<double>(inverse.W()), 0.001);
		}

		TEST_METHOD(NormalizeTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			PonyEngine::Math::Quaternion<float> normalized = quaternion.Normalized();
			Assert::AreEqual(0.853, static_cast<double>(normalized.X()), 0.001);
			Assert::AreEqual(-0.213, static_cast<double>(normalized.Y()), 0.001);
			Assert::AreEqual(0.213, static_cast<double>(normalized.Z()), 0.001);
			Assert::AreEqual(0.426, static_cast<double>(normalized.W()), 0.001);
			quaternion.Normalize();
			Assert::IsTrue(quaternion == normalized);
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			const float nan = std::numeric_limits<float>::quiet_NaN();
			Assert::IsTrue(quaternion.IsFinite());
			quaternion.X() = nan;
			Assert::IsFalse(quaternion.IsFinite());
			quaternion.X() = x;
			quaternion.Y() = nan;
			Assert::IsFalse(quaternion.IsFinite());
			quaternion.Y() = y;
			quaternion.Z() = nan;
			Assert::IsFalse(quaternion.IsFinite());
			quaternion.Z() = z;
			quaternion.W() = nan;
			Assert::IsFalse(quaternion.IsFinite());
		}

		TEST_METHOD(SetTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyEngine::Math::Quaternion<float>();
			quaternion.Set(x, y, z, w);
			Assert::AreEqual(x, quaternion.X());
			Assert::AreEqual(y, quaternion.Y());
			Assert::AreEqual(z, quaternion.Z());
			Assert::AreEqual(w, quaternion.W());
		}

		TEST_METHOD(SetArrayTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyEngine::Math::Quaternion<float>();
			quaternion.Set(std::array<float, 4>{x, y, z, w}.data());
			Assert::AreEqual(x, quaternion.X());
			Assert::AreEqual(y, quaternion.Y());
			Assert::AreEqual(z, quaternion.Z());
			Assert::AreEqual(w, quaternion.W());
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			const std::string expectedString = std::format("({}, {}, {}, {})", x, y, z, w);
			Assert::AreEqual(expectedString, quaternion.ToString());

			std::ostringstream ss;
			ss << quaternion;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(ToVector4Test)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			PonyEngine::Math::Vector4<float> vector = quaternion;
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
			Assert::AreEqual(w, vector.W());
		}

		TEST_METHOD(AccessByIndexTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternion[0]);
			Assert::AreEqual(y, quaternion[1]);
			Assert::AreEqual(z, quaternion[2]);
			Assert::AreEqual(w, quaternion[3]);

			constexpr auto quaternionC = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternionC[0]);
			Assert::AreEqual(y, quaternionC[1]);
			Assert::AreEqual(z, quaternionC[2]);
			Assert::AreEqual(w, quaternionC[3]);
		}

		TEST_METHOD(CopyAssignmentTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			constexpr auto quaternionR = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			auto quaternionC = PonyEngine::Math::Quaternion<float>();
			PonyEngine::Math::Quaternion<float>& quaternionL = quaternionC = quaternionR;
			Assert::AreEqual(x, quaternionC.X());
			Assert::AreEqual(y, quaternionC.Y());
			Assert::AreEqual(z, quaternionC.Z());
			Assert::AreEqual(w, quaternionC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&quaternionC), reinterpret_cast<std::uintptr_t>(&quaternionL));
		}

		TEST_METHOD(MoveAssignmentTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternionR = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			auto quaternionC = PonyEngine::Math::Quaternion<float>();
			PonyEngine::Math::Quaternion<float>& quaternionL = quaternionC = std::move(quaternionR);
			Assert::AreEqual(x, quaternionC.X());
			Assert::AreEqual(y, quaternionC.Y());
			Assert::AreEqual(z, quaternionC.Z());
			Assert::AreEqual(w, quaternionC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&quaternionC), reinterpret_cast<std::uintptr_t>(&quaternionL));
		}

		TEST_METHOD(MultiplyAssignmentTest)
		{
			constexpr float xR = 4;
			constexpr float yR = -1;
			constexpr float zR = 1;
			constexpr float wR = 2;
			constexpr auto quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR);
			constexpr float xC = -2;
			constexpr float yC = 3;
			constexpr float zC = -1;
			constexpr float wC = 2;
			auto quaternionC = PonyEngine::Math::Quaternion<float>(xC, yC, zC, wC);
			PonyEngine::Math::Quaternion<float>& quaternionL = quaternionC *= quaternionR;
			Assert::AreEqual(6.f, quaternionC.X());
			Assert::AreEqual(2.f, quaternionC.Y());
			Assert::AreEqual(-10.f, quaternionC.Z());
			Assert::AreEqual(16.f, quaternionC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&quaternionC), reinterpret_cast<std::uintptr_t>(&quaternionL));
		}

		TEST_METHOD(EqualityTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -5;
			constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			PonyEngine::Math::Quaternion<float> otherQuaternion = quaternion;

			Assert::IsTrue(quaternion == otherQuaternion);
			Assert::IsFalse(quaternion != otherQuaternion);

			for (std::size_t i = 0; i < PonyEngine::Math::Quaternion<float>::ComponentCount; ++i)
			{
				otherQuaternion.Data()[i] = std::nextafter(otherQuaternion.Data()[i], 0.f);
				Assert::IsFalse(quaternion == otherQuaternion);
				Assert::IsTrue(quaternion != otherQuaternion);
				otherQuaternion.Data()[i] += 1;
				Assert::IsFalse(quaternion == otherQuaternion);
				Assert::IsTrue(quaternion != otherQuaternion);
				otherQuaternion.Data()[i] = quaternion.Data()[i];
			}
		}

		TEST_METHOD(DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::QuaternionIdentity<float> == PonyEngine::Math::Quaternion<float>(0, 0, 0, 1));
		}

		TEST_METHOD(DotTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -5;
			constexpr auto quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR);
			constexpr float xL = -2;
			constexpr float yL = 3;
			constexpr float zL = -1;
			constexpr float wL = 2;
			constexpr auto quaternionL = PonyEngine::Math::Quaternion<float>(xL, yL, zL, wL);
			Assert::AreEqual(-28.f, PonyEngine::Math::Dot(quaternionL, quaternionR));
		}

		TEST_METHOD(AngleTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -5;
			const auto quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
			constexpr float xL = -2;
			constexpr float yL = 3;
			constexpr float zL = -1;
			constexpr float wL = 2;
			const auto quaternionL = PonyEngine::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();
			Assert::AreEqual(1.178, static_cast<double>(PonyEngine::Math::Angle(quaternionL, quaternionR)), 0.001);
			Assert::AreEqual(0., static_cast<double>(PonyEngine::Math::Angle(quaternionL, quaternionL)), 0.001);
			Assert::AreEqual(std::numbers::pi_v<double>, static_cast<double>(PonyEngine::Math::Angle(quaternionL, PonyEngine::Math::Quaternion<float>(quaternionL.Y(), -quaternionL.X(), quaternionL.W(), -quaternionL.Z()))), 0.001);
			Assert::AreEqual(std::numbers::pi_v<double> / 2., static_cast<double>(PonyEngine::Math::Angle(quaternionL, PonyEngine::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f))), 0.001);
		}

		TEST_METHOD(LerpTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -5;
			constexpr auto quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR);
			constexpr float xL = -2;
			constexpr float yL = 3;
			constexpr float zL = -1;
			constexpr float wL = 2;
			constexpr auto quaternionL = PonyEngine::Math::Quaternion<float>(xL, yL, zL, wL);

			PonyEngine::Math::Quaternion<float> lerped = PonyEngine::Math::Lerp(quaternionL, quaternionR, 0.f);
			Assert::AreEqual(xL, lerped.X());
			Assert::AreEqual(yL, lerped.Y());
			Assert::AreEqual(zL, lerped.Z());
			Assert::AreEqual(wL, lerped.W());

			lerped = PonyEngine::Math::Lerp(quaternionL, quaternionR, 1.f);
			Assert::AreEqual(xR, lerped.X());
			Assert::AreEqual(yR, lerped.Y());
			Assert::AreEqual(zR, lerped.Z());
			Assert::AreEqual(wR, lerped.W());

			lerped = PonyEngine::Math::Lerp(quaternionL, quaternionR, 0.5f);
			Assert::AreEqual(0.f, lerped.X());
			Assert::AreEqual(0.f, lerped.Y());
			Assert::AreEqual(2.f, lerped.Z());
			Assert::AreEqual(-1.5f, lerped.W());

			lerped = PonyEngine::Math::Lerp(quaternionL, quaternionR, 2.f);
			Assert::AreEqual(6.f, lerped.X());
			Assert::AreEqual(-9.f, lerped.Y());
			Assert::AreEqual(11.f, lerped.Z());
			Assert::AreEqual(-12.f, lerped.W());

			lerped = PonyEngine::Math::Lerp(quaternionL, quaternionR, -1.f);
			Assert::AreEqual(-6.f, lerped.X());
			Assert::AreEqual(9.f, lerped.Y());
			Assert::AreEqual(-7.f, lerped.Z());
			Assert::AreEqual(9.f, lerped.W());
		}

		TEST_METHOD(SlerpTest)
		{
			constexpr float xR = 2;
			constexpr float yR = 3;
			constexpr float zR = 5;
			constexpr float wR = 5;
			const auto quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
			constexpr float xL = 2;
			constexpr float yL = 3;
			constexpr float zL = 1;
			constexpr float wL = 2;
			const auto quaternionL = PonyEngine::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();

			PonyEngine::Math::Quaternion<float> slerped = PonyEngine::Math::Slerp(quaternionL, quaternionR, 0.f);
			Assert::AreEqual(static_cast<double>(quaternionL.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.W()), static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternionL, quaternionR, 1.f);
			Assert::AreEqual(static_cast<double>(quaternionR.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionR.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionR.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionR.W()), static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternionL, quaternionR, 0.5f);
			Assert::AreEqual(0.378, static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(0.567, static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(0.452, static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(0.575, static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternionL, quaternionR.Conjugate(), 0.5f);
			Assert::AreEqual(0.46, static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(0.69, static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(0.55, static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(-0.1, static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternionL, quaternionL, 0.5f);
			Assert::AreEqual(static_cast<double>(quaternionL.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.W()), static_cast<double>(slerped.W()), 0.001);

			slerped = PonyEngine::Math::Slerp(quaternionL, static_cast<PonyEngine::Math::Quaternion<float>>(-static_cast<PonyEngine::Math::Vector4<float>>(quaternionL)), 0.5f);
			Assert::AreEqual(static_cast<double>(quaternionL.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.W()), static_cast<double>(slerped.W()), 0.001);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -5;
			auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
			PonyEngine::Math::Quaternion<float> otherQuaternion = quaternion;

			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual<float, false>(quaternion, otherQuaternion));

			for (std::size_t i = 0; i < PonyEngine::Math::Quaternion<float>::ComponentCount; ++i)
			{
				otherQuaternion.Data()[i] = std::nextafter(otherQuaternion.Data()[i], 0.f);
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual<float, false>(quaternion, otherQuaternion));
				otherQuaternion.Data()[i] += 1;
				Assert::IsFalse(PonyEngine::Math::AreAlmostEqual<float, false>(quaternion, otherQuaternion));
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual<float, false>(quaternion, otherQuaternion, 5.f));
				otherQuaternion.Data()[i] = quaternion.Data()[i];
			}

			quaternion.Normalize();
			otherQuaternion = quaternion;

			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(quaternion, otherQuaternion));

			for (std::size_t i = 0; i < PonyEngine::Math::Quaternion<float>::ComponentCount; ++i)
			{
				otherQuaternion = quaternion;
				otherQuaternion.Data()[i] = std::nextafter(otherQuaternion.Data()[i], 0.f);
				otherQuaternion.Normalize();
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(quaternion, otherQuaternion));
				otherQuaternion.Data()[i] += 1;
				otherQuaternion.Normalize();
				Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(quaternion, otherQuaternion));
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(quaternion, otherQuaternion, 1.f));
				otherQuaternion.Data()[i] = quaternion.Data()[i];
			}
		}

		TEST_METHOD(MultiplicationTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -5;
			constexpr auto quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR);
			constexpr float xL = -2;
			constexpr float yL = 3;
			constexpr float zL = -1;
			constexpr float wL = 2;
			constexpr auto quaternionL = PonyEngine::Math::Quaternion<float>(xL, yL, zL, wL);

			PonyEngine::Math::Quaternion<float> product = quaternionL * quaternionR;
			Assert::AreEqual(26.f, product.X());
			Assert::AreEqual(-13.f, product.Y());
			Assert::AreEqual(15.f, product.Z());
			Assert::AreEqual(8.f, product.W());

			product = quaternionL.Normalized() * quaternionR.Normalized();
			Assert::AreEqual(0.772, static_cast<double>(product.X()), 0.001);
			Assert::AreEqual(-0.386, static_cast<double>(product.Y()), 0.001);
			Assert::AreEqual(0.445, static_cast<double>(product.Z()), 0.001);
			Assert::AreEqual(0.238, static_cast<double>(product.W()), 0.001);
		}

		TEST_METHOD(MultiplicationVectorTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			constexpr float xQ = -2;
			constexpr float yQ = 3;
			constexpr float zQ = -1;
			constexpr float wQ = 2;
			constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(xQ, yQ, zQ, wQ);

			PonyEngine::Math::Vector3<float> product = quaternion * vector;
			Assert::AreEqual(66.f, product.X());
			Assert::AreEqual(5.f, product.Y());
			Assert::AreEqual(-99.f, product.Z());

			product = quaternion.Normalized() * vector;
			Assert::AreEqual(5.556, static_cast<double>(product.X()), 0.001);
			Assert::AreEqual(-2.556, static_cast<double>(product.Y()), 0.001);
			Assert::AreEqual(-0.778, static_cast<double>(product.Z()), 0.001);
		}

		// TODO: add constexpr test
	};
}
