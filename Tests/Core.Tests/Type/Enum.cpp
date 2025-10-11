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
		"Unknown"
	};
	ENUM_VALUE_TO_STRING(Color, ColorNames)

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
	ENUM_MASK_TO_STRING(Permission, PermissionNames)
	ENUM_MASK_OPERATORS(Permission)
	ENUM_MASK_CHECKS(Permission)

	ENUM_VALUE_MASK(Color, Permission)
}

ENUM_VALUE_FORMATTER(Name, Color)
ENUM_MASK_FORMATTER(Name, Permission)

TEST_CASE("ENUM_VALUE_TO_STRING works for valid and invalid values", "[Utility][Enum]")
{
	STATIC_REQUIRE(Name::ToString(Name::Color::Red) == Name::ColorNames[0]);
	STATIC_REQUIRE(Name::ToString(Name::Color::Green) == Name::ColorNames[1]);
	STATIC_REQUIRE(Name::ToString(Name::Color::Blue) == Name::ColorNames[2]);
	STATIC_REQUIRE(Name::ToString(static_cast<Name::Color>(99)) == Name::ColorNames[3]);

	std::ostringstream oss;
	oss << Name::Color::Red;
	REQUIRE(oss.str() == Name::ColorNames[0]);

	std::string formatted = std::format("{}", Name::Color::Green);
	REQUIRE(Name::ToString(Name::Color::Green) == formatted);
}

TEST_CASE("ENUM_MASK_TO_STRING works for masks", "[Utility][Enum]")
{
	REQUIRE(Name::ToString(Name::Permission::None) == "None");
	REQUIRE(Name::ToString(Name::Permission::All) == "All");
	REQUIRE(Name::ToString(Name::Permission::Read) == Name::PermissionNames[0]);
	REQUIRE(Name::ToString(Name::Permission::Write) == Name::PermissionNames[1]);
	REQUIRE(Name::ToString(Name::Permission::Execute) == Name::PermissionNames[2]);
	REQUIRE(Name::ToString(Name::Permission::Read | Name::Permission::Write) == "Read | Write");
	REQUIRE(Name::ToString(Name::Permission::Read | Name::Permission::Execute) == "Read | Execute");
	REQUIRE(Name::ToString(static_cast<Name::Permission>(99)) == "Unknown");

	std::ostringstream oss;
	oss << Name::Permission::Execute;
	REQUIRE(oss.str() == "Execute");

	std::string formatted = std::format("{}", Name::Permission::Read | Name::Permission::Write);
	REQUIRE(Name::ToString(Name::Permission::Read | Name::Permission::Write) == formatted);
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
