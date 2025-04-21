/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <optional>
#include <span>
#include <vector>

import PonyMath.Core;
import PonyMath.Shape;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Shape
{
	TEST_CLASS(UtilityTests)
	{
		TEST_METHOD(CreateBoundingRectTest)
		{
			std::vector<PonyMath::Core::Vector2<float>> points;
			auto aabr = PonyMath::Shape::CreateBoundingRect(std::span<const PonyMath::Core::Vector2<float>>(points.data(), points.size()));
			Assert::IsFalse(aabr.has_value());

			points = { PonyMath::Core::Vector2<float>(2.f, -1.f) };
			aabr = PonyMath::Shape::CreateBoundingRect(std::span<const PonyMath::Core::Vector2<float>>(points.data(), points.size()));
			Assert::IsTrue(aabr.has_value());
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(PonyMath::Shape::AABR<float>(points[0], PonyMath::Core::Vector2<float>::Predefined::Zero), aabr.value()));

			points = { PonyMath::Core::Vector2<float>(2.f, -1.f), PonyMath::Core::Vector2<float>(4.f, -10.f), PonyMath::Core::Vector2<float>(1.f, 20.f), PonyMath::Core::Vector2<float>(-4.f, -5.f) };
			aabr = PonyMath::Shape::CreateBoundingRect(std::span<const PonyMath::Core::Vector2<float>>(points.data(), points.size()));
			Assert::IsTrue(aabr.has_value());
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(PonyMath::Shape::AABR<float>(PonyMath::Core::Vector2<float>(0.f, 5.f), PonyMath::Core::Vector2<float>(4.f, 15.f)), aabr.value()));
		}

		TEST_METHOD(CreateBoundingBoxTest)
		{
			std::vector<PonyMath::Core::Vector3<float>> points;
			auto aabb = PonyMath::Shape::CreateBoundingBox(std::span<const PonyMath::Core::Vector3<float>>(points.data(), points.size()));
			Assert::IsFalse(aabb.has_value());

			points = { PonyMath::Core::Vector3<float>(2.f, -1.f, 4.f) };
			aabb = PonyMath::Shape::CreateBoundingBox(std::span<const PonyMath::Core::Vector3<float>>(points.data(), points.size()));
			Assert::IsTrue(aabb.has_value());
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(PonyMath::Shape::AABB<float>(points[0], PonyMath::Core::Vector3<float>::Predefined::Zero), aabb.value()));

			points = { PonyMath::Core::Vector3<float>(2.f, -1.f, 1.f), PonyMath::Core::Vector3<float>(4.f, -10.f, -2.f), PonyMath::Core::Vector3<float>(1.f, 20.f, -5.f), PonyMath::Core::Vector3<float>(-4.f, -5.f, 2.f) };
			aabb = PonyMath::Shape::CreateBoundingBox(std::span<const PonyMath::Core::Vector3<float>>(points.data(), points.size()));
			Assert::IsTrue(aabb.has_value());
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(0.f, 5.f, -1.5f), PonyMath::Core::Vector3<float>(4.f, 15.f, 3.5f)), aabb.value()));
		}
	};
}
