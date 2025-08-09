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

import PonyEngine.Math;
import PonyEngine.Type;

TEST_CASE("Color static", "[Math][Color]")
{
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red>::ChannelCount == 1uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green>::ChannelCount == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green, PonyEngine::Math::ColorChannel::Blue>::ChannelCount == 3uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green, PonyEngine::Math::ColorChannel::Blue, PonyEngine::Math::ColorChannel::Alpha>::ChannelCount == 4uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<float, PonyEngine::Math::ColorChannel::Red>::ChannelCount == 1uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<float, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green>::ChannelCount == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<float, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green, PonyEngine::Math::ColorChannel::Blue>::ChannelCount == 3uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<float, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green, PonyEngine::Math::ColorChannel::Blue, PonyEngine::Math::ColorChannel::Alpha>::ChannelCount == 4uz);

	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red>::RedIndex == 0uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red>::GreenIndex == std::nullopt);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red>::BlueIndex == std::nullopt);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red>::AlphaIndex == std::nullopt);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red>::HasRed);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red>::HasGreen);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red>::HasBlue);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red>::HasAlpha);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Alpha>::RedIndex == std::nullopt);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Alpha>::GreenIndex == std::nullopt);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Alpha>::BlueIndex == std::nullopt);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Alpha>::AlphaIndex == 0uz);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Alpha>::HasRed);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Alpha>::HasGreen);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Alpha>::HasBlue);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Alpha>::HasAlpha);

	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green>::ChannelCount == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green, PonyEngine::Math::ColorChannel::Blue>::ChannelCount == 3uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green, PonyEngine::Math::ColorChannel::Blue, PonyEngine::Math::ColorChannel::Alpha>::ChannelCount == 4uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<float, PonyEngine::Math::ColorChannel::Red>::ChannelCount == 1uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<float, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green>::ChannelCount == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<float, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green, PonyEngine::Math::ColorChannel::Blue>::ChannelCount == 3uz);
	STATIC_REQUIRE(PonyEngine::Math::Color<float, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green, PonyEngine::Math::ColorChannel::Blue, PonyEngine::Math::ColorChannel::Alpha>::ChannelCount == 4uz);
}

TEST_CASE("Color default constructor", "[Math][Color]")
{
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>() == PonyEngine::Math::ColorRGBA<float>(0.f, 0.f, 0.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRG<std::uint8_t>() == PonyEngine::Math::ColorRG<std::uint8_t>(0u, 0u));
	STATIC_REQUIRE(PonyEngine::Math::ColorR<std::int8_t>() == PonyEngine::Math::ColorR<std::int8_t>(0));
}

TEST_CASE("Color main constructor", "[Math][Color]")
{
	constexpr auto colorF = PonyEngine::Math::ColorRGB<float>(0.1f, 0.2f, 0.7f);
	STATIC_REQUIRE(colorF.R() == 0.1f);
	STATIC_REQUIRE(colorF.G() == 0.2f);
	STATIC_REQUIRE(colorF.B() == 0.7f);

	constexpr auto colorU = PonyEngine::Math::ColorRGBA<std::uint8_t>(10u, 20u, 70u, 255u);
	STATIC_REQUIRE(colorU.R() == 10u);
	STATIC_REQUIRE(colorU.G() == 20u);
	STATIC_REQUIRE(colorU.B() == 70u);
	STATIC_REQUIRE(colorU.A() == 255u);

	constexpr auto colorI = PonyEngine::Math::ColorA<std::int8_t>(-10);
	STATIC_REQUIRE(colorI.A() == -10);
}

TEST_CASE("Color span constructor", "[Math][Color]")
{
	constexpr auto colorF = PonyEngine::Math::ColorRGB<float>(std::array<float, 3>{ 0.1f, 0.2f, 0.7f });
	STATIC_REQUIRE(colorF.R() == 0.1f);
	STATIC_REQUIRE(colorF.G() == 0.2f);
	STATIC_REQUIRE(colorF.B() == 0.7f);

	constexpr auto colorU = PonyEngine::Math::ColorRGBA<std::uint8_t>(std::array<std::uint8_t, 4>{ 10u, 20u, 70u, 255u });
	STATIC_REQUIRE(colorU.R() == 10u);
	STATIC_REQUIRE(colorU.G() == 20u);
	STATIC_REQUIRE(colorU.B() == 70u);
	STATIC_REQUIRE(colorU.A() == 255u);

	constexpr auto colorI = PonyEngine::Math::ColorA<std::int8_t>(std::array<std::int8_t, 1>{ -10 });
	STATIC_REQUIRE(colorI.A() == -10);
}

TEST_CASE("Color vector constructor", "[Math][Color]")
{
	constexpr auto colorF = PonyEngine::Math::ColorRGB<float>(PonyEngine::Math::Vector3<float>(0.1f, 0.2f, 0.7f));
	STATIC_REQUIRE(colorF.R() == 0.1f);
	STATIC_REQUIRE(colorF.G() == 0.2f);
	STATIC_REQUIRE(colorF.B() == 0.7f);

	constexpr auto colorU = PonyEngine::Math::ColorRGBA<std::uint8_t>(PonyEngine::Math::Vector4<std::uint8_t>(10u, 20u, 70u, 255u));
	STATIC_REQUIRE(colorU.R() == 10u);
	STATIC_REQUIRE(colorU.G() == 20u);
	STATIC_REQUIRE(colorU.B() == 70u);
	STATIC_REQUIRE(colorU.A() == 255u);

	constexpr auto colorI = PonyEngine::Math::ColorA<std::int8_t>(PonyEngine::Math::Vector1<std::int8_t>(-10));
	STATIC_REQUIRE(colorI.A() == -10);
}

TEST_CASE("Color copy constructor", "[Math][Color]")
{
	constexpr auto colorF = PonyEngine::Math::ColorRGB<float>(0.1f, 0.2f, 0.7f);
	constexpr auto copyF = colorF;
	STATIC_REQUIRE(copyF.R() == 0.1f);
	STATIC_REQUIRE(copyF.G() == 0.2f);
	STATIC_REQUIRE(copyF.B() == 0.7f);

	constexpr auto colorU = PonyEngine::Math::ColorRGBA<std::uint8_t>(10u, 20u, 70u, 255u);
	constexpr auto copyU = colorU;
	STATIC_REQUIRE(copyU.R() == 10u);
	STATIC_REQUIRE(copyU.G() == 20u);
	STATIC_REQUIRE(copyU.B() == 70u);
	STATIC_REQUIRE(copyU.A() == 255u);

	constexpr auto colorI = PonyEngine::Math::ColorA<std::int8_t>(-10);
	constexpr auto copyI = colorI;
	STATIC_REQUIRE(copyI.A() == -10);
}

TEST_CASE("Color move constructor", "[Math][Color]")
{
	auto test = [](auto&& color) constexpr
	{
		auto copy = color;
		auto moved = std::move(copy);
		return moved;
	};

	constexpr auto colorF = PonyEngine::Math::ColorRGB<float>(0.1f, 0.2f, 0.7f);
	constexpr auto copyF = test(colorF);
	STATIC_REQUIRE(copyF.R() == 0.1f);
	STATIC_REQUIRE(copyF.G() == 0.2f);
	STATIC_REQUIRE(copyF.B() == 0.7f);

	constexpr auto colorU = PonyEngine::Math::ColorRGBA<std::uint8_t>(10u, 20u, 70u, 255u);
	constexpr auto copyU = test(colorU);
	STATIC_REQUIRE(copyU.R() == 10u);
	STATIC_REQUIRE(copyU.G() == 20u);
	STATIC_REQUIRE(copyU.B() == 70u);
	STATIC_REQUIRE(copyU.A() == 255u);

	constexpr auto colorI = PonyEngine::Math::ColorA<std::int8_t>(-10);
	constexpr auto copyI = test(colorI);
	STATIC_REQUIRE(copyI.A() == -10);
}

TEST_CASE("Color predefined", "[Math][Color]")
{
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::Red() == PonyEngine::Math::ColorRGBA<float>(1.f, 0.f, 0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint16_t>::Red() == PonyEngine::Math::ColorRGBA<std::uint16_t>(std::numeric_limits<std::uint16_t>::max(), 0, 0, std::numeric_limits<std::uint16_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::int16_t>::Red() == PonyEngine::Math::ColorRGBA<std::int16_t>(std::numeric_limits<std::int16_t>::max(), std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::Red() == PonyEngine::Math::ColorRGB<float>(1.f, 0.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::Red() == PonyEngine::Math::ColorRGB<std::uint16_t>(std::numeric_limits<std::uint16_t>::max(), 0, 0));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::int16_t>::Red() == PonyEngine::Math::ColorRGB<std::int16_t>(std::numeric_limits<std::int16_t>::max(), std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::min()));

	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::Green() == PonyEngine::Math::ColorRGBA<float>(0.f, 1.f, 0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Green() == PonyEngine::Math::ColorRGBA<std::uint8_t>(0, std::numeric_limits<std::uint8_t>::max(), 0, std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::int8_t>::Green() == PonyEngine::Math::ColorRGBA<std::int8_t>(std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::max(), std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRG<float>::Green() == PonyEngine::Math::ColorRG<float>(0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::Green() == PonyEngine::Math::ColorRGB<std::uint16_t>(0, std::numeric_limits<std::uint16_t>::max(), 0));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::int16_t>::Green() == PonyEngine::Math::ColorRGB<std::int16_t>(std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::max(), std::numeric_limits<std::int16_t>::min()));

	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::Blue() == PonyEngine::Math::ColorRGBA<float>(0.f, 0.f, 1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Blue() == PonyEngine::Math::ColorRGBA<std::uint8_t>(0, 0, std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::int8_t>::Blue() == PonyEngine::Math::ColorRGBA<std::int8_t>(std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::max(), std::numeric_limits<std::int8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::Blue() == PonyEngine::Math::ColorRGB<float>(0.f, 0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::Blue() == PonyEngine::Math::ColorRGB<std::uint16_t>(0, 0, std::numeric_limits<std::uint16_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::int16_t>::Blue() == PonyEngine::Math::ColorRGB<std::int16_t>(std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::max()));

	STATIC_REQUIRE(PonyEngine::Math::ColorA<float>::Black() == PonyEngine::Math::ColorA<float>(1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Black() == PonyEngine::Math::ColorRGBA<std::uint8_t>(0, 0, 0, std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::int8_t>::Black() == PonyEngine::Math::ColorRGBA<std::int8_t>(std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::Black() == PonyEngine::Math::ColorRGB<float>(0.f, 0.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::Black() == PonyEngine::Math::ColorRGB<std::uint16_t>(0, 0, 0));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::int16_t>::Black() == PonyEngine::Math::ColorRGB<std::int16_t>(std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::min()));

	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::White() == PonyEngine::Math::ColorRGBA<float>(1.f, 1.f, 1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::White() == PonyEngine::Math::ColorRGBA<std::uint8_t>(std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::int8_t>::White() == PonyEngine::Math::ColorRGBA<std::int8_t>(std::numeric_limits<std::int8_t>::max(), std::numeric_limits<std::int8_t>::max(), std::numeric_limits<std::int8_t>::max(), std::numeric_limits<std::int8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::White() == PonyEngine::Math::ColorRGB<float>(1.f, 1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::White() == PonyEngine::Math::ColorRGB<std::uint16_t>(std::numeric_limits<std::uint16_t>::max(), std::numeric_limits<std::uint16_t>::max(), std::numeric_limits<std::uint16_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::int16_t>::White() == PonyEngine::Math::ColorRGB<std::int16_t>(std::numeric_limits<std::int16_t>::max(), std::numeric_limits<std::int16_t>::max(), std::numeric_limits<std::int16_t>::max()));

	STATIC_REQUIRE(PonyEngine::Math::ColorA<float>::Clear() == PonyEngine::Math::ColorA<float>(0.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Clear() == PonyEngine::Math::ColorRGBA<std::uint8_t>(0, 0, 0, 0));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::int8_t>::Clear() == PonyEngine::Math::ColorRGBA<std::int8_t>(std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::min()));

	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::Gray() == PonyEngine::Math::ColorRGBA<float>(0.5f, 0.5f, 0.5f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Gray() == PonyEngine::Math::ColorRGBA<std::uint8_t>(std::numeric_limits<std::uint8_t>::max() / 2, std::numeric_limits<std::uint8_t>::max() / 2, std::numeric_limits<std::uint8_t>::max() / 2, std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::int8_t>::Gray() == PonyEngine::Math::ColorRGBA<std::int8_t>(0, 0, 0, std::numeric_limits<std::int8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::Gray() == PonyEngine::Math::ColorRGB<float>(0.5f, 0.5f, 0.5f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::Gray() == PonyEngine::Math::ColorRGB<std::uint16_t>(std::numeric_limits<std::uint16_t>::max() / 2, std::numeric_limits<std::uint16_t>::max() / 2, std::numeric_limits<std::uint16_t>::max() / 2));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::int16_t>::Gray() == PonyEngine::Math::ColorRGB<std::int16_t>(0, 0, 0));

	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::Yellow() == PonyEngine::Math::ColorRGBA<float>(1.f, 1.f, 0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Yellow() == PonyEngine::Math::ColorRGBA<std::uint8_t>(std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max(), 0, std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::int8_t>::Yellow() == PonyEngine::Math::ColorRGBA<std::int8_t>(std::numeric_limits<std::int8_t>::max(), std::numeric_limits<std::int8_t>::max(), std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRG<float>::Yellow() == PonyEngine::Math::ColorRG<float>(1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::Yellow() == PonyEngine::Math::ColorRGB<std::uint16_t>(std::numeric_limits<std::uint16_t>::max(), std::numeric_limits<std::uint16_t>::max(), 0));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::int16_t>::Yellow() == PonyEngine::Math::ColorRGB<std::int16_t>(std::numeric_limits<std::int16_t>::max(), std::numeric_limits<std::int16_t>::max(), std::numeric_limits<std::int16_t>::min()));

	STATIC_REQUIRE(PonyEngine::Math::ColorRBA<float>::Magenta() == PonyEngine::Math::ColorRBA<float>(1.f, 1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Magenta() == PonyEngine::Math::ColorRGBA<std::uint8_t>(std::numeric_limits<std::uint8_t>::max(), 0, std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::int8_t>::Magenta() == PonyEngine::Math::ColorRGBA<std::int8_t>(std::numeric_limits<std::int8_t>::max(), std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::max(), std::numeric_limits<std::int8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::Magenta() == PonyEngine::Math::ColorRGB<float>(1.f, 0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRB<std::uint16_t>::Magenta() == PonyEngine::Math::ColorRB<std::uint16_t>(std::numeric_limits<std::uint16_t>::max(), std::numeric_limits<std::uint16_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::int16_t>::Magenta() == PonyEngine::Math::ColorRGB<std::int16_t>(std::numeric_limits<std::int16_t>::max(), std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::max()));

	STATIC_REQUIRE(PonyEngine::Math::ColorGBA<float>::Cyan() == PonyEngine::Math::ColorGBA<float>(1.f, 1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Cyan() == PonyEngine::Math::ColorRGBA<std::uint8_t>(0, std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::int8_t>::Cyan() == PonyEngine::Math::ColorRGBA<std::int8_t>(std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::max(), std::numeric_limits<std::int8_t>::max(), std::numeric_limits<std::int8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::Cyan() == PonyEngine::Math::ColorRGB<float>(0.f, 1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorGB<std::uint16_t>::Cyan() == PonyEngine::Math::ColorGB<std::uint16_t>(std::numeric_limits<std::uint16_t>::max(), std::numeric_limits<std::uint16_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::int16_t>::Cyan() == PonyEngine::Math::ColorRGB<std::int16_t>(std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::max(), std::numeric_limits<std::int16_t>::max()));
}

TEST_CASE("Color access", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> color) constexpr
	{
		auto copy = color;
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasRed)
		{
			copy.R() -= 1;
		}
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasGreen)
		{
			copy.G() += 1;
		}
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasBlue)
		{
			copy.B() *= 2;
		}
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasAlpha)
		{
			copy.A() /= 2;
		}
		return copy;
	};

	constexpr auto colorF = PonyEngine::Math::ColorGBA<float>(0.1f, 0.2f, 0.7f);
	STATIC_REQUIRE(colorF.G() == 0.1f);
	STATIC_REQUIRE(colorF.B() == 0.2f);
	STATIC_REQUIRE(colorF.A() == 0.7f);
	constexpr auto copyF = test(colorF);
	STATIC_REQUIRE(copyF.G() == 0.1f + 1);
	STATIC_REQUIRE(copyF.B() == 0.2f * 2);
	STATIC_REQUIRE(copyF.A() == 0.7f / 2);

	constexpr auto colorU = PonyEngine::Math::ColorRGBA<std::uint8_t>(10u, 20u, 70u, 255u);
	STATIC_REQUIRE(colorU.R() == 10u);
	STATIC_REQUIRE(colorU.G() == 20u);
	STATIC_REQUIRE(colorU.B() == 70u);
	STATIC_REQUIRE(colorU.A() == 255u);
	constexpr auto copyU = test(colorU);
	STATIC_REQUIRE(copyU.R() == 10u - 1);
	STATIC_REQUIRE(copyU.G() == 20u + 1);
	STATIC_REQUIRE(copyU.B() == 70u * 2);
	STATIC_REQUIRE(copyU.A() == 255u / 2);

	constexpr auto colorI = PonyEngine::Math::ColorA<std::int8_t>(-10);
	STATIC_REQUIRE(colorI.A() == -10);
	constexpr auto copyI = test(colorI);
	STATIC_REQUIRE(copyI.A() == -10 / 2);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return colorU.R() | colorU.G() | colorU.B() | colorU.A();
	};
#endif
}

TEST_CASE("Color access span", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> color) constexpr
	{
		auto copy = color;
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasRed)
		{
			copy.Span()[PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::RedIndex.value()] -= 1;
		}
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasGreen)
		{
			copy.Span()[PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::GreenIndex.value()] += 1;
		}
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasBlue)
		{
			copy.Span()[PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::BlueIndex.value()] *= 2;
		}
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasAlpha)
		{
			copy.Span()[PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::AlphaIndex.value()] /= 2;
		}
		return copy;
	};

	constexpr auto colorF = PonyEngine::Math::ColorGBA<float>(0.1f, 0.2f, 0.7f);
	STATIC_REQUIRE(colorF.Span()[colorF.GreenIndex.value()] == 0.1f);
	STATIC_REQUIRE(colorF.Span()[colorF.BlueIndex.value()] == 0.2f);
	STATIC_REQUIRE(colorF.Span()[colorF.AlphaIndex.value()] == 0.7f);
	constexpr auto copyF = test(colorF);
	STATIC_REQUIRE(copyF.Span()[colorF.GreenIndex.value()] == 0.1f + 1);
	STATIC_REQUIRE(copyF.Span()[colorF.BlueIndex.value()] == 0.2f * 2);
	STATIC_REQUIRE(copyF.Span()[colorF.AlphaIndex.value()] == 0.7f / 2);

	constexpr auto colorU = PonyEngine::Math::ColorRGBA<std::uint8_t>(10u, 20u, 70u, 255u);
	STATIC_REQUIRE(colorU.Span()[colorU.RedIndex.value()] == 10u);
	STATIC_REQUIRE(colorU.Span()[colorU.GreenIndex.value()] == 20u);
	STATIC_REQUIRE(colorU.Span()[colorU.BlueIndex.value()] == 70u);
	STATIC_REQUIRE(colorU.Span()[colorU.AlphaIndex.value()] == 255u);
	constexpr auto copyU = test(colorU);
	STATIC_REQUIRE(copyU.Span()[colorU.RedIndex.value()] == 10u - 1);
	STATIC_REQUIRE(copyU.Span()[colorU.GreenIndex.value()] == 20u + 1);
	STATIC_REQUIRE(copyU.Span()[colorU.BlueIndex.value()] == 70u * 2);
	STATIC_REQUIRE(copyU.Span()[colorU.AlphaIndex.value()] == 255u / 2);

	constexpr auto colorI = PonyEngine::Math::ColorA<std::int8_t>(-10);
	STATIC_REQUIRE(colorI.Span()[colorI.AlphaIndex.value()] == -10);
	constexpr auto copyI = test(colorI);
	STATIC_REQUIRE(copyI.Span()[colorI.AlphaIndex.value()] == -10 / 2);
}
