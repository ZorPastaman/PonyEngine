/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cstddef>;
import <cstdint>;
import <format>;
import <limits>;
import <string>;

import PonyEngine.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(RGBAIntTests)
	{
		TEST_METHOD(ValueTypeTest)
		{
			Assert::IsTrue(std::is_same_v<std::uint8_t, PonyEngine::Math::RGBAInt<std::uint8_t>::ValueType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::numeric_limits<std::uint8_t>::max(), PonyEngine::Math::RGBAInt<std::uint8_t>::MaxValue);
			Assert::AreEqual(std::size_t{4}, PonyEngine::Math::RGBAInt<std::uint8_t>::ComponentCount);
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::Red == PonyEngine::Math::RGBAInt<std::uint8_t>(255, 0, 0, 255));
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::Green == PonyEngine::Math::RGBAInt<std::uint8_t>(0, 255, 0, 255));
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::Blue == PonyEngine::Math::RGBAInt<std::uint8_t>(0, 0, 255, 255));
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::Black == PonyEngine::Math::RGBAInt<std::uint8_t>(0, 0, 0, 255));
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::White == PonyEngine::Math::RGBAInt<std::uint8_t>(255, 255, 255, 255));
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::Clear == PonyEngine::Math::RGBAInt<std::uint8_t>(0, 0, 0, 0));
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::Yellow == PonyEngine::Math::RGBAInt<std::uint8_t>(255, 255, 0, 255));
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::Magenta == PonyEngine::Math::RGBAInt<std::uint8_t>(255, 0, 255, 255));
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::Cyan == PonyEngine::Math::RGBAInt<std::uint8_t>(0, 255, 255, 255));
		}

		TEST_METHOD(ConstructorTest)
		{
			auto defaultColor = PonyEngine::Math::RGBAInt<std::uint8_t>();
			Assert::AreEqual(std::uint8_t{0}, defaultColor.R());
			Assert::AreEqual(std::uint8_t{0}, defaultColor.G());
			Assert::AreEqual(std::uint8_t{0}, defaultColor.B());

			constexpr std::uint8_t r = 56;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 11;
			constexpr std::uint8_t a = 66;
			auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			Assert::AreEqual(a, color.A());

			auto array = std::array{r, g, b, a};
			const auto arrayColor = PonyEngine::Math::RGBAInt<std::uint8_t>(array);
			Assert::AreEqual(r, arrayColor.R());
			Assert::AreEqual(g, arrayColor.G());
			Assert::AreEqual(b, arrayColor.B());
			Assert::AreEqual(a, arrayColor.A());

			constexpr auto rgb = PonyEngine::Math::RGBInt(r, g, b);
			const auto rgba = PonyEngine::Math::RGBAInt<std::uint8_t>(rgb, a);
			Assert::AreEqual(r, rgba.R());
			Assert::AreEqual(g, rgba.G());
			Assert::AreEqual(b, rgba.B());
			Assert::AreEqual(a, rgba.A());

			constexpr auto vector = PonyEngine::Math::Vector4<std::uint8_t>(r, g, b, a);
			auto vectorColor = PonyEngine::Math::RGBAInt<std::uint8_t>(vector);
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
			auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			Assert::AreEqual(a, color.A());
			constexpr auto cColor = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
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
			auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(r, color.Span()[0]);
			Assert::AreEqual(g, color.Span()[1]);
			Assert::AreEqual(b, color.Span()[2]);
			Assert::AreEqual(a, color.Span()[3]);
			color.Span()[0] += 1;
			Assert::AreEqual(static_cast<std::uint8_t>(r + 1), color.Span()[0]);
			constexpr auto cColor = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
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
			auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(std::uint8_t{1}, color.Min());
			constexpr auto cColor = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(std::uint8_t{1}, cColor.Min());
		}

		TEST_METHOD(MaxTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(std::uint8_t{211}, color.Max());
			constexpr auto cColor = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(std::uint8_t{211}, cColor.Max());
		}

		TEST_METHOD(IsBlackTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			constexpr auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::IsFalse(color.IsBlack());
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::Black.IsBlack());
		}

		TEST_METHOD(IsWhiteTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			constexpr auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::IsFalse(color.IsWhite());
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::White.IsWhite());
		}

		TEST_METHOD(IsTransparent)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::IsFalse(color.IsTransparent());
			color.A() = 0;
			Assert::IsTrue(color.IsTransparent());
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::Clear.IsTransparent());
		}

		TEST_METHOD(SetTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			auto color = PonyEngine::Math::RGBAInt<std::uint8_t>();
			color.Set(r, g, b, a);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			Assert::AreEqual(a, color.A());
			color = PonyEngine::Math::RGBAInt<std::uint8_t>();
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
			constexpr auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			const std::string string = color.ToString();
			Assert::AreEqual(std::format("(R: {}, G: {}, B: {}, A: {})", r, g, b, a), string);
			std::ostringstream ss;
			ss << color;
			Assert::AreEqual(string, ss.str());
		}

		TEST_METHOD(ToRGBIntTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr std::uint8_t a = 201;
			constexpr auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			const auto rgb = static_cast<PonyEngine::Math::RGBInt<std::uint8_t>>(color);
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
			constexpr auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			const auto vector = static_cast<PonyEngine::Math::Vector4<std::uint8_t>>(color);
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
			auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			Assert::AreEqual(r, color[0]);
			Assert::AreEqual(g, color[1]);
			Assert::AreEqual(b, color[2]);
			Assert::AreEqual(a, color[3]);
			constexpr auto cColor = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
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
			auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			constexpr std::uint8_t otherR = 100;
			constexpr std::uint8_t otherG = 111;
			constexpr std::uint8_t otherB = 69;
			constexpr std::uint8_t otherA = 9;
			auto otherColor = PonyEngine::Math::RGBAInt<std::uint8_t>(otherR, otherG, otherB, otherA);
			PonyEngine::Math::RGBAInt<std::uint8_t>& result = color = otherColor;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&result));
			Assert::AreEqual(otherR, color.R());
			Assert::AreEqual(otherG, color.G());
			Assert::AreEqual(otherB, color.B());
			Assert::AreEqual(otherA, color.A());
			color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);
			PonyEngine::Math::RGBAInt<std::uint8_t>& otherResult = otherColor = std::move(color);
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
			auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(r, g, b, a);

			for (std::size_t i = 0; i < PonyEngine::Math::RGBAInt<std::uint8_t>::ComponentCount; ++i)
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

		static constexpr PonyEngine::Math::RGBAInt<std::uint8_t> ColorConstexpr()
		{
			auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(3, 250, 128, 111);
			auto copiedColor = color;
			auto movedColor = std::move(color);

			[[maybe_unused]] std::uint8_t r = movedColor.R();
			[[maybe_unused]] std::uint8_t g = movedColor.G();
			[[maybe_unused]] std::uint8_t b = movedColor.B();

			[[maybe_unused]] const auto span = movedColor.Span();

			[[maybe_unused]] const std::uint8_t min = movedColor.Min();
			[[maybe_unused]] const std::uint8_t max = movedColor.Max();

			movedColor.Set(124, 21, 90, 3);
			movedColor.Set(span);

			[[maybe_unused]] auto component = movedColor[1];

			copiedColor = movedColor;
			movedColor = std::move(copiedColor);

			return movedColor;
		}

		TEST_METHOD(ConstexprTest)
		{
			[[maybe_unused]] constexpr auto defaultColor = PonyEngine::Math::RGBAInt<std::uint8_t>();
			[[maybe_unused]] constexpr auto color = PonyEngine::Math::RGBAInt<std::uint8_t>(3, 250, 128, 100);
			[[maybe_unused]] constexpr auto rgb = PonyEngine::Math::RGBAInt<std::uint8_t>(PonyEngine::Math::RGBInt<std::uint8_t>(3, 156, 69), 100);
			[[maybe_unused]] constexpr auto arrayColor = PonyEngine::Math::RGBAInt<std::uint8_t>(std::array{color.R(), color.G(), color.B(), color.A()});
			[[maybe_unused]] constexpr auto copiedColor = color;
			[[maybe_unused]] constexpr auto movedColor = ColorConstexpr();

			[[maybe_unused]] constexpr std::uint8_t r = color.R();
			[[maybe_unused]] constexpr std::uint8_t g = color.G();
			[[maybe_unused]] constexpr std::uint8_t b = color.B();

			[[maybe_unused]] constexpr std::uint8_t min = color.Min();
			[[maybe_unused]] constexpr std::uint8_t max = color.Max();

			[[maybe_unused]] constexpr bool isBlack = color.IsBlack();
			[[maybe_unused]] constexpr bool isWhite = color.IsWhite();
			[[maybe_unused]] constexpr bool isTransparent = color.IsTransparent();

			[[maybe_unused]] constexpr auto span = color.Span();

			[[maybe_unused]] constexpr auto gotRgb = static_cast<PonyEngine::Math::RGBInt<std::uint8_t>>(color);
			[[maybe_unused]] constexpr auto vector = static_cast<PonyEngine::Math::Vector4<std::uint8_t>>(color);

			[[maybe_unused]] constexpr bool areEqual = defaultColor == color;
			[[maybe_unused]] constexpr bool areNorEqual = defaultColor != color;
		}
	};
}
