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

TEST_CASE("Ray-ray intersection. Collinear.", "[Math][RayIntersections]")
{
	constexpr auto origin = PonyEngine::Math::Vector2<float>(1.f, -3.f);
	const auto direction = PonyEngine::Math::Vector2<float>(2.f, 1.f).Normalized();
	const auto ray = PonyEngine::Math::Ray2D<float>(origin, direction);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray, ray));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray, ray).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray, ray).has_value());

	const auto origin1 = ray.Unnormalize(-4.f);
	const auto ray1 = PonyEngine::Math::Ray2D<float>(origin1, direction);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray, ray1));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray, ray1).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray, ray1).has_value());

	const auto ray2 = ray.Flipped();
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray1, ray2));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray1, ray2).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray1, ray2).has_value());

	const auto ray3 = PonyEngine::Math::Ray2D<float>(origin + PonyEngine::Math::Vector2<float>(-2.f, 4.f), direction);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray3, ray1));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray3, ray1).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray3, ray1).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, ray1);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, ray1);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, ray1);
	};
#endif
}

TEST_CASE("Ray-ray intersection. Missing.", "[Math][RayIntersections]")
{
	constexpr auto origin = PonyEngine::Math::Vector2<float>(1.f, -3.f);
	const auto direction = PonyEngine::Math::Vector2<float>(2.f, 1.f).Normalized();
	const auto ray = PonyEngine::Math::Ray2D<float>(origin, direction);
	constexpr auto origin1 = PonyEngine::Math::Vector2<float>(-1.f, 1.f);
	const auto direction1 = PonyEngine::Math::Vector2<float>(-2.f, -2.f).Normalized();
	const auto ray1 = PonyEngine::Math::Ray2D<float>(origin1, direction1);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray, ray1));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray, ray1).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray, ray1).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, ray1);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, ray1);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, ray1);
	};
#endif
}

TEST_CASE("Ray-ray intersection. Hit.", "[Math][RayIntersections]")
{
	constexpr auto origin = PonyEngine::Math::Vector2<float>(1.f, -3.f);
	const auto direction = PonyEngine::Math::Vector2<float>(2.f, 1.f).Normalized();
	const auto ray = PonyEngine::Math::Ray2D<float>(origin, direction);
	constexpr auto origin1 = PonyEngine::Math::Vector2<float>(5.f, -6.f);
	const auto direction1 = PonyEngine::Math::Vector2<float>(-2.f, 3.f).Normalized();
	const auto ray1 = PonyEngine::Math::Ray2D<float>(origin1, direction1);
	REQUIRE(PonyEngine::Math::AreIntersecting(ray, ray1));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime(ray, ray1).value(), 1.677f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint(ray, ray1).value(), ray.Unnormalize(1.677f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, ray1);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, ray1);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, ray1);
	};
#endif
}

TEST_CASE("Ray-ray intersection. Missing bounds.", "[Math][RayIntersections]")
{
	constexpr auto origin = PonyEngine::Math::Vector2<float>(1.f, -3.f);
	const auto direction = PonyEngine::Math::Vector2<float>(2.f, 1.f).Normalized();
	const auto ray = PonyEngine::Math::Ray2D<float>(origin, direction);
	constexpr auto origin1 = PonyEngine::Math::Vector2<float>(5.f, -6.f);
	const auto direction1 = PonyEngine::Math::Vector2<float>(-2.f, 3.f).Normalized();
	const auto ray1 = PonyEngine::Math::Ray2D<float>(origin1, direction1);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray, ray1, PonyEngine::Math::RayBounds<float>{.max = 1.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray, ray1, PonyEngine::Math::RayBounds<float>{.max = 1.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray, ray1, PonyEngine::Math::RayBounds<float>{.max = 1.f}).has_value());

	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray, ray1, PonyEngine::Math::RayBounds<float>{.min = 5.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray, ray1, PonyEngine::Math::RayBounds<float>{.min = 5.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray, ray1, PonyEngine::Math::RayBounds<float>{.min = 5.f}).has_value());

	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray, ray1, PonyEngine::Math::RayBounds<float>{}, PonyEngine::Math::RayBounds<float>{.max = 0.1f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray, ray1, PonyEngine::Math::RayBounds<float>{}, PonyEngine::Math::RayBounds<float>{.max = 0.1f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray, ray1, PonyEngine::Math::RayBounds<float>{}, PonyEngine::Math::RayBounds<float>{.max = 0.1f}).has_value());

	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray, ray1, PonyEngine::Math::RayBounds<float>{}, PonyEngine::Math::RayBounds<float>{.min = 100.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray, ray1, PonyEngine::Math::RayBounds<float>{}, PonyEngine::Math::RayBounds<float>{.min = 100.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray, ray1, PonyEngine::Math::RayBounds<float>{}, PonyEngine::Math::RayBounds<float>{.min = 100.f}).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, ray1, PonyEngine::Math::RayBounds<float>{.min = 0.1f, .max = 1.f}, PonyEngine::Math::RayBounds<float>{.min = 0.1f, .max = 1.f});
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, ray1, PonyEngine::Math::RayBounds<float>{.min = 0.1f, .max = 1.f}, PonyEngine::Math::RayBounds<float>{.min = 0.1f, .max = 1.f});
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, ray1, PonyEngine::Math::RayBounds<float>{.min = 0.1f, .max = 1.f}, PonyEngine::Math::RayBounds<float>{.min = 0.1f, .max = 1.f});
	};
#endif
}

TEST_CASE("Ray-ray intersection. Hit back.", "[Math][RayIntersections]")
{
	constexpr auto origin = PonyEngine::Math::Vector2<float>(1.f, -3.f);
	const auto direction = PonyEngine::Math::Vector2<float>(2.f, 1.f).Normalized();
	const auto ray = PonyEngine::Math::Ray2D<float>(origin, direction);
	constexpr auto origin1 = PonyEngine::Math::Vector2<float>(-1.f, 1.f);
	const auto direction1 = PonyEngine::Math::Vector2<float>(-2.f, -2.f).Normalized();
	const auto ray1 = PonyEngine::Math::Ray2D<float>(origin1, direction1);
	REQUIRE(PonyEngine::Math::AreIntersecting(ray, ray1, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity()}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime(ray, ray1, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity()}).value(), -13.416f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint(ray, ray1, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity()}).value(), ray.Unnormalize(-13.416f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	REQUIRE(PonyEngine::Math::AreIntersecting(ray1, ray, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity()}, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity()}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime(ray1, ray, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity()}, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity()}).value(), 14.142f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint(ray1, ray, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity()}, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity()}).value(), ray1.Unnormalize(14.142f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, ray1, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity(), .max = std::numeric_limits<float>::infinity()}, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity(), .max = std::numeric_limits<float>::infinity()});
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, ray1, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity(), .max = std::numeric_limits<float>::infinity()}, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity(), .max = std::numeric_limits<float>::infinity()});
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, ray1, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity(), .max = std::numeric_limits<float>::infinity()}, PonyEngine::Math::RayBounds<float>{.min = -std::numeric_limits<float>::infinity(), .max = std::numeric_limits<float>::infinity()});
	};
#endif
}

TEST_CASE("Ray-plane intersection. Collinear.", "[Math][RayIntersections]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(1.f, -3.f, 2.f);
	const auto direction = PonyEngine::Math::Vector3<float>(2.f, 1.f, -1.f).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	const auto normal = PonyEngine::Math::Cross(direction, PonyEngine::Math::Vector3<float>::Up()).Normalized();
	const auto plane = PonyEngine::Math::Plane<float>(normal, origin);

	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray, plane));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray, plane).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray, plane).has_value());

	const auto ray1 = PonyEngine::Math::Ray3D<float>(origin + PonyEngine::Math::Vector3<float>(-4.f, 2.f, 2.f), direction);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray1, plane));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray1, plane).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray1, plane).has_value());

	const auto ray2 = ray.Flipped();
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray2, plane));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray2, plane).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray2, plane).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray1, plane);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray1, plane);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray1, plane);
	};
#endif
}

TEST_CASE("Ray-plane intersection. Missing.", "[Math][RayIntersections]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(1.f, -3.f, 2.f);
	const auto direction = PonyEngine::Math::Vector3<float>(2.f, 1.f, -1.f).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	const auto normal = PonyEngine::Math::Vector3<float>(4.f, 5.f, 2.f).Normalized();
	const auto plane = PonyEngine::Math::Plane<float>(normal, 4.f);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray, plane));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray, plane).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray, plane).has_value());

	constexpr auto origin1 = PonyEngine::Math::Vector3<float>(-10.f, -15.f, -11.f);
	const auto direction1 = -direction;
	const auto ray1 = PonyEngine::Math::Ray3D<float>(origin1, direction1);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray1, plane));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray1, plane).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray1, plane).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray1, plane);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray1, plane);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray1, plane);
	};
#endif
}

TEST_CASE("Ray-plane intersection. Hit.", "[Math][RayIntersections]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(1.f, -3.f, 2.f);
	const auto direction = PonyEngine::Math::Vector3<float>(-2.f, -1.f, 1.f).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	const auto normal = PonyEngine::Math::Vector3<float>(4.f, 5.f, 2.f).Normalized();
	const auto plane = PonyEngine::Math::Plane<float>(normal, 4.f);
	REQUIRE(PonyEngine::Math::AreIntersecting(ray, plane));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime(ray, plane).value(), 4.416f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint(ray, plane).value(), ray.Unnormalize(4.416f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	constexpr auto origin1 = PonyEngine::Math::Vector3<float>(-10.f, -15.f, -11.f);
	const auto direction1 = -direction;
	const auto ray1 = PonyEngine::Math::Ray3D<float>(origin1, direction1);
	REQUIRE(PonyEngine::Math::AreIntersecting(ray1, plane));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime(ray1, plane).value(), 24.532f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint(ray1, plane).value(), ray1.Unnormalize(24.532f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray1, plane);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray1, plane);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray1, plane);
	};
#endif
}

TEST_CASE("Ray-plane intersection. Missing bounds.", "[Math][RayIntersections]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(1.f, -3.f, 2.f);
	const auto direction = PonyEngine::Math::Vector3<float>(-2.f, -1.f, 1.f).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	const auto normal = PonyEngine::Math::Vector3<float>(4.f, 5.f, 2.f).Normalized();
	const auto plane = PonyEngine::Math::Plane<float>(normal, 4.f);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray, plane, PonyEngine::Math::RayBounds{.max = 1.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray, plane, PonyEngine::Math::RayBounds{.max = 1.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray, plane, PonyEngine::Math::RayBounds{.max = 1.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray, plane, PonyEngine::Math::RayBounds{.min = 100.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray, plane, PonyEngine::Math::RayBounds{.min = 100.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray, plane, PonyEngine::Math::RayBounds{.min = 100.f}).has_value());

	constexpr auto origin1 = PonyEngine::Math::Vector3<float>(-10.f, -15.f, -11.f);
	const auto direction1 = -direction;
	const auto ray1 = PonyEngine::Math::Ray3D<float>(origin1, direction1);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray1, plane, PonyEngine::Math::RayBounds{.max = 1.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray1, plane, PonyEngine::Math::RayBounds{.max = 1.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray1, plane, PonyEngine::Math::RayBounds{.max = 1.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting(ray1, plane, PonyEngine::Math::RayBounds{.min = 100.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime(ray1, plane, PonyEngine::Math::RayBounds{.min = 100.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint(ray1, plane, PonyEngine::Math::RayBounds{.min = 100.f}).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray1, plane, PonyEngine::Math::RayBounds{.max = 1.f});
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray1, plane, PonyEngine::Math::RayBounds{.max = 1.f});
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray1, plane, PonyEngine::Math::RayBounds{.max = 1.f});
	};
#endif
}

TEST_CASE("Ray-plane intersection. Hit back.", "[Math][RayIntersections]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(1.f, -3.f, 2.f);
	const auto direction = PonyEngine::Math::Vector3<float>(2.f, 1.f, -1.f).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	const auto normal = PonyEngine::Math::Vector3<float>(4.f, 5.f, 2.f).Normalized();
	const auto plane = PonyEngine::Math::Plane<float>(normal, 4.f);
	REQUIRE(PonyEngine::Math::AreIntersecting(ray, plane, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime(ray, plane, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).value(), -4.416f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint(ray, plane, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).value(), ray.Unnormalize(-4.416f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	constexpr auto origin1 = PonyEngine::Math::Vector3<float>(-10.f, -15.f, -11.f);
	const auto direction1 = -direction;
	const auto ray1 = PonyEngine::Math::Ray3D<float>(origin1, direction1);
	REQUIRE(PonyEngine::Math::AreIntersecting(ray1, plane, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime(ray1, plane, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).value(), -24.532f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint(ray1, plane, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).value(), ray1.Unnormalize(-24.532f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray1, plane);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray1, plane);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray1, plane);
	};
#endif
}

TEST_CASE("Ray-ball intersection. Missing direction.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto radius = 3.f;
	constexpr auto ball = PonyEngine::Math::Ball<float, 3>(center, radius);
	constexpr auto origin = PonyEngine::Math::Vector3<float>(8.f, 3.f, -7.f);
	const auto direction = PonyEngine::Math::Vector3<float>(center + PonyEngine::Math::Vector3<float>(radius * 3.f) - origin).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, ball));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, ball));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, ball));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, ball));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, ball).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, ball).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<false>(ray, ball).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<true>(ray, ball).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, ball).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, ball).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<false>(ray, ball).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<true>(ray, ball).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, ball);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, ball);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, ball);
	};
#endif
}

TEST_CASE("Ray-ball intersection. Missing origin.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto radius = 3.f;
	constexpr auto ball = PonyEngine::Math::Ball<float, 3>(center, radius);
	constexpr auto origin = center + PonyEngine::Math::Vector3<float>(5.f);
	const auto direction = (origin - center).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, ball));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, ball));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, ball));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, ball));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, ball).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, ball).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<false>(ray, ball).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<true>(ray, ball).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, ball).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, ball).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<false>(ray, ball).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<true>(ray, ball).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, ball);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, ball);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, ball);
	};
#endif
}

TEST_CASE("Ray-ball intersection. Hit.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto radius = 3.f;
	constexpr auto ball = PonyEngine::Math::Ball<float, 3>(center, radius);
	constexpr auto origin = PonyEngine::Math::Vector3<float>(8.f, 3.f, -7.f);
	const auto direction = PonyEngine::Math::Vector3<float>(center + PonyEngine::Math::Vector3<float>::One() - origin).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);

	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, ball));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, ball));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, ball));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, ball));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTimes(ray, ball).first.value(), 10.778f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTimes(ray, ball).second.value(), 15.68f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime<false>(ray, ball).value(), 10.778f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime<true>(ray, ball).value(), 15.68f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoints(ray, ball).first.value(), ray.Unnormalize(10.778f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoints(ray, ball).second.value(), ray.Unnormalize(15.68f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint<false>(ray, ball).value(), ray.Unnormalize(10.778f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint<true>(ray, ball).value(), ray.Unnormalize(15.68f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, ball);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, ball);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, ball);
	};
#endif
}

TEST_CASE("Ray-ball intersection. Missing bounds.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto radius = 3.f;
	constexpr auto ball = PonyEngine::Math::Ball<float, 3>(center, radius);
	constexpr auto origin = PonyEngine::Math::Vector3<float>(8.f, 3.f, -7.f);
	const auto direction = PonyEngine::Math::Vector3<float>(center + PonyEngine::Math::Vector3<float>::One() - origin).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);

	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f}).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f}).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<false>(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<true>(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f}).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f}).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<false>(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<true>(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f}).has_value());

	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, ball, PonyEngine::Math::RayBounds{.min = 50.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, ball, PonyEngine::Math::RayBounds{.min = 50.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, ball, PonyEngine::Math::RayBounds{.min = 50.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, ball, PonyEngine::Math::RayBounds{.min = 50.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, ball, PonyEngine::Math::RayBounds{.min = 50.f}).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, ball, PonyEngine::Math::RayBounds{.min = 50.f}).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<false>(ray, ball, PonyEngine::Math::RayBounds{.min = 50.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<true>(ray, ball, PonyEngine::Math::RayBounds{.min = 50.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, ball, PonyEngine::Math::RayBounds{.min = 50.f}).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, ball, PonyEngine::Math::RayBounds{.min = 50.f}).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<false>(ray, ball, PonyEngine::Math::RayBounds{.min = 50.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<true>(ray, ball, PonyEngine::Math::RayBounds{.min = 50.f}).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f});
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f});
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, ball, PonyEngine::Math::RayBounds{.max = 1.f});
	};
#endif
}

TEST_CASE("Ray-ball intersection. Hit enter.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto radius = 3.f;
	constexpr auto ball = PonyEngine::Math::Ball<float, 3>(center, radius);
	constexpr auto origin = PonyEngine::Math::Vector3<float>(8.f, 3.f, -7.f);
	const auto direction = PonyEngine::Math::Vector3<float>(center + PonyEngine::Math::Vector3<float>::One() - origin).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);

	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f}));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTimes(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f}).first.value(), 10.778f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f}).second.has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime<false>(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f}).value(), 10.778f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<true>(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f}).has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoints(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f}).first.value(), ray.Unnormalize(10.778f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f}).second.has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint<false>(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f}).value(), ray.Unnormalize(10.778f), PonyEngine::Math::Tolerance{.absolute = 0.001f }));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<true>(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f}).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f});
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f});
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, ball, PonyEngine::Math::RayBounds{.max = 13.f});
	};
#endif
}

TEST_CASE("Ray-ball intersection. Hit exit.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto radius = 3.f;
	constexpr auto ball = PonyEngine::Math::Ball<float, 3>(center, radius);
	constexpr auto origin = PonyEngine::Math::Vector3<float>(8.f, 3.f, -7.f);
	const auto direction = PonyEngine::Math::Vector3<float>(center + PonyEngine::Math::Vector3<float>::One() - origin).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);

	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f}));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f}));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f}).first.has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTimes(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f}).second.value(), 15.68f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<false>(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f}).has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime<true>(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f}).value(), 15.68f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f}).first.has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoints(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f}).second.value(), ray.Unnormalize(15.68f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<false>(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f}).has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint<true>(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f}).value(), ray.Unnormalize(15.68f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f});
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f});
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, ball, PonyEngine::Math::RayBounds{.min = 13.f});
	};
#endif
}

TEST_CASE("Ray-ball intersection. Hit back.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto radius = 3.f;
	constexpr auto ball = PonyEngine::Math::Ball<float, 3>(center, radius);
	constexpr auto origin = center + PonyEngine::Math::Vector3<float>(5.f);
	const auto direction = (origin - center).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTimes(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).first.value(), -11.66f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTimes(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).second.value(), -5.66f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime<false>(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).value(), -11.66f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime<true>(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).value(), -5.66f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoints(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).first.value(), ray.Unnormalize(-11.66f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoints(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).second.value(), ray.Unnormalize(-5.66f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint<false>(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).value(), ray.Unnormalize(-11.66f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint<true>(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).value(), ray.Unnormalize(-5.66f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()});
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()});
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, ball, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()});
	};
#endif
}

TEST_CASE("Ray-box intersection. Missing direction.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 4.f, 3.5f);
	constexpr auto box = PonyEngine::Math::Box<float, 3>(center, extents);
	constexpr auto origin = PonyEngine::Math::Vector3<float>(8.f, 3.f, -7.f);
	const auto direction = PonyEngine::Math::Vector3<float>(center + PonyEngine::Math::Vector3<float>(extents.Max() * 3.f) - origin).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, box));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, box));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, box));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, box));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, box).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, box).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<false>(ray, box).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<true>(ray, box).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, box).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, box).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<false>(ray, box).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<true>(ray, box).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, box);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, box);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, box);
	};
#endif
}

TEST_CASE("Ray-box intersection. Missing origin.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 4.f, 3.5f);
	constexpr auto box = PonyEngine::Math::Box<float, 3>(center, extents);
	constexpr auto origin = center + PonyEngine::Math::Vector3<float>(5.f);
	const auto direction = (origin - center).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, box));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, box));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, box));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, box));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, box).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, box).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<false>(ray, box).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<true>(ray, box).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, box).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, box).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<false>(ray, box).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<true>(ray, box).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, box);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, box);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, box);
	};
#endif
}

TEST_CASE("Ray-box intersection. Missing parallel.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 4.f, 3.5f);
	constexpr auto box = PonyEngine::Math::Box<float, 3>(center, extents);
	constexpr auto origin = PonyEngine::Math::Vector3<float>(-2.f, -5.f, -5.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>::Forward();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, box));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, box));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, box));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, box));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, box).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, box).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<false>(ray, box).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<true>(ray, box).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, box).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, box).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<false>(ray, box).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<true>(ray, box).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, box);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, box);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, box);
	};
#endif
}

TEST_CASE("Ray-box intersection. Hit.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 4.f, 3.5f);
	constexpr auto box = PonyEngine::Math::Box<float, 3>(center, extents);
	constexpr auto origin = PonyEngine::Math::Vector3<float>(8.f, 3.f, -7.f);
	const auto direction = PonyEngine::Math::Vector3<float>(center + PonyEngine::Math::Vector3<float>::One() - origin).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);

	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, box));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, box));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, box));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, box));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTimes(ray, box).first.value(), 8.221f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTimes(ray, box).second.value(), 16.441f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime<false>(ray, box).value(), 8.221f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime<true>(ray, box).value(), 16.441f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoints(ray, box).first.value(), ray.Unnormalize(8.221f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoints(ray, box).second.value(), ray.Unnormalize(16.441f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint<false>(ray, box).value(), ray.Unnormalize(8.221f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint<true>(ray, box).value(), ray.Unnormalize(16.441f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, box);
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, box);
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, box);
	};
#endif
}

TEST_CASE("Ray-box intersection. Missing bounds.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 4.f, 3.5f);
	constexpr auto box = PonyEngine::Math::Box<float, 3>(center, extents);
	constexpr auto origin = PonyEngine::Math::Vector3<float>(8.f, 3.f, -7.f);
	const auto direction = PonyEngine::Math::Vector3<float>(center + PonyEngine::Math::Vector3<float>::One() - origin).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);

	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, box, PonyEngine::Math::RayBounds{.max = 1.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, box, PonyEngine::Math::RayBounds{.max = 1.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, box, PonyEngine::Math::RayBounds{.max = 1.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, box, PonyEngine::Math::RayBounds{.max = 1.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, box, PonyEngine::Math::RayBounds{.max = 1.f}).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, box, PonyEngine::Math::RayBounds{.max = 1.f}).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<false>(ray, box, PonyEngine::Math::RayBounds{.max = 1.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<true>(ray, box, PonyEngine::Math::RayBounds{.max = 1.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, box, PonyEngine::Math::RayBounds{.max = 1.f}).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, box, PonyEngine::Math::RayBounds{.max = 1.f}).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<false>(ray, box, PonyEngine::Math::RayBounds{.max = 1.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<true>(ray, box, PonyEngine::Math::RayBounds{.max = 1.f}).has_value());

	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, box, PonyEngine::Math::RayBounds{.min = 50.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, box, PonyEngine::Math::RayBounds{.min = 50.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, box, PonyEngine::Math::RayBounds{.min = 50.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, box, PonyEngine::Math::RayBounds{.min = 50.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, box, PonyEngine::Math::RayBounds{.min = 50.f}).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, box, PonyEngine::Math::RayBounds{.min = 50.f}).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<false>(ray, box, PonyEngine::Math::RayBounds{.min = 50.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<true>(ray, box, PonyEngine::Math::RayBounds{.min = 50.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, box, PonyEngine::Math::RayBounds{.min = 50.f}).first.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, box, PonyEngine::Math::RayBounds{.min = 50.f}).second.has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<false>(ray, box, PonyEngine::Math::RayBounds{.min = 50.f}).has_value());
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<true>(ray, box, PonyEngine::Math::RayBounds{.min = 50.f}).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, box, PonyEngine::Math::RayBounds{.max = 1.f});
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, box, PonyEngine::Math::RayBounds{.max = 1.f});
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, box, PonyEngine::Math::RayBounds{.max = 1.f});
	};
#endif
}

#define PONY_ENGINE_TESTING_BENCHMARK true

TEST_CASE("Ray-box intersection. Hit enter.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 4.f, 3.5f);
	constexpr auto box = PonyEngine::Math::Box<float, 3>(center, extents);
	constexpr auto origin = PonyEngine::Math::Vector3<float>(8.f, 3.f, -7.f);
	const auto direction = PonyEngine::Math::Vector3<float>(center + PonyEngine::Math::Vector3<float>::One() - origin).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);

	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, box, PonyEngine::Math::RayBounds{.max = 10.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, box, PonyEngine::Math::RayBounds{.max = 10.f}));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, box, PonyEngine::Math::RayBounds{.max = 10.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, box, PonyEngine::Math::RayBounds{.max = 10.f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTimes(ray, box, PonyEngine::Math::RayBounds{.max = 10.f}).first.value(), 8.221f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, box, PonyEngine::Math::RayBounds{.max = 10.f}).second.has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime<false>(ray, box, PonyEngine::Math::RayBounds{.max = 10.f}).value(), 8.221f, PonyEngine::Math::Tolerance{ .absolute = 0.001f }));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<true>(ray, box, PonyEngine::Math::RayBounds{.max = 10.f}).has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoints(ray, box, PonyEngine::Math::RayBounds{.max = 10.f}).first.value(), ray.Unnormalize(8.221f), PonyEngine::Math::Tolerance{ .absolute = 0.001f }));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, box, PonyEngine::Math::RayBounds{.max = 10.f}).second.has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint<false>(ray, box, PonyEngine::Math::RayBounds{.max = 10.f}).value(), ray.Unnormalize(8.221f), PonyEngine::Math::Tolerance{ .absolute = 0.001f }));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<true>(ray, box, PonyEngine::Math::RayBounds{.max = 10.f}).has_value());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, box, PonyEngine::Math::RayBounds{.max = 10.f});
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, box, PonyEngine::Math::RayBounds{.max = 10.f});
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, box, PonyEngine::Math::RayBounds{.max = 10.f});
	};
#endif
}

TEST_CASE("Ray-box intersection. Hit exit.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 4.f, 3.5f);
	constexpr auto box = PonyEngine::Math::Box<float, 3>(center, extents);
	constexpr auto origin = PonyEngine::Math::Vector3<float>(8.f, 3.f, -7.f);
	const auto direction = PonyEngine::Math::Vector3<float>(center + PonyEngine::Math::Vector3<float>::One() - origin).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);

	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, box, PonyEngine::Math::RayBounds{.min = 10.f}));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, box, PonyEngine::Math::RayBounds{.min = 10.f}));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, box, PonyEngine::Math::RayBounds{.min = 10.f}));
	REQUIRE_FALSE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, box, PonyEngine::Math::RayBounds{.min = 10.f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTimes(ray, box, PonyEngine::Math::RayBounds{.min = 10.f}).first.has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTimes(ray, box, PonyEngine::Math::RayBounds{.min = 10.f}).second.value(), 16.441f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionTime<false>(ray, box, PonyEngine::Math::RayBounds{.min = 10.f}).has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime<true>(ray, box, PonyEngine::Math::RayBounds{.min = 10.f}).value(), 16.441f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoints(ray, box, PonyEngine::Math::RayBounds{.min = 10.f}).first.has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoints(ray, box, PonyEngine::Math::RayBounds{.min = 10.f}).second.value(), ray.Unnormalize(16.441f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE_FALSE(PonyEngine::Math::IntersectionPoint<false>(ray, box, PonyEngine::Math::RayBounds{.min = 10.f}).has_value());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint<true>(ray, box, PonyEngine::Math::RayBounds{.min = 10.f}).value(), ray.Unnormalize(16.441f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, box, PonyEngine::Math::RayBounds{.min = 10.f});
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, box, PonyEngine::Math::RayBounds{.min = 10.f});
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, box, PonyEngine::Math::RayBounds{.min = 10.f});
	};
#endif
}

TEST_CASE("Ray-box intersection. Hit back.", "[Math][RayIntersections]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -6.f, 2.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 4.f, 3.5f);
	constexpr auto box = PonyEngine::Math::Box<float, 3>(center, extents);
	constexpr auto origin = center + PonyEngine::Math::Vector3<float>(5.f);
	const auto direction = (origin - center).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Enter>(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Exit>(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Any>(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}));
	REQUIRE(PonyEngine::Math::AreIntersecting<PonyEngine::Math::RayIntersectionMode::Both>(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTimes(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).first.value(), -13.856f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTimes(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).second.value(), -3.464f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime<false>(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).value(), -13.856f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionTime<true>(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).value(), -3.464f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoints(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).first.value(), ray.Unnormalize(-13.856f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoints(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).second.value(), ray.Unnormalize(-3.464f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint<false>(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).value(), ray.Unnormalize(-13.856f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::IntersectionPoint<true>(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()}).value(), ray.Unnormalize(-3.464f), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Time")
	{
		return PonyEngine::Math::IntersectionTime(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()});
	};
	BENCHMARK("Point")
	{
		return PonyEngine::Math::IntersectionPoint(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()});
	};
	BENCHMARK("Check")
	{
		return PonyEngine::Math::AreIntersecting(ray, box, PonyEngine::Math::RayBounds{.min = -std::numeric_limits<float>::infinity()});
	};
#endif
}
