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
	TEST_CLASS(Inside2DTests)
	{
		TEST_METHOD(AabrAabrTest)
		{
			const auto large = PonyMath::Shape::AABR<float>(10.f, 10.f, 20.f, 20.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(large, large));

			auto small = PonyMath::Shape::AABR<float>(12.f, 8.f, 10.f, 10.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABR<float>(5.f,5.f, 30.f, 30.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABR<float>(-50.f, 50.f, 5.f, 5.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(AabrObrTest)
		{
			const auto largeBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 20.f, 20.f);
			const auto large = PonyMath::Shape::OBR<float>(largeBox, 30.f);

			auto small = PonyMath::Shape::AABR<float>(1.f, -1.f, 3.f, 4.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABR<float>(1.f, -1.f, 30.f, 40.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABR<float>(-50.f, 50.f, 5.f, 5.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(ObrObrTest)
		{
			const auto largeBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 20.f, 20.f);
			const auto large = PonyMath::Shape::OBR<float>(largeBox, 30.f);

			auto smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 3.f, 4.f);
			auto small = PonyMath::Shape::OBR<float>(smallBox, 30.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 30.f, 40.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 30.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(-50.f, 50.f, 5.f, 5.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 30.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 3.f, 4.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 45.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 17.f, 17.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 30.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 17.f, 17.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 60.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(ObrAabrTest)
		{
			const auto large = PonyMath::Shape::AABR<float>(10.f, 10.f, 20.f, 20.f);

			auto smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 3.f, 4.f);
			auto small = PonyMath::Shape::OBR<float>(smallBox, 30.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 30.f, 40.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 30.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(-50.f, 50.f, 5.f, 5.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 30.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(10.f, 10.f, 17.f, 17.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 0.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(10.f, -10.f, 17.f, 17.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 45.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}
	};
}
