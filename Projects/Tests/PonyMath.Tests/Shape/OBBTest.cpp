/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstdint>
#include <format>
#include <utility>

import PonyMath.Core;
import PonyMath.Shape;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Shape
{
	TEST_CLASS(OBBTest)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyMath::Shape::OBB<float>::ValueType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{3}, PonyMath::Shape::OBB<float>::AxesCount);

			Assert::AreEqual(std::size_t{0}, PonyMath::Shape::OBB<float>::LeftBottomNearIndex);
			Assert::AreEqual(std::size_t{1}, PonyMath::Shape::OBB<float>::RightBottomNearIndex);
			Assert::AreEqual(std::size_t{2}, PonyMath::Shape::OBB<float>::LeftTopNearIndex);
			Assert::AreEqual(std::size_t{3}, PonyMath::Shape::OBB<float>::RightTopNearIndex);
			Assert::AreEqual(std::size_t{4}, PonyMath::Shape::OBB<float>::LeftBottomFarIndex);
			Assert::AreEqual(std::size_t{5}, PonyMath::Shape::OBB<float>::RightBottomFarIndex);
			Assert::AreEqual(std::size_t{6}, PonyMath::Shape::OBB<float>::LeftTopFarIndex);
			Assert::AreEqual(std::size_t{7}, PonyMath::Shape::OBB<float>::RightTopFarIndex);
			Assert::AreEqual(std::size_t{8}, PonyMath::Shape::OBB<float>::CornerCount);
		}

		TEST_METHOD(DefaultContructorTest)
		{
			const auto defaultObb = PonyMath::Shape::OBB<float>();
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Zero == defaultObb.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Zero == defaultObb.Extents());
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Right == defaultObb.AxisX());
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Up == defaultObb.AxisY());
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Forward == defaultObb.AxisZ());
		}

		TEST_METHOD(AabbConstructorTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto obb = PonyMath::Shape::OBB<float>(aabb);
			Assert::IsTrue(aabb.Center() == obb.Center());
			Assert::IsTrue(aabb.Extents() == obb.Extents());
			Assert::IsTrue(PonyMath::Shape::AABB<float>::Axes[0] == obb.AxisX());
			Assert::IsTrue(PonyMath::Shape::AABB<float>::Axes[1] == obb.AxisY());
			Assert::IsTrue(PonyMath::Shape::AABB<float>::Axes[2] == obb.AxisZ());
		}

		TEST_METHOD(AabbQuaternionConstructorTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			const auto obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(quaternion * aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(aabb.Extents(), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(quaternion * PonyMath::Shape::AABB<float>::Axes[0], obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(quaternion * PonyMath::Shape::AABB<float>::Axes[1], obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(quaternion * PonyMath::Shape::AABB<float>::Axes[2], obb.AxisZ()));
		}

		TEST_METHOD(AabbRsMatrixConstructorTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto rotation = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			constexpr auto scaling = PonyMath::Core::Vector3<float>(-2.f, 1.2f, 2.2f);
			const auto rs = PonyMath::Core::RsMatrix(rotation, scaling);
			const auto obb = PonyMath::Shape::OBB<float>(aabb, rs);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rotation * PonyMath::Shape::AABB<float>::Axes[0] * PonyMath::Core::Sign(scaling[0]), obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rotation * PonyMath::Shape::AABB<float>::Axes[1] * PonyMath::Core::Sign(scaling[1]), obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rotation * PonyMath::Shape::AABB<float>::Axes[2] * PonyMath::Core::Sign(scaling[2]), obb.AxisZ()));
		}

		TEST_METHOD(AabbTrsMatrixConstructorTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			constexpr auto translation = PonyMath::Core::Vector3<float>(4.f, 5.f, -7.f);
			const auto rotation = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			constexpr auto scaling = PonyMath::Core::Vector3<float>(-2.f, 1.2f, 2.2f);
			const auto trs = PonyMath::Core::TrsMatrix(translation, rotation, scaling);
			const auto obb = PonyMath::Shape::OBB<float>(aabb, trs);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::TransformPoint(trs, aabb.Center()), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rotation * PonyMath::Shape::AABB<float>::Axes[0] * PonyMath::Core::Sign(scaling[0]), obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rotation * PonyMath::Shape::AABB<float>::Axes[1] * PonyMath::Core::Sign(scaling[1]), obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rotation * PonyMath::Shape::AABB<float>::Axes[2] * PonyMath::Core::Sign(scaling[2]), obb.AxisZ()));
		}

		TEST_METHOD(ObbQuaternionConstructorTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			const auto quaternion1 = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.1f, -1.7f, 2.2f));
			const auto obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			const auto obb1 = PonyMath::Shape::OBB<float>(obb, quaternion1);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(quaternion1 * quaternion * aabb.Center(), obb1.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(aabb.Extents(), obb1.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(quaternion1 * quaternion * PonyMath::Shape::AABB<float>::Axes[0], obb1.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(quaternion1 * quaternion * PonyMath::Shape::AABB<float>::Axes[1], obb1.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(quaternion1 * quaternion * PonyMath::Shape::AABB<float>::Axes[2], obb1.AxisZ()));
		}

		TEST_METHOD(ObbRsMatrixConstructorTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto rotation = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			constexpr auto scaling = PonyMath::Core::Vector3<float>(-2.f, 1.2f, 2.2f);
			const auto rotation1 = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(2.1f, 0.3f, 2.2f));
			constexpr auto scaling1 = PonyMath::Core::Vector3<float>(3.f, 0.2f, -2.2f);
			const auto rs = PonyMath::Core::RsMatrix(rotation, scaling);
			const auto rs1 = PonyMath::Core::RsMatrix(rotation1, scaling1);
			const auto obb = PonyMath::Shape::OBB<float>(aabb, rs);
			const auto obb1 = PonyMath::Shape::OBB<float>(obb, rs1);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs1 * rs * aabb.Center(), obb1.Center()));
			const auto axisX = rs1 * rs * PonyMath::Shape::AABB<float>::Axes[0];
			const auto axisY = rs1 * rs * PonyMath::Shape::AABB<float>::Axes[1];
			const auto axisZ = rs1 * rs * PonyMath::Shape::AABB<float>::Axes[2];
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector3<float>(axisX.Magnitude() * aabb.ExtentX(), axisY.Magnitude() * aabb.ExtentY(), axisZ.Magnitude() * aabb.ExtentZ()), obb1.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX.Normalized(), obb1.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY.Normalized(), obb1.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ.Normalized(), obb1.AxisZ()));
		}

		TEST_METHOD(ObbTrsMatrixConstructorTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			constexpr auto translation = PonyMath::Core::Vector3<float>(4.f, 5.f, -7.f);
			const auto rotation = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			constexpr auto scaling = PonyMath::Core::Vector3<float>(-2.f, 1.2f, 2.2f);
			constexpr auto translation1 = PonyMath::Core::Vector3<float>(-1.f, -2.f, 5.f);
			const auto rotation1 = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(2.1f, 0.3f, 2.2f));
			constexpr auto scaling1 = PonyMath::Core::Vector3<float>(3.f, 0.2f, -2.2f);
			const auto trs = PonyMath::Core::TrsMatrix(translation, rotation, scaling);
			const auto trs1 = PonyMath::Core::TrsMatrix(translation1, rotation1, scaling1);
			const auto obb = PonyMath::Shape::OBB<float>(aabb, trs);
			const auto obb1 = PonyMath::Shape::OBB<float>(obb, trs1);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::TransformPoint(trs1, PonyMath::Core::TransformPoint(trs, aabb.Center())), obb1.Center()));
			const auto axisX = PonyMath::Core::TransformDirection(trs1, PonyMath::Core::TransformDirection(trs, PonyMath::Shape::AABB<float>::Axes[0]));
			const auto axisY = PonyMath::Core::TransformDirection(trs1, PonyMath::Core::TransformDirection(trs, PonyMath::Shape::AABB<float>::Axes[1]));
			const auto axisZ = PonyMath::Core::TransformDirection(trs1, PonyMath::Core::TransformDirection(trs, PonyMath::Shape::AABB<float>::Axes[2]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector3<float>(axisX.Magnitude() * aabb.ExtentX(), axisY.Magnitude() * aabb.ExtentY(), axisZ.Magnitude() * aabb.ExtentZ()), obb1.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX.Normalized(), obb1.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY.Normalized(), obb1.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ.Normalized(), obb1.AxisZ()));
		}

		TEST_METHOD(ResolveExtentsAxesTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			auto rotation = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			auto scaling = PonyMath::Core::Vector3<float>(-2.f, 1.2f, 2.2f);
			auto rs = PonyMath::Core::RsMatrix(rotation, scaling);
			auto obb = PonyMath::Shape::OBB<float>(aabb, rs);
			auto axisX = (rs * PonyMath::Shape::AABB<float>::Axes[0]).Normalized();
			auto axisY = (rs * PonyMath::Shape::AABB<float>::Axes[1]).Normalized();
			auto axisZ = (rs * PonyMath::Shape::AABB<float>::Axes[2]).Normalized();
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ, obb.AxisZ()));

			scaling = PonyMath::Core::Vector3<float>(0.f, 1.2f, 2.2f);
			rs = PonyMath::Core::RsMatrix(rotation, scaling);
			obb = PonyMath::Shape::OBB<float>(aabb, rs);
			axisY = (rs * PonyMath::Shape::AABB<float>::Axes[1]).Normalized();
			axisZ = (rs * PonyMath::Shape::AABB<float>::Axes[2]).Normalized();
			axisX = PonyMath::Core::Cross(axisY, axisZ);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ, obb.AxisZ()));

			scaling = PonyMath::Core::Vector3<float>(-2.f, 0.f, 2.2f);
			rs = PonyMath::Core::RsMatrix(rotation, scaling);
			obb = PonyMath::Shape::OBB<float>(aabb, rs);
			axisX = (rs * PonyMath::Shape::AABB<float>::Axes[0]).Normalized();
			axisZ = (rs * PonyMath::Shape::AABB<float>::Axes[2]).Normalized();
			axisY = PonyMath::Core::Cross(axisZ, axisX);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ, obb.AxisZ()));

			scaling = PonyMath::Core::Vector3<float>(0.f, 0.f, 2.2f);
			rs = PonyMath::Core::RsMatrix(rotation, scaling);
			obb = PonyMath::Shape::OBB<float>(aabb, rs);
			axisZ = (rs * PonyMath::Shape::AABB<float>::Axes[2]).Normalized();
			axisX = PonyMath::Core::Cross(axisZ, PonyMath::Core::Vector3<float>::Predefined::Up).Normalized();
			axisY = PonyMath::Core::Cross(axisZ, axisX);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ, obb.AxisZ()));

			scaling = PonyMath::Core::Vector3<float>(-2.f, 1.2f, 0.f);
			rs = PonyMath::Core::RsMatrix(rotation, scaling);
			obb = PonyMath::Shape::OBB<float>(aabb, rs);
			axisX = (rs * PonyMath::Shape::AABB<float>::Axes[0]).Normalized();
			axisY = (rs * PonyMath::Shape::AABB<float>::Axes[1]).Normalized();
			axisZ = PonyMath::Core::Cross(axisX, axisY);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ, obb.AxisZ()));

			scaling = PonyMath::Core::Vector3<float>(0.f, 1.2f, 0.f);
			rs = PonyMath::Core::RsMatrix(rotation, scaling);
			obb = PonyMath::Shape::OBB<float>(aabb, rs);
			axisY = (rs * PonyMath::Shape::AABB<float>::Axes[1]).Normalized();
			axisX = PonyMath::Core::Cross(axisY, PonyMath::Core::Vector3<float>::Predefined::Up).Normalized();
			axisZ = PonyMath::Core::Cross(axisX, axisY);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ, obb.AxisZ()));

			scaling = PonyMath::Core::Vector3<float>(-2.f, 0.f, 0.f);
			rs = PonyMath::Core::RsMatrix(rotation, scaling);
			obb = PonyMath::Shape::OBB<float>(aabb, rs);
			axisX = (rs * PonyMath::Shape::AABB<float>::Axes[0]).Normalized();
			axisY = PonyMath::Core::Cross(axisX, PonyMath::Core::Vector3<float>::Predefined::Up).Normalized();
			axisZ = PonyMath::Core::Cross(axisX, axisY);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ, obb.AxisZ()));

			scaling = PonyMath::Core::Vector3<float>(0.f, 0.f, 0.f);
			rs = PonyMath::Core::RsMatrix(rotation, scaling);
			obb = PonyMath::Shape::OBB<float>(aabb, rs);
			axisX = PonyMath::Shape::AABB<float>::Axes[0];
			axisY = PonyMath::Shape::AABB<float>::Axes[1];
			axisZ = PonyMath::Shape::AABB<float>::Axes[2];
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ, obb.AxisZ()));

			rotation = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.f, 0.f, 0.f));
			scaling = PonyMath::Core::Vector3<float>(0.f, 0.f, 2.2f);
			rs = PonyMath::Core::RsMatrix(rotation, scaling);
			obb = PonyMath::Shape::OBB<float>(aabb, rs);
			axisX = PonyMath::Shape::AABB<float>::Axes[1];
			axisY = -PonyMath::Shape::AABB<float>::Axes[0];
			axisZ = PonyMath::Shape::AABB<float>::Axes[2];
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ, obb.AxisZ()));

			scaling = PonyMath::Core::Vector3<float>(0.f, 1.2f, 0.f);
			rs = PonyMath::Core::RsMatrix(rotation, scaling);
			obb = PonyMath::Shape::OBB<float>(aabb, rs);
			axisX = -PonyMath::Shape::AABB<float>::Axes[2];
			axisY = PonyMath::Shape::AABB<float>::Axes[1];
			axisZ = PonyMath::Shape::AABB<float>::Axes[0];
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ, obb.AxisZ()));

			rotation = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.f, 0.f, 90.f) * PonyMath::Core::DegToRad<float>);
			scaling = PonyMath::Core::Vector3<float>(-2.f, 0.f, 0.f);
			rs = PonyMath::Core::RsMatrix(rotation, scaling);
			obb = PonyMath::Shape::OBB<float>(aabb, rs);
			axisX = -PonyMath::Shape::AABB<float>::Axes[1];
			axisY = PonyMath::Shape::AABB<float>::Axes[2];
			axisZ = -PonyMath::Shape::AABB<float>::Axes[0];
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs* aabb.Center(), obb.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling)), obb.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obb.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obb.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisZ, obb.AxisZ()));
		}

		TEST_METHOD(SizeTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			const auto obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			Assert::AreEqual(4., static_cast<double>(obb.Width()), 0.0001);
			Assert::AreEqual(10., static_cast<double>(obb.Height()), 0.0001);
			Assert::AreEqual(2., static_cast<double>(obb.Depth()), 0.0001);
			Assert::AreEqual(4., static_cast<double>(obb.Size(0)), 0.0001);
			Assert::AreEqual(10., static_cast<double>(obb.Size(1)), 0.0001);
			Assert::AreEqual(2., static_cast<double>(obb.Size(2)), 0.0001);
		}

		TEST_METHOD(CornerTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			constexpr auto translation = PonyMath::Core::Vector3<float>(4.f, 5.f, -7.f);
			const auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			constexpr auto scaling = PonyMath::Core::Vector3<float>(-2.f, 1.2f, 2.2f);
			const auto trs = PonyMath::Core::TrsMatrix(translation, quaternion, scaling);
			const auto obb = PonyMath::Shape::OBB<float>(aabb, trs);

			const auto center = PonyMath::Core::TransformPoint(trs, aabb.Center());
			const auto extents = PonyMath::Core::Abs(PonyMath::Core::Multiply(aabb.Extents(), scaling));
			const auto axisX = quaternion * PonyMath::Shape::AABB<float>::Axes[0] * PonyMath::Core::Sign(scaling[0]);
			const auto axisY = quaternion * PonyMath::Shape::AABB<float>::Axes[1] * PonyMath::Core::Sign(scaling[1]);
			const auto axisZ = quaternion * PonyMath::Shape::AABB<float>::Axes[2] * PonyMath::Core::Sign(scaling[2]);

			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] - axisY * extents[1] - axisZ * extents[2], obb.LeftBottomNear()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] - axisY * extents[1] - axisZ * extents[2], obb.RightBottomNear()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] + axisY * extents[1] - axisZ * extents[2], obb.LeftTopNear()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] + axisY * extents[1] - axisZ * extents[2], obb.RightTopNear()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] - axisY * extents[1] + axisZ * extents[2], obb.LeftBottomFar()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] - axisY * extents[1] + axisZ * extents[2], obb.RightBottomFar()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] + axisY * extents[1] + axisZ * extents[2], obb.LeftTopFar()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] + axisY * extents[1] + axisZ * extents[2], obb.RightTopFar()));

			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] - axisY * extents[1] - axisZ * extents[2], obb.Corner(0)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] - axisY * extents[1] - axisZ * extents[2], obb.Corner(1)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] + axisY * extents[1] - axisZ * extents[2], obb.Corner(2)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] + axisY * extents[1] - axisZ * extents[2], obb.Corner(3)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] - axisY * extents[1] + axisZ * extents[2], obb.Corner(4)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] - axisY * extents[1] + axisZ * extents[2], obb.Corner(5)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] + axisY * extents[1] + axisZ * extents[2], obb.Corner(6)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] + axisY * extents[1] + axisZ * extents[2], obb.Corner(7)));

			const std::array<PonyMath::Core::Vector3<float>, 8> corners = obb.Corners();
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] - axisY * extents[1] - axisZ * extents[2], corners[0]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] - axisY * extents[1] - axisZ * extents[2], corners[1]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] + axisY * extents[1] - axisZ * extents[2], corners[2]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] + axisY * extents[1] - axisZ * extents[2], corners[3]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] - axisY * extents[1] + axisZ * extents[2], corners[4]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] - axisY * extents[1] + axisZ * extents[2], corners[5]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] + axisY * extents[1] + axisZ * extents[2], corners[6]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] + axisY * extents[1] + axisZ * extents[2], corners[7]));
		}

		TEST_METHOD(AreaTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			const auto obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			Assert::AreEqual(136., static_cast<double>(obb.Area()), 0.0001);
		}

		TEST_METHOD(VolumeTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			const auto obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			Assert::AreEqual(80., static_cast<double>(obb.Volume()), 0.0001);
		}

		TEST_METHOD(IsFiniteTest)
		{
			auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			auto obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			Assert::IsTrue(obb.IsFinite());

			for (std::size_t i = 0; i < 3; ++i)
			{
				const auto was = obb.Center();
				auto newCenter = was;
				newCenter[i] = std::numeric_limits<float>::quiet_NaN();
				aabb = PonyMath::Shape::AABB<float>(newCenter, aabb.Extents());
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsFalse(obb.IsFinite());
				aabb = PonyMath::Shape::AABB<float>(was, aabb.Extents());
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			}

			for (std::size_t i = 0; i < 3; ++i)
			{
				const auto was = obb.Extents();
				auto newExtents = was;
				newExtents[i] = std::numeric_limits<float>::quiet_NaN();
				aabb = PonyMath::Shape::AABB<float>(aabb.Center(), newExtents);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsFalse(obb.IsFinite());
				aabb = PonyMath::Shape::AABB<float>(aabb.Center(), was);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			}
		}

		TEST_METHOD(ContainsTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			const auto obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			Assert::IsTrue(obb.Contains(obb.Center()));
			Assert::IsTrue(obb.Contains(obb.Center() + obb.AxisX() * obb.ExtentX() * 0.75f - obb.AxisY() * obb.ExtentY() * 0.5f + obb.AxisZ() * obb.ExtentZ() * 0.2f));
			Assert::IsTrue(obb.Contains(obb.Center() - obb.AxisX() * obb.ExtentX() * 0.75f + obb.AxisY() * obb.ExtentY() * 0.5f - obb.AxisZ() * obb.ExtentZ() * 0.2f));
			Assert::IsFalse(obb.Contains(obb.Center() + obb.AxisX() * obb.ExtentX() * 1.75f - obb.AxisY() * obb.ExtentY() * 0.5f + obb.AxisZ() * obb.ExtentZ() * 0.2f));
			Assert::IsFalse(obb.Contains(obb.Center() + obb.AxisX() * obb.ExtentX() * 0.75f - obb.AxisY() * obb.ExtentY() * 1.05f - obb.AxisZ() * obb.ExtentZ() * 1.2f));
		}

		TEST_METHOD(ToStringTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			const auto obb = PonyMath::Shape::OBB<float>(aabb, quaternion);

			const std::string expected = std::format("Center: {}, Extents: {}, AxisX: {}, AxisY: {}, AxisZ: {}", obb.Center().ToString(), obb.Extents().ToString(),
				obb.AxisX().ToString(), obb.AxisY().ToString(), obb.AxisZ().ToString());
			Assert::AreEqual(expected, obb.ToString());

			std::ostringstream ss;
			ss << obb;
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(ConvertTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			const auto obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			const auto converted = static_cast<PonyMath::Shape::OBB<double>>(obb);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(static_cast<PonyMath::Core::Vector3<double>>(obb.Center()), converted.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(static_cast<PonyMath::Core::Vector3<double>>(obb.Extents()), converted.Extents()));
			for (std::size_t i = 0; i < 3; ++i)
			{
				Assert::IsTrue(PonyMath::Core::AreAlmostEqual(static_cast<PonyMath::Core::Vector3<double>>(obb.Axis(i)), converted.Axis(i)));
			}
		}

		TEST_METHOD(AssignmentTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			const auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f));
			const auto obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			auto copied = PonyMath::Shape::OBB<float>();
			copied = obb;
			Assert::IsTrue(obb == copied);

			auto moved = PonyMath::Shape::OBB<float>();
			moved = std::move(copied);
			Assert::IsTrue(obb == moved);
		}

		TEST_METHOD(EqualTest)
		{
			auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.f, 0.f, 0.f));
			auto obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			auto copied = obb;
			Assert::IsTrue(obb == copied);

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = obb.Center()[i];
				aabb.Center()[i] = std::nextafter(was, 0.f);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsFalse(obb == copied);
				aabb.Center()[i] += 1.f;
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsFalse(obb == copied);
				aabb.Center()[i] = was;
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			}

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = obb.Extents()[i];
				aabb.Extent(i, std::nextafter(was, 0.f));
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsFalse(obb == copied);
				aabb.Extent(i, was + 1.f);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsFalse(obb == copied);
				aabb.Extent(i, was);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			}

			aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			auto euler = PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f);
			quaternion = PonyMath::Core::RotationQuaternion(euler);
			obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			copied = obb;
			Assert::IsTrue(obb == copied);

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = euler[i];
				euler[i] = std::nextafter(was, 0.f);
				quaternion = PonyMath::Core::RotationQuaternion(euler);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsFalse(obb == copied);
				euler[i] += 0.1f;
				quaternion = PonyMath::Core::RotationQuaternion(euler);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsFalse(obb == copied);
				euler[i] = was;
				quaternion = PonyMath::Core::RotationQuaternion(euler);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			}
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			auto aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			auto quaternion = PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.f, 0.f, 0.f));
			auto obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			auto copied = obb;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obb, copied));

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = obb.Center()[i];
				aabb.Center()[i] = std::nextafter(was, 0.f);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obb, copied));
				aabb.Center()[i] += 1.f;
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(obb, copied));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obb, copied, 5.f));
				aabb.Center()[i] = was;
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			}

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = obb.Extents()[i];
				aabb.Extent(i, std::nextafter(was, 0.f));
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obb, copied));
				aabb.Extent(i, was + 1.f);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(obb, copied));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obb, copied, 5.f));
				aabb.Extent(i, was);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			}

			aabb = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(3.f, 5.f, 7.f), PonyMath::Core::Vector3<float>(2.f, 5.f, 1.f));
			auto euler = PonyMath::Core::Vector3<float>(1.1f, 0.7f, -1.2f);
			quaternion = PonyMath::Core::RotationQuaternion(euler);
			obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			copied = obb;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obb, copied));

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = euler[i];
				euler[i] = std::nextafter(was, 0.f);
				quaternion = PonyMath::Core::RotationQuaternion(euler);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obb, copied));
				euler[i] += 0.1f;
				quaternion = PonyMath::Core::RotationQuaternion(euler);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(obb, copied));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obb, copied, 5.f));
				euler[i] = was;
				quaternion = PonyMath::Core::RotationQuaternion(euler);
				obb = PonyMath::Shape::OBB<float>(aabb, quaternion);
			}
		}

		static constexpr PonyMath::Shape::OBB<float> ObbConstexpr()
		{
			auto defaultObb = PonyMath::Shape::OBB<float>();
			auto moved = std::move(defaultObb);

			auto copied = PonyMath::Shape::OBB<float>();
			copied = moved;

			moved = std::move(copied);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			constexpr auto aabb = PonyMath::Shape::AABB<float>();

			[[maybe_unused]] constexpr auto defaultObb = PonyMath::Shape::OBB<float>();
			[[maybe_unused]] constexpr auto obb = PonyMath::Shape::OBB<float>(aabb);
			[[maybe_unused]] constexpr auto copied = obb;
			[[maybe_unused]] constexpr auto moved = ObbConstexpr();

			[[maybe_unused]] constexpr auto center = obb.Center();
			[[maybe_unused]] constexpr auto extentX = obb.ExtentX();
			[[maybe_unused]] constexpr auto extentY = obb.ExtentY();
			[[maybe_unused]] constexpr auto extentZ = obb.ExtentZ();
			[[maybe_unused]] constexpr auto extent = obb.Extent(2);
			[[maybe_unused]] constexpr auto extents = obb.Extents();
			[[maybe_unused]] constexpr auto axisX = obb.AxisX();
			[[maybe_unused]] constexpr auto axisY = obb.AxisY();
			[[maybe_unused]] constexpr auto axisZ = obb.AxisZ();
			[[maybe_unused]] constexpr auto axis = obb.Axis(0);
			[[maybe_unused]] constexpr auto axisElement = obb.Axes()[0][0];

			[[maybe_unused]] constexpr auto width = obb.Width();
			[[maybe_unused]] constexpr auto height = obb.Height();
			[[maybe_unused]] constexpr auto depth = obb.Depth();
			[[maybe_unused]] constexpr auto size = obb.Size(1);

			[[maybe_unused]] constexpr auto leftBottomNear = obb.LeftBottomNear();
			[[maybe_unused]] constexpr auto rightBottomNear = obb.RightBottomNear();
			[[maybe_unused]] constexpr auto leftTopNear = obb.LeftTopNear();
			[[maybe_unused]] constexpr auto rightTopNear = obb.RightTopNear();
			[[maybe_unused]] constexpr auto leftBottomFar = obb.LeftBottomFar();
			[[maybe_unused]] constexpr auto rightBottomFar = obb.RightBottomFar();
			[[maybe_unused]] constexpr auto leftTopFar = obb.LeftTopFar();
			[[maybe_unused]] constexpr auto rightTopFar = obb.RightTopFar();
			[[maybe_unused]] constexpr auto corner = obb.Corner(5);
			[[maybe_unused]] constexpr auto corners = obb.Corners();

			[[maybe_unused]] constexpr auto area = obb.Area();
			[[maybe_unused]] constexpr auto volume = obb.Volume();

			[[maybe_unused]] constexpr auto converted = static_cast<PonyMath::Shape::OBB<double>>(obb);

			[[maybe_unused]] constexpr bool equal = obb == defaultObb;
			[[maybe_unused]] constexpr bool notEqual = obb != defaultObb;
			[[maybe_unused]] constexpr bool areAlmostEqual = PonyMath::Shape::AreAlmostEqual(obb, defaultObb);
		}
	};
}
