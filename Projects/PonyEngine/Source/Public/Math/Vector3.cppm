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
import <concepts>;

import PonyEngine.Math.Common;

namespace PonyEngine::Math
{
	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>>
	struct Vector3 final
	{
	public:
		using value_type = T;
		using computational_type = U;

		constexpr Vector3() noexcept;
		constexpr Vector3(const T xParam, const T yParam, const T zParam) noexcept;
		constexpr Vector3(const Vector3& other) noexcept;

		constexpr ~Vector3() noexcept = default;

		constexpr U Magnitude() const noexcept;
		constexpr inline U MagnitudeSquared() const noexcept;

		constexpr Vector3 Normalized() const noexcept;
		constexpr inline void Normalize() noexcept;

		constexpr Vector3& Set(const T xParam, const T yParam, const T zParam) noexcept;

		constexpr Vector3& operator =(const Vector3& other) noexcept;
		constexpr Vector3& operator +=(const Vector3& other) noexcept;
		constexpr Vector3& operator -=(const Vector3& other) noexcept;
		constexpr Vector3& operator *=(const U multiplier) noexcept;
		constexpr Vector3& operator *=(const Vector3& other) noexcept;
		constexpr Vector3& operator /=(const U divisor) noexcept;
		constexpr Vector3& operator /=(const Vector3& other) noexcept;

		T x;
		T y;
		T z;
	};

	export template<Arithmetic T, std::floating_point U>
	constexpr U Dot(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		return static_cast<U>(left.x) * static_cast<U>(right.x) +
			static_cast<U>(left.y) * static_cast<U>(right.y) +
			static_cast<U>(left.z) * static_cast<U>(right.z);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U> Cross(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.y) * static_cast<U>(right.z) - static_cast<U>(left.z) * static_cast<U>(right.y));
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.z) * static_cast<U>(right.x) - static_cast<U>(left.x) * static_cast<U>(right.z));
		const T z = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.x) * static_cast<U>(right.y) - static_cast<U>(left.y) * static_cast<U>(right.x));
		return Vector3(x, y, z);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr U Angle(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		const U dot = Dot(left, right);
		const U superMagnitude = sqrt(left.MagnitudeSquared() * right.MagnitudeSquared());
		const U cos = std::clamp(dot / superMagnitude, U(-1), U(1));
		return std::acos(cos);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr U AngleSigned(const Vector3<T, U>& left, const Vector3<T, U>& right, const Vector3<T, U>& axis) noexcept
	{
		const Vector3 cross = Cross(left, right);
		const U dot = Dot(cross, axis);
		const U sign = Sign(dot);
		const U angle = Angle(left, right);
		return angle * sign;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr inline U AngleDegrees(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		return Angle(left, right) * RadToDeg<U>;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr inline U AngleSignedDegrees(const Vector3<T, U>& left, const Vector3<T, U>& right, const Vector3<T, U>& axis) noexcept
	{
		return AngleSigned(left, right, axis) * RadToDeg<U>;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U> Project(const Vector3<T, U>& vector, const Vector3<T, U>& target) noexcept
	{
		const U multiplier = Dot(vector, target) / Dot(target, target);
		return target * multiplier;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U> ProjectOnPlane(const Vector3<T, U>& vector, const Vector3<T, U>& normal) noexcept
	{
		const U multiplier = Dot(vector, normal) / Dot(normal, normal);
		return vector - normal * multiplier;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U> Reflect(const Vector3<T, U>& vector, const Vector3<T, U>& normal) noexcept
	{
		const U multiplier = U(-2) * Dot(vector, normal);
		return vector + normal * multiplier;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr bool operator ==(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr bool operator !=(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		return left.x != right.x || left.y != right.y || left.z != right.z;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U> operator +(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		return Vector3(static_cast<T>(left.x + right.x), static_cast<T>(left.y + right.y), static_cast<T>(left.z + right.z));
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U> operator -(const Vector3<T, U>& vector) noexcept
	{
		return Vector3(static_cast<T>(-vector.x), static_cast<T>(-vector.y), static_cast<T>(-vector.z));
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U> operator -(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		return Vector3(static_cast<T>(left.x - right.x), static_cast<T>(left.y - right.y), static_cast<T>(left.z - right.z));
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U> operator *(const Vector3<T, U>& vector, const U multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.x) * multiplier);
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.y) * multiplier);
		const T z = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.z) * multiplier);
		return Vector3(x, y, z);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr inline Vector3<T, U> operator *(const U multiplier, const Vector3<T, U>& vector) noexcept
	{
		return vector * multiplier;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U> operator *(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.x) * static_cast<U>(right.x));
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.y) * static_cast<U>(right.y));
		const T z = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.z) * static_cast<U>(right.z));
		return Vector3(x, y, z);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U> operator /(const Vector3<T, U>& vector, const U divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.x) / divisor);
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.y) / divisor);
		const T z = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.z) / divisor);
		return Vector3(x, y, z);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U> operator /(const Vector3<T, U>& left, const Vector3<T, U>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.x) / static_cast<U>(right.x));
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.y) / static_cast<U>(right.y));
		const T z = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.z) / static_cast<U>(right.z));
		return Vector3(x, y, z);
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U>::Vector3() noexcept :
		x{},
		y{},
		z{}
	{
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U>::Vector3(const T xParam, const T yParam, const T zParam) noexcept :
		x(xParam),
		y(yParam),
		z(zParam)
	{
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U>::Vector3(const Vector3<T, U>& other) noexcept : 
		Vector3(other.x, other.y, other.z)
	{
	}

	template<Arithmetic T, std::floating_point U>
	constexpr U Vector3<T, U>::Magnitude() const noexcept
	{
		return sqrt(MagnitudeSquared());
	}

	template<Arithmetic T, std::floating_point U>
	constexpr inline U Vector3<T, U>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U> Vector3<T, U>::Normalized() const noexcept
	{
		return *this / Magnitude();
	}

	template<Arithmetic T, std::floating_point U>
	constexpr inline void Vector3<T, U>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U>& Vector3<T, U>::Set(const T xParam, const T yParam, const T zParam) noexcept
	{
		x = xParam;
		y = yParam;
		z = zParam;
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U>& Vector3<T, U>::operator =(const Vector3<T, U>& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U>& Vector3<T, U>::operator +=(const Vector3<T, U>& other) noexcept
	{
		x = static_cast<T>(x + other.x);
		y = static_cast<T>(y + other.y);
		z = static_cast<T>(z + other.z);
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U>& Vector3<T, U>::operator -=(const Vector3<T, U>& other) noexcept
	{
		x = static_cast<T>(x - other.x);
		y = static_cast<T>(y - other.y);
		z = static_cast<T>(z - other.z);
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U>& Vector3<T, U>::operator *=(const U multiplier) noexcept
	{
		x = RoundToIntegralIfPossible<U, T>(static_cast<U>(x) * multiplier);
		y = RoundToIntegralIfPossible<U, T>(static_cast<U>(y) * multiplier);
		z = RoundToIntegralIfPossible<U, T>(static_cast<U>(z) * multiplier);
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U>& Vector3<T, U>::operator *=(const Vector3& other) noexcept
	{
		x = RoundToIntegralIfPossible<U, T>(static_cast<U>(x) * static_cast<U>(other.x));
		y = RoundToIntegralIfPossible<U, T>(static_cast<U>(y) * static_cast<U>(other.y));
		z = RoundToIntegralIfPossible<U, T>(static_cast<U>(z) * static_cast<U>(other.z));
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U>& Vector3<T, U>::operator /=(const U divisor) noexcept
	{
		x = RoundToIntegralIfPossible<U, T>(static_cast<U>(x) / divisor);
		y = RoundToIntegralIfPossible<U, T>(static_cast<U>(y) / divisor);
		z = RoundToIntegralIfPossible<U, T>(static_cast<U>(z) / divisor);
		return *this;
	}
	template<Arithmetic T, std::floating_point U>
	constexpr Vector3<T, U>& Vector3<T, U>::operator /=(const Vector3& other) noexcept
	{
		x = RoundToIntegralIfPossible<U, T>(static_cast<U>(x) / static_cast<U>(other.x));
		y = RoundToIntegralIfPossible<U, T >>(static_cast<U>(y) / static_cast<U>(other.y));
		z = RoundToIntegralIfPossible<U, T>(static_cast<U>(z) / static_cast<U>(other.z));
		return *this;
	}
}
