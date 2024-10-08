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
	TEST_CLASS(RGBTests)
	{
		TEST_METHOD(ValueTypeTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::RGB<float>::ValueType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{3}, PonyBase::Math::RGB<float>::ComponentCount);
			Assert::AreEqual(2.2f, PonyBase::Math::RGB<float>::GammaValue);
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyBase::Math::RGB<float>::Predefined::Red == PonyBase::Math::RGB<float>(1.f, 0.f, 0.f));
			Assert::IsTrue(PonyBase::Math::RGB<float>::Predefined::Green == PonyBase::Math::RGB<float>(0.f, 1.f, 0.f));
			Assert::IsTrue(PonyBase::Math::RGB<float>::Predefined::Blue == PonyBase::Math::RGB<float>(0.f, 0.f, 1.f));
			Assert::IsTrue(PonyBase::Math::RGB<float>::Predefined::Black == PonyBase::Math::RGB<float>(0.f, 0.f, 0.f));
			Assert::IsTrue(PonyBase::Math::RGB<float>::Predefined::White == PonyBase::Math::RGB<float>(1.f, 1.f, 1.f));
			Assert::IsTrue(PonyBase::Math::RGB<float>::Predefined::Gray == PonyBase::Math::RGB<float>(0.5f, 0.5f, 0.5f));
			Assert::IsTrue(PonyBase::Math::RGB<float>::Predefined::Yellow == PonyBase::Math::RGB<float>(1.f, 1.f, 0.f));
			Assert::IsTrue(PonyBase::Math::RGB<float>::Predefined::Magenta == PonyBase::Math::RGB<float>(1.f, 0.f, 1.f));
			Assert::IsTrue(PonyBase::Math::RGB<float>::Predefined::Cyan == PonyBase::Math::RGB<float>(0.f, 1.f, 1.f));
		}

		TEST_METHOD(ConstructorTest)
		{
			auto defaultColor = PonyBase::Math::RGB<float>();
			Assert::AreEqual(0.f, defaultColor.R());
			Assert::AreEqual(0.f, defaultColor.G());
			Assert::AreEqual(0.f, defaultColor.B());

			constexpr float r = 0.85f;
			constexpr float g = 0.16f;
			constexpr float b = 0.98f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());

			constexpr auto array = std::array<float, 3> { r, g, b };
			const auto arrayColor = PonyBase::Math::RGB<float>(array);
			Assert::AreEqual(r, arrayColor.R());
			Assert::AreEqual(g, arrayColor.G());
			Assert::AreEqual(b, arrayColor.B());

			constexpr std::uint8_t red = 60;
			constexpr std::uint8_t green = 170;
			constexpr std::uint8_t blue = 211;
			constexpr auto rgbInt = PonyBase::Math::RGBInt<std::uint8_t>(red, green, blue);
			auto convertedRGB = PonyBase::Math::RGB<float>(rgbInt);
			Assert::AreEqual(red / 255., static_cast<double>(convertedRGB.R()), 0.00001);
			Assert::AreEqual(green / 255., static_cast<double>(convertedRGB.G()), 0.00001);
			Assert::AreEqual(blue / 255., static_cast<double>(convertedRGB.B()), 0.00001);

			constexpr auto vector = PonyBase::Math::Vector3<float>(r, g, b);
			auto vectorColor = PonyBase::Math::RGB<float>(vector);
			Assert::AreEqual(r, vectorColor.R());
			Assert::AreEqual(g, vectorColor.G());
			Assert::AreEqual(b, vectorColor.B());

			const auto copiedColor = color;
			Assert::AreEqual(r, copiedColor.R());
			Assert::AreEqual(g, copiedColor.G());
			Assert::AreEqual(b, copiedColor.B());

			const auto movedColor = std::move(color);
			Assert::AreEqual(r, movedColor.R());
			Assert::AreEqual(g, movedColor.G());
			Assert::AreEqual(b, movedColor.B());
		}

		TEST_METHOD(AccessTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			constexpr auto cColor = PonyBase::Math::RGB<float>(r, g, b);
			Assert::AreEqual(r, cColor.R());
			Assert::AreEqual(g, cColor.G());
			Assert::AreEqual(b, cColor.B());
		}

		TEST_METHOD(SpanTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			Assert::AreEqual(r, color.Span()[0]);
			Assert::AreEqual(g, color.Span()[1]);
			Assert::AreEqual(b, color.Span()[2]);
			constexpr auto cColor = PonyBase::Math::RGB<float>(r, g, b);
			Assert::AreEqual(r, cColor.Span()[0]);
			Assert::AreEqual(g, cColor.Span()[1]);
			Assert::AreEqual(b, cColor.Span()[2]);
		}

		TEST_METHOD(GrayscaleTest)
		{
			constexpr float r = 0.85f;
			constexpr float g = 0.16f;
			constexpr float b = 0.98f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr double expectedGrayscale = 0.2126 * r + 0.7152 * g + 0.0722 * b;
			Assert::AreEqual(expectedGrayscale, static_cast<double>(color.Grayscale()), 0.00001);
		}

		TEST_METHOD(MinTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			Assert::AreEqual(0.211f, color.Min());
			constexpr auto cColor = PonyBase::Math::RGB<float>(r, g, b);
			Assert::AreEqual(0.211f, cColor.Min());
		}

		TEST_METHOD(MaxTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			Assert::AreEqual(0.69f, color.Max());
			constexpr auto cColor = PonyBase::Math::RGB<float>(r, g, b);
			Assert::AreEqual(0.69f, cColor.Max());
		}

		TEST_METHOD(MinMaxTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			auto pair = color.MinMax();
			Assert::AreEqual(b, pair.first);
			Assert::AreEqual(g, pair.second);
			constexpr auto cColor = PonyBase::Math::RGB<float>(r, g, b);
			auto cPair = cColor.MinMax();
			Assert::AreEqual(b, pair.first);
			Assert::AreEqual(g, pair.second);
		}

		TEST_METHOD(GammaTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.002f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			auto gamma = color.Gamma();
			Assert::AreEqual(0.708, static_cast<double>(gamma.R()), 0.001);
			Assert::AreEqual(0.836, static_cast<double>(gamma.G()), 0.001);
			Assert::AreEqual(0.026, static_cast<double>(gamma.B()), 0.001);
		}

		TEST_METHOD(LinearTest)
		{
			constexpr float r = 0.708f;
			constexpr float g = 0.836f;
			constexpr float b = 0.026f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			auto linear = color.Linear();
			Assert::AreEqual(0.49, static_cast<double>(linear.R()), 0.001);
			Assert::AreEqual(0.69, static_cast<double>(linear.G()), 0.001);
			Assert::AreEqual(0.002, static_cast<double>(linear.B()), 0.001);
		}

		TEST_METHOD(IsBlackTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			Assert::IsFalse(color.IsBlack());
			Assert::IsTrue(PonyBase::Math::RGBInt<std::uint8_t>::Predefined::Black.IsBlack());
		}

		TEST_METHOD(IsAlmostBlackTest)
		{
			auto color = PonyBase::Math::RGB<float>::Predefined::Black;
			Assert::IsTrue(color.IsAlmostBlack());
			Assert::IsTrue(color.IsAlmostBlack(0.5f));

			for (std::size_t i = 0; i < PonyBase::Math::RGB<float>::ComponentCount; ++i)
			{
				color[i] = std::nextafter(color[i], 0.5f);
				Assert::IsFalse(color.IsBlack());
				Assert::IsTrue(color.IsAlmostBlack());
				color[i] += 0.3f;
				Assert::IsFalse(color.IsAlmostBlack());
				Assert::IsTrue(color.IsAlmostBlack(0.5f));
				color[i] = PonyBase::Math::RGB<float>::Predefined::Black[i];
			}
		}

		TEST_METHOD(IsWhiteTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			Assert::IsFalse(color.IsWhite());
			Assert::IsTrue(PonyBase::Math::RGBInt<std::uint8_t>::Predefined::White.IsWhite());
		}

		TEST_METHOD(IsAlmostWhiteTest)
		{
			auto color = PonyBase::Math::RGB<float>::Predefined::White;
			Assert::IsTrue(color.IsAlmostWhite());
			Assert::IsTrue(color.IsAlmostWhite(0.5f));

			for (std::size_t i = 0; i < PonyBase::Math::RGB<float>::ComponentCount; ++i)
			{
				color[i] = std::nextafter(color[i], 0.5f);
				Assert::IsFalse(color.IsWhite());
				Assert::IsTrue(color.IsAlmostWhite());
				color[i] += 0.3f;
				Assert::IsFalse(color.IsAlmostWhite());
				Assert::IsTrue(color.IsAlmostWhite(0.5f));
				color[i] = PonyBase::Math::RGB<float>::Predefined::White[i];
			}
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			const float nan = std::numeric_limits<float>::quiet_NaN();
			Assert::IsTrue(color.IsFinite());
			color.R() = nan;
			Assert::IsFalse(color.IsFinite());
			color.R() = r;
			color.G() = nan;
			Assert::IsFalse(color.IsFinite());
			color.G() = g;
			color.B() = nan;
			Assert::IsFalse(color.IsFinite());
		}

		TEST_METHOD(SetTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>();
			color.Set(r, g, b);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			auto array = std::array<float, 3> { r, g, b };
			color = PonyBase::Math::RGB<float>();
			color.Set(array);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			const std::string string = color.ToString();
			Assert::AreEqual(std::format("(R: {}, G: {}, B: {})", color.R(), color.G(), color.B()), string);
			std::ostringstream ss;
			ss << color;
			Assert::AreEqual(string, ss.str());
		}

		TEST_METHOD(ToRGBTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			auto doubleColor = static_cast<PonyBase::Math::RGB<double>>(color);
			Assert::AreEqual(static_cast<double>(r), doubleColor.R());
			Assert::AreEqual(static_cast<double>(g), doubleColor.G());
			Assert::AreEqual(static_cast<double>(b), doubleColor.B());
		}

		TEST_METHOD(ToRGBIntTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			auto rgb = static_cast<PonyBase::Math::RGBInt<std::uint8_t>>(color);
			Assert::AreEqual(static_cast<std::uint8_t>(r * 255), rgb.R());
			Assert::AreEqual(static_cast<std::uint8_t>(g * 255), rgb.G());
			Assert::AreEqual(static_cast<std::uint8_t>(b * 255), rgb.B());
		}

		TEST_METHOD(ToVectorTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			auto vector = static_cast<PonyBase::Math::Vector3<float>>(color);
			Assert::AreEqual(r, vector.X());
			Assert::AreEqual(g, vector.Y());
			Assert::AreEqual(b, vector.Z());
		}

		TEST_METHOD(ComponentAccessTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			Assert::AreEqual(r, color[0]);
			Assert::AreEqual(g, color[1]);
			Assert::AreEqual(b, color[2]);

			constexpr auto colorC = PonyBase::Math::RGB<float>(r, g, b);
			Assert::AreEqual(r, colorC[0]);
			Assert::AreEqual(g, colorC[1]);
			Assert::AreEqual(b, colorC[2]);
		}

		TEST_METHOD(CopyAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			auto copiedColor = PonyBase::Math::RGB<float>();
			PonyBase::Math::RGB<float>& colorRef = copiedColor = color;
			Assert::AreEqual(r, copiedColor.R());
			Assert::AreEqual(g, copiedColor.G());
			Assert::AreEqual(b, copiedColor.B());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&copiedColor), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(MoveAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			auto movedColor = PonyBase::Math::RGB<float>();
			PonyBase::Math::RGB<float>& colorRef = movedColor = std::move(color);
			Assert::AreEqual(r, movedColor.R());
			Assert::AreEqual(g, movedColor.G());
			Assert::AreEqual(b, movedColor.B());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&movedColor), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(SumAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);
			PonyBase::Math::RGB<float>& colorRef = color += color1;
			Assert::AreEqual(r + r1, color.R());
			Assert::AreEqual(g + g1, color.G());
			Assert::AreEqual(b + b1, color.B());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(SubtractAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);
			PonyBase::Math::RGB<float>& colorRef = color -= color1;
			Assert::AreEqual(r - r1, color.R());
			Assert::AreEqual(g - g1, color.G());
			Assert::AreEqual(b - b1, color.B());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(ColorProductAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);
			PonyBase::Math::RGB<float>& colorRef = color *= color1;
			Assert::AreEqual(r * r1, color.R());
			Assert::AreEqual(g * g1, color.G());
			Assert::AreEqual(b * b1, color.B());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(ProductAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float multiplier = 4.f;
			PonyBase::Math::RGB<float>& colorRef = color *= multiplier;
			Assert::AreEqual(r * multiplier, color.R());
			Assert::AreEqual(g * multiplier, color.G());
			Assert::AreEqual(b * multiplier, color.B());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(ColorDivisionAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);
			PonyBase::Math::RGB<float>& colorRef = color /= color1;
			Assert::AreEqual(static_cast<double>(r / r1), static_cast<double>(color.R()), 0.00001);
			Assert::AreEqual(static_cast<double>(g / g1), static_cast<double>(color.G()), 0.00001);
			Assert::AreEqual(static_cast<double>(b / b1), static_cast<double>(color.B()), 0.00001);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(DivisionAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float divisor = 4.f;
			PonyBase::Math::RGB<float>& colorRef = color /= divisor;
			Assert::AreEqual(r / divisor, color.R());
			Assert::AreEqual(g / divisor, color.G());
			Assert::AreEqual(b / divisor, color.B());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(EqualTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			auto color = PonyBase::Math::RGB<float>(r, g, b);
			const auto otherColor = color;
			Assert::IsTrue(color == otherColor);
			Assert::IsFalse(color != otherColor);

			for (std::size_t i = 0; i < PonyBase::Math::RGB<float>::ComponentCount; ++i)
			{
				const float prevColor = color[i];
				color[i] += 1.f;
				Assert::IsFalse(color == otherColor);
				Assert::IsTrue(color != otherColor);
				color[i] = prevColor;
			}
		}

		TEST_METHOD(DistanceTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);
			Assert::AreEqual(0.45, static_cast<double>(PonyBase::Math::DistanceSquared(color, color1)), 0.001);
			Assert::AreEqual(0.671, static_cast<double>(PonyBase::Math::Distance(color, color1)), 0.001);
		}

		TEST_METHOD(MinCombinedTest)
		{
			constexpr float r = 0.8;
			constexpr float g = 0.12;
			constexpr float b = 0.1;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.10;
			constexpr float g1 = 0.6;
			constexpr float b1 = 0.1;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);
			auto min = PonyBase::Math::Min(color, color1);
			Assert::AreEqual(r1, min.R());
			Assert::AreEqual(g, min.G());
			Assert::AreEqual(b, min.B());
		}

		TEST_METHOD(MaxCombinedTest)
		{
			constexpr float r = 0.8;
			constexpr float g = 0.12;
			constexpr float b = 0.1;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.10;
			constexpr float g1 = 0.6;
			constexpr float b1 = 0.1;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);
			auto max = PonyBase::Math::Max(color, color1);
			Assert::AreEqual(r, max.R());
			Assert::AreEqual(g1, max.G());
			Assert::AreEqual(b, max.B());
		}

		TEST_METHOD(ClampTest)
		{
			constexpr float r = 0.8;
			constexpr float g = 0.2;
			constexpr float b = 0.1;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.9;
			constexpr float g1 = 0.6;
			constexpr float b1 = 0.1;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);
			constexpr float r2 = 0.85;
			constexpr float g2 = 0.8;
			constexpr float b2 = 0.5;
			constexpr auto color2 = PonyBase::Math::RGB<float>(r2, g2, b2);

			auto clamped = PonyBase::Math::Clamp(color2, color, color1);
			Assert::AreEqual(r2, clamped.R());
			Assert::AreEqual(g1, clamped.G());
			Assert::AreEqual(b, clamped.B());
		}

		TEST_METHOD(LerpTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);

			PonyBase::Math::RGB<float> lerped = PonyBase::Math::Lerp(color, color1, 0.f);
			Assert::AreEqual(r, lerped.R());
			Assert::AreEqual(g, lerped.G());
			Assert::AreEqual(b, lerped.B());

			lerped = PonyBase::Math::Lerp(color, color1, 1.f);
			Assert::AreEqual(static_cast<double>(r1), static_cast<double>(lerped.R()), 0.0001);
			Assert::AreEqual(static_cast<double>(g1), static_cast<double>(lerped.G()), 0.0001);
			Assert::AreEqual(static_cast<double>(b1), static_cast<double>(lerped.B()), 0.0001);

			lerped = PonyBase::Math::Lerp(color, color1, 0.5f);
			Assert::AreEqual(0.34, static_cast<double>(lerped.R()), 0.0001);
			Assert::AreEqual(0.39, static_cast<double>(lerped.G()), 0.0001);
			Assert::AreEqual(0.215, static_cast<double>(lerped.B()), 0.0001);

			lerped = PonyBase::Math::Lerp(color, color1, 2.f);
			Assert::AreEqual(-0.11, static_cast<double>(lerped.R()), 0.0001);
			Assert::AreEqual(-0.51, static_cast<double>(lerped.G()), 0.0001);
			Assert::AreEqual(0.227, static_cast<double>(lerped.B()), 0.0001);

			lerped = PonyBase::Math::Lerp(color, color1, -1.f);
			Assert::AreEqual(0.79, static_cast<double>(lerped.R()), 0.0001);
			Assert::AreEqual(1.29, static_cast<double>(lerped.G()), 0.0001);
			Assert::AreEqual(0.203, static_cast<double>(lerped.B()), 0.0001);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			PonyBase::Math::RGB<float> colorL = color;

			for (std::size_t i = 0; i < PonyBase::Math::RGB<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual(colorL, color));
				colorL[i] = std::nextafter(colorL[i], 0.f);
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual(colorL, color));
				colorL[i] += 1;
				Assert::IsFalse(PonyBase::Math::AreAlmostEqual(colorL, color));
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual(colorL, color, 5.f));
				colorL[i] = color[i];
			}
		}

		TEST_METHOD(SumTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);
			auto sum = color + color1;
			Assert::AreEqual(r + r1, sum.R());
			Assert::AreEqual(g + g1, sum.G());
			Assert::AreEqual(b + b1, sum.B());
		}

		TEST_METHOD(DifferenceTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);
			auto difference = color - color1;
			Assert::AreEqual(r - r1, difference.R());
			Assert::AreEqual(g - g1, difference.G());
			Assert::AreEqual(b - b1, difference.B());
		}

		TEST_METHOD(ProductColorTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);
			auto product = color * color1;
			Assert::AreEqual(r * r1, product.R());
			Assert::AreEqual(g * g1, product.G());
			Assert::AreEqual(b * b1, product.B());
		}

		TEST_METHOD(ProductTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float multiplier = 2.f;

			auto product = color * multiplier;
			Assert::AreEqual(r * multiplier, product.R());
			Assert::AreEqual(g * multiplier, product.G());
			Assert::AreEqual(b * multiplier, product.B());

			product = PonyBase::Math::RGB<float>();
			product = multiplier * color;
			Assert::AreEqual(r * multiplier, product.R());
			Assert::AreEqual(g * multiplier, product.G());
			Assert::AreEqual(b * multiplier, product.B());
		}

		TEST_METHOD(DivisionColorTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr auto color1 = PonyBase::Math::RGB<float>(r1, g1, b1);
			auto quotient = color / color1;
			Assert::AreEqual(r / r1, quotient.R());
			Assert::AreEqual(g / g1, quotient.G());
			Assert::AreEqual(b / b1, quotient.B());
		}

		TEST_METHOD(DivisionTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr auto color = PonyBase::Math::RGB<float>(r, g, b);
			constexpr float divisor = 3.f;
			auto quotient = color / divisor;
			Assert::AreEqual(r / divisor, quotient.R());
			Assert::AreEqual(g / divisor, quotient.G());
			Assert::AreEqual(b / divisor, quotient.B());
		}

		static constexpr PonyBase::Math::RGB<float> RGBConstexpr()
		{
			auto color = PonyBase::Math::RGB<float>(0.3f, 0.4f, 0.6f);
			auto copiedColor = color;
			auto movedColor = std::move(color);

			copiedColor.R() *= 2.f;
			copiedColor.G() /= 2.f;
			copiedColor.B() += 1.f;

			movedColor.Span()[0] *= 2.5f;

			copiedColor.Min() /= 3.f;
			copiedColor.Max() *= 2.f;
			[[maybe_unused]] const auto minMax = movedColor.MinMax();

			movedColor.Set(0.1f, 0.69f, 0.228f);
			movedColor.Set(copiedColor.Span());

			movedColor[0] *= 1.5f;
			auto anotherColor = PonyBase::Math::RGB<float>();
			anotherColor = copiedColor;
			movedColor = std::move(anotherColor);

			movedColor += copiedColor;
			movedColor -= copiedColor;
			movedColor *= copiedColor;
			movedColor *= 2.f;
			movedColor /= copiedColor;
			movedColor /= 2.f;

			return movedColor;
		}

		TEST_METHOD(ConstexprTest)
		{
			[[maybe_unused]] constexpr auto defaultColor = PonyBase::Math::RGB<float>();
			[[maybe_unused]] constexpr auto color = PonyBase::Math::RGB<float>(0.3f, 0.4f, 0.6f);
			[[maybe_unused]] constexpr auto spanColor = PonyBase::Math::RGB<float>(std::array<float, 3>{0.4f, 0.1f, 0.2f});
			[[maybe_unused]] constexpr auto rgbIntColor = PonyBase::Math::RGB<float>(PonyBase::Math::RGBInt<unsigned int>(54, 38, 90));
			[[maybe_unused]] constexpr auto vectorColor = PonyBase::Math::RGB<float>(PonyBase::Math::Vector3<float>(0.4f, 0.69f, 0.228f));
			[[maybe_unused]] constexpr auto movedColor = RGBConstexpr();

			[[maybe_unused]] constexpr float r = color.R();
			[[maybe_unused]] constexpr float g = color.G();
			[[maybe_unused]] constexpr float b = color.B();

			[[maybe_unused]] constexpr auto spanElement = color.Span()[0];

			[[maybe_unused]] constexpr auto grayscale = color.Grayscale();

			[[maybe_unused]] constexpr auto min = color.Min();
			[[maybe_unused]] constexpr auto max = color.Max();
			[[maybe_unused]] constexpr std::pair<float, float> minMax = color.MinMax();

			[[maybe_unused]] constexpr bool isBlack = color.IsBlack();
			[[maybe_unused]] constexpr bool isAlmostBlack = color.IsAlmostBlack();
			[[maybe_unused]] constexpr bool isWhite = color.IsWhite();
			[[maybe_unused]] constexpr bool isAlmostWhite = color.IsAlmostWhite();

			[[maybe_unused]] constexpr auto rgb = static_cast<PonyBase::Math::RGB<double>>(color);
			[[maybe_unused]] constexpr auto rgbInt = static_cast<PonyBase::Math::RGBInt<unsigned int>>(color);

			[[maybe_unused]] constexpr auto vector = static_cast<PonyBase::Math::Vector3<float>>(color);

			[[maybe_unused]] constexpr float component = color[0];

			[[maybe_unused]] constexpr bool isEqual = color == defaultColor;
			[[maybe_unused]] constexpr bool isNotEqual = color != defaultColor;

			[[maybe_unused]] constexpr float distanceSquared = PonyBase::Math::DistanceSquared(color, defaultColor);

			[[maybe_unused]] constexpr auto minCombined = PonyBase::Math::Min(defaultColor, spanColor);
			[[maybe_unused]] constexpr auto maxCombined = PonyBase::Math::Max(defaultColor, spanColor);
			[[maybe_unused]] constexpr auto clamped = PonyBase::Math::Clamp(color, defaultColor, spanColor);
			[[maybe_unused]] constexpr auto lerp = PonyBase::Math::Lerp(color, defaultColor, 0.5f);

			[[maybe_unused]] constexpr bool areAlmostEqual = PonyBase::Math::AreAlmostEqual(color, defaultColor);

			[[maybe_unused]] constexpr auto sum = color + defaultColor;
			[[maybe_unused]] constexpr auto difference = color - defaultColor;
			[[maybe_unused]] constexpr auto productColor = color * defaultColor;
			[[maybe_unused]] constexpr auto productR = color * 3.f;
			[[maybe_unused]] constexpr auto productL = 3.f * color;
			[[maybe_unused]] constexpr auto quotient = color / spanColor;
			[[maybe_unused]] constexpr auto quotientN = color / 3.f;
		}
	};
}
