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
import <cstddef>;

import PonyEngine.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(ArrayArithmeticsTests)
	{
		TEST_METHOD(CopyShortTest)
		{
			constexpr short s0 = 30;
			constexpr short s1 = 20;
			constexpr short s2 = 90;
			constexpr short s3 = 50;
			constexpr short s4 = -10;
			constexpr short s5 = 40;

			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = 9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			std::array<short, 6> destination { d0, d1, d2, d3, d4, d5 };
			constexpr std::array<short, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::Copy(destination.data(), source.data(), 5);
			Assert::AreEqual(s0, destination[0]);
			Assert::AreEqual(s1, destination[1]);
			Assert::AreEqual(s2, destination[2]);
			Assert::AreEqual(s3, destination[3]);
			Assert::AreEqual(s4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(CopyFloatTest)
		{
			constexpr float s0 = 30;
			constexpr float s1 = 20;
			constexpr float s2 = 90;
			constexpr float s3 = 50;
			constexpr float s4 = -10;
			constexpr float s5 = 40;

			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = 9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			std::array<float, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<float, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::Copy(destination.data(), source.data(), 5);
			Assert::AreEqual(s0, destination[0]);
			Assert::AreEqual(s1, destination[1]);
			Assert::AreEqual(s2, destination[2]);
			Assert::AreEqual(s3, destination[3]);
			Assert::AreEqual(s4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(CastTest)
		{
			constexpr float s0 = 30.3;
			constexpr float s1 = 20.2;
			constexpr float s2 = 90.6;
			constexpr float s3 = 50.8;
			constexpr float s4 = -10.1;
			constexpr float s5 = 40.7;

			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = 9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<float, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::Cast(destination.data(), source.data(), 5);
			Assert::AreEqual(static_cast<short>(s0), destination[0]);
			Assert::AreEqual(static_cast<short>(s1), destination[1]);
			Assert::AreEqual(static_cast<short>(s2), destination[2]);
			Assert::AreEqual(static_cast<short>(s3), destination[3]);
			Assert::AreEqual(static_cast<short>(s4), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(AddEqualShortTest)
		{
			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = 9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			constexpr short s0 = 30;
			constexpr short s1 = 20;
			constexpr short s2 = 90;
			constexpr short s3 = 50;
			constexpr short s4 = -10;
			constexpr short s5 = 40;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<short, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::Add(destination.data(), source.data(), 5);
			Assert::AreEqual(static_cast<short>(d0 + s0), destination[0]);
			Assert::AreEqual(static_cast<short>(d1 + s1), destination[1]);
			Assert::AreEqual(static_cast<short>(d2 + s2), destination[2]);
			Assert::AreEqual(static_cast<short>(d3 + s3), destination[3]);
			Assert::AreEqual(static_cast<short>(d4 + s4), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(AddEqualFloatTest)
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

			PonyEngine::Math::Add(destination.data(), source.data(), 5);
			Assert::AreEqual(d0 + s0, destination[0]);
			Assert::AreEqual(d1 + s1, destination[1]);
			Assert::AreEqual(d2 + s2, destination[2]);
			Assert::AreEqual(d3 + s3, destination[3]);
			Assert::AreEqual(d4 + s4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(AddShortTest)
		{
			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = 9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			constexpr short l0 = 30;
			constexpr short l1 = 20;
			constexpr short l2 = 90;
			constexpr short l3 = 50;
			constexpr short l4 = -10;
			constexpr short l5 = 40;

			constexpr short r0 = 300;
			constexpr short r1 = 200;
			constexpr short r2 = 900;
			constexpr short r3 = 500;
			constexpr short r4 = -100;
			constexpr short r5 = 400;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<short, 6> left{ l0, l1, l2, l3, l4, l5 };
			constexpr std::array<short, 6> right{ r0, r1, r2, r3, r4, r5 };

			PonyEngine::Math::Add(destination.data(), left.data(), right.data(), 5);
			Assert::AreEqual(static_cast<short>(l0 + r0), destination[0]);
			Assert::AreEqual(static_cast<short>(l1 + r1), destination[1]);
			Assert::AreEqual(static_cast<short>(l2 + r2), destination[2]);
			Assert::AreEqual(static_cast<short>(l3 + r3), destination[3]);
			Assert::AreEqual(static_cast<short>(l4 + r4), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(AddFloatTest)
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

			PonyEngine::Math::Add(destination.data(), left.data(), right.data(), 5);
			Assert::AreEqual(l0 + r0, destination[0]);
			Assert::AreEqual(l1 + r1, destination[1]);
			Assert::AreEqual(l2 + r2, destination[2]);
			Assert::AreEqual(l3 + r3, destination[3]);
			Assert::AreEqual(l4 + r4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(SubtractEqualShortTest)
		{
			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = 9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			constexpr short s0 = 30;
			constexpr short s1 = 20;
			constexpr short s2 = 90;
			constexpr short s3 = 50;
			constexpr short s4 = -10;
			constexpr short s5 = 40;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<short, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::Subtract(destination.data(), source.data(), 5);
			Assert::AreEqual(static_cast<short>(d0 - s0), destination[0]);
			Assert::AreEqual(static_cast<short>(d1 - s1), destination[1]);
			Assert::AreEqual(static_cast<short>(d2 - s2), destination[2]);
			Assert::AreEqual(static_cast<short>(d3 - s3), destination[3]);
			Assert::AreEqual(static_cast<short>(d4 - s4), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(SubtractEqualFloatTest)
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

			PonyEngine::Math::Subtract(destination.data(), source.data(), 5);
			Assert::AreEqual(d0 - s0, destination[0]);
			Assert::AreEqual(d1 - s1, destination[1]);
			Assert::AreEqual(d2 - s2, destination[2]);
			Assert::AreEqual(d3 - s3, destination[3]);
			Assert::AreEqual(d4 - s4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(SubtractShortTest)
		{
			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = 9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			constexpr short l0 = 30;
			constexpr short l1 = 20;
			constexpr short l2 = 90;
			constexpr short l3 = 50;
			constexpr short l4 = -10;
			constexpr short l5 = 40;

			constexpr short r0 = 300;
			constexpr short r1 = 200;
			constexpr short r2 = 900;
			constexpr short r3 = 500;
			constexpr short r4 = -100;
			constexpr short r5 = 400;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<short, 6> left{ l0, l1, l2, l3, l4, l5 };
			constexpr std::array<short, 6> right{ r0, r1, r2, r3, r4, r5 };

			PonyEngine::Math::Subtract(destination.data(), left.data(), right.data(), 5);
			Assert::AreEqual(static_cast<short>(l0 - r0), destination[0]);
			Assert::AreEqual(static_cast<short>(l1 - r1), destination[1]);
			Assert::AreEqual(static_cast<short>(l2 - r2), destination[2]);
			Assert::AreEqual(static_cast<short>(l3 - r3), destination[3]);
			Assert::AreEqual(static_cast<short>(l4 - r4), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(SubtractFloatTest)
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

			PonyEngine::Math::Subtract(destination.data(), left.data(), right.data(), 5);
			Assert::AreEqual(l0 - r0, destination[0]);
			Assert::AreEqual(l1 - r1, destination[1]);
			Assert::AreEqual(l2 - r2, destination[2]);
			Assert::AreEqual(l3 - r3, destination[3]);
			Assert::AreEqual(l4 - r4, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(MultiplyEqualArrayShortTest)
		{
			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = 9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			constexpr short s0 = 30;
			constexpr short s1 = 20;
			constexpr short s2 = 90;
			constexpr short s3 = 50;
			constexpr short s4 = -10;
			constexpr short s5 = 40;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<short, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::Multiply(destination.data(), source.data(), 5);
			Assert::AreEqual(static_cast<short>(d0 * s0), destination[0]);
			Assert::AreEqual(static_cast<short>(d1 * s1), destination[1]);
			Assert::AreEqual(static_cast<short>(d2 * s2), destination[2]);
			Assert::AreEqual(static_cast<short>(d3 * s3), destination[3]);
			Assert::AreEqual(static_cast<short>(d4 * s4), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(MultiplyEqualArrayFloatTest)
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

		TEST_METHOD(MultiplyArrayShortTest)
		{
			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = 9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			constexpr short l0 = 30;
			constexpr short l1 = 20;
			constexpr short l2 = 90;
			constexpr short l3 = 50;
			constexpr short l4 = -10;
			constexpr short l5 = 40;

			constexpr short r0 = 300;
			constexpr short r1 = 200;
			constexpr short r2 = 900;
			constexpr short r3 = 500;
			constexpr short r4 = -100;
			constexpr short r5 = 400;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<short, 6> left{ l0, l1, l2, l3, l4, l5 };
			constexpr std::array<short, 6> right{ r0, r1, r2, r3, r4, r5 };

			PonyEngine::Math::Multiply(destination.data(), left.data(), right.data(), 5);
			Assert::AreEqual(static_cast<short>(l0 * r0), destination[0]);
			Assert::AreEqual(static_cast<short>(l1 * r1), destination[1]);
			Assert::AreEqual(static_cast<short>(l2 * r2), destination[2]);
			Assert::AreEqual(static_cast<short>(l3 * r3), destination[3]);
			Assert::AreEqual(static_cast<short>(l4 * r4), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(MultiplyArrayFloatTest)
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

		TEST_METHOD(MultiplyEqualShortTest)
		{
			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = 9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			constexpr float multiplier = 10;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };

			PonyEngine::Math::Multiply(destination.data(), multiplier, 5);
			Assert::AreEqual(static_cast<short>(d0 * multiplier), destination[0]);
			Assert::AreEqual(static_cast<short>(d1 * multiplier), destination[1]);
			Assert::AreEqual(static_cast<short>(d2 * multiplier), destination[2]);
			Assert::AreEqual(static_cast<short>(d3 * multiplier), destination[3]);
			Assert::AreEqual(static_cast<short>(d4 * multiplier), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(MultiplyEqualFloatTest)
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

		TEST_METHOD(MultiplyShortTest)
		{
			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = 9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			constexpr short l0 = 30;
			constexpr short l1 = 20;
			constexpr short l2 = 90;
			constexpr short l3 = 50;
			constexpr short l4 = -10;
			constexpr short l5 = 40;

			constexpr float multiplier = 10;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<short, 6> left{ l0, l1, l2, l3, l4, l5 };

			PonyEngine::Math::Multiply(destination.data(), left.data(), multiplier, 5);
			Assert::AreEqual(static_cast<short>(l0 * multiplier), destination[0]);
			Assert::AreEqual(static_cast<short>(l1 * multiplier), destination[1]);
			Assert::AreEqual(static_cast<short>(l2 * multiplier), destination[2]);
			Assert::AreEqual(static_cast<short>(l3 * multiplier), destination[3]);
			Assert::AreEqual(static_cast<short>(l4 * multiplier), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(MultiplyFloatTest)
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

		TEST_METHOD(DivideEqualArrayShortTest)
		{
			constexpr short d0 = 300;
			constexpr short d1 = 250;
			constexpr short d2 = 900;
			constexpr short d3 = 5;
			constexpr short d4 = -100;
			constexpr short d5 = 4;

			constexpr short s0 = 30;
			constexpr short s1 = 20;
			constexpr short s2 = 90;
			constexpr short s3 = 50;
			constexpr short s4 = -10;
			constexpr short s5 = 40;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<short, 6> source{ s0, s1, s2, s3, s4, s5 };

			PonyEngine::Math::Divide(destination.data(), source.data(), 5);
			Assert::AreEqual(static_cast<short>(d0 / s0), destination[0]);
			Assert::AreEqual(static_cast<short>(d1 / s1), destination[1]);
			Assert::AreEqual(static_cast<short>(d2 / s2), destination[2]);
			Assert::AreEqual(static_cast<short>(d3 / s3), destination[3]);
			Assert::AreEqual(static_cast<short>(d4 / s4), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(DivideEqualArrayFloatTest)
		{
			constexpr float d0 = 300;
			constexpr float d1 = 250;
			constexpr float d2 = 900;
			constexpr float d3 = 5;
			constexpr float d4 = -100;
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

		TEST_METHOD(DivideArrayShortTest)
		{
			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = 9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			constexpr short l0 = 3000;
			constexpr short l1 = 2050;
			constexpr short l2 = 9000;
			constexpr short l3 = 50;
			constexpr short l4 = -1000;
			constexpr short l5 = 40;

			constexpr short r0 = 300;
			constexpr short r1 = 200;
			constexpr short r2 = 900;
			constexpr short r3 = 500;
			constexpr short r4 = -100;
			constexpr short r5 = 400;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<short, 6> left{ l0, l1, l2, l3, l4, l5 };
			constexpr std::array<short, 6> right{ r0, r1, r2, r3, r4, r5 };

			PonyEngine::Math::Divide(destination.data(), left.data(), right.data(), 5);
			Assert::AreEqual(static_cast<short>(l0 / r0), destination[0]);
			Assert::AreEqual(static_cast<short>(l1 / r1), destination[1]);
			Assert::AreEqual(static_cast<short>(l2 / r2), destination[2]);
			Assert::AreEqual(static_cast<short>(l3 / r3), destination[3]);
			Assert::AreEqual(static_cast<short>(l4 / r4), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(DivideArrayFloatTest)
		{
			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = 9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			constexpr float l0 = 3000;
			constexpr float l1 = 2050;
			constexpr float l2 = 9000;
			constexpr float l3 = 50;
			constexpr float l4 = -1000;
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

		TEST_METHOD(DivideEqualShortTest)
		{
			constexpr short d0 = 300;
			constexpr short d1 = 200;
			constexpr short d2 = 900;
			constexpr short d3 = 5;
			constexpr short d4 = -100;
			constexpr short d5 = 4;

			constexpr float divisor = 10;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };

			PonyEngine::Math::Divide(destination.data(), divisor, 5);
			Assert::AreEqual(static_cast<short>(d0 / divisor), destination[0]);
			Assert::AreEqual(static_cast<short>(d1 / divisor), destination[1]);
			Assert::AreEqual(static_cast<short>(d2 / divisor), destination[2]);
			Assert::AreEqual(static_cast<short>(d3 / divisor), destination[3]);
			Assert::AreEqual(static_cast<short>(d4 / divisor), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(DivideEqualFloatTest)
		{
			constexpr float d0 = 300;
			constexpr float d1 = 200;
			constexpr float d2 = 900;
			constexpr float d3 = 5;
			constexpr float d4 = -100;
			constexpr float d5 = 4;

			constexpr float divisor = 10;

			std::array<float, 6> destination{ d0, d1, d2, d3, d4, d5 };

			PonyEngine::Math::Divide(destination.data(), divisor, 5);
			Assert::AreEqual(d0 / divisor, destination[0]);
			Assert::AreEqual(d1 / divisor, destination[1]);
			Assert::AreEqual(d2 / divisor, destination[2]);
			Assert::AreEqual(d3 / divisor, destination[3]);
			Assert::AreEqual(d4 / divisor, destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(DivideShortTest)
		{
			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = 9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			constexpr short l0 = 300;
			constexpr short l1 = 250;
			constexpr short l2 = 900;
			constexpr short l3 = 5;
			constexpr short l4 = -100;
			constexpr short l5 = 40;

			constexpr float divisor = 10;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<short, 6> left{ l0, l1, l2, l3, l4, l5 };

			PonyEngine::Math::Divide(destination.data(), left.data(), divisor, 5);
			Assert::AreEqual(static_cast<short>(l0 / divisor), destination[0]);
			Assert::AreEqual(static_cast<short>(l1 / divisor), destination[1]);
			Assert::AreEqual(static_cast<short>(l2 / divisor), destination[2]);
			Assert::AreEqual(static_cast<short>(l3 / divisor), destination[3]);
			Assert::AreEqual(static_cast<short>(l4 / divisor), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(DivideFloatTest)
		{
			constexpr float d0 = 3;
			constexpr float d1 = 2;
			constexpr float d2 = 9;
			constexpr float d3 = 5;
			constexpr float d4 = -1;
			constexpr float d5 = 4;

			constexpr float l0 = 300;
			constexpr float l1 = 250;
			constexpr float l2 = 900;
			constexpr float l3 = 5;
			constexpr float l4 = -100;
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

		TEST_METHOD(NegateShortTest)
		{
			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = -9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };

			PonyEngine::Math::Negate(destination.data(), 5);
			Assert::AreEqual(static_cast<short>(-d0), destination[0]);
			Assert::AreEqual(static_cast<short>(-d1), destination[1]);
			Assert::AreEqual(static_cast<short>(-d2), destination[2]);
			Assert::AreEqual(static_cast<short>(-d3), destination[3]);
			Assert::AreEqual(static_cast<short>(-d4), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(NegateFloatTest)
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

		TEST_METHOD(NegateArrayShortTest)
		{
			constexpr short d0 = 3;
			constexpr short d1 = 2;
			constexpr short d2 = -9;
			constexpr short d3 = 5;
			constexpr short d4 = -1;
			constexpr short d5 = 4;

			constexpr short r0 = 300;
			constexpr short r1 = 200;
			constexpr short r2 = 900;
			constexpr short r3 = 500;
			constexpr short r4 = -100;
			constexpr short r5 = 400;

			std::array<short, 6> destination{ d0, d1, d2, d3, d4, d5 };
			constexpr std::array<short, 6> right{ r0, r1, r2, r3, r4, r5 };

			PonyEngine::Math::Negate(destination.data(), right.data(), 5);
			Assert::AreEqual(static_cast<short>(-r0), destination[0]);
			Assert::AreEqual(static_cast<short>(-r1), destination[1]);
			Assert::AreEqual(static_cast<short>(-r2), destination[2]);
			Assert::AreEqual(static_cast<short>(-r3), destination[3]);
			Assert::AreEqual(static_cast<short>(-r4), destination[4]);
			Assert::AreEqual(d5, destination[5]);
		}

		TEST_METHOD(NegateArrayFloatTest)
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

		static constexpr std::array<int, 3> ArithmeticsConstexpr()
		{
			constexpr std::array<int, 3> left{ 2, 3, 4 };
			constexpr std::array<int, 3> right{ 5, 6, 7 };
			constexpr int value = 8;

			std::array<int, 3> destination{ 10, 20, 30 };

			PonyEngine::Math::Copy(destination.data(), left.data(), 3);

			PonyEngine::Math::Cast(destination.data(), left.data(), 3);

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
			constexpr std::array<int, 3> destination = ArithmeticsConstexpr();
		}
	};
}
