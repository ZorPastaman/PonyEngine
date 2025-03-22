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
#include <cstdint>
#include <format>
#include <limits>
#include <ostream>
#include <type_traits>
#include <utility>

import PonyMath.Core;
import PonyMath.Shape;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Shape
{
	TEST_CLASS(PlaneTests)
	{
		TEST_METHOD(TypeTests)
		{
			Assert::IsTrue(std::is_same_v<float, PonyMath::Shape::Plane<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Shape::Plane<double>::ValueType>);
		}

		TEST_METHOD(DefaultConstructorTest)
		{
			const auto plane = PonyMath::Shape::Plane<float>();
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Forward == plane.Normal());
			Assert::AreEqual(0.f, plane.Distance());
		}

		TEST_METHOD(ConstructorTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(-1.f, 2.f, 5.f).Normalized();
			constexpr float distance = 2.f;
			const auto plane = PonyMath::Shape::Plane<float>(normal, distance);
			Assert::IsTrue(normal == plane.Normal());
			Assert::AreEqual(distance, plane.Distance());
		}

		TEST_METHOD(PointConstructorTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(-1.f, 2.f, -5.f).Normalized();
			constexpr auto point = PonyMath::Core::Vector3<float>(2.f, 3.f, -1.f);
			const auto plane = PonyMath::Shape::Plane<float>(normal, point);
			Assert::IsTrue(normal == plane.Normal());
			Assert::AreEqual(-1.643, static_cast<double>(plane.Distance()), 0.001);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(0.f, plane.Distance(point)));
		}

		TEST_METHOD(PointsConstructorTest)
		{
			constexpr auto point0 = PonyMath::Core::Vector3<float>(9.f, -4.f, 1.f);
			constexpr auto point1 = PonyMath::Core::Vector3<float>(2.f, -2.f, -5.f);
			constexpr auto point2 = PonyMath::Core::Vector3<float>(-5.f, 2.f, 4.f);
			const auto plane = PonyMath::Shape::Plane<float>(point0, point1, point2);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector3<float>(0.369f, 0.921f, -0.123f), plane.Normal(), 0.001f));
			Assert::AreEqual(0.491, static_cast<double>(plane.Distance()), 0.001);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(0.f, plane.Distance(point0)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(0.f, plane.Distance(point1)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(0.f, plane.Distance(point2)));
		}

		TEST_METHOD(CopyConstructorTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(-1.f, 2.f, 5.f).Normalized();
			constexpr float distance = 2.f;
			const auto plane = PonyMath::Shape::Plane<float>(normal, distance);
			const auto copied = plane;
			Assert::IsTrue(normal == copied.Normal());
			Assert::AreEqual(distance, copied.Distance());
		}

		TEST_METHOD(MoveConstructorTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(-1.f, 2.f, 5.f).Normalized();
			constexpr float distance = 2.f;
			auto plane = PonyMath::Shape::Plane<float>(normal, distance);
			const auto moved = std::move(plane);
			Assert::IsTrue(normal == moved.Normal());
			Assert::AreEqual(distance, moved.Distance());
		}

		TEST_METHOD(NormalTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(2.f, 1.f, -5.f).Normalized();
			constexpr float distance = -3.f;
			auto plane = PonyMath::Shape::Plane<float>(normal, distance);
			Assert::IsTrue(normal == plane.Normal());

			const auto normal1 = PonyMath::Core::Vector3<float>(-2.f, -3.f, 1.f).Normalized();
			plane.Normal() = normal1;
			Assert::IsTrue(normal1 == plane.Normal());

			const auto planeC = plane;
			Assert::IsTrue(normal1 == planeC.Normal());
		}

		TEST_METHOD(DistanceTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(2.f, 1.f, -5.f).Normalized();
			constexpr float distance = -3.f;
			auto plane = PonyMath::Shape::Plane<float>(normal, distance);
			Assert::AreEqual(distance, plane.Distance());

			constexpr float distance1 = 4.f;
			plane.Distance() = distance1;
			Assert::AreEqual(distance1, plane.Distance());

			const auto planeC = plane;
			Assert::AreEqual(distance1, planeC.Distance());
		}

		TEST_METHOD(FlipTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(2.f, 1.f, -5.f).Normalized();
			constexpr float distance = -3.f;
			auto plane = PonyMath::Shape::Plane<float>(normal, distance);
			const auto flipped = plane.Flipped();
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(-normal, flipped.Normal()));
			Assert::AreEqual(static_cast<double>(-distance), static_cast<double>(flipped.Distance()), 0.0001);

			plane.Flip();
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(flipped, plane));
		}

		TEST_METHOD(IsFiniteTest)
		{
			auto normal = PonyMath::Core::Vector3<float>(2.f, 1.f, -5.f).Normalized();
			constexpr float distance = -3.f;
			auto plane = PonyMath::Shape::Plane<float>(normal, distance);
			Assert::IsTrue(plane.IsFinite());

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = normal[i];
				normal[i] = std::numeric_limits<float>::quiet_NaN();
				plane.Normal() = normal;
				Assert::IsFalse(plane.IsFinite());
				normal[i] = was;
				plane.Normal() = normal;
			}

			plane.Distance() = std::numeric_limits<float>::quiet_NaN();
			Assert::IsFalse(plane.IsFinite());
		}

		TEST_METHOD(DistancePointTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(2.f, 1.f, -5.f).Normalized();
			constexpr float distance = -3.f;
			const auto plane = PonyMath::Shape::Plane<float>(normal, distance);

			Assert::AreEqual(0., static_cast<double>(plane.Distance(PonyMath::Core::Vector3<float>(1.095f, 0.548f, -2.739f))), 0.001);
			Assert::AreEqual(-4.607, static_cast<double>(plane.Distance(PonyMath::Core::Vector3<float>(-2.f, 0.2f, 1.f))), 0.001);
			Assert::AreEqual(4.12, static_cast<double>(plane.Distance(PonyMath::Core::Vector3<float>(5.f, -1.f, -6.f))), 0.001);
		}

		TEST_METHOD(ProjectTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(2.f, 1.f, -5.f).Normalized();
			constexpr float distance = -3.f;
			const auto plane = PonyMath::Shape::Plane<float>(normal, distance);

			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector3<float>(1.095f, 0.548f, -2.739f), plane.Project(PonyMath::Core::Vector3<float>(1.095f, 0.548f, -2.739f)), 0.001f));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector3<float>(0.822f, 2.011f, -2.555f), plane.Project(PonyMath::Core::Vector3<float>(-3.f, 0.1f, 7.f)), 0.001f));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector3<float>(6.629f, -4.686f, -1.572f), plane.Project(PonyMath::Core::Vector3<float>(10.f, -3.f, -10.f)), 0.001f));
		}

		TEST_METHOD(SideTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(2.f, 1.f, -5.f).Normalized();
			auto point = PonyMath::Core::Vector3<float>(2.f, 3.f, 4.f);
			const auto plane = PonyMath::Shape::Plane<float>(normal, point);
			Assert::AreEqual(std::int8_t{0}, plane.Side(point));
			point = PonyMath::Core::Vector3<float>(20.f, 3.f, -4.f);
			Assert::AreEqual(std::int8_t{1}, plane.Side(point));
			point = PonyMath::Core::Vector3<float>(-20.f, -3.f, -4.f);
			Assert::AreEqual(std::int8_t{-1}, plane.Side(point));
		}

		TEST_METHOD(ToStringTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(2.f, 1.f, -5.f).Normalized();
			constexpr float distance = -3.f;
			const auto plane = PonyMath::Shape::Plane<float>(normal, distance);

			const std::string expected = std::format("Normal: {}, Distance: {}", plane.Normal().ToString(), plane.Distance());
			Assert::AreEqual(expected, plane.ToString());

			std::ostringstream ss;
			ss << plane;
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(ConvertTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(2.f, 1.f, -5.f).Normalized();
			constexpr float distance = -3.f;
			const auto plane = PonyMath::Shape::Plane<float>(normal, distance);
			const auto converted = static_cast<PonyMath::Shape::Plane<double>>(plane);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(static_cast<PonyMath::Core::Vector3<double>>(normal), converted.Normal()));
			Assert::AreEqual(static_cast<double>(distance), converted.Distance(), 0.00001);
		}

		TEST_METHOD(AssignmentTest)
		{
			const auto normal = PonyMath::Core::Vector3<float>(2.f, 1.f, -5.f).Normalized();
			constexpr float distance = -3.f;
			const auto plane = PonyMath::Shape::Plane<float>(normal, distance);

			auto copied = PonyMath::Shape::Plane<float>();
			copied = plane;
			Assert::IsTrue(normal == copied.Normal());
			Assert::AreEqual(distance, copied.Distance());

			auto moved = PonyMath::Shape::Plane<float>();
			moved = std::move(copied);
			Assert::IsTrue(normal == moved.Normal());
			Assert::AreEqual(distance, moved.Distance());
		}

		TEST_METHOD(EqualTest)
		{
			auto normal = PonyMath::Core::Vector3<float>(2.f, 1.f, -5.f).Normalized();
			float distance = -3.f;
			auto plane = PonyMath::Shape::Plane<float>(normal, distance);
			const auto copied = plane;
			Assert::IsTrue(plane == copied);

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = normal[i];
				normal[i] = std::nextafter(was, 0.f);
				plane = PonyMath::Shape::Plane<float>(normal, distance);
				Assert::IsFalse(copied == plane);
				normal[i] += 1.f;
				plane = PonyMath::Shape::Plane<float>(normal, distance);
				Assert::IsFalse(copied == plane);
				normal[i] = was;
				plane = PonyMath::Shape::Plane<float>(normal, distance);
			}

			distance = std::nextafter(distance, 0.f);
			plane = PonyMath::Shape::Plane<float>(normal, distance);
			Assert::IsFalse(copied == plane);
			distance += 1.f;
			plane = PonyMath::Shape::Plane<float>(normal, distance);
			Assert::IsFalse(copied == plane);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			auto normal = PonyMath::Core::Vector3<float>(2.f, 1.f, -5.f).Normalized();
			float distance = -3.f;
			auto plane = PonyMath::Shape::Plane<float>(normal, distance);
			const auto copied = plane;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(copied, plane));

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = normal[i];
				normal[i] = std::nextafter(was, 0.f);
				plane = PonyMath::Shape::Plane<float>(normal, distance);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(copied, plane));
				normal[i] += 1.f;
				plane = PonyMath::Shape::Plane<float>(normal, distance);
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(copied, plane));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(copied, plane, 5.f));
				normal[i] = was;
				plane = PonyMath::Shape::Plane<float>(normal, distance);
			}

			distance = std::nextafter(distance, 0.f);
			plane = PonyMath::Shape::Plane<float>(normal, distance);
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(copied, plane));
			distance += 1.f;
			plane = PonyMath::Shape::Plane<float>(normal, distance);
			Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(copied, plane));
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(copied, plane, 5.f));
		}

		static constexpr PonyMath::Shape::Plane<float> PlaneConstexpr()
		{
			auto plane = PonyMath::Shape::Plane<float>(PonyMath::Core::Vector3<float>::Predefined::Right, 4.f);
			auto moved = std::move(plane);

			moved.Normal() = PonyMath::Core::Vector3<float>::Predefined::Up;
			moved.Distance() = -5.f;

			moved.Flip();

			auto copied = PonyMath::Shape::Plane<float>(PonyMath::Core::Vector3<float>::Predefined::Right, 4.f);
			copied = moved;
			moved = std::move(copied);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultPlane = PonyMath::Shape::Plane<float>();
			[[maybe_unused]] constexpr auto plane = PonyMath::Shape::Plane<float>(PonyMath::Core::Vector3<float>::Predefined::Right, 4.f);
			[[maybe_unused]] constexpr auto planeP = PonyMath::Shape::Plane<float>(PonyMath::Core::Vector3<float>::Predefined::Right, PonyMath::Core::Vector3<float>(4.f, 2.f, 6.f));
			[[maybe_unused]] constexpr auto copied = plane;
			[[maybe_unused]] constexpr auto moved = PlaneConstexpr();

			[[maybe_unused]] constexpr auto normal = plane.Normal();
			[[maybe_unused]] constexpr auto distance = plane.Distance();

			[[maybe_unused]] constexpr auto flipped = plane.Flipped();

			[[maybe_unused]] constexpr auto distanceP = plane.Distance(PonyMath::Core::Vector3<float>(4.f, 2.f, 6.f));
			[[maybe_unused]] constexpr auto projected = plane.Project(PonyMath::Core::Vector3<float>(4.f, 2.f, 6.f));
			[[maybe_unused]] constexpr std::int8_t side = plane.Side(PonyMath::Core::Vector3<float>(4.f, 2.f, 6.f));

			[[maybe_unused]] constexpr auto converted = static_cast<PonyMath::Shape::Plane<float>>(plane);

			[[maybe_unused]] constexpr bool equal = plane == planeP;
			[[maybe_unused]] constexpr bool notEqual = plane != planeP;
		}
	};
}
