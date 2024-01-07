/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math.Vector2;

import <utility>;
import <cmath>;
import <algorithm>;
import <concepts>;

import PonyEngine.Math.Common;

namespace PonyEngine::Math
{
	export template<Arithmetic T>
	struct Vector2 final
	{
	public:
		using ValueType = T;
		using ComputationalType = ComputationalFor<T>;

		constexpr Vector2() noexcept;
		constexpr Vector2(const T xParam, const T yParam) noexcept;
		constexpr Vector2(const Vector2& other) noexcept;

		constexpr ~Vector2() noexcept = default;

		constexpr inline ComputationalType Magnitude() const noexcept;
		constexpr inline ComputationalType MagnitudeSquared() const noexcept;

		constexpr Vector2 Normalized() const noexcept;
		constexpr inline void Normalize() noexcept;

		constexpr void Set(const T xParam, const T yParam) noexcept;

		constexpr Vector2& operator =(const Vector2& other) noexcept;
		constexpr Vector2& operator +=(const Vector2& other) noexcept;
		constexpr Vector2& operator -=(const Vector2& other) noexcept;
		constexpr Vector2& operator *=(const ComputationalType multiplier) noexcept;
		constexpr Vector2& operator *=(const Vector2& other) noexcept;
		constexpr Vector2& operator /=(const ComputationalType divisor) noexcept;
		constexpr Vector2& operator /=(const Vector2& other) noexcept;

		static const Vector2 Up;
		static const Vector2 Down;
		static const Vector2 Right;
		static const Vector2 Left;
		static const Vector2 One;
		static const Vector2 Zero;
		static const Vector2 Negative;

		T x;
		T y;
	};

	export template<Arithmetic T>
	constexpr Vector2<T>::ComputationalType Dot(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return static_cast<Vector2<T>::ComputationalType>(left.x) * static_cast<Vector2<T>::ComputationalType>(right.x) +
			static_cast<Vector2<T>::ComputationalType>(left.y) * static_cast<Vector2<T>::ComputationalType>(right.y);
	}

	export template<Arithmetic T>
	constexpr Vector2<T>::ComputationalType Angle(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		const Vector2<T>::ComputationalType dot = Dot(left, right);
		const Vector2<T>::ComputationalType superMagnitude = sqrt(left.MagnitudeSquared() * right.MagnitudeSquared());
		const Vector2<T>::ComputationalType cos = std::clamp(dot / superMagnitude, 
			typename Vector2<T>::ComputationalType{-1}, typename Vector2<T>::ComputationalType{1});

		return std::acos(cos);
	}

	export template<Arithmetic T>
	constexpr Vector2<T>::ComputationalType AngleSigned(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		const Vector2<T>::ComputationalType zCross = left.x * right.y - left.y * right.x;
		const Vector2<T>::ComputationalType sign = Sign(zCross);
		const Vector2<T>::ComputationalType angle = Angle(left, right);

		return angle * sign;
	}

	export template<Arithmetic T>
	constexpr inline Vector2<T>::ComputationalType AngleDegrees(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return Angle(left, right) * RadToDeg<Vector2<T>::ComputationalType>;
	}

	export template<Arithmetic T>
	constexpr inline Vector2<T>::ComputationalType AngleSignedDegrees(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return AngleSigned(left, right) * RadToDeg<Vector2<T>::ComputationalType>;
	}

	export template<Arithmetic T>
	constexpr Vector2<T> Project(const Vector2<T>& vector, const Vector2<T>& target) noexcept
	{
		const Vector2<T>::ComputationalType multiplier = Dot(vector, target) / Dot(target, target);

		return target * multiplier;
	}

	export template<Arithmetic T>
	constexpr Vector2<T> ProjectOnPlane(const Vector2<T>& vector, const Vector2<T>& normal) noexcept
	{
		const Vector2<T>::ComputationalType multiplier = Dot(vector, normal) / Dot(normal, normal);

		return vector - normal * multiplier;
	}

	export template<Arithmetic T>
	constexpr Vector2<T> Reflect(const Vector2<T>& vector, const Vector2<T>& normal) noexcept
	{
		const Vector2<T>::ComputationalType multiplier = typename Vector2<T>::ComputationalType{-2} * Dot(vector, normal) / Dot(normal, normal);

		return vector + normal * multiplier;
	}

	export template<Arithmetic T>
	constexpr bool operator ==(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return left.x == right.x && left.y == right.y;
	}

	export template<Arithmetic T>
	constexpr bool operator !=(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return left.x != right.x || left.y != right.y;
	}

	export template<Arithmetic T>
	constexpr Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return Vector2(static_cast<T>(left.x + right.x), static_cast<T>(left.y + right.y));
	}

	export template<Arithmetic T>
	constexpr Vector2<T> operator -(const Vector2<T>& vector) noexcept
	{
		return Vector2(static_cast<T>(-vector.x), static_cast<T>(-vector.y));
	}

	export template<Arithmetic T>
	constexpr Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return Vector2(static_cast<T>(left.x - right.x), static_cast<T>(left.y - right.y));
	}

	export template<Arithmetic T>
	constexpr Vector2<T> operator *(const Vector2<T>& vector, const typename Vector2<T>::ComputationalType multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(vector.x) * multiplier);
		const T y = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(vector.y) * multiplier);

		return Vector2(x, y);
	}

	export template<Arithmetic T>
	constexpr inline Vector2<T> operator *(const typename Vector2<T>::ComputationalType multiplier, const Vector2<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	export template<Arithmetic T>
	constexpr Vector2<T> operator *(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(left.x) * static_cast<Vector2<T>::ComputationalType>(right.x));
		const T y = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(left.y) * static_cast<Vector2<T>::ComputationalType>(right.y));

		return Vector2(x, y);
	}

	export template<Arithmetic T>
	constexpr Vector2<T> operator /(const Vector2<T>& vector, const typename Vector2<T>::ComputationalType divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(vector.x) / divisor);
		const T y = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(vector.y) / divisor);

		return Vector2(x, y);
	}

	export template<Arithmetic T>
	constexpr Vector2<T> operator /(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(left.x) / static_cast<Vector2<T>::ComputationalType>(right.x));
		const T y = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(left.y) / static_cast<Vector2<T>::ComputationalType>(right.y));

		return Vector2(x, y);
	}

	template<Arithmetic T>
	constexpr Vector2<T>::Vector2() noexcept :
		x{},
		y{}
	{
	}

	template<Arithmetic T>
	constexpr Vector2<T>::Vector2(const T xParam, const T yParam) noexcept :
		x{xParam},
		y{yParam}
	{
	}

	template<Arithmetic T>
	constexpr Vector2<T>::Vector2(const Vector2& other) noexcept :
		Vector2(other.x, other.y)
	{
	}

	template<Arithmetic T>
	constexpr inline Vector2<T>::ComputationalType Vector2<T>::Magnitude() const noexcept
	{
		return sqrt(MagnitudeSquared());
	}

	template<Arithmetic T>
	constexpr inline Vector2<T>::ComputationalType Vector2<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T>
	constexpr Vector2<T> Vector2<T>::Normalized() const noexcept
	{
		return *this / Magnitude();
	}

	template<Arithmetic T>
	constexpr inline void Vector2<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	constexpr void Vector2<T>::Set(const T xParam, const T yParam) noexcept
	{
		x = xParam;
		y = yParam;
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator =(const Vector2& other) noexcept
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator +=(const Vector2& other) noexcept
	{
		x = static_cast<T>(x + other.x);
		y = static_cast<T>(y + other.y);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator -=(const Vector2& other) noexcept
	{
		x = static_cast<T>(x - other.x);
		y = static_cast<T>(y - other.y);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator *=(const Vector2<T>::ComputationalType multiplier) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) * multiplier);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) * multiplier);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator *=(const Vector2& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) * static_cast<ComputationalType>(other.x));
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) * static_cast<ComputationalType>(other.y));

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator /=(const ComputationalType divisor) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / divisor);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / divisor);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator /=(const Vector2& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / static_cast<ComputationalType>(other.x));
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / static_cast<ComputationalType>(other.y));

		return *this;
	}

	template<Arithmetic T>
	const Vector2<T> Vector2<T>::Up = Vector2<T>(T{0}, T{1});
	template<Arithmetic T>
	const Vector2<T> Vector2<T>::Down = Vector2<T>(T{0}, T{-1});
	template<Arithmetic T>
	const Vector2<T> Vector2<T>::Right = Vector2<T>(T{1}, T{0});
	template<Arithmetic T>
	const Vector2<T> Vector2<T>::Left = Vector2<T>(T{-1}, T{0});
	template<Arithmetic T>
	const Vector2<T> Vector2<T>::One = Vector2<T>(T{1}, T{1});
	template<Arithmetic T>
	const Vector2<T> Vector2<T>::Zero = Vector2<T>(T{0}, T{0});
	template<Arithmetic T>
	const Vector2<T> Vector2<T>::Negative = Vector2<T>(T{-1}, T{-1});
}
