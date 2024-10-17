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
#include <format>
#include <numbers>
#include <string>
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

		TEST_METHOD(PositionTest)
		{
			auto transform = PonyMath::Space::Transform2D();
			constexpr auto position = PonyMath::Core::Vector2<float>(3.f, -2.f);
			transform.Position(position);
			Assert::IsTrue(position == transform.Position());
		}

		TEST_METHOD(RotationTest)
		{
			auto transform = PonyMath::Space::Transform2D();
			constexpr float rotation = 0.99f;
			transform.Rotation(rotation);
			Assert::AreEqual(rotation, transform.Rotation());
		}

		TEST_METHOD(ScaleTest)
		{
			auto transform = PonyMath::Space::Transform2D();
			constexpr auto scale = PonyMath::Core::Vector2<float>(0.5f, 1.2f);
			transform.Scale(scale);
			Assert::IsTrue(scale == transform.Scale());

			constexpr float uniformScale = 3.f;
			transform.Scale(uniformScale);
			Assert::IsTrue(PonyMath::Core::Vector2<float>(uniformScale, uniformScale) == transform.Scale());
		}

		TEST_METHOD(TrsMatrixTest)
		{
			constexpr auto position = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float rotation = 0.99f;
			constexpr auto scale = PonyMath::Core::Vector2<float>(0.5f, 1.2f);
			const auto transform = PonyMath::Space::Transform2D(position, rotation, scale);
			Assert::IsTrue(PonyMath::Core::TrsMatrix(position, rotation, scale) == transform.TrsMatrix());
		}

		TEST_METHOD(DirectionsTest)
		{
			constexpr auto position = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float rotation = 0.99f;
			constexpr auto scale = PonyMath::Core::Vector2<float>(0.5f, 1.2f);
			const auto transform = PonyMath::Space::Transform2D(position, rotation, scale);
			Assert::IsTrue(PonyMath::Core::Rotate(PonyMath::Core::Vector2<float>::Predefined::Up, rotation) == transform.Up());
			Assert::IsTrue(PonyMath::Core::Rotate(PonyMath::Core::Vector2<float>::Predefined::Down, rotation) == transform.Down());
			Assert::IsTrue(PonyMath::Core::Rotate(PonyMath::Core::Vector2<float>::Predefined::Right, rotation) == transform.Right());
			Assert::IsTrue(PonyMath::Core::Rotate(PonyMath::Core::Vector2<float>::Predefined::Left, rotation) == transform.Left());
		}

		TEST_METHOD(TranslateTest)
		{
			constexpr auto position = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float rotation = 0.99f;
			constexpr auto scale = PonyMath::Core::Vector2<float>(0.5f, 1.2f);
			auto transform = PonyMath::Space::Transform2D(position, rotation, scale);
			constexpr auto translation = PonyMath::Core::Vector2<float>(-3.1f, 4.5f);
			transform.Translate(translation);
			Assert::IsTrue(position + translation == transform.Position());
		}

		TEST_METHOD(RotateTest)
		{
			constexpr auto position = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float rotation = 0.99f;
			constexpr auto scale = PonyMath::Core::Vector2<float>(0.5f, 1.2f);
			auto transform = PonyMath::Space::Transform2D(position, rotation, scale);
			constexpr float addedRotation = -0.5f;
			transform.Rotate(addedRotation);
			Assert::AreEqual(rotation + addedRotation, transform.Rotation());
		}

		TEST_METHOD(LookInTest)
		{
			constexpr auto position = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float rotation = 0.99f;
			constexpr auto scale = PonyMath::Core::Vector2<float>(0.5f, 1.2f);
			auto transform = PonyMath::Space::Transform2D(position, rotation, scale);

			transform.LookIn(PonyMath::Core::Vector2<float>::Predefined::Right);
			Assert::AreEqual(0., static_cast<double>(transform.Rotation()), 0.001);

			transform.LookIn(PonyMath::Core::Vector2<float>::Predefined::Up);
			Assert::AreEqual(std::numbers::pi_v<double> / 2., static_cast<double>(transform.Rotation()), 0.001);

			transform.LookIn(PonyMath::Core::Vector2<float>::Predefined::Left);
			Assert::AreEqual(std::numbers::pi_v<double>, static_cast<double>(transform.Rotation()), 0.001);

			transform.LookIn(PonyMath::Core::Vector2<float>::Predefined::Down);
			Assert::AreEqual(-std::numbers::pi_v<double> / 2., static_cast<double>(transform.Rotation()), 0.001);

			transform.LookIn(PonyMath::Core::Vector2<float>(1.f, 1.f).Normalized());
			Assert::AreEqual(std::numbers::pi_v<double> / 4., static_cast<double>(transform.Rotation()), 0.001);
		}

		TEST_METHOD(LookAtTest)
		{
			constexpr auto position = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float rotation = 0.99f;
			constexpr auto scale = PonyMath::Core::Vector2<float>(0.5f, 1.2f);
			auto transform = PonyMath::Space::Transform2D(position, rotation, scale);

			transform.LookAt(position);
			Assert::AreEqual(rotation, transform.Rotation());

			transform.LookAt(PonyMath::Core::Vector2<float>(4.f, 3.f));
			Assert::AreEqual(1.373, static_cast<double>(transform.Rotation()), 0.001);
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr auto position = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float rotation = 0.99f;
			constexpr auto scale = PonyMath::Core::Vector2<float>(0.5f, 1.2f);
			const auto transform = PonyMath::Space::Transform2D(position, rotation, scale);

			const std::string expectedString = std::format("Position: {}, Rotation: {}, Scale: {}", position.ToString(), rotation, scale.ToString());
			Assert::AreEqual(expectedString, transform.ToString());

			std::ostringstream ss;
			ss << transform;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(AssignmentTest)
		{
			constexpr auto position = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float rotation = 0.99f;
			constexpr auto scale = PonyMath::Core::Vector2<float>(0.5f, 1.2f);
			auto transform = PonyMath::Space::Transform2D(position, rotation, scale);

			auto copiedTransform = PonyMath::Space::Transform2D();
			copiedTransform = transform;
			Assert::IsTrue(position == copiedTransform.Position());
			Assert::AreEqual(rotation, copiedTransform.Rotation());
			Assert::IsTrue(scale == copiedTransform.Scale());

			auto movedTransform = PonyMath::Space::Transform2D();
			movedTransform = std::move(transform);
			Assert::IsTrue(position == movedTransform.Position());
			Assert::AreEqual(rotation, movedTransform.Rotation());
			Assert::IsTrue(scale == movedTransform.Scale());
		}

		TEST_METHOD(EqualsTest)
		{
			constexpr auto position = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float rotation = 0.99f;
			constexpr auto scale = PonyMath::Core::Vector2<float>(0.5f, 1.2f);
			const auto transform = PonyMath::Space::Transform2D(position, rotation, scale);

			auto otherTransform = transform;
			Assert::IsTrue(transform == otherTransform);
			Assert::IsFalse(transform != otherTransform);

			otherTransform.Translate(PonyMath::Core::Vector2<float>(1.f, -1.f));
			Assert::IsFalse(transform == otherTransform);
			Assert::IsTrue(transform != otherTransform);

			otherTransform.Position(position);
			otherTransform.Rotate(3.f);
			Assert::IsFalse(transform == otherTransform);
			Assert::IsTrue(transform != otherTransform);

			otherTransform.Rotation(rotation);
			otherTransform.Scale(PonyMath::Core::Vector2<float>::Predefined::One);
			Assert::IsFalse(transform == otherTransform);
			Assert::IsTrue(transform != otherTransform);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr auto position = PonyMath::Core::Vector2<float>(3.f, -2.f);
			constexpr float rotation = 0.99f;
			constexpr auto scale = PonyMath::Core::Vector2<float>(0.5f, 1.2f);
			const auto transform = PonyMath::Space::Transform2D(position, rotation, scale);

			auto otherTransform = transform;
			Assert::IsTrue(PonyMath::Space::AreAlmostEqual(transform, otherTransform));

			otherTransform.Position(PonyMath::Core::Vector2<float>(std::nextafter(position.X(), 0.f), std::nextafter(position.Y(), 0.f)));
			Assert::IsTrue(PonyMath::Space::AreAlmostEqual(transform, otherTransform));

			otherTransform.Position(position);
			otherTransform.Rotation(std::nextafter(rotation, 0.f));
			Assert::IsTrue(PonyMath::Space::AreAlmostEqual(transform, otherTransform));

			otherTransform.Rotation(rotation);
			otherTransform.Scale(PonyMath::Core::Vector2<float>(std::nextafter(scale.X(), 0.f), std::nextafter(scale.Y(), 0.f)));

			Assert::IsFalse(PonyMath::Space::AreAlmostEqual(transform, PonyMath::Space::Transform2D()));
			Assert::IsTrue(PonyMath::Space::AreAlmostEqual(transform, PonyMath::Space::Transform2D(), 1000.f));
		}
	};
}
