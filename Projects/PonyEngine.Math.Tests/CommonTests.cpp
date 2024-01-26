#include "CppUnitTest.h"

import <numbers>;
import <type_traits>;

import PonyEngine.Math.Common;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PonyEngineMathTests
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

		TEST_METHOD(DegToRadToDegTest)
		{
			Assert::AreEqual(std::numbers::pi_v<double> / 180., PonyEngine::Math::DegToRad<double>);
			Assert::AreEqual(180. / std::numbers::pi_v<double>, PonyEngine::Math::RadToDeg<double>);

			Assert::AreEqual(std::numbers::pi_v<float> / 180.f, PonyEngine::Math::DegToRad<float>);
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

		TEST_METHOD(SignumTest)
		{
			Assert::AreEqual(short{0}, PonyEngine::Math::Signum(short{0}));
			Assert::AreEqual(short{1}, PonyEngine::Math::Signum(short{39}));
			Assert::AreEqual(short{-1}, PonyEngine::Math::Signum(short{-42}));

			Assert::AreEqual(0, PonyEngine::Math::Signum(0));
			Assert::AreEqual(1, PonyEngine::Math::Signum(39));
			Assert::AreEqual(-1, PonyEngine::Math::Signum(-42));

			Assert::AreEqual(0.f, PonyEngine::Math::Signum(0.f));
			Assert::AreEqual(1.f, PonyEngine::Math::Signum(39.f));
			Assert::AreEqual(-1.f, PonyEngine::Math::Signum(-42.f));
			Assert::AreEqual(1.f, PonyEngine::Math::Signum(0.3f));
			Assert::AreEqual(-1.f, PonyEngine::Math::Signum(-0.3f));
		}
	};
}
