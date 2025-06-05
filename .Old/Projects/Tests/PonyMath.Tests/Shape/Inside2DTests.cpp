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
		TEST_METHOD(CircleCircleTest)
		{
			constexpr auto large = PonyMath::Shape::Circle<float>(4.f, 8.f, 4.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(large, large));

			auto small = PonyMath::Shape::Circle<float>(3.f, 9.f, 2.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.Center() = large.Center();
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::Circle<float>(8.f, 13.f, 4.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::Circle<float>(80.f, 13.f, 4.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(CircleAabrTest)
		{
			constexpr auto large = PonyMath::Shape::AABR<float>(10.f, 10.f, 20.f, 20.f);
			auto small = PonyMath::Shape::Circle<float>(10.f, 10.f, 6.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector2<float>(5.f, 6.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.Radius() = 30.f;
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector2<float>(29.f, 20.f);
			small.Radius() = 3.f;
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector2<float>(40.f, 40.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(CircleObrTest)
		{
			constexpr auto largeBox = PonyMath::Shape::AABR<float>(10.f, 10.f, 20.f, 20.f);
			const auto large = PonyMath::Shape::OBR<float>(largeBox, 30.f * PonyMath::Core::DegToRad<float>);
			auto small = PonyMath::Shape::Circle<float>(large.Center(), 6.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.Center() += PonyMath::Core::Vector2<float>(2.f, -2.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.Radius() = 40.f;
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Lerp(large.Center(), large.LeftTop(), 0.95f);
			small.Radius() = 5.f;
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector2<float>(5.f, -50.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(AabrAabrTest)
		{
			constexpr auto large = PonyMath::Shape::AABR<float>(10.f, 10.f, 20.f, 20.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(large, large));

			auto small = PonyMath::Shape::AABR<float>(12.f, 8.f, 10.f, 10.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABR<float>(5.f,5.f, 30.f, 30.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABR<float>(-50.f, 50.f, 5.f, 5.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(AabrCircleTest)
		{
			constexpr auto large = PonyMath::Shape::Circle<float>(4.f, 8.f, 16.f);
			auto small = PonyMath::Shape::AABR<float>(4.f, 8.f, 3.f, 4.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.Center() += PonyMath::Core::Vector2<float>(-2.f, 3.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small.ExtentY() = 100.f;
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.ExtentY() = 2.f;
			small.Center() = PonyMath::Core::Vector2<float>(20.f, -8.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small.Center() = PonyMath::Core::Vector2<float>(100.f, 100.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(AabrObrTest)
		{
			constexpr auto largeBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 20.f, 20.f);
			const auto large = PonyMath::Shape::OBR<float>(largeBox, 30.f * PonyMath::Core::DegToRad<float>);

			auto small = PonyMath::Shape::AABR<float>(1.f, -1.f, 3.f, 4.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABR<float>(1.f, -1.f, 30.f, 40.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::AABR<float>(-50.f, 50.f, 5.f, 5.f);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(ObrObrTest)
		{
			constexpr auto largeBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 20.f, 20.f);
			const auto large = PonyMath::Shape::OBR<float>(largeBox, 30.f * PonyMath::Core::DegToRad<float>);

			auto smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 3.f, 4.f);
			auto small = PonyMath::Shape::OBR<float>(smallBox, 30.f * PonyMath::Core::DegToRad<float>);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 30.f, 40.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 30.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(-50.f, 50.f, 5.f, 5.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 30.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 3.f, 4.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 45.f * PonyMath::Core::DegToRad<float>);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 17.f, 17.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 30.f * PonyMath::Core::DegToRad<float>);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 17.f, 17.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 60.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(ObrCircleTest)
		{
			constexpr auto large = PonyMath::Shape::Circle<float>(4.f, 8.f, 16.f);
			auto smallBox = PonyMath::Shape::AABR<float>(6.f, 0.f, 2.f, 2.f);
			auto small = PonyMath::Shape::OBR<float>(smallBox, 30.f * PonyMath::Core::DegToRad<float>);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox.ExtentX() = 40.f;
			small = PonyMath::Shape::OBR<float>(smallBox, 30.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox.ExtentX() = 2.f;
			small = PonyMath::Shape::OBR<float>(smallBox, -165.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox.Center() = PonyMath::Core::Vector2<float>(-20.f, -50.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 30.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(ObrAabrTest)
		{
			constexpr auto large = PonyMath::Shape::AABR<float>(10.f, 10.f, 20.f, 20.f);

			auto smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 3.f, 4.f);
			auto small = PonyMath::Shape::OBR<float>(smallBox, 30.f * PonyMath::Core::DegToRad<float>);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(1.f, -1.f, 30.f, 40.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 30.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(-50.f, 50.f, 5.f, 5.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 30.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(10.f, 10.f, 17.f, 17.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 0.f);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			smallBox = PonyMath::Shape::AABR<float>(10.f, -10.f, 17.f, 17.f);
			small = PonyMath::Shape::OBR<float>(smallBox, 45.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}
	};
}
