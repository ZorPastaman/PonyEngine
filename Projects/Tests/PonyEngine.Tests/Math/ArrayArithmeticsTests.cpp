/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <array>;

import PonyEngine.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(ArrayArithmeticsTests)
	{
		TEST_METHOD(AssignmentWithDestinationStepTest)
		{
			constexpr int d0 = 3;
			constexpr int d1 = 2;
			constexpr int d2 = 9;
			constexpr int d3 = 5;
			constexpr int d4 = -1;
			constexpr int d5 = 4;
			constexpr int d6 = -7;
			constexpr int d7 = -3;
			constexpr int d8 = -9;
			constexpr int d9 = -5;
			constexpr int d10 = 8;

			constexpr int s0 = 30;
			constexpr int s1 = 20;
			constexpr int s2 = 90;
			constexpr int s3 = 50;
			constexpr int s4 = -10;
			constexpr int s5 = 40;

			std::array<int, 11> destination{ d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10 };
			constexpr std::array<int, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::AssignWithDestinationStep(destination.data(), source.data(), 5, 2);
			Assert::AreEqual(s0, destination[0]);
			Assert::AreEqual(d1, destination[1]);
			Assert::AreEqual(s1, destination[2]);
			Assert::AreEqual(d3, destination[3]);
			Assert::AreEqual(s2, destination[4]);
			Assert::AreEqual(d5, destination[5]);
			Assert::AreEqual(s3, destination[6]);
			Assert::AreEqual(d7, destination[7]);
			Assert::AreEqual(s4, destination[8]);
			Assert::AreEqual(d9, destination[9]);
			Assert::AreEqual(d10, destination[10]);
		}

		static constexpr std::array<int, 11> AssignmentWithDestinationStepConstexpr(const int d0, const int d1, const int d2, const int d3, const int d4, const int d5, const int d6, const int d7, const int d8, const int d9, const int d10,
			const int s0, const int s1, const int s2, const int s3, const int s4, const int s5)
		{
			std::array<int, 11> destination{ d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10 };
			const std::array<int, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::AssignWithDestinationStep(destination.data(), source.data(), 5, 2);

			return destination;
		}

		TEST_METHOD(AssignmentWithDestinationStepConstexprTest)
		{
			constexpr int d0 = 3;
			constexpr int d1 = 2;
			constexpr int d2 = 9;
			constexpr int d3 = 5;
			constexpr int d4 = -1;
			constexpr int d5 = 4;
			constexpr int d6 = -7;
			constexpr int d7 = -3;
			constexpr int d8 = -9;
			constexpr int d9 = -5;
			constexpr int d10 = 8;

			constexpr int s0 = 30;
			constexpr int s1 = 20;
			constexpr int s2 = 90;
			constexpr int s3 = 50;
			constexpr int s4 = -10;
			constexpr int s5 = 40;

			constexpr std::array<int, 11> destination = AssignmentWithDestinationStepConstexpr(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, s0, s1, s2, s3, s4, s5);
			Assert::AreEqual(s0, destination[0]);
			Assert::AreEqual(d1, destination[1]);
			Assert::AreEqual(s1, destination[2]);
			Assert::AreEqual(d3, destination[3]);
			Assert::AreEqual(s2, destination[4]);
			Assert::AreEqual(d5, destination[5]);
			Assert::AreEqual(s3, destination[6]);
			Assert::AreEqual(d7, destination[7]);
			Assert::AreEqual(s4, destination[8]);
			Assert::AreEqual(d9, destination[9]);
			Assert::AreEqual(d10, destination[10]);
		}

		TEST_METHOD(AssignmentWithSourceStepTest)
		{
			constexpr int d0 = 3;
			constexpr int d1 = 2;
			constexpr int d2 = 9;
			constexpr int d3 = 5;
			constexpr int d4 = -1;
			constexpr int d5 = 4;

			constexpr int s0 = 30;
			constexpr int s1 = 20;
			constexpr int s2 = 90;
			constexpr int s3 = 50;
			constexpr int s4 = -10;
			constexpr int s5 = 40;
			constexpr int s6 = -70;
			constexpr int s7 = -30;
			constexpr int s8 = -90;
			constexpr int s9 = -50;
			constexpr int s10 = 80;

			std::array<int, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<int, 11> source{ s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10 };

			PonyEngine::Math::AssignWithSourceStep(destination.data(), source.data(), 5, 2);
			Assert::AreEqual(s0, destination[0]);
			Assert::AreEqual(s2, destination[1]);
			Assert::AreEqual(s4, destination[2]);
			Assert::AreEqual(s6, destination[3]);
			Assert::AreEqual(s8, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		static constexpr std::array<int, 6> AssignmentWithSourceStepConstexpr(const int d0, const int d1, const int d2, const int d3, const int d4, const int d5,
			const int s0, const int s1, const int s2, const int s3, const int s4, const int s5, const int s6, const int s7, const int s8, const int s9, const int s10)
		{
			std::array<int, 6> destination{ d0, d1, d2, d3, d4, d5 };
			const std::array<int, 11> source{ s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10 };

			PonyEngine::Math::AssignWithSourceStep(destination.data(), source.data(), 5, 2);

			return destination;
		}

		TEST_METHOD(AssignmentWithSourceStepConstexprTest)
		{
			constexpr int d0 = 3;
			constexpr int d1 = 2;
			constexpr int d2 = 9;
			constexpr int d3 = 5;
			constexpr int d4 = -1;
			constexpr int d5 = 4;

			constexpr int s0 = 30;
			constexpr int s1 = 20;
			constexpr int s2 = 90;
			constexpr int s3 = 50;
			constexpr int s4 = -10;
			constexpr int s5 = 40;
			constexpr int s6 = -70;
			constexpr int s7 = -30;
			constexpr int s8 = -90;
			constexpr int s9 = -50;
			constexpr int s10 = 80;

			constexpr std::array<int, 6> destination = AssignmentWithSourceStepConstexpr(d0, d1, d2, d3, d4, d5, s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10);
			Assert::AreEqual(s0, destination[0]);
			Assert::AreEqual(s2, destination[1]);
			Assert::AreEqual(s4, destination[2]);
			Assert::AreEqual(s6, destination[3]);
			Assert::AreEqual(s8, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(AddEqualTest)
		{
			constexpr int d0 = 3;
			constexpr int d1 = 2;
			constexpr int d2 = 9;
			constexpr int d3 = 5;
			constexpr int d4 = -1;
			constexpr int d5 = 4;

			constexpr int s0 = 30;
			constexpr int s1 = 20;
			constexpr int s2 = 90;
			constexpr int s3 = 50;
			constexpr int s4 = -10;
			constexpr int s5 = 40;

			std::array<int, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<int, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::Add(destination.data(), source.data(), 5);
			Assert::AreEqual(d0 + s0, destination[0]);
			Assert::AreEqual(d1 + s1, destination[1]);
			Assert::AreEqual(d2 + s2, destination[2]);
			Assert::AreEqual(d3 + s3, destination[3]);
			Assert::AreEqual(d4 + s4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(AddTest)
		{
			constexpr int d0 = 3;
			constexpr int d1 = 2;
			constexpr int d2 = 9;
			constexpr int d3 = 5;
			constexpr int d4 = -1;
			constexpr int d5 = 4;

			constexpr int l0 = 30;
			constexpr int l1 = 20;
			constexpr int l2 = 90;
			constexpr int l3 = 50;
			constexpr int l4 = -10;
			constexpr int l5 = 40;

			constexpr int r0 = 300;
			constexpr int r1 = 200;
			constexpr int r2 = 900;
			constexpr int r3 = 500;
			constexpr int r4 = -100;
			constexpr int r5 = 400;

			std::array<int, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<int, 6> left{ l0, l1, l2, l3, l4, l5 };
			constexpr std::array<int, 6> right{ r0, r1, r2, r3, r4, r5 };

			PonyEngine::Math::Add(destination.data(), left.data(), right.data(), 5);
			Assert::AreEqual(l0 + r0, destination[0]);
			Assert::AreEqual(l1 + r1, destination[1]);
			Assert::AreEqual(l2 + r2, destination[2]);
			Assert::AreEqual(l3 + r3, destination[3]);
			Assert::AreEqual(l4 + r4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(SubtractEqualTest)
		{
			constexpr int d0 = 3;
			constexpr int d1 = 2;
			constexpr int d2 = 9;
			constexpr int d3 = 5;
			constexpr int d4 = -1;
			constexpr int d5 = 4;

			constexpr int s0 = 30;
			constexpr int s1 = 20;
			constexpr int s2 = 90;
			constexpr int s3 = 50;
			constexpr int s4 = -10;
			constexpr int s5 = 40;

			std::array<int, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<int, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::Subtract(destination.data(), source.data(), 5);
			Assert::AreEqual(d0 - s0, destination[0]);
			Assert::AreEqual(d1 - s1, destination[1]);
			Assert::AreEqual(d2 - s2, destination[2]);
			Assert::AreEqual(d3 - s3, destination[3]);
			Assert::AreEqual(d4 - s4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(SubtractTest)
		{
			constexpr int d0 = 3;
			constexpr int d1 = 2;
			constexpr int d2 = 9;
			constexpr int d3 = 5;
			constexpr int d4 = -1;
			constexpr int d5 = 4;

			constexpr int l0 = 30;
			constexpr int l1 = 20;
			constexpr int l2 = 90;
			constexpr int l3 = 50;
			constexpr int l4 = -10;
			constexpr int l5 = 40;

			constexpr int r0 = 300;
			constexpr int r1 = 200;
			constexpr int r2 = 900;
			constexpr int r3 = 500;
			constexpr int r4 = -100;
			constexpr int r5 = 400;

			std::array<int, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<int, 6> left{ l0, l1, l2, l3, l4, l5 };
			constexpr std::array<int, 6> right{ r0, r1, r2, r3, r4, r5 };

			PonyEngine::Math::Subtract(destination.data(), left.data(), right.data(), 5);
			Assert::AreEqual(l0 - r0, destination[0]);
			Assert::AreEqual(l1 - r1, destination[1]);
			Assert::AreEqual(l2 - r2, destination[2]);
			Assert::AreEqual(l3 - r3, destination[3]);
			Assert::AreEqual(l4 - r4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(MultiplyEqualArrayTest)
		{
			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = 9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			constexpr float s0 = 30;
			constexpr float s1 = 20;
			constexpr float s2 = 90;
			constexpr float s3 = 50;
			constexpr float s4 = -10;
			constexpr float s5 = 40;

			std::array<float, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<float, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::Multiply(destination.data(), source.data(), 5);
			Assert::AreEqual(d0 * s0, destination[0]);
			Assert::AreEqual(d1 * s1, destination[1]);
			Assert::AreEqual(d2 * s2, destination[2]);
			Assert::AreEqual(d3 * s3, destination[3]);
			Assert::AreEqual(d4 * s4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(MultiplyArrayTest)
		{
			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = 9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			constexpr float l0 = 30;
			constexpr float l1 = 20;
			constexpr float l2 = 90;
			constexpr float l3 = 50;
			constexpr float l4 = -10;
			constexpr float l5 = 40;

			constexpr float r0 = 300;
			constexpr float r1 = 200;
			constexpr float r2 = 900;
			constexpr float r3 = 500;
			constexpr float r4 = -100;
			constexpr float r5 = 400;

			std::array<float, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<float, 6> left{ l0, l1, l2, l3, l4, l5 };
			constexpr std::array<float, 6> right{ r0, r1, r2, r3, r4, r5 };

			PonyEngine::Math::Multiply(destination.data(), left.data(), right.data(), 5);
			Assert::AreEqual(l0 * r0, destination[0]);
			Assert::AreEqual(l1 * r1, destination[1]);
			Assert::AreEqual(l2 * r2, destination[2]);
			Assert::AreEqual(l3 * r3, destination[3]);
			Assert::AreEqual(l4 * r4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(MultiplyEqualTest)
		{
			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = 9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			constexpr float multiplier = 10;

			std::array<float, 6> destination{ d0, d1, d2, d3, d4, d5 };

			PonyEngine::Math::Multiply(destination.data(), multiplier, 5);
			Assert::AreEqual(d0 * multiplier, destination[0]);
			Assert::AreEqual(d1 * multiplier, destination[1]);
			Assert::AreEqual(d2 * multiplier, destination[2]);
			Assert::AreEqual(d3 * multiplier, destination[3]);
			Assert::AreEqual(d4 * multiplier, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(MultiplyTest)
		{
			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = 9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			constexpr float l0 = 30;
			constexpr float l1 = 20;
			constexpr float l2 = 90;
			constexpr float l3 = 50;
			constexpr float l4 = -10;
			constexpr float l5 = 40;

			constexpr float multiplier = 10;

			std::array<float, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<float, 6> left{ l0, l1, l2, l3, l4, l5 };

			PonyEngine::Math::Multiply(destination.data(), left.data(), multiplier, 5);
			Assert::AreEqual(l0 * multiplier, destination[0]);
			Assert::AreEqual(l1 * multiplier, destination[1]);
			Assert::AreEqual(l2 * multiplier, destination[2]);
			Assert::AreEqual(l3 * multiplier, destination[3]);
			Assert::AreEqual(l4 * multiplier, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(DivideEqualArrayTest)
		{
			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = 9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			constexpr float s0 = 30;
			constexpr float s1 = 20;
			constexpr float s2 = 90;
			constexpr float s3 = 50;
			constexpr float s4 = -10;
			constexpr float s5 = 40;

			std::array<float, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<float, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::Divide(destination.data(), source.data(), 5);
			Assert::AreEqual(d0 / s0, destination[0]);
			Assert::AreEqual(d1 / s1, destination[1]);
			Assert::AreEqual(d2 / s2, destination[2]);
			Assert::AreEqual(d3 / s3, destination[3]);
			Assert::AreEqual(d4 / s4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(DivideArrayTest)
		{
			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = 9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			constexpr float l0 = 30;
			constexpr float l1 = 20;
			constexpr float l2 = 90;
			constexpr float l3 = 50;
			constexpr float l4 = -10;
			constexpr float l5 = 40;

			constexpr float r0 = 300;
			constexpr float r1 = 200;
			constexpr float r2 = 900;
			constexpr float r3 = 500;
			constexpr float r4 = -100;
			constexpr float r5 = 400;

			std::array<float, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<float, 6> left{ l0, l1, l2, l3, l4, l5 };
			constexpr std::array<float, 6> right{ r0, r1, r2, r3, r4, r5 };

			PonyEngine::Math::Divide(destination.data(), left.data(), right.data(), 5);
			Assert::AreEqual(l0 / r0, destination[0]);
			Assert::AreEqual(l1 / r1, destination[1]);
			Assert::AreEqual(l2 / r2, destination[2]);
			Assert::AreEqual(l3 / r3, destination[3]);
			Assert::AreEqual(l4 / r4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(DivideEqualTest)
		{
			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = 9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			constexpr float divisor = 10;

			std::array<float, 6> destination{ d0, d1, d2, d3, d4, d5 };

			PonyEngine::Math::Divide(destination.data(), divisor, 5);
			Assert::AreEqual(static_cast<double>(d0 / divisor), static_cast<double>(destination[0]), 0.0000001);
			Assert::AreEqual(static_cast<double>(d1 / divisor), static_cast<double>(destination[1]), 0.0000001);
			Assert::AreEqual(static_cast<double>(d2 / divisor), static_cast<double>(destination[2]), 0.0000001);
			Assert::AreEqual(static_cast<double>(d3 / divisor), static_cast<double>(destination[3]), 0.0000001);
			Assert::AreEqual(static_cast<double>(d4 / divisor), static_cast<double>(destination[4]), 0.0000001);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(DivideTest)
		{
			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = 9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			constexpr float l0 = 30;
			constexpr float l1 = 20;
			constexpr float l2 = 90;
			constexpr float l3 = 50;
			constexpr float l4 = -10;
			constexpr float l5 = 40;

			constexpr float divisor = 10;

			std::array<float, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<float, 6> left{ l0, l1, l2, l3, l4, l5 };

			PonyEngine::Math::Divide(destination.data(), left.data(), divisor, 5);
			Assert::AreEqual(l0 / divisor, destination[0]);
			Assert::AreEqual(l1 / divisor, destination[1]);
			Assert::AreEqual(l2 / divisor, destination[2]);
			Assert::AreEqual(l3 / divisor, destination[3]);
			Assert::AreEqual(l4 / divisor, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(NegateTest)
		{
			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = -9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			std::array<float, 6> destination{ d0, d1, d2, d3, d4, d5 };

			PonyEngine::Math::Negate(destination.data(), 5);
			Assert::AreEqual(-d0, destination[0]);
			Assert::AreEqual(-d1, destination[1]);
			Assert::AreEqual(-d2, destination[2]);
			Assert::AreEqual(-d3, destination[3]);
			Assert::AreEqual(-d4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(NegateArrayTest)
		{
			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = -9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			constexpr float r0 = 300;
			constexpr float r1 = 200;
			constexpr float r2 = 900;
			constexpr float r3 = 500;
			constexpr float r4 = -100;
			constexpr float r5 = 400;

			std::array<float, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<float, 6> right{ r0, r1, r2, r3, r4, r5 };

			PonyEngine::Math::Negate(destination.data(), right.data(), 5);
			Assert::AreEqual(-r0, destination[0]);
			Assert::AreEqual(-r1, destination[1]);
			Assert::AreEqual(-r2, destination[2]);
			Assert::AreEqual(-r3, destination[3]);
			Assert::AreEqual(-r4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(IsFiniteTest)
		{
			const float nan = std::numeric_limits<float>::quiet_NaN();

			std::array<float, 6> numbers{ 0, 5, 7, -4, -6, nan };
			Assert::IsTrue(PonyEngine::Math::IsFinite(numbers.data(), 5));

			numbers[0] = nan;
			numbers[5] = 3;
			Assert::IsFalse(PonyEngine::Math::IsFinite(numbers.data(), 5));

			numbers[0] = 4;
			numbers[2] = nan;
			Assert::IsFalse(PonyEngine::Math::IsFinite(numbers.data(), 5));
		}

		static constexpr std::array<float, 3> ArithmeticsConstexpr()
		{
			constexpr std::array<float, 3> left{ 2, 3, 4 };
			constexpr std::array<float, 3> right{ 5, 6, 7 };
			constexpr float value = 8;

			std::array<float, 3> destination{ 10, 20, 30 };

			PonyEngine::Math::Add(destination.data(), right.data(), 3);
			PonyEngine::Math::Add(destination.data(), left.data(), right.data(), 3);

			PonyEngine::Math::Subtract(destination.data(), right.data(), 3);
			PonyEngine::Math::Subtract(destination.data(), left.data(), right.data(), 3);

			PonyEngine::Math::Multiply(destination.data(), right.data(), 3);
			PonyEngine::Math::Multiply(destination.data(), left.data(), right.data(), 3);
			PonyEngine::Math::Multiply(destination.data(), value, 3);
			PonyEngine::Math::Multiply(destination.data(), left.data(), value, 3);

			PonyEngine::Math::Divide(destination.data(), right.data(), 3);
			PonyEngine::Math::Divide(destination.data(), left.data(), right.data(), 3);
			PonyEngine::Math::Divide(destination.data(), value, 3);
			PonyEngine::Math::Divide(destination.data(), left.data(), value, 3);

			PonyEngine::Math::Negate(destination.data(), 3);
			PonyEngine::Math::Negate(destination.data(), right.data(), 3);

			return destination;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			constexpr std::array<float, 3> destination = ArithmeticsConstexpr();
		}
	};
}
