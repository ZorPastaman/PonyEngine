/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Utility/Enum.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <bit>
#include <format>
#include <ostream>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>

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

ENUM_VALUE_MASK(Color, Permission)

TEST_CASE("ENUM_VALUE_TO_STRING works for valid and invalid values", "[Utility][Enum]")
{
	REQUIRE(ToString(Color::Red) == ColorNames[0]);
	REQUIRE(ToString(Color::Green) == ColorNames[1]);
	REQUIRE(ToString(Color::Blue) == ColorNames[2]);
	REQUIRE(ToString(static_cast<Color>(99)) == ColorNames[3]);

	std::ostringstream oss;
	oss << Color::Red;
	REQUIRE(oss.str() == ColorNames[0]);

	std::string formatted = std::format("{}", Color::Green);
	REQUIRE(ToString(Color::Green) == formatted);
}

TEST_CASE("ENUM_MASK_TO_STRING works for masks", "[Utility][Enum]")
{
	REQUIRE(ToString(Permission::None) == "None");
	REQUIRE(ToString(Permission::All) == "All");
	REQUIRE(ToString(Permission::Read) == PermissionNames[0]);
	REQUIRE(ToString(Permission::Write) == PermissionNames[1]);
	REQUIRE(ToString(Permission::Execute) == PermissionNames[2]);
	REQUIRE(ToString(Permission::Read | Permission::Write) == "Read | Write");
	REQUIRE(ToString(Permission::Read | Permission::Execute) == "Read | Execute");

	std::ostringstream oss;
	oss << Permission::Execute;
	REQUIRE(oss.str() == "Execute");

	std::string formatted = std::format("{}", Permission::Read | Permission::Write);
	REQUIRE(ToString(Permission::Read | Permission::Write) == formatted);
}

TEST_CASE("ENUM_MASK_OPERATORS work as expected", "[Utility][Enum]")
{
	Permission p = Permission::Read | Permission::Write;
	REQUIRE((p & Permission::Read) == Permission::Read);
	REQUIRE((p & Permission::Execute) == Permission::None);
	p |= Permission::Execute;
	REQUIRE(p == Permission::All);
	p &= Permission::Write;
	REQUIRE(p == Permission::Write);
	p ^= Permission::Write;
	REQUIRE(p == Permission::None);
	p = (Permission::Read | Permission::Write) ^ Permission::Read;
	REQUIRE(p == Permission::Write);
	REQUIRE(~Permission::None == Permission::All);
}

TEST_CASE("ENUM_VALUE_MASK conversions work", "[Utility][Enum]")
{
	REQUIRE(ToMask(Color::Red) == Permission::Read);
	REQUIRE(ToMask(Color::Green) == Permission::Write);
	REQUIRE(ToMask(Color::Blue) == Permission::Execute);

	std::array colors = { Color::Red, Color::Blue };
	REQUIRE(ToMask(std::span(colors)) == (Permission::Read | Permission::Execute));

	auto mask = Permission::Read | Permission::Write;
	REQUIRE(IsInMask(Color::Red, mask));
	REQUIRE(IsInMask(Color::Green, mask));
	REQUIRE_FALSE(IsInMask(Color::Blue, mask));

	REQUIRE(ToValue(Permission::Write) == Color::Green);

	std::array<Color, 3> out{};
	auto count = ToValues(Permission::Read | Permission::Execute, std::span(out));
	REQUIRE(count == 2);
	REQUIRE(out[0] == Color::Red);
	REQUIRE(out[1] == Color::Blue);
}
