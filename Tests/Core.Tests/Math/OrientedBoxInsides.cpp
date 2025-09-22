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

TEST_CASE("Oriented box-oriented box inside. Outside.", "[Math][OrientedBoxInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	constexpr auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(10.f, -5.f, -7.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(4.f, 3.f, 6.f);
	constexpr auto box1 = PonyEngine::Math::OrientedCuboid<float>(center1, extents1);
	REQUIRE_FALSE(PonyEngine::Math::IsInside(box0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(box0, box1);
	};
#endif
}

TEST_CASE("Oriented box-oriented box inside. Intersecting.", "[Math][OrientedBoxInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	const auto axes0 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.4f, 0.3f, 0.2f));
	const auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0, axes0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(0.f, 3.f, -1.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(4.f, 3.f, 6.f);
	const auto axes1 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.1f, 0.5f, 0.7f));
	const auto box1 = PonyEngine::Math::OrientedCuboid<float>(center1, extents1, axes1);
	REQUIRE_FALSE(PonyEngine::Math::IsInside(box0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(box0, box1);
	};
#endif
}

TEST_CASE("Oriented box-oriented box inside. Inside.", "[Math][OrientedBoxInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	const auto axes0 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.4f, 0.3f, 0.2f));
	const auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0, axes0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(4.f, 3.f, 6.f);
	const auto axes1 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.1f, 0.5f, 0.7f));
	const auto box1 = PonyEngine::Math::OrientedCuboid<float>(center1, extents1, axes1);
	REQUIRE(PonyEngine::Math::IsInside(box0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(box0, box1);
	};
#endif
}

TEST_CASE("Oriented box-oriented box inside. Small.", "[Math][OrientedBoxInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	const auto axes0 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.4f, 0.3f, 0.2f));
	const auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0, axes0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-1.f, 4.f, 4.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(2.f, 3.f, 6.f);
	const auto axes1 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.1f, 0.5f, 0.7f));
	const auto box1 = PonyEngine::Math::OrientedCuboid<float>(center1, extents1, axes1);
	REQUIRE_FALSE(PonyEngine::Math::IsInside(box0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(box0, box1);
	};
#endif
}

TEST_CASE("Oriented box-ball inside. Outside.", "[Math][OrientedBoxInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	constexpr auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(10.f, -5.f, -7.f);
	constexpr auto radius1 = 5.f;
	constexpr auto ball = PonyEngine::Math::Sphere<float>(center1, radius1);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInside(box0, ball));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(box0, ball);
	};
#endif
}

TEST_CASE("Oriented box-ball inside. Intersecting.", "[Math][OrientedBoxInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	const auto axes0 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.4f, 0.3f, 0.2f));
	const auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0, axes0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-1.f, 4.f, 4.f);
	constexpr auto radius1 = 5.f;
	constexpr auto ball = PonyEngine::Math::Sphere<float>(center1, radius1);
	REQUIRE_FALSE(PonyEngine::Math::IsInside(box0, ball));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(box0, ball);
	};
#endif
}

TEST_CASE("Oriented box-ball inside. Inside.", "[Math][OrientedBoxInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	const auto axes0 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.4f, 0.3f, 0.2f));
	const auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0, axes0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-2.f, 4.f, 3.f);
	constexpr auto radius1 = 5.f;
	constexpr auto ball = PonyEngine::Math::Sphere<float>(center1, radius1);
	REQUIRE(PonyEngine::Math::IsInside(box0, ball));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(box0, ball);
	};
#endif
}

TEST_CASE("Oriented box-ball inside. Small.", "[Math][OrientedBoxInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	const auto axes0 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.4f, 0.3f, 0.2f));
	const auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0, axes0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-2.f, 4.f, 3.f);
	constexpr auto radius1 = 1.f;
	constexpr auto ball = PonyEngine::Math::Sphere<float>(center1, radius1);
	REQUIRE_FALSE(PonyEngine::Math::IsInside(box0, ball));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(box0, ball);
	};
#endif
}

TEST_CASE("Oriented box-box inside. Outside.", "[Math][OrientedBoxInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	constexpr auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(10.f, -5.f, -7.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(4.f, 3.f, 6.f);
	constexpr auto box1 = PonyEngine::Math::Cuboid<float>(center1, extents1);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInside(box0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(box0, box1);
	};
#endif
}

TEST_CASE("Oriented box-box inside. Intersecting.", "[Math][OrientedBoxInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	const auto axes0 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.4f, 0.3f, 0.2f));
	const auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0, axes0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(0.f, 3.f, -1.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(4.f, 3.f, 6.f);
	constexpr auto box1 = PonyEngine::Math::Cuboid<float>(center1, extents1);
	REQUIRE_FALSE(PonyEngine::Math::IsInside(box0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(box0, box1);
	};
#endif
}

TEST_CASE("Oriented box-box inside. Inside.", "[Math][OrientedBoxInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	const auto axes0 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.4f, 0.3f, 0.2f));
	const auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0, axes0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-1.f, 4.f, 4.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(14.f, 13.f, 16.f);
	constexpr auto box1 = PonyEngine::Math::Cuboid<float>(center1, extents1);
	REQUIRE(PonyEngine::Math::IsInside(box0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(box0, box1);
	};
#endif
}

TEST_CASE("Oriented box-box inside. Small.", "[Math][OrientedBoxInsides]")
{
	constexpr auto center0 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 3.f);
	constexpr auto extents0 = PonyEngine::Math::Vector3<float>(2.f, 1.f, 3.f);
	const auto axes0 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(-0.4f, 0.3f, 0.2f));
	const auto box0 = PonyEngine::Math::OrientedCuboid<float>(center0, extents0, axes0);
	constexpr auto center1 = PonyEngine::Math::Vector3<float>(-1.f, 4.f, 4.f);
	constexpr auto extents1 = PonyEngine::Math::Vector3<float>(2.f, 3.f, 6.f);
	constexpr auto box1 = PonyEngine::Math::Cuboid<float>(center1, extents1);
	REQUIRE_FALSE(PonyEngine::Math::IsInside(box0, box1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::IsInside(box0, box1);
	};
#endif
}
