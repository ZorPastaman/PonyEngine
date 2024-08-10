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
	TEST_CLASS(RGBIntTests)
	{
		TEST_METHOD(ValueTypeTest)
		{
			Assert::IsTrue(std::is_same_v<std::uint8_t, PonyEngine::Math::RGBInt<std::uint8_t>::ValueType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::numeric_limits<std::uint8_t>::max(), PonyEngine::Math::RGBInt<std::uint8_t>::MaxValue);
			Assert::AreEqual(std::size_t{3}, PonyEngine::Math::RGBInt<std::uint8_t>::ComponentCount);
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyEngine::Math::RGBInt<std::uint8_t>::Predefined::Red == PonyEngine::Math::RGBInt<std::uint8_t>(255, 0, 0));
			Assert::IsTrue(PonyEngine::Math::RGBInt<std::uint8_t>::Predefined::Green == PonyEngine::Math::RGBInt<std::uint8_t>(0, 255, 0));
			Assert::IsTrue(PonyEngine::Math::RGBInt<std::uint8_t>::Predefined::Blue == PonyEngine::Math::RGBInt<std::uint8_t>(0, 0, 255));
			Assert::IsTrue(PonyEngine::Math::RGBInt<std::uint8_t>::Predefined::Black == PonyEngine::Math::RGBInt<std::uint8_t>(0, 0, 0));
			Assert::IsTrue(PonyEngine::Math::RGBInt<std::uint8_t>::Predefined::White == PonyEngine::Math::RGBInt<std::uint8_t>(255, 255, 255));
			Assert::IsTrue(PonyEngine::Math::RGBInt<std::uint8_t>::Predefined::Yellow == PonyEngine::Math::RGBInt<std::uint8_t>(255, 255, 0));
			Assert::IsTrue(PonyEngine::Math::RGBInt<std::uint8_t>::Predefined::Magenta == PonyEngine::Math::RGBInt<std::uint8_t>(255, 0, 255));
			Assert::IsTrue(PonyEngine::Math::RGBInt<std::uint8_t>::Predefined::Cyan == PonyEngine::Math::RGBInt<std::uint8_t>(0, 255, 255));
		}

		TEST_METHOD(ConstructorTest)
		{
			auto defaultColor = PonyEngine::Math::RGBInt<std::uint8_t>();
			Assert::AreEqual(std::uint8_t{0}, defaultColor.R());
			Assert::AreEqual(std::uint8_t{0}, defaultColor.G());
			Assert::AreEqual(std::uint8_t{0}, defaultColor.B());

			constexpr std::uint8_t r = 56;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 11;
			auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());

			auto array = std::array{r, g, b};
			const auto arrayColor = PonyEngine::Math::RGBInt<std::uint8_t>(array.data());
			Assert::AreEqual(r, arrayColor.R());
			Assert::AreEqual(g, arrayColor.G());
			Assert::AreEqual(b, arrayColor.B());

			constexpr auto vector = PonyEngine::Math::Vector3<std::uint8_t>(r, g, b);
			auto vectorColor = PonyEngine::Math::RGBInt<std::uint8_t>(vector);
			Assert::AreEqual(r, vectorColor.R());
			Assert::AreEqual(g, vectorColor.G());
			Assert::AreEqual(b, vectorColor.B());

			auto copiedColor = color;
			Assert::AreEqual(r, copiedColor.R());
			Assert::AreEqual(g, copiedColor.G());
			Assert::AreEqual(b, copiedColor.B());

			auto movedColor = std::move(color);
			Assert::AreEqual(r, movedColor.R());
			Assert::AreEqual(g, movedColor.G());
			Assert::AreEqual(b, movedColor.B());
		}

		TEST_METHOD(AccessTest)
		{
			constexpr std::uint8_t r = 49;
			constexpr std::uint8_t g = 69;
			constexpr std::uint8_t b = 211;
			auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			constexpr auto cColor = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::AreEqual(r, cColor.R());
			Assert::AreEqual(g, cColor.G());
			Assert::AreEqual(b, cColor.B());
		}

		TEST_METHOD(DataTest)
		{
			constexpr std::uint8_t r = 69;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 228;
			auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::AreEqual(r, color.Data()[0]);
			Assert::AreEqual(g, color.Data()[1]);
			Assert::AreEqual(b, color.Data()[2]);
			constexpr auto cColor = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::AreEqual(r, cColor.Data()[0]);
			Assert::AreEqual(g, cColor.Data()[1]);
			Assert::AreEqual(b, cColor.Data()[2]);
		}

		TEST_METHOD(MinTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::AreEqual(std::uint8_t{1}, color.Min());
			constexpr auto cColor = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::AreEqual(std::uint8_t{1}, cColor.Min());
		}

		TEST_METHOD(MaxTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::AreEqual(std::uint8_t{211}, color.Max());
			constexpr auto cColor = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::AreEqual(std::uint8_t{211}, cColor.Max());
		}

		TEST_METHOD(IsBlackTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::IsFalse(color.IsBlack());
			Assert::IsTrue(PonyEngine::Math::RGBInt<std::uint8_t>::Predefined::Black.IsBlack());
		}

		TEST_METHOD(IsWhiteTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::IsFalse(color.IsWhite());
			Assert::IsTrue(PonyEngine::Math::RGBInt<std::uint8_t>::Predefined::White.IsWhite());
		}

		TEST_METHOD(SetTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			auto color = PonyEngine::Math::RGBInt<std::uint8_t>();
			color.Set(r, g, b);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			color = PonyEngine::Math::RGBInt<std::uint8_t>();
			constexpr std::array<std::uint8_t, 3> array = {r, g, b};
			color.Set(array.data());
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
		}

		TEST_METHOD(ToArrayTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			const auto array = color.ToArray();
			Assert::AreEqual(r, array[0]);
			Assert::AreEqual(g, array[1]);
			Assert::AreEqual(b, array[2]);
			std::uint8_t cArray[3];
			color.ToArray(cArray);
			Assert::AreEqual(r, cArray[0]);
			Assert::AreEqual(g, cArray[1]);
			Assert::AreEqual(b, cArray[2]);
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			const std::string string = color.ToString();
			Assert::AreEqual(std::format("(R: {}, G: {}, B: {})", r, g, b), string);
			std::ostringstream ss;
			ss << color;
			Assert::AreEqual(string, ss.str());
		}

		TEST_METHOD(ToVectorTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			constexpr auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			const auto vector = static_cast<PonyEngine::Math::Vector3<std::uint8_t>>(color);
			Assert::AreEqual(r, vector.X());
			Assert::AreEqual(g, vector.Y());
			Assert::AreEqual(b, vector.Z());
		}

		TEST_METHOD(AccessOperatorTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::AreEqual(r, color[0]);
			Assert::AreEqual(g, color[1]);
			Assert::AreEqual(b, color[2]);
			constexpr auto cColor = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			Assert::AreEqual(r, cColor[0]);
			Assert::AreEqual(g, cColor[1]);
			Assert::AreEqual(b, cColor[2]);
		}

		TEST_METHOD(AssignmentOperatorsTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			constexpr std::uint8_t otherR = 100;
			constexpr std::uint8_t otherG = 111;
			constexpr std::uint8_t otherB = 69;
			auto otherColor = PonyEngine::Math::RGBInt<std::uint8_t>(otherR, otherG, otherB);
			PonyEngine::Math::RGBInt<std::uint8_t>& result = color = otherColor;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&result));
			Assert::AreEqual(otherR, color.R());
			Assert::AreEqual(otherG, color.G());
			Assert::AreEqual(otherB, color.B());
			color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);
			PonyEngine::Math::RGBInt<std::uint8_t>& otherResult = otherColor = std::move(color);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&otherColor), reinterpret_cast<std::uintptr_t>(&otherResult));
			Assert::AreEqual(r, otherColor.R());
			Assert::AreEqual(g, otherColor.G());
			Assert::AreEqual(b, otherColor.B());
		}

		TEST_METHOD(EqualTest)
		{
			constexpr std::uint8_t r = 211;
			constexpr std::uint8_t g = 200;
			constexpr std::uint8_t b = 1;
			auto color = PonyEngine::Math::RGBInt<std::uint8_t>(r, g, b);

			for (std::size_t i = 0; i < PonyEngine::Math::RGBInt<std::uint8_t>::ComponentCount; ++i)
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

		static constexpr PonyEngine::Math::RGBInt<std::uint8_t> ColorConstexpr()
		{
			auto color = PonyEngine::Math::RGBInt<std::uint8_t>(3, 250, 128);
			auto copiedColor = color;
			auto movedColor = std::move(color);

			[[maybe_unused]] std::uint8_t r = movedColor.R();
			[[maybe_unused]] std::uint8_t g = movedColor.G();
			[[maybe_unused]] std::uint8_t b = movedColor.B();

			[[maybe_unused]] std::uint8_t* data = movedColor.Data();
			[[maybe_unused]] const std::uint8_t* copiedData = copiedColor.Data();

			[[maybe_unused]] const std::uint8_t min = movedColor.Min();
			[[maybe_unused]] const std::uint8_t max = movedColor.Max();

			std::uint8_t array[3];
			movedColor.ToArray(array);

			movedColor.Set(124, 21, 90);
			movedColor.Set(array);

			[[maybe_unused]] auto component = movedColor[1];

			copiedColor = movedColor;
			movedColor = std::move(copiedColor);

			return movedColor;
		}

		TEST_METHOD(ConstexprTest)
		{
			[[maybe_unused]] constexpr auto defaultColor = PonyEngine::Math::RGBInt<std::uint8_t>();
			[[maybe_unused]] constexpr auto color = PonyEngine::Math::RGBInt<std::uint8_t>(3, 250, 128);
			constexpr auto array = std::array{color.R(), color.G(), color.B()};
			[[maybe_unused]] constexpr auto arrayColor = PonyEngine::Math::RGBInt<std::uint8_t>(array.data());
			[[maybe_unused]] constexpr auto copiedColor = color;
			[[maybe_unused]] constexpr auto movedColor = ColorConstexpr();

			[[maybe_unused]] constexpr std::uint8_t r = color.R();
			[[maybe_unused]] constexpr std::uint8_t g = color.G();
			[[maybe_unused]] constexpr std::uint8_t b = color.B();

			[[maybe_unused]] constexpr std::uint8_t min = color.Min();
			[[maybe_unused]] constexpr std::uint8_t max = color.Max();

			[[maybe_unused]] constexpr bool isBlack = color.IsBlack();
			[[maybe_unused]] constexpr bool isWhite = color.IsWhite();

			[[maybe_unused]] constexpr auto colorArray = color.ToArray();

			[[maybe_unused]] constexpr auto vector = static_cast<PonyEngine::Math::Vector3<std::uint8_t>>(color);

			[[maybe_unused]] constexpr bool areEqual = defaultColor == color;
			[[maybe_unused]] constexpr bool areNorEqual = defaultColor != color;
		}
	};
}
