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

	STATIC_REQUIRE(PonyEngine::Math::Color<float, PonyEngine::Math::ColorChannel::Red>::GammaValue == 2.4);
}

TEST_CASE("Color default constructor", "[Math][Color]")
{
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>() == PonyEngine::Math::ColorRGBA<float>(0.f, 0.f, 0.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRG<std::uint8_t>() == PonyEngine::Math::ColorRG<std::uint8_t>(0u, 0u));
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
}

TEST_CASE("Color predefined", "[Math][Color]")
{
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::Red() == PonyEngine::Math::ColorRGBA<float>(1.f, 0.f, 0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint16_t>::Red() == PonyEngine::Math::ColorRGBA<std::uint16_t>(std::numeric_limits<std::uint16_t>::max(), 0, 0, std::numeric_limits<std::uint16_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::Red() == PonyEngine::Math::ColorRGB<float>(1.f, 0.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::Red() == PonyEngine::Math::ColorRGB<std::uint16_t>(std::numeric_limits<std::uint16_t>::max(), 0, 0));

	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::Green() == PonyEngine::Math::ColorRGBA<float>(0.f, 1.f, 0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Green() == PonyEngine::Math::ColorRGBA<std::uint8_t>(0, std::numeric_limits<std::uint8_t>::max(), 0, std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRG<float>::Green() == PonyEngine::Math::ColorRG<float>(0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::Green() == PonyEngine::Math::ColorRGB<std::uint16_t>(0, std::numeric_limits<std::uint16_t>::max(), 0));

	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::Blue() == PonyEngine::Math::ColorRGBA<float>(0.f, 0.f, 1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Blue() == PonyEngine::Math::ColorRGBA<std::uint8_t>(0, 0, std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::Blue() == PonyEngine::Math::ColorRGB<float>(0.f, 0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::Blue() == PonyEngine::Math::ColorRGB<std::uint16_t>(0, 0, std::numeric_limits<std::uint16_t>::max()));

	STATIC_REQUIRE(PonyEngine::Math::ColorA<float>::Black() == PonyEngine::Math::ColorA<float>(1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Black() == PonyEngine::Math::ColorRGBA<std::uint8_t>(0, 0, 0, std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::Black() == PonyEngine::Math::ColorRGB<float>(0.f, 0.f, 0.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::Black() == PonyEngine::Math::ColorRGB<std::uint16_t>(0, 0, 0));

	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::White() == PonyEngine::Math::ColorRGBA<float>(1.f, 1.f, 1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::White() == PonyEngine::Math::ColorRGBA<std::uint8_t>(std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::White() == PonyEngine::Math::ColorRGB<float>(1.f, 1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::White() == PonyEngine::Math::ColorRGB<std::uint16_t>(std::numeric_limits<std::uint16_t>::max(), std::numeric_limits<std::uint16_t>::max(), std::numeric_limits<std::uint16_t>::max()));

	STATIC_REQUIRE(PonyEngine::Math::ColorA<float>::Clear() == PonyEngine::Math::ColorA<float>(0.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Clear() == PonyEngine::Math::ColorRGBA<std::uint8_t>(0, 0, 0, 0));

	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::Gray() == PonyEngine::Math::ColorRGBA<float>(0.5f, 0.5f, 0.5f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Gray() == PonyEngine::Math::ColorRGBA<std::uint8_t>(std::numeric_limits<std::uint8_t>::max() / 2, std::numeric_limits<std::uint8_t>::max() / 2, std::numeric_limits<std::uint8_t>::max() / 2, std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::Gray() == PonyEngine::Math::ColorRGB<float>(0.5f, 0.5f, 0.5f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::Gray() == PonyEngine::Math::ColorRGB<std::uint16_t>(std::numeric_limits<std::uint16_t>::max() / 2, std::numeric_limits<std::uint16_t>::max() / 2, std::numeric_limits<std::uint16_t>::max() / 2));

	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::Yellow() == PonyEngine::Math::ColorRGBA<float>(1.f, 1.f, 0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Yellow() == PonyEngine::Math::ColorRGBA<std::uint8_t>(std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max(), 0, std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRG<float>::Yellow() == PonyEngine::Math::ColorRG<float>(1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint16_t>::Yellow() == PonyEngine::Math::ColorRGB<std::uint16_t>(std::numeric_limits<std::uint16_t>::max(), std::numeric_limits<std::uint16_t>::max(), 0));

	STATIC_REQUIRE(PonyEngine::Math::ColorRBA<float>::Magenta() == PonyEngine::Math::ColorRBA<float>(1.f, 1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Magenta() == PonyEngine::Math::ColorRGBA<std::uint8_t>(std::numeric_limits<std::uint8_t>::max(), 0, std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::Magenta() == PonyEngine::Math::ColorRGB<float>(1.f, 0.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRB<std::uint16_t>::Magenta() == PonyEngine::Math::ColorRB<std::uint16_t>(std::numeric_limits<std::uint16_t>::max(), std::numeric_limits<std::uint16_t>::max()));

	STATIC_REQUIRE(PonyEngine::Math::ColorGBA<float>::Cyan() == PonyEngine::Math::ColorGBA<float>(1.f, 1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint8_t>::Cyan() == PonyEngine::Math::ColorRGBA<std::uint8_t>(0, std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>::Cyan() == PonyEngine::Math::ColorRGB<float>(0.f, 1.f, 1.f));
	STATIC_REQUIRE(PonyEngine::Math::ColorGB<std::uint16_t>::Cyan() == PonyEngine::Math::ColorGB<std::uint16_t>(std::numeric_limits<std::uint16_t>::max(), std::numeric_limits<std::uint16_t>::max()));
}

TEST_CASE("Color access", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) constexpr
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

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return colorU.R() | colorU.G() | colorU.B() | colorU.A();
	};
#endif
}

TEST_CASE("Color access span", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) constexpr
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
}

TEST_CASE("Color access vector", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) constexpr
	{
		auto copy = color;
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasRed)
		{
			copy.Vector()[PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::RedIndex.value()] -= 1;
		}
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasGreen)
		{
			copy.Vector()[PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::GreenIndex.value()] += 1;
		}
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasBlue)
		{
			copy.Vector()[PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::BlueIndex.value()] *= 2;
		}
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasAlpha)
		{
			copy.Vector()[PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::AlphaIndex.value()] /= 2;
		}
		return copy;
	};

	constexpr auto colorF = PonyEngine::Math::ColorGBA<float>(0.1f, 0.2f, 0.7f);
	STATIC_REQUIRE(colorF.Vector()[colorF.GreenIndex.value()] == 0.1f);
	STATIC_REQUIRE(colorF.Vector()[colorF.BlueIndex.value()] == 0.2f);
	STATIC_REQUIRE(colorF.Vector()[colorF.AlphaIndex.value()] == 0.7f);
	constexpr auto copyF = test(colorF);
	STATIC_REQUIRE(copyF.Vector()[colorF.GreenIndex.value()] == 0.1f + 1);
	STATIC_REQUIRE(copyF.Vector()[colorF.BlueIndex.value()] == 0.2f * 2);
	STATIC_REQUIRE(copyF.Vector()[colorF.AlphaIndex.value()] == 0.7f / 2);

	constexpr auto colorU = PonyEngine::Math::ColorRGBA<std::uint8_t>(10u, 20u, 70u, 255u);
	STATIC_REQUIRE(colorU.Vector()[colorU.RedIndex.value()] == 10u);
	STATIC_REQUIRE(colorU.Vector()[colorU.GreenIndex.value()] == 20u);
	STATIC_REQUIRE(colorU.Vector()[colorU.BlueIndex.value()] == 70u);
	STATIC_REQUIRE(colorU.Vector()[colorU.AlphaIndex.value()] == 255u);
	constexpr auto copyU = test(colorU);
	STATIC_REQUIRE(copyU.Vector()[colorU.RedIndex.value()] == 10u - 1);
	STATIC_REQUIRE(copyU.Vector()[colorU.GreenIndex.value()] == 20u + 1);
	STATIC_REQUIRE(copyU.Vector()[colorU.BlueIndex.value()] == 70u * 2);
	STATIC_REQUIRE(copyU.Vector()[colorU.AlphaIndex.value()] == 255u / 2);
}

TEST_CASE("Color grayscale", "[Math][Color]")
{
	constexpr float r = 0.85f;
	constexpr float g = 0.16f;
	constexpr float b = 0.98f;
	constexpr auto color = PonyEngine::Math::ColorRGB<float>(r, g, b);
	constexpr float expectedGrayscale = 0.2126f * r + 0.7152f * g + 0.0722f * b;
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(expectedGrayscale, color.Grayscale()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ColorRGBA<float>(0.5f, 0.1f, 0.6f, 1.f).Grayscale();
	};
#endif
}

TEST_CASE("Color min this", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) constexpr
	{
		auto copy = color;
		return copy.Min();
	};

	constexpr float r = 0.85f;
	constexpr float g = 0.16f;
	constexpr float b = 0.98f;
	constexpr float a = 0.76f;
	constexpr auto color = PonyEngine::Math::ColorRGBA<float>(r, g, b, a);
	STATIC_REQUIRE(color.Min() == color.Vector().Min());
	STATIC_REQUIRE(test(color) == color.Min());
}

TEST_CASE("Color max this", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) constexpr
	{
		auto copy = color;
		return copy.Max();
	};

	constexpr float r = 0.85f;
	constexpr float g = 0.16f;
	constexpr float b = 0.98f;
	constexpr float a = 0.76f;
	constexpr auto color = PonyEngine::Math::ColorRGBA<float>(r, g, b, a);
	STATIC_REQUIRE(color.Max() == color.Vector().Max());
	STATIC_REQUIRE(test(color) == color.Max());
}

TEST_CASE("Color minmax", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) constexpr
	{
		auto copy = color;
		const std::pair<float, float> p = copy.MinMax();
		return p;
	};

	constexpr float r = 0.85f;
	constexpr float g = 0.16f;
	constexpr float b = 0.98f;
	constexpr float a = 0.76f;
	constexpr auto color = PonyEngine::Math::ColorRGBA<float>(r, g, b, a);
	STATIC_REQUIRE(color.MinMax() == color.Vector().MinMax());
	STATIC_REQUIRE(test(color) == color.MinMax());
}

TEST_CASE("Color gamma", "[Math][Color]")
{
	constexpr float r = 0.49f;
	constexpr float g = 0.69f;
	constexpr float b = 0.002f;
	constexpr float a = 0.166f;
	constexpr auto color = PonyEngine::Math::ColorRGBA<float>(r, g, b, a);
	const auto gamma = color.Gamma();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ColorRGBA<float>(0.729f, 0.849f, 0.026f, a), gamma, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ColorRGBA<float>(0.729f, 0.849f, 0.002f, 0.6f).Gamma();
	};
#endif
}

TEST_CASE("Color linear", "[Math][Color]")
{
	constexpr float r = 0.708f;
	constexpr float g = 0.836f;
	constexpr float b = 0.026f;
	constexpr float a = 0.166f;
	constexpr auto color = PonyEngine::Math::ColorRGBA<float>(r, g, b, a);
	const auto gamma = color.Linear();
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ColorRGBA<float>(0.459f, 0.667f, 0.002f, a), gamma, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ColorRGBA<float>(0.708f, 0.836f, 0.026f, 0.166f).Linear();
	};
#endif
}

TEST_CASE("Color isBlack, isWhite, isTransparent, isOpaque", "[Math][Color]")
{
	STATIC_REQUIRE(PonyEngine::Math::ColorRB<std::uint32_t>::Black().IsBlack());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::ColorRGB<float>(0.000001f, 0.0000001f, 0.00000001f).IsBlack());
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::Black().IsAlmostBlack());
	STATIC_REQUIRE(PonyEngine::Math::ColorRG<float>(0.000000001f, 0.0000000001f).IsAlmostBlack());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::ColorRG<float>(0.3f, 0.0000001f).IsAlmostBlack());
	STATIC_REQUIRE(PonyEngine::Math::ColorRG<float>(0.3f, 0.0000001f).IsAlmostBlack(PonyEngine::Math::Tolerance{.absolute = 2.f}));

	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<std::uint32_t>::White().IsWhite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::ColorRGB<float>(0.99999999f, 0.999999f, 0.9999999f).IsWhite());
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>::White().IsAlmostWhite());
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>(0.9999999f, 0.9999999f, 0.9999999f).IsAlmostWhite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::ColorRGB<float>(0.8f, 0.9f, 0.7f).IsAlmostWhite());
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<float>(0.8f, 0.9f, 0.7f).IsAlmostWhite(PonyEngine::Math::Tolerance{.absolute = 2.f}));

	STATIC_REQUIRE(PonyEngine::Math::ColorA<std::uint32_t>::Clear().IsTransparent());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::ColorBA<float>(0.0000001f, 0.000001f).IsTransparent());
	STATIC_REQUIRE(PonyEngine::Math::ColorRA<float>::Clear().IsAlmostTransparent());
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>(0.0000001f, 0.0000001f, 0.0000001f, 0.00000000000000000000000000000000000001f).IsAlmostTransparent());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::ColorRGBA<float>(0.4f, 0.5f, 0.7f, 0.1f).IsAlmostTransparent());
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>(0.4f, 0.5f, 0.7f, 0.1f).IsAlmostTransparent(PonyEngine::Math::Tolerance{.absolute = 2.f}));

	STATIC_REQUIRE(PonyEngine::Math::ColorA<std::uint32_t>::Black().IsOpaque());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::ColorBA<float>(0.0000001f, 0.95f).IsOpaque());
	STATIC_REQUIRE(PonyEngine::Math::ColorRA<float>::Red().IsAlmostOpaque());
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>(0.4f, 0.2f, 0.8f, 0.9999999999999999999f).IsAlmostOpaque());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::ColorRGBA<float>(0.4f, 0.5f, 0.7f, 0.8f).IsAlmostOpaque());
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>(0.4f, 0.5f, 0.7f, 0.8f).IsAlmostOpaque(PonyEngine::Math::Tolerance{.absolute = 2.f}));
}

TEST_CASE("Color isFinite", "[Math][Color]")
{
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, 0.3f, 0.4f).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::ColorRGBA<float>(std::numeric_limits<float>::quiet_NaN(), 0.2f, 0.3f, 0.4f).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::ColorRGBA<float>(0.1f, std::numeric_limits<float>::quiet_NaN(), 0.3f, 0.4f).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, std::numeric_limits<float>::quiet_NaN(), 0.4f).IsFinite());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, 0.3f, std::numeric_limits<float>::quiet_NaN()).IsFinite());
}

TEST_CASE("Color toString", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, 0.3f, 0.4f);
	auto rgbaExpected = std::format("RGBA: ({:n})", rgba.Span());
	REQUIRE(std::format("{:c:}", rgba) == rgbaExpected);
	rgbaExpected = std::format("({:n})", rgba.Span());
	REQUIRE(std::format("{}", rgba) == rgbaExpected);

	constexpr auto brg = PonyEngine::Math::Color<std::uint8_t, PonyEngine::Math::ColorChannel::Blue, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Green>(72, 127, 250);
	auto brgExpected = std::format("BRG: ({:n})", brg.Span());
	REQUIRE(std::format("{:c:}", brg) == brgExpected);
	brgExpected = std::format("({:n})", brg.Span());
	REQUIRE(std::format("{}", brg) == brgExpected);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, 0.3f, 0.4f).ToString();
	};
#endif
}

TEST_CASE("Color cast", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, 0.3f, 0.4f);
	constexpr auto agrb = static_cast<PonyEngine::Math::Color<std::uint16_t, PonyEngine::Math::ColorChannel::Alpha, PonyEngine::Math::ColorChannel::Green, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Blue>>(rgba);
	STATIC_REQUIRE(agrb.A() == PonyEngine::Math::RoundToIntegral<std::uint16_t>(rgba.A() * std::numeric_limits<std::uint16_t>::max()));
	STATIC_REQUIRE(agrb.G() == PonyEngine::Math::RoundToIntegral<std::uint16_t>(rgba.G() * std::numeric_limits<std::uint16_t>::max()));
	STATIC_REQUIRE(agrb.R() == PonyEngine::Math::RoundToIntegral<std::uint16_t>(rgba.R() * std::numeric_limits<std::uint16_t>::max()));
	STATIC_REQUIRE(agrb.B() == PonyEngine::Math::RoundToIntegral<std::uint16_t>(rgba.B() * std::numeric_limits<std::uint16_t>::max()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return static_cast<PonyEngine::Math::Color<std::uint16_t, PonyEngine::Math::ColorChannel::Alpha, PonyEngine::Math::ColorChannel::Green, PonyEngine::Math::ColorChannel::Red, PonyEngine::Math::ColorChannel::Blue>>(PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, 0.3f, 0.4f));
	};
#endif
}

TEST_CASE("Color cast to vector", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, 0.3f, 0.4f);
	constexpr auto vector = static_cast<PonyEngine::Math::Vector4<float>>(rgba);
	STATIC_REQUIRE(vector.X() == rgba.R());
	STATIC_REQUIRE(vector.Y() == rgba.G());
	STATIC_REQUIRE(vector.Z() == rgba.B());
	STATIC_REQUIRE(vector.W() == rgba.A());
}

TEST_CASE("Color index access", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) constexpr
	{
		auto copy = color;
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasRed)
		{
			copy[0] -= 1;
		}
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasGreen)
		{
			copy[1] += 1;
		}
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasBlue)
		{
			copy[2] *= 2;
		}
		if constexpr (PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasAlpha)
		{
			copy[3] /= 2;
		}
		return copy;
	};

	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, 0.3f, 0.4f);
	STATIC_REQUIRE(rgba[0] == 0.1f);
	STATIC_REQUIRE(rgba[1] == 0.2f);
	STATIC_REQUIRE(rgba[2] == 0.3f);
	STATIC_REQUIRE(rgba[3] == 0.4f);

	constexpr auto copyRgba = test(rgba);
	STATIC_REQUIRE(copyRgba[0] == 0.1f - 1);
	STATIC_REQUIRE(copyRgba[1] == 0.2f + 1);
	STATIC_REQUIRE(copyRgba[2] == 0.3f * 2);
	STATIC_REQUIRE(copyRgba[3] == 0.4f / 2);
}

TEST_CASE("Color copy assignment", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) constexpr
	{
		auto copy = PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>();
		copy = color;
		return copy;
	};

	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, 0.3f, 0.4f);
	constexpr auto copyRgba = test(rgba);
	STATIC_REQUIRE(copyRgba == rgba);
}

TEST_CASE("Color move assignment", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) constexpr
	{
		auto copy = PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>();
		copy = color;
		auto moved = PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>();
		moved = std::move(copy);
		return moved;
	};

	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, 0.3f, 0.4f);
	constexpr auto copyRgba = test(rgba);
	STATIC_REQUIRE(copyRgba == rgba);
}

TEST_CASE("Color sum assignment", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color, const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color1) constexpr
	{
		auto copy = color;
		copy += color1;
		return copy;
	};

	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, 0.3f, 0.4f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.3f, 0.1f, 0.6f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(test(rgba, rgba1), PonyEngine::Math::ColorRGBA<float>(0.6f, 0.5f, 0.4f, 1.f)));

	constexpr auto argb = PonyEngine::Math::ColorARGB<std::uint8_t>(240, 100, 210, 160);
	constexpr auto argb1 = PonyEngine::Math::ColorARGB<std::uint8_t>(100, 110, 80, 20);
	STATIC_REQUIRE(test(argb, argb1) == PonyEngine::Math::ColorARGB<std::uint8_t>(255, 210, 255, 180));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		auto color = PonyEngine::Math::ColorRGBA<float>(0.1f, 0.2f, 0.3f, 0.4f);
		color += PonyEngine::Math::ColorRGBA<float>(0.5f, 0.3f, 0.1f, 0.6f);
		return color;
	};
	BENCHMARK("Uint")
	{
		auto color = PonyEngine::Math::ColorRGBA<std::uint8_t>(10u, 20u, 30u, 40u);
		color += PonyEngine::Math::ColorRGBA<std::uint8_t>(150u, 250u, 10u, 245u);
		return color;
	};
#endif
}

TEST_CASE("Color subtraction assignment", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color, const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color1) constexpr
	{
		auto copy = color;
		copy -= color1;
		return copy;
	};

	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.3f, 0.1f, 0.1f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(test(rgba, rgba1), PonyEngine::Math::ColorRGBA<float>(0.3f, 0.3f, 0.2f, 0.8f)));

	constexpr auto argb = PonyEngine::Math::ColorARGB<std::uint8_t>(240, 100, 210, 160);
	constexpr auto argb1 = PonyEngine::Math::ColorARGB<std::uint8_t>(100, 110, 80, 20);
	STATIC_REQUIRE(test(argb, argb1) == PonyEngine::Math::ColorARGB<std::uint8_t>(140, 0, 130, 140));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		auto color = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f);
		color -= PonyEngine::Math::ColorRGBA<float>(0.5f, 0.3f, 0.1f, 0.1f);
		return color;
	};
	BENCHMARK("Uint")
	{
		auto color = PonyEngine::Math::ColorRGBA<std::uint8_t>(240, 100, 210, 160);
		color -= PonyEngine::Math::ColorRGBA<std::uint8_t>(100, 110, 80, 20);
		return color;
	};
#endif
}

TEST_CASE("Color multiply assignment", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color, const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color1) constexpr
	{
		auto copy = color;
		copy *= color1;
		return copy;
	};

	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.3f, 0.1f, 0.1f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(test(rgba, rgba1), PonyEngine::Math::ColorRGBA<float>(0.8f * 0.5f, 0.6f * 0.3f, 0.3f * 0.1f, 0.9f * 0.1f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto color = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f);
		color *= PonyEngine::Math::ColorRGBA<float>(0.5f, 0.3f, 0.1f, 0.1f);
		return color;
	};
#endif
}

TEST_CASE("Color multiply value assignment", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color, const T multiplier) constexpr
	{
		auto copy = color;
		copy *= multiplier;
		return copy;
	};

	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(test(rgba, 0.5f), PonyEngine::Math::ColorRGBA<float>(0.8f * 0.5f, 0.6f * 0.5f, 0.3f * 0.5f, 0.9f * 0.5f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto color = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f);
		color *= 0.5f;
		return color;
	};
#endif
}

TEST_CASE("Color divide assignment", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>&color, const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>&color1) constexpr
	{
		auto copy = color;
		copy /= color1;
		return copy;
	};

	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.3f, 0.1f, 0.1f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(test(rgba, rgba1), PonyEngine::Math::ColorRGBA<float>(0.8f / 0.5f, 0.6f / 0.3f, 0.3f / 0.1f, 0.9f / 0.1f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto color = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f);
		color /= PonyEngine::Math::ColorRGBA<float>(0.5f, 0.3f, 0.1f, 0.1f);
		return color;
	};
#endif
}

TEST_CASE("Color divide value assignment", "[Math][Color]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>&color, const T multiplier) constexpr
	{
		auto copy = color;
		copy /= multiplier;
		return copy;
	};

	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(test(rgba, 0.5f), PonyEngine::Math::ColorRGBA<float>(0.8f / 0.5f, 0.6f / 0.5f, 0.3f / 0.5f, 0.9f / 0.5f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto color = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f);
		color /= 0.5f;
		return color;
	};
#endif
}

TEST_CASE("Color equals", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f);
	STATIC_REQUIRE(rgba == rgba);
	auto rgba1 = rgba;
	REQUIRE(rgba == rgba1);
	for (std::size_t i = 0; i < PonyEngine::Math::ColorRGBA<float>::ChannelCount; ++i)
	{
		const float prev = rgba1[i];
		rgba1[i] += 0.0000001f;
		REQUIRE_FALSE(rgba == rgba1);
		rgba1[i] -= 1.f;
		REQUIRE_FALSE(rgba == rgba1);
		rgba1[i] = prev;
	}
}

TEST_CASE("Color channel conversion", "[Math][Color]")
{
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<float>(0.6f) == 0.6f);
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<double>(0.6f) == static_cast<double>(0.6f));
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<std::uint8_t>(0.6f) == PonyEngine::Math::RoundToIntegral<std::uint8_t>(0.6f * std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<double>(-0.4f) == static_cast<double>(-0.4f));
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<std::uint8_t>(-0.4f) == 0);
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<double>(1.5f) == static_cast<double>(1.5f));
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<std::uint8_t>(1.5f) == std::numeric_limits<std::uint8_t>::max());
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<double>(-1.5f) == static_cast<double>(-1.5f));
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<std::uint8_t>(-1.5f) == 0);

	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<std::uint8_t>(std::uint8_t{110}) == 110);
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<std::uint16_t>(std::uint8_t{110}) == 28270);
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<std::uint8_t>(std::uint16_t{28270}) == 110);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ConvertColorChannel<float>(std::uint8_t{110}), 110.f / std::numeric_limits<std::uint8_t>::max()));
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<std::uint16_t>(std::numeric_limits<std::uint8_t>::max()) == std::numeric_limits<std::uint16_t>::max());
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<std::uint8_t>(std::numeric_limits<std::uint16_t>::max()) == std::numeric_limits<std::uint8_t>::max());
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<float>(std::numeric_limits<std::uint8_t>::max()) == 1.f);
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<std::uint16_t>(std::uint8_t{0}) == 0);
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<std::uint8_t>(std::uint16_t{0}) == 0);
	STATIC_REQUIRE(PonyEngine::Math::ConvertColorChannel<float>(std::uint8_t{0}) == 0.f);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float to double")
	{
		return PonyEngine::Math::ConvertColorChannel<double>(0.6f);
	};
	BENCHMARK("Float to uint")
	{
		return PonyEngine::Math::ConvertColorChannel<std::uint8_t>(0.6f);
	};
	BENCHMARK("Uint to uint")
	{
		return PonyEngine::Math::ConvertColorChannel<std::uint8_t>(std::uint8_t{110});
	};
	BENCHMARK("Uint to float")
	{
		return PonyEngine::Math::ConvertColorChannel<float>(std::uint8_t{110});
	};
#endif
}

TEST_CASE("Color distance", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.1f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.9f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::DistanceSquared(rgba, rgba1), 0.86f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Distance(rgba, rgba1), std::sqrt(0.86f)));

	constexpr auto rgb = PonyEngine::Math::ColorRGB<std::uint32_t>(30, 200, 130);
	constexpr auto rgb1 = PonyEngine::Math::ColorRGB<std::uint32_t>(100, 50, 200);
	STATIC_REQUIRE(PonyEngine::Math::DistanceSquared(rgb, rgb1) == 32300);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Distance<float>(rgb, rgb1), std::sqrt(32300.f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float squared")
	{
		return PonyEngine::Math::DistanceSquared(PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.1f), PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.9f));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Distance(PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.1f), PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.9f));
	};
	BENCHMARK("Uint squared")
	{
		return PonyEngine::Math::DistanceSquared(PonyEngine::Math::ColorRGBA<std::uint32_t>(30, 200, 130, 44), PonyEngine::Math::ColorRGBA<std::uint32_t>(100, 50, 200, 120));
	};
	BENCHMARK("Uint")
	{
		return PonyEngine::Math::Distance(PonyEngine::Math::ColorRGBA<std::uint32_t>(30, 200, 130, 44), PonyEngine::Math::ColorRGBA<std::uint32_t>(100, 50, 200, 120));
	};
#endif
}

TEST_CASE("Color min", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.1f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.9f);
	constexpr auto rgbaMin = PonyEngine::Math::Min(rgba, rgba1);
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>(0.5f, 0.3f, 0.1f, 0.1f) == rgbaMin);

	constexpr auto rgb = PonyEngine::Math::ColorRGB<std::uint32_t>(30, 200, 130);
	constexpr auto rgb1 = PonyEngine::Math::ColorRGB<std::uint32_t>(100, 50, 200);
	constexpr auto rgbMin = PonyEngine::Math::Min(rgb, rgb1);
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint32_t>(30, 50, 130) == rgbMin);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Min(PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.1f), PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.9f));
	};
	BENCHMARK("Uint")
	{
		return PonyEngine::Math::Min(PonyEngine::Math::ColorRGBA<std::uint32_t>(30, 200, 130, 44), PonyEngine::Math::ColorRGBA<std::uint32_t>(100, 50, 200, 120));
	};
#endif
}

TEST_CASE("Color max", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.1f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.9f);
	constexpr auto rgbaMax = PonyEngine::Math::Max(rgba, rgba1);
	STATIC_REQUIRE(PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f) == rgbaMax);

	constexpr auto rgb = PonyEngine::Math::ColorRGB<std::uint32_t>(30, 200, 130);
	constexpr auto rgb1 = PonyEngine::Math::ColorRGB<std::uint32_t>(100, 50, 200);
	constexpr auto rgbMax = PonyEngine::Math::Max(rgb, rgb1);
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint32_t>(100, 200, 200) == rgbMax);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Max(PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.1f), PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.9f));
	};
	BENCHMARK("Uint")
	{
		return PonyEngine::Math::Max(PonyEngine::Math::ColorRGBA<std::uint32_t>(30, 200, 130, 44), PonyEngine::Math::ColorRGBA<std::uint32_t>(100, 50, 200, 120));
	};
#endif
}

TEST_CASE("Color clamp", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f);
	constexpr auto rgba2 = PonyEngine::Math::ColorRGBA<float>(0.9f, 0.8f, 0.2f, 0.95f);
	STATIC_REQUIRE(PonyEngine::Math::Clamp(rgba, rgba1, rgba2) == PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.2f, 0.9f));

	constexpr auto rgb = PonyEngine::Math::ColorRGB<std::uint8_t>(30, 200, 130);
	constexpr auto rgb1 = PonyEngine::Math::ColorRGB<std::uint8_t>(100, 50, 110);
	constexpr auto rgb2 = PonyEngine::Math::ColorRGB<std::uint8_t>(150, 250, 120);
	STATIC_REQUIRE(PonyEngine::Math::Clamp(rgb, rgb1, rgb2) == PonyEngine::Math::ColorRGB<std::uint8_t>(100, 200, 120));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Clamp(PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f), PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f), PonyEngine::Math::ColorRGBA<float>(0.9f, 0.8f, 0.2f, 0.95f));
	};
	BENCHMARK("Uint")
	{
		return PonyEngine::Math::Clamp(PonyEngine::Math::ColorRGBA<std::uint8_t>(30, 200, 130, 44), PonyEngine::Math::ColorRGBA<std::uint8_t>(100, 50, 110, 120), PonyEngine::Math::ColorRGBA<std::uint8_t>(150, 250, 120, 150));
	};
#endif
}

TEST_CASE("Color lerp", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Lerp(rgba, rgba1, 0.f), PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Lerp(rgba, rgba1, 1.f), PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Lerp(rgba, rgba1, 0.5f), PonyEngine::Math::ColorRGBA<float>(0.65f, 0.45f, 0.2f, 0.5f)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Lerp(rgba, rgba1, 2.f), PonyEngine::Math::ColorRGBA<float>(0.2f, 0.9f, -0.1f, -0.7f)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Lerp(rgba, rgba1, -1.f), PonyEngine::Math::ColorRGBA<float>(1.1f, 0.f, 0.5f, 1.7f)));

	constexpr auto rgb = PonyEngine::Math::ColorRGB<std::uint8_t>(30, 200, 130);
	constexpr auto rgb1 = PonyEngine::Math::ColorRGB<std::uint8_t>(100, 50, 110);
	STATIC_REQUIRE(PonyEngine::Math::Lerp(rgb, rgb1, 0.f) == PonyEngine::Math::ColorRGB<std::uint8_t>(30, 200, 130));
	STATIC_REQUIRE(PonyEngine::Math::Lerp(rgb, rgb1, 1.f) == PonyEngine::Math::ColorRGB<std::uint8_t>(100, 50, 110));
	STATIC_REQUIRE(PonyEngine::Math::Lerp(rgb, rgb1, 0.5f) == PonyEngine::Math::ColorRGB<std::uint8_t>(65, 125, 120));
	STATIC_REQUIRE(PonyEngine::Math::Lerp(rgb, rgb1, 2.f) == PonyEngine::Math::ColorRGB<std::uint8_t>(170, 156, 90));
	STATIC_REQUIRE(PonyEngine::Math::Lerp(rgb, rgb1, -1.f) == PonyEngine::Math::ColorRGB<std::uint8_t>(216, 94, 150));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Lerp(PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f), PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f), 0.5f);
	};
	BENCHMARK("Uint")
	{
		return PonyEngine::Math::Lerp(PonyEngine::Math::ColorRGBA<std::uint8_t>(30, 200, 130, 44), PonyEngine::Math::ColorRGBA<std::uint8_t>(100, 50, 110, 120), 0.5f);
	};
#endif
}

TEST_CASE("Color are almost equal", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.6f, 0.3f, 0.9f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(rgba, rgba));
	auto rgba1 = rgba;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(rgba, rgba1));
	for (std::size_t i = 0; i < PonyEngine::Math::ColorRGBA<float>::ChannelCount; ++i)
	{
		const float prev = rgba1[i];
		rgba1[i] += 0.0000001f;
		REQUIRE(PonyEngine::Math::AreAlmostEqual(rgba, rgba1));
		rgba1[i] -= 1.f;
		REQUIRE_FALSE(PonyEngine::Math::AreAlmostEqual(rgba, rgba1));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(rgba, rgba1, PonyEngine::Math::Tolerance{.absolute = 5.f}));
		rgba1[i] = prev;
	}
}

TEST_CASE("Color sum", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ColorRGBA<float>(1.3f, 0.9f, 0.4f, 1.f), rgba + rgba1));

	constexpr auto rgb = PonyEngine::Math::ColorRGB<std::uint8_t>(230, 200, 130);
	constexpr auto rgb1 = PonyEngine::Math::ColorRGB<std::uint8_t>(100, 50, 110);
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint8_t>(255, 250, 240) == rgb + rgb1);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f) + PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f);
	};
	BENCHMARK("Uint")
	{
		return PonyEngine::Math::ColorRGBA<std::uint8_t>(230, 200, 130, 44) + PonyEngine::Math::ColorRGBA<std::uint8_t>(100, 50, 110, 120);
	};
#endif
}

TEST_CASE("Color negate", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, -0.3f, 0.9f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ColorRGBA<float>(-0.8f, -0.3f, 0.3f, -0.9f), -rgba));

	constexpr auto rgb = PonyEngine::Math::ColorRGB<std::uint8_t>(230, 200, 130);
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint8_t>(-230, -200, -130) == -rgb);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return -PonyEngine::Math::ColorRGBA<float>(0.8f, -0.3f, 0.3f, 0.9f);
	};
	BENCHMARK("Uint")
	{
		return -PonyEngine::Math::ColorRGBA<std::uint8_t>(230, 200, 130, 44);
	};
#endif
}

TEST_CASE("Color subtraction", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ColorRGBA<float>(0.3f, -0.3f, 0.2f, 0.8f), rgba - rgba1));

	constexpr auto rgb = PonyEngine::Math::ColorRGB<std::uint8_t>(230, 200, 130);
	constexpr auto rgb1 = PonyEngine::Math::ColorRGB<std::uint8_t>(100, 50, 160);
	STATIC_REQUIRE(PonyEngine::Math::ColorRGB<std::uint8_t>(130, 150, 0) == rgb - rgb1);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f) - PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f);
	};
	BENCHMARK("Uint")
	{
		return PonyEngine::Math::ColorRGBA<std::uint8_t>(230, 200, 130, 44) - PonyEngine::Math::ColorRGBA<std::uint8_t>(100, 50, 110, 120);
	};
#endif
}

TEST_CASE("Color product", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ColorRGBA<float>(0.8f * 0.5f, 0.3f * 0.6f, 0.3f * 0.1f, 0.9f * 0.1f), rgba * rgba1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f) * PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f);
	};
#endif
}

TEST_CASE("Color product value", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ColorRGBA<float>(0.8f * 0.3f, 0.3f * 0.3f, 0.3f * 0.3f, 0.9f * 0.3f), rgba * 0.3f));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ColorRGBA<float>(0.8f * 0.3f, 0.3f * 0.3f, 0.3f * 0.3f, 0.9f * 0.3f), 0.3f * rgba));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f) * 0.3f;
	};
#endif
}

TEST_CASE("Color division", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f);
	constexpr auto rgba1 = PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ColorRGBA<float>(0.8f / 0.5f, 0.3f / 0.6f, 0.3f / 0.1f, 0.9f / 0.1f), rgba / rgba1));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f) / PonyEngine::Math::ColorRGBA<float>(0.5f, 0.6f, 0.1f, 0.1f);
	};
#endif
}

TEST_CASE("Color division value", "[Math][Color]")
{
	constexpr auto rgba = PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::ColorRGBA<float>(0.8f / 0.3f, 0.3f / 0.3f, 0.3f / 0.3f, 0.9f / 0.3f), rgba / 0.3f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ColorRGBA<float>(0.8f, 0.3f, 0.3f, 0.9f) / 0.3f;
	};
#endif
}
