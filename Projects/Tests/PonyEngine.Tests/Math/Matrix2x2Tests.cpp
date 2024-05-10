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
	TEST_CLASS(Matrix2x2Tests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyEngine::Math::Matrix2x2<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix2x2<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyEngine::Math::Matrix2x2<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix2x2<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyEngine::Math::Matrix2x2<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix2x2<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix2x2<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix2x2<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyEngine::Math::Matrix2x2<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Matrix2x2<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Matrix2x2<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Matrix2x2<double>::ComputationalType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{2}, PonyEngine::Math::Matrix2x2<float>::Dimension);
			Assert::AreEqual(std::size_t{4}, PonyEngine::Math::Matrix2x2<float>::ComponentCount);

			Assert::AreEqual(std::size_t{2}, PonyEngine::Math::Matrix2x2<short>::Dimension);
			Assert::AreEqual(std::size_t{4}, PonyEngine::Math::Matrix2x2<short>::ComponentCount);
		}

		TEST_METHOD(RowToVector2ShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);

			const PonyEngine::Math::Vector2<short> row0 = matrix[0];
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());

			const PonyEngine::Math::Vector2<short> row1 = matrix[1];
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
		}

		TEST_METHOD(RowToVector2FloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);

			const PonyEngine::Math::Vector2<float> row0 = matrix[0];
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());

			const PonyEngine::Math::Vector2<float> row1 = matrix[1];
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
		}

		TEST_METHOD(AccessOperatorReadShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);

			Assert::AreEqual(m00, matrix[0][0]);
			Assert::AreEqual(m01, matrix[0][1]);
			Assert::AreEqual(m10, matrix[1][0]);
			Assert::AreEqual(m11, matrix[1][1]);
		}

		TEST_METHOD(AccessOperatorReadFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);

			Assert::AreEqual(m00, matrix[0][0]);
			Assert::AreEqual(m01, matrix[0][1]);
			Assert::AreEqual(m10, matrix[1][0]);
			Assert::AreEqual(m11, matrix[1][1]);
		}

		TEST_METHOD(AccessOperatorWriteShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);

			constexpr short m00New = 20;
			constexpr short m10New = 30;
			constexpr short m01New = -40;
			constexpr short m11New = -50;
			matrix[0][0] = m00New;
			matrix[0][1] = m01New;
			matrix[1][0] = m10New;
			matrix[1][1] = m11New;

			Assert::AreEqual(m00New, matrix[0][0]);
			Assert::AreEqual(m01New, matrix[0][1]);
			Assert::AreEqual(m10New, matrix[1][0]);
			Assert::AreEqual(m11New, matrix[1][1]);
		}

		TEST_METHOD(AccessOperatorWriteFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);

			constexpr float m00New = 20;
			constexpr float m10New = 30;
			constexpr float m01New = -40;
			constexpr float m11New = -50;
			matrix[0][0] = m00New;
			matrix[0][1] = m01New;
			matrix[1][0] = m10New;
			matrix[1][1] = m11New;

			Assert::AreEqual(m00New, matrix[0][0]);
			Assert::AreEqual(m01New, matrix[0][1]);
			Assert::AreEqual(m10New, matrix[1][0]);
			Assert::AreEqual(m11New, matrix[1][1]);
		}

		TEST_METHOD(Vector2ToRowShortTest)
		{
			constexpr short m00 = 10;
			constexpr short m10 = -15;
			constexpr short m01 = 5;
			constexpr short m11 = -20;
			auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);

			constexpr short m00New = 20;
			constexpr short m10New = 30;
			constexpr short m01New = -40;
			constexpr short m11New = -50;
			matrix[0] = PonyEngine::Math::Vector2<short>(m00New, m01New);
			matrix[1] = PonyEngine::Math::Vector2<short>(m10New, m11New);

			Assert::AreEqual(m00New, matrix[0][0]);
			Assert::AreEqual(m01New, matrix[0][1]);
			Assert::AreEqual(m10New, matrix[1][0]);
			Assert::AreEqual(m11New, matrix[1][1]);
		}

		TEST_METHOD(Vector2ToRowFloatTest)
		{
			constexpr float m00 = 10;
			constexpr float m10 = -15;
			constexpr float m01 = 5;
			constexpr float m11 = -20;
			auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);

			constexpr float m00New = 20;
			constexpr float m10New = 30;
			constexpr float m01New = -40;
			constexpr float m11New = -50;
			matrix[0] = PonyEngine::Math::Vector2<float>(m00New, m01New);
			matrix[1] = PonyEngine::Math::Vector2<float>(m10New, m11New);

			Assert::AreEqual(m00New, matrix[0][0]);
			Assert::AreEqual(m01New, matrix[0][1]);
			Assert::AreEqual(m10New, matrix[1][0]);
			Assert::AreEqual(m11New, matrix[1][1]);
		}

		TEST_METHOD(DefaultConstructorShortTest)
		{
			const auto defaultMatrix = PonyEngine::Math::Matrix2x2<short>();
			Assert::AreEqual(short{}, defaultMatrix.M00());
			Assert::AreEqual(short{}, defaultMatrix.M10());
			Assert::AreEqual(short{}, defaultMatrix.M01());
			Assert::AreEqual(short{}, defaultMatrix.M11());
		}

		TEST_METHOD(DefaultConstructorFloatTest)
		{
			const auto defaultMatrix = PonyEngine::Math::Matrix2x2<float>();
			Assert::AreEqual(float{}, defaultMatrix.M00());
			Assert::AreEqual(float{}, defaultMatrix.M10());
			Assert::AreEqual(float{}, defaultMatrix.M01());
			Assert::AreEqual(float{}, defaultMatrix.M11());
		}

		TEST_METHOD(ConstructorShortTest)
		{
			constexpr short m00 = 4;
			constexpr short m10 = -3;
			constexpr short m01 = 6;
			constexpr short m11 = 5;
			const auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(ConstructorFloatTest)
		{
			constexpr float m00 = 4;
			constexpr float m10 = -3;
			constexpr float m01 = 6;
			constexpr float m11 = 5;
			const auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(ConstructorColumnShortTest)
		{
			constexpr short m00 = 4;
			constexpr short m10 = -3;
			constexpr short m01 = 6;
			constexpr short m11 = 5;
			constexpr auto column0 = PonyEngine::Math::Vector2<short>(m00, m10);
			constexpr auto column1 = PonyEngine::Math::Vector2<short>(m01, m11);
			const auto matrix = PonyEngine::Math::Matrix2x2<short>(column0, column1);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(ConstructorColumnFloatTest)
		{
			constexpr float m00 = 4;
			constexpr float m10 = -3;
			constexpr float m01 = 6;
			constexpr float m11 = 5;
			constexpr auto column0 = PonyEngine::Math::Vector2<float>(m00, m10);
			constexpr auto column1 = PonyEngine::Math::Vector2<float>(m01, m11);
			const auto matrix = PonyEngine::Math::Matrix2x2<float>(column0, column1);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(ConstructorPointerShortTest)
		{
			constexpr short m00 = 4;
			constexpr short m10 = -3;
			constexpr short m01 = 6;
			constexpr short m11 = 5;
			constexpr std::array<short, 4> array{ m00, m10, m01, m11 };
			const auto matrix = PonyEngine::Math::Matrix2x2<short>(array.data());
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(ConstructorPointerFloatTest)
		{
			constexpr float m00 = 4;
			constexpr float m10 = -3;
			constexpr float m01 = 6;
			constexpr float m11 = 5;
			constexpr std::array<float, 4> array{ m00, m10, m01, m11 };
			const auto matrix = PonyEngine::Math::Matrix2x2<float>(array.data());
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(ConstructorCopyShortTest)
		{
			constexpr short m00 = 4;
			constexpr short m10 = -3;
			constexpr short m01 = 6;
			constexpr short m11 = 5;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			const auto copiedMatrix = matrix;
			Assert::AreEqual(m00, copiedMatrix.M00());
			Assert::AreEqual(m10, copiedMatrix.M10());
			Assert::AreEqual(m01, copiedMatrix.M01());
			Assert::AreEqual(m11, copiedMatrix.M11());
		}

		TEST_METHOD(ConstructorCopyFloatTest)
		{
			constexpr float m00 = 4;
			constexpr float m10 = -3;
			constexpr float m01 = 6;
			constexpr float m11 = 5;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			const auto copiedMatrix = matrix;
			Assert::AreEqual(m00, copiedMatrix.M00());
			Assert::AreEqual(m10, copiedMatrix.M10());
			Assert::AreEqual(m01, copiedMatrix.M01());
			Assert::AreEqual(m11, copiedMatrix.M11());
		}

		TEST_METHOD(ConstructorMoveShortTest)
		{
			constexpr short m00 = 4;
			constexpr short m10 = -3;
			constexpr short m01 = 6;
			constexpr short m11 = 5;
			auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			const auto movedMatrix = std::move(matrix);
			Assert::AreEqual(m00, movedMatrix.M00());
			Assert::AreEqual(m10, movedMatrix.M10());
			Assert::AreEqual(m01, movedMatrix.M01());
			Assert::AreEqual(m11, movedMatrix.M11());
		}

		TEST_METHOD(ConstructorMoveFloatTest)
		{
			constexpr float m00 = 4;
			constexpr float m10 = -3;
			constexpr float m01 = 6;
			constexpr float m11 = 5;
			auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			const auto movedMatrix = std::move(matrix);
			Assert::AreEqual(m00, movedMatrix.M00());
			Assert::AreEqual(m10, movedMatrix.M10());
			Assert::AreEqual(m01, movedMatrix.M01());
			Assert::AreEqual(m11, movedMatrix.M11());
		}

		TEST_METHOD(ComponentAccessShortTest)
		{
			constexpr short m00 = 4;
			constexpr short m10 = -3;
			constexpr short m01 = 6;
			constexpr short m11 = 5;

			auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());

			constexpr auto matrixC = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
		}

		TEST_METHOD(ComponentAccessFloatTest)
		{
			constexpr float m00 = 4;
			constexpr float m10 = -3;
			constexpr float m01 = 6;
			constexpr float m11 = 5;

			auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());

			constexpr auto matrixC = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
		}

		TEST_METHOD(DataShortTest)
		{
			constexpr short m00 = 4;
			constexpr short m10 = -3;
			constexpr short m01 = 6;
			constexpr short m11 = 5;
			auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			Assert::AreEqual(m00, matrix.Data()[0]);
			Assert::AreEqual(m10, matrix.Data()[1]);
			Assert::AreEqual(m01, matrix.Data()[2]);
			Assert::AreEqual(m11, matrix.Data()[3]);
			Assert::AreEqual(m00, matrix.Data(0)[0]);
			Assert::AreEqual(m10, matrix.Data(0)[1]);
			Assert::AreEqual(m01, matrix.Data(1)[0]);
			Assert::AreEqual(m11, matrix.Data(1)[1]);

			constexpr auto matrixC = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			Assert::AreEqual(m00, matrixC.Data()[0]);
			Assert::AreEqual(m10, matrixC.Data()[1]);
			Assert::AreEqual(m01, matrixC.Data()[2]);
			Assert::AreEqual(m11, matrixC.Data()[3]);
			Assert::AreEqual(m00, matrixC.Data(0)[0]);
			Assert::AreEqual(m10, matrixC.Data(0)[1]);
			Assert::AreEqual(m01, matrixC.Data(1)[0]);
			Assert::AreEqual(m11, matrixC.Data(1)[1]);
		}

		TEST_METHOD(DataFloatTest)
		{
			constexpr float m00 = 4;
			constexpr float m10 = -3;
			constexpr float m01 = 6;
			constexpr float m11 = 5;
			auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			Assert::AreEqual(m00, matrix.Data()[0]);
			Assert::AreEqual(m10, matrix.Data()[1]);
			Assert::AreEqual(m01, matrix.Data()[2]);
			Assert::AreEqual(m11, matrix.Data()[3]);
			Assert::AreEqual(m00, matrix.Data(0)[0]);
			Assert::AreEqual(m10, matrix.Data(0)[1]);
			Assert::AreEqual(m01, matrix.Data(1)[0]);
			Assert::AreEqual(m11, matrix.Data(1)[1]);

			constexpr auto matrixC = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			Assert::AreEqual(m00, matrixC.Data()[0]);
			Assert::AreEqual(m10, matrixC.Data()[1]);
			Assert::AreEqual(m01, matrixC.Data()[2]);
			Assert::AreEqual(m11, matrixC.Data()[3]);
			Assert::AreEqual(m00, matrixC.Data(0)[0]);
			Assert::AreEqual(m10, matrixC.Data(0)[1]);
			Assert::AreEqual(m01, matrixC.Data(1)[0]);
			Assert::AreEqual(m11, matrixC.Data(1)[1]);
		}

		TEST_METHOD(GetRowShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			const auto row0 = matrix.GetRow(0);
			const auto row1 = matrix.GetRow(1);
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
		}

		TEST_METHOD(GetRowFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			const auto row0 = matrix.GetRow(0);
			const auto row1 = matrix.GetRow(1);
			Assert::AreEqual(m00, row0.X());
			Assert::AreEqual(m01, row0.Y());
			Assert::AreEqual(m10, row1.X());
			Assert::AreEqual(m11, row1.Y());
		}

		TEST_METHOD(SetRowShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			auto matrix = PonyEngine::Math::Matrix2x2<short>();
			constexpr auto row0 = PonyEngine::Math::Vector2<short>(m00, m01);
			constexpr auto row1 = PonyEngine::Math::Vector2<short>(m10, m11);
			matrix.SetRow(0, row0);
			matrix.SetRow(1, row1);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(SetRowFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			auto matrix = PonyEngine::Math::Matrix2x2<float>();
			constexpr auto row0 = PonyEngine::Math::Vector2<float>(m00, m01);
			constexpr auto row1 = PonyEngine::Math::Vector2<float>(m10, m11);
			matrix.SetRow(0, row0);
			matrix.SetRow(1, row1);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(GetColumnShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			const auto column0 = matrix.GetColumn(0);
			const auto column1 = matrix.GetColumn(1);
			Assert::AreEqual(m00, column0.X());
			Assert::AreEqual(m10, column0.Y());
			Assert::AreEqual(m01, column1.X());
			Assert::AreEqual(m11, column1.Y());
		}

		TEST_METHOD(GetColumnFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			const auto column0 = matrix.GetColumn(0);
			const auto column1 = matrix.GetColumn(1);
			Assert::AreEqual(m00, column0.X());
			Assert::AreEqual(m10, column0.Y());
			Assert::AreEqual(m01, column1.X());
			Assert::AreEqual(m11, column1.Y());
		}

		TEST_METHOD(SetColumnShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			auto matrix = PonyEngine::Math::Matrix2x2<short>();
			constexpr auto column0 = PonyEngine::Math::Vector2<short>(m00, m10);
			constexpr auto column1 = PonyEngine::Math::Vector2<short>(m01, m11);
			matrix.SetColumn(0, column0);
			matrix.SetColumn(1, column1);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(SetColumnFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			auto matrix = PonyEngine::Math::Matrix2x2<float>();
			constexpr auto column0 = PonyEngine::Math::Vector2<float>(m00, m10);
			constexpr auto column1 = PonyEngine::Math::Vector2<float>(m01, m11);
			matrix.SetColumn(0, column0);
			matrix.SetColumn(1, column1);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(GetDiagonalShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			const auto diagonal = matrix.GetDiagonal();
			Assert::AreEqual(m00, diagonal.X());
			Assert::AreEqual(m11, diagonal.Y());
		}

		TEST_METHOD(GetDiagonalFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			const auto diagonal = matrix.GetDiagonal();
			Assert::AreEqual(m00, diagonal.X());
			Assert::AreEqual(m11, diagonal.Y());
		}

		TEST_METHOD(SetDiagonalShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m11 = -2;
			auto matrix = PonyEngine::Math::Matrix2x2<short>();
			constexpr auto diagonal = PonyEngine::Math::Vector2<short>(m00, m11);
			matrix.SetDiagonal(diagonal);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(short{}, matrix.M10());
			Assert::AreEqual(short{}, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(SetDiagonalFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m11 = -2;
			auto matrix = PonyEngine::Math::Matrix2x2<float>();
			constexpr auto diagonal = PonyEngine::Math::Vector2<float>(m00, m11);
			matrix.SetDiagonal(diagonal);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(float{}, matrix.M10());
			Assert::AreEqual(float{}, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(GetCounterDiagonalShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			const auto diagonal = matrix.GetCounterDiagonal();
			Assert::AreEqual(m01, diagonal.X());
			Assert::AreEqual(m10, diagonal.Y());
		}

		TEST_METHOD(GetCounterDiagonalFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			const auto diagonal = matrix.GetCounterDiagonal();
			Assert::AreEqual(m01, diagonal.X());
			Assert::AreEqual(m10, diagonal.Y());
		}

		TEST_METHOD(SetCounterDiagonalShortTest)
		{
			constexpr short m01 = 3;
			constexpr short m10 = -2;
			auto matrix = PonyEngine::Math::Matrix2x2<short>();
			constexpr auto counterDiagonal = PonyEngine::Math::Vector2<short>(m01, m10);
			matrix.SetCounterDiagonal(counterDiagonal);
			Assert::AreEqual(short{}, matrix.M00());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(short{}, matrix.M11());
		}

		TEST_METHOD(SetCounterDiagonalFloatTest)
		{
			constexpr float m01 = 3;
			constexpr float m10 = -2;
			auto matrix = PonyEngine::Math::Matrix2x2<float>();
			constexpr auto counterDiagonal = PonyEngine::Math::Vector2<float>(m01, m10);
			matrix.SetCounterDiagonal(counterDiagonal);
			Assert::AreEqual(float{}, matrix.M00());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(float{}, matrix.M11());
		}

		TEST_METHOD(TraceShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			const short trace = matrix.Trace();
			Assert::AreEqual(short{ 1 }, trace);
		}

		TEST_METHOD(TraceFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			const float trace = matrix.Trace();
			Assert::AreEqual(1.f, trace);
		}

		TEST_METHOD(DeterminantShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			Assert::AreEqual(short{29}, matrix.Determinant());
		}

		TEST_METHOD(DeterminantFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			Assert::AreEqual(29.f, matrix.Determinant());
		}

		TEST_METHOD(AdjugateShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			const auto adjugate = matrix.Adjugate();
			Assert::AreEqual(short{-2}, adjugate.M00());
			Assert::AreEqual(short{7}, adjugate.M10());
			Assert::AreEqual(short{-5}, adjugate.M01());
			Assert::AreEqual(short{3}, adjugate.M11());
		}

		TEST_METHOD(AdjugateFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			const auto adjugate = matrix.Adjugate();
			Assert::AreEqual(-2.f, adjugate.M00());
			Assert::AreEqual(7.f, adjugate.M10());
			Assert::AreEqual(-5.f, adjugate.M01());
			Assert::AreEqual(3.f, adjugate.M11());
		}

		TEST_METHOD(TransposeShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			const auto transpose = matrix.Transpose();
			Assert::AreEqual(m00, transpose.M00());
			Assert::AreEqual(m01, transpose.M10());
			Assert::AreEqual(m10, transpose.M01());
			Assert::AreEqual(m11, transpose.M11());
		}

		TEST_METHOD(TransposeFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			const auto transpose = matrix.Transpose();
			Assert::AreEqual(m00, transpose.M00());
			Assert::AreEqual(m01, transpose.M10());
			Assert::AreEqual(m10, transpose.M01());
			Assert::AreEqual(m11, transpose.M11());
		}

		TEST_METHOD(InverseShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = 5;
			constexpr short m01 = 2;
			constexpr short m11 = 4;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			const auto inverse = matrix.Inverse();
			Assert::AreEqual(short{2}, inverse.M00());
			Assert::AreEqual(short{-2}, inverse.M10());
			Assert::AreEqual(short{-1}, inverse.M01());
			Assert::AreEqual(short{1}, inverse.M11());
		}

		TEST_METHOD(InverseFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = 5;
			constexpr float m01 = 2;
			constexpr float m11 = 4;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			const auto inverse = matrix.Inverse();
			Assert::AreEqual(2.f, inverse.M00());
			Assert::AreEqual(-2.5f, inverse.M10());
			Assert::AreEqual(-1.f, inverse.M01());
			Assert::AreEqual(1.5f, inverse.M11());
		}

		TEST_METHOD(IsFiniteTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix2x2Zero<float>.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Matrix2x2Identity<float>.IsFinite());

			const float nan = std::numeric_limits<float>::quiet_NaN();
			constexpr std::array<float, 4> array{ 3.f, 1.f, -5.f, 7.f };
			auto matrix = PonyEngine::Math::Matrix2x2<float>(array.data());
			Assert::IsTrue(matrix.IsFinite());
			for (std::size_t i = 1; i < PonyEngine::Math::Matrix2x2<float>::ComponentCount; ++i)
			{
				matrix.Data()[i] = nan;
				Assert::IsFalse(matrix.IsFinite());
				matrix.Data()[i] = array[i];
			}

			Assert::IsTrue(PonyEngine::Math::Matrix2x2Zero<short>.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Matrix2x2Identity<short>.IsFinite());
		}

		TEST_METHOD(SetShortTest)
		{
			constexpr short m00 = -10;
			constexpr short m10 = -15;
			constexpr short m01 = 5;
			constexpr short m11 = 20;
			auto matrix = PonyEngine::Math::Matrix2x2<short>();
			matrix.Set(m00, m10, m01, m11);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(SetFloatTest)
		{
			constexpr float m00 = -10;
			constexpr float m10 = -15;
			constexpr float m01 = 5;
			constexpr float m11 = 20;
			auto matrix = PonyEngine::Math::Matrix2x2<float>();
			matrix.Set(m00, m10, m01, m11);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(SetColumnsShortTest)
		{
			constexpr short m00 = -10;
			constexpr short m10 = -15;
			constexpr short m01 = 5;
			constexpr short m11 = 20;
			constexpr auto column0 = PonyEngine::Math::Vector2<short>(m00, m10);
			constexpr auto column1 = PonyEngine::Math::Vector2<short>(m01, m11);
			auto matrix = PonyEngine::Math::Matrix2x2<short>();
			matrix.Set(column0, column1);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(SetColumsFloatTest)
		{
			constexpr float m00 = -10;
			constexpr float m10 = -15;
			constexpr float m01 = 5;
			constexpr float m11 = 20;
			constexpr auto column0 = PonyEngine::Math::Vector2<float>(m00, m10);
			constexpr auto column1 = PonyEngine::Math::Vector2<float>(m01, m11);
			auto matrix = PonyEngine::Math::Matrix2x2<float>();
			matrix.Set(column0, column1);
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(SetArrayShortTest)
		{
			constexpr short m00 = -10;
			constexpr short m10 = -15;
			constexpr short m01 = 5;
			constexpr short m11 = 20;
			constexpr std::array<short, 4> array{ m00, m10, m01, m11 };
			auto matrix = PonyEngine::Math::Matrix2x2<short>();
			matrix.Set(array.data());
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(SetArrayFloatTest)
		{
			constexpr float m00 = -10;
			constexpr float m10 = -15;
			constexpr float m01 = 5;
			constexpr float m11 = 20;
			constexpr std::array<float, 4> array{ m00, m10, m01, m11 };
			auto matrix = PonyEngine::Math::Matrix2x2<float>();
			matrix.Set(array.data());
			Assert::AreEqual(m00, matrix.M00());
			Assert::AreEqual(m10, matrix.M10());
			Assert::AreEqual(m01, matrix.M01());
			Assert::AreEqual(m11, matrix.M11());
		}

		TEST_METHOD(ScaleThisShortTest)
		{
			constexpr short m00 = -10;
			constexpr short m10 = -15;
			constexpr short m01 = 5;
			constexpr short m11 = 20;
			constexpr short m00S = 3;
			constexpr short m10S = -2;
			constexpr short m01S = 4;
			constexpr short m11S = -1;
			auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			constexpr auto scale = PonyEngine::Math::Matrix2x2<short>(m00S, m10S, m01S, m11S);
			matrix.Scale(scale);
			Assert::AreEqual(static_cast<short>(m00 * m00S), matrix.M00());
			Assert::AreEqual(static_cast<short>(m10 * m10S), matrix.M10());
			Assert::AreEqual(static_cast<short>(m01 * m01S), matrix.M01());
			Assert::AreEqual(static_cast<short>(m11 * m11S), matrix.M11());
		}

		TEST_METHOD(ScaleThisFloatTest)
		{
			constexpr float m00 = -10;
			constexpr float m10 = -15;
			constexpr float m01 = 5;
			constexpr float m11 = 20;
			constexpr float m00S = 3;
			constexpr float m10S = -2;
			constexpr float m01S = 4;
			constexpr float m11S = -1;
			auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			constexpr auto scale = PonyEngine::Math::Matrix2x2<float>(m00S, m10S, m01S, m11S);
			matrix.Scale(scale);
			Assert::AreEqual(m00 * m00S, matrix.M00());
			Assert::AreEqual(m10 * m10S, matrix.M10());
			Assert::AreEqual(m01 * m01S, matrix.M01());
			Assert::AreEqual(m11 * m11S, matrix.M11());
		}

		TEST_METHOD(ToStringShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			const auto expectedString = std::format("({}, {})({}, {})", m00, m01, m10, m11);
			Assert::AreEqual(expectedString, matrix.ToString());
			std::ostringstream ss;
			ss << matrix;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(ToStringFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			const auto expectedString = std::format("({}, {})({}, {})", m00, m01, m10, m11);
			Assert::AreEqual(expectedString, matrix.ToString());
			std::ostringstream ss;
			ss << matrix;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(AssignmentCopyShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			PonyEngine::Math::Matrix2x2<short> matrixC;
			PonyEngine::Math::Matrix2x2<short>& matrixL = matrixC = matrixR;
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentCopyFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			PonyEngine::Math::Matrix2x2<float> matrixC;
			PonyEngine::Math::Matrix2x2<float>& matrixL = matrixC = matrixR;
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMoveShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			auto matrixR = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			PonyEngine::Math::Matrix2x2<short> matrixC;
			PonyEngine::Math::Matrix2x2<short>& matrixL = matrixC = std::move(matrixR);
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMoveFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			auto matrixR = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			PonyEngine::Math::Matrix2x2<float> matrixC;
			PonyEngine::Math::Matrix2x2<float>& matrixL = matrixC = std::move(matrixR);
			Assert::AreEqual(m00, matrixC.M00());
			Assert::AreEqual(m10, matrixC.M10());
			Assert::AreEqual(m01, matrixC.M01());
			Assert::AreEqual(m11, matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentSumShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			constexpr short m00C = -13;
			constexpr short m10C = 17;
			constexpr short m01C = 15;
			constexpr short m11C = -12;
			auto matrixC = PonyEngine::Math::Matrix2x2<short>(m00C, m10C, m01C, m11C);
			PonyEngine::Math::Matrix2x2<short>& matrixL = matrixC += matrixR;
			Assert::AreEqual(static_cast<short>(m00 + m00C), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10 + m10C), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m01 + m01C), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11 + m11C), matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentSumFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			constexpr float m00C = -13;
			constexpr float m10C = 17;
			constexpr float m01C = 15;
			constexpr float m11C = -12;
			auto matrixC = PonyEngine::Math::Matrix2x2<float>(m00C, m10C, m01C, m11C);
			PonyEngine::Math::Matrix2x2<float>& matrixL = matrixC += matrixR;
			Assert::AreEqual(m00 + m00C, matrixC.M00());
			Assert::AreEqual(m10 + m10C, matrixC.M10());
			Assert::AreEqual(m01 + m01C, matrixC.M01());
			Assert::AreEqual(m11 + m11C, matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentSubtractShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			constexpr short m00C = -13;
			constexpr short m10C = 17;
			constexpr short m01C = 15;
			constexpr short m11C = -12;
			auto matrixC = PonyEngine::Math::Matrix2x2<short>(m00C, m10C, m01C, m11C);
			PonyEngine::Math::Matrix2x2<short>& matrixL = matrixC -= matrixR;
			Assert::AreEqual(static_cast<short>(m00C - m00), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C - m10), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m01C - m01), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C - m11), matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentSubtractFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			constexpr float m00C = -13;
			constexpr float m10C = 17;
			constexpr float m01C = 15;
			constexpr float m11C = -12;
			auto matrixC = PonyEngine::Math::Matrix2x2<float>(m00C, m10C, m01C, m11C);
			PonyEngine::Math::Matrix2x2<float>& matrixL = matrixC -= matrixR;
			Assert::AreEqual(m00C - m00, matrixC.M00());
			Assert::AreEqual(m10C - m10, matrixC.M10());
			Assert::AreEqual(m01C - m01, matrixC.M01());
			Assert::AreEqual(m11C - m11, matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMultiplyNumberShortTest)
		{
			constexpr short multiplierI = 3;
			constexpr short m00C = -13;
			constexpr short m10C = 17;
			constexpr short m01C = 15;
			constexpr short m11C = -12;
			auto matrixC = PonyEngine::Math::Matrix2x2<short>(m00C, m10C, m01C, m11C);
			PonyEngine::Math::Matrix2x2<short>& matrixL = matrixC *= multiplierI;
			Assert::AreEqual(static_cast<short>(m00C * multiplierI), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C * multiplierI), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m01C * multiplierI), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C * multiplierI), matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));

			constexpr float multiplierF = 5.f;
			matrixC = PonyEngine::Math::Matrix2x2<short>(m00C, m10C, m01C, m11C);
			matrixL = matrixC *= multiplierF;
			Assert::AreEqual(static_cast<short>(m00C * multiplierF), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C * multiplierF), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m01C * multiplierF), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C * multiplierF), matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMultiplyNumberFloatTest)
		{
			constexpr float multiplier = 3;
			constexpr float m00C = -13;
			constexpr float m10C = 17;
			constexpr float m01C = 15;
			constexpr float m11C = -12;
			auto matrixC = PonyEngine::Math::Matrix2x2<float>(m00C, m10C, m01C, m11C);
			PonyEngine::Math::Matrix2x2<float>& matrixL = matrixC *= multiplier;
			Assert::AreEqual(m00C * multiplier, matrixC.M00());
			Assert::AreEqual(m10C * multiplier, matrixC.M10());
			Assert::AreEqual(m01C * multiplier, matrixC.M01());
			Assert::AreEqual(m11C * multiplier, matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMultiplyMatrixShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			constexpr short m00C = -13;
			constexpr short m10C = 17;
			constexpr short m01C = 15;
			constexpr short m11C = -12;
			auto matrixC = PonyEngine::Math::Matrix2x2<short>(m00C, m10C, m01C, m11C);
			PonyEngine::Math::Matrix2x2<short>& matrixL = matrixC *= matrixR;
			Assert::AreEqual(short{-144}, matrixC.M00());
			Assert::AreEqual(short{135}, matrixC.M10());
			Assert::AreEqual(short{-95}, matrixC.M01());
			Assert::AreEqual(short{109}, matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentMultiplyMatrixFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			constexpr float m00C = -13;
			constexpr float m10C = 17;
			constexpr float m01C = 15;
			constexpr float m11C = -12;
			auto matrixC = PonyEngine::Math::Matrix2x2<float>(m00C, m10C, m01C, m11C);
			PonyEngine::Math::Matrix2x2<float>& matrixL = matrixC *= matrixR;
			Assert::AreEqual(-144.f, matrixC.M00());
			Assert::AreEqual(135.f, matrixC.M10());
			Assert::AreEqual(-95.f, matrixC.M01());
			Assert::AreEqual(109.f, matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentDivideNumberShortTest)
		{
			constexpr short divisorI = 3;
			constexpr short m00C = -13;
			constexpr short m10C = 17;
			constexpr short m01C = 15;
			constexpr short m11C = -12;
			auto matrixC = PonyEngine::Math::Matrix2x2<short>(m00C, m10C, m01C, m11C);
			PonyEngine::Math::Matrix2x2<short>& matrixL = matrixC /= divisorI;
			Assert::AreEqual(static_cast<short>(m00C / divisorI), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C / divisorI), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m01C / divisorI), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C / divisorI), matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));

			constexpr float divisorF = 5.f;
			matrixC = PonyEngine::Math::Matrix2x2<short>(m00C, m10C, m01C, m11C);
			matrixL = matrixC /= divisorF;
			Assert::AreEqual(static_cast<short>(m00C / divisorF), matrixC.M00());
			Assert::AreEqual(static_cast<short>(m10C / divisorF), matrixC.M10());
			Assert::AreEqual(static_cast<short>(m01C / divisorF), matrixC.M01());
			Assert::AreEqual(static_cast<short>(m11C / divisorF), matrixC.M11());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(AssignmentDivideNumberFloatTest)
		{
			constexpr float divisor = 3;
			constexpr float m00C = -13;
			constexpr float m10C = 17;
			constexpr float m01C = 15;
			constexpr float m11C = -12;
			auto matrixC = PonyEngine::Math::Matrix2x2<float>(m00C, m10C, m01C, m11C);
			PonyEngine::Math::Matrix2x2<float>& matrixL = matrixC /= divisor;
			Assert::AreEqual(static_cast<double>(m00C / divisor), static_cast<double>(matrixC.M00()), 0.00001);
			Assert::AreEqual(static_cast<double>(m10C / divisor), static_cast<double>(matrixC.M10()), 0.00001);
			Assert::AreEqual(static_cast<double>(m01C / divisor), static_cast<double>(matrixC.M01()), 0.00001);
			Assert::AreEqual(static_cast<double>(m11C / divisor), static_cast<double>(matrixC.M11()), 0.00001);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&matrixC), reinterpret_cast<std::uintptr_t>(&matrixL));
		}

		TEST_METHOD(EqualityOperatorShortTest)
		{
			constexpr short m00 = 3;
			constexpr short m10 = -7;
			constexpr short m01 = 5;
			constexpr short m11 = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<short>(m00, m10, m01, m11);
			PonyEngine::Math::Matrix2x2<short> matrixL = matrixR;

			Assert::IsTrue(matrixL == matrixR);
			Assert::IsFalse(matrixL != matrixR);

			for (std::size_t i = 0; i < PonyEngine::Math::Matrix2x2<short>::ComponentCount; ++i)
			{
				matrixL.Data()[i] += 1;
				Assert::IsFalse(matrixL == matrixR);
				Assert::IsTrue(matrixL != matrixR);
				matrixL.Data()[i] = matrixR.Data()[i];
			}
		}

		TEST_METHOD(EqualityOperatorFloatTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			PonyEngine::Math::Matrix2x2<float> matrixL = matrixR;

			Assert::IsTrue(matrixL == matrixR);
			Assert::IsFalse(matrixL != matrixR);

			for (std::size_t i = 0; i < PonyEngine::Math::Matrix2x2<float>::ComponentCount; ++i)
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

		TEST_METHOD(DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix2x2Identity<float> == PonyEngine::Math::Matrix2x2<float>(1.f, 0.f, 0.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Matrix2x2Zero<float> == PonyEngine::Math::Matrix2x2<float>(0.f, 0.f, 0.f, 0.f));

			Assert::IsTrue(PonyEngine::Math::Matrix2x2Identity<short> == PonyEngine::Math::Matrix2x2<short>(1, 0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Matrix2x2Zero<short> == PonyEngine::Math::Matrix2x2<short>(0, 0, 0, 0));
		}

		TEST_METHOD(ScaleShortTest)
		{
			constexpr short m00R = 3;
			constexpr short m10R = -7;
			constexpr short m01R = 5;
			constexpr short m11R = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<short>(m00R, m10R, m01R, m11R);
			constexpr short m00L = -13;
			constexpr short m10L = 17;
			constexpr short m01L = 15;
			constexpr short m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<short>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Matrix2x2<short> scaled = PonyEngine::Math::Scale(matrixL, matrixR);
			Assert::AreEqual(static_cast<short>(m00L * m00R), scaled.M00());
			Assert::AreEqual(static_cast<short>(m10L * m10R), scaled.M10());
			Assert::AreEqual(static_cast<short>(m01L * m01R), scaled.M01());
			Assert::AreEqual(static_cast<short>(m11L * m11R), scaled.M11());
		}

		TEST_METHOD(ScaleFloatTest)
		{
			constexpr float m00R = 3;
			constexpr float m10R = -7;
			constexpr float m01R = 5;
			constexpr float m11R = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<float>(m00R, m10R, m01R, m11R);
			constexpr float m00L = -13;
			constexpr float m10L = 17;
			constexpr float m01L = 15;
			constexpr float m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<float>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Matrix2x2<float> scaled = PonyEngine::Math::Scale(matrixL, matrixR);
			Assert::AreEqual(m00L * m00R, scaled.M00());
			Assert::AreEqual(m10L * m10R, scaled.M10());
			Assert::AreEqual(m01L * m01R, scaled.M01());
			Assert::AreEqual(m11L * m11R, scaled.M11());
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float m00 = 3;
			constexpr float m10 = -7;
			constexpr float m01 = 5;
			constexpr float m11 = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<float>(m00, m10, m01, m11);
			PonyEngine::Math::Matrix2x2<float> matrixL = matrixR;
			for (std::size_t i = 0; i < PonyEngine::Math::Matrix2x2<float>::ComponentCount; ++i)
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
			constexpr short m00R = 3;
			constexpr short m10R = -7;
			constexpr short m01R = 5;
			constexpr short m11R = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<short>(m00R, m10R, m01R, m11R);
			constexpr short m00L = -13;
			constexpr short m10L = 17;
			constexpr short m01L = 15;
			constexpr short m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<short>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Matrix2x2<short> sum = matrixL + matrixR;
			Assert::AreEqual(static_cast<short>(m00L + m00R), sum.M00());
			Assert::AreEqual(static_cast<short>(m10L + m10R), sum.M10());
			Assert::AreEqual(static_cast<short>(m01L + m01R), sum.M01());
			Assert::AreEqual(static_cast<short>(m11L + m11R), sum.M11());
		}

		TEST_METHOD(AddFloatTest)
		{
			constexpr float m00R = 3;
			constexpr float m10R = -7;
			constexpr float m01R = 5;
			constexpr float m11R = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<float>(m00R, m10R, m01R, m11R);
			constexpr float m00L = -13;
			constexpr float m10L = 17;
			constexpr float m01L = 15;
			constexpr float m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<float>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Matrix2x2<float> sum = matrixL + matrixR;
			Assert::AreEqual(m00L + m00R, sum.M00());
			Assert::AreEqual(m10L + m10R, sum.M10());
			Assert::AreEqual(m01L + m01R, sum.M01());
			Assert::AreEqual(m11L + m11R, sum.M11());
		}

		TEST_METHOD(NegateShortTest)
		{
			constexpr short m00R = 3;
			constexpr short m10R = -7;
			constexpr short m01R = 5;
			constexpr short m11R = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<short>(m00R, m10R, m01R, m11R);
			PonyEngine::Math::Matrix2x2<short> negated = -matrixR;
			Assert::AreEqual(static_cast<short>(-m00R), negated.M00());
			Assert::AreEqual(static_cast<short>(-m10R), negated.M10());
			Assert::AreEqual(static_cast<short>(-m01R), negated.M01());
			Assert::AreEqual(static_cast<short>(-m11R), negated.M11());
		}

		TEST_METHOD(NegateFloatTest)
		{
			constexpr float m00R = 3;
			constexpr float m10R = -7;
			constexpr float m01R = 5;
			constexpr float m11R = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<float>(m00R, m10R, m01R, m11R);
			PonyEngine::Math::Matrix2x2<float> negated = -matrixR;
			Assert::AreEqual(-m00R, negated.M00());
			Assert::AreEqual(-m10R, negated.M10());
			Assert::AreEqual(-m01R, negated.M01());
			Assert::AreEqual(-m11R, negated.M11());
		}

		TEST_METHOD(SubtractShortTest)
		{
			constexpr short m00R = 3;
			constexpr short m10R = -7;
			constexpr short m01R = 5;
			constexpr short m11R = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<short>(m00R, m10R, m01R, m11R);
			constexpr short m00L = -13;
			constexpr short m10L = 17;
			constexpr short m01L = 15;
			constexpr short m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<short>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Matrix2x2<short> difference = matrixL - matrixR;
			Assert::AreEqual(static_cast<short>(m00L - m00R), difference.M00());
			Assert::AreEqual(static_cast<short>(m10L - m10R), difference.M10());
			Assert::AreEqual(static_cast<short>(m01L - m01R), difference.M01());
			Assert::AreEqual(static_cast<short>(m11L - m11R), difference.M11());
		}

		TEST_METHOD(SubtractFloatTest)
		{
			constexpr float m00R = 3;
			constexpr float m10R = -7;
			constexpr float m01R = 5;
			constexpr float m11R = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<float>(m00R, m10R, m01R, m11R);
			constexpr float m00L = -13;
			constexpr float m10L = 17;
			constexpr float m01L = 15;
			constexpr float m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<float>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Matrix2x2<float> difference = matrixL - matrixR;
			Assert::AreEqual(m00L - m00R, difference.M00());
			Assert::AreEqual(m10L - m10R, difference.M10());
			Assert::AreEqual(m01L - m01R, difference.M01());
			Assert::AreEqual(m11L - m11R, difference.M11());
		}

		TEST_METHOD(MultiplyNumberShortTest)
		{
			constexpr short multiplierI = 2;
			constexpr short m00L = -13;
			constexpr short m10L = 17;
			constexpr short m01L = 15;
			constexpr short m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<short>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Matrix2x2<short> product = matrixL * multiplierI;
			Assert::AreEqual(static_cast<short>(m00L * multiplierI), product.M00());
			Assert::AreEqual(static_cast<short>(m10L * multiplierI), product.M10());
			Assert::AreEqual(static_cast<short>(m01L * multiplierI), product.M01());
			Assert::AreEqual(static_cast<short>(m11L * multiplierI), product.M11());
			Assert::IsTrue(multiplierI * matrixL == matrixL * multiplierI);

			constexpr float multiplierF = 3;
			product = matrixL * multiplierF;
			Assert::AreEqual(static_cast<short>(m00L * multiplierF), product.M00());
			Assert::AreEqual(static_cast<short>(m10L * multiplierF), product.M10());
			Assert::AreEqual(static_cast<short>(m01L * multiplierF), product.M01());
			Assert::AreEqual(static_cast<short>(m11L * multiplierF), product.M11());
			Assert::IsTrue(multiplierF * matrixL == matrixL * multiplierF);
		}

		TEST_METHOD(MultiplyNumberFloatTest)
		{
			constexpr float multiplierF = 3;
			constexpr float m00L = -13;
			constexpr float m10L = 17;
			constexpr float m01L = 15;
			constexpr float m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<float>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Matrix2x2<float> product = matrixL * multiplierF;
			Assert::AreEqual(m00L * multiplierF, product.M00());
			Assert::AreEqual(m10L * multiplierF, product.M10());
			Assert::AreEqual(m01L * multiplierF, product.M01());
			Assert::AreEqual(m11L * multiplierF, product.M11());
			Assert::IsTrue(multiplierF * matrixL == matrixL * multiplierF);
		}

		TEST_METHOD(MultiplyMatrixShortTest)
		{
			constexpr short m00R = 5;
			constexpr short m10R = -7;
			constexpr short m01R = 15;
			constexpr short m11R = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<short>(m00R, m10R, m01R, m11R);
			constexpr short m00L = -13;
			constexpr short m10L = 7;
			constexpr short m01L = 5;
			constexpr short m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<short>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Matrix2x2<short> product = matrixL * matrixR;
			Assert::AreEqual(short{-100}, product.M00());
			Assert::AreEqual(short{119}, product.M10());
			Assert::AreEqual(short{-205}, product.M01());
			Assert::AreEqual(short{129}, product.M11());
		}

		TEST_METHOD(MultiplyMatrixFloatTest)
		{
			constexpr float m00R = 5;
			constexpr float m10R = -7;
			constexpr float m01R = 15;
			constexpr float m11R = -2;
			constexpr auto matrixR = PonyEngine::Math::Matrix2x2<float>(m00R, m10R, m01R, m11R);
			constexpr float m00L = -13;
			constexpr float m10L = 7;
			constexpr float m01L = 5;
			constexpr float m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<float>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Matrix2x2<float> product = matrixL * matrixR;
			Assert::AreEqual(-100.f, product.M00());
			Assert::AreEqual(119.f, product.M10());
			Assert::AreEqual(-205.f, product.M01());
			Assert::AreEqual(129.f, product.M11());
		}

		TEST_METHOD(MultiplyVectorShortTest)
		{
			constexpr short m00R = 5;
			constexpr short m10R = -7;
			constexpr auto vectorR = PonyEngine::Math::Vector2<short>(m00R, m10R);
			constexpr short m00L = -13;
			constexpr short m10L = 7;
			constexpr short m01L = 5;
			constexpr short m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<short>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Vector2<short> product = matrixL * vectorR;
			Assert::AreEqual(short{-100}, product.X());
			Assert::AreEqual(short{119}, product.Y());
		}

		TEST_METHOD(MultiplyVectorFloatTest)
		{
			constexpr float m00R = 5;
			constexpr float m10R = -7;
			constexpr auto vectorR = PonyEngine::Math::Vector2<float>(m00R, m10R);
			constexpr float m00L = -13;
			constexpr float m10L = 7;
			constexpr float m01L = 5;
			constexpr float m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<float>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Vector2<float> product = matrixL * vectorR;
			Assert::AreEqual(-100.f, product.X());
			Assert::AreEqual(119.f, product.Y());
		}

		TEST_METHOD(DivideShortTest)
		{
			constexpr short divisorI = 2;
			constexpr short m00L = -13;
			constexpr short m10L = 17;
			constexpr short m01L = 15;
			constexpr short m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<short>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Matrix2x2<short> product = matrixL / divisorI;
			Assert::AreEqual(static_cast<short>(m00L / divisorI), product.M00());
			Assert::AreEqual(static_cast<short>(m10L / divisorI), product.M10());
			Assert::AreEqual(static_cast<short>(m01L / divisorI), product.M01());
			Assert::AreEqual(static_cast<short>(m11L / divisorI), product.M11());

			constexpr float divisorF = 3;
			product = matrixL / divisorF;
			Assert::AreEqual(static_cast<short>(m00L / divisorF), product.M00());
			Assert::AreEqual(static_cast<short>(m10L / divisorF), product.M10());
			Assert::AreEqual(static_cast<short>(m01L / divisorF), product.M01());
			Assert::AreEqual(static_cast<short>(m11L / divisorF), product.M11());
		}

		TEST_METHOD(DivideFloatTest)
		{
			constexpr float divisor = 2;
			constexpr float m00L = -13;
			constexpr float m10L = 17;
			constexpr float m01L = 15;
			constexpr float m11L = -12;
			constexpr auto matrixL = PonyEngine::Math::Matrix2x2<float>(m00L, m10L, m01L, m11L);
			PonyEngine::Math::Matrix2x2<float> product = matrixL / divisor;
			Assert::AreEqual(m00L / divisor, product.M00());
			Assert::AreEqual(m10L / divisor, product.M10());
			Assert::AreEqual(m01L / divisor, product.M01());
			Assert::AreEqual(m11L / divisor, product.M11());
		}

		static constexpr PonyEngine::Math::Matrix2x2<int> MatrixConstexpr()
		{
			auto matrix = PonyEngine::Math::Matrix2x2<int>();
			PonyEngine::Math::Matrix2x2<int> movedMatrix = std::move(matrix);

			movedMatrix.M00() += 1.f;
			movedMatrix.M10() -= 2.f;
			movedMatrix.M01() *= 2.f;
			movedMatrix.M11() = 6.f;
			int* const data = movedMatrix.Data();
			int* const columnData = movedMatrix.Data(1);

			constexpr auto constMatrix = PonyEngine::Math::Matrix2x2<int>(4, 3, 9, 1);
			const int* const dataC = constMatrix.Data();
			const int* const columnDataC = constMatrix.Data(1);

			movedMatrix.SetRow(0, PonyEngine::Math::Vector2<int>(3, 6));
			movedMatrix.SetColumn(1, PonyEngine::Math::Vector2<int>(3, 6));
			movedMatrix.SetDiagonal(PonyEngine::Math::Vector2<int>(3, 6));
			movedMatrix.SetCounterDiagonal(PonyEngine::Math::Vector2<int>(3, 6));

			movedMatrix.Set(4, 6, 1, 0);
			movedMatrix.Set(PonyEngine::Math::Vector2<int>(4, 6), PonyEngine::Math::Vector2<int>(9, 4));
			movedMatrix.Set(std::array<int, 4>{4, 5, 6, 6}.data());

			movedMatrix.Scale(constMatrix);

			movedMatrix[1][1] = 5;
			movedMatrix[1] = PonyEngine::Math::Vector2<int>(9, 4);

			auto copyAssigned = PonyEngine::Math::Matrix2x2<int>();
			copyAssigned = movedMatrix;
			movedMatrix = std::move(copyAssigned);

			movedMatrix += constMatrix;
			movedMatrix -= constMatrix;
			movedMatrix *= 3;
			movedMatrix *= 3.f;

			auto leftMatrix = PonyEngine::Math::Matrix2x2<int>(4, 3, 9, 1);
			constexpr auto rightMatrix = PonyEngine::Math::Matrix2x2<int>(6, 8, 1, 1); // Left and right are MSVC internal compiler error overcome.
			leftMatrix *= rightMatrix;
			leftMatrix /= 4;
			leftMatrix /= 5.f;

			return movedMatrix;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			constexpr auto defaultMatrix = PonyEngine::Math::Matrix2x2<int>();
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<int>(0, 2, 3, 4);
			constexpr auto columnMatrix = PonyEngine::Math::Matrix2x2<int>(PonyEngine::Math::Vector2<int>(4, 6), PonyEngine::Math::Vector2<int>(9, 4));
			constexpr auto arrayMatrix = PonyEngine::Math::Matrix2x2<int>(std::array<int, 4>{4, 5, 6, 6}.data());
			constexpr PonyEngine::Math::Matrix2x2<int> copiedMatrix = matrix;
			constexpr PonyEngine::Math::Matrix2x2<int> movedMatrix = MatrixConstexpr();

			constexpr int m00 = matrix.M00();
			constexpr int m10 = matrix.M10();
			constexpr int m01 = matrix.M01();
			constexpr int m11 = matrix.M11();

			constexpr PonyEngine::Math::Vector2<int> row = matrix.GetRow(1);
			constexpr PonyEngine::Math::Vector2<int> column = matrix.GetColumn(0);
			constexpr PonyEngine::Math::Vector2<int> diagonal = matrix.GetDiagonal();
			constexpr PonyEngine::Math::Vector2<int> counterDiagonal = matrix.GetCounterDiagonal();

			constexpr int trace = matrix.Trace();
			constexpr int determinant = matrix.Determinant();
			constexpr PonyEngine::Math::Matrix2x2<int> adjugate = matrix.Adjugate();
			constexpr PonyEngine::Math::Matrix2x2<int> transpose = matrix.Transpose();
			constexpr PonyEngine::Math::Matrix2x2<int> inverse = matrix.Inverse();

			constexpr int m10A = matrix[1][0];
			constexpr PonyEngine::Math::Vector2<int> columnV = matrix[0];

			constexpr bool equal = matrix == defaultMatrix;
			constexpr bool notEqual = matrix != defaultMatrix;

			constexpr PonyEngine::Math::Matrix2x2<int> identity = PonyEngine::Math::Matrix2x2Identity<int>;
			constexpr PonyEngine::Math::Matrix2x2<int> zero = PonyEngine::Math::Matrix2x2Zero<int>;

			constexpr PonyEngine::Math::Matrix2x2<int> scaled = PonyEngine::Math::Scale(matrix, columnMatrix);
			constexpr bool areAlmostEqual = PonyEngine::Math::AreAlmostEqual(matrix, defaultMatrix);

			constexpr PonyEngine::Math::Matrix2x2<int> sum = matrix + columnMatrix;
			constexpr PonyEngine::Math::Matrix2x2<int> negated = -matrix;
			constexpr PonyEngine::Math::Matrix2x2<int> difference = matrix - columnMatrix;
			constexpr PonyEngine::Math::Matrix2x2<int> productNumR = matrix * 3;
			constexpr PonyEngine::Math::Matrix2x2<int> productNumL = 3 * matrix;
			constexpr PonyEngine::Math::Matrix2x2<int> productNumFR = matrix * 3.f;
			constexpr PonyEngine::Math::Matrix2x2<int> productNumFL = 3.f * matrix;
			constexpr PonyEngine::Math::Matrix2x2<int> product = matrix * columnMatrix;
			constexpr PonyEngine::Math::Vector2<int> productV = matrix * PonyEngine::Math::Vector2<int>(4, 6);
			constexpr PonyEngine::Math::Matrix2x2<int> quotient = matrix / 3;
			constexpr PonyEngine::Math::Matrix2x2<int> quotientF = matrix / 3.f;
		}
	};
}
