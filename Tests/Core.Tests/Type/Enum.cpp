/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Type/Enum.h"

#include <catch2/catch_test_macros.hpp>

import std;

namespace Name
{
	enum class Color : uint8_t
	{
		Red,
		Green,
		Blue
	};
	constexpr std::array<std::string_view, 4> ColorNames
	{
		"Red",
		"Green",
		"Blue",
	};

	enum class Permission : uint8_t
	{
		None = 0,
		Read = 1 << 0,
		Write = 1 << 1,
		Execute = 1 << 2,
		All = Read | Write | Execute
	};
	constexpr std::array<std::string_view, 3> PermissionNames
	{
		"Read",
		"Write",
		"Execute"
	};
	PONY_ENUM_MASK_OPERATORS(Permission)
	PONY_ENUM_MASK_CHECKS(Permission)

	PONY_ENUM_VALUE_MASK(Color, Permission)
}

PONY_ENUM_VALUE_FORMATTER(Name::Color, Name::ColorNames)
PONY_ENUM_MASK_FORMATTER(Name::Permission, Name::PermissionNames)

TEST_CASE("ENUM_VALUE_TO_STRING works for valid and invalid values", "[Utility][Enum]")
{
	REQUIRE(std::format("{}", Name::Color::Red) == Name::ColorNames[0]);
	REQUIRE(std::format("{}", Name::Color::Green) == Name::ColorNames[1]);
	REQUIRE(std::format("{}", Name::Color::Blue) == Name::ColorNames[2]);
	REQUIRE(std::format("{}", static_cast<Name::Color>(99)) == "Unknown");
}

TEST_CASE("ENUM_MASK_TO_STRING works for masks", "[Utility][Enum]")
{
	REQUIRE(std::format("{}", Name::Permission::None) == "None");
	REQUIRE(std::format("{}", Name::Permission::All) == "All");
	REQUIRE(std::format("{}", Name::Permission::Read) == Name::PermissionNames[0]);
	REQUIRE(std::format("{}", Name::Permission::Write) == Name::PermissionNames[1]);
	REQUIRE(std::format("{}", Name::Permission::Execute) == Name::PermissionNames[2]);
	REQUIRE(std::format("{}", Name::Permission::Read | Name::Permission::Write) == "Read | Write");
	REQUIRE(std::format("{}", Name::Permission::Read | Name::Permission::Execute) == "Read | Execute");
	REQUIRE(std::format("{}", static_cast<Name::Permission>(99)) == "Unknown");
}

TEST_CASE("ENUM_MASK_OPERATORS work as expected", "[Utility][Enum]")
{
	STATIC_REQUIRE(((Name::Permission::Read | Name::Permission::Write) & Name::Permission::Read) == Name::Permission::Read);
	STATIC_REQUIRE(((Name::Permission::Read | Name::Permission::Write) & Name::Permission::Execute) == Name::Permission::None);
	STATIC_REQUIRE((Name::Permission::Read | Name::Permission::Write | Name::Permission::Execute) == Name::Permission::All);
	STATIC_REQUIRE(((Name::Permission::Read | Name::Permission::Write) ^ Name::Permission::Read) == Name::Permission::Write);
	STATIC_REQUIRE(~Name::Permission::None == Name::Permission::All);
	STATIC_REQUIRE(~Name::Permission::Write == (Name::Permission::Read | Name::Permission::Execute));
}

TEST_CASE("ENUM_MASK_CHECKS work as expected", "[Utility][Enum]")
{
	STATIC_REQUIRE(Name::All(Name::Permission::Read | Name::Permission::Execute, Name::Permission::All));
	STATIC_REQUIRE_FALSE(Name::All(Name::Permission::Read | Name::Permission::Execute, Name::Permission::Read));
	STATIC_REQUIRE(Name::Any(Name::Permission::Read | Name::Permission::Execute, Name::Permission::Read | Name::Permission::Write));
	STATIC_REQUIRE_FALSE(Name::Any(Name::Permission::Read | Name::Permission::Execute, Name::Permission::Write));
	STATIC_REQUIRE_FALSE(Name::None(Name::Permission::Read | Name::Permission::Execute, Name::Permission::Read | Name::Permission::Write));
	STATIC_REQUIRE(Name::None(Name::Permission::Read | Name::Permission::Execute, Name::Permission::Write));
}

TEST_CASE("ENUM_VALUE_MASK conversions work", "[Utility][Enum]")
{
	STATIC_REQUIRE(Name::ToMask(Name::Color::Red) == Name::Permission::Read);
	STATIC_REQUIRE(Name::ToMask(Name::Color::Green) == Name::Permission::Write);
	STATIC_REQUIRE(Name::ToMask(Name::Color::Blue) == Name::Permission::Execute);

	constexpr std::array colors = { Name::Color::Red, Name::Color::Blue };
	STATIC_REQUIRE(ToMask(std::span(colors)) == (Name::Permission::Read | Name::Permission::Execute));

	constexpr auto mask = Name::Permission::Read | Name::Permission::Write;
	STATIC_REQUIRE(IsInMask(Name::Color::Red, mask));
	STATIC_REQUIRE(IsInMask(Name::Color::Green, mask));
	STATIC_REQUIRE_FALSE(IsInMask(Name::Color::Blue, mask));

	STATIC_REQUIRE(Name::ToValue(Name::Permission::Write) == Name::Color::Green);

	auto toValues = [](const Name::Permission m) constexpr
	{
		auto arr = std::array<Name::Color, 3>();
		const std::size_t c = Name::ToValues(m, arr);

		return std::pair(arr, c);
	};
	constexpr auto out = toValues(Name::Permission::Read | Name::Permission::Execute);
	STATIC_REQUIRE(out.second == 2);
	STATIC_REQUIRE(out.first[0] == Name::Color::Red);
	STATIC_REQUIRE(out.first[1] == Name::Color::Blue);
}
