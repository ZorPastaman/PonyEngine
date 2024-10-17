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
#include <string>
#include <type_traits>
#include <utility>

import PonyMath.Core;
import PonyMath.Space;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Space
{
	TEST_CLASS(Transform3DTests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<PonyMath::Core::Vector3<float>, PonyMath::Space::Transform3D::PositionType>);
			Assert::IsTrue(std::is_same_v<PonyMath::Core::Quaternion<float>, PonyMath::Space::Transform3D::RotationType>);
			Assert::IsTrue(std::is_same_v<PonyMath::Core::Vector3<float>, PonyMath::Space::Transform3D::ScaleType>);
		}

		TEST_METHOD(ConstructorTest)
		{
			const auto defaultTransform = PonyMath::Space::Transform3D();
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Zero == defaultTransform.Position());
			Assert::IsTrue(PonyMath::Core::Quaternion<float>::Predefined::Identity == defaultTransform.Rotation());
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::One == defaultTransform.Scale());

			constexpr auto position = PonyMath::Core::Vector3<float>(3.f, -2.f, 1.5f);
			const auto rotation = PonyMath::Core::Quaternion<float>(1.f, 2.f, -3.f, 4.f).Normalized();
			constexpr auto scale = PonyMath::Core::Vector3<float>(0.5f, 1.2f, 2.f);
			auto transform = PonyMath::Space::Transform3D(position, rotation, scale);
			Assert::IsTrue(position == transform.Position());
			Assert::IsTrue(rotation == transform.Rotation());
			Assert::IsTrue(scale == transform.Scale());

			constexpr float uniformScale = 1.5f;
			const auto uniformTransform = PonyMath::Space::Transform3D(position, rotation, uniformScale);
			Assert::IsTrue(position == uniformTransform.Position());
			Assert::IsTrue(rotation == uniformTransform.Rotation());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(uniformScale, uniformScale, uniformScale) == uniformTransform.Scale());

			const PonyMath::Space::Transform3D copiedTransform = transform;
			Assert::IsTrue(position == copiedTransform.Position());
			Assert::IsTrue(rotation == copiedTransform.Rotation());
			Assert::IsTrue(scale == copiedTransform.Scale());

			const PonyMath::Space::Transform3D movedTransform = std::move(transform);
			Assert::IsTrue(position == movedTransform.Position());
			Assert::IsTrue(rotation == movedTransform.Rotation());
			Assert::IsTrue(scale == movedTransform.Scale());
		}

		TEST_METHOD(PositionTest)
		{
			auto transform = PonyMath::Space::Transform3D();
			constexpr auto position = PonyMath::Core::Vector3<float>(3.f, -2.f, 1.5f);
			transform.Position(position);
			Assert::IsTrue(position == transform.Position());
		}

		TEST_METHOD(RotationTest)
		{
			auto transform = PonyMath::Space::Transform3D();
			const auto rotation = PonyMath::Core::Quaternion<float>(1.f, 2.f, -3.f, 4.f).Normalized();
			transform.Rotation(rotation);
			Assert::IsTrue(rotation == transform.Rotation());
		}

		TEST_METHOD(ScaleTest)
		{
			auto transform = PonyMath::Space::Transform3D();
			constexpr auto scale = PonyMath::Core::Vector3<float>(0.5f, 1.2f, 3.f);
			transform.Scale(scale);
			Assert::IsTrue(scale == transform.Scale());

			constexpr float uniformScale = 3.f;
			transform.Scale(uniformScale);
			Assert::IsTrue(PonyMath::Core::Vector3<float>(uniformScale, uniformScale, uniformScale) == transform.Scale());
		}

		TEST_METHOD(TrsMatrixTest)
		{
			constexpr auto position = PonyMath::Core::Vector3<float>(3.f, -2.f, 1.5f);
			const auto rotation = PonyMath::Core::Quaternion<float>(1.f, 2.f, -3.f, 4.f).Normalized();
			constexpr auto scale = PonyMath::Core::Vector3<float>(0.5f, 1.2f, 2.f);
			const auto transform = PonyMath::Space::Transform3D(position, rotation, scale);
			Assert::IsTrue(PonyMath::Core::TrsMatrix(position, rotation, scale) == transform.TrsMatrix());
		}

		TEST_METHOD(DirectionsTest)
		{
			constexpr auto position = PonyMath::Core::Vector3<float>(3.f, -2.f, 1.5f);
			const auto rotation = PonyMath::Core::Quaternion<float>(1.f, 2.f, -3.f, 4.f).Normalized();
			constexpr auto scale = PonyMath::Core::Vector3<float>(0.5f, 1.2f, 2.f);
			const auto transform = PonyMath::Space::Transform3D(position, rotation, scale);
			Assert::IsTrue(rotation * PonyMath::Core::Vector3<float>::Predefined::Forward == transform.Forward());
			Assert::IsTrue(rotation * PonyMath::Core::Vector3<float>::Predefined::Back == transform.Back());
			Assert::IsTrue(rotation * PonyMath::Core::Vector3<float>::Predefined::Up == transform.Up());
			Assert::IsTrue(rotation * PonyMath::Core::Vector3<float>::Predefined::Down == transform.Down());
			Assert::IsTrue(rotation * PonyMath::Core::Vector3<float>::Predefined::Right == transform.Right());
			Assert::IsTrue(rotation * PonyMath::Core::Vector3<float>::Predefined::Left == transform.Left());
		}

		TEST_METHOD(TranslateTest)
		{
			constexpr auto position = PonyMath::Core::Vector3<float>(3.f, -2.f, 1.5f);
			const auto rotation = PonyMath::Core::Quaternion<float>(1.f, 2.f, -3.f, 4.f).Normalized();
			constexpr auto scale = PonyMath::Core::Vector3<float>(0.5f, 1.2f, 2.f);
			auto transform = PonyMath::Space::Transform3D(position, rotation, scale);
			constexpr auto translation = PonyMath::Core::Vector3<float>(-3.1f, 4.5f, -1.f);
			transform.Translate(translation);
			Assert::IsTrue(position + translation == transform.Position());
		}

		TEST_METHOD(RotateTest)
		{
			constexpr auto position = PonyMath::Core::Vector3<float>(3.f, -2.f, 1.5f);
			const auto rotation = PonyMath::Core::Quaternion<float>(1.f, 2.f, -3.f, 4.f).Normalized();
			constexpr auto scale = PonyMath::Core::Vector3<float>(0.5f, 1.2f, 2.f);
			auto transform = PonyMath::Space::Transform3D(position, rotation, scale);
			const auto addedRotation = PonyMath::Core::Quaternion<float>(1.5f, 0.2f, -1.1f, 2.f).Normalized();
			transform.Rotate(addedRotation);
			Assert::IsTrue(addedRotation * rotation == transform.Rotation());
		}

		TEST_METHOD(LookInTest)
		{
			constexpr auto position = PonyMath::Core::Vector3<float>(3.f, -2.f, 1.5f);
			const auto rotation = PonyMath::Core::Quaternion<float>(1.f, 2.f, -3.f, 4.f).Normalized();
			constexpr auto scale = PonyMath::Core::Vector3<float>(0.5f, 1.2f, 2.f);
			auto transform = PonyMath::Space::Transform3D(position, rotation, scale);

			transform.LookIn(PonyMath::Core::Vector3<float>::Predefined::Right, PonyMath::Core::Vector3<float>::Predefined::Up);
			Assert::IsTrue(PonyMath::Core::LookInRotationQuaternion(PonyMath::Core::Vector3<float>::Predefined::Right, PonyMath::Core::Vector3<float>::Predefined::Up) == transform.Rotation());

			transform.LookIn(PonyMath::Core::Vector3<float>::Predefined::Forward, PonyMath::Core::Vector3<float>::Predefined::Up);
			Assert::IsTrue(PonyMath::Core::LookInRotationQuaternion(PonyMath::Core::Vector3<float>::Predefined::Forward, PonyMath::Core::Vector3<float>::Predefined::Up) == transform.Rotation());

			const auto direction = PonyMath::Core::Vector3<float>(1.f, 1.f, -2.f).Normalized();
			transform.LookIn(direction, PonyMath::Core::Vector3<float>::Predefined::Up);
			Assert::IsTrue(PonyMath::Core::LookInRotationQuaternion(direction, PonyMath::Core::Vector3<float>::Predefined::Up) == transform.Rotation());

			transform.LookIn(direction, PonyMath::Core::Vector3<float>(0.3f, 1.f, -0.9f).Normalized());
			Assert::IsTrue(PonyMath::Core::LookInRotationQuaternion(direction, PonyMath::Core::Vector3<float>(0.3f, 1.f, -0.9f).Normalized()) == transform.Rotation());
		}

		TEST_METHOD(LookAtTest)
		{
			constexpr auto position = PonyMath::Core::Vector3<float>(3.f, -2.f, 1.5f);
			const auto rotation = PonyMath::Core::Quaternion<float>(1.f, 2.f, -3.f, 4.f).Normalized();
			constexpr auto scale = PonyMath::Core::Vector3<float>(0.5f, 1.2f, 2.f);
			auto transform = PonyMath::Space::Transform3D(position, rotation, scale);

			transform.LookAt(position, PonyMath::Core::Vector3<float>::Predefined::Up);
			Assert::IsTrue(rotation == transform.Rotation());

			constexpr auto point = PonyMath::Core::Vector3<float>(4.f, 3.f, 2.2f);
			transform.LookAt(point, PonyMath::Core::Vector3<float>::Predefined::Up);
			Assert::IsTrue(PonyMath::Core::LookInRotationQuaternion((point - transform.Position()).Normalized(), PonyMath::Core::Vector3<float>::Predefined::Up) == transform.Rotation());

			transform.LookAt(point, PonyMath::Core::Vector3<float>(0.3f, 1.f, -0.9f).Normalized());
			Assert::IsTrue(PonyMath::Core::LookInRotationQuaternion((point - transform.Position()).Normalized(), PonyMath::Core::Vector3<float>(0.3f, 1.f, -0.9f).Normalized()) == transform.Rotation());
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr auto position = PonyMath::Core::Vector3<float>(3.f, -2.f, 1.5f);
			const auto rotation = PonyMath::Core::Quaternion<float>(1.f, 2.f, -3.f, 4.f).Normalized();
			constexpr auto scale = PonyMath::Core::Vector3<float>(0.5f, 1.2f, 2.f);
			const auto transform = PonyMath::Space::Transform3D(position, rotation, scale);

			const std::string expectedString = std::format("Position: {}, Rotation: {}, Scale: {}", position.ToString(), rotation.ToString(), scale.ToString());
			Assert::AreEqual(expectedString, transform.ToString());

			std::ostringstream ss;
			ss << transform;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(AssignmentTest)
		{
			constexpr auto position = PonyMath::Core::Vector3<float>(3.f, -2.f, 1.5f);
			const auto rotation = PonyMath::Core::Quaternion<float>(1.f, 2.f, -3.f, 4.f).Normalized();
			constexpr auto scale = PonyMath::Core::Vector3<float>(0.5f, 1.2f, 2.f);
			auto transform = PonyMath::Space::Transform3D(position, rotation, scale);

			auto copiedTransform = PonyMath::Space::Transform3D();
			copiedTransform = transform;
			Assert::IsTrue(position == copiedTransform.Position());
			Assert::IsTrue(rotation == copiedTransform.Rotation());
			Assert::IsTrue(scale == copiedTransform.Scale());

			auto movedTransform = PonyMath::Space::Transform3D();
			movedTransform = std::move(transform);
			Assert::IsTrue(position == movedTransform.Position());
			Assert::IsTrue(rotation == movedTransform.Rotation());
			Assert::IsTrue(scale == movedTransform.Scale());
		}

		TEST_METHOD(EqualsTest)
		{
			constexpr auto position = PonyMath::Core::Vector3<float>(3.f, -2.f, 1.5f);
			const auto rotation = PonyMath::Core::Quaternion<float>(1.f, 2.f, -3.f, 4.f).Normalized();
			constexpr auto scale = PonyMath::Core::Vector3<float>(0.5f, 1.2f, 2.f);
			const auto transform = PonyMath::Space::Transform3D(position, rotation, scale);

			auto otherTransform = transform;
			Assert::IsTrue(transform == otherTransform);
			Assert::IsFalse(transform != otherTransform);

			otherTransform.Translate(PonyMath::Core::Vector3<float>(1.f, -1.f, 2.f));
			Assert::IsFalse(transform == otherTransform);
			Assert::IsTrue(transform != otherTransform);

			otherTransform.Position(position);
			otherTransform.Rotate(PonyMath::Core::Quaternion<float>(1.5f, 0.2f, -1.1f, 2.f).Normalized());
			Assert::IsFalse(transform == otherTransform);
			Assert::IsTrue(transform != otherTransform);

			otherTransform.Rotation(rotation);
			otherTransform.Scale(PonyMath::Core::Vector3<float>::Predefined::One);
			Assert::IsFalse(transform == otherTransform);
			Assert::IsTrue(transform != otherTransform);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr auto position = PonyMath::Core::Vector3<float>(3.f, -2.f, 1.5f);
			const auto rotation = PonyMath::Core::Quaternion<float>(1.f, 2.f, -3.f, 4.f).Normalized();
			constexpr auto scale = PonyMath::Core::Vector3<float>(0.5f, 1.2f, 2.f);
			const auto transform = PonyMath::Space::Transform3D(position, rotation, scale);

			auto otherTransform = transform;
			Assert::IsTrue(PonyMath::Space::AreAlmostEqual(transform, otherTransform));

			otherTransform.Position(PonyMath::Core::Vector3<float>(std::nextafter(position.X(), 0.f), std::nextafter(position.Y(), 0.f), std::nextafter(position.Z(), 0.f)));
			Assert::IsTrue(PonyMath::Space::AreAlmostEqual(transform, otherTransform));

			otherTransform.Position(position);
			otherTransform.Rotation(PonyMath::Core::Quaternion<float>(std::nextafter(rotation.X(), 0.f), std::nextafter(rotation.Y(), 0.f), std::nextafter(rotation.Z(), 0.f), std::nextafter(rotation.W(), 0.f)));
			Assert::IsTrue(PonyMath::Space::AreAlmostEqual(transform, otherTransform));

			otherTransform.Rotation(rotation);
			otherTransform.Scale(PonyMath::Core::Vector3<float>(std::nextafter(scale.X(), 0.f), std::nextafter(scale.Y(), 0.f), std::nextafter(scale.Z(), 0.f)));

			Assert::IsFalse(PonyMath::Space::AreAlmostEqual(transform, PonyMath::Space::Transform3D()));
			Assert::IsTrue(PonyMath::Space::AreAlmostEqual(transform, PonyMath::Space::Transform3D(), 1000.f));
		}
	};
}
