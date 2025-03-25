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
	TEST_CLASS(Ray3DTests)
	{
		TEST_METHOD(DefaultConstructorTest)
		{
			const auto ray = PonyMath::Shape::Ray3D<float>();
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Zero == ray.Origin());
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Forward == ray.Direction());
		}

		TEST_METHOD(ConstructorTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			const auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);
			Assert::IsTrue(origin == ray.Origin());
			Assert::IsTrue(direction == ray.Direction());
		}

		TEST_METHOD(CopyConstructorTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			const auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);
			const auto copied = ray;
			Assert::IsTrue(origin == copied.Origin());
			Assert::IsTrue(direction == copied.Direction());
		}

		TEST_METHOD(MoveConstructorTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);
			const auto moved = std::move(ray);
			Assert::IsTrue(origin == moved.Origin());
			Assert::IsTrue(direction == moved.Direction());
		}

		TEST_METHOD(CreateTargetTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(-4.f, 1.f, 2.f);
			constexpr auto target = PonyMath::Core::Vector3<float>(4.f, 5.f, -4.f);
			const auto ray = PonyMath::Shape::Ray3D<float>::Create(origin, target);
			const auto expectedDirection = (target - origin).Normalized();
			Assert::IsTrue(origin == ray.Origin());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expectedDirection, ray.Direction()));
		}
		
		TEST_METHOD(OriginTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);
			Assert::IsTrue(origin == ray.Origin());

			constexpr auto origin1 = PonyMath::Core::Vector3<float>(-5.f, -2.f, 1.f);
			ray.Origin() = origin1;
			Assert::IsTrue(origin1 == ray.Origin());

			const auto rayC = ray;
			Assert::IsTrue(origin1 == rayC.Origin());
		}

		TEST_METHOD(DirectionTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);
			Assert::IsTrue(direction == ray.Direction());

			const auto direction1 = PonyMath::Core::Vector3<float>(1.f, -0.2f, 2.f).Normalized();
			ray.Direction() = direction1;
			Assert::IsTrue(direction1 == ray.Direction());

			const auto rayC = ray;
			Assert::IsTrue(direction1 == rayC.Direction());
		}
		
		TEST_METHOD(FlipTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);

			const auto flipped = ray.Flipped();
			Assert::IsTrue(origin == flipped.Origin());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(-direction, flipped.Direction()));

			ray.Flip();
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(flipped, ray));
		}
		
		TEST_METHOD(IsFiniteTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);
			Assert::IsTrue(ray.IsFinite());

			for (std::size_t i = 0; i < 3; ++i)
			{
				const auto was = origin[i];
				ray.Origin()[i] = std::numeric_limits<float>::quiet_NaN();
				Assert::IsFalse(ray.IsFinite());
				ray.Origin()[i] = was;
			}

			for (std::size_t i = 0; i < 3; ++i)
			{
				const auto was = direction[i];
				ray.Direction()[i] = std::numeric_limits<float>::quiet_NaN();
				Assert::IsFalse(ray.IsFinite());
				ray.Direction()[i] = was;
			}
		}
		
		TEST_METHOD(ProjectTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			const auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);

			auto vector = origin + direction * 6.f;
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(vector, ray.Project(vector)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(origin + direction * 3.f, ray.Project(vector, 3.f)));

			vector = origin + direction * -2.f;
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(origin, ray.Project(vector)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(origin, ray.Project(vector, 3.f)));

			vector = PonyMath::Core::Vector3<float>(-3.f, 10.f, -2.f);
			auto expected = origin + direction * PonyMath::Core::Dot(direction, vector - origin);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, ray.Project(vector)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(origin + direction, ray.Project(vector, 1.f)));

			vector = PonyMath::Core::Vector3<float>(-6.f, -10.f, -5.f);
			expected = origin + direction * PonyMath::Core::Dot(direction, vector - origin);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, ray.Project(vector)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(origin + direction, ray.Project(vector, 1.f)));

			vector = PonyMath::Core::Vector3<float>(5.f, -2.f, 0.5f);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(origin, ray.Project(vector)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(origin, ray.Project(vector, 1.f)));
		}
		
		TEST_METHOD(NormalizeTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			const auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);

			auto vector = origin + direction * 6.f;
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(6.f, ray.Normalize(vector)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(vector, ray.Unnormalize(6.f)));

			vector = origin + direction * -2.f;
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(-2.f, ray.Normalize(vector)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(vector, ray.Unnormalize(-2.f)));

			vector = PonyMath::Core::Vector3<float>(-3.f, 10.f, -2.f);
			auto expected = PonyMath::Core::Dot(direction, vector - origin);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, ray.Normalize(vector)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(origin + direction * expected, ray.Unnormalize(expected)));

			vector = PonyMath::Core::Vector3<float>(-6.f, -10.f, -5.f);
			expected = PonyMath::Core::Dot(direction, vector - origin);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, ray.Normalize(vector)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(origin + direction * expected, ray.Unnormalize(expected)));

			vector = PonyMath::Core::Vector3<float>(5.f, -2.f, 0.5f);
			expected = PonyMath::Core::Dot(direction, vector - origin);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, ray.Normalize(vector)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(origin + direction * expected, ray.Unnormalize(expected)));
		}
		
		TEST_METHOD(ToStringTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			const auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);

			const std::string expected = std::format("Origin: {}, Direction: {}", origin.ToString(), direction.ToString());
			Assert::AreEqual(expected, ray.ToString());

			std::ostringstream ss;
			ss << ray;
			Assert::AreEqual(expected, ss.str());
		}
		
		TEST_METHOD(ConvertTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			const auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);
			const auto converted = static_cast<PonyMath::Shape::Ray3D<double>>(ray);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(static_cast<PonyMath::Core::Vector3<double>>(origin), converted.Origin()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(static_cast<PonyMath::Core::Vector3<double>>(direction), converted.Direction()));
		}
		
		TEST_METHOD(AssignmentTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			const auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);

			auto copied = PonyMath::Shape::Ray3D<float>();
			copied = ray;
			Assert::IsTrue(origin == copied.Origin());
			Assert::IsTrue(direction == copied.Direction());

			auto moved = PonyMath::Shape::Ray3D<float>();
			moved = std::move(copied);
			Assert::IsTrue(origin == moved.Origin());
			Assert::IsTrue(direction == moved.Direction());
		}
		
		TEST_METHOD(EqualTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			const auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);
			auto copied = ray;
			Assert::IsTrue(ray == copied);

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = origin[i];
				copied.Origin()[i] = std::nextafter(origin[i], 0.f);
				Assert::IsFalse(ray == copied);
				copied.Origin()[i] += 1.f;
				Assert::IsFalse(ray == copied);
				copied.Origin()[i] = was;
			}

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = direction[i];
				copied.Direction()[i] = std::nextafter(direction[i], 0.f);
				Assert::IsFalse(ray == copied);
				copied.Direction()[i] += 1.f;
				Assert::IsFalse(ray == copied);
				copied.Direction()[i] = was;
			}
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr auto origin = PonyMath::Core::Vector3<float>(3.f, -2.f, -4.f);
			const auto direction = PonyMath::Core::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
			const auto ray = PonyMath::Shape::Ray3D<float>(origin, direction);
			auto copied = ray;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(ray, copied));

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = origin[i];
				copied.Origin()[i] = std::nextafter(origin[i], 0.f);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(ray, copied));
				copied.Origin()[i] += 1.f;
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(ray, copied));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(ray, copied, 5.f));
				copied.Origin()[i] = was;
			}

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = direction[i];
				copied.Direction()[i] = std::nextafter(direction[i], 0.f);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(ray, copied));
				copied.Direction()[i] += 1.f;
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(ray, copied));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(ray, copied, 5.f));
				copied.Direction()[i] = was;
			}
		}
	};
}
