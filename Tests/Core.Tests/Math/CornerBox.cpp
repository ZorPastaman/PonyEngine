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

TEST_CASE("CornerBox static", "[Math][CornerBox]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::CornerBox<std::int32_t, 2>::ValueType, std::int32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::CornerBox<std::int32_t, 2>::PositionType, PonyEngine::Math::Vector2<std::int32_t>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::CornerBox<std::int32_t, 2>::SizeType, PonyEngine::Math::Vector2<std::int32_t>>);
	STATIC_REQUIRE(PonyEngine::Math::CornerBox<std::int32_t, 2>::Dimension == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::CornerBox<std::int32_t, 2>::CornerCount == 4uz);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::CornerBox<float, 3>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::CornerBox<float, 3>::PositionType, PonyEngine::Math::Vector3<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::CornerBox<float, 3>::SizeType, PonyEngine::Math::Vector3<float>>);
	STATIC_REQUIRE(PonyEngine::Math::CornerBox<float, 3>::Dimension == 3uz);
	STATIC_REQUIRE(PonyEngine::Math::CornerBox<float, 3>::CornerCount == 8uz);
}

TEST_CASE("CornerBox default constructor", "[Math][CornerBox]")
{
	STATIC_REQUIRE(PonyEngine::Math::CornerRect<std::int32_t>() == PonyEngine::Math::CornerRect<std::int32_t>(PonyEngine::Math::Vector2<std::int32_t>::Zero(), PonyEngine::Math::Vector2<std::int32_t>::Zero()));
	STATIC_REQUIRE(PonyEngine::Math::CornerCuboid<float>() == PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>::Zero(), PonyEngine::Math::Vector3<float>::Zero()));
}

TEST_CASE("CornerBox size constructor", "[Math][CornerBox]")
{
	constexpr auto size2 = PonyEngine::Math::Vector2<float>(-3.f, 2.f);
	constexpr auto rect = PonyEngine::Math::CornerRect<float>(size2);
	STATIC_REQUIRE(rect.Position() == PonyEngine::Math::Vector2<float>::Zero());
	STATIC_REQUIRE(rect.Size() == size2);

	constexpr auto size3 = PonyEngine::Math::Vector3<std::int32_t>(-3, 2, 6);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<std::int32_t>(size3);
	STATIC_REQUIRE(cuboid.Position() == PonyEngine::Math::Vector3<std::int32_t>::Zero());
	STATIC_REQUIRE(cuboid.Size() == size3);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f));
	};
#endif
}

TEST_CASE("CornerBox main constructor", "[Math][CornerBox]")
{
	constexpr auto position2 = PonyEngine::Math::Vector2<float>(4.f, -5.f);
	constexpr auto size2 = PonyEngine::Math::Vector2<float>(-3.f, 2.f);
	constexpr auto rect = PonyEngine::Math::CornerRect<float>(position2, size2);
	STATIC_REQUIRE(rect.Position() == position2);
	STATIC_REQUIRE(rect.Size() == size2);

	constexpr auto position3 = PonyEngine::Math::Vector3<std::int32_t>(4, -5, 1);
	constexpr auto size3 = PonyEngine::Math::Vector3<std::int32_t>(-3, 2, 6);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<std::int32_t>(position3, size3);
	STATIC_REQUIRE(cuboid.Position() == position3);
	STATIC_REQUIRE(cuboid.Size() == size3);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f));
	};
#endif
}

TEST_CASE("CornerBox copy constructor", "[Math][CornerBox]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto size = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<float>(position, size);
	constexpr auto copy = cuboid;
	STATIC_REQUIRE(copy.Position() == position);
	STATIC_REQUIRE(copy.Size() == size);
}

TEST_CASE("CornerBox move constructor", "[Math][CornerBox]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t Size>(const PonyEngine::Math::CornerBox<T, Size>& cornerbox) constexpr
	{
		auto copy = cornerbox;
		auto moved = std::move(copy);
		return moved;
	};

	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto size = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<float>(position, size);
	constexpr auto moved = test(cuboid);
	STATIC_REQUIRE(moved.Position() == position);
	STATIC_REQUIRE(moved.Size() == size);
}

TEST_CASE("CornerBox access", "[Math][CornerBox]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t Size>(const PonyEngine::Math::CornerBox<T, Size>& cornerbox) constexpr
	{
		auto copy = cornerbox;
		copy.Position(cornerbox.Position() + PonyEngine::Math::Vector<T, Size>(T{1}));
		copy.Size(cornerbox.Size() - PonyEngine::Math::Vector<T, Size>(T{1}));
		return copy;
	};

	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto size = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<float>(position, size);
	STATIC_REQUIRE(cuboid.Position() == position);
	STATIC_REQUIRE(cuboid.Size() == size);

	constexpr auto copy = test(cuboid);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(position + PonyEngine::Math::Vector3<float>(1.f), copy.Position()));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-4.f, 1.f, 5.f), copy.Size()));
}

TEST_CASE("CornerBox surface", "[Math][CornerBox]")
{
	constexpr auto size2 = PonyEngine::Math::Vector2<float>(-6.f, 4.f);
	constexpr auto rect = PonyEngine::Math::CornerRect<float>(size2);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(20.f, rect.Surface()));

	constexpr auto size = PonyEngine::Math::Vector3<float>(-6.f, 4.f, 12.f);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<float>(size);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(288.f, cuboid.Surface()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Rect")
	{
		return PonyEngine::Math::CornerRect<float>(PonyEngine::Math::Vector2<float>(-3.f, 2.f)).Surface();
	};
	BENCHMARK("Cuboid")
	{
		return PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).Surface();
	};
#endif
}

TEST_CASE("CornerBox volume", "[Math][CornerBox]")
{
	constexpr auto size2 = PonyEngine::Math::Vector2<float>(-6.f, 4.f);
	constexpr auto rect = PonyEngine::Math::CornerRect<float>(size2);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(24.f, rect.Volume()));

	constexpr auto size = PonyEngine::Math::Vector3<float>(-6.f, 4.f, 12.f);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<float>(size);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(288.f, cuboid.Volume()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Rect")
	{
		return PonyEngine::Math::CornerRect<float>(PonyEngine::Math::Vector2<float>(-3.f, 2.f)).Volume();
	};
	BENCHMARK("Cuboid")
	{
		return PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).Volume();
	};
#endif
}

TEST_CASE("CornerBox min", "[Math][CornerBox]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto size = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<float>(position, size);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(4.f, cuboid.Min(0)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(-5.f, cuboid.Min(1)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, cuboid.Min(2)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), cuboid.Min()));
}

TEST_CASE("CornerBox max", "[Math][CornerBox]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto size = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<float>(position, size);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, cuboid.Max(0)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(-3.f, cuboid.Max(1)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(7.f, cuboid.Max(2)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -3.f, 7.f), cuboid.Max()));
}

TEST_CASE("CornerBox corner", "[Math][CornerBox]")
{
	constexpr auto position2 = PonyEngine::Math::Vector2<float>(4.f, -5.f);
	constexpr auto size2 = PonyEngine::Math::Vector2<float>(-3.f, 2.f);
	constexpr auto rect = PonyEngine::Math::CornerRect<float>(position2, size2);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(4.f, -5.f), rect.Corner(0)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(1.f, -5.f), rect.Corner(1)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(4.f, -3.f), rect.Corner(2)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(1.f, -3.f), rect.Corner(3)));
	constexpr std::array<PonyEngine::Math::Vector2<float>, 4> corners2 = rect.Corners();
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(4.f, -5.f), corners2[0]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(1.f, -5.f), corners2[1]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(4.f, -3.f), corners2[2]));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(1.f, -3.f), corners2[3]));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Corner")
	{
		return PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).Corner(6);
	};
	BENCHMARK("Corners")
	{
		return PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).Corners();
	};
#endif
}

TEST_CASE("CornerBox resolve negative", "[Math][CornerBox]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto size = PonyEngine::Math::Vector3<float>(-3.f, 2.f, -6.f);
	auto cuboid = PonyEngine::Math::CornerCuboid<float>(position, size);
	cuboid.ResolveNegativeSize();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -5.f, -5.f), cuboid.Position()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f), cuboid.Size()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto box = PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f));
		box.ResolveNegativeSize();
		return box;
	};
#endif
}

TEST_CASE("CornerBox isFinite", "[Math][CornerBox]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto size = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<float>(position, size);
	STATIC_REQUIRE(cuboid.IsFinite());

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto cube = cuboid;
		auto cent = position;
		cent[i] = std::numeric_limits<float>::quiet_NaN();
		cube.Position(cent);
		REQUIRE_FALSE(cube.IsFinite());
		cube.Position(position);

		auto ext = size;
		ext[i] = std::numeric_limits<float>::quiet_NaN();
		cube.Size(ext);
		REQUIRE_FALSE(cube.IsFinite());
		cube.Size(size);
	}
}

TEST_CASE("CornerBox contains", "[Math][CornerBox]")
{
	constexpr float x = 7;
	constexpr float y = -8;
	constexpr float z = -12;
	constexpr float width = 4;
	constexpr float height = 14;
	constexpr float depth = 2;
	constexpr auto aabb = PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(x, y, z), PonyEngine::Math::Vector3<float>(width, height, depth));
	STATIC_REQUIRE(aabb.Contains(aabb.Position()));
	STATIC_REQUIRE(aabb.Contains(aabb.Min()));
	STATIC_REQUIRE(aabb.Contains(aabb.Max()));
	STATIC_REQUIRE(aabb.Contains(aabb.Position() + PonyEngine::Math::Vector3<float>(width, height, depth) / 2.f));

	STATIC_REQUIRE_FALSE(aabb.Contains(PonyEngine::Math::Vector3<float>(100.f, y, z)));
	STATIC_REQUIRE_FALSE(aabb.Contains(PonyEngine::Math::Vector3<float>(x, -100.f, z)));
	STATIC_REQUIRE_FALSE(aabb.Contains(PonyEngine::Math::Vector3<float>(x, y, 178.f)));
	STATIC_REQUIRE_FALSE(aabb.Contains(aabb.Max() + PonyEngine::Math::Vector3<float>::One()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).Contains(PonyEngine::Math::Vector3<float>(2.f, -4.f, 0.f));
	};
#endif
}

TEST_CASE("CornerBox closest point", "[Math][CornerBox]")
{
	constexpr float x = 7;
	constexpr float y = -8;
	constexpr float z = -12;
	constexpr float width = 4;
	constexpr float height = 14;
	constexpr float depth = 2;
	constexpr auto aabb = PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(x, y, z), PonyEngine::Math::Vector3<float>(width, height, depth));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(aabb.Position(), aabb.ClosestPoint(aabb.Position())));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(aabb.Min(), aabb.ClosestPoint(aabb.Min())));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(aabb.Max(), aabb.ClosestPoint(aabb.Max())));
	constexpr auto vector0 = aabb.Position() + PonyEngine::Math::Vector3<float>(width, height, depth) / 2.f;
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
		return PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).ClosestPoint(PonyEngine::Math::Vector3<float>(-100.f, -6.f, 178.f));
	};
#endif
}

TEST_CASE("CornerBox cast", "[Math][CornerBox]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto size = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<float>(position, size);
	constexpr auto cast = static_cast<PonyEngine::Math::CornerCuboid<double>>(cuboid);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(cast.Position(), static_cast<PonyEngine::Math::Vector3<double>>(position)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(cast.Size(), static_cast<PonyEngine::Math::Vector3<double>>(size)));
}

TEST_CASE("CornerBox equals", "[Math][CornerBox]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto size = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<float>(position, size);
	STATIC_REQUIRE(cuboid == cuboid);
	auto copy = cuboid;
	REQUIRE(copy == cuboid);

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto cent = position;
		cent[i] += 0.000001f;
		copy.Position(cent);
		REQUIRE(copy != cuboid);
		cent[i] += 1.f;
		copy.Position(cent);
		REQUIRE(copy != cuboid);
		copy.Position(position);

		auto ext = size;
		ext[i] -= 0.000001f;
		copy.Size(ext);
		REQUIRE(copy != cuboid);
		ext[i] -= 1.f;
		copy.Size(ext);
		REQUIRE(copy != cuboid);
		copy.Size(size);
	}
}

TEST_CASE("CornerBox are almost equal", "[Math][CornerBox]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto size = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::CornerCuboid<float>(position, size);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(cuboid, cuboid));
	auto copy = cuboid;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, cuboid));

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto cent = position;
		cent[i] += 0.000001f;
		copy.Position(cent);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, cuboid));
		cent[i] += 1.f;
		copy.Position(cent);
		REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(copy, cuboid));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, cuboid, PonyEngine::Math::Tolerance{ .absolute = 5.f }));
		copy.Position(position);

		auto ext = size;
		ext[i] -= 0.000001f;
		copy.Size(ext);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, cuboid));
		ext[i] -= 1.f;
		copy.Size(ext);
		REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(copy, cuboid));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, cuboid, PonyEngine::Math::Tolerance{ .absolute = 5.f }));
		copy.Size(size);
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)), PonyEngine::Math::CornerCuboid<float>(PonyEngine::Math::Vector3<float>(3.f, -6.f, 3.f), PonyEngine::Math::Vector3<float>(-4.f, 3.f, 8.f)));
	};
#endif
}
