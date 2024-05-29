/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <numbers>;

import PonyEngine.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(Transformations2DTests)
	{
		TEST_METHOD(AngleFromMatrixTest)
		{
			auto matrix = PonyEngine::Math::Matrix2x2<float>::Predefined::Identity;
			float angle = PonyEngine::Math::Angle(matrix);
			Assert::AreEqual(0., static_cast<double>(angle), 0.001);

			matrix = PonyEngine::Math::Matrix2x2<float>(0.f, 1.f, -1.f, 0.f);
			angle = PonyEngine::Math::Angle(matrix);
			Assert::AreEqual(std::numbers::pi_v<double> / 2, static_cast<double>(angle), 0.001);

			matrix = -PonyEngine::Math::Matrix2x2<float>::Predefined::Identity;
			angle = PonyEngine::Math::Angle(matrix);
			Assert::AreEqual(std::numbers::pi_v<double>, static_cast<double>(std::abs(angle)), 0.001);

			matrix = PonyEngine::Math::Matrix2x2<float>(0.f, -1.f, 1.f, 0.f);
			angle = PonyEngine::Math::Angle(matrix);
			Assert::AreEqual(-std::numbers::pi_v<double> / 2, static_cast<double>(angle), 0.001);

			matrix = PonyEngine::Math::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			angle = PonyEngine::Math::Angle(matrix);
			Assert::AreEqual(1.065, static_cast<double>(angle), 0.001);

			matrix = PonyEngine::Math::Matrix2x2<float>(-0.545f, 0.839f, -0.839f, -0.545f);
			angle = PonyEngine::Math::Angle(matrix);
			Assert::AreEqual(2.147, static_cast<double>(angle), 0.001);

			matrix = PonyEngine::Math::Matrix2x2<float>(-0.788f, -0.616f, 0.616f, -0.788f);
			angle = PonyEngine::Math::Angle(matrix);
			Assert::AreEqual(-2.478, static_cast<double>(angle), 0.001);

			matrix = PonyEngine::Math::Matrix2x2<float>(0.766f, -0.643f, 0.643f, 0.766f);
			angle = PonyEngine::Math::Angle(matrix);
			Assert::AreEqual(-0.698, static_cast<double>(angle), 0.001);
		}

		TEST_METHOD(MatrixFromAngleTest)
		{
			float angle = 0.f;
			auto matrix = PonyEngine::Math::RotationMatrix(angle);
			Assert::AreEqual(1., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M11()), 0.001);

			angle = std::numbers::pi_v<float> / 2;
			matrix = PonyEngine::Math::RotationMatrix(angle);
			Assert::AreEqual(0., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M11()), 0.001);

			angle = std::numbers::pi_v<float>;
			matrix = PonyEngine::Math::RotationMatrix(angle);
			Assert::AreEqual(1., static_cast<double>(std::abs(matrix.M00())), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1., static_cast<double>(std::abs(matrix.M11())), 0.001);

			angle = -std::numbers::pi_v<float> / 2;
			matrix = PonyEngine::Math::RotationMatrix(angle);
			Assert::AreEqual(0., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M11()), 0.001);

			angle = 1.065f;
			matrix = PonyEngine::Math::RotationMatrix(angle);
			Assert::AreEqual(0.485, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.875, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.875, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.485, static_cast<double>(matrix.M11()), 0.001);

			angle = 2.147f;
			matrix = PonyEngine::Math::RotationMatrix(angle);
			Assert::AreEqual(-0.545, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.839, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.839, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.545, static_cast<double>(matrix.M11()), 0.001);

			angle = -2.478f;
			matrix = PonyEngine::Math::RotationMatrix(angle);
			Assert::AreEqual(-0.788, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.616, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.616, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.788, static_cast<double>(matrix.M11()), 0.001);

			angle = -0.698f;
			matrix = PonyEngine::Math::RotationMatrix(angle);
			Assert::AreEqual(0.766, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.643, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.643, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.766, static_cast<double>(matrix.M11()), 0.001);
		}

		TEST_METHOD(RsMatrixFromAngleScalingTest)
		{
			constexpr float angle = 1.065f;
			constexpr auto scaling = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
			auto matrix = PonyEngine::Math::RsMatrix(angle, scaling);
			Assert::AreEqual(-0.97, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-1.75, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-2.625, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1.454, static_cast<double>(matrix.M11()), 0.001);
		}

		TEST_METHOD(RsMatrixFromRotationMatrixScalingTest)
		{
			constexpr auto rotation = PonyEngine::Math::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			constexpr auto scaling = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
			auto matrix = PonyEngine::Math::RsMatrix(rotation, scaling);
			Assert::AreEqual(-0.97, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-1.75, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-2.625, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1.455, static_cast<double>(matrix.M11()), 0.001);
		}

		TEST_METHOD(TrsMatrixFromTranslationAngleScalingTest)
		{
			constexpr auto translation = PonyEngine::Math::Vector2<float>(-3, 7);
			constexpr auto rotation = 1.065f;
			constexpr auto scaling = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
			auto matrix = PonyEngine::Math::TrsMatrix(translation, rotation, scaling);
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
			constexpr auto rotation = PonyEngine::Math::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			constexpr auto scaling = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
			const auto rsMatrix = PonyEngine::Math::RsMatrix(rotation, scaling);
			auto matrix = PonyEngine::Math::TrsMatrix(rsMatrix);
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
			constexpr auto translation = PonyEngine::Math::Vector2<float>(-3, 7);
			constexpr auto rotation = PonyEngine::Math::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
			constexpr auto scaling = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
			const auto rsMatrix = PonyEngine::Math::RsMatrix(rotation, scaling);
			auto matrix = PonyEngine::Math::TrsMatrix(translation, rsMatrix);
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
			constexpr auto trsMatrix = PonyEngine::Math::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyEngine::Math::Vector2<float> translation = PonyEngine::Math::ExtractTranslationFromTrsMatrix(trsMatrix);
			Assert::AreEqual(-3.f, translation.X());
			Assert::AreEqual(7.f, translation.Y());
		}

		TEST_METHOD(AngleFromRsMatrixTest)
		{
			constexpr auto rsMatrix = PonyEngine::Math::Matrix2x2<float>(-0.97f, -1.75f, -2.625f, 1.455f);
			const float angle = PonyEngine::Math::ExtractAngleFromRsMatrix(rsMatrix);
			Assert::AreEqual(-2.077, static_cast<double>(angle), 0.001);
		}

		TEST_METHOD(AngleFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyEngine::Math::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			const float angle = PonyEngine::Math::ExtractAngleFromTrsMatrix(trsMatrix);
			Assert::AreEqual(-2.077, static_cast<double>(angle), 0.001);
		}

		TEST_METHOD(RotationMatrixFromRsMatrixTest)
		{
			constexpr auto rsMatrix = PonyEngine::Math::Matrix2x2<float>(-0.97f, -1.75f, -2.625f, 1.455f);
			PonyEngine::Math::Matrix2x2<float> matrix = PonyEngine::Math::ExtractRotationMatrixFromRsMatrix(rsMatrix);
			Assert::AreEqual(-0.485, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.875, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.875, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.485, static_cast<double>(matrix.M11()), 0.001);
		}

		TEST_METHOD(RotationMatrixFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyEngine::Math::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyEngine::Math::Matrix2x2<float> matrix = PonyEngine::Math::ExtractRotationMatrixFromTrsMatrix(trsMatrix);
			Assert::AreEqual(-0.485, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.875, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.875, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.485, static_cast<double>(matrix.M11()), 0.001);
		}

		TEST_METHOD(ScalingFromRsMatrixTest)
		{
			constexpr auto rsMatrix = PonyEngine::Math::Matrix2x2<float>(-0.97f, -1.75f, -2.625f, 1.455f);
			PonyEngine::Math::Vector2<float> scaling = PonyEngine::Math::ExtractScalingFromRsMatrix(rsMatrix);
			Assert::AreEqual(2., static_cast<double>(scaling.X()), 0.005);
			Assert::AreEqual(-3., static_cast<double>(scaling.Y()), 0.005);
		}

		TEST_METHOD(ScalingFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyEngine::Math::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyEngine::Math::Vector2<float> scaling = PonyEngine::Math::ExtractScalingFromTrsMatrix(trsMatrix);
			Assert::AreEqual(2., static_cast<double>(scaling.X()), 0.005);
			Assert::AreEqual(-3., static_cast<double>(scaling.Y()), 0.005);
		}

		TEST_METHOD(RsMatrixFromTrsMatrixTest)
		{
			constexpr auto trsMatrix = PonyEngine::Math::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			PonyEngine::Math::Matrix2x2<float> matrix = PonyEngine::Math::ExtractRsMatrixFromTrsMatrix(trsMatrix);
			Assert::AreEqual(-0.97, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-1.75, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-2.625, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1.455, static_cast<double>(matrix.M11()), 0.001);
		}

		TEST_METHOD(RotateVectorTest)
		{
			constexpr auto vector = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
			float angle = 1.56f;
			PonyEngine::Math::Vector2<float> rotated = PonyEngine::Math::Rotate(vector, angle);
			Assert::AreEqual(-3.021, static_cast<double>(rotated.X()), 0.001);
			Assert::AreEqual(-1.968, static_cast<double>(rotated.Y()), 0.001);
		}

		TEST_METHOD(TranformPointTest)
		{
			constexpr auto trsMatrix = PonyEngine::Math::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			constexpr auto vector = PonyEngine::Math::Vector2<float>(4.f, -1.f);
			const PonyEngine::Math::Vector2<float> transformed = PonyEngine::Math::TransformPoint(trsMatrix, vector);
			Assert::AreEqual(-4.252, static_cast<double>(transformed.X()), 0.005);
			Assert::AreEqual(-1.452, static_cast<double>(transformed.Y()), 0.005);
		}

		TEST_METHOD(TranformDirectionTest)
		{
			constexpr auto trsMatrix = PonyEngine::Math::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
			constexpr auto vector = PonyEngine::Math::Vector2<float>(4.f, -1.f);
			const PonyEngine::Math::Vector2<float> transformed = PonyEngine::Math::TransformDirection(trsMatrix, vector);
			Assert::AreEqual(-1.252, static_cast<double>(transformed.X()), 0.005);
			Assert::AreEqual(-8.452, static_cast<double>(transformed.Y()), 0.005);
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			constexpr auto rsMatrix = PonyEngine::Math::Matrix2x2<float>(-0.97f, -1.75f, -2.625f, 1.455f);
			constexpr PonyEngine::Math::Matrix3x3<float> trsMatrix = PonyEngine::Math::TrsMatrix(rsMatrix);
			constexpr auto translation = PonyEngine::Math::Vector2<float>(-3, 7);
			constexpr PonyEngine::Math::Matrix3x3<float> trsMatrixT = PonyEngine::Math::TrsMatrix(translation, rsMatrix);
			constexpr PonyEngine::Math::Vector2<float> translationE = PonyEngine::Math::ExtractTranslationFromTrsMatrix(trsMatrixT);
			constexpr PonyEngine::Math::Matrix2x2<float> rsMatrixE = PonyEngine::Math::ExtractRsMatrixFromTrsMatrix(trsMatrixT);
			constexpr PonyEngine::Math::Vector2<float> point = PonyEngine::Math::TransformPoint(trsMatrixT, translation);
			constexpr PonyEngine::Math::Vector2<float> direction = PonyEngine::Math::TransformDirection(trsMatrixT, translation);
		}
	};
}
