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

TEST_CASE("Ray static", "[Math][Ray]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ray1D<float>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ray1D<float>::OriginType, PonyEngine::Math::Vector1<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ray1D<float>::DirectionType, PonyEngine::Math::Vector1<float>>);
	STATIC_REQUIRE(PonyEngine::Math::Ray1D<float>::Dimension == 1);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ray2D<float>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ray2D<float>::OriginType, PonyEngine::Math::Vector2<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ray2D<float>::DirectionType, PonyEngine::Math::Vector2<float>>);
	STATIC_REQUIRE(PonyEngine::Math::Ray2D<float>::Dimension == 2);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ray3D<float>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ray3D<float>::OriginType, PonyEngine::Math::Vector3<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Ray3D<float>::DirectionType, PonyEngine::Math::Vector3<float>>);
	STATIC_REQUIRE(PonyEngine::Math::Ray3D<float>::Dimension == 3);
}

TEST_CASE("Ray default constructor", "[Math][Ray]")
{
	REQUIRE(PonyEngine::Math::Ray1D<float>() == PonyEngine::Math::Ray1D<float>(PonyEngine::Math::Vector1<float>(), PonyEngine::Math::Vector1<float>()));
	REQUIRE(PonyEngine::Math::Ray2D<float>() == PonyEngine::Math::Ray2D<float>(PonyEngine::Math::Vector2<float>(), PonyEngine::Math::Vector2<float>()));
	REQUIRE(PonyEngine::Math::Ray3D<float>() == PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(), PonyEngine::Math::Vector3<float>()));
	REQUIRE(PonyEngine::Math::Ray<float, 4>() == PonyEngine::Math::Ray<float, 4>(PonyEngine::Math::Vector4<float>(), PonyEngine::Math::Vector4<float>()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Ray3D<float>();
	};
#endif
}

TEST_CASE("Ray main constructor", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f);
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	REQUIRE(ray.Origin() == origin);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(ray.Direction(), direction.Normalized()));

	const auto ray1 = PonyEngine::Math::Ray3D<float>(origin, PonyEngine::Math::Vector3<float>::Zero());
	REQUIRE(ray1.Origin() == origin);
	REQUIRE(ray1.Direction() == PonyEngine::Math::Vector3<float>());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Correct direction")
	{
		return PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f));
	};
	BENCHMARK("Incorrect direction")
	{
		return PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>::Zero());
	};
#endif
}

TEST_CASE("Ray copy constructor", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f);
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	const auto copy = ray;
	REQUIRE(copy.Origin() == ray.Origin());
	REQUIRE(copy.Direction() == ray.Direction());
}

TEST_CASE("Ray move constructor", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f);
	auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	const auto copy = std::move(ray);
	REQUIRE(copy.Origin() == ray.Origin());
	REQUIRE(copy.Direction() == ray.Direction());
}

TEST_CASE("Ray create by target", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f);
	constexpr auto target = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f);
	const auto ray = PonyEngine::Math::Ray3D<float>::CreateByTarget(origin, target);
	REQUIRE(ray.Origin() == origin);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(ray.Direction(), (target - origin).Normalized()));

	const auto ray1 = PonyEngine::Math::Ray3D<float>::CreateByTarget(origin, origin);
	REQUIRE(ray1.Origin() == origin);
	REQUIRE(ray1.Direction() == PonyEngine::Math::Vector3<float>());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Correct direction")
	{
		return PonyEngine::Math::Ray3D<float>::CreateByTarget(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f));
	};
	BENCHMARK("Incorrect direction")
	{
		return PonyEngine::Math::Ray3D<float>::CreateByTarget(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f));
	};
#endif
}

TEST_CASE("Ray access", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f);
	auto ray = PonyEngine::Math::Ray3D<float>();
	ray.Origin(origin);
	REQUIRE(ray.Origin() == origin);
	ray.Direction(direction);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(ray.Direction(), direction.Normalized()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Set direction")
	{
		auto r = PonyEngine::Math::Ray3D<float>();
		r.Direction(PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f));
		return r;
	};
#endif
}

TEST_CASE("Ray flip", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f);
	auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	const auto flipped = ray.Flipped();
	REQUIRE(flipped.Origin() == ray.Origin());
	REQUIRE(flipped.Direction() == -ray.Direction());
	ray.Flip();
	REQUIRE(ray == flipped);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Flipped")
	{
		return PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f)).Flipped();
	};
	BENCHMARK("Flip")
	{
		auto r = PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f));
		r.Flip();
		return r;
	};
#endif
}

TEST_CASE("Ray isFinite", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f);
	auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	REQUIRE(ray.IsFinite());

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto orig = origin;
		orig[i] = std::numeric_limits<float>::quiet_NaN();
		ray.Origin(orig);
		REQUIRE_FALSE(ray.IsFinite());
		ray.Origin(origin);
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f)).IsFinite();
	};
#endif
}

TEST_CASE("Ray project", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(3.f, -2.f, -4.f);
	const auto direction = PonyEngine::Math::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);

	auto vector = origin + direction * 6.f;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector, ray.Project(vector)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(origin + direction * 3.f, ray.Project(vector, PonyEngine::Math::RayBounds{.max = 3.f})));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(origin + direction * 8.f, ray.Project(vector, PonyEngine::Math::RayBounds{.min = 8.f})));

	vector = origin + direction * -2.f;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(origin, ray.Project(vector)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(origin, ray.Project(vector, PonyEngine::Math::RayBounds{.max = 3.f})));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(origin + direction * -2.f, ray.Project(vector, PonyEngine::Math::RayBounds{.min = -8.f})));

	vector = PonyEngine::Math::Vector3<float>(-3.f, 10.f, -2.f);
	auto expected = origin + direction * PonyEngine::Math::Dot(direction, vector - origin);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expected, ray.Project(vector)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(origin + direction, ray.Project(vector, PonyEngine::Math::RayBounds{.max = 1.f})));

	vector = PonyEngine::Math::Vector3<float>(-6.f, -10.f, -5.f);
	expected = origin + direction * PonyEngine::Math::Dot(direction, vector - origin);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expected, ray.Project(vector)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(origin + direction, ray.Project(vector, PonyEngine::Math::RayBounds{.max = 1.f})));

	vector = PonyEngine::Math::Vector3<float>(5.f, -2.f, 0.5f);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(origin, ray.Project(vector)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(origin, ray.Project(vector, PonyEngine::Math::RayBounds{.max = 1.f})));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f)).Project(PonyEngine::Math::Vector3<float>(-5.f, 4.f, 7.f));
	};
#endif
}

TEST_CASE("Ray normalize", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(3.f, -2.f, -4.f);
	const auto direction = PonyEngine::Math::Vector3<float>(-1.f, 0.7f, -0.5f).Normalized();
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);

	auto vector = origin + direction * 6.f;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(6.f, ray.Normalize(vector)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector, ray.Unnormalize(6.f)));

	vector = origin + direction * -2.f;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-2.f, ray.Normalize(vector)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector, ray.Unnormalize(-2.f)));

	vector = PonyEngine::Math::Vector3<float>(-3.f, 10.f, -2.f);
	auto expected = PonyEngine::Math::Dot(direction, vector - origin);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expected, ray.Normalize(vector)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(origin + direction * expected, ray.Unnormalize(expected)));

	vector = PonyEngine::Math::Vector3<float>(-6.f, -10.f, -5.f);
	expected = PonyEngine::Math::Dot(direction, vector - origin);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expected, ray.Normalize(vector)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(origin + direction * expected, ray.Unnormalize(expected)));

	vector = PonyEngine::Math::Vector3<float>(5.f, -2.f, 0.5f);
	expected = PonyEngine::Math::Dot(direction, vector - origin);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expected, ray.Normalize(vector)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(origin + direction * expected, ray.Unnormalize(expected)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Normalize")
	{
		return PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f)).Normalize(PonyEngine::Math::Vector3<float>(-5.f, 4.f, 7.f));
	};
	BENCHMARK("Unnormalize")
	{
		return PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f)).Unnormalize(2.3f);
	};
#endif
}

TEST_CASE("Ray toString", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(3.f, -2.f, -4.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>(-1.f, 0.7f, -0.5f);
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	const std::string expected = std::format("Origin: {}, Direction: {}", ray.Origin(), ray.Direction());
	REQUIRE(ray.ToString() == expected);
	std::ostringstream oss;
	oss << ray;
	REQUIRE(oss.str() == expected);
	REQUIRE(std::format("{}", ray) == expected);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f)).ToString();
	};
#endif
}

TEST_CASE("Ray cast", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(3.f, -2.f, -4.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>(-1.f, 0.7f, -0.5f);
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	const auto cast = static_cast<PonyEngine::Math::Ray3D<double>>(ray);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(static_cast<PonyEngine::Math::Vector3<double>>(origin), cast.Origin()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(static_cast<PonyEngine::Math::Vector3<double>>(direction.Normalized()), cast.Direction()));
}

TEST_CASE("Ray copy assignment", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(3.f, -2.f, -4.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>(-1.f, 0.7f, -0.5f);
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	auto copy = PonyEngine::Math::Ray3D<float>();
	copy = ray;
	REQUIRE(copy == ray);
}

TEST_CASE("Ray move assignment", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(3.f, -2.f, -4.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>(-1.f, 0.7f, -0.5f);
	auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	auto copy = PonyEngine::Math::Ray3D<float>();
	copy = std::move(ray);
	REQUIRE(copy.Origin() == origin);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Direction(), direction.Normalized()));
}

TEST_CASE("Ray equals", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(3.f, -2.f, -4.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>(-1.f, 0.7f, -0.5f);
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	REQUIRE(ray == ray);
	auto copy = ray;
	REQUIRE(copy == ray);

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto orig = origin;
		orig[i] = std::nextafter(orig[i], 0.f);
		copy.Origin(orig);
		REQUIRE(copy != ray);
		orig[i] -= 1.f;
		copy.Origin(orig);
		REQUIRE(copy != ray);
		copy.Origin(origin);

		auto dir = direction;
		dir[i] -= 0.000001f;
		copy.Direction(dir);
		REQUIRE(copy != ray);
		dir[i] -= 1.f;
		copy.Direction(dir);
		REQUIRE(copy != ray);
		copy.Direction(direction);
	}
}

TEST_CASE("Ray are almost equal", "[Math][Ray]")
{
	constexpr auto origin = PonyEngine::Math::Vector3<float>(3.f, -2.f, -4.f);
	constexpr auto direction = PonyEngine::Math::Vector3<float>(-1.f, 0.7f, -0.5f);
	const auto ray = PonyEngine::Math::Ray3D<float>(origin, direction);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(ray, ray));
	auto copy = ray;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, ray));

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto orig = origin;
		orig[i] = std::nextafter(orig[i], 0.f);
		copy.Origin(orig);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, ray));
		orig[i] -= 1.f;
		copy.Origin(orig);
		REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(copy, ray));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, ray, PonyEngine::Math::Tolerance{.absolute = 5.f}));
		copy.Origin(origin);

		auto dir = direction;
		dir[i] -= 0.000001f;
		copy.Direction(dir);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, ray));
		dir[i] -= 1.f;
		copy.Direction(dir);
		REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(copy, ray));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, ray, PonyEngine::Math::Tolerance{.absolute = 5.f}));
		copy.Direction(direction);
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f)), PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f))) &
			PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(4.f, 2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 1.f)), PonyEngine::Math::Ray3D<float>(PonyEngine::Math::Vector3<float>(2.f, 3.f, 8.f), PonyEngine::Math::Vector3<float>(-4.f, -5.f, 6.f)));
	};
#endif
}
