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
		TEST_METHOD(AabbAabbTest)
		{
			const auto large = PonyMath::Shape::AABB<float>(10.f, 10.f, 15.f, 20.f, 20.f, 10.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(large, large));

			auto small = PonyMath::Shape::AABB<float>(12.f, 8.f, 11.f, 10.f, 10.f, 2.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABB<float>(12.f, 8.f, 11.f, 20.f, 25.f, 12.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABB<float>(50.f, 80.f, -11.f, 10.f, 10.f, 2.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(AabbObbTest)
		{
			const auto largeBox = PonyMath::Shape::AABB<float>(1.f, -1.f, 0.5f, 20.f, 20.f, 10.f);
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
			const auto largeBox = PonyMath::Shape::AABB<float>(1.f, -1.f, 0.5f, 20.f, 20.f, 10.f);
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

		TEST_METHOD(ObbAabbTest)
		{
			const auto large = PonyMath::Shape::AABB<float>(1.f, 0.f, 1.f, 20.f, 20.f, 10.f);

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
