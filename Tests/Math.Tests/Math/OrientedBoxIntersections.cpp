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

TEST_CASE("Oriented box-oriented box intersection. Missing on the first step.", "[Math][BoxIntersections]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(2.f, -3.f, 5.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(3.f, 2.f, 4.f);
	constexpr auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(15.f, -3.f, 5.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(2.f, 3.f, 1.f);
	constexpr auto box1 = PonyEngine::Math::OrientedCuboid<float>(center1, extents1);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(box0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreIntersecting(box0, box1);
	};
#endif
}

TEST_CASE("Oriented box-oriented box intersection. Missing on the second step.", "[Math][BoxIntersections]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-4.f, 7.f, 2.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 3.f, 5.f);
	const auto axes0 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.1f, 0.1f, 0.05f));
	const auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0, axes0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(0.f, 11.f, 2.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(1.f, 2.f, 2.f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(0.f, 0.f, 0.7854f));
	const auto box1 = PonyEngine::Math::OrientedCuboid<float>(center1, extents1, axes);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(box0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreIntersecting(box0, box1);
	};
#endif
}

TEST_CASE("Oriented box-oriented box intersection. Missing on the third step.", "[Math][BoxIntersections]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(4.f, 2.f, 1.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 4.f, 3.f);
	const auto axes0 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.1f, 0.1f, 0.05f));
	const auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0, axes0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(8.11f, 2.49f, -3.15f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(0.f, 45.f, 45.f) * PonyEngine::Math::DegToRad<float>);
	const auto box1 = PonyEngine::Math::OrientedCuboid<float>(center1, extents1, axes);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(box0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreIntersecting(box0, box1);
	};
#endif
}

TEST_CASE("Oriented box-oriented box intersection. Hit.", "[Math][BoxIntersections]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-4.f, 2.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(3.f, 5.f, 4.f);
	const auto axes0 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.1f, 0.1f, 0.05f));
	const auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0, axes0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-5.f, -2.f, 7.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(2.f, 4.f, 5.f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(1.f, -2.f, -3.f));
	const auto box1 = PonyEngine::Math::OrientedCuboid<float>(center1, extents1, axes);
	REQUIRE(PonyEngine::Math::AreIntersecting(box0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreIntersecting(box0, box1);
	};
#endif
}

