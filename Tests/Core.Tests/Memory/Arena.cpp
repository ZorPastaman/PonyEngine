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
	constexpr std::size_t alignment = 64uz;
	constexpr std::size_t reserve = 256uz;
	auto arena = PonyEngine::Memory::Arena(alignment, reserve);
	REQUIRE(arena.Alignment() == alignment);
	REQUIRE(arena.Size() == 0uz);
	REQUIRE(arena.Capacity() == reserve);
	REQUIRE(arena.Data());
	REQUIRE(arena.GetMarker().index == 0uz);
}

TEST_CASE("Arena: reserve", "[Memory][Arena]")
{
	constexpr std::size_t alignment = 64uz;
	constexpr std::size_t reserve = 256uz;
	auto arena = PonyEngine::Memory::Arena(alignment);
	REQUIRE(arena.Alignment() == alignment);
	REQUIRE(arena.Size() == 0uz);
	REQUIRE(arena.Capacity() == 0uz);
	REQUIRE(arena.Data());
	REQUIRE(arena.GetMarker().index == 0uz);

	arena.Reserve(reserve);
	REQUIRE(arena.Alignment() == alignment);
	REQUIRE(arena.Size() == 0uz);
	REQUIRE(arena.Capacity() == reserve);
	REQUIRE(arena.Data());
	REQUIRE(arena.GetMarker().index == 0uz);

	arena.Reserve(reserve / 2uz);
	REQUIRE(arena.Alignment() == alignment);
	REQUIRE(arena.Size() == 0uz);
	REQUIRE(arena.Capacity() == reserve);
	REQUIRE(arena.Data());
	REQUIRE(arena.GetMarker().index == 0uz);

	arena.Reserve(reserve * 2uz);
	REQUIRE(arena.Alignment() == alignment);
	REQUIRE(arena.Size() == 0uz);
	REQUIRE(arena.Capacity() == reserve * 2uz);
	REQUIRE(arena.Data());
	REQUIRE(arena.GetMarker().index == 0uz);
}

TEST_CASE("Arena: reserve data safety", "[Memory][Arena]")
{
	auto arena = PonyEngine::Memory::Arena(32uz);
	const PonyEngine::Memory::Arena::Slice<std::int32_t> slice = arena.Allocate<std::int32_t>(3);
	std::span<std::int32_t> span = arena.Span(slice);
	span[0] = 4;
	span[1] = -6;
	span[2] = 0;
	arena.Reserve(1024uz);
	span = arena.Span(slice);
	REQUIRE(span[0] == 4);
	REQUIRE(span[1] == -6);
	REQUIRE(span[2] == 0);
}

TEST_CASE("Arena: allocate", "[Memory][Arena]")
{
	auto arena = PonyEngine::Memory::Arena(32uz);
	REQUIRE_THROWS(arena.Allocate(64uz, 64uz, 2uz));
	REQUIRE_THROWS(arena.Allocate(32uz, 4uz, 2uz));
	PonyEngine::Memory::Arena::Slice<std::byte> slice = arena.Allocate(32uz, 32uz, 4uz);
	REQUIRE(arena.Size() == 128uz);
	REQUIRE(arena.Capacity() == 128uz);
	REQUIRE(arena.GetMarker().index == 128uz);
	REQUIRE(slice.byteOffset == 0uz);
	REQUIRE(slice.objectCount == 128uz);

	slice = arena.Allocate(4uz, 8uz, 3uz);
	REQUIRE(arena.Size() == 152uz);
	REQUIRE(arena.Capacity() == 256uz);
	REQUIRE(arena.GetMarker().index == 152uz);
	REQUIRE(slice.byteOffset == 128uz);
	REQUIRE(slice.objectCount == 24uz);

	slice = arena.Allocate(16uz, 16uz, 2uz);
	REQUIRE(arena.Size() == 192uz);
	REQUIRE(arena.Capacity() == 256uz);
	REQUIRE(arena.GetMarker().index == 192uz);
	REQUIRE(slice.byteOffset == 160uz);
	REQUIRE(slice.objectCount == 32uz);
}

TEST_CASE("Arena: allocate T", "[Memory][Arena]")
{
	struct alignas(64) TooBig final
	{
		std::uint32_t data;
	};
	struct alignas(32) Data32 final
	{
		std::uint64_t data;
	};
	struct alignas(4) Data4 final
	{
		std::uint32_t data;
	};
	struct alignas(16) Data16 final
	{
		std::uint64_t data;
	};

	auto arena = PonyEngine::Memory::Arena(32uz);
	REQUIRE_THROWS(arena.Allocate<TooBig>(2uz));
	const PonyEngine::Memory::Arena::Slice<Data32> slice32 = arena.Allocate<Data32>(4uz);
	REQUIRE(arena.Size() == 128uz);
	REQUIRE(arena.Capacity() == 128uz);
	REQUIRE(arena.GetMarker().index == 128uz);
	REQUIRE(slice32.byteOffset == 0uz);
	REQUIRE(slice32.objectCount == 4uz);

	const PonyEngine::Memory::Arena::Slice<Data4> slice4 = arena.Allocate<Data4>(6uz);
	REQUIRE(arena.Size() == 152uz);
	REQUIRE(arena.Capacity() == 256uz);
	REQUIRE(arena.GetMarker().index == 152uz);
	REQUIRE(slice4.byteOffset == 128uz);
	REQUIRE(slice4.objectCount == 6uz);

	const PonyEngine::Memory::Arena::Slice<Data16> slice16 = arena.Allocate<Data16>(2uz);
	REQUIRE(arena.Size() == 192uz);
	REQUIRE(arena.Capacity() == 256uz);
	REQUIRE(arena.GetMarker().index == 192uz);
	REQUIRE(slice16.byteOffset == 160uz);
	REQUIRE(slice16.objectCount == 2uz);
}

TEST_CASE("Arena: span", "[Memory][Arena]")
{
	struct alignas(32) Data32 final
	{
		std::uint64_t data;
	};
	struct alignas(4) Data4 final
	{
		std::uint32_t data;
	};

	auto arena = PonyEngine::Memory::Arena(32uz);

	PonyEngine::Memory::Arena::Slice<std::byte> slice = arena.Allocate(32uz, 32uz, 4uz);
	std::span<std::byte> span = arena.Span(slice);
	REQUIRE(span.data() == arena.Data() + slice.byteOffset);
	REQUIRE(span.size() == slice.objectCount);

	slice = arena.Allocate(4uz, 8uz, 3uz);
	span = arena.Span(slice);
	REQUIRE(span.data() == arena.Data() + slice.byteOffset);
	REQUIRE(span.size() == slice.objectCount);

	const PonyEngine::Memory::Arena::Slice<Data32> slice32 = arena.Allocate<Data32>(4uz);
	const std::span<Data32> span32 = arena.Span(slice32);
	REQUIRE(reinterpret_cast<std::byte*>(span32.data()) == arena.Data() + slice32.byteOffset);
	REQUIRE(span32.size() == slice32.objectCount);

	const PonyEngine::Memory::Arena::Slice<Data4> slice4 = arena.Allocate<Data4>(2uz);
	const std::span<Data4> span4 = arena.Span(slice4);
	REQUIRE(reinterpret_cast<std::byte*>(span4.data()) == arena.Data() + slice4.byteOffset);
	REQUIRE(span4.size() == slice4.objectCount);
}

TEST_CASE("Arena: free", "[Memory][Arena]")
{
	struct alignas(32) Data32 final
	{
		std::uint64_t data;
	};
	struct alignas(4) Data4 final
	{
		std::uint32_t data;
	};

	auto arena = PonyEngine::Memory::Arena(32uz);

	PonyEngine::Memory::Arena::Marker marker = arena.GetMarker();
	(void)arena.Allocate(32uz, 32uz, 4uz);
	arena.Free(marker);
	REQUIRE(arena.Size() == 0uz);

	(void)arena.Allocate(32uz, 32uz, 4uz);
	marker = arena.GetMarker();
	(void)arena.Allocate(4uz, 8uz, 3uz);
	arena.Free(marker);
	REQUIRE(arena.Size() == 128uz);

	(void)arena.Allocate(32uz, 32uz, 4uz);
	arena.Free();
	REQUIRE(arena.Size() == 0uz);
}
