/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cmath>
#include <numbers>

import PonyMath.Core;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(Transformations2DTests)
	{
		TEST_METHOD(AngleFromMatrixTest)
		{
			auto matrix = PonyMath::Core::Matrix2x2<float>::Predefined::Identity;
			float angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(0.f, angle, 0.001f);

			matrix = PonyMath::Core::Matrix2x2<float>(0.f, 1.f, -1.f, 0.f);
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(std::numbers::pi_v<float> / 2.f, angle, 0.001f);

			matrix = -PonyMath::Core::Matrix2x2<float>::Predefined::Identity;
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(std::numbers::pi_v<float>, std::abs(angle), 0.001f);

			matrix = PonyMath::Core::Matrix2x2<float>(0.f, -1.f, 1.f, 0.f);
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(-std::numbers::pi_v<float> / 2.f, angle, 0.001f);

			matrix = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(1.065f, angle, 0.001f);

			matrix = PonyMath::Core::Matrix2x2<float>(-0.545f, 0.839f, -0.839f, -0.545f);
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(2.147f, angle, 0.001f);

			matrix = PonyMath::Core::Matrix2x2<float>(-0.788f, -0.616f, 0.616f, -0.788f);
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(-2.478f, angle, 0.001f);

			matrix = PonyMath::Core::Matrix2x2<float>(0.766f, -0.643f, 0.643f, 0.766f);
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(-0.698f, angle, 0.001f);
		}

		TEST_METHOD(MatrixFromAngleTest)
		{
			float angle = 0.f;
			auto matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(1.f, matrix.M00(), 0.001f);
			Assert::AreEqual(0.f, matrix.M10(), 0.001f);
			Assert::AreEqual(0.f, matrix.M01(), 0.001f);
			Assert::AreEqual(1.f, matrix.M11(), 0.001f);

			angle = std::numbers::pi_v<float> / 2.f;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(0.f, matrix.M00(), 0.001f);
			Assert::AreEqual(1.f, matrix.M10(), 0.001f);
			Assert::AreEqual(-1.f, matrix.M01(), 0.001f);
			Assert::AreEqual(0.f, matrix.M11(), 0.001f);

			angle = std::numbers::pi_v<float>;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(1.f, std::abs(matrix.M00()), 0.001f);
			Assert::AreEqual(0.f, matrix.M10(), 0.001f);
			Assert::AreEqual(0.f, matrix.M01(), 0.001f);
			Assert::AreEqual(1.f, std::abs(matrix.M11()), 0.001f);

			angle = -std::numbers::pi_v<float> / 2.f;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(0.f, matrix.M00(), 0.001f);
			Assert::AreEqual(-1.f, matrix.M10(), 0.001f);
			Assert::AreEqual(1.f, matrix.M01(), 0.001f);
			Assert::AreEqual(0.f, matrix.M11(), 0.001f);

			angle = 1.065f;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(0.485f, matrix.M00(), 0.001f);
			Assert::AreEqual(0.875f, matrix.M10(), 0.001f);
			Assert::AreEqual(-0.875f, matrix.M01(), 0.001f);
			Assert::AreEqual(0.485f, matrix.M11(), 0.001f);

			angle = 2.147f;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(-0.545f, matrix.M00(), 0.001f);
			Assert::AreEqual(0.839f, matrix.M10(), 0.001f);
			Assert::AreEqual(-0.839f, matrix.M01(), 0.001f);
			Assert::AreEqual(-0.545f, matrix.M11(), 0.001f);

			angle = -2.478f;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(-0.788f, matrix.M00(), 0.001f);
			Assert::AreEqual(-0.616f, matrix.M10(), 0.001f);
			Assert::AreEqual(0.616f, matrix.M01(), 0.001f);
			Assert::AreEqual(-0.788f, matrix.M11(), 0.001f);

			angle = -0.698f;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(0.766f, matrix.M00(), 0.001f);
			Assert::AreEqual(-0.643f, matrix.M10(), 0.001f);
			Assert::AreEqual(0.643f, matrix.M01(), 0.001f);
			Assert::AreEqual(0.766f, matrix.M11(), 0.001f);
		}

		TEST_METHOD(RsMatrixFromAngleScalingTest)
		{
			float angle = 1.065f;
			auto scaling = PonyMath::Core::Vector2<float>(2.f, 3.f);
			auto matrix = PonyMath::Core::RsMatrix(angle, scaling);
			Assert::AreEqual(0.97f, matrix.M00(), 0.001f);
			Assert::AreEqual(1.75f, matrix.M10(), 0.001f);
			Assert::AreEqual(-2.625f, matrix.M01(), 0.001f);
			Assert::AreEqual(1.454f, matrix.M11(), 0.001f);

			angle = 1.065f;
			scaling = PonyMath::Core::Vector2<float>(-4.f, 6.f);
			matrix = PonyMath::Core::RsMatrix(angle, scaling);
			Assert::AreEqual(-1.938f, matrix.M00(), 0.001f);
			Assert::AreEqual(-3.5f, matrix.M10(), 0.001f);
			Assert::AreEqual(-5.249f, matrix.M01(), 0.001f);
			Assert::AreEqual(2.907f, matrix.M11(), 0.001f);

			angle = 1.065f;
			scaling = PonyMath::Core::Vector2<float>(3.f, -2.f);
			matrix = PonyMath::Core::RsMatrix(angle, scaling);
			Assert::AreEqual(1.454f, matrix.M00(), 0.001f);
			Assert::AreEqual(2.625f, matrix.M10(), 0.001f);
			Assert::AreEqual(1.75f, matrix.M01(), 0.001f);
			Assert::AreEqual(-0.97f, matrix.M11(), 0.001f);

			angle = 1.065f;
			scaling = PonyMath::Core::Vector2<float>(-0.5f, -1.f);
			matrix = PonyMath::Core::RsMatrix(angle, scaling);
			Assert::AreEqual(-0.243f, matrix.M00(), 0.001f);
			Assert::AreEqual(-0.438f, matrix.M10(), 0.001f);
			Assert::AreEqual(0.875f, matrix.M01(), 0.001f);
			Assert::AreEqual(-0.485f, matrix.M11(), 0.001f);
		}

		TEST_METHOD(RsMatrixFromRotationMatrixScalingTest)
		{
			auto rotation = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			auto scaling = PonyMath::Core::Vector2<float>(2.f, 3.f);
			auto matrix = PonyMath::Core::RsMatrix(rotation, scaling);
			Assert::AreEqual(0.97f, matrix.M00(), 0.001f);
			Assert::AreEqual(1.75f, matrix.M10(), 0.001f);
			Assert::AreEqual(-2.625f, matrix.M01(), 0.001f);
			Assert::AreEqual(1.455f, matrix.M11(), 0.001f);

			rotation = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			scaling = PonyMath::Core::Vector2<float>(-4.f, 6.f);
			matrix = PonyMath::Core::RsMatrix(rotation, scaling);
			Assert::AreEqual(-1.94f, matrix.M00(), 0.001f);
			Assert::AreEqual(-3.5f, matrix.M10(), 0.001f);
			Assert::AreEqual(-5.25f, matrix.M01(), 0.001f);
			Assert::AreEqual(2.91f, matrix.M11(), 0.001f);

			rotation = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			scaling = PonyMath::Core::Vector2<float>(3.f, -2.f);
			matrix = PonyMath::Core::RsMatrix(rotation, scaling);
			Assert::AreEqual(1.455f, matrix.M00(), 0.001f);
			Assert::AreEqual(2.625f, matrix.M10(), 0.001f);
			Assert::AreEqual(1.75f, matrix.M01(), 0.001f);
			Assert::AreEqual(-0.97f, matrix.M11(), 0.001f);

			rotation = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			scaling = PonyMath::Core::Vector2<float>(-0.5f, -1.f);
			matrix = PonyMath::Core::RsMatrix(rotation, scaling);
			Assert::AreEqual(-0.243f, matrix.M00(), 0.001f);
			Assert::AreEqual(-0.438f, matrix.M10(), 0.001f);
			Assert::AreEqual(0.875f, matrix.M01(), 0.001f);
			Assert::AreEqual(-0.485f, matrix.M11(), 0.001f);
		}

		TEST_METHOD(TrsMatrixFromTranslationAngleScalingTest)
		{
			constexpr PonyMath::Core::Vector2<float> translation(-3.f, 7.f);
			constexpr float rotation = 1.065f;
			constexpr PonyMath::Core::Vector2<float> scaling(-2.f, 3.f);
			auto matrix = PonyMath::Core::TrsMatrix(translation, rotation, scaling);
			Assert::AreEqual(-0.97f, matrix.M00(), 0.001f);
			Assert::AreEqual(-1.75f, matrix.M10(), 0.001f);
			Assert::AreEqual(0.f, matrix.M20(), 0.001f);
			Assert::AreEqual(-2.625f, matrix.M01(), 0.001f);
			Assert::AreEqual(1.454f, matrix.M11(), 0.001f);
			Assert::AreEqual(0.f, matrix.M21(), 0.001f);
			Assert::AreEqual(-3.f, matrix.M02(), 0.001f);
			Assert::AreEqual(7.f, matrix.M12(), 0.001f);
			Assert::AreEqual(1.f, matrix.M22(), 0.001f);
		}

		TEST_METHOD(TrsMatrixFromRsMatrixTest)
		{
			constexpr auto rotation = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);  
			constexpr auto scaling = PonyMath::Core::Vector2<float>(-2.f, 3.f);  
			constexpr auto rsMatrix = PonyMath::Core::RsMatrix(rotation, scaling);  
			auto matrix = PonyMath::Core::TrsMatrix(rsMatrix);  
			Assert::AreEqual(-0.97f, matrix.M00(), 0.001f);  
			Assert::AreEqual(-1.75f, matrix.M10(), 0.001f);  
			Assert::AreEqual(0.f, matrix.M20(), 0.001f);  
			Assert::AreEqual(-2.625f, matrix.M01(), 0.001f);  
			Assert::AreEqual(1.455f, matrix.M11(), 0.001f);  
			Assert::AreEqual(0.f, matrix.M21(), 0.001f);  
			Assert::AreEqual(0.f, matrix.M02(), 0.001f);  
			Assert::AreEqual(0.f, matrix.M12(), 0.001f);  
			Assert::AreEqual(1.f, matrix.M22(), 0.001f);
		}

		TEST_METHOD(TrsMatrixFromTranslationRsMatrixTest)
		{
			constexpr PonyMath::Core::Vector2<float> translation(-3.f, 7.f);
			constexpr PonyMath::Core::Matrix2x2<float> rotation(0.485f, 0.875f, -0.875f, 0.485f);
			constexpr PonyMath::Core::Vector2<float> scaling(-2.f, 3.f);
			constexpr PonyMath::Core::Matrix2x2<float> rsMatrix = PonyMath::Core::RsMatrix(rotation, scaling);
			PonyMath::Core::Matrix3x3<float> matrix = PonyMath::Core::TrsMatrix(translation, rsMatrix);
			Assert::AreEqual(-0.97f, matrix.M00(), 0.001f);
			Assert::AreEqual(-1.75f, matrix.M10(), 0.001f);
			Assert::AreEqual(0.f, matrix.M20(), 0.001f);
			Assert::AreEqual(-2.625f, matrix.M01(), 0.001f);
			Assert::AreEqual(1.455f, matrix.M11(), 0.001f);
			Assert::AreEqual(0.f, matrix.M21(), 0.001f);
			Assert::AreEqual(-3.f, matrix.M02(), 0.001f);
			Assert::AreEqual(7.f, matrix.M12(), 0.001f);
			Assert::AreEqual(1.f, matrix.M22(), 0.001f);
		}

		TEST_METHOD(TranslationFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyMath::Core::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyMath::Core::Vector2<float> translation = PonyMath::Core::ExtractTranslation(trsMatrix);
			Assert::AreEqual(-3.f, translation.X());
			Assert::AreEqual(7.f, translation.Y());
		}

		TEST_METHOD(AngleFromRsMatrixTest)
		{
			auto rsMatrix = PonyMath::Core::Matrix2x2<float>(0.97f, 1.75f, -2.625f, 1.455f);
			float angle = PonyMath::Core::ExtractAngle(rsMatrix);
			Assert::AreEqual(1.065f, angle, 0.001f);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(-1.94f, -3.5f, -5.25f, 2.91f);
			angle = PonyMath::Core::ExtractAngle(rsMatrix);
			Assert::AreEqual(-2.077f, angle, 0.001f);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(1.455f, 2.625f, 1.75f, -0.97f);
			angle = PonyMath::Core::ExtractAngle(rsMatrix);
			Assert::AreEqual(1.065f, angle, 0.001f);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(-0.243f, -0.438f, 0.875f, -0.485f);
			angle = PonyMath::Core::ExtractAngle(rsMatrix);
			Assert::AreEqual(-2.077f, angle, 0.001f);
		}

		TEST_METHOD(AngleFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyMath::Core::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			const float angle = PonyMath::Core::ExtractAngle(trsMatrix);
			Assert::AreEqual(-2.077f, angle, 0.001f);
		}

		TEST_METHOD(RotationMatrixFromRsMatrixTest)
		{
			auto rsMatrix = PonyMath::Core::Matrix2x2<float>(0.97f, 1.75f, -2.625f, 1.455f);
			PonyMath::Core::Matrix2x2<float> matrix = PonyMath::Core::ExtractRotationMatrix2D(rsMatrix);
			Assert::AreEqual(0.485f, matrix.M00(), 0.001f);
			Assert::AreEqual(0.875f, matrix.M10(), 0.001f);
			Assert::AreEqual(-0.875f, matrix.M01(), 0.001f);
			Assert::AreEqual(0.485f, matrix.M11(), 0.001f);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(-1.94f, -3.5f, 5.25f, -2.91f);
			matrix = PonyMath::Core::ExtractRotationMatrix2D(rsMatrix);
			Assert::AreEqual(-0.485f, matrix.M00(), 0.001f);
			Assert::AreEqual(-0.875f, matrix.M10(), 0.001f);
			Assert::AreEqual(0.875f, matrix.M01(), 0.001f);
			Assert::AreEqual(-0.485f, matrix.M11(), 0.001f);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(-1.455f, 2.625f, -1.75f, -0.97f);
			matrix = PonyMath::Core::ExtractRotationMatrix2D(rsMatrix);
			Assert::AreEqual(-0.485f, matrix.M00(), 0.001f);
			Assert::AreEqual(0.875f, matrix.M10(), 0.001f);
			Assert::AreEqual(-0.875f, matrix.M01(), 0.001f);
			Assert::AreEqual(-0.485f, matrix.M11(), 0.001f);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(-0.243f, -0.438f, 0.875f, -0.485f);
			matrix = PonyMath::Core::ExtractRotationMatrix2D(rsMatrix);
			Assert::AreEqual(-0.485f, matrix.M00(), 0.001f);
			Assert::AreEqual(-0.875f, matrix.M10(), 0.001f);
			Assert::AreEqual(0.875f, matrix.M01(), 0.001f);
			Assert::AreEqual(-0.485f, matrix.M11(), 0.001f);
		}

		TEST_METHOD(RotationMatrixFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyMath::Core::Matrix3x3<float>(0.97f, 1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);  
			PonyMath::Core::Matrix2x2<float> matrix = PonyMath::Core::ExtractRotationMatrix2D(trsMatrix);  
			Assert::AreEqual(0.485f, matrix.M00(), 0.001f);  
			Assert::AreEqual(0.875f, matrix.M10(), 0.001f);  
			Assert::AreEqual(-0.875f, matrix.M01(), 0.001f);  
			Assert::AreEqual(0.485f, matrix.M11(), 0.001f);
		}

		TEST_METHOD(ScalingFromRsMatrixTest)
		{
			auto rsMatrix = PonyMath::Core::Matrix2x2<float>(0.97f, 1.75f, -2.625f, 1.455f);
			PonyMath::Core::Vector2<float> scaling = PonyMath::Core::ExtractScaling2D(rsMatrix);
			Assert::AreEqual(2.f, scaling.X(), 0.005f);
			Assert::AreEqual(3.f, scaling.Y(), 0.005f);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(-0.243f, -0.438f, 0.875f, -0.485f);
			scaling = PonyMath::Core::ExtractScaling2D(rsMatrix);
			Assert::AreEqual(0.5f, scaling.X(), 0.005f);
			Assert::AreEqual(1.f, scaling.Y(), 0.005f);
		}

		TEST_METHOD(ScalingFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyMath::Core::Matrix3x3<float>(0.97f, 1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyMath::Core::Vector2<float> scaling = PonyMath::Core::ExtractScaling2D(trsMatrix);
			Assert::AreEqual(2.f, scaling.X(), 0.005f);
			Assert::AreEqual(3.f, scaling.Y(), 0.005f);
		}

		TEST_METHOD(RsMatrixFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyMath::Core::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyMath::Core::Matrix2x2<float> matrix = PonyMath::Core::ExtractRsMatrix(trsMatrix);
			Assert::AreEqual(-0.97f, matrix.M00(), 0.001f);
			Assert::AreEqual(-1.75f, matrix.M10(), 0.001f);
			Assert::AreEqual(-2.625f, matrix.M01(), 0.001f);
			Assert::AreEqual(1.455f, matrix.M11(), 0.001f);
		}

		TEST_METHOD(RotateVectorTest)
		{
			constexpr PonyMath::Core::Vector2<float> vector(-2.f, 3.f);
			float angle = 1.01f;
			PonyMath::Core::Vector2<float> rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(-3.604f, rotated.X(), 0.001f);
			Assert::AreEqual(-0.098f, rotated.Y(), 0.001f);

			angle = 2.52f;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(-0.121f, rotated.X(), 0.001f);
			Assert::AreEqual(-3.604f, rotated.Y(), 0.001f);

			angle = -2.49f;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(3.41f, rotated.X(), 0.001f);
			Assert::AreEqual(-1.173f, rotated.Y(), 0.001f);

			angle = -0.78f;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(0.688f, rotated.X(), 0.001f);
			Assert::AreEqual(3.539f, rotated.Y(), 0.001f);

			angle = 0.f;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(-2.f, rotated.X(), 0.001f);
			Assert::AreEqual(3.f, rotated.Y(), 0.001f);

			angle = std::numbers::pi_v<float> / 2.f;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(-3.f, rotated.X(), 0.001f);
			Assert::AreEqual(-2.f, rotated.Y(), 0.001f);

			angle = -std::numbers::pi_v<float> / 2.f;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(3.f, rotated.X(), 0.001f);
			Assert::AreEqual(2.f, rotated.Y(), 0.001f);

			angle = std::numbers::pi_v<float>;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(2.f, rotated.X(), 0.001f);
			Assert::AreEqual(-3.f, rotated.Y(), 0.001f);
		}

		TEST_METHOD(TranformPointTest)
		{
			constexpr PonyMath::Core::Vector2<float> vector(4.f, -1.f);
			PonyMath::Core::Matrix3x3<float> trsMatrix(0.97f, 1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyMath::Core::Vector2<float> transformed = PonyMath::Core::TransformPoint(trsMatrix, vector);
			Assert::AreEqual(3.505f, transformed.X(), 0.005f);
			Assert::AreEqual(12.545f, transformed.Y(), 0.005f);

			trsMatrix = PonyMath::Core::Matrix3x3<float>(2.298f, -1.929f, 0.f, -0.450f, -0.536f, 0.f, 5.f, -1.f, 1.f);
			transformed = PonyMath::Core::TransformPoint(trsMatrix, vector);
			Assert::AreEqual(14.643f, transformed.X(), 0.005f);
			Assert::AreEqual(-8.176f, transformed.Y(), 0.005f);
		}

		TEST_METHOD(TranformDirectionTest)
		{
			constexpr PonyMath::Core::Vector2<float> vector(4.f, -1.f);
			PonyMath::Core::Matrix3x3<float> trsMatrix(0.97f, 1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyMath::Core::Vector2<float> transformed = PonyMath::Core::TransformDirection(trsMatrix, vector);
			Assert::AreEqual(6.505f, transformed.X(), 0.005f);
			Assert::AreEqual(5.545f, transformed.Y(), 0.005f);

			trsMatrix = PonyMath::Core::Matrix3x3<float>(2.298f, -1.929f, 0.f, -0.450f, -0.536f, 0.f, 5.f, -1.f, 1.f);
			transformed = PonyMath::Core::TransformDirection(trsMatrix, vector);
			Assert::AreEqual(9.643f, transformed.X(), 0.005f);
			Assert::AreEqual(-7.176f, transformed.Y(), 0.005f);
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto rsMatrix = PonyMath::Core::Matrix2x2<float>(-0.97f, -1.75f, -2.625f, 1.455f);
			[[maybe_unused]] constexpr PonyMath::Core::Matrix3x3<float> trsMatrix = PonyMath::Core::TrsMatrix(rsMatrix);
			[[maybe_unused]] constexpr auto translation = PonyMath::Core::Vector2<float>(-3, 7);
			[[maybe_unused]] constexpr PonyMath::Core::Matrix3x3<float> trsMatrixT = PonyMath::Core::TrsMatrix(translation, rsMatrix);
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> translationE = PonyMath::Core::ExtractTranslation(trsMatrixT);
			[[maybe_unused]] constexpr PonyMath::Core::Matrix2x2<float> rsMatrixE = PonyMath::Core::ExtractRsMatrix(trsMatrixT);
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> point = PonyMath::Core::TransformPoint(trsMatrixT, translation);
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> direction = PonyMath::Core::TransformDirection(trsMatrixT, translation);
		}
	};
}
