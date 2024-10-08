/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstddef>
#include <cstdint>
#include <format>
#include <limits>
#include <string>

import PonyBase.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(RGBAIntTests)
	{
		TEST_METHOD(ValueTypeTest)
		{
			Assert::IsTrue(std::is_same_v<std::uint8_t, PonyBase::Math::RGBAInt<std::uint8_t>::ValueType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::numeric_limits<std::uint8_t>::max(), PonyBase::Math::RGBAInt<std::uint8_t>::MaxValue);
			Assert::AreEqual(std::size_t{4}, PonyBase::Math::RGBAInt<std::uint8_t>::ComponentCount);
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyBase::Math::RGBAInt<std::uint8_t>::Predefined::Red == PonyBase::Math::RGBAInt<std::uint8_t>(255, 0, 0, 255));
			Assert::IsTrue(PonyBase::Math::RGBAInt<std::uint8_t>::Predefined::Green == PonyBase::Math::RGBAInt<std::uint8_t>(0, 255, 0, 255));
			Assert::IsTrue(PonyBase::Math::RGBAInt<std::uint8_t>::Predefined::Blue == PonyBase::Math::RGBAInt<std::uint8_t>(0, 0, 255, 255));
			Assert::IsTrue(PonyBase::Math::RGBAInt<std::uint8_t>::Predefined::Black == PonyBase::Math::RGBAInt<std::uint8_t>(0, 0, 0, 255));
			Assert::IsTrue(PonyBase::Math::RGBAInt<std::uint8_t>::Predefined::White == PonyBase::Math::RGBAInt<std::uint8_t>(255, 255, 255, 255));
			Assert::IsTrue(PonyBase::Math::RGBAInt<std::uint8_t>::Predefined::Clear == PonyBase::Math::RGBAInt<std::uint8_t>(0, 0, 0, 0));
			Assert::IsTrue(PonyBase::Math::RGBAInt<std::uint8_t>::Predefined::Yellow == PonyBase::Math::RGBAInt<std::uint8_t>(255, 255, 0, 255));
			Assert::IsTrue(PonyBase::Math::RGBAInt<std::uint8_t>::Predefined::Magenta == PonyBase::Math::RGBAInt<std::uint8_t>(255, 0, 255, 255));
			Assert::IsTrue(PonyBase::Math::RGBAInt<std::uint8_t>::Predefined::Cyan == PonyBase::Math::RGBAInt<std::uint8_t>(0, 255, 255, 255));
		}

		TEST_METHOD(ConstructorTest)
		{
			auto defaultColor = PonyBase::Math::RGBAInt<std::uint8_t>();
			Assert::AreEqual(std::uint8_t{0}, defaultColor.R());
			Assert::AreEqual(std::uint8_t{0}, defaultColor.G());
			Assert::AreEqual(std::uint8_t{0}, defaultColor.B());

			constexpr std::uint8_t r = 56;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 11;
			constexpr std::uint8_t a = 66;
			auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			Assert::AreEqual(a, color.A());

			auto array = std::array{r, g, b, a};
			const auto arrayColor = PonyBase::Math::RGBAInt<std::uint8_t>(array);
			Assert::AreEqual(r, arrayColor.R());
			Assert::AreEqual(g, arrayColor.G());
			Assert::AreEqual(b, arrayColor.B());
			Assert::AreEqual(a, arrayColor.A());

			constexpr auto rgb = PonyBase::Math::RGBInt(r, g, b);
			const auto rgba = PonyBase::Math::RGBAInt<std::uint8_t>(rgb, a);
			Assert::AreEqual(r, rgba.R());
			Assert::AreEqual(g, rgba.G());
			Assert::AreEqual(b, rgba.B());
			Assert::AreEqual(a, rgba.A());

			constexpr auto vector = PonyBase::Math::Vector4<std::uint8_t>(r, g, b, a);
			auto vectorColor = PonyBase::Math::RGBAInt<std::uint8_t>(vector);
			Assert::AreEqual(r, vectorColor.R());
			Assert::AreEqual(g, vectorColor.G());
			Assert::AreEqual(b, vectorColor.B());
			Assert::AreEqual(a, vectorColor.A());

			auto copiedColor = color;
			Assert::AreEqual(r, copiedColor.R());
			Assert::AreEqual(g, copiedColor.G());
			Assert::AreEqual(b, copiedColor.B());
			Assert::AreEqual(a, copiedColor.A());

			auto movedColor = std::move(color);
			Assert::AreEqual(r, movedColor.R());
			Assert::AreEqual(g, movedColor.G());
			Assert::AreEqual(b, movedColor.B());
			Assert::AreEqual(a, movedColor.A());
		}

		TEST_METHOD(AccessTest)
		{
			constexpr std::uint8_t r = 49;
			constexpr std::uint8_t g = 69;
			constexpr std::uint8_t b = 211;
			constexpr std::uint8_t a = 166;
			auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			Assert::AreEqual(a, color.A());
			constexpr auto cColor = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(r, cColor.R());
			Assert::AreEqual(g, cColor.G());
			Assert::AreEqual(b, cColor.B());
			Assert::AreEqual(a, cColor.A());
		}

		TEST_METHOD(SpanTest)
		{
			constexpr std::uint8_t r = 69;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 228;
			constexpr std::uint8_t a = 200;
			auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(r, color.Span()[0]);
			Assert::AreEqual(g, color.Span()[1]);
			Assert::AreEqual(b, color.Span()[2]);
			Assert::AreEqual(a, color.Span()[3]);
			constexpr auto cColor = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(r, cColor.Span()[0]);
			Assert::AreEqual(g, cColor.Span()[1]);
			Assert::AreEqual(b, cColor.Span()[2]);
			Assert::AreEqual(a, cColor.Span()[3]);
		}

		TEST_METHOD(MinTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(std::uint8_t{1}, color.Min());
			constexpr auto cColor = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(std::uint8_t{1}, cColor.Min());
		}

		TEST_METHOD(MaxTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(std::uint8_t{211}, color.Max());
			constexpr auto cColor = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(std::uint8_t{211}, cColor.Max());
		}

		TEST_METHOD(MinMaxTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			auto pair = color.MinMax();
			Assert::AreEqual(b, pair.first);
			Assert::AreEqual(r, pair.second);
			constexpr auto cColor = PonyBase::Math::RGBA<float>(r, g, b, a);
			auto cPair = cColor.MinMax();
			Assert::AreEqual(b, pair.first);
			Assert::AreEqual(r, pair.second);
		}

		TEST_METHOD(IsBlackTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			constexpr auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::IsFalse(color.IsBlack());
			Assert::IsTrue(PonyBase::Math::RGBAInt<std::uint8_t>::Predefined::Black.IsBlack());
		}

		TEST_METHOD(IsWhiteTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			constexpr auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::IsFalse(color.IsWhite());
			Assert::IsTrue(PonyBase::Math::RGBAInt<std::uint8_t>::Predefined::White.IsWhite());
		}

		TEST_METHOD(IsTransparent)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::IsFalse(color.IsTransparent());
			color.A() = 0;
			Assert::IsTrue(color.IsTransparent());
			Assert::IsTrue(PonyBase::Math::RGBAInt<std::uint8_t>::Predefined::Clear.IsTransparent());
		}

		TEST_METHOD(SetTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			auto color = PonyBase::Math::RGBAInt<std::uint8_t>();
			color.Set(r, g, b, a);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			Assert::AreEqual(a, color.A());
			color = PonyBase::Math::RGBAInt<std::uint8_t>();
			constexpr std::array<std::uint8_t, 4> array = {r, g, b, a};
			color.Set(array);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			Assert::AreEqual(a, color.A());
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			constexpr auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			const std::string string = color.ToString();
			Assert::AreEqual(std::format("(R: {}, G: {}, B: {}, A: {})", r, g, b, a), string);
			std::ostringstream ss;
			ss << color;
			Assert::AreEqual(string, ss.str());
		}

		TEST_METHOD(MinCombinedTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 100;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 101;
			constexpr auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			constexpr std::uint8_t r1 = 200;
			constexpr std::uint8_t g1 = 200;
			constexpr std::uint8_t b1 = 1;
			constexpr std::uint8_t a1 = 201;
			constexpr auto color1 = PonyBase::Math::RGBAInt<std::uint8_t>(r1, g1, b1, a1);
			auto min = PonyBase::Math::Min(color, color1);
			Assert::AreEqual(r1, min.R());
			Assert::AreEqual(g, min.G());
			Assert::AreEqual(b, min.B());
			Assert::AreEqual(a, min.A());
		}

		TEST_METHOD(MaxCombinedTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 100;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 101;
			constexpr auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			constexpr std::uint8_t r1 = 200;
			constexpr std::uint8_t g1 = 200;
			constexpr std::uint8_t b1 = 1;
			constexpr std::uint8_t a1 = 201;
			constexpr auto color1 = PonyBase::Math::RGBAInt<std::uint8_t>(r1, g1, b1, a1);
			auto max = PonyBase::Math::Max(color, color1);
			Assert::AreEqual(r, max.R());
			Assert::AreEqual(g1, max.G());
			Assert::AreEqual(b, max.B());
			Assert::AreEqual(a1, max.A());
		}

		TEST_METHOD(ClampTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 100;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 101;
			constexpr auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			constexpr std::uint8_t r1 = 250;
			constexpr std::uint8_t g1 = 200;
			constexpr std::uint8_t b1 = 1;
			constexpr std::uint8_t a1 = 201;
			constexpr auto color1 = PonyBase::Math::RGBAInt<std::uint8_t>(r1, g1, b1, a1);
			constexpr std::uint8_t r2 = 240;
			constexpr std::uint8_t g2 = 210;
			constexpr std::uint8_t b2 = 5;
			constexpr std::uint8_t a2 = 1;
			constexpr auto color2 = PonyBase::Math::RGBAInt<std::uint8_t>(r2, g2, b2, a2);

			auto clamped = PonyBase::Math::Clamp(color2, color, color1);
			Assert::AreEqual(r2, clamped.R());
			Assert::AreEqual(g1, clamped.G());
			Assert::AreEqual(b, clamped.B());
			Assert::AreEqual(a, clamped.A());
		}

		TEST_METHOD(ToRGBIntTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			constexpr auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			const auto rgb = static_cast<PonyBase::Math::RGBInt<std::uint8_t>>(color);
			Assert::AreEqual(r, rgb.R());
			Assert::AreEqual(g, rgb.G());
			Assert::AreEqual(b, rgb.B());
		}

		TEST_METHOD(ToVectorTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			constexpr auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			const auto vector = static_cast<PonyBase::Math::Vector4<std::uint8_t>>(color);
			Assert::AreEqual(r, vector.X());
			Assert::AreEqual(g, vector.Y());
			Assert::AreEqual(b, vector.Z());
			Assert::AreEqual(a, vector.W());
		}

		TEST_METHOD(AccessOperatorTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(r, color[0]);
			Assert::AreEqual(g, color[1]);
			Assert::AreEqual(b, color[2]);
			Assert::AreEqual(a, color[3]);
			constexpr auto cColor = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(r, cColor[0]);
			Assert::AreEqual(g, cColor[1]);
			Assert::AreEqual(b, cColor[2]);
			Assert::AreEqual(a, cColor[3]);
		}

		TEST_METHOD(AssignmentOperatorsTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			constexpr std::uint8_t otherR = 100;
			constexpr std::uint8_t otherG = 111;
			constexpr std::uint8_t otherB = 69;
			constexpr std::uint8_t otherA = 9;
			auto otherColor = PonyBase::Math::RGBAInt<std::uint8_t>(otherR, otherG, otherB, otherA);
			PonyBase::Math::RGBAInt<std::uint8_t>& result = color = otherColor;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&result));
			Assert::AreEqual(otherR, color.R());
			Assert::AreEqual(otherG, color.G());
			Assert::AreEqual(otherB, color.B());
			Assert::AreEqual(otherA, color.A());
			color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			PonyBase::Math::RGBAInt<std::uint8_t>& otherResult = otherColor = std::move(color);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&otherColor), reinterpret_cast<std::uintptr_t>(&otherResult));
			Assert::AreEqual(r, otherColor.R());
			Assert::AreEqual(g, otherColor.G());
			Assert::AreEqual(b, otherColor.B());
			Assert::AreEqual(a, otherColor.A());
		}

		TEST_METHOD(EqualTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			auto color = PonyBase::Math::RGBAInt<std::uint8_t>(r, g, b, a);

			for (std::size_t i = 0; i < PonyBase::Math::RGBAInt<std::uint8_t>::ComponentCount; ++i)
			{
				auto otherColor = color;
				otherColor[i] += 1;
				Assert::IsFalse(color == otherColor);
				Assert::IsTrue(color != otherColor);
			}

			auto otherColor = color;
			Assert::IsTrue(color == otherColor);
			Assert::IsFalse(color != otherColor);
		}

		static constexpr PonyBase::Math::RGBAInt<std::uint8_t> ColorConstexpr()
		{
			auto color = PonyBase::Math::RGBAInt<std::uint8_t>(3, 250, 128, 111);
			auto copiedColor = color;
			auto movedColor = std::move(color);

			[[maybe_unused]] std::uint8_t r = movedColor.R();
			[[maybe_unused]] std::uint8_t g = movedColor.G();
			[[maybe_unused]] std::uint8_t b = movedColor.B();

			[[maybe_unused]] const auto span = movedColor.Span();
			span[0] -= 1;

			[[maybe_unused]] const std::uint8_t min = movedColor.Min();
			[[maybe_unused]] const std::uint8_t max = movedColor.Max();
			[[maybe_unused]] const auto minMax = movedColor.MinMax();

			movedColor.Set(124, 21, 90, 3);
			movedColor.Set(span);

			[[maybe_unused]] auto component = movedColor[1];

			copiedColor = movedColor;
			movedColor = std::move(copiedColor);

			return movedColor;
		}

		TEST_METHOD(ConstexprTest)
		{
			[[maybe_unused]] constexpr auto defaultColor = PonyBase::Math::RGBAInt<std::uint8_t>();
			[[maybe_unused]] constexpr auto color = PonyBase::Math::RGBAInt<std::uint8_t>(3, 250, 128, 100);
			[[maybe_unused]] constexpr auto rgb = PonyBase::Math::RGBAInt<std::uint8_t>(PonyBase::Math::RGBInt<std::uint8_t>(3, 156, 69), 100);
			[[maybe_unused]] constexpr auto arrayColor = PonyBase::Math::RGBAInt<std::uint8_t>(std::array{color.R(), color.G(), color.B(), color.A()});
			[[maybe_unused]] constexpr auto copiedColor = color;
			[[maybe_unused]] constexpr auto movedColor = ColorConstexpr();

			[[maybe_unused]] constexpr std::uint8_t r = color.R();
			[[maybe_unused]] constexpr std::uint8_t g = color.G();
			[[maybe_unused]] constexpr std::uint8_t b = color.B();

			[[maybe_unused]] constexpr std::uint8_t min = color.Min();
			[[maybe_unused]] constexpr std::uint8_t max = color.Max();
			[[maybe_unused]] constexpr std::pair<std::uint8_t, std::uint8_t> minMax = color.MinMax();

			[[maybe_unused]] constexpr bool isBlack = color.IsBlack();
			[[maybe_unused]] constexpr bool isWhite = color.IsWhite();
			[[maybe_unused]] constexpr bool isTransparent = color.IsTransparent();

			[[maybe_unused]] constexpr auto spanElement = color.Span()[0];

			[[maybe_unused]] constexpr auto gotRgb = static_cast<PonyBase::Math::RGBInt<std::uint8_t>>(color);
			[[maybe_unused]] constexpr auto vector = static_cast<PonyBase::Math::Vector4<std::uint8_t>>(color);

			[[maybe_unused]] constexpr bool areEqual = defaultColor == color;
			[[maybe_unused]] constexpr bool areNorEqual = defaultColor != color;

			[[maybe_unused]] constexpr auto minCombined = PonyBase::Math::Min(defaultColor, arrayColor);
			[[maybe_unused]] constexpr auto maxCombined = PonyBase::Math::Max(defaultColor, arrayColor);
			[[maybe_unused]] constexpr auto clamped = PonyBase::Math::Clamp(color, defaultColor, arrayColor);
		}
	};
}
