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

TEST_CASE("Box static", "[Math][Box]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Box<std::int32_t, 2>::ValueType, std::int32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Box<std::int32_t, 2>::CenterType, PonyEngine::Math::Vector2<std::int32_t>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Box<std::int32_t, 2>::ExtentsType, PonyEngine::Math::Vector2<std::int32_t>>);
	STATIC_REQUIRE(PonyEngine::Math::Box<std::int32_t, 2>::Dimension == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Box<std::int32_t, 2>::Axes == PonyEngine::Math::Matrix2x2<std::int32_t>::Identity());
	STATIC_REQUIRE(PonyEngine::Math::Box<std::int32_t, 2>::CornerCount == 4uz);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Box<float, 3>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Box<float, 3>::CenterType, PonyEngine::Math::Vector3<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Box<float, 3>::ExtentsType, PonyEngine::Math::Vector3<float>>);
	STATIC_REQUIRE(PonyEngine::Math::Box<float, 3>::Dimension == 3uz);
	STATIC_REQUIRE(PonyEngine::Math::Box<float, 3>::Axes == PonyEngine::Math::Matrix3x3<float>::Identity());
	STATIC_REQUIRE(PonyEngine::Math::Box<float, 3>::CornerCount == 8uz);
}

TEST_CASE("Box default constructor", "[Math][Box]")
{
	STATIC_REQUIRE(PonyEngine::Math::Rect<std::int32_t>() == PonyEngine::Math::Rect<std::int32_t>(PonyEngine::Math::Vector2<std::int32_t>::Zero(), PonyEngine::Math::Vector2<std::int32_t>::Zero()));
	STATIC_REQUIRE(PonyEngine::Math::Cuboid<float>() == PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>::Zero(), PonyEngine::Math::Vector3<float>::Zero()));
}

TEST_CASE("Box extents constructor", "[Math][Box]")
{
	constexpr auto extents2 = PonyEngine::Math::Vector2<float>(-3.f, 2.f);
	constexpr auto rect = PonyEngine::Math::Rect<float>(extents2);
	STATIC_REQUIRE(rect.Center() == PonyEngine::Math::Vector2<float>::Zero());
	STATIC_REQUIRE(rect.Extents() == PonyEngine::Math::Abs(extents2));

	constexpr auto extents3 = PonyEngine::Math::Vector3<std::int32_t>(-3, 2, 6);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<std::int32_t>(extents3);
	STATIC_REQUIRE(cuboid.Center() == PonyEngine::Math::Vector3<std::int32_t>::Zero());
	STATIC_REQUIRE(cuboid.Extents() == PonyEngine::Math::Abs(extents3));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f));
	};
#endif
}

TEST_CASE("Box main constructor", "[Math][Box]")
{
	constexpr auto center2 = PonyEngine::Math::Vector2<float>(4.f, -5.f);
	constexpr auto extents2 = PonyEngine::Math::Vector2<float>(-3.f, 2.f);
	constexpr auto rect = PonyEngine::Math::Rect<float>(center2, extents2);
	STATIC_REQUIRE(rect.Center() == center2);
	STATIC_REQUIRE(rect.Extents() == PonyEngine::Math::Abs(extents2));

	constexpr auto center3 = PonyEngine::Math::Vector3<std::int32_t>(4, -5, 1);
	constexpr auto extents3 = PonyEngine::Math::Vector3<std::int32_t>(-3, 2, 6);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<std::int32_t>(center3, extents3);
	STATIC_REQUIRE(cuboid.Center() == center3);
	STATIC_REQUIRE(cuboid.Extents() == PonyEngine::Math::Abs(extents3));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f));
	};
#endif
}

TEST_CASE("Box copy constructor", "[Math][Box]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	constexpr auto copy = cuboid;
	STATIC_REQUIRE(copy.Center() == center);
	STATIC_REQUIRE(copy.Extents() == PonyEngine::Math::Abs(extents));
}

TEST_CASE("Box move constructor", "[Math][Box]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t Size>(const PonyEngine::Math::Box<T, Size>& box) constexpr
	{
		auto copy = box;
		auto moved = std::move(copy);
		return moved;
	};

	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	constexpr auto moved = test(cuboid);
	STATIC_REQUIRE(moved.Center() == center);
	STATIC_REQUIRE(moved.Extents() == PonyEngine::Math::Abs(extents));
}

TEST_CASE("Box access", "[Math][Box]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t Size>(const PonyEngine::Math::Box<T, Size>& box) constexpr
	{
		auto copy = box;
		copy.Center(box.Center() + PonyEngine::Math::Vector<T, Size>(T{1}));
		copy.Extents(box.Extents() - PonyEngine::Math::Vector<T, Size>(T{1}));
		copy.Extent(0, T{-3});
		return copy;
	};

	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	STATIC_REQUIRE(cuboid.Center() == center);
	STATIC_REQUIRE(cuboid.Extents() == PonyEngine::Math::Abs(extents));
	STATIC_REQUIRE(cuboid.Extent(0) == PonyEngine::Math::Abs(extents[0]));
	STATIC_REQUIRE(cuboid.Extent(1) == PonyEngine::Math::Abs(extents[1]));
	STATIC_REQUIRE(cuboid.Extent(2) == PonyEngine::Math::Abs(extents[2]));

	constexpr auto copy = test(cuboid);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(center + PonyEngine::Math::Vector3<float>(1.f), copy.Center()));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(3.f, 1.f, 5.f), copy.Extents()));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Extent(0), 3.f));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Extent(1), 1.f));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Extent(2), 5.f));
}

TEST_CASE("Box edge", "[Math][Box]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(6.f, cuboid.Edge(0)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(4.f, cuboid.Edge(1)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(12.f, cuboid.Edge(2)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(6.f, cuboid.Width()));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(4.f, cuboid.Height()));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(12.f, cuboid.Depth()));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(6.f, 4.f, 12.f), cuboid.Edges()));
}

TEST_CASE("Box surface", "[Math][Box]")
{
	constexpr auto extents2 = PonyEngine::Math::Vector2<float>(-3.f, 2.f);
	constexpr auto rect = PonyEngine::Math::Rect<float>(extents2);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(20.f, rect.Surface()));

	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(extents);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(288.f, cuboid.Surface()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Rect")
	{
		return PonyEngine::Math::Rect<float>(PonyEngine::Math::Vector2<float>(-3.f, 2.f)).Surface();
	};
	BENCHMARK("Cuboid")
	{
		return PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).Surface();
	};
#endif
}

TEST_CASE("Box volume", "[Math][Box]")
{
	constexpr auto extents2 = PonyEngine::Math::Vector2<float>(-3.f, 2.f);
	constexpr auto rect = PonyEngine::Math::Rect<float>(extents2);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(24.f, rect.Volume()));

	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(extents);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(288.f, cuboid.Volume()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Rect")
	{
		return PonyEngine::Math::Rect<float>(PonyEngine::Math::Vector2<float>(-3.f, 2.f)).Volume();
	};
	BENCHMARK("Cuboid")
	{
		return PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).Volume();
	};
#endif
}

TEST_CASE("Box min", "[Math][Box]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, cuboid.Min(0)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(-7.f, cuboid.Min(1)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(-5.f, cuboid.Min(2)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -7.f, -5.f), cuboid.Min()));
}

TEST_CASE("Box max", "[Math][Box]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(7.f, cuboid.Max(0)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(-3.f, cuboid.Max(1)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(7.f, cuboid.Max(2)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(7.f, -3.f, 7.f), cuboid.Max()));
}

TEST_CASE("Box corner", "[Math][Box]")
{
	constexpr auto center2 = PonyEngine::Math::Vector2<float>(4.f, -5.f);
	constexpr auto extents2 = PonyEngine::Math::Vector2<float>(-3.f, 2.f);
	constexpr auto rect = PonyEngine::Math::Rect<float>(center2, extents2);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(1.f, -7.f), rect.Corner(0)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(7.f, -7.f), rect.Corner(1)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(1.f, -3.f), rect.Corner(2)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(7.f, -3.f), rect.Corner(3)));
	constexpr std::array<PonyEngine::Math::Vector2<float>, 4> corners2 = rect.Corners();
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(1.f, -7.f), corners2[0]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(7.f, -7.f), corners2[1]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(1.f, -3.f), corners2[2]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(7.f, -3.f), corners2[3]));

	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -7.f, -5.f), cuboid.Corner(0)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(7.f, -7.f, -5.f), cuboid.Corner(1)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -3.f, -5.f), cuboid.Corner(2)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(7.f, -3.f, -5.f), cuboid.Corner(3)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -7.f, 7.f), cuboid.Corner(4)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(7.f, -7.f, 7.f), cuboid.Corner(5)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -3.f, 7.f), cuboid.Corner(6)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(7.f, -3.f, 7.f), cuboid.Corner(7)));
	constexpr std::array<PonyEngine::Math::Vector3<float>, 8> corners3 = cuboid.Corners();
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -7.f, -5.f), corners3[0]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(7.f, -7.f, -5.f), corners3[1]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -3.f, -5.f), corners3[2]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(7.f, -3.f, -5.f), corners3[3]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -7.f, 7.f), corners3[4]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(7.f, -7.f, 7.f), corners3[5]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -3.f, 7.f), corners3[6]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(7.f, -3.f, 7.f), corners3[7]));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Corner")
	{
		return PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).Corner(6);
	};
	BENCHMARK("Corners")
	{
		return PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).Corners();
	};
#endif
}

TEST_CASE("Box isFinite", "[Math][Box]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	STATIC_REQUIRE(cuboid.IsFinite());

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto cube = cuboid;
		auto cent = center;
		cent[i] = std::numeric_limits<float>::quiet_NaN();
		cube.Center(cent);
		REQUIRE_FALSE(cube.IsFinite());
		cube.Center(center);

		auto ext = extents;
		ext[i] = std::numeric_limits<float>::quiet_NaN();
		cube.Extents(ext);
		REQUIRE_FALSE(cube.IsFinite());
		cube.Extents(extents);
	}
}

TEST_CASE("Box contains", "[Math][Box]")
{
	constexpr float x = 7;
	constexpr float y = -8;
	constexpr float z = -12;
	constexpr float halfWidth = 4;
	constexpr float halfHeight = 14;
	constexpr float halfDepth = 2;
	constexpr auto aabb = PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(x, y, z), PonyEngine::Math::Vector3<float>(halfWidth, halfHeight, halfDepth));
	STATIC_REQUIRE(aabb.Contains(aabb.Center()));
	STATIC_REQUIRE(aabb.Contains(aabb.Min()));
	STATIC_REQUIRE(aabb.Contains(aabb.Max()));
	STATIC_REQUIRE(aabb.Contains(aabb.Center() + PonyEngine::Math::Vector3<float>(halfWidth, halfHeight, halfDepth) / 2.f));

	STATIC_REQUIRE_FALSE(aabb.Contains(PonyEngine::Math::Vector3<float>(100.f, y, z)));
	STATIC_REQUIRE_FALSE(aabb.Contains(PonyEngine::Math::Vector3<float>(x, -100.f, z)));
	STATIC_REQUIRE_FALSE(aabb.Contains(PonyEngine::Math::Vector3<float>(x, y, 178.f)));
	STATIC_REQUIRE_FALSE(aabb.Contains(aabb.Max() + PonyEngine::Math::Vector3<float>::One()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).Contains(PonyEngine::Math::Vector3<float>(2.f, -4.f, 0.f));
	};
#endif
}

TEST_CASE("Box closest point", "[Math][Box]")
{
	constexpr float x = 7;
	constexpr float y = -8;
	constexpr float z = -12;
	constexpr float halfWidth = 4;
	constexpr float halfHeight = 14;
	constexpr float halfDepth = 2;
	constexpr auto aabb = PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(x, y, z), PonyEngine::Math::Vector3<float>(halfWidth, halfHeight, halfDepth));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(aabb.Center(), aabb.ClosestPoint(aabb.Center())));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(aabb.Min(), aabb.ClosestPoint(aabb.Min())));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(aabb.Max(), aabb.ClosestPoint(aabb.Max())));
	constexpr auto vector0 = aabb.Center() + PonyEngine::Math::Vector3<float>(halfWidth, halfHeight, -halfDepth) / 2.f;
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(vector0, aabb.ClosestPoint(vector0)));

	constexpr auto vector1 = PonyEngine::Math::Vector3<float>(100.f, y, z);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(aabb.Max(0), y, z), aabb.ClosestPoint(vector1)));

	constexpr auto vector2 = PonyEngine::Math::Vector3<float>(x, -100.f, z);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(x, aabb.Min(1), z), aabb.ClosestPoint(vector2)));

	constexpr auto vector3 = PonyEngine::Math::Vector3<float>(x, y, 178.f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(x, y, aabb.Max(2)), aabb.ClosestPoint(vector3)));

	constexpr auto vector4 = PonyEngine::Math::Vector3<float>(-100.f, 100.f, 178.f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(aabb.Min(0), aabb.Max(1), aabb.Max(2)), aabb.ClosestPoint(vector4)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).ClosestPoint(PonyEngine::Math::Vector3<float>(-100.f, -6.f, 178.f));
	};
#endif
}

TEST_CASE("Box toString", "[Math][Box]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	const std::string expected = std::format("Center: {}, Extents: {}", center, PonyEngine::Math::Abs(extents));
	REQUIRE(expected == cuboid.ToString());
	std::ostringstream oss;
	oss << cuboid;
	REQUIRE(expected == oss.str());
	REQUIRE(expected == std::format("{}", cuboid));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).ToString();
	};
#endif
}

TEST_CASE("Box cast", "[Math][Box]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	constexpr auto cast = static_cast<PonyEngine::Math::Cuboid<double>>(cuboid);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(cast.Center(), static_cast<PonyEngine::Math::Vector3<double>>(center)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(cast.Extents(), static_cast<PonyEngine::Math::Vector3<double>>(PonyEngine::Math::Abs(extents))));
}

TEST_CASE("Box equals", "[Math][Box]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	STATIC_REQUIRE(cuboid == cuboid);
	auto copy = cuboid;
	REQUIRE(copy == cuboid);

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto cent = center;
		cent[i] += 0.000001f;
		copy.Center(cent);
		REQUIRE(copy != cuboid);
		cent[i] += 1.f;
		copy.Center(cent);
		REQUIRE(copy != cuboid);
		copy.Center(center);

		auto ext = extents;
		ext[i] -= 0.000001f;
		copy.Extents(ext);
		REQUIRE(copy != cuboid);
		ext[i] -= 1.f;
		copy.Extents(ext);
		REQUIRE(copy != cuboid);
		copy.Extents(extents);
	}
}

TEST_CASE("Box are almost equal", "[Math][Box]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::Cuboid<float>(center, extents);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(cuboid, cuboid));
	auto copy = cuboid;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, cuboid));

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto cent = center;
		cent[i] += 0.000001f;
		copy.Center(cent);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, cuboid));
		cent[i] += 1.f;
		copy.Center(cent);
		REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(copy, cuboid));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, cuboid, PonyEngine::Math::Tolerance{.absolute = 5.f}));
		copy.Center(center);

		auto ext = extents;
		ext[i] -= 0.000001f;
		copy.Extents(ext);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, cuboid));
		ext[i] -= 1.f;
		copy.Extents(ext);
		REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(copy, cuboid));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, cuboid, PonyEngine::Math::Tolerance{ .absolute = 5.f }));
		copy.Extents(extents);
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)), PonyEngine::Math::Cuboid<float>(PonyEngine::Math::Vector3<float>(3.f, -6.f, 3.f), PonyEngine::Math::Vector3<float>(-4.f, 3.f, 8.f)));
	};
#endif
}
