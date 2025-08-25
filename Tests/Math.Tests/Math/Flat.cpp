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

TEST_CASE("Flat static", "[Math][Flat]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Flat<float, 1>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Flat<float, 1>::NormalType, PonyEngine::Math::Vector<float, 1>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Flat<float, 1>::DistanceType, float>);
	STATIC_REQUIRE(PonyEngine::Math::Flat<float, 1>::Dimension == 1);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Flat<double, 2>::ValueType, double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Flat<double, 2>::NormalType, PonyEngine::Math::Vector<double, 2>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Flat<double, 2>::DistanceType, double>);
	STATIC_REQUIRE(PonyEngine::Math::Flat<float, 2>::Dimension == 2);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Flat<float, 3>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Flat<float, 3>::NormalType, PonyEngine::Math::Vector<float, 3>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Flat<float, 3>::DistanceType, float>);
	STATIC_REQUIRE(PonyEngine::Math::Flat<float, 3>::Dimension == 3);
}

TEST_CASE("Flat default constructor", "[Math][Flat]")
{
	REQUIRE(PonyEngine::Math::Line<float>() == PonyEngine::Math::Flat<float, 2>(PonyEngine::Math::Vector2<float>::Zero(), 0.f));
	REQUIRE(PonyEngine::Math::Plane<float>() == PonyEngine::Math::Flat<float, 3>(PonyEngine::Math::Vector3<float>::Zero(), 0.f));
}

TEST_CASE("Flat main constructor", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f);
	constexpr float distance = 3.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(plane.Normal(), normal.Normalized()));
	REQUIRE(plane.Distance() == distance);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Plane<float>(PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f), 3.f);
	};
#endif
}

TEST_CASE("Flat point constructor", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(-1.f, 2.f, -5.f);
	constexpr auto point = PonyEngine::Math::Vector3<float>(2.f, 3.f, -1.f);
	const auto plane = PonyEngine::Math::Plane<float>(normal, point);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normal.Normalized(), plane.Normal()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-1.643f, plane.Distance(), 0.001f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.f, plane.Distance(point)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Plane<float>(PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(2.f, 3.f, -1.f));
	};
#endif
}

TEST_CASE("Flat copy constructor", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f);
	constexpr float distance = 3.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	const auto copy = plane;
	REQUIRE(copy == plane);
}

TEST_CASE("Flat move constructor", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f);
	constexpr float distance = 3.f;
	auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	const auto copy = std::move(plane);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normal.Normalized(), copy.Normal()));
	REQUIRE(distance == copy.Distance());
}

TEST_CASE("Flat create by points", "[Math][Flat]")
{
	constexpr auto pointP0 = PonyEngine::Math::Vector1<float>(-4.f);
	const auto ray = PonyEngine::Math::Flat<float, 1>::CreateByPoints(std::array<PonyEngine::Math::Vector1<float>, 1>{ pointP0 });
	REQUIRE(ray.Normal() == PonyEngine::Math::Vector1<float>::One());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(ray.Distance(), 4.f, 0.0001f));

	constexpr auto pointL0 = PonyEngine::Math::Vector2<float>(4.f, 3.f);
	constexpr auto pointL1 = PonyEngine::Math::Vector2<float>(-5.f, 1.f);
	const auto line = PonyEngine::Math::Line<float>::CreateByPoints(std::array<PonyEngine::Math::Vector2<float>, 2>{ pointL0, pointL1 });
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Rotate90CW((pointL1 - pointL0).Normalized()), line.Normal()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-2.061f, line.Distance(), 0.001f));

	constexpr auto point0 = PonyEngine::Math::Vector3<float>(9.f, -4.f, 1.f);
	constexpr auto point1 = PonyEngine::Math::Vector3<float>(2.f, -2.f, -5.f);
	constexpr auto point2 = PonyEngine::Math::Vector3<float>(-5.f, 2.f, 4.f);
	const auto plane = PonyEngine::Math::Plane<float>::CreateByPoints(std::array<PonyEngine::Math::Vector3<float>, 3>{ point0, point1, point2 });
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.369f, 0.921f, -0.123f), plane.Normal(), 0.001f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.491f, plane.Distance(), 0.001f));

	constexpr auto pointH0 = PonyEngine::Math::Vector4<float>(9.f, -4.f, 1.f, -1.f);
	constexpr auto pointH1 = PonyEngine::Math::Vector4<float>(2.f, -2.f, -5.f, 6.f);
	constexpr auto pointH2 = PonyEngine::Math::Vector4<float>(-5.f, 2.f, 4.f, -2.f);
	constexpr auto pointH3 = PonyEngine::Math::Vector4<float>(-2.f, 5.f, -7.f, 2.f);
	const auto planeH = PonyEngine::Math::Flat<float, 4>::CreateByPoints(std::array<PonyEngine::Math::Vector4<float>, 4>{ pointH0, pointH1, pointH2, pointH3 });
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector4<float>(-0.328f, -0.626f, -0.457f, -0.54f), planeH.Normal(), 0.001f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.360395f, planeH.Distance(), 0.001f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Line")
	{
		return PonyEngine::Math::Line<float>::CreateByPoints(std::array<PonyEngine::Math::Vector2<float>, 2>{ PonyEngine::Math::Vector2<float>(4.f, 3.f), PonyEngine::Math::Vector2<float>(-5.f, 1.f) });
	};
	BENCHMARK("Plane")
	{
		return PonyEngine::Math::Plane<float>::CreateByPoints(std::array<PonyEngine::Math::Vector3<float>, 3>{ PonyEngine::Math::Vector3<float>(9.f, -4.f, 1.f), PonyEngine::Math::Vector3<float>(2.f, -2.f, -5.f), PonyEngine::Math::Vector3<float>(-5.f, 2.f, 4.f) });
	};
	BENCHMARK("Hyper-plane")
	{
		return PonyEngine::Math::Flat<float, 4>::CreateByPoints(std::array<PonyEngine::Math::Vector4<float>, 4>{ PonyEngine::Math::Vector4<float>(9.f, -4.f, 1.f, -1.f), PonyEngine::Math::Vector4<float>(2.f, -2.f, -5.f, 6.f), PonyEngine::Math::Vector4<float>(-5.f, 2.f, 4.f, -2.f), PonyEngine::Math::Vector4<float>(-2.f, 5.f, -7.f, 2.f) });
	};
#endif
}

TEST_CASE("Flat access", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f);
	constexpr float distance = 3.f;
	auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normal.Normalized(), plane.Normal()));
	REQUIRE(distance == plane.Distance());
	constexpr auto normal1 = PonyEngine::Math::Vector3<float>(-3.f, 5.f, 2.f);
	plane.Normal(normal1);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normal1.Normalized(), plane.Normal()));
	constexpr float distance1 = -5.f;
	plane.Distance(distance1);
	REQUIRE(distance1 == plane.Distance());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Set normal")
	{
		auto p = PonyEngine::Math::Plane<float>();
		p.Normal(PonyEngine::Math::Vector3<float>(-3.f, 5.f, 2.f));
		return p;
	};
#endif
}

TEST_CASE("Flat flip", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f);
	constexpr float distance = 3.f;
	auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	const auto flipped = plane.Flipped();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-normal.Normalized(), flipped.Normal()));
	REQUIRE(-distance == flipped.Distance());
	plane.Flip();
	REQUIRE(flipped == plane);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Flipped")
	{
		return PonyEngine::Math::Plane<float>(PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f), 3.f).Flipped();
	};
	BENCHMARK("Flip")
	{
		auto p = PonyEngine::Math::Plane<float>(PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f), 3.f);
		p.Flip();
		return p;
	};
#endif
}

TEST_CASE("Flat isFinite", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f);
	constexpr float distance = 3.f;
	auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	REQUIRE(plane.IsFinite());

	plane.Distance(std::numeric_limits<float>::quiet_NaN());
	REQUIRE_FALSE(plane.IsFinite());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Plane<float>(PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f), 3.f).IsFinite();
	};
#endif
}

TEST_CASE("Flat distance", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(2.f, 1.f, -5.f);
	constexpr float distance = -3.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.f, plane.Distance(plane.Project(PonyEngine::Math::Vector3<float>(1.0949f, 0.548f, -2.7388f))), 0.001f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-4.607f, plane.Distance(PonyEngine::Math::Vector3<float>(-2.f, 0.2f, 1.f)), 0.001f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(4.12f, plane.Distance(PonyEngine::Math::Vector3<float>(5.f, -1.f, -6.f)), 0.001f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Plane<float>(PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f), 3.f).Distance(PonyEngine::Math::Vector3<float>(1.095f, 0.548f, -2.739f));
	};
#endif
}

TEST_CASE("Flat project", "[Math][Flat]")
{
	const auto normal = PonyEngine::Math::Vector3<float>(2.f, 1.f, -5.f).Normalized();
	constexpr float distance = -3.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.095f, 0.548f, -2.739f), plane.Project(PonyEngine::Math::Vector3<float>(1.095f, 0.548f, -2.739f)), 0.001f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.822f, 2.011f, -2.555f), plane.Project(PonyEngine::Math::Vector3<float>(-3.f, 0.1f, 7.f)), 0.001f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(6.629f, -4.686f, -1.572f), plane.Project(PonyEngine::Math::Vector3<float>(10.f, -3.f, -10.f)), 0.001f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Plane<float>(PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f), 3.f).Project(PonyEngine::Math::Vector3<float>(1.095f, 0.548f, -2.739f));
	};
#endif
}

TEST_CASE("Flat side", "[Math][Flat]")
{
	const auto normal = PonyEngine::Math::Vector3<float>(2.f, 1.f, -5.f).Normalized();
	auto point = PonyEngine::Math::Vector3<float>(2.f, 3.f, 4.f);
	const auto plane = PonyEngine::Math::Plane<float>(normal, point);
	REQUIRE(std::int8_t{0} == plane.Side(point));
	point = PonyEngine::Math::Vector3<float>(20.f, 3.f, -4.f);
	REQUIRE(std::int8_t{1} == plane.Side(point));
	point = PonyEngine::Math::Vector3<float>(-20.f, -3.f, -4.f);
	REQUIRE(std::int8_t{-1} == plane.Side(point));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Plane<float>(PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f), 3.f).Side(PonyEngine::Math::Vector3<float>(1.095f, 0.548f, -2.739f));
	};
#endif
}

TEST_CASE("Flat toString", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(2.f, 1.f, -5.f);
	constexpr float distance = -3.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	const std::string expected = std::format("Normal: {}, Distance: {}", plane.Normal(), plane.Distance());
	REQUIRE(expected == plane.ToString());
	std::ostringstream oss;
	oss << plane;
	REQUIRE(expected == oss.str());
	REQUIRE(std::format("{}", plane) == expected);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Plane<float>(PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f), 3.f).ToString();
	};
#endif
}

TEST_CASE("Flat cast", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(2.f, 1.f, -5.f);
	constexpr float distance = -3.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	const auto cast = static_cast<PonyEngine::Math::Plane<double>>(plane);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(static_cast<PonyEngine::Math::Vector3<double>>(normal).Normalized(), cast.Normal()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(static_cast<double>(distance), cast.Distance()));
}

TEST_CASE("Flat copy assignment", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(2.f, 1.f, -5.f);
	constexpr float distance = -3.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	auto copy = PonyEngine::Math::Plane<float>();
	copy = plane;
	REQUIRE(copy == plane);
}

TEST_CASE("Flat move assignment", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(2.f, 1.f, -5.f);
	constexpr float distance = -3.f;
	auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	auto copy = PonyEngine::Math::Plane<float>();
	copy = std::move(plane);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normal.Normalized(), copy.Normal()));
	REQUIRE(distance == copy.Distance());
}

TEST_CASE("Flat equals", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(2.f, 1.f, -5.f);
	constexpr float distance = -3.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	REQUIRE(plane == plane);
	auto copy = plane;
	REQUIRE(plane == copy);

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto norm = normal;
		norm[i] += 0.00001f;
		copy.Normal(norm);
		REQUIRE(plane != copy);

		norm[i] -= 1.f;
		copy.Normal(norm);
		REQUIRE(plane != copy);

		copy.Normal(plane.Normal());
	}

	copy.Distance(distance - 0.0000001f);
	REQUIRE(plane != copy);
	copy.Distance(distance + 1.f);
	REQUIRE(plane != copy);
}

TEST_CASE("Flat are almost equal", "[Math][Flat]")
{
	constexpr auto normal = PonyEngine::Math::Vector3<float>(2.f, 1.f, -5.f);
	constexpr float distance = -3.f;
	const auto plane = PonyEngine::Math::Plane<float>(normal, distance);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(plane, plane));
	auto copy = plane;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(plane, copy));

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto norm = normal;
		norm[i] += 0.00001f;
		copy.Normal(norm);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(plane, copy));

		norm[i] -= 1.f;
		copy.Normal(norm);
		REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(plane, copy));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(plane, copy, 5.f));

		copy.Normal(plane.Normal());
	}

	copy.Distance(distance - 0.0000001f);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(plane, copy));
	copy.Distance(distance + 1.f);
	REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(plane, copy));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(plane, copy, 5.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Plane<float>(PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f), 3.f), PonyEngine::Math::Plane<float>(PonyEngine::Math::Vector3<float>(-4.f, 2.f, -3.f), 3.f));
	};
#endif
}
