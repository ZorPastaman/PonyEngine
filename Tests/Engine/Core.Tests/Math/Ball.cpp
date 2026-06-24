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

TEST_CASE("Ball static", "[Math][Ball]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ball<float, 1>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ball<float, 1>::CenterType, PonyEngine::Math::Vector<float, 1>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ball<float, 1>::RadiusType, float>);
	STATIC_REQUIRE(PonyEngine::Math::Ball<float, 1>::Dimension == 1);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ball<double, 2>::ValueType, double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ball<double, 2>::CenterType, PonyEngine::Math::Vector<double, 2>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ball<double, 2>::RadiusType, double>);
	STATIC_REQUIRE(PonyEngine::Math::Ball<float, 2>::Dimension == 2);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ball<float, 3>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ball<float, 3>::CenterType, PonyEngine::Math::Vector<float, 3>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ball<float, 3>::RadiusType, float>);
	STATIC_REQUIRE(PonyEngine::Math::Ball<float, 3>::Dimension == 3);
}

TEST_CASE("Ball default constructor", "[Math][Ball]")
{
	STATIC_REQUIRE(PonyEngine::Math::Ball<float, 1>() == PonyEngine::Math::Ball<float, 1>(PonyEngine::Math::Vector1<float>::Zero(), 0.f));
	STATIC_REQUIRE(PonyEngine::Math::Ball<float, 2>() == PonyEngine::Math::Ball<float, 2>(PonyEngine::Math::Vector2<float>::Zero(), 0.f));
	STATIC_REQUIRE(PonyEngine::Math::Ball<float, 3>() == PonyEngine::Math::Ball<float, 3>(PonyEngine::Math::Vector3<float>::Zero(), 0.f));
}

TEST_CASE("Ball radius constructor", "[Math][Ball]")
{
	STATIC_REQUIRE(PonyEngine::Math::Ball<float, 1>(4.f) == PonyEngine::Math::Ball<float, 1>(PonyEngine::Math::Vector1<float>::Zero(), 4.f));
	STATIC_REQUIRE(PonyEngine::Math::Ball<float, 2>(-3.f) == PonyEngine::Math::Ball<float, 2>(PonyEngine::Math::Vector2<float>::Zero(), 3.f));
	STATIC_REQUIRE(PonyEngine::Math::Ball<float, 3>(2.f) == PonyEngine::Math::Ball<float, 3>(PonyEngine::Math::Vector3<float>::Zero(), 2.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Ball<float, 3>(2.f);
	};
#endif
}

TEST_CASE("Ball main constructor", "[Math][Ball]")
{
	STATIC_REQUIRE(PonyEngine::Math::Ball<float, 1>(PonyEngine::Math::Vector1<float>(2.f), 4.f) == PonyEngine::Math::Ball<float, 1>(PonyEngine::Math::Vector1<float>(2.f), 4.f));
	STATIC_REQUIRE(PonyEngine::Math::Ball<float, 2>(PonyEngine::Math::Vector2<float>(5.f, -2.f), -3.f) == PonyEngine::Math::Ball<float, 2>(PonyEngine::Math::Vector2<float>(5.f, -2.f), 3.f));
	STATIC_REQUIRE(PonyEngine::Math::Ball<float, 3>(PonyEngine::Math::Vector3<float>(5.f, -2.f, 1.f), 2.f) == PonyEngine::Math::Ball<float, 3>(PonyEngine::Math::Vector3<float>(5.f, -2.f, 1.f), 2.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Ball<float, 3>(PonyEngine::Math::Vector3<float>(5.f, -2.f, 1.f), 2.f);
	};
#endif
}

TEST_CASE("Ball copy constructor", "[Math][Ball]")
{
	constexpr auto ball = PonyEngine::Math::Ball<float, 2>(PonyEngine::Math::Vector2<float>(5.f, -2.f), -3.f);
	constexpr auto copy = ball;
	STATIC_REQUIRE(copy == ball);
}

TEST_CASE("Ball move constructor", "[Math][Ball]")
{
	auto test = []<std::floating_point T, std::size_t Size>(const PonyEngine::Math::Ball<T, Size>& ball) constexpr 
	{
		auto copy = ball;
		auto moved = std::move(copy);
		return moved;
	};

	constexpr auto ball = PonyEngine::Math::Ball<float, 2>(PonyEngine::Math::Vector2<float>(5.f, -2.f), -3.f);
	constexpr auto moved = test(ball);
	STATIC_REQUIRE(moved == ball);
}

TEST_CASE("Ball access", "[Math][Ball]")
{
	auto test = []<std::floating_point T, std::size_t Size>(const PonyEngine::Math::Ball<T, Size>& ball, const PonyEngine::Math::Vector<T, Size>& center, const T radius) constexpr
	{
		auto copy = ball;
		copy.Center(center);
		copy.Radius(radius);
		return copy;
	};

	constexpr auto ball = PonyEngine::Math::Ball<float, 3>(PonyEngine::Math::Vector3<float>(5.f, -2.f, 1.f), 2.f);
	STATIC_REQUIRE(ball.Center() == PonyEngine::Math::Vector3<float>(5.f, -2.f, 1.f));
	STATIC_REQUIRE(ball.Radius() == 2.f);
	constexpr auto ball1 = test(ball, PonyEngine::Math::Vector3<float>(1.f, 2.f, 3.f), -4.f);
	STATIC_REQUIRE(ball1.Center() == PonyEngine::Math::Vector3<float>(1.f, 2.f, 3.f));
	STATIC_REQUIRE(ball1.Radius() == 4.f);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Set radius")
	{
		auto sphere = PonyEngine::Math::Ball<float, 3>(PonyEngine::Math::Vector3<float>(5.f, -2.f, 1.f), 2.f);
		sphere.Radius(3.f);
		return sphere;
	};
#endif
}

TEST_CASE("Ball diameter", "[Math][Ball]")
{
	constexpr auto ball = PonyEngine::Math::Ball(PonyEngine::Math::Vector3<float>(5.f, -2.f, 1.f), 2.f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(ball.Diameter(), 4.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Ball<float, 3>(PonyEngine::Math::Vector3<float>(5.f, -2.f, 1.f), 2.f).Diameter();
	};
#endif
}

TEST_CASE("Ball surface", "[Math][Ball]")
{
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Ball(PonyEngine::Math::Vector1<float>(5.f), 3.f).Surface(), 2.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Ball(PonyEngine::Math::Vector2<float>(5.f, -4.f), 3.f).Surface(), 18.85f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Ball(PonyEngine::Math::Vector3<float>(5.f, -4.f, 1.f), 3.f).Surface(), 113.097f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Ball(PonyEngine::Math::Vector4<float>(5.f, -4.f, 1.f, -1.f), 3.f).Surface(), 532.959f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("1D")
	{
		return PonyEngine::Math::Ball(PonyEngine::Math::Vector1<float>(5.f), 3.f).Surface();
	};
	BENCHMARK("2D")
	{
		return PonyEngine::Math::Ball(PonyEngine::Math::Vector2<float>(5.f, -4.f), 3.f).Surface();
	};
	BENCHMARK("3D")
	{
		return PonyEngine::Math::Ball(PonyEngine::Math::Vector3<float>(5.f, -4.f, 1.f), 3.f).Surface();
	};
	BENCHMARK("4D")
	{
		return PonyEngine::Math::Ball(PonyEngine::Math::Vector4<float>(5.f, -4.f, 1.f, -1.f), 3.f).Surface();
	};
#endif
}

TEST_CASE("Ball volume", "[Math][Ball]")
{
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Ball(PonyEngine::Math::Vector1<float>(5.f), 3.f).Volume(), 6.f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Ball(PonyEngine::Math::Vector2<float>(5.f, -4.f), 3.f).Volume(), 28.274f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Ball(PonyEngine::Math::Vector3<float>(5.f, -4.f, 1.f), 3.f).Volume(), 113.097f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Ball(PonyEngine::Math::Vector4<float>(5.f, -4.f, 1.f, -1.f), 3.f).Volume(), 399.719f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("1D")
	{
		return PonyEngine::Math::Ball(PonyEngine::Math::Vector1<float>(5.f), 3.f).Volume();
	};
	BENCHMARK("2D")
	{
		return PonyEngine::Math::Ball(PonyEngine::Math::Vector2<float>(5.f, -4.f), 3.f).Volume();
	};
	BENCHMARK("3D")
	{
		return PonyEngine::Math::Ball(PonyEngine::Math::Vector3<float>(5.f, -4.f, 1.f), 3.f).Volume();
	};
	BENCHMARK("4D")
	{
		return PonyEngine::Math::Ball(PonyEngine::Math::Vector4<float>(5.f, -4.f, 1.f, -1.f), 3.f).Volume();
	};
#endif
}

TEST_CASE("Ball isFinite", "[Math][Ball]")
{
	constexpr auto ball = PonyEngine::Math::Ball<float, 3>(PonyEngine::Math::Vector3<float>(5.f, -2.f, 1.f), 2.f);
	STATIC_REQUIRE(ball.IsFinite());
	auto ball1 = ball;
	REQUIRE(ball1.IsFinite());

	for (std::size_t i = 0uz; i < 3uz; ++i)
	{
		auto center = ball.Center();
		center[i] = std::numeric_limits<float>::quiet_NaN();
		ball1.Center(center);
		REQUIRE_FALSE(ball1.IsFinite());
		ball1.Center(ball.Center());
	}

	ball1.Radius(std::numeric_limits<float>::quiet_NaN());
	REQUIRE_FALSE(ball1.IsFinite());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Ball<float, 3>(PonyEngine::Math::Vector3<float>(5.f, -2.f, 1.f), 2.f).IsFinite();
	};
#endif
}

TEST_CASE("Ball contains", "[Math][Ball]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(-2.f, -1.f, 2.f);
	constexpr float radius = 2.f;
	constexpr auto sphere = PonyEngine::Math::Sphere<float>(center, radius);

	STATIC_REQUIRE(sphere.Contains(center));
	STATIC_REQUIRE(sphere.Contains(center + PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f)));
	STATIC_REQUIRE_FALSE(sphere.Contains(PonyEngine::Math::Vector3<float>::Zero()));
	STATIC_REQUIRE_FALSE(sphere.Contains(PonyEngine::Math::Vector3<float>(10.f, 11.f, 12.f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Ball<float, 3>(PonyEngine::Math::Vector3<float>(5.f, -2.f, 1.f), 2.f).Contains(PonyEngine::Math::Vector3<float>(5.1f, -2.1f, 1.9f)) |
			PonyEngine::Math::Ball<float, 3>(PonyEngine::Math::Vector3<float>(5.f, -2.f, 1.f), 2.f).Contains(PonyEngine::Math::Vector3<float>(15.1f, -22.1f, 11.9f));
	};
#endif
}

TEST_CASE("Ball closest point", "[Math][Ball]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(-2.f, -1.f, 2.f);
	constexpr float radius = 2.f;
	constexpr auto sphere = PonyEngine::Math::Sphere<float>(center, radius);

	REQUIRE(PonyEngine::Math::AreAlmostEqual(center, sphere.ClosestPoint(center)));
	auto vector = center + PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector, sphere.ClosestPoint(vector)));
	vector = center + PonyEngine::Math::Vector3<float>(10.f, -12.f, 11.f);
	REQUIRE(PonyEngine::Math::AreAlmostEqual((vector - center).Normalized() * radius + center, sphere.ClosestPoint(vector)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Inside")
	{
		return PonyEngine::Math::Sphere<float>(PonyEngine::Math::Vector3<float>(-2.f, -1.f, 2.f), 2.f).ClosestPoint(PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f));
	};
	BENCHMARK("Outside")
	{
		return PonyEngine::Math::Sphere<float>(PonyEngine::Math::Vector3<float>(-2.f, -1.f, 2.f), 2.f).ClosestPoint(PonyEngine::Math::Vector3<float>(10.f, -12.f, 11.f));
	};
#endif
}

TEST_CASE("Ball cast", "[Math][Ball]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(-2.f, -1.f, 2.f);
	constexpr float radius = 2.f;
	constexpr auto sphere = PonyEngine::Math::Sphere<float>(center, radius);
	constexpr auto cast = static_cast<PonyEngine::Math::Sphere<double>>(sphere);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(cast.Center(), static_cast<PonyEngine::Math::Vector3<double>>(center)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(cast.Radius(), static_cast<double>(radius)));
}

TEST_CASE("Ball copy assignment", "[Math][Ball]")
{
	auto test = []<std::floating_point T, std::size_t Size>(const PonyEngine::Math::Ball<T, Size>& ball) constexpr
	{
		auto copy = PonyEngine::Math::Ball<T, Size>();
		copy = ball;
		return copy;
	};

	constexpr auto center = PonyEngine::Math::Vector3<float>(-2.f, -1.f, 2.f);
	constexpr float radius = 2.f;
	constexpr auto sphere = PonyEngine::Math::Sphere<float>(center, radius);
	STATIC_REQUIRE(test(sphere) == sphere);
}

TEST_CASE("Ball move assignment", "[Math][Ball]")
{
	auto test = []<std::floating_point T, std::size_t Size>(const PonyEngine::Math::Ball<T, Size>&ball) constexpr
	{
		auto copy = ball;
		auto moved = PonyEngine::Math::Ball<T, Size>();
		moved = std::move(ball);
		return moved;
	};

	constexpr auto center = PonyEngine::Math::Vector3<float>(-2.f, -1.f, 2.f);
	constexpr float radius = 2.f;
	constexpr auto sphere = PonyEngine::Math::Sphere<float>(center, radius);
	STATIC_REQUIRE(test(sphere) == sphere);
}

TEST_CASE("Ball equals", "[Math][Ball]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(-2.f, -1.f, 2.f);
	constexpr float radius = 2.f;
	constexpr auto sphere = PonyEngine::Math::Sphere<float>(center, radius);
	STATIC_REQUIRE(sphere == sphere);
	auto copy = sphere;

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto newCenter = center;
		newCenter[i] += 0.000001f;
		copy.Center(newCenter);
		REQUIRE(sphere != copy);
		newCenter[i] -= 1.f;
		copy.Center(newCenter);
		REQUIRE(sphere != copy);
		copy.Center(center);
	}

	copy.Radius(radius - 0.000001f);
	REQUIRE_FALSE(sphere == copy);
	copy.Radius(radius + 1.f);
	REQUIRE_FALSE(sphere == copy);
}

TEST_CASE("Ball are almost equal", "[Math][Ball]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(-2.f, -1.f, 2.f);
	constexpr float radius = 2.f;
	constexpr auto sphere = PonyEngine::Math::Sphere<float>(center, radius);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(sphere, sphere));
	auto copy = sphere;

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto newCenter = center;
		newCenter[i] += 0.0000001f;
		copy.Center(newCenter);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(sphere, copy));
		newCenter[i] -= 2.f;
		copy.Center(newCenter);
		REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(sphere, copy));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(sphere, copy, PonyEngine::Math::Tolerance{.absolute = 5.f}));
		copy.Center(center);
	}

	copy.Radius(radius - 0.000001f);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(sphere, copy));
	copy.Radius(radius + 1.f);
	REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(sphere, copy));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(sphere, copy, PonyEngine::Math::Tolerance{.absolute = 5.f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Sphere<float>(PonyEngine::Math::Vector3<float>(-2.f, -1.f, 2.f), 2.f), PonyEngine::Math::Sphere<float>(PonyEngine::Math::Vector3<float>(-2.0000001f, -1.0000001f, 2.000001f), 1.9999999f));
	};
#endif
}
