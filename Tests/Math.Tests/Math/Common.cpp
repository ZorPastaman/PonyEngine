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

TEST_CASE("Arithmetic concept", "[Math][Common]") 
{
	STATIC_REQUIRE(PonyEngine::Math::Arithmetic<std::int32_t>);
	STATIC_REQUIRE(PonyEngine::Math::Arithmetic<std::uint64_t>);
	STATIC_REQUIRE(PonyEngine::Math::Arithmetic<float>);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Arithmetic<void*>);
}

TEST_CASE("Signed concept", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::Signed<std::int16_t>);
	STATIC_REQUIRE(PonyEngine::Math::Signed<float>);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Signed<std::uint32_t>);
}

TEST_CASE("IsGreater", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::IsGreater<double, float>);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsGreater<float, double>);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsGreater<float, std::int64_t>);
	STATIC_REQUIRE(PonyEngine::Math::IsGreater<std::int64_t, float>);
	STATIC_REQUIRE(PonyEngine::Math::IsGreater<std::uint16_t, std::int8_t>);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsGreater<std::int8_t, std::uint16_t>);
}
TEST_CASE("IsLess", "[Math][Common]")
{
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsLess<double, float>);
	STATIC_REQUIRE(PonyEngine::Math::IsLess<float, double>);
	STATIC_REQUIRE(PonyEngine::Math::IsLess<float, std::int64_t>);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsLess<std::int64_t, float>);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsLess<std::uint16_t, std::int8_t>);
	STATIC_REQUIRE(PonyEngine::Math::IsLess<std::int8_t, std::uint16_t>);
}

TEST_CASE("IsEqual", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::IsEqual<std::int64_t, std::int64_t>);
	STATIC_REQUIRE(PonyEngine::Math::IsEqual<std::int64_t, std::uint64_t>);
	STATIC_REQUIRE(PonyEngine::Math::IsEqual<std::int32_t, float>);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsEqual<std::int16_t, double>);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::IsEqual<float, double>);
}

TEST_CASE("FloatingBySize and ComputationalFor", "[Math][Common]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::FloatingBySize<float>, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::FloatingBySize<double>, double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::FloatingBySize<std::int16_t>, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::FloatingBySize<std::uint32_t>, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::FloatingBySize<std::int64_t>, double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::FloatingBySize<std::uint64_t>, double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::FloatingBySize<std::pair<std::int64_t, std::int8_t>>, long double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::FloatingBySize<std::pair<std::uint64_t, std::uint8_t>>, long double>);
}

TEST_CASE("ComputationalFor", "[Math][Common]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::ComputationalFor<float>, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::ComputationalFor<double>, double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::ComputationalFor<long double>, long double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::ComputationalFor<std::int8_t>, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::ComputationalFor<std::uint16_t>, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::ComputationalFor<std::int32_t>, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::ComputationalFor<std::uint64_t>, double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::ComputationalFor<std::pair<std::int64_t, std::int8_t>>, long double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::ComputationalFor<std::pair<std::uint64_t, std::uint8_t>>, long double>);
}

TEST_CASE("DegToRad and RadToDeg", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::DegToRad<float>, std::numbers::pi_v<float> / 180.f));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::RadToDeg<float>, 180.f / std::numbers::pi_v<float>));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::DegToRad<double>, std::numbers::pi_v<double> / 180.));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::RadToDeg<double>, 180. / std::numbers::pi_v<double>));
}

TEST_CASE("AreAlmostEqual", "[Math][Common]")
{
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, 1.f - 1e-6f));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(1.f, 2.f));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, 2.f, 3.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, 1.f - 1e-6f));
	REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(1.f, 2.f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, 2.f, 3.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreAlmostEqual(1.f, 1.f - 1e-6f) & PonyEngine::Math::AreAlmostEqual(1.f, 2.f);
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
