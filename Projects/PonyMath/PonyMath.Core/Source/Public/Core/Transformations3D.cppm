/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Core:Transformations3D;

import <cmath>;
import <cstddef>;
import <type_traits>;
import <utility>;

import :Matrix3x3;
import :Matrix4x4;
import :Quaternion;
import :Vector3;
import :Vector4;

export namespace PonyMath::Core
{
	/// @brief Converts the 3D rotation matrix to a 3D rotation quaternion.
	/// @tparam T Value type.
	/// @param rotationMatrix Rotation matrix. 
	/// @return Rotation quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> RotationQuaternion(const Matrix3x3<T>& rotationMatrix) noexcept;
	/// @brief Converts the 3D Euler angles to a 3D rotation quaternion.
	/// @tparam T Value type.
	/// @param euler Rotation angles around x, y and z axes in radians.
	/// @return Rotation quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> RotationQuaternion(const Vector3<T>& euler) noexcept;
	/// @brief Converts the 3D axis-angle rotation to a 3D rotation quaternion.
	/// @tparam T Value type.
	/// @param axis Rotation axis. Must be unit.
	/// @param angle Rotation angle in radians.
	/// @return Rotation quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> RotationQuaternion(const Vector3<T>& axis, T angle) noexcept;

	/// @brief Creates a 3D rotation quaternion representing a rotation from the @p fromDirection to the @p toDirection.
	/// @tparam T Value type.
	/// @param fromDirection From direction. Must be unit.
	/// @param toDirection To direction. Must be unit.
	/// @return Rotation quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> FromToRotationQuaternion(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept;
	/// @brief Creates a 3D rotation quaternion representing a rotation so that the @p forward be a look direction and the @p up be an upward vector.
	/// @note If forward and up are collinear, the result up vector is unpredictable.
	/// @tparam T Value type.
	/// @param forward Forward vector. Must be unit.
	/// @param up Upward vector. Must be unit.
	/// @return Rotation quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> LookInRotationQuaternion(const Vector3<T>& forward, const Vector3<T>& up) noexcept;

	/// @brief Converts the 3D rotation quaternion to a 3D rotation matrix.
	/// @tparam T Value type.
	/// @param quaternion Rotation quaternion.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix3x3<T> RotationMatrix(const Quaternion<T>& quaternion) noexcept;
	/// @brief Converts the 3D Euler angles to a 3D rotation matrix.
	/// @tparam T Value type.
	/// @param euler Rotation angles around x, y and z axes in radians.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RotationMatrix(const Vector3<T>& euler) noexcept;
	/// @brief Converts the 3D axis-angle rotation a 3D rotation matrix.
	/// @tparam T Value type.
	/// @param axis Rotation axis. Must be unit.
	/// @param angle Rotation angle in radians.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RotationMatrix(const Vector3<T>& axis, T angle) noexcept;

	/// @brief Creates a 3D rotation matrix representing a rotation from the @p fromDirection to the @p toDirection.
	/// @tparam T Value type.
	/// @param fromDirection From direction. Must be unit.
	/// @param toDirection To direction. Must be unit.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> FromToRotationMatrix(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept;
	/// @brief Creates a 3D rotation matrix representing a rotation so that the @p forward be a look direction and the @p up be an upward vector.
	/// @note If forward and up are collinear, the result up vector is unpredictable.
	/// @tparam T Value type.
	/// @param forward Forward vector. Must be unit.
	/// @param up Upward vector. Must be unit.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> LookInRotationMatrix(const Vector3<T>& forward, const Vector3<T>& up) noexcept;

	/// @brief Converts the 3D rotation quaternion to a 3D Euler angles.
	/// @tparam T Value type.
	/// @param quaternion Rotation quaternion.
	/// @return Euler angles in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Euler(const Quaternion<T>& quaternion) noexcept;
	/// @brief Converts the 3D rotation matrix to a 3D Euler angles.
	/// @tparam T Value type.
	/// @param rotationMatrix Rotation matrix.
	/// @return Euler angles in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Euler(const Matrix3x3<T>& rotationMatrix) noexcept;
	/// @brief Converts the 3D axis-angle rotation to a 3D Euler angles.
	/// @tparam T Value type.
	/// @param axis Rotation axis. Must be unit.
	/// @param angle Rotation angle in radians.
	/// @return Euler angles in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Euler(const Vector3<T>& axis, T angle) noexcept;

	/// @brief Creates 3D Euler angles representing a rotation from the @p fromDirection to the @p toDirection.
	/// @tparam T Value type.
	/// @param fromDirection From direction. Must be unit.
	/// @param toDirection To direction. Must be unit.
	/// @return Euler angles in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> FromToEuler(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept;
	/// @brief Creates a 3D Euler angles representing a rotation so that the @p forward be a look direction and the @p up be an upward vector.
	/// @note If forward and up are collinear, the result up vector is unpredictable.
	/// @tparam T Value type.
	/// @param forward Forward vector. Must be unit.
	/// @param up Upward vector. Must be unit.
	/// @return Euler angles in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> LookInEuler(const Vector3<T>& forward, const Vector3<T>& up) noexcept;

	/// @brief Converts the 3D rotation quaternion to a 3D axis-angle rotation.
	/// @tparam T Value type.
	/// @param quaternion Rotation quaternion.
	/// @return Axis-angle rotation. The angle is in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> AxisAngle(const Quaternion<T>& quaternion) noexcept;
	/// @brief Converts the 3D rotation matrix to a 3D axis-angle rotation.
	/// @tparam T Value type.
	/// @param rotationMatrix Rotation matrix.
	/// @return Axis-angle rotation. The angle is in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> AxisAngle(const Matrix3x3<T>& rotationMatrix) noexcept;
	/// @brief Converts the 3D Euler angles to a 3D axis-angle rotation.
	/// @tparam T Value type.
	/// @param euler Euler angles in radians.
	/// @return Axis-angle rotation. The angle is in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> AxisAngle(const Vector3<T>& euler) noexcept;

	/// @brief Creates a 3D axis-angle rotation representing a rotation from the @p fromDirection to the @p toDirection.
	/// @tparam T Value type.
	/// @param fromDirection From direction. Must be unit.
	/// @param toDirection To direction. Must be unit.
	/// @return Axis-angle rotation. The angle is in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> FromToAxisAngle(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept;
	/// @brief Creates a 3D axis-angle rotation representing a rotation so that the @p forward be a look direction and the @p up be an upward vector.
	/// @note If forward and up are collinear, the result up vector is unpredictable.
	/// @tparam T Value type.
	/// @param forward Forward vector. Must be unit.
	/// @param up Upward vector. Must be unit.
	/// @return Axis-angle rotation. The angle is in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> LookInAxisAngle(const Vector3<T>& forward, const Vector3<T>& up) noexcept;

	/// @brief Creates a 3D rotation-scaling matrix from the rotation quaternion and scaling.
	/// @tparam T Value type.
	/// @param quaternion Rotation quaternion.
	/// @param scaling Scaling.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix3x3<T> RsMatrix(const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a 3D rotation-scaling matrix from the rotation matrix and scaling.
	/// @tparam T Value type.
	/// @param rotationMatrix Rotation matrix.
	/// @param scaling Scaling.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix3x3<T> RsMatrix(const Matrix3x3<T>& rotationMatrix, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a 3D rotation-scaling matrix from the Euler angles and scaling.
	/// @tparam T Value type.
	/// @param euler Euler angles in radians.
	/// @param scaling Scaling.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RsMatrix(const Vector3<T>& euler, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a 3D rotation-scaling matrix from the axis-angle rotation and scaling.
	/// @tparam T Value type.
	/// @param axis Rotation axis.
	/// @param angle Rotation angle in radians.
	/// @param scaling Scaling.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RsMatrix(const Vector3<T>& axis, T angle, const Vector3<T>& scaling) noexcept;

	/// @brief Creates a 3D translation-rotation-scaling matrix from the translation, rotation quaternion and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param quaternion Rotation quaternion.
	/// @param scaling Scaling.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a 3D translation-rotation-scaling matrix from the translation, rotation matrix and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param rotationMatrix Rotation matrix.
	/// @param scaling Scaling.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Matrix3x3<T>& rotationMatrix, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a 3D translation-rotation-scaling matrix from the translation, Euler angles and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param euler Euler angles in radians.
	/// @param scaling Scaling.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Vector3<T>& euler, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a 3D translation-rotation-scaling matrix from the translation, axis-angle rotation and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param axis Axis. Must be unit.
	/// @param angle Rotation angle in radians.
	/// @param scaling Scaling.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Vector3<T>& axis, T angle, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a 3D translation-rotation-scaling matrix with the zero translation from the rotation-scaling matrix.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix4x4<T> TrsMatrix(const Matrix3x3<T>& rsMatrix) noexcept;
	/// @brief Creates a 3D translation-rotation-scaling matrix from the translation and rotation-scaling matrix.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Matrix3x3<T>& rsMatrix) noexcept;

	/// @brief Creates a 3D perspective projection matrix.
	/// @tparam T Value type.
	/// @param fov Vertical field of view in radians.
	/// @param aspect Aspect ratio (width / height).
	/// @param nearPlane Distance between a camera and a near clipping plane.
	/// @param farPlane Distance between a camera and a far clipping plane.
	/// @return Perspective projection matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix4x4<T> PerspectiveMatrix(T fov, T aspect, T nearPlane, T farPlane) noexcept;

	/// @brief Extracts a translation from the 3D translation-rotation-scaling matrix.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Translation.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> ExtractTranslation(const Matrix4x4<T>& trsMatrix) noexcept;

	/// @brief Attempts to extract a rotation quaternion from the 3D rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Rotation quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> ExtractRotationQuaternion(const Matrix3x3<T>& rsMatrix) noexcept;
	/// @brief Attempts to extract a rotation quaternion from the 3D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Rotation quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> ExtractRotationQuaternion(const Matrix4x4<T>& trsMatrix) noexcept;

	/// @brief Attempts to extract a rotation matrix from the 3D rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> ExtractRotationMatrix3D(const Matrix3x3<T>& rsMatrix) noexcept;
	/// @brief Attempts to extract a rotation matrix from the 3D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> ExtractRotationMatrix3D(const Matrix4x4<T>& trsMatrix) noexcept;

	/// @brief Attempts to extract Euler angles from the 3D rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Euler angles in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> ExtractEuler(const Matrix3x3<T>& rsMatrix) noexcept;
	/// @brief Attempts to extract Euler angles from the 3D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Euler angles in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> ExtractEuler(const Matrix4x4<T>& trsMatrix) noexcept;

	/// @brief Attempts to extract an axis-angle rotation from the 3D rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Axis-angle rotation. The angle is in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> ExtractAxisAngle(const Matrix3x3<T>& rsMatrix) noexcept;
	/// @brief Attempts to extract an axis-angle rotation from the 3D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Axis-angle rotation. The angle is in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> ExtractAxisAngle(const Matrix4x4<T>& trsMatrix) noexcept;

	/// @brief Attempts to extract a 3D scaling from the 3D rotation-scaling matrix.
	/// @note It works correctly if the scaling is non-negative.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Scaling.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> ExtractScaling3D(const Matrix3x3<T>& rsMatrix) noexcept;
	/// @brief Attempts to extract a 3D scaling from the 3D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is non-negative.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Scaling.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> ExtractScaling3D(const Matrix4x4<T>& trsMatrix) noexcept;

	/// @brief Extracts a 3D rotation-scaling matrix from the 3D translation-rotation-scaling matrix.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix3x3<T> ExtractRsMatrix(const Matrix4x4<T>& trsMatrix) noexcept;

	/// @brief Rotates the @p vector with the @p euler.
	/// @tparam T Value type.
	/// @param vector Vector to rotate.
	/// @param euler Euler angles in radians.
	/// @return Rotated vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Rotate(const Vector3<T>& vector, const Vector3<T>& euler) noexcept;
	/// @brief Rotates the @p vector with the @p axis and @p angle.
	/// @tparam T Value type.
	/// @param vector Vector to rotate.
	/// @param axis Rotation axis.
	/// @param angle Rotation angle in radians.
	/// @return Rotated vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Rotate(const Vector3<T>& vector, const Vector3<T>& axis, T angle) noexcept;

	/// @brief Applies the 3D transformation matrix to the point vector.
	/// @tparam T Value type.
	/// @param transformationMatrix Transformation matrix.
	/// @param vector Point.
	/// @return Transformed point.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> TransformPoint(const Matrix4x4<T>& transformationMatrix, const Vector3<T>& vector) noexcept;
	/// @brief Applies the 3D transformation matrix to the direction vector.
	/// @tparam T Value type.
	/// @param transformationMatrix Transformation matrix.
	/// @param vector Direction.
	/// @return Transformed direction.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> TransformDirection(const Matrix4x4<T>& transformationMatrix, const Vector3<T>& vector) noexcept;
}

namespace PonyMath::Core
{
	/// @brief Creates a 3D rotation matrix representing a rotation so that the @p forward be a look direction and the @p up be an upward vector.
	/// @note Forward and up mustn't be collinear.
	/// @tparam T Value type.
	/// @param forward Forward vector. Must be unit.
	/// @param up Upward vector. Must be unit.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> LookIn(const Vector3<T>& forward, const Vector3<T>& up) noexcept;

	/// @brief Applies the 3D transformation matrix to the vector.
	/// @tparam T Value type.
	/// @param transformationMatrix Transformation matrix.
	/// @param vector Vector.
	/// @param w W component. It determines how to treat the @p vector.
	/// @return Transformed vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> TransformVector(const Matrix4x4<T>& transformationMatrix, const Vector3<T>& vector, T w) noexcept;

	template<std::floating_point T>
	Quaternion<T> RotationQuaternion(const Matrix3x3<T>& rotationMatrix) noexcept
	{
		Quaternion<T> quaternion;

		if (const T trace = rotationMatrix.Trace(); trace > T{0})
		{
			const T s = std::sqrt(T{1} + trace) * T{2};
			const T inverseS = T{1} / s;

			quaternion.X() = (rotationMatrix.M21() - rotationMatrix.M12()) * inverseS;
			quaternion.Y() = (rotationMatrix.M02() - rotationMatrix.M20()) * inverseS;
			quaternion.Z() = (rotationMatrix.M10() - rotationMatrix.M01()) * inverseS;
			quaternion.W() = s * T{0.25};
		}
		else if (rotationMatrix.M00() > rotationMatrix.M11() && rotationMatrix.M00() > rotationMatrix.M22())
		{
			const T s = std::sqrt(T{1} + rotationMatrix.M00() - rotationMatrix.M11() - rotationMatrix.M22()) * T{2};
			const T inverseS = T{1} / s;

			quaternion.X() = s * T{0.25};
			quaternion.Y() = (rotationMatrix.M01() + rotationMatrix.M10()) * inverseS;
			quaternion.Z() = (rotationMatrix.M02() + rotationMatrix.M20()) * inverseS;
			quaternion.W() = (rotationMatrix.M21() - rotationMatrix.M12()) * inverseS;
		}
		else if (rotationMatrix.M11() > rotationMatrix.M22())
		{
			const T s = std::sqrt(T{1} + rotationMatrix.M11() - rotationMatrix.M00() - rotationMatrix.M22()) * T{2};
			const T inverseS = T{1} / s;

			quaternion.X() = (rotationMatrix.M01() + rotationMatrix.M10()) * inverseS;
			quaternion.Y() = s * T{0.25};
			quaternion.Z() = (rotationMatrix.M12() + rotationMatrix.M21()) * inverseS;
			quaternion.W() = (rotationMatrix.M02() - rotationMatrix.M20()) * inverseS;
		}
		else
		{
			const T s = std::sqrt(T{1} + rotationMatrix.M22() - rotationMatrix.M00() - rotationMatrix.M11()) * T{2};
			const T inverseS = T{1} / s;

			quaternion.X() = (rotationMatrix.M02() + rotationMatrix.M20()) * inverseS;
			quaternion.Y() = (rotationMatrix.M12() + rotationMatrix.M21()) * inverseS;
			quaternion.Z() = s * T{0.25};
			quaternion.W() = (rotationMatrix.M10() - rotationMatrix.M01()) * inverseS;
		}

		return quaternion;
	}

	template<std::floating_point T>
	Quaternion<T> RotationQuaternion(const Vector3<T>& euler) noexcept
	{
		const T xHalf = euler.X() * T{0.5};
		const T yHalf = euler.Y() * T{0.5};
		const T zHalf = euler.Z() * T{0.5};

		const T xSin = std::sin(xHalf);
		const T ySin = std::sin(yHalf);
		const T zSin = std::sin(zHalf);

		const T xCos = std::cos(xHalf);
		const T yCos = std::cos(yHalf);
		const T zCos = std::cos(zHalf);

		const T xSyS = xSin * ySin;
		const T xSyC = xSin * yCos;
		const T xCyS = xCos * ySin;
		const T xCyC = xCos * yCos;

		Quaternion<T> quaternion;
		quaternion.X() = xSyC * zCos + xCyS * zSin;
		quaternion.Y() = xCyS * zCos - xSyC * zSin;
		quaternion.Z() = xCyC * zSin - xSyS * zCos;
		quaternion.W() = xCyC * zCos + xSyS * zSin;

		return quaternion;
	}

	template<std::floating_point T>
	Quaternion<T> RotationQuaternion(const Vector3<T>& axis, const T angle) noexcept
	{
		const T halfAngle = angle * T{0.5};

		const T sin = std::sin(halfAngle);
		const T cos = std::cos(halfAngle);

		Quaternion<T> quaternion;
		quaternion.X() = axis.X() * sin;
		quaternion.Y() = axis.Y() * sin;
		quaternion.Z() = axis.Z() * sin;
		quaternion.W() = cos;

		return quaternion;
	}

	template<std::floating_point T>
	Quaternion<T> FromToRotationQuaternion(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept
	{
		const std::pair<Vector3<T>, T> axisAngle = FromToAxisAngle(fromDirection, toDirection);

		return RotationQuaternion(axisAngle.first, axisAngle.second);
	}

	template<std::floating_point T>
	Quaternion<T> LookInRotationQuaternion(const Vector3<T>& forward, const Vector3<T>& up) noexcept
	{
		if (std::abs(Dot(forward, up)) > T{0.9999}) [[unlikely]]
		{
			return FromToRotationQuaternion(Vector3<T>::Predefined::Forward, forward);
		}

		return RotationQuaternion(LookIn(forward, up));
	}

	template<std::floating_point T>
	constexpr Matrix3x3<T> RotationMatrix(const Quaternion<T>& quaternion) noexcept
	{
		const T xx = quaternion.X() * quaternion.X();
		const T xy = quaternion.X() * quaternion.Y();
		const T xz = quaternion.X() * quaternion.Z();
		const T xw = quaternion.X() * quaternion.W();

		const T yy = quaternion.Y() * quaternion.Y();
		const T yz = quaternion.Y() * quaternion.Z();
		const T yw = quaternion.Y() * quaternion.W();

		const T zz = quaternion.Z() * quaternion.Z();
		const T zw = quaternion.Z() * quaternion.W();

		Matrix3x3<T> rotationMatrix;
		rotationMatrix.M00() = T{1} - T{2} * (yy + zz);
		rotationMatrix.M10() = T{2} * (xy + zw);
		rotationMatrix.M20() = T{2} * (xz - yw);
		rotationMatrix.M01() = T{2} * (xy - zw);
		rotationMatrix.M11() = T{1} - T{2} * (xx + zz);
		rotationMatrix.M21() = T{2} * (yz + xw);
		rotationMatrix.M02() = T{2} * (xz + yw);
		rotationMatrix.M12() = T{2} * (yz - xw);
		rotationMatrix.M22() = T{1} - T{2} * (xx + yy);

		return rotationMatrix;
	}

	template<std::floating_point T>
	Matrix3x3<T> RotationMatrix(const Vector3<T>& euler) noexcept
	{
		const T xSin = std::sin(euler.X());
		const T ySin = std::sin(euler.Y());
		const T zSin = std::sin(euler.Z());

		const T xCos = std::cos(euler.X());
		const T yCos = std::cos(euler.Y());
		const T zCos = std::cos(euler.Z());

		Matrix3x3<T> rotationMatrix;
		rotationMatrix.M00() = xSin * ySin * zSin + yCos * zCos;
		rotationMatrix.M10() = xCos * zSin;
		rotationMatrix.M20() = xSin * yCos * zSin - ySin * zCos;
		rotationMatrix.M01() = xSin * ySin * zCos - yCos * zSin;
		rotationMatrix.M11() = xCos * zCos;
		rotationMatrix.M21() = xSin * yCos * zCos + ySin * zSin;
		rotationMatrix.M02() = xCos * ySin;
		rotationMatrix.M12() = -xSin;
		rotationMatrix.M22() = xCos * yCos;

		return rotationMatrix;
	}

	template<std::floating_point T>
	Matrix3x3<T> RotationMatrix(const Vector3<T>& axis, const T angle) noexcept
	{
		const T sin = std::sin(angle);
		const T cos = std::cos(angle);
		const T mCos = T{1} - cos;

		const T mx = mCos * axis.X();
		const T my = mCos * axis.Y();
		const T mz = mCos * axis.Z();

		const T mxx = mx * axis.X();
		const T mxy = mx * axis.Y();
		const T mxz = mx * axis.Z();
		const T myy = my * axis.Y();
		const T myz = my * axis.Z();
		const T mzz = mz * axis.Z();

		const T sx = sin * axis.X();
		const T sy = sin * axis.Y();
		const T sz = sin * axis.Z();

		Matrix3x3<T> rotationMatrix;
		rotationMatrix.M00() = mxx + cos;
		rotationMatrix.M10() = mxy + sz;
		rotationMatrix.M20() = mxz - sy;
		rotationMatrix.M01() = mxy - sz;
		rotationMatrix.M11() = myy + cos;
		rotationMatrix.M21() = myz + sx;
		rotationMatrix.M02() = mxz + sy;
		rotationMatrix.M12() = myz - sx;
		rotationMatrix.M22() = mzz + cos;

		return rotationMatrix;
	}

	template<std::floating_point T>
	Matrix3x3<T> FromToRotationMatrix(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept
	{
		const std::pair<Vector3<T>, T> axisAngle = FromToAxisAngle(fromDirection, toDirection);

		return RotationMatrix(axisAngle.first, axisAngle.second);
	}

	template<std::floating_point T>
	Matrix3x3<T> LookInRotationMatrix(const Vector3<T>& forward, const Vector3<T>& up) noexcept
	{
		if (std::abs(Dot(forward, up)) > T{0.9999}) [[unlikely]]
		{
			return FromToRotationMatrix(Vector3<T>::Predefined::Forward, forward);
		}

		return LookIn(forward, up);
	}

	template<std::floating_point T>
	Vector3<T> Euler(const Quaternion<T>& quaternion) noexcept
	{
		const T halfSin = quaternion.X() * quaternion.W() - quaternion.Y() * quaternion.Z();

		Vector3<T> euler;

		if (std::abs(halfSin) > T{0.4999}) [[unlikely]] // singularity in the North Pole (+) or in the South Pole (-)
		{
			euler.X() = std::copysign(std::numbers::pi_v<T> * T{0.5}, halfSin);
			euler.Y() = std::copysign(T{2}, halfSin) * std::atan2(quaternion.Y(), quaternion.X());
			euler.Z() = T{0};
		}
		else [[likely]]
		{
			euler.X() = std::asin(T{2} * halfSin);
			euler.Y() = std::atan2(T{2} * (quaternion.X() * quaternion.Z() + quaternion.Y() * quaternion.W()), T{1} - T{2} * (quaternion.X() * quaternion.X() + quaternion.Y() * quaternion.Y()));
			euler.Z() = std::atan2(T{2} * (quaternion.X() * quaternion.Y() + quaternion.Z() * quaternion.W()), T{1} - T{2} * (quaternion.X() * quaternion.X() + quaternion.Z() * quaternion.Z()));
		}

		return euler;
	}

	template<std::floating_point T>
	Vector3<T> Euler(const Matrix3x3<T>& rotationMatrix) noexcept
	{
		Vector3<T> euler;

		if (std::abs(rotationMatrix.M12()) > T{0.9999}) [[unlikely]] // singularity in the North Pole (-) or in the South Pole (+)
		{
			euler.X() = std::copysign(std::numbers::pi_v<T> * T{0.5}, -rotationMatrix.M12());
			euler.Y() = std::atan2(-rotationMatrix.M20(), rotationMatrix.M00());
			euler.Z() = T{0};
		}
		else [[likely]]
		{
			euler.X() = std::asin(-rotationMatrix.M12());
			euler.Y() = std::atan2(rotationMatrix.M02(), rotationMatrix.M22());
			euler.Z() = std::atan2(rotationMatrix.M10(), rotationMatrix.M11());
		}

		return euler;
	}

	template<std::floating_point T>
	Vector3<T> Euler(const Vector3<T>& axis, const T angle) noexcept
	{
		return Euler(RotationQuaternion(axis, angle));
	}

	template<std::floating_point T>
	Vector3<T> FromToEuler(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept
	{
		const std::pair<Vector3<T>, T> axisAngle = FromToAxisAngle(fromDirection, toDirection);

		return Euler(axisAngle.first, axisAngle.second);
	}

	template<std::floating_point T>
	Vector3<T> LookInEuler(const Vector3<T>& forward, const Vector3<T>& up) noexcept
	{
		if (std::abs(Dot(forward, up)) > T{0.9999}) [[unlikely]]
		{
			return FromToEuler(Vector3<T>::Predefined::Forward, forward);
		}

		return Euler(LookIn(forward, up));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> AxisAngle(const Quaternion<T>& quaternion) noexcept
	{
		std::pair<Vector3<T>, T> axisAngle;

		if (std::abs(quaternion.W()) > T{0.9999}) [[unlikely]]
		{
			axisAngle.first = Vector3<T>::Predefined::Forward;
			axisAngle.second = T{0};
		}
		else [[likely]]
		{
			const T halfAngle = std::acos(quaternion.W());
			axisAngle.first = Vector3<T>(quaternion.X(), quaternion.Y(), quaternion.Z()) * (T{1} / std::sin(halfAngle));
			axisAngle.second = halfAngle * T{2};
		}

		return axisAngle;
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> AxisAngle(const Matrix3x3<T>& rotationMatrix) noexcept
	{
		return AxisAngle(RotationQuaternion(rotationMatrix));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> AxisAngle(const Vector3<T>& euler) noexcept
	{
		return AxisAngle(RotationQuaternion(euler));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> FromToAxisAngle(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept
	{
		const T dot = Dot(fromDirection, toDirection);

		std::pair<Vector3<T>, T> axisAngle;

		if (dot > T{0.9999}) [[unlikely]]
		{
			axisAngle.first = Vector3<T>::Predefined::Forward;
			axisAngle.second = T{0};
		}
		else if (dot < T{-0.9999}) [[unlikely]]
		{
			axisAngle.first = std::abs(Dot(fromDirection, Vector3<T>::Predefined::Up)) > T{0.5}
				? Cross(fromDirection, Vector3<T>::Predefined::Forward)
				: Cross(fromDirection, Vector3<T>::Predefined::Up);
			axisAngle.first.Normalize();
			axisAngle.second = std::numbers::pi_v<T>;
		}
		else [[likely]]
		{
			axisAngle.first = Cross(fromDirection, toDirection).Normalized();
			axisAngle.second = std::acos(dot);
		}

		return axisAngle;
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> LookInAxisAngle(const Vector3<T>& forward, const Vector3<T>& up) noexcept
	{
		if (std::abs(Dot(forward, up)) > T{0.9999}) [[unlikely]]
		{
			return FromToAxisAngle(Vector3<T>::Predefined::Forward, forward);
		}

		return AxisAngle(LookIn(forward, up));
	}

	template<std::floating_point T>
	constexpr Matrix3x3<T> RsMatrix(const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept
	{
		return RsMatrix(RotationMatrix(quaternion), scaling);
	}

	template<std::floating_point T>
	constexpr Matrix3x3<T> RsMatrix(const Matrix3x3<T>& rotationMatrix, const Vector3<T>& scaling) noexcept
	{
		Matrix3x3<T> rsMatrix;
		for (std::size_t i = 0; i < Matrix3x3<T>::Dimension; ++i)
		{
			rsMatrix.Column(i, rotationMatrix.Column(i) * scaling[i]);
		}

		return rsMatrix;
	}

	template<std::floating_point T>
	Matrix3x3<T> RsMatrix(const Vector3<T>& euler, const Vector3<T>& scaling) noexcept
	{
		return RsMatrix(RotationMatrix(euler), scaling);
	}

	template<std::floating_point T>
	Matrix3x3<T> RsMatrix(const Vector3<T>& axis, const T angle, const Vector3<T>& scaling) noexcept
	{
		return RsMatrix(RotationMatrix(axis, angle), scaling);
	}

	template<std::floating_point T>
	constexpr Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(quaternion, scaling));
	}

	template<std::floating_point T>
	constexpr Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Matrix3x3<T>& rotationMatrix, const Vector3<T>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(rotationMatrix, scaling));
	}

	template<std::floating_point T>
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Vector3<T>& euler, const Vector3<T>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(euler, scaling));
	}

	template<std::floating_point T>
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Vector3<T>& axis, const T angle, const Vector3<T>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(axis, angle, scaling));
	}

	template<std::floating_point T>
	constexpr Matrix4x4<T> TrsMatrix(const Matrix3x3<T>& rsMatrix) noexcept
	{
		Matrix4x4<T> trsMatrix = Matrix4x4<T>::Predefined::Identity;
		trsMatrix.M00() = rsMatrix.M00();
		trsMatrix.M10() = rsMatrix.M10();
		trsMatrix.M20() = rsMatrix.M20();
		trsMatrix.M01() = rsMatrix.M01();
		trsMatrix.M11() = rsMatrix.M11();
		trsMatrix.M21() = rsMatrix.M21();
		trsMatrix.M02() = rsMatrix.M02();
		trsMatrix.M12() = rsMatrix.M12();
		trsMatrix.M22() = rsMatrix.M22();

		return trsMatrix;
	}

	template<std::floating_point T>
	constexpr Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Matrix3x3<T>& rsMatrix) noexcept
	{
		Matrix4x4<T> trsMatrix = TrsMatrix(rsMatrix);
		trsMatrix.M03() = translation.X();
		trsMatrix.M13() = translation.Y();
		trsMatrix.M23() = translation.Z();

		return trsMatrix;
	}

	template<std::floating_point T>
	Matrix4x4<T> PerspectiveMatrix(const T fov, const T aspect, const T nearPlane, const T farPlane) noexcept // TODO: Add extract functions
	{
		const T fovScale = T{1} / std::tan(fov * T{0.5});
		const T planeScale = farPlane / (farPlane - nearPlane);

		Matrix4x4<T> perspective = Matrix4x4<T>::Predefined::Zero;
		perspective.M00() = fovScale / aspect;
		perspective.M11() = fovScale;
		perspective.M22() = planeScale;
		perspective.M32() = T{1};
		perspective.M23() = -nearPlane * planeScale;

		return perspective;
	}

	template<std::floating_point T>
	constexpr Vector3<T> ExtractTranslation(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return Vector3<T>(trsMatrix.M03(), trsMatrix.M13(), trsMatrix.M23());
	}

	template<std::floating_point T>
	Quaternion<T> ExtractRotationQuaternion(const Matrix3x3<T>& rsMatrix) noexcept
	{
		return RotationQuaternion(ExtractRotationMatrix3D(rsMatrix));
	}

	template<std::floating_point T>
	Quaternion<T> ExtractRotationQuaternion(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return RotationQuaternion(ExtractRotationMatrix3D(trsMatrix));
	}

	template<std::floating_point T>
	Matrix3x3<T> ExtractRotationMatrix3D(const Matrix3x3<T>& rsMatrix) noexcept
	{
		const Vector3<T> scaling = ExtractScaling3D(rsMatrix);

		Matrix3x3<T> rotationMatrix;
		for (std::size_t i = 0; i < Matrix3x3<T>::Dimension; ++i)
		{
			const T inverseScaling = T{1} / scaling[i];
			rotationMatrix.Column(i, rsMatrix.Column(i) * inverseScaling);
		}

		return rotationMatrix;
	}

	template<std::floating_point T>
	Matrix3x3<T> ExtractRotationMatrix3D(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return ExtractRotationMatrix3D(ExtractRsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	Vector3<T> ExtractEuler(const Matrix3x3<T>& rsMatrix) noexcept
	{
		return Euler(ExtractRotationMatrix3D(rsMatrix));
	}

	template<std::floating_point T>
	Vector3<T> ExtractEuler(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return Euler(ExtractRotationMatrix3D(trsMatrix));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> ExtractAxisAngle(const Matrix3x3<T>& rsMatrix) noexcept
	{
		return AxisAngle(ExtractRotationMatrix3D(rsMatrix));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> ExtractAxisAngle(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return AxisAngle(ExtractRotationMatrix3D(trsMatrix));
	}

	template<std::floating_point T>
	Vector3<T> ExtractScaling3D(const Matrix3x3<T>& rsMatrix) noexcept
	{
		Vector3<T> scaling;
		for (std::size_t i = 0; i < Matrix3x3<T>::Dimension; ++i)
		{
			scaling[i] = rsMatrix.Column(i).Magnitude();
		}

		return scaling;
	}

	template<std::floating_point T>
	Vector3<T> ExtractScaling3D(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return ExtractScaling3D(ExtractRsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	constexpr Matrix3x3<T> ExtractRsMatrix(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return Matrix3x3<T>(trsMatrix.M00(), trsMatrix.M10(), trsMatrix.M20(), trsMatrix.M01(), trsMatrix.M11(), trsMatrix.M21(), trsMatrix.M02(), trsMatrix.M12(), trsMatrix.M22());
	}

	template<std::floating_point T>
	Vector3<T> Rotate(const Vector3<T>& vector, const Vector3<T>& euler) noexcept
	{
		return RotationQuaternion(euler) * vector;
	}

	template<std::floating_point T>
	Vector3<T> Rotate(const Vector3<T>& vector, const Vector3<T>& axis, const T angle) noexcept
	{
		const Vector3<T> cross = Cross(axis, vector);
		const T dot = Dot(axis, vector);
		const T sin = std::sin(angle);
		const T cos = std::cos(angle);
		const T mCos = T{1} - cos;

		return vector * cos + cross * sin + axis * (dot * mCos);
	}

	template<std::floating_point T>
	constexpr Vector3<T> TransformPoint(const Matrix4x4<T>& transformationMatrix, const Vector3<T>& vector) noexcept
	{
		return TransformVector(transformationMatrix, vector, T{1});
	}

	template<std::floating_point T>
	constexpr Vector3<T> TransformDirection(const Matrix4x4<T>& transformationMatrix, const Vector3<T>& vector) noexcept
	{
		return TransformVector(transformationMatrix, vector, T{0});
	}

	template<std::floating_point T>
	Matrix3x3<T> LookIn(const Vector3<T>& forward, const Vector3<T>& up) noexcept
	{
		const Vector3<T> right = Cross(up, forward).Normalized();
		const Vector3<T> trueUp = Cross(forward, right);

		return Matrix3x3<T>(right, trueUp, forward);
	}

	template<std::floating_point T>
	constexpr Vector3<T> TransformVector(const Matrix4x4<T>& transformationMatrix, const Vector3<T>& vector, const T w) noexcept
	{
		const Vector4<T> transformed = transformationMatrix * Vector4<T>(vector.X(), vector.Y(), vector.Z(), w);

		return Vector3<T>(transformed.X(), transformed.Y(), transformed.Z());
	}
}