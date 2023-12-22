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
	export template<VectorComponent T, VectorComponentComputational<T> U = DefaultComputationalType<T>>
	struct Vector3 final
	{
	public:
		using value_type = T;
		using computational_type = U;

		constexpr Vector3() noexcept;
		constexpr Vector3(const T xParam, const T yParam, const T zParam) noexcept;
		constexpr Vector3(const Vector3& other) noexcept;
		constexpr Vector3(Vector3&& other) noexcept;

		constexpr ~Vector3() noexcept = default;

		constexpr U Magnitude() const noexcept;
		constexpr inline U MagnitudeSquare() const noexcept;

		constexpr Vector3 Normalized() const noexcept;
		constexpr inline void Normalize() noexcept;

		constexpr Vector3& operator =(const Vector3& other) noexcept;
		constexpr Vector3& operator +=(const Vector3& other) noexcept;
		constexpr Vector3& operator -=(const Vector3& other) noexcept;
		constexpr Vector3& operator *=(const U multiplier) noexcept;
		constexpr Vector3& operator /=(const U divisor) noexcept;

		T x;
		T y;
		T z;
	};

	export template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr U Dot(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		return static_cast<T>(static_cast<U>(left.x) * static_cast<U>(right.x)) +
			static_cast<T>(static_cast<U>(left.y) * static_cast<U>(right.y)) +
			static_cast<T>(static_cast<U>(left.z) * static_cast<U>(right.z));
	}

	export template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U> Cross(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		const T x = static_cast<T>(static_cast<U>(left.y) * static_cast<U>(right.z)) - static_cast<T>(static_cast<U>(left.z) * static_cast<U>(right.y));
		const T y = static_cast<T>(static_cast<U>(left.z) * static_cast<U>(right.x)) - static_cast<T>(static_cast<U>(left.x) * static_cast<U>(right.z));
		const T z = static_cast<T>(static_cast<U>(left.x) * static_cast<U>(right.y)) - static_cast<T>(static_cast<U>(left.y) * static_cast<U>(right.x));
		return Vector3(x, y, z);
	}

	export template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr bool operator ==(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}

	export template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr bool operator !=(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		return left.x != right.x || left.y != right.y || left.z != right.z;
	}

	export template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U> operator +(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	export template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U> operator -(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		return Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	export template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U> operator *(const Vector3<T, U>& vector, const U multiplier) noexcept
	{
		const T x = static_cast<T>(static_cast<U>(vector.x) * multiplier);
		const T y = static_cast<T>(static_cast<U>(vector.y) * multiplier);
		const T z = static_cast<T>(static_cast<U>(vector.z) * multiplier);
		return Vector3(x, y, z);
	}

	export template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr inline Vector3<T, U> operator *(const U multiplier, const Vector3<T, U>& vector) noexcept
	{
		return vector * multiplier;
	}

	export template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U> operator /(const Vector3<T, U>& vector, const U divisor) noexcept
	{
		const T x = static_cast<T>(static_cast<U>(vector.x) / divisor);
		const T y = static_cast<T>(static_cast<U>(vector.y) / divisor);
		const T z = static_cast<T>(static_cast<U>(vector.z) / divisor);
		return Vector3(x, y, z);
	}

	export template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U> operator *(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		const T x = static_cast<T>(static_cast<U>(left.x) * static_cast<U>(right.x));
		const T y = static_cast<T>(static_cast<U>(left.y) * static_cast<U>(right.y));
		const T z = static_cast<T>(static_cast<U>(left.z) * static_cast<U>(right.z));
		return Vector3(x, y, z);
	}

	export template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U> operator /(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		const T x = static_cast<T>(static_cast<U>(left.x) / static_cast<U>(right.x));
		const T y = static_cast<T>(static_cast<U>(left.y) / static_cast<U>(right.y));
		const T z = static_cast<T>(static_cast<U>(left.z) / static_cast<U>(right.z));
		return Vector3(x, y, z);
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U>::Vector3() noexcept :
		x(),
		y(),
		z()
	{
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U>::Vector3(const T xParam, const T yParam, const T zParam) noexcept :
		x(xParam),
		y(yParam),
		z(zParam)
	{
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U>::Vector3(const Vector3<T, U>& other) noexcept : Vector3(other.x, other.y, other.z)
	{
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U>::Vector3(Vector3<T, U>&& other) noexcept :
		x(std::move(other.x)),
		y(std::move(other.y)),
		z(std::move(other.z))
	{
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr U Vector3<T, U>::Magnitude() const noexcept
	{
		return sqrt(MagnitudeSquare());
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr inline U Vector3<T, U>::MagnitudeSquare() const noexcept
	{
		return Dot(*this, *this);
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U> Vector3<T, U>::Normalized() const noexcept
	{
		return *this / Magnitude();
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr inline void Vector3<T, U>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U>& Vector3<T, U>::operator =(const Vector3<T, U>& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U>& Vector3<T, U>::operator +=(const Vector3<T, U>& other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U>& Vector3<T, U>::operator -=(const Vector3<T, U>& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U>& Vector3<T, U>::operator *=(const U multiplier) noexcept
	{
		x = static_cast<T>(static_cast<U>(x) * multiplier);
		y = static_cast<T>(static_cast<U>(y) * multiplier);
		z = static_cast<T>(static_cast<U>(z) * multiplier);
		return *this;
	}

	template<VectorComponent T, VectorComponentComputational<T> U>
	constexpr Vector3<T, U>& Vector3<T, U>::operator /=(const U divisor) noexcept
	{
		x = static_cast<T>(static_cast<U>(x) / divisor);
		y = static_cast<T>(static_cast<U>(y) / divisor);
		z = static_cast<T>(static_cast<U>(z) / divisor);
		return *this;
	}
}
