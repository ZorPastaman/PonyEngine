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

TEST_CASE("Ball-ball inside. Outside.", "[Math][BallInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr float radius0 = 2.f;
	constexpr auto ball0 = PonyEngine::Math::Sphere<float>(center0, radius0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-10.f, 3.f, -2.f);
	constexpr float radius1 = 4.f;
	constexpr auto ball1 = PonyEngine::Math::Sphere<float>(center1, radius1);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInside(ball0, ball1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(ball0, ball1);
	};
#endif
}

TEST_CASE("Ball-ball inside. Intersecting.", "[Math][BallInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr float radius0 = 2.f;
	constexpr auto ball0 = PonyEngine::Math::Sphere<float>(center0, radius0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-1.f, 3.f, -1.f);
	constexpr float radius1 = 4.f;
	constexpr auto ball1 = PonyEngine::Math::Sphere<float>(center1, radius1);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInside(ball0, ball1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(ball0, ball1);
	};
#endif
}

TEST_CASE("Ball-ball inside. Inside.", "[Math][BallInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr float radius0 = 2.f;
	constexpr auto ball0 = PonyEngine::Math::Sphere<float>(center0, radius0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-2.f, 4.f, 4.f);
	constexpr float radius1 = 4.f;
	constexpr auto ball1 = PonyEngine::Math::Sphere<float>(center1, radius1);
	STATIC_REQUIRE(PonyEngine::Math::IsInside(ball0, ball1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(ball0, ball1);
	};
#endif
}

TEST_CASE("Ball-ball inside. Small.", "[Math][BallInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr float radius0 = 2.f;
	constexpr auto ball0 = PonyEngine::Math::Sphere<float>(center0, radius0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-2.f, 4.f, 4.f);
	constexpr float radius1 = 1.f;
	constexpr auto ball1 = PonyEngine::Math::Sphere<float>(center1, radius1);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInside(ball0, ball1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(ball0, ball1);
	};
#endif
}

TEST_CASE("Ball-box inside. Outside.", "[Math][BallInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr float radius0 = 2.f;
	constexpr auto ball0 = PonyEngine::Math::Sphere<float>(center0, radius0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-10.f, 3.f, -2.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(4.f, 5.f, 4.5f);
	constexpr auto box1 = PonyEngine::Math::Cuboid<float>(center1, extents1);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInside(ball0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(ball0, box1);
	};
#endif
}

TEST_CASE("Ball-box inside. Intersecting.", "[Math][BallInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr float radius0 = 2.f;
	constexpr auto ball0 = PonyEngine::Math::Sphere<float>(center0, radius0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-5.f, 3.f, 6.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(4.f, 5.f, 4.5f);
	constexpr auto box1 = PonyEngine::Math::Cuboid<float>(center1, extents1);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInside(ball0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(ball0, box1);
	};
#endif
}

TEST_CASE("Ball-box inside. Inside.", "[Math][BallInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr float radius0 = 2.f;
	constexpr auto ball0 = PonyEngine::Math::Sphere<float>(center0, radius0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-5.f, 3.f, 3.5f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(4.f, 5.f, 4.5f);
	constexpr auto box1 = PonyEngine::Math::Cuboid<float>(center1, extents1);
	STATIC_REQUIRE(PonyEngine::Math::IsInside(ball0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(ball0, box1);
	};
#endif
}

TEST_CASE("Ball-box inside. Small.", "[Math][BallInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr float radius0 = 2.f;
	constexpr auto ball0 = PonyEngine::Math::Sphere<float>(center0, radius0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-5.f, 3.f, 3.5f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(2.f, 2.f, 1.f);
	constexpr auto box1 = PonyEngine::Math::Cuboid<float>(center1, extents1);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInside(ball0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(ball0, box1);
	};
#endif
}

TEST_CASE("Ball-oriented box inside. Outside.", "[Math][BallInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr float radius0 = 2.f;
	constexpr auto ball0 = PonyEngine::Math::Sphere<float>(center0, radius0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-10.f, 3.f, -2.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(4.f, 5.f, 4.5f);
	constexpr auto box1 = PonyEngine::Math::OrientedCuboid<float>(center1, extents1);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInside(ball0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(ball0, box1);
	};
#endif
}

TEST_CASE("Ball-oriented box inside. Intersecting.", "[Math][BallInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr float radius0 = 2.f;
	constexpr auto ball0 = PonyEngine::Math::Sphere<float>(center0, radius0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-5.f, 3.f, 6.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(4.f, 5.f, 4.5f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-1.f, -2.f, 1.f));
	const auto box1 = PonyEngine::Math::OrientedCuboid<float>(center1, extents1, axes);
	REQUIRE_FALSE(PonyEngine::Math::IsInside(ball0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(ball0, box1);
	};
#endif
}

TEST_CASE("Ball-oriented box inside. Inside.", "[Math][BallInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr float radius0 = 2.f;
	constexpr auto ball0 = PonyEngine::Math::Sphere<float>(center0, radius0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-5.f, 3.f, 3.5f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(4.f, 5.f, 4.5f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-1.f, -2.f, 1.f));
	const auto box1 = PonyEngine::Math::OrientedCuboid<float>(center1, extents1, axes);
	REQUIRE(PonyEngine::Math::IsInside(ball0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(ball0, box1);
	};
#endif
}

TEST_CASE("Ball-oriented box inside. Small.", "[Math][BallInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr float radius0 = 2.f;
	constexpr auto ball0 = PonyEngine::Math::Sphere<float>(center0, radius0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-5.f, 3.f, 3.5f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(2.f, 2.f, 1.f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-1.f, -2.f, 1.f));
	const auto box1 = PonyEngine::Math::OrientedCuboid<float>(center1, extents1, axes);
	REQUIRE_FALSE(PonyEngine::Math::IsInside(ball0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(ball0, box1);
	};
#endif
}
