/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cmath>
#include <cstddef>
#include <format>
#include <limits>
#include <numbers>
#include <ostream>
#include <type_traits>
#include <utility>

import PonyMath.Core;
import PonyMath.Shape;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Shape
{
	TEST_CLASS(CircleTests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyMath::Shape::Circle<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Shape::Circle<double>::ValueType>);
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyMath::Shape::Circle<float>(PonyMath::Core::Vector2<float>::Predefined::Zero, 0.f) == PonyMath::Shape::Circle<float>::Predefined::Zero);
		}

		TEST_METHOD(DefaultConstructorTest)
		{
			const auto circle = PonyMath::Shape::Circle<float>();
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Zero == circle.Center());
			Assert::AreEqual(0.f, circle.Radius());
		}

		TEST_METHOD(ConstructorValueTest)
		{
			const auto circle = PonyMath::Shape::Circle<float>(5.f, -2.f, 4.f);
			Assert::AreEqual(5.f, circle.Center().X());
			Assert::AreEqual(-2.f, circle.Center().Y());
			Assert::AreEqual(4.f, circle.Radius());
		}

		TEST_METHOD(ConstructorTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			const auto circle = PonyMath::Shape::Circle<float>(center, radius);
			Assert::IsTrue(center == circle.Center());
			Assert::AreEqual(radius, circle.Radius());
		}

		TEST_METHOD(CopyConstructorTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			constexpr auto circle = PonyMath::Shape::Circle<float>(center, radius);
			const auto copied = circle;
			Assert::IsTrue(center == copied.Center());
			Assert::AreEqual(radius, copied.Radius());
		}

		TEST_METHOD(MoveConstructorTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			auto circle = PonyMath::Shape::Circle<float>(center, radius);
			const auto moved = std::move(circle);
			Assert::IsTrue(center == moved.Center());
			Assert::AreEqual(radius, moved.Radius());
		}

		TEST_METHOD(CenterTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			auto circle = PonyMath::Shape::Circle<float>(center, radius);
			Assert::IsTrue(center == circle.Center());

			constexpr auto center1 = PonyMath::Core::Vector2<float>(-2.f, -2.f);
			circle.Center() = center1;
			Assert::IsTrue(center1 == circle.Center());

			const auto circleC = circle;
			Assert::IsTrue(center1 == circleC.Center());
		}

		TEST_METHOD(RadiusTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			auto circle = PonyMath::Shape::Circle<float>(center, radius);
			Assert::AreEqual(radius, circle.Radius());

			constexpr float radius1 = 5.f;
			circle.Radius() = radius1;
			Assert::AreEqual(radius1, circle.Radius());

			const auto circleC = circle;
			Assert::AreEqual(radius1, circleC.Radius());
		}

		TEST_METHOD(DiameterTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			constexpr auto circle = PonyMath::Shape::Circle<float>(center, radius);
			Assert::AreEqual(radius * 2.f, circle.Diameter(), 0.00001f);
		}

		TEST_METHOD(PerimeterTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			constexpr auto circle = PonyMath::Shape::Circle<float>(center, radius);
			Assert::AreEqual(2.f * std::numbers::pi_v<float> * radius, circle.Perimeter(), 0.0001f);
		}

		TEST_METHOD(AreaTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			constexpr auto circle = PonyMath::Shape::Circle<float>(center, radius);
			Assert::AreEqual(std::numbers::pi_v<float> * radius * radius, circle.Area(), 0.0001f);
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			auto circle = PonyMath::Shape::Circle<float>(center, radius);
			Assert::IsTrue(circle.IsFinite());

			for (std::size_t i = 0; i < 2; ++i)
			{
				const auto was = center[i];
				circle.Center()[i] = std::numeric_limits<float>::quiet_NaN();
				Assert::IsFalse(circle.IsFinite());
				circle.Center()[i] = was;
			}

			circle.Radius() = std::numeric_limits<float>::quiet_NaN();
			Assert::IsFalse(circle.IsFinite());
		}

		TEST_METHOD(ContainsTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			constexpr auto circle = PonyMath::Shape::Circle<float>(center, radius);

			Assert::IsTrue(circle.Contains(center));
			Assert::IsTrue(circle.Contains(center + PonyMath::Core::Vector2<float>(-1.f, 1.f)));
			Assert::IsFalse(circle.Contains(PonyMath::Core::Vector2<float>::Predefined::Zero));
			Assert::IsFalse(circle.Contains(PonyMath::Core::Vector2<float>(10.f, 11.f)));
		}

		TEST_METHOD(ClosestPointTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			constexpr auto circle = PonyMath::Shape::Circle<float>(center, radius);

			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center, circle.ClosestPoint(center)));
			auto vector = center + PonyMath::Core::Vector2<float>(1.f, 1.f);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(vector, circle.ClosestPoint(vector)));
			vector = center + PonyMath::Core::Vector2<float>(10.f, -12.f);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual((vector - center).Normalized() * radius + center, circle.ClosestPoint(vector)));
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			constexpr auto circle = PonyMath::Shape::Circle<float>(center, radius);

			const std::string expected = std::format("Center: {}, Radius: {}", center.ToString(), radius);
			Assert::AreEqual(expected, circle.ToString());

			std::ostringstream ss;
			ss << circle;
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(ConvertTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			constexpr auto circle = PonyMath::Shape::Circle<float>(center, radius);
			const auto converted = static_cast<PonyMath::Shape::Circle<double>>(circle);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(static_cast<PonyMath::Core::Vector2<double>>(center), converted.Center()));
			Assert::AreEqual(2., converted.Radius(), 0.00001);
		}

		TEST_METHOD(AssignmentTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			constexpr auto circle = PonyMath::Shape::Circle<float>(center, radius);

			auto copied = PonyMath::Shape::Circle<float>();
			copied = circle;
			Assert::IsTrue(circle == copied);

			auto moved = PonyMath::Shape::Circle<float>();
			moved = std::move(copied);
			Assert::IsTrue(circle == moved);
		}

		TEST_METHOD(EqualTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			constexpr auto circle = PonyMath::Shape::Circle<float>(center, radius);
			auto other = circle;
			Assert::IsTrue(other == circle);

			for (std::size_t i = 0; i < 2; ++i)
			{
				const float was = center[i];
				other.Center()[i] = std::nextafter(was, 0.f);
				Assert::IsFalse(other == circle);
				other.Center()[i] += 1.f;
				Assert::IsFalse(other == circle);
				other.Center()[i] = was;
			}

			other.Radius() = std::nextafter(radius, 0.f);
			Assert::IsFalse(other == circle);
			other.Radius() += 1.f;
			Assert::IsFalse(other == circle);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr auto center = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			constexpr float radius = 2.f;
			constexpr auto circle = PonyMath::Shape::Circle<float>(center, radius);
			auto other = circle;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(other, circle));

			for (std::size_t i = 0; i < 2; ++i)
			{
				const float was = center[i];
				other.Center()[i] = std::nextafter(was, 0.f);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(other, circle));
				other.Center()[i] += 1.f;
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(other, circle));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(other, circle, 5.f));
				other.Center()[i] = was;
			}

			other.Radius() = std::nextafter(radius, 0.f);
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(other, circle));
			other.Radius() += 1.f;
			Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(other, circle));
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(other, circle, 5.f));
		}

		static constexpr PonyMath::Shape::Circle<float> CircleConstexpr()
		{
			auto circle = PonyMath::Shape::Circle<float>(2.f, 3.f, 5.f);
			auto moved = std::move(circle);

			moved.Center() = PonyMath::Core::Vector2<float>(1.f, 2.f);
			moved.Radius() = 6.f;

			auto copied = PonyMath::Shape::Circle<float>();
			copied = moved;

			moved = std::move(copied);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultCircle = PonyMath::Shape::Circle<float>();
			[[maybe_unused]] constexpr auto circle = PonyMath::Shape::Circle<float>(2.f, 3.f, 5.f);
			[[maybe_unused]] constexpr auto circleV = PonyMath::Shape::Circle<float>(PonyMath::Core::Vector2<float>(2.f, 4.f), 6.f);
			[[maybe_unused]] constexpr auto copied = circle;
			[[maybe_unused]] constexpr auto moved = CircleConstexpr();

			[[maybe_unused]] constexpr auto center = circle.Center();
			[[maybe_unused]] constexpr auto radius = circle.Radius();

			[[maybe_unused]] constexpr auto diameter = circle.Diameter();

			[[maybe_unused]] constexpr auto perimeter = circle.Perimeter();
			[[maybe_unused]] constexpr auto area = circle.Area();

			[[maybe_unused]] constexpr auto contains = circle.Contains(PonyMath::Core::Vector2<float>(2.f, 4.f));

			[[maybe_unused]] constexpr auto converted = static_cast<PonyMath::Shape::Circle<double>>(circle);

			[[maybe_unused]] constexpr bool equal = circle == circleV;
			[[maybe_unused]] constexpr bool notEqual = circle != circleV;
		}
	};
}
