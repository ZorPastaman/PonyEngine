/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <format>
#include <ostream>
#include <string>

import PonyBase.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(Matrix3x3Tests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyBase::Math::Matrix3x3<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::Matrix3x3<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyBase::Math::Matrix3x3<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::Matrix3x3<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyBase::Math::Matrix3x3<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::Matrix3x3<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::Matrix3x3<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::Matrix3x3<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyBase::Math::Matrix3x3<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyBase::Math::Matrix3x3<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyBase::Math::Matrix3x3<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyBase::Math::Matrix3x3<double>::ComputationalType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{3}, PonyBase::Math::Matrix3x3<float>::Dimension);
			Assert::AreEqual(std::size_t{9}, PonyBase::Math::Matrix3x3<float>::ComponentCount);

			Assert::AreEqual(std::size_t{3}, PonyBase::Math::Matrix3x3<short>::Dimension);
			Assert::AreEqual(std::size_t{9}, PonyBase::Math::Matrix3x3<short>::ComponentCount);
		}

		TEST_METHOD(RowToVector3ShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);

			const PonyBase::Math::Vector3<short> row0 = matrix[0];
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());
			Assert::AreEqual(m02, row0.Z());

			const PonyBase::Math::Vector3<short> row1 = matrix[1];
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
			Assert::AreEqual(m12, row1.Z());

			const PonyBase::Math::Vector3<short> row2 = matrix[2];
			Assert::AreEqual(m20, row2.X());
			Assert::AreEqual(m21, row2.Y());
			Assert::AreEqual(m22, row2.Z());
		}

		TEST_METHOD(RowToVector3FloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);

			const PonyBase::Math::Vector3<float> row0 = matrix[0];
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());
			Assert::AreEqual(m02, row0.Z());

			const PonyBase::Math::Vector3<float> row1 = matrix[1];
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
			Assert::AreEqual(m12, row1.Z());

			const PonyBase::Math::Vector3<float> row2 = matrix[2];
			Assert::AreEqual(m20, row2.X());
			Assert::AreEqual(m21, row2.Y());
			Assert::AreEqual(m22, row2.Z());
		}

		TEST_METHOD(CastTest)
		{
			constexpr auto floatMatrix = PonyBase::Math::Matrix3x3<float>(3.1f, -2.2f, 4.4f, -5.9f, 4.8f, 7.1f, 12.f, 11.5f, -13.4f);
			const auto intMatrix = static_cast<PonyBase::Math::Matrix3x3<int>>(floatMatrix);
			Assert::AreEqual(3, intMatrix.M00());
			Assert::AreEqual(-2, intMatrix.M10());
			Assert::AreEqual(4, intMatrix.M20());
			Assert::AreEqual(-5, intMatrix.M01());
			Assert::AreEqual(4, intMatrix.M11());
			Assert::AreEqual(7, intMatrix.M21());
			Assert::AreEqual(12, intMatrix.M02());
			Assert::AreEqual(11, intMatrix.M12());
			Assert::AreEqual(-13, intMatrix.M22());
		}

		TEST_METHOD(AccessOperatorReadShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);

			Assert::AreEqual(m00, matrix[0][0]);
			Assert::AreEqual(m01, matrix[0][1]);
			Assert::AreEqual(m02, matrix[0][2]);
			Assert::AreEqual(m10, matrix[1][0]);
			Assert::AreEqual(m11, matrix[1][1]);
			Assert::AreEqual(m12, matrix[1][2]);
			Assert::AreEqual(m20, matrix[2][0]);
			Assert::AreEqual(m21, matrix[2][1]);
			Assert::AreEqual(m22, matrix[2][2]);
		}

		TEST_METHOD(AccessOperatorReadFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);

			Assert::AreEqual(m00, matrix[0][0]);
			Assert::AreEqual(m01, matrix[0][1]);
			Assert::AreEqual(m02, matrix[0][2]);
			Assert::AreEqual(m10, matrix[1][0]);
			Assert::AreEqual(m11, matrix[1][1]);
			Assert::AreEqual(m12, matrix[1][2]);
			Assert::AreEqual(m20, matrix[2][0]);
			Assert::AreEqual(m21, matrix[2][1]);
			Assert::AreEqual(m22, matrix[2][2]);
		}

		TEST_METHOD(AccessOperatorWriteShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);

			constexpr short m00New = 20;
			constexpr short m10New = 30;
			constexpr short m20New = 30;
			constexpr short m01New = -40;
			constexpr short m11New = -50;
			constexpr short m21New = 330;
			constexpr short m02New = 60;
			constexpr short m12New = 70;
			constexpr short m22New = 190;
			matrix[0][0] = m00New;
			matrix[0][1] = m01New;
			matrix[0][2] = m02New;
			matrix[1][0] = m10New;
			matrix[1][1] = m11New;
			matrix[1][2] = m12New;
			matrix[2][0] = m20New;
			matrix[2][1] = m21New;
			matrix[2][2] = m22New;

			Assert::AreEqual(m00New, matrix[0][0]);
			Assert::AreEqual(m01New, matrix[0][1]);
			Assert::AreEqual(m02New, matrix[0][2]);
			Assert::AreEqual(m10New, matrix[1][0]);
			Assert::AreEqual(m11New, matrix[1][1]);
			Assert::AreEqual(m12New, matrix[1][2]);
			Assert::AreEqual(m20New, matrix[2][0]);
			Assert::AreEqual(m21New, matrix[2][1]);
			Assert::AreEqual(m22New, matrix[2][2]);
		}

		TEST_METHOD(AccessOperatorWriteFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);

			constexpr float m00New = 20;
			constexpr float m10New = 30;
			constexpr float m20New = 30;
			constexpr float m01New = -40;
			constexpr float m11New = -50;
			constexpr float m21New = 330;
			constexpr float m02New = 60;
			constexpr float m12New = 70;
			constexpr float m22New = 190;
			matrix[0][0] = m00New;
			matrix[0][1] = m01New;
			matrix[0][2] = m02New;
			matrix[1][0] = m10New;
			matrix[1][1] = m11New;
			matrix[1][2] = m12New;
			matrix[2][0] = m20New;
			matrix[2][1] = m21New;
			matrix[2][2] = m22New;

			Assert::AreEqual(m00New, matrix[0][0]);
			Assert::AreEqual(m01New, matrix[0][1]);
			Assert::AreEqual(m02New, matrix[0][2]);
			Assert::AreEqual(m10New, matrix[1][0]);
			Assert::AreEqual(m11New, matrix[1][1]);
			Assert::AreEqual(m12New, matrix[1][2]);
			Assert::AreEqual(m20New, matrix[2][0]);
			Assert::AreEqual(m21New, matrix[2][1]);
			Assert::AreEqual(m22New, matrix[2][2]);
		}

		TEST_METHOD(Vector3ToRowShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);

			constexpr short m00New = 20;
			constexpr short m10New = 30;
			constexpr short m20New = 30;
			constexpr short m01New = -40;
			constexpr short m11New = -50;
			constexpr short m21New = 330;
			constexpr short m02New = 60;
			constexpr short m12New = 70;
			constexpr short m22New = 190;
			matrix[0] = PonyBase::Math::Vector3<short>(m00New, m01New, m02New);
			matrix[1] = PonyBase::Math::Vector3<short>(m10New, m11New, m12New);
			matrix[2] = PonyBase::Math::Vector3<short>(m20New, m21New, m22New);

			Assert::AreEqual(m00New, matrix[0][0]);
			Assert::AreEqual(m01New, matrix[0][1]);
			Assert::AreEqual(m02New, matrix[0][2]);
			Assert::AreEqual(m10New, matrix[1][0]);
			Assert::AreEqual(m11New, matrix[1][1]);
			Assert::AreEqual(m12New, matrix[1][2]);
			Assert::AreEqual(m20New, matrix[2][0]);
			Assert::AreEqual(m21New, matrix[2][1]);
			Assert::AreEqual(m22New, matrix[2][2]);
		}

		TEST_METHOD(Vector3ToRowFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);

			constexpr float m00New = 20;
			constexpr float m10New = 30;
			constexpr float m20New = 30;
			constexpr float m01New = -40;
			constexpr float m11New = -50;
			constexpr float m21New = 330;
			constexpr float m02New = 60;
			constexpr float m12New = 70;
			constexpr float m22New = 190;
			matrix[0] = PonyBase::Math::Vector3<float>(m00New, m01New, m02New);
			matrix[1] = PonyBase::Math::Vector3<float>(m10New, m11New, m12New);
			matrix[2] = PonyBase::Math::Vector3<float>(m20New, m21New, m22New);

			Assert::AreEqual(m00New, matrix[0][0]);
			Assert::AreEqual(m01New, matrix[0][1]);
			Assert::AreEqual(m02New, matrix[0][2]);
			Assert::AreEqual(m10New, matrix[1][0]);
			Assert::AreEqual(m11New, matrix[1][1]);
			Assert::AreEqual(m12New, matrix[1][2]);
			Assert::AreEqual(m20New, matrix[2][0]);
			Assert::AreEqual(m21New, matrix[2][1]);
			Assert::AreEqual(m22New, matrix[2][2]);
		}

		TEST_METHOD(DefaultConstructorShortTest)
		{
			const auto defaultMatrix = PonyBase::Math::Matrix3x3<short>();
			Assert::AreEqual(short{}, defaultMatrix.M00());
			Assert::AreEqual(short{}, defaultMatrix.M10());
			Assert::AreEqual(short{}, defaultMatrix.M20());
			Assert::AreEqual(short{}, defaultMatrix.M01());
			Assert::AreEqual(short{}, defaultMatrix.M11());
			Assert::AreEqual(short{}, defaultMatrix.M21());
			Assert::AreEqual(short{}, defaultMatrix.M02());
			Assert::AreEqual(short{}, defaultMatrix.M12());
			Assert::AreEqual(short{}, defaultMatrix.M22());
		}

		TEST_METHOD(DefaultConstructorFloatTest)
		{
			const auto defaultMatrix = PonyBase::Math::Matrix3x3<float>();
			Assert::AreEqual(float{}, defaultMatrix.M00());
			Assert::AreEqual(float{}, defaultMatrix.M10());
			Assert::AreEqual(float{}, defaultMatrix.M20());
			Assert::AreEqual(float{}, defaultMatrix.M01());
			Assert::AreEqual(float{}, defaultMatrix.M11());
			Assert::AreEqual(float{}, defaultMatrix.M21());
			Assert::AreEqual(float{}, defaultMatrix.M02());
			Assert::AreEqual(float{}, defaultMatrix.M12());
			Assert::AreEqual(float{}, defaultMatrix.M22());
		}

		TEST_METHOD(ConstructorShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(ConstructorFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(ConstructorColumnShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr auto column0 = PonyBase::Math::Vector3<short>(m00, m10, m20);
			constexpr auto column1 = PonyBase::Math::Vector3<short>(m01, m11, m21);
			constexpr auto column2 = PonyBase::Math::Vector3<short>(m02, m12, m22);
			const auto matrix = PonyBase::Math::Matrix3x3<short>(column0, column1, column2);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(ConstructorColumnFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr auto column0 = PonyBase::Math::Vector3<float>(m00, m10, m20);
			constexpr auto column1 = PonyBase::Math::Vector3<float>(m01, m11, m21);
			constexpr auto column2 = PonyBase::Math::Vector3<float>(m02, m12, m22);
			const auto matrix = PonyBase::Math::Matrix3x3<float>(column0, column1, column2);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(ConstructorSpanShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr std::array<short, 9> array{ m00, m10, m20, m01, m11, m21, m02, m12, m22 };
			const auto matrix = PonyBase::Math::Matrix3x3<short>(array);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(ConstructorSpanFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr std::array<float, 9> array{ m00, m10, m20, m01, m11, m21, m02, m12, m22 };
			const auto matrix = PonyBase::Math::Matrix3x3<float>(array);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(ConstructorCopyShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto copiedMatrix = matrix;
			Assert::AreEqual(m00, copiedMatrix.M00());
			Assert::AreEqual(m10, copiedMatrix.M10());
			Assert::AreEqual(m20, copiedMatrix.M20());
			Assert::AreEqual(m01, copiedMatrix.M01());
			Assert::AreEqual(m11, copiedMatrix.M11());
			Assert::AreEqual(m21, copiedMatrix.M21());
			Assert::AreEqual(m02, copiedMatrix.M02());
			Assert::AreEqual(m12, copiedMatrix.M12());
			Assert::AreEqual(m22, copiedMatrix.M22());
		}

		TEST_METHOD(ConstructorCopyFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto copiedMatrix = matrix;
			Assert::AreEqual(m00, copiedMatrix.M00());
			Assert::AreEqual(m10, copiedMatrix.M10());
			Assert::AreEqual(m20, copiedMatrix.M20());
			Assert::AreEqual(m01, copiedMatrix.M01());
			Assert::AreEqual(m11, copiedMatrix.M11());
			Assert::AreEqual(m21, copiedMatrix.M21());
			Assert::AreEqual(m02, copiedMatrix.M02());
			Assert::AreEqual(m12, copiedMatrix.M12());
			Assert::AreEqual(m22, copiedMatrix.M22());
		}

		TEST_METHOD(ConstructorMoveShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto movedMatrix = std::move(matrix);
			Assert::AreEqual(m00, movedMatrix.M00());
			Assert::AreEqual(m10, movedMatrix.M10());
			Assert::AreEqual(m20, movedMatrix.M20());
			Assert::AreEqual(m01, movedMatrix.M01());
			Assert::AreEqual(m11, movedMatrix.M11());
			Assert::AreEqual(m21, movedMatrix.M21());
			Assert::AreEqual(m02, movedMatrix.M02());
			Assert::AreEqual(m12, movedMatrix.M12());
			Assert::AreEqual(m22, movedMatrix.M22());
		}

		TEST_METHOD(ConstructorMoveFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto movedMatrix = std::move(matrix);
			Assert::AreEqual(m00, movedMatrix.M00());
			Assert::AreEqual(m10, movedMatrix.M10());
			Assert::AreEqual(m20, movedMatrix.M20());
			Assert::AreEqual(m01, movedMatrix.M01());
			Assert::AreEqual(m11, movedMatrix.M11());
			Assert::AreEqual(m21, movedMatrix.M21());
			Assert::AreEqual(m02, movedMatrix.M02());
			Assert::AreEqual(m12, movedMatrix.M12());
			Assert::AreEqual(m22, movedMatrix.M22());
		}

		TEST_METHOD(ComponentAccessShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;

			auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m00, matrix.Component(0));
			Assert::AreEqual(m10, matrix.Component(1));
			Assert::AreEqual(m20, matrix.Component(2));
			Assert::AreEqual(m01, matrix.Component(3));
			Assert::AreEqual(m11, matrix.Component(4));
			Assert::AreEqual(m21, matrix.Component(5));
			Assert::AreEqual(m02, matrix.Component(6));
			Assert::AreEqual(m12, matrix.Component(7));
			Assert::AreEqual(m22, matrix.Component(8));

			constexpr auto matrixC = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m20, matrixC.M20());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(m21, matrixC.M21());
			Assert::AreEqual(m02, matrixC.M02());
			Assert::AreEqual(m12, matrixC.M12());
			Assert::AreEqual(m22, matrixC.M22());
			Assert::AreEqual(m00, matrixC.Component(0));
			Assert::AreEqual(m10, matrixC.Component(1));
			Assert::AreEqual(m20, matrixC.Component(2));
			Assert::AreEqual(m01, matrixC.Component(3));
			Assert::AreEqual(m11, matrixC.Component(4));
			Assert::AreEqual(m21, matrixC.Component(5));
			Assert::AreEqual(m02, matrixC.Component(6));
			Assert::AreEqual(m12, matrixC.Component(7));
			Assert::AreEqual(m22, matrixC.Component(8));
		}

		TEST_METHOD(ComponentAccessFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;

			auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
			Assert::AreEqual(m00, matrix.Component(0));
			Assert::AreEqual(m10, matrix.Component(1));
			Assert::AreEqual(m20, matrix.Component(2));
			Assert::AreEqual(m01, matrix.Component(3));
			Assert::AreEqual(m11, matrix.Component(4));
			Assert::AreEqual(m21, matrix.Component(5));
			Assert::AreEqual(m02, matrix.Component(6));
			Assert::AreEqual(m12, matrix.Component(7));
			Assert::AreEqual(m22, matrix.Component(8));

			constexpr auto matrixC = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m20, matrixC.M20());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(m21, matrixC.M21());
			Assert::AreEqual(m02, matrixC.M02());
			Assert::AreEqual(m12, matrixC.M12());
			Assert::AreEqual(m22, matrixC.M22());
			Assert::AreEqual(m00, matrixC.Component(0));
			Assert::AreEqual(m10, matrixC.Component(1));
			Assert::AreEqual(m20, matrixC.Component(2));
			Assert::AreEqual(m01, matrixC.Component(3));
			Assert::AreEqual(m11, matrixC.Component(4));
			Assert::AreEqual(m21, matrixC.Component(5));
			Assert::AreEqual(m02, matrixC.Component(6));
			Assert::AreEqual(m12, matrixC.Component(7));
			Assert::AreEqual(m22, matrixC.Component(8));
		}

		TEST_METHOD(SpanShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;

			auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(m00, matrix.Span()[0]);
			Assert::AreEqual(m10, matrix.Span()[1]);
			Assert::AreEqual(m20, matrix.Span()[2]);
			Assert::AreEqual(m01, matrix.Span()[3]);
			Assert::AreEqual(m11, matrix.Span()[4]);
			Assert::AreEqual(m21, matrix.Span()[5]);
			Assert::AreEqual(m02, matrix.Span()[6]);
			Assert::AreEqual(m12, matrix.Span()[7]);
			Assert::AreEqual(m22, matrix.Span()[8]);
			Assert::AreEqual(m00, matrix.Span(0)[0]);
			Assert::AreEqual(m10, matrix.Span(0)[1]);
			Assert::AreEqual(m20, matrix.Span(0)[2]);
			Assert::AreEqual(m01, matrix.Span(1)[0]);
			Assert::AreEqual(m11, matrix.Span(1)[1]);
			Assert::AreEqual(m21, matrix.Span(1)[2]);
			Assert::AreEqual(m02, matrix.Span(2)[0]);
			Assert::AreEqual(m12, matrix.Span(2)[1]);
			Assert::AreEqual(m22, matrix.Span(2)[2]);

			constexpr auto matrixC = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(m00, matrixC.Span()[0]);
			Assert::AreEqual(m10, matrixC.Span()[1]);
			Assert::AreEqual(m20, matrixC.Span()[2]);
			Assert::AreEqual(m01, matrixC.Span()[3]);
			Assert::AreEqual(m11, matrixC.Span()[4]);
			Assert::AreEqual(m21, matrixC.Span()[5]);
			Assert::AreEqual(m02, matrixC.Span()[6]);
			Assert::AreEqual(m12, matrixC.Span()[7]);
			Assert::AreEqual(m22, matrixC.Span()[8]);
			Assert::AreEqual(m00, matrixC.Span(0)[0]);
			Assert::AreEqual(m10, matrixC.Span(0)[1]);
			Assert::AreEqual(m20, matrixC.Span(0)[2]);
			Assert::AreEqual(m01, matrixC.Span(1)[0]);
			Assert::AreEqual(m11, matrixC.Span(1)[1]);
			Assert::AreEqual(m21, matrixC.Span(1)[2]);
			Assert::AreEqual(m02, matrixC.Span(2)[0]);
			Assert::AreEqual(m12, matrixC.Span(2)[1]);
			Assert::AreEqual(m22, matrixC.Span(2)[2]);
		}

		TEST_METHOD(SpanFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;

			auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(m00, matrix.Span()[0]);
			Assert::AreEqual(m10, matrix.Span()[1]);
			Assert::AreEqual(m20, matrix.Span()[2]);
			Assert::AreEqual(m01, matrix.Span()[3]);
			Assert::AreEqual(m11, matrix.Span()[4]);
			Assert::AreEqual(m21, matrix.Span()[5]);
			Assert::AreEqual(m02, matrix.Span()[6]);
			Assert::AreEqual(m12, matrix.Span()[7]);
			Assert::AreEqual(m22, matrix.Span()[8]);
			Assert::AreEqual(m00, matrix.Span(0)[0]);
			Assert::AreEqual(m10, matrix.Span(0)[1]);
			Assert::AreEqual(m20, matrix.Span(0)[2]);
			Assert::AreEqual(m01, matrix.Span(1)[0]);
			Assert::AreEqual(m11, matrix.Span(1)[1]);
			Assert::AreEqual(m21, matrix.Span(1)[2]);
			Assert::AreEqual(m02, matrix.Span(2)[0]);
			Assert::AreEqual(m12, matrix.Span(2)[1]);
			Assert::AreEqual(m22, matrix.Span(2)[2]);

			constexpr auto matrixC = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(m00, matrixC.Span()[0]);
			Assert::AreEqual(m10, matrixC.Span()[1]);
			Assert::AreEqual(m20, matrixC.Span()[2]);
			Assert::AreEqual(m01, matrixC.Span()[3]);
			Assert::AreEqual(m11, matrixC.Span()[4]);
			Assert::AreEqual(m21, matrixC.Span()[5]);
			Assert::AreEqual(m02, matrixC.Span()[6]);
			Assert::AreEqual(m12, matrixC.Span()[7]);
			Assert::AreEqual(m22, matrixC.Span()[8]);
			Assert::AreEqual(m00, matrixC.Span(0)[0]);
			Assert::AreEqual(m10, matrixC.Span(0)[1]);
			Assert::AreEqual(m20, matrixC.Span(0)[2]);
			Assert::AreEqual(m01, matrixC.Span(1)[0]);
			Assert::AreEqual(m11, matrixC.Span(1)[1]);
			Assert::AreEqual(m21, matrixC.Span(1)[2]);
			Assert::AreEqual(m02, matrixC.Span(2)[0]);
			Assert::AreEqual(m12, matrixC.Span(2)[1]);
			Assert::AreEqual(m22, matrixC.Span(2)[2]);
		}

		TEST_METHOD(GetRowShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto row0 = matrix.Row(0);
			const auto row1 = matrix.Row(1);
			const auto row2 = matrix.Row(2);
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());
			Assert::AreEqual(m02, row0.Z());
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
			Assert::AreEqual(m12, row1.Z());
			Assert::AreEqual(m20, row2.X());
			Assert::AreEqual(m21, row2.Y());
			Assert::AreEqual(m22, row2.Z());
		}

		TEST_METHOD(GetRowFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto row0 = matrix.Row(0);
			const auto row1 = matrix.Row(1);
			const auto row2 = matrix.Row(2);
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());
			Assert::AreEqual(m02, row0.Z());
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
			Assert::AreEqual(m12, row1.Z());
			Assert::AreEqual(m20, row2.X());
			Assert::AreEqual(m21, row2.Y());
			Assert::AreEqual(m22, row2.Z());
		}

		TEST_METHOD(SetRowShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<short>();
			constexpr auto row0 = PonyBase::Math::Vector3<short>(m00, m01, m02);
			constexpr auto row1 = PonyBase::Math::Vector3<short>(m10, m11, m12);
			constexpr auto row2 = PonyBase::Math::Vector3<short>(m20, m21, m22);
			matrix.Row(0, row0);
			matrix.Row(1, row1);
			matrix.Row(2, row2);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(SetRowFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<float>();
			constexpr auto row0 = PonyBase::Math::Vector3<float>(m00, m01, m02);
			constexpr auto row1 = PonyBase::Math::Vector3<float>(m10, m11, m12);
			constexpr auto row2 = PonyBase::Math::Vector3<float>(m20, m21, m22);
			matrix.Row(0, row0);
			matrix.Row(1, row1);
			matrix.Row(2, row2);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(GetColumnShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto column0 = matrix.Column(0);
			const auto column1 = matrix.Column(1);
			const auto column2 = matrix.Column(2);
			Assert::AreEqual(m00, column0.X());
			Assert::AreEqual(m10, column0.Y());
			Assert::AreEqual(m20, column0.Z());
			Assert::AreEqual(m01, column1.X());
			Assert::AreEqual(m11, column1.Y());
			Assert::AreEqual(m21, column1.Z());
			Assert::AreEqual(m02, column2.X());
			Assert::AreEqual(m12, column2.Y());
			Assert::AreEqual(m22, column2.Z());
		}

		TEST_METHOD(GetColumnFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto column0 = matrix.Column(0);
			const auto column1 = matrix.Column(1);
			const auto column2 = matrix.Column(2);
			Assert::AreEqual(m00, column0.X());
			Assert::AreEqual(m10, column0.Y());
			Assert::AreEqual(m20, column0.Z());
			Assert::AreEqual(m01, column1.X());
			Assert::AreEqual(m11, column1.Y());
			Assert::AreEqual(m21, column1.Z());
			Assert::AreEqual(m02, column2.X());
			Assert::AreEqual(m12, column2.Y());
			Assert::AreEqual(m22, column2.Z());
		}

		TEST_METHOD(SetColumnShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<short>();
			constexpr auto column0 = PonyBase::Math::Vector3<short>(m00, m10, m20);
			constexpr auto column1 = PonyBase::Math::Vector3<short>(m01, m11, m21);
			constexpr auto column2 = PonyBase::Math::Vector3<short>(m02, m12, m22);
			matrix.Column(0, column0);
			matrix.Column(1, column1);
			matrix.Column(2, column2);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(SetColumnFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<float>();
			constexpr auto column0 = PonyBase::Math::Vector3<float>(m00, m10, m20);
			constexpr auto column1 = PonyBase::Math::Vector3<float>(m01, m11, m21);
			constexpr auto column2 = PonyBase::Math::Vector3<float>(m02, m12, m22);
			matrix.Column(0, column0);
			matrix.Column(1, column1);
			matrix.Column(2, column2);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(GetDiagonalShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto diagonal = matrix.Diagonal();
			Assert::AreEqual(m00, diagonal.X());
			Assert::AreEqual(m11, diagonal.Y());
			Assert::AreEqual(m22, diagonal.Z());
		}

		TEST_METHOD(GetDiagonalFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto diagonal = matrix.Diagonal();
			Assert::AreEqual(m00, diagonal.X());
			Assert::AreEqual(m11, diagonal.Y());
			Assert::AreEqual(m22, diagonal.Z());
		}

		TEST_METHOD(SetDiagonalShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m11 = -2;
			constexpr short m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<short>();
			constexpr auto diagonal = PonyBase::Math::Vector3<short>(m00, m11, m22);
			matrix.Diagonal(diagonal);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(short{}, matrix.M10());
			Assert::AreEqual(short{}, matrix.M20());
			Assert::AreEqual(short{}, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(short{}, matrix.M21());
			Assert::AreEqual(short{}, matrix.M02());
			Assert::AreEqual(short{}, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(SetDiagonalFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m11 = -2;
			constexpr float m22 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<float>();
			constexpr auto diagonal = PonyBase::Math::Vector3<float>(m00, m11, m22);
			matrix.Diagonal(diagonal);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(float{}, matrix.M10());
			Assert::AreEqual(float{}, matrix.M20());
			Assert::AreEqual(float{}, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(float{}, matrix.M21());
			Assert::AreEqual(float{}, matrix.M02());
			Assert::AreEqual(float{}, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(GetCounterDiagonalShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto counterDiagonal = matrix.CounterDiagonal();
			Assert::AreEqual(m02, counterDiagonal.X());
			Assert::AreEqual(m11, counterDiagonal.Y());
			Assert::AreEqual(m20, counterDiagonal.Z());
		}

		TEST_METHOD(GetCounterDiagonalFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto counterDiagonal = matrix.CounterDiagonal();
			Assert::AreEqual(m02, counterDiagonal.X());
			Assert::AreEqual(m11, counterDiagonal.Y());
			Assert::AreEqual(m20, counterDiagonal.Z());
		}

		TEST_METHOD(SetCounterDiagonalShortTest)
		{
			constexpr short m02 = 3;
			constexpr short m11 = -2;
			constexpr short m20 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<short>();
			constexpr auto counterDiagonal = PonyBase::Math::Vector3<short>(m02, m11, m20);
			matrix.CounterDiagonal(counterDiagonal);
			Assert::AreEqual(short{}, matrix.M00());
			Assert::AreEqual(short{}, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(short{}, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(short{}, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(short{}, matrix.M12());
			Assert::AreEqual(short{}, matrix.M22());
		}

		TEST_METHOD(SetCounterDiagonalFloatTest)
		{
			constexpr float m02 = 3;
			constexpr float m11 = -2;
			constexpr float m20 = 19;
			auto matrix = PonyBase::Math::Matrix3x3<float>();
			constexpr auto counterDiagonal = PonyBase::Math::Vector3<float>(m02, m11, m20);
			matrix.CounterDiagonal(counterDiagonal);
			Assert::AreEqual(float{}, matrix.M00());
			Assert::AreEqual(float{}, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(float{}, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(float{}, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(float{}, matrix.M12());
			Assert::AreEqual(float{}, matrix.M22());
		}

		TEST_METHOD(TraceShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(short{9}, matrix.Trace());
		}

		TEST_METHOD(TraceFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(9.f, matrix.Trace());
		}

		TEST_METHOD(DeterminantShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(short{-7190}, matrix.Determinant());
		}

		TEST_METHOD(DeterminantFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(-7190.f, matrix.Determinant());
		}

		TEST_METHOD(AdjugateShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto adjugate = matrix.Adjugate();
			Assert::AreEqual(short{-611}, adjugate.M00());
			Assert::AreEqual(short{306}, adjugate.M10());
			Assert::AreEqual(short{-435}, adjugate.M20());
			Assert::AreEqual(short{103}, adjugate.M01());
			Assert::AreEqual(short{172}, adjugate.M11());
			Assert::AreEqual(short{-315 }, adjugate.M21());
			Assert::AreEqual(short{155}, adjugate.M02());
			Assert::AreEqual(short{-160}, adjugate.M12());
			Assert::AreEqual(short{-125}, adjugate.M22());
		}

		TEST_METHOD(AdjugateFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto adjugate = matrix.Adjugate();
			Assert::AreEqual(-611.f, adjugate.M00());
			Assert::AreEqual(306.f, adjugate.M10());
			Assert::AreEqual(-435.f, adjugate.M20());
			Assert::AreEqual(103.f, adjugate.M01());
			Assert::AreEqual(172.f, adjugate.M11());
			Assert::AreEqual(-315.f, adjugate.M21());
			Assert::AreEqual(155.f, adjugate.M02());
			Assert::AreEqual(-160.f, adjugate.M12());
			Assert::AreEqual(-125.f, adjugate.M22());
		}

		TEST_METHOD(TransposeShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m20 = 3;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr short m21 = 33;
			constexpr short m02 = 6;
			constexpr short m12 = 7;
			constexpr short m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto transpose = matrix.Transpose();
			Assert::AreEqual(m00, transpose.M00());
			Assert::AreEqual(m01, transpose.M10());
			Assert::AreEqual(m02, transpose.M20());
			Assert::AreEqual(m10, transpose.M01());
			Assert::AreEqual(m11, transpose.M11());
			Assert::AreEqual(m12, transpose.M21());
			Assert::AreEqual(m20, transpose.M02());
			Assert::AreEqual(m21, transpose.M12());
			Assert::AreEqual(m22, transpose.M22());
		}

		TEST_METHOD(TransposeFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m20 = 3;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr float m21 = 33;
			constexpr float m02 = 6;
			constexpr float m12 = 7;
			constexpr float m22 = 19;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto transpose = matrix.Transpose();
			Assert::AreEqual(m00, transpose.M00());
			Assert::AreEqual(m01, transpose.M10());
			Assert::AreEqual(m02, transpose.M20());
			Assert::AreEqual(m10, transpose.M01());
			Assert::AreEqual(m11, transpose.M11());
			Assert::AreEqual(m12, transpose.M21());
			Assert::AreEqual(m20, transpose.M02());
			Assert::AreEqual(m21, transpose.M12());
			Assert::AreEqual(m22, transpose.M22());
		}

		TEST_METHOD(InverseFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto inverse = matrix.Inverse();
			Assert::AreEqual(0.066, static_cast<double>(inverse.M00()), 0.001);
			Assert::AreEqual(0.033, static_cast<double>(inverse.M10()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(inverse.M20()), 0.001);
			Assert::AreEqual(1.733, static_cast<double>(inverse.M01()), 0.001);
			Assert::AreEqual(-0.633, static_cast<double>(inverse.M11()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(inverse.M21()), 0.001);
			Assert::AreEqual(-2.133, static_cast<double>(inverse.M02()), 0.001);
			Assert::AreEqual(0.933, static_cast<double>(inverse.M12()), 0.001);
			Assert::AreEqual(-0.2, static_cast<double>(inverse.M22()), 0.001);
		}

		TEST_METHOD(IsZeroShortTest)
		{
			Assert::IsTrue(PonyBase::Math::Matrix3x3<short>::Predefined::Zero.IsZero());

			auto matrix = PonyBase::Math::Matrix3x3<short>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyBase::Math::Matrix3x3<float>::ComponentCount; ++i)
			{
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyBase::Math::Matrix3x3<short>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsZeroFloatTest)
		{
			Assert::IsTrue(PonyBase::Math::Matrix3x3<float>::Predefined::Zero.IsZero());

			auto matrix = PonyBase::Math::Matrix3x3<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyBase::Math::Matrix3x3<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsZero());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyBase::Math::Matrix3x3<float>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsAlmostZeroTest)
		{
			Assert::IsTrue(PonyBase::Math::Matrix3x3<float>::Predefined::Zero.IsAlmostZero());

			auto matrix = PonyBase::Math::Matrix3x3<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsAlmostZero());

			for (std::size_t i = 0; i < PonyBase::Math::Matrix3x3<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsAlmostZero());
				Assert::IsTrue(matrix.IsAlmostZero(5.f));
				matrix.Span()[i] = PonyBase::Math::Matrix3x3<float>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsIdentityShortTest)
		{
			Assert::IsTrue(PonyBase::Math::Matrix3x3<short>::Predefined::Identity.IsIdentity());

			auto matrix = PonyBase::Math::Matrix3x3<short>::Predefined::Identity;
			Assert::IsTrue(matrix.IsIdentity());

			for (std::size_t i = 0; i < PonyBase::Math::Matrix3x3<float>::ComponentCount; ++i)
			{
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsIdentity());
				matrix.Span()[i] = PonyBase::Math::Matrix3x3<short>::Predefined::Identity.Span()[i];
			}
		}

		TEST_METHOD(IsIdentityFloatTest)
		{
			Assert::IsTrue(PonyBase::Math::Matrix3x3<float>::Predefined::Identity.IsIdentity());

			auto matrix = PonyBase::Math::Matrix3x3<float>::Predefined::Identity;
			Assert::IsTrue(matrix.IsIdentity());

			for (std::size_t i = 0; i < PonyBase::Math::Matrix3x3<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsIdentity());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsFalse(matrix.IsIdentity());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsIdentity());
				matrix.Span()[i] = PonyBase::Math::Matrix3x3<float>::Predefined::Identity.Span()[i];
			}
		}

		TEST_METHOD(IsAlmostIdentityTest)
		{
			Assert::IsTrue(PonyBase::Math::Matrix3x3<float>::Predefined::Identity.IsAlmostIdentity());

			auto matrix = PonyBase::Math::Matrix3x3<float>::Predefined::Identity;
			Assert::IsTrue(matrix.IsAlmostIdentity());

			for (std::size_t i = 0; i < PonyBase::Math::Matrix3x3<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsAlmostIdentity());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsTrue(matrix.IsAlmostIdentity());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsAlmostIdentity());
				Assert::IsTrue(matrix.IsAlmostIdentity(5.f));
				matrix.Span()[i] = PonyBase::Math::Matrix3x3<float>::Predefined::Identity.Span()[i];
			}
		}

		TEST_METHOD(IsFiniteTest)
		{
			Assert::IsTrue(PonyBase::Math::Matrix3x3<float>::Predefined::Zero.IsFinite());
			Assert::IsTrue(PonyBase::Math::Matrix3x3<float>::Predefined::Identity.IsFinite());

			const float nan = std::numeric_limits<float>::quiet_NaN();
			constexpr std::array<float, 9> array{ 3.f, 1.f, -5.f, 7.f, 4.f, -6.f, -7.f, 10.f, 20.f };
			auto matrix = PonyBase::Math::Matrix3x3<float>(array);
			Assert::IsTrue(matrix.IsFinite());
			for (std::size_t i = 0; i < PonyBase::Math::Matrix3x3<float>::ComponentCount; ++i)
			{
				matrix.Span()[i] = nan;
				Assert::IsFalse(matrix.IsFinite());
				matrix.Span()[i] = array[i];
			}
		}

		TEST_METHOD(SetShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = 3;
			constexpr short m20 = 2;
			constexpr short m01 = 4;
			constexpr short m11 = 6;
			constexpr short m21 = 5;
			constexpr short m02 = 8;
			constexpr short m12 = -4;
			constexpr short m22 = -3;
			auto matrix = PonyBase::Math::Matrix3x3<short>();
			matrix.Set(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(SetFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			auto matrix = PonyBase::Math::Matrix3x3<float>();
			matrix.Set(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(SetColumnsShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = 3;
			constexpr short m20 = 2;
			constexpr short m01 = 4;
			constexpr short m11 = 6;
			constexpr short m21 = 5;
			constexpr short m02 = 8;
			constexpr short m12 = -4;
			constexpr short m22 = -3;
			constexpr auto column0 = PonyBase::Math::Vector3<short>(m00, m10, m20);
			constexpr auto column1 = PonyBase::Math::Vector3<short>(m01, m11, m21);
			constexpr auto column2 = PonyBase::Math::Vector3<short>(m02, m12, m22);
			auto matrix = PonyBase::Math::Matrix3x3<short>();
			matrix.Set(column0, column1, column2);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(SetColumsFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			constexpr auto column0 = PonyBase::Math::Vector3<float>(m00, m10, m20);
			constexpr auto column1 = PonyBase::Math::Vector3<float>(m01, m11, m21);
			constexpr auto column2 = PonyBase::Math::Vector3<float>(m02, m12, m22);
			auto matrix = PonyBase::Math::Matrix3x3<float>();
			matrix.Set(column0, column1, column2);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(SetSpanShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = 3;
			constexpr short m20 = 2;
			constexpr short m01 = 4;
			constexpr short m11 = 6;
			constexpr short m21 = 5;
			constexpr short m02 = 8;
			constexpr short m12 = -4;
			constexpr short m22 = -3;
			constexpr std::array<short, 9> array{ m00, m10, m20, m01, m11, m21, m02, m12, m22 };
			auto matrix = PonyBase::Math::Matrix3x3<short>();
			matrix.Set(array);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(SetSpanFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			constexpr std::array<float, 9> array{ m00, m10, m20, m01, m11, m21, m02, m12, m22 };
			auto matrix = PonyBase::Math::Matrix3x3<float>();
			matrix.Set(array);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m20, matrix.M20());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
			Assert::AreEqual(m21, matrix.M21());
			Assert::AreEqual(m02, matrix.M02());
			Assert::AreEqual(m12, matrix.M12());
			Assert::AreEqual(m22, matrix.M22());
		}

		TEST_METHOD(ScaleThisShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = 3;
			constexpr short m20 = 2;
			constexpr short m01 = 4;
			constexpr short m11 = 6;
			constexpr short m21 = 5;
			constexpr short m02 = 8;
			constexpr short m12 = -4;
			constexpr short m22 = -3;
			constexpr short m00S = 3;
			constexpr short m10S = -2;
			constexpr short m20S = 5;
			constexpr short m01S = 4;
			constexpr short m11S = -1;
			constexpr short m21S = 7;
			constexpr short m02S = -5;
			constexpr short m12S = 6;
			constexpr short m22S = -7;
			auto matrix = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			constexpr auto scale = PonyBase::Math::Matrix3x3<short>(m00S, m10S, m20S, m01S, m11S, m21S, m02S, m12S, m22S);
			matrix.Scale(scale);
			Assert::AreEqual(static_cast<short>(m00 * m00S), matrix.M00());
			Assert::AreEqual(static_cast<short>(m10 * m10S), matrix.M10());
			Assert::AreEqual(static_cast<short>(m20 * m20S), matrix.M20());
			Assert::AreEqual(static_cast<short>(m01 * m01S), matrix.M01());
			Assert::AreEqual(static_cast<short>(m11 * m11S), matrix.M11());
			Assert::AreEqual(static_cast<short>(m21 * m21S), matrix.M21());
			Assert::AreEqual(static_cast<short>(m02 * m02S), matrix.M02());
			Assert::AreEqual(static_cast<short>(m12 * m12S), matrix.M12());
			Assert::AreEqual(static_cast<short>(m22 * m22S), matrix.M22());
		}

		TEST_METHOD(ScaleThisFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			constexpr float m00S = 3;
			constexpr float m10S = -2;
			constexpr float m20S = 5;
			constexpr float m01S = 4;
			constexpr float m11S = -1;
			constexpr float m21S = 7;
			constexpr float m02S = -5;
			constexpr float m12S = 6;
			constexpr float m22S = -7;
			auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			constexpr auto scale = PonyBase::Math::Matrix3x3<float>(m00S, m10S, m20S, m01S, m11S, m21S, m02S, m12S, m22S);
			matrix.Scale(scale);
			Assert::AreEqual(m00 * m00S, matrix.M00());
			Assert::AreEqual(m10 * m10S, matrix.M10());
			Assert::AreEqual(m20 * m20S, matrix.M20());
			Assert::AreEqual(m01 * m01S, matrix.M01());
			Assert::AreEqual(m11 * m11S, matrix.M11());
			Assert::AreEqual(m21 * m21S, matrix.M21());
			Assert::AreEqual(m02 * m02S, matrix.M02());
			Assert::AreEqual(m12 * m12S, matrix.M12());
			Assert::AreEqual(m22 * m22S, matrix.M22());
		}

		TEST_METHOD(ToStringShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = 3;
			constexpr short m20 = 2;
			constexpr short m01 = 4;
			constexpr short m11 = 6;
			constexpr short m21 = 5;
			constexpr short m02 = 8;
			constexpr short m12 = -4;
			constexpr short m22 = -3;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto expectedString = std::format("({}, {}, {})({}, {}, {})({}, {}, {})", m00, m01, m02, m10, m11, m12, m20, m21, m22);
			Assert::AreEqual(expectedString, matrix.ToString());
			std::ostringstream ss;
			ss << matrix;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(ToStringFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			constexpr auto matrix = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			const auto expectedString = std::format("({}, {}, {})({}, {}, {})({}, {}, {})", m00, m01, m02, m10, m11, m12, m20, m21, m22);
			Assert::AreEqual(expectedString, matrix.ToString());
			std::ostringstream ss;
			ss << matrix;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(AssignmentCopyShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = 3;
			constexpr short m20 = 2;
			constexpr short m01 = 4;
			constexpr short m11 = 6;
			constexpr short m21 = 5;
			constexpr short m02 = 8;
			constexpr short m12 = -4;
			constexpr short m22 = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			PonyBase::Math::Matrix3x3<short> matrixC;
			PonyBase::Math::Matrix3x3<short>& matrixL = matrixC = matrixR;
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m20, matrixC.M20());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(m21, matrixC.M21());
			Assert::AreEqual(m02, matrixC.M02());
			Assert::AreEqual(m12, matrixC.M12());
			Assert::AreEqual(m22, matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentCopyFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			PonyBase::Math::Matrix3x3<float> matrixC;
			PonyBase::Math::Matrix3x3<float>& matrixL = matrixC = matrixR;
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m20, matrixC.M20());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(m21, matrixC.M21());
			Assert::AreEqual(m02, matrixC.M02());
			Assert::AreEqual(m12, matrixC.M12());
			Assert::AreEqual(m22, matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMoveShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = 3;
			constexpr short m20 = 2;
			constexpr short m01 = 4;
			constexpr short m11 = 6;
			constexpr short m21 = 5;
			constexpr short m02 = 8;
			constexpr short m12 = -4;
			constexpr short m22 = -3;
			auto matrixR = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			PonyBase::Math::Matrix3x3<short> matrixC;
			PonyBase::Math::Matrix3x3<short>& matrixL = matrixC = std::move(matrixR);
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m20, matrixC.M20());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(m21, matrixC.M21());
			Assert::AreEqual(m02, matrixC.M02());
			Assert::AreEqual(m12, matrixC.M12());
			Assert::AreEqual(m22, matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMoveFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			auto matrixR = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			PonyBase::Math::Matrix3x3<float> matrixC;
			PonyBase::Math::Matrix3x3<float>& matrixL = matrixC = std::move(matrixR);
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m20, matrixC.M20());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(m21, matrixC.M21());
			Assert::AreEqual(m02, matrixC.M02());
			Assert::AreEqual(m12, matrixC.M12());
			Assert::AreEqual(m22, matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentSumShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = 3;
			constexpr short m20 = 2;
			constexpr short m01 = 4;
			constexpr short m11 = 6;
			constexpr short m21 = 5;
			constexpr short m02 = 8;
			constexpr short m12 = -4;
			constexpr short m22 = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			constexpr short m00C = 3;
			constexpr short m10C = -2;
			constexpr short m20C = 5;
			constexpr short m01C = 4;
			constexpr short m11C = -1;
			constexpr short m21C = 7;
			constexpr short m02C = -5;
			constexpr short m12C = 6;
			constexpr short m22C = -7;
			auto matrixC = PonyBase::Math::Matrix3x3<short>(m00C, m10C, m20C, m01C, m11C, m21C, m02C, m12C, m22C);
			PonyBase::Math::Matrix3x3<short>& matrixL = matrixC += matrixR;
			Assert::AreEqual(static_cast<short>(m00 + m00C), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10 + m10C), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m20 + m20C), matrixC.M20());
			Assert::AreEqual(static_cast<short>(m01 + m01C), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11 + m11C), matrixC.M11());
			Assert::AreEqual(static_cast<short>(m21 + m21C), matrixC.M21());
			Assert::AreEqual(static_cast<short>(m02 + m02C), matrixC.M02());
			Assert::AreEqual(static_cast<short>(m12 + m12C), matrixC.M12());
			Assert::AreEqual(static_cast<short>(m22 + m22C), matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentSumFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			constexpr float m00C = 3;
			constexpr float m10C = -2;
			constexpr float m20C = 5;
			constexpr float m01C = 4;
			constexpr float m11C = -1;
			constexpr float m21C = 7;
			constexpr float m02C = -5;
			constexpr float m12C = 6;
			constexpr float m22C = -7;
			auto matrixC = PonyBase::Math::Matrix3x3<float>(m00C, m10C, m20C, m01C, m11C, m21C, m02C, m12C, m22C);
			PonyBase::Math::Matrix3x3<float>& matrixL = matrixC += matrixR;
			Assert::AreEqual(m00 + m00C, matrixC.M00());
			Assert::AreEqual(m10 + m10C, matrixC.M10());
			Assert::AreEqual(m20 + m20C, matrixC.M20());
			Assert::AreEqual(m01 + m01C, matrixC.M01());
			Assert::AreEqual(m11 + m11C, matrixC.M11());
			Assert::AreEqual(m21 + m21C, matrixC.M21());
			Assert::AreEqual(m02 + m02C, matrixC.M02());
			Assert::AreEqual(m12 + m12C, matrixC.M12());
			Assert::AreEqual(m22 + m22C, matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentSubtractShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = 3;
			constexpr short m20 = 2;
			constexpr short m01 = 4;
			constexpr short m11 = 6;
			constexpr short m21 = 5;
			constexpr short m02 = 8;
			constexpr short m12 = -4;
			constexpr short m22 = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			constexpr short m00C = 3;
			constexpr short m10C = -2;
			constexpr short m20C = 5;
			constexpr short m01C = 4;
			constexpr short m11C = -1;
			constexpr short m21C = 7;
			constexpr short m02C = -5;
			constexpr short m12C = 6;
			constexpr short m22C = -7;
			auto matrixC = PonyBase::Math::Matrix3x3<short>(m00C, m10C, m20C, m01C, m11C, m21C, m02C, m12C, m22C);
			PonyBase::Math::Matrix3x3<short>& matrixL = matrixC -= matrixR;
			Assert::AreEqual(static_cast<short>(m00C - m00), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C - m10), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m20C - m20), matrixC.M20());
			Assert::AreEqual(static_cast<short>(m01C - m01), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C - m11), matrixC.M11());
			Assert::AreEqual(static_cast<short>(m21C - m21), matrixC.M21());
			Assert::AreEqual(static_cast<short>(m02C - m02), matrixC.M02());
			Assert::AreEqual(static_cast<short>(m12C - m12), matrixC.M12());
			Assert::AreEqual(static_cast<short>(m22C - m22), matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentSubtractFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			constexpr float m00C = 3;
			constexpr float m10C = -2;
			constexpr float m20C = 5;
			constexpr float m01C = 4;
			constexpr float m11C = -1;
			constexpr float m21C = 7;
			constexpr float m02C = -5;
			constexpr float m12C = 6;
			constexpr float m22C = -7;
			auto matrixC = PonyBase::Math::Matrix3x3<float>(m00C, m10C, m20C, m01C, m11C, m21C, m02C, m12C, m22C);
			PonyBase::Math::Matrix3x3<float>& matrixL = matrixC -= matrixR;
			Assert::AreEqual(m00C - m00, matrixC.M00());
			Assert::AreEqual(m10C - m10, matrixC.M10());
			Assert::AreEqual(m20C - m20, matrixC.M20());
			Assert::AreEqual(m01C - m01, matrixC.M01());
			Assert::AreEqual(m11C - m11, matrixC.M11());
			Assert::AreEqual(m21C - m21, matrixC.M21());
			Assert::AreEqual(m02C - m02, matrixC.M02());
			Assert::AreEqual(m12C - m12, matrixC.M12());
			Assert::AreEqual(m22C - m22, matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMultiplyNumberShortTest)
		{
			constexpr short multiplierI = 3;
			constexpr short m00C = 3;
			constexpr short m10C = -2;
			constexpr short m20C = 5;
			constexpr short m01C = 4;
			constexpr short m11C = -1;
			constexpr short m21C = 7;
			constexpr short m02C = -5;
			constexpr short m12C = 6;
			constexpr short m22C = -7;
			auto matrixC = PonyBase::Math::Matrix3x3<short>(m00C, m10C, m20C, m01C, m11C, m21C, m02C, m12C, m22C);
			PonyBase::Math::Matrix3x3<short>& matrixL = matrixC *= multiplierI;
			Assert::AreEqual(static_cast<short>(m00C * multiplierI), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C * multiplierI), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m20C * multiplierI), matrixC.M20());
			Assert::AreEqual(static_cast<short>(m01C * multiplierI), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C * multiplierI), matrixC.M11());
			Assert::AreEqual(static_cast<short>(m21C * multiplierI), matrixC.M21());
			Assert::AreEqual(static_cast<short>(m02C * multiplierI), matrixC.M02());
			Assert::AreEqual(static_cast<short>(m12C * multiplierI), matrixC.M12());
			Assert::AreEqual(static_cast<short>(m22C * multiplierI), matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));

			constexpr float multiplierF = 5.f;
			matrixC = PonyBase::Math::Matrix3x3<short>(m00C, m10C, m20C, m01C, m11C, m21C, m02C, m12C, m22C);
			PonyBase::Math::Matrix3x3<short>& matrixL1 = matrixC *= multiplierF;
			Assert::AreEqual(static_cast<short>(m00C * multiplierF), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C * multiplierF), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m20C * multiplierF), matrixC.M20());
			Assert::AreEqual(static_cast<short>(m01C * multiplierF), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C * multiplierF), matrixC.M11());
			Assert::AreEqual(static_cast<short>(m21C * multiplierF), matrixC.M21());
			Assert::AreEqual(static_cast<short>(m02C * multiplierF), matrixC.M02());
			Assert::AreEqual(static_cast<short>(m12C * multiplierF), matrixC.M12());
			Assert::AreEqual(static_cast<short>(m22C * multiplierF), matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL1));
		}

		TEST_METHOD(AssignmentMultiplyNumberFloatTest)
		{
			constexpr float multiplier = 3;
			constexpr float m00C = 3;
			constexpr float m10C = -2;
			constexpr float m20C = 5;
			constexpr float m01C = 4;
			constexpr float m11C = -1;
			constexpr float m21C = 7;
			constexpr float m02C = -5;
			constexpr float m12C = 6;
			constexpr float m22C = -7;
			auto matrixC = PonyBase::Math::Matrix3x3<float>(m00C, m10C, m20C, m01C, m11C, m21C, m02C, m12C, m22C);
			PonyBase::Math::Matrix3x3<float>& matrixL = matrixC *= multiplier;
			Assert::AreEqual(m00C * multiplier, matrixC.M00());
			Assert::AreEqual(m10C * multiplier, matrixC.M10());
			Assert::AreEqual(m20C * multiplier, matrixC.M20());
			Assert::AreEqual(m01C * multiplier, matrixC.M01());
			Assert::AreEqual(m11C * multiplier, matrixC.M11());
			Assert::AreEqual(m21C * multiplier, matrixC.M21());
			Assert::AreEqual(m02C * multiplier, matrixC.M02());
			Assert::AreEqual(m12C * multiplier, matrixC.M12());
			Assert::AreEqual(m22C * multiplier, matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMultiplyMatrixShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = 3;
			constexpr short m20 = 2;
			constexpr short m01 = 4;
			constexpr short m11 = 6;
			constexpr short m21 = 5;
			constexpr short m02 = 8;
			constexpr short m12 = -4;
			constexpr short m22 = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			constexpr short m00C = 3;
			constexpr short m10C = -2;
			constexpr short m20C = 5;
			constexpr short m01C = 4;
			constexpr short m11C = -1;
			constexpr short m21C = 7;
			constexpr short m02C = -5;
			constexpr short m12C = 6;
			constexpr short m22C = -7;
			auto matrixC = PonyBase::Math::Matrix3x3<short>(m00C, m10C, m20C, m01C, m11C, m21C, m02C, m12C, m22C);
			PonyBase::Math::Matrix3x3<short>& matrixL = matrixC *= matrixR;
			Assert::AreEqual(short{5}, matrixC.M00());
			Assert::AreEqual(short{7}, matrixC.M10());
			Assert::AreEqual(short{12}, matrixC.M20());
			Assert::AreEqual(short{11}, matrixC.M01());
			Assert::AreEqual(short{16}, matrixC.M11());
			Assert::AreEqual(short{27}, matrixC.M21());
			Assert::AreEqual(short{23}, matrixC.M02());
			Assert::AreEqual(short{-30}, matrixC.M12());
			Assert::AreEqual(short{33}, matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMultiplyMatrixFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			constexpr float m00C = 3;
			constexpr float m10C = -2;
			constexpr float m20C = 5;
			constexpr float m01C = 4;
			constexpr float m11C = -1;
			constexpr float m21C = 7;
			constexpr float m02C = -5;
			constexpr float m12C = 6;
			constexpr float m22C = -7;
			auto matrixC = PonyBase::Math::Matrix3x3<float>(m00C, m10C, m20C, m01C, m11C, m21C, m02C, m12C, m22C);
			PonyBase::Math::Matrix3x3<float>& matrixL = matrixC *= matrixR;
			Assert::AreEqual(5.f, matrixC.M00());
			Assert::AreEqual(7.f, matrixC.M10());
			Assert::AreEqual(12.f, matrixC.M20());
			Assert::AreEqual(11.f, matrixC.M01());
			Assert::AreEqual(16.f, matrixC.M11());
			Assert::AreEqual(27.f, matrixC.M21());
			Assert::AreEqual(23.f, matrixC.M02());
			Assert::AreEqual(-30.f, matrixC.M12());
			Assert::AreEqual(33.f, matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentDivideNumberShortTest)
		{
			constexpr short divisorI = 3;
			constexpr short m00C = 3;
			constexpr short m10C = -2;
			constexpr short m20C = 5;
			constexpr short m01C = 4;
			constexpr short m11C = -1;
			constexpr short m21C = 7;
			constexpr short m02C = -5;
			constexpr short m12C = 6;
			constexpr short m22C = -7;
			auto matrixC = PonyBase::Math::Matrix3x3<short>(m00C, m10C, m20C, m01C, m11C, m21C, m02C, m12C, m22C);
			PonyBase::Math::Matrix3x3<short>& matrixL = matrixC /= divisorI;
			Assert::AreEqual(static_cast<short>(m00C / divisorI), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C / divisorI), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m20C / divisorI), matrixC.M20());
			Assert::AreEqual(static_cast<short>(m01C / divisorI), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C / divisorI), matrixC.M11());
			Assert::AreEqual(static_cast<short>(m21C / divisorI), matrixC.M21());
			Assert::AreEqual(static_cast<short>(m02C / divisorI), matrixC.M02());
			Assert::AreEqual(static_cast<short>(m12C / divisorI), matrixC.M12());
			Assert::AreEqual(static_cast<short>(m22C / divisorI), matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));

			constexpr float divisorF = 5.f;
			matrixC = PonyBase::Math::Matrix3x3<short>(m00C, m10C, m20C, m01C, m11C, m21C, m02C, m12C, m22C);
			PonyBase::Math::Matrix3x3<short>& matrixL1 = matrixC /= divisorF;
			Assert::AreEqual(static_cast<short>(m00C / divisorF), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C / divisorF), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m20C / divisorF), matrixC.M20());
			Assert::AreEqual(static_cast<short>(m01C / divisorF), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C / divisorF), matrixC.M11());
			Assert::AreEqual(static_cast<short>(m21C / divisorF), matrixC.M21());
			Assert::AreEqual(static_cast<short>(m02C / divisorF), matrixC.M02());
			Assert::AreEqual(static_cast<short>(m12C / divisorF), matrixC.M12());
			Assert::AreEqual(static_cast<short>(m22C / divisorF), matrixC.M22());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL1));
		}

		TEST_METHOD(AssignmentDivideNumberFloatTest)
		{
			constexpr float divisor = 3;
			constexpr float m00C = 3;
			constexpr float m10C = -2;
			constexpr float m20C = 5;
			constexpr float m01C = 4;
			constexpr float m11C = -1;
			constexpr float m21C = 7;
			constexpr float m02C = -5;
			constexpr float m12C = 6;
			constexpr float m22C = -7;
			auto matrixC = PonyBase::Math::Matrix3x3<float>(m00C, m10C, m20C, m01C, m11C, m21C, m02C, m12C, m22C);
			PonyBase::Math::Matrix3x3<float>& matrixL = matrixC /= divisor;
			Assert::AreEqual(static_cast<double>(m00C / divisor), static_cast<double>(matrixC.M00()), 0.00001);
			Assert::AreEqual(static_cast<double>(m10C / divisor), static_cast<double>(matrixC.M10()), 0.00001);
			Assert::AreEqual(static_cast<double>(m20C / divisor), static_cast<double>(matrixC.M20()), 0.00001);
			Assert::AreEqual(static_cast<double>(m01C / divisor), static_cast<double>(matrixC.M01()), 0.00001);
			Assert::AreEqual(static_cast<double>(m11C / divisor), static_cast<double>(matrixC.M11()), 0.00001);
			Assert::AreEqual(static_cast<double>(m21C / divisor), static_cast<double>(matrixC.M21()), 0.00001);
			Assert::AreEqual(static_cast<double>(m02C / divisor), static_cast<double>(matrixC.M02()), 0.00001);
			Assert::AreEqual(static_cast<double>(m12C / divisor), static_cast<double>(matrixC.M12()), 0.00001);
			Assert::AreEqual(static_cast<double>(m22C / divisor), static_cast<double>(matrixC.M22()), 0.00001);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(EqualityOperatorShortTest)
		{
			constexpr short m00 = 1;
			constexpr short m10 = 3;
			constexpr short m20 = 2;
			constexpr short m01 = 4;
			constexpr short m11 = 6;
			constexpr short m21 = 5;
			constexpr short m02 = 8;
			constexpr short m12 = -4;
			constexpr short m22 = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<short>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			PonyBase::Math::Matrix3x3<short> matrixL = matrixR;

			Assert::IsTrue(matrixL == matrixR);
			Assert::IsFalse(matrixL != matrixR);

			for (std::size_t i = 0; i < PonyBase::Math::Matrix3x3<short>::ComponentCount; ++i)
			{
				matrixL.Span()[i] += 1;
				Assert::IsFalse(matrixL == matrixR);
				Assert::IsTrue(matrixL != matrixR);
				matrixL.Span()[i] = matrixR.Span()[i];
			}
		}

		TEST_METHOD(EqualityOperatorFloatTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			PonyBase::Math::Matrix3x3<float> matrixL = matrixR;

			Assert::IsTrue(matrixL == matrixR);
			Assert::IsFalse(matrixL != matrixR);

			for (std::size_t i = 0; i < PonyBase::Math::Matrix3x3<float>::ComponentCount; ++i)
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
			Assert::IsTrue(PonyBase::Math::Matrix3x3<float>::Predefined::Identity == PonyBase::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f));
			Assert::IsTrue(PonyBase::Math::Matrix3x3<float>::Predefined::Zero == PonyBase::Math::Matrix3x3<float>(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f));

			Assert::IsTrue(PonyBase::Math::Matrix3x3<short>::Predefined::Identity == PonyBase::Math::Matrix3x3<short>(1, 0, 0, 0, 1, 0, 0, 0, 1));
			Assert::IsTrue(PonyBase::Math::Matrix3x3<short>::Predefined::Zero == PonyBase::Math::Matrix3x3<short>(0, 0, 0, 0, 0, 0, 0, 0, 0));
		}

		TEST_METHOD(ScaleShortTest)
		{
			constexpr short m00R = 1;
			constexpr short m10R = 3;
			constexpr short m20R = 2;
			constexpr short m01R = 4;
			constexpr short m11R = 6;
			constexpr short m21R = 5;
			constexpr short m02R = 8;
			constexpr short m12R = -4;
			constexpr short m22R = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<short>(m00R, m10R, m20R, m01R, m11R, m21R, m02R, m12R, m22R);
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<short>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Matrix3x3<short> scaled = PonyBase::Math::Scale(matrixL, matrixR);
			Assert::AreEqual(static_cast<short>(m00L * m00R), scaled.M00());
			Assert::AreEqual(static_cast<short>(m10L * m10R), scaled.M10());
			Assert::AreEqual(static_cast<short>(m20L * m20R), scaled.M20());
			Assert::AreEqual(static_cast<short>(m01L * m01R), scaled.M01());
			Assert::AreEqual(static_cast<short>(m11L * m11R), scaled.M11());
			Assert::AreEqual(static_cast<short>(m21L * m21R), scaled.M21());
			Assert::AreEqual(static_cast<short>(m02L * m02R), scaled.M02());
			Assert::AreEqual(static_cast<short>(m12L * m12R), scaled.M12());
			Assert::AreEqual(static_cast<short>(m22L * m22R), scaled.M22());
		}

		TEST_METHOD(ScaleFloatTest)
		{
			constexpr float m00R = 1;
			constexpr float m10R = 3;
			constexpr float m20R = 2;
			constexpr float m01R = 4;
			constexpr float m11R = 6;
			constexpr float m21R = 5;
			constexpr float m02R = 8;
			constexpr float m12R = -4;
			constexpr float m22R = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<float>(m00R, m10R, m20R, m01R, m11R, m21R, m02R, m12R, m22R);
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<float>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Matrix3x3<float> scaled = PonyBase::Math::Scale(matrixL, matrixR);
			Assert::AreEqual(m00L * m00R, scaled.M00());
			Assert::AreEqual(m10L * m10R, scaled.M10());
			Assert::AreEqual(m20L * m20R, scaled.M20());
			Assert::AreEqual(m01L * m01R, scaled.M01());
			Assert::AreEqual(m11L * m11R, scaled.M11());
			Assert::AreEqual(m21L * m21R, scaled.M21());
			Assert::AreEqual(m02L * m02R, scaled.M02());
			Assert::AreEqual(m12L * m12R, scaled.M12());
			Assert::AreEqual(m22L * m22R, scaled.M22());
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float m00 = 1;
			constexpr float m10 = 3;
			constexpr float m20 = 2;
			constexpr float m01 = 4;
			constexpr float m11 = 6;
			constexpr float m21 = 5;
			constexpr float m02 = 8;
			constexpr float m12 = -4;
			constexpr float m22 = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<float>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			PonyBase::Math::Matrix3x3<float> matrixL = matrixR;
			for (std::size_t i = 0; i < PonyBase::Math::Matrix3x3<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual(matrixL, matrixR));
				matrixL.Span()[i] = std::nextafter(matrixL.Span()[i], 0.f);
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual(matrixL, matrixR));
				matrixL.Span()[i] += 1;
				Assert::IsFalse(PonyBase::Math::AreAlmostEqual(matrixL, matrixR));
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual(matrixL, matrixR, 5.f));
				matrixL.Span()[i] = matrixR.Span()[i];
			}
		}

		TEST_METHOD(AddShortTest)
		{
			constexpr short m00R = 1;
			constexpr short m10R = 3;
			constexpr short m20R = 2;
			constexpr short m01R = 4;
			constexpr short m11R = 6;
			constexpr short m21R = 5;
			constexpr short m02R = 8;
			constexpr short m12R = -4;
			constexpr short m22R = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<short>(m00R, m10R, m20R, m01R, m11R, m21R, m02R, m12R, m22R);
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<short>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Matrix3x3<short> sum = matrixL + matrixR;
			Assert::AreEqual(static_cast<short>(m00L + m00R), sum.M00());
			Assert::AreEqual(static_cast<short>(m10L + m10R), sum.M10());
			Assert::AreEqual(static_cast<short>(m20L + m20R), sum.M20());
			Assert::AreEqual(static_cast<short>(m01L + m01R), sum.M01());
			Assert::AreEqual(static_cast<short>(m11L + m11R), sum.M11());
			Assert::AreEqual(static_cast<short>(m21L + m21R), sum.M21());
			Assert::AreEqual(static_cast<short>(m02L + m02R), sum.M02());
			Assert::AreEqual(static_cast<short>(m12L + m12R), sum.M12());
			Assert::AreEqual(static_cast<short>(m22L + m22R), sum.M22());
		}

		TEST_METHOD(AddFloatTest)
		{
			constexpr float m00R = 1;
			constexpr float m10R = 3;
			constexpr float m20R = 2;
			constexpr float m01R = 4;
			constexpr float m11R = 6;
			constexpr float m21R = 5;
			constexpr float m02R = 8;
			constexpr float m12R = -4;
			constexpr float m22R = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<float>(m00R, m10R, m20R, m01R, m11R, m21R, m02R, m12R, m22R);
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<float>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Matrix3x3<float> sum = matrixL + matrixR;
			Assert::AreEqual(m00L + m00R, sum.M00());
			Assert::AreEqual(m10L + m10R, sum.M10());
			Assert::AreEqual(m20L + m20R, sum.M20());
			Assert::AreEqual(m01L + m01R, sum.M01());
			Assert::AreEqual(m11L + m11R, sum.M11());
			Assert::AreEqual(m21L + m21R, sum.M21());
			Assert::AreEqual(m02L + m02R, sum.M02());
			Assert::AreEqual(m12L + m12R, sum.M12());
			Assert::AreEqual(m22L + m22R, sum.M22());
		}

		TEST_METHOD(NegateShortTest)
		{
			constexpr short m00R = 1;
			constexpr short m10R = 3;
			constexpr short m20R = 2;
			constexpr short m01R = 4;
			constexpr short m11R = 6;
			constexpr short m21R = 5;
			constexpr short m02R = 8;
			constexpr short m12R = -4;
			constexpr short m22R = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<short>(m00R, m10R, m20R, m01R, m11R, m21R, m02R, m12R, m22R);
			PonyBase::Math::Matrix3x3<short> negated = -matrixR;
			Assert::AreEqual(static_cast<short>(-m00R), negated.M00());
			Assert::AreEqual(static_cast<short>(-m10R), negated.M10());
			Assert::AreEqual(static_cast<short>(-m20R), negated.M20());
			Assert::AreEqual(static_cast<short>(-m01R), negated.M01());
			Assert::AreEqual(static_cast<short>(-m11R), negated.M11());
			Assert::AreEqual(static_cast<short>(-m21R), negated.M21());
			Assert::AreEqual(static_cast<short>(-m02R), negated.M02());
			Assert::AreEqual(static_cast<short>(-m12R), negated.M12());
			Assert::AreEqual(static_cast<short>(-m22R), negated.M22());
		}

		TEST_METHOD(NegateFloatTest)
		{
			constexpr float m00R = 1;
			constexpr float m10R = 3;
			constexpr float m20R = 2;
			constexpr float m01R = 4;
			constexpr float m11R = 6;
			constexpr float m21R = 5;
			constexpr float m02R = 8;
			constexpr float m12R = -4;
			constexpr float m22R = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<float>(m00R, m10R, m20R, m01R, m11R, m21R, m02R, m12R, m22R);
			PonyBase::Math::Matrix3x3<float> negated = -matrixR;
			Assert::AreEqual(-m00R, negated.M00());
			Assert::AreEqual(-m10R, negated.M10());
			Assert::AreEqual(-m20R, negated.M20());
			Assert::AreEqual(-m01R, negated.M01());
			Assert::AreEqual(-m11R, negated.M11());
			Assert::AreEqual(-m21R, negated.M21());
			Assert::AreEqual(-m02R, negated.M02());
			Assert::AreEqual(-m12R, negated.M12());
			Assert::AreEqual(-m22R, negated.M22());
		}

		TEST_METHOD(SubtractShortTest)
		{
			constexpr short m00R = 1;
			constexpr short m10R = 3;
			constexpr short m20R = 2;
			constexpr short m01R = 4;
			constexpr short m11R = 6;
			constexpr short m21R = 5;
			constexpr short m02R = 8;
			constexpr short m12R = -4;
			constexpr short m22R = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<short>(m00R, m10R, m20R, m01R, m11R, m21R, m02R, m12R, m22R);
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<short>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Matrix3x3<short> sum = matrixL - matrixR;
			Assert::AreEqual(static_cast<short>(m00L - m00R), sum.M00());
			Assert::AreEqual(static_cast<short>(m10L - m10R), sum.M10());
			Assert::AreEqual(static_cast<short>(m20L - m20R), sum.M20());
			Assert::AreEqual(static_cast<short>(m01L - m01R), sum.M01());
			Assert::AreEqual(static_cast<short>(m11L - m11R), sum.M11());
			Assert::AreEqual(static_cast<short>(m21L - m21R), sum.M21());
			Assert::AreEqual(static_cast<short>(m02L - m02R), sum.M02());
			Assert::AreEqual(static_cast<short>(m12L - m12R), sum.M12());
			Assert::AreEqual(static_cast<short>(m22L - m22R), sum.M22());
		}

		TEST_METHOD(SubtractFloatTest)
		{
			constexpr float m00R = 1;
			constexpr float m10R = 3;
			constexpr float m20R = 2;
			constexpr float m01R = 4;
			constexpr float m11R = 6;
			constexpr float m21R = 5;
			constexpr float m02R = 8;
			constexpr float m12R = -4;
			constexpr float m22R = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<float>(m00R, m10R, m20R, m01R, m11R, m21R, m02R, m12R, m22R);
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<float>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Matrix3x3<float> sum = matrixL - matrixR;
			Assert::AreEqual(m00L - m00R, sum.M00());
			Assert::AreEqual(m10L - m10R, sum.M10());
			Assert::AreEqual(m20L - m20R, sum.M20());
			Assert::AreEqual(m01L - m01R, sum.M01());
			Assert::AreEqual(m11L - m11R, sum.M11());
			Assert::AreEqual(m21L - m21R, sum.M21());
			Assert::AreEqual(m02L - m02R, sum.M02());
			Assert::AreEqual(m12L - m12R, sum.M12());
			Assert::AreEqual(m22L - m22R, sum.M22());
		}

		TEST_METHOD(MultiplyNumberShortTest)
		{
			constexpr short multiplierI = 2;
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<short>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Matrix3x3<short> product = matrixL * multiplierI;
			Assert::AreEqual(static_cast<short>(m00L * multiplierI), product.M00());
			Assert::AreEqual(static_cast<short>(m10L * multiplierI), product.M10());
			Assert::AreEqual(static_cast<short>(m20L * multiplierI), product.M20());
			Assert::AreEqual(static_cast<short>(m01L * multiplierI), product.M01());
			Assert::AreEqual(static_cast<short>(m11L * multiplierI), product.M11());
			Assert::AreEqual(static_cast<short>(m21L * multiplierI), product.M21());
			Assert::AreEqual(static_cast<short>(m02L * multiplierI), product.M02());
			Assert::AreEqual(static_cast<short>(m12L * multiplierI), product.M12());
			Assert::AreEqual(static_cast<short>(m22L * multiplierI), product.M22());
			Assert::IsTrue(multiplierI * matrixL == matrixL * multiplierI);

			constexpr float multiplierF = 3;
			product = matrixL * multiplierF;
			Assert::AreEqual(static_cast<short>(m00L * multiplierF), product.M00());
			Assert::AreEqual(static_cast<short>(m10L * multiplierF), product.M10());
			Assert::AreEqual(static_cast<short>(m20L * multiplierF), product.M20());
			Assert::AreEqual(static_cast<short>(m01L * multiplierF), product.M01());
			Assert::AreEqual(static_cast<short>(m11L * multiplierF), product.M11());
			Assert::AreEqual(static_cast<short>(m21L * multiplierF), product.M21());
			Assert::AreEqual(static_cast<short>(m02L * multiplierF), product.M02());
			Assert::AreEqual(static_cast<short>(m12L * multiplierF), product.M12());
			Assert::AreEqual(static_cast<short>(m22L * multiplierF), product.M22());
			Assert::IsTrue(multiplierF * matrixL == matrixL * multiplierF);
		}

		TEST_METHOD(MultiplyNumberFloatTest)
		{
			constexpr float multiplier = 3;
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<float>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Matrix3x3<float> product = matrixL * multiplier;
			Assert::AreEqual(m00L * multiplier, product.M00());
			Assert::AreEqual(m10L * multiplier, product.M10());
			Assert::AreEqual(m20L * multiplier, product.M20());
			Assert::AreEqual(m01L * multiplier, product.M01());
			Assert::AreEqual(m11L * multiplier, product.M11());
			Assert::AreEqual(m21L * multiplier, product.M21());
			Assert::AreEqual(m02L * multiplier, product.M02());
			Assert::AreEqual(m12L * multiplier, product.M12());
			Assert::AreEqual(m22L * multiplier, product.M22());
			Assert::IsTrue(multiplier * matrixL == matrixL * multiplier);
		}

		TEST_METHOD(MultiplyMatrixShortTest)
		{
			constexpr short m00R = 1;
			constexpr short m10R = 3;
			constexpr short m20R = 2;
			constexpr short m01R = 4;
			constexpr short m11R = 6;
			constexpr short m21R = 5;
			constexpr short m02R = 8;
			constexpr short m12R = -4;
			constexpr short m22R = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<short>(m00R, m10R, m20R, m01R, m11R, m21R, m02R, m12R, m22R);
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<short>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Matrix3x3<short> product = matrixL * matrixR;
			Assert::AreEqual(short{5}, product.M00());
			Assert::AreEqual(short{7}, product.M10());
			Assert::AreEqual(short{12}, product.M20());
			Assert::AreEqual(short{11}, product.M01());
			Assert::AreEqual(short{16}, product.M11());
			Assert::AreEqual(short{27}, product.M21());
			Assert::AreEqual(short{23}, product.M02());
			Assert::AreEqual(short{-30}, product.M12());
			Assert::AreEqual(short{33}, product.M22());
		}

		TEST_METHOD(MultiplyMatrixFloatTest)
		{
			constexpr float m00R = 1;
			constexpr float m10R = 3;
			constexpr float m20R = 2;
			constexpr float m01R = 4;
			constexpr float m11R = 6;
			constexpr float m21R = 5;
			constexpr float m02R = 8;
			constexpr float m12R = -4;
			constexpr float m22R = -3;
			constexpr auto matrixR = PonyBase::Math::Matrix3x3<float>(m00R, m10R, m20R, m01R, m11R, m21R, m02R, m12R, m22R);
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<float>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Matrix3x3<float> product = matrixL * matrixR;
			Assert::AreEqual(5.f, product.M00());
			Assert::AreEqual(7.f, product.M10());
			Assert::AreEqual(12.f, product.M20());
			Assert::AreEqual(11.f, product.M01());
			Assert::AreEqual(16.f, product.M11());
			Assert::AreEqual(27.f, product.M21());
			Assert::AreEqual(23.f, product.M02());
			Assert::AreEqual(-30.f, product.M12());
			Assert::AreEqual(33.f, product.M22());
		}

		TEST_METHOD(MultiplyVectorShortTest)
		{
			constexpr short m00R = 5;
			constexpr short m10R = -7;
			constexpr short m20R = 2;
			constexpr auto vectorR = PonyBase::Math::Vector3<short>(m00R, m10R, m20R);
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<short>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Vector3<short> product = matrixL * vectorR;
			Assert::AreEqual(short{-23}, product.X());
			Assert::AreEqual(short{9}, product.Y());
			Assert::AreEqual(short{-38}, product.Z());
		}

		TEST_METHOD(MultiplyVectorFloatTest)
		{
			constexpr float m00R = 5;
			constexpr float m10R = -7;
			constexpr float m20R = 2;
			constexpr auto vectorR = PonyBase::Math::Vector3<float>(m00R, m10R, m20R);
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<float>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Vector3<float> product = matrixL * vectorR;
			Assert::AreEqual(-23.f, product.X());
			Assert::AreEqual(9.f, product.Y());
			Assert::AreEqual(-38.f, product.Z());
		}

		TEST_METHOD(DivideShortTest)
		{
			constexpr short divisorI = 2;
			constexpr short m00L = 3;
			constexpr short m10L = -2;
			constexpr short m20L = 5;
			constexpr short m01L = 4;
			constexpr short m11L = -1;
			constexpr short m21L = 7;
			constexpr short m02L = -5;
			constexpr short m12L = 6;
			constexpr short m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<short>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Matrix3x3<short> product = matrixL / divisorI;
			Assert::AreEqual(static_cast<short>(m00L / divisorI), product.M00());
			Assert::AreEqual(static_cast<short>(m10L / divisorI), product.M10());
			Assert::AreEqual(static_cast<short>(m20L / divisorI), product.M20());
			Assert::AreEqual(static_cast<short>(m01L / divisorI), product.M01());
			Assert::AreEqual(static_cast<short>(m11L / divisorI), product.M11());
			Assert::AreEqual(static_cast<short>(m21L / divisorI), product.M21());
			Assert::AreEqual(static_cast<short>(m02L / divisorI), product.M02());
			Assert::AreEqual(static_cast<short>(m12L / divisorI), product.M12());
			Assert::AreEqual(static_cast<short>(m22L / divisorI), product.M22());

			constexpr float divisorF = 3;
			product = matrixL / divisorF;
			Assert::AreEqual(static_cast<short>(m00L / divisorF), product.M00());
			Assert::AreEqual(static_cast<short>(m10L / divisorF), product.M10());
			Assert::AreEqual(static_cast<short>(m20L / divisorF), product.M20());
			Assert::AreEqual(static_cast<short>(m01L / divisorF), product.M01());
			Assert::AreEqual(static_cast<short>(m11L / divisorF), product.M11());
			Assert::AreEqual(static_cast<short>(m21L / divisorF), product.M21());
			Assert::AreEqual(static_cast<short>(m02L / divisorF), product.M02());
			Assert::AreEqual(static_cast<short>(m12L / divisorF), product.M12());
			Assert::AreEqual(static_cast<short>(m22L / divisorF), product.M22());
		}

		TEST_METHOD(DivideFloatTest)
		{
			constexpr float divisor = 2;
			constexpr float m00L = 3;
			constexpr float m10L = -2;
			constexpr float m20L = 5;
			constexpr float m01L = 4;
			constexpr float m11L = -1;
			constexpr float m21L = 7;
			constexpr float m02L = -5;
			constexpr float m12L = 6;
			constexpr float m22L = -7;
			constexpr auto matrixL = PonyBase::Math::Matrix3x3<float>(m00L, m10L, m20L, m01L, m11L, m21L, m02L, m12L, m22L);
			PonyBase::Math::Matrix3x3<float> product = matrixL / divisor;
			Assert::AreEqual(m00L / divisor, product.M00());
			Assert::AreEqual(m10L / divisor, product.M10());
			Assert::AreEqual(m20L / divisor, product.M20());
			Assert::AreEqual(m01L / divisor, product.M01());
			Assert::AreEqual(m11L / divisor, product.M11());
			Assert::AreEqual(m21L / divisor, product.M21());
			Assert::AreEqual(m02L / divisor, product.M02());
			Assert::AreEqual(m12L / divisor, product.M12());
			Assert::AreEqual(m22L / divisor, product.M22());
		}

		static constexpr PonyBase::Math::Matrix3x3<int> MatrixConstexpr()
		{
			[[maybe_unused]] auto matrix = PonyBase::Math::Matrix3x3<int>();
			PonyBase::Math::Matrix3x3<int> movedMatrix = std::move(matrix);

			movedMatrix.M00() += 1;
			movedMatrix.M10() -= 2;
			movedMatrix.M20() -= 3;
			movedMatrix.M01() *= 2;
			movedMatrix.M11() = 6;
			movedMatrix.M21() = 9;
			movedMatrix.M02() *= 6;
			movedMatrix.M12() = 7;
			movedMatrix.M22() = 1;
			movedMatrix.Component(2) += 2;
			movedMatrix.Span()[0] *= 3;
			movedMatrix.Span(1)[0] /= 3;

			[[maybe_unused]] constexpr auto constMatrix = PonyBase::Math::Matrix3x3<int>(4, 3, 9, 1, -8, -5, -4, 6, 7);

			movedMatrix.Row(0, PonyBase::Math::Vector3<int>(3, 6, 9));
			movedMatrix.Column(1, PonyBase::Math::Vector3<int>(3, 6, 9));
			movedMatrix.Diagonal(PonyBase::Math::Vector3<int>(3, 6, 9));
			movedMatrix.CounterDiagonal(PonyBase::Math::Vector3<int>(3, 6, 9));

			movedMatrix.Set(4, 6, 1, 0, 8, -4, -2, -1, 7);
			movedMatrix.Set(PonyBase::Math::Vector3<int>(4, 6, 1), PonyBase::Math::Vector3<int>(9, 4, 1), PonyBase::Math::Vector3<int>(9, 4, 1));
			movedMatrix.Set(std::array<int, 9>{4, 5, 6, 6, 1, 6, -4, -6, -7});

			movedMatrix.Scale(constMatrix);

			movedMatrix[1][1] = 5;
			movedMatrix[1] = PonyBase::Math::Vector3<int>(9, 4, 8);

			[[maybe_unused]] auto copyAssigned = PonyBase::Math::Matrix3x3<int>();
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
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> identity = PonyBase::Math::Matrix3x3<int>::Predefined::Identity;
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> zero = PonyBase::Math::Matrix3x3<int>::Predefined::Zero;

			[[maybe_unused]] constexpr auto defaultMatrix = PonyBase::Math::Matrix3x3<int>();
			[[maybe_unused]] constexpr auto matrix = PonyBase::Math::Matrix3x3<int>(0, 2, 3, 4, -1, -8, 1, 5, 0);
			[[maybe_unused]] constexpr auto columnMatrix = PonyBase::Math::Matrix3x3<int>(PonyBase::Math::Vector3<int>(4, 6, -1), PonyBase::Math::Vector3<int>(9, 4, -1), PonyBase::Math::Vector3<int>(9, 4, -1));
			[[maybe_unused]] constexpr auto arrayMatrix = PonyBase::Math::Matrix3x3<int>(std::array<int, 9>{4, 5, 6, 6, 7, 1, -5, -8, -1});
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> copiedMatrix = matrix;
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> movedMatrix = MatrixConstexpr();

			[[maybe_unused]] constexpr int m00 = matrix.M00();
			[[maybe_unused]] constexpr int m10 = matrix.M10();
			[[maybe_unused]] constexpr int m20 = matrix.M20();
			[[maybe_unused]] constexpr int m01 = matrix.M01();
			[[maybe_unused]] constexpr int m11 = matrix.M11();
			[[maybe_unused]] constexpr int m21 = matrix.M21();
			[[maybe_unused]] constexpr int m02 = matrix.M02();
			[[maybe_unused]] constexpr int m12 = matrix.M12();
			[[maybe_unused]] constexpr int m22 = matrix.M22();
			[[maybe_unused]] constexpr auto component = matrix.Component(2);

			[[maybe_unused]] constexpr auto spanElement = matrix.Span()[0];
			[[maybe_unused]] constexpr auto columnSpanElement = matrix.Span(1)[0];

			[[maybe_unused]] constexpr PonyBase::Math::Vector3<int> row = matrix.Row(1);
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<int> column = matrix.Column(0);
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<int> diagonal = matrix.Diagonal();
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<int> counterDiagonal = matrix.CounterDiagonal();

			[[maybe_unused]] constexpr int trace = matrix.Trace();
			[[maybe_unused]] constexpr int determinant = matrix.Determinant();
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> adjugate = matrix.Adjugate();
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> transpose = matrix.Transpose();
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<float> inverse = PonyBase::Math::Matrix3x3<float>(0, 2, 3, 4, -1, -8, 1, 5, 0).Inverse();

			[[maybe_unused]] constexpr bool isZero = matrix.IsZero();
			[[maybe_unused]] constexpr bool isAlmostZero = PonyBase::Math::Matrix3x3<float>::Predefined::Zero.IsAlmostZero();
			[[maybe_unused]] constexpr bool isIdentity = matrix.IsIdentity();
			[[maybe_unused]] constexpr bool isAlmostIdentity = PonyBase::Math::Matrix3x3<float>::Predefined::Identity.IsAlmostIdentity();

			[[maybe_unused]] constexpr auto floatMatrix = static_cast<PonyBase::Math::Matrix3x3<float>>(matrix);

			[[maybe_unused]] constexpr int m10A = matrix[1][0];
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<int> columnV = matrix[0];

			[[maybe_unused]] constexpr bool equal = matrix == defaultMatrix;
			[[maybe_unused]] constexpr bool notEqual = matrix != defaultMatrix;

			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> scaled = PonyBase::Math::Scale(matrix, columnMatrix);
			[[maybe_unused]] constexpr bool areAlmostEqual = PonyBase::Math::AreAlmostEqual(PonyBase::Math::Matrix3x3<float>(0, 2, 3, 4, -1, -8, 1, 5, 0), PonyBase::Math::Matrix3x3<float>(0, 2, 3, 4, -1, -8, 1, 5, 0));

			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> sum = matrix + columnMatrix;
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> negated = -matrix;
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> difference = matrix - columnMatrix;
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> productNumR = matrix * 3;
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> productNumL = 3 * matrix;
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> productNumFR = matrix * 3.f;
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> productNumFL = 3.f * matrix;
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> product = matrix * columnMatrix;
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<int> productV = matrix * PonyBase::Math::Vector3<int>(4, 6, 1);
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> quotient = matrix / 3;
			[[maybe_unused]] constexpr PonyBase::Math::Matrix3x3<int> quotientF = matrix / 3.f;
		}
	};
}
