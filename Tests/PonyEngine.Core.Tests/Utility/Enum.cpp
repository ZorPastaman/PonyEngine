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

	ENUM_VALUE_MASK(Color, Permission)
}

ENUM_VALUE_FORMATTER(Name, Color)
ENUM_MASK_FORMATTER(Name, Permission)

TEST_CASE("ENUM_VALUE_TO_STRING works for valid and invalid values", "[Utility][Enum]")
{
	REQUIRE(Name::ToString(Name::Color::Red) == Name::ColorNames[0]);
	REQUIRE(Name::ToString(Name::Color::Green) == Name::ColorNames[1]);
	REQUIRE(Name::ToString(Name::Color::Blue) == Name::ColorNames[2]);
	REQUIRE(Name::ToString(static_cast<Name::Color>(99)) == Name::ColorNames[3]);

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
	Name::Permission p = Name::Permission::Read | Name::Permission::Write;
	REQUIRE((p & Name::Permission::Read) == Name::Permission::Read);
	REQUIRE((p & Name::Permission::Execute) == Name::Permission::None);
	p |= Name::Permission::Execute;
	REQUIRE(p == Name::Permission::All);
	p &= Name::Permission::Write;
	REQUIRE(p == Name::Permission::Write);
	p ^= Name::Permission::Write;
	REQUIRE(p == Name::Permission::None);
	p = (Name::Permission::Read | Name::Permission::Write) ^ Name::Permission::Read;
	REQUIRE(p == Name::Permission::Write);
	REQUIRE(~Name::Permission::None == Name::Permission::All);
}

TEST_CASE("ENUM_VALUE_MASK conversions work", "[Utility][Enum]")
{
	REQUIRE(Name::ToMask(Name::Color::Red) == Name::Permission::Read);
	REQUIRE(Name::ToMask(Name::Color::Green) == Name::Permission::Write);
	REQUIRE(Name::ToMask(Name::Color::Blue) == Name::Permission::Execute);

	std::array colors = { Name::Color::Red, Name::Color::Blue };
	REQUIRE(ToMask(std::span(colors)) == (Name::Permission::Read | Name::Permission::Execute));

	auto mask = Name::Permission::Read | Name::Permission::Write;
	REQUIRE(IsInMask(Name::Color::Red, mask));
	REQUIRE(IsInMask(Name::Color::Green, mask));
	REQUIRE_FALSE(IsInMask(Name::Color::Blue, mask));

	REQUIRE(Name::ToValue(Name::Permission::Write) == Name::Color::Green);

	std::array<Name::Color, 3> out{};
	auto count = Name::ToValues(Name::Permission::Read | Name::Permission::Execute, std::span(out));
	REQUIRE(count == 2);
	REQUIRE(out[0] == Name::Color::Red);
	REQUIRE(out[1] == Name::Color::Blue);
}

TEST_CASE("EnumMacro constexpr compilation test", "[Utility][Enum]")
{
	auto testOperators = []() constexpr
	{
		Name::Permission pOp = ~(Name::Permission::All & (Name::Permission::Write | Name::Permission::Read) ^ Name::Permission::Execute);
		pOp &= Name::Permission::Write;
		pOp |= Name::Permission::Read;
		pOp ^= Name::Permission::Execute;

		return pOp;
	};
	auto toMask = []() constexpr
	{
		const auto vec = std::vector<Name::Color> { Name::Color::Blue, Name::Color::Red };
		return Name::ToMask(vec);
	};
	auto toValue = []() constexpr
	{
		auto arr = std::array<Name::Color, 3>();
		Name::ToValues(Name::Permission::Read | Name::Permission::Write, arr);
		return arr[0];
	};

	[[maybe_unused]] constexpr std::string_view valueStr = Name::ToString(Name::Color::Blue);
	[[maybe_unused]] constexpr Name::Permission pOp = testOperators();
	[[maybe_unused]] constexpr Name::Permission pV = Name::ToMask(Name::Color::Blue);
	[[maybe_unused]] constexpr Name::Permission pM = toMask();
	[[maybe_unused]] constexpr bool isInMask = Name::IsInMask(Name::Color::Blue, Name::Permission::Read);
	[[maybe_unused]] constexpr Name::Color cV = Name::ToValue(Name::Permission::Read);
	[[maybe_unused]] constexpr Name::Color cM = toValue();
}
