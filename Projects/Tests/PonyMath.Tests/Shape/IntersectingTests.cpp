/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstdint>

import PonyMath.Shape;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Shape
{
	TEST_CLASS(IntersectingTests)
	{
		TEST_METHOD(AreIntersectingRectRectTest)
		{
			auto left = PonyMath::Shape::Rect<std::int32_t>(2, 3, 2, 1);
			auto right = PonyMath::Shape::Rect<std::int32_t>(1, 2, 5, 6);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(left, right));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(right, left));

			left = PonyMath::Shape::Rect<std::int32_t>(2, 3, 5, 6);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(left, right));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(right, left));

			right = PonyMath::Shape::Rect<std::int32_t>(-10, -20, 5, 6);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(left, right));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(right, left));

			left = PonyMath::Shape::Rect<std::int32_t>(-10, 0, 15, 16);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(left, right));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(right, left));
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr bool rectRect = PonyMath::Shape::AreIntersecting(PonyMath::Shape::Rect<std::int32_t>(1, 2, 5, 6), PonyMath::Shape::Rect<std::int32_t>(2, 3, 2, 1));
		}
	};
}
