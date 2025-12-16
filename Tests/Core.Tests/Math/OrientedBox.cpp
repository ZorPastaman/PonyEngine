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

TEST_CASE("OrientedBox static", "[Math][OrientedBox]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::OrientedRect<float>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::OrientedRect<float>::CenterType, PonyEngine::Math::Vector2<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::OrientedRect<float>::ExtentsType, PonyEngine::Math::Vector2<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::OrientedRect<float>::AxisType, PonyEngine::Math::Vector2<float>>);
	STATIC_REQUIRE(PonyEngine::Math::OrientedRect<float>::Dimension == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::OrientedRect<float>::CornerCount == 4uz);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::OrientedCuboid<float>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::OrientedCuboid<float>::CenterType, PonyEngine::Math::Vector3<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::OrientedCuboid<float>::ExtentsType, PonyEngine::Math::Vector3<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::OrientedCuboid<float>::AxisType, PonyEngine::Math::Vector3<float>>);
	STATIC_REQUIRE(PonyEngine::Math::OrientedCuboid<float>::Dimension == 3uz);
	STATIC_REQUIRE(PonyEngine::Math::OrientedCuboid<float>::CornerCount == 8uz);
}

TEST_CASE("OrientedBox default constructor", "[Math][OrientedBox]")
{
	constexpr auto obb = PonyEngine::Math::OrientedCuboid<float>();
	STATIC_REQUIRE(obb.Center() == PonyEngine::Math::Vector3<float>::Zero());
	STATIC_REQUIRE(obb.Extents() == PonyEngine::Math::Vector3<float>::Zero());
	STATIC_REQUIRE(obb.Axis(0) == PonyEngine::Math::Vector3<float>::Right());
	STATIC_REQUIRE(obb.Axis(1) == PonyEngine::Math::Vector3<float>::Up());
	STATIC_REQUIRE(obb.Axis(2) == PonyEngine::Math::Vector3<float>::Forward());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::OrientedCuboid<float>();
	};
#endif
}

TEST_CASE("OrientedBox extents constructor", "[Math][OrientedBox]")
{
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto obb = PonyEngine::Math::OrientedCuboid<float>(extents);
	STATIC_REQUIRE(obb.Center() == PonyEngine::Math::Vector3<float>::Zero());
	STATIC_REQUIRE(obb.Extents() == PonyEngine::Math::Abs(extents));
	STATIC_REQUIRE(obb.Axis(0) == PonyEngine::Math::Vector3<float>::Right());
	STATIC_REQUIRE(obb.Axis(1) == PonyEngine::Math::Vector3<float>::Up());
	STATIC_REQUIRE(obb.Axis(2) == PonyEngine::Math::Vector3<float>::Forward());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f));
	};
#endif
}

TEST_CASE("OrientedBox center extents constructor", "[Math][OrientedBox]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto obb = PonyEngine::Math::OrientedCuboid<float>(center, extents);
	STATIC_REQUIRE(obb.Center() == center);
	STATIC_REQUIRE(obb.Extents() == PonyEngine::Math::Abs(extents));
	STATIC_REQUIRE(obb.Axis(0) == PonyEngine::Math::Vector3<float>::Right());
	STATIC_REQUIRE(obb.Axis(1) == PonyEngine::Math::Vector3<float>::Up());
	STATIC_REQUIRE(obb.Axis(2) == PonyEngine::Math::Vector3<float>::Forward());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f));
	};
#endif
}

TEST_CASE("OrientedBox main constructor", "[Math][OrientedBox]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto right = PonyEngine::Math::Vector3<float>(2.f, 4.f, -3.f);
	constexpr auto up = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 5.f);
	constexpr auto forward = PonyEngine::Math::Vector3<float>(-4.f, 1.f, 2.f);
	const auto obb = PonyEngine::Math::OrientedCuboid<float>(center, extents, PonyEngine::Math::Matrix3x3<float>(right, up, forward));
	REQUIRE(obb.Center() == center);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Extent(0), -extents[0] * right.Magnitude()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Extent(1), extents[1] * up.Magnitude()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Extent(2), extents[2] * forward.Magnitude()));
	REQUIRE(obb.Axis(0) == right.Normalized());
	REQUIRE(obb.Axis(1) == up.Normalized());
	REQUIRE(obb.Axis(2) == forward.Normalized());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f),
			PonyEngine::Math::Matrix3x3<float>(PonyEngine::Math::Vector3<float>(2.f, 4.f, -3.f), PonyEngine::Math::Vector3<float>(-1.f, 0.f, 5.f), PonyEngine::Math::Vector3<float>(-4.f, 1.f, 2.f)));
	};
#endif
}

TEST_CASE("OrientedBox copy constructor", "[Math][OrientedBox]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto right = PonyEngine::Math::Vector3<float>(2.f, 4.f, -3.f);
	constexpr auto up = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 5.f);
	constexpr auto forward = PonyEngine::Math::Vector3<float>(-4.f, 1.f, 2.f);
	const auto obb = PonyEngine::Math::OrientedCuboid<float>(center, extents, PonyEngine::Math::Matrix3x3<float>(right, up, forward));
	const auto copy = obb;
	REQUIRE(copy == obb);
}

TEST_CASE("OrientedBox move constructor", "[Math][OrientedBox]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto right = PonyEngine::Math::Vector3<float>(2.f, 4.f, -3.f);
	constexpr auto up = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 5.f);
	constexpr auto forward = PonyEngine::Math::Vector3<float>(-4.f, 1.f, 2.f);
	auto obb = PonyEngine::Math::OrientedCuboid<float>(center, extents, PonyEngine::Math::Matrix3x3<float>(right, up, forward));
	const auto copy = std::move(obb);
	REQUIRE(copy == obb);
}

TEST_CASE("OrientedBox access center", "[Math][OrientedBox]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	auto obb = PonyEngine::Math::OrientedCuboid<float>();
	obb.Center(center);
	REQUIRE(obb.Center() == center);
}

TEST_CASE("OrientedBox access extent", "[Math][OrientedBox]")
{
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	auto obb = PonyEngine::Math::OrientedCuboid<float>();
	obb.Extent(1, extents[1]);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Extent(1), extents[1]));
	obb.Axis(0, PonyEngine::Math::Vector3<float>::Zero());
	obb.Extent(0, extents[0]);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Extent(0), 0.f));

	obb = PonyEngine::Math::OrientedCuboid<float>();
	obb.Axes(PonyEngine::Math::Matrix3x3<float>(PonyEngine::Math::Vector3<float>::Right(), PonyEngine::Math::Vector3<float>::Forward(), PonyEngine::Math::Vector3<float>::Zero()));
	obb.Extents(extents);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Extents(), PonyEngine::Math::Vector3<float>(-extents[0], extents[1], 0.f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("One")
	{
		auto cuboid = PonyEngine::Math::OrientedCuboid<float>();
		cuboid.Extent(2, -3.f);
		return cuboid;
	};
	BENCHMARK("Many")
	{
		auto cuboid = PonyEngine::Math::OrientedCuboid<float>();
		cuboid.Extents(PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f));
		return cuboid;
	};
#endif
}

TEST_CASE("OrientedBox access axis", "[Math][OrientedBox]")
{
	constexpr auto right = PonyEngine::Math::Vector3<float>(2.f, 4.f, -3.f);
	constexpr auto up = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 5.f);
	constexpr auto forward = PonyEngine::Math::Vector3<float>(-4.f, 1.f, 2.f);
	auto obb = PonyEngine::Math::OrientedCuboid<float>();
	obb.Axis(1, up);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Axis(1), up.Normalized()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Extent(1), 0.f));

	obb.Extent(2, 5.f);
	obb.Axis(2, forward);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Axis(2), forward.Normalized()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Extent(2), 5.f * forward.Magnitude()));

	obb.Extent(0, 8.f);
	obb.Axis(0, PonyEngine::Math::Vector3<float>::Zero());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Axis(0), PonyEngine::Math::Vector3<float>::Zero()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Extent(0), 0.f));

	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	obb = PonyEngine::Math::OrientedCuboid<float>(extents);
	obb.Axes(PonyEngine::Math::Matrix3x3<float>(right, up, forward));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Axis(0), right.Normalized()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Axis(1), up.Normalized()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Axis(2), forward.Normalized()));
	REQUIRE(obb.Axes().Column(0) == obb.Axis(0));
	REQUIRE(obb.Axes().Column(1) == obb.Axis(1));
	REQUIRE(obb.Axes().Column(2) == obb.Axis(2));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Extent(0), -extents[0] * right.Magnitude()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Extent(1), extents[1] * up.Magnitude()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Extent(2), extents[2] * forward.Magnitude()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("One")
	{
		auto cuboid = PonyEngine::Math::OrientedCuboid<float>();
		cuboid.Axis(0, PonyEngine::Math::Vector3<float>(-1.f, 0.f, 5.f));
		return cuboid;
	};
	BENCHMARK("Many")
	{
		auto cuboid = PonyEngine::Math::OrientedCuboid<float>();
		cuboid.Axes(PonyEngine::Math::Matrix3x3<float>(PonyEngine::Math::Vector3<float>(2.f, 4.f, -3.f), PonyEngine::Math::Vector3<float>(-1.f, 0.f, 5.f), PonyEngine::Math::Vector3<float>(-4.f, 1.f, 2.f)));
		return cuboid;
	};
#endif
}

TEST_CASE("OrientedBox edge", "[Math][OrientedBox]")
{
	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::OrientedCuboid<float>(extents);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(6.f, cuboid.Edge(0)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(4.f, cuboid.Edge(1)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(12.f, cuboid.Edge(2)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(6.f, 4.f, 12.f), cuboid.Edges()));
}

TEST_CASE("OrientedBox surface", "[Math][OrientedBox]")
{
	constexpr auto extents2 = PonyEngine::Math::Vector2<float>(-3.f, 2.f);
	constexpr auto rect = PonyEngine::Math::OrientedRect<float>(extents2);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(20.f, rect.Surface()));

	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::OrientedCuboid<float>(extents);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(288.f, cuboid.Surface()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Rect")
	{
		return PonyEngine::Math::OrientedRect<float>(PonyEngine::Math::Vector2<float>(-3.f, 2.f)).Surface();
	};
	BENCHMARK("Cuboid")
	{
		return PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).Surface();
	};
#endif
}

TEST_CASE("OrientedBox volume", "[Math][OrientedBox]")
{
	constexpr auto extents2 = PonyEngine::Math::Vector2<float>(-3.f, 2.f);
	constexpr auto rect = PonyEngine::Math::OrientedRect<float>(extents2);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(24.f, rect.Volume()));

	constexpr auto extents = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f);
	constexpr auto cuboid = PonyEngine::Math::OrientedCuboid<float>(extents);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(288.f, cuboid.Volume()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Rect")
	{
		return PonyEngine::Math::OrientedRect<float>(PonyEngine::Math::Vector2<float>(-3.f, 2.f)).Volume();
	};
	BENCHMARK("Cuboid")
	{
		return PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f)).Volume();
	};
#endif
}

TEST_CASE("OrientedBox corner", "[Math][OrientedBox]")
{
	constexpr auto center2 = PonyEngine::Math::Vector2<float>(4.f, -5.f);
	constexpr auto extents2 = PonyEngine::Math::Vector2<float>(3.f, 2.f);
	const auto axes2 = PonyEngine::Math::RotationMatrix(2.f);
	const auto rect = PonyEngine::Math::OrientedRect<float>(center2, extents2, axes2);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center2 + axes2 * PonyEngine::Math::Vector2<float>(-extents2[0], -extents2[1]), rect.Corner(0)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center2 + axes2 * PonyEngine::Math::Vector2<float>(extents2[0], -extents2[1]), rect.Corner(1)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center2 + axes2 * PonyEngine::Math::Vector2<float>(-extents2[0], extents2[1]), rect.Corner(2)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center2 + axes2 * PonyEngine::Math::Vector2<float>(extents2[0], extents2[1]), rect.Corner(3)));
	const std::array<PonyEngine::Math::Vector2<float>, 4> corners2 = rect.Corners();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center2 + axes2 * PonyEngine::Math::Vector2<float>(-extents2[0], -extents2[1]), corners2[0]));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center2 + axes2 * PonyEngine::Math::Vector2<float>(extents2[0], -extents2[1]), corners2[1]));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center2 + axes2 * PonyEngine::Math::Vector2<float>(-extents2[0], extents2[1]), corners2[2]));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center2 + axes2 * PonyEngine::Math::Vector2<float>(extents2[0], extents2[1]), corners2[3]));

	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f);
	const auto axes3 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(2.3f, -1.8f, 3.f));
	const auto cuboid = PonyEngine::Math::OrientedCuboid<float>(center, extents, axes3);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(-extents[0], -extents[1], -extents[2]), cuboid.Corner(0)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(extents[0], -extents[1], -extents[2]), cuboid.Corner(1)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(-extents[0], extents[1], -extents[2]), cuboid.Corner(2)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(extents[0], extents[1], -extents[2]), cuboid.Corner(3)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(-extents[0], -extents[1], extents[2]), cuboid.Corner(4)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(extents[0], -extents[1], extents[2]), cuboid.Corner(5)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(-extents[0], extents[1], extents[2]), cuboid.Corner(6)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(extents[0], extents[1], extents[2]), cuboid.Corner(7)));
	const std::array<PonyEngine::Math::Vector3<float>, 8> corners3 = cuboid.Corners();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(-extents[0], -extents[1], -extents[2]), corners3[0]));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(extents[0], -extents[1], -extents[2]), corners3[1]));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(-extents[0], extents[1], -extents[2]), corners3[2]));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(extents[0], extents[1], -extents[2]), corners3[3]));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(-extents[0], -extents[1], extents[2]), corners3[4]));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(extents[0], -extents[1], extents[2]), corners3[5]));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(-extents[0], extents[1], extents[2]), corners3[6]));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(center + axes3 * PonyEngine::Math::Vector3<float>(extents[0], extents[1], extents[2]), corners3[7]));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Corner")
	{
		return PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f), axes3).Corner(6);
	};
	BENCHMARK("Corners")
	{
		return PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(-3.f, 2.f, 6.f), axes3).Corners();
	};
#endif
}

TEST_CASE("OrientedBox isFinite", "[Math][OrientedBox]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f);
	const auto axes3 = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(2.3f, -1.8f, 3.f));
	auto cuboid = PonyEngine::Math::OrientedCuboid<float>(center, extents, axes3);
	REQUIRE(cuboid.IsFinite());

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto c = cuboid.Center();
		c[i] = std::numeric_limits<float>::quiet_NaN();
		cuboid.Center(c);
		REQUIRE_FALSE(cuboid.IsFinite());
		c[i] = center[i];
		cuboid.Center(c);
	}

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto e = cuboid.Extents();
		e[i] = std::numeric_limits<float>::quiet_NaN();
		cuboid.Extents(e);
		REQUIRE_FALSE(cuboid.IsFinite());
		e[i] = extents[i];
		cuboid.Extents(e);
	}
}

TEST_CASE("OrientedBox are axes perpendicular", "[Math][OrientedBox]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f);
	auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(2.3f, -1.8f, 3.f));
	auto cuboid = PonyEngine::Math::OrientedCuboid<float>(center, extents, axes);
	REQUIRE(cuboid.AreAxesPerpendicular());

	axes.Column(0) = -axes.Column(0);
	cuboid.Axes(axes);
	REQUIRE(cuboid.AreAxesPerpendicular());

	axes.Column(1) = axes.Column(0);
	cuboid.Axes(axes);
	REQUIRE_FALSE(cuboid.AreAxesPerpendicular());

	axes.Column(1) = PonyEngine::Math::Vector3<float>(-2.f, 2.f, 8.f).Normalized();
	cuboid.Axes(axes);
	REQUIRE_FALSE(cuboid.AreAxesPerpendicular());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f)).AreAxesPerpendicular();
	};
#endif
}

TEST_CASE("OrientedBox has zero axis", "[Math][OrientedBox]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f);
	auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(2.3f, -1.8f, 3.f));
	auto cuboid = PonyEngine::Math::OrientedCuboid<float>(center, extents, axes);
	REQUIRE_FALSE(cuboid.HasZeroAxis());

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto ax = axes;
		ax.Column(i) = PonyEngine::Math::Vector3<float>::Zero();
		cuboid.Axes(ax);
		REQUIRE(cuboid.HasZeroAxis());
		cuboid.Axes(axes);
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(4.f, -5.f, 1.f), PonyEngine::Math::Vector3<float>(3.f, 2.f, 6.f)).HasZeroAxis();
	};
#endif
}

TEST_CASE("OrientedBox contains", "[Math][OrientedBox]")
{
	const auto obb = PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(3.f, 5.f, 7.f), PonyEngine::Math::Vector3<float>(2.f, 5.f, 1.f), PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(1.1f, 0.7f, -1.2f)));
	REQUIRE(obb.Contains(obb.Center()));
	REQUIRE(obb.Contains(obb.Center() + obb.Axis(0) * obb.Extent(0) * 0.75f - obb.Axis(1) * obb.Extent(1) * 0.5f + obb.Axis(2) * obb.Extent(2) * 0.2f));
	REQUIRE(obb.Contains(obb.Center() - obb.Axis(0) * obb.Extent(0) * 0.75f + obb.Axis(1) * obb.Extent(1) * 0.5f - obb.Axis(2) * obb.Extent(2) * 0.2f));
	REQUIRE_FALSE(obb.Contains(obb.Center() + obb.Axis(0) * obb.Extent(0) * 1.75f - obb.Axis(1) * obb.Extent(1) * 0.5f + obb.Axis(2) * obb.Extent(2) * 0.2f));
	REQUIRE_FALSE(obb.Contains(obb.Center() + obb.Axis(0) * obb.Extent(0) * 0.75f - obb.Axis(1) * obb.Extent(1) * 1.05f - obb.Axis(2) * obb.Extent(2) * 1.2f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(3.f, 5.f, 7.f), PonyEngine::Math::Vector3<float>(2.f, 5.f, 1.f)).Contains(PonyEngine::Math::Vector3<float>(4.f, 4.f, 7.f));
	};
#endif
}

TEST_CASE("OrientedBox closest point", "[Math][OrientedBox]")
{
	const auto obb = PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(3.f, 5.f, 7.f), PonyEngine::Math::Vector3<float>(2.f, 5.f, 1.f), PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(1.1f, 0.7f, -1.2f)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb.Center(), obb.ClosestPoint(obb.Center())));
	auto expected = obb.Center() + PonyEngine::Math::Vector3<float>(-0.5f, 1.f, 0.5f);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expected, obb.ClosestPoint(expected)));
	constexpr auto test = PonyEngine::Math::Vector3<float>(13.f, 15.f, -7.f);
	expected = PonyEngine::Math::Vector3<float>(6.7964f, 5.8675f, 3.1484f);
	const auto t = obb.ClosestPoint(test);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expected, obb.ClosestPoint(test), PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(3.f, 5.f, 7.f), PonyEngine::Math::Vector3<float>(2.f, 5.f, 1.f)).ClosestPoint(PonyEngine::Math::Vector3<float>(13.f, 15.f, -7.f));
	};
#endif
}

TEST_CASE("OrientedBox cast", "[Math][OrientedBox]")
{
	const auto obb = PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(3.f, 5.f, 7.f), PonyEngine::Math::Vector3<float>(2.f, 5.f, 1.f), PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(1.1f, 0.7f, -1.2f)));
	const auto cast = static_cast<PonyEngine::Math::OrientedCuboid<double>>(obb);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(cast.Center(), PonyEngine::Math::Vector3<double>(obb.Center())));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(cast.Extents(), PonyEngine::Math::Vector3<double>(obb.Extents())));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(cast.Axes(), PonyEngine::Math::Matrix3x3<double>(obb.Axes())));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return static_cast<PonyEngine::Math::OrientedCuboid<double>>(PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(3.f, 5.f, 7.f), PonyEngine::Math::Vector3<float>(2.f, 5.f, 1.f)));
	};
#endif
}

TEST_CASE("OrientedBox copy assignment", "[Math][OrientedBox]")
{
	const auto obb = PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(3.f, 5.f, 7.f), PonyEngine::Math::Vector3<float>(2.f, 5.f, 1.f), PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(1.1f, 0.7f, -1.2f)));
	auto copy = PonyEngine::Math::OrientedCuboid<float>();
	copy = obb;
	REQUIRE(copy == obb);
}

TEST_CASE("OrientedBox move assignment", "[Math][OrientedBox]")
{
	auto obb = PonyEngine::Math::OrientedCuboid<float>(PonyEngine::Math::Vector3<float>(3.f, 5.f, 7.f), PonyEngine::Math::Vector3<float>(2.f, 5.f, 1.f), PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(1.1f, 0.7f, -1.2f)));
	auto copy = PonyEngine::Math::OrientedCuboid<float>();
	copy = std::move(obb);
	REQUIRE(copy == obb);
}

TEST_CASE("OrientedBox equals", "[Math][OrientedBox]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(3.f, 5.f, 7.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(2.f, 5.f, 1.f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(1.1f, 0.7f, -1.2f));
	const auto obb = PonyEngine::Math::OrientedCuboid<float>(center, extents, axes);
	REQUIRE(obb == obb);
	auto copy = obb;
	REQUIRE(copy == obb);

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto cent = center;
		cent[i] += 0.000001f;
		copy.Center(cent);
		REQUIRE(copy != obb);
		cent[i] -= 1.f;
		copy.Center(cent);
		REQUIRE(copy != obb);
		copy.Center(center);
	}

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto ext = extents;
		ext[i] += 0.000001f;
		copy.Extents(ext);
		REQUIRE(copy != obb);
		ext[i] -= 1.f;
		copy.Extents(ext);
		REQUIRE(copy != obb);
		copy.Extents(extents);
	}

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto ax = axes;
		ax.Column(i) = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(0.000001f, -0.000002f, -0.00001f)) * ax.Column(i);
		copy.Axes(ax);
		copy.Extents(extents);
		REQUIRE(copy != obb);
		ax.Column(i) += PonyEngine::Math::Vector3<float>(-1.f, 2.f, -3.f);
		copy.Axes(ax);
		copy.Extents(extents);
		REQUIRE(copy != obb);
		copy.Axes(axes);
		copy.Extents(extents);
	}
}

TEST_CASE("OrientedBox are almost equal", "[Math][OrientedBox]")
{
	constexpr auto center = PonyEngine::Math::Vector3<float>(3.f, 5.f, 7.f);
	constexpr auto extents = PonyEngine::Math::Vector3<float>(2.f, 5.f, 1.f);
	const auto axes = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(1.1f, 0.7f, -1.2f));
	const auto obb = PonyEngine::Math::OrientedCuboid<float>(center, extents, axes);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(obb, obb));
	auto copy = obb;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, obb));

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto cent = center;
		cent[i] += 0.000001f;
		copy.Center(cent);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, obb));
		cent[i] -= 1.f;
		copy.Center(cent);
		REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(copy, obb));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, obb, PonyEngine::Math::Tolerance{.absolute = 5.f}));
		copy.Center(center);
	}

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto ext = extents;
		ext[i] += 0.0000001f;
		copy.Extents(ext);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, obb));
		ext[i] -= 1.f;
		copy.Extents(ext);
		REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(copy, obb));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, obb, PonyEngine::Math::Tolerance{.absolute = 5.f}));
		copy.Extents(extents);
	}

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto ax = axes;
		ax.Column(i) = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(0.000001f, -0.000002f, -0.00001f)) * ax.Column(i);
		copy.Axes(ax);
		copy.Extents(extents);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, obb));
		ax.Column(i) += PonyEngine::Math::Vector3<float>(-1.f, 2.f, -3.f);
		copy.Axes(ax);
		copy.Extents(extents);
		REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(copy, obb));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(copy, obb, PonyEngine::Math::Tolerance{.absolute = 10.f}));
		copy.Axes(axes);
		copy.Extents(extents);
	}
}
