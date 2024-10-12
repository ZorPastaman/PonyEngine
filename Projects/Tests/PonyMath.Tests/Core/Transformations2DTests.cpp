/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <numbers>

import PonyMath.Core;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(Transformations2DTests)
	{
		TEST_METHOD(AngleFromMatrixTest)
		{
			auto matrix = PonyMath::Core::Matrix2x2<float>::Predefined::Identity;
			float angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(0., static_cast<double>(angle), 0.001);

			matrix = PonyMath::Core::Matrix2x2<float>(0.f, 1.f, -1.f, 0.f);
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(std::numbers::pi_v<double> / 2, static_cast<double>(angle), 0.001);

			matrix = -PonyMath::Core::Matrix2x2<float>::Predefined::Identity;
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(std::numbers::pi_v<double>, static_cast<double>(std::abs(angle)), 0.001);

			matrix = PonyMath::Core::Matrix2x2<float>(0.f, -1.f, 1.f, 0.f);
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(-std::numbers::pi_v<double> / 2, static_cast<double>(angle), 0.001);

			matrix = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(1.065, static_cast<double>(angle), 0.001);

			matrix = PonyMath::Core::Matrix2x2<float>(-0.545f, 0.839f, -0.839f, -0.545f);
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(2.147, static_cast<double>(angle), 0.001);

			matrix = PonyMath::Core::Matrix2x2<float>(-0.788f, -0.616f, 0.616f, -0.788f);
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(-2.478, static_cast<double>(angle), 0.001);

			matrix = PonyMath::Core::Matrix2x2<float>(0.766f, -0.643f, 0.643f, 0.766f);
			angle = PonyMath::Core::Angle(matrix);
			Assert::AreEqual(-0.698, static_cast<double>(angle), 0.001);
		}

		TEST_METHOD(MatrixFromAngleTest)
		{
			float angle = 0.f;
			auto matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(1., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M11()), 0.001);

			angle = std::numbers::pi_v<float> / 2;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(0., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M11()), 0.001);

			angle = std::numbers::pi_v<float>;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(1., static_cast<double>(std::abs(matrix.M00())), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1., static_cast<double>(std::abs(matrix.M11())), 0.001);

			angle = -std::numbers::pi_v<float> / 2;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(0., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M11()), 0.001);

			angle = 1.065f;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(0.485, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.875, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.875, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.485, static_cast<double>(matrix.M11()), 0.001);

			angle = 2.147f;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(-0.545, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.839, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.839, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.545, static_cast<double>(matrix.M11()), 0.001);

			angle = -2.478f;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(-0.788, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.616, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.616, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.788, static_cast<double>(matrix.M11()), 0.001);

			angle = -0.698f;
			matrix = PonyMath::Core::RotationMatrix(angle);
			Assert::AreEqual(0.766, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.643, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.643, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.766, static_cast<double>(matrix.M11()), 0.001);
		}

		TEST_METHOD(RsMatrixFromAngleScalingTest)
		{
			float angle = 1.065f;
			auto scaling = PonyMath::Core::Vector2<float>(2.f, 3.f);
			auto matrix = PonyMath::Core::RsMatrix(angle, scaling);
			Assert::AreEqual(0.97, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(1.75, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-2.625, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1.454, static_cast<double>(matrix.M11()), 0.001);

			angle = 1.065f;
			scaling = PonyMath::Core::Vector2<float>(-4.f, 6.f);
			matrix = PonyMath::Core::RsMatrix(angle, scaling);
			Assert::AreEqual(-1.938, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-3.5, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-5.249, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(2.907, static_cast<double>(matrix.M11()), 0.001);

			angle = 1.065f;
			scaling = PonyMath::Core::Vector2<float>(3.f, -2.f);
			matrix = PonyMath::Core::RsMatrix(angle, scaling);
			Assert::AreEqual(1.454, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(2.625, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(1.75, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.97, static_cast<double>(matrix.M11()), 0.001);

			angle = 1.065f;
			scaling = PonyMath::Core::Vector2<float>(-0.5f, -1.f);
			matrix = PonyMath::Core::RsMatrix(angle, scaling);
			Assert::AreEqual(-0.243, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.438, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.875, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.485, static_cast<double>(matrix.M11()), 0.001);
		}

		TEST_METHOD(RsMatrixFromRotationMatrixScalingTest)
		{
			auto rotation = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			auto scaling = PonyMath::Core::Vector2<float>(2.f, 3.f);
			auto matrix = PonyMath::Core::RsMatrix(rotation, scaling);
			Assert::AreEqual(0.97, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(1.75, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-2.625, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1.455, static_cast<double>(matrix.M11()), 0.001);

			rotation = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			scaling = PonyMath::Core::Vector2<float>(-4.f, 6.f);
			matrix = PonyMath::Core::RsMatrix(rotation, scaling);
			Assert::AreEqual(-1.94, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-3.5, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-5.25, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(2.91, static_cast<double>(matrix.M11()), 0.001);

			rotation = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			scaling = PonyMath::Core::Vector2<float>(3.f, -2.f);
			matrix = PonyMath::Core::RsMatrix(rotation, scaling);
			Assert::AreEqual(1.455, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(2.625, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(1.75, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.97, static_cast<double>(matrix.M11()), 0.001);

			rotation = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			scaling = PonyMath::Core::Vector2<float>(-0.5f, -1.f);
			matrix = PonyMath::Core::RsMatrix(rotation, scaling);
			Assert::AreEqual(-0.243, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.438, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.875, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.485, static_cast<double>(matrix.M11()), 0.001);
		}

		TEST_METHOD(TrsMatrixFromTranslationAngleScalingTest)
		{
			constexpr auto translation = PonyMath::Core::Vector2<float>(-3, 7);
			constexpr auto rotation = 1.065f;
			constexpr auto scaling = PonyMath::Core::Vector2<float>(-2.f, 3.f);
			auto matrix = PonyMath::Core::TrsMatrix(translation, rotation, scaling);
			Assert::AreEqual(-0.97, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-1.75, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-2.625, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1.454, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-3., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(7., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M22()), 0.001);
		}

		TEST_METHOD(TrsMatrixFromRsMatrixTest)
		{
			constexpr auto rotation = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			constexpr auto scaling = PonyMath::Core::Vector2<float>(-2.f, 3.f);
			constexpr auto rsMatrix = PonyMath::Core::RsMatrix(rotation, scaling);
			auto matrix = PonyMath::Core::TrsMatrix(rsMatrix);
			Assert::AreEqual(-0.97, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-1.75, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-2.625, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1.455, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M22()), 0.001);
		}

		TEST_METHOD(TrsMatrixFromTranslationRsMatrixTest)
		{
			constexpr auto translation = PonyMath::Core::Vector2<float>(-3, 7);
			constexpr auto rotation = PonyMath::Core::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			constexpr auto scaling = PonyMath::Core::Vector2<float>(-2.f, 3.f);
			constexpr auto rsMatrix = PonyMath::Core::RsMatrix(rotation, scaling);
			auto matrix = PonyMath::Core::TrsMatrix(translation, rsMatrix);
			Assert::AreEqual(-0.97, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-1.75, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-2.625, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1.455, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-3., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(7., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M22()), 0.001);
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
			Assert::AreEqual(1.065, static_cast<double>(angle), 0.001);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(-1.94f, -3.5f, -5.25f, 2.91f);
			angle = PonyMath::Core::ExtractAngle(rsMatrix);
			Assert::AreEqual(-2.077, static_cast<double>(angle), 0.001);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(1.455f, 2.625f, 1.75f, -0.97f);
			angle = PonyMath::Core::ExtractAngle(rsMatrix);
			Assert::AreEqual(1.065, static_cast<double>(angle), 0.001);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(-0.243f, -0.438f, 0.875f, -0.485f);
			angle = PonyMath::Core::ExtractAngle(rsMatrix);
			Assert::AreEqual(-2.077, static_cast<double>(angle), 0.001);
		}

		TEST_METHOD(AngleFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyMath::Core::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			const float angle = PonyMath::Core::ExtractAngle(trsMatrix);
			Assert::AreEqual(-2.077, static_cast<double>(angle), 0.001);
		}

		TEST_METHOD(RotationMatrixFromRsMatrixTest)
		{
			auto rsMatrix = PonyMath::Core::Matrix2x2<float>(0.97f, 1.75f, -2.625f, 1.455f);
			PonyMath::Core::Matrix2x2<float> matrix = PonyMath::Core::ExtractRotationMatrix2D(rsMatrix);
			Assert::AreEqual(0.485, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.875, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.875, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.485, static_cast<double>(matrix.M11()), 0.001);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(-1.94f, -3.5f, 5.25f, -2.91f);
			matrix = PonyMath::Core::ExtractRotationMatrix2D(rsMatrix);
			Assert::AreEqual(-0.485, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.875, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.875, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.485, static_cast<double>(matrix.M11()), 0.001);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(-1.455f, 2.625f, -1.75f, -0.97f);
			matrix = PonyMath::Core::ExtractRotationMatrix2D(rsMatrix);
			Assert::AreEqual(-0.485, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.875, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.875, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.485, static_cast<double>(matrix.M11()), 0.001);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(-0.243f, -0.438f, 0.875f, -0.485f);
			matrix = PonyMath::Core::ExtractRotationMatrix2D(rsMatrix);
			Assert::AreEqual(-0.485, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.875, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.875, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.485, static_cast<double>(matrix.M11()), 0.001);
		}

		TEST_METHOD(RotationMatrixFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyMath::Core::Matrix3x3<float>(0.97f, 1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyMath::Core::Matrix2x2<float> matrix = PonyMath::Core::ExtractRotationMatrix2D(trsMatrix);
			Assert::AreEqual(0.485, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.875, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.875, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.485, static_cast<double>(matrix.M11()), 0.001);
		}

		TEST_METHOD(ScalingFromRsMatrixTest)
		{
			auto rsMatrix = PonyMath::Core::Matrix2x2<float>(0.97f, 1.75f, -2.625f, 1.455f);
			PonyMath::Core::Vector2<float> scaling = PonyMath::Core::ExtractScaling2D(rsMatrix);
			Assert::AreEqual(2., static_cast<double>(scaling.X()), 0.005);
			Assert::AreEqual(3., static_cast<double>(scaling.Y()), 0.005);

			rsMatrix = PonyMath::Core::Matrix2x2<float>(-0.243f, -0.438f, 0.875f, -0.485f);
			scaling = PonyMath::Core::ExtractScaling2D(rsMatrix);
			Assert::AreEqual(0.5, static_cast<double>(scaling.X()), 0.005);
			Assert::AreEqual(1., static_cast<double>(scaling.Y()), 0.005);
		}

		TEST_METHOD(ScalingFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyMath::Core::Matrix3x3<float>(0.97f, 1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyMath::Core::Vector2<float> scaling = PonyMath::Core::ExtractScaling2D(trsMatrix);
			Assert::AreEqual(2., static_cast<double>(scaling.X()), 0.005);
			Assert::AreEqual(3., static_cast<double>(scaling.Y()), 0.005);
		}

		TEST_METHOD(RsMatrixFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyMath::Core::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyMath::Core::Matrix2x2<float> matrix = PonyMath::Core::ExtractRsMatrix(trsMatrix);
			Assert::AreEqual(-0.97, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-1.75, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-2.625, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1.455, static_cast<double>(matrix.M11()), 0.001);
		}

		TEST_METHOD(RotateVectorTest)
		{
			constexpr auto vector = PonyMath::Core::Vector2<float>(-2.f, 3.f);
			float angle = 1.01f;
			PonyMath::Core::Vector2<float> rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(-3.604, static_cast<double>(rotated.X()), 0.001);
			Assert::AreEqual(-0.098, static_cast<double>(rotated.Y()), 0.001);

			angle = 2.52f;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(-0.121, static_cast<double>(rotated.X()), 0.001);
			Assert::AreEqual(-3.604, static_cast<double>(rotated.Y()), 0.001);

			angle = -2.49f;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(3.41, static_cast<double>(rotated.X()), 0.001);
			Assert::AreEqual(-1.173, static_cast<double>(rotated.Y()), 0.001);

			angle = -0.78f;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(0.688, static_cast<double>(rotated.X()), 0.001);
			Assert::AreEqual(3.539, static_cast<double>(rotated.Y()), 0.001);

			angle = 0.f;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(-2., static_cast<double>(rotated.X()), 0.001);
			Assert::AreEqual(3., static_cast<double>(rotated.Y()), 0.001);

			angle = std::numbers::pi_v<float> / 2.f;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(-3., static_cast<double>(rotated.X()), 0.001);
			Assert::AreEqual(-2., static_cast<double>(rotated.Y()), 0.001);

			angle = -std::numbers::pi_v<float> / 2.f;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(3., static_cast<double>(rotated.X()), 0.001);
			Assert::AreEqual(2., static_cast<double>(rotated.Y()), 0.001);

			angle = std::numbers::pi_v<float>;
			rotated = PonyMath::Core::Rotate(vector, angle);
			Assert::AreEqual(2., static_cast<double>(rotated.X()), 0.001);
			Assert::AreEqual(-3., static_cast<double>(rotated.Y()), 0.001);
		}

		TEST_METHOD(TranformPointTest)
		{
			constexpr auto vector = PonyMath::Core::Vector2<float>(4.f, -1.f);
			auto trsMatrix = PonyMath::Core::Matrix3x3<float>(0.97f, 1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyMath::Core::Vector2<float> transformed = PonyMath::Core::TransformPoint(trsMatrix, vector);
			Assert::AreEqual(3.505, static_cast<double>(transformed.X()), 0.005);
			Assert::AreEqual(12.545, static_cast<double>(transformed.Y()), 0.005);

			trsMatrix = PonyMath::Core::Matrix3x3<float>(2.298f, -1.929f, 0.f, -0.450f, -0.536f, 0.f, 5.f, -1.f, 1.f);
			transformed = PonyMath::Core::TransformPoint(trsMatrix, vector);
			Assert::AreEqual(14.643, static_cast<double>(transformed.X()), 0.005);
			Assert::AreEqual(-8.176, static_cast<double>(transformed.Y()), 0.005);
		}

		TEST_METHOD(TranformDirectionTest)
		{
			constexpr auto vector = PonyMath::Core::Vector2<float>(4.f, -1.f);
			auto trsMatrix = PonyMath::Core::Matrix3x3<float>(0.97f, 1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyMath::Core::Vector2<float> transformed = PonyMath::Core::TransformDirection(trsMatrix, vector);
			Assert::AreEqual(6.505, static_cast<double>(transformed.X()), 0.005);
			Assert::AreEqual(5.545, static_cast<double>(transformed.Y()), 0.005);

			trsMatrix = PonyMath::Core::Matrix3x3<float>(2.298f, -1.929f, 0.f, -0.450f, -0.536f, 0.f, 5.f, -1.f, 1.f);
			transformed = PonyMath::Core::TransformDirection(trsMatrix, vector);
			Assert::AreEqual(9.643, static_cast<double>(transformed.X()), 0.005);
			Assert::AreEqual(-7.176, static_cast<double>(transformed.Y()), 0.005);
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			constexpr auto rsMatrix = PonyMath::Core::Matrix2x2<float>(-0.97f, -1.75f, -2.625f, 1.455f);
			constexpr PonyMath::Core::Matrix3x3<float> trsMatrix = PonyMath::Core::TrsMatrix(rsMatrix);
			constexpr auto translation = PonyMath::Core::Vector2<float>(-3, 7);
			constexpr PonyMath::Core::Matrix3x3<float> trsMatrixT = PonyMath::Core::TrsMatrix(translation, rsMatrix);
			constexpr PonyMath::Core::Vector2<float> translationE = PonyMath::Core::ExtractTranslation(trsMatrixT);
			constexpr PonyMath::Core::Matrix2x2<float> rsMatrixE = PonyMath::Core::ExtractRsMatrix(trsMatrixT);
			constexpr PonyMath::Core::Vector2<float> point = PonyMath::Core::TransformPoint(trsMatrixT, translation);
			constexpr PonyMath::Core::Vector2<float> direction = PonyMath::Core::TransformDirection(trsMatrixT, translation);
		}
	};
}
