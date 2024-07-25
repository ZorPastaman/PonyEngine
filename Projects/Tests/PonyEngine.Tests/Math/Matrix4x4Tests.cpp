/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <format>;
import <ostream>;
import <string>;

import PonyEngine.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(Matrix4x4Tests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyEngine::Math::Matrix4x4<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix4x4<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyEngine::Math::Matrix4x4<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix4x4<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyEngine::Math::Matrix4x4<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix4x4<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix4x4<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix4x4<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyEngine::Math::Matrix4x4<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Matrix4x4<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Matrix4x4<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Matrix4x4<double>::ComputationalType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{4}, PonyEngine::Math::Matrix4x4<float>::Dimension);
			Assert::AreEqual(std::size_t{16}, PonyEngine::Math::Matrix4x4<float>::ComponentCount);

			Assert::AreEqual(std::size_t{4}, PonyEngine::Math::Matrix4x4<short>::Dimension);
			Assert::AreEqual(std::size_t{16}, PonyEngine::Math::Matrix4x4<short>::ComponentCount);
		}

		TEST_METHOD(RowToVector4ShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

			const PonyEngine::Math::Vector4<short> row0 = matrix[0];
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());
			Assert::AreEqual(m02, row0.Z());
			Assert::AreEqual(m03, row0.W());

			const PonyEngine::Math::Vector4<short> row1 = matrix[1];
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
			Assert::AreEqual(m12, row1.Z());
			Assert::AreEqual(m13, row1.W());

			const PonyEngine::Math::Vector4<short> row2 = matrix[2];
			Assert::AreEqual(m20, row2.X());
			Assert::AreEqual(m21, row2.Y());
			Assert::AreEqual(m22, row2.Z());
			Assert::AreEqual(m23, row2.W());

			const PonyEngine::Math::Vector4<short> row3 = matrix[3];
			Assert::AreEqual(m30, row3.X());
			Assert::AreEqual(m31, row3.Y());
			Assert::AreEqual(m32, row3.Z());
			Assert::AreEqual(m33, row3.W());
		}

		TEST_METHOD(RowToVector4FloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

			const PonyEngine::Math::Vector4<float> row0 = matrix[0];
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());
			Assert::AreEqual(m02, row0.Z());
			Assert::AreEqual(m03, row0.W());

			const PonyEngine::Math::Vector4<float> row1 = matrix[1];
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
			Assert::AreEqual(m12, row1.Z());
			Assert::AreEqual(m13, row1.W());

			const PonyEngine::Math::Vector4<float> row2 = matrix[2];
			Assert::AreEqual(m20, row2.X());
			Assert::AreEqual(m21, row2.Y());
			Assert::AreEqual(m22, row2.Z());
			Assert::AreEqual(m23, row2.W());

			const PonyEngine::Math::Vector4<float> row3 = matrix[3];
			Assert::AreEqual(m30, row3.X());
			Assert::AreEqual(m31, row3.Y());
			Assert::AreEqual(m32, row3.Z());
			Assert::AreEqual(m33, row3.W());
		}

		TEST_METHOD(CastTest)
		{
			constexpr auto floatMatrix = PonyEngine::Math::Matrix4x4<float>(3.1f, -2.2f, 4.4f, -2.1f, -5.9f, 4.8f, 7.1f, -6.5f, 12.f, 11.5f, -13.4f, -12.1f, 15.8f, -16.9f, 10.f, -1.f);
			const auto intMatrix = static_cast<PonyEngine::Math::Matrix4x4<int>>(floatMatrix);
			Assert::AreEqual(3, intMatrix.M00());
			Assert::AreEqual(-2, intMatrix.M10());
			Assert::AreEqual(4, intMatrix.M20());
			Assert::AreEqual(-2, intMatrix.M30());
			Assert::AreEqual(-5, intMatrix.M01());
			Assert::AreEqual(4, intMatrix.M11());
			Assert::AreEqual(7, intMatrix.M21());
			Assert::AreEqual(-6, intMatrix.M31());
			Assert::AreEqual(12, intMatrix.M02());
			Assert::AreEqual(11, intMatrix.M12());
			Assert::AreEqual(-13, intMatrix.M22());
			Assert::AreEqual(-12, intMatrix.M32());
			Assert::AreEqual(15, intMatrix.M03());
			Assert::AreEqual(-16, intMatrix.M13());
			Assert::AreEqual(10, intMatrix.M23());
			Assert::AreEqual(-1, intMatrix.M33());
		}

		TEST_METHOD(AccessOperatorReadShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

			Assert::AreEqual(m00, matrix[0][0]);
			Assert::AreEqual(m01, matrix[0][1]);
			Assert::AreEqual(m02, matrix[0][2]);
			Assert::AreEqual(m03, matrix[0][3]);
			Assert::AreEqual(m10, matrix[1][0]);
			Assert::AreEqual(m11, matrix[1][1]);
			Assert::AreEqual(m12, matrix[1][2]);
			Assert::AreEqual(m13, matrix[1][3]);
			Assert::AreEqual(m20, matrix[2][0]);
			Assert::AreEqual(m21, matrix[2][1]);
			Assert::AreEqual(m22, matrix[2][2]);
			Assert::AreEqual(m23, matrix[2][3]);
			Assert::AreEqual(m30, matrix[3][0]);
			Assert::AreEqual(m31, matrix[3][1]);
			Assert::AreEqual(m32, matrix[3][2]);
			Assert::AreEqual(m33, matrix[3][3]);
		}

		TEST_METHOD(AccessOperatorReadFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

			Assert::AreEqual(m00, matrix[0][0]);
			Assert::AreEqual(m01, matrix[0][1]);
			Assert::AreEqual(m02, matrix[0][2]);
			Assert::AreEqual(m03, matrix[0][3]);
			Assert::AreEqual(m10, matrix[1][0]);
			Assert::AreEqual(m11, matrix[1][1]);
			Assert::AreEqual(m12, matrix[1][2]);
			Assert::AreEqual(m13, matrix[1][3]);
			Assert::AreEqual(m20, matrix[2][0]);
			Assert::AreEqual(m21, matrix[2][1]);
			Assert::AreEqual(m22, matrix[2][2]);
			Assert::AreEqual(m23, matrix[2][3]);
			Assert::AreEqual(m30, matrix[3][0]);
			Assert::AreEqual(m31, matrix[3][1]);
			Assert::AreEqual(m32, matrix[3][2]);
			Assert::AreEqual(m33, matrix[3][3]);
		}

		TEST_METHOD(AccessOperatorWriteShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

			constexpr short m00New = 20;
			constexpr short m10New = 30;
			constexpr short m20New = 30;
			constexpr short m30New = 21;
			constexpr short m01New = -40;
			constexpr short m11New = -50;
			constexpr short m21New = 330;
			constexpr short m31New = -10;
			constexpr short m02New = 60;
			constexpr short m12New = 70;
			constexpr short m22New = 190;
			constexpr short m32New = -100;
			constexpr short m03New = 160;
			constexpr short m13New = 170;
			constexpr short m23New = 180;
			constexpr short m33New = -130;
			matrix[0][0] = m00New;
			matrix[0][1] = m01New;
			matrix[0][2] = m02New;
			matrix[0][3] = m03New;
			matrix[1][0] = m10New;
			matrix[1][1] = m11New;
			matrix[1][2] = m12New;
			matrix[1][3] = m13New;
			matrix[2][0] = m20New;
			matrix[2][1] = m21New;
			matrix[2][2] = m22New;
			matrix[2][3] = m23New;
			matrix[3][0] = m30New;
			matrix[3][1] = m31New;
			matrix[3][2] = m32New;
			matrix[3][3] = m33New;

			Assert::AreEqual(m00New, matrix[0][0]);
			Assert::AreEqual(m01New, matrix[0][1]);
			Assert::AreEqual(m02New, matrix[0][2]);
			Assert::AreEqual(m03New, matrix[0][3]);
			Assert::AreEqual(m10New, matrix[1][0]);
			Assert::AreEqual(m11New, matrix[1][1]);
			Assert::AreEqual(m12New, matrix[1][2]);
			Assert::AreEqual(m13New, matrix[1][3]);
			Assert::AreEqual(m20New, matrix[2][0]);
			Assert::AreEqual(m21New, matrix[2][1]);
			Assert::AreEqual(m22New, matrix[2][2]);
			Assert::AreEqual(m23New, matrix[2][3]);
			Assert::AreEqual(m30New, matrix[3][0]);
			Assert::AreEqual(m31New, matrix[3][1]);
			Assert::AreEqual(m32New, matrix[3][2]);
			Assert::AreEqual(m33New, matrix[3][3]);
		}

		TEST_METHOD(AccessOperatorWriteFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

			constexpr float m00New = 20;
			constexpr float m10New = 30;
			constexpr float m20New = 30;
			constexpr float m30New = 21;
			constexpr float m01New = -40;
			constexpr float m11New = -50;
			constexpr float m21New = 330;
			constexpr float m31New = -10;
			constexpr float m02New = 60;
			constexpr float m12New = 70;
			constexpr float m22New = 190;
			constexpr float m32New = -100;
			constexpr float m03New = 160;
			constexpr float m13New = 170;
			constexpr float m23New = 180;
			constexpr float m33New = -130;
			matrix[0][0] = m00New;
			matrix[0][1] = m01New;
			matrix[0][2] = m02New;
			matrix[0][3] = m03New;
			matrix[1][0] = m10New;
			matrix[1][1] = m11New;
			matrix[1][2] = m12New;
			matrix[1][3] = m13New;
			matrix[2][0] = m20New;
			matrix[2][1] = m21New;
			matrix[2][2] = m22New;
			matrix[2][3] = m23New;
			matrix[3][0] = m30New;
			matrix[3][1] = m31New;
			matrix[3][2] = m32New;
			matrix[3][3] = m33New;

			Assert::AreEqual(m00New, matrix[0][0]);
			Assert::AreEqual(m01New, matrix[0][1]);
			Assert::AreEqual(m02New, matrix[0][2]);
			Assert::AreEqual(m03New, matrix[0][3]);
			Assert::AreEqual(m10New, matrix[1][0]);
			Assert::AreEqual(m11New, matrix[1][1]);
			Assert::AreEqual(m12New, matrix[1][2]);
			Assert::AreEqual(m13New, matrix[1][3]);
			Assert::AreEqual(m20New, matrix[2][0]);
			Assert::AreEqual(m21New, matrix[2][1]);
			Assert::AreEqual(m22New, matrix[2][2]);
			Assert::AreEqual(m23New, matrix[2][3]);
			Assert::AreEqual(m30New, matrix[3][0]);
			Assert::AreEqual(m31New, matrix[3][1]);
			Assert::AreEqual(m32New, matrix[3][2]);
			Assert::AreEqual(m33New, matrix[3][3]);
		}

		TEST_METHOD(Vector4ToRowShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

			constexpr short m00New = 20;
			constexpr short m10New = 30;
			constexpr short m20New = 30;
			constexpr short m30New = 21;
			constexpr short m01New = -40;
			constexpr short m11New = -50;
			constexpr short m21New = 330;
			constexpr short m31New = -10;
			constexpr short m02New = 60;
			constexpr short m12New = 70;
			constexpr short m22New = 190;
			constexpr short m32New = -100;
			constexpr short m03New = 160;
			constexpr short m13New = 170;
			constexpr short m23New = 180;
			constexpr short m33New = -130;
			matrix[0] = PonyEngine::Math::Vector4<short>(m00New, m01New, m02New, m03New);
			matrix[1] = PonyEngine::Math::Vector4<short>(m10New, m11New, m12New, m13New);
			matrix[2] = PonyEngine::Math::Vector4<short>(m20New, m21New, m22New, m23New);
			matrix[3] = PonyEngine::Math::Vector4<short>(m30New, m31New, m32New, m33New);

			Assert::AreEqual(m00New, matrix[0][0]);
			Assert::AreEqual(m01New, matrix[0][1]);
			Assert::AreEqual(m02New, matrix[0][2]);
			Assert::AreEqual(m03New, matrix[0][3]);
			Assert::AreEqual(m10New, matrix[1][0]);
			Assert::AreEqual(m11New, matrix[1][1]);
			Assert::AreEqual(m12New, matrix[1][2]);
			Assert::AreEqual(m13New, matrix[1][3]);
			Assert::AreEqual(m20New, matrix[2][0]);
			Assert::AreEqual(m21New, matrix[2][1]);
			Assert::AreEqual(m22New, matrix[2][2]);
			Assert::AreEqual(m23New, matrix[2][3]);
			Assert::AreEqual(m30New, matrix[3][0]);
			Assert::AreEqual(m31New, matrix[3][1]);
			Assert::AreEqual(m32New, matrix[3][2]);
			Assert::AreEqual(m33New, matrix[3][3]);
		}

		TEST_METHOD(Vector4ToRowFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

			constexpr float m00New = 20;
			constexpr float m10New = 30;
			constexpr float m20New = 30;
			constexpr float m30New = 21;
			constexpr float m01New = -40;
			constexpr float m11New = -50;
			constexpr float m21New = 330;
			constexpr float m31New = -10;
			constexpr float m02New = 60;
			constexpr float m12New = 70;
			constexpr float m22New = 190;
			constexpr float m32New = -100;
			constexpr float m03New = 160;
			constexpr float m13New = 170;
			constexpr float m23New = 180;
			constexpr float m33New = -130;
			matrix[0] = PonyEngine::Math::Vector4<float>(m00New, m01New, m02New, m03New);
			matrix[1] = PonyEngine::Math::Vector4<float>(m10New, m11New, m12New, m13New);
			matrix[2] = PonyEngine::Math::Vector4<float>(m20New, m21New, m22New, m23New);
			matrix[3] = PonyEngine::Math::Vector4<float>(m30New, m31New, m32New, m33New);

			Assert::AreEqual(m00New, matrix[0][0]);
			Assert::AreEqual(m01New, matrix[0][1]);
			Assert::AreEqual(m02New, matrix[0][2]);
			Assert::AreEqual(m03New, matrix[0][3]);
			Assert::AreEqual(m10New, matrix[1][0]);
			Assert::AreEqual(m11New, matrix[1][1]);
			Assert::AreEqual(m12New, matrix[1][2]);
			Assert::AreEqual(m13New, matrix[1][3]);
			Assert::AreEqual(m20New, matrix[2][0]);
			Assert::AreEqual(m21New, matrix[2][1]);
			Assert::AreEqual(m22New, matrix[2][2]);
			Assert::AreEqual(m23New, matrix[2][3]);
			Assert::AreEqual(m30New, matrix[3][0]);
			Assert::AreEqual(m31New, matrix[3][1]);
			Assert::AreEqual(m32New, matrix[3][2]);
			Assert::AreEqual(m33New, matrix[3][3]);
		}

		TEST_METHOD(DefaultConstructorShortTest)
		{
			const auto defaultMatrix = PonyEngine::Math::Matrix4x4<short>();
			Assert::AreEqual(short{}, defaultMatrix.M00());
			Assert::AreEqual(short{}, defaultMatrix.M10());
			Assert::AreEqual(short{}, defaultMatrix.M20());
			Assert::AreEqual(short{}, defaultMatrix.M30());
			Assert::AreEqual(short{}, defaultMatrix.M01());
			Assert::AreEqual(short{}, defaultMatrix.M11());
			Assert::AreEqual(short{}, defaultMatrix.M21());
			Assert::AreEqual(short{}, defaultMatrix.M31());
			Assert::AreEqual(short{}, defaultMatrix.M02());
			Assert::AreEqual(short{}, defaultMatrix.M12());
			Assert::AreEqual(short{}, defaultMatrix.M22());
			Assert::AreEqual(short{}, defaultMatrix.M32());
			Assert::AreEqual(short{}, defaultMatrix.M03());
			Assert::AreEqual(short{}, defaultMatrix.M13());
			Assert::AreEqual(short{}, defaultMatrix.M23());
			Assert::AreEqual(short{}, defaultMatrix.M33());
		}

		TEST_METHOD(DefaultConstructorFloatTest)
		{
			const auto defaultMatrix = PonyEngine::Math::Matrix4x4<float>();
			Assert::AreEqual(float{}, defaultMatrix.M00());
			Assert::AreEqual(float{}, defaultMatrix.M10());
			Assert::AreEqual(float{}, defaultMatrix.M20());
			Assert::AreEqual(float{}, defaultMatrix.M30());
			Assert::AreEqual(float{}, defaultMatrix.M01());
			Assert::AreEqual(float{}, defaultMatrix.M11());
			Assert::AreEqual(float{}, defaultMatrix.M21());
			Assert::AreEqual(float{}, defaultMatrix.M31());
			Assert::AreEqual(float{}, defaultMatrix.M02());
			Assert::AreEqual(float{}, defaultMatrix.M12());
			Assert::AreEqual(float{}, defaultMatrix.M22());
			Assert::AreEqual(float{}, defaultMatrix.M32());
			Assert::AreEqual(float{}, defaultMatrix.M03());
			Assert::AreEqual(float{}, defaultMatrix.M13());
			Assert::AreEqual(float{}, defaultMatrix.M23());
			Assert::AreEqual(float{}, defaultMatrix.M33());
		}

		TEST_METHOD(ConstructorShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(ConstructorFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(ConstructorColumnShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto column0 = PonyEngine::Math::Vector4<short>(m00, m10, m20, m30);
			constexpr auto column1 = PonyEngine::Math::Vector4<short>(m01, m11, m21, m31);
			constexpr auto column2 = PonyEngine::Math::Vector4<short>(m02, m12, m22, m32);
			constexpr auto column3 = PonyEngine::Math::Vector4<short>(m03, m13, m23, m33);
			const auto matrix = PonyEngine::Math::Matrix4x4<short>(column0, column1, column2, column3);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(ConstructorColumnFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto column0 = PonyEngine::Math::Vector4<float>(m00, m10, m20, m30);
			constexpr auto column1 = PonyEngine::Math::Vector4<float>(m01, m11, m21, m31);
			constexpr auto column2 = PonyEngine::Math::Vector4<float>(m02, m12, m22, m32);
			constexpr auto column3 = PonyEngine::Math::Vector4<float>(m03, m13, m23, m33);
			const auto matrix = PonyEngine::Math::Matrix4x4<float>(column0, column1, column2, column3);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(ConstructorPointerShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr std::array<short, 16> array{ m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33 };
			const auto matrix = PonyEngine::Math::Matrix4x4<short>(array.data());
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(ConstructorPointerFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr std::array<float, 16> array{ m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33 };
			const auto matrix = PonyEngine::Math::Matrix4x4<float>(array.data());
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(ConstructorCopyShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto copiedMatrix = matrix;
			Assert::AreEqual(m00, copiedMatrix.M00());
			Assert::AreEqual(m10, copiedMatrix.M10());
			Assert::AreEqual(m20, copiedMatrix.M20());
			Assert::AreEqual(m30, copiedMatrix.M30());
			Assert::AreEqual(m01, copiedMatrix.M01());
			Assert::AreEqual(m11, copiedMatrix.M11());
			Assert::AreEqual(m21, copiedMatrix.M21());
			Assert::AreEqual(m31, copiedMatrix.M31());
			Assert::AreEqual(m02, copiedMatrix.M02());
			Assert::AreEqual(m12, copiedMatrix.M12());
			Assert::AreEqual(m22, copiedMatrix.M22());
			Assert::AreEqual(m32, copiedMatrix.M32());
			Assert::AreEqual(m03, copiedMatrix.M03());
			Assert::AreEqual(m13, copiedMatrix.M13());
			Assert::AreEqual(m23, copiedMatrix.M23());
			Assert::AreEqual(m33, copiedMatrix.M33());
		}

		TEST_METHOD(ConstructorCopyFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto copiedMatrix = matrix;
			Assert::AreEqual(m00, copiedMatrix.M00());
			Assert::AreEqual(m10, copiedMatrix.M10());
			Assert::AreEqual(m20, copiedMatrix.M20());
			Assert::AreEqual(m30, copiedMatrix.M30());
			Assert::AreEqual(m01, copiedMatrix.M01());
			Assert::AreEqual(m11, copiedMatrix.M11());
			Assert::AreEqual(m21, copiedMatrix.M21());
			Assert::AreEqual(m31, copiedMatrix.M31());
			Assert::AreEqual(m02, copiedMatrix.M02());
			Assert::AreEqual(m12, copiedMatrix.M12());
			Assert::AreEqual(m22, copiedMatrix.M22());
			Assert::AreEqual(m32, copiedMatrix.M32());
			Assert::AreEqual(m03, copiedMatrix.M03());
			Assert::AreEqual(m13, copiedMatrix.M13());
			Assert::AreEqual(m23, copiedMatrix.M23());
			Assert::AreEqual(m33, copiedMatrix.M33());
		}

		TEST_METHOD(ConstructorMoveShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto movedMatrix = std::move(matrix);
			Assert::AreEqual(m00, movedMatrix.M00());
			Assert::AreEqual(m10, movedMatrix.M10());
			Assert::AreEqual(m20, movedMatrix.M20());
			Assert::AreEqual(m30, movedMatrix.M30());
			Assert::AreEqual(m01, movedMatrix.M01());
			Assert::AreEqual(m11, movedMatrix.M11());
			Assert::AreEqual(m21, movedMatrix.M21());
			Assert::AreEqual(m31, movedMatrix.M31());
			Assert::AreEqual(m02, movedMatrix.M02());
			Assert::AreEqual(m12, movedMatrix.M12());
			Assert::AreEqual(m22, movedMatrix.M22());
			Assert::AreEqual(m32, movedMatrix.M32());
			Assert::AreEqual(m03, movedMatrix.M03());
			Assert::AreEqual(m13, movedMatrix.M13());
			Assert::AreEqual(m23, movedMatrix.M23());
			Assert::AreEqual(m33, movedMatrix.M33());
		}

		TEST_METHOD(ConstructorMoveFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto movedMatrix = std::move(matrix);
			Assert::AreEqual(m00, movedMatrix.M00());
			Assert::AreEqual(m10, movedMatrix.M10());
			Assert::AreEqual(m20, movedMatrix.M20());
			Assert::AreEqual(m30, movedMatrix.M30());
			Assert::AreEqual(m01, movedMatrix.M01());
			Assert::AreEqual(m11, movedMatrix.M11());
			Assert::AreEqual(m21, movedMatrix.M21());
			Assert::AreEqual(m31, movedMatrix.M31());
			Assert::AreEqual(m02, movedMatrix.M02());
			Assert::AreEqual(m12, movedMatrix.M12());
			Assert::AreEqual(m22, movedMatrix.M22());
			Assert::AreEqual(m32, movedMatrix.M32());
			Assert::AreEqual(m03, movedMatrix.M03());
			Assert::AreEqual(m13, movedMatrix.M13());
			Assert::AreEqual(m23, movedMatrix.M23());
			Assert::AreEqual(m33, movedMatrix.M33());
		}

		TEST_METHOD(ComponentAccessShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;

			auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());

			constexpr auto matrixC = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m20, matrixC.M20());
			Assert::AreEqual(m30, matrixC.M30());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(m21, matrixC.M21());
			Assert::AreEqual(m31, matrixC.M31());
			Assert::AreEqual(m02, matrixC.M02());
			Assert::AreEqual(m12, matrixC.M12());
			Assert::AreEqual(m22, matrixC.M22());
			Assert::AreEqual(m32, matrixC.M32());
			Assert::AreEqual(m03, matrixC.M03());
			Assert::AreEqual(m13, matrixC.M13());
			Assert::AreEqual(m23, matrixC.M23());
			Assert::AreEqual(m33, matrixC.M33());
		}

		TEST_METHOD(ComponentAccessFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;

			auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());

			constexpr auto matrixC = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m20, matrixC.M20());
			Assert::AreEqual(m30, matrixC.M30());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(m21, matrixC.M21());
			Assert::AreEqual(m31, matrixC.M31());
			Assert::AreEqual(m02, matrixC.M02());
			Assert::AreEqual(m12, matrixC.M12());
			Assert::AreEqual(m22, matrixC.M22());
			Assert::AreEqual(m32, matrixC.M32());
			Assert::AreEqual(m03, matrixC.M03());
			Assert::AreEqual(m13, matrixC.M13());
			Assert::AreEqual(m23, matrixC.M23());
			Assert::AreEqual(m33, matrixC.M33());
		}

		TEST_METHOD(DataShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;

			auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrix.Data()[0]);
			Assert::AreEqual(m10, matrix.Data()[1]);
			Assert::AreEqual(m20, matrix.Data()[2]);
			Assert::AreEqual(m30, matrix.Data()[3]);
			Assert::AreEqual(m01, matrix.Data()[4]);
			Assert::AreEqual(m11, matrix.Data()[5]);
			Assert::AreEqual(m21, matrix.Data()[6]);
			Assert::AreEqual(m31, matrix.Data()[7]);
			Assert::AreEqual(m02, matrix.Data()[8]);
			Assert::AreEqual(m12, matrix.Data()[9]);
			Assert::AreEqual(m22, matrix.Data()[10]);
			Assert::AreEqual(m32, matrix.Data()[11]);
			Assert::AreEqual(m03, matrix.Data()[12]);
			Assert::AreEqual(m13, matrix.Data()[13]);
			Assert::AreEqual(m23, matrix.Data()[14]);
			Assert::AreEqual(m33, matrix.Data()[15]);
			Assert::AreEqual(m00, matrix.Data(0)[0]);
			Assert::AreEqual(m10, matrix.Data(0)[1]);
			Assert::AreEqual(m20, matrix.Data(0)[2]);
			Assert::AreEqual(m30, matrix.Data(0)[3]);
			Assert::AreEqual(m01, matrix.Data(1)[0]);
			Assert::AreEqual(m11, matrix.Data(1)[1]);
			Assert::AreEqual(m21, matrix.Data(1)[2]);
			Assert::AreEqual(m31, matrix.Data(1)[3]);
			Assert::AreEqual(m02, matrix.Data(2)[0]);
			Assert::AreEqual(m12, matrix.Data(2)[1]);
			Assert::AreEqual(m22, matrix.Data(2)[2]);
			Assert::AreEqual(m32, matrix.Data(2)[3]);
			Assert::AreEqual(m03, matrix.Data(3)[0]);
			Assert::AreEqual(m13, matrix.Data(3)[1]);
			Assert::AreEqual(m23, matrix.Data(3)[2]);
			Assert::AreEqual(m33, matrix.Data(3)[3]);

			constexpr auto matrixC = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrixC.Data()[0]);
			Assert::AreEqual(m10, matrixC.Data()[1]);
			Assert::AreEqual(m20, matrixC.Data()[2]);
			Assert::AreEqual(m30, matrixC.Data()[3]);
			Assert::AreEqual(m01, matrixC.Data()[4]);
			Assert::AreEqual(m11, matrixC.Data()[5]);
			Assert::AreEqual(m21, matrixC.Data()[6]);
			Assert::AreEqual(m31, matrixC.Data()[7]);
			Assert::AreEqual(m02, matrixC.Data()[8]);
			Assert::AreEqual(m12, matrixC.Data()[9]);
			Assert::AreEqual(m22, matrixC.Data()[10]);
			Assert::AreEqual(m32, matrixC.Data()[11]);
			Assert::AreEqual(m03, matrixC.Data()[12]);
			Assert::AreEqual(m13, matrixC.Data()[13]);
			Assert::AreEqual(m23, matrixC.Data()[14]);
			Assert::AreEqual(m33, matrixC.Data()[15]);
			Assert::AreEqual(m00, matrixC.Data(0)[0]);
			Assert::AreEqual(m10, matrixC.Data(0)[1]);
			Assert::AreEqual(m20, matrixC.Data(0)[2]);
			Assert::AreEqual(m30, matrixC.Data(0)[3]);
			Assert::AreEqual(m01, matrixC.Data(1)[0]);
			Assert::AreEqual(m11, matrixC.Data(1)[1]);
			Assert::AreEqual(m21, matrixC.Data(1)[2]);
			Assert::AreEqual(m31, matrixC.Data(1)[3]);
			Assert::AreEqual(m02, matrixC.Data(2)[0]);
			Assert::AreEqual(m12, matrixC.Data(2)[1]);
			Assert::AreEqual(m22, matrixC.Data(2)[2]);
			Assert::AreEqual(m32, matrixC.Data(2)[3]);
			Assert::AreEqual(m03, matrixC.Data(3)[0]);
			Assert::AreEqual(m13, matrixC.Data(3)[1]);
			Assert::AreEqual(m23, matrixC.Data(3)[2]);
			Assert::AreEqual(m33, matrixC.Data(3)[3]);
		}

		TEST_METHOD(DataFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;

			auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrix.Data()[0]);
			Assert::AreEqual(m10, matrix.Data()[1]);
			Assert::AreEqual(m20, matrix.Data()[2]);
			Assert::AreEqual(m30, matrix.Data()[3]);
			Assert::AreEqual(m01, matrix.Data()[4]);
			Assert::AreEqual(m11, matrix.Data()[5]);
			Assert::AreEqual(m21, matrix.Data()[6]);
			Assert::AreEqual(m31, matrix.Data()[7]);
			Assert::AreEqual(m02, matrix.Data()[8]);
			Assert::AreEqual(m12, matrix.Data()[9]);
			Assert::AreEqual(m22, matrix.Data()[10]);
			Assert::AreEqual(m32, matrix.Data()[11]);
			Assert::AreEqual(m03, matrix.Data()[12]);
			Assert::AreEqual(m13, matrix.Data()[13]);
			Assert::AreEqual(m23, matrix.Data()[14]);
			Assert::AreEqual(m33, matrix.Data()[15]);
			Assert::AreEqual(m00, matrix.Data(0)[0]);
			Assert::AreEqual(m10, matrix.Data(0)[1]);
			Assert::AreEqual(m20, matrix.Data(0)[2]);
			Assert::AreEqual(m30, matrix.Data(0)[3]);
			Assert::AreEqual(m01, matrix.Data(1)[0]);
			Assert::AreEqual(m11, matrix.Data(1)[1]);
			Assert::AreEqual(m21, matrix.Data(1)[2]);
			Assert::AreEqual(m31, matrix.Data(1)[3]);
			Assert::AreEqual(m02, matrix.Data(2)[0]);
			Assert::AreEqual(m12, matrix.Data(2)[1]);
			Assert::AreEqual(m22, matrix.Data(2)[2]);
			Assert::AreEqual(m32, matrix.Data(2)[3]);
			Assert::AreEqual(m03, matrix.Data(3)[0]);
			Assert::AreEqual(m13, matrix.Data(3)[1]);
			Assert::AreEqual(m23, matrix.Data(3)[2]);
			Assert::AreEqual(m33, matrix.Data(3)[3]);

			constexpr auto matrixC = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrixC.Data()[0]);
			Assert::AreEqual(m10, matrixC.Data()[1]);
			Assert::AreEqual(m20, matrixC.Data()[2]);
			Assert::AreEqual(m30, matrixC.Data()[3]);
			Assert::AreEqual(m01, matrixC.Data()[4]);
			Assert::AreEqual(m11, matrixC.Data()[5]);
			Assert::AreEqual(m21, matrixC.Data()[6]);
			Assert::AreEqual(m31, matrixC.Data()[7]);
			Assert::AreEqual(m02, matrixC.Data()[8]);
			Assert::AreEqual(m12, matrixC.Data()[9]);
			Assert::AreEqual(m22, matrixC.Data()[10]);
			Assert::AreEqual(m32, matrixC.Data()[11]);
			Assert::AreEqual(m03, matrixC.Data()[12]);
			Assert::AreEqual(m13, matrixC.Data()[13]);
			Assert::AreEqual(m23, matrixC.Data()[14]);
			Assert::AreEqual(m33, matrixC.Data()[15]);
			Assert::AreEqual(m00, matrixC.Data(0)[0]);
			Assert::AreEqual(m10, matrixC.Data(0)[1]);
			Assert::AreEqual(m20, matrixC.Data(0)[2]);
			Assert::AreEqual(m30, matrixC.Data(0)[3]);
			Assert::AreEqual(m01, matrixC.Data(1)[0]);
			Assert::AreEqual(m11, matrixC.Data(1)[1]);
			Assert::AreEqual(m21, matrixC.Data(1)[2]);
			Assert::AreEqual(m31, matrixC.Data(1)[3]);
			Assert::AreEqual(m02, matrixC.Data(2)[0]);
			Assert::AreEqual(m12, matrixC.Data(2)[1]);
			Assert::AreEqual(m22, matrixC.Data(2)[2]);
			Assert::AreEqual(m32, matrixC.Data(2)[3]);
			Assert::AreEqual(m03, matrixC.Data(3)[0]);
			Assert::AreEqual(m13, matrixC.Data(3)[1]);
			Assert::AreEqual(m23, matrixC.Data(3)[2]);
			Assert::AreEqual(m33, matrixC.Data(3)[3]);
		}

		TEST_METHOD(GetRowShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto row0 = matrix.GetRow(0);
			const auto row1 = matrix.GetRow(1);
			const auto row2 = matrix.GetRow(2);
			const auto row3 = matrix.GetRow(3);
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());
			Assert::AreEqual(m02, row0.Z());
			Assert::AreEqual(m03, row0.W());
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
			Assert::AreEqual(m12, row1.Z());
			Assert::AreEqual(m13, row1.W());
			Assert::AreEqual(m20, row2.X());
			Assert::AreEqual(m21, row2.Y());
			Assert::AreEqual(m22, row2.Z());
			Assert::AreEqual(m23, row2.W());
			Assert::AreEqual(m30, row3.X());
			Assert::AreEqual(m31, row3.Y());
			Assert::AreEqual(m32, row3.Z());
			Assert::AreEqual(m33, row3.W());
		}

		TEST_METHOD(GetRowFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto row0 = matrix.GetRow(0);
			const auto row1 = matrix.GetRow(1);
			const auto row2 = matrix.GetRow(2);
			const auto row3 = matrix.GetRow(3);
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());
			Assert::AreEqual(m02, row0.Z());
			Assert::AreEqual(m03, row0.W());
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
			Assert::AreEqual(m12, row1.Z());
			Assert::AreEqual(m13, row1.W());
			Assert::AreEqual(m20, row2.X());
			Assert::AreEqual(m21, row2.Y());
			Assert::AreEqual(m22, row2.Z());
			Assert::AreEqual(m23, row2.W());
			Assert::AreEqual(m30, row3.X());
			Assert::AreEqual(m31, row3.Y());
			Assert::AreEqual(m32, row3.Z());
			Assert::AreEqual(m33, row3.W());
		}

		TEST_METHOD(SetRowShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<short>();
			constexpr auto row0 = PonyEngine::Math::Vector4<short>(m00, m01, m02, m03);
			constexpr auto row1 = PonyEngine::Math::Vector4<short>(m10, m11, m12, m13);
			constexpr auto row2 = PonyEngine::Math::Vector4<short>(m20, m21, m22, m23);
			constexpr auto row3 = PonyEngine::Math::Vector4<short>(m30, m31, m32, m33);
			matrix.SetRow(0, row0);
			matrix.SetRow(1, row1);
			matrix.SetRow(2, row2);
			matrix.SetRow(3, row3);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(SetRowFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<float>();
			constexpr auto row0 = PonyEngine::Math::Vector4<float>(m00, m01, m02, m03);
			constexpr auto row1 = PonyEngine::Math::Vector4<float>(m10, m11, m12, m13);
			constexpr auto row2 = PonyEngine::Math::Vector4<float>(m20, m21, m22, m23);
			constexpr auto row3 = PonyEngine::Math::Vector4<float>(m30, m31, m32, m33);
			matrix.SetRow(0, row0);
			matrix.SetRow(1, row1);
			matrix.SetRow(2, row2);
			matrix.SetRow(3, row3);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(GetColumnShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto column0 = matrix.GetColumn(0);
			const auto column1 = matrix.GetColumn(1);
			const auto column2 = matrix.GetColumn(2);
			const auto column3 = matrix.GetColumn(3);
			Assert::AreEqual(m00, column0.X());
			Assert::AreEqual(m10, column0.Y());
			Assert::AreEqual(m20, column0.Z());
			Assert::AreEqual(m30, column0.W());
			Assert::AreEqual(m01, column1.X());
			Assert::AreEqual(m11, column1.Y());
			Assert::AreEqual(m21, column1.Z());
			Assert::AreEqual(m31, column1.W());
			Assert::AreEqual(m02, column2.X());
			Assert::AreEqual(m12, column2.Y());
			Assert::AreEqual(m22, column2.Z());
			Assert::AreEqual(m32, column2.W());
			Assert::AreEqual(m03, column3.X());
			Assert::AreEqual(m13, column3.Y());
			Assert::AreEqual(m23, column3.Z());
			Assert::AreEqual(m33, column3.W());
		}

		TEST_METHOD(GetColumnFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto column0 = matrix.GetColumn(0);
			const auto column1 = matrix.GetColumn(1);
			const auto column2 = matrix.GetColumn(2);
			const auto column3 = matrix.GetColumn(3);
			Assert::AreEqual(m00, column0.X());
			Assert::AreEqual(m10, column0.Y());
			Assert::AreEqual(m20, column0.Z());
			Assert::AreEqual(m30, column0.W());
			Assert::AreEqual(m01, column1.X());
			Assert::AreEqual(m11, column1.Y());
			Assert::AreEqual(m21, column1.Z());
			Assert::AreEqual(m31, column1.W());
			Assert::AreEqual(m02, column2.X());
			Assert::AreEqual(m12, column2.Y());
			Assert::AreEqual(m22, column2.Z());
			Assert::AreEqual(m32, column2.W());
			Assert::AreEqual(m03, column3.X());
			Assert::AreEqual(m13, column3.Y());
			Assert::AreEqual(m23, column3.Z());
			Assert::AreEqual(m33, column3.W());
		}

		TEST_METHOD(SetColumnShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<short>();
			constexpr auto column0 = PonyEngine::Math::Vector4<short>(m00, m10, m20, m30);
			constexpr auto column1 = PonyEngine::Math::Vector4<short>(m01, m11, m21, m31);
			constexpr auto column2 = PonyEngine::Math::Vector4<short>(m02, m12, m22, m32);
			constexpr auto column3 = PonyEngine::Math::Vector4<short>(m03, m13, m23, m33);
			matrix.SetColumn(0, column0);
			matrix.SetColumn(1, column1);
			matrix.SetColumn(2, column2);
			matrix.SetColumn(3, column3);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(SetColumnFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<float>();
			constexpr auto column0 = PonyEngine::Math::Vector4<float>(m00, m10, m20, m30);
			constexpr auto column1 = PonyEngine::Math::Vector4<float>(m01, m11, m21, m31);
			constexpr auto column2 = PonyEngine::Math::Vector4<float>(m02, m12, m22, m32);
			constexpr auto column3 = PonyEngine::Math::Vector4<float>(m03, m13, m23, m33);
			matrix.SetColumn(0, column0);
			matrix.SetColumn(1, column1);
			matrix.SetColumn(2, column2);
			matrix.SetColumn(3, column3);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(GetDiagonalShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto diagonal = matrix.GetDiagonal();
			Assert::AreEqual(m00, diagonal.X());
			Assert::AreEqual(m11, diagonal.Y());
			Assert::AreEqual(m22, diagonal.Z());
			Assert::AreEqual(m33, diagonal.W());
		}

		TEST_METHOD(GetDiagonalFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto diagonal = matrix.GetDiagonal();
			Assert::AreEqual(m00, diagonal.X());
			Assert::AreEqual(m11, diagonal.Y());
			Assert::AreEqual(m22, diagonal.Z());
			Assert::AreEqual(m33, diagonal.W());
		}

		TEST_METHOD(SetDiagonalShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m11 = -2;
			constexpr short m22 = 19;
			constexpr short m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<short>();
			constexpr auto diagonal = PonyEngine::Math::Vector4<short>(m00, m11, m22, m33);
			matrix.SetDiagonal(diagonal);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(short{}, matrix.M10());
			Assert::AreEqual(short{}, matrix.M20());
			Assert::AreEqual(short{}, matrix.M30());
			Assert::AreEqual(short{}, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(short{}, matrix.M21());
			Assert::AreEqual(short{}, matrix.M31());
			Assert::AreEqual(short{}, matrix.M02());
			Assert::AreEqual(short{}, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(short{}, matrix.M32());
			Assert::AreEqual(short{}, matrix.M03());
			Assert::AreEqual(short{}, matrix.M13());
			Assert::AreEqual(short{}, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(SetDiagonalFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m11 = -2;
			constexpr float m22 = 19;
			constexpr float m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<float>();
			constexpr auto diagonal = PonyEngine::Math::Vector4<float>(m00, m11, m22, m33);
			matrix.SetDiagonal(diagonal);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(float{}, matrix.M10());
			Assert::AreEqual(float{}, matrix.M20());
			Assert::AreEqual(float{}, matrix.M30());
			Assert::AreEqual(float{}, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(float{}, matrix.M21());
			Assert::AreEqual(float{}, matrix.M31());
			Assert::AreEqual(float{}, matrix.M02());
			Assert::AreEqual(float{}, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(float{}, matrix.M32());
			Assert::AreEqual(float{}, matrix.M03());
			Assert::AreEqual(float{}, matrix.M13());
			Assert::AreEqual(float{}, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(GetCounterDiagonalShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto counterDiagonal = matrix.GetCounterDiagonal();
			Assert::AreEqual(m03, counterDiagonal.X());
			Assert::AreEqual(m12, counterDiagonal.Y());
			Assert::AreEqual(m21, counterDiagonal.Z());
			Assert::AreEqual(m30, counterDiagonal.W());
		}

		TEST_METHOD(GetCounterDiagonalFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto counterDiagonal = matrix.GetCounterDiagonal();
			Assert::AreEqual(m03, counterDiagonal.X());
			Assert::AreEqual(m12, counterDiagonal.Y());
			Assert::AreEqual(m21, counterDiagonal.Z());
			Assert::AreEqual(m30, counterDiagonal.W());
		}

		TEST_METHOD(SetCounterDiagonalShortTest)
		{
			constexpr short m03 = 3;
			constexpr short m12 = -2;
			constexpr short m21 = 19;
			constexpr short m30 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<short>();
			constexpr auto counterDiagonal = PonyEngine::Math::Vector4<short>(m03, m12, m21, m30);
			matrix.SetCounterDiagonal(counterDiagonal);
			Assert::AreEqual(short{}, matrix.M00());
			Assert::AreEqual(short{}, matrix.M10());
			Assert::AreEqual(short{}, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(short{}, matrix.M01());
			Assert::AreEqual(short{}, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(short{}, matrix.M31());
			Assert::AreEqual(short{}, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(short{}, matrix.M22());
			Assert::AreEqual(short{}, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(short{}, matrix.M13());
			Assert::AreEqual(short{}, matrix.M23());
			Assert::AreEqual(short{}, matrix.M33());
		}

		TEST_METHOD(SetCounterDiagonalFloatTest)
		{
			constexpr float m03 = 3;
			constexpr float m12 = -2;
			constexpr float m21 = 19;
			constexpr float m30 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<float>();
			constexpr auto counterDiagonal = PonyEngine::Math::Vector4<float>(m03, m12, m21, m30);
			matrix.SetCounterDiagonal(counterDiagonal);
			Assert::AreEqual(float{}, matrix.M00());
			Assert::AreEqual(float{}, matrix.M10());
			Assert::AreEqual(float{}, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(float{}, matrix.M01());
			Assert::AreEqual(float{}, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(float{}, matrix.M31());
			Assert::AreEqual(float{}, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(float{}, matrix.M22());
			Assert::AreEqual(float{}, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(float{}, matrix.M13());
			Assert::AreEqual(float{}, matrix.M23());
			Assert::AreEqual(float{}, matrix.M33());
		}

		TEST_METHOD(TraceShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(short{11}, matrix.Trace());
		}

		TEST_METHOD(TraceFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(11.f, matrix.Trace());
		}

		TEST_METHOD(DeterminantShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = -5;
			constexpr short m20 = 3;
			constexpr short m30 = 2;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr short m21 = 3;
			constexpr short m31 = 1;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 9;
			constexpr short m32 = -2;
			constexpr short m03 = -1;
			constexpr short m13 = 1;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(short{578}, matrix.Determinant());
		}

		TEST_METHOD(DeterminantFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = -5;
			constexpr float m20 = 3;
			constexpr float m30 = 2;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr float m21 = 3;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = -2;
			constexpr float m03 = -1;
			constexpr float m13 = 1;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(578.f, matrix.Determinant());
		}

		TEST_METHOD(AdjugateShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = -5;
			constexpr short m20 = 3;
			constexpr short m30 = 2;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr short m21 = 3;
			constexpr short m31 = 1;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 9;
			constexpr short m32 = -2;
			constexpr short m03 = -1;
			constexpr short m13 = 1;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto adjugate = matrix.Adjugate();
			Assert::AreEqual(short{-96}, adjugate.M00());
			Assert::AreEqual(short{160}, adjugate.M10());
			Assert::AreEqual(short{-22}, adjugate.M20());
			Assert::AreEqual(short{-6}, adjugate.M30());
			Assert::AreEqual(short{-53}, adjugate.M01());
			Assert::AreEqual(short{-8}, adjugate.M11());
			Assert::AreEqual(short{30}, adjugate.M21());
			Assert::AreEqual(short{87}, adjugate.M31());
			Assert::AreEqual(short{113}, adjugate.M02());
			Assert::AreEqual(short{-92}, adjugate.M12());
			Assert::AreEqual(short{56}, adjugate.M22());
			Assert::AreEqual(short{-11}, adjugate.M32());
			Assert::AreEqual(short{35}, adjugate.M03());
			Assert::AreEqual(short{38}, adjugate.M13());
			Assert::AreEqual(short{2}, adjugate.M23());
			Assert::AreEqual(short{237}, adjugate.M33());
		}

		TEST_METHOD(AdjugateFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = -5;
			constexpr float m20 = 3;
			constexpr float m30 = 2;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr float m21 = 3;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = -2;
			constexpr float m03 = -1;
			constexpr float m13 = 1;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto adjugate = matrix.Adjugate();
			Assert::AreEqual(-96.f, adjugate.M00());
			Assert::AreEqual(160.f, adjugate.M10());
			Assert::AreEqual(-22.f, adjugate.M20());
			Assert::AreEqual(-6.f, adjugate.M30());
			Assert::AreEqual(-53.f, adjugate.M01());
			Assert::AreEqual(-8.f, adjugate.M11());
			Assert::AreEqual(30.f, adjugate.M21());
			Assert::AreEqual(87.f, adjugate.M31());
			Assert::AreEqual(113.f, adjugate.M02());
			Assert::AreEqual(-92.f, adjugate.M12());
			Assert::AreEqual(56.f, adjugate.M22());
			Assert::AreEqual(-11.f, adjugate.M32());
			Assert::AreEqual(35.f, adjugate.M03());
			Assert::AreEqual(38.f, adjugate.M13());
			Assert::AreEqual(2.f, adjugate.M23());
			Assert::AreEqual(237.f, adjugate.M33());
		}

		TEST_METHOD(TransposeShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = -5;
			constexpr short m20 = 3;
			constexpr short m30 = 2;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr short m21 = 3;
			constexpr short m31 = 1;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 9;
			constexpr short m32 = -2;
			constexpr short m03 = -1;
			constexpr short m13 = 1;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto transpose = matrix.Transpose();
			Assert::AreEqual(m00, transpose.M00());
			Assert::AreEqual(m01, transpose.M10());
			Assert::AreEqual(m02, transpose.M20());
			Assert::AreEqual(m03, transpose.M30());
			Assert::AreEqual(m10, transpose.M01());
			Assert::AreEqual(m11, transpose.M11());
			Assert::AreEqual(m12, transpose.M21());
			Assert::AreEqual(m13, transpose.M31());
			Assert::AreEqual(m20, transpose.M02());
			Assert::AreEqual(m21, transpose.M12());
			Assert::AreEqual(m22, transpose.M22());
			Assert::AreEqual(m23, transpose.M32());
			Assert::AreEqual(m30, transpose.M03());
			Assert::AreEqual(m31, transpose.M13());
			Assert::AreEqual(m32, transpose.M23());
			Assert::AreEqual(m33, transpose.M33());
		}

		TEST_METHOD(TransposeFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = -5;
			constexpr float m20 = 3;
			constexpr float m30 = 2;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr float m21 = 3;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = -2;
			constexpr float m03 = -1;
			constexpr float m13 = 1;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto transpose = matrix.Transpose();
			Assert::AreEqual(m00, transpose.M00());
			Assert::AreEqual(m01, transpose.M10());
			Assert::AreEqual(m02, transpose.M20());
			Assert::AreEqual(m03, transpose.M30());
			Assert::AreEqual(m10, transpose.M01());
			Assert::AreEqual(m11, transpose.M11());
			Assert::AreEqual(m12, transpose.M21());
			Assert::AreEqual(m13, transpose.M31());
			Assert::AreEqual(m20, transpose.M02());
			Assert::AreEqual(m21, transpose.M12());
			Assert::AreEqual(m22, transpose.M22());
			Assert::AreEqual(m23, transpose.M32());
			Assert::AreEqual(m30, transpose.M03());
			Assert::AreEqual(m31, transpose.M13());
			Assert::AreEqual(m32, transpose.M23());
			Assert::AreEqual(m33, transpose.M33());
		}

		TEST_METHOD(InverseFloatTest)
		{
			constexpr float m00 = 11;
			constexpr float m10 = 5;
			constexpr float m20 = 3;
			constexpr float m30 = 5;
			constexpr float m01 = 5;
			constexpr float m11 = 2;
			constexpr float m21 = 3;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = 2;
			constexpr float m03 = 3;
			constexpr float m13 = 1;
			constexpr float m23 = 1;
			constexpr float m33 = 1;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto inverse = matrix.Inverse();
			Assert::AreEqual(0.375f, inverse.M00());
			Assert::AreEqual(1.25f, inverse.M10());
			Assert::AreEqual(-0.25f, inverse.M20());
			Assert::AreEqual(-2.625f, inverse.M30());
			Assert::AreEqual(1.75f, inverse.M01());
			Assert::AreEqual(3.5f, inverse.M11());
			Assert::AreEqual(-0.5f, inverse.M21());
			Assert::AreEqual(-11.25f, inverse.M31());
			Assert::AreEqual(-1.25f, inverse.M02());
			Assert::AreEqual(-2.5f, inverse.M12());
			Assert::AreEqual(0.5f, inverse.M22());
			Assert::AreEqual(7.75f, inverse.M32());
			Assert::AreEqual(-1.625f, inverse.M03());
			Assert::AreEqual(-4.75f, inverse.M13());
			Assert::AreEqual(0.75f, inverse.M23());
			Assert::AreEqual(12.375f, inverse.M33());
		}

		TEST_METHOD(IsZeroShortTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix4x4<short>::Predefined::Zero.IsZero());

			auto matrix = PonyEngine::Math::Matrix4x4<short>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyEngine::Math::Matrix4x4<float>::ComponentCount; ++i)
			{
				matrix.Data()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Data()[i] = PonyEngine::Math::Matrix4x4<short>::Predefined::Zero.Data()[i];
			}
		}

		TEST_METHOD(IsZeroFloatTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix4x4<float>::Predefined::Zero.IsZero());

			auto matrix = PonyEngine::Math::Matrix4x4<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyEngine::Math::Matrix4x4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsZero());
				matrix.Data()[i] = std::nextafter(matrix.Data()[i], 0.5f);
				Assert::IsFalse(matrix.IsZero());
				matrix.Data()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Data()[i] = PonyEngine::Math::Matrix4x4<float>::Predefined::Zero.Data()[i];
			}
		}

		TEST_METHOD(IsAlmostZeroTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix4x4<float>::Predefined::Zero.IsAlmostZero());

			auto matrix = PonyEngine::Math::Matrix4x4<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsAlmostZero());

			for (std::size_t i = 0; i < PonyEngine::Math::Matrix4x4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Data()[i] = std::nextafter(matrix.Data()[i], 0.5f);
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Data()[i] += 1;
				Assert::IsFalse(matrix.IsAlmostZero());
				Assert::IsTrue(matrix.IsAlmostZero(5.f));
				matrix.Data()[i] = PonyEngine::Math::Matrix4x4<float>::Predefined::Zero.Data()[i];
			}
		}

		TEST_METHOD(IsIdentityShortTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix4x4<short>::Predefined::Identity.IsIdentity());

			auto matrix = PonyEngine::Math::Matrix4x4<short>::Predefined::Identity;
			Assert::IsTrue(matrix.IsIdentity());

			for (std::size_t i = 0; i < PonyEngine::Math::Matrix4x4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsIdentity());
				matrix.Data()[i] += 1;
				Assert::IsFalse(matrix.IsIdentity());
				matrix.Data()[i] = PonyEngine::Math::Matrix4x4<short>::Predefined::Identity.Data()[i];
			}
		}

		TEST_METHOD(IsIdentityFloatTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix4x4<float>::Predefined::Identity.IsIdentity());

			auto matrix = PonyEngine::Math::Matrix4x4<float>::Predefined::Identity;
			Assert::IsTrue(matrix.IsIdentity());

			for (std::size_t i = 0; i < PonyEngine::Math::Matrix4x4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsIdentity());
				matrix.Data()[i] = std::nextafter(matrix.Data()[i], 0.5f);
				Assert::IsFalse(matrix.IsIdentity());
				matrix.Data()[i] += 1;
				Assert::IsFalse(matrix.IsIdentity());
				matrix.Data()[i] = PonyEngine::Math::Matrix4x4<float>::Predefined::Identity.Data()[i];
			}
		}

		TEST_METHOD(IsAlmostIdentityTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix4x4<float>::Predefined::Identity.IsAlmostIdentity());

			auto matrix = PonyEngine::Math::Matrix4x4<float>::Predefined::Identity;
			Assert::IsTrue(matrix.IsAlmostIdentity());

			for (std::size_t i = 0; i < PonyEngine::Math::Matrix4x4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsAlmostIdentity());
				matrix.Data()[i] = std::nextafter(matrix.Data()[i], 0.5f);
				Assert::IsTrue(matrix.IsAlmostIdentity());
				matrix.Data()[i] += 1;
				Assert::IsFalse(matrix.IsAlmostIdentity());
				Assert::IsTrue(matrix.IsAlmostIdentity(5.f));
				matrix.Data()[i] = PonyEngine::Math::Matrix4x4<float>::Predefined::Identity.Data()[i];
			}
		}

		TEST_METHOD(IsFiniteTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix4x4<float>::Predefined::Zero.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Matrix4x4<float>::Predefined::Identity.IsFinite());

			const float nan = std::numeric_limits<float>::quiet_NaN();
			constexpr std::array<float, 16> array{ 3.f, 1.f, -5.f, 7.f, 4.f, -6.f, -7.f, 10.f, 20.f, -13.f, 14.f, 18.f, 9.f, 12.f, -11.f, 21.f };
			auto matrix = PonyEngine::Math::Matrix4x4<float>(array.data());
			Assert::IsTrue(matrix.IsFinite());
			for (std::size_t i = 0; i < PonyEngine::Math::Matrix4x4<float>::ComponentCount; ++i)
			{
				matrix.Data()[i] = nan;
				Assert::IsFalse(matrix.IsFinite());
				matrix.Data()[i] = array[i];
			}
		}

		TEST_METHOD(SetShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<short>();
			matrix.Set(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(SetFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			auto matrix = PonyEngine::Math::Matrix4x4<float>();
			matrix.Set(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(SetColumnsShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr auto column0 = PonyEngine::Math::Vector4<short>(m00, m10, m20, m30);
			constexpr auto column1 = PonyEngine::Math::Vector4<short>(m01, m11, m21, m31);
			constexpr auto column2 = PonyEngine::Math::Vector4<short>(m02, m12, m22, m32);
			constexpr auto column3 = PonyEngine::Math::Vector4<short>(m03, m13, m23, m33);
			auto matrix = PonyEngine::Math::Matrix4x4<short>();
			matrix.Set(column0, column1, column2, column3);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(SetColumsFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr auto column0 = PonyEngine::Math::Vector4<float>(m00, m10, m20, m30);
			constexpr auto column1 = PonyEngine::Math::Vector4<float>(m01, m11, m21, m31);
			constexpr auto column2 = PonyEngine::Math::Vector4<float>(m02, m12, m22, m32);
			constexpr auto column3 = PonyEngine::Math::Vector4<float>(m03, m13, m23, m33);
			auto matrix = PonyEngine::Math::Matrix4x4<float>();
			matrix.Set(column0, column1, column2, column3);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(SetArrayShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m30 = 22;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m31 = 11;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr short m32 = -22;
			constexpr short m03 = -12;
			constexpr short m13 = 31;
			constexpr short m23 = -1;
			constexpr short m33 = 2;
			constexpr std::array<short, 16> array{ m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33 };
			auto matrix = PonyEngine::Math::Matrix4x4<short>();
			matrix.Set(array.data());
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(SetArrayFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m30 = 22;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m31 = 11;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr float m32 = -22;
			constexpr float m03 = -12;
			constexpr float m13 = 31;
			constexpr float m23 = -1;
			constexpr float m33 = 2;
			constexpr std::array<float, 16> array{ m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33 };
			auto matrix = PonyEngine::Math::Matrix4x4<float>();
			matrix.Set(array.data());
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m31, matrix.M31());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m32, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(m13, matrix.M13());
			Assert::AreEqual(m23, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(ScaleThisShortTest)
		{
			constexpr short m00 = 11;
			constexpr short m10 = 5;
			constexpr short m20 = 3;
			constexpr short m30 = 5;
			constexpr short m01 = 5;
			constexpr short m11 = 2;
			constexpr short m21 = 3;
			constexpr short m31 = 1;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 9;
			constexpr short m32 = 2;
			constexpr short m03 = 3;
			constexpr short m13 = 1;
			constexpr short m23 = 1;
			constexpr short m33 = 1;
			constexpr short m00S = 3;
			constexpr short m10S = -2;
			constexpr short m20S = 5;
			constexpr short m30S = 7;
			constexpr short m01S = 4;
			constexpr short m11S = -1;
			constexpr short m21S = 7;
			constexpr short m31S = -3;
			constexpr short m02S = -5;
			constexpr short m12S = 6;
			constexpr short m22S = -7;
			constexpr short m32S = 8;
			constexpr short m03S = 4;
			constexpr short m13S = -1;
			constexpr short m23S = 9;
			constexpr short m33S = -8;
			auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr auto scale = PonyEngine::Math::Matrix4x4<short>(m00S, m10S, m20S, m30S, m01S, m11S, m21S, m31S, m02S, m12S, m22S, m32S, m03S, m13S, m23S, m33S);
			matrix.Scale(scale);
			Assert::AreEqual(static_cast<short>(m00 * m00S), matrix.M00());
			Assert::AreEqual(static_cast<short>(m10 * m10S), matrix.M10());
			Assert::AreEqual(static_cast<short>(m20 * m20S), matrix.M20());
			Assert::AreEqual(static_cast<short>(m30 * m30S), matrix.M30());
			Assert::AreEqual(static_cast<short>(m01 * m01S), matrix.M01());
			Assert::AreEqual(static_cast<short>(m11 * m11S), matrix.M11());
			Assert::AreEqual(static_cast<short>(m21 * m21S), matrix.M21());
			Assert::AreEqual(static_cast<short>(m31 * m31S), matrix.M31());
			Assert::AreEqual(static_cast<short>(m02 * m02S), matrix.M02());
			Assert::AreEqual(static_cast<short>(m12 * m12S), matrix.M12());
			Assert::AreEqual(static_cast<short>(m22 * m22S), matrix.M22());
			Assert::AreEqual(static_cast<short>(m32 * m32S), matrix.M32());
			Assert::AreEqual(static_cast<short>(m03 * m03S), matrix.M03());
			Assert::AreEqual(static_cast<short>(m13 * m13S), matrix.M13());
			Assert::AreEqual(static_cast<short>(m23 * m23S), matrix.M23());
			Assert::AreEqual(static_cast<short>(m33 * m33S), matrix.M33());
		}

		TEST_METHOD(ScaleThisFloatTest)
		{
			constexpr float m00 = 11;
			constexpr float m10 = 5;
			constexpr float m20 = 3;
			constexpr float m30 = 5;
			constexpr float m01 = 5;
			constexpr float m11 = 2;
			constexpr float m21 = 3;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = 2;
			constexpr float m03 = 3;
			constexpr float m13 = 1;
			constexpr float m23 = 1;
			constexpr float m33 = 1;
			constexpr float m00S = 3;
			constexpr float m10S = -2;
			constexpr float m20S = 5;
			constexpr float m30S = 7;
			constexpr float m01S = 4;
			constexpr float m11S = -1;
			constexpr float m21S = 7;
			constexpr float m31S = -3;
			constexpr float m02S = -5;
			constexpr float m12S = 6;
			constexpr float m22S = -7;
			constexpr float m32S = 8;
			constexpr float m03S = 4;
			constexpr float m13S = -1;
			constexpr float m23S = 9;
			constexpr float m33S = -8;
			auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr auto scale = PonyEngine::Math::Matrix4x4<float>(m00S, m10S, m20S, m30S, m01S, m11S, m21S, m31S, m02S, m12S, m22S, m32S, m03S, m13S, m23S, m33S);
			matrix.Scale(scale);
			Assert::AreEqual(m00 * m00S, matrix.M00());
			Assert::AreEqual(m10 * m10S, matrix.M10());
			Assert::AreEqual(m20 * m20S, matrix.M20());
			Assert::AreEqual(m30 * m30S, matrix.M30());
			Assert::AreEqual(m01 * m01S, matrix.M01());
			Assert::AreEqual(m11 * m11S, matrix.M11());
			Assert::AreEqual(m21 * m21S, matrix.M21());
			Assert::AreEqual(m31 * m31S, matrix.M31());
			Assert::AreEqual(m02 * m02S, matrix.M02());
			Assert::AreEqual(m12 * m12S, matrix.M12());
			Assert::AreEqual(m22 * m22S, matrix.M22());
			Assert::AreEqual(m32 * m32S, matrix.M32());
			Assert::AreEqual(m03 * m03S, matrix.M03());
			Assert::AreEqual(m13 * m13S, matrix.M13());
			Assert::AreEqual(m23 * m23S, matrix.M23());
			Assert::AreEqual(m33 * m33S, matrix.M33());
		}

		TEST_METHOD(ToStringShortTest)
		{
			constexpr short m00 = 11;
			constexpr short m10 = 15;
			constexpr short m20 = 3;
			constexpr short m30 = 5;
			constexpr short m01 = 55;
			constexpr short m11 = 2;
			constexpr short m21 = 30;
			constexpr short m31 = 1;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 9;
			constexpr short m32 = 21;
			constexpr short m03 = -13;
			constexpr short m13 = 10;
			constexpr short m23 = 11;
			constexpr short m33 = -6;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto expectedString = std::format("({}, {}, {}, {})({}, {}, {}, {})({}, {}, {}, {})({}, {}, {}, {})", m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
			Assert::AreEqual(expectedString, matrix.ToString());
			std::ostringstream ss;
			ss << matrix;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(ToStringFloatTest)
		{
			constexpr float m00 = 11;
			constexpr float m10 = 15;
			constexpr float m20 = 3;
			constexpr float m30 = 5;
			constexpr float m01 = 55;
			constexpr float m11 = 2;
			constexpr float m21 = 30;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = 21;
			constexpr float m03 = -13;
			constexpr float m13 = 10;
			constexpr float m23 = 11;
			constexpr float m33 = -6;
			constexpr auto matrix = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto expectedString = std::format("({}, {}, {}, {})({}, {}, {}, {})({}, {}, {}, {})({}, {}, {}, {})", m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
			Assert::AreEqual(expectedString, matrix.ToString());
			std::ostringstream ss;
			ss << matrix;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(AssignmentCopyShortTest)
		{
			constexpr short m00 = 11;
			constexpr short m10 = 15;
			constexpr short m20 = 3;
			constexpr short m30 = 5;
			constexpr short m01 = 55;
			constexpr short m11 = 2;
			constexpr short m21 = 30;
			constexpr short m31 = 1;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 9;
			constexpr short m32 = 21;
			constexpr short m03 = -13;
			constexpr short m13 = 10;
			constexpr short m23 = 11;
			constexpr short m33 = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyEngine::Math::Matrix4x4<short> matrixC;
			PonyEngine::Math::Matrix4x4<short>& matrixL = matrixC = matrixR;
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m20, matrixC.M20());
			Assert::AreEqual(m30, matrixC.M30());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(m21, matrixC.M21());
			Assert::AreEqual(m31, matrixC.M31());
			Assert::AreEqual(m02, matrixC.M02());
			Assert::AreEqual(m12, matrixC.M12());
			Assert::AreEqual(m22, matrixC.M22());
			Assert::AreEqual(m32, matrixC.M32());
			Assert::AreEqual(m03, matrixC.M03());
			Assert::AreEqual(m13, matrixC.M13());
			Assert::AreEqual(m23, matrixC.M23());
			Assert::AreEqual(m33, matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentCopyFloatTest)
		{
			constexpr float m00 = 11;
			constexpr float m10 = 15;
			constexpr float m20 = 3;
			constexpr float m30 = 5;
			constexpr float m01 = 55;
			constexpr float m11 = 2;
			constexpr float m21 = 30;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = 21;
			constexpr float m03 = -13;
			constexpr float m13 = 10;
			constexpr float m23 = 11;
			constexpr float m33 = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyEngine::Math::Matrix4x4<float> matrixC;
			PonyEngine::Math::Matrix4x4<float>& matrixL = matrixC = matrixR;
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m20, matrixC.M20());
			Assert::AreEqual(m30, matrixC.M30());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(m21, matrixC.M21());
			Assert::AreEqual(m31, matrixC.M31());
			Assert::AreEqual(m02, matrixC.M02());
			Assert::AreEqual(m12, matrixC.M12());
			Assert::AreEqual(m22, matrixC.M22());
			Assert::AreEqual(m32, matrixC.M32());
			Assert::AreEqual(m03, matrixC.M03());
			Assert::AreEqual(m13, matrixC.M13());
			Assert::AreEqual(m23, matrixC.M23());
			Assert::AreEqual(m33, matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMoveShortTest)
		{
			constexpr short m00 = 11;
			constexpr short m10 = 15;
			constexpr short m20 = 3;
			constexpr short m30 = 5;
			constexpr short m01 = 55;
			constexpr short m11 = 2;
			constexpr short m21 = 30;
			constexpr short m31 = 1;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 9;
			constexpr short m32 = 21;
			constexpr short m03 = -13;
			constexpr short m13 = 10;
			constexpr short m23 = 11;
			constexpr short m33 = -6;
			auto matrixR = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyEngine::Math::Matrix4x4<short> matrixC;
			PonyEngine::Math::Matrix4x4<short>& matrixL = matrixC = std::move(matrixR);
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m20, matrixC.M20());
			Assert::AreEqual(m30, matrixC.M30());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(m21, matrixC.M21());
			Assert::AreEqual(m31, matrixC.M31());
			Assert::AreEqual(m02, matrixC.M02());
			Assert::AreEqual(m12, matrixC.M12());
			Assert::AreEqual(m22, matrixC.M22());
			Assert::AreEqual(m32, matrixC.M32());
			Assert::AreEqual(m03, matrixC.M03());
			Assert::AreEqual(m13, matrixC.M13());
			Assert::AreEqual(m23, matrixC.M23());
			Assert::AreEqual(m33, matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMoveFloatTest)
		{
			constexpr float m00 = 11;
			constexpr float m10 = 15;
			constexpr float m20 = 3;
			constexpr float m30 = 5;
			constexpr float m01 = 55;
			constexpr float m11 = 2;
			constexpr float m21 = 30;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = 21;
			constexpr float m03 = -13;
			constexpr float m13 = 10;
			constexpr float m23 = 11;
			constexpr float m33 = -6;
			auto matrixR = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyEngine::Math::Matrix4x4<float> matrixC;
			PonyEngine::Math::Matrix4x4<float>& matrixL = matrixC = std::move(matrixR);
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m20, matrixC.M20());
			Assert::AreEqual(m30, matrixC.M30());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(m21, matrixC.M21());
			Assert::AreEqual(m31, matrixC.M31());
			Assert::AreEqual(m02, matrixC.M02());
			Assert::AreEqual(m12, matrixC.M12());
			Assert::AreEqual(m22, matrixC.M22());
			Assert::AreEqual(m32, matrixC.M32());
			Assert::AreEqual(m03, matrixC.M03());
			Assert::AreEqual(m13, matrixC.M13());
			Assert::AreEqual(m23, matrixC.M23());
			Assert::AreEqual(m33, matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentSumShortTest)
		{
			constexpr short m00 = 11;
			constexpr short m10 = 15;
			constexpr short m20 = 3;
			constexpr short m30 = 5;
			constexpr short m01 = 55;
			constexpr short m11 = 2;
			constexpr short m21 = 30;
			constexpr short m31 = 1;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 9;
			constexpr short m32 = 21;
			constexpr short m03 = -13;
			constexpr short m13 = 10;
			constexpr short m23 = 11;
			constexpr short m33 = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr short m00C = 3;
			constexpr short m10C = -2;
			constexpr short m20C = 5;
			constexpr short m30C = 15;
			constexpr short m01C = 4;
			constexpr short m11C = -1;
			constexpr short m21C = 7;
			constexpr short m31C = 17;
			constexpr short m02C = -5;
			constexpr short m12C = 6;
			constexpr short m22C = -7;
			constexpr short m32C = -17;
			constexpr short m03C = 5;
			constexpr short m13C = -6;
			constexpr short m23C = 7;
			constexpr short m33C = 17;
			auto matrixC = PonyEngine::Math::Matrix4x4<short>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyEngine::Math::Matrix4x4<short>& matrixL = matrixC += matrixR;
			Assert::AreEqual(static_cast<short>(m00 + m00C), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10 + m10C), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m20 + m20C), matrixC.M20());
			Assert::AreEqual(static_cast<short>(m30 + m30C), matrixC.M30());
			Assert::AreEqual(static_cast<short>(m01 + m01C), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11 + m11C), matrixC.M11());
			Assert::AreEqual(static_cast<short>(m21 + m21C), matrixC.M21());
			Assert::AreEqual(static_cast<short>(m31 + m31C), matrixC.M31());
			Assert::AreEqual(static_cast<short>(m02 + m02C), matrixC.M02());
			Assert::AreEqual(static_cast<short>(m12 + m12C), matrixC.M12());
			Assert::AreEqual(static_cast<short>(m22 + m22C), matrixC.M22());
			Assert::AreEqual(static_cast<short>(m32 + m32C), matrixC.M32());
			Assert::AreEqual(static_cast<short>(m03 + m03C), matrixC.M03());
			Assert::AreEqual(static_cast<short>(m13 + m13C), matrixC.M13());
			Assert::AreEqual(static_cast<short>(m23 + m23C), matrixC.M23());
			Assert::AreEqual(static_cast<short>(m33 + m33C), matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentSumFloatTest)
		{
			constexpr float m00 = 11;
			constexpr float m10 = 15;
			constexpr float m20 = 3;
			constexpr float m30 = 5;
			constexpr float m01 = 55;
			constexpr float m11 = 2;
			constexpr float m21 = 30;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = 21;
			constexpr float m03 = -13;
			constexpr float m13 = 10;
			constexpr float m23 = 11;
			constexpr float m33 = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr float m00C = 3;
			constexpr float m10C = -2;
			constexpr float m20C = 5;
			constexpr float m30C = 15;
			constexpr float m01C = 4;
			constexpr float m11C = -1;
			constexpr float m21C = 7;
			constexpr float m31C = 17;
			constexpr float m02C = -5;
			constexpr float m12C = 6;
			constexpr float m22C = -7;
			constexpr float m32C = -17;
			constexpr float m03C = 5;
			constexpr float m13C = -6;
			constexpr float m23C = 7;
			constexpr float m33C = 17;
			auto matrixC = PonyEngine::Math::Matrix4x4<float>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyEngine::Math::Matrix4x4<float>& matrixL = matrixC += matrixR;
			Assert::AreEqual(m00 + m00C, matrixC.M00());
			Assert::AreEqual(m10 + m10C, matrixC.M10());
			Assert::AreEqual(m20 + m20C, matrixC.M20());
			Assert::AreEqual(m30 + m30C, matrixC.M30());
			Assert::AreEqual(m01 + m01C, matrixC.M01());
			Assert::AreEqual(m11 + m11C, matrixC.M11());
			Assert::AreEqual(m21 + m21C, matrixC.M21());
			Assert::AreEqual(m31 + m31C, matrixC.M31());
			Assert::AreEqual(m02 + m02C, matrixC.M02());
			Assert::AreEqual(m12 + m12C, matrixC.M12());
			Assert::AreEqual(m22 + m22C, matrixC.M22());
			Assert::AreEqual(m32 + m32C, matrixC.M32());
			Assert::AreEqual(m03 + m03C, matrixC.M03());
			Assert::AreEqual(m13 + m13C, matrixC.M13());
			Assert::AreEqual(m23 + m23C, matrixC.M23());
			Assert::AreEqual(m33 + m33C, matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentSubtractShortTest)
		{
			constexpr short m00 = 11;
			constexpr short m10 = 15;
			constexpr short m20 = 3;
			constexpr short m30 = 5;
			constexpr short m01 = 55;
			constexpr short m11 = 2;
			constexpr short m21 = 30;
			constexpr short m31 = 1;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 9;
			constexpr short m32 = 21;
			constexpr short m03 = -13;
			constexpr short m13 = 10;
			constexpr short m23 = 11;
			constexpr short m33 = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr short m00C = 3;
			constexpr short m10C = -2;
			constexpr short m20C = 5;
			constexpr short m30C = 15;
			constexpr short m01C = 4;
			constexpr short m11C = -1;
			constexpr short m21C = 7;
			constexpr short m31C = 17;
			constexpr short m02C = -5;
			constexpr short m12C = 6;
			constexpr short m22C = -7;
			constexpr short m32C = -17;
			constexpr short m03C = 5;
			constexpr short m13C = -6;
			constexpr short m23C = 7;
			constexpr short m33C = 17;
			auto matrixC = PonyEngine::Math::Matrix4x4<short>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyEngine::Math::Matrix4x4<short>& matrixL = matrixC -= matrixR;
			Assert::AreEqual(static_cast<short>(m00C - m00), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C - m10), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m20C - m20), matrixC.M20());
			Assert::AreEqual(static_cast<short>(m30C - m30), matrixC.M30());
			Assert::AreEqual(static_cast<short>(m01C - m01), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C - m11), matrixC.M11());
			Assert::AreEqual(static_cast<short>(m21C - m21), matrixC.M21());
			Assert::AreEqual(static_cast<short>(m31C - m31), matrixC.M31());
			Assert::AreEqual(static_cast<short>(m02C - m02), matrixC.M02());
			Assert::AreEqual(static_cast<short>(m12C - m12), matrixC.M12());
			Assert::AreEqual(static_cast<short>(m22C - m22), matrixC.M22());
			Assert::AreEqual(static_cast<short>(m32C - m32), matrixC.M32());
			Assert::AreEqual(static_cast<short>(m03C - m03), matrixC.M03());
			Assert::AreEqual(static_cast<short>(m13C - m13), matrixC.M13());
			Assert::AreEqual(static_cast<short>(m23C - m23), matrixC.M23());
			Assert::AreEqual(static_cast<short>(m33C - m33), matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentSubtractFloatTest)
		{
			constexpr float m00 = 11;
			constexpr float m10 = 15;
			constexpr float m20 = 3;
			constexpr float m30 = 5;
			constexpr float m01 = 55;
			constexpr float m11 = 2;
			constexpr float m21 = 30;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = 21;
			constexpr float m03 = -13;
			constexpr float m13 = 10;
			constexpr float m23 = 11;
			constexpr float m33 = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr float m00C = 3;
			constexpr float m10C = -2;
			constexpr float m20C = 5;
			constexpr float m30C = 15;
			constexpr float m01C = 4;
			constexpr float m11C = -1;
			constexpr float m21C = 7;
			constexpr float m31C = 17;
			constexpr float m02C = -5;
			constexpr float m12C = 6;
			constexpr float m22C = -7;
			constexpr float m32C = -17;
			constexpr float m03C = 5;
			constexpr float m13C = -6;
			constexpr float m23C = 7;
			constexpr float m33C = 17;
			auto matrixC = PonyEngine::Math::Matrix4x4<float>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyEngine::Math::Matrix4x4<float>& matrixL = matrixC -= matrixR;
			Assert::AreEqual(m00C - m00, matrixC.M00());
			Assert::AreEqual(m10C - m10, matrixC.M10());
			Assert::AreEqual(m20C - m20, matrixC.M20());
			Assert::AreEqual(m30C - m30, matrixC.M30());
			Assert::AreEqual(m01C - m01, matrixC.M01());
			Assert::AreEqual(m11C - m11, matrixC.M11());
			Assert::AreEqual(m21C - m21, matrixC.M21());
			Assert::AreEqual(m31C - m31, matrixC.M31());
			Assert::AreEqual(m02C - m02, matrixC.M02());
			Assert::AreEqual(m12C - m12, matrixC.M12());
			Assert::AreEqual(m22C - m22, matrixC.M22());
			Assert::AreEqual(m32C - m32, matrixC.M32());
			Assert::AreEqual(m03C - m03, matrixC.M03());
			Assert::AreEqual(m13C - m13, matrixC.M13());
			Assert::AreEqual(m23C - m23, matrixC.M23());
			Assert::AreEqual(m33C - m33, matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMultiplyNumberShortTest)
		{
			constexpr short multiplierI = 3;
			constexpr short m00C = 3;
			constexpr short m10C = -2;
			constexpr short m20C = 5;
			constexpr short m30C = 15;
			constexpr short m01C = 4;
			constexpr short m11C = -1;
			constexpr short m21C = 7;
			constexpr short m31C = 17;
			constexpr short m02C = -5;
			constexpr short m12C = 6;
			constexpr short m22C = -7;
			constexpr short m32C = -17;
			constexpr short m03C = 5;
			constexpr short m13C = -6;
			constexpr short m23C = 7;
			constexpr short m33C = 17;
			auto matrixC = PonyEngine::Math::Matrix4x4<short>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyEngine::Math::Matrix4x4<short>& matrixL = matrixC *= multiplierI;
			Assert::AreEqual(static_cast<short>(m00C * multiplierI), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C * multiplierI), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m20C * multiplierI), matrixC.M20());
			Assert::AreEqual(static_cast<short>(m30C * multiplierI), matrixC.M30());
			Assert::AreEqual(static_cast<short>(m01C * multiplierI), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C * multiplierI), matrixC.M11());
			Assert::AreEqual(static_cast<short>(m21C * multiplierI), matrixC.M21());
			Assert::AreEqual(static_cast<short>(m31C * multiplierI), matrixC.M31());
			Assert::AreEqual(static_cast<short>(m02C * multiplierI), matrixC.M02());
			Assert::AreEqual(static_cast<short>(m12C * multiplierI), matrixC.M12());
			Assert::AreEqual(static_cast<short>(m22C * multiplierI), matrixC.M22());
			Assert::AreEqual(static_cast<short>(m32C * multiplierI), matrixC.M32());
			Assert::AreEqual(static_cast<short>(m03C * multiplierI), matrixC.M03());
			Assert::AreEqual(static_cast<short>(m13C * multiplierI), matrixC.M13());
			Assert::AreEqual(static_cast<short>(m23C * multiplierI), matrixC.M23());
			Assert::AreEqual(static_cast<short>(m33C * multiplierI), matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));

			constexpr float multiplierF = 5.f;
			matrixC = PonyEngine::Math::Matrix4x4<short>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyEngine::Math::Matrix4x4<short>& matrixL1 = matrixC *= multiplierF;
			Assert::AreEqual(static_cast<short>(m00C * multiplierF), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C * multiplierF), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m20C * multiplierF), matrixC.M20());
			Assert::AreEqual(static_cast<short>(m30C * multiplierF), matrixC.M30());
			Assert::AreEqual(static_cast<short>(m01C * multiplierF), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C * multiplierF), matrixC.M11());
			Assert::AreEqual(static_cast<short>(m21C * multiplierF), matrixC.M21());
			Assert::AreEqual(static_cast<short>(m31C * multiplierF), matrixC.M31());
			Assert::AreEqual(static_cast<short>(m02C * multiplierF), matrixC.M02());
			Assert::AreEqual(static_cast<short>(m12C * multiplierF), matrixC.M12());
			Assert::AreEqual(static_cast<short>(m22C * multiplierF), matrixC.M22());
			Assert::AreEqual(static_cast<short>(m32C * multiplierF), matrixC.M32());
			Assert::AreEqual(static_cast<short>(m03C * multiplierF), matrixC.M03());
			Assert::AreEqual(static_cast<short>(m13C * multiplierF), matrixC.M13());
			Assert::AreEqual(static_cast<short>(m23C * multiplierF), matrixC.M23());
			Assert::AreEqual(static_cast<short>(m33C * multiplierF), matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL1));
		}

		TEST_METHOD(AssignmentMultiplyNumberFloatTest)
		{
			constexpr float multiplier = 3;
			constexpr float m00C = 3;
			constexpr float m10C = -2;
			constexpr float m20C = 5;
			constexpr float m30C = 15;
			constexpr float m01C = 4;
			constexpr float m11C = -1;
			constexpr float m21C = 7;
			constexpr float m31C = 17;
			constexpr float m02C = -5;
			constexpr float m12C = 6;
			constexpr float m22C = -7;
			constexpr float m32C = -17;
			constexpr float m03C = 5;
			constexpr float m13C = -6;
			constexpr float m23C = 7;
			constexpr float m33C = 17;
			auto matrixC = PonyEngine::Math::Matrix4x4<float>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyEngine::Math::Matrix4x4<float>& matrixL = matrixC *= multiplier;
			Assert::AreEqual(m00C * multiplier, matrixC.M00());
			Assert::AreEqual(m10C * multiplier, matrixC.M10());
			Assert::AreEqual(m20C * multiplier, matrixC.M20());
			Assert::AreEqual(m30C * multiplier, matrixC.M30());
			Assert::AreEqual(m01C * multiplier, matrixC.M01());
			Assert::AreEqual(m11C * multiplier, matrixC.M11());
			Assert::AreEqual(m21C * multiplier, matrixC.M21());
			Assert::AreEqual(m31C * multiplier, matrixC.M31());
			Assert::AreEqual(m02C * multiplier, matrixC.M02());
			Assert::AreEqual(m12C * multiplier, matrixC.M12());
			Assert::AreEqual(m22C * multiplier, matrixC.M22());
			Assert::AreEqual(m32C * multiplier, matrixC.M32());
			Assert::AreEqual(m03C * multiplier, matrixC.M03());
			Assert::AreEqual(m13C * multiplier, matrixC.M13());
			Assert::AreEqual(m23C * multiplier, matrixC.M23());
			Assert::AreEqual(m33C * multiplier, matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMultiplyMatrixShortTest)
		{
			constexpr short m00 = 11;
			constexpr short m10 = 15;
			constexpr short m20 = 3;
			constexpr short m30 = 5;
			constexpr short m01 = 55;
			constexpr short m11 = 2;
			constexpr short m21 = 30;
			constexpr short m31 = 1;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 9;
			constexpr short m32 = 21;
			constexpr short m03 = -13;
			constexpr short m13 = 10;
			constexpr short m23 = 11;
			constexpr short m33 = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr short m00C = 3;
			constexpr short m10C = -2;
			constexpr short m20C = 5;
			constexpr short m30C = 15;
			constexpr short m01C = 4;
			constexpr short m11C = -1;
			constexpr short m21C = 7;
			constexpr short m31C = 17;
			constexpr short m02C = -5;
			constexpr short m12C = 6;
			constexpr short m22C = -7;
			constexpr short m32C = -17;
			constexpr short m03C = 5;
			constexpr short m13C = -6;
			constexpr short m23C = 7;
			constexpr short m33C = 17;
			auto matrixC = PonyEngine::Math::Matrix4x4<short>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyEngine::Math::Matrix4x4<short>& matrixL = matrixC *= matrixR;
			Assert::AreEqual(short{103}, matrixC.M00());
			Assert::AreEqual(short{-49}, matrixC.M10());
			Assert::AreEqual(short{174}, matrixC.M20());
			Assert::AreEqual(short{454}, matrixC.M30());
			Assert::AreEqual(short{28}, matrixC.M01());
			Assert::AreEqual(short{62}, matrixC.M11());
			Assert::AreEqual(short{86}, matrixC.M21());
			Assert::AreEqual(short{366}, matrixC.M31());
			Assert::AreEqual(short{106}, matrixC.M02());
			Assert::AreEqual(short{-91}, matrixC.M12());
			Assert::AreEqual(short{163}, matrixC.M22());
			Assert::AreEqual(short{413}, matrixC.M32());
			Assert::AreEqual(short{-84}, matrixC.M03());
			Assert::AreEqual(short{118}, matrixC.M13());
			Assert::AreEqual(short{-114}, matrixC.M23());
			Assert::AreEqual(short{-314}, matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMultiplyMatrixFloatTest)
		{
			constexpr float m00 = 11;
			constexpr float m10 = 15;
			constexpr float m20 = 3;
			constexpr float m30 = 5;
			constexpr float m01 = 55;
			constexpr float m11 = 2;
			constexpr float m21 = 30;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = 21;
			constexpr float m03 = -13;
			constexpr float m13 = 10;
			constexpr float m23 = 11;
			constexpr float m33 = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr float m00C = 3;
			constexpr float m10C = -2;
			constexpr float m20C = 5;
			constexpr float m30C = 15;
			constexpr float m01C = 4;
			constexpr float m11C = -1;
			constexpr float m21C = 7;
			constexpr float m31C = 17;
			constexpr float m02C = -5;
			constexpr float m12C = 6;
			constexpr float m22C = -7;
			constexpr float m32C = -17;
			constexpr float m03C = 5;
			constexpr float m13C = -6;
			constexpr float m23C = 7;
			constexpr float m33C = 17;
			auto matrixC = PonyEngine::Math::Matrix4x4<float>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyEngine::Math::Matrix4x4<float>& matrixL = matrixC *= matrixR;
			Assert::AreEqual(103.f, matrixC.M00());
			Assert::AreEqual(-49.f, matrixC.M10());
			Assert::AreEqual(174.f, matrixC.M20());
			Assert::AreEqual(454.f, matrixC.M30());
			Assert::AreEqual(28.f, matrixC.M01());
			Assert::AreEqual(62.f, matrixC.M11());
			Assert::AreEqual(86.f, matrixC.M21());
			Assert::AreEqual(366.f, matrixC.M31());
			Assert::AreEqual(106.f, matrixC.M02());
			Assert::AreEqual(-91.f, matrixC.M12());
			Assert::AreEqual(163.f, matrixC.M22());
			Assert::AreEqual(413.f, matrixC.M32());
			Assert::AreEqual(-84.f, matrixC.M03());
			Assert::AreEqual(118.f, matrixC.M13());
			Assert::AreEqual(-114.f, matrixC.M23());
			Assert::AreEqual(-314.f, matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentDivideNumberShortTest)
		{
			constexpr short multiplierI = 3;
			constexpr short m00C = 3;
			constexpr short m10C = -2;
			constexpr short m20C = 5;
			constexpr short m30C = 15;
			constexpr short m01C = 4;
			constexpr short m11C = -1;
			constexpr short m21C = 7;
			constexpr short m31C = 17;
			constexpr short m02C = -5;
			constexpr short m12C = 6;
			constexpr short m22C = -7;
			constexpr short m32C = -17;
			constexpr short m03C = 5;
			constexpr short m13C = -6;
			constexpr short m23C = 7;
			constexpr short m33C = 17;
			auto matrixC = PonyEngine::Math::Matrix4x4<short>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyEngine::Math::Matrix4x4<short>& matrixL = matrixC /= multiplierI;
			Assert::AreEqual(static_cast<short>(m00C / multiplierI), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C / multiplierI), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m20C / multiplierI), matrixC.M20());
			Assert::AreEqual(static_cast<short>(m30C / multiplierI), matrixC.M30());
			Assert::AreEqual(static_cast<short>(m01C / multiplierI), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C / multiplierI), matrixC.M11());
			Assert::AreEqual(static_cast<short>(m21C / multiplierI), matrixC.M21());
			Assert::AreEqual(static_cast<short>(m31C / multiplierI), matrixC.M31());
			Assert::AreEqual(static_cast<short>(m02C / multiplierI), matrixC.M02());
			Assert::AreEqual(static_cast<short>(m12C / multiplierI), matrixC.M12());
			Assert::AreEqual(static_cast<short>(m22C / multiplierI), matrixC.M22());
			Assert::AreEqual(static_cast<short>(m32C / multiplierI), matrixC.M32());
			Assert::AreEqual(static_cast<short>(m03C / multiplierI), matrixC.M03());
			Assert::AreEqual(static_cast<short>(m13C / multiplierI), matrixC.M13());
			Assert::AreEqual(static_cast<short>(m23C / multiplierI), matrixC.M23());
			Assert::AreEqual(static_cast<short>(m33C / multiplierI), matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));

			constexpr float multiplierF = 5.f;
			matrixC = PonyEngine::Math::Matrix4x4<short>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyEngine::Math::Matrix4x4<short>& matrixL1 = matrixC /= multiplierF;
			Assert::AreEqual(static_cast<short>(m00C / multiplierF), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C / multiplierF), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m20C / multiplierF), matrixC.M20());
			Assert::AreEqual(static_cast<short>(m30C / multiplierF), matrixC.M30());
			Assert::AreEqual(static_cast<short>(m01C / multiplierF), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C / multiplierF), matrixC.M11());
			Assert::AreEqual(static_cast<short>(m21C / multiplierF), matrixC.M21());
			Assert::AreEqual(static_cast<short>(m31C / multiplierF), matrixC.M31());
			Assert::AreEqual(static_cast<short>(m02C / multiplierF), matrixC.M02());
			Assert::AreEqual(static_cast<short>(m12C / multiplierF), matrixC.M12());
			Assert::AreEqual(static_cast<short>(m22C / multiplierF), matrixC.M22());
			Assert::AreEqual(static_cast<short>(m32C / multiplierF), matrixC.M32());
			Assert::AreEqual(static_cast<short>(m03C / multiplierF), matrixC.M03());
			Assert::AreEqual(static_cast<short>(m13C / multiplierF), matrixC.M13());
			Assert::AreEqual(static_cast<short>(m23C / multiplierF), matrixC.M23());
			Assert::AreEqual(static_cast<short>(m33C / multiplierF), matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL1));
		}

		TEST_METHOD(AssignmentDivideNumberFloatTest)
		{
			constexpr float multiplier = 3;
			constexpr float m00C = 3;
			constexpr float m10C = -2;
			constexpr float m20C = 5;
			constexpr float m30C = 15;
			constexpr float m01C = 4;
			constexpr float m11C = -1;
			constexpr float m21C = 7;
			constexpr float m31C = 17;
			constexpr float m02C = -5;
			constexpr float m12C = 6;
			constexpr float m22C = -7;
			constexpr float m32C = -17;
			constexpr float m03C = 5;
			constexpr float m13C = -6;
			constexpr float m23C = 7;
			constexpr float m33C = 17;
			auto matrixC = PonyEngine::Math::Matrix4x4<float>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyEngine::Math::Matrix4x4<float>& matrixL = matrixC /= multiplier;
			Assert::AreEqual(static_cast<double>(m00C / multiplier), static_cast<double>(matrixC.M00()), 0.0001);
			Assert::AreEqual(static_cast<double>(m10C / multiplier), static_cast<double>(matrixC.M10()), 0.0001);
			Assert::AreEqual(static_cast<double>(m20C / multiplier), static_cast<double>(matrixC.M20()), 0.0001);
			Assert::AreEqual(static_cast<double>(m30C / multiplier), static_cast<double>(matrixC.M30()), 0.0001);
			Assert::AreEqual(static_cast<double>(m01C / multiplier), static_cast<double>(matrixC.M01()), 0.0001);
			Assert::AreEqual(static_cast<double>(m11C / multiplier), static_cast<double>(matrixC.M11()), 0.0001);
			Assert::AreEqual(static_cast<double>(m21C / multiplier), static_cast<double>(matrixC.M21()), 0.0001);
			Assert::AreEqual(static_cast<double>(m31C / multiplier), static_cast<double>(matrixC.M31()), 0.0001);
			Assert::AreEqual(static_cast<double>(m02C / multiplier), static_cast<double>(matrixC.M02()), 0.0001);
			Assert::AreEqual(static_cast<double>(m12C / multiplier), static_cast<double>(matrixC.M12()), 0.0001);
			Assert::AreEqual(static_cast<double>(m22C / multiplier), static_cast<double>(matrixC.M22()), 0.0001);
			Assert::AreEqual(static_cast<double>(m32C / multiplier), static_cast<double>(matrixC.M32()), 0.0001);
			Assert::AreEqual(static_cast<double>(m03C / multiplier), static_cast<double>(matrixC.M03()), 0.0001);
			Assert::AreEqual(static_cast<double>(m13C / multiplier), static_cast<double>(matrixC.M13()), 0.0001);
			Assert::AreEqual(static_cast<double>(m23C / multiplier), static_cast<double>(matrixC.M23()), 0.0001);
			Assert::AreEqual(static_cast<double>(m33C / multiplier), static_cast<double>(matrixC.M33()), 0.0001);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(EqualityOperatorShortTest)
		{
			constexpr short m00 = 11;
			constexpr short m10 = 15;
			constexpr short m20 = 3;
			constexpr short m30 = 5;
			constexpr short m01 = 55;
			constexpr short m11 = 2;
			constexpr short m21 = 30;
			constexpr short m31 = 1;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 9;
			constexpr short m32 = 21;
			constexpr short m03 = -13;
			constexpr short m13 = 10;
			constexpr short m23 = 11;
			constexpr short m33 = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<short>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyEngine::Math::Matrix4x4<short> matrixL = matrixR;

			Assert::IsTrue(matrixL == matrixR);
			Assert::IsFalse(matrixL != matrixR);

			for (std::size_t i = 0; i < PonyEngine::Math::Matrix4x4<short>::ComponentCount; ++i)
			{
				matrixL.Data()[i] += 1;
				Assert::IsFalse(matrixL == matrixR);
				Assert::IsTrue(matrixL != matrixR);
				matrixL.Data()[i] = matrixR.Data()[i];
			}
		}

		TEST_METHOD(EqualityOperatorFloatTest)
		{
			constexpr float m00 = 11;
			constexpr float m10 = 15;
			constexpr float m20 = 3;
			constexpr float m30 = 5;
			constexpr float m01 = 55;
			constexpr float m11 = 2;
			constexpr float m21 = 30;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = 21;
			constexpr float m03 = -13;
			constexpr float m13 = 10;
			constexpr float m23 = 11;
			constexpr float m33 = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyEngine::Math::Matrix4x4<float> matrixL = matrixR;

			Assert::IsTrue(matrixL == matrixR);
			Assert::IsFalse(matrixL != matrixR);

			for (std::size_t i = 0; i < PonyEngine::Math::Matrix4x4<float>::ComponentCount; ++i)
			{
				matrixL.Data()[i] = std::nextafter(matrixL.Data()[i], 0.f);
				Assert::IsFalse(matrixL == matrixR);
				Assert::IsTrue(matrixL != matrixR);
				matrixL.Data()[i] += 1;
				Assert::IsFalse(matrixL == matrixR);
				Assert::IsTrue(matrixL != matrixR);
				matrixL.Data()[i] = matrixR.Data()[i];
			}
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix4x4<float>::Predefined::Identity == PonyEngine::Math::Matrix4x4<float>(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Matrix4x4<float>::Predefined::Zero == PonyEngine::Math::Matrix4x4<float>(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f));

			Assert::IsTrue(PonyEngine::Math::Matrix4x4<short>::Predefined::Identity == PonyEngine::Math::Matrix4x4<short>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Matrix4x4<short>::Predefined::Zero == PonyEngine::Math::Matrix4x4<short>(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
		}

		TEST_METHOD(ScaleShortTest)
		{
			constexpr short m00R = 11;
			constexpr short m10R = 15;
			constexpr short m20R = 3;
			constexpr short m30R = 5;
			constexpr short m01R = 55;
			constexpr short m11R = 2;
			constexpr short m21R = 30;
			constexpr short m31R = 1;
			constexpr short m02R = 6;
			constexpr short m12R = 7;
			constexpr short m22R = 9;
			constexpr short m32R = 21;
			constexpr short m03R = -13;
			constexpr short m13R = 10;
			constexpr short m23R = 11;
			constexpr short m33R = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<short>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m30L = 15;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m31L = 17;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr short m32L = -17;
			constexpr short m03L = 5;
			constexpr short m13L = -6;
			constexpr short m23L = 7;
			constexpr short m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<short>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			const PonyEngine::Math::Matrix4x4<short> scaled = PonyEngine::Math::Scale(matrixL, matrixR);
			Assert::AreEqual(static_cast<short>(m00L * m00R), scaled.M00());
			Assert::AreEqual(static_cast<short>(m10L * m10R), scaled.M10());
			Assert::AreEqual(static_cast<short>(m20L * m20R), scaled.M20());
			Assert::AreEqual(static_cast<short>(m30L * m30R), scaled.M30());
			Assert::AreEqual(static_cast<short>(m01L * m01R), scaled.M01());
			Assert::AreEqual(static_cast<short>(m11L * m11R), scaled.M11());
			Assert::AreEqual(static_cast<short>(m21L * m21R), scaled.M21());
			Assert::AreEqual(static_cast<short>(m31L * m31R), scaled.M31());
			Assert::AreEqual(static_cast<short>(m02L * m02R), scaled.M02());
			Assert::AreEqual(static_cast<short>(m12L * m12R), scaled.M12());
			Assert::AreEqual(static_cast<short>(m22L * m22R), scaled.M22());
			Assert::AreEqual(static_cast<short>(m32L * m32R), scaled.M32());
			Assert::AreEqual(static_cast<short>(m03L * m03R), scaled.M03());
			Assert::AreEqual(static_cast<short>(m13L * m13R), scaled.M13());
			Assert::AreEqual(static_cast<short>(m23L * m23R), scaled.M23());
			Assert::AreEqual(static_cast<short>(m33L * m33R), scaled.M33());
		}

		TEST_METHOD(ScaleFloatTest)
		{
			constexpr float m00R = 11;
			constexpr float m10R = 15;
			constexpr float m20R = 3;
			constexpr float m30R = 5;
			constexpr float m01R = 55;
			constexpr float m11R = 2;
			constexpr float m21R = 30;
			constexpr float m31R = 1;
			constexpr float m02R = 6;
			constexpr float m12R = 7;
			constexpr float m22R = 9;
			constexpr float m32R = 21;
			constexpr float m03R = -13;
			constexpr float m13R = 10;
			constexpr float m23R = 11;
			constexpr float m33R = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<float>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m30L = 15;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m31L = 17;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr float m32L = -17;
			constexpr float m03L = 5;
			constexpr float m13L = -6;
			constexpr float m23L = 7;
			constexpr float m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			const PonyEngine::Math::Matrix4x4<float> scaled = PonyEngine::Math::Scale(matrixL, matrixR);
			Assert::AreEqual(m00L * m00R, scaled.M00());
			Assert::AreEqual(m10L * m10R, scaled.M10());
			Assert::AreEqual(m20L * m20R, scaled.M20());
			Assert::AreEqual(m30L * m30R, scaled.M30());
			Assert::AreEqual(m01L * m01R, scaled.M01());
			Assert::AreEqual(m11L * m11R, scaled.M11());
			Assert::AreEqual(m21L * m21R, scaled.M21());
			Assert::AreEqual(m31L * m31R, scaled.M31());
			Assert::AreEqual(m02L * m02R, scaled.M02());
			Assert::AreEqual(m12L * m12R, scaled.M12());
			Assert::AreEqual(m22L * m22R, scaled.M22());
			Assert::AreEqual(m32L * m32R, scaled.M32());
			Assert::AreEqual(m03L * m03R, scaled.M03());
			Assert::AreEqual(m13L * m13R, scaled.M13());
			Assert::AreEqual(m23L * m23R, scaled.M23());
			Assert::AreEqual(m33L * m33R, scaled.M33());
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float m00 = 11;
			constexpr float m10 = 15;
			constexpr float m20 = 3;
			constexpr float m30 = 5;
			constexpr float m01 = 55;
			constexpr float m11 = 2;
			constexpr float m21 = 30;
			constexpr float m31 = 1;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 9;
			constexpr float m32 = 21;
			constexpr float m03 = -13;
			constexpr float m13 = 10;
			constexpr float m23 = 11;
			constexpr float m33 = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyEngine::Math::Matrix4x4<float> matrixL = matrixR;
			for (std::size_t i = 0; i < PonyEngine::Math::Matrix4x4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(matrixL, matrixR));
				matrixL.Data()[i] = std::nextafter(matrixL.Data()[i], 0.f);
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(matrixL, matrixR));
				matrixL.Data()[i] += 1;
				Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(matrixL, matrixR));
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(matrixL, matrixR, 5.f));
				matrixL.Data()[i] = matrixR.Data()[i];
			}
		}

		TEST_METHOD(AddShortTest)
		{
			constexpr short m00R = 11;
			constexpr short m10R = 15;
			constexpr short m20R = 3;
			constexpr short m30R = 5;
			constexpr short m01R = 55;
			constexpr short m11R = 2;
			constexpr short m21R = 30;
			constexpr short m31R = 1;
			constexpr short m02R = 6;
			constexpr short m12R = 7;
			constexpr short m22R = 9;
			constexpr short m32R = 21;
			constexpr short m03R = -13;
			constexpr short m13R = 10;
			constexpr short m23R = 11;
			constexpr short m33R = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<short>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m30L = 15;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m31L = 17;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr short m32L = -17;
			constexpr short m03L = 5;
			constexpr short m13L = -6;
			constexpr short m23L = 7;
			constexpr short m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<short>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyEngine::Math::Matrix4x4<short> sum = matrixL + matrixR;
			Assert::AreEqual(static_cast<short>(m00L + m00R), sum.M00());
			Assert::AreEqual(static_cast<short>(m10L + m10R), sum.M10());
			Assert::AreEqual(static_cast<short>(m20L + m20R), sum.M20());
			Assert::AreEqual(static_cast<short>(m30L + m30R), sum.M30());
			Assert::AreEqual(static_cast<short>(m01L + m01R), sum.M01());
			Assert::AreEqual(static_cast<short>(m11L + m11R), sum.M11());
			Assert::AreEqual(static_cast<short>(m21L + m21R), sum.M21());
			Assert::AreEqual(static_cast<short>(m31L + m31R), sum.M31());
			Assert::AreEqual(static_cast<short>(m02L + m02R), sum.M02());
			Assert::AreEqual(static_cast<short>(m12L + m12R), sum.M12());
			Assert::AreEqual(static_cast<short>(m22L + m22R), sum.M22());
			Assert::AreEqual(static_cast<short>(m32L + m32R), sum.M32());
			Assert::AreEqual(static_cast<short>(m03L + m03R), sum.M03());
			Assert::AreEqual(static_cast<short>(m13L + m13R), sum.M13());
			Assert::AreEqual(static_cast<short>(m23L + m23R), sum.M23());
			Assert::AreEqual(static_cast<short>(m33L + m33R), sum.M33());
		}

		TEST_METHOD(AddFloatTest)
		{
			constexpr float m00R = 11;
			constexpr float m10R = 15;
			constexpr float m20R = 3;
			constexpr float m30R = 5;
			constexpr float m01R = 55;
			constexpr float m11R = 2;
			constexpr float m21R = 30;
			constexpr float m31R = 1;
			constexpr float m02R = 6;
			constexpr float m12R = 7;
			constexpr float m22R = 9;
			constexpr float m32R = 21;
			constexpr float m03R = -13;
			constexpr float m13R = 10;
			constexpr float m23R = 11;
			constexpr float m33R = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<float>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m30L = 15;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m31L = 17;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr float m32L = -17;
			constexpr float m03L = 5;
			constexpr float m13L = -6;
			constexpr float m23L = 7;
			constexpr float m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyEngine::Math::Matrix4x4<float> sum = matrixL + matrixR;
			Assert::AreEqual(m00L + m00R, sum.M00());
			Assert::AreEqual(m10L + m10R, sum.M10());
			Assert::AreEqual(m20L + m20R, sum.M20());
			Assert::AreEqual(m30L + m30R, sum.M30());
			Assert::AreEqual(m01L + m01R, sum.M01());
			Assert::AreEqual(m11L + m11R, sum.M11());
			Assert::AreEqual(m21L + m21R, sum.M21());
			Assert::AreEqual(m31L + m31R, sum.M31());
			Assert::AreEqual(m02L + m02R, sum.M02());
			Assert::AreEqual(m12L + m12R, sum.M12());
			Assert::AreEqual(m22L + m22R, sum.M22());
			Assert::AreEqual(m32L + m32R, sum.M32());
			Assert::AreEqual(m03L + m03R, sum.M03());
			Assert::AreEqual(m13L + m13R, sum.M13());
			Assert::AreEqual(m23L + m23R, sum.M23());
			Assert::AreEqual(m33L + m33R, sum.M33());
		}

		TEST_METHOD(NegateShortTest)
		{
			constexpr short m00R = 11;
			constexpr short m10R = 15;
			constexpr short m20R = 3;
			constexpr short m30R = 5;
			constexpr short m01R = 55;
			constexpr short m11R = 2;
			constexpr short m21R = 30;
			constexpr short m31R = 1;
			constexpr short m02R = 6;
			constexpr short m12R = 7;
			constexpr short m22R = 9;
			constexpr short m32R = 21;
			constexpr short m03R = -13;
			constexpr short m13R = 10;
			constexpr short m23R = 11;
			constexpr short m33R = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<short>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			PonyEngine::Math::Matrix4x4<short> negated = -matrixR;
			Assert::AreEqual(static_cast<short>(-m00R), negated.M00());
			Assert::AreEqual(static_cast<short>(-m10R), negated.M10());
			Assert::AreEqual(static_cast<short>(-m20R), negated.M20());
			Assert::AreEqual(static_cast<short>(-m30R), negated.M30());
			Assert::AreEqual(static_cast<short>(-m01R), negated.M01());
			Assert::AreEqual(static_cast<short>(-m11R), negated.M11());
			Assert::AreEqual(static_cast<short>(-m21R), negated.M21());
			Assert::AreEqual(static_cast<short>(-m31R), negated.M31());
			Assert::AreEqual(static_cast<short>(-m02R), negated.M02());
			Assert::AreEqual(static_cast<short>(-m12R), negated.M12());
			Assert::AreEqual(static_cast<short>(-m22R), negated.M22());
			Assert::AreEqual(static_cast<short>(-m32R), negated.M32());
			Assert::AreEqual(static_cast<short>(-m03R), negated.M03());
			Assert::AreEqual(static_cast<short>(-m13R), negated.M13());
			Assert::AreEqual(static_cast<short>(-m23R), negated.M23());
			Assert::AreEqual(static_cast<short>(-m33R), negated.M33());
		}

		TEST_METHOD(NegateFloatTest)
		{
			constexpr float m00R = 11;
			constexpr float m10R = 15;
			constexpr float m20R = 3;
			constexpr float m30R = 5;
			constexpr float m01R = 55;
			constexpr float m11R = 2;
			constexpr float m21R = 30;
			constexpr float m31R = 1;
			constexpr float m02R = 6;
			constexpr float m12R = 7;
			constexpr float m22R = 9;
			constexpr float m32R = 21;
			constexpr float m03R = -13;
			constexpr float m13R = 10;
			constexpr float m23R = 11;
			constexpr float m33R = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<float>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			PonyEngine::Math::Matrix4x4<float> negated = -matrixR;
			Assert::AreEqual(-m00R, negated.M00());
			Assert::AreEqual(-m10R, negated.M10());
			Assert::AreEqual(-m20R, negated.M20());
			Assert::AreEqual(-m30R, negated.M30());
			Assert::AreEqual(-m01R, negated.M01());
			Assert::AreEqual(-m11R, negated.M11());
			Assert::AreEqual(-m21R, negated.M21());
			Assert::AreEqual(-m31R, negated.M31());
			Assert::AreEqual(-m02R, negated.M02());
			Assert::AreEqual(-m12R, negated.M12());
			Assert::AreEqual(-m22R, negated.M22());
			Assert::AreEqual(-m32R, negated.M32());
			Assert::AreEqual(-m03R, negated.M03());
			Assert::AreEqual(-m13R, negated.M13());
			Assert::AreEqual(-m23R, negated.M23());
			Assert::AreEqual(-m33R, negated.M33());
		}

		TEST_METHOD(SubtractShortTest)
		{
			constexpr short m00R = 11;
			constexpr short m10R = 15;
			constexpr short m20R = 3;
			constexpr short m30R = 5;
			constexpr short m01R = 55;
			constexpr short m11R = 2;
			constexpr short m21R = 30;
			constexpr short m31R = 1;
			constexpr short m02R = 6;
			constexpr short m12R = 7;
			constexpr short m22R = 9;
			constexpr short m32R = 21;
			constexpr short m03R = -13;
			constexpr short m13R = 10;
			constexpr short m23R = 11;
			constexpr short m33R = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<short>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m30L = 15;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m31L = 17;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr short m32L = -17;
			constexpr short m03L = 5;
			constexpr short m13L = -6;
			constexpr short m23L = 7;
			constexpr short m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<short>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyEngine::Math::Matrix4x4<short> sum = matrixL - matrixR;
			Assert::AreEqual(static_cast<short>(m00L - m00R), sum.M00());
			Assert::AreEqual(static_cast<short>(m10L - m10R), sum.M10());
			Assert::AreEqual(static_cast<short>(m20L - m20R), sum.M20());
			Assert::AreEqual(static_cast<short>(m30L - m30R), sum.M30());
			Assert::AreEqual(static_cast<short>(m01L - m01R), sum.M01());
			Assert::AreEqual(static_cast<short>(m11L - m11R), sum.M11());
			Assert::AreEqual(static_cast<short>(m21L - m21R), sum.M21());
			Assert::AreEqual(static_cast<short>(m31L - m31R), sum.M31());
			Assert::AreEqual(static_cast<short>(m02L - m02R), sum.M02());
			Assert::AreEqual(static_cast<short>(m12L - m12R), sum.M12());
			Assert::AreEqual(static_cast<short>(m22L - m22R), sum.M22());
			Assert::AreEqual(static_cast<short>(m32L - m32R), sum.M32());
			Assert::AreEqual(static_cast<short>(m03L - m03R), sum.M03());
			Assert::AreEqual(static_cast<short>(m13L - m13R), sum.M13());
			Assert::AreEqual(static_cast<short>(m23L - m23R), sum.M23());
			Assert::AreEqual(static_cast<short>(m33L - m33R), sum.M33());
		}

		TEST_METHOD(SubtractFloatTest)
		{
			constexpr float m00R = 11;
			constexpr float m10R = 15;
			constexpr float m20R = 3;
			constexpr float m30R = 5;
			constexpr float m01R = 55;
			constexpr float m11R = 2;
			constexpr float m21R = 30;
			constexpr float m31R = 1;
			constexpr float m02R = 6;
			constexpr float m12R = 7;
			constexpr float m22R = 9;
			constexpr float m32R = 21;
			constexpr float m03R = -13;
			constexpr float m13R = 10;
			constexpr float m23R = 11;
			constexpr float m33R = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<float>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m30L = 15;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m31L = 17;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr float m32L = -17;
			constexpr float m03L = 5;
			constexpr float m13L = -6;
			constexpr float m23L = 7;
			constexpr float m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyEngine::Math::Matrix4x4<float> sum = matrixL - matrixR;
			Assert::AreEqual(m00L - m00R, sum.M00());
			Assert::AreEqual(m10L - m10R, sum.M10());
			Assert::AreEqual(m20L - m20R, sum.M20());
			Assert::AreEqual(m30L - m30R, sum.M30());
			Assert::AreEqual(m01L - m01R, sum.M01());
			Assert::AreEqual(m11L - m11R, sum.M11());
			Assert::AreEqual(m21L - m21R, sum.M21());
			Assert::AreEqual(m31L - m31R, sum.M31());
			Assert::AreEqual(m02L - m02R, sum.M02());
			Assert::AreEqual(m12L - m12R, sum.M12());
			Assert::AreEqual(m22L - m22R, sum.M22());
			Assert::AreEqual(m32L - m32R, sum.M32());
			Assert::AreEqual(m03L - m03R, sum.M03());
			Assert::AreEqual(m13L - m13R, sum.M13());
			Assert::AreEqual(m23L - m23R, sum.M23());
			Assert::AreEqual(m33L - m33R, sum.M33());
		}

		TEST_METHOD(MultiplyNumberShortTest)
		{
			constexpr short multiplierI = 2;
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m30L = 15;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m31L = 17;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr short m32L = -17;
			constexpr short m03L = 5;
			constexpr short m13L = -6;
			constexpr short m23L = 7;
			constexpr short m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<short>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyEngine::Math::Matrix4x4<short> product = matrixL * multiplierI;
			Assert::AreEqual(static_cast<short>(m00L * multiplierI), product.M00());
			Assert::AreEqual(static_cast<short>(m10L * multiplierI), product.M10());
			Assert::AreEqual(static_cast<short>(m20L * multiplierI), product.M20());
			Assert::AreEqual(static_cast<short>(m30L * multiplierI), product.M30());
			Assert::AreEqual(static_cast<short>(m01L * multiplierI), product.M01());
			Assert::AreEqual(static_cast<short>(m11L * multiplierI), product.M11());
			Assert::AreEqual(static_cast<short>(m21L * multiplierI), product.M21());
			Assert::AreEqual(static_cast<short>(m31L * multiplierI), product.M31());
			Assert::AreEqual(static_cast<short>(m02L * multiplierI), product.M02());
			Assert::AreEqual(static_cast<short>(m12L * multiplierI), product.M12());
			Assert::AreEqual(static_cast<short>(m22L * multiplierI), product.M22());
			Assert::AreEqual(static_cast<short>(m32L * multiplierI), product.M32());
			Assert::AreEqual(static_cast<short>(m03L * multiplierI), product.M03());
			Assert::AreEqual(static_cast<short>(m13L * multiplierI), product.M13());
			Assert::AreEqual(static_cast<short>(m23L * multiplierI), product.M23());
			Assert::AreEqual(static_cast<short>(m33L * multiplierI), product.M33());
			Assert::IsTrue(multiplierI * matrixL == matrixL * multiplierI);

			constexpr float multiplierF = 3;
			product = matrixL * multiplierF;
			Assert::AreEqual(static_cast<short>(m00L * multiplierF), product.M00());
			Assert::AreEqual(static_cast<short>(m10L * multiplierF), product.M10());
			Assert::AreEqual(static_cast<short>(m20L * multiplierF), product.M20());
			Assert::AreEqual(static_cast<short>(m30L * multiplierF), product.M30());
			Assert::AreEqual(static_cast<short>(m01L * multiplierF), product.M01());
			Assert::AreEqual(static_cast<short>(m11L * multiplierF), product.M11());
			Assert::AreEqual(static_cast<short>(m21L * multiplierF), product.M21());
			Assert::AreEqual(static_cast<short>(m31L * multiplierF), product.M31());
			Assert::AreEqual(static_cast<short>(m02L * multiplierF), product.M02());
			Assert::AreEqual(static_cast<short>(m12L * multiplierF), product.M12());
			Assert::AreEqual(static_cast<short>(m22L * multiplierF), product.M22());
			Assert::AreEqual(static_cast<short>(m32L * multiplierF), product.M32());
			Assert::AreEqual(static_cast<short>(m03L * multiplierF), product.M03());
			Assert::AreEqual(static_cast<short>(m13L * multiplierF), product.M13());
			Assert::AreEqual(static_cast<short>(m23L * multiplierF), product.M23());
			Assert::AreEqual(static_cast<short>(m33L * multiplierF), product.M33());
			Assert::IsTrue(multiplierF * matrixL == matrixL * multiplierF);
		}

		TEST_METHOD(MultiplyNumberFloatTest)
		{
			constexpr float multiplier = 3;
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m30L = 15;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m31L = 17;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr float m32L = -17;
			constexpr float m03L = 5;
			constexpr float m13L = -6;
			constexpr float m23L = 7;
			constexpr float m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyEngine::Math::Matrix4x4<float> product = matrixL * multiplier;
			Assert::AreEqual(m00L * multiplier, product.M00());
			Assert::AreEqual(m10L * multiplier, product.M10());
			Assert::AreEqual(m20L * multiplier, product.M20());
			Assert::AreEqual(m30L * multiplier, product.M30());
			Assert::AreEqual(m01L * multiplier, product.M01());
			Assert::AreEqual(m11L * multiplier, product.M11());
			Assert::AreEqual(m21L * multiplier, product.M21());
			Assert::AreEqual(m31L * multiplier, product.M31());
			Assert::AreEqual(m02L * multiplier, product.M02());
			Assert::AreEqual(m12L * multiplier, product.M12());
			Assert::AreEqual(m22L * multiplier, product.M22());
			Assert::AreEqual(m32L * multiplier, product.M32());
			Assert::AreEqual(m03L * multiplier, product.M03());
			Assert::AreEqual(m13L * multiplier, product.M13());
			Assert::AreEqual(m23L * multiplier, product.M23());
			Assert::AreEqual(m33L * multiplier, product.M33());
			Assert::IsTrue(multiplier * matrixL == matrixL * multiplier);
		}

		TEST_METHOD(MultiplyMatrixShortTest)
		{
			constexpr short m00R = 11;
			constexpr short m10R = 15;
			constexpr short m20R = 3;
			constexpr short m30R = 5;
			constexpr short m01R = 55;
			constexpr short m11R = 2;
			constexpr short m21R = 30;
			constexpr short m31R = 1;
			constexpr short m02R = 6;
			constexpr short m12R = 7;
			constexpr short m22R = 9;
			constexpr short m32R = 21;
			constexpr short m03R = -13;
			constexpr short m13R = 10;
			constexpr short m23R = 11;
			constexpr short m33R = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<short>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m30L = 15;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m31L = 17;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr short m32L = -17;
			constexpr short m03L = 5;
			constexpr short m13L = -6;
			constexpr short m23L = 7;
			constexpr short m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<short>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyEngine::Math::Matrix4x4<short> product = matrixL * matrixR;
			Assert::AreEqual(short{103}, product.M00());
			Assert::AreEqual(short{-49}, product.M10());
			Assert::AreEqual(short{174}, product.M20());
			Assert::AreEqual(short{454}, product.M30());
			Assert::AreEqual(short{28}, product.M01());
			Assert::AreEqual(short{62}, product.M11());
			Assert::AreEqual(short{86}, product.M21());
			Assert::AreEqual(short{366}, product.M31());
			Assert::AreEqual(short{106}, product.M02());
			Assert::AreEqual(short{-91}, product.M12());
			Assert::AreEqual(short{163}, product.M22());
			Assert::AreEqual(short{413}, product.M32());
			Assert::AreEqual(short{-84}, product.M03());
			Assert::AreEqual(short{118}, product.M13());
			Assert::AreEqual(short{-114}, product.M23());
			Assert::AreEqual(short{-314}, product.M33());
		}

		TEST_METHOD(MultiplyMatrixFloatTest)
		{
			constexpr float m00R = 11;
			constexpr float m10R = 15;
			constexpr float m20R = 3;
			constexpr float m30R = 5;
			constexpr float m01R = 55;
			constexpr float m11R = 2;
			constexpr float m21R = 30;
			constexpr float m31R = 1;
			constexpr float m02R = 6;
			constexpr float m12R = 7;
			constexpr float m22R = 9;
			constexpr float m32R = 21;
			constexpr float m03R = -13;
			constexpr float m13R = 10;
			constexpr float m23R = 11;
			constexpr float m33R = -6;
			constexpr auto matrixR = PonyEngine::Math::Matrix4x4<float>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m30L = 15;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m31L = 17;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr float m32L = -17;
			constexpr float m03L = 5;
			constexpr float m13L = -6;
			constexpr float m23L = 7;
			constexpr float m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyEngine::Math::Matrix4x4<float> product = matrixL * matrixR;
			Assert::AreEqual(103.f, product.M00());
			Assert::AreEqual(-49.f, product.M10());
			Assert::AreEqual(174.f, product.M20());
			Assert::AreEqual(454.f, product.M30());
			Assert::AreEqual(28.f, product.M01());
			Assert::AreEqual(62.f, product.M11());
			Assert::AreEqual(86.f, product.M21());
			Assert::AreEqual(366.f, product.M31());
			Assert::AreEqual(106.f, product.M02());
			Assert::AreEqual(-91.f, product.M12());
			Assert::AreEqual(163.f, product.M22());
			Assert::AreEqual(413.f, product.M32());
			Assert::AreEqual(-84.f, product.M03());
			Assert::AreEqual(118.f, product.M13());
			Assert::AreEqual(-114.f, product.M23());
			Assert::AreEqual(-314.f, product.M33());
		}

		TEST_METHOD(MultiplyVectorShortTest)
		{
			constexpr short m00R = 11;
			constexpr short m10R = 15;
			constexpr short m20R = 3;
			constexpr short m30R = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector4<short>(m00R, m10R, m20R, m30R);
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m30L = 15;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m31L = 17;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr short m32L = -17;
			constexpr short m03L = 5;
			constexpr short m13L = -6;
			constexpr short m23L = 7;
			constexpr short m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<short>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyEngine::Math::Vector4<short> product = matrixL * vectorR;
			Assert::AreEqual(short{103}, product.X());
			Assert::AreEqual(short{-49}, product.Y());
			Assert::AreEqual(short{174}, product.Z());
			Assert::AreEqual(short{454}, product.W());
		}

		TEST_METHOD(MultiplyVectorFloatTest)
		{
			constexpr float m00R = 11;
			constexpr float m10R = 15;
			constexpr float m20R = 3;
			constexpr float m30R = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector4<float>(m00R, m10R, m20R, m30R);
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m30L = 15;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m31L = 17;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr float m32L = -17;
			constexpr float m03L = 5;
			constexpr float m13L = -6;
			constexpr float m23L = 7;
			constexpr float m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyEngine::Math::Vector4<float> product = matrixL * vectorR;
			Assert::AreEqual(103.f, product.X());
			Assert::AreEqual(-49.f, product.Y());
			Assert::AreEqual(174.f, product.Z());
			Assert::AreEqual(454.f, product.W());
		}

		TEST_METHOD(DivideShortTest)
		{
			constexpr short multiplierI = 2;
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m30L = 15;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m31L = 17;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr short m32L = -17;
			constexpr short m03L = 5;
			constexpr short m13L = -6;
			constexpr short m23L = 7;
			constexpr short m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<short>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyEngine::Math::Matrix4x4<short> product = matrixL / multiplierI;
			Assert::AreEqual(static_cast<short>(m00L / multiplierI), product.M00());
			Assert::AreEqual(static_cast<short>(m10L / multiplierI), product.M10());
			Assert::AreEqual(static_cast<short>(m20L / multiplierI), product.M20());
			Assert::AreEqual(static_cast<short>(m30L / multiplierI), product.M30());
			Assert::AreEqual(static_cast<short>(m01L / multiplierI), product.M01());
			Assert::AreEqual(static_cast<short>(m11L / multiplierI), product.M11());
			Assert::AreEqual(static_cast<short>(m21L / multiplierI), product.M21());
			Assert::AreEqual(static_cast<short>(m31L / multiplierI), product.M31());
			Assert::AreEqual(static_cast<short>(m02L / multiplierI), product.M02());
			Assert::AreEqual(static_cast<short>(m12L / multiplierI), product.M12());
			Assert::AreEqual(static_cast<short>(m22L / multiplierI), product.M22());
			Assert::AreEqual(static_cast<short>(m32L / multiplierI), product.M32());
			Assert::AreEqual(static_cast<short>(m03L / multiplierI), product.M03());
			Assert::AreEqual(static_cast<short>(m13L / multiplierI), product.M13());
			Assert::AreEqual(static_cast<short>(m23L / multiplierI), product.M23());
			Assert::AreEqual(static_cast<short>(m33L / multiplierI), product.M33());
			Assert::IsTrue(multiplierI * matrixL == matrixL * multiplierI);

			constexpr float multiplierF = 3;
			product = matrixL / multiplierF;
			Assert::AreEqual(static_cast<short>(m00L / multiplierF), product.M00());
			Assert::AreEqual(static_cast<short>(m10L / multiplierF), product.M10());
			Assert::AreEqual(static_cast<short>(m20L / multiplierF), product.M20());
			Assert::AreEqual(static_cast<short>(m30L / multiplierF), product.M30());
			Assert::AreEqual(static_cast<short>(m01L / multiplierF), product.M01());
			Assert::AreEqual(static_cast<short>(m11L / multiplierF), product.M11());
			Assert::AreEqual(static_cast<short>(m21L / multiplierF), product.M21());
			Assert::AreEqual(static_cast<short>(m31L / multiplierF), product.M31());
			Assert::AreEqual(static_cast<short>(m02L / multiplierF), product.M02());
			Assert::AreEqual(static_cast<short>(m12L / multiplierF), product.M12());
			Assert::AreEqual(static_cast<short>(m22L / multiplierF), product.M22());
			Assert::AreEqual(static_cast<short>(m32L / multiplierF), product.M32());
			Assert::AreEqual(static_cast<short>(m03L / multiplierF), product.M03());
			Assert::AreEqual(static_cast<short>(m13L / multiplierF), product.M13());
			Assert::AreEqual(static_cast<short>(m23L / multiplierF), product.M23());
			Assert::AreEqual(static_cast<short>(m33L / multiplierF), product.M33());
			Assert::IsTrue(multiplierF * matrixL == matrixL * multiplierF);
		}

		TEST_METHOD(DivideFloatTest)
		{
			constexpr float multiplier = 3;
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m30L = 15;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m31L = 17;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr float m32L = -17;
			constexpr float m03L = 5;
			constexpr float m13L = -6;
			constexpr float m23L = 7;
			constexpr float m33L = 17;
			constexpr auto matrixL = PonyEngine::Math::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyEngine::Math::Matrix4x4<float> product = matrixL / multiplier;
			Assert::AreEqual(static_cast<double>(m00L / multiplier), static_cast<double>(product.M00()), 0.0001);
			Assert::AreEqual(static_cast<double>(m10L / multiplier), static_cast<double>(product.M10()), 0.0001);
			Assert::AreEqual(static_cast<double>(m20L / multiplier), static_cast<double>(product.M20()), 0.0001);
			Assert::AreEqual(static_cast<double>(m30L / multiplier), static_cast<double>(product.M30()), 0.0001);
			Assert::AreEqual(static_cast<double>(m01L / multiplier), static_cast<double>(product.M01()), 0.0001);
			Assert::AreEqual(static_cast<double>(m11L / multiplier), static_cast<double>(product.M11()), 0.0001);
			Assert::AreEqual(static_cast<double>(m21L / multiplier), static_cast<double>(product.M21()), 0.0001);
			Assert::AreEqual(static_cast<double>(m31L / multiplier), static_cast<double>(product.M31()), 0.0001);
			Assert::AreEqual(static_cast<double>(m02L / multiplier), static_cast<double>(product.M02()), 0.0001);
			Assert::AreEqual(static_cast<double>(m12L / multiplier), static_cast<double>(product.M12()), 0.0001);
			Assert::AreEqual(static_cast<double>(m22L / multiplier), static_cast<double>(product.M22()), 0.0001);
			Assert::AreEqual(static_cast<double>(m32L / multiplier), static_cast<double>(product.M32()), 0.0001);
			Assert::AreEqual(static_cast<double>(m03L / multiplier), static_cast<double>(product.M03()), 0.0001);
			Assert::AreEqual(static_cast<double>(m13L / multiplier), static_cast<double>(product.M13()), 0.0001);
			Assert::AreEqual(static_cast<double>(m23L / multiplier), static_cast<double>(product.M23()), 0.0001);
			Assert::AreEqual(static_cast<double>(m33L / multiplier), static_cast<double>(product.M33()), 0.0001);
			Assert::IsTrue(multiplier * matrixL == matrixL * multiplier);
		}

		static constexpr PonyEngine::Math::Matrix4x4<int> MatrixConstexpr()
		{
			[[maybe_unused]] auto matrix = PonyEngine::Math::Matrix4x4<int>();
			PonyEngine::Math::Matrix4x4<int> movedMatrix = std::move(matrix);

			movedMatrix.M00() += 1;
			movedMatrix.M10() -= 2;
			movedMatrix.M20() -= 3;
			movedMatrix.M30() /= 3;
			movedMatrix.M01() *= 2;
			movedMatrix.M11() = 6;
			movedMatrix.M21() = 9;
			movedMatrix.M31() /= 9;
			movedMatrix.M02() *= 6;
			movedMatrix.M12() = 7;
			movedMatrix.M22() = 1;
			movedMatrix.M32() += 1;
			movedMatrix.M03() -= 6;
			movedMatrix.M13() /= 7;
			movedMatrix.M23() *= 1;
			movedMatrix.M33() += 1;
			[[maybe_unused]] int* const data = movedMatrix.Data();
			[[maybe_unused]] int* const columnData = movedMatrix.Data(1);

			[[maybe_unused]] constexpr auto constMatrix = PonyEngine::Math::Matrix4x4<int>(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8);
			[[maybe_unused]] const int* const dataC = constMatrix.Data();
			[[maybe_unused]] const int* const columnDataC = constMatrix.Data(1);

			movedMatrix.SetRow(0, PonyEngine::Math::Vector4<int>(3, 6, 9, 5));
			movedMatrix.SetColumn(1, PonyEngine::Math::Vector4<int>(3, 6, 9, 3));
			movedMatrix.SetDiagonal(PonyEngine::Math::Vector4<int>(3, 6, 9, 4));
			movedMatrix.SetCounterDiagonal(PonyEngine::Math::Vector4<int>(3, 6, 9, 3));

			movedMatrix.Set(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8);
			movedMatrix.Set(PonyEngine::Math::Vector4<int>(3, 6, 9, 5), PonyEngine::Math::Vector4<int>(3, 6, 9, 5), PonyEngine::Math::Vector4<int>(3, 6, 9, 5), PonyEngine::Math::Vector4<int>(3, 6, 9, 5));
			movedMatrix.Set(std::array<int, 16>{4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8}.data());

			movedMatrix.Scale(constMatrix);

			movedMatrix[1][1] = 5;
			movedMatrix[1] = PonyEngine::Math::Vector4<int>(9, 4, 8, 5);

			[[maybe_unused]] auto copyAssigned = PonyEngine::Math::Matrix4x4<int>();
			copyAssigned = movedMatrix;
			movedMatrix = std::move(copyAssigned);

			movedMatrix += constMatrix;
			movedMatrix -= constMatrix;
			movedMatrix *= 3;
			movedMatrix *= 3.f;

			[[maybe_unused]] auto leftMatrix = PonyEngine::Math::Matrix4x4<int>(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8);
			[[maybe_unused]] constexpr auto rightMatrix = PonyEngine::Math::Matrix4x4<int>(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8); // Left and right are MSVC internal compiler error overcome.
			leftMatrix *= rightMatrix;
			leftMatrix /= 4;
			leftMatrix /= 5.f;

			return movedMatrix;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> identity = PonyEngine::Math::Matrix4x4<int>::Predefined::Identity;
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> zero = PonyEngine::Math::Matrix4x4<int>::Predefined::Zero;

			[[maybe_unused]] constexpr auto defaultMatrix = PonyEngine::Math::Matrix4x4<int>();
			[[maybe_unused]] constexpr auto matrix = PonyEngine::Math::Matrix4x4<int>(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8);
			[[maybe_unused]] constexpr auto columnMatrix = PonyEngine::Math::Matrix4x4<int>(PonyEngine::Math::Vector4<int>(3, 6, 9, 5), PonyEngine::Math::Vector4<int>(3, 6, 9, 5), PonyEngine::Math::Vector4<int>(3, 6, 9, 5), PonyEngine::Math::Vector4<int>(3, 6, 9, 5));
			[[maybe_unused]] constexpr auto arrayMatrix = PonyEngine::Math::Matrix4x4<int>(std::array<int, 16>{4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8}.data());
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> copiedMatrix = matrix;
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> movedMatrix = MatrixConstexpr();

			[[maybe_unused]] constexpr int m00 = matrix.M00();
			[[maybe_unused]] constexpr int m10 = matrix.M10();
			[[maybe_unused]] constexpr int m20 = matrix.M20();
			[[maybe_unused]] constexpr int m30 = matrix.M30();
			[[maybe_unused]] constexpr int m01 = matrix.M01();
			[[maybe_unused]] constexpr int m11 = matrix.M11();
			[[maybe_unused]] constexpr int m21 = matrix.M21();
			[[maybe_unused]] constexpr int m31 = matrix.M31();
			[[maybe_unused]] constexpr int m02 = matrix.M02();
			[[maybe_unused]] constexpr int m12 = matrix.M12();
			[[maybe_unused]] constexpr int m22 = matrix.M22();
			[[maybe_unused]] constexpr int m32 = matrix.M32();
			[[maybe_unused]] constexpr int m03 = matrix.M03();
			[[maybe_unused]] constexpr int m13 = matrix.M13();
			[[maybe_unused]] constexpr int m23 = matrix.M23();
			[[maybe_unused]] constexpr int m33 = matrix.M33();

			[[maybe_unused]] constexpr PonyEngine::Math::Vector4<int> row = matrix.GetRow(1);
			[[maybe_unused]] constexpr PonyEngine::Math::Vector4<int> column = matrix.GetColumn(0);
			[[maybe_unused]] constexpr PonyEngine::Math::Vector4<int> diagonal = matrix.GetDiagonal();
			[[maybe_unused]] constexpr PonyEngine::Math::Vector4<int> counterDiagonal = matrix.GetCounterDiagonal();

			[[maybe_unused]] constexpr int trace = matrix.Trace();
			[[maybe_unused]] constexpr int determinant = matrix.Determinant();
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> adjugate = matrix.Adjugate();
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> transpose = matrix.Transpose();
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<float> inverse = PonyEngine::Math::Matrix4x4<float>(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8).Inverse();

			[[maybe_unused]] constexpr bool isZero = matrix.IsZero();
			[[maybe_unused]] constexpr bool isAlmostZero = PonyEngine::Math::Matrix4x4<float>::Predefined::Zero.IsAlmostZero();
			[[maybe_unused]] constexpr bool isIdentity = matrix.IsIdentity();
			[[maybe_unused]] constexpr bool isAlmostIdentity = PonyEngine::Math::Matrix4x4<float>::Predefined::Identity.IsAlmostIdentity();

			[[maybe_unused]] constexpr auto floatMatrix = static_cast<PonyEngine::Math::Matrix4x4<float>>(matrix);

			[[maybe_unused]] constexpr int m10A = matrix[1][0];
			[[maybe_unused]] constexpr PonyEngine::Math::Vector4<int> columnV = matrix[0];

			[[maybe_unused]] constexpr bool equal = matrix == defaultMatrix;
			[[maybe_unused]] constexpr bool notEqual = matrix != defaultMatrix;

			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> scaled = PonyEngine::Math::Scale(matrix, columnMatrix);
			[[maybe_unused]] constexpr bool areAlmostEqual = PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8), PonyEngine::Math::Matrix4x4<float>(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8));

			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> sum = matrix + columnMatrix;
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> negated = -matrix;
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> difference = matrix - columnMatrix;
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> productNumR = matrix * 3;
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> productNumL = 3 * matrix;
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> productNumFR = matrix * 3.f;
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> productNumFL = 3.f * matrix;
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> product = matrix * columnMatrix;
			[[maybe_unused]] constexpr PonyEngine::Math::Vector4<int> productV = matrix * PonyEngine::Math::Vector4<int>(4, 6, 1, 5);
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> quotient = matrix / 3;
			[[maybe_unused]] constexpr PonyEngine::Math::Matrix4x4<int> quotientF = matrix / 3.f;
		}
	};
}
