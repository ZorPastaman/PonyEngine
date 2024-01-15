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
		constexpr Quaternion(const Quaternion& other) noexcept;

		constexpr ~Quaternion() noexcept = default;

		constexpr static Quaternion CreateByEuler(const T xRotation, const T yRotation, const T zRotation) noexcept;
		constexpr inline static Quaternion CreateByEulerDegrees(const T xRotation, const T yRotation, const T zRotation) noexcept;
		constexpr inline static Quaternion CreateByEuler(const Vector3<T>& rotation) noexcept;
		constexpr inline static Quaternion CreateByEulerDegrees(const Vector3<T>& rotation) noexcept;
		constexpr static Quaternion CreateByAxisAngle(const Vector3<T>& axis, const T angle) noexcept;
		constexpr inline static Quaternion CreateByAxisAngleDegrees(const Vector3<T>& axis, const T angle) noexcept;
		constexpr static Quaternion CreateByDirection(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept;

		constexpr inline T Magnitude() const noexcept;
		constexpr inline T MagnitudeSquared() const noexcept;

		constexpr inline Quaternion Conjugated() const noexcept;
		constexpr inline void Conjugate() noexcept;

		constexpr Quaternion Normalized() const noexcept;
		constexpr inline void Normalize() noexcept;

		constexpr Vector3<T> Euler() const noexcept;
		constexpr inline Vector3<T> EulerDegrees() const noexcept;

		constexpr std::pair<Vector3<T>, T> AxisAngle() const noexcept;
		constexpr inline std::pair<Vector3<T>, T> AxisAngleDegrees() const noexcept;

		constexpr void Set(const T xParam, const T yParam, const T zParam, const T wParam) noexcept;

		constexpr operator Vector4<T>() const noexcept;

		constexpr Quaternion& operator =(const Quaternion& other) noexcept;
		constexpr Quaternion& operator *=(const Quaternion& other) noexcept;

		static const Quaternion Identity;

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
	constexpr T Angle(const Quaternion<T>& left, const Quaternion<T>& right) noexcept // Must be normalized
	{
		const T dot = Dot(left, right);

		return T{2} * std::acos(dot);
	}

	export template<std::floating_point T>
	constexpr inline T AngleDegrees(const Quaternion<T>& left, const Quaternion<T>& right) noexcept // Must be normalized
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
	constexpr Vector3<T> operator *(const Quaternion<T>& quaternion, const Vector3<T> vector) noexcept // Must be normalized
	{
		const Vector3<T> u = Vector3<T>(quaternion.x, quaternion.y, quaternion.z);
		const Vector3<T> t = Cross(u, vector) * T{2};

		return vector + quaternion.w * t + Cross(u, t);
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
	constexpr Quaternion<T>::Quaternion(const Quaternion& other) noexcept :
		x{other.x},
		y{other.y},
		z{other.z},
		w{other.w}
	{
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Quaternion<T>::CreateByEuler(const T xRotation, const T yRotation, const T zRotation) noexcept
	{
		const T xHalf = xRotation / T{2};
		const T yHalf = yRotation / T{2};
		const T zHalf = zRotation / T{2};

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

		return Quaternion(x, y, z, w);
	}

	template<std::floating_point T>
	constexpr inline Quaternion<T> Quaternion<T>::CreateByEulerDegrees(const T xRotation, const T yRotation, const T zRotation) noexcept
	{
		return CreateByEuler(xRotation * DegToRad<T>, yRotation * DegToRad<T>, zRotation * DegToRad<T>);
	}

	template<std::floating_point T>
	constexpr inline Quaternion<T> Quaternion<T>::CreateByEuler(const Vector3<T>& rotation) noexcept
	{
		return CreateByEuler(rotation.x, rotation.y, rotation.z);
	}

	template<std::floating_point T>
	constexpr inline Quaternion<T> Quaternion<T>::CreateByEulerDegrees(const Vector3<T>& rotation) noexcept
	{
		return CreateByEuler(rotation.x * DegToRad<T>, rotation.y * DegToRad<T>, rotation.z * DegToRad<T>);
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Quaternion<T>::CreateByAxisAngle(const Vector3<T>& axis, const T angle) noexcept // Must be normalized
	{
		const T angleHalf = angle / T{2};

		const T angleSin = std::sin(angleHalf);
		const T angleCos = std::cos(angleHalf);

		const T x = axis.x * angleSin;
		const T y = axis.y * angleSin;
		const T z = axis.z * angleSin;
		const T w = angleCos;

		return Quaternion(x, y, z, w);
	}

	template<std::floating_point T>
	constexpr inline Quaternion<T> Quaternion<T>::CreateByAxisAngleDegrees(const Vector3<T>& axis, const T angle) noexcept // Must be normalized
	{
		return CreateByAxisAngle(axis, angle * DegToRad<T>);
	}


	template<std::floating_point T>
	constexpr Quaternion<T> Quaternion<T>::CreateByDirection(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept // Must be normalized
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
	constexpr inline T Quaternion<T>::Magnitude() const noexcept
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
		return Quaternion(-x, -y, -z, w);
	}

	template<std::floating_point T>
	constexpr inline void Quaternion<T>::Conjugate() noexcept
	{
		*this = Conjugated();
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Quaternion<T>::Normalized() const noexcept
	{
		const T magnitude = Magnitude();

		return Quaternion(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
	}

	template<std::floating_point T>
	constexpr inline void Quaternion<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<std::floating_point T>
	constexpr Vector3<T> Quaternion<T>::Euler() const noexcept
	{
		const T halfSinp = (x * w - y * z);

		if (std::abs(halfSinp) > T{0.4995}) // singularity at north pole (+) or south pole (-)
		{
			const T xRotation = std::copysign(std::numbers::pi_v<T> / T{2}, halfSinp);
			const T yRotationRound = std::copysign(T{2}, halfSinp) * std::atan2(y, x);
			const T signedPi = std::copysign(std::numbers::pi_v<T>, yRotationRound);
			const T yRotation = std::fmod(yRotationRound + signedPi, T{2} * std::numbers::pi_v<T>) - signedPi;
			const T zRotation = T{0};

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
	constexpr inline Vector3<T> Quaternion<T>::EulerDegrees() const noexcept
	{
		return Euler() * RadToDeg<T>;
	}

	template<std::floating_point T>
	constexpr std::pair<Vector3<T>, T> Quaternion<T>::AxisAngle() const noexcept
	{
		const T halfAngle = std::acos(w);
		const T angleSin = std::sin(halfAngle);

		const T angleCorrection = (halfAngle > std::numbers::pi_v<T> / T{2}) * std::numbers::pi_v<T>;
		const T angle = T{2} * (halfAngle - angleCorrection);

		const T xAxis = x / angleSin;
		const T yAxis = y / angleSin;
		const T zAxis = z / angleSin;

		const Vector3<T> axis = Vector3<T>(xAxis, yAxis, zAxis);

		return std::pair<Vector3<T>, T>(axis, angle);
	}

	template<std::floating_point T>
	constexpr inline std::pair<Vector3<T>, T> Quaternion<T>::AxisAngleDegrees() const noexcept
	{
		std::pair < Vector3<T>, T> axisAngle = AxisAngle();
		axisAngle.second *= RadToDeg<T>;

		return axisAngle;
	}

	template<std::floating_point T>
	constexpr void Quaternion<T>::Set(const T xParam, const T yParam, const T zParam, const T wParam) noexcept
	{
		x = xParam;
		y = yParam;
		z = zParam;
		w = wParam;
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::operator Vector4<T>() const noexcept
	{
		return Vector4<T>(x, y, z, w);
	}

	template<std::floating_point T>
	constexpr Quaternion<T>& Quaternion<T>::operator =(const Quaternion& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;

		return *this;
	}

	template<std::floating_point T>
	constexpr Quaternion<T>& Quaternion<T>::operator *=(const Quaternion& other) noexcept
	{
		return *this = *this * other;
	}

	template<std::floating_point T>
	const Quaternion<T> Quaternion<T>::Identity = Quaternion<T>(T{0}, T{0}, T{0}, T{1});
}
