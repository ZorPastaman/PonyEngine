/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <format>
#include <ostream>
#include <span>
#include <string>
#include <type_traits>
#include <utility>

import PonyMath.Core;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(Matrix4x4Tests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<std::int8_t, PonyMath::Core::Matrix4x4<std::int8_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Matrix4x4<std::int8_t>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<std::int16_t, PonyMath::Core::Matrix4x4<std::int16_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Matrix4x4<std::int16_t>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<std::int32_t, PonyMath::Core::Matrix4x4<std::int32_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Matrix4x4<std::int32_t>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Matrix4x4<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Matrix4x4<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<std::int64_t, PonyMath::Core::Matrix4x4<std::int64_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::Matrix4x4<std::int64_t>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::Matrix4x4<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::Matrix4x4<double>::ComputationalType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{4}, PonyMath::Core::Matrix4x4<float>::Dimension);
			Assert::AreEqual(std::size_t{16}, PonyMath::Core::Matrix4x4<float>::ComponentCount);

			Assert::AreEqual(std::size_t{4}, PonyMath::Core::Matrix4x4<std::int16_t>::Dimension);
			Assert::AreEqual(std::size_t{16}, PonyMath::Core::Matrix4x4<std::int16_t>::ComponentCount);
		}

		TEST_METHOD(RowToVector4ShortTest)
		{
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

			const PonyMath::Core::Vector4<std::int16_t> row0 = matrix[0];
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());
			Assert::AreEqual(m02, row0.Z());
			Assert::AreEqual(m03, row0.W());

			const PonyMath::Core::Vector4<std::int16_t> row1 = matrix[1];
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
			Assert::AreEqual(m12, row1.Z());
			Assert::AreEqual(m13, row1.W());

			const PonyMath::Core::Vector4<std::int16_t> row2 = matrix[2];
			Assert::AreEqual(m20, row2.X());
			Assert::AreEqual(m21, row2.Y());
			Assert::AreEqual(m22, row2.Z());
			Assert::AreEqual(m23, row2.W());

			const PonyMath::Core::Vector4<std::int16_t> row3 = matrix[3];
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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

			const PonyMath::Core::Vector4<float> row0 = matrix[0];
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());
			Assert::AreEqual(m02, row0.Z());
			Assert::AreEqual(m03, row0.W());

			const PonyMath::Core::Vector4<float> row1 = matrix[1];
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
			Assert::AreEqual(m12, row1.Z());
			Assert::AreEqual(m13, row1.W());

			const PonyMath::Core::Vector4<float> row2 = matrix[2];
			Assert::AreEqual(m20, row2.X());
			Assert::AreEqual(m21, row2.Y());
			Assert::AreEqual(m22, row2.Z());
			Assert::AreEqual(m23, row2.W());

			const PonyMath::Core::Vector4<float> row3 = matrix[3];
			Assert::AreEqual(m30, row3.X());
			Assert::AreEqual(m31, row3.Y());
			Assert::AreEqual(m32, row3.Z());
			Assert::AreEqual(m33, row3.W());
		}

		TEST_METHOD(CastTest)
		{
			constexpr auto floatMatrix = PonyMath::Core::Matrix4x4<float>(3.1f, -2.2f, 4.4f, -2.1f, -5.9f, 4.8f, 7.1f, -6.5f, 12.f, 11.5f, -13.4f, -12.1f, 15.8f, -16.9f, 10.f, -1.f);
			const auto intMatrix = static_cast<PonyMath::Core::Matrix4x4<std::int32_t>>(floatMatrix);
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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

			constexpr std::int16_t m00New = 20;
			constexpr std::int16_t m10New = 30;
			constexpr std::int16_t m20New = 30;
			constexpr std::int16_t m30New = 21;
			constexpr std::int16_t m01New = -40;
			constexpr std::int16_t m11New = -50;
			constexpr std::int16_t m21New = 330;
			constexpr std::int16_t m31New = -10;
			constexpr std::int16_t m02New = 60;
			constexpr std::int16_t m12New = 70;
			constexpr std::int16_t m22New = 190;
			constexpr std::int16_t m32New = -100;
			constexpr std::int16_t m03New = 160;
			constexpr std::int16_t m13New = 170;
			constexpr std::int16_t m23New = 180;
			constexpr std::int16_t m33New = -130;
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
			auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

			constexpr std::int16_t m00New = 20;
			constexpr std::int16_t m10New = 30;
			constexpr std::int16_t m20New = 30;
			constexpr std::int16_t m30New = 21;
			constexpr std::int16_t m01New = -40;
			constexpr std::int16_t m11New = -50;
			constexpr std::int16_t m21New = 330;
			constexpr std::int16_t m31New = -10;
			constexpr std::int16_t m02New = 60;
			constexpr std::int16_t m12New = 70;
			constexpr std::int16_t m22New = 190;
			constexpr std::int16_t m32New = -100;
			constexpr std::int16_t m03New = 160;
			constexpr std::int16_t m13New = 170;
			constexpr std::int16_t m23New = 180;
			constexpr std::int16_t m33New = -130;
			matrix[0] = PonyMath::Core::Vector4<std::int16_t>(m00New, m01New, m02New, m03New);
			matrix[1] = PonyMath::Core::Vector4<std::int16_t>(m10New, m11New, m12New, m13New);
			matrix[2] = PonyMath::Core::Vector4<std::int16_t>(m20New, m21New, m22New, m23New);
			matrix[3] = PonyMath::Core::Vector4<std::int16_t>(m30New, m31New, m32New, m33New);

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
			auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);

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
			matrix[0] = PonyMath::Core::Vector4<float>(m00New, m01New, m02New, m03New);
			matrix[1] = PonyMath::Core::Vector4<float>(m10New, m11New, m12New, m13New);
			matrix[2] = PonyMath::Core::Vector4<float>(m20New, m21New, m22New, m23New);
			matrix[3] = PonyMath::Core::Vector4<float>(m30New, m31New, m32New, m33New);

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
			const auto defaultMatrix = PonyMath::Core::Matrix4x4<std::int16_t>();
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M00());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M10());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M20());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M30());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M01());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M11());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M21());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M31());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M02());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M12());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M22());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M32());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M03());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M13());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M23());
			Assert::AreEqual(std::int16_t{}, defaultMatrix.M33());
		}

		TEST_METHOD(DefaultConstructorFloatTest)
		{
			const auto defaultMatrix = PonyMath::Core::Matrix4x4<float>();
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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto column0 = PonyMath::Core::Vector4<std::int16_t>(m00, m10, m20, m30);
			constexpr auto column1 = PonyMath::Core::Vector4<std::int16_t>(m01, m11, m21, m31);
			constexpr auto column2 = PonyMath::Core::Vector4<std::int16_t>(m02, m12, m22, m32);
			constexpr auto column3 = PonyMath::Core::Vector4<std::int16_t>(m03, m13, m23, m33);
			const auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(column0, column1, column2, column3);
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
			constexpr auto column0 = PonyMath::Core::Vector4<float>(m00, m10, m20, m30);
			constexpr auto column1 = PonyMath::Core::Vector4<float>(m01, m11, m21, m31);
			constexpr auto column2 = PonyMath::Core::Vector4<float>(m02, m12, m22, m32);
			constexpr auto column3 = PonyMath::Core::Vector4<float>(m03, m13, m23, m33);
			const auto matrix = PonyMath::Core::Matrix4x4<float>(column0, column1, column2, column3);
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

		TEST_METHOD(ConstructorColumnSpanShortTest)
		{
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto column0 = PonyMath::Core::Vector4<std::int16_t>(m00, m10, m20, m30);
			constexpr auto column1 = PonyMath::Core::Vector4<std::int16_t>(m01, m11, m21, m31);
			constexpr auto column2 = PonyMath::Core::Vector4<std::int16_t>(m02, m12, m22, m32);
			constexpr auto column3 = PonyMath::Core::Vector4<std::int16_t>(m03, m13, m23, m33);
			constexpr auto columns = std::array{ column0, column1, column2, column3 };
			const auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(columns);
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

		TEST_METHOD(ConstructorColumnSpanFloatTest)
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
			constexpr auto column0 = PonyMath::Core::Vector4<float>(m00, m10, m20, m30);
			constexpr auto column1 = PonyMath::Core::Vector4<float>(m01, m11, m21, m31);
			constexpr auto column2 = PonyMath::Core::Vector4<float>(m02, m12, m22, m32);
			constexpr auto column3 = PonyMath::Core::Vector4<float>(m03, m13, m23, m33);
			constexpr auto columns = std::array{ column0, column1, column2, column3 };
			const auto matrix = PonyMath::Core::Matrix4x4<float>(columns);
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

		TEST_METHOD(ConstructorSpanShortTest)
		{
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr std::array<std::int16_t, 16> array{ m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33 };
			const auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(array);
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

		TEST_METHOD(ConstructorSpanFloatTest)
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
			const auto matrix = PonyMath::Core::Matrix4x4<float>(array);
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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;

			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			Assert::AreEqual(m00, matrix.Component(0));
			Assert::AreEqual(m10, matrix.Component(1));
			Assert::AreEqual(m20, matrix.Component(2));
			Assert::AreEqual(m30, matrix.Component(3));
			Assert::AreEqual(m01, matrix.Component(4));
			Assert::AreEqual(m11, matrix.Component(5));
			Assert::AreEqual(m21, matrix.Component(6));
			Assert::AreEqual(m31, matrix.Component(7));
			Assert::AreEqual(m02, matrix.Component(8));
			Assert::AreEqual(m12, matrix.Component(9));
			Assert::AreEqual(m22, matrix.Component(10));
			Assert::AreEqual(m32, matrix.Component(11));
			Assert::AreEqual(m03, matrix.Component(12));
			Assert::AreEqual(m13, matrix.Component(13));
			Assert::AreEqual(m23, matrix.Component(14));
			Assert::AreEqual(m33, matrix.Component(15));

			constexpr auto matrixC = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			Assert::AreEqual(m00, matrixC.Component(0));
			Assert::AreEqual(m10, matrixC.Component(1));
			Assert::AreEqual(m20, matrixC.Component(2));
			Assert::AreEqual(m30, matrixC.Component(3));
			Assert::AreEqual(m01, matrixC.Component(4));
			Assert::AreEqual(m11, matrixC.Component(5));
			Assert::AreEqual(m21, matrixC.Component(6));
			Assert::AreEqual(m31, matrixC.Component(7));
			Assert::AreEqual(m02, matrixC.Component(8));
			Assert::AreEqual(m12, matrixC.Component(9));
			Assert::AreEqual(m22, matrixC.Component(10));
			Assert::AreEqual(m32, matrixC.Component(11));
			Assert::AreEqual(m03, matrixC.Component(12));
			Assert::AreEqual(m13, matrixC.Component(13));
			Assert::AreEqual(m23, matrixC.Component(14));
			Assert::AreEqual(m33, matrixC.Component(15));
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

			auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			Assert::AreEqual(m00, matrix.Component(0));
			Assert::AreEqual(m10, matrix.Component(1));
			Assert::AreEqual(m20, matrix.Component(2));
			Assert::AreEqual(m30, matrix.Component(3));
			Assert::AreEqual(m01, matrix.Component(4));
			Assert::AreEqual(m11, matrix.Component(5));
			Assert::AreEqual(m21, matrix.Component(6));
			Assert::AreEqual(m31, matrix.Component(7));
			Assert::AreEqual(m02, matrix.Component(8));
			Assert::AreEqual(m12, matrix.Component(9));
			Assert::AreEqual(m22, matrix.Component(10));
			Assert::AreEqual(m32, matrix.Component(11));
			Assert::AreEqual(m03, matrix.Component(12));
			Assert::AreEqual(m13, matrix.Component(13));
			Assert::AreEqual(m23, matrix.Component(14));
			Assert::AreEqual(m33, matrix.Component(15));

			constexpr auto matrixC = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			Assert::AreEqual(m00, matrixC.Component(0));
			Assert::AreEqual(m10, matrixC.Component(1));
			Assert::AreEqual(m20, matrixC.Component(2));
			Assert::AreEqual(m30, matrixC.Component(3));
			Assert::AreEqual(m01, matrixC.Component(4));
			Assert::AreEqual(m11, matrixC.Component(5));
			Assert::AreEqual(m21, matrixC.Component(6));
			Assert::AreEqual(m31, matrixC.Component(7));
			Assert::AreEqual(m02, matrixC.Component(8));
			Assert::AreEqual(m12, matrixC.Component(9));
			Assert::AreEqual(m22, matrixC.Component(10));
			Assert::AreEqual(m32, matrixC.Component(11));
			Assert::AreEqual(m03, matrixC.Component(12));
			Assert::AreEqual(m13, matrixC.Component(13));
			Assert::AreEqual(m23, matrixC.Component(14));
			Assert::AreEqual(m33, matrixC.Component(15));
		}

		TEST_METHOD(SpanShortTest)
		{
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;

			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrix.Span()[0]);
			Assert::AreEqual(m10, matrix.Span()[1]);
			Assert::AreEqual(m20, matrix.Span()[2]);
			Assert::AreEqual(m30, matrix.Span()[3]);
			Assert::AreEqual(m01, matrix.Span()[4]);
			Assert::AreEqual(m11, matrix.Span()[5]);
			Assert::AreEqual(m21, matrix.Span()[6]);
			Assert::AreEqual(m31, matrix.Span()[7]);
			Assert::AreEqual(m02, matrix.Span()[8]);
			Assert::AreEqual(m12, matrix.Span()[9]);
			Assert::AreEqual(m22, matrix.Span()[10]);
			Assert::AreEqual(m32, matrix.Span()[11]);
			Assert::AreEqual(m03, matrix.Span()[12]);
			Assert::AreEqual(m13, matrix.Span()[13]);
			Assert::AreEqual(m23, matrix.Span()[14]);
			Assert::AreEqual(m33, matrix.Span()[15]);
			Assert::AreEqual(m00, matrix.Span(0)[0]);
			Assert::AreEqual(m10, matrix.Span(0)[1]);
			Assert::AreEqual(m20, matrix.Span(0)[2]);
			Assert::AreEqual(m30, matrix.Span(0)[3]);
			Assert::AreEqual(m01, matrix.Span(1)[0]);
			Assert::AreEqual(m11, matrix.Span(1)[1]);
			Assert::AreEqual(m21, matrix.Span(1)[2]);
			Assert::AreEqual(m31, matrix.Span(1)[3]);
			Assert::AreEqual(m02, matrix.Span(2)[0]);
			Assert::AreEqual(m12, matrix.Span(2)[1]);
			Assert::AreEqual(m22, matrix.Span(2)[2]);
			Assert::AreEqual(m32, matrix.Span(2)[3]);
			Assert::AreEqual(m03, matrix.Span(3)[0]);
			Assert::AreEqual(m13, matrix.Span(3)[1]);
			Assert::AreEqual(m23, matrix.Span(3)[2]);
			Assert::AreEqual(m33, matrix.Span(3)[3]);

			constexpr auto matrixC = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrixC.Span()[0]);
			Assert::AreEqual(m10, matrixC.Span()[1]);
			Assert::AreEqual(m20, matrixC.Span()[2]);
			Assert::AreEqual(m30, matrixC.Span()[3]);
			Assert::AreEqual(m01, matrixC.Span()[4]);
			Assert::AreEqual(m11, matrixC.Span()[5]);
			Assert::AreEqual(m21, matrixC.Span()[6]);
			Assert::AreEqual(m31, matrixC.Span()[7]);
			Assert::AreEqual(m02, matrixC.Span()[8]);
			Assert::AreEqual(m12, matrixC.Span()[9]);
			Assert::AreEqual(m22, matrixC.Span()[10]);
			Assert::AreEqual(m32, matrixC.Span()[11]);
			Assert::AreEqual(m03, matrixC.Span()[12]);
			Assert::AreEqual(m13, matrixC.Span()[13]);
			Assert::AreEqual(m23, matrixC.Span()[14]);
			Assert::AreEqual(m33, matrixC.Span()[15]);
			Assert::AreEqual(m00, matrixC.Span(0)[0]);
			Assert::AreEqual(m10, matrixC.Span(0)[1]);
			Assert::AreEqual(m20, matrixC.Span(0)[2]);
			Assert::AreEqual(m30, matrixC.Span(0)[3]);
			Assert::AreEqual(m01, matrixC.Span(1)[0]);
			Assert::AreEqual(m11, matrixC.Span(1)[1]);
			Assert::AreEqual(m21, matrixC.Span(1)[2]);
			Assert::AreEqual(m31, matrixC.Span(1)[3]);
			Assert::AreEqual(m02, matrixC.Span(2)[0]);
			Assert::AreEqual(m12, matrixC.Span(2)[1]);
			Assert::AreEqual(m22, matrixC.Span(2)[2]);
			Assert::AreEqual(m32, matrixC.Span(2)[3]);
			Assert::AreEqual(m03, matrixC.Span(3)[0]);
			Assert::AreEqual(m13, matrixC.Span(3)[1]);
			Assert::AreEqual(m23, matrixC.Span(3)[2]);
			Assert::AreEqual(m33, matrixC.Span(3)[3]);
		}

		TEST_METHOD(SpanFloatTest)
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

			auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrix.Span()[0]);
			Assert::AreEqual(m10, matrix.Span()[1]);
			Assert::AreEqual(m20, matrix.Span()[2]);
			Assert::AreEqual(m30, matrix.Span()[3]);
			Assert::AreEqual(m01, matrix.Span()[4]);
			Assert::AreEqual(m11, matrix.Span()[5]);
			Assert::AreEqual(m21, matrix.Span()[6]);
			Assert::AreEqual(m31, matrix.Span()[7]);
			Assert::AreEqual(m02, matrix.Span()[8]);
			Assert::AreEqual(m12, matrix.Span()[9]);
			Assert::AreEqual(m22, matrix.Span()[10]);
			Assert::AreEqual(m32, matrix.Span()[11]);
			Assert::AreEqual(m03, matrix.Span()[12]);
			Assert::AreEqual(m13, matrix.Span()[13]);
			Assert::AreEqual(m23, matrix.Span()[14]);
			Assert::AreEqual(m33, matrix.Span()[15]);
			Assert::AreEqual(m00, matrix.Span(0)[0]);
			Assert::AreEqual(m10, matrix.Span(0)[1]);
			Assert::AreEqual(m20, matrix.Span(0)[2]);
			Assert::AreEqual(m30, matrix.Span(0)[3]);
			Assert::AreEqual(m01, matrix.Span(1)[0]);
			Assert::AreEqual(m11, matrix.Span(1)[1]);
			Assert::AreEqual(m21, matrix.Span(1)[2]);
			Assert::AreEqual(m31, matrix.Span(1)[3]);
			Assert::AreEqual(m02, matrix.Span(2)[0]);
			Assert::AreEqual(m12, matrix.Span(2)[1]);
			Assert::AreEqual(m22, matrix.Span(2)[2]);
			Assert::AreEqual(m32, matrix.Span(2)[3]);
			Assert::AreEqual(m03, matrix.Span(3)[0]);
			Assert::AreEqual(m13, matrix.Span(3)[1]);
			Assert::AreEqual(m23, matrix.Span(3)[2]);
			Assert::AreEqual(m33, matrix.Span(3)[3]);

			constexpr auto matrixC = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(m00, matrixC.Span()[0]);
			Assert::AreEqual(m10, matrixC.Span()[1]);
			Assert::AreEqual(m20, matrixC.Span()[2]);
			Assert::AreEqual(m30, matrixC.Span()[3]);
			Assert::AreEqual(m01, matrixC.Span()[4]);
			Assert::AreEqual(m11, matrixC.Span()[5]);
			Assert::AreEqual(m21, matrixC.Span()[6]);
			Assert::AreEqual(m31, matrixC.Span()[7]);
			Assert::AreEqual(m02, matrixC.Span()[8]);
			Assert::AreEqual(m12, matrixC.Span()[9]);
			Assert::AreEqual(m22, matrixC.Span()[10]);
			Assert::AreEqual(m32, matrixC.Span()[11]);
			Assert::AreEqual(m03, matrixC.Span()[12]);
			Assert::AreEqual(m13, matrixC.Span()[13]);
			Assert::AreEqual(m23, matrixC.Span()[14]);
			Assert::AreEqual(m33, matrixC.Span()[15]);
			Assert::AreEqual(m00, matrixC.Span(0)[0]);
			Assert::AreEqual(m10, matrixC.Span(0)[1]);
			Assert::AreEqual(m20, matrixC.Span(0)[2]);
			Assert::AreEqual(m30, matrixC.Span(0)[3]);
			Assert::AreEqual(m01, matrixC.Span(1)[0]);
			Assert::AreEqual(m11, matrixC.Span(1)[1]);
			Assert::AreEqual(m21, matrixC.Span(1)[2]);
			Assert::AreEqual(m31, matrixC.Span(1)[3]);
			Assert::AreEqual(m02, matrixC.Span(2)[0]);
			Assert::AreEqual(m12, matrixC.Span(2)[1]);
			Assert::AreEqual(m22, matrixC.Span(2)[2]);
			Assert::AreEqual(m32, matrixC.Span(2)[3]);
			Assert::AreEqual(m03, matrixC.Span(3)[0]);
			Assert::AreEqual(m13, matrixC.Span(3)[1]);
			Assert::AreEqual(m23, matrixC.Span(3)[2]);
			Assert::AreEqual(m33, matrixC.Span(3)[3]);
		}

		TEST_METHOD(GetRowShortTest)
		{
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto row0 = matrix.Row(0);
			const auto row1 = matrix.Row(1);
			const auto row2 = matrix.Row(2);
			const auto row3 = matrix.Row(3);
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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto row0 = matrix.Row(0);
			const auto row1 = matrix.Row(1);
			const auto row2 = matrix.Row(2);
			const auto row3 = matrix.Row(3);
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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>();
			constexpr auto row0 = PonyMath::Core::Vector4<std::int16_t>(m00, m01, m02, m03);
			constexpr auto row1 = PonyMath::Core::Vector4<std::int16_t>(m10, m11, m12, m13);
			constexpr auto row2 = PonyMath::Core::Vector4<std::int16_t>(m20, m21, m22, m23);
			constexpr auto row3 = PonyMath::Core::Vector4<std::int16_t>(m30, m31, m32, m33);
			matrix.Row(0, row0);
			matrix.Row(1, row1);
			matrix.Row(2, row2);
			matrix.Row(3, row3);
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
			auto matrix = PonyMath::Core::Matrix4x4<float>();
			constexpr auto row0 = PonyMath::Core::Vector4<float>(m00, m01, m02, m03);
			constexpr auto row1 = PonyMath::Core::Vector4<float>(m10, m11, m12, m13);
			constexpr auto row2 = PonyMath::Core::Vector4<float>(m20, m21, m22, m23);
			constexpr auto row3 = PonyMath::Core::Vector4<float>(m30, m31, m32, m33);
			matrix.Row(0, row0);
			matrix.Row(1, row1);
			matrix.Row(2, row2);
			matrix.Row(3, row3);
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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto column0 = matrix.Column(0);
			const auto column1 = matrix.Column(1);
			const auto column2 = matrix.Column(2);
			const auto column3 = matrix.Column(3);
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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto column0 = matrix.Column(0);
			const auto column1 = matrix.Column(1);
			const auto column2 = matrix.Column(2);
			const auto column3 = matrix.Column(3);
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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>();
			constexpr auto column0 = PonyMath::Core::Vector4<std::int16_t>(m00, m10, m20, m30);
			constexpr auto column1 = PonyMath::Core::Vector4<std::int16_t>(m01, m11, m21, m31);
			constexpr auto column2 = PonyMath::Core::Vector4<std::int16_t>(m02, m12, m22, m32);
			constexpr auto column3 = PonyMath::Core::Vector4<std::int16_t>(m03, m13, m23, m33);
			matrix.Column(0, column0);
			matrix.Column(1, column1);
			matrix.Column(2, column2);
			matrix.Column(3, column3);
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
			auto matrix = PonyMath::Core::Matrix4x4<float>();
			constexpr auto column0 = PonyMath::Core::Vector4<float>(m00, m10, m20, m30);
			constexpr auto column1 = PonyMath::Core::Vector4<float>(m01, m11, m21, m31);
			constexpr auto column2 = PonyMath::Core::Vector4<float>(m02, m12, m22, m32);
			constexpr auto column3 = PonyMath::Core::Vector4<float>(m03, m13, m23, m33);
			matrix.Column(0, column0);
			matrix.Column(1, column1);
			matrix.Column(2, column2);
			matrix.Column(3, column3);
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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto diagonal = matrix.Diagonal();
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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto diagonal = matrix.Diagonal();
			Assert::AreEqual(m00, diagonal.X());
			Assert::AreEqual(m11, diagonal.Y());
			Assert::AreEqual(m22, diagonal.Z());
			Assert::AreEqual(m33, diagonal.W());
		}

		TEST_METHOD(SetDiagonalShortTest)
		{
			constexpr std::int16_t m00 = 3;
			constexpr std::int16_t m11 = -2;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m33 = 2;
			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>();
			constexpr auto diagonal = PonyMath::Core::Vector4<std::int16_t>(m00, m11, m22, m33);
			matrix.Diagonal(diagonal);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(std::int16_t{}, matrix.M10());
			Assert::AreEqual(std::int16_t{}, matrix.M20());
			Assert::AreEqual(std::int16_t{}, matrix.M30());
			Assert::AreEqual(std::int16_t{}, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(std::int16_t{}, matrix.M21());
			Assert::AreEqual(std::int16_t{}, matrix.M31());
			Assert::AreEqual(std::int16_t{}, matrix.M02());
			Assert::AreEqual(std::int16_t{}, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(std::int16_t{}, matrix.M32());
			Assert::AreEqual(std::int16_t{}, matrix.M03());
			Assert::AreEqual(std::int16_t{}, matrix.M13());
			Assert::AreEqual(std::int16_t{}, matrix.M23());
			Assert::AreEqual(m33, matrix.M33());
		}

		TEST_METHOD(SetDiagonalFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m11 = -2;
			constexpr float m22 = 19;
			constexpr float m33 = 2;
			auto matrix = PonyMath::Core::Matrix4x4<float>();
			constexpr auto diagonal = PonyMath::Core::Vector4<float>(m00, m11, m22, m33);
			matrix.Diagonal(diagonal);
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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto counterDiagonal = matrix.CounterDiagonal();
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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto counterDiagonal = matrix.CounterDiagonal();
			Assert::AreEqual(m03, counterDiagonal.X());
			Assert::AreEqual(m12, counterDiagonal.Y());
			Assert::AreEqual(m21, counterDiagonal.Z());
			Assert::AreEqual(m30, counterDiagonal.W());
		}

		TEST_METHOD(SetCounterDiagonalShortTest)
		{
			constexpr std::int16_t m03 = 3;
			constexpr std::int16_t m12 = -2;
			constexpr std::int16_t m21 = 19;
			constexpr std::int16_t m30 = 2;
			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>();
			constexpr auto counterDiagonal = PonyMath::Core::Vector4<std::int16_t>(m03, m12, m21, m30);
			matrix.CounterDiagonal(counterDiagonal);
			Assert::AreEqual(std::int16_t{}, matrix.M00());
			Assert::AreEqual(std::int16_t{}, matrix.M10());
			Assert::AreEqual(std::int16_t{}, matrix.M20());
			Assert::AreEqual(m30, matrix.M30());
			Assert::AreEqual(std::int16_t{}, matrix.M01());
			Assert::AreEqual(std::int16_t{}, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(std::int16_t{}, matrix.M31());
			Assert::AreEqual(std::int16_t{}, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(std::int16_t{}, matrix.M22());
			Assert::AreEqual(std::int16_t{}, matrix.M32());
			Assert::AreEqual(m03, matrix.M03());
			Assert::AreEqual(std::int16_t{}, matrix.M13());
			Assert::AreEqual(std::int16_t{}, matrix.M23());
			Assert::AreEqual(std::int16_t{}, matrix.M33());
		}

		TEST_METHOD(SetCounterDiagonalFloatTest)
		{
			constexpr float m03 = 3;
			constexpr float m12 = -2;
			constexpr float m21 = 19;
			constexpr float m30 = 2;
			auto matrix = PonyMath::Core::Matrix4x4<float>();
			constexpr auto counterDiagonal = PonyMath::Core::Vector4<float>(m03, m12, m21, m30);
			matrix.CounterDiagonal(counterDiagonal);
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
			constexpr std::int16_t m00 = 10;
			constexpr std::int16_t m10 = -15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 22;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -20;
			constexpr std::int16_t m21 = 33;
			constexpr std::int16_t m31 = 11;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 19;
			constexpr std::int16_t m32 = -22;
			constexpr std::int16_t m03 = -12;
			constexpr std::int16_t m13 = 31;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(std::int16_t{11}, matrix.Trace());
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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(11.f, matrix.Trace());
		}

		TEST_METHOD(DeterminantShortTest)
		{
			constexpr std::int16_t m00 = 1;
			constexpr std::int16_t m10 = -5;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 2;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -2;
			constexpr std::int16_t m21 = 3;
			constexpr std::int16_t m31 = 1;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 9;
			constexpr std::int16_t m32 = -2;
			constexpr std::int16_t m03 = -1;
			constexpr std::int16_t m13 = 1;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(std::int16_t{578}, matrix.Determinant());
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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			Assert::AreEqual(578.f, matrix.Determinant());
		}

		TEST_METHOD(AdjugateShortTest)
		{
			constexpr std::int16_t m00 = 1;
			constexpr std::int16_t m10 = -5;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 2;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -2;
			constexpr std::int16_t m21 = 3;
			constexpr std::int16_t m31 = 1;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 9;
			constexpr std::int16_t m32 = -2;
			constexpr std::int16_t m03 = -1;
			constexpr std::int16_t m13 = 1;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto adjugate = matrix.Adjugate();
			Assert::AreEqual(std::int16_t{-96}, adjugate.M00());
			Assert::AreEqual(std::int16_t{160}, adjugate.M10());
			Assert::AreEqual(std::int16_t{-22}, adjugate.M20());
			Assert::AreEqual(std::int16_t{-6}, adjugate.M30());
			Assert::AreEqual(std::int16_t{-53}, adjugate.M01());
			Assert::AreEqual(std::int16_t{-8}, adjugate.M11());
			Assert::AreEqual(std::int16_t{30}, adjugate.M21());
			Assert::AreEqual(std::int16_t{87}, adjugate.M31());
			Assert::AreEqual(std::int16_t{113}, adjugate.M02());
			Assert::AreEqual(std::int16_t{-92}, adjugate.M12());
			Assert::AreEqual(std::int16_t{56}, adjugate.M22());
			Assert::AreEqual(std::int16_t{-11}, adjugate.M32());
			Assert::AreEqual(std::int16_t{35}, adjugate.M03());
			Assert::AreEqual(std::int16_t{38}, adjugate.M13());
			Assert::AreEqual(std::int16_t{2}, adjugate.M23());
			Assert::AreEqual(std::int16_t{237}, adjugate.M33());
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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			constexpr std::int16_t m00 = 1;
			constexpr std::int16_t m10 = -5;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 2;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = -2;
			constexpr std::int16_t m21 = 3;
			constexpr std::int16_t m31 = 1;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 9;
			constexpr std::int16_t m32 = -2;
			constexpr std::int16_t m03 = -1;
			constexpr std::int16_t m13 = 1;
			constexpr std::int16_t m23 = -1;
			constexpr std::int16_t m33 = 2;
			constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			Assert::IsTrue(PonyMath::Core::Matrix4x4<std::int16_t>::Predefined::Zero.IsZero());

			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyMath::Core::Matrix4x4<float>::ComponentCount; ++i)
			{
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyMath::Core::Matrix4x4<std::int16_t>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsZeroFloatTest)
		{
			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Zero.IsZero());

			auto matrix = PonyMath::Core::Matrix4x4<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyMath::Core::Matrix4x4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsZero());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyMath::Core::Matrix4x4<float>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsAlmostZeroTest)
		{
			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Zero.IsAlmostZero());

			auto matrix = PonyMath::Core::Matrix4x4<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsAlmostZero());

			for (std::size_t i = 0; i < PonyMath::Core::Matrix4x4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsAlmostZero());
				Assert::IsTrue(matrix.IsAlmostZero(5.f));
				matrix.Span()[i] = PonyMath::Core::Matrix4x4<float>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsIdentityShortTest)
		{
			Assert::IsTrue(PonyMath::Core::Matrix4x4<std::int16_t>::Predefined::Identity.IsIdentity());

			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>::Predefined::Identity;
			Assert::IsTrue(matrix.IsIdentity());

			for (std::size_t i = 0; i < PonyMath::Core::Matrix4x4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsIdentity());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsIdentity());
				matrix.Span()[i] = PonyMath::Core::Matrix4x4<std::int16_t>::Predefined::Identity.Span()[i];
			}
		}

		TEST_METHOD(IsIdentityFloatTest)
		{
			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Identity.IsIdentity());

			auto matrix = PonyMath::Core::Matrix4x4<float>::Predefined::Identity;
			Assert::IsTrue(matrix.IsIdentity());

			for (std::size_t i = 0; i < PonyMath::Core::Matrix4x4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsIdentity());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsFalse(matrix.IsIdentity());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsIdentity());
				matrix.Span()[i] = PonyMath::Core::Matrix4x4<float>::Predefined::Identity.Span()[i];
			}
		}

		TEST_METHOD(IsAlmostIdentityTest)
		{
			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Identity.IsAlmostIdentity());

			auto matrix = PonyMath::Core::Matrix4x4<float>::Predefined::Identity;
			Assert::IsTrue(matrix.IsAlmostIdentity());

			for (std::size_t i = 0; i < PonyMath::Core::Matrix4x4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsAlmostIdentity());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsTrue(matrix.IsAlmostIdentity());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsAlmostIdentity());
				Assert::IsTrue(matrix.IsAlmostIdentity(5.f));
				matrix.Span()[i] = PonyMath::Core::Matrix4x4<float>::Predefined::Identity.Span()[i];
			}
		}

		TEST_METHOD(IsFiniteTest)
		{
			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Zero.IsFinite());
			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Identity.IsFinite());

			const float nan = std::numeric_limits<float>::quiet_NaN();
			constexpr std::array<float, 16> array{ 3.f, 1.f, -5.f, 7.f, 4.f, -6.f, -7.f, 10.f, 20.f, -13.f, 14.f, 18.f, 9.f, 12.f, -11.f, 21.f };
			auto matrix = PonyMath::Core::Matrix4x4<float>(array);
			Assert::IsTrue(matrix.IsFinite());
			for (std::size_t i = 0; i < PonyMath::Core::Matrix4x4<float>::ComponentCount; ++i)
			{
				matrix.Span()[i] = nan;
				Assert::IsFalse(matrix.IsFinite());
				matrix.Span()[i] = array[i];
			}
		}

		TEST_METHOD(MultiplyThisShortTest)
		{
			constexpr std::int16_t m00 = 11;
			constexpr std::int16_t m10 = 5;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 5;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = 2;
			constexpr std::int16_t m21 = 3;
			constexpr std::int16_t m31 = 1;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 9;
			constexpr std::int16_t m32 = 2;
			constexpr std::int16_t m03 = 3;
			constexpr std::int16_t m13 = 1;
			constexpr std::int16_t m23 = 1;
			constexpr std::int16_t m33 = 1;
			constexpr std::int16_t m00S = 3;
			constexpr std::int16_t m10S = -2;
			constexpr std::int16_t m20S = 5;
			constexpr std::int16_t m30S = 7;
			constexpr std::int16_t m01S = 4;
			constexpr std::int16_t m11S = -1;
			constexpr std::int16_t m21S = 7;
			constexpr std::int16_t m31S = -3;
			constexpr std::int16_t m02S = -5;
			constexpr std::int16_t m12S = 6;
			constexpr std::int16_t m22S = -7;
			constexpr std::int16_t m32S = 8;
			constexpr std::int16_t m03S = 4;
			constexpr std::int16_t m13S = -1;
			constexpr std::int16_t m23S = 9;
			constexpr std::int16_t m33S = -8;
			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr auto scale = PonyMath::Core::Matrix4x4<std::int16_t>(m00S, m10S, m20S, m30S, m01S, m11S, m21S, m31S, m02S, m12S, m22S, m32S, m03S, m13S, m23S, m33S);
			matrix.Multiply(scale);
			Assert::AreEqual(static_cast<std::int16_t>(m00 * m00S), matrix.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10 * m10S), matrix.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20 * m20S), matrix.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30 * m30S), matrix.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01 * m01S), matrix.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11 * m11S), matrix.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21 * m21S), matrix.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31 * m31S), matrix.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02 * m02S), matrix.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12 * m12S), matrix.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22 * m22S), matrix.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32 * m32S), matrix.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03 * m03S), matrix.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13 * m13S), matrix.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23 * m23S), matrix.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33 * m33S), matrix.M33());
		}

		TEST_METHOD(MultiplyThisFloatTest)
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
			auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr auto scale = PonyMath::Core::Matrix4x4<float>(m00S, m10S, m20S, m30S, m01S, m11S, m21S, m31S, m02S, m12S, m22S, m32S, m03S, m13S, m23S, m33S);
			matrix.Multiply(scale);
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

		TEST_METHOD(DivideThisShortTest)
		{
			constexpr std::int16_t m00 = 11;
			constexpr std::int16_t m10 = 5;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 5;
			constexpr std::int16_t m01 = 5;
			constexpr std::int16_t m11 = 2;
			constexpr std::int16_t m21 = 3;
			constexpr std::int16_t m31 = 1;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 9;
			constexpr std::int16_t m32 = 2;
			constexpr std::int16_t m03 = 3;
			constexpr std::int16_t m13 = 1;
			constexpr std::int16_t m23 = 1;
			constexpr std::int16_t m33 = 1;
			constexpr std::int16_t m00S = 3;
			constexpr std::int16_t m10S = -2;
			constexpr std::int16_t m20S = 5;
			constexpr std::int16_t m30S = 7;
			constexpr std::int16_t m01S = 4;
			constexpr std::int16_t m11S = -1;
			constexpr std::int16_t m21S = 7;
			constexpr std::int16_t m31S = -3;
			constexpr std::int16_t m02S = -5;
			constexpr std::int16_t m12S = 6;
			constexpr std::int16_t m22S = -7;
			constexpr std::int16_t m32S = 8;
			constexpr std::int16_t m03S = 4;
			constexpr std::int16_t m13S = -1;
			constexpr std::int16_t m23S = 9;
			constexpr std::int16_t m33S = -8;
			auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr auto scale = PonyMath::Core::Matrix4x4<std::int16_t>(m00S, m10S, m20S, m30S, m01S, m11S, m21S, m31S, m02S, m12S, m22S, m32S, m03S, m13S, m23S, m33S);
			matrix.Divide(scale);
			Assert::AreEqual(static_cast<std::int16_t>(m00 / m00S), matrix.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10 / m10S), matrix.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20 / m20S), matrix.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30 / m30S), matrix.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01 / m01S), matrix.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11 / m11S), matrix.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21 / m21S), matrix.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31 / m31S), matrix.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02 / m02S), matrix.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12 / m12S), matrix.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22 / m22S), matrix.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32 / m32S), matrix.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03 / m03S), matrix.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13 / m13S), matrix.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23 / m23S), matrix.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33 / m33S), matrix.M33());
		}

		TEST_METHOD(DivideThisFloatTest)
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
			auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr auto scale = PonyMath::Core::Matrix4x4<float>(m00S, m10S, m20S, m30S, m01S, m11S, m21S, m31S, m02S, m12S, m22S, m32S, m03S, m13S, m23S, m33S);
			matrix.Divide(scale);
			Assert::AreEqual(m00 / m00S, matrix.M00(), 0.0001f);
			Assert::AreEqual(m10 / m10S, matrix.M10(), 0.0001f);
			Assert::AreEqual(m20 / m20S, matrix.M20(), 0.0001f);
			Assert::AreEqual(m30 / m30S, matrix.M30(), 0.0001f);
			Assert::AreEqual(m01 / m01S, matrix.M01(), 0.0001f);
			Assert::AreEqual(m11 / m11S, matrix.M11(), 0.0001f);
			Assert::AreEqual(m21 / m21S, matrix.M21(), 0.0001f);
			Assert::AreEqual(m31 / m31S, matrix.M31(), 0.0001f);
			Assert::AreEqual(m02 / m02S, matrix.M02(), 0.0001f);
			Assert::AreEqual(m12 / m12S, matrix.M12(), 0.0001f);
			Assert::AreEqual(m22 / m22S, matrix.M22(), 0.0001f);
			Assert::AreEqual(m32 / m32S, matrix.M32(), 0.0001f);
			Assert::AreEqual(m03 / m03S, matrix.M03(), 0.0001f);
			Assert::AreEqual(m13 / m13S, matrix.M13(), 0.0001f);
			Assert::AreEqual(m23 / m23S, matrix.M23(), 0.0001f);
			Assert::AreEqual(m33 / m33S, matrix.M33(), 0.0001f);
		}

		TEST_METHOD(ToStringShortTest)
		{
			constexpr std::int16_t m00 = 11;
			constexpr std::int16_t m10 = 15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 5;
			constexpr std::int16_t m01 = 55;
			constexpr std::int16_t m11 = 2;
			constexpr std::int16_t m21 = 30;
			constexpr std::int16_t m31 = 1;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 9;
			constexpr std::int16_t m32 = 21;
			constexpr std::int16_t m03 = -13;
			constexpr std::int16_t m13 = 10;
			constexpr std::int16_t m23 = 11;
			constexpr std::int16_t m33 = -6;
			constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			constexpr auto matrix = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			const auto expectedString = std::format("({}, {}, {}, {})({}, {}, {}, {})({}, {}, {}, {})({}, {}, {}, {})", m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
			Assert::AreEqual(expectedString, matrix.ToString());
			std::ostringstream ss;
			ss << matrix;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(AssignmentCopyShortTest)
		{
			constexpr std::int16_t m00 = 11;
			constexpr std::int16_t m10 = 15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 5;
			constexpr std::int16_t m01 = 55;
			constexpr std::int16_t m11 = 2;
			constexpr std::int16_t m21 = 30;
			constexpr std::int16_t m31 = 1;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 9;
			constexpr std::int16_t m32 = 21;
			constexpr std::int16_t m03 = -13;
			constexpr std::int16_t m13 = 10;
			constexpr std::int16_t m23 = 11;
			constexpr std::int16_t m33 = -6;
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyMath::Core::Matrix4x4<std::int16_t> matrixC;
			PonyMath::Core::Matrix4x4<std::int16_t>& matrixL = matrixC = matrixR;
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
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyMath::Core::Matrix4x4<float> matrixC;
			PonyMath::Core::Matrix4x4<float>& matrixL = matrixC = matrixR;
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
			constexpr std::int16_t m00 = 11;
			constexpr std::int16_t m10 = 15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 5;
			constexpr std::int16_t m01 = 55;
			constexpr std::int16_t m11 = 2;
			constexpr std::int16_t m21 = 30;
			constexpr std::int16_t m31 = 1;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 9;
			constexpr std::int16_t m32 = 21;
			constexpr std::int16_t m03 = -13;
			constexpr std::int16_t m13 = 10;
			constexpr std::int16_t m23 = 11;
			constexpr std::int16_t m33 = -6;
			auto matrixR = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyMath::Core::Matrix4x4<std::int16_t> matrixC;
			PonyMath::Core::Matrix4x4<std::int16_t>& matrixL = matrixC = std::move(matrixR);
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
			auto matrixR = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyMath::Core::Matrix4x4<float> matrixC;
			PonyMath::Core::Matrix4x4<float>& matrixL = matrixC = std::move(matrixR);
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
			constexpr std::int16_t m00 = 11;
			constexpr std::int16_t m10 = 15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 5;
			constexpr std::int16_t m01 = 55;
			constexpr std::int16_t m11 = 2;
			constexpr std::int16_t m21 = 30;
			constexpr std::int16_t m31 = 1;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 9;
			constexpr std::int16_t m32 = 21;
			constexpr std::int16_t m03 = -13;
			constexpr std::int16_t m13 = 10;
			constexpr std::int16_t m23 = 11;
			constexpr std::int16_t m33 = -6;
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr std::int16_t m00C = 3;
			constexpr std::int16_t m10C = -2;
			constexpr std::int16_t m20C = 5;
			constexpr std::int16_t m30C = 15;
			constexpr std::int16_t m01C = 4;
			constexpr std::int16_t m11C = -1;
			constexpr std::int16_t m21C = 7;
			constexpr std::int16_t m31C = 17;
			constexpr std::int16_t m02C = -5;
			constexpr std::int16_t m12C = 6;
			constexpr std::int16_t m22C = -7;
			constexpr std::int16_t m32C = -17;
			constexpr std::int16_t m03C = 5;
			constexpr std::int16_t m13C = -6;
			constexpr std::int16_t m23C = 7;
			constexpr std::int16_t m33C = 17;
			auto matrixC = PonyMath::Core::Matrix4x4<std::int16_t>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyMath::Core::Matrix4x4<std::int16_t>& matrixL = matrixC += matrixR;
			Assert::AreEqual(static_cast<std::int16_t>(m00 + m00C), matrixC.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10 + m10C), matrixC.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20 + m20C), matrixC.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30 + m30C), matrixC.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01 + m01C), matrixC.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11 + m11C), matrixC.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21 + m21C), matrixC.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31 + m31C), matrixC.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02 + m02C), matrixC.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12 + m12C), matrixC.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22 + m22C), matrixC.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32 + m32C), matrixC.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03 + m03C), matrixC.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13 + m13C), matrixC.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23 + m23C), matrixC.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33 + m33C), matrixC.M33());
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
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			auto matrixC = PonyMath::Core::Matrix4x4<float>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyMath::Core::Matrix4x4<float>& matrixL = matrixC += matrixR;
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
			constexpr std::int16_t m00 = 11;
			constexpr std::int16_t m10 = 15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 5;
			constexpr std::int16_t m01 = 55;
			constexpr std::int16_t m11 = 2;
			constexpr std::int16_t m21 = 30;
			constexpr std::int16_t m31 = 1;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 9;
			constexpr std::int16_t m32 = 21;
			constexpr std::int16_t m03 = -13;
			constexpr std::int16_t m13 = 10;
			constexpr std::int16_t m23 = 11;
			constexpr std::int16_t m33 = -6;
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr std::int16_t m00C = 3;
			constexpr std::int16_t m10C = -2;
			constexpr std::int16_t m20C = 5;
			constexpr std::int16_t m30C = 15;
			constexpr std::int16_t m01C = 4;
			constexpr std::int16_t m11C = -1;
			constexpr std::int16_t m21C = 7;
			constexpr std::int16_t m31C = 17;
			constexpr std::int16_t m02C = -5;
			constexpr std::int16_t m12C = 6;
			constexpr std::int16_t m22C = -7;
			constexpr std::int16_t m32C = -17;
			constexpr std::int16_t m03C = 5;
			constexpr std::int16_t m13C = -6;
			constexpr std::int16_t m23C = 7;
			constexpr std::int16_t m33C = 17;
			auto matrixC = PonyMath::Core::Matrix4x4<std::int16_t>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyMath::Core::Matrix4x4<std::int16_t>& matrixL = matrixC -= matrixR;
			Assert::AreEqual(static_cast<std::int16_t>(m00C - m00), matrixC.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10C - m10), matrixC.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20C - m20), matrixC.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30C - m30), matrixC.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01C - m01), matrixC.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11C - m11), matrixC.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21C - m21), matrixC.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31C - m31), matrixC.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02C - m02), matrixC.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12C - m12), matrixC.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22C - m22), matrixC.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32C - m32), matrixC.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03C - m03), matrixC.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13C - m13), matrixC.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23C - m23), matrixC.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33C - m33), matrixC.M33());
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
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			auto matrixC = PonyMath::Core::Matrix4x4<float>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyMath::Core::Matrix4x4<float>& matrixL = matrixC -= matrixR;
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
			constexpr std::int16_t multiplierI = 3;
			constexpr std::int16_t m00C = 3;
			constexpr std::int16_t m10C = -2;
			constexpr std::int16_t m20C = 5;
			constexpr std::int16_t m30C = 15;
			constexpr std::int16_t m01C = 4;
			constexpr std::int16_t m11C = -1;
			constexpr std::int16_t m21C = 7;
			constexpr std::int16_t m31C = 17;
			constexpr std::int16_t m02C = -5;
			constexpr std::int16_t m12C = 6;
			constexpr std::int16_t m22C = -7;
			constexpr std::int16_t m32C = -17;
			constexpr std::int16_t m03C = 5;
			constexpr std::int16_t m13C = -6;
			constexpr std::int16_t m23C = 7;
			constexpr std::int16_t m33C = 17;
			auto matrixC = PonyMath::Core::Matrix4x4<std::int16_t>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyMath::Core::Matrix4x4<std::int16_t>& matrixL = matrixC *= multiplierI;
			Assert::AreEqual(static_cast<std::int16_t>(m00C * multiplierI), matrixC.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10C * multiplierI), matrixC.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20C * multiplierI), matrixC.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30C * multiplierI), matrixC.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01C * multiplierI), matrixC.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11C * multiplierI), matrixC.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21C * multiplierI), matrixC.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31C * multiplierI), matrixC.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02C * multiplierI), matrixC.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12C * multiplierI), matrixC.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22C * multiplierI), matrixC.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32C * multiplierI), matrixC.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03C * multiplierI), matrixC.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13C * multiplierI), matrixC.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23C * multiplierI), matrixC.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33C * multiplierI), matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));

			constexpr float multiplierF = 5.f;
			matrixC = PonyMath::Core::Matrix4x4<std::int16_t>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyMath::Core::Matrix4x4<std::int16_t>& matrixL1 = matrixC *= multiplierF;
			Assert::AreEqual(static_cast<std::int16_t>(m00C * multiplierF), matrixC.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10C * multiplierF), matrixC.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20C * multiplierF), matrixC.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30C * multiplierF), matrixC.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01C * multiplierF), matrixC.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11C * multiplierF), matrixC.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21C * multiplierF), matrixC.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31C * multiplierF), matrixC.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02C * multiplierF), matrixC.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12C * multiplierF), matrixC.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22C * multiplierF), matrixC.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32C * multiplierF), matrixC.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03C * multiplierF), matrixC.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13C * multiplierF), matrixC.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23C * multiplierF), matrixC.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33C * multiplierF), matrixC.M33());
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
			auto matrixC = PonyMath::Core::Matrix4x4<float>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyMath::Core::Matrix4x4<float>& matrixL = matrixC *= multiplier;
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
			constexpr std::int16_t m00 = 11;
			constexpr std::int16_t m10 = 15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 5;
			constexpr std::int16_t m01 = 55;
			constexpr std::int16_t m11 = 2;
			constexpr std::int16_t m21 = 30;
			constexpr std::int16_t m31 = 1;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 9;
			constexpr std::int16_t m32 = 21;
			constexpr std::int16_t m03 = -13;
			constexpr std::int16_t m13 = 10;
			constexpr std::int16_t m23 = 11;
			constexpr std::int16_t m33 = -6;
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			constexpr std::int16_t m00C = 3;
			constexpr std::int16_t m10C = -2;
			constexpr std::int16_t m20C = 5;
			constexpr std::int16_t m30C = 15;
			constexpr std::int16_t m01C = 4;
			constexpr std::int16_t m11C = -1;
			constexpr std::int16_t m21C = 7;
			constexpr std::int16_t m31C = 17;
			constexpr std::int16_t m02C = -5;
			constexpr std::int16_t m12C = 6;
			constexpr std::int16_t m22C = -7;
			constexpr std::int16_t m32C = -17;
			constexpr std::int16_t m03C = 5;
			constexpr std::int16_t m13C = -6;
			constexpr std::int16_t m23C = 7;
			constexpr std::int16_t m33C = 17;
			auto matrixC = PonyMath::Core::Matrix4x4<std::int16_t>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyMath::Core::Matrix4x4<std::int16_t>& matrixL = matrixC *= matrixR;
			Assert::AreEqual(std::int16_t{103}, matrixC.M00());
			Assert::AreEqual(std::int16_t{-49}, matrixC.M10());
			Assert::AreEqual(std::int16_t{174}, matrixC.M20());
			Assert::AreEqual(std::int16_t{454}, matrixC.M30());
			Assert::AreEqual(std::int16_t{28}, matrixC.M01());
			Assert::AreEqual(std::int16_t{62}, matrixC.M11());
			Assert::AreEqual(std::int16_t{86}, matrixC.M21());
			Assert::AreEqual(std::int16_t{366}, matrixC.M31());
			Assert::AreEqual(std::int16_t{106}, matrixC.M02());
			Assert::AreEqual(std::int16_t{-91}, matrixC.M12());
			Assert::AreEqual(std::int16_t{163}, matrixC.M22());
			Assert::AreEqual(std::int16_t{413}, matrixC.M32());
			Assert::AreEqual(std::int16_t{-84}, matrixC.M03());
			Assert::AreEqual(std::int16_t{118}, matrixC.M13());
			Assert::AreEqual(std::int16_t{-114}, matrixC.M23());
			Assert::AreEqual(std::int16_t{-314}, matrixC.M33());
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
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
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
			auto matrixC = PonyMath::Core::Matrix4x4<float>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyMath::Core::Matrix4x4<float>& matrixL = matrixC *= matrixR;
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
			constexpr std::int16_t multiplierI = 3;
			constexpr std::int16_t m00C = 3;
			constexpr std::int16_t m10C = -2;
			constexpr std::int16_t m20C = 5;
			constexpr std::int16_t m30C = 15;
			constexpr std::int16_t m01C = 4;
			constexpr std::int16_t m11C = -1;
			constexpr std::int16_t m21C = 7;
			constexpr std::int16_t m31C = 17;
			constexpr std::int16_t m02C = -5;
			constexpr std::int16_t m12C = 6;
			constexpr std::int16_t m22C = -7;
			constexpr std::int16_t m32C = -17;
			constexpr std::int16_t m03C = 5;
			constexpr std::int16_t m13C = -6;
			constexpr std::int16_t m23C = 7;
			constexpr std::int16_t m33C = 17;
			auto matrixC = PonyMath::Core::Matrix4x4<std::int16_t>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyMath::Core::Matrix4x4<std::int16_t>& matrixL = matrixC /= multiplierI;
			Assert::AreEqual(static_cast<std::int16_t>(m00C / multiplierI), matrixC.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10C / multiplierI), matrixC.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20C / multiplierI), matrixC.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30C / multiplierI), matrixC.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01C / multiplierI), matrixC.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11C / multiplierI), matrixC.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21C / multiplierI), matrixC.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31C / multiplierI), matrixC.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02C / multiplierI), matrixC.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12C / multiplierI), matrixC.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22C / multiplierI), matrixC.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32C / multiplierI), matrixC.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03C / multiplierI), matrixC.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13C / multiplierI), matrixC.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23C / multiplierI), matrixC.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33C / multiplierI), matrixC.M33());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));

			constexpr float multiplierF = 5.f;
			matrixC = PonyMath::Core::Matrix4x4<std::int16_t>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyMath::Core::Matrix4x4<std::int16_t>& matrixL1 = matrixC /= multiplierF;
			Assert::AreEqual(static_cast<std::int16_t>(m00C / multiplierF), matrixC.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10C / multiplierF), matrixC.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20C / multiplierF), matrixC.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30C / multiplierF), matrixC.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01C / multiplierF), matrixC.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11C / multiplierF), matrixC.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21C / multiplierF), matrixC.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31C / multiplierF), matrixC.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02C / multiplierF), matrixC.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12C / multiplierF), matrixC.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22C / multiplierF), matrixC.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32C / multiplierF), matrixC.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03C / multiplierF), matrixC.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13C / multiplierF), matrixC.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23C / multiplierF), matrixC.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33C / multiplierF), matrixC.M33());
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
			auto matrixC = PonyMath::Core::Matrix4x4<float>(m00C, m10C, m20C, m30C, m01C, m11C, m21C, m31C, m02C, m12C, m22C, m32C, m03C, m13C, m23C, m33C);
			PonyMath::Core::Matrix4x4<float>& matrixL = matrixC /= multiplier;
			Assert::AreEqual(m00C / multiplier, matrixC.M00(), 0.0001f);
			Assert::AreEqual(m10C / multiplier, matrixC.M10(), 0.0001f);
			Assert::AreEqual(m20C / multiplier, matrixC.M20(), 0.0001f);
			Assert::AreEqual(m30C / multiplier, matrixC.M30(), 0.0001f);
			Assert::AreEqual(m01C / multiplier, matrixC.M01(), 0.0001f);
			Assert::AreEqual(m11C / multiplier, matrixC.M11(), 0.0001f);
			Assert::AreEqual(m21C / multiplier, matrixC.M21(), 0.0001f);
			Assert::AreEqual(m31C / multiplier, matrixC.M31(), 0.0001f);
			Assert::AreEqual(m02C / multiplier, matrixC.M02(), 0.0001f);
			Assert::AreEqual(m12C / multiplier, matrixC.M12(), 0.0001f);
			Assert::AreEqual(m22C / multiplier, matrixC.M22(), 0.0001f);
			Assert::AreEqual(m32C / multiplier, matrixC.M32(), 0.0001f);
			Assert::AreEqual(m03C / multiplier, matrixC.M03(), 0.0001f);
			Assert::AreEqual(m13C / multiplier, matrixC.M13(), 0.0001f);
			Assert::AreEqual(m23C / multiplier, matrixC.M23(), 0.0001f);
			Assert::AreEqual(m33C / multiplier, matrixC.M33(), 0.0001f);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(EqualityOperatorShortTest)
		{
			constexpr std::int16_t m00 = 11;
			constexpr std::int16_t m10 = 15;
			constexpr std::int16_t m20 = 3;
			constexpr std::int16_t m30 = 5;
			constexpr std::int16_t m01 = 55;
			constexpr std::int16_t m11 = 2;
			constexpr std::int16_t m21 = 30;
			constexpr std::int16_t m31 = 1;
			constexpr std::int16_t m02 = 6;
			constexpr std::int16_t m12 = 7;
			constexpr std::int16_t m22 = 9;
			constexpr std::int16_t m32 = 21;
			constexpr std::int16_t m03 = -13;
			constexpr std::int16_t m13 = 10;
			constexpr std::int16_t m23 = 11;
			constexpr std::int16_t m33 = -6;
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<std::int16_t>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyMath::Core::Matrix4x4<std::int16_t> matrixL = matrixR;

			Assert::IsTrue(matrixL == matrixR);
			Assert::IsFalse(matrixL != matrixR);

			for (std::size_t i = 0; i < PonyMath::Core::Matrix4x4<std::int16_t>::ComponentCount; ++i)
			{
				matrixL.Span()[i] += 1;
				Assert::IsFalse(matrixL == matrixR);
				Assert::IsTrue(matrixL != matrixR);
				matrixL.Span()[i] = matrixR.Span()[i];
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
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyMath::Core::Matrix4x4<float> matrixL = matrixR;

			Assert::IsTrue(matrixL == matrixR);
			Assert::IsFalse(matrixL != matrixR);

			for (std::size_t i = 0; i < PonyMath::Core::Matrix4x4<float>::ComponentCount; ++i)
			{
				matrixL.Span()[i] = std::nextafter(matrixL.Span()[i], 0.f);
				Assert::IsFalse(matrixL == matrixR);
				Assert::IsTrue(matrixL != matrixR);
				matrixL.Span()[i] += 1;
				Assert::IsFalse(matrixL == matrixR);
				Assert::IsTrue(matrixL != matrixR);
				matrixL.Span()[i] = matrixR.Span()[i];
			}
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Identity == PonyMath::Core::Matrix4x4<float>(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f));
			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Zero == PonyMath::Core::Matrix4x4<float>(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f));

			Assert::IsTrue(PonyMath::Core::Matrix4x4<std::int16_t>::Predefined::Identity == PonyMath::Core::Matrix4x4<std::int16_t>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
			Assert::IsTrue(PonyMath::Core::Matrix4x4<std::int16_t>::Predefined::Zero == PonyMath::Core::Matrix4x4<std::int16_t>(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
		}

		TEST_METHOD(MultiplyShortTest)
		{
			constexpr std::int16_t m00R = 11;
			constexpr std::int16_t m10R = 15;
			constexpr std::int16_t m20R = 3;
			constexpr std::int16_t m30R = 5;
			constexpr std::int16_t m01R = 55;
			constexpr std::int16_t m11R = 2;
			constexpr std::int16_t m21R = 30;
			constexpr std::int16_t m31R = 1;
			constexpr std::int16_t m02R = 6;
			constexpr std::int16_t m12R = 7;
			constexpr std::int16_t m22R = 9;
			constexpr std::int16_t m32R = 21;
			constexpr std::int16_t m03R = -13;
			constexpr std::int16_t m13R = 10;
			constexpr std::int16_t m23R = 11;
			constexpr std::int16_t m33R = -6;
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<std::int16_t>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr std::int16_t m00L = 3;
			constexpr std::int16_t m10L = -2;
			constexpr std::int16_t m20L = 5;
			constexpr std::int16_t m30L = 15;
			constexpr std::int16_t m01L = 4;
			constexpr std::int16_t m11L = -1;
			constexpr std::int16_t m21L = 7;
			constexpr std::int16_t m31L = 17;
			constexpr std::int16_t m02L = -5;
			constexpr std::int16_t m12L = 6;
			constexpr std::int16_t m22L = -7;
			constexpr std::int16_t m32L = -17;
			constexpr std::int16_t m03L = 5;
			constexpr std::int16_t m13L = -6;
			constexpr std::int16_t m23L = 7;
			constexpr std::int16_t m33L = 17;
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<std::int16_t>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			const PonyMath::Core::Matrix4x4<std::int16_t> scaled = PonyMath::Core::Multiply(matrixL, matrixR);
			Assert::AreEqual(static_cast<std::int16_t>(m00L * m00R), scaled.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10L * m10R), scaled.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20L * m20R), scaled.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30L * m30R), scaled.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01L * m01R), scaled.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11L * m11R), scaled.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21L * m21R), scaled.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31L * m31R), scaled.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02L * m02R), scaled.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12L * m12R), scaled.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22L * m22R), scaled.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32L * m32R), scaled.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03L * m03R), scaled.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13L * m13R), scaled.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23L * m23R), scaled.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33L * m33R), scaled.M33());
		}

		TEST_METHOD(MultiplyFloatTest)
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
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<float>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
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
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			const PonyMath::Core::Matrix4x4<float> scaled = PonyMath::Core::Multiply(matrixL, matrixR);
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

		TEST_METHOD(DivideMatrixShortTest)
		{
			constexpr std::int16_t m00R = 11;
			constexpr std::int16_t m10R = 15;
			constexpr std::int16_t m20R = 3;
			constexpr std::int16_t m30R = 5;
			constexpr std::int16_t m01R = 55;
			constexpr std::int16_t m11R = 2;
			constexpr std::int16_t m21R = 30;
			constexpr std::int16_t m31R = 1;
			constexpr std::int16_t m02R = 6;
			constexpr std::int16_t m12R = 7;
			constexpr std::int16_t m22R = 9;
			constexpr std::int16_t m32R = 21;
			constexpr std::int16_t m03R = -13;
			constexpr std::int16_t m13R = 10;
			constexpr std::int16_t m23R = 11;
			constexpr std::int16_t m33R = -6;
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<std::int16_t>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr std::int16_t m00L = 3;
			constexpr std::int16_t m10L = -2;
			constexpr std::int16_t m20L = 5;
			constexpr std::int16_t m30L = 15;
			constexpr std::int16_t m01L = 4;
			constexpr std::int16_t m11L = -1;
			constexpr std::int16_t m21L = 7;
			constexpr std::int16_t m31L = 17;
			constexpr std::int16_t m02L = -5;
			constexpr std::int16_t m12L = 6;
			constexpr std::int16_t m22L = -7;
			constexpr std::int16_t m32L = -17;
			constexpr std::int16_t m03L = 5;
			constexpr std::int16_t m13L = -6;
			constexpr std::int16_t m23L = 7;
			constexpr std::int16_t m33L = 17;
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<std::int16_t>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			const PonyMath::Core::Matrix4x4<std::int16_t> scaled = PonyMath::Core::Divide(matrixL, matrixR);
			Assert::AreEqual(static_cast<std::int16_t>(m00L / m00R), scaled.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10L / m10R), scaled.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20L / m20R), scaled.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30L / m30R), scaled.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01L / m01R), scaled.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11L / m11R), scaled.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21L / m21R), scaled.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31L / m31R), scaled.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02L / m02R), scaled.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12L / m12R), scaled.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22L / m22R), scaled.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32L / m32R), scaled.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03L / m03R), scaled.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13L / m13R), scaled.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23L / m23R), scaled.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33L / m33R), scaled.M33());
		}

		TEST_METHOD(DivideMatrixFloatTest)
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
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<float>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
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
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			const PonyMath::Core::Matrix4x4<float> scaled = PonyMath::Core::Divide(matrixL, matrixR);
			Assert::AreEqual(m00L / m00R, scaled.M00(), 0.0001f);
			Assert::AreEqual(m10L / m10R, scaled.M10(), 0.0001f);
			Assert::AreEqual(m20L / m20R, scaled.M20(), 0.0001f);
			Assert::AreEqual(m30L / m30R, scaled.M30(), 0.0001f);
			Assert::AreEqual(m01L / m01R, scaled.M01(), 0.0001f);
			Assert::AreEqual(m11L / m11R, scaled.M11(), 0.0001f);
			Assert::AreEqual(m21L / m21R, scaled.M21(), 0.0001f);
			Assert::AreEqual(m31L / m31R, scaled.M31(), 0.0001f);
			Assert::AreEqual(m02L / m02R, scaled.M02(), 0.0001f);
			Assert::AreEqual(m12L / m12R, scaled.M12(), 0.0001f);
			Assert::AreEqual(m22L / m22R, scaled.M22(), 0.0001f);
			Assert::AreEqual(m32L / m32R, scaled.M32(), 0.0001f);
			Assert::AreEqual(m03L / m03R, scaled.M03(), 0.0001f);
			Assert::AreEqual(m13L / m13R, scaled.M13(), 0.0001f);
			Assert::AreEqual(m23L / m23R, scaled.M23(), 0.0001f);
			Assert::AreEqual(m33L / m33R, scaled.M33(), 0.0001f);
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
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<float>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			PonyMath::Core::Matrix4x4<float> matrixL = matrixR;
			for (std::size_t i = 0; i < PonyMath::Core::Matrix4x4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(PonyMath::Core::AreAlmostEqual(matrixL, matrixR));
				matrixL.Span()[i] = std::nextafter(matrixL.Span()[i], 0.f);
				Assert::IsTrue(PonyMath::Core::AreAlmostEqual(matrixL, matrixR));
				matrixL.Span()[i] += 1;
				Assert::IsFalse(PonyMath::Core::AreAlmostEqual(matrixL, matrixR));
				Assert::IsTrue(PonyMath::Core::AreAlmostEqual(matrixL, matrixR, 5.f));
				matrixL.Span()[i] = matrixR.Span()[i];
			}
		}

		TEST_METHOD(AddShortTest)
		{
			constexpr std::int16_t m00R = 11;
			constexpr std::int16_t m10R = 15;
			constexpr std::int16_t m20R = 3;
			constexpr std::int16_t m30R = 5;
			constexpr std::int16_t m01R = 55;
			constexpr std::int16_t m11R = 2;
			constexpr std::int16_t m21R = 30;
			constexpr std::int16_t m31R = 1;
			constexpr std::int16_t m02R = 6;
			constexpr std::int16_t m12R = 7;
			constexpr std::int16_t m22R = 9;
			constexpr std::int16_t m32R = 21;
			constexpr std::int16_t m03R = -13;
			constexpr std::int16_t m13R = 10;
			constexpr std::int16_t m23R = 11;
			constexpr std::int16_t m33R = -6;
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<std::int16_t>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr std::int16_t m00L = 3;
			constexpr std::int16_t m10L = -2;
			constexpr std::int16_t m20L = 5;
			constexpr std::int16_t m30L = 15;
			constexpr std::int16_t m01L = 4;
			constexpr std::int16_t m11L = -1;
			constexpr std::int16_t m21L = 7;
			constexpr std::int16_t m31L = 17;
			constexpr std::int16_t m02L = -5;
			constexpr std::int16_t m12L = 6;
			constexpr std::int16_t m22L = -7;
			constexpr std::int16_t m32L = -17;
			constexpr std::int16_t m03L = 5;
			constexpr std::int16_t m13L = -6;
			constexpr std::int16_t m23L = 7;
			constexpr std::int16_t m33L = 17;
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<std::int16_t>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyMath::Core::Matrix4x4<std::int16_t> sum = matrixL + matrixR;
			Assert::AreEqual(static_cast<std::int16_t>(m00L + m00R), sum.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10L + m10R), sum.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20L + m20R), sum.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30L + m30R), sum.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01L + m01R), sum.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11L + m11R), sum.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21L + m21R), sum.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31L + m31R), sum.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02L + m02R), sum.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12L + m12R), sum.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22L + m22R), sum.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32L + m32R), sum.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03L + m03R), sum.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13L + m13R), sum.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23L + m23R), sum.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33L + m33R), sum.M33());
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
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<float>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
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
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyMath::Core::Matrix4x4<float> sum = matrixL + matrixR;
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
			constexpr std::int16_t m00R = 11;
			constexpr std::int16_t m10R = 15;
			constexpr std::int16_t m20R = 3;
			constexpr std::int16_t m30R = 5;
			constexpr std::int16_t m01R = 55;
			constexpr std::int16_t m11R = 2;
			constexpr std::int16_t m21R = 30;
			constexpr std::int16_t m31R = 1;
			constexpr std::int16_t m02R = 6;
			constexpr std::int16_t m12R = 7;
			constexpr std::int16_t m22R = 9;
			constexpr std::int16_t m32R = 21;
			constexpr std::int16_t m03R = -13;
			constexpr std::int16_t m13R = 10;
			constexpr std::int16_t m23R = 11;
			constexpr std::int16_t m33R = -6;
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<std::int16_t>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			PonyMath::Core::Matrix4x4<std::int16_t> negated = -matrixR;
			Assert::AreEqual(static_cast<std::int16_t>(-m00R), negated.M00());
			Assert::AreEqual(static_cast<std::int16_t>(-m10R), negated.M10());
			Assert::AreEqual(static_cast<std::int16_t>(-m20R), negated.M20());
			Assert::AreEqual(static_cast<std::int16_t>(-m30R), negated.M30());
			Assert::AreEqual(static_cast<std::int16_t>(-m01R), negated.M01());
			Assert::AreEqual(static_cast<std::int16_t>(-m11R), negated.M11());
			Assert::AreEqual(static_cast<std::int16_t>(-m21R), negated.M21());
			Assert::AreEqual(static_cast<std::int16_t>(-m31R), negated.M31());
			Assert::AreEqual(static_cast<std::int16_t>(-m02R), negated.M02());
			Assert::AreEqual(static_cast<std::int16_t>(-m12R), negated.M12());
			Assert::AreEqual(static_cast<std::int16_t>(-m22R), negated.M22());
			Assert::AreEqual(static_cast<std::int16_t>(-m32R), negated.M32());
			Assert::AreEqual(static_cast<std::int16_t>(-m03R), negated.M03());
			Assert::AreEqual(static_cast<std::int16_t>(-m13R), negated.M13());
			Assert::AreEqual(static_cast<std::int16_t>(-m23R), negated.M23());
			Assert::AreEqual(static_cast<std::int16_t>(-m33R), negated.M33());
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
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<float>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			PonyMath::Core::Matrix4x4<float> negated = -matrixR;
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
			constexpr std::int16_t m00R = 11;
			constexpr std::int16_t m10R = 15;
			constexpr std::int16_t m20R = 3;
			constexpr std::int16_t m30R = 5;
			constexpr std::int16_t m01R = 55;
			constexpr std::int16_t m11R = 2;
			constexpr std::int16_t m21R = 30;
			constexpr std::int16_t m31R = 1;
			constexpr std::int16_t m02R = 6;
			constexpr std::int16_t m12R = 7;
			constexpr std::int16_t m22R = 9;
			constexpr std::int16_t m32R = 21;
			constexpr std::int16_t m03R = -13;
			constexpr std::int16_t m13R = 10;
			constexpr std::int16_t m23R = 11;
			constexpr std::int16_t m33R = -6;
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<std::int16_t>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr std::int16_t m00L = 3;
			constexpr std::int16_t m10L = -2;
			constexpr std::int16_t m20L = 5;
			constexpr std::int16_t m30L = 15;
			constexpr std::int16_t m01L = 4;
			constexpr std::int16_t m11L = -1;
			constexpr std::int16_t m21L = 7;
			constexpr std::int16_t m31L = 17;
			constexpr std::int16_t m02L = -5;
			constexpr std::int16_t m12L = 6;
			constexpr std::int16_t m22L = -7;
			constexpr std::int16_t m32L = -17;
			constexpr std::int16_t m03L = 5;
			constexpr std::int16_t m13L = -6;
			constexpr std::int16_t m23L = 7;
			constexpr std::int16_t m33L = 17;
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<std::int16_t>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyMath::Core::Matrix4x4<std::int16_t> sum = matrixL - matrixR;
			Assert::AreEqual(static_cast<std::int16_t>(m00L - m00R), sum.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10L - m10R), sum.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20L - m20R), sum.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30L - m30R), sum.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01L - m01R), sum.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11L - m11R), sum.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21L - m21R), sum.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31L - m31R), sum.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02L - m02R), sum.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12L - m12R), sum.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22L - m22R), sum.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32L - m32R), sum.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03L - m03R), sum.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13L - m13R), sum.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23L - m23R), sum.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33L - m33R), sum.M33());
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
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<float>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
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
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyMath::Core::Matrix4x4<float> sum = matrixL - matrixR;
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
			constexpr std::int16_t multiplierI = 2;
			constexpr std::int16_t m00L = 3;
			constexpr std::int16_t m10L = -2;
			constexpr std::int16_t m20L = 5;
			constexpr std::int16_t m30L = 15;
			constexpr std::int16_t m01L = 4;
			constexpr std::int16_t m11L = -1;
			constexpr std::int16_t m21L = 7;
			constexpr std::int16_t m31L = 17;
			constexpr std::int16_t m02L = -5;
			constexpr std::int16_t m12L = 6;
			constexpr std::int16_t m22L = -7;
			constexpr std::int16_t m32L = -17;
			constexpr std::int16_t m03L = 5;
			constexpr std::int16_t m13L = -6;
			constexpr std::int16_t m23L = 7;
			constexpr std::int16_t m33L = 17;
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<std::int16_t>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyMath::Core::Matrix4x4<std::int16_t> product = matrixL * multiplierI;
			Assert::AreEqual(static_cast<std::int16_t>(m00L * multiplierI), product.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10L * multiplierI), product.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20L * multiplierI), product.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30L * multiplierI), product.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01L * multiplierI), product.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11L * multiplierI), product.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21L * multiplierI), product.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31L * multiplierI), product.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02L * multiplierI), product.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12L * multiplierI), product.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22L * multiplierI), product.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32L * multiplierI), product.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03L * multiplierI), product.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13L * multiplierI), product.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23L * multiplierI), product.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33L * multiplierI), product.M33());
			Assert::IsTrue(multiplierI * matrixL == matrixL * multiplierI);

			constexpr float multiplierF = 3;
			product = matrixL * multiplierF;
			Assert::AreEqual(static_cast<std::int16_t>(m00L * multiplierF), product.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10L * multiplierF), product.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20L * multiplierF), product.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30L * multiplierF), product.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01L * multiplierF), product.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11L * multiplierF), product.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21L * multiplierF), product.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31L * multiplierF), product.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02L * multiplierF), product.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12L * multiplierF), product.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22L * multiplierF), product.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32L * multiplierF), product.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03L * multiplierF), product.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13L * multiplierF), product.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23L * multiplierF), product.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33L * multiplierF), product.M33());
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
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyMath::Core::Matrix4x4<float> product = matrixL * multiplier;
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
			constexpr std::int16_t m00R = 11;
			constexpr std::int16_t m10R = 15;
			constexpr std::int16_t m20R = 3;
			constexpr std::int16_t m30R = 5;
			constexpr std::int16_t m01R = 55;
			constexpr std::int16_t m11R = 2;
			constexpr std::int16_t m21R = 30;
			constexpr std::int16_t m31R = 1;
			constexpr std::int16_t m02R = 6;
			constexpr std::int16_t m12R = 7;
			constexpr std::int16_t m22R = 9;
			constexpr std::int16_t m32R = 21;
			constexpr std::int16_t m03R = -13;
			constexpr std::int16_t m13R = 10;
			constexpr std::int16_t m23R = 11;
			constexpr std::int16_t m33R = -6;
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<std::int16_t>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
			constexpr std::int16_t m00L = 3;
			constexpr std::int16_t m10L = -2;
			constexpr std::int16_t m20L = 5;
			constexpr std::int16_t m30L = 15;
			constexpr std::int16_t m01L = 4;
			constexpr std::int16_t m11L = -1;
			constexpr std::int16_t m21L = 7;
			constexpr std::int16_t m31L = 17;
			constexpr std::int16_t m02L = -5;
			constexpr std::int16_t m12L = 6;
			constexpr std::int16_t m22L = -7;
			constexpr std::int16_t m32L = -17;
			constexpr std::int16_t m03L = 5;
			constexpr std::int16_t m13L = -6;
			constexpr std::int16_t m23L = 7;
			constexpr std::int16_t m33L = 17;
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<std::int16_t>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyMath::Core::Matrix4x4<std::int16_t> product = matrixL * matrixR;
			Assert::AreEqual(std::int16_t{103}, product.M00());
			Assert::AreEqual(std::int16_t{-49}, product.M10());
			Assert::AreEqual(std::int16_t{174}, product.M20());
			Assert::AreEqual(std::int16_t{454}, product.M30());
			Assert::AreEqual(std::int16_t{28}, product.M01());
			Assert::AreEqual(std::int16_t{62}, product.M11());
			Assert::AreEqual(std::int16_t{86}, product.M21());
			Assert::AreEqual(std::int16_t{366}, product.M31());
			Assert::AreEqual(std::int16_t{106}, product.M02());
			Assert::AreEqual(std::int16_t{-91}, product.M12());
			Assert::AreEqual(std::int16_t{163}, product.M22());
			Assert::AreEqual(std::int16_t{413}, product.M32());
			Assert::AreEqual(std::int16_t{-84}, product.M03());
			Assert::AreEqual(std::int16_t{118}, product.M13());
			Assert::AreEqual(std::int16_t{-114}, product.M23());
			Assert::AreEqual(std::int16_t{-314}, product.M33());
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
			constexpr auto matrixR = PonyMath::Core::Matrix4x4<float>(m00R, m10R, m20R, m30R, m01R, m11R, m21R, m31R, m02R, m12R, m22R, m32R, m03R, m13R, m23R, m33R);
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
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyMath::Core::Matrix4x4<float> product = matrixL * matrixR;
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
			constexpr std::int16_t m00R = 11;
			constexpr std::int16_t m10R = 15;
			constexpr std::int16_t m20R = 3;
			constexpr std::int16_t m30R = 5;
			constexpr auto vectorR = PonyMath::Core::Vector4<std::int16_t>(m00R, m10R, m20R, m30R);
			constexpr std::int16_t m00L = 3;
			constexpr std::int16_t m10L = -2;
			constexpr std::int16_t m20L = 5;
			constexpr std::int16_t m30L = 15;
			constexpr std::int16_t m01L = 4;
			constexpr std::int16_t m11L = -1;
			constexpr std::int16_t m21L = 7;
			constexpr std::int16_t m31L = 17;
			constexpr std::int16_t m02L = -5;
			constexpr std::int16_t m12L = 6;
			constexpr std::int16_t m22L = -7;
			constexpr std::int16_t m32L = -17;
			constexpr std::int16_t m03L = 5;
			constexpr std::int16_t m13L = -6;
			constexpr std::int16_t m23L = 7;
			constexpr std::int16_t m33L = 17;
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<std::int16_t>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyMath::Core::Vector4<std::int16_t> product = matrixL * vectorR;
			Assert::AreEqual(std::int16_t{103}, product.X());
			Assert::AreEqual(std::int16_t{-49}, product.Y());
			Assert::AreEqual(std::int16_t{174}, product.Z());
			Assert::AreEqual(std::int16_t{454}, product.W());
		}

		TEST_METHOD(MultiplyVectorFloatTest)
		{
			constexpr float m00R = 11;
			constexpr float m10R = 15;
			constexpr float m20R = 3;
			constexpr float m30R = 5;
			constexpr auto vectorR = PonyMath::Core::Vector4<float>(m00R, m10R, m20R, m30R);
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
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyMath::Core::Vector4<float> product = matrixL * vectorR;
			Assert::AreEqual(103.f, product.X());
			Assert::AreEqual(-49.f, product.Y());
			Assert::AreEqual(174.f, product.Z());
			Assert::AreEqual(454.f, product.W());
		}

		TEST_METHOD(DivideShortTest)
		{
			constexpr std::int16_t multiplierI = 2;
			constexpr std::int16_t m00L = 3;
			constexpr std::int16_t m10L = -2;
			constexpr std::int16_t m20L = 5;
			constexpr std::int16_t m30L = 15;
			constexpr std::int16_t m01L = 4;
			constexpr std::int16_t m11L = -1;
			constexpr std::int16_t m21L = 7;
			constexpr std::int16_t m31L = 17;
			constexpr std::int16_t m02L = -5;
			constexpr std::int16_t m12L = 6;
			constexpr std::int16_t m22L = -7;
			constexpr std::int16_t m32L = -17;
			constexpr std::int16_t m03L = 5;
			constexpr std::int16_t m13L = -6;
			constexpr std::int16_t m23L = 7;
			constexpr std::int16_t m33L = 17;
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<std::int16_t>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyMath::Core::Matrix4x4<std::int16_t> product = matrixL / multiplierI;
			Assert::AreEqual(static_cast<std::int16_t>(m00L / multiplierI), product.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10L / multiplierI), product.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20L / multiplierI), product.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30L / multiplierI), product.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01L / multiplierI), product.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11L / multiplierI), product.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21L / multiplierI), product.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31L / multiplierI), product.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02L / multiplierI), product.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12L / multiplierI), product.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22L / multiplierI), product.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32L / multiplierI), product.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03L / multiplierI), product.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13L / multiplierI), product.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23L / multiplierI), product.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33L / multiplierI), product.M33());
			Assert::IsTrue(multiplierI * matrixL == matrixL * multiplierI);

			constexpr float multiplierF = 3;
			product = matrixL / multiplierF;
			Assert::AreEqual(static_cast<std::int16_t>(m00L / multiplierF), product.M00());
			Assert::AreEqual(static_cast<std::int16_t>(m10L / multiplierF), product.M10());
			Assert::AreEqual(static_cast<std::int16_t>(m20L / multiplierF), product.M20());
			Assert::AreEqual(static_cast<std::int16_t>(m30L / multiplierF), product.M30());
			Assert::AreEqual(static_cast<std::int16_t>(m01L / multiplierF), product.M01());
			Assert::AreEqual(static_cast<std::int16_t>(m11L / multiplierF), product.M11());
			Assert::AreEqual(static_cast<std::int16_t>(m21L / multiplierF), product.M21());
			Assert::AreEqual(static_cast<std::int16_t>(m31L / multiplierF), product.M31());
			Assert::AreEqual(static_cast<std::int16_t>(m02L / multiplierF), product.M02());
			Assert::AreEqual(static_cast<std::int16_t>(m12L / multiplierF), product.M12());
			Assert::AreEqual(static_cast<std::int16_t>(m22L / multiplierF), product.M22());
			Assert::AreEqual(static_cast<std::int16_t>(m32L / multiplierF), product.M32());
			Assert::AreEqual(static_cast<std::int16_t>(m03L / multiplierF), product.M03());
			Assert::AreEqual(static_cast<std::int16_t>(m13L / multiplierF), product.M13());
			Assert::AreEqual(static_cast<std::int16_t>(m23L / multiplierF), product.M23());
			Assert::AreEqual(static_cast<std::int16_t>(m33L / multiplierF), product.M33());
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
			constexpr auto matrixL = PonyMath::Core::Matrix4x4<float>(m00L, m10L, m20L, m30L, m01L, m11L, m21L, m31L, m02L, m12L, m22L, m32L, m03L, m13L, m23L, m33L);
			PonyMath::Core::Matrix4x4<float> product = matrixL / multiplier;
			Assert::AreEqual(m00L / multiplier, product.M00(), 0.0001f);
			Assert::AreEqual(m10L / multiplier, product.M10(), 0.0001f);
			Assert::AreEqual(m20L / multiplier, product.M20(), 0.0001f);
			Assert::AreEqual(m30L / multiplier, product.M30(), 0.0001f);
			Assert::AreEqual(m01L / multiplier, product.M01(), 0.0001f);
			Assert::AreEqual(m11L / multiplier, product.M11(), 0.0001f);
			Assert::AreEqual(m21L / multiplier, product.M21(), 0.0001f);
			Assert::AreEqual(m31L / multiplier, product.M31(), 0.0001f);
			Assert::AreEqual(m02L / multiplier, product.M02(), 0.0001f);
			Assert::AreEqual(m12L / multiplier, product.M12(), 0.0001f);
			Assert::AreEqual(m22L / multiplier, product.M22(), 0.0001f);
			Assert::AreEqual(m32L / multiplier, product.M32(), 0.0001f);
			Assert::AreEqual(m03L / multiplier, product.M03(), 0.0001f);
			Assert::AreEqual(m13L / multiplier, product.M13(), 0.0001f);
			Assert::AreEqual(m23L / multiplier, product.M23(), 0.0001f);
			Assert::AreEqual(m33L / multiplier, product.M33(), 0.0001f);
			Assert::IsTrue(multiplier * matrixL == matrixL * multiplier);
		}

		static constexpr PonyMath::Core::Matrix4x4<std::int32_t> MatrixConstexpr()
		{
			[[maybe_unused]] auto matrix = PonyMath::Core::Matrix4x4<std::int32_t>();
			PonyMath::Core::Matrix4x4<std::int32_t> movedMatrix = std::move(matrix);

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
			movedMatrix.Component(3) *= 1;
			movedMatrix.Span()[0] -= 3;
			movedMatrix.Span(1)[0] /= 2;

			[[maybe_unused]] constexpr auto constMatrix = PonyMath::Core::Matrix4x4<std::int32_t>(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8);

			movedMatrix.Row(0, PonyMath::Core::Vector4<std::int32_t>(3, 6, 9, 5));
			movedMatrix.Column(1, PonyMath::Core::Vector4<std::int32_t>(3, 6, 9, 3));
			movedMatrix.Diagonal(PonyMath::Core::Vector4<std::int32_t>(3, 6, 9, 4));
			movedMatrix.CounterDiagonal(PonyMath::Core::Vector4<std::int32_t>(3, 6, 9, 3));

			movedMatrix.Multiply(constMatrix);
			movedMatrix.Divide(constMatrix);

			movedMatrix[1][1] = 5;
			movedMatrix[1] = PonyMath::Core::Vector4<std::int32_t>(9, 4, 8, 5);

			[[maybe_unused]] auto copyAssigned = PonyMath::Core::Matrix4x4<std::int32_t>();
			copyAssigned = movedMatrix;
			movedMatrix = std::move(copyAssigned);

			movedMatrix += constMatrix;
			movedMatrix -= constMatrix;
			movedMatrix *= 3;
			movedMatrix *= 3.f;
			movedMatrix *= constMatrix;
			movedMatrix /= 4;
			movedMatrix /= 5.f;

			return movedMatrix;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> identity = PonyMath::Core::Matrix4x4<std::int32_t>::Predefined::Identity;
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> zero = PonyMath::Core::Matrix4x4<std::int32_t>::Predefined::Zero;

			[[maybe_unused]] constexpr auto defaultMatrix = PonyMath::Core::Matrix4x4<std::int32_t>();
			[[maybe_unused]] constexpr auto matrix = PonyMath::Core::Matrix4x4<std::int32_t>(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8);
			[[maybe_unused]] constexpr auto columnMatrix = PonyMath::Core::Matrix4x4<std::int32_t>(PonyMath::Core::Vector4<std::int32_t>(3, 6, 9, 5), PonyMath::Core::Vector4<std::int32_t>(3, 6, 9, 5), PonyMath::Core::Vector4<std::int32_t>(3, 6, 9, 5), PonyMath::Core::Vector4<std::int32_t>(3, 6, 9, 5));
			[[maybe_unused]] constexpr auto columnSpanMatrix = PonyMath::Core::Matrix4x4<std::int32_t>(std::array{ PonyMath::Core::Vector4<std::int32_t>(3, 6, 9, 5), PonyMath::Core::Vector4<std::int32_t>(3, 6, 9, 5), PonyMath::Core::Vector4<std::int32_t>(3, 6, 9, 5), PonyMath::Core::Vector4<std::int32_t>(3, 6, 9, 5) });
			[[maybe_unused]] constexpr auto arrayMatrix = PonyMath::Core::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16>{4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8});
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> copiedMatrix = matrix;
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> movedMatrix = MatrixConstexpr();

			[[maybe_unused]] constexpr std::int32_t m00 = matrix.M00();
			[[maybe_unused]] constexpr std::int32_t m10 = matrix.M10();
			[[maybe_unused]] constexpr std::int32_t m20 = matrix.M20();
			[[maybe_unused]] constexpr std::int32_t m30 = matrix.M30();
			[[maybe_unused]] constexpr std::int32_t m01 = matrix.M01();
			[[maybe_unused]] constexpr std::int32_t m11 = matrix.M11();
			[[maybe_unused]] constexpr std::int32_t m21 = matrix.M21();
			[[maybe_unused]] constexpr std::int32_t m31 = matrix.M31();
			[[maybe_unused]] constexpr std::int32_t m02 = matrix.M02();
			[[maybe_unused]] constexpr std::int32_t m12 = matrix.M12();
			[[maybe_unused]] constexpr std::int32_t m22 = matrix.M22();
			[[maybe_unused]] constexpr std::int32_t m32 = matrix.M32();
			[[maybe_unused]] constexpr std::int32_t m03 = matrix.M03();
			[[maybe_unused]] constexpr std::int32_t m13 = matrix.M13();
			[[maybe_unused]] constexpr std::int32_t m23 = matrix.M23();
			[[maybe_unused]] constexpr std::int32_t m33 = matrix.M33();

			[[maybe_unused]] constexpr auto spanElement = matrix.Span()[0];
			[[maybe_unused]] constexpr auto columnSpanElement = matrix.Span(1)[0];

			[[maybe_unused]] constexpr PonyMath::Core::Vector4<std::int32_t> row = matrix.Row(1);
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<std::int32_t> column = matrix.Column(0);
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<std::int32_t> diagonal = matrix.Diagonal();
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<std::int32_t> counterDiagonal = matrix.CounterDiagonal();

			[[maybe_unused]] constexpr std::int32_t trace = matrix.Trace();
			[[maybe_unused]] constexpr std::int32_t determinant = matrix.Determinant();
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> adjugate = matrix.Adjugate();
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> transpose = matrix.Transpose();
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<float> inverse = PonyMath::Core::Matrix4x4<float>(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8).Inverse();

			[[maybe_unused]] constexpr bool isZero = matrix.IsZero();
			[[maybe_unused]] constexpr bool isAlmostZero = PonyMath::Core::Matrix4x4<float>::Predefined::Zero.IsAlmostZero();
			[[maybe_unused]] constexpr bool isIdentity = matrix.IsIdentity();
			[[maybe_unused]] constexpr bool isAlmostIdentity = PonyMath::Core::Matrix4x4<float>::Predefined::Identity.IsAlmostIdentity();

			[[maybe_unused]] constexpr auto floatMatrix = static_cast<PonyMath::Core::Matrix4x4<float>>(matrix);

			[[maybe_unused]] constexpr std::int32_t m10A = matrix[1][0];
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<std::int32_t> columnV = matrix[0];

			[[maybe_unused]] constexpr bool equal = matrix == defaultMatrix;
			[[maybe_unused]] constexpr bool notEqual = matrix != defaultMatrix;

			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> scaled = PonyMath::Core::Multiply(matrix, columnMatrix);
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> scaledD = PonyMath::Core::Divide(matrix, columnMatrix);
			[[maybe_unused]] constexpr bool areAlmostEqual = PonyMath::Core::AreAlmostEqual(PonyMath::Core::Matrix4x4<float>(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8), PonyMath::Core::Matrix4x4<float>(4, 3, 9, 1, -8, -5, -4, 6, 7, 1, 5, -3, 6, 1, 6, 8));

			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> sum = matrix + columnMatrix;
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> negated = -matrix;
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> difference = matrix - columnMatrix;
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> productNumR = matrix * 3;
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> productNumL = 3 * matrix;
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> productNumFR = matrix * 3.f;
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> productNumFL = 3.f * matrix;
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> product = matrix * columnMatrix;
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<std::int32_t> productV = matrix * PonyMath::Core::Vector4<std::int32_t>(4, 6, 1, 5);
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> quotient = matrix / 3;
			[[maybe_unused]] constexpr PonyMath::Core::Matrix4x4<std::int32_t> quotientF = matrix / 3.f;
		}
	};
}
