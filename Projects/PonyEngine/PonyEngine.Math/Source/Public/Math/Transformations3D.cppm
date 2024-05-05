/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Transformations3D;

import <cmath>;
import <type_traits>;
import <utility>;

import :Matrix3x3;
import :Matrix4x4;
import :Quaternion;
import :Vector3;
import :Vector4;

export namespace PonyEngine::Math
{
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> Rotation(const Matrix3x3<T>& rotationMatrix) noexcept;
	/// @brief Creates a rotation quaternion by Euler angles. The rotation order is ZXY.
	/// @param euler Rotations in radians around x, y and z axis component-wise.
	/// @return Created quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> Rotation(const Vector3<T>& euler) noexcept;
	/// @brief Creates a rotation quaternion by the rotation of @p angle around the @p axis.
	/// @param axis Rotation axis. Must be normalized.
	/// @param angle Rotation angle in radians.
	/// @return Created quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> Rotation(const Vector3<T>& axis, T angle) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> Rotation(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RotationMatrix(const Quaternion<T>& quaternion) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RotationMatrix(const Vector3<T>& euler) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RotationMatrix(const Vector3<T>& axis, T angle) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RotationMatrix(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept;

	/// @brief Computes Euler angles. The rotation order is ZXY.
	///	@param quaternion Rotation.
	/// @return Euler angles in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Euler(const Quaternion<T>& quaternion) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Euler(const Matrix3x3<T>& rotationMatrix) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Euler(const Vector3<T>& axis, T angle) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Euler(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept;

	/// @brief Computes a rotation axis and angle.
	///	@param quaternion Rotation.
	/// @return Axis and angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> AxisAngle(const Quaternion<T>& quaternion) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> AxisAngle(const Matrix3x3<T>& rotationMatrix) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> AxisAngle(const Vector3<T>& euler) noexcept;
	/// @brief Computes an axis and an angle of a rotation from @p fromDirection to @p toDirection.
	/// @tparam T Component type.
	/// @param fromDirection From direction. Must be normalized.
	/// @param toDirection To direction. Must be normalized.
	/// @return Axis and angle of a rotation.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> AxisAngle(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RsMatrix(const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RsMatrix(const Matrix3x3<T>& rotationMatrix, const Vector3<T>& scaling) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RsMatrix(const Vector3<T>& euler, const Vector3<T>& scaling) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RsMatrix(const Vector3<T>& axis, T angle, const Vector3<T>& scaling) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Matrix3x3<T>& rotationMatrix, const Vector3<T>& scaling) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Vector3<T>& euler, const Vector3<T>& scaling) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Vector3<T>& axis, T angle, const Vector3<T>& scaling) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix4x4<T> TrsMatrix(const Matrix3x3<T>& rsMatrix) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Matrix3x3<T>& rsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> ExtractTranslationFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> ExtractRotationFromRsMatrix(const Matrix3x3<T>& rsMatrix) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> ExtractRotationFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> ExtractRotationMatrixFromRsMatrix(const Matrix3x3<T>& rsMatrix) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> ExtractRotationMatrixFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> ExtractEulerFromRsMatrix(const Matrix3x3<T>& rsMatrix) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> ExtractEulerFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> ExtractAxisAngleFromRsMatrix(const Matrix3x3<T>& rsMatrix) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> ExtractAxisAngleFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> ExtractScalingFromRsMatrix(const Matrix3x3<T>& rsMatrix) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> ExtractScalingFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> ExtractRsMatrixFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Rotate(const Vector3<T>& vector, const Vector3<T>& euler) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Rotate(const Vector3<T>& vector, const Vector3<T>& axis, T angle) noexcept;
}

namespace PonyEngine::Math
{
	template<std::floating_point T>
	Quaternion<T> Rotation(const Matrix3x3<T>& rotationMatrix) noexcept
	{
		Quaternion<T> quaternion;
		const T trace = rotationMatrix.Trace();

		if (trace > T{0}) [[likely]]
		{
			const T s = std::sqrt(trace + T{1}) * T{2};
			const T inverseS = T{1} / s;

			quaternion.X() = (rotationMatrix.M21() - rotationMatrix.M12()) * inverseS;
			quaternion.Y() = (rotationMatrix.M02() - rotationMatrix.M20()) * inverseS;
			quaternion.Z() = (rotationMatrix.M10() - rotationMatrix.M01()) * inverseS;
			quaternion.W() = s * T{0.25};
		}
		else if (rotationMatrix.M00() > rotationMatrix.M11() && rotationMatrix.M00() > rotationMatrix.M22()) [[unlikely]]
		{
			const T s = std::sqrt(T{1} + rotationMatrix.M00() - rotationMatrix.M11() - rotationMatrix.M22()) * T{2};
			const T inverseS = T{1} / s;

			quaternion.X() = s * T{0.25};
			quaternion.Y() = (rotationMatrix.M01() + rotationMatrix.M10()) * inverseS;
			quaternion.Z() = (rotationMatrix.M02() + rotationMatrix.M20()) * inverseS;
			quaternion.W() = (rotationMatrix.M21() - rotationMatrix.M12()) * inverseS;
		}
		else if (rotationMatrix.M11() > rotationMatrix.M22()) [[unlikely]]
		{
			const T s = std::sqrt(T{1} + rotationMatrix.M11() - rotationMatrix.M00() - rotationMatrix.M22()) * T{2};
			const T inverseS = T{1} / s;

			quaternion.X() = (rotationMatrix.M01 + rotationMatrix.M10()) * inverseS;
			quaternion.Y() = s * T{0.25};
			quaternion.Z() = (rotationMatrix.m12() + rotationMatrix.M21()) * inverseS;
			quaternion.W() = (rotationMatrix.M02() - rotationMatrix.M20()) * inverseS;
		}
		else [[unlikely]]
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
	Quaternion<T> Rotation(const Vector3<T>& euler) noexcept
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

		Quaternion<T> quaternion;
		quaternion.X() = xSin * yCos * zCos + xCos * ySin * zSin;
		quaternion.Y() = xCos * ySin * zCos - xSin * yCos * zSin;
		quaternion.Z() = xCos * yCos * zSin - xSin * ySin * zCos;
		quaternion.W() = xCos * yCos * zCos + xSin * ySin * zSin;

		return quaternion;
	}

	template<std::floating_point T>
	Quaternion<T> Rotation(const Vector3<T>& axis, const T angle) noexcept
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
	Quaternion<T> Rotation(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept
	{
		const std::pair<Vector3<T>, T> axisAngle = AxisAngle(fromDirection, toDirection);

		return Rotation(axisAngle.first, axisAngle.second);
	}

	template<std::floating_point T>
	Matrix3x3<T> RotationMatrix(const Quaternion<T>& quaternion) noexcept
	{
		const T xx = quaternion.X() * quaternion.X();
		const T xy = quaternion.X() * quaternion.Y();
		const T xz = quaternion.X() * quaternion.Z();
		const T xw = quaternion.W() * quaternion.W();

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
		rotationMatrix.M00() = yCos * zCos - xSin * ySin * zSin;
		rotationMatrix.M10() = yCos * zSin + xSin * ySin * zCos;
		rotationMatrix.M20() = -xCos * ySin;
		rotationMatrix.M01() = -xCos * zSin;
		rotationMatrix.M11() = xCos * zCos;
		rotationMatrix.M21() = xSin;
		rotationMatrix.M02() = ySin * zCos + xSin * yCos * zSin;
		rotationMatrix.M12() = ySin * zSin - xSin * yCos * zCos;
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
	Matrix3x3<T> RotationMatrix(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept
	{
		const std::pair<Vector3<T>, T> axisAngle = AxisAngle(fromDirection, toDirection);

		return RotationMatrix(axisAngle.first, axisAngle.second);
	}

	template<std::floating_point T>
	Vector3<T> Euler(const Quaternion<T>& quaternion) noexcept
	{
		const T halfSin = quaternion.X() * quaternion.W() - quaternion.Y() * quaternion.Z();

		Vector3<T> euler;

		if (std::abs(halfSin) > T{0.49999}) [[unlikely]] // singularity in the North Pole (+) or in the South Pole (-)
		{
			euler.X() = std::copysign(std::numbers::pi_v<T> * T{0.5}, halfSin);
			euler.Y() = std::copysign(T{2}, halfSin) * std::atan2(quaternion.Y(), quaternion.X());
			euler.Z() = T{0};
		}
		else [[likely]]
		{
			euler.X() = std::asin(T{2} * halfSin);
			euler.Y() = std::atan2(T{2} * (quaternion.Y() * quaternion.W() + quaternion.Z() * quaternion.X()), T{1} - T{2} * (quaternion.X() * quaternion.X() + quaternion.Y() * quaternion.Y()));
			euler.Z() = std::atan2(T{2} * (quaternion.Z() * quaternion.W() + quaternion.X() * quaternion.Y()), T{1} - T{2} * (quaternion.X() * quaternion.X() + quaternion.Z() * quaternion.Z()));
		}

		return euler;
	}

	template<std::floating_point T>
	Vector3<T> Euler(const Matrix3x3<T>& rotationMatrix) noexcept
	{
		Vector3<T> euler;

		if (std::abs(rotationMatrix.M21()) > T{0.99999}) [[unlikely]] // singularity in the North Pole (+) or in the South Pole (-)
		{
			euler.X() = std::copysign(std::numbers::pi_v<T> * T{0.5}, rotationMatrix.M21());
			euler.Y() = std::atan2(rotationMatrix.M10(), rotationMatrix.M00());
			euler.Z() = T{0};
		}
		else [[likely]]
		{
			euler.X() = std::asin(rotationMatrix.M21());
			euler.Y() = std::atan2(-rotationMatrix.M20(), rotationMatrix.M22());
			euler.Z() = std::atan2(-rotationMatrix.M01(), rotationMatrix.M11());
		}

		return euler;
	}

	template<std::floating_point T>
	Vector3<T> Euler(const Vector3<T>& axis, T angle) noexcept
	{
		return Euler(Rotation(axis, angle));
	}

	template<std::floating_point T>
	Vector3<T> Euler(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept
	{
		const std::pair<Vector3<T>, T> axisAngle = AxisAngle(fromDirection, toDirection);

		return Euler(axisAngle.first, axisAngle.second);
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> AxisAngle(const Quaternion<T>& quaternion) noexcept
	{
		const T halfAngle = std::acos(quaternion.W());

		std::pair<Vector3<T>, T> axisAngle;
		axisAngle.first = Vector3<T>(quaternion.X(), quaternion.Y(), quaternion.Z()) * (T{1} / std::sin(halfAngle));
		axisAngle.second = halfAngle * T{2};

		return axisAngle;
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> AxisAngle(const Matrix3x3<T>& rotationMatrix) noexcept
	{
		return AxisAngle(Rotation(rotationMatrix));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> AxisAngle(const Vector3<T>& euler) noexcept
	{
		return AxisAngle(Rotation(euler));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> AxisAngle(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept
	{
		const T dot = Dot(fromDirection, toDirection);

		std::pair<Vector3<T>, T> axisAngle;

		if (AreAlmostEqual(dot, T{1})) [[unlikely]]
		{
			axisAngle.first = Vector3<T>::Forward;
		}
		else if (AreAlmostEqual(dot, T{-1})) [[unlikely]]
		{
			axisAngle.first = std::abs(Dot(fromDirection, Vector3<T>::Up)) > T{0.5}
				? Cross(fromDirection, Vector3<T>::Forward)
				: Cross(fromDirection, Vector3<T>::Up);
		}
		else [[likely]]
		{
			axisAngle.first = Cross(fromDirection, toDirection);
		}
		axisAngle.first.Normalize();

		axisAngle.second = std::acos(dot);

		return axisAngle;
	}

	template<std::floating_point T>
	Matrix3x3<T> RsMatrix(const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept
	{
		return RsMatrix(RotationMatrix(quaternion), scaling);
	}

	template<std::floating_point T>
	Matrix3x3<T> RsMatrix(const Matrix3x3<T>& rotationMatrix, const Vector3<T>& scaling) noexcept
	{
		Matrix3x3<T> rsMatrix = rotationMatrix;
		for (std::size_t i = 0; i < Matrix3x3<T>::Dimension; ++i)
		{
			rsMatrix.SetColumn(i, rotationMatrix.GetColumn(i) * scaling[i]);
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
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Quaternion<T>& quaternion, const Vector3<T>& scaling) noexcept
	{
		return TrsMatrix(translation, RsMatrix(quaternion, scaling));
	}

	template<std::floating_point T>
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Matrix3x3<T>& rotationMatrix, const Vector3<T>& scaling) noexcept
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
	Matrix4x4<T> TrsMatrix(const Matrix3x3<T>& rsMatrix) noexcept
	{
		Matrix4x4<T> trsMatrix = Matrix4x4Identity<T>;
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
	Matrix4x4<T> TrsMatrix(const Vector3<T>& translation, const Matrix3x3<T>& rsMatrix) noexcept
	{
		Matrix4x4<T> trsMatrix = TrsMatrix(rsMatrix);
		trsMatrix.M03() = translation.X();
		trsMatrix.M13() = translation.Y();
		trsMatrix.M23() = translation.Z();

		return trsMatrix;
	}

	template<std::floating_point T>
	Vector3<T> ExtractTranslationFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return Vector3<T>(trsMatrix.M03(), trsMatrix.M13(), trsMatrix.M23());
	}

	template<std::floating_point T>
	Quaternion<T> ExtractRotationFromRsMatrix(const Matrix3x3<T>& rsMatrix) noexcept
	{
		return Rotation(ExtractRotationMatrixFromRsMatrix(rsMatrix));
	}

	template<std::floating_point T>
	Quaternion<T> ExtractRotationFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return Rotation(ExtractRotationMatrixFromTrsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	Matrix3x3<T> ExtractRotationMatrixFromRsMatrix(const Matrix3x3<T>& rsMatrix) noexcept
	{
		const Vector3<T> scaling = ExtractScalingFromRsMatrix(rsMatrix);
		Matrix3x3<T> scalingMatrix = Matrix3x3Identity<T>;
		scalingMatrix.SetDiagonal(scaling);

		return rsMatrix * scalingMatrix.Inverse();
	}

	template<std::floating_point T>
	Matrix3x3<T> ExtractRotationMatrixFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return ExtractRotationMatrixFromRsMatrix(ExtractRsMatrixFromTrsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	Vector3<T> ExtractEulerFromRsMatrix(const Matrix3x3<T>& rsMatrix) noexcept
	{
		return Euler(ExtractRotationMatrixFromRsMatrix(rsMatrix));
	}

	template<std::floating_point T>
	Vector3<T> ExtractEulerFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return Euler(ExtractRotationMatrixFromTrsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> ExtractAxisAngleFromRsMatrix(const Matrix3x3<T>& rsMatrix) noexcept
	{
		return AxisAngle(ExtractRotationMatrixFromRsMatrix(rsMatrix));
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> ExtractAxisAngleFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return AxisAngle(ExtractRotationMatrixFromTrsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	Vector3<T> ExtractScalingFromRsMatrix(const Matrix3x3<T>& rsMatrix) noexcept
	{
		Vector3<T> scaling;
		for (std::size_t i = 0; i < Matrix3x3<T>::Dimension; ++i)
		{
			scaling[i] = rsMatrix.GetColumn(i).Magnitude();
		}

		return scaling;
	}

	template<std::floating_point T>
	Vector3<T> ExtractScalingFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return ExtractScalingFromRsMatrix(ExtractRsMatrixFromTrsMatrix(trsMatrix));
	}

	template<std::floating_point T>
	Matrix3x3<T> ExtractRsMatrixFromTrsMatrix(const Matrix4x4<T>& trsMatrix) noexcept
	{
		return Matrix3x3<T>(trsMatrix.M00(), trsMatrix.M10(), trsMatrix.M20(), trsMatrix.M01(), trsMatrix.M11(), trsMatrix.M21(), trsMatrix.M02(), trsMatrix.M12(), trsMatrix.M22());
	}

	template<std::floating_point T>
	Vector3<T> Rotate(const Vector3<T>& vector, const Vector3<T>& euler) noexcept
	{
		return RotationMatrix(euler) * vector;
	}

	template<std::floating_point T>
	Vector3<T> Rotate(const Vector3<T>& vector, const Vector3<T>& axis, const T angle) noexcept
	{
		const T sin = std::sin(angle);
		const T cos = std::cos(angle);
		const T mCos = T{1} - cos;
		const T dot = Dot(axis, vector);
		const T cross = Cross(axis, vector);

		return vector * cos + cross * sin + axis * (dot * mCos);
	}
}
