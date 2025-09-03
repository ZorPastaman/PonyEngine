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

TEST_CASE("Line-line intersection. Collinear.", "[Math][FlatIntersections]")
{
	const auto normal = PonyEngine::Math::Vector2<float>(-1.f, 2.f).Normalized();
	constexpr float distance = 4.f;
	const auto line = PonyEngine::Math::Line<float>(normal, distance);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(line, line));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(line, line).has_value());

	constexpr float distance1 = 1.f;
	const auto line1 = PonyEngine::Math::Line<float>(normal, distance1);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(line, line1));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(line, line1).has_value());

	const auto line2 = line1.Flipped();
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(line1, line2));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(line1, line2).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(line, line1);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(line, line1);
	};
#endif
}

TEST_CASE("Line-line intersection. Hit.", "[Math][FlatIntersections]")
{
	const auto normal = PonyEngine::Math::Vector2<float>(-1.f, 2.f).Normalized();
	constexpr float distance = 4.f;
	const auto line = PonyEngine::Math::Line<float>(normal, distance);
	const auto normal1 = PonyEngine::Math::Vector2<float>(2.f, 1.f).Normalized();
	constexpr float distance1 = 1.f;
	const auto line1 = PonyEngine::Math::Line<float>(normal1, distance1);
	REQUIRE(PonyEngine::Math::AreIntersecting(line, line1));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint(line, line1).value(), PonyEngine::Math::Vector2<float>(0.894f, -4.025f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(line, line1);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(line, line1);
	};
#endif
}

TEST_CASE("Plane-plane intersection. Collinear.", "[Math][FlatIntersections]")
{
	const auto normal = PonyEngine::Math::Vector3<float>(-1.f, 2.f, 1.f).Normalized();
	constexpr float distance = 4.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(plane, plane));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionRay(plane, plane).has_value());

	constexpr float distance1 = 1.f;
	const auto plane1 = PonyEngine::Math::Plane<float>(normal, distance1);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(plane, plane1));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionRay(plane, plane1).has_value());

	const auto plane2 = plane1.Flipped();
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(plane1, plane2));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionRay(plane1, plane2).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Ray")
	{
		return PonyEngine::Math::IntersectionRay(plane, plane1);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(plane, plane1);
	};
#endif
}

TEST_CASE("Plane-plane intersection. Hit.", "[Math][FlatIntersections]")
{
	const auto normal = PonyEngine::Math::Vector3<float>(-1.f, 2.f, 1.f).Normalized();
	constexpr float distance = 4.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	const auto normal1 = PonyEngine::Math::Vector3<float>(2.f, 1.f, -1.f).Normalized();
	constexpr float distance1 = 1.f;
	const auto plane1 = PonyEngine::Math::Plane<float>(normal1, distance1);
	REQUIRE(PonyEngine::Math::AreIntersecting(plane, plane1));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionRay(plane, plane1).value(), PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(0.35f, -4.199f, -1.05f), PonyEngine::Math::Vector3<float>(-0.507f, 0.169f, -0.845f)), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Ray")
	{
		return PonyEngine::Math::IntersectionRay(plane, plane1);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(plane, plane1);
	};
#endif
}

TEST_CASE("Flat-ball intersection. Missing.", "[Math][FlatIntersections]")
{
	const auto normal = PonyEngine::Math::Vector3<float>(-1.f, 2.f, 1.f).Normalized();
	constexpr float distance = 4.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	constexpr auto center = PonyEngine::Math::Vector3<float>(-4.f, 6.f, -2.f);
	constexpr auto radius = 3.f;
	constexpr auto ball = PonyEngine::Math::Ball<float, 3>(center, radius);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(plane, ball));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(plane, ball);
	};
#endif
}

TEST_CASE("Flat-ball intersection. Hit.", "[Math][FlatIntersections]")
{
	const auto normal = PonyEngine::Math::Vector3<float>(-1.f, 2.f, 1.f).Normalized();
	constexpr float distance = 4.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto radius = 3.f;
	constexpr auto ball = PonyEngine::Math::Ball<float, 3>(center, radius);
	REQUIRE(PonyEngine::Math::AreIntersecting(plane, ball));
	REQUIRE(PonyEngine::Math::AreIntersecting(ball, plane));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(plane, ball);
	};
#endif
}

TEST_CASE("Flat-box intersection. Missing.", "[Math][FlatIntersections]")
{
	const auto normal = PonyEngine::Math::Vector3<float>(-1.f, 2.f, 1.f).Normalized();
	constexpr float distance = 4.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	constexpr auto center = PonyEngine::Math::Vector3<float>(-4.f, 6.f, -2.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(1.f, 2.f, 3.f);
	constexpr auto box = PonyEngine::Math::Cuboid<float>(center, extents);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(plane, box));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(plane, box);
	};
#endif
}

TEST_CASE("Flat-box intersection. Hit.", "[Math][FlatIntersections]")
{
	const auto normal = PonyEngine::Math::Vector3<float>(-1.f, 2.f, 1.f).Normalized();
	constexpr float distance = 4.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(1.f, 2.f, 3.f);
	constexpr auto box = PonyEngine::Math::Cuboid<float>(center, extents);
	REQUIRE(PonyEngine::Math::AreIntersecting(plane, box));
	REQUIRE(PonyEngine::Math::AreIntersecting(box, plane));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(plane, box);
	};
#endif
}

TEST_CASE("Flat-oriented box intersection. Missing.", "[Math][FlatIntersections]")
{
	const auto normal = PonyEngine::Math::Vector3<float>(-1.f, 2.f, 1.f).Normalized();
	constexpr float distance = 4.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	constexpr auto center = PonyEngine::Math::Vector3<float>(-4.f, 6.f, -2.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(1.f, 2.f, 3.f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(3.f, -2.f, -1.f));
	const auto box = PonyEngine::Math::OrientedCuboid<float>(center, extents, axes);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(plane, box));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(plane, box);
	};
#endif
}

TEST_CASE("Flat-oriented box intersection. Hit.", "[Math][FlatIntersections]")
{
	const auto normal = PonyEngine::Math::Vector3<float>(-1.f, 2.f, 1.f).Normalized();
	constexpr float distance = 4.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(1.f, 2.f, 3.f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(3.f, -2.f, -1.f));
	const auto box = PonyEngine::Math::OrientedCuboid<float>(center, extents, axes);
	REQUIRE(PonyEngine::Math::AreIntersecting(plane, box));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(plane, box);
	};
#endif
}
