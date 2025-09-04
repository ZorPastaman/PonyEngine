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

TEST_CASE("Ball-ball intersection. Missing.", "[Math][BallIntersections]")
{
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(2.f, 4.f, -3.f);
	constexpr auto radius1 = 1.5f;
	constexpr auto ball1 = PonyEngine::Math::Sphere<float>(center1, radius1);
	constexpr auto center2 = PonyEngine::Math::Vector3<float>(5.f, 7.f, 3.f);
	constexpr auto radius2 = 2.f;
	constexpr auto ball2 = PonyEngine::Math::Sphere<float>(center2, radius2);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ball1, ball2));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreIntersecting(ball1, ball2);
	};
#endif
}

TEST_CASE("Ball-ball intersection. Hit.", "[Math][BallIntersections]")
{
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(2.f, 4.f, -3.f);
	constexpr auto radius1 = 1.5f;
	constexpr auto ball1 = PonyEngine::Math::Sphere<float>(center1, radius1);
	constexpr auto center2 = PonyEngine::Math::Vector3<float>(3.f, 3.f, -3.f);
	constexpr auto radius2 = 2.f;
	constexpr auto ball2 = PonyEngine::Math::Sphere<float>(center2, radius2);
	REQUIRE(PonyEngine::Math::AreIntersecting(ball1, ball2));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreIntersecting(ball1, ball2);
	};
#endif
}

TEST_CASE("Ball-box intersection. Missing.", "[Math][BallIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(2.f, 4.f, -3.f);
	constexpr float radius = 2.f;
	constexpr auto ball = PonyEngine::Math::Sphere<float>(center, radius);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(8.f, 10.f, -9.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 1.f);
	constexpr auto box = PonyEngine::Math::Cuboid<float>(center1, extents);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ball, box));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreIntersecting(ball, box);
	};
#endif
}

TEST_CASE("Ball-box intersection. Hit.", "[Math][BallIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(2.f, 4.f, -3.f);
	constexpr float radius = 2.f;
	constexpr auto ball = PonyEngine::Math::Sphere<float>(center, radius);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(3.f, 5.f, -4.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 1.f);
	constexpr auto box = PonyEngine::Math::Cuboid<float>(center1, extents);
	REQUIRE(PonyEngine::Math::AreIntersecting(ball, box));
	REQUIRE(PonyEngine::Math::AreIntersecting(box, ball));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreIntersecting(ball, box);
	};
#endif
}

TEST_CASE("Ball-oriented box intersection. Missing.", "[Math][BallIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(2.f, 4.f, -3.f);
	constexpr float radius = 2.f;
	constexpr auto ball = PonyEngine::Math::Sphere<float>(center, radius);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(8.f, 10.f, -9.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 1.f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(2.f, 3.f, -1.f));
	const auto box = PonyEngine::Math::OrientedCuboid<float>(center1, extents, axes);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ball, box));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreIntersecting(ball, box);
	};
#endif
}

TEST_CASE("Ball-oriented box intersection. Hit.", "[Math][BallIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(2.f, 4.f, -3.f);
	constexpr float radius = 2.f;
	constexpr auto ball = PonyEngine::Math::Sphere<float>(center, radius);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(3.f, 5.f, -4.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 1.f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(2.f, 3.f, -1.f));
	const auto box = PonyEngine::Math::OrientedCuboid<float>(center1, extents, axes);
	REQUIRE(PonyEngine::Math::AreIntersecting(ball, box));
	REQUIRE(PonyEngine::Math::AreIntersecting(box, ball));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreIntersecting(ball, box);
	};
#endif
}
