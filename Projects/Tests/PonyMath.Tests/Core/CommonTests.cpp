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

namespace Math
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
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::FloatingBySize<char>>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::FloatingBySize<int>>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::FloatingBySize<float>>);

			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::FloatingBySize<long long>>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::FloatingBySize<double>>);
		}

		TEST_METHOD(ComputationalForTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<bool>>);

			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<signed char>>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<unsigned char>>);

			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<signed short>>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<unsigned short>>);

			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<signed int>>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::ComputationalFor<unsigned int>>);

			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::ComputationalFor<signed long long>>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::ComputationalFor<unsigned long long>>);

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
			Assert::AreEqual(short{1}, PonyMath::Core::Sign(short{0}));
			Assert::AreEqual(short{1}, PonyMath::Core::Sign(short{39}));
			Assert::AreEqual(short{-1}, PonyMath::Core::Sign(short{-42}));
		}

		TEST_METHOD(SignFloatTest)
		{
			Assert::AreEqual(1.f, PonyMath::Core::Sign(0.f));
			Assert::AreEqual(1.f, PonyMath::Core::Sign(39.f));
			Assert::AreEqual(-1.f, PonyMath::Core::Sign(-42.f));
			Assert::AreEqual(1.f, PonyMath::Core::Sign(0.3f));
			Assert::AreEqual(-1.f, PonyMath::Core::Sign(-0.3f));
		}

		TEST_METHOD(SignumShortTest)
		{
			Assert::AreEqual(short{0}, PonyMath::Core::Signum(short{0}));
			Assert::AreEqual(short{1}, PonyMath::Core::Signum(short{39}));
			Assert::AreEqual(short{-1}, PonyMath::Core::Signum(short{-42}));
		}

		TEST_METHOD(SignumFloatTest)
		{
			Assert::AreEqual(0.f, PonyMath::Core::Signum(0.f));
			Assert::AreEqual(1.f, PonyMath::Core::Signum(39.f));
			Assert::AreEqual(-1.f, PonyMath::Core::Signum(-42.f));
			Assert::AreEqual(1.f, PonyMath::Core::Signum(0.3f));
			Assert::AreEqual(-1.f, PonyMath::Core::Signum(-0.3f));
		}

		TEST_METHOD(RoundToIntegralShortTest)
		{
			Assert::AreEqual(short{0}, PonyMath::Core::RoundToIntegral<float, short>(0.f));
			Assert::AreEqual(short{0}, PonyMath::Core::RoundToIntegral<float, short>(0.3f));
			Assert::AreEqual(short{0}, PonyMath::Core::RoundToIntegral<float, short>(-0.3f));
			Assert::AreEqual(short{1}, PonyMath::Core::RoundToIntegral<float, short>(0.7f));
			Assert::AreEqual(short{-1}, PonyMath::Core::RoundToIntegral<float, short>(-0.7f));
			Assert::AreEqual(short{1}, PonyMath::Core::RoundToIntegral<float, short>(1.2f));
			Assert::AreEqual(short{-1}, PonyMath::Core::RoundToIntegral<float, short>(-1.2f));
			Assert::AreEqual(short{10}, PonyMath::Core::RoundToIntegral<float, short>(10.3f));
			Assert::AreEqual(short{-10}, PonyMath::Core::RoundToIntegral<float, short>(-10.3f));
			Assert::AreEqual(short{11}, PonyMath::Core::RoundToIntegral<float, short>(10.7f));
			Assert::AreEqual(short{-11}, PonyMath::Core::RoundToIntegral<float, short>(-10.7f));
		}

		TEST_METHOD(RoundToIntegralLongLongTest)
		{
			Assert::AreEqual(0LL, PonyMath::Core::RoundToIntegral<double, long long>(0.));
			Assert::AreEqual(0LL, PonyMath::Core::RoundToIntegral<double, long long>(0.3));
			Assert::AreEqual(0LL, PonyMath::Core::RoundToIntegral<double, long long>(-0.3));
			Assert::AreEqual(1LL, PonyMath::Core::RoundToIntegral<double, long long>(0.7));
			Assert::AreEqual(-1LL, PonyMath::Core::RoundToIntegral<double, long long>(-0.7));
			Assert::AreEqual(1LL, PonyMath::Core::RoundToIntegral<double, long long>(1.2));
			Assert::AreEqual(-1LL, PonyMath::Core::RoundToIntegral<double, long long>(-1.2));
			Assert::AreEqual(10LL, PonyMath::Core::RoundToIntegral<double, long long>(10.3));
			Assert::AreEqual(-10LL, PonyMath::Core::RoundToIntegral<double, long long>(-10.3));
			Assert::AreEqual(11LL, PonyMath::Core::RoundToIntegral<double, long long>(10.7));
			Assert::AreEqual(-11LL, PonyMath::Core::RoundToIntegral<double, long long>(-10.7));
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr float degToRad = PonyMath::Core::DegToRad<float>;
			[[maybe_unused]] constexpr float radToDeg = PonyMath::Core::RadToDeg<float>;
			[[maybe_unused]] constexpr float sign = PonyMath::Core::Sign<float>(4.f);
			[[maybe_unused]] constexpr float signum = PonyMath::Core::Signum<float>(3.f);
			[[maybe_unused]] constexpr int round = PonyMath::Core::RoundToIntegral<float, int>(3.5f);
		}
	};
}
