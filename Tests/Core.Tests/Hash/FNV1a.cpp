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

import PonyEngine.Hash;

TEST_CASE("FNV1a32", "[Hash][FNV1a]")
{
	REQUIRE(PonyEngine::Hash::FNV1a32("") == 2166136261);
	REQUIRE(PonyEngine::Hash::FNV1a32("hello") == 1335831723);
	REQUIRE(PonyEngine::Hash::FNV1a32("Hello, world!") == 3985698964);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Hash::FNV1a32("Kinda_typical_length_of_an_asset_directory/on_some_machines/Kinda_typical_length_of_an_asset_name.extension");
	};
#endif
}

TEST_CASE("FNV1a64", "[Hash][FNV1a]")
{
	REQUIRE(PonyEngine::Hash::FNV1a64("") == 14695981039346656037);
	REQUIRE(PonyEngine::Hash::FNV1a64("hello") == 11831194018420276491);
	REQUIRE(PonyEngine::Hash::FNV1a64("Hello, world!") == 4094109891673226228);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Hash::FNV1a64("Kinda_typical_length_of_an_asset_directory/on_some_machines/Kinda_typical_length_of_an_asset_name.extension");
	};
#endif
}
