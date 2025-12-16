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
import PonyEngine.Type;

TEST_CASE("Vector static", "[Math][Vector]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector1<std::int32_t>::ValueType, std::int32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector1<std::uint32_t>::ValueType, std::uint32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector1<float>::ValueType, float>);

	STATIC_REQUIRE(PonyEngine::Math::Vector1<std::int32_t>::ComponentCount == 1uz);
	STATIC_REQUIRE(PonyEngine::Math::Vector1<std::uint32_t>::ComponentCount == 1uz);
	STATIC_REQUIRE(PonyEngine::Math::Vector1<float>::ComponentCount == 1uz);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector2<std::int32_t>::ValueType, std::int32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector2<std::uint32_t>::ValueType, std::uint32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector2<float>::ValueType, float>);

	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::ComponentCount == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::uint32_t>::ComponentCount == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::ComponentCount == 2uz);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector3<std::int32_t>::ValueType, std::int32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector3<std::uint32_t>::ValueType, std::uint32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector3<float>::ValueType, float>);

	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>::ComponentCount == 3uz);
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::uint32_t>::ComponentCount == 3uz);
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>::ComponentCount == 3uz);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector4<std::int32_t>::ValueType, std::int32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector4<std::uint32_t>::ValueType, std::uint32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Vector4<float>::ValueType, float>);

	STATIC_REQUIRE(PonyEngine::Math::Vector4<std::int32_t>::ComponentCount == 4uz);
	STATIC_REQUIRE(PonyEngine::Math::Vector4<std::uint32_t>::ComponentCount == 4uz);
	STATIC_REQUIRE(PonyEngine::Math::Vector4<float>::ComponentCount == 4uz);
}

TEST_CASE("Vector default constructor", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector1<std::int32_t>() == PonyEngine::Math::Vector1<std::int32_t>(0));
	STATIC_REQUIRE(PonyEngine::Math::Vector1<float>() == PonyEngine::Math::Vector1<float>(0.f));

	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>() == PonyEngine::Math::Vector2<std::int32_t>(0, 0));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>() == PonyEngine::Math::Vector2<float>(0.f, 0.f));

	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>() == PonyEngine::Math::Vector3<std::int32_t>(0, 0, 0));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>() == PonyEngine::Math::Vector3<float>(0.f, 0.f, 0.f));

	STATIC_REQUIRE(PonyEngine::Math::Vector4<std::int32_t>() == PonyEngine::Math::Vector4<std::int32_t>(0, 0, 0, 0));
	STATIC_REQUIRE(PonyEngine::Math::Vector4<float>() == PonyEngine::Math::Vector4<float>(0.f, 0.f, 0.f, 0.f));
}

TEST_CASE("Vector fill constructor", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;

	constexpr auto vector1 = PonyEngine::Math::Vector1<float>(x);
	STATIC_REQUIRE(vector1.X() == x);

	constexpr auto vector2 = PonyEngine::Math::Vector2<float>(x);
	STATIC_REQUIRE(vector2.X() == x);
	STATIC_REQUIRE(vector2.Y() == x);

	constexpr auto vector3 = PonyEngine::Math::Vector3<float>(x);
	STATIC_REQUIRE(vector3.X() == x);
	STATIC_REQUIRE(vector3.Y() == x);
	STATIC_REQUIRE(vector3.Z() == x);

	constexpr auto vector4 = PonyEngine::Math::Vector4<float>(x);
	STATIC_REQUIRE(vector4.X() == x);
	STATIC_REQUIRE(vector4.Y() == x);
	STATIC_REQUIRE(vector4.Z() == x);
	STATIC_REQUIRE(vector4.W() == x);

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x);
	STATIC_REQUIRE(intVector.X() == x);
	STATIC_REQUIRE(intVector.Y() == x);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(4);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector4<float>(4.f);
	};
#endif
}

TEST_CASE("Vector main constructor", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = 7;
	constexpr std::int16_t w = -2;

	constexpr auto vector1 = PonyEngine::Math::Vector1<float>(x);
	STATIC_REQUIRE(vector1.X() == x);

	constexpr auto vector2 = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(vector2.X() == x);
	STATIC_REQUIRE(vector2.Y() == y);

	constexpr auto vector3 = PonyEngine::Math::Vector3<float>(x, y, z);
	STATIC_REQUIRE(vector3.X() == x);
	STATIC_REQUIRE(vector3.Y() == y);
	STATIC_REQUIRE(vector3.Z() == z);

	constexpr auto vector4 = PonyEngine::Math::Vector4<float>(x, y, z, w);
	STATIC_REQUIRE(vector4.X() == x);
	STATIC_REQUIRE(vector4.Y() == y);
	STATIC_REQUIRE(vector4.Z() == z);
	STATIC_REQUIRE(vector4.W() == w);

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(intVector.X() == x);
	STATIC_REQUIRE(intVector.Y() == y);
}

TEST_CASE("Vector span constructor", "[Math][Vector]")
{
	constexpr std::int32_t x = -5;
	constexpr std::int32_t y = 3;
	constexpr std::int32_t z = 7;
	constexpr std::int32_t w = -2;

	constexpr auto vector1 = PonyEngine::Math::Vector1<float>(std::array<float, 1uz>{x});
	STATIC_REQUIRE(vector1.X() == x);

	constexpr auto vector2 = PonyEngine::Math::Vector2<float>(std::array<float, 2uz>{x, y});
	STATIC_REQUIRE(vector2.X() == x);
	STATIC_REQUIRE(vector2.Y() == y);

	constexpr auto vector3 = PonyEngine::Math::Vector3<float>(std::array<float, 3uz>{x, y, z});
	STATIC_REQUIRE(vector3.X() == x);
	STATIC_REQUIRE(vector3.Y() == y);
	STATIC_REQUIRE(vector3.Z() == z);

	constexpr auto vector4 = PonyEngine::Math::Vector4<float>(std::array<float, 4uz>{x, y, z, w});
	STATIC_REQUIRE(vector4.X() == x);
	STATIC_REQUIRE(vector4.Y() == y);
	STATIC_REQUIRE(vector4.Z() == z);
	STATIC_REQUIRE(vector4.W() == w);

	auto vector4R = PonyEngine::Math::Vector4<float>(std::array<float, 4uz>{x, y, z, w});
	REQUIRE(vector4R.X() == x);
	REQUIRE(vector4R.Y() == y);
	REQUIRE(vector4R.Z() == z);
	REQUIRE(vector4R.W() == w);

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(std::array<std::int32_t, 2uz>{x, y});
	STATIC_REQUIRE(intVector.X() == x);
	STATIC_REQUIRE(intVector.Y() == y);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(std::array<std::int32_t, 4uz>{-3, 4, 1, -8});
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector4<float>(std::array<float, 4uz>{-3.f, 4.f, 1.f, -8.f});
	};
#endif
}

TEST_CASE("Vector copy constructor", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = 7;
	constexpr std::int16_t w = -2;

	constexpr auto vector1 = PonyEngine::Math::Vector1<float>(x);
	constexpr PonyEngine::Math::Vector1<float> vector1Copy = vector1;
	STATIC_REQUIRE(vector1Copy.X() == x);

	constexpr auto vector2 = PonyEngine::Math::Vector2<float>(x, y);
	constexpr PonyEngine::Math::Vector2<float> vector2Copy = vector2;
	STATIC_REQUIRE(vector2Copy.X() == x);
	STATIC_REQUIRE(vector2Copy.Y() == y);

	constexpr auto vector3 = PonyEngine::Math::Vector3<float>(x, y, z);
	constexpr PonyEngine::Math::Vector3<float> vector3Copy = vector3;
	STATIC_REQUIRE(vector3Copy.X() == x);
	STATIC_REQUIRE(vector3Copy.Y() == y);
	STATIC_REQUIRE(vector3Copy.Z() == z);

	constexpr auto vector4 = PonyEngine::Math::Vector4<float>(x, y, z, w);
	constexpr PonyEngine::Math::Vector4<float> vector4Copy = vector4;
	STATIC_REQUIRE(vector4Copy.X() == x);
	STATIC_REQUIRE(vector4Copy.Y() == y);
	STATIC_REQUIRE(vector4Copy.Z() == z);
	STATIC_REQUIRE(vector4Copy.W() == w);

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr PonyEngine::Math::Vector2<std::int32_t> intVectorCopy = intVector;
	STATIC_REQUIRE(intVectorCopy.X() == x);
	STATIC_REQUIRE(intVectorCopy.Y() == y);
}

TEST_CASE("Vector move constructor", "[Math][Vector]")
{
	auto moveTest = []<PonyEngine::Type::Arithmetic T, std::size_t Size>(const PonyEngine::Math::Vector<T, Size>& vector) constexpr
	{
		auto copy = vector;
		auto moved = std::move(copy);
		return moved;
	};

	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = 7;
	constexpr std::int16_t w = -2;

	constexpr auto vector1 = PonyEngine::Math::Vector1<float>(x);
	constexpr PonyEngine::Math::Vector1<float> vector1Copy = moveTest(vector1);
	STATIC_REQUIRE(vector1Copy.X() == x);

	constexpr auto vector2 = PonyEngine::Math::Vector2<float>(x, y);
	constexpr PonyEngine::Math::Vector2<float> vector2Copy = moveTest(vector2);
	STATIC_REQUIRE(vector2Copy.X() == x);
	STATIC_REQUIRE(vector2Copy.Y() == y);

	constexpr auto vector3 = PonyEngine::Math::Vector3<float>(x, y, z);
	constexpr PonyEngine::Math::Vector3<float> vector3Copy = moveTest(vector3);
	STATIC_REQUIRE(vector3Copy.X() == x);
	STATIC_REQUIRE(vector3Copy.Y() == y);
	STATIC_REQUIRE(vector3Copy.Z() == z);

	constexpr auto vector4 = PonyEngine::Math::Vector4<float>(x, y, z, w);
	constexpr PonyEngine::Math::Vector4<float> vector4Copy = moveTest(vector4);
	STATIC_REQUIRE(vector4Copy.X() == x);
	STATIC_REQUIRE(vector4Copy.Y() == y);
	STATIC_REQUIRE(vector4Copy.Z() == z);
	STATIC_REQUIRE(vector4Copy.W() == w);

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr PonyEngine::Math::Vector2<std::int32_t> intVectorCopy = moveTest(intVector);
	STATIC_REQUIRE(intVectorCopy.X() == x);
	STATIC_REQUIRE(intVectorCopy.Y() == y);
}

TEST_CASE("Vector create one value", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>::CreateOneValue(4.f, 2uz) == PonyEngine::Math::Vector3<float>(0.f, 0.f, 4.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::CreateOneValue(-3, 0uz) == PonyEngine::Math::Vector2<std::int32_t>(-3, 0));
}

TEST_CASE("Vector predefined", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector1<float>::Zero() == PonyEngine::Math::Vector1<float>(0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector1<std::int32_t>::Zero() == PonyEngine::Math::Vector1<std::int32_t>(0));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Zero() == PonyEngine::Math::Vector2<float>(0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Zero() == PonyEngine::Math::Vector2<std::int32_t>(0));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>::Zero() == PonyEngine::Math::Vector3<float>(0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>::Zero() == PonyEngine::Math::Vector3<std::int32_t>(0));
	STATIC_REQUIRE(PonyEngine::Math::Vector4<float>::Zero() == PonyEngine::Math::Vector4<float>(0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector4<std::int32_t>::Zero() == PonyEngine::Math::Vector4<std::int32_t>(0));

	STATIC_REQUIRE(PonyEngine::Math::Vector1<float>::One() == PonyEngine::Math::Vector1<float>(1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector1<std::int32_t>::One() == PonyEngine::Math::Vector1<std::int32_t>(1));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::One() == PonyEngine::Math::Vector2<float>(1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::One() == PonyEngine::Math::Vector2<std::int32_t>(1));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>::One() == PonyEngine::Math::Vector3<float>(1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>::One() == PonyEngine::Math::Vector3<std::int32_t>(1));
	STATIC_REQUIRE(PonyEngine::Math::Vector4<float>::One() == PonyEngine::Math::Vector4<float>(1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector4<std::int32_t>::One() == PonyEngine::Math::Vector4<std::int32_t>(1));

	STATIC_REQUIRE(PonyEngine::Math::Vector1<float>::Negative() == PonyEngine::Math::Vector1<float>(-1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector1<std::int32_t>::Negative() == PonyEngine::Math::Vector1<std::int32_t>(-1));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Negative() == PonyEngine::Math::Vector2<float>(-1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Negative() == PonyEngine::Math::Vector2<std::int32_t>(-1));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>::Negative() == PonyEngine::Math::Vector3<float>(-1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>::Negative() == PonyEngine::Math::Vector3<std::int32_t>(-1));
	STATIC_REQUIRE(PonyEngine::Math::Vector4<float>::Negative() == PonyEngine::Math::Vector4<float>(-1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector4<std::int32_t>::Negative() == PonyEngine::Math::Vector4<std::int32_t>(-1));

	STATIC_REQUIRE(PonyEngine::Math::Vector1<float>::Right() == PonyEngine::Math::Vector1<float>(1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector1<std::int32_t>::Right() == PonyEngine::Math::Vector1<std::int32_t>(1));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Right() == PonyEngine::Math::Vector2<float>(1.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Right() == PonyEngine::Math::Vector2<std::int32_t>(1, 0));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>::Right() == PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>::Right() == PonyEngine::Math::Vector3<std::int32_t>(1, 0, 0));

	STATIC_REQUIRE(PonyEngine::Math::Vector1<float>::Left() == PonyEngine::Math::Vector1<float>(-1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector1<std::int32_t>::Left() == PonyEngine::Math::Vector1<std::int32_t>(-1));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Left() == PonyEngine::Math::Vector2<float>(-1.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Left() == PonyEngine::Math::Vector2<std::int32_t>(-1, 0));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>::Left() == PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>::Left() == PonyEngine::Math::Vector3<std::int32_t>(-1, 0, 0));

	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Up() == PonyEngine::Math::Vector2<float>(0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Up() == PonyEngine::Math::Vector2<std::int32_t>(0, 1));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>::Up() == PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>::Up() == PonyEngine::Math::Vector3<std::int32_t>(0, 1, 0));

	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>::Down() == PonyEngine::Math::Vector2<float>(0.f, -1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Down() == PonyEngine::Math::Vector2<std::int32_t>(0, -1));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>::Down() == PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>::Down() == PonyEngine::Math::Vector3<std::int32_t>(0, -1, 0));

	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>::Forward() == PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>::Forward() == PonyEngine::Math::Vector3<std::int32_t>(0, 0, 1));

	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>::Back() == PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>::Back() == PonyEngine::Math::Vector3<std::int32_t>(0, 0, -1));
}

TEST_CASE("Vector access", "[Math][Vector]")
{
	auto accessTest = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector4<T>& vector) constexpr
	{
		PonyEngine::Math::Vector4<T> copy = vector;
		copy.X() -= T{2};
		copy.Y() += T{3};
		copy.Z() -= T{1};
		copy.W() += T{4};

		return copy;
	};

	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = 7;
	constexpr std::int16_t w = -2;

	constexpr auto intVector = PonyEngine::Math::Vector4<std::int32_t>(x, y, z, w);
	STATIC_REQUIRE(intVector.X() == x);
	STATIC_REQUIRE(intVector.Y() == y);
	STATIC_REQUIRE(intVector.Z() == z);
	STATIC_REQUIRE(intVector.W() == w);
	constexpr PonyEngine::Math::Vector4<std::int32_t> intVectorCopy = accessTest(intVector);
	STATIC_REQUIRE(intVectorCopy.X() == x - 2);
	STATIC_REQUIRE(intVectorCopy.Y() == y + 3);
	STATIC_REQUIRE(intVectorCopy.Z() == z - 1);
	STATIC_REQUIRE(intVectorCopy.W() == w + 4);

	constexpr auto floatVector = PonyEngine::Math::Vector4<float>(x, y, z, w);
	STATIC_REQUIRE(floatVector.X() == x);
	STATIC_REQUIRE(floatVector.Y() == y);
	STATIC_REQUIRE(floatVector.Z() == z);
	STATIC_REQUIRE(floatVector.W() == w);
	constexpr PonyEngine::Math::Vector4<float> floatVectorCopy = accessTest(floatVector);
	STATIC_REQUIRE(floatVectorCopy.X() == x - 2);
	STATIC_REQUIRE(floatVectorCopy.Y() == y + 3);
	STATIC_REQUIRE(floatVectorCopy.Z() == z - 1);
	STATIC_REQUIRE(floatVectorCopy.W() == w + 4);
}

TEST_CASE("Vector span", "[Math][Vector]")
{
	auto spanTest = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector4<T>&vector) constexpr
	{
		PonyEngine::Math::Vector4<T> copy = vector;
		copy.Span()[0] -= T{2};
		copy.Span()[1] += T{3};
		copy.Span()[2] -= T{1};
		copy.Span()[3] += T{4};

		return copy;
	};

	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = 7;
	constexpr std::int16_t w = -2;

	constexpr auto intVector = PonyEngine::Math::Vector4<std::int32_t>(x, y, z, w);
	STATIC_REQUIRE(intVector.Span()[0] == x);
	STATIC_REQUIRE(intVector.Span()[1] == y);
	STATIC_REQUIRE(intVector.Span()[2] == z);
	STATIC_REQUIRE(intVector.Span()[3] == w);
	constexpr PonyEngine::Math::Vector4<std::int32_t> intVectorCopy = spanTest(intVector);
	STATIC_REQUIRE(intVectorCopy.Span()[0] == x - 2);
	STATIC_REQUIRE(intVectorCopy.Span()[1] == y + 3);
	STATIC_REQUIRE(intVectorCopy.Span()[2] == z - 1);
	STATIC_REQUIRE(intVectorCopy.Span()[3] == w + 4);

	constexpr auto floatVector = PonyEngine::Math::Vector4<float>(x, y, z, w);
	STATIC_REQUIRE(floatVector.Span()[0] == x);
	STATIC_REQUIRE(floatVector.Span()[1] == y);
	STATIC_REQUIRE(floatVector.Span()[2] == z);
	STATIC_REQUIRE(floatVector.Span()[3] == w);
	constexpr PonyEngine::Math::Vector4<float> floatVectorCopy = spanTest(floatVector);
	STATIC_REQUIRE(floatVectorCopy.Span()[0] == x - 2);
	STATIC_REQUIRE(floatVectorCopy.Span()[1] == y + 3);
	STATIC_REQUIRE(floatVectorCopy.Span()[2] == z - 1);
	STATIC_REQUIRE(floatVectorCopy.Span()[3] == w + 4);
}

TEST_CASE("Vector magnitude", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = 7;
	constexpr std::int16_t w = -2;

	constexpr auto intVector = PonyEngine::Math::Vector4<std::int32_t>(x, y, z, w);
	STATIC_REQUIRE(intVector.MagnitudeSquared() == 87);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(intVector.Magnitude<float>(), 9.327f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	constexpr auto floatVector = PonyEngine::Math::Vector4<float>(x, y, z, w);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(floatVector.MagnitudeSquared(), 87.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(floatVector.Magnitude(), 9.327f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Magnitude int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(-4, 9, -8, 3).Magnitude();
	};
	BENCHMARK("Magnitude float")
	{
		return PonyEngine::Math::Vector4<float>(-4.f, 9.f, -8.f, 3.f).Magnitude();
	};
	BENCHMARK("Magnitude squared int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(-4, 9, -8, 3).MagnitudeSquared();
	};
	BENCHMARK("Magnitude squared float")
	{
		return PonyEngine::Math::Vector4<float>(-4.f, 9.f, -8.f, 3.f).MagnitudeSquared();
	};
#endif
}

TEST_CASE("Vector normalize", "[Math][Vector]")
{
	constexpr float x = -5.f;
	constexpr float y = 3.f;
	constexpr float z = 7.f;
	constexpr float w = -2.f;
	auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);

	const PonyEngine::Math::Vector4<float> normalized = vector.Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.X(), x / vector.Magnitude()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.Y(), y / vector.Magnitude()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.Z(), z / vector.Magnitude()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.W(), w / vector.Magnitude()));

	vector.Normalize();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector, normalized));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Normalized")
	{
		return PonyEngine::Math::Vector4<float>(6.f, 1.f, -3.f, -7.f).Normalized();
	};
	BENCHMARK("Normalize")
	{
		auto vector = PonyEngine::Math::Vector4<float>(6.f, 1.f, -3.f, -7.f);
		vector.Normalize();
		return vector;
	};
#endif
}

TEST_CASE("Vector normalize fallback", "[Math][Vector]")
{
	constexpr float x = -5.f;
	constexpr float y = 3.f;
	constexpr float z = 7.f;
	constexpr float w = -2.f;
	auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);
	constexpr auto fallback = PonyEngine::Math::Vector4<float>::CreateOneValue(1.f, 0uz);

	PonyEngine::Math::Vector4<float> normalized = vector.Normalized(fallback);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.X(), x / vector.Magnitude()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.Y(), y / vector.Magnitude()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.Z(), z / vector.Magnitude()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalized.W(), w / vector.Magnitude()));

	normalized = PonyEngine::Math::Vector4<float>::Zero().Normalized(fallback);
	REQUIRE(normalized == fallback);

	normalized = vector.Normalized(fallback);
	vector.Normalize(fallback);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector.X(), normalized.X()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector.Y(), normalized.Y()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector.Z(), normalized.Z()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(vector.W(), normalized.W()));

	vector = PonyEngine::Math::Vector4<float>::Zero();
	vector.Normalize(fallback);
	REQUIRE(vector == fallback);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Normalized")
	{
		auto normalized = PonyEngine::Math::Vector4<float>(6.f, 1.f, 4.f, -8.f).Normalized();
		return PonyEngine::Math::Vector4<float>::Zero().Normalized(normalized);
	};
	BENCHMARK("Normalize")
	{
		auto vector = PonyEngine::Math::Vector4<float>(6.f, 1.f, 4.f, -8.f);
		vector.Normalize(PonyEngine::Math::Vector4<float>::CreateOneValue(1.f, 0uz));
		auto zero = PonyEngine::Math::Vector4<float>::Zero();
		zero.Normalize(vector);
		return zero;
	};
#endif
}

TEST_CASE("Vector min this", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>(-2, 4, 5).Min() == -2);
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>(7, 4, 10).Min() == 4);
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>(-2.f, 4.f, -5.f).Min() == -5.f);
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>(7.f, 4.f, 10.f).Min() == 4.f);

	constexpr auto intVector = PonyEngine::Math::Vector3<std::int32_t>(7, 4, 10);
	STATIC_REQUIRE(intVector.Min() == 4);
	constexpr auto floatVector = PonyEngine::Math::Vector3<float>(-2.f, 4.f, -5.f);
	STATIC_REQUIRE(floatVector.Min() == -5.f);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(-2, 4, 1, -3).Min();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector4<float>(7.f, 4.f, 1.f, -3.f).Min();
	};
#endif
}

TEST_CASE("Vector max this", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>(-2, 4, 5).Max() == 5);
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>(7, 4, 1).Max() == 7);
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>(-2.f, 4.f, -5.f).Max() == 4.f);
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>(7.f, 4.f, 10.f).Max() == 10.f);

	constexpr auto intVector = PonyEngine::Math::Vector3<std::int32_t>(7, 4, 10);
	STATIC_REQUIRE(intVector.Max() == 10);
	constexpr auto floatVector = PonyEngine::Math::Vector3<float>(-2.f, 4.f, -5.f);
	STATIC_REQUIRE(floatVector.Max() == 4.f);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(-2, 4, 1, -3).Max();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector4<float>(7.f, 4.f, 1.f, -3.f).Max();
	};
#endif
}

TEST_CASE("Vector minmax", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>(-2, 4, 5).MinMax() == std::pair(-2, 5));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<std::int32_t>(7, 4, 1).MinMax() == std::pair(1, 7));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>(-2.f, 4.f, -5.f).MinMax() == std::pair(-5.f, 4.f));
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>(7.f, 4.f, 10.f).MinMax() == std::pair(4.f, 10.f));

	constexpr auto intVector = PonyEngine::Math::Vector3<std::int32_t>(7, 4, 10);
	STATIC_REQUIRE(intVector.MinMax() == std::pair(4, 10));
	constexpr auto floatVector = PonyEngine::Math::Vector3<float>(-2.f, 4.f, -5.f);
	STATIC_REQUIRE(floatVector.MinMax() == std::pair(-5.f, 4.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(-2, 4, 3, -2).MinMax();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector4<float>(7.f, 4.f, 3.f, -2.f).MinMax();
	};
#endif
}

TEST_CASE("Vector sum this", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector4<std::int32_t>(1, 8, -4, -1).Sum() == 4);
	STATIC_REQUIRE(PonyEngine::Math::Vector4<float>(7.f, -3.f, 4.f, -1.f).Sum() == 7.f - 3.f + 4.f - 1.f);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(1, 8, -4, -1).Sum();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector4<float>(7.f, -3.f, 4.f, -1.f).Sum();
	};
#endif
}

TEST_CASE("Vector product this", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector4<std::int32_t>(1, 8, -4, -1).Product() == 32);
	STATIC_REQUIRE(PonyEngine::Math::Vector4<float>(7.f, -3.f, 4.f, -1.f).Product() == 7.f * (-3.f) * 4.f * (-1.f));

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

TEST_CASE("Vector isZero, isUnit, isUniform", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Zero().IsZero());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector3<std::int32_t>(2, 1, 4).IsZero());
	STATIC_REQUIRE(PonyEngine::Math::Vector4<float>::Zero().IsZero());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector1<float>(2.f).IsZero());
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(0.000000000001f, 0.000000000001f).IsAlmostZero());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(0.1f, 0.1f).IsAlmostZero());

	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::Up().IsUnit());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector3<std::int32_t>(1, 1, 1).IsUnit());
	STATIC_REQUIRE(PonyEngine::Math::Vector3<float>::Right().IsUnit());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(2.f, 1.f).IsUnit());
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(0.9999999f, 0.f).IsAlmostUnit());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector3<float>(1.f, 0.1f, 0.f).IsAlmostUnit());

	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>::One().IsUniform());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector4<std::int32_t>(2, 1, 9, 4).IsUniform());
	STATIC_REQUIRE(PonyEngine::Math::Vector4<float>::Zero().IsUniform());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(2.f, 1.f).IsUniform());
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(1.f, 0.9999999f).IsAlmostUniform());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector2<float>(0.3f, 0.1f).IsAlmostUniform());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("IsZero Int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>::Zero().IsZero() | PonyEngine::Math::Vector4<std::int32_t>(2, 1, 1, -2).IsZero();
	};
	BENCHMARK("IsZero float")
	{
		return PonyEngine::Math::Vector4<float>::Zero().IsZero() | PonyEngine::Math::Vector4<float>(2.f, 1.f, 1.f, -2.f).IsZero();
	};
	BENCHMARK("IsAlmostZero float")
	{
		return PonyEngine::Math::Vector4<float>::Zero().IsAlmostZero() | PonyEngine::Math::Vector4<float>(2.f, 1.f, 1.f, -2.f).IsAlmostZero();
	};
	BENCHMARK("IsUnit Int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>::CreateOneValue(1, 1uz).IsUnit() | PonyEngine::Math::Vector4<std::int32_t>(2, 1, 1, -2).IsUnit();
	};
	BENCHMARK("IsUnit float")
	{
		return PonyEngine::Math::Vector4<float>::CreateOneValue(1.f, 1uz).IsUnit() | PonyEngine::Math::Vector4<float>(2.f, 1.f, 1.f, -2.f).IsUnit();
	};
	BENCHMARK("IsAlmostUnit float")
	{
		return PonyEngine::Math::Vector4<float>::CreateOneValue(1.f, 1uz).IsAlmostUnit() | PonyEngine::Math::Vector4<float>(2.f, 1.f, 1.f, -2.f).IsAlmostUnit();
	};
	BENCHMARK("IsUniform Int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>::One().IsUniform() | PonyEngine::Math::Vector4<std::int32_t>(2, 1, 1, -2).IsUniform();
	};
	BENCHMARK("IsUniform float")
	{
		return PonyEngine::Math::Vector4<float>::One().IsUniform() | PonyEngine::Math::Vector4<float>(2.f, 1.f, 1.f, -2.f).IsUniform();
	};
	BENCHMARK("IsAlmostUniform float")
	{
		return PonyEngine::Math::Vector4<float>::One().IsAlmostUniform() | PonyEngine::Math::Vector4<float>(2.f, 1.f, 1.f, -2.f).IsAlmostUniform();
	};
#endif
}

TEST_CASE("Vector isFinite", "[Math][Vector]")
{
	STATIC_REQUIRE(PonyEngine::Math::Vector4<float>::Zero().IsFinite());
	STATIC_REQUIRE(PonyEngine::Math::Vector2<float>(-3.f, 2.f).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector3<float>(std::numeric_limits<float>::quiet_NaN(), 2.f, 0.f).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector3<float>(-3.f, std::numeric_limits<float>::quiet_NaN(), 0.f).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Vector3<float>(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN()).IsFinite());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Vector4<float>(2.f, -2.f, 3.f, -1.f).IsFinite() | PonyEngine::Math::Vector4<float>(2.f, -2.f, 3.f, std::numeric_limits<float>::quiet_NaN()).IsFinite();
	};
#endif
}

TEST_CASE("Vector multiply this", "[Math][Vector]")
{
	auto multiply = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector4<T>& lhs, const PonyEngine::Math::Vector4<T>& rhs) constexpr
	{
		auto copy = lhs;
		copy.Multiply(rhs);
		return copy;
	};

	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = -15;
	constexpr std::int16_t w = 13;
	constexpr std::int16_t x1 = 15;
	constexpr std::int16_t y1 = -13;
	constexpr std::int16_t z1 = 5;
	constexpr std::int16_t w1 = 3;

	STATIC_REQUIRE(multiply(PonyEngine::Math::Vector4<std::int32_t>(x, y, z, w), PonyEngine::Math::Vector4<std::int32_t>(x1, y1, z1, w1)) == PonyEngine::Math::Vector4<std::int32_t>(x * x1, y * y1, z * z1, w * w1));
	STATIC_REQUIRE(multiply(PonyEngine::Math::Vector4<float>(x, y, z, w), PonyEngine::Math::Vector4<float>(x1, y1, z1, w1)) == PonyEngine::Math::Vector4<float>(static_cast<float>(x) * x1, static_cast<float>(y) * y1, static_cast<float>(z) * z1, static_cast<float>(w) * w1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto vector = PonyEngine::Math::Vector4<std::int32_t>(-3, 1, 2, 4);
		vector.Multiply(PonyEngine::Math::Vector4<std::int32_t>(4, 2, -9, 6));
		return vector;
	};
	BENCHMARK("Float")
	{
		auto vector = PonyEngine::Math::Vector4<float>(-3.f, 1.f, 2.f, 4.f);
		vector.Multiply(PonyEngine::Math::Vector4<float>(4.f, 2.f, -9.f, 6.f));
		return vector;
	};
#endif
}

TEST_CASE("Vector divide this", "[Math][Vector]")
{
	auto divide = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector4<T>&lhs, const PonyEngine::Math::Vector4<T>&rhs) constexpr
	{
		auto copy = lhs;
		copy.Divide(rhs);
		return copy;
	};

	constexpr std::int16_t x = -50;
	constexpr std::int16_t y = 30;
	constexpr std::int16_t z = -150;
	constexpr std::int16_t w = 130;
	constexpr std::int16_t x1 = 15;
	constexpr std::int16_t y1 = -13;
	constexpr std::int16_t z1 = 5;
	constexpr std::int16_t w1 = 3;

	STATIC_REQUIRE(divide(PonyEngine::Math::Vector4<std::int32_t>(x, y, z, w), PonyEngine::Math::Vector4<std::int32_t>(x1, y1, z1, w1)) == PonyEngine::Math::Vector4<std::int32_t>(x / x1, y / y1, z / z1, w / w1));
	STATIC_REQUIRE(divide(PonyEngine::Math::Vector4<float>(x, y, z, w), PonyEngine::Math::Vector4<float>(x1, y1, z1, w1)) == PonyEngine::Math::Vector4<float>(static_cast<float>(x) / x1, static_cast<float>(y) / y1, static_cast<float>(z) / z1, static_cast<float>(w) / w1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto vector = PonyEngine::Math::Vector4<std::int32_t>(-3, 1, 2, 4);
		vector.Divide(PonyEngine::Math::Vector4<std::int32_t>(4, 2, -9, 6));
		return vector;
	};
	BENCHMARK("Float")
	{
		auto vector = PonyEngine::Math::Vector4<float>(-3.f, 1.f, 2.f, 4.f);
		vector.Divide(PonyEngine::Math::Vector4<float>(4.f, 2.f, -9.f, 6.f));
		return vector;
	};
#endif
}

TEST_CASE("Vector ToString", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = -15;
	constexpr std::int16_t w = 13;
	constexpr auto intVector = PonyEngine::Math::Vector4<std::int32_t>(x, y, z, w);
	const std::string intExpected = std::format("({}, {}, {}, {})", x, y, z, w);
	REQUIRE(std::format("{}", intVector) == intExpected);

	constexpr auto floatVector = PonyEngine::Math::Vector4<float>(x, y, z, w);
	const std::string floatExpected = std::format("({}, {}, {}, {})", floatVector.X(), floatVector.Y(), floatVector.Z(), floatVector.W());
	REQUIRE(std::format("{}", floatVector) == floatExpected);
}

TEST_CASE("Vector cast", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = -15;
	constexpr std::int16_t w = 13;
	constexpr auto vector = PonyEngine::Math::Vector4<std::int32_t>(x, y, z, w);
	constexpr auto cast = static_cast<PonyEngine::Math::Vector4<float>>(vector);
	STATIC_REQUIRE(cast.X() == static_cast<float>(x));
	STATIC_REQUIRE(cast.Y() == static_cast<float>(y));
	STATIC_REQUIRE(cast.Z() == static_cast<float>(z));
	STATIC_REQUIRE(cast.W() == static_cast<float>(w));
	constexpr auto castInt = static_cast<PonyEngine::Math::Vector4<std::int32_t>>(cast);
	STATIC_REQUIRE(castInt.X() == static_cast<std::int32_t>(cast.X()));
	STATIC_REQUIRE(castInt.Y() == static_cast<std::int32_t>(cast.Y()));
	STATIC_REQUIRE(castInt.Z() == static_cast<std::int32_t>(cast.Z()));
	STATIC_REQUIRE(castInt.W() == static_cast<std::int32_t>(cast.W()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int to float")
	{
		return static_cast<PonyEngine::Math::Vector4<float>>(PonyEngine::Math::Vector4<std::int32_t>(-3, 1, 4, -2));
	};
	BENCHMARK("Float to int")
	{
		return static_cast<PonyEngine::Math::Vector4<std::int32_t>>(PonyEngine::Math::Vector4<float>(-3.f, 1.f, 4.f, -2.f));
	};
#endif
}

TEST_CASE("Vector access by index", "[Math][Vector]")
{
	auto accessTest = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector4<T>& vector) constexpr
	{
		PonyEngine::Math::Vector4<T> copy = vector;
		copy[0] -= T{2};
		copy[1] += T{3};
		copy[2] -= T{1};
		copy[3] += T{4};

		return copy;
	};

	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = -15;
	constexpr std::int16_t w = 13;
	constexpr auto intVector = PonyEngine::Math::Vector4<std::int32_t>(x, y, z, w);
	STATIC_REQUIRE(intVector[0] == x);
	STATIC_REQUIRE(intVector[1] == y);
	STATIC_REQUIRE(intVector[2] == z);
	STATIC_REQUIRE(intVector[3] == w);
	constexpr PonyEngine::Math::Vector4<std::int32_t> intCopy = accessTest(intVector);
	STATIC_REQUIRE(intCopy[0] == x - 2);
	STATIC_REQUIRE(intCopy[1] == y + 3);
	STATIC_REQUIRE(intCopy[2] == z - 1);
	STATIC_REQUIRE(intCopy[3] == w + 4);

	constexpr auto floatVector = PonyEngine::Math::Vector4<float>(x, y, z, w);
	STATIC_REQUIRE(floatVector[0] == x);
	STATIC_REQUIRE(floatVector[1] == y);
	STATIC_REQUIRE(floatVector[2] == z);
	STATIC_REQUIRE(floatVector[3] == w);
	constexpr PonyEngine::Math::Vector4<float> floatCopy = accessTest(floatVector);
	STATIC_REQUIRE(floatCopy[0] == x - 2.f);
	STATIC_REQUIRE(floatCopy[1] == y + 3.f);
	STATIC_REQUIRE(floatCopy[2] == z - 1.f);
	STATIC_REQUIRE(floatCopy[3] == w + 4.f);
}

TEST_CASE("Vector copy assignment", "[Math][Vector]")
{
	auto assignment = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector4<T>& vector) constexpr
	{
		auto copy = PonyEngine::Math::Vector4<T>();
		return copy = vector;
	};

	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = -15;
	constexpr std::int16_t w = 13;

	constexpr auto intVector = PonyEngine::Math::Vector4<std::int32_t>(x, y, z, w);
	STATIC_REQUIRE(assignment(intVector) == intVector);

	constexpr auto floatVector = PonyEngine::Math::Vector4<float>(x, y, z, w);
	STATIC_REQUIRE(assignment(floatVector) == floatVector);
}

TEST_CASE("Vector move assignment", "[Math][Vector]")
{
	auto assignment = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector2<T>& vector) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		PonyEngine::Math::Vector2<T> moved = PonyEngine::Math::Vector2<T>();
		return moved = std::move(copy);
	};

	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(assignment(intVector) == intVector);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(assignment(floatVector) == floatVector);
}

TEST_CASE("Vector sum assignment", "[Math][Vector]")
{
	auto assignment = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector4<T>& vector, const PonyEngine::Math::Vector4<T>& other) constexpr
	{
		PonyEngine::Math::Vector4<T> copy = vector;
		return copy += other;
	};

	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = -15;
	constexpr std::int16_t w = 13;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;
	constexpr std::int16_t z1 = -1;
	constexpr std::int16_t w1 = 4;

	constexpr auto intVector = PonyEngine::Math::Vector4<std::int32_t>(x, y, z, w);
	constexpr auto intVector1 = PonyEngine::Math::Vector4<std::int32_t>(x1, y1, z1, w1);
	STATIC_REQUIRE(assignment(intVector, intVector1) == intVector + intVector1);

	constexpr auto floatVector = PonyEngine::Math::Vector4<float>(x, y, z, w);
	constexpr auto floatVector1 = PonyEngine::Math::Vector4<float>(x1, y1, z1, w1);
	STATIC_REQUIRE(assignment(floatVector, floatVector1) == floatVector + floatVector1);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto vector = PonyEngine::Math::Vector4<std::int32_t>(3, -2, 6, 2);
		auto vector1 = PonyEngine::Math::Vector4<std::int32_t>(-6, 7, 2, 1);
		return vector += vector1;
	};
	BENCHMARK("Float")
	{
		auto vector = PonyEngine::Math::Vector4<float>(3.f, -2.f, 6.f, 2.f);
		auto vector1 = PonyEngine::Math::Vector4<float>(-6.f, 7.f, 2.f, 1.f);
		return vector += vector1;
	};
#endif
}

TEST_CASE("Vector subtraction assignment", "[Math][Vector]")
{
	auto assignment = []<PonyEngine::Type::Arithmetic T>(const PonyEngine::Math::Vector2<T>&vector, const PonyEngine::Math::Vector2<T>&other) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		return copy -= other;
	};

	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(assignment(intVector, intVector1) == intVector - intVector1);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(assignment(floatVector, floatVector1) == floatVector - floatVector1);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto vector = PonyEngine::Math::Vector4<std::int32_t>(3, -2, 10, 12);
		auto vector1 = PonyEngine::Math::Vector4<std::int32_t>(-6, 7, 4, 3);
		return vector -= vector1;
	};
	BENCHMARK("Float")
	{
		auto vector = PonyEngine::Math::Vector4<float>(3.f, -2.f, 10.f, 12.f);
		auto vector1 = PonyEngine::Math::Vector4<float>(-6.f, 7.f, 4.f, 3.f);
		return vector -= vector1;
	};
#endif
}

TEST_CASE("Vector product assignment", "[Math][Vector]")
{
	auto assignment = []<PonyEngine::Type::Arithmetic T, PonyEngine::Type::Arithmetic U>(const PonyEngine::Math::Vector2<T>&vector, U multiplier) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		return copy *= multiplier;
	};

	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t multiplier = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(assignment(intVector, multiplier) == intVector * static_cast<std::int32_t>(multiplier));
	STATIC_REQUIRE(assignment(intVector, static_cast<float>(multiplier)) == intVector * static_cast<float>(multiplier));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(assignment(floatVector, static_cast<float>(multiplier)) == floatVector * static_cast<float>(multiplier));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int by int")
	{
		auto vector = PonyEngine::Math::Vector4<std::int32_t>(3, -2, 1, -3);
		return vector *= 4;
	};
	BENCHMARK("Int by float")
	{
		auto vector = PonyEngine::Math::Vector4<std::int32_t>(3, -2, 1, -3);
		return vector *= 4.f;
	};
	BENCHMARK("Float")
	{
		auto vector = PonyEngine::Math::Vector4<float>(3.f, -2.f, 1.f, -3.f);
		return vector *= 4.f;
	};
#endif
}

TEST_CASE("Vector division assignment", "[Math][Vector]")
{
	auto assignment = []<PonyEngine::Type::Arithmetic T, PonyEngine::Type::Arithmetic U>(const PonyEngine::Math::Vector2<T>& vector, const U multiplier) constexpr
	{
		PonyEngine::Math::Vector2<T> copy = vector;
		return copy /= multiplier;
	};

	constexpr std::int16_t x = -50;
	constexpr std::int16_t y = 30;
	constexpr std::int16_t multiplier = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(assignment(intVector, multiplier) == intVector / static_cast<std::int32_t>(multiplier));
	STATIC_REQUIRE(assignment(intVector, static_cast<float>(multiplier)) == intVector / static_cast<float>(multiplier));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(assignment(floatVector, static_cast<float>(multiplier)) == floatVector / static_cast<float>(multiplier));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int by int")
	{
		auto vector = PonyEngine::Math::Vector4<std::int32_t>(30, -20, 40, -50);
		return vector /= 4;
	};
	BENCHMARK("Int by float")
	{
		auto vector = PonyEngine::Math::Vector4<std::int32_t>(30, -20, 40, -50);
		return vector /= 4.f;
	};
	BENCHMARK("Float")
	{
		auto vector = PonyEngine::Math::Vector4<float>(3.f, -2.f, 4.f, -5.f);
		return vector /= 4.f;
	};
#endif
}

TEST_CASE("Vector equals", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

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

TEST_CASE("Vector dot", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Dot(intVector, intVector1) == -28);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Dot(floatVector, floatVector1), -28.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Dot(PonyEngine::Math::Vector4<std::int32_t>(5, 3, -2, -4), PonyEngine::Math::Vector4<std::int32_t>(-2, 3, 2, 4));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Dot(PonyEngine::Math::Vector4<float>(5.f, 3.f, -2.f, -4.f), PonyEngine::Math::Vector4<float>(-2.f, 3.f, 2.f, 4.f));
	};
#endif
}

TEST_CASE("Vector2 crossZ", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

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

TEST_CASE("Vector3 cross", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = 4;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;
	constexpr std::int16_t z1 = -2;

	constexpr auto intVector = PonyEngine::Math::Vector3<std::int32_t>(x, y, z);
	constexpr auto intVector1 = PonyEngine::Math::Vector3<std::int32_t>(x1, y1, z1);
	STATIC_REQUIRE(PonyEngine::Math::Cross(intVector, intVector1) == PonyEngine::Math::Vector3<std::int32_t>(18, -2, 24));

	constexpr auto floatVector = PonyEngine::Math::Vector3<float>(x, y, z);
	constexpr auto floatVector1 = PonyEngine::Math::Vector3<float>(x1, y1, z1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Cross(floatVector, floatVector1), PonyEngine::Math::Vector3<float>(18.f, -2.f, 24.f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Cross(PonyEngine::Math::Vector3<std::int32_t>(5, 3, 4), PonyEngine::Math::Vector3<std::int32_t>(-2, 3, 1));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Cross(PonyEngine::Math::Vector3<float>(5.f, 3.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, -2.f));
	};
#endif
}

TEST_CASE("Vector distance", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::DistanceSquared(intVector, intVector1) == 130);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Distance<float>(intVector, intVector1), std::sqrt(130.f)));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::DistanceSquared(floatVector, floatVector1), 130.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Distance(floatVector, floatVector1), std::sqrt(130.f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Distance(PonyEngine::Math::Vector4<std::int32_t>(5, 3, 0, 1), PonyEngine::Math::Vector4<std::int32_t>(-2, 3, -3, -5));
	};
	BENCHMARK("Int squared")
	{
		return PonyEngine::Math::DistanceSquared(PonyEngine::Math::Vector4<std::int32_t>(5, 3, 0, 1), PonyEngine::Math::Vector4<std::int32_t>(-2, 3, -3, -5));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Distance(PonyEngine::Math::Vector4<float>(5.f, 3.f, 0.f, 1.f), PonyEngine::Math::Vector4<float>(-2.f, 3.f, -3.f, -5.f));
	};
	BENCHMARK("Float squared")
	{
		return PonyEngine::Math::DistanceSquared(PonyEngine::Math::Vector4<float>(5.f, 3.f, 0.f, 1.f), PonyEngine::Math::Vector4<float>(-2.f, 3.f, -3.f, -5.f));
	};
#endif
}

TEST_CASE("Vector2 angle", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	auto vector = PonyEngine::Math::Vector2<float>(x, y).Normalized();
	auto vector1 = PonyEngine::Math::Vector2<float>(x1, y1).Normalized();
	auto vector2 = PonyEngine::Math::Rotate90CW(vector);
	auto vector3 = -vector;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Angle(vector, vector), 0.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Angle(vector, vector1), 2.433f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Angle(vector, vector2), std::numbers::pi_v<float> / 2.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Angle(vector, vector3), std::numbers::pi_v<float>));

	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::AngleSigned(vector, vector1), 2.433f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::AngleSigned(vector1, vector), -2.433f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

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

TEST_CASE("Vector3 angle", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t z = 4;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;
	constexpr std::int16_t z1 = -4;

	auto vector = PonyEngine::Math::Vector3<float>(x, y, z).Normalized();
	auto vector1 = PonyEngine::Math::Vector3<float>(x1, y1, z1).Normalized();
	auto vector2 = PonyEngine::Math::Vector3<float>(0.f, 4.f, -3.f);
	auto vector3 = -vector;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Angle(vector, vector), 0.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Angle(vector, vector1), 2.553f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Angle(vector, vector2), std::numbers::pi_v<float> / 2.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Angle(vector, vector3), std::numbers::pi_v<float>));

	constexpr auto axis = PonyEngine::Math::Vector3<float>(1.f, 2.f, 4.f);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::AngleSigned(vector, vector1, axis), 2.553f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::AngleSigned(vector1, vector, axis), -2.553f, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Unsigned")
	{
		return PonyEngine::Math::Angle(vector, vector1);
	};
	BENCHMARK("Signed")
	{
		return PonyEngine::Math::AngleSigned(vector, vector1, axis);
	};
#endif
}

TEST_CASE("Vector2 rotate90", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(PonyEngine::Math::Rotate90CW(intVector) == PonyEngine::Math::Vector2<std::int32_t>(3, 5));
	STATIC_REQUIRE(PonyEngine::Math::Rotate90CCW(intVector) == PonyEngine::Math::Vector2<std::int32_t>(-3, -5));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(PonyEngine::Math::Rotate90CW(floatVector) == PonyEngine::Math::Vector2<float>(3.f, 5.f));
	STATIC_REQUIRE(PonyEngine::Math::Rotate90CCW(floatVector) == PonyEngine::Math::Vector2<float>(-3.f, -5.f));
}

TEST_CASE("Vector project", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto vector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	constexpr auto vector2 = PonyEngine::Math::Rotate90CW(vector1);
	auto normal = vector1.Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Project(vector, normal), PonyEngine::Math::Vector2<float>(-1.4f, 4.2f)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Project(vector1, normal), vector1));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Project(vector2, normal), PonyEngine::Math::Vector2<float>::Zero()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Project(-vector1, normal), -vector1));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Project(PonyEngine::Math::Vector2<float>::Up(), PonyEngine::Math::Vector2<float>::Right()), PonyEngine::Math::Vector2<float>::Zero()));

#if PONY_ENGINE_TESTING_BENCHMARK
	constexpr auto benchVector = PonyEngine::Math::Vector4<float>(2.f, 4.f, -7.f, 1.f);
	auto benchNormal = PonyEngine::Math::Vector4<float>(4.f, -3.f, 4.f, -7.f).Normalized();
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Project(benchVector, benchNormal);
	};
#endif
}

TEST_CASE("Vector project on plane", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto vector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	constexpr auto vector2 = PonyEngine::Math::Rotate90CW(vector1);
	auto normal = vector1.Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ProjectOnPlane(vector, normal), PonyEngine::Math::Vector2<float>(-3.6f, -1.2f)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ProjectOnPlane(vector1, normal), PonyEngine::Math::Vector2<float>::Zero(), PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ProjectOnPlane(vector2, normal), vector2));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ProjectOnPlane(-vector2, normal), -vector2));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ProjectOnPlane(PonyEngine::Math::Vector2<float>::Up(), PonyEngine::Math::Vector2<float>::Right()), PonyEngine::Math::Vector2<float>::Up()));

#if PONY_ENGINE_TESTING_BENCHMARK
	constexpr auto benchVector = PonyEngine::Math::Vector4<float>(2.f, -3.f, -4.f, -5.f);
	auto benchNormal = PonyEngine::Math::Vector4<float>(1.f, -3.f, 4.f, 5.f).Normalized();
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ProjectOnPlane(benchVector, benchNormal);
	};
#endif
}

TEST_CASE("Vector reflect", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto vector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	constexpr auto vector2 = PonyEngine::Math::Rotate90CW(vector1);
	auto normal = vector1.Normalized();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Reflect(vector, normal), PonyEngine::Math::Vector2<float>(-2.2f, -5.4f)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Reflect(vector1, normal), -vector1));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Reflect(vector2, normal), vector2));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Reflect(-vector2, normal), -vector2));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Reflect(PonyEngine::Math::Vector2<float>::Up(), PonyEngine::Math::Vector2<float>::Right()), PonyEngine::Math::Vector2<float>::Up()));

#if PONY_ENGINE_TESTING_BENCHMARK
	constexpr auto benchVector = PonyEngine::Math::Vector4<float>(5.f, 4.f, 2.f, 1.f);
	auto benchNormal = PonyEngine::Math::Vector4<float>(-1.f, 2.f, 5.f, 3.f).Normalized();
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Reflect(benchVector, benchNormal);
	};
#endif
}

TEST_CASE("Vector multiply", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Multiply(intVector, intVector1) == PonyEngine::Math::Vector2<std::int32_t>(x * x1, y * y1));
	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Multiply(floatVector, floatVector1) == PonyEngine::Math::Vector2<float>(static_cast<float>(x * x1), static_cast<float>(y * y1)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Multiply(PonyEngine::Math::Vector4<std::int32_t>(2, 3, -1, -2), PonyEngine::Math::Vector4<std::int32_t>(-6, 4, 2, 4));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Multiply(PonyEngine::Math::Vector4<float>(2.f, 3.f, -1.f, -2.f), PonyEngine::Math::Vector4<float>(-6.f, 4.f, 2.f, 4.f));
	};
#endif
}

TEST_CASE("Vector divide", "[Math][Vector]")
{
	constexpr std::int16_t x = -50;
	constexpr std::int16_t y = 30;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Divide(intVector, intVector1) == PonyEngine::Math::Vector2<std::int32_t>(x / x1, y / y1));
	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Divide(floatVector, floatVector1), PonyEngine::Math::Vector2<float>(static_cast<float>(x / x1), static_cast<float>(y / y1))));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Divide(PonyEngine::Math::Vector4<std::int32_t>(20, 30, -20, -30), PonyEngine::Math::Vector4<std::int32_t>(-6, 4, -1, 2));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Divide(PonyEngine::Math::Vector4<float>(2.f, 3.f, -2.f, -3.f), PonyEngine::Math::Vector4<float>(-6.f, 4.f, -1.f, -2.f));
	};
#endif
}

TEST_CASE("Vector abs", "[Math][Vector]")
{
	constexpr std::int16_t x = 5;
	constexpr std::int16_t y = 3;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVectorX = PonyEngine::Math::Vector2<std::int32_t>(-x, y);
	constexpr auto intVectorY = PonyEngine::Math::Vector2<std::int32_t>(x, -y);
	constexpr auto intVectorXY = PonyEngine::Math::Vector2<std::int32_t>(-x, -y);
	STATIC_REQUIRE(PonyEngine::Math::Abs(intVector) == intVector);
	STATIC_REQUIRE(PonyEngine::Math::Abs(intVectorX) == intVector);
	STATIC_REQUIRE(PonyEngine::Math::Abs(intVectorY) == intVector);
	STATIC_REQUIRE(PonyEngine::Math::Abs(intVectorXY) == intVector);

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVectorX = PonyEngine::Math::Vector2<float>(static_cast<float>(-x), y);
	constexpr auto floatVectorY = PonyEngine::Math::Vector2<float>(x, static_cast<float>(-y));
	constexpr auto floatVectorXY = PonyEngine::Math::Vector2<float>(static_cast<float>(-x), static_cast<float>(-y));
	STATIC_REQUIRE(PonyEngine::Math::Abs(floatVector) == floatVector);
	STATIC_REQUIRE(PonyEngine::Math::Abs(floatVectorX) == floatVector);
	STATIC_REQUIRE(PonyEngine::Math::Abs(floatVectorY) == floatVector);
	STATIC_REQUIRE(PonyEngine::Math::Abs(floatVectorXY) == floatVector);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Abs(PonyEngine::Math::Vector4<std::int32_t>(3, -1, -3, 1));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Abs(PonyEngine::Math::Vector4<float>(3.f, -1.f, -3.f, 1.f));
	};
#endif
}

TEST_CASE("Vector min", "[Math][Vector]")
{
	constexpr std::int16_t x = -50;
	constexpr std::int16_t y = 30;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Min(intVector, intVector1) == PonyEngine::Math::Vector2<std::int32_t>(x, y1));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Min(floatVector, floatVector1) == PonyEngine::Math::Vector2<float>(x, y1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Min(PonyEngine::Math::Vector4<std::int32_t>(3, -1, 4, -2), PonyEngine::Math::Vector4<std::int32_t>(-8, 7, 4, -4));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Min(PonyEngine::Math::Vector4<float>(3.f, -1.f, 4.f, -2.f), PonyEngine::Math::Vector4<float>(-8.f, 7.f, 4.f, -4.f));
	};
#endif
}

TEST_CASE("Vector max", "[Math][Vector]")
{
	constexpr std::int16_t x = -50;
	constexpr std::int16_t y = 30;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Max(intVector, intVector1) == PonyEngine::Math::Vector2<std::int32_t>(x1, y));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Max(floatVector, floatVector1) == PonyEngine::Math::Vector2<float>(x1, y));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Max(PonyEngine::Math::Vector4<std::int32_t>(3, -1, 4, -2), PonyEngine::Math::Vector4<std::int32_t>(-8, 7, 4, -4));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Max(PonyEngine::Math::Vector4<float>(3.f, -1.f, 4.f, -2.f), PonyEngine::Math::Vector4<float>(-8.f, 7.f, 4.f, -4.f));
	};
#endif
}

TEST_CASE("Vector clamp", "[Math][Vector]")
{
	constexpr std::int16_t x = 5;
	constexpr std::int16_t y = 30;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;
	constexpr std::int16_t x2 = 20;
	constexpr std::int16_t y2 = 10;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	constexpr auto intVector2 = PonyEngine::Math::Vector2<std::int32_t>(x2, y2);
	STATIC_REQUIRE(PonyEngine::Math::Clamp(intVector, intVector1, intVector2) == PonyEngine::Math::Vector2<std::int32_t>(x, y2));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(static_cast<float>(x1 - 1), static_cast<float>(y2 - 1));
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	constexpr auto floatVector2 = PonyEngine::Math::Vector2<float>(x2, y2);
	STATIC_REQUIRE(PonyEngine::Math::Clamp(floatVector, floatVector1, floatVector2) == PonyEngine::Math::Vector2<float>(x1, static_cast<float>(y2 - 1)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Clamp(PonyEngine::Math::Vector4<std::int32_t>(3, -1, 2, -2), PonyEngine::Math::Vector4<std::int32_t>(-8, 7, 0, -1), PonyEngine::Math::Vector4<std::int32_t>(8, 71, 4, 3));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Clamp(PonyEngine::Math::Vector4<float>(3.f, -1.f, 2.f, -2.f), PonyEngine::Math::Vector4<float>(-8.f, 7.f, 0.f, -1.f), PonyEngine::Math::Vector4<float>(8.f, 71.f, 4.f, 3.f));
	};
#endif
}

TEST_CASE("Vector clamp magnitude", "[Math][Vector]")
{
	constexpr std::int16_t x = 5;
	constexpr std::int16_t y = 3;
	constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
	REQUIRE(PonyEngine::Math::ClampMagnitude(vector, 100.f) == vector);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ClampMagnitude(vector, 2.3f), vector.Normalized() * 2.3f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("No clamp")
	{
		return PonyEngine::Math::ClampMagnitude(PonyEngine::Math::Vector4<float>(5.f, 3.f, 1.f, 0.5f), 100.f);
	};
	BENCHMARK("Clamp")
	{
		return PonyEngine::Math::ClampMagnitude(PonyEngine::Math::Vector4<float>(5.f, 3.f, 1.f, 0.5f), 1.5f);
	};
#endif
}

TEST_CASE("Vector lerp", "[Math][Vector]")
{
	constexpr std::int16_t x = 5;
	constexpr std::int16_t y = 30;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::Lerp(intVector, intVector1, 0.f) == intVector);
	STATIC_REQUIRE(PonyEngine::Math::Lerp(intVector, intVector1, 1.f) == intVector1);
	STATIC_REQUIRE(PonyEngine::Math::Lerp(intVector, intVector1, 0.5f) == PonyEngine::Math::Vector2<std::int32_t>(3, 12));
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
		return PonyEngine::Math::Lerp(PonyEngine::Math::Vector4<std::int32_t>(3, -1, 2, 3), PonyEngine::Math::Vector4<std::int32_t>(-8, 7, 0, 2), 0.7f);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Lerp(PonyEngine::Math::Vector4<float>(3.f, -1.f, 2.f, 3.f), PonyEngine::Math::Vector4<float>(-8.f, 7.f, 0.f, 2.f), 0.4f);
	};
#endif
}

TEST_CASE("Vector round to integral", "[Math][Vector]")
{
	constexpr float x = 5.4f;
	constexpr float y = 30.9f;
	constexpr float z = -2.6f;
	constexpr float w = -6.2f;

	constexpr auto vector = PonyEngine::Math::Vector4<float>(x, y, z, w);
	constexpr auto intVector = PonyEngine::Math::RoundToIntegral<std::int32_t>(vector);
	STATIC_REQUIRE(PonyEngine::Math::RoundToIntegral<std::int32_t>(x) == intVector.X());
	STATIC_REQUIRE(PonyEngine::Math::RoundToIntegral<std::int32_t>(y) == intVector.Y());
	STATIC_REQUIRE(PonyEngine::Math::RoundToIntegral<std::int32_t>(z) == intVector.Z());
	STATIC_REQUIRE(PonyEngine::Math::RoundToIntegral<std::int32_t>(w) == intVector.W());

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RoundToIntegral<std::int32_t>(PonyEngine::Math::Vector4<float>(5.1f, -5.9f, -10.1f, 8.8f));
	};
#endif
}

TEST_CASE("Vector are almost equal", "[Math][Vector]")
{
	constexpr std::int16_t x = -5;
	constexpr std::int16_t y = 3;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto vector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(vector, vector));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(vector, vector1));
	constexpr auto closeFloatVector = PonyEngine::Math::Vector2<float>(x + 0.000001f, y - 0.000001f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(vector, closeFloatVector));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector4<float>(3.f, 2.f, 0.f, -1.f), PonyEngine::Math::Vector4<float>(3.0000001f, 1.9999999f, 0.000000001f, -1.000000000001f));
	};
#endif
}

TEST_CASE("Vector sum", "[Math][Vector]")
{
	constexpr std::int16_t x = 5;
	constexpr std::int16_t y = 30;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(intVector + intVector1 == PonyEngine::Math::Vector2<std::int32_t>(x + x1, y + y1));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(floatVector + floatVector1, PonyEngine::Math::Vector2<float>(static_cast<float>(x + x1), static_cast<float>(y + y1))));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(5, 3, 0, 1) + PonyEngine::Math::Vector4<std::int32_t>(-7, 6, -1, 0);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector4<float>(5.f, 3.f, 0.f, 1.f) + PonyEngine::Math::Vector4<float>(-7.f, 6.f, -1.f, 0.f);
	};
#endif
}

TEST_CASE("Vector negation", "[Math][Vector]")
{
	constexpr std::int16_t x = 5;
	constexpr std::int16_t y = -30;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(-intVector == PonyEngine::Math::Vector2<std::int32_t>(-x, -y));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(-floatVector, PonyEngine::Math::Vector2<float>(static_cast<float>(-x), static_cast<float>(-y))));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return -PonyEngine::Math::Vector4<std::int32_t>(5, 3, -2, -1);
	};
	BENCHMARK("Float")
	{
		return -PonyEngine::Math::Vector4<float>(5.f, 3.f, -2.f, -1.f);
	};
#endif
}

TEST_CASE("Vector subtraction", "[Math][Vector]")
{
	constexpr std::int16_t x = 5;
	constexpr std::int16_t y = 30;
	constexpr std::int16_t x1 = 2;
	constexpr std::int16_t y1 = -6;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	constexpr auto intVector1 = PonyEngine::Math::Vector2<std::int32_t>(x1, y1);
	STATIC_REQUIRE(intVector - intVector1 == PonyEngine::Math::Vector2<std::int32_t>(x - x1, y - y1));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	constexpr auto floatVector1 = PonyEngine::Math::Vector2<float>(x1, y1);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(floatVector - floatVector1, PonyEngine::Math::Vector2<float>(static_cast<float>(x - x1), static_cast<float>(y - y1))));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(5, 3, 2, 3) - PonyEngine::Math::Vector4<std::int32_t>(-7, 6, -1, 2);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector4<float>(5.f, 3.f, 2.f, 3.f) - PonyEngine::Math::Vector4<float>(-7.f, 6.f, -1.f, 2.f);
	};
#endif
}

TEST_CASE("Vector product", "[Math][Vector]")
{
	constexpr std::int16_t x = 5;
	constexpr std::int16_t y = 30;
	constexpr std::int16_t multiplier = 4;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(intVector * static_cast<std::int32_t>(multiplier) == PonyEngine::Math::Vector2<std::int32_t>(x * multiplier, y * multiplier));
	STATIC_REQUIRE(static_cast<std::int32_t>(multiplier) * intVector == PonyEngine::Math::Vector2<std::int32_t>(x * multiplier, y * multiplier));
	STATIC_REQUIRE(intVector * static_cast<float>(multiplier) == PonyEngine::Math::Vector2<std::int32_t>(static_cast<std::int32_t>(x * static_cast<float>(multiplier)), static_cast<std::int32_t>(y * static_cast<float>(multiplier))));
	STATIC_REQUIRE(static_cast<float>(multiplier) * intVector == PonyEngine::Math::Vector2<std::int32_t>(static_cast<std::int32_t>(x * static_cast<float>(multiplier)), static_cast<std::int32_t>(y * static_cast<float>(multiplier))));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(floatVector * static_cast<float>(multiplier) == PonyEngine::Math::Vector2<float>(x * static_cast<float>(multiplier), y * static_cast<float>(multiplier)));
	STATIC_REQUIRE(static_cast<float>(multiplier) * floatVector == PonyEngine::Math::Vector2<float>(x * static_cast<float>(multiplier), y * static_cast<float>(multiplier)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int by int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(5, 3, -1, -2) * 4;
	};
	BENCHMARK("Int by float")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(5, 3, -1, -2) * 4.f;
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector4<float>(5.f, 3.f, -1.f, -2.f) * 4.f;
	};
#endif
}

TEST_CASE("Vector division", "[Math][Vector]")
{
	constexpr std::int16_t x = 50;
	constexpr std::int16_t y = 30;
	constexpr std::int16_t divisor = 4;

	constexpr auto intVector = PonyEngine::Math::Vector2<std::int32_t>(x, y);
	STATIC_REQUIRE(intVector / static_cast<std::int32_t>(divisor) == PonyEngine::Math::Vector2<std::int32_t>(x / divisor, y / divisor));
	STATIC_REQUIRE(intVector / static_cast<float>(divisor) == PonyEngine::Math::Vector2<std::int32_t>(static_cast<std::int32_t>(x / static_cast<float>(divisor)), static_cast<std::int32_t>(y / static_cast<float>(divisor))));

	constexpr auto floatVector = PonyEngine::Math::Vector2<float>(x, y);
	STATIC_REQUIRE(floatVector / static_cast<float>(divisor) == PonyEngine::Math::Vector2<float>(x / static_cast<float>(divisor), y / static_cast<float>(divisor)));

	STATIC_REQUIRE(divisor * 100 / intVector == PonyEngine::Math::Vector2<std::int32_t>(divisor * 100 / x, divisor * 100 / y));
	STATIC_REQUIRE(static_cast<float>(divisor * 100) / intVector == PonyEngine::Math::Vector2<std::int32_t>(static_cast<std::int32_t>(static_cast<float>(divisor * 100) / x), static_cast<std::int32_t>(static_cast<float>(divisor * 100) / y)));

	STATIC_REQUIRE(static_cast<float>(divisor) / floatVector == PonyEngine::Math::Vector2<float>(static_cast<float>(divisor) / x, static_cast<float>(divisor) / y));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int by int")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(50, 30, -10, -20) / 4;
	};
	BENCHMARK("Int by float")
	{
		return PonyEngine::Math::Vector4<std::int32_t>(50, 30, -10, -20) / 4.f;
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Vector4<float>(50.f, 30.f, -10.f, -20.f) / 4.f;
	};
	BENCHMARK("Int by int - Scalar")
	{
		return 400 / PonyEngine::Math::Vector4<std::int32_t>(50, 30, -10, -20);
	};
	BENCHMARK("Int by float - Scalar")
	{
		return 400.f / PonyEngine::Math::Vector4<std::int32_t>(50, 30, -10, -20);
	};
	BENCHMARK("Float - Scalar")
	{
		return 4.f / PonyEngine::Math::Vector4<float>(50.f, 30.f, -10.f, -20.f);
	};
#endif
}
