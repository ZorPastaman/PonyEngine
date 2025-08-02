/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Transformations;

import std;

import :Matrix;
import :Quaternion;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Converts the 2D rotation matrix to a rotation angle.
	/// @tparam T Value type.
	/// @param rotationMatrix Rotation matrix.
	/// @return Rotation angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T RotationAngle(const Matrix2x2<T>& rotationMatrix) noexcept;

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

	/// @brief Converts the rotation angle to a 2D rotation matrix.
	/// @param angle Rotation angle in radians.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> RotationMatrix(T angle) noexcept;
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

	/// @brief Creates a 2D rotation-scaling matrix from the angle and scaling.
	/// @param angle Rotation angle in radians.
	/// @param scaling Component-wise scaling.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x2<T> RsMatrix(T angle, const Vector2<T>& scaling) noexcept;
	/// @brief Creates a 3D rotation-scaling matrix from the rotation quaternion and scaling.
	/// @tparam T Value type.
	/// @param quaternion Rotation quaternion.
	/// @param scaling Scaling.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix3x3<T> RsMatrix(const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a rotation-scaling matrix from the rotation matrix and scaling.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param rotationMatrix Rotation matrix. 
	/// @param scaling Scaling.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Matrix<T, Size, Size> RsMatrix(const Matrix<T, Size, Size>& rotationMatrix, const Vector<T, Size>& scaling) noexcept;
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

	/// @brief Creates a 2D translation-rotation-scaling matrix from the 2D translation, rotation angle and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param angle Rotation angle in radians.
	/// @param scaling Scaling.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, T angle, const Vector2<T>& scaling) noexcept;
	/// @brief Creates a compact 2D translation-rotation-scaling matrix from the 2D translation, rotation angle and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param angle Rotation angle in radians.
	/// @param scaling Scaling.
	/// @return Compact translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix2x3<T> TrsMatrixCompact(const Vector2<T>& translation, T angle, const Vector2<T>& scaling) noexcept;
	/// @brief Creates a 3D translation-rotation-scaling matrix from the translation, rotation quaternion and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param quaternion Rotation quaternion.
	/// @param scaling Scaling.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a compact 3D translation-rotation-scaling matrix from the translation, rotation quaternion and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param quaternion Rotation quaternion.
	/// @param scaling Scaling.
	/// @return Compact translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix3x4<T> TrsMatrixCompact(const Vector3<T>& translation, const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a translation-rotation-scaling matrix from the translation, rotation matrix and scaling.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param translation Translation.
	/// @param rotationMatrix Rotation matrix.
	/// @param scaling Scaling.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Matrix<T, Size + 1, Size + 1> TrsMatrix(const Vector<T, Size>& translation, const Matrix<T, Size, Size>& rotationMatrix, const Vector<T, Size>& scaling) noexcept;
	/// @brief Creates a compact translation-rotation-scaling matrix from the translation, rotation matrix and scaling.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param translation Translation.
	/// @param rotationMatrix Rotation matrix.
	/// @param scaling Scaling.
	/// @return Compact translation-rotation-scaling matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Matrix<T, Size, Size + 1> TrsMatrixCompact(const Vector<T, Size>& translation, const Matrix<T, Size, Size>& rotationMatrix, const Vector<T, Size>& scaling) noexcept;
	/// @brief Creates a 3D translation-rotation-scaling matrix from the translation, Euler angles and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param euler Euler angles in radians.
	/// @param scaling Scaling.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Vector3<T>& euler, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a compact 3D translation-rotation-scaling matrix from the translation, Euler angles and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param euler Euler angles in radians.
	/// @param scaling Scaling.
	/// @return Compact translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x4<T> TrsMatrixCompact(const Vector3<T>& translation, const Vector3<T>& euler, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a 3D translation-rotation-scaling matrix from the translation, axis-angle rotation and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param axis Axis. Must be unit.
	/// @param angle Rotation angle in radians.
	/// @param scaling Scaling.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Vector3<T>& axis, T angle, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a compact 3D translation-rotation-scaling matrix from the translation, axis-angle rotation and scaling.
	/// @tparam T Value type.
	/// @param translation Translation.
	/// @param axis Axis. Must be unit.
	/// @param angle Rotation angle in radians.
	/// @param scaling Scaling.
	/// @return Compact translation-rotation-scaling matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x4<T> TrsMatrixCompact(const Vector3<T>& translation, const Vector3<T>& axis, T angle, const Vector3<T>& scaling) noexcept;
	/// @brief Creates a translation-rotation-scaling matrix from the rotation-scaling matrix. The translation part will be zero.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Matrix<T, Size + 1, Size + 1> TrsMatrix(const Matrix<T, Size, Size>& rsMatrix) noexcept;
	/// @brief Creates a compact translation-rotation-scaling matrix from the rotation-scaling matrix. The translation part will be zero.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Compact translation-rotation-scaling matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Matrix<T, Size, Size + 1> TrsMatrixCompact(const Matrix<T, Size, Size>& rsMatrix) noexcept;
	/// @brief Creates a translation-rotation-scaling matrix from the translation and rotation-scaling matrix.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param translation Translation.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Matrix<T, Size + 1, Size + 1> TrsMatrix(const Vector<T, Size>& translation, const Matrix<T, Size, Size>& rsMatrix) noexcept;
	/// @brief Creates a compact translation-rotation-scaling matrix from the translation and rotation-scaling matrix.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param translation Translation.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Compact translation-rotation-scaling matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Matrix<T, Size, Size + 1> TrsMatrixCompact(const Vector<T, Size>& translation, const Matrix<T, Size, Size>& rsMatrix) noexcept;
	/// @brief Converts the compact translation-rotation-scaling matrix to a full translation-rotation-scaling matrix.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param trsMatrixCompact Compact translation-rotation-scaling matrix. 
	/// @return Translation-rotation-scaling matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Matrix<T, Size + 1, Size + 1> TrsMatrix(const Matrix<T, Size, Size + 1>& trsMatrixCompact) noexcept;

	/// @brief Creates a 3D perspective projection matrix.
	/// @tparam T Value type.
	/// @param fov Vertical field of view in radians. Must be positive.
	/// @param aspect Aspect ratio (width / height). Must be positive.
	/// @param nearPlane Distance between a camera and a near clipping plane. Must be positive.
	/// @param farPlane Distance between a camera and a far clipping plane. Must be positive and greater than the @p nearPlane.
	/// @return Perspective projection matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix4x4<T> PerspectiveMatrix(T fov, T aspect, T nearPlane, T farPlane) noexcept;
	/// @brief Creates a 3D orthographic projection matrix.
	/// @tparam T Value type.
	/// @param width Width. Must be positive.
	/// @param height Height. Must be positive.
	/// @param nearPlane Distance between a camera and a near clipping plane. Must be positive.
	/// @param farPlane Distance between a camera and a far clipping plane. Must be positive and greater than the @p nearPlane.
	/// @return Orthographic projection matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Matrix4x4<T> OrthographicMatrix(T width, T height, T nearPlane, T farPlane) noexcept;

	/// @brief Extracts a translation from the translation-rotation-scaling matrix.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Translation.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size - 1> ExtractTranslationFromTrs(const Matrix<T, Size, Size>& trsMatrix) noexcept requires (Size > 1);
	/// @brief Extracts a translation from the compact translation-rotation-scaling matrix.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param trsMatrix Compact translation-rotation-scaling matrix.
	/// @return Translation.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> ExtractTranslationFromTrs(const Matrix<T, Size, Size + 1>& trsMatrix) noexcept;

	/// @brief Attempts to extract a rotation angle from the 2D rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Rotation angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T ExtractAngleFromRs(const Matrix2x2<T>& rsMatrix) noexcept;
	/// @brief Attempts to extract a rotation angle from the 2D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Rotation angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T ExtractAngleFromTrs(const Matrix3x3<T>& trsMatrix) noexcept;
	/// @brief Attempts to extract a rotation angle from the compact 2D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Compact translation-rotation-scaling matrix.
	/// @return Rotation angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T ExtractAngleFromTrs(const Matrix2x3<T>& trsMatrix) noexcept;

	/// @brief Attempts to extract a rotation quaternion from the 3D rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Rotation quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> ExtractRotationQuaternionFromRs(const Matrix3x3<T>& rsMatrix) noexcept;
	/// @brief Attempts to extract a rotation quaternion from the 3D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Rotation quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> ExtractRotationQuaternionFromTrs(const Matrix4x4<T>& trsMatrix) noexcept;
	/// @brief Attempts to extract a rotation quaternion from the compact 3D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Compact translation-rotation-scaling matrix.
	/// @return Rotation quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> ExtractRotationQuaternionFromTrs(const Matrix3x4<T>& trsMatrix) noexcept;

	/// @brief Attempts to extract a rotation matrix from the rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @note If the matrix has a zero column, the result is undefined.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Rotation matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Matrix<T, Size, Size> ExtractRotationMatrixFromRs(const Matrix<T, Size, Size>& rsMatrix) noexcept;
	/// @brief Attempts to extract a rotation matrix from the translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @note If the rotation-scaling part of the matrix has a zero column, the result is undefined.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Rotation matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Matrix<T, Size - 1, Size - 1> ExtractRotationMatrixFromTrs(const Matrix<T, Size, Size>& trsMatrix) noexcept requires (Size > 1);
	/// @brief Attempts to extract a rotation matrix from the compact translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @note If the rotation-scaling part of the matrix has a zero column, the result is undefined.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param trsMatrix Compact translation-rotation-scaling matrix.
	/// @return Rotation matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Matrix<T, Size, Size> ExtractRotationMatrixFromTrs(const Matrix<T, Size, Size + 1>& trsMatrix) noexcept;

	/// @brief Attempts to extract Euler angles from the 3D rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Euler angles in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> ExtractEulerFromRs(const Matrix3x3<T>& rsMatrix) noexcept;
	/// @brief Attempts to extract Euler angles from the 3D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Euler angles in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> ExtractEulerFromTrs(const Matrix4x4<T>& trsMatrix) noexcept;
	/// @brief Attempts to extract Euler angles from the compact 3D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Compact translation-rotation-scaling matrix.
	/// @return Euler angles in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> ExtractEulerFromTrs(const Matrix3x4<T>& trsMatrix) noexcept;

	/// @brief Attempts to extract an axis-angle rotation from the 3D rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Axis-angle rotation. The angle is in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> ExtractAxisAngleFromRs(const Matrix3x3<T>& rsMatrix) noexcept;
	/// @brief Attempts to extract an axis-angle rotation from the 3D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Axis-angle rotation. The angle is in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> ExtractAxisAngleFromTrs(const Matrix4x4<T>& trsMatrix) noexcept;
	/// @brief Attempts to extract an axis-angle rotation from the compact 3D translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is positive.
	/// @tparam T Value type.
	/// @param trsMatrix Compact translation-rotation-scaling matrix.
	/// @return Axis-angle rotation. The angle is in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> ExtractAxisAngleFromTrs(const Matrix3x4<T>& trsMatrix) noexcept;

	/// @brief Attempts to extract a scaling from the rotation-scaling matrix.
	/// @note It works correctly if the scaling is non-negative.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param rsMatrix Rotation-scaling matrix.
	/// @return Scaling.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Vector<T, Size> ExtractScalingFromRs(const Matrix<T, Size, Size>& rsMatrix) noexcept;
	/// @brief Attempts to extract a scaling from the translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is non-negative.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Scaling.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Vector<T, Size - 1> ExtractScalingFromTrs(const Matrix<T, Size, Size>& trsMatrix) noexcept requires (Size > 1);
	/// @brief Attempts to extract a scaling from the compact translation-rotation-scaling matrix.
	/// @note It works correctly if the scaling is non-negative.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param trsMatrix Compact translation-rotation-scaling matrix.
	/// @return Scaling.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Vector<T, Size> ExtractScalingFromTrs(const Matrix<T, Size, Size + 1>& trsMatrix) noexcept;

	/// @brief Extracts a rotation-scaling matrix from the translation-rotation-scaling matrix.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param trsMatrix Translation-rotation-scaling matrix.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Matrix<T, Size - 1, Size - 1> ExtractRsMatrixFromTrs(const Matrix<T, Size, Size>& trsMatrix) noexcept requires (Size > 1);
	/// @brief Extracts a rotation-scaling matrix from the compact translation-rotation-scaling matrix.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param trsMatrix Compact translation-rotation-scaling matrix.
	/// @return Rotation-scaling matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Matrix<T, Size, Size> ExtractRsMatrixFromTrs(const Matrix<T, Size, Size + 1>& trsMatrix) noexcept;
	/// @brief Extracts a compact translation-rotation-scaling matrix from the full translation-rotation-scaling matrix.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param trsMatrix Translation-rotation-scaling matrix. 
	/// @return Compact translation-rotation-scaling matrix.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Matrix<T, Size - 1, Size> ExtractTrsMatrixFromTrs(const Matrix<T, Size, Size>& trsMatrix) noexcept requires (Size > 1);

	/// @brief Extracts a field of view from the perspective projection matrix.
	/// @tparam T Value type.
	/// @param perspectiveMatrix Perspective projection matrix.
	/// @return Field of view in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T ExtractFov(const Matrix4x4<T>& perspectiveMatrix) noexcept;
	/// @brief Extracts a width from the orthographic projection matrix.
	/// @tparam T Value type.
	/// @param orthographicMatrix Orthographic projection matrix.
	/// @return Width.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T ExtractWidth(const Matrix4x4<T>& orthographicMatrix) noexcept;
	/// @brief Extracts a height from the orthographic projection matrix.
	/// @tparam T Value type.
	/// @param orthographicMatrix Orthographic projection matrix.
	/// @return Height.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T ExtractHeight(const Matrix4x4<T>& orthographicMatrix) noexcept;
	/// @brief Extracts an aspect ratio from the perspective or orthographic projection matrix.
	/// @tparam T Value type.
	/// @param projectionMatrix Projection matrix.
	/// @return Aspect ratio (width / height).
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T ExtractAspect(const Matrix4x4<T>& projectionMatrix) noexcept;
	/// @brief Extracts a near clipping plane distance from the perspective or orthographic projection matrix.
	/// @tparam T Value type.
	/// @param projectionMatrix Projection matrix.
	/// @return Near clipping plane distance.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T ExtractNearPlane(const Matrix4x4<T>& projectionMatrix) noexcept;
	/// @brief Extracts a far clipping plane distance from the perspective projection matrix.
	/// @tparam T Value type.
	/// @param perspectiveMatrix Perspective projection matrix.
	/// @return Far clipping plane distance.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T ExtractFarPlanePerspective(const Matrix4x4<T>& perspectiveMatrix) noexcept;
	/// @brief Extracts a far clipping plane distance from the orthographic projection matrix.
	/// @tparam T Value type.
	/// @param orthographicMatrix Orthographic projection matrix.
	/// @return Far clipping plane distance.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T ExtractFarPlaneOrthographic(const Matrix4x4<T>& orthographicMatrix) noexcept;

	/// @brief Rotates the @p vector by the @p angle.
	/// @tparam T Value type.
	/// @param vector Vector to rotate.
	/// @param angle Rotation angle in radians.
	/// @return Rotated vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector2<T> Rotate(const Vector2<T>& vector, T angle) noexcept;
	/// @brief Rotates the @p vector with the @p axis and @p angle.
	/// @tparam T Value type.
	/// @param vector Vector to rotate.
	/// @param axis Rotation axis.
	/// @param angle Rotation angle in radians.
	/// @return Rotated vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Rotate(const Vector3<T>& vector, const Vector3<T>& axis, T angle) noexcept;

	/// @brief Applies the transformation matrix to the point vector.
	/// @tparam PerspectiveDivision Whether to divide by a homogeneous divisor after transformation.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param transformationMatrix Transformation matrix. 
	/// @param vector Point.
	/// @return Transformed point.
	template<bool PerspectiveDivision = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> TransformPoint(const Matrix<T, Size + 1, Size + 1>& transformationMatrix, const Vector<T, Size>& vector) noexcept;
	/// @brief Applies the compact transformation matrix to the point vector.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param transformationMatrix Transformation matrix. 
	/// @param vector Point.
	/// @return Transformed point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> TransformPoint(const Matrix<T, Size, Size + 1>& transformationMatrix, const Vector<T, Size>& vector) noexcept;
	/// @brief Applies the transformation matrix to the direction vector.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param transformationMatrix Transformation matrix. 
	/// @param vector Direction.
	/// @return Transformed direction.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> TransformDirection(const Matrix<T, Size + 1, Size + 1>& transformationMatrix, const Vector<T, Size>& vector) noexcept;
	/// @brief Applies the compact transformation matrix to the direction vector.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param transformationMatrix Transformation matrix. 
	/// @param vector Direction.
	/// @return Transformed direction.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> TransformDirection(const Matrix<T, Size, Size + 1>& transformationMatrix, const Vector<T, Size>& vector) noexcept;
	/// @brief Applies the transformation matrix to the vector in the homogeneous space.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param transformationMatrix Transformation matrix. 
	/// @param vector Vector.
	/// @param homogeneousComponent Homogeneous component.
	/// @return Transformed vector.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size + 1> TransformHomogeneous(const Matrix<T, Size + 1, Size + 1>& transformationMatrix, const Vector<T, Size>& vector, T homogeneousComponent) noexcept;
	/// @brief Applies the compact transformation matrix to the vector in the homogeneous space.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param transformationMatrix Transformation matrix. 
	/// @param vector Vector.
	/// @param homogeneousComponent Homogeneous component.
	/// @return Transformed vector.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> TransformHomogeneous(const Matrix<T, Size, Size + 1>& transformationMatrix, const Vector<T, Size>& vector, T homogeneousComponent) noexcept;

	/// @brief Creates a homogeneous vector.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param vector Vector.
	/// @param homogeneousComponent Homogeneous component.
	/// @return Homogeneous vector.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size + 1> CreateHomogeneous(const Vector<T, Size>& vector, T homogeneousComponent) noexcept;
}

namespace PonyEngine::Math
{
	/// @brief Creates a 3D rotation matrix representing a rotation so that the @p forward be a look direction and the @p up be an upward vector.
	/// @note Forward and up mustn't be collinear.
	/// @tparam T Value type.
	/// @param forward Forward vector. Must be unit.
	/// @param up Upward vector. Must be unit.
	/// @return Rotation matrix.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> LookIn(const Vector3<T>& forward, const Vector3<T>& up) noexcept;

	template<std::floating_point T>
	T RotationAngle(const Matrix2x2<T>& rotationMatrix) noexcept
	{
		return std::atan2(rotationMatrix[1, 0], rotationMatrix[0, 0]);
	}

	template<std::floating_point T>
	Quaternion<T> RotationQuaternion(const Matrix3x3<T>& rotationMatrix) noexcept
	{
		Quaternion<T> quaternion;
		if (const T trace = rotationMatrix.Trace(); trace > T{0})
		{
			const T s = std::sqrt(T{1} + trace) * T{2};
			const T inverseS = T{1} / s;

			quaternion.X() = (rotationMatrix[2, 1] - rotationMatrix[1, 2]) * inverseS;
			quaternion.Y() = (rotationMatrix[0, 2] - rotationMatrix[2, 0]) * inverseS;
			quaternion.Z() = (rotationMatrix[1, 0] - rotationMatrix[0, 1]) * inverseS;
			quaternion.W() = s * T{0.25};
		}
		else if (rotationMatrix[0, 0] > rotationMatrix[1, 1] && rotationMatrix[0, 0] > rotationMatrix[2, 2])
		{
			const T s = std::sqrt(T{1} + rotationMatrix[0, 0] - rotationMatrix[1, 1] - rotationMatrix[2, 2]) * T{2};
			const T inverseS = T{1} / s;

			quaternion.X() = s * T{0.25};
			quaternion.Y() = (rotationMatrix[0, 1] + rotationMatrix[1, 0]) * inverseS;
			quaternion.Z() = (rotationMatrix[0, 2] + rotationMatrix[2, 0]) * inverseS;
			quaternion.W() = (rotationMatrix[2, 1] - rotationMatrix[1, 2]) * inverseS;
		}
		else if (rotationMatrix[1, 1] > rotationMatrix[2, 2])
		{
			const T s = std::sqrt(T{1} + rotationMatrix[1, 1] - rotationMatrix[0, 0] - rotationMatrix[2, 2]) * T{2};
			const T inverseS = T{1} / s;

			quaternion.X() = (rotationMatrix[0, 1] + rotationMatrix[1, 0]) * inverseS;
			quaternion.Y() = s * T{0.25};
			quaternion.Z() = (rotationMatrix[1, 2] + rotationMatrix[2, 1]) * inverseS;
			quaternion.W() = (rotationMatrix[0, 2] - rotationMatrix[2, 0]) * inverseS;
		}
		else
		{
			const T s = std::sqrt(T{1} + rotationMatrix[2, 2] - rotationMatrix[0, 0] - rotationMatrix[1, 1]) * T{2};
			const T inverseS = T{1} / s;

			quaternion.X() = (rotationMatrix[0, 2] + rotationMatrix[2, 0]) * inverseS;
			quaternion.Y() = (rotationMatrix[1, 2] + rotationMatrix[2, 1]) * inverseS;
			quaternion.Z() = s * T{0.25};
			quaternion.W() = (rotationMatrix[1, 0] - rotationMatrix[0, 1]) * inverseS;
		}

		return quaternion;
	}

	template<std::floating_point T>
	Quaternion<T> RotationQuaternion(const Vector3<T>& euler) noexcept
	{
		const Vector3<T> eulerHalf = euler * T{0.5};

		const T xSin = std::sin(eulerHalf.X());
		const T xCos = std::cos(eulerHalf.X());
		const T ySin = std::sin(eulerHalf.Y());
		const T yCos = std::cos(eulerHalf.Y());
		const T zSin = std::sin(eulerHalf.Z());
		const T zCos = std::cos(eulerHalf.Z());

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
			return FromToRotationQuaternion(Vector3<T>::Forward(), forward);
		}

		return RotationQuaternion(LookIn(forward, up));
	}

	template<std::floating_point T>
	Matrix2x2<T> RotationMatrix(const T angle) noexcept
	{
		const T angleSin = std::sin(angle);
		const T angleCos = std::cos(angle);

		return Matrix2x2<T>(angleCos, angleSin, -angleSin, angleCos);
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
		rotationMatrix[0, 0] = T{1} - (yy + zz) * T{2};
		rotationMatrix[1, 0] = T{2} * (xy + zw);
		rotationMatrix[2, 0] = T{2} * (xz - yw);
		rotationMatrix[0, 1] = T{2} * (xy - zw);
		rotationMatrix[1, 1] = T{1} - (xx + zz) * T{2};
		rotationMatrix[2, 1] = T{2} * (yz + xw);
		rotationMatrix[0, 2] = T{2} * (xz + yw);
		rotationMatrix[1, 2] = T{2} * (yz - xw);
		rotationMatrix[2, 2] = T{1} - (xx + yy) * T{2};

		return rotationMatrix;
	}

	template<std::floating_point T>
	Matrix3x3<T> RotationMatrix(const Vector3<T>& euler) noexcept
	{
		const T xSin = std::sin(euler.X());
		const T xCos = std::cos(euler.X());
		const T ySin = std::sin(euler.Y());
		const T yCos = std::cos(euler.Y());
		const T zSin = std::sin(euler.Z());
		const T zCos = std::cos(euler.Z());

		const T xSyS = xSin * ySin;
		const T xSyC = xSin * yCos;

		Matrix3x3<T> rotationMatrix;
		rotationMatrix[0, 0] = xSyS * zSin + yCos * zCos;
		rotationMatrix[1, 0] = xCos * zSin;
		rotationMatrix[2, 0] = xSyC * zSin - ySin * zCos;
		rotationMatrix[0, 1] = xSyS * zCos - yCos * zSin;
		rotationMatrix[1, 1] = xCos * zCos;
		rotationMatrix[2, 1] = xSyC * zCos + ySin * zSin;
		rotationMatrix[0, 2] = xCos * ySin;
		rotationMatrix[1, 2] = -xSin;
		rotationMatrix[2, 2] = xCos * yCos;

		return rotationMatrix;
	}

	template<std::floating_point T>
	Matrix3x3<T> RotationMatrix(const Vector3<T>& axis, const T angle) noexcept
	{
		const T sin = std::sin(angle);
		const T cos = std::cos(angle);

		const Vector3<T> axisSin = axis * sin;
		const Vector3<T> axisCos = axis * (T{1} - cos);

		const T xx = axisCos.X() * axis.X();
		const T xy = axisCos.X() * axis.Y();
		const T xz = axisCos.X() * axis.Z();
		const T yy = axisCos.Y() * axis.Y();
		const T yz = axisCos.Y() * axis.Z();
		const T zz = axisCos.Z() * axis.Z();

		Matrix3x3<T> rotationMatrix;
		rotationMatrix[0, 0] = xx + cos;
		rotationMatrix[1, 0] = xy + axisSin.Z();
		rotationMatrix[2, 0] = xz - axisSin.Y();
		rotationMatrix[0, 1] = xy - axisSin.Z();
		rotationMatrix[1, 1] = yy + cos;
		rotationMatrix[2, 1] = yz + axisSin.X();
		rotationMatrix[0, 2] = xz + axisSin.Y();
		rotationMatrix[1, 2] = yz - axisSin.X();
		rotationMatrix[2, 2] = zz + cos;

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
			return FromToRotationMatrix(Vector3<T>::Forward(), forward);
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
			const T xx = quaternion.X() * quaternion.X();
			euler.X() = std::asin(T{2} * halfSin);
			euler.Y() = std::atan2(T{2} * (quaternion.X() * quaternion.Z() + quaternion.Y() * quaternion.W()), T{1} - T{2} * (xx + quaternion.Y() * quaternion.Y()));
			euler.Z() = std::atan2(T{2} * (quaternion.X() * quaternion.Y() + quaternion.Z() * quaternion.W()), T{1} - T{2} * (xx + quaternion.Z() * quaternion.Z()));
		}

		return euler;
	}

	template<std::floating_point T>
	Vector3<T> Euler(const Matrix3x3<T>& rotationMatrix) noexcept
	{
		Vector3<T> euler;
		if (std::abs(rotationMatrix[1, 2]) > T{0.9999}) [[unlikely]] // singularity in the North Pole (-) or in the South Pole (+)
		{
			euler.X() = std::copysign(std::numbers::pi_v<T> * T{0.5}, -rotationMatrix[1, 2]);
			euler.Y() = std::atan2(-rotationMatrix[2, 0], rotationMatrix[0, 0]);
			euler.Z() = T{0};
		}
		else [[likely]]
		{
			euler.X() = std::asin(-rotationMatrix[1, 2]);
			euler.Y() = std::atan2(rotationMatrix[0, 2], rotationMatrix[2, 2]);
			euler.Z() = std::atan2(rotationMatrix[1, 0], rotationMatrix[1, 1]);
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
			return FromToEuler(Vector3<T>::Forward(), forward);
		}

		return Euler(LookIn(forward, up));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> AxisAngle(const Quaternion<T>& quaternion) noexcept
	{
		std::pair<Vector3<T>, T> axisAngle;
		if (std::abs(quaternion.W()) > T{0.9999}) [[unlikely]]
		{
			axisAngle.first = Vector3<T>::Forward();
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
			axisAngle.first = Vector3<T>::Forward();
			axisAngle.second = T{0};
		}
		else if (dot < T{-0.9999}) [[unlikely]]
		{
			axisAngle.first = std::abs(Dot(fromDirection, Vector3<T>::Up())) > T{0.5}
				? Cross(fromDirection, Vector3<T>::Forward())
				: Cross(fromDirection, Vector3<T>::Up());
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
			return FromToAxisAngle(Vector3<T>::Forward(), forward);
		}

		return AxisAngle(LookIn(forward, up));
	}

	template<std::floating_point T>
	Matrix2x2<T> RsMatrix(const T angle, const Vector2<T>& scaling) noexcept
	{
		return RsMatrix(RotationMatrix(angle), scaling);
	}

	template<std::floating_point T>
	constexpr Matrix3x3<T> RsMatrix(const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept
	{
		return RsMatrix(RotationMatrix(quaternion), scaling);
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Matrix<T, Size, Size> RsMatrix(const Matrix<T, Size, Size>& rotationMatrix, const Vector<T, Size>& scaling) noexcept
	{
		Matrix<T, Size, Size> rsMatrix;
		for (std::size_t i = 0; i < Size; ++i)
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
	Matrix3x3<T> TrsMatrix(const Vector2<T>& translation, const T angle, const Vector2<T>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(angle, scaling));
	}

	template<std::floating_point T>
	Matrix2x3<T> TrsMatrixCompact(const Vector2<T>& translation, const T angle, const Vector2<T>& scaling) noexcept
	{
		return TrsMatrixCompact(translation, RsMatrix(angle, scaling));
	}

	template<std::floating_point T>
	constexpr Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(quaternion, scaling));
	}

	template<std::floating_point T>
	constexpr Matrix3x4<T> TrsMatrixCompact(const Vector3<T>& translation, const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept
	{
		return TrsMatrixCompact(translation, RsMatrix(quaternion, scaling));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Matrix<T, Size + 1, Size + 1> TrsMatrix(const Vector<T, Size>& translation, const Matrix<T, Size, Size>& rotationMatrix, const Vector<T, Size>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(rotationMatrix, scaling));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Matrix<T, Size, Size + 1> TrsMatrixCompact(const Vector<T, Size>& translation, const Matrix<T, Size, Size>& rotationMatrix, const Vector<T, Size>& scaling) noexcept
	{
		return TrsMatrixCompact(translation, RsMatrix(rotationMatrix, scaling));
	}

	template<std::floating_point T>
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Vector3<T>& euler, const Vector3<T>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(euler, scaling));
	}

	template<std::floating_point T>
	Matrix3x4<T> TrsMatrixCompact(const Vector3<T>& translation, const Vector3<T>& euler, const Vector3<T>& scaling) noexcept
	{
		return TrsMatrixCompact(translation, RsMatrix(euler, scaling));
	}

	template<std::floating_point T>
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Vector3<T>& axis, const T angle, const Vector3<T>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(axis, angle, scaling));
	}

	template<std::floating_point T>
	Matrix3x4<T> TrsMatrixCompact(const Vector3<T>& translation, const Vector3<T>& axis, const T angle, const Vector3<T>& scaling) noexcept
	{
		return TrsMatrixCompact(translation, RsMatrix(axis, angle, scaling));
	}

	template<std::floating_point T, std::size_t Size> 
	constexpr Matrix<T, Size + 1, Size + 1> TrsMatrix(const Matrix<T, Size, Size>& rsMatrix) noexcept
	{
		Matrix<T, Size + 1, Size + 1> trsMatrix = Matrix<T, Size + 1, Size + 1>::Identity();
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			if consteval
			{
				std::ranges::copy(rsMatrix.Column(i).Span(), trsMatrix.Column(i).Span().begin());
			}
			else
			{
				std::memcpy(&trsMatrix.Column(i), &rsMatrix.Column(i), sizeof(T) * Size);
			}
		}

		return trsMatrix;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Matrix<T, Size, Size + 1> TrsMatrixCompact(const Matrix<T, Size, Size>& rsMatrix) noexcept
	{
		Matrix<T, Size, Size + 1> trsMatrix = Matrix<T, Size, Size + 1>::Zero();
		if consteval
		{
			for (std::size_t i = 0uz; i < Size; ++i)
			{
				trsMatrix.Column(i, rsMatrix.Column(i));
			}
		}
		else
		{
			std::memcpy(&trsMatrix, &rsMatrix, sizeof(T) * Size * Size);
		}

		return trsMatrix;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Matrix<T, Size + 1, Size + 1> TrsMatrix(const Vector<T, Size>& translation, const Matrix<T, Size, Size>& rsMatrix) noexcept
	{
		Matrix<T, Size + 1, Size + 1> trsMatrix = TrsMatrix(rsMatrix);
		if consteval
		{
			std::ranges::copy(translation.Span(), trsMatrix.Column(Size).Span().begin());
		}
		else
		{
			std::memcpy(&trsMatrix.Column(Size), &translation, sizeof(T) * Size);
		}

		return trsMatrix;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Matrix<T, Size, Size + 1> TrsMatrixCompact(const Vector<T, Size>& translation, const Matrix<T, Size, Size>& rsMatrix) noexcept
	{
		Matrix<T, Size, Size + 1> trsMatrix = TrsMatrixCompact(rsMatrix);
		trsMatrix.Column(Size, translation);

		return trsMatrix;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Matrix<T, Size + 1, Size + 1> TrsMatrix(const Matrix<T, Size, Size + 1>& trsMatrixCompact) noexcept
	{
		auto trsMatrix = Matrix<T, Size + 1, Size + 1>::Identity();
		for (std::size_t i = 0uz; i < Size + 1; ++i)
		{
			if consteval
			{
				std::ranges::copy(trsMatrixCompact.Column(i).Span(), trsMatrix.Column(i).Span().begin());
			}
			else
			{
				std::memcpy(&trsMatrix.Column(i), &trsMatrixCompact.Column(i), sizeof(T) * Size);
			}
		}

		return trsMatrix;
	}

	template<std::floating_point T>
	Matrix4x4<T> PerspectiveMatrix(const T fov, const T aspect, const T nearPlane, const T farPlane) noexcept
	{
		const T fovScale = T{1} / std::tan(fov * T{0.5});
		const T planeScale = farPlane / (farPlane - nearPlane);

		Matrix4x4<T> perspective = Matrix4x4<T>::Zero();
		perspective[0, 0] = fovScale / aspect;
		perspective[1, 1] = fovScale;
		perspective[2, 2] = planeScale;
		perspective[3, 2] = T{1};
		perspective[2, 3] = -nearPlane * planeScale;

		return perspective;
	}

	template<std::floating_point T>
	constexpr Matrix4x4<T> OrthographicMatrix(const T width, const T height, const T nearPlane, const T farPlane) noexcept
	{
		const T inverseDepth = T{1} / (farPlane - nearPlane);

		Matrix4x4<T> orthographic = Matrix4x4<T>::Identity();
		orthographic[0, 0] = T{2} / width;
		orthographic[1, 1] = T{2} / height;
		orthographic[2, 2] = inverseDepth;
		orthographic[2, 3] = -nearPlane * inverseDepth;

		return orthographic;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size - 1> ExtractTranslationFromTrs(const Matrix<T, Size, Size>& trsMatrix) noexcept requires (Size > 1)
	{
		return Vector<T, Size - 1>(trsMatrix.Column(Size - 1).Span().subspan<0, Size - 1>());
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size> ExtractTranslationFromTrs(const Matrix<T, Size, Size + 1>& trsMatrix) noexcept
	{
		return trsMatrix.Column(Size);
	}

	template<std::floating_point T>
	T ExtractAngleFromRs(const Matrix2x2<T>& rsMatrix) noexcept
	{
		return rsMatrix.Column(0).IsAlmostZero()
			? std::atan2(-rsMatrix[0, 1], rsMatrix[1, 1])
			: std::atan2(rsMatrix[1, 0], rsMatrix[0, 0]);
	}

	template<std::floating_point T>
	T ExtractAngleFromTrs(const Matrix3x3<T>& trsMatrix) noexcept
	{
		return ExtractAngleFromRs(ExtractRsMatrixFromTrs(trsMatrix));
	}

	template<std::floating_point T>
	T ExtractAngleFromTrs(const Matrix2x3<T>& trsMatrix) noexcept
	{
		return ExtractAngleFromRs(ExtractRsMatrixFromTrs(trsMatrix));
	}

	template<std::floating_point T>
	Quaternion<T> ExtractRotationQuaternionFromRs(const Matrix3x3<T>& rsMatrix) noexcept
	{
		return RotationQuaternion(ExtractRotationMatrixFromRs(rsMatrix));
	}

	template<std::floating_point T>
	Quaternion<T> ExtractRotationQuaternionFromTrs(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return RotationQuaternion(ExtractRotationMatrixFromTrs(trsMatrix));
	}

	template<std::floating_point T>
	Quaternion<T> ExtractRotationQuaternionFromTrs(const Matrix3x4<T>& trsMatrix) noexcept
	{
		return RotationQuaternion(ExtractRotationMatrixFromTrs(trsMatrix));
	}

	template<std::floating_point T, std::size_t Size>
	Matrix<T, Size, Size> ExtractRotationMatrixFromRs(const Matrix<T, Size, Size>& rsMatrix) noexcept
	{
		const Vector<T, Size> scaling = ExtractScalingFromRs(rsMatrix);

		Matrix<T, Size, Size> rotationMatrix;
		for (std::size_t i = 0; i < Size; ++i)
		{
			const T inverseScaling = T{1} / scaling[i];
			rotationMatrix.Column(i, rsMatrix.Column(i) * inverseScaling);
		}

		return rotationMatrix;
	}

	template<std::floating_point T, std::size_t Size>
	Matrix<T, Size - 1, Size - 1> ExtractRotationMatrixFromTrs(const Matrix<T, Size, Size>& trsMatrix) noexcept requires (Size > 1)
	{
		return ExtractRotationMatrixFromRs(ExtractRsMatrixFromTrs(trsMatrix));
	}

	template<std::floating_point T, std::size_t Size>
	Matrix<T, Size, Size> ExtractRotationMatrixFromTrs(const Matrix<T, Size, Size + 1>& trsMatrix) noexcept
	{
		return ExtractRotationMatrixFromRs(ExtractRsMatrixFromTrs(trsMatrix));
	}

	template<std::floating_point T>
	Vector3<T> ExtractEulerFromRs(const Matrix3x3<T>& rsMatrix) noexcept
	{
		return Euler(ExtractRotationMatrixFromRs(rsMatrix));
	}

	template<std::floating_point T>
	Vector3<T> ExtractEulerFromTrs(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return Euler(ExtractRotationMatrixFromTrs(trsMatrix));
	}

	template<std::floating_point T>
	Vector3<T> ExtractEulerFromTrs(const Matrix3x4<T>& trsMatrix) noexcept
	{
		return Euler(ExtractRotationMatrixFromTrs(trsMatrix));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> ExtractAxisAngleFromRs(const Matrix3x3<T>& rsMatrix) noexcept
	{
		return AxisAngle(ExtractRotationMatrixFromRs(rsMatrix));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> ExtractAxisAngleFromTrs(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return AxisAngle(ExtractRotationMatrixFromTrs(trsMatrix));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> ExtractAxisAngleFromTrs(const Matrix3x4<T>& trsMatrix) noexcept
	{
		return AxisAngle(ExtractRotationMatrixFromTrs(trsMatrix));
	}

	template<std::floating_point T, std::size_t Size>
	Vector<T, Size> ExtractScalingFromRs(const Matrix<T, Size, Size>& rsMatrix) noexcept
	{
		Vector<T, Size> scaling;
		for (std::size_t i = 0; i < Size; ++i)
		{
			scaling[i] = rsMatrix.Column(i).Magnitude();
		}

		return scaling;
	}

	template<std::floating_point T, std::size_t Size>
	Vector<T, Size - 1> ExtractScalingFromTrs(const Matrix<T, Size, Size>& trsMatrix) noexcept requires (Size > 1)
	{
		return ExtractScalingFromRs(ExtractRsMatrixFromTrs(trsMatrix));
	}

	template<std::floating_point T, std::size_t Size>
	Vector<T, Size> ExtractScalingFromTrs(const Matrix<T, Size, Size + 1>& trsMatrix) noexcept
	{
		return ExtractScalingFromRs(ExtractRsMatrixFromTrs(trsMatrix));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Matrix<T, Size - 1, Size - 1> ExtractRsMatrixFromTrs(const Matrix<T, Size, Size>& trsMatrix) noexcept requires (Size > 1)
	{
		Matrix<T, Size - 1, Size - 1> rsMatrix;
		for (std::size_t i = 0uz; i < Size - 1; ++i)
		{
			const auto vector = Vector<T, Size - 1>(trsMatrix.Column(i).Span().subspan<0, Size - 1>());
			rsMatrix.Column(i, vector);
		}

		return rsMatrix;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Matrix<T, Size, Size> ExtractRsMatrixFromTrs(const Matrix<T, Size, Size + 1>& trsMatrix) noexcept
	{
		if consteval
		{
			Matrix<T, Size, Size> rsMatrix;
			for (std::size_t i = 0uz; i < Size; ++i)
			{
				rsMatrix.Column(i, trsMatrix.Column(i));
			}

			return rsMatrix;
		}
		else
		{
			return Matrix<T, Size, Size>(trsMatrix.Span().subspan<0, Size * Size>());
		}
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Matrix<T, Size - 1, Size> ExtractTrsMatrixFromTrs(const Matrix<T, Size, Size>& trsMatrix) noexcept requires (Size > 1)
	{
		Matrix<T, Size - 1, Size> trsMatrixCompact;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			const auto vector = Vector<T, Size - 1>(trsMatrix.Column(i).Span().subspan<0, Size - 1>());
			trsMatrixCompact.Column(i, vector);
		}

		return trsMatrixCompact;
	}

	template<std::floating_point T>
	T ExtractFov(const Matrix4x4<T>& perspectiveMatrix) noexcept
	{
		const T fovTan = T{1} / perspectiveMatrix[1, 1];

		return std::atan(fovTan) * T{2};
	}

	template<std::floating_point T>
	constexpr T ExtractWidth(const Matrix4x4<T>& orthographicMatrix) noexcept
	{
		return T{2} / orthographicMatrix[0, 0];
	}

	template<std::floating_point T>
	constexpr T ExtractHeight(const Matrix4x4<T>& orthographicMatrix) noexcept
	{
		return T{2} / orthographicMatrix[1, 1];
	}

	template<std::floating_point T>
	constexpr T ExtractAspect(const Matrix4x4<T>& projectionMatrix) noexcept
	{
		return projectionMatrix[1, 1] / projectionMatrix[0, 0];
	}

	template<std::floating_point T>
	constexpr T ExtractNearPlane(const Matrix4x4<T>& projectionMatrix) noexcept
	{
		return -projectionMatrix[2, 3] / projectionMatrix[2, 2];
	}

	template<std::floating_point T>
	constexpr T ExtractFarPlanePerspective(const Matrix4x4<T>& perspectiveMatrix) noexcept
	{
		return -perspectiveMatrix[2, 3] / (perspectiveMatrix[2, 3] - T{1});
	}

	template<std::floating_point T>
	constexpr T ExtractFarPlaneOrthographic(const Matrix4x4<T>& orthographicMatrix) noexcept
	{
		return (T{1} - orthographicMatrix[2, 3]) / orthographicMatrix[2, 2];
	}

	template<std::floating_point T>
	Vector2<T> Rotate(const Vector2<T>& vector, const T angle) noexcept
	{
		return RotationMatrix(angle) * vector;
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

	template<bool PerspectiveDivision, std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size> TransformPoint(const Matrix<T, Size + 1, Size + 1>& transformationMatrix, const Vector<T, Size>& vector) noexcept
	{
		const Vector<T, Size + 1> homogeneous = transformationMatrix * CreateHomogeneous(vector, T{1});
		auto transformed =  Vector<T, Size>(homogeneous.Span().subspan<0, Size>());
		if constexpr (PerspectiveDivision)
		{
			transformed *= T{1} / homogeneous[Size];
		}

		return transformed;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size> TransformPoint(const Matrix<T, Size, Size + 1>& transformationMatrix, const Vector<T, Size>& vector) noexcept
	{
		return transformationMatrix * CreateHomogeneous(vector, T{1});
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size> TransformDirection(const Matrix<T, Size + 1, Size + 1>& transformationMatrix, const Vector<T, Size>& vector) noexcept
	{
		const Vector<T, Size + 1> homogeneous = transformationMatrix * CreateHomogeneous(vector, T{0});

		return Vector<T, Size>(homogeneous.Span().subspan<0, Size>());
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size> TransformDirection(const Matrix<T, Size, Size + 1>& transformationMatrix, const Vector<T, Size>& vector) noexcept
	{
		return transformationMatrix * CreateHomogeneous(vector, T{0});
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size + 1> TransformHomogeneous(const Matrix<T, Size + 1, Size + 1>& transformationMatrix, const Vector<T, Size>& vector, const T homogeneousComponent) noexcept
	{
		return transformationMatrix * CreateHomogeneous(vector, homogeneousComponent);
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size> TransformHomogeneous(const Matrix<T, Size, Size + 1>& transformationMatrix, const Vector<T, Size>& vector, const T homogeneousComponent) noexcept
	{
		return transformationMatrix * CreateHomogeneous(vector, homogeneousComponent);
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size + 1> CreateHomogeneous(const Vector<T, Size>& vector, const T homogeneousComponent) noexcept
	{
		Vector<T, Size + 1> homogeneous;
		std::ranges::copy(vector.Span(), homogeneous.Span().begin());
		homogeneous[Size] = homogeneousComponent;

		return homogeneous;
	}

	template<std::floating_point T>
	Matrix3x3<T> LookIn(const Vector3<T>& forward, const Vector3<T>& up) noexcept
	{
		const Vector3<T> right = Cross(up, forward).Normalized();
		const Vector3<T> trueUp = Cross(forward, right);

		return Matrix3x3<T>(right, trueUp, forward);
	}
}
