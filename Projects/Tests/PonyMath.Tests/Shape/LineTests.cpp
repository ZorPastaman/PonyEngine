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
	TEST_CLASS(LineTests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyMath::Shape::Line<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Shape::Line<double>::ValueType>);
		}

		TEST_METHOD(DefaultConstructorTest)
		{
			const auto defaultLine = PonyMath::Shape::Line<float>();
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Up == defaultLine.Normal());
			Assert::AreEqual(0.f, defaultLine.Distance());
		}

		TEST_METHOD(ConstructorTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(3.f, -2.f).Normalized();
			constexpr float distance = 4.f;
			const auto line = PonyMath::Shape::Line<float>(normal, distance);
			Assert::IsTrue(normal == line.Normal());
			Assert::AreEqual(distance, line.Distance());
		}

		TEST_METHOD(ConstructorPointTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(3.f, -2.f).Normalized();
			const auto point = PonyMath::Core::Vector2<float>(-4.f, 3.f);
			const auto line = PonyMath::Shape::Line<float>(normal, point);
			Assert::IsTrue(normal == line.Normal());
			Assert::AreEqual(0., static_cast<double>(line.Distance(point)), 0.0001);
		}

		TEST_METHOD(CopyConstructorTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(3.f, -2.f).Normalized();
			constexpr float distance = 4.f;
			const auto line = PonyMath::Shape::Line<float>(normal, distance);
			const auto copied = line;
			Assert::IsTrue(line == copied);
		}

		TEST_METHOD(MoveConstructorTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(3.f, -2.f).Normalized();
			constexpr float distance = 4.f;
			auto line = PonyMath::Shape::Line<float>(normal, distance);
			const auto moved = std::move(line);
			Assert::IsTrue(line == moved);
		}

		TEST_METHOD(CreateTwoPointsTest)
		{
			constexpr auto point0 = PonyMath::Core::Vector2<float>(4.f, 3.f);
			constexpr auto point1 = PonyMath::Core::Vector2<float>(-5.f, 1.f);
			const auto line = PonyMath::Shape::Line<float>::Create(point0, point1);
			Assert::AreEqual(0., static_cast<double>(line.Distance(point0)), 0.0001);
			Assert::AreEqual(0., static_cast<double>(line.Distance(point1)), 0.0001);
		}

		TEST_METHOD(NormalTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(4.f, -3.f).Normalized();
			constexpr float distance = 3.f;
			auto line = PonyMath::Shape::Line<float>(normal, distance);
			Assert::IsTrue(normal == line.Normal());

			const auto normal1 = PonyMath::Core::Vector2<float>(6.f, -7.f).Normalized();
			line.Normal() = normal1;
			Assert::IsTrue(normal1 == line.Normal());

			const auto lineC = line;
			Assert::IsTrue(normal1 == lineC.Normal());
		}

		TEST_METHOD(DistanceTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(4.f, -3.f).Normalized();
			constexpr float distance = 3.f;
			auto line = PonyMath::Shape::Line<float>(normal, distance);
			Assert::AreEqual(distance, line.Distance());

			constexpr float distance1 = -4.f;
			line.Distance() = distance1;
			Assert::AreEqual(distance1, line.Distance());

			const auto lineC = line;
			Assert::AreEqual(distance1, lineC.Distance());
		}

		TEST_METHOD(FlipTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(4.f, -3.f).Normalized();
			constexpr float distance = 3.f;
			auto line = PonyMath::Shape::Line<float>(normal, distance);
			const auto flipped = line.Flipped();
			Assert::IsTrue(-normal == flipped.Normal());
			Assert::AreEqual(-distance, flipped.Distance());

			line.Flip();
			Assert::IsTrue(flipped == line);
		}

		TEST_METHOD(IsFiniteTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(4.f, -3.f).Normalized();
			constexpr float distance = 3.f;
			auto line = PonyMath::Shape::Line<float>(normal, distance);
			Assert::IsTrue(line.IsFinite());

			line.Normal().X() = std::numeric_limits<float>::quiet_NaN();
			Assert::IsFalse(line.IsFinite());

			line.Normal().X() = normal.X();
			line.Normal().Y() = std::numeric_limits<float>::quiet_NaN();
			Assert::IsFalse(line.IsFinite());

			line.Normal().Y() = normal.Y();
			line.Distance() = std::numeric_limits<float>::quiet_NaN();
			Assert::IsFalse(line.IsFinite());
		}

		TEST_METHOD(DistancePointTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(4.f, -3.f).Normalized();
			constexpr float distance = 3.f;
			const auto line = PonyMath::Shape::Line<float>(normal, distance);

			Assert::AreEqual(3., static_cast<double>(line.Distance(PonyMath::Core::Vector2<float>::Predefined::Zero)), 0.0001);
			Assert::AreEqual(0., static_cast<double>(line.Distance(-normal * 3.f)), 0.0001);
			Assert::AreEqual(-3., static_cast<double>(line.Distance(-normal * 6.f)), 0.0001);
			Assert::AreEqual(5.8, static_cast<double>(line.Distance(PonyMath::Core::Vector2<float>(5.f, 2.f))), 0.0001);
			Assert::AreEqual(-4.2, static_cast<double>(line.Distance(PonyMath::Core::Vector2<float>(-6.f, 4.f))), 0.0001);
		}

		TEST_METHOD(ProjectTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(4.f, -3.f).Normalized();
			constexpr float distance = 3.f;
			const auto line = PonyMath::Shape::Line<float>(normal, distance);

			PonyMath::Core::Vector2<float> projected = line.Project(PonyMath::Core::Vector2<float>::Predefined::Zero);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector2<float>(-2.4f, 1.8f), projected));

			projected = line.Project(PonyMath::Core::Vector2<float>(-2.4f, 1.8f));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector2<float>(-2.4f, 1.8f), projected));

			projected = line.Project(PonyMath::Core::Vector2<float>(-4.8f, 3.6f));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector2<float>(-2.4f, 1.8f), projected));

			projected = line.Project(PonyMath::Core::Vector2<float>(5.f, 2.f));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector2<float>(0.36f, 5.48f), projected));

			projected = line.Project(PonyMath::Core::Vector2<float>(-6.f, 4.f));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector2<float>(-2.64f, 1.48f), projected));
		}

		TEST_METHOD(SideTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(4.f, -3.f).Normalized();
			constexpr float distance = 3.f;
			const auto line = PonyMath::Shape::Line<float>(normal, distance);

			Assert::AreEqual(std::int8_t{1}, line.Side(PonyMath::Core::Vector2<float>::Predefined::Zero));
			Assert::AreEqual(std::int8_t{0}, line.Side(-normal * 3.f));
			Assert::AreEqual(std::int8_t{-1}, line.Side(-normal * 6.f));
			Assert::AreEqual(std::int8_t{1}, line.Side(PonyMath::Core::Vector2<float>(5.f, 2.f)));
			Assert::AreEqual(std::int8_t{-1}, line.Side(PonyMath::Core::Vector2<float>(-6.f, 4.f)));
		}

		TEST_METHOD(ToStringTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(4.f, -3.f).Normalized();
			constexpr float distance = 3.f;
			const auto line = PonyMath::Shape::Line<float>(normal, distance);

			const std::string expected = std::format("Normal: {}, Distance: {}", normal.ToString(), distance);
			Assert::AreEqual(expected, line.ToString());

			std::ostringstream ss;
			ss << line;
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(ConvertTest)
		{
			const auto normal = PonyMath::Core::Vector2<float>(4.f, -3.f).Normalized();
			constexpr float distance = 3.f;
			const auto line = PonyMath::Shape::Line<float>(normal, distance);
			const auto converted = static_cast<PonyMath::Shape::Line<double>>(line);
			Assert::AreEqual(static_cast<double>(normal.X()), converted.Normal().X(), 0.0001);
			Assert::AreEqual(static_cast<double>(normal.Y()), converted.Normal().Y(), 0.0001);
			Assert::AreEqual(static_cast<double>(distance), converted.Distance(), 0.0001);
		}

		TEST_METHOD(AssignmentTest)
		{
			auto line = PonyMath::Shape::Line<float>(PonyMath::Core::Vector2<float>(1.f, 3.f).Normalized(), -6.f);

			auto copied = PonyMath::Shape::Line<float>();
			copied = line;
			Assert::IsTrue(line == copied);

			auto moved = PonyMath::Shape::Line<float>();
			moved = std::move(line);
			Assert::IsTrue(copied == moved);
		}

		TEST_METHOD(EqualTest)
		{
			auto line = PonyMath::Shape::Line<float>(PonyMath::Core::Vector2<float>(1.f, 3.f).Normalized(), -6.f);
			const auto other = line;
			Assert::IsTrue(line == other);

			line.Normal().X() = std::nextafter(line.Normal().X(), 0.f);
			Assert::IsFalse(line == other);
			line.Normal().X() += 1.f;
			Assert::IsFalse(line == other);

			line.Normal().X() = other.Normal().X();
			line.Normal().Y() = std::nextafter(line.Normal().Y(), 0.f);
			Assert::IsFalse(line == other);
			line.Normal().Y() += 1.f;
			Assert::IsFalse(line == other);

			line.Normal().Y() = other.Normal().Y();
			line.Distance() = std::nextafter(line.Distance(), 0.f);
			Assert::IsFalse(line == other);
			line.Distance() -= 1.f;
			Assert::IsFalse(line == other);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			auto line = PonyMath::Shape::Line<float>(PonyMath::Core::Vector2<float>(1.f, 3.f).Normalized(), -6.f);
			const auto other = line;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(line, other));

			line.Normal().X() = std::nextafter(line.Normal().X(), 0.f);
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(line, other));
			line.Normal().X() += 1.f;
			Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(line, other));
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(line, other, 5.f));

			line.Normal().X() = other.Normal().X();
			line.Normal().Y() = std::nextafter(line.Normal().Y(), 0.f);
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(line, other));
			line.Normal().Y() += 1.f;
			Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(line, other));
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(line, other, 5.f));

			line.Normal().Y() = other.Normal().Y();
			line.Distance() = std::nextafter(line.Distance(), 0.f);
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(line, other));
			line.Distance() -= 1.f;
			Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(line, other));
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(line, other, 5.f));
		}

		static constexpr PonyMath::Shape::Line<float> LineConstexpr()
		{
			auto line = PonyMath::Shape::Line<float>(PonyMath::Core::Vector2<float>::Predefined::Right, 2.f);
			auto moved = std::move(line);

			const auto normal = moved.Normal();
			moved.Normal() = PonyMath::Core::Vector2<float>::Predefined::Up;
			const float distance = moved.Distance();
			moved.Distance() = 5.f;

			moved.Flip();

			auto copied = PonyMath::Shape::Line<float>(normal, distance);
			copied = moved;
			moved = std::move(copied);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultLine = PonyMath::Shape::Line<float>();
			[[maybe_unused]] constexpr auto line = PonyMath::Shape::Line<float>(PonyMath::Core::Vector2<float>::Predefined::Right, 2.f);
			[[maybe_unused]] constexpr auto pointLine = PonyMath::Shape::Line<float>(PonyMath::Core::Vector2<float>::Predefined::Up, PonyMath::Core::Vector2<float>(4.f, -2.f));
			[[maybe_unused]] constexpr auto copiedLine = line;
			[[maybe_unused]] constexpr auto moved = LineConstexpr();

			[[maybe_unused]] constexpr auto normal = line.Normal();
			[[maybe_unused]] constexpr float distance = line.Distance();

			[[maybe_unused]] constexpr auto flipped = line.Flipped();

			[[maybe_unused]] constexpr auto distanceToPoint = line.Distance(PonyMath::Core::Vector2<float>::Predefined::Zero);
			[[maybe_unused]] constexpr auto projected = line.Project(PonyMath::Core::Vector2<float>::Predefined::One);

			[[maybe_unused]] constexpr auto side = line.Side(PonyMath::Core::Vector2<float>::Predefined::One);

			[[maybe_unused]] constexpr auto converted = static_cast<PonyMath::Shape::Line<double>>(line);

			[[maybe_unused]] constexpr bool equal = line == pointLine;
			[[maybe_unused]] constexpr bool notEqual = line != pointLine;

			[[maybe_unused]] constexpr bool areAlmostEqual = PonyMath::Shape::AreAlmostEqual(line, pointLine);
		}
	};
}
