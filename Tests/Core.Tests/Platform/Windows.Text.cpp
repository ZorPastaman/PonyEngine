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

import PonyEngine.Platform;

TEST_CASE("ConvertToString - Empty wstring", "[Platform][Windows][Text]")
{
	constexpr std::wstring_view input;
	const auto result = PonyEngine::Platform::Windows::ConvertToString(input);
	REQUIRE(result.empty());
}

TEST_CASE("ConvertToString - ASCII wstring", "[Platform][Windows][Text]")
{
	constexpr std::wstring_view input = L"Hello, world!";
	auto result = PonyEngine::Platform::Windows::ConvertToString(input);
	REQUIRE(result == "Hello, world!");
}

TEST_CASE("ConvertToString - Unicode wstring", "[Platform][Windows][Text]")
{
	constexpr std::wstring_view input = L"Привет, мир! 你好，世界！";
	const auto result = PonyEngine::Platform::Windows::ConvertToString(input);
	auto roundtrip = PonyEngine::Platform::Windows::ConvertToWideString(result);
	REQUIRE(roundtrip == input);
}

TEST_CASE("ConvertToWideString - Empty string", "[Platform][Windows][Text]")
{
	constexpr std::string_view input;
	const auto result = PonyEngine::Platform::Windows::ConvertToWideString(input);
	REQUIRE(result.empty());
}

TEST_CASE("ConvertToWideString - ASCII string", "[Platform][Windows][Text]")
{
	constexpr std::string_view input = "Hello, world!";
	auto result = PonyEngine::Platform::Windows::ConvertToWideString(input);
	REQUIRE(result == L"Hello, world!");
}

TEST_CASE("ConvertToWideString - Unicode string", "[Platform][Windows][Text]")
{
	std::wstring_view original = L"こんにちは世界";
	const auto utf8 = PonyEngine::Platform::Windows::ConvertToString(original);
	auto result = PonyEngine::Platform::Windows::ConvertToWideString(utf8);
	REQUIRE(result == original);
}
