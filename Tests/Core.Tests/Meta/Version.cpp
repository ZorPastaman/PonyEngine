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

import PonyEngine.Meta;

TEST_CASE("Version: Default constructor", "[Meta][Version]")
{
	constexpr auto version = PonyEngine::Meta::Version();

	STATIC_REQUIRE(version.Major() == 0u);
	STATIC_REQUIRE(version.Minor() == 0u);
	STATIC_REQUIRE(version.Patch() == 0u);
	STATIC_REQUIRE(version.Tweak() == 0u);
}

TEST_CASE("Version: Single parameter constructor", "[Meta][Version]")
{
	constexpr auto version = PonyEngine::Meta::Version(5u);

	STATIC_REQUIRE(version.Major() == 5u);
	STATIC_REQUIRE(version.Minor() == 0u);
	STATIC_REQUIRE(version.Patch() == 0u);
	STATIC_REQUIRE(version.Tweak() == 0u);
}

TEST_CASE("Version: Two parameter constructor", "[Meta][Version]")
{
	constexpr auto version = PonyEngine::Meta::Version(2u, 3u);

	STATIC_REQUIRE(version.Major() == 2u);
	STATIC_REQUIRE(version.Minor() == 3u);
	STATIC_REQUIRE(version.Patch() == 0u);
	STATIC_REQUIRE(version.Tweak() == 0u);
}

TEST_CASE("Version: Three parameter constructor", "[Meta][Version]")
{
	constexpr auto version = PonyEngine::Meta::Version(1u, 5u, 7u);

	STATIC_REQUIRE(version.Major() == 1u);
	STATIC_REQUIRE(version.Minor() == 5u);
	STATIC_REQUIRE(version.Patch() == 7u);
	STATIC_REQUIRE(version.Tweak() == 0u);
}

TEST_CASE("Version: Four parameter constructor", "[Meta][Version]")
{
	constexpr auto version = PonyEngine::Meta::Version(3u, 2u, 1u, 4u);

	STATIC_REQUIRE(version.Major() == 3u);
	STATIC_REQUIRE(version.Minor() == 2u);
	STATIC_REQUIRE(version.Patch() == 1u);
	STATIC_REQUIRE(version.Tweak() == 4u);
}

TEST_CASE("Version: Copy constructor", "[Meta][Version]")
{
	constexpr auto original = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
	constexpr PonyEngine::Meta::Version copy = original;

	STATIC_REQUIRE(copy.Major() == original.Major());
	STATIC_REQUIRE(copy.Minor() == original.Minor());
	STATIC_REQUIRE(copy.Patch() == original.Patch());
	STATIC_REQUIRE(copy.Tweak() == original.Tweak());
}

TEST_CASE("Version: Move constructor", "[Meta][Version]")
{
	auto original = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
	const auto moved = std::move(original);

	REQUIRE(moved.Major() == 1u);
	REQUIRE(moved.Minor() == 2u);
	REQUIRE(moved.Patch() == 3u);
	REQUIRE(moved.Tweak() == 4u);
}

TEST_CASE("Version: Copy assignment", "[Meta][Version]")
{
	auto version1 = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
	PonyEngine::Meta::Version version2;
	version2 = version1;

	REQUIRE(version2.Major() == 1u);
	REQUIRE(version2.Minor() == 2u);
	REQUIRE(version2.Patch() == 3u);
	REQUIRE(version2.Tweak() == 4u);
}

TEST_CASE("Version: Move assignment", "[Meta][Version]")
{
	auto version1 = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
	PonyEngine::Meta::Version version2;
	version2 = std::move(version1);

	REQUIRE(version2.Major() == 1u);
	REQUIRE(version2.Minor() == 2u);
	REQUIRE(version2.Patch() == 3u);
	REQUIRE(version2.Tweak() == 4u);
}

TEST_CASE("Version: Major accessor", "[Meta][Version]")
{
	SECTION("Const access")
	{
		constexpr auto version = PonyEngine::Meta::Version(5u, 0u, 0u, 0u);
		STATIC_REQUIRE(version.Major() == 5u);
	}

	SECTION("Mutable access")
	{
		auto version = PonyEngine::Meta::Version();
		version.Major() = 10u;
		REQUIRE(version.Major() == 10u);
	}
}

TEST_CASE("Version: Minor accessor", "[Meta][Version]")
{
	SECTION("Const access")
	{
		constexpr auto version = PonyEngine::Meta::Version(0u, 7u, 0u, 0u);
		STATIC_REQUIRE(version.Minor() == 7u);
	}

	SECTION("Mutable access")
	{
		auto version = PonyEngine::Meta::Version();
		version.Minor() = 15u;
		REQUIRE(version.Minor() == 15u);
	}
}

TEST_CASE("Version: Patch accessor", "[Meta][Version]")
{
	SECTION("Const access")
	{
		constexpr auto version = PonyEngine::Meta::Version(0u, 0u, 3u, 0u);
		STATIC_REQUIRE(version.Patch() == 3u);
	}

	SECTION("Mutable access")
	{
		auto version = PonyEngine::Meta::Version();
		version.Patch() = 20u;
		REQUIRE(version.Patch() == 20u);
	}
}

TEST_CASE("Version: Tweak accessor", "[Meta][Version]")
{
	SECTION("Const access")
	{
		constexpr auto version = PonyEngine::Meta::Version(0u, 0u, 0u, 9u);
		STATIC_REQUIRE(version.Tweak() == 9u);
	}

	SECTION("Mutable access")
	{
		auto version = PonyEngine::Meta::Version();
		version.Tweak() = 25u;
		REQUIRE(version.Tweak() == 25u);
	}
}

TEST_CASE("Version: Data accessor", "[Meta][Version]")
{
	SECTION("Const access")
	{
		constexpr auto version = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
		const auto* data = version.Data();

		REQUIRE(data[0] == 1u);
		REQUIRE(data[1] == 2u);
		REQUIRE(data[2] == 3u);
		REQUIRE(data[3] == 4u);
	}

	SECTION("Mutable access")
	{
		auto version = PonyEngine::Meta::Version();
		auto* data = version.Data();
		data[0] = 5u;
		data[1] = 6u;
		data[2] = 7u;
		data[3] = 8u;

		REQUIRE(version.Major() == 5u);
		REQUIRE(version.Minor() == 6u);
		REQUIRE(version.Patch() == 7u);
		REQUIRE(version.Tweak() == 8u);
	}
}

TEST_CASE("Version: Subscript operator", "[Meta][Version]")
{
	SECTION("Const access")
	{
		constexpr auto version = PonyEngine::Meta::Version(10u, 20u, 30u, 40u);

		STATIC_REQUIRE(version[0] == 10u);
		STATIC_REQUIRE(version[1] == 20u);
		STATIC_REQUIRE(version[2] == 30u);
		STATIC_REQUIRE(version[3] == 40u);
	}

	SECTION("Mutable access")
	{
		auto version = PonyEngine::Meta::Version();
		version[0] = 11u;
		version[1] = 22u;
		version[2] = 33u;
		version[3] = 44u;

		REQUIRE(version[0] == 11u);
		REQUIRE(version[1] == 22u);
		REQUIRE(version[2] == 33u);
		REQUIRE(version[3] == 44u);
	}
}

TEST_CASE("Version: Comparison operators", "[Meta][Version]")
{
	SECTION("Equality")
	{
		constexpr auto v1 = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
		constexpr auto v2 = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
		constexpr auto v3 = PonyEngine::Meta::Version(1u, 2u, 3u, 5u);

		STATIC_REQUIRE(v1 == v2);
		STATIC_REQUIRE_FALSE(v1 == v3);
	}

	SECTION("Inequality")
	{
		constexpr auto v1 = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
		constexpr auto v2 = PonyEngine::Meta::Version(1u, 2u, 3u, 5u);

		STATIC_REQUIRE(v1 != v2);
		STATIC_REQUIRE_FALSE(v1 != v1);
	}

	SECTION("Less than")
	{
		constexpr auto v1 = PonyEngine::Meta::Version(1u, 0u, 0u, 0u);
		constexpr auto v2 = PonyEngine::Meta::Version(2u, 0u, 0u, 0u);
		constexpr auto v3 = PonyEngine::Meta::Version(1u, 1u, 0u, 0u);

		STATIC_REQUIRE(v1 < v2);
		STATIC_REQUIRE(v1 < v3);
		STATIC_REQUIRE_FALSE(v2 < v1);
	}

	SECTION("Less than or equal")
	{
		constexpr auto v1 = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
		constexpr auto v2 = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
		constexpr auto v3 = PonyEngine::Meta::Version(1u, 2u, 3u, 5u);

		STATIC_REQUIRE(v1 <= v2);
		STATIC_REQUIRE(v1 <= v3);
		STATIC_REQUIRE_FALSE(v3 <= v1);
	}

	SECTION("Greater than")
	{
		constexpr auto v1 = PonyEngine::Meta::Version(2u, 0u, 0u, 0u);
		constexpr auto v2 = PonyEngine::Meta::Version(1u, 0u, 0u, 0u);
		constexpr auto v3 = PonyEngine::Meta::Version(2u, 1u, 0u, 0u);

		STATIC_REQUIRE(v1 > v2);
		STATIC_REQUIRE(v3 > v2);
		STATIC_REQUIRE_FALSE(v2 > v1);
	}

	SECTION("Greater than or equal")
	{
		constexpr auto v1 = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
		constexpr auto v2 = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
		constexpr auto v3 = PonyEngine::Meta::Version(1u, 2u, 3u, 5u);

		STATIC_REQUIRE(v1 >= v2);
		STATIC_REQUIRE(v3 >= v1);
		STATIC_REQUIRE_FALSE(v1 >= v3);
	}

	SECTION("Spaceship operator")
	{
		constexpr auto v1 = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
		constexpr auto v2 = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
		constexpr auto v3 = PonyEngine::Meta::Version(1u, 2u, 3u, 5u);

		STATIC_REQUIRE((v1 <=> v2) == std::strong_ordering::equal);
		STATIC_REQUIRE((v1 <=> v3) == std::strong_ordering::less);
		STATIC_REQUIRE((v3 <=> v1) == std::strong_ordering::greater);
	}
}

TEST_CASE("Version: Version number count constant", "[Meta][Version]")
{
	STATIC_REQUIRE(PonyEngine::Meta::Version::VersionNumberCount == 4uz);
}

TEST_CASE("Version: Format - Default (3 numbers)", "[Meta][Version]")
{
	constexpr auto version = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
	const auto formatted = std::format("{}", version);

	REQUIRE(formatted == "1.2.3");
}

TEST_CASE("Version: Format - With :n1", "[Meta][Version]")
{
	constexpr auto version = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
	const auto formatted = std::format("{:n1}", version);

	REQUIRE(formatted == "1");
}

TEST_CASE("Version: Format - With :n2", "[Meta][Version]")
{
	constexpr auto version = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
	const auto formatted = std::format("{:n2}", version);

	REQUIRE(formatted == "1.2");
}

TEST_CASE("Version: Format - With :n3", "[Meta][Version]")
{
	constexpr auto version = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
	const auto formatted = std::format("{:n3}", version);

	REQUIRE(formatted == "1.2.3");
}

TEST_CASE("Version: Format - With :n4", "[Meta][Version]")
{
	constexpr auto version = PonyEngine::Meta::Version(1u, 2u, 3u, 4u);
	const auto formatted = std::format("{:n4}", version);

	REQUIRE(formatted == "1.2.3.4");
}
