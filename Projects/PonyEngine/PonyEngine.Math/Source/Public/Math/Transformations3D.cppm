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

import :Matrix3x3;
import :Quaternion;
import :Vector3;

export namespace PonyEngine::Math
{
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
	Matrix3x3<T> RotationMatrix(const Quaternion<T>& quaternion) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RotationMatrix(const Vector3<T>& euler) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> RotationMatrix(const Vector3<T>& axis, T angle) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	Matrix3x3<T> ScalingMatrix(const Vector3<T>& scaling) noexcept;

	/// @brief Computes Euler angles. The rotation order is ZXY.
	///	@param quaternion Rotation.
	/// @return Euler angles in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Vector3<T> Euler(const Quaternion<T>& quaternion) noexcept;

	/// @brief Computes a rotation axis and angle.
	///	@param quaternion Rotation.
	/// @return Axis and angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> AxisAngle(const Quaternion<T>& quaternion) noexcept;
	/// @brief Computes an axis and an angle of a rotation from @p fromDirection to @p toDirection.
	/// @tparam T Component type.
	/// @param fromDirection From direction. Must be normalized.
	/// @param toDirection To direction. Must be normalized.
	/// @return Axis and angle of a rotation.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<Vector3<T>, T> AngleAxis(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept;
}

namespace PonyEngine::Math
{
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

		const T x = xSin * yCos * zCos + xCos * ySin * zSin;
		const T y = xCos * ySin * zCos - xSin * yCos * zSin;
		const T z = xCos * yCos * zSin - xSin * ySin * zCos;
		const T w = xCos * yCos * zCos + xSin * ySin * zSin;

		return Quaternion(x, y, z, w);
	}

	template<std::floating_point T>
	Quaternion<T> Rotation(const Vector3<T>& axis, const T angle) noexcept
	{
		const T angleHalf = angle * T{0.5};

		const T angleSin = std::sin(angleHalf);
		const T angleCos = std::cos(angleHalf);

		const T x = axis.X() * angleSin;
		const T y = axis.Y() * angleSin;
		const T z = axis.Z() * angleSin;
		const T w = angleCos;

		return Quaternion(x, y, z, w);
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

		const T ww = quaternion.W() * quaternion.W();

		const T inverse = T{1} / (xx + yy + zz + ww);
		const T inverse2 = T{2} *inverse;

		const T m00 = (xx - yy - zz + ww) * inverse;
		const T m10 = (xy + zw) * inverse2;
		const T m20 = (xz - yw) * inverse2;
		const T m01 = (xy - zw) * inverse2;
		const T m11 = (-xx + yy - zz + ww) * inverse;
		const T m21 = (yz + xw) * inverse2;
		const T m02 = (xz + yw) * inverse2;
		const T m12 = (yz - xw) * inverse2;
		const T m22 = (-xx - yy + zz + ww) * inverse;

		return Matrix3x3<T>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
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

		const T m00 = yCos * zCos - xSin * ySin * zSin;
		const T m10 = yCos * zSin + xSin * ySin * zCos;
		const T m20 = -xCos * ySin;
		const T m01 = -xCos * zSin;
		const T m11 = xCos * zCos;
		const T m21 = xSin;
		const T m02 = ySin * zCos + xSin * yCos * zSin;
		const T m12 = ySin * zSin - xSin * yCos * zCos;
		const T m22 = xCos * yCos;

		return Matrix3x3<T>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
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

		const T m00 = mxx + cos;
		const T m10 = mxy + sz;
		const T m20 = mxz - sy;
		const T m01 = mxy - sz;
		const T m11 = myy + cos;
		const T m21 = myz + sx;
		const T m02 = mxz + sy;
		const T m12 = myz - sx;
		const T m22 = mzz + cos;

		return Matrix3x3<T>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
	}

	template<std::floating_point T>
	Matrix3x3<T> ScalingMatrix(const Vector3<T>& scaling) noexcept
	{
		Matrix3x3<T> answer = Matrix3x3<T>::Identity;
		answer.M00() = scaling.X();
		answer.M11() = scaling.Y();
		answer.M22() = scaling.Z();

		return answer;
	}

	template<std::floating_point T>
	Vector3<T> Euler(const Quaternion<T>& quaternion) noexcept
	{
		const T halfSin = quaternion.X() * quaternion.W() - quaternion.Y() * quaternion.Z();

		if (std::abs(halfSin) > T{0.49999}) [[unlikely]] // singularity in the North Pole (+) or in the South Pole (-)
		{
			const T xRotation = std::copysign(std::numbers::pi_v<T> * T{0.5}, halfSin);
			const T yRotation = std::copysign(T{2}, halfSin) * std::atan2(quaternion.Y(), quaternion.X());
			constexpr T zRotation = T{0};

			return Vector3<T>(xRotation, yRotation, zRotation);
		}
		else [[likely]]
		{
			const T xRotation = std::asin(T{2} * halfSin);
			const T yRotation = std::atan2(T{2} * (quaternion.Y() * quaternion.W() + quaternion.Z() * quaternion.X()), T{1} - T{2} * (quaternion.X() * quaternion.X() + quaternion.Y() * quaternion.Y()));
			const T zRotation = std::atan2(T{2} * (quaternion.Z() * quaternion.W() + quaternion.X() * quaternion.Y()), T{1} - T{2} * (quaternion.X() * quaternion.X() + quaternion.Z() * quaternion.Z()));

			return Vector3<T>(xRotation, yRotation, zRotation);
		}
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> AxisAngle(const Quaternion<T>& quaternion) noexcept
	{
		const T halfAngle = std::acos(quaternion.W());

		const Vector3<T> axis = Vector3<T>(quaternion.X(), quaternion.Y(), quaternion.Z()) * (T{1} / std::sin(halfAngle));
		const T angle = T{2} * halfAngle;

		return std::pair<Vector3<T>, T>(axis, angle);
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> AngleAxis(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept
	{
		const T dot = Dot(fromDirection, toDirection);

		Vector3<T> axis;
		if (AreAlmostEqual(dot, T{-1}))
		{
			axis = std::abs(Dot(fromDirection, Vector3<T>::Up)) > T{0.5}
				? Cross(fromDirection, Vector3<T>::Forward)
				: Cross(fromDirection, Vector3<T>::Up);
		}
		else
		{
			axis = Cross(fromDirection, toDirection);
		}
		axis.Normalize();
		if (!axis.IsFinite())
		{
			axis = Vector3<T>::Forward;
		}

		const T angle = std::acos(dot);

		return std::pair(axis, angle);
	}
}
