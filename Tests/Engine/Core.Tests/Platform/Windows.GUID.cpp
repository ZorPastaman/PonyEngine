/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Platform/Windows/COM.h"

#include <catch2/catch_test_macros.hpp>

import std;

import PonyEngine.Platform;

TEST_CASE("AcquireGuid returns unique GUIDs", "[Platform][Windows][GUID]")
{
	const GUID guid1 = PonyEngine::Platform::Windows::AcquireGuid();
	const GUID guid2 = PonyEngine::Platform::Windows::AcquireGuid();

	const auto isZero = [](const GUID& g)
	{
		return g.Data1 == 0 && g.Data2 == 0 && g.Data3 == 0 && std::ranges::all_of(g.Data4, [](auto b) { return b == 0; });
	};
	REQUIRE_FALSE(isZero(guid1));
	REQUIRE_FALSE(isZero(guid2));

	const bool areEqual = guid1.Data1 == guid2.Data1 && guid1.Data2 == guid2.Data2 && guid1.Data3 == guid2.Data3 &&
		std::equal(std::begin(guid1.Data4), std::end(guid1.Data4), std::begin(guid2.Data4));
	REQUIRE_FALSE(areEqual);
}

TEST_CASE("std::format supports GUID", "[Platform][Windows][GUID]")
{
	const GUID guid = PonyEngine::Platform::Windows::AcquireGuid();
	auto buffer = std::wstring(39, L'\0');
	StringFromGUID2(guid, buffer.data(), static_cast<int>(buffer.size()));
	const std::string expected = PonyEngine::Platform::Windows::ConvertToString(std::wstring_view(&buffer.front() + 1, &buffer.back() - 1));

	REQUIRE(std::format("{}", guid) == std::format("{{{}}}", expected));
	REQUIRE(std::format("{:n}", guid) == expected);
}
