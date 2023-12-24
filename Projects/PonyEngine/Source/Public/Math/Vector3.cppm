/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math.Vector3;

import <utility>;
import <cmath>;
import <algorithm>;

import PonyEngine.Math.VectorConcepts;
import PonyEngine.Math.Common;

namespace PonyEngine::Math
{
	export template<VectorComponent T>
	struct Vector3 final
	{
	public:
		using value_type = T;

		constexpr Vector3() noexcept;
		constexpr Vector3(const T xParam, const T yParam, const T zParam) noexcept;
		constexpr Vector3(const Vector3& other) noexcept;
		constexpr Vector3(Vector3&& other) noexcept;

		constexpr ~Vector3() noexcept = default;

		constexpr float Magnitude() const noexcept;
		constexpr inline float MagnitudeSquared() const noexcept;

		constexpr Vector3 Normalized() const noexcept;
		constexpr inline void Normalize() noexcept;

		constexpr Vector3& operator =(const Vector3& other) noexcept;
		constexpr Vector3& operator +=(const Vector3& other) noexcept;
		constexpr Vector3& operator -=(const Vector3& other) noexcept;
		constexpr Vector3& operator *=(const float multiplier) noexcept;
		constexpr Vector3& operator *=(const Vector3& other) noexcept;
		constexpr Vector3& operator /=(const float divisor) noexcept;
		constexpr Vector3& operator /=(const Vector3& other) noexcept;

		T x;
		T y;
		T z;
	};

	export template<VectorComponent T>
	constexpr float Dot(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return static_cast<float>(left.x) * static_cast<float>(right.x) +
			static_cast<float>(left.y) * static_cast<float>(right.y) +
			static_cast<float>(left.z) * static_cast<float>(right.z);
	}

	export template<VectorComponent T>
	constexpr Vector3<T> Cross(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const T x = static_cast<T>(static_cast<float>(left.y) * static_cast<float>(right.z) - static_cast<float>(left.z) * static_cast<float>(right.y));
		const T y = static_cast<T>(static_cast<float>(left.z) * static_cast<float>(right.x) - static_cast<float>(left.x) * static_cast<float>(right.z));
		const T z = static_cast<T>(static_cast<float>(left.x) * static_cast<float>(right.y) - static_cast<float>(left.y) * static_cast<float>(right.x));
		return Vector3(x, y, z);
	}

	export template<VectorComponent T>
	constexpr float Angle(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const float dot = Dot(left, right);
		const float superMagnitude = sqrt(left.MagnitudeSquared() * right.MagnitudeSquared());
		const float cos = std::clamp(dot / superMagnitude, -1.f, 1.f);
		return std::acos(cos);
	}

	export template<VectorComponent T>
	constexpr float AngleSigned(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept
	{
		const Vector3 cross = Cross(left, right);
		const float dot = Dot(cross, axis);
		const float sign = Sign(dot);
		const float angle = Angle(left, right);
		return angle * sign;
	}

	export template<VectorComponent T>
	constexpr inline float AngleDegrees(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Angle(left, right) * RadToDeg;
	}

	export template<VectorComponent T>
	constexpr inline float AngleSignedDegrees(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept
	{
		return AngleSigned(left, right, axis) * RadToDeg;
	}

	export template<VectorComponent T>
	constexpr Vector3<T> Project(const Vector3<T>& vector, const Vector3<T>& target) noexcept
	{
		const float multiplier = Dot(vector, target) / Dot(target, target);
		return target * multiplier;
	}

	export template<VectorComponent T>
	constexpr Vector3<T> ProjectOnPlane(const Vector3<T>& vector, const Vector3<T>& normal) noexcept
	{
		const float multiplier = Dot(vector, normal) / Dot(normal, normal);
		return vector - normal * multiplier;
	}

	export template<VectorComponent T>
	constexpr Vector3<T> Reflect(const Vector3<T>& vector, const Vector3<T>& normal) noexcept
	{
		const float multiplier = -2.f * Dot(vector, normal);
		return vector + normal * multiplier;
	}

	export template<VectorComponent T>
	constexpr bool operator ==(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return static_cast<bool>(left.x == right.x) && static_cast<bool>(left.y == right.y) && static_cast<bool>(left.z == right.z);
	}

	export template<VectorComponent T>
	constexpr bool operator !=(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return static_cast<bool>(left.x != right.x) || static_cast<bool>(left.y != right.y) || static_cast<bool>(left.z != right.z);
	}

	export template<VectorComponent T>
	constexpr Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Vector3(static_cast<T>(left.x + right.x), static_cast<T>(left.y + right.y), static_cast<T>(left.z + right.z));
	}

	export template<VectorComponent T>
	constexpr Vector3<T> operator -(const Vector3<T>& vector) noexcept
	{
		return Vector3(static_cast<T>(-vector.x), static_cast<T>(-vector.y), static_cast<T>(-vector.z));
	}

	export template<VectorComponent T>
	constexpr Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Vector3(static_cast<T>(left.x - right.x), static_cast<T>(left.y - right.y), static_cast<T>(left.z - right.z));
	}

	export template<VectorComponent T>
	constexpr Vector3<T> operator *(const Vector3<T>& vector, const float multiplier) noexcept
	{
		const T x = static_cast<T>(static_cast<float>(vector.x) * multiplier);
		const T y = static_cast<T>(static_cast<float>(vector.y) * multiplier);
		const T z = static_cast<T>(static_cast<float>(vector.z) * multiplier);
		return Vector3(x, y, z);
	}

	export template<VectorComponent T>
	constexpr inline Vector3<T> operator *(const float multiplier, const Vector3<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	export template<VectorComponent T>
	constexpr Vector3<T> operator *(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const T x = static_cast<T>(static_cast<float>(left.x) * static_cast<float>(right.x));
		const T y = static_cast<T>(static_cast<float>(left.y) * static_cast<float>(right.y));
		const T z = static_cast<T>(static_cast<float>(left.z) * static_cast<float>(right.z));
		return Vector3(x, y, z);
	}

	export template<VectorComponent T>
	constexpr Vector3<T> operator /(const Vector3<T>& vector, const float divisor) noexcept
	{
		const T x = static_cast<T>(static_cast<float>(vector.x) / divisor);
		const T y = static_cast<T>(static_cast<float>(vector.y) / divisor);
		const T z = static_cast<T>(static_cast<float>(vector.z) / divisor);
		return Vector3(x, y, z);
	}

	export template<VectorComponent T>
	constexpr Vector3<T> operator /(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const T x = static_cast<T>(static_cast<float>(left.x) / static_cast<float>(right.x));
		const T y = static_cast<T>(static_cast<float>(left.y) / static_cast<float>(right.y));
		const T z = static_cast<T>(static_cast<float>(left.z) / static_cast<float>(right.z));
		return Vector3(x, y, z);
	}

	template<VectorComponent T>
	constexpr Vector3<T>::Vector3() noexcept :
		x{},
		y{},
		z{}
	{
	}

	template<VectorComponent T>
	constexpr Vector3<T>::Vector3(const T xParam, const T yParam, const T zParam) noexcept :
		x(xParam),
		y(yParam),
		z(zParam)
	{
	}

	template<VectorComponent T>
	constexpr Vector3<T>::Vector3(const Vector3<T>& other) noexcept : 
		Vector3(other.x, other.y, other.z)
	{
	}

	template<VectorComponent T>
	constexpr Vector3<T>::Vector3(Vector3<T>&& other) noexcept :
		x(std::move(other.x)),
		y(std::move(other.y)),
		z(std::move(other.z))
	{
	}

	template<VectorComponent T>
	constexpr float Vector3<T>::Magnitude() const noexcept
	{
		return sqrt(MagnitudeSquared());
	}

	template<VectorComponent T>
	constexpr inline float Vector3<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<VectorComponent T>
	constexpr Vector3<T> Vector3<T>::Normalized() const noexcept
	{
		return *this / Magnitude();
	}

	template<VectorComponent T>
	constexpr inline void Vector3<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<VectorComponent T>
	constexpr Vector3<T>& Vector3<T>::operator =(const Vector3<T>& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	template<VectorComponent T>
	constexpr Vector3<T>& Vector3<T>::operator +=(const Vector3<T>& other) noexcept
	{
		x = static_cast<T>(x + other.x);
		y = static_cast<T>(y + other.y);
		z = static_cast<T>(z + other.z);
		return *this;
	}

	template<VectorComponent T>
	constexpr Vector3<T>& Vector3<T>::operator -=(const Vector3<T>& other) noexcept
	{
		x = static_cast<T>(x - other.x);
		y = static_cast<T>(y - other.y);
		z = static_cast<T>(z - other.z);
		return *this;
	}

	template<VectorComponent T>
	constexpr Vector3<T>& Vector3<T>::operator *=(const float multiplier) noexcept
	{
		x = static_cast<T>(static_cast<float>(x) * multiplier);
		y = static_cast<T>(static_cast<float>(y) * multiplier);
		z = static_cast<T>(static_cast<float>(z) * multiplier);
		return *this;
	}

	template<VectorComponent T>
	constexpr Vector3<T>& Vector3<T>::operator *=(const Vector3& other) noexcept
	{
		x = static_cast<T>(static_cast<float>(x) * static_cast<float>(other.x));
		y = static_cast<T>(static_cast<float>(y) * static_cast<float>(other.y));
		z = static_cast<T>(static_cast<float>(z) * static_cast<float>(other.z));
		return *this;
	}

	template<VectorComponent T>
	constexpr Vector3<T>& Vector3<T>::operator /=(const float divisor) noexcept
	{
		x = static_cast<T>(static_cast<float>(x) / divisor);
		y = static_cast<T>(static_cast<float>(y) / divisor);
		z = static_cast<T>(static_cast<float>(z) / divisor);
		return *this;
	}
	template<VectorComponent T>
	constexpr Vector3<T>& Vector3<T>::operator /=(const Vector3& other) noexcept
	{
		x = static_cast<T>(static_cast<float>(x) / static_cast<float>(other.x));
		y = static_cast<T>(static_cast<float>(y) / static_cast<float>(other.y));
		z = static_cast<T>(static_cast<float>(z) / static_cast<float>(other.z));
		return *this;
	}
}
