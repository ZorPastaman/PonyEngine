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
	TEST_CLASS(InsideTests)
	{
		TEST_METHOD(IsInsideRectRectTest)
		{
			auto large = PonyMath::Shape::Rect<std::int32_t>(1, 2, 5, 6);
			auto small = PonyMath::Shape::Rect<std::int32_t>(2, 3, 2, 1);
			Assert::IsTrue(PonyMath::Shape::IsInside(small, large));

			small = PonyMath::Shape::Rect<std::int32_t>(2, 3, 5, 6);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));

			large = PonyMath::Shape::Rect<std::int32_t>(-10, -20, 5, 6);
			Assert::IsFalse(PonyMath::Shape::IsInside(small, large));
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr bool rectRect = PonyMath::Shape::IsInside(PonyMath::Shape::Rect<std::int32_t>(1, 2, 5, 6), PonyMath::Shape::Rect<std::int32_t>(2, 3, 2, 1));
		}
	};
}
