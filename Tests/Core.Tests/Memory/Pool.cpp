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

TEST_CASE("Pool: create", "[Memory][Pool]")
{
	const auto pool = PonyEngine::Memory::Pool<int>(
		[]() { return std::unique_ptr<int, std::function<void(int*)>>(new int(0), [](int* const ptr) { delete ptr; }); },
		[](int& object) { object = 42; },
		[](int& object) { object = 0; },
		[](const int& object) { return static_cast<std::uint64_t>(object); },
		10uz);
	REQUIRE(pool.MaxSize() == 10uz);
	REQUIRE(pool.ActiveCount() == 0uz);
	REQUIRE(pool.InactiveCount() == 0uz);

	const auto poolS = PonyEngine::Memory::Pool<int>(
		[]() { return std::unique_ptr<int, std::function<void(int*)>>(new int(0), [](int* const ptr) { delete ptr; }); },
		[](int& object) { object = 42; },
		[](int& object) { object = 0; },
		[](const int& object) { return static_cast<std::uint64_t>(object); },
		0uz);
	REQUIRE(poolS.MaxSize() == 1uz);
	REQUIRE(poolS.ActiveCount() == 0uz);
	REQUIRE(poolS.InactiveCount() == 0uz);
}

TEST_CASE("Pool: events", "[Memory][Pool]")
{
	std::size_t createCalled = 0uz;
	std::size_t destroyCalled = 0uz;
	std::size_t acquireCalled = 0uz;
	std::size_t releaseCalled = 0uz;
	std::size_t utilityCalled = 0uz;

	auto pool = PonyEngine::Memory::Pool<int>(
		[&]() { ++createCalled; return std::unique_ptr<int, std::function<void(int*)>>(new int(0), [&](int* const ptr) { ++destroyCalled; delete ptr; }); },
		[&](int& object) { ++acquireCalled; object = 42; },
		[&](int& object) { ++releaseCalled; object = 0; },
		[&](const int& object) { ++utilityCalled; return static_cast<std::uint64_t>(object); },
		2uz);

	int& obj0 = pool.Acquire();
	REQUIRE(pool.ActiveCount() == 1uz);
	REQUIRE(pool.InactiveCount() == 0uz);
	REQUIRE(createCalled == 1uz);
	REQUIRE(destroyCalled == 0uz);
	REQUIRE(acquireCalled == 1uz);
	REQUIRE(releaseCalled == 0uz);
	REQUIRE(!utilityCalled);

	int& obj1 = pool.Acquire();
	REQUIRE(pool.ActiveCount() == 2uz);
	REQUIRE(pool.InactiveCount() == 0uz);
	REQUIRE(createCalled == 2uz);
	REQUIRE(destroyCalled == 0uz);
	REQUIRE(acquireCalled == 2uz);
	REQUIRE(releaseCalled == 0uz);
	REQUIRE(!utilityCalled);

	int& obj2 = pool.Acquire();
	REQUIRE(pool.ActiveCount() == 3uz);
	REQUIRE(pool.InactiveCount() == 0uz);
	REQUIRE(createCalled == 3uz);
	REQUIRE(destroyCalled == 0uz);
	REQUIRE(acquireCalled == 3uz);
	REQUIRE(releaseCalled == 0uz);
	REQUIRE(!utilityCalled);

	int& obj3 = pool.Acquire();
	obj3 = 120;
	REQUIRE(pool.ActiveCount() == 4uz);
	REQUIRE(pool.InactiveCount() == 0uz);
	REQUIRE(createCalled == 4uz);
	REQUIRE(destroyCalled == 0uz);
	REQUIRE(acquireCalled == 4uz);
	REQUIRE(releaseCalled == 0uz);
	REQUIRE(!utilityCalled);

	pool.Release(obj1);
	REQUIRE(pool.ActiveCount() == 3uz);
	REQUIRE(pool.InactiveCount() == 1uz);
	REQUIRE(createCalled == 4uz);
	REQUIRE(destroyCalled == 0uz);
	REQUIRE(acquireCalled == 4uz);
	REQUIRE(releaseCalled == 1uz);
	REQUIRE(!utilityCalled);

	pool.Release(obj2);
	REQUIRE(pool.ActiveCount() == 2uz);
	REQUIRE(pool.InactiveCount() == 2uz);
	REQUIRE(createCalled == 4uz);
	REQUIRE(destroyCalled == 0uz);
	REQUIRE(acquireCalled == 4uz);
	REQUIRE(releaseCalled == 2uz);
	REQUIRE(!utilityCalled);

	pool.Release(obj0);
	REQUIRE(pool.ActiveCount() == 1uz);
	REQUIRE(pool.InactiveCount() == 2uz);
	REQUIRE(createCalled == 4uz);
	REQUIRE(destroyCalled == 1uz);
	REQUIRE(acquireCalled == 4uz);
	REQUIRE(releaseCalled == 3uz);
	REQUIRE(utilityCalled);

	pool.Release(obj3);
	REQUIRE(pool.ActiveCount() == 0uz);
	REQUIRE(pool.InactiveCount() == 2uz);
	REQUIRE(createCalled == 4uz);
	REQUIRE(destroyCalled == 2uz);
	REQUIRE(acquireCalled == 4uz);
	REQUIRE(releaseCalled == 4uz);
	REQUIRE(utilityCalled);

	int& obj4 = pool.Acquire();
	REQUIRE(pool.ActiveCount() == 1uz);
	REQUIRE(pool.InactiveCount() == 1uz);
	REQUIRE(createCalled == 4uz);
	REQUIRE(destroyCalled == 2uz);
	REQUIRE(acquireCalled == 5uz);
	REQUIRE(releaseCalled == 4uz);

	pool.Release(obj4);
	REQUIRE(pool.ActiveCount() == 0uz);
	REQUIRE(pool.InactiveCount() == 2uz);
	REQUIRE(createCalled == 4uz);
	REQUIRE(destroyCalled == 2uz);
	REQUIRE(acquireCalled == 5uz);
	REQUIRE(releaseCalled == 5uz);
}

TEST_CASE("Pool: lease", "[Memory][Pool]")
{
	auto pool = PonyEngine::Memory::Pool<int>(
		[]() { return std::unique_ptr<int, std::function<void(int*)>>(new int(0), [](int* const ptr) { delete ptr; }); },
		[](int& object) { object = 42; },
		[](int& object) { object = 0; },
		[](const int& object) { return static_cast<std::uint64_t>(object); },
		10uz);

	{
		PonyEngine::Memory::Pool<int>::Object lease0 = pool.Lease();
		REQUIRE(pool.ActiveCount() == 1uz);
		REQUIRE(pool.InactiveCount() == 0uz);
	}

	REQUIRE(pool.ActiveCount() == 0uz);
	REQUIRE(pool.InactiveCount() == 1uz);
}
