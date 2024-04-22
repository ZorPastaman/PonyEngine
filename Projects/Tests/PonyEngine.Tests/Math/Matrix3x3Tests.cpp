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
	TEST_CLASS(Matrix3x3Tests)
	{
		TEST_METHOD(ConstructorTest)
		{
			auto defaultMatrixF = PonyEngine::Math::Matrix3x3<float>();
			Assert::AreEqual(float{}, defaultMatrixF.M00());
			Assert::AreEqual(float{}, defaultMatrixF.M10());
			Assert::AreEqual(float{}, defaultMatrixF.M20());
			Assert::AreEqual(float{}, defaultMatrixF.M01());
			Assert::AreEqual(float{}, defaultMatrixF.M11());
			Assert::AreEqual(float{}, defaultMatrixF.M21());
			Assert::AreEqual(float{}, defaultMatrixF.M02());
			Assert::AreEqual(float{}, defaultMatrixF.M12());
			Assert::AreEqual(float{}, defaultMatrixF.M22());

			float m00F = 3.f;
			float m10F = -4.f;
			float m20F = 4.f;
			float m01F = 6.f;
			float m11F = -6.f;
			float m21F = 1.f;
			float m02F = -9.f;
			float m12F = -4.f;
			float m22F = 2.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			Assert::AreEqual(m00F, matrixF.M00());
			Assert::AreEqual(m10F, matrixF.M10());
			Assert::AreEqual(m20F, matrixF.M20());
			Assert::AreEqual(m01F, matrixF.M01());
			Assert::AreEqual(m11F, matrixF.M11());
			Assert::AreEqual(m21F, matrixF.M21());
			Assert::AreEqual(m02F, matrixF.M02());
			Assert::AreEqual(m12F, matrixF.M12());
			Assert::AreEqual(m22F, matrixF.M22());

			auto column0F = PonyEngine::Math::Vector3<float>(m00F, m10F, m20F);
			auto column1F = PonyEngine::Math::Vector3<float>(m01F, m11F, m21F);
			auto column2F = PonyEngine::Math::Vector3<float>(m02F, m12F, m22F);
			auto columnMatrixF = PonyEngine::Math::Matrix3x3<float>(column0F, column1F, column2F);
			Assert::AreEqual(m00F, columnMatrixF.M00());
			Assert::AreEqual(m10F, columnMatrixF.M10());
			Assert::AreEqual(m20F, columnMatrixF.M20());
			Assert::AreEqual(m01F, columnMatrixF.M01());
			Assert::AreEqual(m11F, columnMatrixF.M11());
			Assert::AreEqual(m21F, columnMatrixF.M21());
			Assert::AreEqual(m02F, columnMatrixF.M02());
			Assert::AreEqual(m12F, columnMatrixF.M12());
			Assert::AreEqual(m22F, columnMatrixF.M22());

			auto copiedMatrixF = matrixF;
			Assert::AreEqual(m00F, copiedMatrixF.M00());
			Assert::AreEqual(m10F, copiedMatrixF.M10());
			Assert::AreEqual(m20F, copiedMatrixF.M20());
			Assert::AreEqual(m01F, copiedMatrixF.M01());
			Assert::AreEqual(m11F, copiedMatrixF.M11());
			Assert::AreEqual(m21F, copiedMatrixF.M21());
			Assert::AreEqual(m02F, copiedMatrixF.M02());
			Assert::AreEqual(m12F, copiedMatrixF.M12());
			Assert::AreEqual(m22F, copiedMatrixF.M22());

			auto defaultMatrixI = PonyEngine::Math::Matrix3x3<short>();
			Assert::AreEqual(short{}, defaultMatrixI.M00());
			Assert::AreEqual(short{}, defaultMatrixI.M10());
			Assert::AreEqual(short{}, defaultMatrixI.M20());
			Assert::AreEqual(short{}, defaultMatrixI.M01());
			Assert::AreEqual(short{}, defaultMatrixI.M11());
			Assert::AreEqual(short{}, defaultMatrixI.M21());
			Assert::AreEqual(short{}, defaultMatrixI.M02());
			Assert::AreEqual(short{}, defaultMatrixI.M12());
			Assert::AreEqual(short{}, defaultMatrixI.M22());

			short m00I = 3;
			short m10I = -4;
			short m20I = 4;
			short m01I = 6;
			short m11I = -6;
			short m21I = 1;
			short m02I = -9;
			short m12I = -4;
			short m22I = 2;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			Assert::AreEqual(m00I, matrixI.M00());
			Assert::AreEqual(m10I, matrixI.M10());
			Assert::AreEqual(m20I, matrixI.M20());
			Assert::AreEqual(m01I, matrixI.M01());
			Assert::AreEqual(m11I, matrixI.M11());
			Assert::AreEqual(m21I, matrixI.M21());
			Assert::AreEqual(m02I, matrixI.M02());
			Assert::AreEqual(m12I, matrixI.M12());
			Assert::AreEqual(m22I, matrixI.M22());

			auto column0I = PonyEngine::Math::Vector3<short>(m00I, m10I, m20I);
			auto column1I = PonyEngine::Math::Vector3<short>(m01I, m11I, m21I);
			auto column2I = PonyEngine::Math::Vector3<short>(m02I, m12I, m22I);
			auto columnMatrixI = PonyEngine::Math::Matrix3x3<short>(column0I, column1I, column2I);
			Assert::AreEqual(m00I, columnMatrixI.M00());
			Assert::AreEqual(m10I, columnMatrixI.M10());
			Assert::AreEqual(m20I, columnMatrixI.M20());
			Assert::AreEqual(m01I, columnMatrixI.M01());
			Assert::AreEqual(m11I, columnMatrixI.M11());
			Assert::AreEqual(m21I, columnMatrixI.M21());
			Assert::AreEqual(m02I, columnMatrixI.M02());
			Assert::AreEqual(m12I, columnMatrixI.M12());
			Assert::AreEqual(m22I, columnMatrixI.M22());

			auto copiedMatrixI = matrixI;
			Assert::AreEqual(m00I, copiedMatrixI.M00());
			Assert::AreEqual(m10I, copiedMatrixI.M10());
			Assert::AreEqual(m20I, copiedMatrixI.M20());
			Assert::AreEqual(m01I, copiedMatrixI.M01());
			Assert::AreEqual(m11I, copiedMatrixI.M11());
			Assert::AreEqual(m21I, copiedMatrixI.M21());
			Assert::AreEqual(m02I, copiedMatrixI.M02());
			Assert::AreEqual(m12I, copiedMatrixI.M12());
			Assert::AreEqual(m22I, copiedMatrixI.M22());
		}

		TEST_METHOD(DataTest)
		{
			float m00F = 3.f;
			float m10F = -4.f;
			float m20F = 4.f;
			float m01F = 6.f;
			float m11F = -6.f;
			float m21F = 1.f;
			float m02F = -9.f;
			float m12F = -4.f;
			float m22F = 2.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			Assert::AreEqual(m00F, matrixF.Data()[0]);
			Assert::AreEqual(m10F, matrixF.Data()[1]);
			Assert::AreEqual(m20F, matrixF.Data()[2]);
			Assert::AreEqual(m01F, matrixF.Data()[3]);
			Assert::AreEqual(m11F, matrixF.Data()[4]);
			Assert::AreEqual(m21F, matrixF.Data()[5]);
			Assert::AreEqual(m02F, matrixF.Data()[6]);
			Assert::AreEqual(m12F, matrixF.Data()[7]);
			Assert::AreEqual(m22F, matrixF.Data()[8]);

			const auto matrixCF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			Assert::AreEqual(m00F, matrixCF.Data()[0]);
			Assert::AreEqual(m10F, matrixCF.Data()[1]);
			Assert::AreEqual(m20F, matrixCF.Data()[2]);
			Assert::AreEqual(m01F, matrixCF.Data()[3]);
			Assert::AreEqual(m11F, matrixCF.Data()[4]);
			Assert::AreEqual(m21F, matrixCF.Data()[5]);
			Assert::AreEqual(m02F, matrixCF.Data()[6]);
			Assert::AreEqual(m12F, matrixCF.Data()[7]);
			Assert::AreEqual(m22F, matrixCF.Data()[8]);

			short m00I = 3;
			short m10I = -4;
			short m20I = 4;
			short m01I = 6;
			short m11I = -6;
			short m21I = 1;
			short m02I = -9;
			short m12I = -4;
			short m22I = 2;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			Assert::AreEqual(m00I, matrixI.Data()[0]);
			Assert::AreEqual(m10I, matrixI.Data()[1]);
			Assert::AreEqual(m20I, matrixI.Data()[2]);
			Assert::AreEqual(m01I, matrixI.Data()[3]);
			Assert::AreEqual(m11I, matrixI.Data()[4]);
			Assert::AreEqual(m21I, matrixI.Data()[5]);
			Assert::AreEqual(m02I, matrixI.Data()[6]);
			Assert::AreEqual(m12I, matrixI.Data()[7]);
			Assert::AreEqual(m22I, matrixI.Data()[8]);

			const auto matrixCI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			Assert::AreEqual(m00I, matrixCI.Data()[0]);
			Assert::AreEqual(m10I, matrixCI.Data()[1]);
			Assert::AreEqual(m20I, matrixCI.Data()[2]);
			Assert::AreEqual(m01I, matrixCI.Data()[3]);
			Assert::AreEqual(m11I, matrixCI.Data()[4]);
			Assert::AreEqual(m21I, matrixCI.Data()[5]);
			Assert::AreEqual(m02I, matrixCI.Data()[6]);
			Assert::AreEqual(m12I, matrixCI.Data()[7]);
			Assert::AreEqual(m22I, matrixCI.Data()[8]);
		}

		TEST_METHOD(DeterminantTest)
		{
			float m00F = 3.f;
			float m10F = -4.f;
			float m20F = 4.f;
			float m01F = 6.f;
			float m11F = -6.f;
			float m21F = 1.f;
			float m02F = -9.f;
			float m12F = -4.f;
			float m22F = 2.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			Assert::AreEqual(-252.f, matrixF.Determinant());

			short m00I = 3;
			short m10I = -4;
			short m20I = 4;
			short m01I = 6;
			short m11I = -6;
			short m21I = 1;
			short m02I = -9;
			short m12I = -4;
			short m22I = 2;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			Assert::AreEqual(short{-252}, matrixI.Determinant());
		}

		TEST_METHOD(AdjugateTest)
		{
			float m00F = 3.f;
			float m10F = -4.f;
			float m20F = 4.f;
			float m01F = 6.f;
			float m11F = -6.f;
			float m21F = 1.f;
			float m02F = -9.f;
			float m12F = -4.f;
			float m22F = 2.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			auto adjugateF = matrixF.Adjugate();
			Assert::AreEqual(-8.f, adjugateF.M00());
			Assert::AreEqual(-8.f, adjugateF.M10());
			Assert::AreEqual(20.f, adjugateF.M20());
			Assert::AreEqual(-21.f, adjugateF.M01());
			Assert::AreEqual(42.f, adjugateF.M11());
			Assert::AreEqual(21.f, adjugateF.M21());
			Assert::AreEqual(-78.f, adjugateF.M02());
			Assert::AreEqual(48.f, adjugateF.M12());
			Assert::AreEqual(6.f, adjugateF.M22());

			short m00I = 3;
			short m10I = -4;
			short m20I = 4;
			short m01I = 6;
			short m11I = -6;
			short m21I = 1;
			short m02I = -9;
			short m12I = -4;
			short m22I = 2;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			auto adjugateI = matrixI.Adjugate();
			Assert::AreEqual(short{-8}, adjugateI.M00());
			Assert::AreEqual(short{-8}, adjugateI.M10());
			Assert::AreEqual(short{20}, adjugateI.M20());
			Assert::AreEqual(short{-21}, adjugateI.M01());
			Assert::AreEqual(short{42}, adjugateI.M11());
			Assert::AreEqual(short{21}, adjugateI.M21());
			Assert::AreEqual(short{-78}, adjugateI.M02());
			Assert::AreEqual(short{48}, adjugateI.M12());
			Assert::AreEqual(short{6}, adjugateI.M22());
		}

		TEST_METHOD(TransposeTest)
		{
			float m00F = 3.f;
			float m10F = -4.f;
			float m20F = 4.f;
			float m01F = 6.f;
			float m11F = -6.f;
			float m21F = 1.f;
			float m02F = -9.f;
			float m12F = -4.f;
			float m22F = 2.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			auto transposeF = matrixF.Transposed();
			Assert::AreEqual(3.f, transposeF.M00());
			Assert::AreEqual(6.f, transposeF.M10());
			Assert::AreEqual(-9.f, transposeF.M20());
			Assert::AreEqual(-4.f, transposeF.M01());
			Assert::AreEqual(-6.f, transposeF.M11());
			Assert::AreEqual(-4.f, transposeF.M21());
			Assert::AreEqual(4.f, transposeF.M02());
			Assert::AreEqual(1.f, transposeF.M12());
			Assert::AreEqual(2.f, transposeF.M22());

			matrixF.Transpose();
			Assert::AreEqual(transposeF.M00(), matrixF.M00());
			Assert::AreEqual(transposeF.M10(), matrixF.M10());
			Assert::AreEqual(transposeF.M20(), matrixF.M20());
			Assert::AreEqual(transposeF.M01(), matrixF.M01());
			Assert::AreEqual(transposeF.M11(), matrixF.M11());
			Assert::AreEqual(transposeF.M21(), matrixF.M21());
			Assert::AreEqual(transposeF.M02(), matrixF.M02());
			Assert::AreEqual(transposeF.M12(), matrixF.M12());
			Assert::AreEqual(transposeF.M22(), matrixF.M22());

			short m00I = 3;
			short m10I = -4;
			short m20I = 4;
			short m01I = 6;
			short m11I = -6;
			short m21I = 1;
			short m02I = -9;
			short m12I = -4;
			short m22I = 2;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			auto transposeI = matrixI.Transposed();
			Assert::AreEqual(short{3}, transposeI.M00());
			Assert::AreEqual(short{6}, transposeI.M10());
			Assert::AreEqual(short{-9}, transposeI.M20());
			Assert::AreEqual(short{-4}, transposeI.M01());
			Assert::AreEqual(short{-6}, transposeI.M11());
			Assert::AreEqual(short{-4}, transposeI.M21());
			Assert::AreEqual(short{4}, transposeI.M02());
			Assert::AreEqual(short{1}, transposeI.M12());
			Assert::AreEqual(short{2}, transposeI.M22());

			matrixI.Transpose();
			Assert::AreEqual(transposeI.M00(), matrixI.M00());
			Assert::AreEqual(transposeI.M10(), matrixI.M10());
			Assert::AreEqual(transposeI.M20(), matrixI.M20());
			Assert::AreEqual(transposeI.M01(), matrixI.M01());
			Assert::AreEqual(transposeI.M11(), matrixI.M11());
			Assert::AreEqual(transposeI.M21(), matrixI.M21());
			Assert::AreEqual(transposeI.M02(), matrixI.M02());
			Assert::AreEqual(transposeI.M12(), matrixI.M12());
			Assert::AreEqual(transposeI.M22(), matrixI.M22());
		}

		TEST_METHOD(InverseTest)
		{
			float m00F = 3.f;
			float m10F = -4.f;
			float m20F = 4.f;
			float m01F = 6.f;
			float m11F = -6.f;
			float m21F = 1.f;
			float m02F = -9.f;
			float m12F = -4.f;
			float m22F = 2.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			auto inverseF = matrixF.Inversed();
			Assert::AreEqual(static_cast<double>(2.f / 63.f), static_cast<double>(inverseF.M00()), 0.0001);
			Assert::AreEqual(static_cast<double>(2.f / 63.f), static_cast<double>(inverseF.M10()), 0.0001);
			Assert::AreEqual(static_cast<double>(-5.f / 63.f), static_cast<double>(inverseF.M20()), 0.0001);
			Assert::AreEqual(static_cast<double>(1.f / 12.f), static_cast<double>(inverseF.M01()), 0.0001);
			Assert::AreEqual(static_cast<double>(-1.f / 6.f), static_cast<double>(inverseF.M11()), 0.0001);
			Assert::AreEqual(static_cast<double>(-1.f / 12.f), static_cast<double>(inverseF.M21()), 0.0001);
			Assert::AreEqual(static_cast<double>(13.f / 42.f), static_cast<double>(inverseF.M02()), 0.0001);
			Assert::AreEqual(static_cast<double>(-4.f / 21.f), static_cast<double>(inverseF.M12()), 0.0001);
			Assert::AreEqual(static_cast<double>(-1.f / 42.f), static_cast<double>(inverseF.M22()), 0.0001);

			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(matrixF * inverseF, PonyEngine::Math::Matrix3x3<float>::Identity));

			matrixF.Inverse();
			Assert::AreEqual(inverseF.M00(), matrixF.M00());
			Assert::AreEqual(inverseF.M10(), matrixF.M10());
			Assert::AreEqual(inverseF.M20(), matrixF.M20());
			Assert::AreEqual(inverseF.M01(), matrixF.M01());
			Assert::AreEqual(inverseF.M11(), matrixF.M11());
			Assert::AreEqual(inverseF.M21(), matrixF.M21());
			Assert::AreEqual(inverseF.M02(), matrixF.M02());
			Assert::AreEqual(inverseF.M12(), matrixF.M12());
			Assert::AreEqual(inverseF.M22(), matrixF.M22());
		}

		TEST_METHOD(IsFiniteTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix3x3<float>::Zero.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Matrix3x3<float>::Identity.IsFinite());
			float nan = std::numeric_limits<float>::quiet_NaN();
			auto matrix = PonyEngine::Math::Matrix3x3<float>(nan, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
			Assert::IsFalse(matrix.IsFinite());
			for (std::size_t i = 1; i < 9; ++i)
			{
				matrix.Data()[i - 1] = 0.f;
				matrix.Data()[i] = nan;
			}

			Assert::IsTrue(PonyEngine::Math::Matrix3x3<short>::Zero.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Matrix3x3<short>::Identity.IsFinite());
		}

		TEST_METHOD(SetTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>();
			matrixF.Set(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			Assert::AreEqual(m00F, matrixF.M00());
			Assert::AreEqual(m10F, matrixF.M10());
			Assert::AreEqual(m20F, matrixF.M20());
			Assert::AreEqual(m01F, matrixF.M01());
			Assert::AreEqual(m11F, matrixF.M11());
			Assert::AreEqual(m21F, matrixF.M21());
			Assert::AreEqual(m02F, matrixF.M02());
			Assert::AreEqual(m12F, matrixF.M12());
			Assert::AreEqual(m22F, matrixF.M22());

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>();
			matrixI.Set(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			Assert::AreEqual(m00I, matrixI.M00());
			Assert::AreEqual(m10I, matrixI.M10());
			Assert::AreEqual(m20I, matrixI.M20());
			Assert::AreEqual(m01I, matrixI.M01());
			Assert::AreEqual(m11I, matrixI.M11());
			Assert::AreEqual(m21I, matrixI.M21());
			Assert::AreEqual(m02I, matrixI.M02());
			Assert::AreEqual(m12I, matrixI.M12());
			Assert::AreEqual(m22I, matrixI.M22());
		}

		TEST_METHOD(ScaleTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			float m00SF = 3.f;
			float m10SF = -2.f;
			float m20SF = 8.f;
			float m01SF = 4.f;
			float m11SF = -1.f;
			float m21SF = -9.f;
			float m02SF = 10.f;
			float m12SF = -11.f;
			float m22SF = 5.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			auto scaleF = PonyEngine::Math::Matrix3x3<float>(m00SF, m10SF, m20SF, m01SF, m11SF, m21SF, m02SF, m12SF, m22SF);
			auto scaledF = PonyEngine::Math::Scale(matrixF, scaleF);
			Assert::AreEqual(m00F * m00SF, scaledF.M00());
			Assert::AreEqual(m10F * m10SF, scaledF.M10());
			Assert::AreEqual(m20F * m20SF, scaledF.M20());
			Assert::AreEqual(m01F * m01SF, scaledF.M01());
			Assert::AreEqual(m11F * m11SF, scaledF.M11());
			Assert::AreEqual(m21F * m21SF, scaledF.M21());
			Assert::AreEqual(m02F * m02SF, scaledF.M02());
			Assert::AreEqual(m12F * m12SF, scaledF.M12());
			Assert::AreEqual(m22F * m22SF, scaledF.M22());
			matrixF.Scale(scaleF);
			Assert::AreEqual(scaledF.M00(), matrixF.M00());
			Assert::AreEqual(scaledF.M10(), matrixF.M10());
			Assert::AreEqual(scaledF.M20(), matrixF.M20());
			Assert::AreEqual(scaledF.M01(), matrixF.M01());
			Assert::AreEqual(scaledF.M11(), matrixF.M11());
			Assert::AreEqual(scaledF.M21(), matrixF.M21());
			Assert::AreEqual(scaledF.M02(), matrixF.M02());
			Assert::AreEqual(scaledF.M12(), matrixF.M12());
			Assert::AreEqual(scaledF.M22(), matrixF.M22());

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			short m00SI = 3;
			short m10SI = -2;
			short m20SI = 8;
			short m01SI = 4;
			short m11SI = -1;
			short m21SI = -9;
			short m02SI = 10;
			short m12SI = -11;
			short m22SI = 5;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			auto scaleI = PonyEngine::Math::Matrix3x3<short>(m00SI, m10SI, m20SI, m01SI, m11SI, m21SI, m02SI, m12SI, m22SI);
			auto scaledI = PonyEngine::Math::Scale(matrixI, scaleI);
			Assert::AreEqual(static_cast<short>(m00I * m00SI), scaledI.M00());
			Assert::AreEqual(static_cast<short>(m10I * m10SI), scaledI.M10());
			Assert::AreEqual(static_cast<short>(m20I * m20SI), scaledI.M20());
			Assert::AreEqual(static_cast<short>(m01I * m01SI), scaledI.M01());
			Assert::AreEqual(static_cast<short>(m11I * m11SI), scaledI.M11());
			Assert::AreEqual(static_cast<short>(m21I * m21SI), scaledI.M21());
			Assert::AreEqual(static_cast<short>(m02I * m02SI), scaledI.M02());
			Assert::AreEqual(static_cast<short>(m12I * m12SI), scaledI.M12());
			Assert::AreEqual(static_cast<short>(m22I * m22SI), scaledI.M22());
			matrixI.Scale(scaleI);
			Assert::AreEqual(scaledI.M00(), matrixI.M00());
			Assert::AreEqual(scaledI.M10(), matrixI.M10());
			Assert::AreEqual(scaledI.M20(), matrixI.M20());
			Assert::AreEqual(scaledI.M01(), matrixI.M01());
			Assert::AreEqual(scaledI.M11(), matrixI.M11());
			Assert::AreEqual(scaledI.M21(), matrixI.M21());
			Assert::AreEqual(scaledI.M02(), matrixI.M02());
			Assert::AreEqual(scaledI.M12(), matrixI.M12());
			Assert::AreEqual(scaledI.M22(), matrixI.M22());
		}

		TEST_METHOD(GetRowTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			auto row0F = matrixF.GetRow(0);
			auto row1F = matrixF.GetRow(1);
			auto row2F = matrixF.GetRow(2);
			Assert::AreEqual(m00F, row0F.X());
			Assert::AreEqual(m01F, row0F.Y());
			Assert::AreEqual(m02F, row0F.Z());
			Assert::AreEqual(m10F, row1F.X());
			Assert::AreEqual(m11F, row1F.Y());
			Assert::AreEqual(m12F, row1F.Z());
			Assert::AreEqual(m20F, row2F.X());
			Assert::AreEqual(m21F, row2F.Y());
			Assert::AreEqual(m22F, row2F.Z());

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			auto row0I = matrixI.GetRow(0);
			auto row1I = matrixI.GetRow(1);
			auto row2I = matrixI.GetRow(2);
			Assert::AreEqual(m00I, row0I.X());
			Assert::AreEqual(m01I, row0I.Y());
			Assert::AreEqual(m02I, row0I.Z());
			Assert::AreEqual(m10I, row1I.X());
			Assert::AreEqual(m11I, row1I.Y());
			Assert::AreEqual(m12I, row1I.Z());
			Assert::AreEqual(m20I, row2I.X());
			Assert::AreEqual(m21I, row2I.Y());
			Assert::AreEqual(m22I, row2I.Z());
		}

		TEST_METHOD(SetRowTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>();
			auto row0F = PonyEngine::Math::Vector3<float>(m00F, m01F, m02F);
			auto row1F = PonyEngine::Math::Vector3<float>(m10F, m11F, m12F);
			auto row2F = PonyEngine::Math::Vector3<float>(m20F, m21F, m22F);
			matrixF.SetRow(0, row0F);
			matrixF.SetRow(1, row1F);
			matrixF.SetRow(2, row2F);
			Assert::AreEqual(m00F, matrixF.M00());
			Assert::AreEqual(m10F, matrixF.M10());
			Assert::AreEqual(m20F, matrixF.M20());
			Assert::AreEqual(m01F, matrixF.M01());
			Assert::AreEqual(m11F, matrixF.M11());
			Assert::AreEqual(m21F, matrixF.M21());
			Assert::AreEqual(m02F, matrixF.M02());
			Assert::AreEqual(m12F, matrixF.M12());
			Assert::AreEqual(m22F, matrixF.M22());

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>();
			auto row0I = PonyEngine::Math::Vector3<short>(m00I, m01I, m02I);
			auto row1I = PonyEngine::Math::Vector3<short>(m10I, m11I, m12I);
			auto row2I = PonyEngine::Math::Vector3<short>(m20I, m21I, m22I);
			matrixI.SetRow(0, row0I);
			matrixI.SetRow(1, row1I);
			matrixI.SetRow(2, row2I);
			Assert::AreEqual(m00I, matrixI.M00());
			Assert::AreEqual(m10I, matrixI.M10());
			Assert::AreEqual(m20I, matrixI.M20());
			Assert::AreEqual(m01I, matrixI.M01());
			Assert::AreEqual(m11I, matrixI.M11());
			Assert::AreEqual(m21I, matrixI.M21());
			Assert::AreEqual(m02I, matrixI.M02());
			Assert::AreEqual(m12I, matrixI.M12());
			Assert::AreEqual(m22I, matrixI.M22());
		}

		TEST_METHOD(GetColumnTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			auto column0F = matrixF.GetColumn(0);
			auto column1F = matrixF.GetColumn(1);
			auto column2F = matrixF.GetColumn(2);
			Assert::AreEqual(m00F, column0F.X());
			Assert::AreEqual(m10F, column0F.Y());
			Assert::AreEqual(m20F, column0F.Z());
			Assert::AreEqual(m01F, column1F.X());
			Assert::AreEqual(m11F, column1F.Y());
			Assert::AreEqual(m21F, column1F.Z());
			Assert::AreEqual(m02F, column2F.X());
			Assert::AreEqual(m12F, column2F.Y());
			Assert::AreEqual(m22F, column2F.Z());

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			auto column0I = matrixI.GetColumn(0);
			auto column1I = matrixI.GetColumn(1);
			auto column2I = matrixI.GetColumn(2);
			Assert::AreEqual(m00I, column0I.X());
			Assert::AreEqual(m10I, column0I.Y());
			Assert::AreEqual(m20I, column0I.Z());
			Assert::AreEqual(m01I, column1I.X());
			Assert::AreEqual(m11I, column1I.Y());
			Assert::AreEqual(m21I, column1I.Z());
			Assert::AreEqual(m02I, column2I.X());
			Assert::AreEqual(m12I, column2I.Y());
			Assert::AreEqual(m22I, column2I.Z());
		}

		TEST_METHOD(SetColumnTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>();
			auto column0F = PonyEngine::Math::Vector3<float>(m00F, m10F, m20F);
			auto column1F = PonyEngine::Math::Vector3<float>(m01F, m11F, m21F);
			auto column2F = PonyEngine::Math::Vector3<float>(m02F, m12F, m22F);
			matrixF.SetColumn(0, column0F);
			matrixF.SetColumn(1, column1F);
			matrixF.SetColumn(2, column2F);
			Assert::AreEqual(m00F, matrixF.M00());
			Assert::AreEqual(m10F, matrixF.M10());
			Assert::AreEqual(m20F, matrixF.M20());
			Assert::AreEqual(m01F, matrixF.M01());
			Assert::AreEqual(m11F, matrixF.M11());
			Assert::AreEqual(m21F, matrixF.M21());
			Assert::AreEqual(m02F, matrixF.M02());
			Assert::AreEqual(m12F, matrixF.M12());
			Assert::AreEqual(m22F, matrixF.M22());

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>();
			auto column0I = PonyEngine::Math::Vector3<short>(m00I, m10I, m20I);
			auto column1I = PonyEngine::Math::Vector3<short>(m01I, m11I, m21I);
			auto column2I = PonyEngine::Math::Vector3<short>(m02I, m12I, m22I);
			matrixI.SetColumn(0, column0I);
			matrixI.SetColumn(1, column1I);
			matrixI.SetColumn(2, column2I);
			Assert::AreEqual(m00I, matrixI.M00());
			Assert::AreEqual(m10I, matrixI.M10());
			Assert::AreEqual(m20I, matrixI.M20());
			Assert::AreEqual(m01I, matrixI.M01());
			Assert::AreEqual(m11I, matrixI.M11());
			Assert::AreEqual(m21I, matrixI.M21());
			Assert::AreEqual(m02I, matrixI.M02());
			Assert::AreEqual(m12I, matrixI.M12());
			Assert::AreEqual(m22I, matrixI.M22());
		}

		TEST_METHOD(GetDiagonalTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			auto diagonalF = matrixF.GetDiagonal();
			Assert::AreEqual(m00F, diagonalF.X());
			Assert::AreEqual(m11F, diagonalF.Y());
			Assert::AreEqual(m22F, diagonalF.Z());

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			auto diagonalI = matrixI.GetDiagonal();
			Assert::AreEqual(m00I, diagonalI.X());
			Assert::AreEqual(m11I, diagonalI.Y());
			Assert::AreEqual(m22I, diagonalI.Z());
		}

		TEST_METHOD(SetDiagonalTest)
		{
			float m00F = 3.f;
			float m11F = -2.f;
			float m22F = -8.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>();
			auto diagonalF = PonyEngine::Math::Vector3<float>(m00F, m11F, m22F);
			matrixF.SetDiagonal(diagonalF);
			Assert::AreEqual(m00F, matrixF.M00());
			Assert::AreEqual(m11F, matrixF.M11());
			Assert::AreEqual(m22F, matrixF.M22());

			short m00I = 3;
			short m11I = -2;
			short m22I = -8;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>();
			auto diagonalI = PonyEngine::Math::Vector3<short>(m00I, m11I, m22I);
			matrixI.SetDiagonal(diagonalI);
			Assert::AreEqual(m00I, matrixI.M00());
			Assert::AreEqual(m11I, matrixI.M11());
			Assert::AreEqual(m22I, matrixI.M22());
		}

		TEST_METHOD(GetCounterDiagonalTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			auto diagonalF = matrixF.GetCounterDiagonal();
			Assert::AreEqual(m02F, diagonalF.X());
			Assert::AreEqual(m11F, diagonalF.Y());
			Assert::AreEqual(m20F, diagonalF.Z());

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			auto diagonalI = matrixI.GetCounterDiagonal();
			Assert::AreEqual(m02I, diagonalI.X());
			Assert::AreEqual(m11I, diagonalI.Y());
			Assert::AreEqual(m20I, diagonalI.Z());
		}

		TEST_METHOD(SetCounterDiagonalTest)
		{
			float m02F = 3.f;
			float m11F = -2.f;
			float m20F = -8.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>();
			auto diagonalF = PonyEngine::Math::Vector3<float>(m02F, m11F, m20F);
			matrixF.SetCounterDiagonal(diagonalF);
			Assert::AreEqual(m02F, matrixF.M02());
			Assert::AreEqual(m11F, matrixF.M11());
			Assert::AreEqual(m20F, matrixF.M20());

			short m02I = 3;
			short m11I = -2;
			short m20I = -8;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>();
			auto diagonalI = PonyEngine::Math::Vector3<short>(m02I, m11I, m20I);
			matrixI.SetCounterDiagonal(diagonalI);
			Assert::AreEqual(m02I, matrixI.M02());
			Assert::AreEqual(m11I, matrixI.M11());
			Assert::AreEqual(m20I, matrixI.M20());
		}

		TEST_METHOD(ToStringTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			auto expectedStringF = std::format("({}, {}, {})({}, {}, {})({}, {}, {})", m00F, m01F, m02F, m10F, m11F, m12F, m20F, m21F, m22F);
			Assert::AreEqual(expectedStringF, matrixF.ToString());
			std::ostringstream ssF;
			ssF << matrixF;
			Assert::AreEqual(expectedStringF, ssF.str());

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			auto expectedStringI = std::format("({}, {}, {})({}, {}, {})({}, {}, {})", m00F, m01F, m02F, m10F, m11F, m12F, m20F, m21F, m22F);
			Assert::AreEqual(expectedStringI, matrixI.ToString());
			std::ostringstream ssI;
			ssI << matrixI;
			Assert::AreEqual(expectedStringI, ssI.str());
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			auto matrix0 = PonyEngine::Math::Matrix3x3<float>(1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f);
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
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			auto matrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			Assert::AreEqual(m00F, matrixF[0][0]);
			Assert::AreEqual(m10F, matrixF[1][0]);
			Assert::AreEqual(m20F, matrixF[2][0]);
			Assert::AreEqual(m01F, matrixF[0][1]);
			Assert::AreEqual(m11F, matrixF[1][1]);
			Assert::AreEqual(m21F, matrixF[2][1]);
			Assert::AreEqual(m02F, matrixF[0][2]);
			Assert::AreEqual(m12F, matrixF[1][2]);
			Assert::AreEqual(m22F, matrixF[2][2]);

			PonyEngine::Math::Vector3<float> rowF = matrixF[1];
			Assert::AreEqual(m10F, rowF.X());
			Assert::AreEqual(m11F, rowF.Y());
			Assert::AreEqual(m12F, rowF.Z());

			matrixF[0][0] = matrixF[1][0] = matrixF[0][1] = matrixF[1][1] = 10.f;
			Assert::AreEqual(10.f, matrixF[0][0]);
			Assert::AreEqual(10.f, matrixF[1][0]);
			Assert::AreEqual(10.f, matrixF[0][1]);
			Assert::AreEqual(10.f, matrixF[1][1]);

			const auto constMatrixF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			Assert::AreEqual(constMatrixF.M00(), constMatrixF[0][0]);
			Assert::AreEqual(constMatrixF.M10(), constMatrixF[1][0]);
			Assert::AreEqual(constMatrixF.M20(), constMatrixF[2][0]);
			Assert::AreEqual(constMatrixF.M01(), constMatrixF[0][1]);
			Assert::AreEqual(constMatrixF.M11(), constMatrixF[1][1]);
			Assert::AreEqual(constMatrixF.M21(), constMatrixF[2][1]);
			Assert::AreEqual(constMatrixF.M02(), constMatrixF[0][2]);
			Assert::AreEqual(constMatrixF.M12(), constMatrixF[1][2]);
			Assert::AreEqual(constMatrixF.M22(), constMatrixF[2][2]);

			PonyEngine::Math::Vector3<float> constRowF = constMatrixF[1];
			Assert::AreEqual(m10F, constRowF.X());
			Assert::AreEqual(m11F, constRowF.Y());
			Assert::AreEqual(m12F, constRowF.Z());

			Assert::AreEqual(std::size_t{3}, PonyEngine::Math::Matrix3x3<float>::RowCount);
			Assert::AreEqual(std::size_t{3}, PonyEngine::Math::Matrix3x3<float>::ColumnCount);
			Assert::AreEqual(std::size_t{9}, PonyEngine::Math::Matrix3x3<float>::ComponentCount);

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			auto matrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			Assert::AreEqual(m00I, matrixI[0][0]);
			Assert::AreEqual(m10I, matrixI[1][0]);
			Assert::AreEqual(m20I, matrixI[2][0]);
			Assert::AreEqual(m01I, matrixI[0][1]);
			Assert::AreEqual(m11I, matrixI[1][1]);
			Assert::AreEqual(m21I, matrixI[2][1]);
			Assert::AreEqual(m02I, matrixI[0][2]);
			Assert::AreEqual(m12I, matrixI[1][2]);
			Assert::AreEqual(m22I, matrixI[2][2]);

			PonyEngine::Math::Vector3<short> rowI = matrixI[1];
			Assert::AreEqual(m10I, rowI.X());
			Assert::AreEqual(m11I, rowI.Y());
			Assert::AreEqual(m12I, rowI.Z());

			matrixI[0][0] = matrixI[1][0] = matrixI[0][1] = matrixI[1][1] = 10;
			Assert::AreEqual(short{10}, matrixI[0][0]);
			Assert::AreEqual(short{10}, matrixI[1][0]);
			Assert::AreEqual(short{10}, matrixI[0][1]);
			Assert::AreEqual(short{10}, matrixI[1][1]);

			const auto constMatrixI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			Assert::AreEqual(constMatrixI.M00(), constMatrixI[0][0]);
			Assert::AreEqual(constMatrixI.M10(), constMatrixI[1][0]);
			Assert::AreEqual(constMatrixI.M20(), constMatrixI[2][0]);
			Assert::AreEqual(constMatrixI.M01(), constMatrixI[0][1]);
			Assert::AreEqual(constMatrixI.M11(), constMatrixI[1][1]);
			Assert::AreEqual(constMatrixI.M21(), constMatrixI[2][1]);
			Assert::AreEqual(constMatrixI.M02(), constMatrixI[0][2]);
			Assert::AreEqual(constMatrixI.M12(), constMatrixI[1][2]);
			Assert::AreEqual(constMatrixI.M22(), constMatrixI[2][2]);

			PonyEngine::Math::Vector3<short> constRowI = constMatrixI[1];
			Assert::AreEqual(m10I, constRowI.X());
			Assert::AreEqual(m11I, constRowI.Y());
			Assert::AreEqual(m12I, constRowI.Z());

			Assert::AreEqual(std::size_t{3}, PonyEngine::Math::Matrix3x3<short>::RowCount);
			Assert::AreEqual(std::size_t{3}, PonyEngine::Math::Matrix3x3<short>::ColumnCount);
			Assert::AreEqual(std::size_t{9}, PonyEngine::Math::Matrix3x3<short>::ComponentCount);
		}

		TEST_METHOD(AssignmentOperatorsTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			auto rightF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			auto centerF = PonyEngine::Math::Matrix3x3<float>();
			auto leftF = centerF = rightF;
			Assert::AreEqual(m00F, centerF.M00());
			Assert::AreEqual(m10F, centerF.M10());
			Assert::AreEqual(m20F, centerF.M20());
			Assert::AreEqual(m01F, centerF.M01());
			Assert::AreEqual(m11F, centerF.M11());
			Assert::AreEqual(m21F, centerF.M21());
			Assert::AreEqual(m02F, centerF.M02());
			Assert::AreEqual(m12F, centerF.M12());
			Assert::AreEqual(m22F, centerF.M22());
			Assert::AreEqual(m00F, leftF.M00());
			Assert::AreEqual(m10F, leftF.M10());
			Assert::AreEqual(m20F, leftF.M20());
			Assert::AreEqual(m01F, leftF.M01());
			Assert::AreEqual(m11F, leftF.M11());
			Assert::AreEqual(m21F, leftF.M21());
			Assert::AreEqual(m02F, leftF.M02());
			Assert::AreEqual(m12F, leftF.M12());
			Assert::AreEqual(m22F, leftF.M22());

			float m00CF = 14.f;
			float m10CF = -13.f;
			float m20CF = 20.f;
			float m01CF = 16.f;
			float m11CF = 15.f;
			float m21CF = -4.f;
			float m02CF = -6.f;
			float m12CF = 7.f;
			float m22CF = 21.f;
			centerF = PonyEngine::Math::Matrix3x3<float>(m00CF, m10CF, m20CF, m01CF, m11CF, m21CF, m02CF, m12CF, m22CF);
			leftF = centerF += rightF;
			Assert::AreEqual(m00F + m00CF, centerF.M00());
			Assert::AreEqual(m10F + m10CF, centerF.M10());
			Assert::AreEqual(m20F + m20CF, centerF.M20());
			Assert::AreEqual(m01F + m01CF, centerF.M01());
			Assert::AreEqual(m11F + m11CF, centerF.M11());
			Assert::AreEqual(m21F + m21CF, centerF.M21());
			Assert::AreEqual(m02F + m02CF, centerF.M02());
			Assert::AreEqual(m12F + m12CF, centerF.M12());
			Assert::AreEqual(m22F + m22CF, centerF.M22());
			Assert::AreEqual(m00F + m00CF, leftF.M00());
			Assert::AreEqual(m10F + m10CF, leftF.M10());
			Assert::AreEqual(m20F + m20CF, leftF.M20());
			Assert::AreEqual(m01F + m01CF, leftF.M01());
			Assert::AreEqual(m11F + m11CF, leftF.M11());
			Assert::AreEqual(m21F + m21CF, leftF.M21());
			Assert::AreEqual(m02F + m02CF, leftF.M02());
			Assert::AreEqual(m12F + m12CF, leftF.M12());
			Assert::AreEqual(m22F + m22CF, leftF.M22());

			centerF = PonyEngine::Math::Matrix3x3<float>(m00CF, m10CF, m20CF, m01CF, m11CF, m21CF, m02CF, m12CF, m22CF);
			leftF = centerF -= rightF;
			Assert::AreEqual(m00CF - m00F, centerF.M00());
			Assert::AreEqual(m10CF - m10F, centerF.M10());
			Assert::AreEqual(m20CF - m20F, centerF.M20());
			Assert::AreEqual(m01CF - m01F, centerF.M01());
			Assert::AreEqual(m11CF - m11F, centerF.M11());
			Assert::AreEqual(m21CF - m21F, centerF.M21());
			Assert::AreEqual(m02CF - m02F, centerF.M02());
			Assert::AreEqual(m12CF - m12F, centerF.M12());
			Assert::AreEqual(m22CF - m22F, centerF.M22());
			Assert::AreEqual(m00CF - m00F, leftF.M00());
			Assert::AreEqual(m10CF - m10F, leftF.M10());
			Assert::AreEqual(m20CF - m20F, leftF.M20());
			Assert::AreEqual(m01CF - m01F, leftF.M01());
			Assert::AreEqual(m11CF - m11F, leftF.M11());
			Assert::AreEqual(m21CF - m21F, leftF.M21());
			Assert::AreEqual(m02CF - m02F, leftF.M02());
			Assert::AreEqual(m12CF - m12F, leftF.M12());
			Assert::AreEqual(m22CF - m22F, leftF.M22());

			float multiplierF = 3.f;
			centerF = PonyEngine::Math::Matrix3x3<float>(m00CF, m10CF, m20CF, m01CF, m11CF, m21CF, m02CF, m12CF, m22CF);
			leftF = centerF *= multiplierF;
			Assert::AreEqual(m00CF * multiplierF, centerF.M00());
			Assert::AreEqual(m10CF * multiplierF, centerF.M10());
			Assert::AreEqual(m20CF * multiplierF, centerF.M20());
			Assert::AreEqual(m01CF * multiplierF, centerF.M01());
			Assert::AreEqual(m11CF * multiplierF, centerF.M11());
			Assert::AreEqual(m21CF * multiplierF, centerF.M21());
			Assert::AreEqual(m02CF * multiplierF, centerF.M02());
			Assert::AreEqual(m12CF * multiplierF, centerF.M12());
			Assert::AreEqual(m22CF * multiplierF, centerF.M22());
			Assert::AreEqual(m00CF * multiplierF, leftF.M00());
			Assert::AreEqual(m10CF * multiplierF, leftF.M10());
			Assert::AreEqual(m20CF * multiplierF, leftF.M20());
			Assert::AreEqual(m01CF * multiplierF, leftF.M01());
			Assert::AreEqual(m11CF * multiplierF, leftF.M11());
			Assert::AreEqual(m21CF * multiplierF, leftF.M21());
			Assert::AreEqual(m02CF * multiplierF, leftF.M02());
			Assert::AreEqual(m12CF * multiplierF, leftF.M12());
			Assert::AreEqual(m22CF * multiplierF, leftF.M22());

			centerF = PonyEngine::Math::Matrix3x3<float>(m00CF, m10CF, m20CF, m01CF, m11CF, m21CF, m02CF, m12CF, m22CF);
			leftF = centerF *= rightF;
			Assert::AreEqual(m00CF * m00F + m01CF * m10F + m02CF * m20F, centerF.M00());
			Assert::AreEqual(m10CF * m00F + m11CF * m10F + m12CF * m20F, centerF.M10());
			Assert::AreEqual(m20CF * m00F + m21CF * m10F + m22CF * m20F, centerF.M20());
			Assert::AreEqual(m00CF * m01F + m01CF * m11F + m02CF * m21F, centerF.M01());
			Assert::AreEqual(m10CF * m01F + m11CF * m11F + m12CF * m21F, centerF.M11());
			Assert::AreEqual(m20CF * m01F + m21CF * m11F + m22CF * m21F, centerF.M21());
			Assert::AreEqual(m00CF * m02F + m01CF * m12F + m02CF * m22F, centerF.M02());
			Assert::AreEqual(m10CF * m02F + m11CF * m12F + m12CF * m22F, centerF.M12());
			Assert::AreEqual(m20CF * m02F + m21CF * m12F + m22CF * m22F, centerF.M22());
			Assert::AreEqual(m00CF * m00F + m01CF * m10F + m02CF * m20F, leftF.M00());
			Assert::AreEqual(m10CF * m00F + m11CF * m10F + m12CF * m20F, leftF.M10());
			Assert::AreEqual(m20CF * m00F + m21CF * m10F + m22CF * m20F, leftF.M20());
			Assert::AreEqual(m00CF * m01F + m01CF * m11F + m02CF * m21F, leftF.M01());
			Assert::AreEqual(m10CF * m01F + m11CF * m11F + m12CF * m21F, leftF.M11());
			Assert::AreEqual(m20CF * m01F + m21CF * m11F + m22CF * m21F, leftF.M21());
			Assert::AreEqual(m00CF * m02F + m01CF * m12F + m02CF * m22F, leftF.M02());
			Assert::AreEqual(m10CF * m02F + m11CF * m12F + m12CF * m22F, leftF.M12());
			Assert::AreEqual(m20CF * m02F + m21CF * m12F + m22CF * m22F, leftF.M22());

			centerF = PonyEngine::Math::Matrix3x3<float>(m00CF, m10CF, m20CF, m01CF, m11CF, m21CF, m02CF, m12CF, m22CF);
			leftF = centerF /= multiplierF;
			Assert::AreEqual(m00CF / multiplierF, centerF.M00());
			Assert::AreEqual(m10CF / multiplierF, centerF.M10());
			Assert::AreEqual(m20CF / multiplierF, centerF.M20());
			Assert::AreEqual(m01CF / multiplierF, centerF.M01());
			Assert::AreEqual(m11CF / multiplierF, centerF.M11());
			Assert::AreEqual(m21CF / multiplierF, centerF.M21());
			Assert::AreEqual(m02CF / multiplierF, centerF.M02());
			Assert::AreEqual(m12CF / multiplierF, centerF.M12());
			Assert::AreEqual(m22CF / multiplierF, centerF.M22());
			Assert::AreEqual(m00CF / multiplierF, leftF.M00());
			Assert::AreEqual(m10CF / multiplierF, leftF.M10());
			Assert::AreEqual(m20CF / multiplierF, leftF.M20());
			Assert::AreEqual(m01CF / multiplierF, leftF.M01());
			Assert::AreEqual(m11CF / multiplierF, leftF.M11());
			Assert::AreEqual(m21CF / multiplierF, leftF.M21());
			Assert::AreEqual(m02CF / multiplierF, leftF.M02());
			Assert::AreEqual(m12CF / multiplierF, leftF.M12());
			Assert::AreEqual(m22CF / multiplierF, leftF.M22());

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			auto rightI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			auto centerI = PonyEngine::Math::Matrix3x3<short>();
			auto leftI = centerI = rightI;
			Assert::AreEqual(m00I, centerI.M00());
			Assert::AreEqual(m10I, centerI.M10());
			Assert::AreEqual(m20I, centerI.M20());
			Assert::AreEqual(m01I, centerI.M01());
			Assert::AreEqual(m11I, centerI.M11());
			Assert::AreEqual(m21I, centerI.M21());
			Assert::AreEqual(m02I, centerI.M02());
			Assert::AreEqual(m12I, centerI.M12());
			Assert::AreEqual(m22I, centerI.M22());
			Assert::AreEqual(m00I, leftI.M00());
			Assert::AreEqual(m10I, leftI.M10());
			Assert::AreEqual(m20I, leftI.M20());
			Assert::AreEqual(m01I, leftI.M01());
			Assert::AreEqual(m11I, leftI.M11());
			Assert::AreEqual(m21I, leftI.M21());
			Assert::AreEqual(m02I, leftI.M02());
			Assert::AreEqual(m12I, leftI.M12());
			Assert::AreEqual(m22I, leftI.M22());

			short m00CI = 14;
			short m10CI = -13;
			short m20CI = 20;
			short m01CI = 16;
			short m11CI = 15;
			short m21CI = -4;
			short m02CI = -6;
			short m12CI = 7;
			short m22CI = 21;
			centerI = PonyEngine::Math::Matrix3x3<short>(m00CI, m10CI, m20CI, m01CI, m11CI, m21CI, m02CI, m12CI, m22CI);
			leftI = centerI += rightI;
			Assert::AreEqual(static_cast<short>(m00I + m00CI), centerI.M00());
			Assert::AreEqual(static_cast<short>(m10I + m10CI), centerI.M10());
			Assert::AreEqual(static_cast<short>(m20I + m20CI), centerI.M20());
			Assert::AreEqual(static_cast<short>(m01I + m01CI), centerI.M01());
			Assert::AreEqual(static_cast<short>(m11I + m11CI), centerI.M11());
			Assert::AreEqual(static_cast<short>(m21I + m21CI), centerI.M21());
			Assert::AreEqual(static_cast<short>(m02I + m02CI), centerI.M02());
			Assert::AreEqual(static_cast<short>(m12I + m12CI), centerI.M12());
			Assert::AreEqual(static_cast<short>(m22I + m22CI), centerI.M22());
			Assert::AreEqual(static_cast<short>(m00I + m00CI), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10I + m10CI), leftI.M10());
			Assert::AreEqual(static_cast<short>(m20I + m20CI), leftI.M20());
			Assert::AreEqual(static_cast<short>(m01I + m01CI), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11I + m11CI), leftI.M11());
			Assert::AreEqual(static_cast<short>(m21I + m21CI), leftI.M21());
			Assert::AreEqual(static_cast<short>(m02I + m02CI), leftI.M02());
			Assert::AreEqual(static_cast<short>(m12I + m12CI), leftI.M12());
			Assert::AreEqual(static_cast<short>(m22I + m22CI), leftI.M22());

			centerI = PonyEngine::Math::Matrix3x3<short>(m00CI, m10CI, m20CI, m01CI, m11CI, m21CI, m02CI, m12CI, m22CI);
			leftI = centerI -= rightI;
			Assert::AreEqual(static_cast<short>(m00CI - m00I), centerI.M00());
			Assert::AreEqual(static_cast<short>(m10CI - m10I), centerI.M10());
			Assert::AreEqual(static_cast<short>(m20CI - m20I), centerI.M20());
			Assert::AreEqual(static_cast<short>(m01CI - m01I), centerI.M01());
			Assert::AreEqual(static_cast<short>(m11CI - m11I), centerI.M11());
			Assert::AreEqual(static_cast<short>(m21CI - m21I), centerI.M21());
			Assert::AreEqual(static_cast<short>(m02CI - m02I), centerI.M02());
			Assert::AreEqual(static_cast<short>(m12CI - m12I), centerI.M12());
			Assert::AreEqual(static_cast<short>(m22CI - m22I), centerI.M22());
			Assert::AreEqual(static_cast<short>(m00CI - m00I), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI - m10I), leftI.M10());
			Assert::AreEqual(static_cast<short>(m20CI - m20I), leftI.M20());
			Assert::AreEqual(static_cast<short>(m01CI - m01I), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI - m11I), leftI.M11());
			Assert::AreEqual(static_cast<short>(m21CI - m21I), leftI.M21());
			Assert::AreEqual(static_cast<short>(m02CI - m02I), leftI.M02());
			Assert::AreEqual(static_cast<short>(m12CI - m12I), leftI.M12());
			Assert::AreEqual(static_cast<short>(m22CI - m22I), leftI.M22());

			short multiplierI = 3;
			centerI = PonyEngine::Math::Matrix3x3<short>(m00CI, m10CI, m20CI, m01CI, m11CI, m21CI, m02CI, m12CI, m22CI);
			leftI = centerI *= multiplierI;
			Assert::AreEqual(static_cast<short>(m00CI * multiplierI), centerI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierI), centerI.M10());
			Assert::AreEqual(static_cast<short>(m20CI * multiplierI), centerI.M20());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierI), centerI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierI), centerI.M11());
			Assert::AreEqual(static_cast<short>(m21CI * multiplierI), centerI.M21());
			Assert::AreEqual(static_cast<short>(m02CI * multiplierI), centerI.M02());
			Assert::AreEqual(static_cast<short>(m12CI * multiplierI), centerI.M12());
			Assert::AreEqual(static_cast<short>(m22CI * multiplierI), centerI.M22());
			Assert::AreEqual(static_cast<short>(m00CI * multiplierI), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierI), leftI.M10());
			Assert::AreEqual(static_cast<short>(m20CI * multiplierI), leftI.M20());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierI), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierI), leftI.M11());
			Assert::AreEqual(static_cast<short>(m21CI * multiplierI), leftI.M21());
			Assert::AreEqual(static_cast<short>(m02CI * multiplierI), leftI.M02());
			Assert::AreEqual(static_cast<short>(m12CI * multiplierI), leftI.M12());
			Assert::AreEqual(static_cast<short>(m22CI * multiplierI), leftI.M22());

			centerI = PonyEngine::Math::Matrix3x3<short>(m00CI, m10CI, m20CI, m01CI, m11CI, m21CI, m02CI, m12CI, m22CI);
			leftI = centerI *= multiplierF;
			Assert::AreEqual(static_cast<short>(m00CI * multiplierF), centerI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierF), centerI.M10());
			Assert::AreEqual(static_cast<short>(m20CI * multiplierF), centerI.M20());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierF), centerI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierF), centerI.M11());
			Assert::AreEqual(static_cast<short>(m21CI * multiplierF), centerI.M21());
			Assert::AreEqual(static_cast<short>(m02CI * multiplierF), centerI.M02());
			Assert::AreEqual(static_cast<short>(m12CI * multiplierF), centerI.M12());
			Assert::AreEqual(static_cast<short>(m22CI * multiplierF), centerI.M22());
			Assert::AreEqual(static_cast<short>(m00CI * multiplierF), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierF), leftI.M10());
			Assert::AreEqual(static_cast<short>(m20CI * multiplierF), leftI.M20());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierF), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierF), leftI.M11());
			Assert::AreEqual(static_cast<short>(m21CI * multiplierF), leftI.M21());
			Assert::AreEqual(static_cast<short>(m02CI * multiplierF), leftI.M02());
			Assert::AreEqual(static_cast<short>(m12CI * multiplierF), leftI.M12());
			Assert::AreEqual(static_cast<short>(m22CI * multiplierF), leftI.M22());

			centerI = PonyEngine::Math::Matrix3x3<short>(m00CI, m10CI, m20CI, m01CI, m11CI, m21CI, m02CI, m12CI, m22CI);
			leftI = centerI *= rightI;
			Assert::AreEqual(static_cast<short>(m00CI * m00I + m01CI * m10I + m02CI * m20I), centerI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * m00I + m11CI * m10I + m12CI * m20I), centerI.M10());
			Assert::AreEqual(static_cast<short>(m20CI * m00I + m21CI * m10I + m22CI * m20I), centerI.M20());
			Assert::AreEqual(static_cast<short>(m00CI * m01I + m01CI * m11I + m02CI * m21I), centerI.M01());
			Assert::AreEqual(static_cast<short>(m10CI * m01I + m11CI * m11I + m12CI * m21I), centerI.M11());
			Assert::AreEqual(static_cast<short>(m20CI * m01I + m21CI * m11I + m22CI * m21I), centerI.M21());
			Assert::AreEqual(static_cast<short>(m00CI * m02I + m01CI * m12I + m02CI * m22I), centerI.M02());
			Assert::AreEqual(static_cast<short>(m10CI * m02I + m11CI * m12I + m12CI * m22I), centerI.M12());
			Assert::AreEqual(static_cast<short>(m20CI * m02I + m21CI * m12I + m22CI * m22I), centerI.M22());
			Assert::AreEqual(static_cast<short>(m00CI * m00I + m01CI * m10I + m02CI * m20I), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * m00I + m11CI * m10I + m12CI * m20I), leftI.M10());
			Assert::AreEqual(static_cast<short>(m20CI * m00I + m21CI * m10I + m22CI * m20I), leftI.M20());
			Assert::AreEqual(static_cast<short>(m00CI * m01I + m01CI * m11I + m02CI * m21I), leftI.M01());
			Assert::AreEqual(static_cast<short>(m10CI * m01I + m11CI * m11I + m12CI * m21I), leftI.M11());
			Assert::AreEqual(static_cast<short>(m20CI * m01I + m21CI * m11I + m22CI * m21I), leftI.M21());
			Assert::AreEqual(static_cast<short>(m00CI * m02I + m01CI * m12I + m02CI * m22I), leftI.M02());
			Assert::AreEqual(static_cast<short>(m10CI * m02I + m11CI * m12I + m12CI * m22I), leftI.M12());
			Assert::AreEqual(static_cast<short>(m20CI * m02I + m21CI * m12I + m22CI * m22I), leftI.M22());

			centerI = PonyEngine::Math::Matrix3x3<short>(m00CI, m10CI, m20CI, m01CI, m11CI, m21CI, m02CI, m12CI, m22CI);
			leftI = centerI /= multiplierF;
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m00CI / multiplierF), centerI.M00());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m10CI / multiplierF), centerI.M10());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m20CI / multiplierF), centerI.M20());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m01CI / multiplierF), centerI.M01());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m11CI / multiplierF), centerI.M11());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m21CI / multiplierF), centerI.M21());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m02CI / multiplierF), centerI.M02());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m12CI / multiplierF), centerI.M12());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m22CI / multiplierF), centerI.M22());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m00CI / multiplierF), leftI.M00());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m10CI / multiplierF), leftI.M10());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m20CI / multiplierF), leftI.M20());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m01CI / multiplierF), leftI.M01());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m11CI / multiplierF), leftI.M11());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m21CI / multiplierF), leftI.M21());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m02CI / multiplierF), leftI.M02());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m12CI / multiplierF), leftI.M12());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m22CI / multiplierF), leftI.M22());
		}

		TEST_METHOD(EqualityOperatorsTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			auto rightF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
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

			leftF.M01() = m01F;
			leftF.M02() += 1.f;
			Assert::IsFalse(leftF == rightF);
			Assert::IsTrue(leftF != rightF);

			leftF.M02() = m02F;
			leftF.M10() += 1.f;
			Assert::IsFalse(leftF == rightF);
			Assert::IsTrue(leftF != rightF);

			leftF.M10() = m10F;
			leftF.M11() += 1.f;
			Assert::IsFalse(leftF == rightF);
			Assert::IsTrue(leftF != rightF);

			leftF.M11() = m11F;
			leftF.M12() += 1.f;
			Assert::IsFalse(leftF == rightF);
			Assert::IsTrue(leftF != rightF);

			leftF.M12() = m12F;
			leftF.M20() += 1.f;
			Assert::IsFalse(leftF == rightF);
			Assert::IsTrue(leftF != rightF);

			leftF.M20() = m20F;
			leftF.M21() += 1.f;
			Assert::IsFalse(leftF == rightF);
			Assert::IsTrue(leftF != rightF);

			leftF.M21() = m21F;
			leftF.M22() += 1.f;
			Assert::IsFalse(leftF == rightF);
			Assert::IsTrue(leftF != rightF);

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			auto rightI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
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

			leftI.M01() = m01I;
			leftI.M02() += 1;
			Assert::IsFalse(leftI == rightI);
			Assert::IsTrue(leftI != rightI);

			leftI.M02() = m02I;
			leftI.M10() += 1;
			Assert::IsFalse(leftI == rightI);
			Assert::IsTrue(leftI != rightI);

			leftI.M10() = m10I;
			leftI.M11() += 1;
			Assert::IsFalse(leftI == rightI);
			Assert::IsTrue(leftI != rightI);

			leftI.M11() = m11I;
			leftI.M12() += 1;
			Assert::IsFalse(leftI == rightI);
			Assert::IsTrue(leftI != rightI);

			leftI.M12() = m12I;
			leftI.M20() += 1;
			Assert::IsFalse(leftI == rightI);
			Assert::IsTrue(leftI != rightI);

			leftI.M20() = m20I;
			leftI.M21() += 1;
			Assert::IsFalse(leftI == rightI);
			Assert::IsTrue(leftI != rightI);

			leftI.M21() = m21I;
			leftI.M22() += 1;
			Assert::IsFalse(leftI == rightI);
			Assert::IsTrue(leftI != rightI);
		}

		TEST_METHOD(ComputationalOperatorsTest)
		{
			float m00F = -10.f;
			float m10F = -15.f;
			float m20F = 7.f;
			float m01F = 5.f;
			float m11F = 20.f;
			float m21F = -2.f;
			float m02F = 10.f;
			float m12F = 22.f;
			float m22F = -8.f;
			float m00CF = 14.f;
			float m10CF = -13.f;
			float m20CF = 20.f;
			float m01CF = 16.f;
			float m11CF = 15.f;
			float m21CF = -4.f;
			float m02CF = -6.f;
			float m12CF = 7.f;
			float m22CF = 21.f;
			auto rightF = PonyEngine::Math::Matrix3x3<float>(m00F, m10F, m20F, m01F, m11F, m21F, m02F, m12F, m22F);
			auto centerF = PonyEngine::Math::Matrix3x3<float>(m00CF, m10CF, m20CF, m01CF, m11CF, m21CF, m02CF, m12CF, m22CF);
			auto leftF = centerF + rightF;
			Assert::AreEqual(m00F + m00CF, leftF.M00());
			Assert::AreEqual(m10F + m10CF, leftF.M10());
			Assert::AreEqual(m20F + m20CF, leftF.M20());
			Assert::AreEqual(m01F + m01CF, leftF.M01());
			Assert::AreEqual(m11F + m11CF, leftF.M11());
			Assert::AreEqual(m21F + m21CF, leftF.M21());
			Assert::AreEqual(m02F + m02CF, leftF.M02());
			Assert::AreEqual(m12F + m12CF, leftF.M12());
			Assert::AreEqual(m22F + m22CF, leftF.M22());

			leftF = centerF - rightF;
			Assert::AreEqual(m00CF - m00F, leftF.M00());
			Assert::AreEqual(m10CF - m10F, leftF.M10());
			Assert::AreEqual(m20CF - m20F, leftF.M20());
			Assert::AreEqual(m01CF - m01F, leftF.M01());
			Assert::AreEqual(m11CF - m11F, leftF.M11());
			Assert::AreEqual(m21CF - m21F, leftF.M21());
			Assert::AreEqual(m02CF - m02F, leftF.M02());
			Assert::AreEqual(m12CF - m12F, leftF.M12());
			Assert::AreEqual(m22CF - m22F, leftF.M22());

			float multiplierF = 3.f;
			centerF = PonyEngine::Math::Matrix3x3<float>(m00CF, m10CF, m20CF, m01CF, m11CF, m21CF, m02CF, m12CF, m22CF);
			leftF = centerF * multiplierF;
			Assert::AreEqual(m00CF * multiplierF, leftF.M00());
			Assert::AreEqual(m10CF * multiplierF, leftF.M10());
			Assert::AreEqual(m20CF * multiplierF, leftF.M20());
			Assert::AreEqual(m01CF * multiplierF, leftF.M01());
			Assert::AreEqual(m11CF * multiplierF, leftF.M11());
			Assert::AreEqual(m21CF * multiplierF, leftF.M21());
			Assert::AreEqual(m02CF * multiplierF, leftF.M02());
			Assert::AreEqual(m12CF * multiplierF, leftF.M12());
			Assert::AreEqual(m22CF * multiplierF, leftF.M22());
			leftF = multiplierF * centerF;
			Assert::AreEqual(m00CF * multiplierF, leftF.M00());
			Assert::AreEqual(m10CF * multiplierF, leftF.M10());
			Assert::AreEqual(m20CF * multiplierF, leftF.M20());
			Assert::AreEqual(m01CF * multiplierF, leftF.M01());
			Assert::AreEqual(m11CF * multiplierF, leftF.M11());
			Assert::AreEqual(m21CF * multiplierF, leftF.M21());
			Assert::AreEqual(m02CF * multiplierF, leftF.M02());
			Assert::AreEqual(m12CF * multiplierF, leftF.M12());
			Assert::AreEqual(m22CF * multiplierF, leftF.M22());

			centerF = PonyEngine::Math::Matrix3x3<float>(m00CF, m10CF, m20CF, m01CF, m11CF, m21CF, m02CF, m12CF, m22CF);
			leftF = centerF * rightF;
			Assert::AreEqual(m00CF * m00F + m01CF * m10F + m02CF * m20F, leftF.M00());
			Assert::AreEqual(m10CF * m00F + m11CF * m10F + m12CF * m20F, leftF.M10());
			Assert::AreEqual(m20CF * m00F + m21CF * m10F + m22CF * m20F, leftF.M20());
			Assert::AreEqual(m00CF * m01F + m01CF * m11F + m02CF * m21F, leftF.M01());
			Assert::AreEqual(m10CF * m01F + m11CF * m11F + m12CF * m21F, leftF.M11());
			Assert::AreEqual(m20CF * m01F + m21CF * m11F + m22CF * m21F, leftF.M21());
			Assert::AreEqual(m00CF * m02F + m01CF * m12F + m02CF * m22F, leftF.M02());
			Assert::AreEqual(m10CF * m02F + m11CF * m12F + m12CF * m22F, leftF.M12());
			Assert::AreEqual(m20CF * m02F + m21CF * m12F + m22CF * m22F, leftF.M22());

			float xF = 7.f;
			float yF = 3.f;
			float zF = -4.f;
			auto vectorF = PonyEngine::Math::Vector3<float>(xF, yF, zF);
			auto mulVectorF = rightF * vectorF;
			Assert::AreEqual(m00F * xF + m01F * yF + m02F * zF, mulVectorF.X());
			Assert::AreEqual(m10F * xF + m11F * yF + m12F * zF, mulVectorF.Y());
			Assert::AreEqual(m20F * xF + m21F * yF + m22F * zF, mulVectorF.Z());

			centerF = PonyEngine::Math::Matrix3x3<float>(m00CF, m10CF, m20CF, m01CF, m11CF, m21CF, m02CF, m12CF, m22CF);
			leftF = centerF / multiplierF;
			Assert::AreEqual(m00CF / multiplierF, leftF.M00());
			Assert::AreEqual(m10CF / multiplierF, leftF.M10());
			Assert::AreEqual(m20CF / multiplierF, leftF.M20());
			Assert::AreEqual(m01CF / multiplierF, leftF.M01());
			Assert::AreEqual(m11CF / multiplierF, leftF.M11());
			Assert::AreEqual(m21CF / multiplierF, leftF.M21());
			Assert::AreEqual(m02CF / multiplierF, leftF.M02());
			Assert::AreEqual(m12CF / multiplierF, leftF.M12());
			Assert::AreEqual(m22CF / multiplierF, leftF.M22());

			short m00I = -10;
			short m10I = -15;
			short m20I = 7;
			short m01I = 5;
			short m11I = 20;
			short m21I = -2;
			short m02I = 10;
			short m12I = 22;
			short m22I = -8;
			auto rightI = PonyEngine::Math::Matrix3x3<short>(m00I, m10I, m20I, m01I, m11I, m21I, m02I, m12I, m22I);
			short m00CI = 14;
			short m10CI = -13;
			short m20CI = 20;
			short m01CI = 16;
			short m11CI = 15;
			short m21CI = -4;
			short m02CI = -6;
			short m12CI = 7;
			short m22CI = 21;
			auto centerI = PonyEngine::Math::Matrix3x3<short>(m00CI, m10CI, m20CI, m01CI, m11CI, m21CI, m02CI, m12CI, m22CI);
			auto leftI = centerI + rightI;
			Assert::AreEqual(static_cast<short>(m00I + m00CI), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10I + m10CI), leftI.M10());
			Assert::AreEqual(static_cast<short>(m20I + m20CI), leftI.M20());
			Assert::AreEqual(static_cast<short>(m01I + m01CI), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11I + m11CI), leftI.M11());
			Assert::AreEqual(static_cast<short>(m21I + m21CI), leftI.M21());
			Assert::AreEqual(static_cast<short>(m02I + m02CI), leftI.M02());
			Assert::AreEqual(static_cast<short>(m12I + m12CI), leftI.M12());
			Assert::AreEqual(static_cast<short>(m22I + m22CI), leftI.M22());

			centerI = PonyEngine::Math::Matrix3x3<short>(m00CI, m10CI, m20CI, m01CI, m11CI, m21CI, m02CI, m12CI, m22CI);
			leftI = centerI - rightI;
			Assert::AreEqual(static_cast<short>(m00CI - m00I), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI - m10I), leftI.M10());
			Assert::AreEqual(static_cast<short>(m20CI - m20I), leftI.M20());
			Assert::AreEqual(static_cast<short>(m01CI - m01I), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI - m11I), leftI.M11());
			Assert::AreEqual(static_cast<short>(m21CI - m21I), leftI.M21());
			Assert::AreEqual(static_cast<short>(m02CI - m02I), leftI.M02());
			Assert::AreEqual(static_cast<short>(m12CI - m12I), leftI.M12());
			Assert::AreEqual(static_cast<short>(m22CI - m22I), leftI.M22());

			short multiplierI = 3;
			centerI = PonyEngine::Math::Matrix3x3<short>(m00CI, m10CI, m20CI, m01CI, m11CI, m21CI, m02CI, m12CI, m22CI);
			leftI = centerI * multiplierI;
			Assert::AreEqual(static_cast<short>(m00CI * multiplierI), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierI), leftI.M10());
			Assert::AreEqual(static_cast<short>(m20CI * multiplierI), leftI.M20());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierI), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierI), leftI.M11());
			Assert::AreEqual(static_cast<short>(m21CI * multiplierI), leftI.M21());
			Assert::AreEqual(static_cast<short>(m02CI * multiplierI), leftI.M02());
			Assert::AreEqual(static_cast<short>(m12CI * multiplierI), leftI.M12());
			Assert::AreEqual(static_cast<short>(m22CI * multiplierI), leftI.M22());
			leftI = multiplierI * centerI;
			Assert::AreEqual(static_cast<short>(m00CI * multiplierI), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierI), leftI.M10());
			Assert::AreEqual(static_cast<short>(m20CI * multiplierI), leftI.M20());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierI), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierI), leftI.M11());
			Assert::AreEqual(static_cast<short>(m21CI * multiplierI), leftI.M21());
			Assert::AreEqual(static_cast<short>(m02CI * multiplierI), leftI.M02());
			Assert::AreEqual(static_cast<short>(m12CI * multiplierI), leftI.M12());
			Assert::AreEqual(static_cast<short>(m22CI * multiplierI), leftI.M22());

			centerI = PonyEngine::Math::Matrix3x3<short>(m00CI, m10CI, m20CI, m01CI, m11CI, m21CI, m02CI, m12CI, m22CI);
			leftI = centerI * multiplierF;
			Assert::AreEqual(static_cast<short>(m00CI * multiplierF), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierF), leftI.M10());
			Assert::AreEqual(static_cast<short>(m20CI * multiplierF), leftI.M20());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierF), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierF), leftI.M11());
			Assert::AreEqual(static_cast<short>(m21CI * multiplierF), leftI.M21());
			Assert::AreEqual(static_cast<short>(m02CI * multiplierF), leftI.M02());
			Assert::AreEqual(static_cast<short>(m12CI * multiplierF), leftI.M12());
			Assert::AreEqual(static_cast<short>(m22CI * multiplierF), leftI.M22());
			leftI = multiplierF * centerI;
			Assert::AreEqual(static_cast<short>(m00CI * multiplierF), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * multiplierF), leftI.M10());
			Assert::AreEqual(static_cast<short>(m20CI * multiplierF), leftI.M20());
			Assert::AreEqual(static_cast<short>(m01CI * multiplierF), leftI.M01());
			Assert::AreEqual(static_cast<short>(m11CI * multiplierF), leftI.M11());
			Assert::AreEqual(static_cast<short>(m21CI * multiplierF), leftI.M21());
			Assert::AreEqual(static_cast<short>(m02CI * multiplierF), leftI.M02());
			Assert::AreEqual(static_cast<short>(m12CI * multiplierF), leftI.M12());
			Assert::AreEqual(static_cast<short>(m22CI * multiplierF), leftI.M22());

			centerI = PonyEngine::Math::Matrix3x3<short>(m00CI, m10CI, m20CI, m01CI, m11CI, m21CI, m02CI, m12CI, m22CI);
			leftI = centerI * rightI;
			Assert::AreEqual(static_cast<short>(m00CI * m00I + m01CI * m10I + m02CI * m20I), leftI.M00());
			Assert::AreEqual(static_cast<short>(m10CI * m00I + m11CI * m10I + m12CI * m20I), leftI.M10());
			Assert::AreEqual(static_cast<short>(m20CI * m00I + m21CI * m10I + m22CI * m20I), leftI.M20());
			Assert::AreEqual(static_cast<short>(m00CI * m01I + m01CI * m11I + m02CI * m21I), leftI.M01());
			Assert::AreEqual(static_cast<short>(m10CI * m01I + m11CI * m11I + m12CI * m21I), leftI.M11());
			Assert::AreEqual(static_cast<short>(m20CI * m01I + m21CI * m11I + m22CI * m21I), leftI.M21());
			Assert::AreEqual(static_cast<short>(m00CI * m02I + m01CI * m12I + m02CI * m22I), leftI.M02());
			Assert::AreEqual(static_cast<short>(m10CI * m02I + m11CI * m12I + m12CI * m22I), leftI.M12());
			Assert::AreEqual(static_cast<short>(m20CI * m02I + m21CI * m12I + m22CI * m22I), leftI.M22());

			short xI = 7;
			short yI = 3;
			short zI = -4;
			auto vectorI = PonyEngine::Math::Vector3<short>(xI, yI, zI);
			auto mulVectorI = rightI * vectorI;
			Assert::AreEqual(static_cast<short>(m00I * xI + m01I * yI + m02I * zI), mulVectorI.X());
			Assert::AreEqual(static_cast<short>(m10I * xI + m11I * yI + m12I * zI), mulVectorI.Y());
			Assert::AreEqual(static_cast<short>(m20I * xI + m21I * yI + m22I * zI), mulVectorI.Z());

			centerI = PonyEngine::Math::Matrix3x3<short>(m00CI, m10CI, m20CI, m01CI, m11CI, m21CI, m02CI, m12CI, m22CI);
			leftI = centerI / multiplierF;
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m00CI / multiplierF), leftI.M00());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m10CI / multiplierF), leftI.M10());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m20CI / multiplierF), leftI.M20());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m01CI / multiplierF), leftI.M01());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m11CI / multiplierF), leftI.M11());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m21CI / multiplierF), leftI.M21());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m02CI / multiplierF), leftI.M02());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m12CI / multiplierF), leftI.M12());
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(m22CI / multiplierF), leftI.M22());
		}

		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyEngine::Math::Matrix3x3<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix3x3<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyEngine::Math::Matrix3x3<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix3x3<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyEngine::Math::Matrix3x3<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix3x3<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix3x3<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Matrix3x3<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyEngine::Math::Matrix3x3<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Matrix3x3<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Matrix3x3<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Matrix3x3<double>::ComputationalType>);
		}

		TEST_METHOD(DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::Matrix3x3<float>::Identity == PonyEngine::Math::Matrix3x3<float>(1, 0, 0, 0, 1, 0, 0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Matrix3x3<float>::Zero == PonyEngine::Math::Matrix3x3<float>(0, 0, 0, 0, 0, 0, 0, 0, 0));

			Assert::IsTrue(PonyEngine::Math::Matrix3x3<short>::Identity == PonyEngine::Math::Matrix3x3<short>(1, 0, 0, 0, 1, 0, 0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Matrix3x3<short>::Zero == PonyEngine::Math::Matrix3x3<short>(0, 0, 0, 0, 0, 0, 0, 0, 0));
		}

		TEST_METHOD(ConstexprTest)
		{
#pragma warning(disable:4189)
			constexpr auto defaultMatrix = PonyEngine::Math::Matrix3x3<float>();
			constexpr auto matrix = PonyEngine::Math::Matrix3x3<float>(2, 3, -1, 5, 5, 1, 4, 9, -7);
			constexpr auto columnMatrix = PonyEngine::Math::Matrix3x3<float>(PonyEngine::Math::Vector3<float>(2, 3, 9), PonyEngine::Math::Vector3<float>(-1, 5, -2), PonyEngine::Math::Vector3<float>(10, 5, -20));
			constexpr auto copiedMatrix = matrix;

			constexpr auto m00 = matrix.M00();
			constexpr auto m10 = matrix.M10();
			constexpr auto m20 = matrix.M20();
			constexpr auto m01 = matrix.M01();
			constexpr auto m11 = matrix.M11();
			constexpr auto m21 = matrix.M21();
			constexpr auto m02 = matrix.M02();
			constexpr auto m12 = matrix.M12();
			constexpr auto m22 = matrix.M22();

			static constexpr PonyEngine::Math::Matrix3x3<float> StaticMatrix(0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
			constexpr auto pointer = StaticMatrix.Data();

			constexpr auto identity = PonyEngine::Math::Matrix3x3<float>::CreateIdentity();
			Assert::AreEqual(1.f, identity.M00());
			Assert::AreEqual(0.f, identity.M10());
			Assert::AreEqual(0.f, identity.M20());
			Assert::AreEqual(0.f, identity.M01());
			Assert::AreEqual(1.f, identity.M11());
			Assert::AreEqual(0.f, identity.M21());
			Assert::AreEqual(0.f, identity.M02());
			Assert::AreEqual(0.f, identity.M12());
			Assert::AreEqual(1.f, identity.M22());

			constexpr auto zero = PonyEngine::Math::Matrix3x3<float>::CreateZero();
			Assert::AreEqual(0.f, zero.M00());
			Assert::AreEqual(0.f, zero.M10());
			Assert::AreEqual(0.f, zero.M20());
			Assert::AreEqual(0.f, zero.M01());
			Assert::AreEqual(0.f, zero.M11());
			Assert::AreEqual(0.f, zero.M21());
			Assert::AreEqual(0.f, zero.M02());
			Assert::AreEqual(0.f, zero.M12());
			Assert::AreEqual(0.f, zero.M22());

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

			constexpr auto multipliedLI = PonyEngine::Math::Matrix3x3<short>(2, 3, -1, 5, 5, 1, 4, 9, -7) * 3;
			constexpr auto multipliedRI = 3 * PonyEngine::Math::Matrix3x3<short>(2, 3, -1, 5, 5, 1, 4, 9, -7);

			constexpr auto divided = matrix / 3.f;
#pragma warning(default:4189)
		}
	};
}
