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
	TEST_CLASS(SphereTests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyMath::Shape::Sphere<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Shape::Sphere<double>::ValueType>);
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyMath::Shape::Sphere<float>(PonyMath::Core::Vector3<float>::Predefined::Zero, 0.f) == PonyMath::Shape::Sphere<float>::Predefined::Zero);
		}

		TEST_METHOD(DefaultConstructorTest)
		{
			const auto sphere = PonyMath::Shape::Sphere<float>();
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Zero == sphere.Center());
			Assert::AreEqual(0.f, sphere.Radius());
		}
		
		TEST_METHOD(ConstructorValueTest)
		{
			const auto sphere = PonyMath::Shape::Sphere<float>(5.f, -2.f, 2.f, 4.f);
			Assert::AreEqual(5.f, sphere.Center().X());
			Assert::AreEqual(-2.f, sphere.Center().Y());
			Assert::AreEqual(2.f, sphere.Center().Z());
			Assert::AreEqual(4.f, sphere.Radius());
		}
		
		TEST_METHOD(ConstructorTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			const auto sphere = PonyMath::Shape::Sphere<float>(center, radius);
			Assert::IsTrue(center == sphere.Center());
			Assert::AreEqual(radius, sphere.Radius());
		}
		
		TEST_METHOD(CopyConstructorTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			constexpr auto sphere = PonyMath::Shape::Sphere<float>(center, radius);
			const auto copied = sphere;
			Assert::IsTrue(center == copied.Center());
			Assert::AreEqual(radius, copied.Radius());
		}
		
		TEST_METHOD(MoveConstructorTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			auto sphere = PonyMath::Shape::Sphere<float>(center, radius);
			const auto moved = std::move(sphere);
			Assert::IsTrue(center == moved.Center());
			Assert::AreEqual(radius, moved.Radius());
		}
		
		TEST_METHOD(CenterTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			auto sphere = PonyMath::Shape::Sphere<float>(center, radius);
			Assert::IsTrue(center == sphere.Center());

			constexpr auto center1 = PonyMath::Core::Vector3<float>(-2.f, -2.f, 1.f);
			sphere.Center() = center1;
			Assert::IsTrue(center1 == sphere.Center());

			const auto sphereC = sphere;
			Assert::IsTrue(center1 == sphereC.Center());
		}
		
		TEST_METHOD(RadiusTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			auto sphere = PonyMath::Shape::Sphere<float>(center, radius);
			Assert::AreEqual(radius, sphere.Radius());

			constexpr float radius1 = 5.f;
			sphere.Radius() = radius1;
			Assert::AreEqual(radius1, sphere.Radius());

			const auto sphereC = sphere;
			Assert::AreEqual(radius1, sphereC.Radius());
		}
		
		TEST_METHOD(DiameterTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			constexpr auto sphere = PonyMath::Shape::Sphere<float>(center, radius);
			Assert::AreEqual(radius * 2.f, sphere.Diameter(), 0.00001f);
		}
		
		TEST_METHOD(AreaTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			constexpr auto sphere = PonyMath::Shape::Sphere<float>(center, radius);
			Assert::AreEqual(4.f * std::numbers::pi_v<float> * radius * radius, sphere.Area(), 0.0001f);
		}

		TEST_METHOD(VolumeTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			constexpr auto sphere = PonyMath::Shape::Sphere<float>(center, radius);
			Assert::AreEqual(4.f / 3.f * std::numbers::pi_v<float> * radius * radius * radius, sphere.Volume(), 0.0001f);
		}
		
		TEST_METHOD(IsFiniteTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			auto sphere = PonyMath::Shape::Sphere<float>(center, radius);
			Assert::IsTrue(sphere.IsFinite());

			for (std::size_t i = 0; i < 3; ++i)
			{
				const auto was = center[i];
				sphere.Center()[i] = std::numeric_limits<float>::quiet_NaN();
				Assert::IsFalse(sphere.IsFinite());
				sphere.Center()[i] = was;
			}

			sphere.Radius() = std::numeric_limits<float>::quiet_NaN();
			Assert::IsFalse(sphere.IsFinite());
		}
		
		TEST_METHOD(ContainsTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			constexpr auto sphere = PonyMath::Shape::Sphere<float>(center, radius);

			Assert::IsTrue(sphere.Contains(center));
			Assert::IsTrue(sphere.Contains(center + PonyMath::Core::Vector3<float>(-1.f, 1.f, 1.f)));
			Assert::IsFalse(sphere.Contains(PonyMath::Core::Vector3<float>::Predefined::Zero));
			Assert::IsFalse(sphere.Contains(PonyMath::Core::Vector3<float>(10.f, 11.f, 12.f)));
		}
		
		TEST_METHOD(ClosestPointTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			constexpr auto sphere = PonyMath::Shape::Sphere<float>(center, radius);

			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(center, sphere.ClosestPoint(center)));
			auto vector = center + PonyMath::Core::Vector3<float>(1.f, 1.f, -1.f);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(vector, sphere.ClosestPoint(vector)));
			vector = center + PonyMath::Core::Vector3<float>(10.f, -12.f, 11.f);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual((vector - center).Normalized() * radius + center, sphere.ClosestPoint(vector)));
		}
		
		TEST_METHOD(ToStringTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			constexpr auto sphere = PonyMath::Shape::Sphere<float>(center, radius);

			const std::string expected = std::format("Center: {}, Radius: {}", center.ToString(), radius);
			Assert::AreEqual(expected, sphere.ToString());

			std::ostringstream ss;
			ss << sphere;
			Assert::AreEqual(expected, ss.str());
		}
		
		TEST_METHOD(ConvertTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			constexpr auto sphere = PonyMath::Shape::Sphere<float>(center, radius);
			const auto converted = static_cast<PonyMath::Shape::Sphere<double>>(sphere);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(static_cast<PonyMath::Core::Vector3<double>>(center), converted.Center()));
			Assert::AreEqual(2., converted.Radius(), 0.00001);
		}
		
		TEST_METHOD(AssignmentTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			constexpr auto sphere = PonyMath::Shape::Sphere<float>(center, radius);

			auto copied = PonyMath::Shape::Sphere<float>();
			copied = sphere;
			Assert::IsTrue(sphere == copied);

			auto moved = PonyMath::Shape::Sphere<float>();
			moved = std::move(copied);
			Assert::IsTrue(sphere == moved);
		}
		
		TEST_METHOD(EqualTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			constexpr auto sphere = PonyMath::Shape::Sphere<float>(center, radius);
			auto other = sphere;
			Assert::IsTrue(other == sphere);

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = center[i];
				other.Center()[i] = std::nextafter(was, 0.f);
				Assert::IsFalse(other == sphere);
				other.Center()[i] += 1.f;
				Assert::IsFalse(other == sphere);
				other.Center()[i] = was;
			}

			other.Radius() = std::nextafter(radius, 0.f);
			Assert::IsFalse(other == sphere);
			other.Radius() += 1.f;
			Assert::IsFalse(other == sphere);
		}
		
		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr auto center = PonyMath::Core::Vector3<float>(-2.f, -1.f, 2.f);
			constexpr float radius = 2.f;
			constexpr auto sphere = PonyMath::Shape::Sphere<float>(center, radius);
			auto other = sphere;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(other, sphere));

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = center[i];
				other.Center()[i] = std::nextafter(was, 0.f);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(other, sphere));
				other.Center()[i] += 1.f;
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(other, sphere));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(other, sphere, 5.f));
				other.Center()[i] = was;
			}

			other.Radius() = std::nextafter(radius, 0.f);
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(other, sphere));
			other.Radius() += 1.f;
			Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(other, sphere));
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(other, sphere, 5.f));
		}

		static constexpr PonyMath::Shape::Sphere<float> SphereConstexpr()
		{
			auto sphere = PonyMath::Shape::Sphere<float>(2.f, 3.f, 5.f, 6.f);
			auto moved = std::move(sphere);

			moved.Center() = PonyMath::Core::Vector3<float>(1.f, 2.f, 3.f);
			moved.Radius() = 6.f;

			auto copied = PonyMath::Shape::Sphere<float>();
			copied = moved;

			moved = std::move(copied);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultSphere = PonyMath::Shape::Sphere<float>();
			[[maybe_unused]] constexpr auto sphere = PonyMath::Shape::Sphere<float>(2.f, 3.f, 5.f, 2.f);
			[[maybe_unused]] constexpr auto sphereV = PonyMath::Shape::Sphere<float>(PonyMath::Core::Vector3<float>(2.f, 4.f, 4.f), 6.f);
			[[maybe_unused]] constexpr auto copied = sphere;
			[[maybe_unused]] constexpr auto moved = SphereConstexpr();

			[[maybe_unused]] constexpr auto center = sphere.Center();
			[[maybe_unused]] constexpr auto radius = sphere.Radius();

			[[maybe_unused]] constexpr auto diameter = sphere.Diameter();

			[[maybe_unused]] constexpr auto area = sphere.Area();
			[[maybe_unused]] constexpr auto volume = sphere.Volume();

			[[maybe_unused]] constexpr auto contains = sphere.Contains(PonyMath::Core::Vector3<float>(2.f, 4.f, 3.f));

			[[maybe_unused]] constexpr auto converted = static_cast<PonyMath::Shape::Sphere<double>>(sphere);

			[[maybe_unused]] constexpr bool equal = sphere == sphereV;
			[[maybe_unused]] constexpr bool notEqual = sphere != sphereV;
		}
	};
}
