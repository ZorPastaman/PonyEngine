/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Transformations2D;

import <cmath>;
import <cstddef>;
import <type_traits>;

import :Matrix2x2;
import :Matrix3x3;
import :Vector2;
import :Vector3;

export namespace PonyEngine::Math
{
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T Rotation(const Matrix2x2<T>& rotationMatrix) noexcept;

	/// @brief s a rotation matrix for a @p Vector2.
	/// @param angle Rotation angle in radians.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> RotationMatrix(T angle) noexcept;

	/// @brief s a rotation-scaling matrix for a @p Vector2.
	/// @param angle Rotation angle in radians.
	/// @param scaling Component-wise scaling.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> RsMatrix(T angle, const Vector2<T>& scaling) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> RsMatrix(const Matrix2x2<T>& rotationMatrix, const Vector2<T>& scaling) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, T angle, const Vector2<T>& scaling) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> TrsMatrix(const Matrix2x2<T>& rsMatrix) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, const Matrix2x2<T>& rsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> ExtractTranslationFromTrsMatrix(const Matrix3x3<T>& trsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	T ExtractRotationFromRsMatrix(const Matrix2x2<T>& rsMatrix) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T ExtractRotationFromTrsMatrix(const Matrix3x3<T>& trsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> ExtractRotationMatrixFromRsMatrix(const Matrix2x2<T>& rsMatrix) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> ExtractRotationMatrixFromTrsMatrix(const Matrix3x3<T>& trsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> ExtractScalingFromRsMatrix(const Matrix2x2<T>& rsMatrix) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> ExtractScalingFromTrsMatrix(const Matrix3x3<T>& trsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> ExtractRsMatrixFromTrsMatrix(const Matrix3x3<T>& trsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> Rotate(const Vector2<T>& vector, T angle);

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> TransformPoint(const Matrix3x3<T>& transformationMatrix, const Vector2<T>& vector);
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> TransformDirection(const Matrix3x3<T>& transformationMatrix, const Vector2<T>& vector);
}

namespace PonyEngine::Math
{
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> TransformVector(const Matrix3x3<T>& transformationMatrix, const Vector2<T>& vector, T z);

	template<std::floating_point T>
	T Rotation(const Matrix2x2<T>& rotationMatrix) noexcept
	{
		return std::atan2(rotationMatrix.M10(), rotationMatrix.M00());
	}

	template<std::floating_point T>
	Matrix2x2<T> RotationMatrix(const T angle) noexcept
	{
		const T angleSin = std::sin(angle);
		const T angleCos = std::cos(angle);

		return Matrix2x2<T>(angleCos, angleSin, -angleSin, angleCos);
	}

	template<std::floating_point T>
	Matrix2x2<T> RsMatrix(const T angle, const Vector2<T>& scaling) noexcept
	{
		return RsMatrix(RotationMatrix(angle), scaling);
	}

	template<std::floating_point T>
	Matrix2x2<T> RsMatrix(const Matrix2x2<T>& rotationMatrix, const Vector2<T>& scaling) noexcept
	{
		Matrix2x2<T> rsMatrix;
		for (std::size_t i = 0; i < Matrix2x2<T>::Dimension; ++i)
		{
			rsMatrix.SetColumn(i, rotationMatrix.GetColumn(i) * scaling[i]);
		}

		return rsMatrix;
	}

	template<std::floating_point T>
	Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, const T angle, const Vector2<T>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(angle, scaling));
	}

	template<std::floating_point T>
	Matrix3x3<T> TrsMatrix(const Matrix2x2<T>& rsMatrix) noexcept
	{
		Matrix3x3<T> trsMatrix = Matrix3x3Identity<T>;
		trsMatrix.M00() = rsMatrix.M00();
		trsMatrix.M10() = rsMatrix.M10();
		trsMatrix.M01() = rsMatrix.M01();
		trsMatrix.M11() = rsMatrix.M11();

		return trsMatrix;
	}

	template<std::floating_point T>
	Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, const Matrix2x2<T>& rsMatrix) noexcept
	{
		Matrix3x3 trsMatrix = TrsMatrix(rsMatrix);
		trsMatrix.M02() = translation.X();
		trsMatrix.M12() = translation.Y();

		return trsMatrix;
	}

	template<std::floating_point T>
	Vector2<T> ExtractTranslationFromTrsMatrix(const Matrix3x3<T>& trsMatrix) noexcept
	{
		return Vector2<T>(trsMatrix.M02(), trsMatrix.M12());
	}

	template<std::floating_point T>
	T ExtractRotationFromRsMatrix(const Matrix2x2<T>& rsMatrix) noexcept
	{
		return Rotation(ExtractRotationMatrixFromRsMatrix(rsMatrix));
	}

	template<std::floating_point T>
	T ExtractRotationFromTrsMatrix(const Matrix3x3<T>& trsMatrix) noexcept
	{
		return ExtractRotationFromRsMatrix(ExtractRsMatrixFromTrsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	Matrix2x2<T> ExtractRotationMatrixFromRsMatrix(const Matrix2x2<T>& rsMatrix) noexcept
	{
		const Vector2<T> scaling = ExtractScalingFromRsMatrix(rsMatrix);
		Matrix2x2<T> scalingMatrix = Matrix2x2Identity<T>;
		scalingMatrix.SetDiagonal(scaling);

		return rsMatrix * scalingMatrix.Inverse();
	}

	template<std::floating_point T>
	Matrix2x2<T> ExtractRotationMatrixFromTrsMatrix(const Matrix3x3<T>& trsMatrix) noexcept
	{
		return ExtractRotationMatrixFromRsMatrix(ExtractRsMatrixFromTrsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	Vector2<T> ExtractScalingFromRsMatrix(const Matrix2x2<T>& rsMatrix) noexcept
	{
		Vector2<T> scaling;
		for (std::size_t i = 0; i < Matrix2x2<T>::Dimension; ++i)
		{
			scaling[i] = rsMatrix.GetColumn(i).Magnitude();
		}

		return scaling;
	}

	template<std::floating_point T>
	Vector2<T> ExtractScalingFromTrsMatrix(const Matrix3x3<T>& trsMatrix) noexcept
	{
		return ExtractScalingMatrixFromRsMatrix(ExtractRsMatrixFromTrsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	Matrix2x2<T> ExtractRsMatrixFromTrsMatrix(const Matrix3x3<T>& trsMatrix) noexcept
	{
		return Matrix2x2<T>(trsMatrix.M00(), trsMatrix.M10(), trsMatrix.M01(), trsMatrix.M11());
	}

	template<std::floating_point T>
	Vector2<T> Rotate(const Vector2<T>& vector, const T angle)
	{
		return RotationMatrix(angle) * vector;
	}

	template<std::floating_point T>
	Vector2<T> TransformPoint(const Matrix3x3<T>& transformationMatrix, const Vector2<T>& vector)
	{
		return TransformVector(transformationMatrix, vector, T{1});
	}

	template<std::floating_point T>
	Vector2<T> TransformDirection(const Matrix3x3<T>& transformationMatrix, const Vector2<T>& vector)
	{
		return TransformVector(transformationMatrix, vector, T{0});
	}

	template<std::floating_point T>
	Vector2<T> TransformVector(const Matrix3x3<T>& transformationMatrix, const Vector2<T>& vector, const T z)
	{
		const Vector3<T> transformed = transformationMatrix * Vector3<T>(vector.X(), vector.Y(), z);

		return Vector2<T>(transformed.X(), transformed.Y());
	}
}
