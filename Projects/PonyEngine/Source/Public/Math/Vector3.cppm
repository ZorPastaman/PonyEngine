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

import PonyEngine.Math.VectorConcepts;

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
		constexpr inline float MagnitudeSquare() const noexcept;

		constexpr Vector3 Normalized() const noexcept;
		constexpr inline void Normalize() noexcept;

		constexpr Vector3& operator =(const Vector3& other) noexcept;
		constexpr Vector3& operator +=(const Vector3& other) noexcept;
		constexpr Vector3& operator -=(const Vector3& other) noexcept;
		constexpr Vector3& operator *=(const float multiplier) noexcept;
		constexpr Vector3& operator /=(const float divisor) noexcept;

		T x;
		T y;
		T z;
	};

	export template<VectorComponent T>
	constexpr float Dot(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return static_cast<T>(static_cast<float>(left.x) * static_cast<float>(right.x) +
			static_cast<float>(left.y) * static_cast<float>(right.y) +
			static_cast<float>(left.z) * static_cast<float>(right.z));
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
	constexpr bool operator ==(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}

	export template<VectorComponent T>
	constexpr bool operator !=(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return left.x != right.x || left.y != right.y || left.z != right.z;
	}

	export template<VectorComponent T>
	constexpr Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	export template<VectorComponent T>
	constexpr Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
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
	constexpr Vector3<T> operator /(const Vector3<T>& vector, const float divisor) noexcept
	{
		const T x = static_cast<T>(static_cast<float>(vector.x) / divisor);
		const T y = static_cast<T>(static_cast<float>(vector.y) / divisor);
		const T z = static_cast<T>(static_cast<float>(vector.z) / divisor);
		return Vector3(x, y, z);
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
	constexpr Vector3<T> operator /(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const T x = static_cast<T>(static_cast<float>(left.x) / static_cast<float>(right.x));
		const T y = static_cast<T>(static_cast<float>(left.y) / static_cast<float>(right.y));
		const T z = static_cast<T>(static_cast<float>(left.z) / static_cast<float>(right.z));
		return Vector3(x, y, z);
	}

	template<VectorComponent T>
	constexpr Vector3<T>::Vector3() noexcept :
		x(),
		y(),
		z()
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
	constexpr Vector3<T>::Vector3(const Vector3<T>& other) noexcept : Vector3(other.x, other.y, other.z)
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
		return sqrt(MagnitudeSquare());
	}

	template<VectorComponent T>
	constexpr inline float Vector3<T>::MagnitudeSquare() const noexcept
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
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	template<VectorComponent T>
	constexpr Vector3<T>& Vector3<T>::operator -=(const Vector3<T>& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
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
	constexpr Vector3<T>& Vector3<T>::operator /=(const float divisor) noexcept
	{
		x = static_cast<T>(static_cast<float>(x) / divisor);
		y = static_cast<T>(static_cast<float>(y) / divisor);
		z = static_cast<T>(static_cast<float>(z) / divisor);
		return *this;
	}
}
