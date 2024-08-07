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
	/// @brief Converts the 2D rotation matrix to a rotation angle.
	/// @tparam T Value type.
	/// @param rotationMatrix Rotation matrix. 
	/// @return Rotation angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T Angle(const Matrix2x2<T>& rotationMatrix) noexcept;

	/// @brief Converts the rotation angle to a 2D rotation matrix.
	/// @param angle Rotation angle in radians.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> RotationMatrix(T angle) noexcept;

	/// @brief Creates a 2D rotation-scaling matrix from the angle and scaling.
	/// @param angle Rotation angle in radians.
	/// @param scaling Component-wise scaling.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> RsMatrix(T angle, const Vector2<T>& scaling) noexcept;
	/// @brief Creates a 2D rotation-scaling matrix from the 2D rotation matrix and scaling.
	/// @tparam T Value type.
	/// @param rotationMatrix Rotation matrix. 
	/// @param scaling Scaling.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix2x2<T> RsMatrix(const Matrix2x2<T>& rotationMatrix, const Vector2<T>& scaling) noexcept;

	/// @brief Creates a 2D translation-rotation-scaling matrix from the 2D translation, rotation angle and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param angle Rotation angle in radians.
	/// @param scaling Scaling.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, T angle, const Vector2<T>& scaling) noexcept;
	/// @brief Creates a 2D translation-rotation scaling matrix from a 2D rotation scaling matrix. The translation part will be zero.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix3x3<T> TrsMatrix(const Matrix2x2<T>& rsMatrix) noexcept;
	/// @brief Creates a 2D translation-rotation-scaling matrix from the 2D translation and rotation-scaling matrix.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, const Matrix2x2<T>& rsMatrix) noexcept;

	/// @brief Extracts a 2D translation from the 2D translation-rotation-scaling matrix.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Translation.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> ExtractTranslation(const Matrix3x3<T>& trsMatrix) noexcept;

	/// @brief Attempts to extract a rotation angle from the 2D rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Rotation angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T ExtractAngle(const Matrix2x2<T>& rsMatrix) noexcept;
	/// @brief Attempts to extract a rotation angle from the 2D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Rotation angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T ExtractAngle(const Matrix3x3<T>& trsMatrix) noexcept;

	/// @brief Attempts to extract a 2D rotation matrix from the 2D rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @note If the matrix has a zero column, the result is undefined.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> ExtractRotationMatrix2D(const Matrix2x2<T>& rsMatrix) noexcept;
	/// @brief Attempts to extract a 2D rotation matrix from the 2D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @note If the rotation-scaling part of the matrix has a zero column, the result is undefined.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> ExtractRotationMatrix2D(const Matrix3x3<T>& trsMatrix) noexcept;

	/// @brief Attempts to extract a 2D scaling from the 2D rotation-scaling matrix.
	/// @note It works correctly if the scaling is non-negative.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Scaling.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> ExtractScaling2D(const Matrix2x2<T>& rsMatrix) noexcept;
	/// @brief Attempts to extract a 2D scaling from the 2D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is non-negative.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Scaling.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> ExtractScaling2D(const Matrix3x3<T>& trsMatrix) noexcept;

	/// @brief Extracts a 2D rotation-scaling matrix from the 2D translation-rotation-scaling matrix.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix2x2<T> ExtractRsMatrix(const Matrix3x3<T>& trsMatrix) noexcept;

	/// @brief Rotates the @p vector by the @p angle.
	/// @tparam T Value type.
	/// @param vector Vector to rotate.
	/// @param angle Rotation angle in radians.
	/// @return Rotated vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> Rotate(const Vector2<T>& vector, T angle) noexcept;

	/// @brief Applies the 2D transformation matrix to the point vector.
	/// @tparam T Value type.
	/// @param transformationMatrix Transformation matrix. 
	/// @param vector Point.
	/// @return Transformed point.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> TransformPoint(const Matrix3x3<T>& transformationMatrix, const Vector2<T>& vector) noexcept;
	/// @brief Applies the 2D transformation matrix to the direction vector.
	/// @tparam T Value type.
	/// @param transformationMatrix Transformation matrix. 
	/// @param vector Direction.
	/// @return Transformed direction.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> TransformDirection(const Matrix3x3<T>& transformationMatrix, const Vector2<T>& vector) noexcept;
}

namespace PonyEngine::Math
{
	/// @brief Applies the 2D transformation matrix to the vector.
	/// @tparam T Value type.
	/// @param transformationMatrix Transformation matrix. 
	/// @param vector Vector.
	/// @param z Z component. It determines how to treat the @p vector.
	/// @return Transformed vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> TransformVector(const Matrix3x3<T>& transformationMatrix, const Vector2<T>& vector, T z) noexcept;

	template<std::floating_point T>
	T Angle(const Matrix2x2<T>& rotationMatrix) noexcept
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
	constexpr Matrix2x2<T> RsMatrix(const Matrix2x2<T>& rotationMatrix, const Vector2<T>& scaling) noexcept
	{
		Matrix2x2<T> rsMatrix;
		for (std::size_t i = 0; i < Matrix2x2<T>::Dimension; ++i)
		{
			rsMatrix.Column(i, rotationMatrix.Column(i) * scaling[i]);
		}

		return rsMatrix;
	}

	template<std::floating_point T>
	Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, const T angle, const Vector2<T>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(angle, scaling));
	}

	template<std::floating_point T>
	constexpr Matrix3x3<T> TrsMatrix(const Matrix2x2<T>& rsMatrix) noexcept
	{
		Matrix3x3<T> trsMatrix = Matrix3x3<T>::Predefined::Identity;
		trsMatrix.M00() = rsMatrix.M00();
		trsMatrix.M10() = rsMatrix.M10();
		trsMatrix.M01() = rsMatrix.M01();
		trsMatrix.M11() = rsMatrix.M11();

		return trsMatrix;
	}

	template<std::floating_point T>
	constexpr Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, const Matrix2x2<T>& rsMatrix) noexcept
	{
		Matrix3x3 trsMatrix = TrsMatrix(rsMatrix);
		trsMatrix.M02() = translation.X();
		trsMatrix.M12() = translation.Y();

		return trsMatrix;
	}

	template<std::floating_point T>
	constexpr Vector2<T> ExtractTranslation(const Matrix3x3<T>& trsMatrix) noexcept
	{
		return Vector2<T>(trsMatrix.M02(), trsMatrix.M12());
	}

	template<std::floating_point T>
	T ExtractAngle(const Matrix2x2<T>& rsMatrix) noexcept
	{
		return Angle(rsMatrix);
	}

	template<std::floating_point T>
	T ExtractAngle(const Matrix3x3<T>& trsMatrix) noexcept
	{
		return ExtractAngle(ExtractRsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	Matrix2x2<T> ExtractRotationMatrix2D(const Matrix2x2<T>& rsMatrix) noexcept
	{
		const Vector2<T> scaling = ExtractScaling2D(rsMatrix);

		Matrix2x2<T> rotationMatrix;
		for (std::size_t i = 0; i < Matrix2x2<T>::Dimension; ++i)
		{
			const T inverseScaling = T{1} / scaling[i];
			rotationMatrix.Column(i, rsMatrix.Column(i) * inverseScaling);
		}

		return rotationMatrix;
	}

	template<std::floating_point T>
	Matrix2x2<T> ExtractRotationMatrix2D(const Matrix3x3<T>& trsMatrix) noexcept
	{
		return ExtractRotationMatrix2D(ExtractRsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	Vector2<T> ExtractScaling2D(const Matrix2x2<T>& rsMatrix) noexcept
	{
		Vector2<T> scaling;
		for (std::size_t i = 0; i < Matrix2x2<T>::Dimension; ++i)
		{
			scaling[i] = rsMatrix.Column(i).Magnitude();
		}

		return scaling;
	}

	template<std::floating_point T>
	Vector2<T> ExtractScaling2D(const Matrix3x3<T>& trsMatrix) noexcept
	{
		return ExtractScaling2D(ExtractRsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	constexpr Matrix2x2<T> ExtractRsMatrix(const Matrix3x3<T>& trsMatrix) noexcept
	{
		return Matrix2x2<T>(trsMatrix.M00(), trsMatrix.M10(), trsMatrix.M01(), trsMatrix.M11());
	}

	template<std::floating_point T>
	Vector2<T> Rotate(const Vector2<T>& vector, const T angle) noexcept
	{
		return RotationMatrix(angle) * vector;
	}

	template<std::floating_point T>
	constexpr Vector2<T> TransformPoint(const Matrix3x3<T>& transformationMatrix, const Vector2<T>& vector) noexcept
	{
		return TransformVector(transformationMatrix, vector, T{1});
	}

	template<std::floating_point T>
	constexpr Vector2<T> TransformDirection(const Matrix3x3<T>& transformationMatrix, const Vector2<T>& vector) noexcept
	{
		return TransformVector(transformationMatrix, vector, T{0});
	}

	template<std::floating_point T>
	constexpr Vector2<T> TransformVector(const Matrix3x3<T>& transformationMatrix, const Vector2<T>& vector, const T z) noexcept
	{
		const Vector3<T> transformed = transformationMatrix * Vector3<T>(vector.X(), vector.Y(), z);

		return Vector2<T>(transformed.X(), transformed.Y());
	}
}
