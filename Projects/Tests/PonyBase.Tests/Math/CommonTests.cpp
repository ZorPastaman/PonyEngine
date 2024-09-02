/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstdint>
#include <numbers>

import PonyBase.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(CommonTests)
	{
	public:
		TEST_METHOD(IsGreaterTest)
		{
			Assert::IsTrue(PonyBase::Math::IsGreaterThan<std::uint32_t, std::uint8_t>);
			Assert::IsFalse(PonyBase::Math::IsGreaterThan<std::uint32_t, std::uint32_t>);
			Assert::IsFalse(PonyBase::Math::IsGreaterThan<std::uint8_t, std::uint32_t>);

			Assert::IsFalse(PonyBase::Math::IsGreaterThan<float, float>);
			Assert::IsTrue(PonyBase::Math::IsGreaterThan<double, float>);
			Assert::IsFalse(PonyBase::Math::IsGreaterThan<float, double>);
		}

		TEST_METHOD(FloatingBySizeTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::FloatingBySize<char>>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::FloatingBySize<int>>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::FloatingBySize<float>>);

			Assert::IsTrue(std::is_same_v<double, PonyBase::Math::FloatingBySize<long long>>);
			Assert::IsTrue(std::is_same_v<double, PonyBase::Math::FloatingBySize<double>>);
		}

		TEST_METHOD(ComputationalForTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::ComputationalFor<bool>>);

			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::ComputationalFor<signed char>>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::ComputationalFor<unsigned char>>);

			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::ComputationalFor<signed short>>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::ComputationalFor<unsigned short>>);

			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::ComputationalFor<signed int>>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::ComputationalFor<unsigned int>>);

			Assert::IsTrue(std::is_same_v<double, PonyBase::Math::ComputationalFor<signed long long>>);
			Assert::IsTrue(std::is_same_v<double, PonyBase::Math::ComputationalFor<unsigned long long>>);

			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::ComputationalFor<float>>);
			Assert::IsTrue(std::is_same_v<double, PonyBase::Math::ComputationalFor<double>>);
		}

		TEST_METHOD(DegToRadTest)
		{
			Assert::AreEqual(std::numbers::pi_v<double> / 180., PonyBase::Math::DegToRad<double>);
			Assert::AreEqual(std::numbers::pi_v<float> / 180.f, PonyBase::Math::DegToRad<float>);
		}

		TEST_METHOD(RadToDegTest)
		{
			Assert::AreEqual(180. / std::numbers::pi_v<double>, PonyBase::Math::RadToDeg<double>);
			Assert::AreEqual(180.f / std::numbers::pi_v<float>, PonyBase::Math::RadToDeg<float>);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			Assert::IsTrue(PonyBase::Math::AreAlmostEqual(1.f, 1.f));
			Assert::IsTrue(PonyBase::Math::AreAlmostEqual(1.f, std::nextafter(1.f, 0.f)));
			Assert::IsTrue(PonyBase::Math::AreAlmostEqual(1.f, 1.f - 0.000001f));
			Assert::IsTrue(PonyBase::Math::AreAlmostEqual(1.f, 0.f, 2.f));

			Assert::IsFalse(PonyBase::Math::AreAlmostEqual(1.f, 1.5f));
		}

		TEST_METHOD(SignShortTest)
		{
			Assert::AreEqual(short{1}, PonyBase::Math::Sign(short{0}));
			Assert::AreEqual(short{1}, PonyBase::Math::Sign(short{39}));
			Assert::AreEqual(short{-1}, PonyBase::Math::Sign(short{-42}));
		}

		TEST_METHOD(SignFloatTest)
		{
			Assert::AreEqual(1.f, PonyBase::Math::Sign(0.f));
			Assert::AreEqual(1.f, PonyBase::Math::Sign(39.f));
			Assert::AreEqual(-1.f, PonyBase::Math::Sign(-42.f));
			Assert::AreEqual(1.f, PonyBase::Math::Sign(0.3f));
			Assert::AreEqual(-1.f, PonyBase::Math::Sign(-0.3f));
		}

		TEST_METHOD(SignumShortTest)
		{
			Assert::AreEqual(short{0}, PonyBase::Math::Signum(short{0}));
			Assert::AreEqual(short{1}, PonyBase::Math::Signum(short{39}));
			Assert::AreEqual(short{-1}, PonyBase::Math::Signum(short{-42}));
		}

		TEST_METHOD(SignumFloatTest)
		{
			Assert::AreEqual(0.f, PonyBase::Math::Signum(0.f));
			Assert::AreEqual(1.f, PonyBase::Math::Signum(39.f));
			Assert::AreEqual(-1.f, PonyBase::Math::Signum(-42.f));
			Assert::AreEqual(1.f, PonyBase::Math::Signum(0.3f));
			Assert::AreEqual(-1.f, PonyBase::Math::Signum(-0.3f));
		}

		TEST_METHOD(RoundToIntegralShortTest)
		{
			Assert::AreEqual(short{0}, PonyBase::Math::RoundToIntegral<float, short>(0.f));
			Assert::AreEqual(short{0}, PonyBase::Math::RoundToIntegral<float, short>(0.3f));
			Assert::AreEqual(short{0}, PonyBase::Math::RoundToIntegral<float, short>(-0.3f));
			Assert::AreEqual(short{1}, PonyBase::Math::RoundToIntegral<float, short>(0.7f));
			Assert::AreEqual(short{-1}, PonyBase::Math::RoundToIntegral<float, short>(-0.7f));
			Assert::AreEqual(short{1}, PonyBase::Math::RoundToIntegral<float, short>(1.2f));
			Assert::AreEqual(short{-1}, PonyBase::Math::RoundToIntegral<float, short>(-1.2f));
			Assert::AreEqual(short{10}, PonyBase::Math::RoundToIntegral<float, short>(10.3f));
			Assert::AreEqual(short{-10}, PonyBase::Math::RoundToIntegral<float, short>(-10.3f));
			Assert::AreEqual(short{11}, PonyBase::Math::RoundToIntegral<float, short>(10.7f));
			Assert::AreEqual(short{-11}, PonyBase::Math::RoundToIntegral<float, short>(-10.7f));
		}

		TEST_METHOD(RoundToIntegralLongLongTest)
		{
			Assert::AreEqual(0LL, PonyBase::Math::RoundToIntegral<double, long long>(0.));
			Assert::AreEqual(0LL, PonyBase::Math::RoundToIntegral<double, long long>(0.3));
			Assert::AreEqual(0LL, PonyBase::Math::RoundToIntegral<double, long long>(-0.3));
			Assert::AreEqual(1LL, PonyBase::Math::RoundToIntegral<double, long long>(0.7));
			Assert::AreEqual(-1LL, PonyBase::Math::RoundToIntegral<double, long long>(-0.7));
			Assert::AreEqual(1LL, PonyBase::Math::RoundToIntegral<double, long long>(1.2));
			Assert::AreEqual(-1LL, PonyBase::Math::RoundToIntegral<double, long long>(-1.2));
			Assert::AreEqual(10LL, PonyBase::Math::RoundToIntegral<double, long long>(10.3));
			Assert::AreEqual(-10LL, PonyBase::Math::RoundToIntegral<double, long long>(-10.3));
			Assert::AreEqual(11LL, PonyBase::Math::RoundToIntegral<double, long long>(10.7));
			Assert::AreEqual(-11LL, PonyBase::Math::RoundToIntegral<double, long long>(-10.7));
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr float degToRad = PonyBase::Math::DegToRad<float>;
			[[maybe_unused]] constexpr float radToDeg = PonyBase::Math::RadToDeg<float>;
			[[maybe_unused]] constexpr float sign = PonyBase::Math::Sign<float>(4.f);
			[[maybe_unused]] constexpr float signum = PonyBase::Math::Signum<float>(3.f);
			[[maybe_unused]] constexpr int round = PonyBase::Math::RoundToIntegral<float, int>(3.5f);
		}
	};
}
