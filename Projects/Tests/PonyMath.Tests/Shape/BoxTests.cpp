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
	TEST_CLASS(BoxTests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<std::int16_t, PonyMath::Shape::Box<std::int16_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Shape::Box<float>::ValueType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{0}, PonyMath::Shape::Box<float>::LeftBottomNearIndex);
			Assert::AreEqual(std::size_t{1}, PonyMath::Shape::Box<float>::RightBottomNearIndex);
			Assert::AreEqual(std::size_t{2}, PonyMath::Shape::Box<float>::LeftTopNearIndex);
			Assert::AreEqual(std::size_t{3}, PonyMath::Shape::Box<float>::RightTopNearIndex);
			Assert::AreEqual(std::size_t{4}, PonyMath::Shape::Box<float>::LeftBottomFarIndex);
			Assert::AreEqual(std::size_t{5}, PonyMath::Shape::Box<float>::RightBottomFarIndex);
			Assert::AreEqual(std::size_t{6}, PonyMath::Shape::Box<float>::LeftTopFarIndex);
			Assert::AreEqual(std::size_t{7}, PonyMath::Shape::Box<float>::RightTopFarIndex);
			Assert::AreEqual(std::size_t{8}, PonyMath::Shape::Box<float>::CornerCount);
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyMath::Shape::Box<float>(0.f, 0.f, 0.f, 0.f, 0.f, 0.f) == PonyMath::Shape::Box<float>::Predefined::Zero);
			Assert::IsTrue(PonyMath::Shape::Box<float>(0.f, 0.f, 0.f, 1.f, 1.f, 1.f) == PonyMath::Shape::Box<float>::Predefined::NormalizedFull);
		}

		TEST_METHOD(ConstructorDefaultShortTest)
		{
			const auto box = PonyMath::Shape::Box<std::int16_t>();
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>::Predefined::Zero == box.Position());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>::Predefined::Zero == box.Size());
		}

		TEST_METHOD(ConstructorDefaultFloatTest)
		{
			const auto box = PonyMath::Shape::Box<float>();
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Zero == box.Position());
			Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Zero == box.Size());
		}

		TEST_METHOD(ConstructorDataShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t width = 24;
			constexpr std::int16_t height = 12;
			constexpr std::int16_t depth = 22;
			const auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x, y, z) == box.Position());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(width, height, depth) == box.Size());
		}

		TEST_METHOD(ConstructorDataFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float width = 24;
			constexpr float height = 12;
			constexpr float depth = 22;
			const auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x, y, z) == box.Position());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(width, height, depth) == box.Size());
		}

		TEST_METHOD(ConstructorVectorShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t width = 24;
			constexpr std::int16_t height = 12;
			constexpr std::int16_t depth = 22;
			constexpr auto position = PonyMath::Core::Vector3<std::int16_t>(x, y, z);
			constexpr auto size = PonyMath::Core::Vector3<std::int16_t>(width, height, depth);
			const auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::IsTrue(position == box.Position());
			Assert::IsTrue(size == box.Size());
		}

		TEST_METHOD(ConstructorVectorFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float width = 24;
			constexpr float height = 12;
			constexpr float depth = 22;
			constexpr auto position = PonyMath::Core::Vector3<float>(x, y, z);
			constexpr auto size = PonyMath::Core::Vector3<float>(width, height, depth);
			const auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::IsTrue(position == box.Position());
			Assert::IsTrue(size == box.Size());
		}

		TEST_METHOD(ConstructorCopyShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t width = 24;
			constexpr std::int16_t height = 12;
			constexpr std::int16_t depth = 22;
			constexpr auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			const auto copied = box;
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x, y, z) == copied.Position());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(width, height, depth) == copied.Size());
		}

		TEST_METHOD(ConstructorCopyFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float width = 24;
			constexpr float height = 12;
			constexpr float depth = 22;
			constexpr auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			const auto copied = box;
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x, y, z) == copied.Position());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(width, height, depth) == copied.Size());
		}

		TEST_METHOD(ConstructorMoveShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t width = 24;
			constexpr std::int16_t height = 12;
			constexpr std::int16_t depth = 22;
			auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			const auto moved = std::move(box);
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x, y, z) == moved.Position());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(width, height, depth) == moved.Size());
		}

		TEST_METHOD(ConstructorMoveFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float width = 24;
			constexpr float height = 12;
			constexpr float depth = 22;
			auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			const auto moved = std::move(box);
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x, y, z) == moved.Position());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(width, height, depth) == moved.Size());
		}

		TEST_METHOD(PositionShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t width = 24;
			constexpr std::int16_t height = 12;
			constexpr std::int16_t depth = 22;
			constexpr auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x, y, z) == box.Position());
		}

		TEST_METHOD(PositionFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float width = 24;
			constexpr float height = 12;
			constexpr float depth = 22;
			constexpr auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x, y, z) == box.Position());
		}

		TEST_METHOD(SizeShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t width = 24;
			constexpr std::int16_t height = 12;
			constexpr std::int16_t depth = 22;
			constexpr auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(width, height, depth) == box.Size());
		}

		TEST_METHOD(SizeFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float width = 24;
			constexpr float height = 12;
			constexpr float depth = 22;
			constexpr auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::IsTrue(PonyMath::Core::Vector3<float>(width, height, depth) == box.Size());
		}

		TEST_METHOD(MinGetShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t width = 24;
			constexpr std::int16_t height = 12;
			constexpr std::int16_t depth = 22;
			constexpr auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::AreEqual(x, box.MinX());
			Assert::AreEqual(y, box.MinY());
			Assert::AreEqual(z, box.MinZ());
			Assert::AreEqual(x, box.Min(0));
			Assert::AreEqual(y, box.Min(1));
			Assert::AreEqual(z, box.Min(2));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x, y, z) == box.Min());
		}

		TEST_METHOD(MinGetFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float width = 24;
			constexpr float height = 12;
			constexpr float depth = 22;
			constexpr auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::AreEqual(x, box.MinX());
			Assert::AreEqual(y, box.MinY());
			Assert::AreEqual(z, box.MinZ());
			Assert::AreEqual(x, box.Min(0));
			Assert::AreEqual(y, box.Min(1));
			Assert::AreEqual(z, box.Min(2));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x, y, z) == box.Min());
		}

		TEST_METHOD(MinSetShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t x1 = 7;
			constexpr std::int16_t y1 = -5;
			constexpr std::int16_t z1 = 15;
			auto box = PonyMath::Shape::Box<std::int16_t>();
			box.MinX(x);
			box.MinY(y);
			box.MinZ(z);
			Assert::AreEqual(x, box.MinX());
			Assert::AreEqual(y, box.MinY());
			Assert::AreEqual(z, box.MinZ());
			box.Min(0, x1);
			box.Min(1, y1);
			box.Min(2, z1);
			Assert::AreEqual(x1, box.Min(0));
			Assert::AreEqual(y1, box.Min(1));
			Assert::AreEqual(z1, box.Min(2));
			box.Min(PonyMath::Core::Vector3<std::int16_t>(x, y, z));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x, y, z) == box.Min());
		}

		TEST_METHOD(MinSetFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float x1 = 7;
			constexpr float y1 = -5;
			constexpr float z1 = 15;
			auto box = PonyMath::Shape::Box<float>();
			box.MinX(x);
			box.MinY(y);
			box.MinZ(z);
			Assert::AreEqual(x, box.MinX());
			Assert::AreEqual(y, box.MinY());
			Assert::AreEqual(z, box.MinZ());
			box.Min(0, x1);
			box.Min(1, y1);
			box.Min(2, z1);
			Assert::AreEqual(x1, box.Min(0));
			Assert::AreEqual(y1, box.Min(1));
			Assert::AreEqual(z1, box.Min(2));
			box.Min(PonyMath::Core::Vector3<float>(x, y, z));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x, y, z) == box.Min());
		}

		TEST_METHOD(MaxGetShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t width = 24;
			constexpr std::int16_t height = 12;
			constexpr std::int16_t depth = 22;
			constexpr auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::AreEqual(static_cast<std::int16_t>(x + width), box.MaxX());
			Assert::AreEqual(static_cast<std::int16_t>(y + height), box.MaxY());
			Assert::AreEqual(static_cast<std::int16_t>(z + depth), box.MaxZ());
			Assert::AreEqual(static_cast<std::int16_t>(x + width), box.Max(0));
			Assert::AreEqual(static_cast<std::int16_t>(y + height), box.Max(1));
			Assert::AreEqual(static_cast<std::int16_t>(z + depth), box.Max(2));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x + width, y + height, z + depth) == box.Max());
		}

		TEST_METHOD(MaxGetFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float width = 24;
			constexpr float height = 12;
			constexpr float depth = 22;
			constexpr auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::AreEqual(x + width, box.MaxX());
			Assert::AreEqual(y + height, box.MaxY());
			Assert::AreEqual(z + depth, box.MaxZ());
			Assert::AreEqual(x + width, box.Max(0));
			Assert::AreEqual(y + height, box.Max(1));
			Assert::AreEqual(z + depth, box.Max(2));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x + width, y + height, z + depth) == box.Max());
		}

		TEST_METHOD(MaxSetShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t x1 = 7;
			constexpr std::int16_t y1 = -5;
			constexpr std::int16_t z1 = 15;
			auto box = PonyMath::Shape::Box<std::int16_t>();
			box.MaxX(x);
			box.MaxY(y);
			box.MaxZ(z);
			Assert::AreEqual(x, box.MaxX());
			Assert::AreEqual(y, box.MaxY());
			Assert::AreEqual(z, box.MaxZ());
			box.Max(0, x1);
			box.Max(1, y1);
			box.Max(2, z1);
			Assert::AreEqual(x1, box.Max(0));
			Assert::AreEqual(y1, box.Max(1));
			Assert::AreEqual(z1, box.Max(2));
			box.Max(PonyMath::Core::Vector3<std::int16_t>(x, y, z));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x, y, z) == box.Max());
		}

		TEST_METHOD(MaxSetFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float x1 = 7;
			constexpr float y1 = -5;
			constexpr float z1 = 15;
			auto box = PonyMath::Shape::Box<float>();
			box.MaxX(x);
			box.MaxY(y);
			box.MaxZ(z);
			Assert::AreEqual(x, box.MaxX());
			Assert::AreEqual(y, box.MaxY());
			Assert::AreEqual(z, box.MaxZ());
			box.Max(0, x1);
			box.Max(1, y1);
			box.Max(2, z1);
			Assert::AreEqual(x1, box.Max(0));
			Assert::AreEqual(y1, box.Max(1));
			Assert::AreEqual(z1, box.Max(2));
			box.Max(PonyMath::Core::Vector3<float>(x, y, z));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x, y, z) == box.Max());
		}

		TEST_METHOD(SizeGetShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t width = 24;
			constexpr std::int16_t height = 12;
			constexpr std::int16_t depth = 22;
			constexpr auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::AreEqual(width, box.Width());
			Assert::AreEqual(height, box.Height());
			Assert::AreEqual(depth, box.Depth());
			Assert::AreEqual(width, box.Size(0));
			Assert::AreEqual(height, box.Size(1));
			Assert::AreEqual(depth, box.Size(2));
		}

		TEST_METHOD(SizeGetFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float width = 24;
			constexpr float height = 12;
			constexpr float depth = 22;
			constexpr auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::AreEqual(width, box.Width());
			Assert::AreEqual(height, box.Height());
			Assert::AreEqual(depth, box.Depth());
			Assert::AreEqual(width, box.Size(0));
			Assert::AreEqual(height, box.Size(1));
			Assert::AreEqual(depth, box.Size(2));
		}

		TEST_METHOD(SizeSetShortTest)
		{
			auto box = PonyMath::Shape::Box<std::int16_t>();

			box.Width<false>(4);
			Assert::AreEqual(std::int16_t{4}, box.Width());
			Assert::AreEqual(std::int16_t{0}, box.Position().X());
			box.Width<true>(10);
			Assert::AreEqual(std::int16_t{10}, box.Width());
			Assert::AreEqual(std::int16_t{2}, box.Center().X());

			box.Height<false>(8);
			Assert::AreEqual(std::int16_t{8}, box.Height());
			Assert::AreEqual(std::int16_t{0}, box.Position().Y());
			box.Height<true>(4);
			Assert::AreEqual(std::int16_t{4}, box.Height());
			Assert::AreEqual(std::int16_t{4}, box.Center().Y());

			box.Depth<false>(3);
			Assert::AreEqual(std::int16_t{3}, box.Depth());
			Assert::AreEqual(std::int16_t{0}, box.Position().Z());
			box.Depth<true>(15);
			Assert::AreEqual(std::int16_t{15}, box.Depth());
			Assert::AreEqual(std::int16_t{1}, box.Center().Z());
		}

		TEST_METHOD(SizeSetFloatTest)
		{
			auto box = PonyMath::Shape::Box<float>();

			box.Width<false>(4);
			Assert::AreEqual(4.f, box.Width());
			Assert::AreEqual(0.f, box.Position().X());
			box.Width<true>(10);
			Assert::AreEqual(10.f, box.Width());
			Assert::AreEqual(2.f, box.Center().X());

			box.Height<false>(8);
			Assert::AreEqual(8.f, box.Height());
			Assert::AreEqual(0.f, box.Position().Y());
			box.Height<true>(4);
			Assert::AreEqual(4.f, box.Height());
			Assert::AreEqual(4.f, box.Center().Y());

			box.Depth<false>(3);
			Assert::AreEqual(3.f, box.Depth());
			Assert::AreEqual(0.f, box.Position().Z());
			box.Depth<true>(15);
			Assert::AreEqual(15.f, box.Depth());
			Assert::AreEqual(1.5f, box.Center().Z());
		}

		TEST_METHOD(CenterShortTest)
		{
			constexpr std::int16_t x = -3;
			constexpr std::int16_t y = 5;
			constexpr std::int16_t z = 10;
			constexpr std::int16_t width = 24;
			constexpr std::int16_t height = 12;
			constexpr std::int16_t depth = 22;
			auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(x + width / 2, y + height / 2, z + depth / 2) == box.Center());

			constexpr auto center = PonyMath::Core::Vector3<std::int16_t>(5, -4, -8);
			box.Center(center);
			Assert::IsTrue(center == box.Center());
		}

		TEST_METHOD(CenterFloatTest)
		{
			constexpr float x = -3;
			constexpr float y = 5;
			constexpr float z = 10;
			constexpr float width = 24;
			constexpr float height = 12;
			constexpr float depth = 22;
			auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::IsTrue(PonyMath::Core::Vector3<float>(x + width / 2, y + height / 2, z + depth / 2) == box.Center());

			constexpr auto center = PonyMath::Core::Vector3<float>(5, -4, -8);
			box.Center(center);
			Assert::IsTrue(center == box.Center());
		}

		TEST_METHOD(CornerShortTest)
		{
			constexpr std::int16_t x = 3;
			constexpr std::int16_t y = -22;
			constexpr std::int16_t z = -14;
			constexpr std::int16_t width = 8;
			constexpr std::int16_t height = 28;
			constexpr std::int16_t depth = 4;
			const auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, -22, -14) == box.LeftBottomNear());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, -22, -14) == box.RightBottomNear());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, 6, -14) == box.LeftTopNear());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, 6, -14) == box.RightTopNear());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, -22, -10) == box.LeftBottomFar());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, -22, -10) == box.RightBottomFar());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, 6, -10) == box.LeftTopFar());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, 6, -10) == box.RightTopFar());
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, -22, -14) == box.Corner(0));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, -22, -14) == box.Corner(1));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, 6, -14) == box.Corner(2));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, 6, -14) == box.Corner(3));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, -22, -10) == box.Corner(4));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, -22, -10) == box.Corner(5));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(3, 6, -10) == box.Corner(6));
			Assert::IsTrue(PonyMath::Core::Vector3<std::int16_t>(11, 6, -10) == box.Corner(7));

			const auto corners = box.Corners();
			for (std::size_t i = 0; i < 8; ++i)
			{
				Assert::IsTrue(box.Corner(i) == corners[i]);
			}
		}

		TEST_METHOD(CornerFloatTest)
		{
			constexpr float x = 3;
			constexpr float y = -22;
			constexpr float z = -14;
			constexpr float width = 8;
			constexpr float height = 28;
			constexpr float depth = 4;
			const auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, -22, -14) == box.LeftBottomNear());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, -22, -14) == box.RightBottomNear());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, 6, -14) == box.LeftTopNear());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, 6, -14) == box.RightTopNear());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, -22, -10) == box.LeftBottomFar());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, -22, -10) == box.RightBottomFar());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, 6, -10) == box.LeftTopFar());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, 6, -10) == box.RightTopFar());
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, -22, -14) == box.Corner(0));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, -22, -14) == box.Corner(1));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, 6, -14) == box.Corner(2));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, 6, -14) == box.Corner(3));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, -22, -10) == box.Corner(4));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, -22, -10) == box.Corner(5));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(3, 6, -10) == box.Corner(6));
			Assert::IsTrue(PonyMath::Core::Vector3<float>(11, 6, -10) == box.Corner(7));

			const auto corners = box.Corners();
			for (std::size_t i = 0; i < 8; ++i)
			{
				Assert::IsTrue(box.Corner(i) == corners[i]);
			}
		}

		TEST_METHOD(AreaShortTest)
		{
			constexpr std::int16_t x = 3;
			constexpr std::int16_t y = -22;
			constexpr std::int16_t z = -14;
			constexpr std::int16_t width = 8;
			constexpr std::int16_t height = 28;
			constexpr std::int16_t depth = 4;
			constexpr auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::AreEqual(std::int16_t{736}, box.Area());
		}

		TEST_METHOD(AreaFloatTest)
		{
			constexpr float x = 3;
			constexpr float y = -22;
			constexpr float z = -14;
			constexpr float width = 8;
			constexpr float height = 28;
			constexpr float depth = 4;
			constexpr auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::AreEqual(736.f, box.Area());
		}

		TEST_METHOD(VolumeShortTest)
		{
			constexpr std::int16_t x = 3;
			constexpr std::int16_t y = -22;
			constexpr std::int16_t z = -14;
			constexpr std::int16_t width = 8;
			constexpr std::int16_t height = 28;
			constexpr std::int16_t depth = 4;
			constexpr auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::AreEqual(std::int16_t{896}, box.Volume());
		}

		TEST_METHOD(VolumeFloatTest)
		{
			constexpr float x = 3;
			constexpr float y = -22;
			constexpr float z = -14;
			constexpr float width = 8;
			constexpr float height = 28;
			constexpr float depth = 4;
			constexpr auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::AreEqual(896.f, box.Volume());
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr float x = 3;
			constexpr float y = -22;
			constexpr float z = -14;
			constexpr float width = 8;
			constexpr float height = 28;
			constexpr float depth = 4;
			auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::IsTrue(box.IsFinite());

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = box.Position()[i];
				box.Position()[i] = std::numeric_limits<float>::quiet_NaN();
				Assert::IsFalse(box.IsFinite());
				box.Position()[i] = was;
			}

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = box.Size(i);
				box.Size(i, std::numeric_limits<float>::quiet_NaN());
				Assert::IsFalse(box.IsFinite());
				box.Size(i, was);
			}
		}

		TEST_METHOD(ContainsShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t z = -12;
			constexpr std::int16_t width = 4;
			constexpr std::int16_t height = 14;
			constexpr std::int16_t depth = 2;
			constexpr auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::IsTrue(box.Contains(box.Center()));
			Assert::IsTrue(box.Contains(box.Min()));
			Assert::IsTrue(box.Contains(box.Max()));
			Assert::IsTrue(box.Contains(box.Center() + PonyMath::Core::Vector3<std::int16_t>(width, height, depth) / 2));

			Assert::IsFalse(box.Contains(PonyMath::Core::Vector3<std::int16_t>(100, y, z)));
			Assert::IsFalse(box.Contains(PonyMath::Core::Vector3<std::int16_t>(x, -100, z)));
			Assert::IsFalse(box.Contains(PonyMath::Core::Vector3<std::int16_t>(x, y, 178)));
			Assert::IsFalse(box.Contains(box.Max() + PonyMath::Core::Vector3<std::int16_t>::Predefined::One));
		}

		TEST_METHOD(ContainsFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float width = 4;
			constexpr float height = 14;
			constexpr float depth = 2;
			constexpr auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::IsTrue(box.Contains(box.Center()));
			Assert::IsTrue(box.Contains(box.Min()));
			Assert::IsTrue(box.Contains(box.Max()));
			Assert::IsTrue(box.Contains(box.Center() + PonyMath::Core::Vector3<float>(width, height, depth) / 2.f));

			Assert::IsFalse(box.Contains(PonyMath::Core::Vector3<float>(100.f, y, z)));
			Assert::IsFalse(box.Contains(PonyMath::Core::Vector3<float>(x, -100, z)));
			Assert::IsFalse(box.Contains(PonyMath::Core::Vector3<float>(x, y, 178)));
			Assert::IsFalse(box.Contains(box.Max() + PonyMath::Core::Vector3<float>::Predefined::One));
		}

		TEST_METHOD(ClosestPointShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t z = -12;
			constexpr std::int16_t width = 4;
			constexpr std::int16_t height = 14;
			constexpr std::int16_t depth = 2;
			constexpr auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			Assert::IsTrue(box.Center() == box.ClosestPoint(box.Center()));
			Assert::IsTrue(box.Min() == box.ClosestPoint(box.Min()));
			Assert::IsTrue(box.Max() == box.ClosestPoint(box.Max()));
			auto vector = box.Center() + PonyMath::Core::Vector3<std::int16_t>(width, height, -depth) / 2;
			Assert::IsTrue(vector == box.ClosestPoint(vector));

			vector = PonyMath::Core::Vector3<std::int16_t>(100, y, z);
			auto expected = PonyMath::Core::Vector3<std::int16_t>(box.MaxX(), y, z);
			Assert::IsTrue(expected == box.ClosestPoint(vector));

			vector = PonyMath::Core::Vector3<std::int16_t>(x, -100, z);
			expected = PonyMath::Core::Vector3<std::int16_t>(x, box.MinY(), z);
			Assert::IsTrue(expected == box.ClosestPoint(vector));

			vector = PonyMath::Core::Vector3<std::int16_t>(x, y, 178);
			expected = PonyMath::Core::Vector3<std::int16_t>(x, y, box.MaxZ());
			Assert::IsTrue(expected == box.ClosestPoint(vector));

			vector = PonyMath::Core::Vector3<std::int16_t>(-100, 100, 178);
			expected = PonyMath::Core::Vector3<std::int16_t>(box.MinX(), box.MaxY(), box.MaxZ());
			Assert::IsTrue(expected == box.ClosestPoint(vector));
		}

		TEST_METHOD(ClosestPointFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float width = 4;
			constexpr float height = 14;
			constexpr float depth = 2;
			constexpr auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(box.Center(), box.ClosestPoint(box.Center())));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(box.Min(), box.ClosestPoint(box.Min())));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(box.Max(), box.ClosestPoint(box.Max())));
			auto vector = box.Center() + PonyMath::Core::Vector3<float>(width, height, -depth) / 2.f;
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(vector, box.ClosestPoint(vector)));

			vector = PonyMath::Core::Vector3<float>(100, y, z);
			auto expected = PonyMath::Core::Vector3<float>(box.MaxX(), y, z);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, box.ClosestPoint(vector)));

			vector = PonyMath::Core::Vector3<float>(x, -100, z);
			expected = PonyMath::Core::Vector3<float>(x, box.MinY(), z);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, box.ClosestPoint(vector)));

			vector = PonyMath::Core::Vector3<float>(x, y, 178);
			expected = PonyMath::Core::Vector3<float>(x, y, box.MaxZ());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, box.ClosestPoint(vector)));

			vector = PonyMath::Core::Vector3<float>(-100, 100, 178);
			expected = PonyMath::Core::Vector3<float>(box.MinX(), box.MaxY(), box.MaxZ());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(expected, box.ClosestPoint(vector)));
		}

		TEST_METHOD(NormalizeVectorTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float width = 4;
			constexpr float height = 14;
			constexpr float depth = 2;
			const auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			const auto vector = PonyMath::Core::Vector3<float>(9.f, -10, -8);

			const auto normalized = box.Normalize(vector);
			Assert::AreEqual(0.5f, normalized.X(), 0.0001f);
			Assert::AreEqual(-1.f / 7.f, normalized.Y(), 0.0001f);
			Assert::AreEqual(2.f, normalized.Z(), 0.0001f);

			const auto unnormalized = box.Unnormalize(normalized);
			Assert::IsTrue(vector == unnormalized);
		}

		TEST_METHOD(NormalizeBoxTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float width = 4;
			constexpr float height = 14;
			constexpr float depth = 2;
			const auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			const auto other = PonyMath::Shape::Box<float>(1.f, -1.f, 20.f, 8.f, 7.f, 10.f);

			const auto normalized = box.Normalize(other);
			Assert::AreEqual(-1.5f, normalized.Position().X(), 0.0001f);
			Assert::AreEqual(0.5f, normalized.Position().Y(), 0.0001f);
			Assert::AreEqual(16.f, normalized.Position().Z(), 0.0001f);
			Assert::AreEqual(2.f, normalized.Size().X(), 0.0001f);
			Assert::AreEqual(0.5f, normalized.Size().Y(), 0.0001f);
			Assert::AreEqual(5.f, normalized.Size().Z(), 0.0001f);

			const auto unnormalized = box.Unnormalize(normalized);
			Assert::IsTrue(other == unnormalized);
		}

		TEST_METHOD(ResolveNegativeSizeShortTest)
		{
			constexpr std::int16_t x = 7;
			constexpr std::int16_t y = -8;
			constexpr std::int16_t z = -12;
			constexpr std::int16_t width = -4;
			constexpr std::int16_t height = 14;
			constexpr std::int16_t depth = -2;
			auto box = PonyMath::Shape::Box<std::int16_t>(x, y, z, width, height, depth);
			box.ResolveNegativeSize();
			Assert::AreEqual(static_cast<std::int16_t>(std::abs(width)), box.Width());
			Assert::AreEqual(static_cast<std::int16_t>(std::abs(height)), box.Height());
			Assert::AreEqual(static_cast<std::int16_t>(std::abs(depth)), box.Depth());
		}

		TEST_METHOD(ResolveNegativeSizeFloatTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float width = -4;
			constexpr float height = 14;
			constexpr float depth = -2;
			auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			box.ResolveNegativeSize();
			Assert::AreEqual(std::abs(width), box.Width());
			Assert::AreEqual(std::abs(height), box.Height());
			Assert::AreEqual(std::abs(depth), box.Depth());
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float width = -4;
			constexpr float height = 14;
			constexpr float depth = -2;
			constexpr auto position = PonyMath::Core::Vector3<float>(x, y, z);
			constexpr auto size = PonyMath::Core::Vector3<float>(width, height, depth);
			constexpr auto box = PonyMath::Shape::Box<float>(position, size);

			const std::string expected = std::format("Position: {}, Size: {}", position.ToString(), size.ToString());
			Assert::AreEqual(expected, box.ToString());

			std::ostringstream ss;
			ss << box;
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(BoxCastTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float width = -4;
			constexpr float height = 14;
			constexpr float depth = -2;
			constexpr auto position = PonyMath::Core::Vector3<float>(x, y, z);
			constexpr auto size = PonyMath::Core::Vector3<float>(width, height, depth);
			constexpr auto box = PonyMath::Shape::Box<float>(position, size);
			const auto cast = static_cast<PonyMath::Shape::Box<double>>(box);
			Assert::IsTrue(static_cast<PonyMath::Core::Vector3<double>>(position) == cast.Position());
			Assert::IsTrue(static_cast<PonyMath::Core::Vector3<double>>(size) == cast.Size());
		}

		TEST_METHOD(AssignmentTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float width = -4;
			constexpr float height = 14;
			constexpr float depth = -2;
			constexpr auto position = PonyMath::Core::Vector3<float>(x, y, z);
			constexpr auto size = PonyMath::Core::Vector3<float>(width, height, depth);
			constexpr auto box = PonyMath::Shape::Box<float>(position, size);

			auto copied = PonyMath::Shape::Box<float>();
			copied = box;
			Assert::IsTrue(position == copied.Position());
			Assert::IsTrue(size == copied.Size());

			auto moved = PonyMath::Shape::Box<float>();
			moved = std::move(copied);
			Assert::IsTrue(position == moved.Position());
			Assert::IsTrue(size == moved.Size());
		}

		TEST_METHOD(EqualityTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float width = -4;
			constexpr float height = 14;
			constexpr float depth = -2;
			const auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			auto another = box;
			Assert::IsTrue(box == another);

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = another.Position()[i];
				another.Position()[i] = std::nextafter(was, 0.f);
				Assert::IsFalse(box == another);
				another.Position()[i] += 1.f;
				Assert::IsFalse(box == another);
				another.Position()[i] = was;
			}

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = another.Size(i);
				another.Size(i, std::nextafter(was, 0.f));
				Assert::IsFalse(box == another);
				another.Size(i, was + 1.f);
				Assert::IsFalse(box == another);
				another.Size(i, was);
			}
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float x = 7;
			constexpr float y = -8;
			constexpr float z = -12;
			constexpr float width = -4;
			constexpr float height = 14;
			constexpr float depth = -2;
			const auto box = PonyMath::Shape::Box<float>(x, y, z, width, height, depth);
			auto another = box;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(box, another));

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = another.Position()[i];
				another.Position()[i] = std::nextafter(was, 0.f);
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(box, another));
				another.Position()[i] += 1.f;
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(box, another));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(box, another, 50.f));
				another.Position()[i] = was;
			}

			for (std::size_t i = 0; i < 3; ++i)
			{
				const float was = another.Size(i);
				another.Size(i, std::nextafter(was, 0.f));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(box, another));
				another.Size(i, was + 1.f);
				Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(box, another));
				Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(box, another, 50.f));
				another.Size(i, was);
			}
		}

		static constexpr PonyMath::Shape::Box<float> BoxConstexpr()
		{
			auto box = PonyMath::Shape::Box<float>(3.f, 5.f, -7.f, 42.f, 34.f, 69.f);
			auto moved = std::move(box);

			const auto position = moved.Position();
			const auto size = moved.Size();

			moved.MinX(3.f);
			moved.MinY(-4.f);
			moved.MinZ(10.f);
			moved.Min(0, 9.f);
			moved.Min(size);

			moved.MaxX(3.f);
			moved.MaxY(-4.f);
			moved.MaxZ(10.f);
			moved.Max(0, 9.f);
			moved.Max(position);

			moved.Width<false>(2.f);
			moved.Width<true>(3.f);
			moved.Height<false>(4.f);
			moved.Height<true>(1.f);
			moved.Depth<false>(11.f);
			moved.Depth<true>(12.f);
			moved.Size<false>(1, 1.f);
			moved.Size<true>(2, 4.f);

			[[maybe_unused]] const auto center = moved.Center();

			auto copiedBox = PonyMath::Shape::Box<float>();
			copiedBox = moved;

			auto movedBox = PonyMath::Shape::Box<float>();
			movedBox = std::move(copiedBox);

			return movedBox;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultBox = PonyMath::Shape::Box<float>();
			[[maybe_unused]] constexpr auto box = PonyMath::Shape::Box<float>(3.f, 5.f, -7.f, 42.f, 34.f, 69.f);
			[[maybe_unused]] constexpr auto vectorBox = PonyMath::Shape::Box(PonyMath::Core::Vector3<float>(1.f, 0.f, -8.f), PonyMath::Core::Vector3<float>(-9.f, 10.f, 1.f));
			[[maybe_unused]] constexpr auto copied = box;
			[[maybe_unused]] constexpr auto moved = BoxConstexpr();

			[[maybe_unused]] constexpr auto position = box.Position();
			[[maybe_unused]] constexpr auto size = box.Size();

			[[maybe_unused]] constexpr float minX = box.MinX();
			[[maybe_unused]] constexpr float minY = box.MinY();
			[[maybe_unused]] constexpr float minZ = box.MinZ();
			[[maybe_unused]] constexpr float min = box.Min(1);
			[[maybe_unused]] constexpr auto minV = box.Min();

			[[maybe_unused]] constexpr float maxX = box.MaxX();
			[[maybe_unused]] constexpr float maxY = box.MaxY();
			[[maybe_unused]] constexpr float maxZ = box.MaxZ();
			[[maybe_unused]] constexpr float max = box.Max(1);
			[[maybe_unused]] constexpr auto maxV = box.Max();

			[[maybe_unused]] constexpr float width = box.Width();
			[[maybe_unused]] constexpr float height = box.Height();
			[[maybe_unused]] constexpr float depth = box.Depth();
			[[maybe_unused]] constexpr float sizeS = box.Size(2);

			[[maybe_unused]] constexpr auto center = box.Center();

			[[maybe_unused]] constexpr auto leftBottomNear = box.LeftBottomNear();
			[[maybe_unused]] constexpr auto rightBottomNear = box.RightBottomNear();
			[[maybe_unused]] constexpr auto leftTopNear = box.LeftTopNear();
			[[maybe_unused]] constexpr auto rightTopNear = box.RightTopNear();
			[[maybe_unused]] constexpr auto leftBottomFar = box.LeftBottomFar();
			[[maybe_unused]] constexpr auto rightBottomFar = box.RightBottomFar();
			[[maybe_unused]] constexpr auto leftTopFar = box.LeftTopFar();
			[[maybe_unused]] constexpr auto rightTopFar = box.RightTopFar();
			[[maybe_unused]] constexpr auto corner = box.Corner(2);
			[[maybe_unused]] constexpr auto corners = box.Corners();

			[[maybe_unused]] constexpr float area = box.Area();
			[[maybe_unused]] constexpr float volume = box.Volume();

			[[maybe_unused]] constexpr bool contains = box.Contains(PonyMath::Core::Vector3<float>(-3.f, 2.f, 5.f));
			[[maybe_unused]] constexpr auto closest = moved.ClosestPoint(PonyMath::Core::Vector3<float>(1.f, 2.f, 3.f));

			[[maybe_unused]] constexpr auto normalizedV = box.Normalize(PonyMath::Core::Vector3<float>(-3.f, 2.f, 5.f));
			[[maybe_unused]] constexpr auto unnormalizedV = box.Unnormalize(normalizedV);
			[[maybe_unused]] constexpr auto normalizedB = box.Normalize(copied);
			[[maybe_unused]] constexpr auto unnormalizedB = box.Unnormalize(normalizedB);

			[[maybe_unused]] constexpr auto cast = static_cast<PonyMath::Shape::Box<double>>(box);

			[[maybe_unused]] constexpr bool equal = box == defaultBox;
			[[maybe_unused]] constexpr bool notEqual = box != defaultBox;

			[[maybe_unused]] constexpr bool areAlmostEqual = PonyMath::Shape::AreAlmostEqual(box, defaultBox);
		}
	};
}
