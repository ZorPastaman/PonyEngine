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
import <type_traits>;

import :Matrix2x2;
import :Matrix3x3;
import :Vector2;

export namespace PonyEngine::Math
{
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> Translation(const Matrix3x3<T>& matrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	T Rotation(const Matrix2x2<T>& matrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> Scaling(const Matrix2x2<T>& matrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> TranslationMatrix(const Vector2<T>& translation) noexcept;

	/// @brief s a rotation matrix for a @p Vector2.
	/// @param angle Rotation angle in radians.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> RotationMatrix(T angle) noexcept;

	/// @brief s a scaling matrix for a @p Vector2.
	/// @param scaling Component-wise scaling.
	/// @return Scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> ScalingMatrix(const Vector2<T>& scaling) noexcept;

	/// @brief s a rotation-scaling matrix for a @p Vector2.
	/// @param angle Rotation angle in radians.
	/// @param scaling Component-wise scaling.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> RsMatrix(T angle, const Vector2<T>& scaling) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> RsMatrix(const Matrix3x3<T>& matrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, T angle, const Vector2<T>& scaling) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> TrsMatrix(const Matrix2x2<T>& rs) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, const Matrix2x2<T>& rs) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> Rotate(const Vector2<T>& vector, T angle);

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> TransformPoint(const Matrix3x3<T>& matrix, const Vector2<T>& vector);
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> TransformDirection(const Matrix3x3<T>& matrix, const Vector2<T>& vector);
}

namespace PonyEngine::Math
{
	namespace
	{
		template<std::floating_point T> [[nodiscard("Pure function")]]
		Vector2<T> TransformVector(const Matrix3x3<T>& matrix, const Vector2<T>& vector, const T z)
		{
			const Vector3<T> transformed = matrix * Vector3<T>(vector.X(), vector.Y(), z);

			return Vector2<T>(transformed.X(), transformed.Y());
		}
	}

	template<std::floating_point T>
	Vector2<T> Translation(const Matrix3x3<T>& matrix) noexcept
	{
		return Vector2<T>(matrix.M02(), matrix.M12());
	}

	template<std::floating_point T>
	T Rotation(const Matrix2x2<T>& matrix) noexcept
	{
		const T cos = matrix.M00();
		const T sin = matrix.M10();

		return std::atan2(sin, cos);
	}

	template<std::floating_point T>
	Vector2<T> Scaling(const Matrix2x2<T>& matrix) noexcept
	{
		const T x = Vector2<T>(matrix.M00(), matrix.M10()).Magnitude();
		const T y = Vector2<T>(matrix.M01(), matrix.M11()).Magnitude();

		return Vector2<T>(x, y);
	}

	template<std::floating_point T>
	Matrix3x3<T> TranslationMatrix(const Vector2<T>& translation) noexcept
	{
		Matrix3x3<T> answer = Matrix3x3<T>::Identity;
		answer.M02() = translation.X();
		answer.M12() = translation.Y();

		return answer;
	}

	template<std::floating_point T>
	Matrix2x2<T> RotationMatrix(const T angle) noexcept
	{
		const T angleSin = std::sin(angle);
		const T angleCos = std::cos(angle);

		return Matrix2x2<T>(angleCos, angleSin, -angleSin, angleCos);
	}

	template<std::floating_point T>
	Matrix2x2<T> ScalingMatrix(const Vector2<T>& scaling) noexcept
	{
		Matrix2x2<T> answer = Matrix2x2<T>::Identity;
		answer.M00() = scaling.X();
		answer.M11() = scaling.Y();

		return answer;
	}

	template<std::floating_point T>
	Matrix2x2<T> RsMatrix(const T angle, const Vector2<T>& scaling) noexcept
	{
		Matrix2x2 answer = RotationMatrix(angle);
		answer.M00() *= scaling.X();
		answer.M10() *= scaling.X();
		answer.M01() *= scaling.Y();
		answer.M11() *= scaling.Y();

		return answer;
	}

	template<std::floating_point T>
	Matrix2x2<T> RsMatrix(const Matrix3x3<T>& matrix) noexcept
	{
		return Matrix2x2<T>(matrix.M00(), matrix.M10(), matrix.M01(), matrix.M11());
	}

	template<std::floating_point T>
	Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, const T angle, const Vector2<T>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(angle, scaling));
	}

	template<std::floating_point T>
	Matrix3x3<T> TrsMatrix(const Matrix2x2<T>& rs) noexcept
	{
		Matrix2x2<T> answer = Matrix2x2<T>::Identity;
		answer.M00() = rs.M00();
		answer.M10() = rs.M10();
		answer.M01() = rs.M01();
		answer.M11() = rs.M11();

		return answer;
	}

	template<std::floating_point T>
	Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, const Matrix2x2<T>& rs) noexcept
	{
		Matrix3x3 answer = TrsMatrix(rs);
		answer.M02() = translation.X();
		answer.M12() = translation.Y();

		return answer;
	}

	template<std::floating_point T>
	Vector2<T> Rotate(const Vector2<T>& vector, const T angle)
	{
		const T angleSin = std::sin(angle);
		const T angleCos = std::cos(angle);

		const T x = vector.X() * angleCos - vector.Y() * angleSin;
		const T y = vector.X() * angleSin + vector.Y() * angleCos;

		return Vector2<T>(x, y);
	}

	template<std::floating_point T>
	Vector2<T> TransformPoint(const Matrix3x3<T>& matrix, const Vector2<T>& vector)
	{
		return TransformVector(matrix, vector, T{1});
	}

	template<std::floating_point T>
	Vector2<T> TransformDirection(const Matrix3x3<T>& matrix, const Vector2<T>& vector)
	{
		return TransformVector(matrix, vector, T{0});
	}
}
