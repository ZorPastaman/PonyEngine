/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cmath>
#include <cstdint>
#include <numbers>
#include <type_traits>

import PonyMath.Core;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(CommonTests)
	{
	public:
		TEST_METHOD(IsGreaterTest)
		{
			Assert::IsTrue(PonyMath::Core::IsGreaterThan<std::uint32_t, std::uint8_t>);
			Assert::IsFalse(PonyMath::Core::IsGreaterThan<std::uint32_t, std::uint32_t>);
			Assert::IsFalse(PonyMath::Core::IsGreaterThan<std::uint8_t, std::uint32_t>);

			Assert::IsFalse(PonyMath::Core::IsGreaterThan<float, float>);
			Assert::IsTrue(PonyMath::Core::IsGreaterThan<double, float>);
			Assert::IsFalse(PonyMath::Core::IsGreaterThan<float, double>);
		}

		TEST_METHOD(FloatingBySizeTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::FloatingBySize<std::int8_t>>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::FloatingBySize<std::int32_t>>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::FloatingBySize<float>>);

			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::FloatingBySize<std::int64_t>>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::FloatingBySize<double>>);
		}

		TEST_METHOD(ComputationalForTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<bool>>);

			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<std::int8_t>>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<std::uint8_t>>);

			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<std::int16_t>>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<std::uint16_t>>);

			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<std::int32_t>>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<std::uint32_t>>);

			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::ComputationalFor<std::int64_t>>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::ComputationalFor<std::uint64_t>>);

			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<float>>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::ComputationalFor<double>>);
		}

		TEST_METHOD(DegToRadTest)
		{
			Assert::AreEqual(std::numbers::pi_v<double> / 180., PonyMath::Core::DegToRad<double>);
			Assert::AreEqual(std::numbers::pi_v<float> / 180.f, PonyMath::Core::DegToRad<float>);
		}

		TEST_METHOD(RadToDegTest)
		{
			Assert::AreEqual(180. / std::numbers::pi_v<double>, PonyMath::Core::RadToDeg<double>);
			Assert::AreEqual(180.f / std::numbers::pi_v<float>, PonyMath::Core::RadToDeg<float>);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(1.f, 1.f));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(1.f, std::nextafter(1.f, 0.f)));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(1.f, 1.f - 0.000001f));
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(1.f, 0.f, 2.f));

			Assert::IsFalse(PonyMath::Core::AreAlmostEqual(1.f, 1.5f));
		}

		TEST_METHOD(SignShortTest)
		{
			Assert::AreEqual(std::int16_t{1}, PonyMath::Core::Sign(std::int16_t{0}));
			Assert::AreEqual(std::int16_t{1}, PonyMath::Core::Sign(std::int16_t{39}));
			Assert::AreEqual(std::int16_t{-1}, PonyMath::Core::Sign(std::int16_t{-42}));
		}

		TEST_METHOD(SignFloatTest)
		{
			Assert::AreEqual(1.f, PonyMath::Core::Sign(0.f));
			Assert::AreEqual(1.f, PonyMath::Core::Sign(39.f));
			Assert::AreEqual(-1.f, PonyMath::Core::Sign(-42.f));
			Assert::AreEqual(1.f, PonyMath::Core::Sign(0.3f));
			Assert::AreEqual(-1.f, PonyMath::Core::Sign(-0.3f));
		}

		TEST_METHOD(SignShortFromBoolTest)
		{
			Assert::AreEqual(std::int16_t{1}, PonyMath::Core::Sign<std::int16_t>(true));
			Assert::AreEqual(std::int16_t{-1}, PonyMath::Core::Sign<std::int16_t>(false));
		}

		TEST_METHOD(SignFloatFromBoolTest)
		{
			Assert::AreEqual(1.f, PonyMath::Core::Sign<float>(true));
			Assert::AreEqual(-1.f, PonyMath::Core::Sign<float>(false));
		}

		TEST_METHOD(SignumShortTest)
		{
			Assert::AreEqual(std::int16_t{0}, PonyMath::Core::Signum(std::int16_t{0}));
			Assert::AreEqual(std::int16_t{1}, PonyMath::Core::Signum(std::int16_t{39}));
			Assert::AreEqual(std::int16_t{-1}, PonyMath::Core::Signum(std::int16_t{-42}));
		}

		TEST_METHOD(SignumFloatTest)
		{
			Assert::AreEqual(0.f, PonyMath::Core::Signum(0.f));
			Assert::AreEqual(1.f, PonyMath::Core::Signum(39.f));
			Assert::AreEqual(-1.f, PonyMath::Core::Signum(-42.f));
			Assert::AreEqual(1.f, PonyMath::Core::Signum(0.3f));
			Assert::AreEqual(-1.f, PonyMath::Core::Signum(-0.3f));
		}

		TEST_METHOD(SignumWithConversionShortTest)
		{
			Assert::AreEqual(std::int16_t{ 0 }, PonyMath::Core::Signum<std::int16_t>(0.f));
			Assert::AreEqual(std::int16_t{1}, PonyMath::Core::Signum<std::int16_t>(5.f));
			Assert::AreEqual(std::int16_t{-1}, PonyMath::Core::Signum<std::int16_t>(-42.f));
			Assert::AreEqual(std::int16_t{1}, PonyMath::Core::Signum<std::int16_t>(0.1f));
			Assert::AreEqual(std::int16_t{-1}, PonyMath::Core::Signum<std::int16_t>(-0.1f));
		}

		TEST_METHOD(SignumWithConversionFloatTest)
		{
			Assert::AreEqual(0.f, PonyMath::Core::Signum<float>(0));
			Assert::AreEqual(1.f, PonyMath::Core::Signum<float>(39));
			Assert::AreEqual(-1.f, PonyMath::Core::Signum<float>(-42));
		}

		TEST_METHOD(RoundToIntegralShortTest)
		{
			Assert::AreEqual(std::int16_t{0}, PonyMath::Core::RoundToIntegral<float, std::int16_t>(0.f));
			Assert::AreEqual(std::int16_t{0}, PonyMath::Core::RoundToIntegral<float, std::int16_t>(0.3f));
			Assert::AreEqual(std::int16_t{0}, PonyMath::Core::RoundToIntegral<float, std::int16_t>(-0.3f));
			Assert::AreEqual(std::int16_t{1}, PonyMath::Core::RoundToIntegral<float, std::int16_t>(0.7f));
			Assert::AreEqual(std::int16_t{-1}, PonyMath::Core::RoundToIntegral<float, std::int16_t>(-0.7f));
			Assert::AreEqual(std::int16_t{1}, PonyMath::Core::RoundToIntegral<float, std::int16_t>(1.2f));
			Assert::AreEqual(std::int16_t{-1}, PonyMath::Core::RoundToIntegral<float, std::int16_t>(-1.2f));
			Assert::AreEqual(std::int16_t{10}, PonyMath::Core::RoundToIntegral<float, std::int16_t>(10.3f));
			Assert::AreEqual(std::int16_t{-10}, PonyMath::Core::RoundToIntegral<float, std::int16_t>(-10.3f));
			Assert::AreEqual(std::int16_t{11}, PonyMath::Core::RoundToIntegral<float, std::int16_t>(10.7f));
			Assert::AreEqual(std::int16_t{-11}, PonyMath::Core::RoundToIntegral<float, std::int16_t>(-10.7f));
		}

		TEST_METHOD(RoundToIntegralLongLongTest)
		{
			Assert::AreEqual(0LL, PonyMath::Core::RoundToIntegral<double, std::int64_t>(0.));
			Assert::AreEqual(0LL, PonyMath::Core::RoundToIntegral<double, std::int64_t>(0.3));
			Assert::AreEqual(0LL, PonyMath::Core::RoundToIntegral<double, std::int64_t>(-0.3));
			Assert::AreEqual(1LL, PonyMath::Core::RoundToIntegral<double, std::int64_t>(0.7));
			Assert::AreEqual(-1LL, PonyMath::Core::RoundToIntegral<double, std::int64_t>(-0.7));
			Assert::AreEqual(1LL, PonyMath::Core::RoundToIntegral<double, std::int64_t>(1.2));
			Assert::AreEqual(-1LL, PonyMath::Core::RoundToIntegral<double, std::int64_t>(-1.2));
			Assert::AreEqual(10LL, PonyMath::Core::RoundToIntegral<double, std::int64_t>(10.3));
			Assert::AreEqual(-10LL, PonyMath::Core::RoundToIntegral<double, std::int64_t>(-10.3));
			Assert::AreEqual(11LL, PonyMath::Core::RoundToIntegral<double, std::int64_t>(10.7));
			Assert::AreEqual(-11LL, PonyMath::Core::RoundToIntegral<double, std::int64_t>(-10.7));
		}

		TEST_METHOD(DivideCeilTest)
		{
			Assert::AreEqual(3u, PonyMath::Core::DivideCeil(12u, 5u));
			Assert::AreEqual(1u, PonyMath::Core::DivideCeil(1u, 6u));
			Assert::AreEqual(1u, PonyMath::Core::DivideCeil(7u, 7u));
			Assert::AreEqual(1u, PonyMath::Core::DivideCeil(7u, 8u));
			Assert::AreEqual(2u, PonyMath::Core::DivideCeil(9u, 8u));
			Assert::AreEqual(4u, PonyMath::Core::DivideCeil(100u, 26u));
		}

		TEST_METHOD(AlignTest)
		{
			Assert::AreEqual(8u, PonyMath::Core::Align(5u, 4u));
			Assert::AreEqual(256u, PonyMath::Core::Align(200u, 64u));
			Assert::AreEqual(4u, PonyMath::Core::Align(1u, 4u));
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr float degToRad = PonyMath::Core::DegToRad<float>;
			[[maybe_unused]] constexpr float radToDeg = PonyMath::Core::RadToDeg<float>;
			[[maybe_unused]] constexpr float sign = PonyMath::Core::Sign(4.f);
			[[maybe_unused]] constexpr float signB = PonyMath::Core::Sign<float>(true);
			[[maybe_unused]] constexpr float signum = PonyMath::Core::Signum(3.f);
			[[maybe_unused]] constexpr float signumCast = PonyMath::Core::Signum<float>(4);
			[[maybe_unused]] constexpr std::int32_t round = PonyMath::Core::RoundToIntegral<float, std::int32_t>(3.5f);
			[[maybe_unused]] constexpr std::uint32_t divCeil = PonyMath::Core::DivideCeil(6u, 2u);
			[[maybe_unused]] constexpr std::uint32_t align = PonyMath::Core::Align(12u, 32u);
		}
	};
}
