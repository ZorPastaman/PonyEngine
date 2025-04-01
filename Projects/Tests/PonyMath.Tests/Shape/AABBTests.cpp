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
#include <cstddef>
#include <cstdint>
#include <format>
#include <limits>
#include <ostream>
#include <type_traits>
#include <utility>

import PonyMath.Core;
import PonyMath.Shape;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Shape
{
	TEST_CLASS(AABBTests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<std::int16_t, PonyMath::Shape::AABB<std::int16_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Shape::AABB<float>::ValueType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Right == PonyMath::Shape::AABB<float>::Axes[0]);
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Up == PonyMath::Shape::AABB<float>::Axes[1]);
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Forward == PonyMath::Shape::AABB<float>::Axes[2]);

			Assert::AreEqual(std::size_t{0}, PonyMath::Shape::AABB<float>::LeftBottomNearIndex);
			Assert::AreEqual(std::size_t{1}, PonyMath::Shape::AABB<float>::RightBottomNearIndex);
			Assert::AreEqual(std::size_t{2}, PonyMath::Shape::AABB<float>::LeftTopNearIndex);
			Assert::AreEqual(std::size_t{3}, PonyMath::Shape::AABB<float>::RightTopNearIndex);
			Assert::AreEqual(std::size_t{4}, PonyMath::Shape::AABB<float>::LeftBottomFarIndex);
			Assert::AreEqual(std::size_t{5}, PonyMath::Shape::AABB<float>::RightBottomFarIndex);
			Assert::AreEqual(std::size_t{6}, PonyMath::Shape::AABB<float>::LeftTopFarIndex);
			Assert::AreEqual(std::size_t{7}, PonyMath::Shape::AABB<float>::RightTopFarIndex);
			Assert::AreEqual(std::size_t{8}, PonyMath::Shape::AABB<float>::CornerCount);

			Assert::IsTrue(PonyMath::Shape::AABB<float>(0.f, 0.f, 0.f, 0.f, 0.f, 0.f) == PonyMath::Shape::AABB<float>::Predefined::Zero);
		}

		TEST_METHOD(ConstructorDefaultShortTest)
		{
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>();
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>::Predefined::Zero == aabb.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>::Predefined::Zero == aabb.Extents());
		}

		TEST_METHOD(ConstructorDefaultFloatTest)
		{
			const auto aabb = PonyMath::Shape::AABB<float>();
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Zero == aabb.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Zero == aabb.Extents());
		}

		TEST_METHOD(ConstructorDataShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = 12;
			constexpr std::int16_t halfDepth = 22;
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x, y, z) == aabb.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(halfWidth, halfHeight, halfDepth) == aabb.Extents());
		}

		TEST_METHOD(ConstructorDataFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = 12;
			constexpr float halfDepth = 22;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x, y, z) == aabb.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(halfWidth, halfHeight, halfDepth) == aabb.Extents());
		}

		TEST_METHOD(ConstructorVectorShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = 12;
			constexpr std::int16_t halfDepth = 22;
			constexpr auto center = PonyMath::Core::Vector3<std::int16_t>(x, y, z);
			constexpr auto extents = PonyMath::Core::Vector3<std::int16_t>(halfWidth, halfHeight, halfDepth);
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>(center, extents);
			Assert::IsTrue(center == aabb.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(halfWidth, halfHeight, halfDepth) == aabb.Extents());
		}

		TEST_METHOD(ConstructorVectorFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = 12;
			constexpr float halfDepth = 22;
			constexpr auto center = PonyMath::Core::Vector3<float>(x, y, z);
			constexpr auto extents = PonyMath::Core::Vector3<float>(halfWidth, halfHeight, halfDepth);
			const auto aabb = PonyMath::Shape::AABB<float>(center, extents);
			Assert::IsTrue(center == aabb.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(halfWidth, halfHeight, halfDepth) == aabb.Extents());
		}

		TEST_METHOD(ConstructorBoxShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t width = 24;
			constexpr std::int16_t height = -12;
			constexpr std::int16_t depth = -22;
			constexpr auto box = PonyMath::Shape::Box(x, y, z, width, height, depth);
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>(box);
			Assert::IsTrue(box.Center() == aabb.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(width / 2u, -height / 2u, -depth / 2u) == aabb.Extents());
		}

		TEST_METHOD(ConstructorBoxFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float width = 24;
			constexpr float height = -12;
			constexpr float depth = -22;
			constexpr auto box = PonyMath::Shape::Box(x, y, z, width, height, depth);
			const auto aabb = PonyMath::Shape::AABB<float>(box);
			Assert::IsTrue(box.Center() == aabb.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(width / 2.f, -height / 2.f, -depth / 2.f) == aabb.Extents());
		}

		TEST_METHOD(ConstructorCopyShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = 12;
			constexpr std::int16_t halfDepth = 22;
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			const auto copy = aabb;
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x, y, z) == copy.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(halfWidth, halfHeight, halfDepth) == copy.Extents());
		}

		TEST_METHOD(ConstructorCopyFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = 12;
			constexpr float halfDepth = 22;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			const auto copy = aabb;
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x, y, z) == copy.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(halfWidth, halfHeight, halfDepth) == copy.Extents());
		}

		TEST_METHOD(ConstructorMoveShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = 12;
			constexpr std::int16_t halfDepth = 22;
			auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			const auto copy = std::move(aabb);
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x, y, z) == copy.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(halfWidth, halfHeight, halfDepth) == copy.Extents());
		}

		TEST_METHOD(ConstructorMoveFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = 12;
			constexpr float halfDepth = 22;
			auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			const auto copy = std::move(aabb);
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x, y, z) == copy.Center());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(halfWidth, halfHeight, halfDepth) == copy.Extents());
		}

		TEST_METHOD(CenterShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = 12;
			constexpr std::int16_t halfDepth = 22;
			auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x, y, z) == aabb.Center());
		}

		TEST_METHOD(CenterFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = 12;
			constexpr float halfDepth = 22;
			auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x, y, z) == aabb.Center());
		}

		TEST_METHOD(ExtentShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = 12;
			constexpr std::int16_t halfDepth = 22;
			auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::AreEqual(halfWidth, aabb.ExtentX());
			Assert::AreEqual(halfHeight, aabb.ExtentY());
			Assert::AreEqual(halfDepth, aabb.ExtentZ());
			Assert::AreEqual(halfWidth, aabb.Extent(0));
			Assert::AreEqual(halfHeight, aabb.Extent(1));
			Assert::AreEqual(halfDepth, aabb.Extent(2));

			aabb.ExtentX() = 3;
			aabb.ExtentY() = 6;
			aabb.ExtentZ() = 8;
			Assert::AreEqual(std::int16_t{3}, aabb.ExtentX());
			Assert::AreEqual(std::int16_t{6}, aabb.ExtentY());
			Assert::AreEqual(std::int16_t{8}, aabb.ExtentZ());

			aabb.Extent(2) = 6;
			Assert::AreEqual(std::int16_t{6}, aabb.Extent(2));
		}

		TEST_METHOD(ExtentFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = 12;
			constexpr float halfDepth = 22;
			auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::AreEqual(halfWidth, aabb.ExtentX());
			Assert::AreEqual(halfHeight, aabb.ExtentY());
			Assert::AreEqual(halfDepth, aabb.ExtentZ());
			Assert::AreEqual(halfWidth, aabb.Extent(0));
			Assert::AreEqual(halfHeight, aabb.Extent(1));
			Assert::AreEqual(halfDepth, aabb.Extent(2));

			aabb.ExtentX() = 3;
			aabb.ExtentY() = 6;
			aabb.ExtentZ() = 8;
			Assert::AreEqual(3.f, aabb.ExtentX());
			Assert::AreEqual(6.f, aabb.ExtentY());
			Assert::AreEqual(8.f, aabb.ExtentZ());

			aabb.Extent(2) = 6;
			Assert::AreEqual(6.f, aabb.Extent(2));
		}

		TEST_METHOD(ExtentsShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t halfWidth = 24;
			constexpr std::int16_t halfHeight = 12;
			constexpr std::int16_t halfDepth = 22;
			auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(halfWidth, halfHeight, halfDepth) == aabb.Extents());

			constexpr auto extents = PonyMath::Core::Vector3<std::int16_t>(5, 8, 9);
			aabb.Extents() = extents;
			Assert::IsTrue(extents == aabb.Extents());
		}

		TEST_METHOD(ExtentsFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float halfWidth = 24;
			constexpr float halfHeight = 12;
			constexpr float halfDepth = 22;
			auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(PonyMath::Core::Vector3<float>(halfWidth, halfHeight, halfDepth) == aabb.Extents());

			constexpr auto extents = PonyMath::Core::Vector3<float>(5, 8, 9);
			aabb.Extents() = extents;
			Assert::IsTrue(extents == aabb.Extents());
		}

		TEST_METHOD(SizeShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t z = -12;
			constexpr std::int16_t halfWidth = 4;
			constexpr std::int16_t halfHeight = 14;
			constexpr std::int16_t halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::AreEqual(std::int16_t{8}, aabb.Width());
			Assert::AreEqual(std::int16_t{28}, aabb.Height());
			Assert::AreEqual(std::int16_t{4}, aabb.Depth());
			Assert::AreEqual(std::int16_t{8}, aabb.Size(0));
			Assert::AreEqual(std::int16_t{28}, aabb.Size(1));
			Assert::AreEqual(std::int16_t{4}, aabb.Size(2));
		}

		TEST_METHOD(SizeFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = 4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::AreEqual(8.f, aabb.Width());
			Assert::AreEqual(28.f, aabb.Height());
			Assert::AreEqual(4.f, aabb.Depth());
			Assert::AreEqual(8.f, aabb.Size(0));
			Assert::AreEqual(28.f, aabb.Size(1));
			Assert::AreEqual(4.f, aabb.Size(2));
		}

		TEST_METHOD(MinShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t z = -12;
			constexpr std::int16_t halfWidth = 4;
			constexpr std::int16_t halfHeight = 14;
			constexpr std::int16_t halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::AreEqual(std::int16_t{3}, aabb.MinX());
			Assert::AreEqual(std::int16_t{-22}, aabb.MinY());
			Assert::AreEqual(std::int16_t{-14}, aabb.MinZ());
			Assert::AreEqual(std::int16_t{3}, aabb.Min(0));
			Assert::AreEqual(std::int16_t{-22}, aabb.Min(1));
			Assert::AreEqual(std::int16_t{-14}, aabb.Min(2));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, -22, -14) == aabb.Min());
		}

		TEST_METHOD(MinFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = 4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::AreEqual(3.f, aabb.MinX());
			Assert::AreEqual(-22.f, aabb.MinY());
			Assert::AreEqual(-14.f, aabb.MinZ());
			Assert::AreEqual(3.f, aabb.Min(0));
			Assert::AreEqual(-22.f, aabb.Min(1));
			Assert::AreEqual(-14.f, aabb.Min(2));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3.f, -22.f, -14.f) == aabb.Min());
		}

		TEST_METHOD(MaxShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t z = -12;
			constexpr std::int16_t halfWidth = 4;
			constexpr std::int16_t halfHeight = 14;
			constexpr std::int16_t halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::AreEqual(std::int16_t{11}, aabb.MaxX());
			Assert::AreEqual(std::int16_t{6}, aabb.MaxY());
			Assert::AreEqual(std::int16_t{-10}, aabb.MaxZ());
			Assert::AreEqual(std::int16_t{11}, aabb.Max(0));
			Assert::AreEqual(std::int16_t{6}, aabb.Max(1));
			Assert::AreEqual(std::int16_t{-10}, aabb.Max(2));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, 6, -10) == aabb.Max());
		}

		TEST_METHOD(MaxFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = 4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::AreEqual(11.f, aabb.MaxX());
			Assert::AreEqual(6.f, aabb.MaxY());
			Assert::AreEqual(-10.f, aabb.MaxZ());
			Assert::AreEqual(11.f, aabb.Max(0));
			Assert::AreEqual(6.f, aabb.Max(1));
			Assert::AreEqual(-10.f, aabb.Max(2));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11.f, 6.f, -10.f) == aabb.Max());
		}

		TEST_METHOD(CornerShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t z = -12;
			constexpr std::int16_t halfWidth = 4;
			constexpr std::int16_t halfHeight = 14;
			constexpr std::int16_t halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, -22, -14) == aabb.LeftBottomNear());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, -22, -14) == aabb.RightBottomNear());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, 6, -14) == aabb.LeftTopNear());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, 6, -14) == aabb.RightTopNear());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, -22, -10) == aabb.LeftBottomFar());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, -22, -10) == aabb.RightBottomFar());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, 6, -10) == aabb.LeftTopFar());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, 6, -10) == aabb.RightTopFar());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, -22, -14) == aabb.Corner(0));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, -22, -14) == aabb.Corner(1));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, 6, -14) == aabb.Corner(2));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, 6, -14) == aabb.Corner(3));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, -22, -10) == aabb.Corner(4));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, -22, -10) == aabb.Corner(5));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, 6, -10) == aabb.Corner(6));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, 6, -10) == aabb.Corner(7));

			const auto corners = aabb.Corners();
			for (std::size_t i = 0; i < 8; ++i)
			{
				Assert::IsTrue(aabb.Corner(i) == corners[i]);
			}
		}

		TEST_METHOD(CornerFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = 4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, -22, -14) == aabb.LeftBottomNear());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, -22, -14) == aabb.RightBottomNear());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, 6, -14) == aabb.LeftTopNear());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, 6, -14) == aabb.RightTopNear());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, -22, -10) == aabb.LeftBottomFar());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, -22, -10) == aabb.RightBottomFar());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, 6, -10) == aabb.LeftTopFar());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, 6, -10) == aabb.RightTopFar());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, -22, -14) == aabb.Corner(0));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, -22, -14) == aabb.Corner(1));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, 6, -14) == aabb.Corner(2));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, 6, -14) == aabb.Corner(3));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, -22, -10) == aabb.Corner(4));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, -22, -10) == aabb.Corner(5));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, 6, -10) == aabb.Corner(6));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, 6, -10) == aabb.Corner(7));

			const auto corners = aabb.Corners();
			for (std::size_t i = 0; i < 8; ++i)
			{
				Assert::IsTrue(aabb.Corner(i) == corners[i]);
			}
		}

		TEST_METHOD(AreaShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t z = -12;
			constexpr std::int16_t halfWidth = 4;
			constexpr std::int16_t halfHeight = 14;
			constexpr std::int16_t halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::AreEqual(std::int16_t{736}, aabb.Area());
		}

		TEST_METHOD(AreaFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = 4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::AreEqual(736.f, aabb.Area());
		}

		TEST_METHOD(VolumeShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t z = -12;
			constexpr std::int16_t halfWidth = 4;
			constexpr std::int16_t halfHeight = 14;
			constexpr std::int16_t halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::AreEqual(std::int16_t{896}, aabb.Volume());
		}

		TEST_METHOD(VolumeFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = 4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::AreEqual(896.f, aabb.Volume());
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = -2;
			auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(aabb.IsFinite());

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = aabb.Center()[i];
				aabb.Center()[i] = std::numeric_limits<float>::quiet_NaN();
				Assert::IsFalse(aabb.IsFinite());
				aabb.Center()[i] = was;
			}

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = aabb.Extent(i);
				aabb.Extent(i) = std::numeric_limits<float>::quiet_NaN();
				Assert::IsFalse(aabb.IsFinite());
				aabb.Extent(i) = was;
			}
		}

		TEST_METHOD(ContainsShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t z = -12;
			constexpr std::int16_t halfWidth = 4;
			constexpr std::int16_t halfHeight = 14;
			constexpr std::int16_t halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(aabb.Contains(aabb.Center()));
			Assert::IsTrue(aabb.Contains(aabb.Min()));
			Assert::IsTrue(aabb.Contains(aabb.Max()));
			Assert::IsTrue(aabb.Contains(aabb.Center() + PonyMath::Core::Vector3<std::int16_t>(halfWidth, halfHeight, -halfDepth) / 2));

			Assert::IsFalse(aabb.Contains(PonyMath::Core::Vector3<std::int16_t>(100, y, z)));
			Assert::IsFalse(aabb.Contains(PonyMath::Core::Vector3<std::int16_t>(x, -100, z)));
			Assert::IsFalse(aabb.Contains(PonyMath::Core::Vector3<std::int16_t>(x, y, 178)));
			Assert::IsFalse(aabb.Contains(aabb.Max() + PonyMath::Core::Vector3<std::int16_t>::Predefined::One));
		}

		TEST_METHOD(ContainsFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = 4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(aabb.Contains(aabb.Center()));
			Assert::IsTrue(aabb.Contains(aabb.Min()));
			Assert::IsTrue(aabb.Contains(aabb.Max()));
			Assert::IsTrue(aabb.Contains(aabb.Center() + PonyMath::Core::Vector3<float>(halfWidth, halfHeight, halfDepth) / 2.f));

			Assert::IsFalse(aabb.Contains(PonyMath::Core::Vector3<float>(100.f, y, z)));
			Assert::IsFalse(aabb.Contains(PonyMath::Core::Vector3<float>(x, -100, z)));
			Assert::IsFalse(aabb.Contains(PonyMath::Core::Vector3<float>(x, y, 178)));
			Assert::IsFalse(aabb.Contains(aabb.Max() + PonyMath::Core::Vector3<float>::Predefined::One));
		}

		TEST_METHOD(ClosestPointShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t z = -12;
			constexpr std::int16_t halfWidth = 4;
			constexpr std::int16_t halfHeight = 14;
			constexpr std::int16_t halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<std::int16_t>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(aabb.Center() == aabb.ClosestPoint(aabb.Center()));
			Assert::IsTrue(aabb.Min() == aabb.ClosestPoint(aabb.Min()));
			Assert::IsTrue(aabb.Max() == aabb.ClosestPoint(aabb.Max()));
			auto vector = aabb.Center() + PonyMath::Core::Vector3<std::int16_t>(halfWidth, halfHeight, -halfDepth) / 2;
			Assert::IsTrue(vector == aabb.ClosestPoint(vector));

			vector = PonyMath::Core::Vector3<std::int16_t>(100, y, z);
			auto expected = PonyMath::Core::Vector3<std::int16_t>(aabb.MaxX(), y, z);
			Assert::IsTrue(expected == aabb.ClosestPoint(vector));

			vector = PonyMath::Core::Vector3<std::int16_t>(x, -100, z);
			expected = PonyMath::Core::Vector3<std::int16_t>(x, aabb.MinY(), z);
			Assert::IsTrue(expected == aabb.ClosestPoint(vector));

			vector = PonyMath::Core::Vector3<std::int16_t>(x, y, 178);
			expected = PonyMath::Core::Vector3<std::int16_t>(x, y, aabb.MaxZ());
			Assert::IsTrue(expected == aabb.ClosestPoint(vector));

			vector = PonyMath::Core::Vector3<std::int16_t>(-100, 100, 178);
			expected = PonyMath::Core::Vector3<std::int16_t>(aabb.MinX(), aabb.MaxY(), aabb.MaxZ());
			Assert::IsTrue(expected == aabb.ClosestPoint(vector));
		}

		TEST_METHOD(ClosestPointFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = 4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(aabb.Center(), aabb.ClosestPoint(aabb.Center())));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(aabb.Min(), aabb.ClosestPoint(aabb.Min())));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(aabb.Max(), aabb.ClosestPoint(aabb.Max())));
			auto vector = aabb.Center() + PonyMath::Core::Vector3<float>(halfWidth, halfHeight, -halfDepth) / 2.f;
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(vector, aabb.ClosestPoint(vector)));

			vector = PonyMath::Core::Vector3<float>(100, y, z);
			auto expected = PonyMath::Core::Vector3<float>(aabb.MaxX(), y, z);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, aabb.ClosestPoint(vector)));

			vector = PonyMath::Core::Vector3<float>(x, -100, z);
			expected = PonyMath::Core::Vector3<float>(x, aabb.MinY(), z);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, aabb.ClosestPoint(vector)));

			vector = PonyMath::Core::Vector3<float>(x, y, 178);
			expected = PonyMath::Core::Vector3<float>(x, y, aabb.MaxZ());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, aabb.ClosestPoint(vector)));

			vector = PonyMath::Core::Vector3<float>(-100, 100, 178);
			expected = PonyMath::Core::Vector3<float>(aabb.MinX(), aabb.MaxY(), aabb.MaxZ());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, aabb.ClosestPoint(vector)));
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = 4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			const std::string expected = std::format("Center: {}, Extents: {}", aabb.Center().ToString(), aabb.Extents().ToString());
			Assert::AreEqual(expected, aabb.ToString());

			std::ostringstream ss;
			ss << aabb;
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(ConvertTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = 4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			const auto aabbInt = static_cast<PonyMath::Shape::AABB<std::int16_t>>(aabb);
			Assert::AreEqual(static_cast<std::int16_t>(x), aabbInt.Center().X());
			Assert::AreEqual(static_cast<std::int16_t>(y), aabbInt.Center().Y());
			Assert::AreEqual(static_cast<std::int16_t>(z), aabbInt.Center().Z());
			Assert::AreEqual(static_cast<std::int16_t>(halfWidth), aabbInt.ExtentX());
			Assert::AreEqual(static_cast<std::int16_t>(halfHeight), aabbInt.ExtentY());
			Assert::AreEqual(static_cast<std::int16_t>(halfDepth), aabbInt.ExtentZ());
		}

		TEST_METHOD(ConvertToBoxTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = 4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			const auto box = static_cast<PonyMath::Shape::Box<float>>(aabb);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(aabb.Min(), box.Position()));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(PonyMath::Core::Vector3<float>(halfWidth, halfHeight, halfDepth) * 2.f, box.Size()));
		}

		TEST_METHOD(EqualityTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = 4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = 2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			auto another = aabb;
			Assert::IsTrue(aabb == another);

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = another.Center()[i];
				another.Center()[i] = std::nextafter(was, 0.f);
				Assert::IsFalse(aabb == another);
				another.Center()[i] += 1.f;
				Assert::IsFalse(aabb == another);
				another.Center()[i] = was;
			}

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = another.Extent(i);
				another.Extent(i) = std::nextafter(was, 0.f);
				Assert::IsFalse(aabb == another);
				another.Extent(i) = was + 1.f;
				Assert::IsFalse(aabb == another);
				another.Extent(i) = was;
			}
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float halfWidth = -4;
			constexpr float halfHeight = 14;
			constexpr float halfDepth = -2;
			const auto aabb = PonyMath::Shape::AABB<float>(x, y, z, halfWidth, halfHeight, halfDepth);
			auto another = aabb;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(aabb, another));

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = another.Center()[i];
				another.Center()[i] = std::nextafter(was, 0.f);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(aabb, another));
				another.Center()[i] += 1.f;
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(aabb, another));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(aabb, another, 5.f));
				another.Center()[i] = was;
			}

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = another.Extent(i);
				another.Extent(i) = std::nextafter(was, 0.f);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(aabb, another));
				another.Extent(i) = was + 1.f;
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(aabb, another));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(aabb, another, 5.f));
				another.Extent(i) = was;
			}
		}

		static constexpr PonyMath::Shape::AABB<float> AABBConstexpr()
		{
			auto defaultAABB = PonyMath::Shape::AABB<float>();
			auto movedAABB = std::move(defaultAABB);

			movedAABB.Center() = PonyMath::Core::Vector3<float>(2.f, 5.f, -8.f);
			movedAABB.ExtentX() = 2.f;
			movedAABB.ExtentY() = 4.f;
			movedAABB.ExtentZ() = 3.f;
			movedAABB.Extent(1) = 3.f;
			movedAABB.Extents() = PonyMath::Core::Vector3<float>(2.f, 5.f, 8.f);

			auto copied = PonyMath::Shape::AABB<float>();
			copied = defaultAABB;

			auto moved = PonyMath::Shape::AABB<float>();
			moved = std::move(movedAABB);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultAABB = PonyMath::Shape::AABB<float>();
			[[maybe_unused]] constexpr auto copied = defaultAABB;
			[[maybe_unused]] constexpr auto aabb = PonyMath::Shape::AABB<float>(-2.f, 3.f, 4.f, 4.f, 5.f, 2.f);
			[[maybe_unused]] constexpr auto aabbV = PonyMath::Shape::AABB<float>(PonyMath::Core::Vector3<float>(-2.f, 3.f, 4.f), PonyMath::Core::Vector3<float>(4.f, 5.f, 2.f));
			[[maybe_unused]] constexpr auto moved = AABBConstexpr();

			[[maybe_unused]] constexpr auto center = moved.Center();

			[[maybe_unused]] constexpr auto extentX = moved.ExtentX();
			[[maybe_unused]] constexpr auto extentY = moved.ExtentY();
			[[maybe_unused]] constexpr auto extentZ = moved.ExtentZ();
			[[maybe_unused]] constexpr auto extent = moved.Extent(1);
			[[maybe_unused]] constexpr auto extents = moved.Extents();

			[[maybe_unused]] constexpr auto width = moved.Width();
			[[maybe_unused]] constexpr auto height = moved.Height();
			[[maybe_unused]] constexpr auto depth = moved.Depth();
			[[maybe_unused]] constexpr auto size = moved.Size(0);

			[[maybe_unused]] constexpr auto minX = moved.MinX();
			[[maybe_unused]] constexpr auto minY = moved.MinY();
			[[maybe_unused]] constexpr auto minZ = moved.MinZ();
			[[maybe_unused]] constexpr auto minI = moved.Min(2);
			[[maybe_unused]] constexpr auto min = moved.Min();
			[[maybe_unused]] constexpr auto maxX = moved.MaxX();
			[[maybe_unused]] constexpr auto maxY = moved.MaxY();
			[[maybe_unused]] constexpr auto maxZ = moved.MaxZ();
			[[maybe_unused]] constexpr auto maxI = moved.Max(2);
			[[maybe_unused]] constexpr auto max = moved.Max();

			[[maybe_unused]] constexpr auto leftBottomNear = moved.LeftBottomNear();
			[[maybe_unused]] constexpr auto rightBottomNear = moved.RightBottomNear();
			[[maybe_unused]] constexpr auto leftTopNear = moved.LeftTopNear();
			[[maybe_unused]] constexpr auto rightTopNear = moved.RightTopNear();
			[[maybe_unused]] constexpr auto leftBottomFar = moved.LeftBottomFar();
			[[maybe_unused]] constexpr auto rightBottomFar = moved.RightBottomFar();
			[[maybe_unused]] constexpr auto leftTopFar = moved.LeftTopFar();
			[[maybe_unused]] constexpr auto rightTopFar = moved.RightTopFar();
			[[maybe_unused]] constexpr auto corner = moved.Corner(5);
			[[maybe_unused]] constexpr auto corners = moved.Corners();

			[[maybe_unused]] constexpr auto area = moved.Area();
			[[maybe_unused]] constexpr auto volume = moved.Volume();

			[[maybe_unused]] constexpr auto closest = moved.ClosestPoint(PonyMath::Core::Vector3<float>(1.f, 2.f, 3.f));

			[[maybe_unused]] constexpr auto box = static_cast<PonyMath::Shape::Box<float>>(moved);

			[[maybe_unused]] constexpr bool equal = moved == defaultAABB;
			[[maybe_unused]] constexpr bool notEqual = moved != defaultAABB;

			[[maybe_unused]] constexpr bool areAlmostEqual = PonyMath::Shape::AreAlmostEqual(moved, defaultAABB);
		}
	};
}
