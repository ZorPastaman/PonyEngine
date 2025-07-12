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

TEST_CASE("Quaternion static", "[Math][Quaternion]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Quaternion<float>::ValueType, float>);
	STATIC_REQUIRE(PonyEngine::Math::Quaternion<float>::ComponentCount == 4uz);
}

TEST_CASE("Quaternion default constructor", "[Math][Quaternion]")
{
	STATIC_REQUIRE(PonyEngine::Math::Quaternion<float>() == PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.f, 0.f));
}

TEST_CASE("Quaternion main constructor", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	STATIC_REQUIRE(quaternion.X() == x);
	STATIC_REQUIRE(quaternion.Y() == y);
	STATIC_REQUIRE(quaternion.Z() == z);
	STATIC_REQUIRE(quaternion.W() == w);
}

TEST_CASE("Quaternion span constructor", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(std::array<float, 4>{x, y, z, w});
	STATIC_REQUIRE(quaternion.X() == x);
	STATIC_REQUIRE(quaternion.Y() == y);
	STATIC_REQUIRE(quaternion.Z() == z);
	STATIC_REQUIRE(quaternion.W() == w);
}

TEST_CASE("Quaternion from vector constructor", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(PonyEngine::Math::Vector4<float>(x, y, z, w));
	STATIC_REQUIRE(quaternion.X() == x);
	STATIC_REQUIRE(quaternion.Y() == y);
	STATIC_REQUIRE(quaternion.Z() == z);
	STATIC_REQUIRE(quaternion.W() == w);
}

TEST_CASE("Quaternion copy constructor", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto copy = quaternion;
	STATIC_REQUIRE(copy.X() == x);
	STATIC_REQUIRE(copy.Y() == y);
	STATIC_REQUIRE(copy.Z() == z);
	STATIC_REQUIRE(copy.W() == w);
}

TEST_CASE("Quaternion move constructor", "[Math][Quaternion]")
{
	auto move = []<std::floating_point T>(const PonyEngine::Math::Quaternion<T>& quaternion) constexpr
	{
		auto copy = quaternion;
		auto moved = std::move(copy);
		return moved;
	};

	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto moved = move(quaternion);
	STATIC_REQUIRE(moved.X() == x);
	STATIC_REQUIRE(moved.Y() == y);
	STATIC_REQUIRE(moved.Z() == z);
	STATIC_REQUIRE(moved.W() == w);
}

TEST_CASE("Quaternion predefined", "[Math][Quaternion]")
{
	STATIC_REQUIRE(PonyEngine::Math::Quaternion<float>::Identity() == PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.f, 1.f));
}

TEST_CASE("Quaternion access", "[Math][Quaternion]")
{
	auto access = []<std::floating_point T>(const PonyEngine::Math::Quaternion<T>& quaternion) constexpr
	{
		auto copy = quaternion;
		copy.X() -= 2.f;
		copy.Y() += 4.f;
		copy.Z() += 1.f;
		copy.W() -= 3.f;

		return copy;
	};

	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	STATIC_REQUIRE(quaternion.X() == x);
	STATIC_REQUIRE(quaternion.Y() == y);
	STATIC_REQUIRE(quaternion.Z() == z);
	STATIC_REQUIRE(quaternion.W() == w);
	constexpr auto copy = access(quaternion);
	STATIC_REQUIRE(copy.X() == x - 2.f);
	STATIC_REQUIRE(copy.Y() == y + 4.f);
	STATIC_REQUIRE(copy.Z() == z + 1.f);
	STATIC_REQUIRE(copy.W() == w - 3.f);
}

TEST_CASE("Quaternion span", "[Math][Quaternion]")
{
	auto access = []<std::floating_point T>(const PonyEngine::Math::Quaternion<T>&quaternion) constexpr
	{
		auto copy = quaternion;
		copy.Span()[0] -= 2.f;
		copy.Span()[1] += 4.f;
		copy.Span()[2] += 1.f;
		copy.Span()[3] -= 3.f;

		return copy;
	};

	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	STATIC_REQUIRE(quaternion.Span()[0] == x);
	STATIC_REQUIRE(quaternion.Span()[1] == y);
	STATIC_REQUIRE(quaternion.Span()[2] == z);
	STATIC_REQUIRE(quaternion.Span()[3] == w);
	constexpr auto copy = access(quaternion);
	STATIC_REQUIRE(copy.Span()[0] == x - 2.f);
	STATIC_REQUIRE(copy.Span()[1] == y + 4.f);
	STATIC_REQUIRE(copy.Span()[2] == z + 1.f);
	STATIC_REQUIRE(copy.Span()[3] == w - 3.f);
}

TEST_CASE("Quaternion magnitude", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	STATIC_REQUIRE(quaternion.MagnitudeSquared() == 30.f);
	REQUIRE(quaternion.Magnitude() == std::sqrt(30.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Magnitude")
	{
		return PonyEngine::Math::Quaternion<float>(2.f, -3.f, 4.f, 1.f).Magnitude();
	};
	BENCHMARK("Magnitude Squared")
	{
		return PonyEngine::Math::Quaternion<float>(2.f, -3.f, 4.f, 1.f).MagnitudeSquared();
	};
#endif
}

TEST_CASE("Quaternion conjugate", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto conjugate = quaternion.Conjugate();
	STATIC_REQUIRE(conjugate.X() == -x);
	STATIC_REQUIRE(conjugate.Y() == -y);
	STATIC_REQUIRE(conjugate.Z() == -z);
	STATIC_REQUIRE(conjugate.W() == w);

	auto normalized = quaternion.Normalized();
	auto normalizedConjugate = normalized.Conjugate();
	REQUIRE((normalized * normalizedConjugate).IsAlmostIdentity());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Quaternion<float>(2.f, -3.f, 4.f, 1.f).Conjugate();
	};
#endif
}

TEST_CASE("Quaternion inverse", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto inverse = quaternion.Inverse();
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(inverse.X(), -x / 30.f));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(inverse.Y(), -y / 30.f));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(inverse.Z(), -z / 30.f));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(inverse.W(), w / 30.f));
	STATIC_REQUIRE((quaternion * inverse).IsAlmostIdentity());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Quaternion<float>(2.f, -3.f, 4.f, 1.f).Inverse();
	};
#endif
}

TEST_CASE("Quaternion normalize", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	auto normalized = quaternion.Normalized();
	const auto magnitude = quaternion.Magnitude();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.X(), x / magnitude));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.Y(), y / magnitude));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.Z(), z / magnitude));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.W(), w / magnitude));

	quaternion.Normalize();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(quaternion, normalized));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Normalized")
	{
		return PonyEngine::Math::Quaternion<float>(2.f, -3.f, 4.f, 1.f).Normalized();
	};
	BENCHMARK("Normalize")
	{
		auto quaternion = PonyEngine::Math::Quaternion<float>(2.f, -3.f, 4.f, 1.f);
		quaternion.Normalize();
		return quaternion;
	};
#endif
}

TEST_CASE("Quaternion vector", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	STATIC_REQUIRE(quaternion.Vector() == PonyEngine::Math::Vector4<float>(x, y, z, w));
}

TEST_CASE("Quaternion isIdentity, isUnit", "[Math][Quaternion]")
{
	STATIC_REQUIRE(PonyEngine::Math::Quaternion<float>::Identity().IsIdentity());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Quaternion<float>(0.00000001f, 0.00000001f, -0.0000000001f, 1.00000000001f).IsIdentity());
	STATIC_REQUIRE(PonyEngine::Math::Quaternion<float>(0.00000001f, 0.00000001f, -0.0000000001f, 1.00000000001f).IsAlmostIdentity());
	STATIC_REQUIRE(PonyEngine::Math::Quaternion<float>(0.00000001f, 0.00000001f, -0.0000000001f, 2.f).IsAlmostIdentity<false>(3.f));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Quaternion<float>(0.00000001f, 0.00000001f, -0.0000000001f, 2.f).IsAlmostIdentity<false>());
	STATIC_REQUIRE(PonyEngine::Math::Quaternion<float>::Identity().IsUnit());
	STATIC_REQUIRE(PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f).IsUnit());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Quaternion<float>(1.0000001f, 0.f, 0.f, 0.f).IsUnit());
	STATIC_REQUIRE(PonyEngine::Math::Quaternion<float>(1.0000001f, 0.f, 0.f, 0.f).IsAlmostUnit());
	STATIC_REQUIRE(PonyEngine::Math::Quaternion<float>(1.0000000001f, 0.f, 0.f, 1.f).IsAlmostUnit(3.f));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Quaternion<float>(1.0000000001f, 0.f, 0.f, 1.f).IsAlmostUnit());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("IsIdentity")
	{
		return PonyEngine::Math::Quaternion<float>::Identity().IsIdentity() | PonyEngine::Math::Quaternion<float>(0.00000001f, 0.00000001f, -0.0000000001f, 1.00000000001f).IsIdentity();
	};
	BENCHMARK("IsAlmostIdentity")
	{
		return PonyEngine::Math::Quaternion<float>::Identity().IsAlmostIdentity() | PonyEngine::Math::Quaternion<float>(0.00000001f, 0.00000001f, -0.0000000001f, 1.00000000001f).IsAlmostIdentity();
	};
	BENCHMARK("IsAlmostIdentity not unit")
	{
		return PonyEngine::Math::Quaternion<float>::Identity().IsAlmostIdentity<false>() | PonyEngine::Math::Quaternion<float>(0.00000001f, 0.00000001f, -0.0000000001f, 1.00000000001f).IsAlmostIdentity<false>();
	};
	BENCHMARK("IsUnit")
	{
		return PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f).IsUnit() | PonyEngine::Math::Quaternion<float>(1.0000001f, 0.f, 0.f, 0.f).IsUnit();
	};
	BENCHMARK("IsAlmostUnit")
	{
		return PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f).IsAlmostUnit() | PonyEngine::Math::Quaternion<float>(1.0000001f, 0.f, 0.f, 0.f).IsAlmostUnit();
	};
#endif
}

TEST_CASE("Quaternion isFinite", "[Math][Quaternion]")
{
	STATIC_REQUIRE(PonyEngine::Math::Quaternion<float>::Identity().IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Quaternion<float>(std::numeric_limits<float>::quiet_NaN(), 0.f, 2.f, 1.f).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Quaternion<float>(4.f, std::numeric_limits<float>::quiet_NaN(), 2.f, 1.f).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Quaternion<float>(4.f, 0.f, std::numeric_limits<float>::quiet_NaN(), 1.f).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Quaternion<float>(4.f, 0.f, 2.f, std::numeric_limits<float>::quiet_NaN()).IsFinite());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Quaternion<float>(3.f, 4.f, -1.f, 2.f).IsFinite() | PonyEngine::Math::Quaternion<float>(3.f, 4.f, -1.f, std::numeric_limits<float>::quiet_NaN()).IsFinite();
	};
#endif
}

TEST_CASE("Quaternion ToString", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	const auto expected = std::format("({}, {}, {}, {})", x, y, z, w);

	REQUIRE(quaternion.ToString() == expected);

	std::ostringstream oss;
	oss << quaternion;
	REQUIRE(oss.str() == expected);

	REQUIRE(std::format("{}", quaternion) == expected);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Quaternion<float>(3.f, 4.f, -1.f, 2.f).ToString();
	};
#endif
}

TEST_CASE("Quaternion cast", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto quaternionDouble = static_cast<PonyEngine::Math::Quaternion<double>>(quaternion);
	STATIC_REQUIRE(quaternionDouble.X() == static_cast<double>(x));
	STATIC_REQUIRE(quaternionDouble.Y() == static_cast<double>(y));
	STATIC_REQUIRE(quaternionDouble.Z() == static_cast<double>(z));
	STATIC_REQUIRE(quaternionDouble.W() == static_cast<double>(w));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return static_cast<PonyEngine::Math::Quaternion<double>>(PonyEngine::Math::Quaternion<float>(3.f, 4.f, -1.f, 2.f));
	};
#endif
}

TEST_CASE("Quaternion access by index", "[Math][Quaternion]")
{
	auto access = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Quaternion<T>& quaternion) constexpr
	{
		auto copy = quaternion;
		copy[0] -= 2.f;
		copy[1] += 3.f;
		copy[2] += 1.f;
		copy[3] -= 4.f;
		return copy;
	};

	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	STATIC_REQUIRE(quaternion[0] == x);
	STATIC_REQUIRE(quaternion[1] == y);
	STATIC_REQUIRE(quaternion[2] == z);
	STATIC_REQUIRE(quaternion[3] == w);

	constexpr auto copy = access(quaternion);
	STATIC_REQUIRE(copy[0] == x - 2.f);
	STATIC_REQUIRE(copy[1] == y + 3.f);
	STATIC_REQUIRE(copy[2] == z + 1.f);
	STATIC_REQUIRE(copy[3] == w - 4.f);
}

TEST_CASE("Quaternion copy assignment", "[Math][Quaternion]")
{
	auto assign = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Quaternion<T>& quaternion) constexpr
	{
		auto copy = PonyEngine::Math::Quaternion<T>();
		copy = quaternion;

		return copy;
	};

	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto copy = assign(quaternion);
	STATIC_REQUIRE(copy.X() == x);
	STATIC_REQUIRE(copy.Y() == y);
	STATIC_REQUIRE(copy.Z() == z);
	STATIC_REQUIRE(copy.W() == w);
}

TEST_CASE("Quaternion move assignment", "[Math][Quaternion]")
{
	auto assign = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Quaternion<T>&quaternion) constexpr
	{
		auto copy = quaternion;
		auto moved = PonyEngine::Math::Quaternion<T>();
		moved = std::move(copy);
		return moved;
	};

	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto copy = assign(quaternion);
	STATIC_REQUIRE(copy.X() == x);
	STATIC_REQUIRE(copy.Y() == y);
	STATIC_REQUIRE(copy.Z() == z);
	STATIC_REQUIRE(copy.W() == w);
}

TEST_CASE("Quaternion product assignment", "[Math][Quaternion]")
{
	auto assign = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Quaternion<T>& quaternion, const PonyEngine::Math::Quaternion<T>& other) constexpr
	{
		auto copy = quaternion;
		copy *= other;
		return copy;
	};

	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr float x1 = 3.f;
	constexpr float y1 = 4.f;
	constexpr float z1 = -5.f;
	constexpr float w1 = -1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto quaternion1 = PonyEngine::Math::Quaternion<float>(x1, y1, z1, w1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual<false>(assign(quaternion, quaternion1), quaternion * quaternion1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto benchQuaternion = PonyEngine::Math::Quaternion<float>(3.f, 2.f, -1.f, -4.f);
		constexpr auto benchQuaternion1 = PonyEngine::Math::Quaternion<float>(2.f, 3.f, 1.f, 4.f);
		return benchQuaternion *= benchQuaternion1;
	};
#endif
}

TEST_CASE("Quaternion equals", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	STATIC_REQUIRE(quaternion == quaternion);
	STATIC_REQUIRE_FALSE(quaternion != quaternion);
	STATIC_REQUIRE_FALSE(quaternion == PonyEngine::Math::Add(quaternion, PonyEngine::Math::Quaternion<float>(0.000001f, 0.f, 0.f, 0.f)));
	STATIC_REQUIRE(quaternion != PonyEngine::Math::Add(quaternion, PonyEngine::Math::Quaternion<float>(0.000001f, 0.f, 0.f, 0.f)));
	STATIC_REQUIRE_FALSE(quaternion == PonyEngine::Math::Add(quaternion, PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.000001f, 0.f)));
	STATIC_REQUIRE(quaternion != PonyEngine::Math::Add(quaternion, PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.000001f, 0.f)));
}

TEST_CASE("Quaternion dot", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr float x1 = 3.f;
	constexpr float y1 = 4.f;
	constexpr float z1 = -5.f;
	constexpr float w1 = -1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto quaternion1 = PonyEngine::Math::Quaternion<float>(x1, y1, z1, w1);
	STATIC_REQUIRE(PonyEngine::Math::Dot(quaternion, quaternion1) == PonyEngine::Math::Dot(quaternion.Vector(), quaternion1.Vector()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Dot(PonyEngine::Math::Quaternion<float>(3.f, -2.f, 1.f, -4.f), PonyEngine::Math::Quaternion<float>(2.f, 3.f, -1.f, -5.f));
	};
#endif
}

TEST_CASE("Quaternion angle", "[Math][Quaternion]")
{
	float xR = 2;
	float yR = -3;
	float zR = 5;
	float wR = -5;
	auto quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
	float xL = -2;
	float yL = 3;
	float zL = -1;
	float wL = 2;
	auto quaternionL = PonyEngine::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.178f, PonyEngine::Math::Angle(quaternionL, quaternionR), 0.001f));
	xR = 2;
	yR = 3;
	zR = 5;
	wR = -5;
	quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
	xL = 2;
	yL = 3;
	zL = 1;
	wL = 2;
	quaternionL = PonyEngine::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.662f, PonyEngine::Math::Angle(quaternionL, quaternionR), 0.001f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.f, PonyEngine::Math::Angle(quaternionL, quaternionL)));
	xR = 3;
	yR = 2;
	zR = 2;
	wR = 1;
	quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
	xL = -2;
	yL = 3;
	zL = -1;
	wL = 2;
	quaternionL = PonyEngine::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, PonyEngine::Math::Angle(quaternionL, quaternionR)));
	xR = 0;
	yR = 1;
	zR = 0;
	wR = 0;
	quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
	xL = -2;
	yL = 3;
	zL = -1;
	wL = 2;
	quaternionL = PonyEngine::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, PonyEngine::Math::Angle(quaternionL, quaternionR), 0.001f));

#if PONY_ENGINE_TESTING_BENCHMARK
	const auto benchQuaternionL = PonyEngine::Math::Quaternion<float>(-3.f, 2.f, 1.f, -1.f).Normalized();
	const auto benchQuaternionR = PonyEngine::Math::Quaternion<float>(2.f, -2.f, 1.f, -1.f).Normalized();
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Angle(benchQuaternionL, benchQuaternionR);
	};
#endif
}

TEST_CASE("Quaternion add", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr float x1 = 3.f;
	constexpr float y1 = 4.f;
	constexpr float z1 = -5.f;
	constexpr float w1 = -1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto quaternion1 = PonyEngine::Math::Quaternion<float>(x1, y1, z1, w1);
	STATIC_REQUIRE(PonyEngine::Math::Add(quaternion, quaternion1) == PonyEngine::Math::Quaternion<float>(quaternion.Vector() + quaternion1.Vector()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Add(PonyEngine::Math::Quaternion<float>(2.f, -3.f, 4.f, 1.f), PonyEngine::Math::Quaternion<float>(3.f, 4.f, -5.f, -1.f));
	};
#endif
}

TEST_CASE("Quaternion negate", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	STATIC_REQUIRE(PonyEngine::Math::Negate(quaternion) == PonyEngine::Math::Quaternion<float>(-quaternion.Vector()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Negate(PonyEngine::Math::Quaternion<float>(2.f, -3.f, 4.f, 1.f));
	};
#endif
}

TEST_CASE("Quaternion subtract", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr float x1 = 3.f;
	constexpr float y1 = 4.f;
	constexpr float z1 = -5.f;
	constexpr float w1 = -1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto quaternion1 = PonyEngine::Math::Quaternion<float>(x1, y1, z1, w1);
	STATIC_REQUIRE(PonyEngine::Math::Subtract(quaternion, quaternion1) == PonyEngine::Math::Quaternion<float>(quaternion.Vector() - quaternion1.Vector()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Subtract(PonyEngine::Math::Quaternion<float>(2.f, -3.f, 4.f, 1.f), PonyEngine::Math::Quaternion<float>(3.f, 4.f, -5.f, -1.f));
	};
#endif
}

TEST_CASE("Quaternion multiply", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	STATIC_REQUIRE(PonyEngine::Math::Multiply(quaternion, 2.f) == PonyEngine::Math::Quaternion<float>(quaternion.Vector() * 2.f));
	STATIC_REQUIRE(PonyEngine::Math::Multiply(2.f, quaternion) == PonyEngine::Math::Quaternion<float>(quaternion.Vector() * 2.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Multiply(PonyEngine::Math::Quaternion<float>(2.f, -3.f, 4.f, 1.f), 2.f);
	};
#endif
}

TEST_CASE("Quaternion divide", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	STATIC_REQUIRE(PonyEngine::Math::Divide(quaternion, 2.f) == PonyEngine::Math::Quaternion<float>(quaternion.Vector() / 2.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Divide(PonyEngine::Math::Quaternion<float>(2.f, -3.f, 4.f, 1.f), 2.f);
	};
#endif
}

TEST_CASE("Quaternion lerp", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr float x1 = 3.f;
	constexpr float y1 = -4.f;
	constexpr float z1 = 1.f;
	constexpr float w1 = 3.f;

	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto quaternion1 = PonyEngine::Math::Quaternion<float>(x1, y1, z1, w1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual<false>(PonyEngine::Math::Lerp(quaternion, quaternion1, 0.f), quaternion));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual<false>(PonyEngine::Math::Lerp(quaternion, quaternion1, 1.f), quaternion1));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual<false>(PonyEngine::Math::Lerp(quaternion, quaternion1, 0.5f), PonyEngine::Math::Quaternion(PonyEngine::Math::Lerp(quaternion.Vector(), quaternion1.Vector(), 0.5f))));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual<false>(PonyEngine::Math::Lerp(quaternion, quaternion1, -1.f), PonyEngine::Math::Quaternion(PonyEngine::Math::Lerp(quaternion.Vector(), quaternion1.Vector(), -1.f))));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual<false>(PonyEngine::Math::Lerp(quaternion, quaternion1, 2.f), PonyEngine::Math::Quaternion(PonyEngine::Math::Lerp(quaternion.Vector(), quaternion1.Vector(), 2.f))));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Lerp(PonyEngine::Math::Quaternion<float>(3.f, -1.f, 2.f, 3.f), PonyEngine::Math::Quaternion<float>(-8.f, 7.f, 0.f, 2.f), 0.4f);
	};
#endif
}

TEST_CASE("Quaternion slerp", "[Math][Quaternion]")
{
	float xR = 2;
	float yR = 3;
	float zR = 5;
	float wR = 5;
	auto quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
	float xL = 2;
	float yL = 3;
	float zL = 1;
	float wL = 2;
	auto quaternionL = PonyEngine::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();

	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Slerp(quaternionL, quaternionR, 0.f), quaternionL));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Slerp(quaternionL, quaternionR, 1.f), quaternionR));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Slerp(quaternionL, quaternionR, 0.5f), PonyEngine::Math::Quaternion<float>(0.378f, 0.567f, 0.452f, 0.575f), 0.001f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Slerp(quaternionL, quaternionR.Conjugate(), 0.5f), PonyEngine::Math::Quaternion<float>(0.46f, 0.69f, 0.55f, -0.1f), 0.001f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Slerp(quaternionL, PonyEngine::Math::Negate(quaternionL), 0.5f), quaternionL));

	xR = 2;
	yR = 3;
	zR = 5;
	wR = 5;
	quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR).Normalized();
	xL = 3;
	yL = -2;
	zL = -5;
	wL = 5;
	quaternionL = PonyEngine::Math::Quaternion<float>(xL, yL, zL, wL).Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Slerp(quaternionL, quaternionR, 0.5f), PonyEngine::Math::Quaternion<float>(0.445f, 0.089f, 0.f, 0.891f), 0.001f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Slerp(PonyEngine::Math::Quaternion<float>(3.f, -1.f, 2.f, 3.f), PonyEngine::Math::Quaternion<float>(-8.f, 7.f, 0.f, 2.f), 0.6f);
	};
#endif
}

TEST_CASE("Quaternion are almost equal", "[Math][Quaternion]")
{
	constexpr float x = 2.f;
	constexpr float y = -3.f;
	constexpr float z = 4.f;
	constexpr float w = 1.f;
	constexpr float x1 = 3.f;
	constexpr float y1 = -4.f;
	constexpr float z1 = 1.f;
	constexpr float w1 = 3.f;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(x, y, z, w);
	constexpr auto quaternion1 = PonyEngine::Math::Quaternion<float>(x1, y1, z1, w1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual<false>(quaternion, quaternion));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual<false>(quaternion, quaternion1));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual<false>(quaternion, quaternion1, 5.f));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual<false>(quaternion, PonyEngine::Math::Quaternion<float>(x + 0.0000001f, y - 0.0000001f, z - 0.00000001f, w + 0.00000001f)));

	const auto quaternionN = quaternion.Normalized();
	const auto quaternionN1 = quaternion1.Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(quaternionN, quaternionN));
	REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(quaternionN, quaternionN1));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(quaternionN, quaternionN1, 5.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(quaternionN, PonyEngine::Math::Add(quaternionN, PonyEngine::Math::Quaternion<float>(0.0000000000001f, -0.00000000000001f, -0.0000000000001f, 0.00000000001f))));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Normalized")
	{
		return PonyEngine::Math::AreAlmostEqual(quaternionN, quaternionN1) | PonyEngine::Math::AreAlmostEqual(quaternionN, quaternionN);
	};
	BENCHMARK("Not normalized")
	{
		return PonyEngine::Math::AreAlmostEqual<false>(quaternion, quaternion1) | PonyEngine::Math::AreAlmostEqual<false>(quaternion, quaternion);
	};
#endif
}

TEST_CASE("Quaternion product", "[Math][Quaternion]")
{
	constexpr float xR = 2;
	constexpr float yR = -3;
	constexpr float zR = 5;
	constexpr float wR = -5;
	constexpr auto quaternionR = PonyEngine::Math::Quaternion<float>(xR, yR, zR, wR);
	constexpr float xL = -2;
	constexpr float yL = 3;
	constexpr float zL = -1;
	constexpr float wL = 2;
	constexpr auto quaternionL = PonyEngine::Math::Quaternion<float>(xL, yL, zL, wL);

	constexpr PonyEngine::Math::Quaternion<float> product = quaternionL * quaternionR;
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual<false>(quaternionL * quaternionR, PonyEngine::Math::Quaternion<float>(26.f, -13.f, 15.f, 8.f)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(quaternionL.Normalized() * quaternionR.Normalized(), PonyEngine::Math::Quaternion<float>(0.772f, -0.386f, 0.445f, 0.238f), 0.001f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Quaternion<float>(2.f, 3.f, -1.f, 2.f) * PonyEngine::Math::Quaternion<float>(-1.f, 0.f, 2.f, -3.f);
	};
#endif
}

TEST_CASE("Quaternion product vector", "[Math][Quaternion]")
{
	constexpr float x = 2;
	constexpr float y = -3;
	constexpr float z = 5;
	constexpr auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
	constexpr float xQ = -2;
	constexpr float yQ = 3;
	constexpr float zQ = -1;
	constexpr float wQ = 2;
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(xQ, yQ, zQ, wQ);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(quaternion * vector, PonyEngine::Math::Vector3<float>(66.f, 5.f, -99.f)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(quaternion.Normalized() * vector, PonyEngine::Math::Vector3<float>(5.556f, -2.556f, -0.778f), 0.001f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Quaternion<float>(2.f, 3.f, -1.f, 2.f) * PonyEngine::Math::Vector3<float>(-1.f, 0.f, 2.f);
	};
#endif
}
