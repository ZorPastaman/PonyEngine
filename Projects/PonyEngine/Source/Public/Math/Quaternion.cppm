/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math.Quaternion;

import <concepts>;
import <cmath>;

import PonyEngine.Math.Common;
import PonyEngine.Math.Vector3;
import PonyEngine.Math.Vector4;

namespace PonyEngine::Math
{
	export template<std::floating_point T>
	struct Quaternion final
	{
	public:
		using ValueType = T;

		constexpr Quaternion() noexcept;
		constexpr Quaternion(const T xParam, const T yParam, const T zParam, const T wParam) noexcept;
		constexpr Quaternion(const Vector4<T>& vector) noexcept;
		constexpr Quaternion(const Quaternion<T>& other) noexcept;

		constexpr ~Quaternion() noexcept = default;

		static Quaternion<T> CreateByEuler(const T xRotation, const T yRotation, const T zRotation) noexcept;
		inline static Quaternion<T> CreateByEulerDegrees(const T xRotation, const T yRotation, const T zRotation) noexcept;
		inline static Quaternion<T> CreateByEuler(const Vector3<T>& rotation) noexcept;
		inline static Quaternion<T> CreateByEulerDegrees(const Vector3<T>& rotation) noexcept;
		static Quaternion<T> CreateByAxisAngle(const Vector3<T>& axis, const T angle) noexcept;
		inline static Quaternion<T> CreateByAxisAngleDegrees(const Vector3<T>& axis, const T angle) noexcept;
		static Quaternion<T> CreateByDirection(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept;

		inline T Magnitude() const noexcept;
		constexpr inline T MagnitudeSquared() const noexcept;

		constexpr inline Quaternion<T> Conjugated() const noexcept;
		inline void Conjugate() noexcept;

		Quaternion<T> Normalized() const noexcept;
		inline void Normalize() noexcept;

		Vector3<T> Euler() const noexcept;
		inline Vector3<T> EulerDegrees() const noexcept;

		std::pair<Vector3<T>, T> AxisAngle() const noexcept;
		inline std::pair<Vector3<T>, T> AxisAngleDegrees() const noexcept;

		inline void Set(const T xParam, const T yParam, const T zParam, const T wParam) noexcept;

		constexpr inline operator Vector4<T>() const noexcept;

		inline Quaternion<T>& operator =(const Quaternion<T>& other) noexcept;
		inline Quaternion<T>& operator *=(const Quaternion<T>& other) noexcept;

		static const Quaternion<T> Identity;

		T x;
		T y;
		T z;
		T w;
	};

	export template<std::floating_point T>
	constexpr T Dot(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
	}

	export template<std::floating_point T>
	T Angle(const Quaternion<T>& left, const Quaternion<T>& right) noexcept // Must be normalized
	{
		return T{2} * std::acos(Dot(left, right));
	}

	export template<std::floating_point T>
	inline T AngleDegrees(const Quaternion<T>& left, const Quaternion<T>& right) noexcept // Must be normalized
	{
		return Angle(left, right) * RadToDeg<T>;
	}

	export template<std::floating_point T>
	constexpr bool operator ==(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
	}

	export template<std::floating_point T>
	constexpr bool operator !=(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		return left.x != right.x || left.y != right.y || left.z != right.z || left.w != right.w;
	}

	export template<std::floating_point T>
	constexpr Quaternion<T> operator *(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		const T x = left.x * right.w + left.y * right.z - left.z * right.y + left.w * right.x;
		const T y = left.y * right.w + left.z * right.x - left.x * right.z + left.w * right.y;
		const T z = left.z * right.w + left.x * right.y - left.y * right.x + left.w * right.z;
		const T w = left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z;

		return Quaternion<T>(x, y, z, w);
	}

	export template<std::floating_point T>
	constexpr Vector3<T> operator *(const Quaternion<T>& quaternion, const Vector3<T>& vector) noexcept
	{
		const Vector3<T> u = Vector3<T>(quaternion.x, quaternion.y, quaternion.z);
		const Vector3<T> t = Cross(u, vector) * T{2};

		return vector + t * quaternion.w + Cross(u, t);
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::Quaternion() noexcept :
		x{},
		y{},
		z{},
		w{}
	{
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::Quaternion(const T xParam, const T yParam, const T zParam, const T wParam) noexcept :
		x{xParam},
		y{yParam},
		z{zParam},
		w{wParam}
	{
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::Quaternion(const Vector4<T>& vector) noexcept :
		Quaternion(vector.x, vector.y, vector.z, vector.w)
	{
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::Quaternion(const Quaternion<T>& other) noexcept :
		Quaternion(other.x, other.y, other.z, other.w)
	{
	}

	template<std::floating_point T>
	Quaternion<T> Quaternion<T>::CreateByEuler(const T xRotation, const T yRotation, const T zRotation) noexcept
	{
		const T xHalf = xRotation * T{0.5};
		const T yHalf = yRotation * T{0.5};
		const T zHalf = zRotation * T{0.5};

		const T xCos = std::cos(xHalf);
		const T yCos = std::cos(yHalf);
		const T zCos = std::cos(zHalf);

		const T xSin = std::sin(xHalf);
		const T ySin = std::sin(yHalf);
		const T zSin = std::sin(zHalf);

		const T x = xSin * yCos * zCos + xCos * ySin * zSin;
		const T y = xCos * ySin * zCos - xSin * yCos * zSin;
		const T z = xCos * yCos * zSin - xSin * ySin * zCos;
		const T w = xCos * yCos * zCos + xSin * ySin * zSin;

		return Quaternion<T>(x, y, z, w);
	}

	template<std::floating_point T>
	inline Quaternion<T> Quaternion<T>::CreateByEulerDegrees(const T xRotation, const T yRotation, const T zRotation) noexcept
	{
		return CreateByEuler(xRotation * DegToRad<T>, yRotation * DegToRad<T>, zRotation * DegToRad<T>);
	}

	template<std::floating_point T>
	inline Quaternion<T> Quaternion<T>::CreateByEuler(const Vector3<T>& rotation) noexcept
	{
		return CreateByEuler(rotation.x, rotation.y, rotation.z);
	}

	template<std::floating_point T>
	inline Quaternion<T> Quaternion<T>::CreateByEulerDegrees(const Vector3<T>& rotation) noexcept
	{
		return CreateByEuler(rotation.x * DegToRad<T>, rotation.y * DegToRad<T>, rotation.z * DegToRad<T>);
	}

	template<std::floating_point T>
	Quaternion<T> Quaternion<T>::CreateByAxisAngle(const Vector3<T>& axis, const T angle) noexcept // Must be normalized
	{
		const T angleHalf = angle * T{0.5};

		const T angleSin = std::sin(angleHalf);
		const T angleCos = std::cos(angleHalf);

		const T x = axis.x * angleSin;
		const T y = axis.y * angleSin;
		const T z = axis.z * angleSin;
		const T w = angleCos;

		return Quaternion<T>(x, y, z, w);
	}

	template<std::floating_point T>
	inline Quaternion<T> Quaternion<T>::CreateByAxisAngleDegrees(const Vector3<T>& axis, const T angle) noexcept // Must be normalized
	{
		return CreateByAxisAngle(axis, angle * DegToRad<T>);
	}

	template<std::floating_point T>
	Quaternion<T> Quaternion<T>::CreateByDirection(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept // Must be normalized
	{
		const T dot = static_cast<T>(Dot(fromDirection, toDirection));

		const Vector3<T> axis = dot < T{-0.9995}
			?  std::abs(Dot(fromDirection, Vector3<T>::Up)) > T{0.9995} 
				? Cross(fromDirection, Vector3<T>::Forward) 
				: Cross(fromDirection, Vector3<T>::Up)
			: Cross(fromDirection, toDirection);
		const T angle = std::acos(dot);

		return Quaternion::CreateByAxisAngle(axis, angle);
	} 

	template<std::floating_point T>
	inline T Quaternion<T>::Magnitude() const noexcept
	{
		return std::sqrt(MagnitudeSquared());
	}

	template<std::floating_point T>
	constexpr inline T Quaternion<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<std::floating_point T>
	constexpr inline Quaternion<T> Quaternion<T>::Conjugated() const noexcept
	{
		return Quaternion<T>(-x, -y, -z, w);
	}

	template<std::floating_point T>
	inline void Quaternion<T>::Conjugate() noexcept
	{
		*this = Conjugated();
	}

	template<std::floating_point T>
	Quaternion<T> Quaternion<T>::Normalized() const noexcept
	{
		const T inverseMagnitude = T{1} / Magnitude();

		return Quaternion<T>(x * inverseMagnitude, y * inverseMagnitude, z * inverseMagnitude, w * inverseMagnitude);
	}

	template<std::floating_point T>
	inline void Quaternion<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<std::floating_point T>
	Vector3<T> Quaternion<T>::Euler() const noexcept
	{
		const T halfSinp = (x * w - y * z);

		if (std::abs(halfSinp) > T{0.4995}) // singularity at north pole (+) or south pole (-)
		{
			const T xRotation = std::copysign(std::numbers::pi_v<T> * T{0.5}, halfSinp);
			const T yRotationRound = std::copysign(T{2}, halfSinp) * std::atan2(y, x);
			const T yRotationCorrection = std::copysign((std::abs(yRotationRound) > std::numbers::pi_v<T>) * std::numbers::pi_v<T> * T{2}, yRotationRound);
			const T yRotation = yRotationRound - yRotationCorrection;
			constexpr T zRotation = T{0};

			return Vector3<T>(xRotation, yRotation, zRotation);
		}
		else
		{
			const T xRotation = std::asin(T{2} * halfSinp);
			const T yRotation = std::atan2(T{2} * (y * w + z * x), T{1} - T{2} * (x * x + y * y));
			const T zRotation = std::atan2(T{2} * (z * w + x * y), T{1} - T{2} * (x * x + z * z));

			return Vector3<T>(xRotation, yRotation, zRotation);
		}
	}

	template<std::floating_point T>
	inline Vector3<T> Quaternion<T>::EulerDegrees() const noexcept
	{
		return Euler() * RadToDeg<T>;
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> Quaternion<T>::AxisAngle() const noexcept
	{
		const T halfAngle = std::acos(w);
		const T inverseAngleSin = T{1} / std::sin(halfAngle);

		const T angleCorrection = (halfAngle > std::numbers::pi_v<T> * T{0.5}) * std::numbers::pi_v<T>;
		const T angle = T{2} * (halfAngle - angleCorrection);

		const T xAxis = x * inverseAngleSin;
		const T yAxis = y * inverseAngleSin;
		const T zAxis = z * inverseAngleSin;

		const Vector3<T> axis = Vector3<T>(xAxis, yAxis, zAxis);

		return std::pair<Vector3<T>, T>(axis, angle);
	}

	template<std::floating_point T>
	inline std::pair<Vector3<T>, T> Quaternion<T>::AxisAngleDegrees() const noexcept
	{
		std::pair < Vector3<T>, T> axisAngle = AxisAngle();
		axisAngle.second *= RadToDeg<T>;

		return axisAngle;
	}

	template<std::floating_point T>
	inline void Quaternion<T>::Set(const T xParam, const T yParam, const T zParam, const T wParam) noexcept
	{
		x = xParam;
		y = yParam;
		z = zParam;
		w = wParam;
	}

	template<std::floating_point T>
	constexpr inline Quaternion<T>::operator Vector4<T>() const noexcept
	{
		return Vector4<T>(x, y, z, w);
	}

	template<std::floating_point T>
	inline Quaternion<T>& Quaternion<T>::operator =(const Quaternion<T>& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;

		return *this;
	}

	template<std::floating_point T>
	inline Quaternion<T>& Quaternion<T>::operator *=(const Quaternion<T>& other) noexcept
	{
		return *this = *this * other;
	}

	template<std::floating_point T>
	const Quaternion<T> Quaternion<T>::Identity = Quaternion<T>(T{0}, T{0}, T{0}, T{1});
}
