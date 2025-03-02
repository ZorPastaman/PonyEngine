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
#include <format>
#include <utility>

import PonyMath.Core;
import PonyMath.Shape;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Shape
{
	TEST_CLASS(AABRTests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<std::int16_t, PonyMath::Shape::AABR<std::int16_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Shape::AABR<float>::ValueType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Right == PonyMath::Shape::AABR<float>::Axes[0]);
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Up == PonyMath::Shape::AABR<float>::Axes[1]);

			Assert::AreEqual(std::size_t{0}, PonyMath::Shape::AABR<float>::LeftBottomIndex);
			Assert::AreEqual(std::size_t{1}, PonyMath::Shape::AABR<float>::RightBottomIndex);
			Assert::AreEqual(std::size_t{2}, PonyMath::Shape::AABR<float>::LeftTopIndex);
			Assert::AreEqual(std::size_t{3}, PonyMath::Shape::AABR<float>::RightTopIndex);
			Assert::AreEqual(std::size_t{4}, PonyMath::Shape::AABR<float>::CornerCount);

			Assert::IsTrue(PonyMath::Shape::AABR<float>(0.f, 0.f, 0.f, 0.f) == PonyMath::Shape::AABR<float>::Predefined::Zero);
		}

		TEST_METHOD(ConstructorDefaultShortTest)
		{
			const auto aabr = PonyMath::Shape::AABR<std::int16_t>();
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>::Predefined::Zero == aabr.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>::Predefined::Zero == aabr.Extents());
		}

		TEST_METHOD(ConstructorDefaultFloatTest)
		{
			const auto aabr = PonyMath::Shape::AABR<float>();
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Zero == aabr.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Zero == aabr.Extents());
		}

		TEST_METHOD(ConstructorDataShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = -12;
			const auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(x, y) == aabr.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(halfWidth, -halfHeight) == aabr.Extents());
		}

		TEST_METHOD(ConstructorDataFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = -12;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			Assert::IsTrue(PonyMath::Core::Vector2<float>(x, y) == aabr.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(halfWidth, -halfHeight) == aabr.Extents());
		}

		TEST_METHOD(ConstructorVectorShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = -12;
			constexpr auto center = PonyMath::Core::Vector2<std::int16_t>(x, y);
			constexpr auto extents = PonyMath::Core::Vector2<std::int16_t>(halfWidth, halfHeight);
			const auto aabr = PonyMath::Shape::AABR<std::int16_t>(center, extents);
			Assert::IsTrue(center == aabr.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(halfWidth, -halfHeight) == aabr.Extents());
		}

		TEST_METHOD(ConstructorVectorFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = -12;
			constexpr auto center = PonyMath::Core::Vector2<float>(x, y);
			constexpr auto extents = PonyMath::Core::Vector2<float>(halfWidth, halfHeight);
			const auto aabr = PonyMath::Shape::AABR<float>(center, extents);
			Assert::IsTrue(center == aabr.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(halfWidth, -halfHeight) == aabr.Extents());
		}

		TEST_METHOD(ConstructorRectShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t width = 24;
			constexpr std::int16_t height = -12;
			constexpr auto rect = PonyMath::Shape::Rect(x, y, width, height);
			const auto aabr = PonyMath::Shape::AABR<std::int16_t>(rect);
			Assert::IsTrue(rect.Center() == aabr.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(width / 2u, -height / 2u) == aabr.Extents());
		}

		TEST_METHOD(ConstructorRectFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float width = 24;
			constexpr float height = -12;
			constexpr auto rect = PonyMath::Shape::Rect(x, y, width, height);
			const auto aabr = PonyMath::Shape::AABR<float>(rect);
			Assert::IsTrue(rect.Center() == aabr.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(width / 2.f, -height / 2.f) == aabr.Extents());
		}

		TEST_METHOD(ConstructorCopyShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = -12;
			const auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			const auto copy = aabr;
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(x, y) == copy.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(halfWidth, -halfHeight) == copy.Extents());
		}

		TEST_METHOD(ConstructorCopyFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = -12;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			const auto copy = aabr;
			Assert::IsTrue(PonyMath::Core::Vector2<float>(x, y) == copy.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(halfWidth, -halfHeight) == copy.Extents());
		}

		TEST_METHOD(ConstructorMoveShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = -12;
			auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			const auto copy = std::move(aabr);
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(x, y) == copy.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(halfWidth, -halfHeight) == copy.Extents());
		}

		TEST_METHOD(ConstructorMoveFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = -12;
			auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			const auto copy = std::move(aabr);
			Assert::IsTrue(PonyMath::Core::Vector2<float>(x, y) == copy.Center());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(halfWidth, -halfHeight) == copy.Extents());
		}

		TEST_METHOD(CenterShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = -12;
			auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(x, y) == aabr.Center());
		}

		TEST_METHOD(CenterFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = -12;
			auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			Assert::IsTrue(PonyMath::Core::Vector2<float>(x, y) == aabr.Center());
		}

		TEST_METHOD(ExtentShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = -12;
			auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			Assert::AreEqual(halfWidth, aabr.ExtentX());
			Assert::AreEqual(std::int16_t{-halfHeight}, aabr.ExtentY());
			Assert::AreEqual(halfWidth, aabr.Extent(0));
			Assert::AreEqual(std::int16_t{-halfHeight}, aabr.Extent(1));

			aabr.ExtentX(-3);
			aabr.ExtentY(6);
			Assert::AreEqual(std::int16_t{3}, aabr.ExtentX());
			Assert::AreEqual(std::int16_t{6}, aabr.ExtentY());

			aabr.Extent(0, -6);
			Assert::AreEqual(std::int16_t{6}, aabr.Extent(0));
		}

		TEST_METHOD(ExtentFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = -12;
			auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			Assert::AreEqual(halfWidth, aabr.ExtentX());
			Assert::AreEqual(-halfHeight, aabr.ExtentY());
			Assert::AreEqual(halfWidth, aabr.Extent(0));
			Assert::AreEqual(-halfHeight, aabr.Extent(1));

			aabr.ExtentX(-3);
			aabr.ExtentY(6);
			Assert::AreEqual(3.f, aabr.ExtentX());
			Assert::AreEqual(6.f, aabr.ExtentY());

			aabr.Extent(0, -6);
			Assert::AreEqual(6.f, aabr.Extent(0));
		}

		TEST_METHOD(ExtentsShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = -12;
			auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(halfWidth, -halfHeight) == aabr.Extents());

			constexpr auto extents = PonyMath::Core::Vector2<std::int16_t>(-5, -8);
			aabr.Extents(extents);
			Assert::IsTrue(PonyMath::Core::Abs(extents) == aabr.Extents());
		}

		TEST_METHOD(ExtentsFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = -12;
			auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			Assert::IsTrue(PonyMath::Core::Vector2<float>(halfWidth, -halfHeight) == aabr.Extents());

			constexpr auto extents = PonyMath::Core::Vector2<float>(-5, -8);
			aabr.Extents(extents);
			Assert::IsTrue(PonyMath::Core::Abs(extents) == aabr.Extents());
		}

		TEST_METHOD(SizeShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t halfWidth = -4;
			constexpr std::int16_t halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			Assert::AreEqual(std::int16_t{8}, aabr.Width());
			Assert::AreEqual(std::int16_t{28}, aabr.Height());
			Assert::AreEqual(std::int16_t{8}, aabr.Size(0));
			Assert::AreEqual(std::int16_t{28}, aabr.Size(1));
		}

		TEST_METHOD(SizeFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			Assert::AreEqual(8.f, aabr.Width());
			Assert::AreEqual(28.f, aabr.Height());
			Assert::AreEqual(8.f, aabr.Size(0));
			Assert::AreEqual(28.f, aabr.Size(1));
		}

		TEST_METHOD(MinShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t halfWidth = -4;
			constexpr std::int16_t halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			Assert::AreEqual(std::int16_t{3}, aabr.MinX());
			Assert::AreEqual(std::int16_t{-22}, aabr.MinY());
			Assert::AreEqual(std::int16_t{3}, aabr.Min(0));
			Assert::AreEqual(std::int16_t{-22}, aabr.Min(1));
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(3, -22) == aabr.Min());
		}

		TEST_METHOD(MinFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			Assert::AreEqual(3.f, aabr.MinX());
			Assert::AreEqual(-22.f, aabr.MinY());
			Assert::AreEqual(3.f, aabr.Min(0));
			Assert::AreEqual(-22.f, aabr.Min(1));
			Assert::IsTrue(PonyMath::Core::Vector2<float>(3.f, -22.f) == aabr.Min());
		}

		TEST_METHOD(MaxShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t halfWidth = -4;
			constexpr std::int16_t halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			Assert::AreEqual(std::int16_t{11}, aabr.MaxX());
			Assert::AreEqual(std::int16_t{6}, aabr.MaxY());
			Assert::AreEqual(std::int16_t{11}, aabr.Max(0));
			Assert::AreEqual(std::int16_t{6}, aabr.Max(1));
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(11, 6) == aabr.Max());
		}

		TEST_METHOD(MaxFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			Assert::AreEqual(11.f, aabr.MaxX());
			Assert::AreEqual(6.f, aabr.MaxY());
			Assert::AreEqual(11.f, aabr.Max(0));
			Assert::AreEqual(6.f, aabr.Max(1));
			Assert::IsTrue(PonyMath::Core::Vector2<float>(11.f, 6.f) == aabr.Max());
		}

		TEST_METHOD(CornerShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t halfWidth = -4;
			constexpr std::int16_t halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(3, -22) == aabr.LeftBottom());
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(11, -22) == aabr.RightBottom());
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(3, 6) == aabr.LeftTop());
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(11, 6) == aabr.RightTop());
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(3, -22) == aabr.Corner(0));
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(11, -22) == aabr.Corner(1));
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(3, 6) == aabr.Corner(2));
			Assert::IsTrue(PonyMath::Core::Vector2<std::int16_t>(11, 6) == aabr.Corner(3));

			const auto corners = aabr.Corners();
			for (std::size_t i = 0; i < 4; ++i)
			{
				Assert::IsTrue(aabr.Corner(i) == corners[i]);
			}
		}

		TEST_METHOD(CornerFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			Assert::IsTrue(PonyMath::Core::Vector2<float>(3, -22) == aabr.LeftBottom());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(11, -22) == aabr.RightBottom());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(3, 6) == aabr.LeftTop());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(11, 6) == aabr.RightTop());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(3, -22) == aabr.Corner(0));
			Assert::IsTrue(PonyMath::Core::Vector2<float>(11, -22) == aabr.Corner(1));
			Assert::IsTrue(PonyMath::Core::Vector2<float>(3, 6) == aabr.Corner(2));
			Assert::IsTrue(PonyMath::Core::Vector2<float>(11, 6) == aabr.Corner(3));

			const auto corners = aabr.Corners();
			for (std::size_t i = 0; i < 4; ++i)
			{
				Assert::IsTrue(aabr.Corner(i) == corners[i]);
			}
		}

		TEST_METHOD(PerimeterShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t halfWidth = -4;
			constexpr std::int16_t halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			Assert::AreEqual(std::int16_t{72}, aabr.Perimeter());
		}

		TEST_METHOD(PerimeterFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			Assert::AreEqual(72.f, aabr.Perimeter());
		}

		TEST_METHOD(AreaShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t halfWidth = -4;
			constexpr std::int16_t halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			Assert::AreEqual(std::int16_t{224}, aabr.Area());
		}

		TEST_METHOD(AreaFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			Assert::AreEqual(224.f, aabr.Area());
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			Assert::IsTrue(aabr.IsFinite());

			for (std::size_t i = 0; i < 2; ++i)
			{
				const float was = aabr.Center()[i];
				aabr.Center()[i] = std::numeric_limits<float>::quiet_NaN();
				Assert::IsFalse(aabr.IsFinite());
				aabr.Center()[i] = was;
			}

			for (std::size_t i = 0; i < 2; ++i)
			{
				const float was = aabr.Extent(i);
				aabr.Extent(i, std::numeric_limits<float>::quiet_NaN());
				Assert::IsFalse(aabr.IsFinite());
				aabr.Extent(i, was);
			}
		}

		TEST_METHOD(ContainsShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t halfWidth = -4;
			constexpr std::int16_t halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<std::int16_t>(x, y, halfWidth, halfHeight);
			Assert::IsTrue(aabr.Contains(aabr.Center()));
			Assert::IsTrue(aabr.Contains(aabr.Min()));
			Assert::IsTrue(aabr.Contains(aabr.Max()));
			Assert::IsTrue(aabr.Contains(aabr.Center() + PonyMath::Core::Vector2<std::int16_t>(halfWidth, halfHeight) / 2));

			Assert::IsFalse(aabr.Contains(PonyMath::Core::Vector2<std::int16_t>(100, y)));
			Assert::IsFalse(aabr.Contains(PonyMath::Core::Vector2<std::int16_t>(x, -100)));
			Assert::IsFalse(aabr.Contains(aabr.Max() + PonyMath::Core::Vector2<std::int16_t>::Predefined::One));
		}

		TEST_METHOD(ContainsFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			Assert::IsTrue(aabr.Contains(aabr.Center()));
			Assert::IsTrue(aabr.Contains(aabr.Min()));
			Assert::IsTrue(aabr.Contains(aabr.Max()));
			Assert::IsTrue(aabr.Contains(aabr.Center() + PonyMath::Core::Vector2<float>(halfWidth, halfHeight) / 2.f));

			Assert::IsFalse(aabr.Contains(PonyMath::Core::Vector2<float>(100.f, y)));
			Assert::IsFalse(aabr.Contains(PonyMath::Core::Vector2<float>(x, -100)));
			Assert::IsFalse(aabr.Contains(aabr.Max() + PonyMath::Core::Vector2<float>::Predefined::One));
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			const std::string expected = std::format("Center: {}, Extents: {}", aabr.Center().ToString(), aabr.Extents().ToString());
			Assert::AreEqual(expected, aabr.ToString());

			std::ostringstream ss;
			ss << aabr;
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(ConvertTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			const auto aabrInt = static_cast<PonyMath::Shape::AABR<std::int16_t>>(aabr);
			Assert::AreEqual(static_cast<std::int16_t>(x), aabrInt.Center().X());
			Assert::AreEqual(static_cast<std::int16_t>(y), aabrInt.Center().Y());
			Assert::AreEqual(static_cast<std::int16_t>(-halfWidth), aabrInt.ExtentX());
			Assert::AreEqual(static_cast<std::int16_t>(halfHeight), aabrInt.ExtentY());
		}

		TEST_METHOD(ConvertToRectTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			const auto rect = static_cast<PonyMath::Shape::Rect<float>>(aabr);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(aabr.Min(), rect.Position()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector2<float>(-halfWidth, halfHeight) * 2.f, rect.Size()));
		}

		TEST_METHOD(EqualityTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			auto another = aabr;
			Assert::IsTrue(aabr == another);

			for (std::size_t i = 0; i < 2; ++i)
			{
				const float was = another.Center()[i];
				another.Center()[i] = std::nextafter(was, 0.f);
				Assert::IsFalse(aabr == another);
				another.Center()[i] += 1.f;
				Assert::IsFalse(aabr == another);
				another.Center()[i] = was;
			}

			for (std::size_t i = 0; i < 2; ++i)
			{
				const float was = another.Extent(i);
				another.Extent(i, std::nextafter(was, 0.f));
				Assert::IsFalse(aabr == another);
				another.Extent(i, was + 1.f);
				Assert::IsFalse(aabr == another);
				another.Extent(i, was);
			}
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			const auto aabr = PonyMath::Shape::AABR<float>(x, y, halfWidth, halfHeight);
			auto another = aabr;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(aabr, another));

			for (std::size_t i = 0; i < 2; ++i)
			{
				const float was = another.Center()[i];
				another.Center()[i] = std::nextafter(was, 0.f);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(aabr, another));
				another.Center()[i] += 1.f;
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(aabr, another));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(aabr, another, 5.f));
				another.Center()[i] = was;
			}

			for (std::size_t i = 0; i < 2; ++i)
			{
				const float was = another.Extent(i);
				another.Extent(i, std::nextafter(was, 0.f));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(aabr, another));
				another.Extent(i, was + 1.f);
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(aabr, another));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(aabr, another, 5.f));
				another.Extent(i, was);
			}
		}

		static constexpr PonyMath::Shape::AABR<float> AABRConstexpr()
		{
			auto defaultAABR = PonyMath::Shape::AABR<float>();
			auto movedAABR = std::move(defaultAABR);

			movedAABR.Center() = PonyMath::Core::Vector2<float>(2.f, 5.f);

			auto copied = PonyMath::Shape::AABR<float>();
			copied = defaultAABR;

			auto moved = PonyMath::Shape::AABR<float>();
			moved = std::move(movedAABR);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultAABR = PonyMath::Shape::AABR<float>();
			[[maybe_unused]] constexpr auto copied = defaultAABR;
			[[maybe_unused]] constexpr auto moved = AABRConstexpr();

			[[maybe_unused]] constexpr auto center = moved.Center();

			[[maybe_unused]] constexpr auto extentX = moved.ExtentX();
			[[maybe_unused]] constexpr auto extentY = moved.ExtentY();
			[[maybe_unused]] constexpr auto extent = moved.Extent(1);
			[[maybe_unused]] constexpr auto extents = moved.Extents();

			[[maybe_unused]] constexpr auto width = moved.Width();
			[[maybe_unused]] constexpr auto height = moved.Height();
			[[maybe_unused]] constexpr auto size = moved.Size(0);

			[[maybe_unused]] constexpr auto minX = moved.MinX();
			[[maybe_unused]] constexpr auto minY = moved.MinY();
			[[maybe_unused]] constexpr auto minI = moved.Min(0);
			[[maybe_unused]] constexpr auto min = moved.Min();
			[[maybe_unused]] constexpr auto maxX = moved.MaxX();
			[[maybe_unused]] constexpr auto maxY = moved.MaxY();
			[[maybe_unused]] constexpr auto maxI = moved.Max(1);
			[[maybe_unused]] constexpr auto max = moved.Max();

			[[maybe_unused]] constexpr auto leftBottom = moved.LeftBottom();
			[[maybe_unused]] constexpr auto rightBottom = moved.RightBottom();
			[[maybe_unused]] constexpr auto leftTop = moved.LeftTop();
			[[maybe_unused]] constexpr auto rightTop = moved.RightTop();
			[[maybe_unused]] constexpr auto corner = moved.Corner(2);
			[[maybe_unused]] constexpr auto corners = moved.Corners();

			[[maybe_unused]] constexpr auto perimeter = moved.Perimeter();
			[[maybe_unused]] constexpr auto area = moved.Area();

			[[maybe_unused]] constexpr auto rect = static_cast<PonyMath::Shape::Rect<float>>(moved);

			[[maybe_unused]] constexpr bool equal = moved == defaultAABR;
			[[maybe_unused]] constexpr bool notEqual = moved != defaultAABR;

			[[maybe_unused]] constexpr bool areAlmostEqual = PonyMath::Shape::AreAlmostEqual(moved, defaultAABR);
		}
	};
}
