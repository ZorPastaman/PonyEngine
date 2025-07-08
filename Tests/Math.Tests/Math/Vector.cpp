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

TEST_CASE("Vector2 static", "[Math][Vector]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector2<std::int32_t>::ValueType, std::int32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector2<std::uint32_t>::ValueType, std::uint32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector2<float>::ValueType, float>);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector2<std::int32_t>::ComputationalType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector2<std::uint32_t>::ComputationalType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector2<float>::ComputationalType, float>);

	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::ComponentCount == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::uint32_t>::ComponentCount == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::ComponentCount == 2uz);
}

TEST_CASE("Vector2 predefined", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Predefined::Up == PonyEngine::Math::Vector2<std::int32_t>(0, 1));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Predefined::Down == PonyEngine::Math::Vector2<std::int32_t>(0, -1));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Predefined::Right == PonyEngine::Math::Vector2<std::int32_t>(1, 0));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Predefined::Left == PonyEngine::Math::Vector2<std::int32_t>(-1, 0));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Predefined::One == PonyEngine::Math::Vector2<std::int32_t>(1, 1));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Predefined::Zero == PonyEngine::Math::Vector2<std::int32_t>(0, 0));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Predefined::Negative == PonyEngine::Math::Vector2<std::int32_t>(-1, -1));

	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::uint32_t>::Predefined::Up == PonyEngine::Math::Vector2<std::uint32_t>(0u, 1u));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::uint32_t>::Predefined::Right == PonyEngine::Math::Vector2<std::uint32_t>(1u, 0u));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::uint32_t>::Predefined::One == PonyEngine::Math::Vector2<std::uint32_t>(1u, 1u));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::uint32_t>::Predefined::Zero == PonyEngine::Math::Vector2<std::uint32_t>(0u, 0u));

	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Predefined::Up == PonyEngine::Math::Vector2<float>(0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Predefined::Down == PonyEngine::Math::Vector2<float>(0.f, -1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Predefined::Right == PonyEngine::Math::Vector2<float>(1.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Predefined::Left == PonyEngine::Math::Vector2<float>(-1.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Predefined::One == PonyEngine::Math::Vector2<float>(1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Predefined::Zero == PonyEngine::Math::Vector2<float>(0.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Predefined::Negative == PonyEngine::Math::Vector2<float>(-1.f, -1.f));
}

TEST_CASE("Vector2 default constructor", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>() == PonyEngine::Math::Vector2<std::int32_t>(0, 0));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>() == PonyEngine::Math::Vector2<float>(0.f, 0.f));
}

TEST_CASE("Vector2 main constructor", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(intVector.X() == x);
	STATIC_REQUIRE(intVector.Y() == y);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(floatVector.X() == x);
	STATIC_REQUIRE(floatVector.Y() == y);
}

TEST_CASE("Vector2 span constructor", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(std::array<std::int32_t, 2uz>{x, y});
	STATIC_REQUIRE(intVector.X() == x);
	STATIC_REQUIRE(intVector.Y() == y);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(std::array<float, 2uz>{x, y});
	STATIC_REQUIRE(floatVector.X() == x);
	STATIC_REQUIRE(floatVector.Y() == y);
}

TEST_CASE("Vector2 copy constructor", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr PonyEngine::Math::Vector2<std::int32_t> intVectorCopy = intVector;
	STATIC_REQUIRE(intVectorCopy.X() == x);
	STATIC_REQUIRE(intVectorCopy.Y() == y);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr PonyEngine::Math::Vector2<float> floatVectorCopy = floatVector;
	STATIC_REQUIRE(floatVectorCopy.X() == x);
	STATIC_REQUIRE(floatVectorCopy.Y() == y);
}

TEST_CASE("Vector2 move constructor", "[Math][Vector]")
{
	auto moveTest = [](const auto& x, const auto& y) constexpr
	{
		auto vector = PonyEngine::Math::Vector2(x, y);
		const PonyEngine::Math::Vector2 moved = std::move(vector);

		return moved;
	};

	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;

	constexpr PonyEngine::Math::Vector2<std::int32_t> intVector = moveTest(x, y);
	STATIC_REQUIRE(intVector.X() == x);
	STATIC_REQUIRE(intVector.Y() == y);

	constexpr auto floatVector = moveTest(static_cast<float>(x), static_cast<float>(y));
	STATIC_REQUIRE(floatVector.X() == x);
	STATIC_REQUIRE(floatVector.Y() == y);
}

TEST_CASE("Vector2 access", "[Math][Vector]")
{
	auto accessTest = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector2<T>& vector) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		copy.X() -= T{2};
		copy.Y() += T{3};

		return copy;
	};

	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(intVector.X() == x);
	STATIC_REQUIRE(intVector.Y() == y);
	constexpr PonyEngine::Math::Vector2<std::int32_t> intVectorCopy = accessTest(intVector);
	STATIC_REQUIRE(intVectorCopy.X() == x - 2);
	STATIC_REQUIRE(intVectorCopy.Y() == y + 3);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(floatVector.X() == x);
	STATIC_REQUIRE(floatVector.Y() == y);
	constexpr PonyEngine::Math::Vector2<float> floatVectorCopy = accessTest(floatVector);
	STATIC_REQUIRE(floatVectorCopy.X() == x - 2);
	STATIC_REQUIRE(floatVectorCopy.Y() == y + 3);
}

TEST_CASE("Vector2 span", "[Math][Vector]")
{
	auto spanTest = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector2<T>& vector) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		copy.Span()[0] -= T{2};
		copy.Span()[1] += T{3};

		return copy;
	};

	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(intVector.Span()[0] == x);
	STATIC_REQUIRE(intVector.Span()[1] == y);
	constexpr PonyEngine::Math::Vector2<std::int32_t> intVectorCopy = spanTest(intVector);
	STATIC_REQUIRE(intVectorCopy.Span()[0] == x - 2);
	STATIC_REQUIRE(intVectorCopy.Span()[1] == y + 3);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(floatVector.Span()[0] == x);
	STATIC_REQUIRE(floatVector.Span()[1] == y);
	constexpr PonyEngine::Math::Vector2<float> floatVectorCopy = spanTest(floatVector);
	STATIC_REQUIRE(floatVectorCopy.Span()[0] == x - 2);
	STATIC_REQUIRE(floatVectorCopy.Span()[1] == y + 3);
}

TEST_CASE("Vector2 swizzle", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr PonyEngine::Math::Vector2<std::int32_t> xxIntVector = intVector.XX();
	STATIC_REQUIRE(xxIntVector.X() == x);
	STATIC_REQUIRE(xxIntVector.Y() == x);
	constexpr PonyEngine::Math::Vector2<std::int32_t> xyIntVector = intVector.XY();
	STATIC_REQUIRE(xyIntVector.X() == x);
	STATIC_REQUIRE(xyIntVector.Y() == y);
	constexpr PonyEngine::Math::Vector2<std::int32_t> yxIntVector = intVector.YX();
	STATIC_REQUIRE(yxIntVector.X() == y);
	STATIC_REQUIRE(yxIntVector.Y() == x);
	constexpr PonyEngine::Math::Vector2<std::int32_t> yyIntVector = intVector.YY();
	STATIC_REQUIRE(yyIntVector.X() == y);
	STATIC_REQUIRE(yyIntVector.Y() == y);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr PonyEngine::Math::Vector2<float> xxFloatVector = floatVector.XX();
	STATIC_REQUIRE(xxFloatVector.X() == x);
	STATIC_REQUIRE(xxFloatVector.Y() == x);
	constexpr PonyEngine::Math::Vector2<float> xyFloatVector = floatVector.XY();
	STATIC_REQUIRE(xyFloatVector.X() == x);
	STATIC_REQUIRE(xyFloatVector.Y() == y);
	constexpr PonyEngine::Math::Vector2<float> yxFloatVector = floatVector.YX();
	STATIC_REQUIRE(yxFloatVector.X() == y);
	STATIC_REQUIRE(yxFloatVector.Y() == x);
	constexpr PonyEngine::Math::Vector2<float> yyFloatVector = floatVector.YY();
	STATIC_REQUIRE(yyFloatVector.X() == y);
	STATIC_REQUIRE(yyFloatVector.Y() == y);
}

TEST_CASE("Vector2 rotate90", "[Math][Vector]")
{
	auto rotateCW = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector2<T>& vector) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		copy.Rotate90CW();
		return copy;
	};
	auto rotateCCW = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector2<T>&vector) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		copy.Rotate90CCW();
		return copy;
	};

	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(intVector.Rotated90CW() == PonyEngine::Math::Vector2<std::int32_t>(3, 5));
	STATIC_REQUIRE(rotateCW(intVector) == PonyEngine::Math::Vector2<std::int32_t>(3, 5));
	STATIC_REQUIRE(intVector.Rotated90CCW() == PonyEngine::Math::Vector2<std::int32_t>(-3, -5));
	STATIC_REQUIRE(rotateCCW(intVector) == PonyEngine::Math::Vector2<std::int32_t>(-3, -5));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(floatVector.Rotated90CW() == PonyEngine::Math::Vector2<float>(3, 5));
	STATIC_REQUIRE(rotateCW(floatVector) == PonyEngine::Math::Vector2<float>(3, 5));
	STATIC_REQUIRE(floatVector.Rotated90CCW() == PonyEngine::Math::Vector2<float>(-3, -5));
	STATIC_REQUIRE(rotateCCW(floatVector) == PonyEngine::Math::Vector2<float>(-3, -5));
}

TEST_CASE("Vector2 magnitude", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(intVector.MagnitudeSquared() == 34);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(intVector.Magnitude(), 5.831f, 0.001f));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(floatVector.MagnitudeSquared() == 34.f);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(floatVector.Magnitude(), 5.831f, 0.001f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Magnitude int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(-4, 9).Magnitude();
	};
	BENCHMARK("Magnitude float")
	{
		return PonyEngine::Math::Vector2<float>(-4.f, 9.f).Magnitude();
	};
	BENCHMARK("Magnitude squared int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(-4, 9).MagnitudeSquared();
	};
	BENCHMARK("Magnitude squared float")
	{
		return PonyEngine::Math::Vector2<float>(-4.f, 9.f).MagnitudeSquared();
	};
#endif
}

TEST_CASE("Vector2 normalize", "[Math][Vector]")
{
	constexpr float x = -5.f;
	constexpr float y = 3.f;
	auto vector = PonyEngine::Math::Vector2<float>(x, y);

	const PonyEngine::Math::Vector2<float> normalized = vector.Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.X(), x / vector.Magnitude()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.Y(), y / vector.Magnitude()));

	vector.Normalize();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector.X(), normalized.X()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector.Y(), normalized.Y()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Normalized")
	{
		return PonyEngine::Math::Vector2<float>(6.f, 1.f).Normalized();
	};
	BENCHMARK("Normalize")
	{
		auto vector = PonyEngine::Math::Vector2<float>(6.f, 1.f);
		vector.Normalize();
		return vector;
	};
#endif
}

TEST_CASE("Vector2 normalize fallback", "[Math][Vector]")
{
	constexpr float x = -5.f;
	constexpr float y = 3.f;
	auto vector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto fallback = PonyEngine::Math::Vector2<float>::Predefined::Right;

	PonyEngine::Math::Vector2<float> normalized = vector.Normalized(fallback);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.X(), x / vector.Magnitude()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.Y(), y / vector.Magnitude()));

	normalized = PonyEngine::Math::Vector2<float>::Predefined::Zero.Normalized(fallback);
	REQUIRE(normalized == fallback);

	normalized = vector.Normalized(fallback);
	vector.Normalize(fallback);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector.X(), normalized.X()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector.Y(), normalized.Y()));

	vector = PonyEngine::Math::Vector2<float>::Predefined::Zero;
	vector.Normalize(fallback);
	REQUIRE(vector == fallback);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Normalized")
	{
		auto normalized = PonyEngine::Math::Vector2<float>(6.f, 1.f).Normalized();
		return PonyEngine::Math::Vector2<float>::Predefined::Zero.Normalized(normalized);
	};
	BENCHMARK("Normalize")
	{
		auto vector = PonyEngine::Math::Vector2<float>(6.f, 1.f);
		vector.Normalize(PonyEngine::Math::Vector2<float>::Predefined::Right);
		auto zero = PonyEngine::Math::Vector2<float>::Predefined::Zero;
		zero.Normalize(vector);
		return zero;
	};
#endif
}

TEST_CASE("Vector2 min this", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>(-2, 4).Min() == -2);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>(7, 4).Min() == 4);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(-2.f, 4.f).Min() == -2.f);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(7.f, 4.f).Min() == 4.f);

	constexpr auto intXVector = PonyEngine::Math::Vector2<std::int32_t>(-2, 4);
	STATIC_REQUIRE(intXVector.Min() == -2);
	constexpr auto intYVector = PonyEngine::Math::Vector2<std::int32_t>(7, 4);
	STATIC_REQUIRE(intYVector.Min() == 4);
	constexpr auto floatXVector = PonyEngine::Math::Vector2<float>(-2.f, 4.f);
	STATIC_REQUIRE(floatXVector.Min() == -2.f);
	constexpr auto floatYVector = PonyEngine::Math::Vector2<float>(7.f, 4.f);
	STATIC_REQUIRE(floatYVector.Min() == 4.f);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(-2, 4).Min();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector2<float>(7.f, 4.f).Min();
	};
#endif
}

TEST_CASE("Vector2 max this", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>(-2, -4).Max() == -2);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>(7, 41).Max() == 41);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(-2.f, -4.f).Max() == -2.f);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(7.f, 41.f).Max() == 41.f);

	constexpr auto intXVector = PonyEngine::Math::Vector2<std::int32_t>(-2, -4);
	STATIC_REQUIRE(intXVector.Max() == -2);
	constexpr auto intYVector = PonyEngine::Math::Vector2<std::int32_t>(7, 41);
	STATIC_REQUIRE(intYVector.Max() == 41);
	constexpr auto floatXVector = PonyEngine::Math::Vector2<float>(-2.f, -4.f);
	STATIC_REQUIRE(floatXVector.Max() == -2.f);
	constexpr auto floatYVector = PonyEngine::Math::Vector2<float>(7.f, 41.f);
	STATIC_REQUIRE(floatYVector.Max() == 41.f);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(-2, 4).Max();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector2<float>(7.f, 4.f).Max();
	};
#endif
}

TEST_CASE("Vector2 minmax", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>(1, 8).MinMax() == std::pair(1, 8));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>(7, -3).MinMax() == std::pair(-3, 7));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(1.f, 8.f).MinMax() == std::pair(1.f, 8.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(7.f, -3.f).MinMax() == std::pair(-3.f, 7.f));

	constexpr auto intXYVector = PonyEngine::Math::Vector2<std::int32_t>(1, 8);
	STATIC_REQUIRE(intXYVector.MinMax() == std::pair(1, 8));
	constexpr auto intYXVector = PonyEngine::Math::Vector2<std::int32_t>(7, -3);
	STATIC_REQUIRE(intYXVector.MinMax() == std::pair(-3, 7));
	constexpr auto floatXYVector = PonyEngine::Math::Vector2<float>(1.f, 8.f);
	STATIC_REQUIRE(floatXYVector.MinMax() == std::pair(1.f, 8.f));
	constexpr auto floatYXVector = PonyEngine::Math::Vector2<float>(7.f, -3.f);
	STATIC_REQUIRE(floatYXVector.MinMax() == std::pair(-3.f, 7.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(-2, 4).MinMax();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector2<float>(7.f, 4.f).MinMax();
	};
#endif
}

TEST_CASE("Vector2 sum this", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>(1, 8).Sum() == 9);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(7.f, -3.f).Sum() == 7.f - 3.f);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(1, 8).Sum();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector2<float>(7.f, -3.f).Sum();
	};
#endif
}

TEST_CASE("Vector2 product this", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>(1, 8).Product() == 8);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(7.f, -3.f).Product() == -3.f * 7.f);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(1, 8).Product();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector2<float>(7.f, -3.f).Product();
	};
#endif
}

TEST_CASE("Vector2 isZero, isUnit, isUniform", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Predefined::Zero.IsZero());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<std::int32_t>(2, 1).IsZero());
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Predefined::Zero.IsZero());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(2.f, 1.f).IsZero());
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(0.0000001f, 0.000001f).IsAlmostZero());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(0.1f, 0.1f).IsAlmostZero());

	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Predefined::Up.IsUnit());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<std::int32_t>(1, 1).IsUnit());
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Predefined::Right.IsUnit());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(2.f, 1.f).IsUnit());
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(0.9999999f,0.f).IsAlmostUnit());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(1.f, 0.1f).IsAlmostUnit());

	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Predefined::One.IsUniform());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<std::int32_t>(2, 3).IsUniform());
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Predefined::Zero.IsUniform());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(2.f, 1.f).IsUniform());
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(1.f, 0.9999999f).IsAlmostUniform());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(0.3f, 0.1f).IsAlmostUniform());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("IsZero Int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>::Predefined::Zero.IsZero() | PonyEngine::Math::Vector2<std::int32_t>(2, 1).IsZero();
	};
	BENCHMARK("IsZero float")
	{
		return PonyEngine::Math::Vector2<float>::Predefined::Zero.IsZero() | PonyEngine::Math::Vector2<float>(2.f, 1.f).IsZero();
	};
	BENCHMARK("IsAlmostZero float")
	{
		return PonyEngine::Math::Vector2<float>::Predefined::Zero.IsAlmostZero() | PonyEngine::Math::Vector2<float>(2.f, 1.f).IsAlmostZero();
	};
	BENCHMARK("IsUnit Int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>::Predefined::Up.IsUnit() | PonyEngine::Math::Vector2<std::int32_t>(2, 1).IsUnit();
	};
	BENCHMARK("IsUnit float")
	{
		return PonyEngine::Math::Vector2<float>::Predefined::Up.IsUnit() | PonyEngine::Math::Vector2<float>(2.f, 1.f).IsUnit();
	};
	BENCHMARK("IsAlmostUnit float")
	{
		return PonyEngine::Math::Vector2<float>::Predefined::Right.IsAlmostUnit() | PonyEngine::Math::Vector2<float>(2.f, 1.f).IsAlmostUnit();
	};
	BENCHMARK("IsUniform Int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>::Predefined::One.IsUniform() | PonyEngine::Math::Vector2<std::int32_t>(2, 1).IsUniform();
	};
	BENCHMARK("IsUniform float")
	{
		return PonyEngine::Math::Vector2<float>::Predefined::One.IsUniform() | PonyEngine::Math::Vector2<float>(2.f, 1.f).IsUniform();
	};
	BENCHMARK("IsAlmostUniform float")
	{
		return PonyEngine::Math::Vector2<float>::Predefined::One.IsAlmostUniform() | PonyEngine::Math::Vector2<float>(2.f, 1.f).IsAlmostUniform();
	};
#endif
}

TEST_CASE("Vector2 isFinite", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Predefined::Zero.IsFinite());
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(-3.f, 2.f).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(std::numeric_limits<float>::quiet_NaN(), 2.f).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(-3.f, std::numeric_limits<float>::quiet_NaN()).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN()).IsFinite());
}

TEST_CASE("Vector2 multiply this", "[Math][Vector]")
{
	auto multiply = []<PonyEngine::Type::Arithmetic T>(const T x, const T y, const T x1, const T y1) constexpr
	{
		auto vector = PonyEngine::Math::Vector2<T>(x, y);
		vector.Multiply(PonyEngine::Math::Vector2<T>(x1, y1));
		return vector;
	};

	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 15;
	constexpr std::int32_t y1 = -13;

	STATIC_REQUIRE(multiply(x, y, x1, y1) == PonyEngine::Math::Vector2<std::int32_t>(x * x1, y * y1));
	STATIC_REQUIRE(multiply(static_cast<float>(x), static_cast<float>(y), static_cast<float>(x1), static_cast<float>(y1)) == PonyEngine::Math::Vector2<float>(x * x1, y * y1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto vector = PonyEngine::Math::Vector2<std::int32_t>(-3, 1);
		vector.Multiply(PonyEngine::Math::Vector2<std::int32_t>(4, 2));
		return vector;
	};
	BENCHMARK("Float")
	{
		auto vector = PonyEngine::Math::Vector2<float>(-3.f, 1.f);
		vector.Multiply(PonyEngine::Math::Vector2<float>(4.f, 2.f));
		return vector;
	};
#endif
}

TEST_CASE("Vector2 divide this", "[Math][Vector]")
{
	auto divide = []<PonyEngine::Type::Arithmetic T>(const T x, const T y, const T x1, const T y1) constexpr
	{
		auto vector = PonyEngine::Math::Vector2<T>(x, y);
		vector.Divide(PonyEngine::Math::Vector2<T>(x1, y1));
		return vector;
	};

	constexpr std::int32_t x = -50;
	constexpr std::int32_t y = 30;
	constexpr std::int32_t x1 = 15;
	constexpr std::int32_t y1 = -13;

	STATIC_REQUIRE(divide(x, y, x1, y1) == PonyEngine::Math::Vector2<std::int32_t>(x / x1, y / y1));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(divide(static_cast<float>(x), static_cast<float>(y), static_cast<float>(x1), static_cast<float>(y1)), PonyEngine::Math::Vector2<float>(static_cast<float>(x) / x1, static_cast<float>(y) / y1)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto vector = PonyEngine::Math::Vector2<std::int32_t>(-30, 10);
		vector.Divide(PonyEngine::Math::Vector2<std::int32_t>(4, 2));
		return vector;
	};
	BENCHMARK("Float")
	{
		auto vector = PonyEngine::Math::Vector2<float>(-3.f, 1.f);
		vector.Divide(PonyEngine::Math::Vector2<float>(4.f, 2.f));
		return vector;
	};
#endif
}

TEST_CASE("Vector2 ToString", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	const std::string intExpected = std::format("({}, {})", x, y);

	REQUIRE(intVector.ToString() == intExpected);
	std::ostringstream oss;
	oss << intVector;
	REQUIRE(oss.str() == intExpected);
	REQUIRE(std::format("{}", intVector) == intExpected);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	const std::string floatExpected = std::format("({}, {})", x, y);

	REQUIRE(floatVector.ToString() == floatExpected);
	std::ostringstream ossf;
	ossf << floatVector;
	REQUIRE(ossf.str() == floatExpected);
	REQUIRE(std::format("{}", floatVector) == floatExpected);
}

TEST_CASE("Vector2 cast", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr auto vector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto cast = static_cast<PonyEngine::Math::Vector2<float>>(vector);
	STATIC_REQUIRE(cast.X() == static_cast<float>(x));
	STATIC_REQUIRE(cast.Y() == static_cast<float>(y));
	constexpr auto castInt = static_cast<PonyEngine::Math::Vector2<std::int32_t>>(cast);
	STATIC_REQUIRE(castInt.X() == static_cast<std::int32_t>(cast.X()));
	STATIC_REQUIRE(castInt.Y() == static_cast<std::int32_t>(cast.Y()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int to float")
	{
		auto vector = PonyEngine::Math::Vector2<std::int32_t>(-3, 1);
		return static_cast<PonyEngine::Math::Vector2<float>>(vector);
	};
	BENCHMARK("Float to int")
	{
		auto vector = PonyEngine::Math::Vector2<float>(-3.f, 1.f);
		return static_cast<PonyEngine::Math::Vector2<std::int32_t>>(vector);
	};
#endif
}

TEST_CASE("Vector2 access by index", "[Math][Vector]")
{
	auto accessTest = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector2<T>&vector) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		copy[0] -= T{2};
		copy[1] += T{3};

		return copy;
	};

	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(intVector[0] == x);
	STATIC_REQUIRE(intVector[1] == y);
	constexpr PonyEngine::Math::Vector2<std::int32_t> intCopy = accessTest(intVector);
	STATIC_REQUIRE(intCopy[0] == x - 2);
	STATIC_REQUIRE(intCopy[1] == y + 3);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(floatVector[0] == x);
	STATIC_REQUIRE(floatVector[1] == y);
	constexpr PonyEngine::Math::Vector2<float> floatCopy = accessTest(floatVector);
	STATIC_REQUIRE(floatCopy[0] == x - 2.f);
	STATIC_REQUIRE(floatCopy[1] == y + 3.f);
}

TEST_CASE("Vector2 swizzle by index", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(intVector[1, 0] == PonyEngine::Math::Vector2<std::int32_t>(y, x));
	STATIC_REQUIRE(intVector[0, 0] == PonyEngine::Math::Vector2<std::int32_t>(x, x));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(floatVector[0, 1] == PonyEngine::Math::Vector2<float>(x, y));
	STATIC_REQUIRE(floatVector[1, 1] == PonyEngine::Math::Vector2<float>(y, y));
}

TEST_CASE("Vector2 copy assignment", "[Math][Vector]")
{
	auto assignment = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector2<T>& vector) constexpr
	{
		auto copy = PonyEngine::Math::Vector2<T>();
		return copy = vector;
	};

	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(assignment(intVector) == intVector);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(assignment(floatVector) == floatVector);
}

TEST_CASE("Vector2 move assignment", "[Math][Vector]")
{
	auto assignment = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector2<T>& vector) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		PonyEngine::Math::Vector2<T> moved = PonyEngine::Math::Vector2<T>();
		return moved = std::move(copy);
	};

	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(assignment(intVector) == intVector);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(assignment(floatVector) == floatVector);
}

TEST_CASE("Vector2 sum assignment", "[Math][Vector]")
{
	auto assignment = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector2<T>& vector, const PonyEngine::Math::Vector2<T>& other) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		return copy += other;
	};

	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(assignment(intVector, intVector1) == intVector + intVector1);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(assignment(floatVector, floatVector1) == floatVector + floatVector1);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto vector = PonyEngine::Math::Vector2<std::int32_t>(3, -2);
		auto vector1 = PonyEngine::Math::Vector2<std::int32_t>(-6, 7);
		return vector += vector1;
	};
	BENCHMARK("Float")
	{
		auto vector = PonyEngine::Math::Vector2<float>(3.f, -2.f);
		auto vector1 = PonyEngine::Math::Vector2<float>(-6.f, 7.f);
		return vector += vector1;
	};
#endif
}

TEST_CASE("Vector2 subtraction assignment", "[Math][Vector]")
{
	auto assignment = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector2<T>&vector, const PonyEngine::Math::Vector2<T>&other) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		return copy -= other;
	};

	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(assignment(intVector, intVector1) == intVector - intVector1);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(assignment(floatVector, floatVector1) == floatVector - floatVector1);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto vector = PonyEngine::Math::Vector2<std::int32_t>(3, -2);
		auto vector1 = PonyEngine::Math::Vector2<std::int32_t>(-6, 7);
		return vector -= vector1;
	};
	BENCHMARK("Float")
	{
		auto vector = PonyEngine::Math::Vector2<float>(3.f, -2.f);
		auto vector1 = PonyEngine::Math::Vector2<float>(-6.f, 7.f);
		return vector -= vector1;
	};
#endif
}

TEST_CASE("Vector2 product assignment", "[Math][Vector]")
{
	auto assignment = []<PonyEngine::Type::Arithmetic T, PonyEngine::Type::Arithmetic U>(const PonyEngine::Math::Vector2<T>&vector, U multiplier) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		return copy *= multiplier;
	};

	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t multiplier = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(assignment(intVector, multiplier) == intVector * multiplier);
	STATIC_REQUIRE(assignment(intVector, static_cast<float>(multiplier)) == intVector * static_cast<float>(multiplier));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(assignment(floatVector, static_cast<float>(multiplier)) == floatVector * static_cast<float>(multiplier));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int by int")
	{
		auto vector = PonyEngine::Math::Vector2<std::int32_t>(3, -2);
		return vector *= 4;
	};
	BENCHMARK("Int by float")
	{
		auto vector = PonyEngine::Math::Vector2<std::int32_t>(3, -2);
		return vector *= 4.f;
	};
	BENCHMARK("Float")
	{
		auto vector = PonyEngine::Math::Vector2<float>(3.f, -2.f);
		return vector *= 4.f;
	};
#endif
}

TEST_CASE("Vector2 division assignment", "[Math][Vector]")
{
	auto assignment = []<PonyEngine::Type::Arithmetic T, PonyEngine::Type::Arithmetic U>(const PonyEngine::Math::Vector2<T>&vector, U multiplier) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		return copy /= multiplier;
	};

	constexpr std::int32_t x = -50;
	constexpr std::int32_t y = 30;
	constexpr std::int32_t multiplier = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(assignment(intVector, multiplier) == intVector / multiplier);
	STATIC_REQUIRE(assignment(intVector, static_cast<float>(multiplier)) == intVector / static_cast<float>(multiplier));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(assignment(floatVector, static_cast<float>(multiplier)) == floatVector / static_cast<float>(multiplier));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int by int")
	{
		auto vector = PonyEngine::Math::Vector2<std::int32_t>(30, -20);
		return vector /= 4;
	};
	BENCHMARK("Int by float")
	{
		auto vector = PonyEngine::Math::Vector2<std::int32_t>(30, -20);
		return vector /= 4.f;
	};
	BENCHMARK("Float")
	{
		auto vector = PonyEngine::Math::Vector2<float>(3.f, -2.f);
		return vector /= 4.f;
	};
#endif
}

TEST_CASE("Vector2 equals", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(intVector == intVector);
	STATIC_REQUIRE_FALSE(intVector == intVector1);
	STATIC_REQUIRE_FALSE(intVector != intVector);
	STATIC_REQUIRE(intVector != intVector1);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(floatVector == floatVector);
	STATIC_REQUIRE_FALSE(floatVector == floatVector1);
	STATIC_REQUIRE_FALSE(floatVector != floatVector);
	STATIC_REQUIRE(floatVector != floatVector1);
	constexpr auto closeFloatVector = PonyEngine::Math::Vector2<float>(x + 0.000001f, y - 0.000001f);
	STATIC_REQUIRE_FALSE(floatVector == closeFloatVector);
	STATIC_REQUIRE(floatVector != closeFloatVector);
}

TEST_CASE("Vector2 dot", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Dot(intVector, intVector1) == -28);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Dot(floatVector, floatVector1), -28.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Dot(PonyEngine::Math::Vector2<std::int32_t>(5, 3), PonyEngine::Math::Vector2<std::int32_t>(-2, 3));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Dot(PonyEngine::Math::Vector2<float>(5.f, 3.f), PonyEngine::Math::Vector2<float>(-2.f, 3.f));
	};
#endif
}

TEST_CASE("Vector2 crossZ", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::CrossZ(intVector, intVector1) == 24);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::CrossZ(floatVector, floatVector1), 24.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::CrossZ(PonyEngine::Math::Vector2<std::int32_t>(5, 3), PonyEngine::Math::Vector2<std::int32_t>(-2, 3));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::CrossZ(PonyEngine::Math::Vector2<float>(5.f, 3.f), PonyEngine::Math::Vector2<float>(-2.f, 3.f));
	};
#endif
}

TEST_CASE("Vector2 distance", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::DistanceSquared(intVector, intVector1) == 130);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Distance(intVector, intVector1), std::sqrt(130.f)));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::DistanceSquared(floatVector, floatVector1), 130.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Distance(floatVector, floatVector1), std::sqrt(130.f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Distance(PonyEngine::Math::Vector2<std::int32_t>(5, 3), PonyEngine::Math::Vector2<std::int32_t>(-2, 3));
	};
	BENCHMARK("Int squared")
	{
		return PonyEngine::Math::DistanceSquared(PonyEngine::Math::Vector2<std::int32_t>(5, 3), PonyEngine::Math::Vector2<std::int32_t>(-2, 3));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Distance(PonyEngine::Math::Vector2<float>(5.f, 3.f), PonyEngine::Math::Vector2<float>(-2.f, 3.f));
	};
	BENCHMARK("Float squared")
	{
		return PonyEngine::Math::DistanceSquared(PonyEngine::Math::Vector2<float>(5.f, 3.f), PonyEngine::Math::Vector2<float>(-2.f, 3.f));
	};
#endif
}

TEST_CASE("Vector2 angle", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	auto vector = PonyEngine::Math::Vector2<float>(x, y).Normalized();
	auto vector1 = PonyEngine::Math::Vector2<float>(x1, y1).Normalized();
	auto vector2 = vector.Rotated90CW();
	auto vector3 = -vector;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Angle(vector, vector), 0.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Angle(vector, vector1), 2.433f, 0.001f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Angle(vector, vector2), std::numbers::pi_v<float> / 2.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Angle(vector, vector3), std::numbers::pi_v<float>));

	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::AngleSigned(vector, vector1), 2.433f, 0.001f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::AngleSigned(vector1, vector), -2.433f, 0.001f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Unsigned")
	{
		return PonyEngine::Math::Angle(vector, vector1);
	};
	BENCHMARK("Signed")
	{
		return PonyEngine::Math::AngleSigned(vector, vector1);
	};
#endif
}

TEST_CASE("Vector2 project", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto vector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	constexpr auto vector2 = vector1.Rotated90CW();
	auto normal = vector1.Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Project(vector, normal), PonyEngine::Math::Vector2<float>(-1.4f, 4.2f)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Project(vector1, normal), vector1));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Project(vector2, normal), PonyEngine::Math::Vector2<float>::Predefined::Zero));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Project(-vector1, normal), -vector1));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Project(PonyEngine::Math::Vector2<float>::Predefined::Up, PonyEngine::Math::Vector2<float>::Predefined::Right), PonyEngine::Math::Vector2<float>::Predefined::Zero));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Project(vector, normal);
	};
#endif
}

TEST_CASE("Vector2 project on plane", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto vector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	constexpr auto vector2 = vector1.Rotated90CW();
	auto normal = vector1.Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ProjectOnPlane(vector, normal), PonyEngine::Math::Vector2<float>(-3.6f, -1.2f)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ProjectOnPlane(vector1, normal), PonyEngine::Math::Vector2<float>::Predefined::Zero));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ProjectOnPlane(vector2, normal), vector2));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ProjectOnPlane(-vector2, normal), -vector2));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ProjectOnPlane(PonyEngine::Math::Vector2<float>::Predefined::Up, PonyEngine::Math::Vector2<float>::Predefined::Right), PonyEngine::Math::Vector2<float>::Predefined::Up));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ProjectOnPlane(vector, normal);
	};
#endif
}

TEST_CASE("Vector2 reflect", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto vector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	constexpr auto vector2 = vector1.Rotated90CW();
	auto normal = vector1.Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Reflect(vector, normal), PonyEngine::Math::Vector2<float>(-2.2f, -5.4f)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Reflect(vector1, normal), -vector1));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Reflect(vector2, normal), vector2));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Reflect(-vector2, normal), -vector2));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Reflect(PonyEngine::Math::Vector2<float>::Predefined::Up, PonyEngine::Math::Vector2<float>::Predefined::Right), PonyEngine::Math::Vector2<float>::Predefined::Up));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Reflect(vector, normal);
	};
#endif
}

TEST_CASE("Vector2 multiply", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Multiply(intVector, intVector1) == PonyEngine::Math::Vector2<std::int32_t>(x * x1, y * y1));
	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Multiply(floatVector, floatVector1) == PonyEngine::Math::Vector2<float>(x * x1, y * y1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Multiply(PonyEngine::Math::Vector2<std::int32_t>(2, 3), PonyEngine::Math::Vector2<std::int32_t>(-6, 4));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Multiply(PonyEngine::Math::Vector2<float>(2.f, 3.f), PonyEngine::Math::Vector2<float>(-6.f, 4.f));
	};
#endif
}

TEST_CASE("Vector2 divide", "[Math][Vector]")
{
	constexpr std::int32_t x = -50;
	constexpr std::int32_t y = 30;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Divide(intVector, intVector1) == PonyEngine::Math::Vector2<std::int32_t>(x / x1, y / y1));
	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Divide(floatVector, floatVector1), PonyEngine::Math::Vector2<float>(x / x1, y / y1)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Divide(PonyEngine::Math::Vector2<std::int32_t>(20, 30), PonyEngine::Math::Vector2<std::int32_t>(-6, 4));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Divide(PonyEngine::Math::Vector2<float>(2.f, 3.f), PonyEngine::Math::Vector2<float>(-6.f, 4.f));
	};
#endif
}

TEST_CASE("Vector2 abs", "[Math][Vector]")
{
	constexpr std::int32_t x = 5;
	constexpr std::int32_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVectorX = PonyEngine::Math::Vector2<std::int32_t>(-x, y);
	constexpr auto intVectorY = PonyEngine::Math::Vector2<std::int32_t>(x, -y);
	constexpr auto intVectorXY = PonyEngine::Math::Vector2<std::int32_t>(-x, -y);
	STATIC_REQUIRE(PonyEngine::Math::Abs(intVector) == intVector);
	STATIC_REQUIRE(PonyEngine::Math::Abs(intVectorX) == intVector);
	STATIC_REQUIRE(PonyEngine::Math::Abs(intVectorY) == intVector);
	STATIC_REQUIRE(PonyEngine::Math::Abs(intVectorXY) == intVector);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVectorX = PonyEngine::Math::Vector2<float>(-x, y);
	constexpr auto floatVectorY = PonyEngine::Math::Vector2<float>(x, -y);
	constexpr auto floatVectorXY = PonyEngine::Math::Vector2<float>(-x, -y);
	STATIC_REQUIRE(PonyEngine::Math::Abs(floatVector) == floatVector);
	STATIC_REQUIRE(PonyEngine::Math::Abs(floatVectorX) == floatVector);
	STATIC_REQUIRE(PonyEngine::Math::Abs(floatVectorY) == floatVector);
	STATIC_REQUIRE(PonyEngine::Math::Abs(floatVectorXY) == floatVector);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Abs(PonyEngine::Math::Vector2<std::int32_t>(3, -1));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Abs(PonyEngine::Math::Vector2<float>(3.f, -1.f));
	};
#endif
}

TEST_CASE("Vector2 min", "[Math][Vector]")
{
	constexpr std::int32_t x = -50;
	constexpr std::int32_t y = 30;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Min(intVector, intVector1) == PonyEngine::Math::Vector2<std::int32_t>(x, y1));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Min(floatVector, floatVector1) == PonyEngine::Math::Vector2<float>(x, y1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Min(PonyEngine::Math::Vector2<std::int32_t>(3, -1), PonyEngine::Math::Vector2<std::int32_t>(-8, 7));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Min(PonyEngine::Math::Vector2<float>(3.f, -1.f), PonyEngine::Math::Vector2<float>(-8.f, 7.f));
	};
#endif
}

TEST_CASE("Vector2 max", "[Math][Vector]")
{
	constexpr std::int32_t x = -50;
	constexpr std::int32_t y = 30;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Max(intVector, intVector1) == PonyEngine::Math::Vector2<std::int32_t>(x1, y));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Max(floatVector, floatVector1) == PonyEngine::Math::Vector2<float>(x1, y));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Max(PonyEngine::Math::Vector2<std::int32_t>(3, -1), PonyEngine::Math::Vector2<std::int32_t>(-8, 7));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Max(PonyEngine::Math::Vector2<float>(3.f, -1.f), PonyEngine::Math::Vector2<float>(-8.f, 7.f));
	};
#endif
}

TEST_CASE("Vector2 clamp", "[Math][Vector]")
{
	constexpr std::int32_t x = 5;
	constexpr std::int32_t y = 30;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;
	constexpr std::int32_t x2 = 20;
	constexpr std::int32_t y2 = 10;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	constexpr auto intVector2 = PonyEngine::Math::Vector2<std::int32_t>(x2, y2);
	STATIC_REQUIRE(PonyEngine::Math::Clamp(intVector, intVector1, intVector2) == PonyEngine::Math::Vector2<std::int32_t>(x, y2));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x1 - 1, y2 - 1);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	constexpr auto floatVector2 = PonyEngine::Math::Vector2<float>(x2, y2);
	STATIC_REQUIRE(PonyEngine::Math::Clamp(floatVector, floatVector1, floatVector2) == PonyEngine::Math::Vector2<float>(x1, y2 - 1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Clamp(PonyEngine::Math::Vector2<std::int32_t>(3, -1), PonyEngine::Math::Vector2<std::int32_t>(-8, 7), PonyEngine::Math::Vector2<std::int32_t>(8, 71));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Clamp(PonyEngine::Math::Vector2<float>(3.f, -1.f), PonyEngine::Math::Vector2<float>(-8.f, 7.f), PonyEngine::Math::Vector2<float>(8.f, 71.f));
	};
#endif
}

TEST_CASE("Vector2 clamp magnitude", "[Math][Vector]")
{
	constexpr std::int32_t x = 5;
	constexpr std::int32_t y = 3;
	constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
	REQUIRE(PonyEngine::Math::ClampMagnitude(vector, 100.f) == vector);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ClampMagnitude(vector, 2.3f), vector.Normalized() * 2.3f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("No clamp")
	{
		return PonyEngine::Math::ClampMagnitude(PonyEngine::Math::Vector2<float>(5.f, 3.f), 100.f);
	};
	BENCHMARK("Clamp")
	{
		return PonyEngine::Math::ClampMagnitude(PonyEngine::Math::Vector2<float>(5.f, 3.f), 1.5f);
	};
#endif
}

TEST_CASE("Vector2 lerp", "[Math][Vector]")
{
	constexpr std::int32_t x = 5;
	constexpr std::int32_t y = 30;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Lerp(intVector, intVector1, 0.f) == intVector);
	STATIC_REQUIRE(PonyEngine::Math::Lerp(intVector, intVector1, 1.f) == intVector1);
	STATIC_REQUIRE(PonyEngine::Math::Lerp(intVector, intVector1, 0.5f) == PonyEngine::Math::Vector2<std::int32_t>(4, 12));
	STATIC_REQUIRE(PonyEngine::Math::Lerp(intVector, intVector1, -1.f) == intVector - (intVector1 - intVector));
	STATIC_REQUIRE(PonyEngine::Math::Lerp(intVector, intVector1, 2.f) == intVector + (intVector1 - intVector) * 2);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Lerp(floatVector, floatVector1, 0.f), floatVector));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Lerp(floatVector, floatVector1, 1.f), floatVector1));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Lerp(floatVector, floatVector1, 0.5f), PonyEngine::Math::Vector2<float>(3.5f, 12.f)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Lerp(floatVector, floatVector1, -1.f), floatVector - (floatVector1 - floatVector)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Lerp(floatVector, floatVector1, 2.f), floatVector + (floatVector1 - floatVector) * 2.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Lerp(PonyEngine::Math::Vector2<std::int32_t>(3, -1), PonyEngine::Math::Vector2<std::int32_t>(-8, 7), 0.7f);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Lerp(PonyEngine::Math::Vector2<float>(3.f, -1.f), PonyEngine::Math::Vector2<float>(-8.f, 7.f), 0.4f);
	};
#endif
}

TEST_CASE("Vector2 are almost equal", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto vector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(vector, vector));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(vector, vector1));
	constexpr auto closeFloatVector = PonyEngine::Math::Vector2<float>(x + 0.000001f, y - 0.000001f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(vector, closeFloatVector));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(3.f, 2.f), PonyEngine::Math::Vector2<float>(3.0000001f, 1.9999999f));
	};
#endif
}

TEST_CASE("Vector2 sum", "[Math][Vector]")
{
	constexpr std::int32_t x = 5;
	constexpr std::int32_t y = 30;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(intVector + intVector1 == PonyEngine::Math::Vector2<std::int32_t>(x + x1, y + y1));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(floatVector + floatVector1, PonyEngine::Math::Vector2<float>(x + x1, y + y1)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(5, 3) + PonyEngine::Math::Vector2<std::int32_t>(-7, 6);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector2<float>(5.f, 3.f) + PonyEngine::Math::Vector2<float>(-7.f, 6.f);
	};
#endif
}

TEST_CASE("Vector2 plus", "[Math][Vector]")
{
	constexpr std::int32_t x = 5;
	constexpr std::int32_t y = 30;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(intVector + intVector1 == PonyEngine::Math::Vector2<std::int32_t>(x + x1, y + y1));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(floatVector + floatVector1, PonyEngine::Math::Vector2<float>(x + x1, y + y1)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(5, 3) + PonyEngine::Math::Vector2<std::int32_t>(-7, 6);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector2<float>(5.f, 3.f) + PonyEngine::Math::Vector2<float>(-7.f, 6.f);
	};
#endif
}

TEST_CASE("Vector2 negation", "[Math][Vector]")
{
	constexpr std::int32_t x = 5;
	constexpr std::int32_t y = -30;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(-intVector == PonyEngine::Math::Vector2<std::int32_t>(-x, -y));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(-floatVector, PonyEngine::Math::Vector2<float>(-x, -y)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return -PonyEngine::Math::Vector2<std::int32_t>(5, 3);
	};
	BENCHMARK("Float")
	{
		return -PonyEngine::Math::Vector2<float>(5.f, 3.f);
	};
#endif
}

TEST_CASE("Vector2 subtraction", "[Math][Vector]")
{
	constexpr std::int32_t x = 5;
	constexpr std::int32_t y = 30;
	constexpr std::int32_t x1 = 2;
	constexpr std::int32_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(intVector - intVector1 == PonyEngine::Math::Vector2<std::int32_t>(x - x1, y - y1));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(floatVector - floatVector1, PonyEngine::Math::Vector2<float>(x - x1, y - y1)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(5, 3) - PonyEngine::Math::Vector2<std::int32_t>(-7, 6);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector2<float>(5.f, 3.f) - PonyEngine::Math::Vector2<float>(-7.f, 6.f);
	};
#endif
}

TEST_CASE("Vector2 product", "[Math][Vector]")
{
	constexpr std::int32_t x = 5;
	constexpr std::int32_t y = 30;
	constexpr std::int32_t multiplier = 4;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(intVector * multiplier == PonyEngine::Math::Vector2<std::int32_t>(x * multiplier, y * multiplier));
	STATIC_REQUIRE(multiplier * intVector == PonyEngine::Math::Vector2<std::int32_t>(x * multiplier, y * multiplier));
	STATIC_REQUIRE(intVector * static_cast<float>(multiplier) == PonyEngine::Math::Vector2<std::int32_t>(x * static_cast<float>(multiplier), y * static_cast<float>(multiplier)));
	STATIC_REQUIRE(static_cast<float>(multiplier) * intVector == PonyEngine::Math::Vector2<std::int32_t>(x * static_cast<float>(multiplier), y * static_cast<float>(multiplier)));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(floatVector * static_cast<float>(multiplier) == PonyEngine::Math::Vector2<float>(x * static_cast<float>(multiplier), y * static_cast<float>(multiplier)));
	STATIC_REQUIRE(static_cast<float>(multiplier) * floatVector == PonyEngine::Math::Vector2<float>(x * static_cast<float>(multiplier), y * static_cast<float>(multiplier)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int by int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(5, 3) * 4;
	};
	BENCHMARK("Int by float")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(5, 3) * 4.f;
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector2<float>(5.f, 3.f) * 4.f;
	};
#endif
}

TEST_CASE("Vector2 division", "[Math][Vector]")
{
	constexpr std::int32_t x = 50;
	constexpr std::int32_t y = 30;
	constexpr std::int32_t divisor = 4;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(intVector / divisor == PonyEngine::Math::Vector2<std::int32_t>(x / divisor, y / divisor));
	STATIC_REQUIRE(intVector / static_cast<float>(divisor) == PonyEngine::Math::Vector2<std::int32_t>(x / static_cast<float>(divisor), y / static_cast<float>(divisor)));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(floatVector / static_cast<float>(divisor) == PonyEngine::Math::Vector2<float>(x / static_cast<float>(divisor), y / static_cast<float>(divisor)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int by int")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(50, 30) / 4;
	};
	BENCHMARK("Int by float")
	{
		return PonyEngine::Math::Vector2<std::int32_t>(50, 30) / 4.f;
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector2<float>(50.f, 30.f) / 4.f;
	};
#endif
}
