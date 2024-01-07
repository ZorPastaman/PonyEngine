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
	export template<Arithmetic T>
	struct Vector3 final
	{
	public:
		using ValueType = T;
		using ComputationalType = ComputationalFor<T>;

		constexpr Vector3() noexcept;
		constexpr Vector3(const T xParam, const T yParam, const T zParam) noexcept;
		constexpr Vector3(const Vector3& other) noexcept;

		constexpr ~Vector3() noexcept = default;

		constexpr inline ComputationalType Magnitude() const noexcept;
		constexpr inline ComputationalType MagnitudeSquared() const noexcept;

		constexpr Vector3 Normalized() const noexcept;
		constexpr inline void Normalize() noexcept;

		constexpr void Set(const T xParam, const T yParam, const T zParam) noexcept;

		constexpr Vector3& operator =(const Vector3& other) noexcept;
		constexpr Vector3& operator +=(const Vector3& other) noexcept;
		constexpr Vector3& operator -=(const Vector3& other) noexcept;
		constexpr Vector3& operator *=(const ComputationalType multiplier) noexcept;
		constexpr Vector3& operator *=(const Vector3& other) noexcept;
		constexpr Vector3& operator /=(const ComputationalType divisor) noexcept;
		constexpr Vector3& operator /=(const Vector3& other) noexcept;

		static const Vector3 Forward;
		static const Vector3 Back;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Right;
		static const Vector3 Left;
		static const Vector3 One;
		static const Vector3 Zero;
		static const Vector3 Negative;

		T x;
		T y;
		T z;
	};

	export template<Arithmetic T>
	constexpr Vector3<T>::ComputationalType Dot(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return static_cast<Vector3<T>::ComputationalType>(left.x) * static_cast<Vector3<T>::ComputationalType>(right.x) +
			static_cast<Vector3<T>::ComputationalType>(left.y) * static_cast<Vector3<T>::ComputationalType>(right.y) +
			static_cast<Vector3<T>::ComputationalType>(left.z) * static_cast<Vector3<T>::ComputationalType>(right.z);
	}

	export template<Arithmetic T>
	constexpr Vector3<T> Cross(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.y) * static_cast<Vector3<T>::ComputationalType>(right.z) - 
			static_cast<Vector3<T>::ComputationalType>(left.z) * static_cast<Vector3<T>::ComputationalType>(right.y));
		const T y = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.z) * static_cast<Vector3<T>::ComputationalType>(right.x) - 
			static_cast<Vector3<T>::ComputationalType>(left.x) * static_cast<Vector3<T>::ComputationalType>(right.z));
		const T z = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.x) * static_cast<Vector3<T>::ComputationalType>(right.y) - 
			static_cast<Vector3<T>::ComputationalType>(left.y) * static_cast<Vector3<T>::ComputationalType>(right.x));

		return Vector3(x, y, z);
	}

	export template<Arithmetic T>
	constexpr Vector3<T>::ComputationalType Angle(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const Vector3<T>::ComputationalType dot = Dot(left, right);
		const Vector3<T>::ComputationalType superMagnitude = sqrt(left.MagnitudeSquared() * right.MagnitudeSquared());
		const Vector3<T>::ComputationalType cos = std::clamp(dot / superMagnitude, 
			typename Vector3<T>::ComputationalType{-1}, typename Vector3<T>::ComputationalType{1});

		return std::acos(cos);
	}

	export template<Arithmetic T>
	constexpr Vector3<T>::ComputationalType AngleSigned(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept
	{
		const Vector3 cross = Cross(left, right);
		const Vector3<T>::ComputationalType dot = Dot(cross, axis);
		const Vector3<T>::ComputationalType sign = Sign(dot);
		const Vector3<T>::ComputationalType angle = Angle(left, right);

		return angle * sign;
	}

	export template<Arithmetic T>
	constexpr inline Vector3<T>::ComputationalType AngleDegrees(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Angle(left, right) * RadToDeg<Vector3<T>::ComputationalType>;
	}

	export template<Arithmetic T>
	constexpr inline Vector3<T>::ComputationalType AngleSignedDegrees(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept
	{
		return AngleSigned(left, right, axis) * RadToDeg<Vector3<T>::ComputationalType>;
	}

	export template<Arithmetic T>
	constexpr Vector3<T> Project(const Vector3<T>& vector, const Vector3<T>& target) noexcept
	{
		const Vector3<T>::ComputationalType multiplier = Dot(vector, target) / Dot(target, target);

		return target * multiplier;
	}

	export template<Arithmetic T>
	constexpr Vector3<T> ProjectOnPlane(const Vector3<T>& vector, const Vector3<T>& normal) noexcept
	{
		const Vector3<T>::ComputationalType multiplier = Dot(vector, normal) / Dot(normal, normal);

		return vector - normal * multiplier;
	}

	export template<Arithmetic T>
	constexpr Vector3<T> Reflect(const Vector3<T>& vector, const Vector3<T>& normal) noexcept
	{
		const Vector3<T>::ComputationalType multiplier = typename Vector3<T>::ComputationalType{-2} * Dot(vector, normal) / Dot(normal, normal);

		return vector + normal * multiplier;
	}

	export template<Arithmetic T>
	constexpr bool operator ==(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}

	export template<Arithmetic T>
	constexpr bool operator !=(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return left.x != right.x || left.y != right.y || left.z != right.z;
	}

	export template<Arithmetic T>
	constexpr Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Vector3(static_cast<T>(left.x + right.x), static_cast<T>(left.y + right.y), static_cast<T>(left.z + right.z));
	}

	export template<Arithmetic T>
	constexpr Vector3<T> operator -(const Vector3<T>& vector) noexcept
	{
		return Vector3(static_cast<T>(-vector.x), static_cast<T>(-vector.y), static_cast<T>(-vector.z));
	}

	export template<Arithmetic T>
	constexpr Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Vector3(static_cast<T>(left.x - right.x), static_cast<T>(left.y - right.y), static_cast<T>(left.z - right.z));
	}

	export template<Arithmetic T>
	constexpr Vector3<T> operator *(const Vector3<T>& vector, const typename Vector3<T>::ComputationalType multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(vector.x) * multiplier);
		const T y = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(vector.y) * multiplier);
		const T z = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(vector.z) * multiplier);

		return Vector3(x, y, z);
	}

	export template<Arithmetic T>
	constexpr inline Vector3<T> operator *(const typename Vector3<T>::ComputationalType multiplier, const Vector3<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	export template<Arithmetic T>
	constexpr Vector3<T> operator *(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.x) * static_cast<Vector3<T>::ComputationalType>(right.x));
		const T y = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.y) * static_cast<Vector3<T>::ComputationalType>(right.y));
		const T z = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.z) * static_cast<Vector3<T>::ComputationalType>(right.z));

		return Vector3(x, y, z);
	}

	export template<Arithmetic T>
	constexpr Vector3<T> operator /(const Vector3<T>& vector, const typename Vector3<T>::ComputationalType divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(vector.x) / divisor);
		const T y = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(vector.y) / divisor);
		const T z = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(vector.z) / divisor);

		return Vector3(x, y, z);
	}

	export template<Arithmetic T>
	constexpr Vector3<T> operator /(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.x) / static_cast<Vector3<T>::ComputationalType>(right.x));
		const T y = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.y) / static_cast<Vector3<T>::ComputationalType>(right.y));
		const T z = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.z) / static_cast<Vector3<T>::ComputationalType>(right.z));

		return Vector3(x, y, z);
	}

	template<Arithmetic T>
	constexpr Vector3<T>::Vector3() noexcept :
		x{},
		y{},
		z{}
	{
	}

	template<Arithmetic T>
	constexpr Vector3<T>::Vector3(const T xParam, const T yParam, const T zParam) noexcept :
		x{xParam},
		y{yParam},
		z{zParam}
	{
	}

	template<Arithmetic T>
	constexpr Vector3<T>::Vector3(const Vector3<T>& other) noexcept : 
		Vector3(other.x, other.y, other.z)
	{
	}

	template<Arithmetic T>
	constexpr inline Vector3<T>::ComputationalType Vector3<T>::Magnitude() const noexcept
	{
		return std::sqrt(MagnitudeSquared());
	}

	template<Arithmetic T>
	constexpr inline Vector3<T>::ComputationalType Vector3<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T>
	constexpr Vector3<T> Vector3<T>::Normalized() const noexcept
	{
		return *this / Magnitude();
	}

	template<Arithmetic T>
	constexpr inline void Vector3<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	constexpr void Vector3<T>::Set(const T xParam, const T yParam, const T zParam) noexcept
	{
		x = xParam;
		y = yParam;
		z = zParam;
	}

	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator =(const Vector3<T>& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator +=(const Vector3<T>& other) noexcept
	{
		x = static_cast<T>(x + other.x);
		y = static_cast<T>(y + other.y);
		z = static_cast<T>(z + other.z);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator -=(const Vector3<T>& other) noexcept
	{
		x = static_cast<T>(x - other.x);
		y = static_cast<T>(y - other.y);
		z = static_cast<T>(z - other.z);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) * multiplier);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) * multiplier);
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) * multiplier);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator *=(const Vector3& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) * static_cast<ComputationalType>(other.x));
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) * static_cast<ComputationalType>(other.y));
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) * static_cast<ComputationalType>(other.z));

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator /=(const ComputationalType divisor) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / divisor);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / divisor);
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) / divisor);

		return *this;
	}
	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator /=(const Vector3& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / static_cast<ComputationalType>(other.x));
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / static_cast<ComputationalType>(other.y));
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) / static_cast<ComputationalType>(other.z));

		return *this;
	}

	template<Arithmetic T>
	const Vector3<T> Vector3<T>::Forward = Vector3<T>(T{0}, T{0}, T{1});
	template<Arithmetic T>
	const Vector3<T> Vector3<T>::Back = Vector3<T>(T{0}, T{0}, T{-1});
	template<Arithmetic T>
	const Vector3<T> Vector3<T>::Up = Vector3<T>(T{0}, T{1}, T{0});
	template<Arithmetic T>
	const Vector3<T> Vector3<T>::Down = Vector3<T>(T{0}, T{-1}, T{0});
	template<Arithmetic T>
	const Vector3<T> Vector3<T>::Right = Vector3<T>(T{1}, T{0}, T{0});
	template<Arithmetic T>
	const Vector3<T> Vector3<T>::Left = Vector3<T>(T{-1}, T{0}, T{0});
	template<Arithmetic T>
	const Vector3<T> Vector3<T>::One = Vector3<T>(T{1}, T{1}, T{1});
	template<Arithmetic T>
	const Vector3<T> Vector3<T>::Zero = Vector3<T>(T{0}, T{0}, T{0});
	template<Arithmetic T>
	const Vector3<T> Vector3<T>::Negative = Vector3<T>(T{-1}, T{-1}, T{-1});
}
