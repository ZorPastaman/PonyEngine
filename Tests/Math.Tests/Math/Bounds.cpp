/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

import std;

import PonyEngine.Math;

TEST_CASE("Bounding box to ball", "[Math][Bounds]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	const auto sphere = PonyEngine::Math::BoundingBall(cuboid);
	REQUIRE(sphere.Center() == center);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(sphere.Radius(), 7.f, 0.001f));
	REQUIRE(sphere.Contains(center));
	REQUIRE(sphere.Contains(center + extents));
	REQUIRE(sphere.Contains(center - extents));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::BoundingBall(PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f)));
	};
#endif
}

TEST_CASE("Bounding oriented box to ball", "[Math][Bounds]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(3.f, -2.f, 1.1f));
	const auto cuboid = PonyEngine::Math::OrientedCuboid<float>(center, extents, axes);
	const auto sphere = PonyEngine::Math::BoundingBall(cuboid);
	REQUIRE(sphere.Center() == center);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(sphere.Radius(), 7.f, 0.001f));
	REQUIRE(sphere.Contains(center));
	REQUIRE(sphere.Contains(center + extents));
	REQUIRE(sphere.Contains(center - extents));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::BoundingBall(PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f)));
	};
#endif
}

TEST_CASE("Bounding ball to box", "[Math][Bounds]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto radius = 4.f;
	constexpr auto sphere = PonyEngine::Math::Sphere<float>(center, radius);
	constexpr auto cuboid = PonyEngine::Math::AxisAlignedBoundingBox(sphere);
	STATIC_REQUIRE(cuboid.Center() == center);
	STATIC_REQUIRE(cuboid.Extents() == PonyEngine::Math::Vector3<float>(radius));
	STATIC_REQUIRE(cuboid.Contains(center));
	STATIC_REQUIRE(cuboid.Contains(center + PonyEngine::Math::Vector3<float>(radius)));
	STATIC_REQUIRE(cuboid.Contains(center - PonyEngine::Math::Vector3<float>(radius)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AxisAlignedBoundingBox(PonyEngine::Math::Sphere<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), 4.f));
	};
#endif
}

TEST_CASE("Bounding oriented box to box", "[Math][Bounds]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(3.f, -2.f, 1.1f));
	const auto cuboid = PonyEngine::Math::OrientedCuboid<float>(center, extents, axes);
	const auto aabb = PonyEngine::Math::AxisAlignedBoundingBox(cuboid);
	REQUIRE(aabb.Center() == center);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(aabb.Extents(), PonyEngine::Math::Vector3<float>(6.936f, 4.392f, 5.226f), 0.001f));
	REQUIRE(aabb.Contains(center));
	for (std::size_t i = 0; i < PonyEngine::Math::OrientedCuboid<float>::CornerCount; ++i)
	{
		REQUIRE(aabb.Contains(cuboid.Corner(i)));
	}

	constexpr auto cuboid1 = PonyEngine::Math::OrientedCuboid<float>(center, extents);
	constexpr auto aabb1 = PonyEngine::Math::AxisAlignedBoundingBox(cuboid1);
	STATIC_REQUIRE(aabb1.Center() == center);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(aabb1.Extents(), extents));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AxisAlignedBoundingBox(PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f)));
	};
#endif
}

TEST_CASE("Bounding box to oriented box with rs", "[Math][Bounds]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(3.f, -2.f, -1.1f));
	const auto orientedBox = PonyEngine::Math::OrientedBoundingBox(cuboid, axes);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(orientedBox.Center(), axes * center));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(orientedBox.Extents(), extents));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(orientedBox.Axes(), axes));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		PonyEngine::Math::OrientedBoundingBox(PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f)), axes);
	};
#endif
}

TEST_CASE("Bounding box to oriented box with compact trs", "[Math][Bounds]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	constexpr auto translation = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto rotation = PonyEngine::Math::Vector3<float>(3.f, -2.f, -1.1f);
	constexpr auto scaling = PonyEngine::Math::Vector3<float>(1.f, 2.f, 5.f);
	const auto axes = PonyEngine::Math::TrsMatrixCompact(translation, rotation, scaling);
	const auto orientedBox = PonyEngine::Math::OrientedBoundingBox(cuboid, axes);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(orientedBox.Center(), PonyEngine::Math::TransformPoint(axes, center)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(orientedBox.Extents(), PonyEngine::Math::Vector3<float>(3.f, 4.f, 30.f)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(orientedBox.Axes(), PonyEngine::Math::ExtractRotationMatrixFromTrs(axes)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		PonyEngine::Math::OrientedBoundingBox(PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f)), axes);
	};
#endif
}

TEST_CASE("Bounding box to oriented box with trs", "[Math][Bounds]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	constexpr auto translation = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto rotation = PonyEngine::Math::Vector3<float>(3.f, -2.f, -1.1f);
	constexpr auto scaling = PonyEngine::Math::Vector3<float>(1.f, 2.f, 5.f);
	const auto axes = PonyEngine::Math::TrsMatrix(translation, rotation, scaling);
	const auto orientedBox = PonyEngine::Math::OrientedBoundingBox(cuboid, axes);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(orientedBox.Center(), PonyEngine::Math::TransformPoint(axes, center)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(orientedBox.Extents(), PonyEngine::Math::Vector3<float>(3.f, 4.f, 30.f)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(orientedBox.Axes(), PonyEngine::Math::ExtractRotationMatrixFromTrs(axes)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		PonyEngine::Math::OrientedBoundingBox(PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f)), axes);
	};
#endif
}
