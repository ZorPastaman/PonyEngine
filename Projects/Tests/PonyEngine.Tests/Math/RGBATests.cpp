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
	TEST_CLASS(RGBATests)
	{
		TEST_METHOD(ValueTypeTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::RGBA<float>::ValueType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{4}, PonyEngine::Math::RGBA<float>::ComponentCount);
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyEngine::Math::RGBA<float>::Predefined::Red == PonyEngine::Math::RGBA<float>(1.f, 0.f, 0.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::RGBA<float>::Predefined::Green == PonyEngine::Math::RGBA<float>(0.f, 1.f, 0.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::RGBA<float>::Predefined::Blue == PonyEngine::Math::RGBA<float>(0.f, 0.f, 1.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::RGBA<float>::Predefined::Black == PonyEngine::Math::RGBA<float>(0.f, 0.f, 0.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::RGBA<float>::Predefined::White == PonyEngine::Math::RGBA<float>(1.f, 1.f, 1.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::RGBA<float>::Predefined::Clear == PonyEngine::Math::RGBA<float>(0.f, 0.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::RGBA<float>::Predefined::Gray == PonyEngine::Math::RGBA<float>(0.5f, 0.5f, 0.5f, 1.f));
			Assert::IsTrue(PonyEngine::Math::RGBA<float>::Predefined::Yellow == PonyEngine::Math::RGBA<float>(1.f, 1.f, 0.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::RGBA<float>::Predefined::Magenta == PonyEngine::Math::RGBA<float>(1.f, 0.f, 1.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::RGBA<float>::Predefined::Cyan == PonyEngine::Math::RGBA<float>(0.f, 1.f, 1.f, 1.f));
		}

		TEST_METHOD(ConstructorTest)
		{
			auto defaultColor = PonyEngine::Math::RGBA<float>();
			Assert::AreEqual(0.f, defaultColor.R());
			Assert::AreEqual(0.f, defaultColor.G());
			Assert::AreEqual(0.f, defaultColor.B());
			Assert::AreEqual(0.f, defaultColor.A());

			constexpr float r = 0.85f;
			constexpr float g = 0.16f;
			constexpr float b = 0.98f;
			constexpr float a = 0.95f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			Assert::AreEqual(a, color.A());

			constexpr auto array = std::array<float, 4> { r, g, b, a };
			const auto arrayColor = PonyEngine::Math::RGBA<float>(array);
			Assert::AreEqual(r, arrayColor.R());
			Assert::AreEqual(g, arrayColor.G());
			Assert::AreEqual(b, arrayColor.B());
			Assert::AreEqual(a, arrayColor.A());

			constexpr auto rgb = PonyEngine::Math::RGB<float>(r, g, b);
			auto rgba = PonyEngine::Math::RGBA<float>(rgb, a);
			Assert::AreEqual(r, rgba.R());
			Assert::AreEqual(g, rgba.G());
			Assert::AreEqual(b, rgba.B());
			Assert::AreEqual(a, rgba.A());

			constexpr std::uint8_t red = 60;
			constexpr std::uint8_t green = 170;
			constexpr std::uint8_t blue = 211;
			constexpr std::uint8_t alpha = 220;
			constexpr auto rgbaInt = PonyEngine::Math::RGBAInt<std::uint8_t>(red, green, blue, alpha);
			auto convertedRGBA = PonyEngine::Math::RGBA<float>(rgbaInt);
			Assert::AreEqual(red / 255., static_cast<double>(convertedRGBA.R()), 0.00001);
			Assert::AreEqual(green / 255., static_cast<double>(convertedRGBA.G()), 0.00001);
			Assert::AreEqual(blue / 255., static_cast<double>(convertedRGBA.B()), 0.00001);
			Assert::AreEqual(alpha / 255., static_cast<double>(convertedRGBA.A()), 0.00001);

			constexpr auto rgbInt = PonyEngine::Math::RGBInt<std::uint8_t>(red, green, blue);
			auto convertedRGB = PonyEngine::Math::RGBA<float>(rgbInt, a);
			Assert::AreEqual(red / 255., static_cast<double>(convertedRGB.R()), 0.00001);
			Assert::AreEqual(green / 255., static_cast<double>(convertedRGB.G()), 0.00001);
			Assert::AreEqual(blue / 255., static_cast<double>(convertedRGB.B()), 0.00001);
			Assert::AreEqual(a, convertedRGB.A());

			constexpr auto vector = PonyEngine::Math::Vector4<float>(r, g, b, a);
			auto vectorColor = PonyEngine::Math::RGBA<float>(vector);
			Assert::AreEqual(r, vectorColor.R());
			Assert::AreEqual(g, vectorColor.G());
			Assert::AreEqual(b, vectorColor.B());
			Assert::AreEqual(a, vectorColor.A());

			const auto copiedColor = color;
			Assert::AreEqual(r, copiedColor.R());
			Assert::AreEqual(g, copiedColor.G());
			Assert::AreEqual(b, copiedColor.B());
			Assert::AreEqual(a, copiedColor.A());

			const auto movedColor = std::move(color);
			Assert::AreEqual(r, movedColor.R());
			Assert::AreEqual(g, movedColor.G());
			Assert::AreEqual(b, movedColor.B());
			Assert::AreEqual(a, movedColor.A());
		}

		TEST_METHOD(AccessTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			Assert::AreEqual(a, color.A());
			constexpr auto cColor = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::AreEqual(r, cColor.R());
			Assert::AreEqual(g, cColor.G());
			Assert::AreEqual(b, cColor.B());
			Assert::AreEqual(a, cColor.A());
		}

		TEST_METHOD(SpanTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::AreEqual(r, color.Span()[0]);
			Assert::AreEqual(g, color.Span()[1]);
			Assert::AreEqual(b, color.Span()[2]);
			Assert::AreEqual(a, color.Span()[3]);
			constexpr auto cColor = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::AreEqual(r, cColor.Span()[0]);
			Assert::AreEqual(g, cColor.Span()[1]);
			Assert::AreEqual(b, cColor.Span()[2]);
			Assert::AreEqual(a, cColor.Span()[3]);
		}

		TEST_METHOD(GrayscaleTest)
		{
			constexpr float r = 0.85f;
			constexpr float g = 0.16f;
			constexpr float b = 0.98f;
			constexpr float a = 0.95f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr double expectedGrayscale = 0.2126 * r + 0.7152 * g + 0.0722 * b;
			Assert::AreEqual(expectedGrayscale, static_cast<double>(color.Grayscale()), 0.00001);
		}

		TEST_METHOD(MinTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::AreEqual(0.166f, color.Min());
			constexpr auto cColor = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::AreEqual(0.166f, cColor.Min());
		}

		TEST_METHOD(MaxTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::AreEqual(0.69f, color.Max());
			constexpr auto cColor = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::AreEqual(0.69f, cColor.Max());
		}

		TEST_METHOD(GammaTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.002f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			auto gamma = color.Gamma();
			Assert::AreEqual(0.708, static_cast<double>(gamma.R()), 0.001);
			Assert::AreEqual(0.836, static_cast<double>(gamma.G()), 0.001);
			Assert::AreEqual(0.026, static_cast<double>(gamma.B()), 0.001);
			Assert::AreEqual(a, gamma.A());
		}

		TEST_METHOD(LinearTest)
		{
			constexpr float r = 0.708f;
			constexpr float g = 0.836f;
			constexpr float b = 0.026f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			auto linear = color.Linear();
			Assert::AreEqual(0.49, static_cast<double>(linear.R()), 0.001);
			Assert::AreEqual(0.69, static_cast<double>(linear.G()), 0.001);
			Assert::AreEqual(0.002, static_cast<double>(linear.B()), 0.001);
			Assert::AreEqual(a, linear.A());
		}

		TEST_METHOD(IsBlackTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::IsFalse(color.IsBlack());
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::Black.IsBlack());
		}

		TEST_METHOD(IsAlmostBlackTest)
		{
			auto color = PonyEngine::Math::RGBA<float>::Predefined::Black;
			Assert::IsTrue(color.IsAlmostBlack());
			Assert::IsTrue(color.IsAlmostBlack(0.5f));

			for (std::size_t i = 0; i < PonyEngine::Math::RGBA<float>::ComponentCount; ++i)
			{
				color[i] = std::nextafter(color[i], 0.5f);
				Assert::IsFalse(color.IsBlack());
				Assert::IsTrue(color.IsAlmostBlack());
				color[i] += 0.3f;
				Assert::IsFalse(color.IsAlmostBlack());
				Assert::IsTrue(color.IsAlmostBlack(0.5f));
				color[i] = PonyEngine::Math::RGBA<float>::Predefined::Black[i];
			}
		}

		TEST_METHOD(IsWhiteTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::IsFalse(color.IsWhite());
			Assert::IsTrue(PonyEngine::Math::RGBAInt<std::uint8_t>::Predefined::White.IsWhite());
		}

		TEST_METHOD(IsAlmostWhiteTest)
		{
			auto color = PonyEngine::Math::RGBA<float>::Predefined::White;
			Assert::IsTrue(color.IsAlmostWhite());
			Assert::IsTrue(color.IsAlmostWhite(0.5f));

			for (std::size_t i = 0; i < PonyEngine::Math::RGBA<float>::ComponentCount; ++i)
			{
				color[i] = std::nextafter(color[i], 0.5f);
				Assert::IsFalse(color.IsWhite());
				Assert::IsTrue(color.IsAlmostWhite());
				color[i] += 0.3f;
				Assert::IsFalse(color.IsAlmostWhite());
				Assert::IsTrue(color.IsAlmostWhite(0.5f));
				color[i] = PonyEngine::Math::RGBA<float>::Predefined::White[i];
			}
		}

		TEST_METHOD(IsTransparent)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::IsFalse(color.IsTransparent());
			color.A() = 0.f;
			Assert::IsTrue(color.IsTransparent());
			Assert::IsTrue(PonyEngine::Math::RGBA<float>::Predefined::Clear.IsTransparent());
		}

		TEST_METHOD(IsAlmostTransparent)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::IsFalse(color.IsAlmostTransparent());
			Assert::IsTrue(color.IsAlmostTransparent(0.5f));
			color.A() = 0.f;
			Assert::IsTrue(color.IsAlmostTransparent());
			Assert::IsTrue(color.IsAlmostTransparent(0.5f));
			Assert::IsTrue(PonyEngine::Math::RGBA<float>::Predefined::Clear.IsAlmostTransparent());
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
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
			color.A() = a;
			color.A() = nan;
			Assert::IsFalse(color.IsFinite());
		}

		TEST_METHOD(SetTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>();
			color.Set(r, g, b, a);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			Assert::AreEqual(a, color.A());
			auto array = std::array<float, 4> { r, g, b, a };
			color = PonyEngine::Math::RGBA<float>();
			color.Set(array);
			Assert::AreEqual(r, color.R());
			Assert::AreEqual(g, color.G());
			Assert::AreEqual(b, color.B());
			Assert::AreEqual(a, color.A());
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			const std::string string = color.ToString();
			Assert::AreEqual(std::format("(R: {}, G: {}, B: {}, A: {})", color.R(), color.G(), color.B(), color.A()), string);
			std::ostringstream ss;
			ss << color;
			Assert::AreEqual(string, ss.str());
		}

		TEST_METHOD(ToRGBATest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			auto doubleColor = static_cast<PonyEngine::Math::RGBA<double>>(color);
			Assert::AreEqual(static_cast<double>(r), doubleColor.R());
			Assert::AreEqual(static_cast<double>(g), doubleColor.G());
			Assert::AreEqual(static_cast<double>(b), doubleColor.B());
			Assert::AreEqual(static_cast<double>(a), doubleColor.A());
		}

		TEST_METHOD(ToRGBTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			auto rgb = static_cast<PonyEngine::Math::RGB<float>>(color);
			Assert::AreEqual(r, rgb.R());
			Assert::AreEqual(g, rgb.G());
			Assert::AreEqual(b, rgb.B());
		}

		TEST_METHOD(ToRGBIntTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			auto rgb = static_cast<PonyEngine::Math::RGBInt<std::uint8_t>>(color);
			Assert::AreEqual(static_cast<std::uint8_t>(r * 255), rgb.R());
			Assert::AreEqual(static_cast<std::uint8_t>(g * 255), rgb.G());
			Assert::AreEqual(static_cast<std::uint8_t>(b * 255), rgb.B());
		}

		TEST_METHOD(ToRGBAIntTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			auto rgba = static_cast<PonyEngine::Math::RGBAInt<std::uint8_t>>(color);
			Assert::AreEqual(static_cast<std::uint8_t>(r * 255), rgba.R());
			Assert::AreEqual(static_cast<std::uint8_t>(g * 255), rgba.G());
			Assert::AreEqual(static_cast<std::uint8_t>(b * 255), rgba.B());
			Assert::AreEqual(static_cast<std::uint8_t>(a * 255), rgba.A());
		}

		TEST_METHOD(ToVectorTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			auto vector = static_cast<PonyEngine::Math::Vector4<float>>(color);
			Assert::AreEqual(r, vector.X());
			Assert::AreEqual(g, vector.Y());
			Assert::AreEqual(b, vector.Z());
			Assert::AreEqual(a, vector.W());
		}

		TEST_METHOD(ComponentAccessTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::AreEqual(r, color[0]);
			Assert::AreEqual(g, color[1]);
			Assert::AreEqual(b, color[2]);
			Assert::AreEqual(a, color[3]);

			constexpr auto colorC = PonyEngine::Math::RGBA<float>(r, g, b, a);
			Assert::AreEqual(r, colorC[0]);
			Assert::AreEqual(g, colorC[1]);
			Assert::AreEqual(b, colorC[2]);
			Assert::AreEqual(a, colorC[3]);
		}

		TEST_METHOD(CopyAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			auto copiedColor = PonyEngine::Math::RGBA<float>();
			PonyEngine::Math::RGBA<float>& colorRef = copiedColor = color;
			Assert::AreEqual(r, copiedColor.R());
			Assert::AreEqual(g, copiedColor.G());
			Assert::AreEqual(b, copiedColor.B());
			Assert::AreEqual(a, copiedColor.A());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&copiedColor), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(MoveAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			auto movedColor = PonyEngine::Math::RGBA<float>();
			PonyEngine::Math::RGBA<float>& colorRef = movedColor = std::move(color);
			Assert::AreEqual(r, movedColor.R());
			Assert::AreEqual(g, movedColor.G());
			Assert::AreEqual(b, movedColor.B());
			Assert::AreEqual(a, movedColor.A());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&movedColor), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(SumAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr float a1 = 0.366f;
			constexpr auto color1 = PonyEngine::Math::RGBA<float>(r1, g1, b1, a1);
			PonyEngine::Math::RGBA<float>& colorRef = color += color1;
			Assert::AreEqual(r + r1, color.R());
			Assert::AreEqual(g + g1, color.G());
			Assert::AreEqual(b + b1, color.B());
			Assert::AreEqual(a + a1, color.A());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(SubtractAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr float a1 = 0.366f;
			constexpr auto color1 = PonyEngine::Math::RGBA<float>(r1, g1, b1, a1);
			PonyEngine::Math::RGBA<float>& colorRef = color -= color1;
			Assert::AreEqual(r - r1, color.R());
			Assert::AreEqual(g - g1, color.G());
			Assert::AreEqual(b - b1, color.B());
			Assert::AreEqual(a - a1, color.A());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(ColorProductAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr float a1 = 0.366f;
			constexpr auto color1 = PonyEngine::Math::RGBA<float>(r1, g1, b1, a1);
			PonyEngine::Math::RGBA<float>& colorRef = color *= color1;
			Assert::AreEqual(r * r1, color.R());
			Assert::AreEqual(g * g1, color.G());
			Assert::AreEqual(b * b1, color.B());
			Assert::AreEqual(a * a1, color.A());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(ProductAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float multiplier = 4.f;
			PonyEngine::Math::RGBA<float>& colorRef = color *= multiplier;
			Assert::AreEqual(r * multiplier, color.R());
			Assert::AreEqual(g * multiplier, color.G());
			Assert::AreEqual(b * multiplier, color.B());
			Assert::AreEqual(a * multiplier, color.A());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(ColorDivisionAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr float a1 = 0.366f;
			constexpr auto color1 = PonyEngine::Math::RGBA<float>(r1, g1, b1, a1);
			PonyEngine::Math::RGBA<float>& colorRef = color /= color1;
			Assert::AreEqual(static_cast<double>(r / r1), static_cast<double>(color.R()), 0.00001);
			Assert::AreEqual(static_cast<double>(g / g1), static_cast<double>(color.G()), 0.00001);
			Assert::AreEqual(static_cast<double>(b / b1), static_cast<double>(color.B()), 0.00001);
			Assert::AreEqual(static_cast<double>(a / a1), static_cast<double>(color.A()), 0.00001);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(DivisionAssignmentTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float divisor = 4.f;
			PonyEngine::Math::RGBA<float>& colorRef = color /= divisor;
			Assert::AreEqual(r / divisor, color.R());
			Assert::AreEqual(g / divisor, color.G());
			Assert::AreEqual(b / divisor, color.B());
			Assert::AreEqual(a / divisor, color.A());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&color), reinterpret_cast<std::uintptr_t>(&colorRef));
		}

		TEST_METHOD(EqualTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			const auto otherColor = color;
			Assert::IsTrue(color == otherColor);
			Assert::IsFalse(color != otherColor);

			for (std::size_t i = 0; i < PonyEngine::Math::RGBA<float>::ComponentCount; ++i)
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
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr float a1 = 0.366f;
			constexpr auto color1 = PonyEngine::Math::RGBA<float>(r1, g1, b1, a1);
			Assert::AreEqual(0.49, static_cast<double>(PonyEngine::Math::DistanceSquared(color, color1)), 0.001);
			Assert::AreEqual(0.7, static_cast<double>(PonyEngine::Math::Distance(color, color1)), 0.001);
		}

		TEST_METHOD(LerpTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr float a1 = 0.366f;
			constexpr auto color1 = PonyEngine::Math::RGBA<float>(r1, g1, b1, a1);

			PonyEngine::Math::RGBA<float> lerped = PonyEngine::Math::Lerp(color, color1, 0.f);
			Assert::AreEqual(r, lerped.R());
			Assert::AreEqual(g, lerped.G());
			Assert::AreEqual(b, lerped.B());
			Assert::AreEqual(a, lerped.A());

			lerped = PonyEngine::Math::Lerp(color, color1, 1.f);
			Assert::AreEqual(static_cast<double>(r1), static_cast<double>(lerped.R()), 0.0001);
			Assert::AreEqual(static_cast<double>(g1), static_cast<double>(lerped.G()), 0.0001);
			Assert::AreEqual(static_cast<double>(b1), static_cast<double>(lerped.B()), 0.0001);
			Assert::AreEqual(static_cast<double>(a1), static_cast<double>(lerped.A()), 0.0001);

			lerped = PonyEngine::Math::Lerp(color, color1, 0.5f);
			Assert::AreEqual(0.34, static_cast<double>(lerped.R()), 0.0001);
			Assert::AreEqual(0.39, static_cast<double>(lerped.G()), 0.0001);
			Assert::AreEqual(0.215, static_cast<double>(lerped.B()), 0.0001);
			Assert::AreEqual(0.266, static_cast<double>(lerped.A()), 0.0001);

			lerped = PonyEngine::Math::Lerp(color, color1, 2.f);
			Assert::AreEqual(-0.11, static_cast<double>(lerped.R()), 0.0001);
			Assert::AreEqual(-0.51, static_cast<double>(lerped.G()), 0.0001);
			Assert::AreEqual(0.227, static_cast<double>(lerped.B()), 0.0001);
			Assert::AreEqual(0.566, static_cast<double>(lerped.A()), 0.0001);

			lerped = PonyEngine::Math::Lerp(color, color1, -1.f);
			Assert::AreEqual(0.79, static_cast<double>(lerped.R()), 0.0001);
			Assert::AreEqual(1.29, static_cast<double>(lerped.G()), 0.0001);
			Assert::AreEqual(0.203, static_cast<double>(lerped.B()), 0.0001);
			Assert::AreEqual(-0.034, static_cast<double>(lerped.A()), 0.0001);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			PonyEngine::Math::RGBA<float> colorL = color;

			for (std::size_t i = 0; i < PonyEngine::Math::RGBA<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(colorL, color));
				colorL[i] = std::nextafter(colorL[i], 0.f);
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(colorL, color));
				colorL[i] += 1;
				Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(colorL, color));
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(colorL, color, 5.f));
				colorL[i] = color[i];
			}
		}

		TEST_METHOD(SumTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr float a1 = 0.366f;
			constexpr auto color1 = PonyEngine::Math::RGBA<float>(r1, g1, b1, a1);
			auto sum = color + color1;
			Assert::AreEqual(r + r1, sum.R());
			Assert::AreEqual(g + g1, sum.G());
			Assert::AreEqual(b + b1, sum.B());
			Assert::AreEqual(a + a1, sum.A());
		}

		TEST_METHOD(DifferenceTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr float a1 = 0.366f;
			constexpr auto color1 = PonyEngine::Math::RGBA<float>(r1, g1, b1, a1);
			auto difference = color - color1;
			Assert::AreEqual(r - r1, difference.R());
			Assert::AreEqual(g - g1, difference.G());
			Assert::AreEqual(b - b1, difference.B());
			Assert::AreEqual(a - a1, difference.A());
		}

		TEST_METHOD(ProductColorTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr float a1 = 0.366f;
			constexpr auto color1 = PonyEngine::Math::RGBA<float>(r1, g1, b1, a1);
			auto product = color * color1;
			Assert::AreEqual(r * r1, product.R());
			Assert::AreEqual(g * g1, product.G());
			Assert::AreEqual(b * b1, product.B());
			Assert::AreEqual(a * a1, product.A());
		}

		TEST_METHOD(ProductTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float multiplier = 2.f;

			auto product = color * multiplier;
			Assert::AreEqual(r * multiplier, product.R());
			Assert::AreEqual(g * multiplier, product.G());
			Assert::AreEqual(b * multiplier, product.B());
			Assert::AreEqual(a * multiplier, product.A());

			product = PonyEngine::Math::RGBA<float>();
			product = multiplier * color;
			Assert::AreEqual(r * multiplier, product.R());
			Assert::AreEqual(g * multiplier, product.G());
			Assert::AreEqual(b * multiplier, product.B());
			Assert::AreEqual(a * multiplier, product.A());
		}

		TEST_METHOD(DivisionColorTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float r1 = 0.19f;
			constexpr float g1 = 0.09f;
			constexpr float b1 = 0.219f;
			constexpr float a1 = 0.366f;
			constexpr auto color1 = PonyEngine::Math::RGBA<float>(r1, g1, b1, a1);
			auto quotient = color / color1;
			Assert::AreEqual(r / r1, quotient.R());
			Assert::AreEqual(g / g1, quotient.G());
			Assert::AreEqual(b / b1, quotient.B());
			Assert::AreEqual(a / a1, quotient.A());
		}

		TEST_METHOD(DivisionTest)
		{
			constexpr float r = 0.49f;
			constexpr float g = 0.69f;
			constexpr float b = 0.211f;
			constexpr float a = 0.166f;
			constexpr auto color = PonyEngine::Math::RGBA<float>(r, g, b, a);
			constexpr float divisor = 3.f;
			auto quotient = color / divisor;
			Assert::AreEqual(r / divisor, quotient.R());
			Assert::AreEqual(g / divisor, quotient.G());
			Assert::AreEqual(b / divisor, quotient.B());
			Assert::AreEqual(a / divisor, quotient.A());
		}

		static constexpr PonyEngine::Math::RGBA<float> RGBAConstexpr()
		{
			auto color = PonyEngine::Math::RGBA<float>(0.3f, 0.4f, 0.6f, 0.69f);
			auto copiedColor = color;
			auto movedColor = std::move(color);

			copiedColor.R() *= 2.f;
			copiedColor.G() /= 2.f;
			copiedColor.B() += 1.f;
			copiedColor.A() -= 1.f;

			movedColor.Span()[0] *= 2.5f;

			copiedColor.Min() /= 3.f;
			copiedColor.Max() *= 2.f;

			movedColor.Set(0.1f, 0.69f, 0.228f, 0.322f);
			movedColor.Set(copiedColor.Span());

			movedColor[0] *= 1.5f;
			auto anotherColor = PonyEngine::Math::RGBA<float>();
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
			[[maybe_unused]] constexpr auto defaultColor = PonyEngine::Math::RGBA<float>();
			[[maybe_unused]] constexpr auto color = PonyEngine::Math::RGBA<float>(0.3f, 0.4f, 0.6f, 0.69f);
			[[maybe_unused]] constexpr auto spanColor = PonyEngine::Math::RGBA<float>(std::array<float, 4>{0.4f, 0.1f, 0.2f, 0.9f});
			[[maybe_unused]] constexpr auto rgbColor = PonyEngine::Math::RGBA<float>(PonyEngine::Math::RGB<float>(0.1f, 0.2f, 0.3f), 0.4f);
			[[maybe_unused]] constexpr auto rgbIntColor = PonyEngine::Math::RGBA<float>(PonyEngine::Math::RGBInt<unsigned int>(54, 38, 90), 0.4f);
			[[maybe_unused]] constexpr auto rgbaColor = PonyEngine::Math::RGBA<float>(PonyEngine::Math::RGBAInt<unsigned short>(215, 574, 136, 907));
			[[maybe_unused]] constexpr auto vectorColor = PonyEngine::Math::RGBA<float>(PonyEngine::Math::Vector4<float>(0.4f, 0.69f, 0.228f, 0.322f));
			[[maybe_unused]] constexpr auto movedColor = RGBAConstexpr();

			[[maybe_unused]] constexpr float r = color.R();
			[[maybe_unused]] constexpr float g = color.G();
			[[maybe_unused]] constexpr float b = color.B();
			[[maybe_unused]] constexpr float a = color.A();

			[[maybe_unused]] constexpr auto span = color.Span();

			[[maybe_unused]] constexpr auto grayscale = color.Grayscale();

			[[maybe_unused]] constexpr auto min = color.Min();
			[[maybe_unused]] constexpr auto max = color.Max();

			[[maybe_unused]] constexpr bool isBlack = color.IsBlack();
			[[maybe_unused]] constexpr bool isAlmostBlack = color.IsAlmostBlack();
			[[maybe_unused]] constexpr bool isWhite = color.IsWhite();
			[[maybe_unused]] constexpr bool isAlmostWhite = color.IsAlmostWhite();
			[[maybe_unused]] constexpr bool isTransparent = color.IsTransparent();
			[[maybe_unused]] constexpr bool isAlmostTransparent = color.IsAlmostTransparent();

			[[maybe_unused]] constexpr auto rgba = static_cast<PonyEngine::Math::RGBA<double>>(color);
			[[maybe_unused]] constexpr auto rgb = static_cast<PonyEngine::Math::RGB<float>>(color);
			[[maybe_unused]] constexpr auto rgbaInt = static_cast<PonyEngine::Math::RGBAInt<unsigned int>>(color);
			[[maybe_unused]] constexpr auto rgbInt = static_cast<PonyEngine::Math::RGBInt<unsigned int>>(color);

			[[maybe_unused]] constexpr auto vector = static_cast<PonyEngine::Math::Vector4<float>>(color);

			[[maybe_unused]] constexpr float component = color[0];

			[[maybe_unused]] constexpr bool isEqual = color == defaultColor;
			[[maybe_unused]] constexpr bool isNotEqual = color != defaultColor;

			[[maybe_unused]] constexpr float distanceSquared = PonyEngine::Math::DistanceSquared(color, defaultColor);

			[[maybe_unused]] constexpr auto lerp = PonyEngine::Math::Lerp(color, defaultColor, 0.5f);

			[[maybe_unused]] constexpr bool areAlmostEqual = PonyEngine::Math::AreAlmostEqual(color, defaultColor);

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
