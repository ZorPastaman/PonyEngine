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

import PonyEngine.RawInput;

TEST_CASE("DeviceType static data", "[RawInput][DeviceType]")
{
	STATIC_REQUIRE(PonyEngine::RawInput::DeviceType::SubtypeSeparator == '/');
}

TEST_CASE("DeviceType constructor", "[RawInput][DeviceType]")
{
	const auto defaultDeviceType = PonyEngine::RawInput::DeviceType();
	REQUIRE(defaultDeviceType.Type() == "");
	REQUIRE(defaultDeviceType.BaseType() == "");

	constexpr std::string_view gamepad = "Gamepad";
	const auto simpleDeviceType = PonyEngine::RawInput::DeviceType(gamepad);
	REQUIRE(simpleDeviceType.Type() == gamepad);
	REQUIRE(simpleDeviceType.BaseType() == gamepad);

	const std::string bestGamepad = std::format("{}/Best", gamepad);
	const auto devicetype = PonyEngine::RawInput::DeviceType(bestGamepad);
	REQUIRE(devicetype.Type() == bestGamepad);
	REQUIRE(devicetype.BaseType() == gamepad);

	const std::string complexGamepad = std::format("{}//Best////Very", gamepad);
	const auto complexDeviceType = PonyEngine::RawInput::DeviceType(complexGamepad);
	REQUIRE(complexDeviceType.Type() == std::format("{}/Best/Very", gamepad));
	REQUIRE(complexDeviceType.BaseType() == gamepad);

	const PonyEngine::RawInput::DeviceType copy = devicetype;
	REQUIRE(copy == devicetype);

	const PonyEngine::RawInput::DeviceType moved = std::move(devicetype);
	REQUIRE(copy == moved);
}

TEST_CASE("DeviceType append", "[RawInput][DeviceType]")
{
	constexpr std::string_view gamepad = "Gamepad";
	constexpr std::string_view best = "Best";
	constexpr std::string_view very = "Very";
	constexpr std::string_view mine = "Mine";

	auto devicetype = PonyEngine::RawInput::DeviceType();
	devicetype /= gamepad;
	devicetype /= PonyEngine::RawInput::DeviceType(best);
	const auto finalDeviceType = devicetype / PonyEngine::RawInput::DeviceType(very) / mine;
	REQUIRE(finalDeviceType.Type() == std::format("{}/{}/{}/{}", gamepad, best, very, mine));
	REQUIRE(finalDeviceType.BaseType() == gamepad);
}

TEST_CASE("DeviceType equals", "[RawInput][DeviceType]")
{
	constexpr std::string_view gamepad = "Gamepad";
	constexpr std::string_view best = "Best";
	const auto devicetype = PonyEngine::RawInput::DeviceType(std::format("{}/{}", gamepad, best));
	REQUIRE(devicetype == PonyEngine::RawInput::DeviceType(std::format("{}/{}", gamepad, best)));
	REQUIRE(devicetype == std::format("{}/{}", gamepad, best));
}

