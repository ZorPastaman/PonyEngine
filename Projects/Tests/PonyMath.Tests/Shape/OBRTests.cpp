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
	TEST_CLASS(OBRTests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyMath::Shape::OBR<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Shape::OBR<double>::ValueType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{2}, PonyMath::Shape::OBR<float>::AxesCount);

			Assert::AreEqual(std::size_t{0}, PonyMath::Shape::OBR<float>::LeftBottomIndex);
			Assert::AreEqual(std::size_t{1}, PonyMath::Shape::OBR<float>::RightBottomIndex);
			Assert::AreEqual(std::size_t{2}, PonyMath::Shape::OBR<float>::LeftTopIndex);
			Assert::AreEqual(std::size_t{3}, PonyMath::Shape::OBR<float>::RightTopIndex);
			Assert::AreEqual(std::size_t{4}, PonyMath::Shape::OBR<float>::CornerCount);
		}

		TEST_METHOD(DefaultConstructorTest)
		{
			const auto obr = PonyMath::Shape::OBR<float>();
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Zero == obr.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Zero == obr.Extents());
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Right == obr.AxisX());
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Up == obr.AxisY());
		}

		TEST_METHOD(AabrConstructorTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			const auto obr = PonyMath::Shape::OBR<float>(aabr);
			Assert::IsTrue(aabr.Center() == obr.Center());
			Assert::IsTrue(aabr.Extents() == obr.Extents());
			Assert::IsTrue(PonyMath::Shape::AABR<float>::Axes[0] == obr.AxisX());
			Assert::IsTrue(PonyMath::Shape::AABR<float>::Axes[1] == obr.AxisY());
		}

		TEST_METHOD(AabrAngleConstructorTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			const auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(aabr.Center(), angle), obr.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(aabr.Extents(), obr.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[0], angle), obr.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[1], angle), obr.AxisY()));
		}

		TEST_METHOD(AabrRsMatrixConstructorTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			constexpr auto scaling = PonyMath::Core::Vector2<float>(-1.f, 2.f);
			const auto rs = PonyMath::Core::RsMatrix(angle, scaling);
			const auto obr = PonyMath::Shape::OBR<float>(aabr, rs);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabr.Center(), obr.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabr.Extents(), scaling)), obr.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[0], angle) * PonyMath::Core::Sign(scaling[0]), obr.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[1], angle) * PonyMath::Core::Sign(scaling[1]), obr.AxisY()));
		}

		TEST_METHOD(AabrTrsMatrixConstructorTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr auto translation = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float angle = 0.3f;
			constexpr auto scaling = PonyMath::Core::Vector2<float>(-1.f, 2.f);
			const auto trs = PonyMath::Core::TrsMatrix(translation, angle, scaling);
			const auto obr = PonyMath::Shape::OBR<float>(aabr, trs);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::TransformPoint(trs, aabr.Center()), obr.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabr.Extents(), scaling)), obr.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[0], angle) * PonyMath::Core::Sign(scaling[0]), obr.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[1], angle) * PonyMath::Core::Sign(scaling[1]), obr.AxisY()));
		}

		TEST_METHOD(ObrAngleConstructorTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			constexpr float angle1 = -0.1f;
			const auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			const auto obr1 = PonyMath::Shape::OBR<float>(obr, angle1);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Core::Rotate(aabr.Center(), angle), angle1), obr1.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(aabr.Extents(), obr1.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[0], angle), angle1), obr1.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[1], angle), angle1), obr1.AxisY()));
		}

		TEST_METHOD(ObrRsMatrixConstructorTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			constexpr float angle1 = -0.1f;
			constexpr auto scaling = PonyMath::Core::Vector2<float>(-1.f, 2.f);
			constexpr auto scaling1 = PonyMath::Core::Vector2<float>(1.2f, -2.3f);
			const auto rs = PonyMath::Core::RsMatrix(angle, scaling);
			const auto rs1 = PonyMath::Core::RsMatrix(angle1, scaling1);
			const auto obr = PonyMath::Shape::OBR<float>(aabr, rs);
			const auto obr1 = PonyMath::Shape::OBR<float>(obr, rs1);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs1 * rs * aabr.Center(), obr1.Center()));
			const auto axisX = rs1 * rs * PonyMath::Shape::AABR<float>::Axes[0];
			const auto axisY = rs1 * rs * PonyMath::Shape::AABR<float>::Axes[1];
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector2<float>(axisX.Magnitude() * aabr.ExtentX(), axisY.Magnitude() * aabr.ExtentY()), obr1.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX.Normalized(), obr1.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY.Normalized(), obr1.AxisY()));
		}

		TEST_METHOD(ObrTrsMatrixConstructorTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr auto translation = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr auto translation1 = PonyMath::Core::Vector2<float>(-4.f, -5.f);
			constexpr float angle = 0.3f;
			constexpr float angle1 = -1.3f;
			constexpr auto scaling = PonyMath::Core::Vector2<float>(-1.f, 2.f);
			constexpr auto scaling1 = PonyMath::Core::Vector2<float>(3.f, 4.f);
			const auto trs = PonyMath::Core::TrsMatrix(translation, angle, scaling);
			const auto trs1 = PonyMath::Core::TrsMatrix(translation1, angle1, scaling1);
			const auto obr = PonyMath::Shape::OBR<float>(aabr, trs);
			const auto obr1 = PonyMath::Shape::OBR<float>(obr, trs1);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::TransformPoint(trs1, PonyMath::Core::TransformPoint(trs, aabr.Center())), obr1.Center()));
			const auto axisX = PonyMath::Core::TransformDirection(trs1, PonyMath::Core::TransformDirection(trs, PonyMath::Shape::AABR<float>::Axes[0]));
			const auto axisY = PonyMath::Core::TransformDirection(trs1, PonyMath::Core::TransformDirection(trs, PonyMath::Shape::AABR<float>::Axes[1]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector2<float>(axisX.Magnitude() * aabr.ExtentX(), axisY.Magnitude() * aabr.ExtentY()), obr1.Extents()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX.Normalized(), obr1.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY.Normalized(), obr1.AxisY()));
		}

		TEST_METHOD(ResolveExtentsAxesTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			auto scaling = PonyMath::Core::Vector2<float>(0.f, 2.f);
			auto rs = PonyMath::Core::RsMatrix(angle, scaling);
			auto obr = PonyMath::Shape::OBR<float>(aabr, rs);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabr.Center(), obr.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabr.Extents(), scaling)), obr.Extents()));
			auto axisY = (rs * PonyMath::Shape::AABR<float>::Axes[1]).Normalized();
			auto axisX = PonyMath::Core::Vector2<float>(axisY.Y(), -axisY.X());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obr.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obr.AxisY()));

			scaling = PonyMath::Core::Vector2<float>(-1.f, 0.f);
			rs = PonyMath::Core::RsMatrix(angle, scaling);
			obr = PonyMath::Shape::OBR<float>(aabr, rs);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabr.Center(), obr.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabr.Extents(), scaling)), obr.Extents()));
			axisX = (rs * PonyMath::Shape::AABR<float>::Axes[0]).Normalized();
			axisY = PonyMath::Core::Vector2<float>(-axisX.Y(), axisX.X());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obr.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obr.AxisY()));

			scaling = PonyMath::Core::Vector2<float>(0.f, 0.f);
			rs = PonyMath::Core::RsMatrix(angle, scaling);
			obr = PonyMath::Shape::OBR<float>(aabr, rs);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(rs * aabr.Center(), obr.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Abs(PonyMath::Core::Multiply(aabr.Extents(), scaling)), obr.Extents()));
			axisX = PonyMath::Core::Vector2<float>::Predefined::Right;
			axisY = PonyMath::Core::Vector2<float>::Predefined::Up;
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisX, obr.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(axisY, obr.AxisY()));
		}

		TEST_METHOD(CenterTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			const auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(aabr.Center(), angle), obr.Center()));
		}

		TEST_METHOD(ExtentsTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			const auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::AreEqual(aabr.ExtentX(), obr.ExtentX());
			Assert::AreEqual(aabr.ExtentY(), obr.ExtentY());
			Assert::AreEqual(aabr.ExtentX(), obr.Extent(0));
			Assert::AreEqual(aabr.ExtentY(), obr.Extent(1));
			Assert::IsTrue(aabr.Extents() == obr.Extents());
		}

		TEST_METHOD(AxesTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			const auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[0], angle), obr.AxisX()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[1], angle), obr.AxisY()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[0], angle), obr.Axis(0)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[1], angle), obr.Axis(1)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[0], angle), obr.Axes()[0]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[1], angle), obr.Axes()[1]));
		}

		TEST_METHOD(SizeTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			const auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::AreEqual(4., static_cast<double>(obr.Width()), 0.0001);
			Assert::AreEqual(6., static_cast<double>(obr.Height()), 0.0001);
			Assert::AreEqual(4., static_cast<double>(obr.Size(0)), 0.0001);
			Assert::AreEqual(6., static_cast<double>(obr.Size(1)), 0.0001);
		}

		TEST_METHOD(CornerTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr auto translation = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float angle = 0.3f;
			constexpr auto scaling = PonyMath::Core::Vector2<float>(-1.f, 2.f);
			const auto trs = PonyMath::Core::TrsMatrix(translation, angle, scaling);
			const auto obr = PonyMath::Shape::OBR<float>(aabr, trs);

			const auto center = PonyMath::Core::TransformPoint(trs, aabr.Center());
			const auto extents = PonyMath::Core::Abs(PonyMath::Core::Multiply(aabr.Extents(), scaling));
			const auto axisX = PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[0], angle) * PonyMath::Core::Sign(scaling[0]);
			const auto axisY = PonyMath::Core::Rotate(PonyMath::Shape::AABR<float>::Axes[1], angle) * PonyMath::Core::Sign(scaling[1]);

			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] - axisY * extents[1], obr.LeftBottom()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] - axisY * extents[1], obr.RightBottom()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] + axisY * extents[1], obr.LeftTop()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] + axisY * extents[1], obr.RightTop()));

			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] - axisY * extents[1], obr.Corner(0)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] - axisY * extents[1], obr.Corner(1)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] + axisY * extents[1], obr.Corner(2)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] + axisY * extents[1], obr.Corner(3)));

			const std::array<PonyMath::Core::Vector2<float>, 4> corners = obr.Corners();
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] - axisY * extents[1], corners[0]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] - axisY * extents[1], corners[1]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center - axisX * extents[0] + axisY * extents[1], corners[2]));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center + axisX * extents[0] + axisY * extents[1], corners[3]));
		}

		TEST_METHOD(PerimeterTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			const auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::AreEqual(20., static_cast<double>(obr.Perimeter()), 0.0001);
		}

		TEST_METHOD(AreaTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			const auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::AreEqual(24., static_cast<double>(obr.Area()), 0.0001);
		}

		TEST_METHOD(IsFiniteTest)
		{
			auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::IsTrue(obr.IsFinite());

			for (std::size_t i = 0; i < 2; ++i)
			{
				const auto was = obr.Center();
				auto newCenter = was;
				newCenter[i] = std::numeric_limits<float>::quiet_NaN();
				aabr = PonyMath::Shape::AABR<float>(newCenter, aabr.Extents());
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
				Assert::IsFalse(obr.IsFinite());
				aabr = PonyMath::Shape::AABR<float>(was, aabr.Extents());
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
			}

			for (std::size_t i = 0; i < 2; ++i)
			{
				const auto was = obr.Extents();
				auto newExtents = was;
				newExtents[i] = std::numeric_limits<float>::quiet_NaN();
				aabr = PonyMath::Shape::AABR<float>(aabr.Center(), newExtents);
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
				Assert::IsFalse(obr.IsFinite());
				aabr = PonyMath::Shape::AABR<float>(aabr.Center(), was);
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
			}
		}

		TEST_METHOD(ContainsTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			const auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::IsTrue(obr.Contains(obr.Center()));
			Assert::IsTrue(obr.Contains(obr.Center() + obr.AxisX() * obr.ExtentX() * 0.75f - obr.AxisY() * obr.ExtentY() * 0.5f));
			Assert::IsTrue(obr.Contains(obr.Center() - obr.AxisX() * obr.ExtentX() * 0.75f + obr.AxisY() * obr.ExtentY() * 0.5f));
			Assert::IsFalse(obr.Contains(obr.Center() + obr.AxisX() * obr.ExtentX() * 1.75f - obr.AxisY() * obr.ExtentY() * 0.5f));
			Assert::IsFalse(obr.Contains(obr.Center() + obr.AxisX() * obr.ExtentX() * 0.75f - obr.AxisY() * obr.ExtentY() * 1.05f));
		}

		TEST_METHOD(ToStringTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			const auto obr = PonyMath::Shape::OBR<float>(aabr, angle);

			const std::string expected = std::format("Center: {}, Extents: {}, AxisX: {}, AxisY: {}", obr.Center().ToString(), obr.Extents().ToString(),
				obr.AxisX().ToString(), obr.AxisY().ToString());
			Assert::AreEqual(expected, obr.ToString());

			std::ostringstream ss;
			ss << obr;
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(ConvertTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			const auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			const auto converted = static_cast<PonyMath::Shape::OBR<double>>(obr);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(static_cast<PonyMath::Core::Vector2<double>>(obr.Center()), converted.Center()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(static_cast<PonyMath::Core::Vector2<double>>(obr.Extents()), converted.Extents()));
			for (std::size_t i = 0; i < 2; ++i)
			{
				Assert::IsTrue(PonyMath::Core::AreAlmostEqual(static_cast<PonyMath::Core::Vector2<double>>(obr.Axis(i)), converted.Axis(i)));
			}
		}

		TEST_METHOD(AssignmentTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			constexpr float angle = 0.3f;
			const auto obr = PonyMath::Shape::OBR<float>(aabr, angle);

			auto copied = PonyMath::Shape::OBR<float>();
			copied = obr;
			Assert::IsTrue(obr == copied);

			auto moved = PonyMath::Shape::OBR<float>();
			moved = std::move(copied);
			Assert::IsTrue(obr == moved);
		}

		TEST_METHOD(EqualTest)
		{
			auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			float angle = 0.f;
			auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			auto copied = obr;
			Assert::IsTrue(obr == copied);

			for (std::size_t i = 0; i < 2; ++i)
			{
				const float was = obr.Center()[i];
				aabr.Center()[i] = std::nextafter(was, 0.f);
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
				Assert::IsFalse(obr == copied);
				aabr.Center()[i] += 1.f;
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
				Assert::IsFalse(obr == copied);
				aabr.Center()[i] = was;
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
			}

			for (std::size_t i = 0; i < 2; ++i)
			{
				const float was = obr.Extents()[i];
				aabr.Extent(i, std::nextafter(was, 0.f));
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
				Assert::IsFalse(obr == copied);
				aabr.Extent(i, was + 1.f);
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
				Assert::IsFalse(obr == copied);
				aabr.Extent(i, was);
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
			}

			aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(3.f, 5.f), PonyMath::Core::Vector2<float>(2.f, 5.f));
			angle = -0.7f;
			obr = PonyMath::Shape::OBR<float>(aabr, angle);
			copied = obr;
			Assert::IsTrue(obr == copied);

			angle = std::nextafter(angle, 0.f);
			obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::IsFalse(obr == copied);
			angle += 0.1f;
			obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::IsFalse(obr == copied);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			auto aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(-2.f, 3.f), PonyMath::Core::Vector2<float>(2.f, 3.f));
			float angle = 0.f;
			auto obr = PonyMath::Shape::OBR<float>(aabr, angle);
			auto copied = obr;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obr, copied));

			for (std::size_t i = 0; i < 2; ++i)
			{
				const float was = obr.Center()[i];
				aabr.Center()[i] = std::nextafter(was, 0.f);
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obr, copied));
				aabr.Center()[i] += 1.f;
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(obr, copied));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obr, copied, 5.f));
				aabr.Center()[i] = was;
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
			}

			for (std::size_t i = 0; i < 2; ++i)
			{
				const float was = obr.Extents()[i];
				aabr.Extent(i, std::nextafter(was, 0.f));
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obr, copied));
				aabr.Extent(i, was + 1.f);
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(obr, copied));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obr, copied, 5.f));
				aabr.Extent(i, was);
				obr = PonyMath::Shape::OBR<float>(aabr, angle);
			}

			aabr = PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(3.f, 5.f), PonyMath::Core::Vector2<float>(2.f, 5.f));
			angle = -0.7f;
			obr = PonyMath::Shape::OBR<float>(aabr, angle);
			copied = obr;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obr, copied));

			angle = std::nextafter(angle, 0.f);
			obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obr, copied));
			angle += 0.1f;
			obr = PonyMath::Shape::OBR<float>(aabr, angle);
			Assert::IsFalse(obr == copied);
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(obr, copied, 5.f));
		}

		static constexpr PonyMath::Shape::OBR<float> ObrConstexpr()
		{
			auto defaultObr = PonyMath::Shape::OBR<float>();
			auto moved = std::move(defaultObr);

			auto copied = PonyMath::Shape::OBR<float>();
			copied = moved;

			moved = std::move(copied);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			constexpr auto aabr = PonyMath::Shape::AABR<float>();

			[[maybe_unused]] constexpr auto defaultObr = PonyMath::Shape::OBR<float>();
			[[maybe_unused]] constexpr auto obr = PonyMath::Shape::OBR<float>(aabr);
			[[maybe_unused]] constexpr auto copied = obr;
			[[maybe_unused]] constexpr auto moved = ObrConstexpr();

			[[maybe_unused]] constexpr auto center = obr.Center();
			[[maybe_unused]] constexpr auto extentX = obr.ExtentX();
			[[maybe_unused]] constexpr auto extentY = obr.ExtentY();
			[[maybe_unused]] constexpr auto extent = obr.Extent(1);
			[[maybe_unused]] constexpr auto extents = obr.Extents();
			[[maybe_unused]] constexpr auto axisX = obr.AxisX();
			[[maybe_unused]] constexpr auto axisY = obr.AxisY();
			[[maybe_unused]] constexpr auto axis = obr.Axis(0);
			[[maybe_unused]] constexpr auto axisElement = obr.Axes()[0][0];

			[[maybe_unused]] constexpr auto width = obr.Width();
			[[maybe_unused]] constexpr auto height = obr.Height();
			[[maybe_unused]] constexpr auto size = obr.Size(1);

			[[maybe_unused]] constexpr auto leftBottom = obr.LeftBottom();
			[[maybe_unused]] constexpr auto rightBottom = obr.RightBottom();
			[[maybe_unused]] constexpr auto leftTop = obr.LeftTop();
			[[maybe_unused]] constexpr auto rightTop = obr.RightTop();
			[[maybe_unused]] constexpr auto corner = obr.Corner(5);
			[[maybe_unused]] constexpr auto corners = obr.Corners();

			[[maybe_unused]] constexpr auto perimeter = obr.Perimeter();
			[[maybe_unused]] constexpr auto area = obr.Area();

			[[maybe_unused]] constexpr auto converted = static_cast<PonyMath::Shape::OBR<double>>(obr);

			[[maybe_unused]] constexpr bool equal = obr == defaultObr;
			[[maybe_unused]] constexpr bool notEqual = obr != defaultObr;
			[[maybe_unused]] constexpr bool areAlmostEqual = PonyMath::Shape::AreAlmostEqual(obr, defaultObr);
		}
	};
}
