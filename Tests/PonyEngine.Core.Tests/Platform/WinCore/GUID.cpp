/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <algorithm>
#include <ostream>
#include <string>
#include <format>

#include "PonyEngine/Platform/WinCore/Framework.h"

#include <catch2/catch_test_macros.hpp>

import PonyEngine.Platform.WinCore;

TEST_CASE("AcquireGuid returns unique GUIDs", "[Platform][GUID]")
{
	const GUID guid1 = PonyEngine::Platform::WinCore::AcquireGuid();
	const GUID guid2 = PonyEngine::Platform::WinCore::AcquireGuid();

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

TEST_CASE("ToString produces a valid GUID string", "[Platform][GUID]")
{
	const GUID guid = PonyEngine::Platform::WinCore::AcquireGuid();
	const std::string guidStr = PonyEngine::Platform::WinCore::ToString(guid);

	auto buffer = std::wstring(39, L'\0');
	StringFromGUID2(guid, buffer.data(), static_cast<int>(buffer.size()));
	REQUIRE(std::wstring_view(&buffer.front() + 1, &buffer.back() - 1) == std::wstring(guidStr.cbegin(), guidStr.cend()));
}

TEST_CASE("operator << outputs GUID as string", "[Platform][GUID]") {
	const GUID guid = PonyEngine::Platform::WinCore::AcquireGuid();
	std::ostringstream oss;
	oss << guid;
	const std::string guidStr = oss.str();

	REQUIRE(guidStr == PonyEngine::Platform::WinCore::ToString(guid));
}

TEST_CASE("std::format supports GUID", "[Platform][GUID]") {
	const GUID guid = PonyEngine::Platform::WinCore::AcquireGuid();
	const std::string formatted = std::format("{}", guid);

	REQUIRE(formatted == PonyEngine::Platform::WinCore::ToString(guid));
}
