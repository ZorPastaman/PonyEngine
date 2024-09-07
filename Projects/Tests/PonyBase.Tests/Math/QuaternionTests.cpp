/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <array>
#include <format>
#include <numbers>

import PonyBase.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(QuaternionTests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::Quaternion<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyBase::Math::Quaternion<double>::ValueType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{4}, PonyBase::Math::Quaternion<float>::ComponentCount);
		}

		TEST_METHOD(DefaultConstructorTest)
		{
			auto quaternion = PonyBase::Math::Quaternion<float>();
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
			auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternion.X());
			Assert::AreEqual(y, quaternion.Y());
			Assert::AreEqual(z, quaternion.Z());
			Assert::AreEqual(w, quaternion.W());
		}

		TEST_METHOD(ConstructorSpanTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyBase::Math::Quaternion<float>(std::array<float, 4>{x, y, z, w});
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
			constexpr auto vector = PonyBase::Math::Vector4<float>(x, y, z, w);
			auto quaternion = static_cast<PonyBase::Math::Quaternion<float>>(vector);
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
			constexpr auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			PonyBase::Math::Quaternion<float> copiedQuaternion = quaternion;
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
			auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			PonyBase::Math::Quaternion<float> copiedQuaternion = std::move(quaternion);
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
			auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternion.X());
			Assert::AreEqual(y, quaternion.Y());
			Assert::AreEqual(z, quaternion.Z());
			Assert::AreEqual(w, quaternion.W());

			constexpr auto quaternionC = PonyBase::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternionC.X());
			Assert::AreEqual(y, quaternionC.Y());
			Assert::AreEqual(z, quaternionC.Z());
			Assert::AreEqual(w, quaternionC.W());
		}

		TEST_METHOD(SpanTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternion.Span()[0]);
			Assert::AreEqual(y, quaternion.Span()[1]);
			Assert::AreEqual(z, quaternion.Span()[2]);
			Assert::AreEqual(w, quaternion.Span()[3]);

			constexpr auto quaternionC = PonyBase::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternionC.Span()[0]);
			Assert::AreEqual(y, quaternionC.Span()[1]);
			Assert::AreEqual(z, quaternionC.Span()[2]);
			Assert::AreEqual(w, quaternionC.Span()[3]);
		}

		TEST_METHOD(MagnitudeTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			constexpr auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(22.f, quaternion.MagnitudeSquared());
			Assert::AreEqual(4.69, static_cast<double>(quaternion.Magnitude()), 0.001);
		}

		TEST_METHOD(ConjugateTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			constexpr auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			PonyBase::Math::Quaternion<float> conjugate = quaternion.Conjugate();
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
			constexpr auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			PonyBase::Math::Quaternion<float> inverse = quaternion.Inverse();
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
			auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			PonyBase::Math::Quaternion<float> normalized = quaternion.Normalized();
			Assert::AreEqual(0.853, static_cast<double>(normalized.X()), 0.001);
			Assert::AreEqual(-0.213, static_cast<double>(normalized.Y()), 0.001);
			Assert::AreEqual(0.213, static_cast<double>(normalized.Z()), 0.001);
			Assert::AreEqual(0.426, static_cast<double>(normalized.W()), 0.001);
			quaternion.Normalize();
			Assert::IsTrue(quaternion == normalized);
		}

		TEST_METHOD(IsIdentityTest)
		{
			Assert::IsTrue(PonyBase::Math::Quaternion<float>::Predefined::Identity.IsIdentity());

			auto quaternion = PonyBase::Math::Quaternion<float>::Predefined::Identity;
			Assert::IsTrue(quaternion.IsIdentity());

			for (std::size_t i = 0; i < PonyBase::Math::Quaternion<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(quaternion.IsIdentity());
				quaternion.Span()[i] = std::nextafter(quaternion.Span()[i], 0.5f);
				Assert::IsFalse(quaternion.IsIdentity());
				quaternion.Span()[i] += 1;
				Assert::IsFalse(quaternion.IsIdentity());
				quaternion.Span()[i] = PonyBase::Math::Quaternion<float>::Predefined::Identity.Span()[i];
			}
		}

		TEST_METHOD(IsAlmostIdentityTest)
		{
			Assert::IsTrue(PonyBase::Math::Quaternion<float>::Predefined::Identity.IsAlmostIdentity());
			Assert::IsTrue(PonyBase::Math::Quaternion<float>::Predefined::Identity.IsAlmostIdentity<false>());

			auto quaternion = PonyBase::Math::Quaternion<float>::Predefined::Identity;
			Assert::IsTrue(quaternion.IsAlmostIdentity());
			Assert::IsTrue(quaternion.IsAlmostIdentity<false>());

			for (std::size_t i = 0; i < PonyBase::Math::Quaternion<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(quaternion.IsAlmostIdentity());
				quaternion.Span()[i] = std::nextafter(quaternion.Span()[i], 0.5f);
				Assert::IsTrue(quaternion.IsAlmostIdentity());
				quaternion.Span()[i] += 1;
				Assert::IsFalse(quaternion.IsAlmostIdentity<false>());
				Assert::IsTrue(quaternion.IsAlmostIdentity<false>(5.f));
				quaternion.Span()[i] = PonyBase::Math::Matrix4x4<float>::Predefined::Identity.Span()[i];
			}
		}

		TEST_METHOD(IsUnitTest)
		{
			Assert::IsTrue(PonyBase::Math::Quaternion<float>::Predefined::Identity.IsUnit());
			Assert::IsTrue(PonyBase::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f).IsUnit());
			Assert::IsTrue(PonyBase::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f).IsUnit());
			Assert::IsTrue(PonyBase::Math::Quaternion<float>(0.f, 0.f, 1.f, 0.f).IsUnit());

			Assert::IsFalse(PonyBase::Math::Quaternion<float>(1.f, 2.f, 1.f, 3.f).IsUnit());
			Assert::IsTrue(PonyBase::Math::Quaternion<float>(1.f, 2.f, 1.f, 3.f).Normalized().IsUnit());
		}

		TEST_METHOD(IsAlmostUnitTest)
		{
			Assert::IsTrue(PonyBase::Math::Quaternion<float>::Predefined::Identity.IsAlmostUnit());
			Assert::IsTrue(PonyBase::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f).IsAlmostUnit());
			Assert::IsTrue(PonyBase::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f).IsAlmostUnit());
			Assert::IsTrue(PonyBase::Math::Quaternion<float>(0.f, 0.f, 1.f, 0.f).IsAlmostUnit());

			Assert::IsFalse(PonyBase::Math::Quaternion<float>(1.f, 2.f, 1.f, 3.f).IsAlmostUnit());
			Assert::IsTrue(PonyBase::Math::Quaternion<float>(1.f, 2.f, 1.f, 3.f).IsAlmostUnit(20.f));
			Assert::IsTrue(PonyBase::Math::Quaternion<float>(1.f, 2.f, 1.f, 3.f).Normalized().IsAlmostUnit());
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
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
			auto quaternion = PonyBase::Math::Quaternion<float>();
			quaternion.Set(x, y, z, w);
			Assert::AreEqual(x, quaternion.X());
			Assert::AreEqual(y, quaternion.Y());
			Assert::AreEqual(z, quaternion.Z());
			Assert::AreEqual(w, quaternion.W());
		}

		TEST_METHOD(SetSpanTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyBase::Math::Quaternion<float>();
			quaternion.Set(std::array<float, 4>{x, y, z, w});
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
			constexpr auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
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
			constexpr auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			auto vector = static_cast<PonyBase::Math::Vector4<float>>(quaternion);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
			Assert::AreEqual(w, vector.W());
		}

		TEST_METHOD(CastTest)
		{
			constexpr auto floatQuaternion = PonyBase::Math::Quaternion<float>(3.1f, -2.2f, 4.4f, -2.1f);
			const auto doubleQuaternion = static_cast<PonyBase::Math::Quaternion<double>>(floatQuaternion);
			Assert::AreEqual(3.1, doubleQuaternion.X(), 0.0001);
			Assert::AreEqual(-2.2, doubleQuaternion.Y(), 0.0001);
			Assert::AreEqual(4.4, doubleQuaternion.Z(), 0.0001);
			Assert::AreEqual(-2.1, doubleQuaternion.W(), 0.0001);
		}

		TEST_METHOD(AccessByIndexTest)
		{
			constexpr float x = 4;
			constexpr float y = -1;
			constexpr float z = 1;
			constexpr float w = 2;
			auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			Assert::AreEqual(x, quaternion[0]);
			Assert::AreEqual(y, quaternion[1]);
			Assert::AreEqual(z, quaternion[2]);
			Assert::AreEqual(w, quaternion[3]);

			constexpr auto quaternionC = PonyBase::Math::Quaternion<float>(x, y, z, w);
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
			constexpr auto quaternionR = PonyBase::Math::Quaternion<float>(x, y, z, w);
			auto quaternionC = PonyBase::Math::Quaternion<float>();
			PonyBase::Math::Quaternion<float>& quaternionL = quaternionC = quaternionR;
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
			auto quaternionR = PonyBase::Math::Quaternion<float>(x, y, z, w);
			auto quaternionC = PonyBase::Math::Quaternion<float>();
			PonyBase::Math::Quaternion<float>& quaternionL = quaternionC = std::move(quaternionR);
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
			constexpr auto quaternionR = PonyBase::Math::Quaternion<float>(xR, yR, zR, wR);
			constexpr float xC = -2;
			constexpr float yC = 3;
			constexpr float zC = -1;
			constexpr float wC = 2;
			auto quaternionC = PonyBase::Math::Quaternion<float>(xC, yC, zC, wC);
			PonyBase::Math::Quaternion<float>& quaternionL = quaternionC *= quaternionR;
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
			constexpr auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			PonyBase::Math::Quaternion<float> otherQuaternion = quaternion;

			Assert::IsTrue(quaternion == otherQuaternion);
			Assert::IsFalse(quaternion != otherQuaternion);

			for (std::size_t i = 0; i < PonyBase::Math::Quaternion<float>::ComponentCount; ++i)
			{
				otherQuaternion.Span()[i] = std::nextafter(otherQuaternion.Span()[i], 0.f);
				Assert::IsFalse(quaternion == otherQuaternion);
				Assert::IsTrue(quaternion != otherQuaternion);
				otherQuaternion.Span()[i] += 1;
				Assert::IsFalse(quaternion == otherQuaternion);
				Assert::IsTrue(quaternion != otherQuaternion);
				otherQuaternion.Span()[i] = quaternion.Span()[i];
			}
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyBase::Math::Quaternion<float>::Predefined::Identity == PonyBase::Math::Quaternion<float>(0, 0, 0, 1));
		}

		TEST_METHOD(DotTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -5;
			constexpr auto quaternionR = PonyBase::Math::Quaternion<float>(xR, yR, zR, wR);
			constexpr float xL = -2;
			constexpr float yL = 3;
			constexpr float zL = -1;
			constexpr float wL = 2;
			constexpr auto quaternionL = PonyBase::Math::Quaternion<float>(xL, yL, zL, wL);
			Assert::AreEqual(-28.f, PonyBase::Math::Dot(quaternionL, quaternionR));
		}

		TEST_METHOD(AngleTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			float wR = -5;
			auto quaternionR = PonyBase::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
			float xL = -2;
			float yL = 3;
			float zL = -1;
			float wL = 2;
			auto quaternionL = PonyBase::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();
			Assert::AreEqual(1.178, static_cast<double>(PonyBase::Math::Angle(quaternionL, quaternionR)), 0.001);
			xR = 2;
			yR = 3;
			zR = 5;
			wR = -5;
			quaternionR = PonyBase::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
			xL = 2;
			yL = 3;
			zL = 1;
			wL = 2;
			quaternionL = PonyBase::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();
			Assert::AreEqual(2.662, static_cast<double>(PonyBase::Math::Angle(quaternionL, quaternionR)), 0.001);
			Assert::AreEqual(0., static_cast<double>(PonyBase::Math::Angle(quaternionL, quaternionL)), 0.001);
			xR = 3;
			yR = 2;
			zR = 2;
			wR = 1;
			quaternionR = PonyBase::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
			xL = -2;
			yL = 3;
			zL = -1;
			wL = 2;
			quaternionL = PonyBase::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();
			Assert::AreEqual(std::numbers::pi_v<double>, static_cast<double>(PonyBase::Math::Angle(quaternionL, quaternionR)), 0.001);
			xR = 0;
			yR = 1;
			zR = 0;
			wR = 0;
			quaternionR = PonyBase::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
			xL = -2;
			yL = 3;
			zL = -1;
			wL = 2;
			quaternionL = PonyBase::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();
			Assert::AreEqual(std::numbers::pi_v<double> / 2., static_cast<double>(PonyBase::Math::Angle(quaternionL, quaternionR)), 0.001);
		}

		TEST_METHOD(LerpTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -5;
			constexpr auto quaternionR = PonyBase::Math::Quaternion<float>(xR, yR, zR, wR);
			constexpr float xL = -2;
			constexpr float yL = 3;
			constexpr float zL = -1;
			constexpr float wL = 2;
			constexpr auto quaternionL = PonyBase::Math::Quaternion<float>(xL, yL, zL, wL);

			PonyBase::Math::Quaternion<float> lerped = PonyBase::Math::Lerp(quaternionL, quaternionR, 0.f);
			Assert::AreEqual(xL, lerped.X());
			Assert::AreEqual(yL, lerped.Y());
			Assert::AreEqual(zL, lerped.Z());
			Assert::AreEqual(wL, lerped.W());

			lerped = PonyBase::Math::Lerp(quaternionL, quaternionR, 1.f);
			Assert::AreEqual(xR, lerped.X());
			Assert::AreEqual(yR, lerped.Y());
			Assert::AreEqual(zR, lerped.Z());
			Assert::AreEqual(wR, lerped.W());

			lerped = PonyBase::Math::Lerp(quaternionL, quaternionR, 0.5f);
			Assert::AreEqual(0.f, lerped.X());
			Assert::AreEqual(0.f, lerped.Y());
			Assert::AreEqual(2.f, lerped.Z());
			Assert::AreEqual(-1.5f, lerped.W());

			lerped = PonyBase::Math::Lerp(quaternionL, quaternionR, 2.f);
			Assert::AreEqual(6.f, lerped.X());
			Assert::AreEqual(-9.f, lerped.Y());
			Assert::AreEqual(11.f, lerped.Z());
			Assert::AreEqual(-12.f, lerped.W());

			lerped = PonyBase::Math::Lerp(quaternionL, quaternionR, -1.f);
			Assert::AreEqual(-6.f, lerped.X());
			Assert::AreEqual(9.f, lerped.Y());
			Assert::AreEqual(-7.f, lerped.Z());
			Assert::AreEqual(9.f, lerped.W());
		}

		TEST_METHOD(SlerpTest)
		{
			float xR = 2;
			float yR = 3;
			float zR = 5;
			float wR = 5;
			auto quaternionR = PonyBase::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
			float xL = 2;
			float yL = 3;
			float zL = 1;
			float wL = 2;
			auto quaternionL = PonyBase::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();

			PonyBase::Math::Quaternion<float> slerped = PonyBase::Math::Slerp(quaternionL, quaternionR, 0.f);
			Assert::AreEqual(static_cast<double>(quaternionL.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.W()), static_cast<double>(slerped.W()), 0.001);

			slerped = PonyBase::Math::Slerp(quaternionL, quaternionR, 1.f);
			Assert::AreEqual(static_cast<double>(quaternionR.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionR.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionR.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionR.W()), static_cast<double>(slerped.W()), 0.001);

			slerped = PonyBase::Math::Slerp(quaternionL, quaternionR, 0.5f);
			Assert::AreEqual(0.378, static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(0.567, static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(0.452, static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(0.575, static_cast<double>(slerped.W()), 0.001);

			slerped = PonyBase::Math::Slerp(quaternionL, quaternionR.Conjugate(), 0.5f);
			Assert::AreEqual(0.46, static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(0.69, static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(0.55, static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(-0.1, static_cast<double>(slerped.W()), 0.001);

			slerped = PonyBase::Math::Slerp(quaternionL, quaternionL, 0.5f);
			Assert::AreEqual(static_cast<double>(quaternionL.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.W()), static_cast<double>(slerped.W()), 0.001);

			slerped = PonyBase::Math::Slerp(quaternionL, static_cast<PonyBase::Math::Quaternion<float>>(-static_cast<PonyBase::Math::Vector4<float>>(quaternionL)), 0.5f);
			Assert::AreEqual(static_cast<double>(quaternionL.X()), static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.Y()), static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.Z()), static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternionL.W()), static_cast<double>(slerped.W()), 0.001);

			xR = 2;
			yR = 3;
			zR = 5;
			wR = 5;
			quaternionR = PonyBase::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
			xL = 3;
			yL = -2;
			zL = -5;
			wL = 5;
			quaternionL = PonyBase::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();
			slerped = PonyBase::Math::Slerp(quaternionL, quaternionR, 0.5f);
			Assert::AreEqual(0.445, static_cast<double>(slerped.X()), 0.001);
			Assert::AreEqual(0.089, static_cast<double>(slerped.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(slerped.Z()), 0.001);
			Assert::AreEqual(0.891, static_cast<double>(slerped.W()), 0.001);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -5;
			auto quaternion = PonyBase::Math::Quaternion<float>(x, y, z, w);
			PonyBase::Math::Quaternion<float> otherQuaternion = quaternion;

			Assert::IsTrue(PonyBase::Math::AreAlmostEqual<float, false>(quaternion, otherQuaternion));

			for (std::size_t i = 0; i < PonyBase::Math::Quaternion<float>::ComponentCount; ++i)
			{
				otherQuaternion.Span()[i] = std::nextafter(otherQuaternion.Span()[i], 0.f);
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual<float, false>(quaternion, otherQuaternion));
				otherQuaternion.Span()[i] += 1;
				Assert::IsFalse(PonyBase::Math::AreAlmostEqual<float, false>(quaternion, otherQuaternion));
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual<float, false>(quaternion, otherQuaternion, 5.f));
				otherQuaternion.Span()[i] = quaternion.Span()[i];
			}

			quaternion.Normalize();
			otherQuaternion = quaternion;

			Assert::IsTrue(PonyBase::Math::AreAlmostEqual(quaternion, otherQuaternion));

			for (std::size_t i = 0; i < PonyBase::Math::Quaternion<float>::ComponentCount; ++i)
			{
				otherQuaternion = quaternion;
				otherQuaternion.Span()[i] = std::nextafter(otherQuaternion.Span()[i], 0.f);
				otherQuaternion.Normalize();
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual(quaternion, otherQuaternion));
				otherQuaternion.Span()[i] += 1;
				otherQuaternion.Normalize();
				Assert::IsFalse(PonyBase::Math::AreAlmostEqual(quaternion, otherQuaternion));
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual(quaternion, otherQuaternion, 1.f));
				otherQuaternion.Span()[i] = quaternion.Span()[i];
			}
		}

		TEST_METHOD(MultiplicationTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -5;
			constexpr auto quaternionR = PonyBase::Math::Quaternion<float>(xR, yR, zR, wR);
			constexpr float xL = -2;
			constexpr float yL = 3;
			constexpr float zL = -1;
			constexpr float wL = 2;
			constexpr auto quaternionL = PonyBase::Math::Quaternion<float>(xL, yL, zL, wL);

			PonyBase::Math::Quaternion<float> product = quaternionL * quaternionR;
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
			constexpr auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			constexpr float xQ = -2;
			constexpr float yQ = 3;
			constexpr float zQ = -1;
			constexpr float wQ = 2;
			constexpr auto quaternion = PonyBase::Math::Quaternion<float>(xQ, yQ, zQ, wQ);

			PonyBase::Math::Vector3<float> product = quaternion * vector;
			Assert::AreEqual(66.f, product.X());
			Assert::AreEqual(5.f, product.Y());
			Assert::AreEqual(-99.f, product.Z());

			product = quaternion.Normalized() * vector;
			Assert::AreEqual(5.556, static_cast<double>(product.X()), 0.001);
			Assert::AreEqual(-2.556, static_cast<double>(product.Y()), 0.001);
			Assert::AreEqual(-0.778, static_cast<double>(product.Z()), 0.001);
		}

		static constexpr PonyBase::Math::Quaternion<float> QuaternionConstexpr()
		{
			[[maybe_unused]] auto quaternionToMove = PonyBase::Math::Quaternion<float>(0, 4, 5, 1);
			PonyBase::Math::Quaternion<float> movedQuaternion = std::move(quaternionToMove);

			[[maybe_unused]] auto quaternion = PonyBase::Math::Quaternion<float>(0, 4, 5, 1);
			quaternion.X() *= 3.f;
			quaternion.Y() /= 4.f;
			quaternion.Z() += 2.f;
			quaternion.W() -= 1.f;
			quaternion.Span()[2] -= 6.f;

			[[maybe_unused]] const auto quaternionC = PonyBase::Math::Quaternion<float>(0, 4, 5, 1);

			quaternion.Set(1.f, 6.f, 7.f, -1.f);
			quaternion.Set(quaternion.Span());

			quaternion[0] *= 5.f;

			movedQuaternion = quaternionC;
			movedQuaternion = std::move(quaternion);

			movedQuaternion *= movedQuaternion;

			return movedQuaternion;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto identity = PonyBase::Math::Quaternion<float>::Predefined::Identity;

			[[maybe_unused]] constexpr auto defaultQuaternion = PonyBase::Math::Quaternion<float>();
			[[maybe_unused]] constexpr auto quaternion = PonyBase::Math::Quaternion<float>(0, 4, 5, 1);
			[[maybe_unused]] constexpr auto vectorQuaternion = PonyBase::Math::Quaternion<float>(PonyBase::Math::Vector4<float>(0, 4, 5, 1));
			[[maybe_unused]] constexpr PonyBase::Math::Quaternion<float> copiedQuaternion = quaternion;
			[[maybe_unused]] constexpr PonyBase::Math::Quaternion<float> movedQuaternion = QuaternionConstexpr();

			[[maybe_unused]] constexpr float x = quaternion.X();
			[[maybe_unused]] constexpr float y = quaternion.Y();
			[[maybe_unused]] constexpr float z = quaternion.Z();
			[[maybe_unused]] constexpr float w = quaternion.W();
			[[maybe_unused]] constexpr auto span = quaternion.Span();

			[[maybe_unused]] constexpr float magnitudeSquared = quaternion.MagnitudeSquared();

			[[maybe_unused]] constexpr PonyBase::Math::Quaternion<float> conjugate = quaternion.Conjugate();
			[[maybe_unused]] constexpr PonyBase::Math::Quaternion<float> inverse = quaternion.Inverse();

			[[maybe_unused]] constexpr bool isIdentity = quaternion.IsIdentity();
			[[maybe_unused]] constexpr bool isUnit = quaternion.IsUnit();

			[[maybe_unused]] constexpr auto vector = static_cast<PonyBase::Math::Vector4<float>>(quaternion);
			[[maybe_unused]] constexpr auto doubleQuaternion = static_cast<PonyBase::Math::Quaternion<double>>(quaternion);

			[[maybe_unused]] constexpr float component = quaternion[2];

			[[maybe_unused]] constexpr bool equal = quaternion == defaultQuaternion;
			[[maybe_unused]] constexpr bool notEqual = quaternion != defaultQuaternion;

			[[maybe_unused]] constexpr float dot = PonyBase::Math::Dot(quaternion, vectorQuaternion);
			[[maybe_unused]] constexpr PonyBase::Math::Quaternion<float> lerped = PonyBase::Math::Lerp(defaultQuaternion, quaternion, 0.5f);

			[[maybe_unused]] constexpr PonyBase::Math::Quaternion<float> product = quaternion * vectorQuaternion;
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> productV = quaternion * PonyBase::Math::Vector3<float>(0, 4, 5);
		}
	};
}