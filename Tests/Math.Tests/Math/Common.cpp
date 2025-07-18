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

TEST_CASE("DegToRad and RadToDeg", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::DegToRad<float>, std::numbers::pi_v<float> / 180.f));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::RadToDeg<float>, 180.f / std::numbers::pi_v<float>));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::DegToRad<double>, std::numbers::pi_v<double> / 180.));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::RadToDeg<double>, 180. / std::numbers::pi_v<double>));
}

TEST_CASE("AreAlmostEqual", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, 1.f - 1e-10f));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(1.f, 2.f));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, 2.f, 3.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, 1.f - 1e-10f));
	REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(1.f, 2.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, 2.f, 3.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreAlmostEqual(1.f, 1.f - 1e-10f) & PonyEngine::Math::AreAlmostEqual(1.f, 2.f);
	};
#endif
}

TEST_CASE("Sign", "[Math][Common]") 
{
	STATIC_REQUIRE(PonyEngine::Math::Sign(-5) == -1);
	STATIC_REQUIRE(PonyEngine::Math::Sign(0) == 1);
	STATIC_REQUIRE(PonyEngine::Math::Sign(7) == 1);
	STATIC_REQUIRE(PonyEngine::Math::Sign(-5.f) == -1.f);
	STATIC_REQUIRE(PonyEngine::Math::Sign(0.f) == 1.f);
	STATIC_REQUIRE(PonyEngine::Math::Sign(7.f) == 1.f);
	STATIC_REQUIRE(PonyEngine::Math::Sign<int>(-5.f) == -1);
	STATIC_REQUIRE(PonyEngine::Math::Sign<int>(0.f) == 1);
	STATIC_REQUIRE(PonyEngine::Math::Sign<int>(7.f) == 1);
	STATIC_REQUIRE(PonyEngine::Math::Sign<float>(-5) == -1.f);
	STATIC_REQUIRE(PonyEngine::Math::Sign<float>(0) == 1.f);
	STATIC_REQUIRE(PonyEngine::Math::Sign<float>(7) == 1.f);

	STATIC_REQUIRE(PonyEngine::Math::Sign<int>(true) == 1);
	STATIC_REQUIRE(PonyEngine::Math::Sign<int>(false) == -1);
	STATIC_REQUIRE(PonyEngine::Math::Sign<float>(true) == 1.f);
	STATIC_REQUIRE(PonyEngine::Math::Sign<float>(false) == -1.f);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int to int")
	{
		return PonyEngine::Math::Sign(-5) + PonyEngine::Math::Sign(0) + PonyEngine::Math::Sign(7);
	};
	BENCHMARK("Float to float")
	{
		return PonyEngine::Math::Sign(-5.f) + PonyEngine::Math::Sign(0.f) + PonyEngine::Math::Sign(7.f);
	};
	BENCHMARK("Float to int")
	{
		return PonyEngine::Math::Sign<int>(-5.f) + PonyEngine::Math::Sign<int>(0.f) + PonyEngine::Math::Sign<int>(7.f);
	};
	BENCHMARK("Int to float")
	{
		return PonyEngine::Math::Sign<float>(-5) + PonyEngine::Math::Sign<float>(0) + PonyEngine::Math::Sign<float>(7);
	};
	BENCHMARK("Bool to int")
	{
		return PonyEngine::Math::Sign<int>(true) + PonyEngine::Math::Sign<int>(false);
	};
	BENCHMARK("Bool to float")
	{
		return PonyEngine::Math::Sign<float>(true) + PonyEngine::Math::Sign<float>(false);
	};
#endif
}

TEST_CASE("Signum", "[Math][Common]") 
{
	STATIC_REQUIRE(PonyEngine::Math::Signum(-5) == -1);
	STATIC_REQUIRE(PonyEngine::Math::Signum(0) == 0);
	STATIC_REQUIRE(PonyEngine::Math::Signum(7) == 1);
	STATIC_REQUIRE(PonyEngine::Math::Signum(-5.f) == -1.f);
	STATIC_REQUIRE(PonyEngine::Math::Signum(0.f) == 0.f);
	STATIC_REQUIRE(PonyEngine::Math::Signum(7.f) == 1.f);

	STATIC_REQUIRE(PonyEngine::Math::Signum<int>(-5.f) == -1);
	STATIC_REQUIRE(PonyEngine::Math::Signum<int>(0.f) == 0);
	STATIC_REQUIRE(PonyEngine::Math::Signum<int>(7.f) == 1);
	STATIC_REQUIRE(PonyEngine::Math::Signum<float>(-5) == -1.f);
	STATIC_REQUIRE(PonyEngine::Math::Signum<float>(0) == 0.f);
	STATIC_REQUIRE(PonyEngine::Math::Signum<float>(7) == 1.f);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int to int")
	{
		return PonyEngine::Math::Signum(-5) + PonyEngine::Math::Signum(0) + PonyEngine::Math::Signum(7);
	};
	BENCHMARK("Float to float")
	{
		return PonyEngine::Math::Signum(-5.f) + PonyEngine::Math::Signum(0.f) + PonyEngine::Math::Signum(7.f);
	};
	BENCHMARK("Int to float")
	{
		return PonyEngine::Math::Signum<float>(-5) + PonyEngine::Math::Signum<float>(0) + PonyEngine::Math::Signum<float>(7);
	};
	BENCHMARK("Float to int")
	{
		return PonyEngine::Math::Signum<int>(-5.f) + PonyEngine::Math::Signum<int>(0.f) + PonyEngine::Math::Signum<int>(7.f);
	};
#endif
}

TEST_CASE("RoundToIntegral", "[Math][Common]") 
{
	STATIC_REQUIRE(PonyEngine::Math::RoundToIntegral<unsigned int>(2.3f) == 2u);
	STATIC_REQUIRE(PonyEngine::Math::RoundToIntegral<unsigned int>(2.7f) == 3u);
	STATIC_REQUIRE(PonyEngine::Math::RoundToIntegral<int>(-2.3f) == -2);
	STATIC_REQUIRE(PonyEngine::Math::RoundToIntegral<int>(-2.7f) == -3);
	STATIC_REQUIRE(PonyEngine::Math::RoundToIntegral<int>(2.3f) == 2);
	STATIC_REQUIRE(PonyEngine::Math::RoundToIntegral<int>(2.7f) == 3);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float to unsigned int")
	{
		return PonyEngine::Math::RoundToIntegral<unsigned int>(2.3f) + PonyEngine::Math::RoundToIntegral<unsigned int>(2.7f);
	};
	BENCHMARK("Float to int")
	{
		return PonyEngine::Math::RoundToIntegral<int>(2.3f) + PonyEngine::Math::RoundToIntegral<int>(-2.7f);
	};
#endif
}

TEST_CASE("DivideCeil", "[Math][Common]") 
{
	STATIC_REQUIRE(PonyEngine::Math::DivideCeil(10u, 3u) == 4u);
	STATIC_REQUIRE(PonyEngine::Math::DivideCeil(9u, 3u) == 3u);
	STATIC_REQUIRE(PonyEngine::Math::DivideCeil(0u, 3u) == 0u);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::DivideCeil(10u, 3u);
	};
#endif
}

TEST_CASE("Align", "[Math][Common]") 
{
	STATIC_REQUIRE(PonyEngine::Math::Align(5u, 4u) == 8u);
	STATIC_REQUIRE(PonyEngine::Math::Align(16u, 8u) == 16u);
	STATIC_REQUIRE(PonyEngine::Math::Align(17u, 8u) == 24u);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Align(17u, 8u);
	};
#endif
}

TEST_CASE("Align SIMD", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::AlignSIMD(0, 0) == 0uz);
	STATIC_REQUIRE(PonyEngine::Math::AlignSIMD(0, 1) == 0uz);
	STATIC_REQUIRE(PonyEngine::Math::AlignSIMD(1, 1) == 1uz);
	STATIC_REQUIRE(PonyEngine::Math::AlignSIMD(2, 1) == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::AlignSIMD(2, 2) == 4uz);
	STATIC_REQUIRE(PonyEngine::Math::AlignSIMD(4, 3) == 4uz);
	STATIC_REQUIRE(PonyEngine::Math::AlignSIMD(4, 4) == 16uz);
	STATIC_REQUIRE(PonyEngine::Math::AlignSIMD(4, 10) == 8uz);
	STATIC_REQUIRE(PonyEngine::Math::AlignSIMD(4, 16) == 64uz);
	STATIC_REQUIRE(PonyEngine::Math::AlignSIMD(4, 9) == 4uz);
}

TEST_CASE("Abs", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::Abs(5) == 5);
	STATIC_REQUIRE(PonyEngine::Math::Abs(-5) == 5);
	STATIC_REQUIRE(PonyEngine::Math::Abs(5.f) == 5.f);
	STATIC_REQUIRE(PonyEngine::Math::Abs(-5.f) == 5.f);
	STATIC_REQUIRE(PonyEngine::Math::Abs(5u) == 5u);
	REQUIRE(PonyEngine::Math::Abs(5) == 5);
	REQUIRE(PonyEngine::Math::Abs(-5) == 5);
	REQUIRE(PonyEngine::Math::Abs(5.f) == 5.f);
	REQUIRE(PonyEngine::Math::Abs(-5.f) == 5.f);
	REQUIRE(PonyEngine::Math::Abs(5u) == 5u);
}

TEST_CASE("Factorial", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::Factorial(0u) == 1u);
	STATIC_REQUIRE(PonyEngine::Math::Factorial(1u) == 1u);
	STATIC_REQUIRE(PonyEngine::Math::Factorial(2u) == 2u);
	STATIC_REQUIRE(PonyEngine::Math::Factorial(10u) == 3628800u);
	STATIC_REQUIRE(PonyEngine::Math::Factorial(20ull) == 2432902008176640000ull);
	REQUIRE(PonyEngine::Math::Factorial(0u) == 1u);
	REQUIRE(PonyEngine::Math::Factorial(1u) == 1u);
	REQUIRE(PonyEngine::Math::Factorial(2u) == 2u);
	REQUIRE(PonyEngine::Math::Factorial(10u) == 3628800u);
	REQUIRE(PonyEngine::Math::Factorial(20ull) == 2432902008176640000ull);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Zero")
	{
		return PonyEngine::Math::Factorial(0u);
	};
	BENCHMARK("One")
	{
		return PonyEngine::Math::Factorial(1u);
	};
	BENCHMARK("Ten")
	{
		return PonyEngine::Math::Factorial(10u);
	};
	BENCHMARK("Twenty")
	{
		return PonyEngine::Math::Factorial(20u);
	};
#endif
}

TEST_CASE("IsInf", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::IsInf(std::numeric_limits<float>::infinity()));
	STATIC_REQUIRE(PonyEngine::Math::IsInf(-std::numeric_limits<float>::infinity()));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInf(1.23f));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInf(0.f));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInf(std::numeric_limits<float>::quiet_NaN()));
	REQUIRE(PonyEngine::Math::IsInf(std::numeric_limits<float>::infinity()));
	REQUIRE(PonyEngine::Math::IsInf(-std::numeric_limits<float>::infinity()));
	REQUIRE_FALSE(PonyEngine::Math::IsInf(1.23f));
	REQUIRE_FALSE(PonyEngine::Math::IsInf(0.f));
	REQUIRE_FALSE(PonyEngine::Math::IsInf(std::numeric_limits<float>::quiet_NaN()));

	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInf(42));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInf(0));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsInf(-69));
	REQUIRE_FALSE(PonyEngine::Math::IsInf(42));
	REQUIRE_FALSE(PonyEngine::Math::IsInf(0));
	REQUIRE_FALSE(PonyEngine::Math::IsInf(-69));
}

TEST_CASE("IsNan", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::IsNan(std::numeric_limits<float>::quiet_NaN()));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsNan(std::numeric_limits<float>::infinity()));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsNan(-std::numeric_limits<float>::infinity()));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsNan(0.f));
	REQUIRE(PonyEngine::Math::IsNan(std::numeric_limits<float>::quiet_NaN()));
	REQUIRE_FALSE(PonyEngine::Math::IsNan(std::numeric_limits<float>::infinity()));
	REQUIRE_FALSE(PonyEngine::Math::IsNan(-std::numeric_limits<float>::infinity()));
	REQUIRE_FALSE(PonyEngine::Math::IsNan(0.f));

	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsNan(42));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsNan(0));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsNan(-69));
	REQUIRE_FALSE(PonyEngine::Math::IsNan(42));
	REQUIRE_FALSE(PonyEngine::Math::IsNan(0));
	REQUIRE_FALSE(PonyEngine::Math::IsNan(-69));
}

TEST_CASE("IsNormal", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::IsNormal(1.23f));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsNormal(0.f));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsNormal(std::numeric_limits<float>::infinity()));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsNormal(-std::numeric_limits<float>::infinity()));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsNormal(std::numeric_limits<float>::quiet_NaN()));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsNormal(std::numeric_limits<float>::denorm_min()));
	REQUIRE(PonyEngine::Math::IsNormal(1.23f));
	REQUIRE_FALSE(PonyEngine::Math::IsNormal(0.f));
	REQUIRE_FALSE(PonyEngine::Math::IsNormal(std::numeric_limits<float>::infinity()));
	REQUIRE_FALSE(PonyEngine::Math::IsNormal(-std::numeric_limits<float>::infinity()));
	REQUIRE_FALSE(PonyEngine::Math::IsNormal(std::numeric_limits<float>::quiet_NaN()));
	REQUIRE_FALSE(PonyEngine::Math::IsNormal(std::numeric_limits<float>::denorm_min()));

	STATIC_REQUIRE(PonyEngine::Math::IsNormal(42));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsNormal(0));
	STATIC_REQUIRE(PonyEngine::Math::IsNormal(-69));
	REQUIRE(PonyEngine::Math::IsNormal(42));
	REQUIRE_FALSE(PonyEngine::Math::IsNormal(0));
	REQUIRE(PonyEngine::Math::IsNormal(-69));
}

TEST_CASE("IsFinite", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::IsFinite(1.23f));
	STATIC_REQUIRE(PonyEngine::Math::IsFinite(0.f));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsFinite(std::numeric_limits<float>::infinity()));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsFinite(-std::numeric_limits<float>::infinity()));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsFinite(std::numeric_limits<float>::quiet_NaN()));
	REQUIRE(PonyEngine::Math::IsFinite(1.23f));
	REQUIRE(PonyEngine::Math::IsFinite(0.f));
	REQUIRE_FALSE(PonyEngine::Math::IsFinite(std::numeric_limits<float>::infinity()));
	REQUIRE_FALSE(PonyEngine::Math::IsFinite(-std::numeric_limits<float>::infinity()));
	REQUIRE_FALSE(PonyEngine::Math::IsFinite(std::numeric_limits<float>::quiet_NaN()));

	STATIC_REQUIRE(PonyEngine::Math::IsFinite(42));
	STATIC_REQUIRE(PonyEngine::Math::IsFinite(0));
	STATIC_REQUIRE(PonyEngine::Math::IsFinite(-69));
	REQUIRE(PonyEngine::Math::IsFinite(42));
	REQUIRE(PonyEngine::Math::IsFinite(0));
	REQUIRE(PonyEngine::Math::IsFinite(-69));
}

TEST_CASE("IsEven/Odd", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::IsEven(0));
	STATIC_REQUIRE(PonyEngine::Math::IsEven(2));
	STATIC_REQUIRE(PonyEngine::Math::IsEven(-10));
	STATIC_REQUIRE(PonyEngine::Math::IsOdd(1));
	STATIC_REQUIRE(PonyEngine::Math::IsOdd(7));
	STATIC_REQUIRE(PonyEngine::Math::IsOdd(-11));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsOdd(0));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsOdd(2));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsOdd(-10));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsEven(1));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsEven(7));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsEven(-11));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("IsEven")
	{
		return PonyEngine::Math::IsEven(2) | PonyEngine::Math::IsEven(7);
	};
	BENCHMARK("IsOdd")
	{
		return PonyEngine::Math::IsEven(5) | PonyEngine::Math::IsEven(12);
	};
#endif
}
