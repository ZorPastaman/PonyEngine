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

TEST_CASE("Bounding ball to box", "[Math][Bounds]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto radius = 4.f;
	constexpr auto sphere = PonyEngine::Math::Sphere<float>(center, radius);
	constexpr auto cuboid = PonyEngine::Math::BoundingBox(sphere);
	STATIC_REQUIRE(cuboid.Center() == center);
	STATIC_REQUIRE(cuboid.Extents() == PonyEngine::Math::Vector3<float>(radius));
	STATIC_REQUIRE(cuboid.Contains(center));
	STATIC_REQUIRE(cuboid.Contains(center + PonyEngine::Math::Vector3<float>(radius)));
	STATIC_REQUIRE(cuboid.Contains(center - PonyEngine::Math::Vector3<float>(radius)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::BoundingBox(PonyEngine::Math::Sphere<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), 4.f));
	};
#endif
}
