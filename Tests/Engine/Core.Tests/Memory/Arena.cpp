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

import PonyEngine.Memory;

TEST_CASE("Arena: create", "[Memory][Arena]")
{
	alignas(64) std::array<std::byte, 1024> buffer;
	auto arena = PonyEngine::Memory::Arena(buffer);
	REQUIRE(arena.Size() == 0uz);
	REQUIRE(arena.Capacity() == buffer.size());
	REQUIRE(arena.GetMarker().mark == 0uz);
}

TEST_CASE("Arena: scope", "[Memory][Arena]")
{
	alignas(64) std::array<std::byte, 1024> buffer;
	auto arena = PonyEngine::Memory::Arena(buffer);

	{
		const auto marker = arena.GetMarker();
		const auto scope = arena.GetScope();
		REQUIRE(scope.Arena() == &arena);
		REQUIRE(scope.Marker().mark == marker.mark);

		(void)arena.AllocateArray(32uz, 32uz, 4uz);
	}

	REQUIRE(arena.Size() == 0uz);

	(void)arena.AllocateArray(32uz, 32uz, 4uz);

	{
		const auto marker = arena.GetMarker();
		const auto scope = arena.GetScope();
		REQUIRE(scope.Arena() == &arena);
		REQUIRE(scope.Marker().mark == marker.mark);

		(void)arena.AllocateArray(32uz, 32uz, 4uz);
	}

	REQUIRE(arena.Size() == 128uz);
}

TEST_CASE("Arena: allocate object", "[Memory][Arena]")
{
	alignas(64) std::array<std::byte, 1024> buffer;
	auto arena = PonyEngine::Memory::Arena(buffer);
	REQUIRE_THROWS(arena.AllocateObject(64uz, 64000uz));
	const void* const object = arena.AllocateObject(32uz, 32uz);
	REQUIRE(arena.Size() == 32uz);
	REQUIRE(arena.Capacity() == 1024uz);
	REQUIRE(arena.GetMarker().mark == 32uz);
	REQUIRE(object == buffer.data());

	const std::int64_t* const object1 = arena.AllocateObject<std::int64_t>();
	REQUIRE(arena.Size() == 40uz);
	REQUIRE(arena.Capacity() == 1024uz);
	REQUIRE(arena.GetMarker().mark == 40uz);
	REQUIRE(static_cast<const void*>(object1) == buffer.data() + 32uz);

	const std::int64_t* const object2 = arena.CreateObject<std::int64_t>(3);
	REQUIRE(arena.Size() == 48uz);
	REQUIRE(arena.Capacity() == 1024uz);
	REQUIRE(arena.GetMarker().mark == 48uz);
	REQUIRE(static_cast<const void*>(object2) == buffer.data() + 40uz);
	REQUIRE(*object2 == 3);
}

TEST_CASE("Arena: allocate array", "[Memory][Arena]")
{
	alignas(64) std::array<std::byte, 1024> buffer;
	auto arena = PonyEngine::Memory::Arena(buffer);
	REQUIRE_THROWS(arena.AllocateArray(64uz, 64000uz, 2uz));
	REQUIRE_THROWS(arena.AllocateArray(32uz, 4uz, 20000uz));
	const void* const slice = arena.AllocateArray(32uz, 32uz, 4uz);
	REQUIRE(arena.Size() == 128uz);
	REQUIRE(arena.Capacity() == 1024uz);
	REQUIRE(arena.GetMarker().mark == 128uz);
	REQUIRE(slice == buffer.data());

	const std::span<const std::pair<std::uint32_t, std::uint32_t>> slice1 = arena.AllocateArray<std::pair<std::uint32_t, std::uint32_t>>(3uz);
	REQUIRE(arena.Size() == 152uz);
	REQUIRE(arena.Capacity() == 1024uz);
	REQUIRE(arena.GetMarker().mark == 152uz);
	REQUIRE(static_cast<const void*>(slice1.data()) == buffer.data() + 128uz);
	REQUIRE(slice1.size() == 3uz);

	const std::span<const std::uint64_t> slice2 = arena.CreateArray<std::uint64_t>(2uz, 4);
	REQUIRE(arena.Size() == 168uz);
	REQUIRE(arena.Capacity() == 1024uz);
	REQUIRE(arena.GetMarker().mark == 168uz);
	REQUIRE(static_cast<const void*>(slice2.data()) == buffer.data() + 152uz);
	REQUIRE(slice2.size() == 2uz);
	REQUIRE(slice2[0] == 4);
	REQUIRE(slice2[1] == 4);
}
