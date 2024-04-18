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
		TEST_METHOD(ConstructorTest)
		{
			auto defaultMatrixF = PonyEngine::Math::Matrix2x2<float>();
			Assert::AreEqual(float{}, defaultMatrixF.M00());
			Assert::AreEqual(float{}, defaultMatrixF.M10());
			Assert::AreEqual(float{}, defaultMatrixF.M01());
			Assert::AreEqual(float{}, defaultMatrixF.M11());

			float m00F = 4.f;
			float m10F = -3.f;
			float m01F = 6.f;
			float m11F = 5.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			Assert::AreEqual(m00F, matrixF.M00());
			Assert::AreEqual(m10F, matrixF.M10());
			Assert::AreEqual(m01F, matrixF.M01());
			Assert::AreEqual(m11F, matrixF.M11());

			auto copiedMatrixF = matrixF;
			Assert::AreEqual(m00F, copiedMatrixF.M00());
			Assert::AreEqual(m10F, copiedMatrixF.M10());
			Assert::AreEqual(m01F, copiedMatrixF.M01());
			Assert::AreEqual(m11F, copiedMatrixF.M11());

			auto column0F = PonyEngine::Math::Vector2<float>(m00F, m10F);
			auto column1F = PonyEngine::Math::Vector2<float>(m01F, m11F);
			auto vectorMatrixF = PonyEngine::Math::Matrix2x2<float>(column0F, column1F);
			Assert::AreEqual(m00F, vectorMatrixF.M00());
			Assert::AreEqual(m10F, vectorMatrixF.M10());
			Assert::AreEqual(m01F, vectorMatrixF.M01());
			Assert::AreEqual(m11F, vectorMatrixF.M11());

			auto defaultMatrixI = PonyEngine::Math::Matrix2x2<short>();
			Assert::AreEqual(short{}, defaultMatrixI.M00());
			Assert::AreEqual(short{}, defaultMatrixI.M10());
			Assert::AreEqual(short{}, defaultMatrixI.M01());
			Assert::AreEqual(short{}, defaultMatrixI.M11());

			short m00I = 4;
			short m10I = -3;
			short m01I = 6;
			short m11I = 5;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			Assert::AreEqual(m00I, matrixI.M00());
			Assert::AreEqual(m10I, matrixI.M10());
			Assert::AreEqual(m01I, matrixI.M01());
			Assert::AreEqual(m11I, matrixI.M11());

			auto copiedMatrixI = matrixI;
			Assert::AreEqual(m00I, copiedMatrixI.M00());
			Assert::AreEqual(m10I, copiedMatrixI.M10());
			Assert::AreEqual(m01I, copiedMatrixI.M01());
			Assert::AreEqual(m11I, copiedMatrixI.M11());

			auto column0I = PonyEngine::Math::Vector2<short>(m00I, m10I);
			auto column1I = PonyEngine::Math::Vector2<short>(m01I, m11I);
			auto vectorMatrixI = PonyEngine::Math::Matrix2x2<short>(column0I, column1I);
			Assert::AreEqual(m00I, vectorMatrixI.M00());
			Assert::AreEqual(m10I, vectorMatrixI.M10());
			Assert::AreEqual(m01I, vectorMatrixI.M01());
			Assert::AreEqual(m11I, vectorMatrixI.M11());
		}

		TEST_METHOD(DataTest)
		{
			float m00F = 4.f;
			float m10F = -3.f;
			float m01F = 6.f;
			float m11F = 5.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			Assert::AreEqual(matrixF.M00(), matrixF.Data()[0]);
			Assert::AreEqual(matrixF.M10(), matrixF.Data()[1]);
			Assert::AreEqual(matrixF.M01(), matrixF.Data()[2]);
			Assert::AreEqual(matrixF.M11(), matrixF.Data()[3]);

			short m00I = 4;
			short m10I = -3;
			short m01I = 6;
			short m11I = 5;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			Assert::AreEqual(matrixI.M00(), matrixI.Data()[0]);
			Assert::AreEqual(matrixI.M10(), matrixI.Data()[1]);
			Assert::AreEqual(matrixI.M01(), matrixI.Data()[2]);
			Assert::AreEqual(matrixI.M11(), matrixI.Data()[3]);
		}

		TEST_METHOD(DeterminantTest)
		{
			float m00F = 3.f;
			float m10F = -7.f;
			float m01F = 5.f;
			float m11F = -2.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			Assert::AreEqual(29.f, matrixF.Determinant());

			short m00I = 3;
			short m10I = -7;
			short m01I = 5;
			short m11I = -2;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			Assert::AreEqual(short{29}, matrixI.Determinant());
		}

		TEST_METHOD(AdjugateTest)
		{
			float m00F = 3.f;
			float m10F = -7.f;
			float m01F = 5.f;
			float m11F = -2.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			auto adjugateF = matrixF.Adjugate();
			Assert::AreEqual(-2.f, adjugateF.M00());
			Assert::AreEqual(7.f, adjugateF.M10());
			Assert::AreEqual(-5.f, adjugateF.M01());
			Assert::AreEqual(3.f, adjugateF.M11());

			short m00I = 3;
			short m10I = -7;
			short m01I = 5;
			short m11I = -2;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			auto adjugateI = matrixI.Adjugate();
			Assert::AreEqual(short{-2}, adjugateI.M00());
			Assert::AreEqual(short{7}, adjugateI.M10());
			Assert::AreEqual(short{-5}, adjugateI.M01());
			Assert::AreEqual(short{3}, adjugateI.M11());
		}

		TEST_METHOD(TransposeTest)
		{
			float m00F = 3.f;
			float m10F = -7.f;
			float m01F = 5.f;
			float m11F = -2.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			auto adjugateF = matrixF.Transposed();
			Assert::AreEqual(3.f, adjugateF.M00());
			Assert::AreEqual(5.f, adjugateF.M10());
			Assert::AreEqual(-7.f, adjugateF.M01());
			Assert::AreEqual(-2.f, adjugateF.M11());
			matrixF.Transpose();
			Assert::AreEqual(adjugateF.M00(), matrixF.M00());
			Assert::AreEqual(adjugateF.M10(), matrixF.M10());
			Assert::AreEqual(adjugateF.M01(), matrixF.M01());
			Assert::AreEqual(adjugateF.M11(), matrixF.M11());

			short m00I = 3;
			short m10I = -7;
			short m01I = 5;
			short m11I = -2;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			auto adjugateI = matrixI.Transposed();
			Assert::AreEqual(short{3}, adjugateI.M00());
			Assert::AreEqual(short{5}, adjugateI.M10());
			Assert::AreEqual(short{-7}, adjugateI.M01());
			Assert::AreEqual(short{-2}, adjugateI.M11());
			matrixI.Transpose();
			Assert::AreEqual(adjugateI.M00(), matrixI.M00());
			Assert::AreEqual(adjugateI.M10(), matrixI.M10());
			Assert::AreEqual(adjugateI.M01(), matrixI.M01());
			Assert::AreEqual(adjugateI.M11(), matrixI.M11());
		}

		TEST_METHOD(InverseTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m01F = 5.f;
			float m11F = 20.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			auto inversedF = matrixF.Inversed();
			Assert::AreEqual(static_cast<double>(-4.f / 25.f), static_cast<double>(inversedF.M00()), 0.0001);
			Assert::AreEqual(static_cast<double>(-3.f / 25.f), static_cast<double>(inversedF.M10()), 0.0001);
			Assert::AreEqual(static_cast<double>(1.f / 25.f), static_cast<double>(inversedF.M01()), 0.0001);
			Assert::AreEqual(static_cast<double>(2.f / 25.f), static_cast<double>(inversedF.M11()), 0.0001);

			auto multipliedF = matrixF * inversedF;
			Assert::AreEqual(static_cast<double>(PonyEngine::Math::Matrix2x2<float>::Identity.M00()), static_cast<double>(multipliedF.M00()), 0.0001);
			Assert::AreEqual(static_cast<double>(PonyEngine::Math::Matrix2x2<float>::Identity.M10()), static_cast<double>(multipliedF.M10()), 0.0001);
			Assert::AreEqual(static_cast<double>(PonyEngine::Math::Matrix2x2<float>::Identity.M01()), static_cast<double>(multipliedF.M01()), 0.0001);
			Assert::AreEqual(static_cast<double>(PonyEngine::Math::Matrix2x2<float>::Identity.M11()), static_cast<double>(multipliedF.M11()), 0.0001);

			matrixF.Inverse();
			Assert::AreEqual(inversedF.M00(), matrixF.M00());
			Assert::AreEqual(inversedF.M10(), matrixF.M10());
			Assert::AreEqual(inversedF.M01(), matrixF.M01());
			Assert::AreEqual(inversedF.M11(), matrixF.M11());
		}

		TEST_METHOD(IsFiniteTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix2x2<float>::Zero.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Matrix2x2<float>::Identity.IsFinite());
			float nan = std::numeric_limits<float>::quiet_NaN();
			auto matrix = PonyEngine::Math::Matrix2x2<float>(nan, 0.f, 0.f, 0.f);
			Assert::IsFalse(matrix.IsFinite());
			matrix.M00() = 0.f;
			matrix.M01() = nan;
			Assert::IsFalse(matrix.IsFinite());
			matrix.M01() = 0.f;
			matrix.M10() = nan;
			Assert::IsFalse(matrix.IsFinite());
			matrix.M10() = 0.f;
			matrix.M11() = nan;
			Assert::IsFalse(matrix.IsFinite());

			Assert::IsTrue(PonyEngine::Math::Matrix2x2<short>::Zero.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Matrix2x2<short>::Identity.IsFinite());
		}

		TEST_METHOD(SetTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m01F = 5.f;
			float m11F = 20.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>();
			matrixF.Set(m00F, m10F, m01F, m11F);
			Assert::AreEqual(m00F, matrixF.M00());
			Assert::AreEqual(m10F, matrixF.M10());
			Assert::AreEqual(m01F, matrixF.M01());
			Assert::AreEqual(m11F, matrixF.M11());

			short m00I = -10;
			short m10I = -15;
			short m01I = 5;
			short m11I = 20;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>();
			matrixI.Set(m00I, m10I, m01I, m11I);
			Assert::AreEqual(m00I, matrixI.M00());
			Assert::AreEqual(m10I, matrixI.M10());
			Assert::AreEqual(m01I, matrixI.M01());
			Assert::AreEqual(m11I, matrixI.M11());
		}

		TEST_METHOD(ScaleTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m00SF = 3.f;
			float m10SF = -2.f;
			float m01SF = 4.f;
			float m11SF =-1.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			auto scaleF = PonyEngine::Math::Matrix2x2<float>(m00SF, m10SF, m01SF, m11SF);
			auto scaledF = PonyEngine::Math::Scale(matrixF, scaleF);
			Assert::AreEqual(m00F * m00SF, scaledF.M00());
			Assert::AreEqual(m10F * m10SF, scaledF.M10());
			Assert::AreEqual(m01F * m01SF, scaledF.M01());
			Assert::AreEqual(m11F * m11SF, scaledF.M11());
			matrixF.Scale(scaleF);
			Assert::AreEqual(scaledF.M00(), matrixF.M00());
			Assert::AreEqual(scaledF.M10(), matrixF.M10());
			Assert::AreEqual(scaledF.M01(), matrixF.M01());
			Assert::AreEqual(scaledF.M11(), matrixF.M11());

			short m00I = -10;
			short m10I = -15;
			short m01I = 5;
			short m11I = 20;
			short m00SI = 3;
			short m10SI = -2;
			short m01SI = 4;
			short m11SI = -1;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			auto scaleI = PonyEngine::Math::Matrix2x2<short>(m00SI, m10SI, m01SI, m11SI);
			auto scaledI = PonyEngine::Math::Scale(matrixI, scaleI);
			Assert::AreEqual(static_cast<short>(m00I * m00SI), scaledI.M00());
			Assert::AreEqual(static_cast<short>(m10I * m10SI), scaledI.M10());
			Assert::AreEqual(static_cast<short>(m01I * m01SI), scaledI.M01());
			Assert::AreEqual(static_cast<short>(m11I * m11SI), scaledI.M11());
			matrixI.Scale(scaleI);
			Assert::AreEqual(scaledI.M00(), matrixI.M00());
			Assert::AreEqual(scaledI.M10(), matrixI.M10());
			Assert::AreEqual(scaledI.M01(), matrixI.M01());
			Assert::AreEqual(scaledI.M11(), matrixI.M11());
		}

		TEST_METHOD(GetRowTest)
		{
			float m00F = 3.f;
			float m10F = -7.f;
			float m01F = 5.f;
			float m11F = -2.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			auto row0F = matrixF.GetRow(0);
			auto row1F = matrixF.GetRow(1);
			Assert::AreEqual(m00F, row0F.X());
			Assert::AreEqual(m01F, row0F.Y());
			Assert::AreEqual(m10F, row1F.X());
			Assert::AreEqual(m11F, row1F.Y());

			short m00I = 3;
			short m10I = -7;
			short m01I = 5;
			short m11I = -2;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			auto row0I = matrixI.GetRow(0);
			auto row1I = matrixI.GetRow(1);
			Assert::AreEqual(m00I, row0I.X());
			Assert::AreEqual(m01I, row0I.Y());
			Assert::AreEqual(m10I, row1I.X());
			Assert::AreEqual(m11I, row1I.Y());
		}

		TEST_METHOD(SetRowTest)
		{
			float m00F = 3.f;
			float m10F = -7.f;
			float m01F = 5.f;
			float m11F = -2.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>();
			auto row0F = PonyEngine::Math::Vector2<float>(m00F, m01F);
			auto row1F = PonyEngine::Math::Vector2<float>(m10F, m11F);
			matrixF.SetRow(0, row0F);
			matrixF.SetRow(1, row1F);
			Assert::AreEqual(m00F, matrixF.M00());
			Assert::AreEqual(m01F, matrixF.M01());
			Assert::AreEqual(m10F, matrixF.M10());
			Assert::AreEqual(m11F, matrixF.M11());

			short m00I = 3;
			short m10I = -7;
			short m01I = 5;
			short m11I = -2;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>();
			auto row0I = PonyEngine::Math::Vector2<short>(m00I, m01I);
			auto row1I = PonyEngine::Math::Vector2<short>(m10I, m11I);
			matrixI.SetRow(0, row0I);
			matrixI.SetRow(1, row1I);
			Assert::AreEqual(m00I, matrixI.M00());
			Assert::AreEqual(m01I, matrixI.M01());
			Assert::AreEqual(m10I, matrixI.M10());
			Assert::AreEqual(m11I, matrixI.M11());
		}

		TEST_METHOD(GetColumnTest)
		{
			float m00F = 3.f;
			float m10F = -7.f;
			float m01F = 5.f;
			float m11F = -2.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			auto column0F = matrixF.GetColumn(0);
			auto column1F = matrixF.GetColumn(1);
			Assert::AreEqual(m00F, column0F.X());
			Assert::AreEqual(m10F, column0F.Y());
			Assert::AreEqual(m01F, column1F.X());
			Assert::AreEqual(m11F, column1F.Y());

			short m00I = 3;
			short m10I = -7;
			short m01I = 5;
			short m11I = -2;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			auto column0I = matrixI.GetColumn(0);
			auto column1I = matrixI.GetColumn(1);
			Assert::AreEqual(m00I, column0I.X());
			Assert::AreEqual(m10I, column0I.Y());
			Assert::AreEqual(m01I, column1I.X());
			Assert::AreEqual(m11I, column1I.Y());
		}

		TEST_METHOD(SetColumnTest)
		{
			float m00F = 3.f;
			float m10F = -7.f;
			float m01F = 5.f;
			float m11F = -2.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>();
			auto column0F = PonyEngine::Math::Vector2<float>(m00F, m10F);
			auto column1F = PonyEngine::Math::Vector2<float>(m01F, m11F);
			matrixF.SetColumn(0, column0F);
			matrixF.SetColumn(1, column1F);
			Assert::AreEqual(m00F, matrixF.M00());
			Assert::AreEqual(m01F, matrixF.M01());
			Assert::AreEqual(m10F, matrixF.M10());
			Assert::AreEqual(m11F, matrixF.M11());

			short m00I = 3;
			short m10I = -7;
			short m01I = 5;
			short m11I = -2;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>();
			auto column0I = PonyEngine::Math::Vector2<short>(m00I, m10I);
			auto column1I = PonyEngine::Math::Vector2<short>(m01I, m11I);
			matrixI.SetColumn(0, column0I);
			matrixI.SetColumn(1, column1I);
			Assert::AreEqual(m00I, matrixI.M00());
			Assert::AreEqual(m01I, matrixI.M01());
			Assert::AreEqual(m10I, matrixI.M10());
			Assert::AreEqual(m11I, matrixI.M11());
		}

		TEST_METHOD(GetDiagonalTest)
		{
			float m00F = 3.f;
			float m10F = -7.f;
			float m01F = 5.f;
			float m11F = -2.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			auto diagonalF = matrixF.GetDiagonal();
			Assert::AreEqual(m00F, diagonalF.X());
			Assert::AreEqual(m11F, diagonalF.Y());

			short m00I = 3;
			short m10I = -7;
			short m01I = 5;
			short m11I = -2;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			auto diagonalI = matrixI.GetDiagonal();
			Assert::AreEqual(m00I, diagonalI.X());
			Assert::AreEqual(m11I, diagonalI.Y());
		}

		TEST_METHOD(SetDiagonalTest)
		{
			float m00F = 3.f;
			float m11F = -2.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>();
			auto diagonalF = PonyEngine::Math::Vector2<float>(m00F, m11F);
			matrixF.SetDiagonal(diagonalF);
			Assert::AreEqual(m00F, matrixF.M00());
			Assert::AreEqual(m11F, matrixF.M11());

			short m00I = 3;
			short m11I = -2;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>();
			auto diagonalI = PonyEngine::Math::Vector2<short>(m00I, m11I);
			matrixI.SetDiagonal(diagonalI);
			Assert::AreEqual(m00I, matrixI.M00());
			Assert::AreEqual(m11I, matrixI.M11());
		}

		TEST_METHOD(GetCounterDiagonalTest)
		{
			float m00F = 3.f;
			float m10F = -7.f;
			float m01F = 5.f;
			float m11F = -2.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			auto diagonalF = matrixF.GetCounterDiagonal();
			Assert::AreEqual(m01F, diagonalF.X());
			Assert::AreEqual(m10F, diagonalF.Y());

			short m00I = 3;
			short m10I = -7;
			short m01I = 5;
			short m11I = -2;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			auto diagonalI = matrixI.GetCounterDiagonal();
			Assert::AreEqual(m01I, diagonalI.X());
			Assert::AreEqual(m10I, diagonalI.Y());
		}

		TEST_METHOD(SetCounterDiagonalTest)
		{
			float m01F = 3.f;
			float m10F = -2.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>();
			auto diagonalF = PonyEngine::Math::Vector2<float>(m01F, m10F);
			matrixF.SetCounterDiagonal(diagonalF);
			Assert::AreEqual(m01F, matrixF.M01());
			Assert::AreEqual(m10F, matrixF.M10());

			short m01I = 3;
			short m10I = -2;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>();
			auto diagonalI = PonyEngine::Math::Vector2<short>(m01I, m10I);
			matrixI.SetCounterDiagonal(diagonalI);
			Assert::AreEqual(m01I, matrixI.M01());
			Assert::AreEqual(m10I, matrixI.M10());
		}

		TEST_METHOD(ToStringTest)
		{
			float m00F = 3.f;
			float m10F = -7.f;
			float m01F = 5.f;
			float m11F = -2.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			auto expectedStringF = std::format("({}, {})({}, {})", m00F, m01F, m10F, m11F);
			Assert::AreEqual(expectedStringF, matrixF.ToString());
			std::ostringstream ssF;
			ssF << matrixF;
			Assert::AreEqual(expectedStringF, ssF.str());

			short m00I = 3;
			short m10I = -7;
			short m01I = 5;
			short m11I = -2;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			auto expectedStringI = std::format("({}, {})({}, {})", m00I, m01I, m10I, m11I);
			Assert::AreEqual(expectedStringI, matrixI.ToString());
			std::ostringstream ssI;
			ssI << matrixI;
			Assert::AreEqual(expectedStringI, ssI.str());
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			auto matrix0 = PonyEngine::Math::Matrix2x2<float>(1.f, 1.f, 1.f, 1.f);
			auto matrix1 = matrix0;

			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(matrix0, matrix1));

			matrix1.M00() = std::nextafter(matrix1.M00(), 0.f);
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(matrix0, matrix1));

			matrix1.M00() = 0.f;
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(matrix0, matrix1, 5.f));

			Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(matrix0, matrix1));
		}

		TEST_METHOD(AccessOperatorTest)
		{
			float m00F = 4.f;
			float m10F = -3.f;
			float m01F = 6.f;
			float m11F = 5.f;
			auto matrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			Assert::AreEqual(matrixF.M00(), matrixF[0][0]);
			Assert::AreEqual(matrixF.M10(), matrixF[1][0]);
			Assert::AreEqual(matrixF.M01(), matrixF[0][1]);
			Assert::AreEqual(matrixF.M11(), matrixF[1][1]);

			PonyEngine::Math::Vector2<float> rowF = matrixF[1];
			Assert::AreEqual(m10F, rowF.X());
			Assert::AreEqual(m11F, rowF.Y());

			matrixF[0][0] = matrixF[1][0] = matrixF[0][1] = matrixF[1][1] = 10.f;
			Assert::AreEqual(10.f, matrixF[0][0]);
			Assert::AreEqual(10.f, matrixF[1][0]);
			Assert::AreEqual(10.f, matrixF[0][1]);
			Assert::AreEqual(10.f, matrixF[1][1]);

			const auto constMatrixF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			Assert::AreEqual(constMatrixF.M00(), constMatrixF[0][0]);
			Assert::AreEqual(constMatrixF.M10(), constMatrixF[1][0]);
			Assert::AreEqual(constMatrixF.M01(), constMatrixF[0][1]);
			Assert::AreEqual(constMatrixF.M11(), constMatrixF[1][1]);

			PonyEngine::Math::Vector2<float> constRowF = constMatrixF[1];
			Assert::AreEqual(m10F, constRowF.X());
			Assert::AreEqual(m11F, constRowF.Y());

			Assert::AreEqual(std::size_t{2}, PonyEngine::Math::Matrix2x2<float>::RowCount);
			Assert::AreEqual(std::size_t{2}, PonyEngine::Math::Matrix2x2<float>::ColumnCount);
			Assert::AreEqual(std::size_t{4}, PonyEngine::Math::Matrix2x2<float>::ComponentCount);

			short m00I = 4;
			short m10I = -3;
			short m01I = 6;
			short m11I = 5;
			auto matrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			Assert::AreEqual(matrixI.M00(), matrixI[0][0]);
			Assert::AreEqual(matrixI.M10(), matrixI[1][0]);
			Assert::AreEqual(matrixI.M01(), matrixI[0][1]);
			Assert::AreEqual(matrixI.M11(), matrixI[1][1]);

			PonyEngine::Math::Vector2<short> rowI = matrixI[1];
			Assert::AreEqual(m10I, rowI.X());
			Assert::AreEqual(m11I, rowI.Y());

			matrixI[0][0] = matrixI[1][0] = matrixI[0][1] = matrixI[1][1] = 10;
			Assert::AreEqual(short{10}, matrixI[0][0]);
			Assert::AreEqual(short{10}, matrixI[1][0]);
			Assert::AreEqual(short{10}, matrixI[0][1]);
			Assert::AreEqual(short{10}, matrixI[1][1]);

			const auto constMatrixI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			Assert::AreEqual(constMatrixI.M00(), constMatrixI[0][0]);
			Assert::AreEqual(constMatrixI.M10(), constMatrixI[1][0]);
			Assert::AreEqual(constMatrixI.M01(), constMatrixI[0][1]);
			Assert::AreEqual(constMatrixI.M11(), constMatrixI[1][1]);

			PonyEngine::Math::Vector2<short> constRowI = constMatrixI[1];
			Assert::AreEqual(m10I, constRowI.X());
			Assert::AreEqual(m11I, constRowI.Y());

			Assert::AreEqual(std::size_t{2}, PonyEngine::Math::Matrix2x2<short>::RowCount);
			Assert::AreEqual(std::size_t{2}, PonyEngine::Math::Matrix2x2<short>::ColumnCount);
			Assert::AreEqual(std::size_t{4}, PonyEngine::Math::Matrix2x2<short>::ComponentCount);
		}

		TEST_METHOD(AssignmentOperatorsTest)
		{
			float m00F = 4.f;
			float m10F = -3.f;
			float m01F = 6.f;
			float m11F = 5.f;
			auto rightF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			auto centerF = PonyEngine::Math::Matrix2x2<float>();
			auto leftF = centerF = rightF;
			Assert::AreEqual(m00F, centerF.M00());
			Assert::AreEqual(m10F, centerF.M10());
			Assert::AreEqual(m01F, centerF.M01());
			Assert::AreEqual(m11F, centerF.M11());
			Assert::AreEqual(m00F, leftF.M00());
			Assert::AreEqual(m10F, leftF.M10());
			Assert::AreEqual(m01F, leftF.M01());
			Assert::AreEqual(m11F, leftF.M11());

			float m00CF = 14.f;
			float m10CF = -13.f;
			float m01CF = 16.f;
			float m11CF = 15.f;
			centerF = PonyEngine::Math::Matrix2x2<float>(m00CF, m10CF, m01CF, m11CF);
			leftF = centerF += rightF;
			Assert::AreEqual(m00F + m00CF, centerF.M00());
			Assert::AreEqual(m10F + m10CF, centerF.M10());
			Assert::AreEqual(m01F + m01CF, centerF.M01());
			Assert::AreEqual(m11F + m11CF, centerF.M11());
			Assert::AreEqual(m00F + m00CF, leftF.M00());
			Assert::AreEqual(m10F + m10CF, leftF.M10());
			Assert::AreEqual(m01F + m01CF, leftF.M01());
			Assert::AreEqual(m11F + m11CF, leftF.M11());

			centerF = PonyEngine::Math::Matrix2x2<float>(m00CF, m10CF, m01CF, m11CF);
			leftF = centerF -= rightF;
			Assert::AreEqual(m00CF - m00F, centerF.M00());
			Assert::AreEqual(m10CF - m10F, centerF.M10());
			Assert::AreEqual(m01CF - m01F, centerF.M01());
			Assert::AreEqual(m11CF - m11F, centerF.M11());
			Assert::AreEqual(m00CF - m00F, leftF.M00());
			Assert::AreEqual(m10CF - m10F, leftF.M10());
			Assert::AreEqual(m01CF - m01F, leftF.M01());
			Assert::AreEqual(m11CF - m11F, leftF.M11());

			float multiplierF = 3.f;
			centerF = PonyEngine::Math::Matrix2x2<float>(m00CF, m10CF, m01CF, m11CF);
			leftF = centerF *= multiplierF;
			Assert::AreEqual(m00CF * multiplierF, centerF.M00());
			Assert::AreEqual(m10CF * multiplierF, centerF.M10());
			Assert::AreEqual(m01CF * multiplierF, centerF.M01());
			Assert::AreEqual(m11CF * multiplierF, centerF.M11());
			Assert::AreEqual(m00CF * multiplierF, leftF.M00());
			Assert::AreEqual(m10CF * multiplierF, leftF.M10());
			Assert::AreEqual(m01CF * multiplierF, leftF.M01());
			Assert::AreEqual(m11CF * multiplierF, leftF.M11());

			centerF = PonyEngine::Math::Matrix2x2<float>(m00CF, m10CF, m01CF, m11CF);
			leftF = centerF *= rightF;
			Assert::AreEqual(m00CF * m00F + m01CF * m10F, centerF.M00());
			Assert::AreEqual(m10CF * m00F + m11CF * m10F, centerF.M10());
			Assert::AreEqual(m00CF * m01F + m01CF * m11F, centerF.M01());
			Assert::AreEqual(m10CF * m01F + m11CF * m11F, centerF.M11());
			Assert::AreEqual(m00CF * m00F + m01CF * m10F, leftF.M00());
			Assert::AreEqual(m10CF * m00F + m11CF * m10F, leftF.M10());
			Assert::AreEqual(m00CF * m01F + m01CF * m11F, leftF.M01());
			Assert::AreEqual(m10CF * m01F + m11CF * m11F, leftF.M11());

			centerF = PonyEngine::Math::Matrix2x2<float>(m00CF, m10CF, m01CF, m11CF);
			leftF = centerF /= multiplierF;
			Assert::AreEqual(m00CF / multiplierF, centerF.M00());
			Assert::AreEqual(m10CF / multiplierF, centerF.M10());
			Assert::AreEqual(m01CF / multiplierF, centerF.M01());
			Assert::AreEqual(m11CF / multiplierF, centerF.M11());
			Assert::AreEqual(m00CF / multiplierF, leftF.M00());
			Assert::AreEqual(m10CF / multiplierF, leftF.M10());
			Assert::AreEqual(m01CF / multiplierF, leftF.M01());
			Assert::AreEqual(m11CF / multiplierF, leftF.M11());

			short m00I = 4;
			short m10I = -3;
			short m01I = 6;
			short m11I = 5;
			auto rightI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			auto centerI = PonyEngine::Math::Matrix2x2<short>();
			auto leftI = centerI = rightI;
			Assert::AreEqual(m00I, centerI.M00());
			Assert::AreEqual(m10I, centerI.M10());
			Assert::AreEqual(m01I, centerI.M01());
			Assert::AreEqual(m11I, centerI.M11());
			Assert::AreEqual(m00I, leftI.M00());
			Assert::AreEqual(m10I, leftI.M10());
			Assert::AreEqual(m01I, leftI.M01());
			Assert::AreEqual(m11I, leftI.M11());

			short m00CI = 14;
			short m10CI = -13;
			short m01CI = 16;
			short m11CI = 15;
			centerI = PonyEngine::Math::Matrix2x2<short>(m00CI, m10CI, m01CI, m11CI);
			leftI = centerI += rightI;
			Assert::AreEqual(static_cast<short>(m00I + m00CI), centerI.M00());
			Assert::AreEqual(static_cast<short>(m10I + m10CI), centerI.M10());
			Assert::AreEqual(static_cast<short>(m01I + m01CI), centerI.M01());
			Assert::AreEqual(static_cast<short>(m11I + m11CI), centerI.M11());
			Assert::AreEqual(static_cast<short>(m00I + m00CI), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10I + m10CI), leftI.M10());
			Assert::AreEqual(static_cast<short>(m01I + m01CI), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11I + m11CI), leftI.M11());

			centerI = PonyEngine::Math::Matrix2x2<short>(m00CI, m10CI, m01CI, m11CI);
			leftI = centerI -= rightI;
			Assert::AreEqual(static_cast<short>(m00CI - m00I), centerI.M00());
			Assert::AreEqual(static_cast<short>(m10CI - m10I), centerI.M10());
			Assert::AreEqual(static_cast<short>(m01CI - m01I), centerI.M01());
			Assert::AreEqual(static_cast<short>(m11CI - m11I), centerI.M11());
			Assert::AreEqual(static_cast<short>(m00CI - m00I), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI - m10I), leftI.M10());
			Assert::AreEqual(static_cast<short>(m01CI - m01I), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI - m11I), leftI.M11());

			short multiplierI = 3;
			centerI = PonyEngine::Math::Matrix2x2<short>(m00CI, m10CI, m01CI, m11CI);
			leftI = centerI *= multiplierI;
			Assert::AreEqual(static_cast<short>(m00CI * multiplierI), centerI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierI), centerI.M10());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierI), centerI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierI), centerI.M11());
			Assert::AreEqual(static_cast<short>(m00CI * multiplierI), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierI), leftI.M10());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierI), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierI), leftI.M11());

			centerI = PonyEngine::Math::Matrix2x2<short>(m00CI, m10CI, m01CI, m11CI);
			leftI = centerI *= multiplierF;
			Assert::AreEqual(static_cast<short>(m00CI * multiplierF), centerI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierF), centerI.M10());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierF), centerI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierF), centerI.M11());
			Assert::AreEqual(static_cast<short>(m00CI * multiplierF), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierF), leftI.M10());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierF), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierF), leftI.M11());

			centerI = PonyEngine::Math::Matrix2x2<short>(m00CI, m10CI, m01CI, m11CI);
			leftI = centerI *= rightI;
			Assert::AreEqual(static_cast<short>(m00CI * m00I + m01CI * m10I), centerI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * m00I + m11CI * m10I), centerI.M10());
			Assert::AreEqual(static_cast<short>(m00CI * m01I + m01CI * m11I), centerI.M01());
			Assert::AreEqual(static_cast<short>(m10CI * m01I + m11CI * m11I), centerI.M11());
			Assert::AreEqual(static_cast<short>(m00CI * m00I + m01CI * m10I), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * m00I + m11CI * m10I), leftI.M10());
			Assert::AreEqual(static_cast<short>(m00CI * m01I + m01CI * m11I), leftI.M01());
			Assert::AreEqual(static_cast<short>(m10CI * m01I + m11CI * m11I), leftI.M11());

			centerI = PonyEngine::Math::Matrix2x2<short>(m00CI, m10CI, m01CI, m11CI);
			leftI = centerI /= multiplierF;
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m00CI / multiplierF), centerI.M00());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m10CI / multiplierF), centerI.M10());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m01CI / multiplierF), centerI.M01());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m11CI / multiplierF), centerI.M11());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m00CI / multiplierF), leftI.M00());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m10CI / multiplierF), leftI.M10());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m01CI / multiplierF), leftI.M01());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m11CI / multiplierF), leftI.M11());
		}

		TEST_METHOD(EqualityOperatorsTest)
		{
			float m00F = 4.f;
			float m10F = -3.f;
			float m01F = 6.f;
			float m11F = 5.f;
			auto rightF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			auto leftF = rightF;
			Assert::IsTrue(leftF == rightF);
			Assert::IsFalse(leftF != rightF);

			leftF.M00() += 1.f;
			Assert::IsFalse(leftF == rightF);
			Assert::IsTrue(leftF != rightF);

			leftF.M00() = m00F;
			leftF.M01() += 1.f;
			Assert::IsFalse(leftF == rightF);
			Assert::IsTrue(leftF != rightF);

			leftF.M01() = m10F;
			leftF.M10() += 1.f;
			Assert::IsFalse(leftF == rightF);
			Assert::IsTrue(leftF != rightF);

			leftF.M10() = m10F;
			leftF.M11() += 1.f;
			Assert::IsFalse(leftF == rightF);
			Assert::IsTrue(leftF != rightF);

			short m00I = 4;
			short m10I = -3;
			short m01I = 6;
			short m11I = 5;
			auto rightI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			auto leftI = rightI;
			Assert::IsTrue(leftI == rightI);
			Assert::IsFalse(leftI != rightI);

			leftI.M00() += 1;
			Assert::IsFalse(leftI == rightI);
			Assert::IsTrue(leftI != rightI);

			leftI.M00() = m00I;
			leftI.M01() += 1;
			Assert::IsFalse(leftI == rightI);
			Assert::IsTrue(leftI != rightI);

			leftI.M01() = m10I;
			leftI.M10() += 1;
			Assert::IsFalse(leftI == rightI);
			Assert::IsTrue(leftI != rightI);

			leftI.M10() = m10I;
			leftI.M11() += 1;
			Assert::IsFalse(leftI == rightI);
			Assert::IsTrue(leftI != rightI);
		}

		TEST_METHOD(ComputationalOperatorsTest)
		{
			float m00F = 4.f;
			float m10F = -3.f;
			float m01F = 6.f;
			float m11F = 5.f;
			float m00CF = 14.f;
			float m10CF = -13.f;
			float m01CF = 16.f;
			float m11CF = 15.f;
			auto rightF = PonyEngine::Math::Matrix2x2<float>(m00F, m10F, m01F, m11F);
			auto centerF = PonyEngine::Math::Matrix2x2<float>(m00CF, m10CF, m01CF, m11CF);
			auto leftF = centerF + rightF;
			Assert::AreEqual(m00F + m00CF, leftF.M00());
			Assert::AreEqual(m10F + m10CF, leftF.M10());
			Assert::AreEqual(m01F + m01CF, leftF.M01());
			Assert::AreEqual(m11F + m11CF, leftF.M11());

			leftF = centerF - rightF;
			Assert::AreEqual(m00CF - m00F, leftF.M00());
			Assert::AreEqual(m10CF - m10F, leftF.M10());
			Assert::AreEqual(m01CF - m01F, leftF.M01());
			Assert::AreEqual(m11CF - m11F, leftF.M11());

			float multiplierF = 3.f;
			centerF = PonyEngine::Math::Matrix2x2<float>(m00CF, m10CF, m01CF, m11CF);
			leftF = centerF * multiplierF;
			Assert::AreEqual(m00CF * multiplierF, leftF.M00());
			Assert::AreEqual(m10CF * multiplierF, leftF.M10());
			Assert::AreEqual(m01CF * multiplierF, leftF.M01());
			Assert::AreEqual(m11CF * multiplierF, leftF.M11());
			leftF = multiplierF * centerF;
			Assert::AreEqual(m00CF * multiplierF, leftF.M00());
			Assert::AreEqual(m10CF * multiplierF, leftF.M10());
			Assert::AreEqual(m01CF * multiplierF, leftF.M01());
			Assert::AreEqual(m11CF * multiplierF, leftF.M11());

			centerF = PonyEngine::Math::Matrix2x2<float>(m00CF, m10CF, m01CF, m11CF);
			leftF = centerF * rightF;
			Assert::AreEqual(m00CF * m00F + m01CF * m10F, leftF.M00());
			Assert::AreEqual(m10CF * m00F + m11CF * m10F, leftF.M10());
			Assert::AreEqual(m00CF * m01F + m01CF * m11F, leftF.M01());
			Assert::AreEqual(m10CF * m01F + m11CF * m11F, leftF.M11());

			centerF = PonyEngine::Math::Matrix2x2<float>(m00CF, m10CF, m01CF, m11CF);
			leftF = centerF / multiplierF;
			Assert::AreEqual(m00CF / multiplierF, leftF.M00());
			Assert::AreEqual(m10CF / multiplierF, leftF.M10());
			Assert::AreEqual(m01CF / multiplierF, leftF.M01());
			Assert::AreEqual(m11CF / multiplierF, leftF.M11());

			short m00I = 4;
			short m10I = -3;
			short m01I = 6;
			short m11I = 5;
			auto rightI = PonyEngine::Math::Matrix2x2<short>(m00I, m10I, m01I, m11I);
			short m00CI = 14;
			short m10CI = -13;
			short m01CI = 16;
			short m11CI = 15;
			auto centerI = PonyEngine::Math::Matrix2x2<short>(m00CI, m10CI, m01CI, m11CI);
			auto leftI = centerI + rightI;
			Assert::AreEqual(static_cast<short>(m00I + m00CI), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10I + m10CI), leftI.M10());
			Assert::AreEqual(static_cast<short>(m01I + m01CI), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11I + m11CI), leftI.M11());

			centerI = PonyEngine::Math::Matrix2x2<short>(m00CI, m10CI, m01CI, m11CI);
			leftI = centerI - rightI;
			Assert::AreEqual(static_cast<short>(m00CI - m00I), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI - m10I), leftI.M10());
			Assert::AreEqual(static_cast<short>(m01CI - m01I), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI - m11I), leftI.M11());

			short multiplierI = 3;
			centerI = PonyEngine::Math::Matrix2x2<short>(m00CI, m10CI, m01CI, m11CI);
			leftI = centerI * multiplierI;
			Assert::AreEqual(static_cast<short>(m00CI * multiplierI), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierI), leftI.M10());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierI), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierI), leftI.M11());
			leftI = multiplierI * centerI;
			Assert::AreEqual(static_cast<short>(m00CI * multiplierI), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierI), leftI.M10());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierI), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierI), leftI.M11());

			centerI = PonyEngine::Math::Matrix2x2<short>(m00CI, m10CI, m01CI, m11CI);
			leftI = centerI * multiplierF;
			Assert::AreEqual(static_cast<short>(m00CI * multiplierF), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierF), leftI.M10());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierF), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierF), leftI.M11());
			leftI = multiplierF * centerI;
			Assert::AreEqual(static_cast<short>(m00CI * multiplierF), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierF), leftI.M10());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierF), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierF), leftI.M11());

			centerI = PonyEngine::Math::Matrix2x2<short>(m00CI, m10CI, m01CI, m11CI);
			leftI = centerI * rightI;
			Assert::AreEqual(static_cast<short>(m00CI * m00I + m01CI * m10I), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * m00I + m11CI * m10I), leftI.M10());
			Assert::AreEqual(static_cast<short>(m00CI * m01I + m01CI * m11I), leftI.M01());
			Assert::AreEqual(static_cast<short>(m10CI * m01I + m11CI * m11I), leftI.M11());

			centerI = PonyEngine::Math::Matrix2x2<short>(m00CI, m10CI, m01CI, m11CI);
			leftI = centerI / multiplierF;
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m00CI / multiplierF), leftI.M00());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m10CI / multiplierF), leftI.M10());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m01CI / multiplierF), leftI.M01());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m11CI / multiplierF), leftI.M11());
		}

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

		TEST_METHOD(DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix2x2<float>::Identity == PonyEngine::Math::Matrix2x2<float>(1, 0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Matrix2x2<float>::Zero == PonyEngine::Math::Matrix2x2<float>(0, 0, 0, 0));

			Assert::IsTrue(PonyEngine::Math::Matrix2x2<short>::Identity == PonyEngine::Math::Matrix2x2<short>(1, 0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Matrix2x2<short>::Zero == PonyEngine::Math::Matrix2x2<short>(0, 0, 0, 0));
		}

		TEST_METHOD(ConstexprTest)
		{
#pragma warning(disable:4189)
			constexpr auto defaultMatrix = PonyEngine::Math::Matrix2x2<float>();
			constexpr auto matrix = PonyEngine::Math::Matrix2x2<float>(2, 3, -1, 5);
			constexpr auto columnMatrix = PonyEngine::Math::Matrix2x2<float>(PonyEngine::Math::Vector2<float>(2, 3), PonyEngine::Math::Vector2<float>(-1, 5));
			constexpr auto copiedMatrix = matrix;

			constexpr auto m00 = matrix.M00();
			constexpr auto m10 = matrix.M10();
			constexpr auto m01 = matrix.M01();
			constexpr auto m11 = matrix.M11();

			constexpr auto determinant = matrix.Determinant();
			constexpr auto adjugate = matrix.Adjugate();
			constexpr auto transposed = matrix.Transposed();
			constexpr auto inversed = matrix.Inversed();

			constexpr auto row = matrix.GetRow(1);
			constexpr auto column = matrix.GetColumn(1);
			constexpr auto diagonal = matrix.GetDiagonal();
			constexpr auto counterDiagonal = matrix.GetCounterDiagonal();

			constexpr auto element = matrix[1][0];

			constexpr auto equal = matrix == copiedMatrix;
			constexpr auto notEqual = matrix != copiedMatrix;

			constexpr auto scaled = PonyEngine::Math::Scale(matrix, copiedMatrix);
			constexpr auto almostEqual = PonyEngine::Math::AreAlmostEqual(matrix, copiedMatrix);

			constexpr auto sum = matrix + copiedMatrix;
			constexpr auto negative = -matrix;
			constexpr auto sub = matrix - copiedMatrix;
			constexpr auto multipliedL = matrix * 3.f;
			constexpr auto multipliedR = 3.f * matrix;
			constexpr auto multiplied = matrix * copiedMatrix;
			constexpr auto multipliedV = matrix * column;

			constexpr auto multipliedLI = PonyEngine::Math::Matrix2x2<short>(2, 3, -1, 2) * 3;
			constexpr auto multipliedRI = 3 * PonyEngine::Math::Matrix2x2<short>(2, 3, -1, 2);

			constexpr auto divided = matrix / 3.f;
#pragma warning(default:4189)
		}
	};
}
