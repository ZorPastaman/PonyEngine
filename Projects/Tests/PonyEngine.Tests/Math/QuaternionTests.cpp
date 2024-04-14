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

		TEST_METHOD(QuaternionEulerTest)
		{
			float x = 0.f;
			float y = 0.f;
			float z = 0.f;
			auto quaternion = PonyEngine::Math::Quaternion<float>::CreateByEuler(x, y, z);
			Assert::AreEqual(0.f, quaternion.X());
			Assert::AreEqual(0.f, quaternion.Y());
			Assert::AreEqual(0.f, quaternion.Z());
			Assert::AreEqual(1.f, quaternion.W());
			auto euler = quaternion.Euler();
			Assert::AreEqual(x, euler.X());
			Assert::AreEqual(y, euler.Y());
			Assert::AreEqual(z, euler.Z());

			x = 90.f;
			y = 0.f;
			z = 0.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.Z()), 0.001);

			x = 90.f;
			y = 60.f;
			z = 45.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.701, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.092, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.092, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.701, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(90., static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(15., static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(euler.Z()), 0.001);

			x = 0.f;
			y = 90.f;
			z = 0.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.Z()), 0.001);

			x = 0.f;
			y = 0.f;
			z = 90.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.Z()), 0.001);

			x = -90.f;
			y = 0.f;
			z = 0.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.Z()), 0.001);

			x = -90.f;
			y = -60.f;
			z = -45.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.430, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.561, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.561, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.430, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(-90., static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(-105., static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(euler.Z()), 0.001);

			x = 0.f;
			y = -90.f;
			z = 0.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.Z()), 0.001);

			x = 0.f;
			y = 0.f;
			z = -90.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.Z()), 0.001);

			x = 46.f;
			y = 78.f;
			z = 32.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.452, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.473, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.039, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.755, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.Z()), 0.001);

			x = -46.f;
			y = -78.f;
			z = -32.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.132, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.640, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.434, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.620, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(euler.Z()), 0.001);

			x = 146.f;
			y = 178.f;
			z = 132.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.274, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.104, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.384, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.876, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(34., static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(-2., static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(-48., static_cast<double>(euler.Z()), 0.001);

			x = -146.f;
			y = -178.f;
			z = -132.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.260, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.134, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.393, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.871, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(-34., static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(2., static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(48., static_cast<double>(euler.Z()), 0.001);

			x = 200.f;
			y = 220.f;
			z = 265.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.107, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.359, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.669, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.642, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(-20., static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(40., static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(85., static_cast<double>(euler.Z()), 0.001);

			x = -200.f;
			y = -220.f;
			z = -265.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.348, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.138, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.581, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.722, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(20., static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(-40., static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(-85., static_cast<double>(euler.Z()), 0.001);

			x = 300.f;
			y = 320.f;
			z = 285.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(0.192, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.521, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.631, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.541, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(-60., static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(-40., static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(-75., static_cast<double>(euler.Z()), 0.001);

			x = -300.f;
			y = -320.f;
			z = -285.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.553, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.051, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.360, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.750, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(60., static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(40., static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(75., static_cast<double>(euler.Z()), 0.001);

			x = 400.f;
			y = 500.f;
			z = 600.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.706, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.543, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.439, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.118, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(40., static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(140., static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(-120., static_cast<double>(euler.Z()), 0.001);

			x = -400.f;
			y = -500.f;
			z = -600.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x, y, z);
			Assert::AreEqual(-0.823, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.340, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.118, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.439, static_cast<double>(quaternion.W()), 0.001);
			euler = quaternion.EulerDegrees();
			Assert::AreEqual(-40., static_cast<double>(euler.X()), 0.001);
			Assert::AreEqual(-140., static_cast<double>(euler.Y()), 0.001);
			Assert::AreEqual(120., static_cast<double>(euler.Z()), 0.001);

			x = 1.f;
			y = 2.f;
			z = 3.f;
			auto quaternion0 = PonyEngine::Math::Quaternion<float>::CreateByEuler(x, y, z);
			auto quaternion1 = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(x * PonyEngine::Math::RadToDeg<float>, y * PonyEngine::Math::RadToDeg<float>, z * PonyEngine::Math::RadToDeg<float>);
			auto quaternion2 = PonyEngine::Math::Quaternion<float>::CreateByEuler(PonyEngine::Math::Vector3<float>(x, y, z));
			auto quaternion3 = PonyEngine::Math::Quaternion<float>::CreateByEulerDegrees(PonyEngine::Math::Vector3<float>(x, y, z) * PonyEngine::Math::RadToDeg<float>);
			Assert::AreEqual(static_cast<double>(quaternion0.X()), static_cast<double>(quaternion1.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Y()), static_cast<double>(quaternion1.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Z()), static_cast<double>(quaternion1.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.W()), static_cast<double>(quaternion1.W()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.X()), static_cast<double>(quaternion2.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Y()), static_cast<double>(quaternion2.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Z()), static_cast<double>(quaternion2.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.W()), static_cast<double>(quaternion2.W()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.X()), static_cast<double>(quaternion3.X()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Y()), static_cast<double>(quaternion3.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.Z()), static_cast<double>(quaternion3.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(quaternion0.W()), static_cast<double>(quaternion3.W()), 0.001);

			auto radVector = quaternion0.Euler();
			auto degVector = quaternion0.EulerDegrees();
			Assert::AreEqual(radVector.X() * PonyEngine::Math::RadToDeg<float>, degVector.X());
			Assert::AreEqual(radVector.Y() * PonyEngine::Math::RadToDeg<float>, degVector.Y());
			Assert::AreEqual(radVector.Z() * PonyEngine::Math::RadToDeg<float>, degVector.Z());
		}

		TEST_METHOD(QuaternionAxisAngleTest)
		{
			float x = 1.f;
			float y = 2.f;
			float z = 3.f;
			auto axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.X();
			y = axis.Y();
			z = axis.Z();
			float angle = 1.5f;
			auto quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngle(axis, angle);
			Assert::AreEqual(0.182, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.364, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.547, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.732, static_cast<double>(quaternion.W()), 0.001);
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle * PonyEngine::Math::RadToDeg<float>);
			Assert::AreEqual(0.182, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.364, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.547, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.732, static_cast<double>(quaternion.W()), 0.001);
			auto axisAngle = quaternion.AxisAngle();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(axisAngle.first.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(axisAngle.first.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(axisAngle.first.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(angle), static_cast<double>(axisAngle.second), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(axisAngle.first.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(axisAngle.first.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(axisAngle.first.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(angle * PonyEngine::Math::RadToDeg<float>), static_cast<double>(axisAngle.second), 0.001);

			x = -x;
			y = -y;
			z = -z;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.X();
			y = axis.Y();
			z = axis.Z();
			angle = -angle;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngle(axis, angle);
			Assert::AreEqual(0.182, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.364, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.547, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.732, static_cast<double>(quaternion.W()), 0.001);
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle * PonyEngine::Math::RadToDeg<float>);
			Assert::AreEqual(0.182, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.364, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.547, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.732, static_cast<double>(quaternion.W()), 0.001);
			axisAngle = quaternion.AxisAngle();
			Assert::AreEqual(static_cast<double>(-x), static_cast<double>(axisAngle.first.X()), 0.001);
			Assert::AreEqual(static_cast<double>(-y), static_cast<double>(axisAngle.first.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(-z), static_cast<double>(axisAngle.first.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(-angle), static_cast<double>(axisAngle.second), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(-x), static_cast<double>(axisAngle.first.X()), 0.001);
			Assert::AreEqual(static_cast<double>(-y), static_cast<double>(axisAngle.first.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(-z), static_cast<double>(axisAngle.first.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(-angle * PonyEngine::Math::RadToDeg<float>), static_cast<double>(axisAngle.second), 0.001);

			x = -2.f;
			y = 4.f;
			z = 1.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.X();
			y = axis.Y();
			z = axis.Z();
			angle = 120.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(-0.378, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.756, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.189, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.5, static_cast<double>(quaternion.W()), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(axisAngle.first.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(axisAngle.first.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(axisAngle.first.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(angle), static_cast<double>(axisAngle.second), 0.001);

			x = 3.f;
			y = -4.f;
			z = 3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.X();
			y = axis.Y();
			z = axis.Z();
			angle = 220.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(0.483, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.644, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.483, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.342, static_cast<double>(quaternion.W()), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(axisAngle.first.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(axisAngle.first.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(axisAngle.first.Z()), 0.001);
			Assert::AreEqual(-140., static_cast<double>(axisAngle.second), 0.001);

			x = 5.f;
			y = 4.f;
			z = -3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.X();
			y = axis.Y();
			z = axis.Z();
			angle = 300.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(0.354, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.282, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.212, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.866, static_cast<double>(quaternion.W()), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(x), static_cast<double>(axisAngle.first.X()), 0.001);
			Assert::AreEqual(static_cast<double>(y), static_cast<double>(axisAngle.first.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(z), static_cast<double>(axisAngle.first.Z()), 0.001);
			Assert::AreEqual(-60., static_cast<double>(axisAngle.second), 0.001);

			x = 5.f;
			y = -4.f;
			z = -3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.X();
			y = axis.Y();
			z = axis.Z();
			angle = -60.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(-0.353, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.283, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.212, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.866, static_cast<double>(quaternion.W()), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(-x), static_cast<double>(axisAngle.first.X()), 0.001);
			Assert::AreEqual(static_cast<double>(-y), static_cast<double>(axisAngle.first.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(-z), static_cast<double>(axisAngle.first.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(-angle), static_cast<double>(axisAngle.second), 0.001);

			x = -5.f;
			y = -4.f;
			z = 3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.X();
			y = axis.Y();
			z = axis.Z();
			angle = -160.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(0.696, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.557, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.418, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(quaternion.W()), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(-x), static_cast<double>(axisAngle.first.X()), 0.001);
			Assert::AreEqual(static_cast<double>(-y), static_cast<double>(axisAngle.first.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(-z), static_cast<double>(axisAngle.first.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(-angle), static_cast<double>(axisAngle.second), 0.001);

			x = -5.f;
			y = -4.f;
			z = -3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.X();
			y = axis.Y();
			z = axis.Z();
			angle = -260.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(0.542, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.433, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.325, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.643, static_cast<double>(quaternion.W()), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(-x), static_cast<double>(axisAngle.first.X()), 0.001);
			Assert::AreEqual(static_cast<double>(-y), static_cast<double>(axisAngle.first.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(-z), static_cast<double>(axisAngle.first.Z()), 0.001);
			Assert::AreEqual(-100., static_cast<double>(axisAngle.second), 0.001);

			x = 5.f;
			y = 4.f;
			z = 3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.X();
			y = axis.Y();
			z = axis.Z();
			angle = -300.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(-0.354, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.283, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.212, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.866, static_cast<double>(quaternion.W()), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::AreEqual(static_cast<double>(-x), static_cast<double>(axisAngle.first.X()), 0.001);
			Assert::AreEqual(static_cast<double>(-y), static_cast<double>(axisAngle.first.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(-z), static_cast<double>(axisAngle.first.Z()), 0.001);
			Assert::AreEqual(-60., static_cast<double>(axisAngle.second), 0.001);

			x = 5.f;
			y = 4.f;
			z = 3.f;
			axis = PonyEngine::Math::Vector3<float>(x, y, z);
			axis.Normalize();
			x = axis.X();
			y = axis.Y();
			z = axis.Z();
			angle = 0.f;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngleDegrees(axis, angle);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(1., static_cast<double>(quaternion.W()), 0.001);
			axisAngle = quaternion.AxisAngleDegrees();
			Assert::IsTrue(std::isnan(axisAngle.first.X()) || axisAngle.first.X() == 0.f);
			Assert::IsTrue(std::isnan(axisAngle.first.Y()) || axisAngle.first.Y() == 0.f);
			Assert::IsTrue(std::isnan(axisAngle.first.Z()) || axisAngle.first.Z() == 0.f);
			Assert::AreEqual(0., static_cast<double>(axisAngle.second), 0.001);
		}

		TEST_METHOD(QuaternionDirectionTest)
		{
			auto from = PonyEngine::Math::Vector3<float>(1.f, 4.f, -3.f).Normalized();
			auto to = PonyEngine::Math::Vector3<float>(-4.f, 2.f, 1.f).Normalized();
			auto quaternion = PonyEngine::Math::Quaternion<float>::CreateByDirection(from, to);
			Assert::AreEqual(0.296, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.326, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.533, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.722, static_cast<double>(quaternion.W()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>::CreateByDirection(PonyEngine::Math::Vector3<float>::Down, PonyEngine::Math::Vector3<float>::Up);
			Assert::AreEqual(-1., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>::CreateByDirection(PonyEngine::Math::Vector3<float>::Left, PonyEngine::Math::Vector3<float>::Right);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>::CreateByDirection(PonyEngine::Math::Vector3<float>::Down, PonyEngine::Math::Vector3<float>::Down);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(1., static_cast<double>(quaternion.W()), 0.001);

			from = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
			auto axis = PonyEngine::Math::Cross(from, PonyEngine::Math::Vector3<float>::Right).Normalized();
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByAxisAngle(axis, std::acos(std::nextafter(-1.f, 0.f)));
			to = quaternion * from;
			quaternion = PonyEngine::Math::Quaternion<float>::CreateByDirection(from, to);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);
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
			auto conjugated = quaternion.Conjugated();
			Assert::AreEqual(-x, conjugated.X());
			Assert::AreEqual(-y, conjugated.Y());
			Assert::AreEqual(-z, conjugated.Z());
			Assert::AreEqual(w, conjugated.W());

			quaternion.Conjugate();
			Assert::AreEqual(conjugated.X(), quaternion.X());
			Assert::AreEqual(conjugated.Y(), quaternion.Y());
			Assert::AreEqual(conjugated.Z(), quaternion.Z());
			Assert::AreEqual(conjugated.W(), quaternion.W());

			quaternion.Normalize();
			conjugated = quaternion.Conjugated();
			auto multiplied = quaternion * conjugated;
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

			quaternion1 = quaternion0.Conjugated();
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
			Assert::AreEqual(121.818, PonyEngine::Math::AngleDegrees(quaternion0, quaternion1), 0.001);

			quaternion1 = quaternion0;
			Assert::AreEqual(0., PonyEngine::Math::Angle(quaternion0, quaternion1));
			Assert::AreEqual(0., PonyEngine::Math::AngleDegrees(quaternion0, quaternion1));
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

			constexpr float magnitudeSquared = quaternion.MagnitudeSquared();
			constexpr auto conjugated = quaternion.Conjugated();
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
