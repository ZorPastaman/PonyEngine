/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <numbers>;
import <type_traits>;

import PonyEngine.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(CommonTests)
	{
	public:
		TEST_METHOD(ComputationalForTest)
		{
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::ComputationalFor<bool>>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::ComputationalFor<signed char>>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::ComputationalFor<unsigned char>>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::ComputationalFor<signed short>>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::ComputationalFor<unsigned short>>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::ComputationalFor<signed int>>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::ComputationalFor<unsigned int>>);

			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::ComputationalFor<signed long long>>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::ComputationalFor<unsigned long long>>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::ComputationalFor<float>>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::ComputationalFor<double>>);
		}

		TEST_METHOD(DegToRadTest)
		{
			Assert::AreEqual(std::numbers::pi_v<double> / 180., PonyEngine::Math::DegToRad<double>);
			Assert::AreEqual(std::numbers::pi_v<float> / 180.f, PonyEngine::Math::DegToRad<float>);
		}

		TEST_METHOD(RadToDegTest)
		{
			Assert::AreEqual(180. / std::numbers::pi_v<double>, PonyEngine::Math::RadToDeg<double>);
			Assert::AreEqual(180.f / std::numbers::pi_v<float>, PonyEngine::Math::RadToDeg<float>);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(1.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(1.f, std::nextafter(1.f, 0.f)));
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(1.f, 1.f - 0.000001f));
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(1.f, 0.f, 2.f));

			Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(1.f, 1.5f));
		}

		TEST_METHOD(SignumShortTest)
		{
			Assert::AreEqual(short{0}, PonyEngine::Math::Signum(short{ 0 }));
			Assert::AreEqual(short{1}, PonyEngine::Math::Signum(short{ 39 }));
			Assert::AreEqual(short{-1}, PonyEngine::Math::Signum(short{ -42 }));
		}

		TEST_METHOD(SignumFloatTest)
		{
			Assert::AreEqual(0.f, PonyEngine::Math::Signum(0.f));
			Assert::AreEqual(1.f, PonyEngine::Math::Signum(39.f));
			Assert::AreEqual(-1.f, PonyEngine::Math::Signum(-42.f));
			Assert::AreEqual(1.f, PonyEngine::Math::Signum(0.3f));
			Assert::AreEqual(-1.f, PonyEngine::Math::Signum(-0.3f));
		}

		TEST_METHOD(RoundToIntegralShortTest)
		{
			Assert::AreEqual(short{0}, PonyEngine::Math::RoundToIntegral<float, short>(0.f));
			Assert::AreEqual(short{0}, PonyEngine::Math::RoundToIntegral<float, short>(0.3f));
			Assert::AreEqual(short{0}, PonyEngine::Math::RoundToIntegral<float, short>(-0.3f));
			Assert::AreEqual(short{1}, PonyEngine::Math::RoundToIntegral<float, short>(0.7f));
			Assert::AreEqual(short{-1}, PonyEngine::Math::RoundToIntegral<float, short>(-0.7f));
			Assert::AreEqual(short{1}, PonyEngine::Math::RoundToIntegral<float, short>(1.2f));
			Assert::AreEqual(short{-1}, PonyEngine::Math::RoundToIntegral<float, short>(-1.2f));
			Assert::AreEqual(short{10}, PonyEngine::Math::RoundToIntegral<float, short>(10.3f));
			Assert::AreEqual(short{-10}, PonyEngine::Math::RoundToIntegral<float, short>(-10.3f));
			Assert::AreEqual(short{11}, PonyEngine::Math::RoundToIntegral<float, short>(10.7f));
			Assert::AreEqual(short{-11}, PonyEngine::Math::RoundToIntegral<float, short>(-10.7f));
		}

		TEST_METHOD(RoundToIntegralLongLongTest)
		{
			Assert::AreEqual(0LL, PonyEngine::Math::RoundToIntegral<double, long long>(0.));
			Assert::AreEqual(0LL, PonyEngine::Math::RoundToIntegral<double, long long>(0.3));
			Assert::AreEqual(0LL, PonyEngine::Math::RoundToIntegral<double, long long>(-0.3));
			Assert::AreEqual(1LL, PonyEngine::Math::RoundToIntegral<double, long long>(0.7));
			Assert::AreEqual(-1LL, PonyEngine::Math::RoundToIntegral<double, long long>(-0.7));
			Assert::AreEqual(1LL, PonyEngine::Math::RoundToIntegral<double, long long>(1.2));
			Assert::AreEqual(-1LL, PonyEngine::Math::RoundToIntegral<double, long long>(-1.2));
			Assert::AreEqual(10LL, PonyEngine::Math::RoundToIntegral<double, long long>(10.3));
			Assert::AreEqual(-10LL, PonyEngine::Math::RoundToIntegral<double, long long>(-10.3));
			Assert::AreEqual(11LL, PonyEngine::Math::RoundToIntegral<double, long long>(10.7));
			Assert::AreEqual(-11LL, PonyEngine::Math::RoundToIntegral<double, long long>(-10.7));
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr float degToRad = PonyEngine::Math::DegToRad<float>;
			[[maybe_unused]] constexpr float radToDeg = PonyEngine::Math::RadToDeg<float>;
			[[maybe_unused]] constexpr float signum = PonyEngine::Math::Signum<float>(3.f);
			[[maybe_unused]] constexpr int round = PonyEngine::Math::RoundToIntegral<float, int>(3.5f);
		}
	};
}
