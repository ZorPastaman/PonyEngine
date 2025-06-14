/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyMath.Core;
import PonyMath.Shape;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Shape
{
	TEST_CLASS(Inside3DTests)
	{
		TEST_METHOD(SphereSphereTest)
		{
			constexpr auto large = PonyMath::Shape::Sphere<float>(-5.f, -6.f, 7.f, 20.f);
			auto small = PonyMath::Shape::Sphere<float>(large.Center(), 4.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.Center() += PonyMath::Core::Vector3<float>(-6.f, 7.f, 1.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.Radius() = 30.f;
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector3<float>(15.f, 14.f, 27.f);
			small.Radius() = 3.f;
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector3<float>(10.f, 0.f, 100.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(SphereAabbTest)
		{
			constexpr auto large = PonyMath::Shape::AABB<float>(10.f, 10.f, 15.f, 20.f, 20.f, 10.f);
			auto small = PonyMath::Shape::Sphere<float>(large.Center(), 4.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector3<float>(12.f, 8.f, 17.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.Radius() = 40.f;
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector3<float>(-10.f, -10.f, 25.f);
			small.Radius() = 3.f;
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector3<float>(-100.f, -100.f, 250.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(SphereObbTest)
		{
			constexpr auto largeBox = PonyMath::Shape::AABB<float>(1.f, -1.f, 0.5f, 20.f, 20.f, 10.f);
			const auto large = PonyMath::Shape::OBB<float>(largeBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.f, 0.4f, -0.1f)));
			auto small = PonyMath::Shape::Sphere<float>(large.Center(), 4.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.Center() += PonyMath::Core::Vector3<float>(2.f, 3.f, -2.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.Radius() = 40.f;
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector3<float>(-10.f, -10.f, 25.f);
			small.Radius() = 3.f;
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector3<float>(-100.f, -100.f, 250.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(AabbAabbTest)
		{
			constexpr auto large = PonyMath::Shape::AABB<float>(10.f, 10.f, 15.f, 20.f, 20.f, 10.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(large, large));

			auto small = PonyMath::Shape::AABB<float>(12.f, 8.f, 11.f, 10.f, 10.f, 2.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABB<float>(12.f, 8.f, 11.f, 20.f, 25.f, 12.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABB<float>(50.f, 80.f, -11.f, 10.f, 10.f, 2.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(AabbSphereTest)
		{
			constexpr auto large = PonyMath::Shape::Sphere<float>(-5.f, -6.f, 7.f, 20.f);
			auto small = PonyMath::Shape::AABB<float>(-5.f, -6.f, 7.f, 3.f, 4.f, 2.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(large, large));

			small.Center() += PonyMath::Core::Vector3<float>(-2.f, 2.f, 2.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(large, large));

			small.ExtentZ() = 40.f;
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.ExtentZ() = 1.f;
			small.Center() = large.Center() + PonyMath::Core::Vector3<float>::Predefined::One.Normalized() * large.Radius();
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector3<float>(-3.f, 20.f, 50.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(AabbObbTest)
		{
			constexpr auto largeBox = PonyMath::Shape::AABB<float>(1.f, -1.f, 0.5f, 20.f, 20.f, 10.f);
			const auto large = PonyMath::Shape::OBB<float>(largeBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.f, 0.4f, -0.1f)));

			auto small = PonyMath::Shape::AABB<float>(1.2f, -1.5f, 0.8f, 3.f, 2.f, 3.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABB<float>(1.f, -1.f, 0.5f, 20.f, 20.f, 10.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABB<float>(10.f, -19.f, 9.5f, 3.f, 2.f, 3.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(ObbObbTest)
		{
			constexpr auto largeBox = PonyMath::Shape::AABB<float>(1.f, -1.f, 0.5f, 20.f, 20.f, 10.f);
			const auto large = PonyMath::Shape::OBB<float>(largeBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.f, 0.4f, -0.1f)));

			auto smallBox = PonyMath::Shape::AABB<float>(1.2f, -1.5f, 0.8f, 3.f, 2.f, 3.f);
			auto small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.7f, 0.6f, -0.3f)));
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABB<float>(1.f, -1.f, 0.5f, 20.f, 20.f, 10.f);
			small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.7f, 0.6f, -0.3f)));
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABB<float>(10.f, -19.f, 9.5f, 3.f, 2.f, 3.f);
			small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.7f, 0.6f, -0.3f)));
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABB<float>(1.2f, -1.5f, 0.8f, 3.f, 2.f, 3.f);
			small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.7f, 0.6f, -0.3f)));
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABB<float>(1.2f, -1.5f, 0.8f, 13.f, 15.f, 2.f);
			small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.7f, 0.6f, -0.3f)));
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABB<float>(1.2f, -1.5f, 0.8f, 13.f, 15.f, 2.f);
			small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.7f, 1.6f, -0.9f)));
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(ObbSphereTest)
		{
			constexpr auto large = PonyMath::Shape::Sphere<float>(-5.f, -6.f, 7.f, 20.f);
			auto smallBox = PonyMath::Shape::AABB<float>(1.2f, -1.5f, 0.8f, 3.f, 2.f, 3.f);
			auto small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.7f, 0.6f, -0.3f)));
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(3.f, 3.f, -3.f)));
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox.Center() = PonyMath::Core::Vector3<float>(40.f, 20.f, 40.f);
			small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.7f, 0.6f, -0.3f)));
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABB<float>(1.2f, -1.5f, 0.8f, 30.f, 22.f, 31.f);
			small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.7f, 0.6f, -0.3f)));
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(ObbAabbTest)
		{
			constexpr auto large = PonyMath::Shape::AABB<float>(1.f, 0.f, 1.f, 20.f, 20.f, 10.f);

			auto smallBox = PonyMath::Shape::AABB<float>(1.2f, -1.5f, 0.8f, 3.f, 2.f, 3.f);
			auto small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.7f, 0.6f, -0.3f)));
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABB<float>(1.f, -1.f, 0.5f, 20.f, 20.f, 10.f);
			small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.7f, 0.6f, -0.3f)));
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABB<float>(10.f, -19.f, 9.5f, 3.f, 2.f, 3.f);
			small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.7f, 0.6f, -0.3f)));
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABB<float>(1.2f, -1.5f, 0.8f, 3.f, 2.f, 3.f);
			small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.7f, 0.6f, -0.3f)));
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABB<float>(1.2f, -1.5f, 0.8f, 13.f, 15.f, 2.f);
			small = PonyMath::Shape::OBB<float>(smallBox, PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(1.7f, 1.6f, -0.9f)));
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}
	};
}
