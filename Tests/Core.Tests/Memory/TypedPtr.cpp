/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <catch2/catch_test_macros.hpp>

import std;

import PonyEngine.Memory;

TEST_CASE("TypedPtr: ValueType", "[Memory][ObjectInterfaces]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Memory::TypedPtr<PonyEngine::Memory::Mutability::None>::ValueType, void>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Memory::TypedPtr<PonyEngine::Memory::Mutability::Constant>::ValueType, const void>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Memory::TypedPtr<PonyEngine::Memory::Mutability::Volatile>::ValueType, volatile void>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Memory::TypedPtr<PonyEngine::Memory::Mutability::All>::ValueType, const volatile void>);
}

TEST_CASE("TypedPtr: Default constructor", "[Memory][ObjectInterfaces]")
{
	const auto ptr = PonyEngine::Memory::TypedPtr();
	REQUIRE(ptr.Type() == typeid(std::nullptr_t));
	REQUIRE_FALSE(ptr.Get());
}

TEST_CASE("TypedPtr: Constructor", "[Memory][ObjectInterfaces]")
{
	int value = 3;
	const auto ptr = PonyEngine::Memory::TypedPtr(&value);
	REQUIRE(ptr.Type() == typeid(int));
	REQUIRE(ptr.Get() == &value);
}

TEST_CASE("TypedPtr: Copy constructor", "[Memory][ObjectInterfaces]")
{
	int value = 3;
	const auto ptr = PonyEngine::Memory::TypedPtr(&value);
	const auto copy = ptr;
	REQUIRE(copy.Type() == typeid(int));
	REQUIRE(copy.Get() == &value);
}

TEST_CASE("TypedPtr: Move constructor", "[Memory][ObjectInterfaces]")
{
	int value = 3;
	auto ptr = PonyEngine::Memory::TypedPtr(&value);
	const auto copy = std::move(ptr);
	REQUIRE(copy.Type() == typeid(int));
	REQUIRE(copy.Get() == &value);
}

TEST_CASE("TypedPtr: Bool cast", "[Memory][ObjectInterfaces]")
{
	REQUIRE_FALSE(static_cast<bool>(PonyEngine::Memory::TypedPtr<>()));

	int value = 3;
	const auto ptr = PonyEngine::Memory::TypedPtr(&value);
	REQUIRE(static_cast<bool>(ptr));
}

TEST_CASE("TypedPtr: Copy assignment", "[Memory][ObjectInterfaces]")
{
	int value = 3;
	const auto ptr = PonyEngine::Memory::TypedPtr(&value);
	auto copy = PonyEngine::Memory::TypedPtr();
	copy = ptr;
	REQUIRE(copy.Type() == typeid(int));
	REQUIRE(copy.Get() == &value);
}

TEST_CASE("TypedPtr: Move assignment", "[Memory][ObjectInterfaces]")
{
	int value = 3;
	auto ptr = PonyEngine::Memory::TypedPtr(&value);
	auto copy = PonyEngine::Memory::TypedPtr();
	copy = std::move(ptr);
	REQUIRE(copy.Type() == typeid(int));
	REQUIRE(copy.Get() == &value);
}

TEST_CASE("TypedPtr: equals", "[Memory][ObjectInterfaces]")
{
	int value0 = 3;
	int value1 = 2;

	const auto ptr0 = PonyEngine::Memory::TypedPtr(&value0);
	REQUIRE(ptr0 == ptr0);

	const auto ptr1 = PonyEngine::Memory::TypedPtr(&value0);
	REQUIRE(ptr0 == ptr1);

	const auto ptr2 = PonyEngine::Memory::TypedPtr(&value1);
	REQUIRE_FALSE(ptr0 == ptr2);

	const auto ptr3 = PonyEngine::Memory::TypedPtr(reinterpret_cast<char*>(&value0));
	REQUIRE_FALSE(ptr0 == ptr3);
}
