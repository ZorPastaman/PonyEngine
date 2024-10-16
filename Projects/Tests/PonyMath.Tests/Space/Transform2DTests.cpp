/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <type_traits>
#include <utility>

import PonyMath.Core;
import PonyMath.Space;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Space
{
	TEST_CLASS(Transform2DTests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<PonyMath::Core::Vector2<float>, PonyMath::Space::Transform2D::PositionType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Space::Transform2D::RotationType>);
			Assert::IsTrue(std::is_same_v<PonyMath::Core::Vector2<float>, PonyMath::Space::Transform2D::ScaleType>);
		}

		TEST_METHOD(ConstructorTest)
		{
			const auto defaultTransform = PonyMath::Space::Transform2D();
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Zero == defaultTransform.Position());
			Assert::AreEqual(0.f, defaultTransform.Rotation());
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::One == defaultTransform.Scale());

			constexpr auto position = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float rotation = 0.99f;
			constexpr auto scale = PonyMath::Core::Vector2<float>(0.5f, 1.2f);
			auto transform = PonyMath::Space::Transform2D(position, rotation, scale);
			Assert::IsTrue(position == transform.Position());
			Assert::AreEqual(rotation, transform.Rotation());
			Assert::IsTrue(scale == transform.Scale());

			constexpr float uniformScale = 1.5f;
			const auto uniformTransform = PonyMath::Space::Transform2D(position, rotation, uniformScale);
			Assert::IsTrue(position == uniformTransform.Position());
			Assert::AreEqual(rotation, uniformTransform.Rotation());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(uniformScale, uniformScale) == uniformTransform.Scale());

			const PonyMath::Space::Transform2D copiedTransform = transform;
			Assert::IsTrue(position == copiedTransform.Position());
			Assert::AreEqual(rotation, copiedTransform.Rotation());
			Assert::IsTrue(scale == copiedTransform.Scale());

			const PonyMath::Space::Transform2D movedTransform = std::move(transform);
			Assert::IsTrue(position == movedTransform.Position());
			Assert::AreEqual(rotation, movedTransform.Rotation());
			Assert::IsTrue(scale == movedTransform.Scale());
		}
	};
}
