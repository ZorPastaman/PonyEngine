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
	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>>
	struct Vector2 final
	{
	public:
		using value_type = T;
		using computational_type = U;

		constexpr Vector2() noexcept;
		constexpr Vector2(const T xParam, const T yParam) noexcept;
		constexpr Vector2(const Vector2& other) noexcept;

		constexpr ~Vector2() noexcept = default;

		constexpr U Magnitude() const noexcept;
		constexpr inline U MagnitudeSquared() const noexcept;

		constexpr Vector2 Normalized() const noexcept;
		constexpr inline void Normalize() noexcept;

		constexpr Vector2& Set(const T xParam, const T yParam) noexcept;

		constexpr Vector2& operator =(const Vector2& other) noexcept;
		constexpr Vector2& operator +=(const Vector2& other) noexcept;
		constexpr Vector2& operator -=(const Vector2& other) noexcept;
		constexpr Vector2& operator *=(const U multiplier) noexcept;
		constexpr Vector2& operator *=(const Vector2& other) noexcept;
		constexpr Vector2& operator /=(const U divisor) noexcept;
		constexpr Vector2& operator /=(const Vector2& other) noexcept;

		T x;
		T y;
	};

	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>>
	constexpr inline const Vector2<T, U> Up2 = Vector2<T, U>(T{0}, T{1});
	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>> requires std::is_signed_v<T>
	constexpr inline const Vector2<T, U> Down2 = Vector2<T, U>(T{0}, T{-1});
	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>>
	constexpr inline const Vector2<T, U> Right2 = Vector2<T, U>(T{1}, T{0});
	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>> requires std::is_signed_v<T>
	constexpr inline const Vector2<T, U> Left2 = Vector2<T, U>(T{-1}, T{0});
	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>>
	constexpr inline const Vector2<T, U> One2 = Vector2<T, U>(T{1}, T{1});
	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>>
	constexpr inline const Vector2<T, U> Zero2 = Vector2<T, U>(T{0}, T{0});
	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>> requires std::is_signed_v<T>
	constexpr inline const Vector2<T, U> Negative2 = Vector2<T, U>(T{-1}, T{-1});

	export template<Arithmetic T, std::floating_point U>
	constexpr U Dot(const Vector2<T, U>& left, const Vector2<T, U>& right) noexcept
	{
		return static_cast<U>(left.x) * static_cast<U>(right.x) +
			static_cast<U>(left.y) * static_cast<U>(right.y);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr U Angle(const Vector2<T, U>& left, const Vector2<T, U>& right) noexcept
	{
		const U dot = Dot(left, right);
		const U superMagnitude = sqrt(left.MagnitudeSquared() * right.MagnitudeSquared());
		const U cos = std::clamp(dot / superMagnitude, U(-1), U(1));
		return std::acos(cos);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr U AngleSigned(const Vector2<T, U>& left, const Vector2<T, U>& right) noexcept
	{
		const U zCross = left.x * right.y - left.y * right.x;
		const U sign = Sign(zCross);
		const U angle = Angle(left, right);
		return angle * sign;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr inline U AngleDegrees(const Vector2<T, U>& left, const Vector2<T, U>& right) noexcept
	{
		return Angle(left, right) * RadToDeg<U>;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr inline U AngleSignedDegrees(const Vector2<T, U>& left, const Vector2<T, U>& right) noexcept
	{
		return AngleSigned(left, right) * RadToDeg<U>;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U> Project(const Vector2<T, U>& vector, const Vector2<T, U>& target) noexcept
	{
		const U multiplier = Dot(vector, target) / Dot(target, target);
		return target * multiplier;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U> ProjectOnPlane(const Vector2<T, U>& vector, const Vector2<T, U>& normal) noexcept
	{
		const U multiplier = Dot(vector, normal) / Dot(normal, normal);
		return vector - normal * multiplier;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U> Reflect(const Vector2<T, U>& vector, const Vector2<T, U>& normal) noexcept
	{
		const U multiplier = U(-2) * Dot(vector, normal) / Dot(normal, normal);
		return vector + normal * multiplier;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr bool operator ==(const Vector2<T, U>& left, const Vector2<T, U>& right) noexcept
	{
		return left.x == right.x && left.y == right.y;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr bool operator !=(const Vector2<T, U>& left, const Vector2<T, U>& right) noexcept
	{
		return left.x != right.x || left.y != right.y;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U> operator +(const Vector2<T, U>& left, const Vector2<T, U>& right) noexcept
	{
		return Vector2(static_cast<T>(left.x + right.x), static_cast<T>(left.y + right.y));
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U> operator -(const Vector2<T, U>& vector) noexcept
	{
		return Vector2(static_cast<T>(-vector.x), static_cast<T>(-vector.y));
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U> operator -(const Vector2<T, U>& left, const Vector2<T, U>& right) noexcept
	{
		return Vector2(static_cast<T>(left.x - right.x), static_cast<T>(left.y - right.y));
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U> operator *(const Vector2<T, U>& vector, const U multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.x) * multiplier);
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.y) * multiplier);
		return Vector2(x, y);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr inline Vector2<T, U> operator *(const U multiplier, const Vector2<T, U>& vector) noexcept
	{
		return vector * multiplier;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U> operator *(const Vector2<T, U>& left, const Vector2<T, U>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.x) * static_cast<U>(right.x));
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.y) * static_cast<U>(right.y));
		return Vector2(x, y);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U> operator /(const Vector2<T, U>& vector, const U divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.x) / divisor);
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.y) / divisor);
		return Vector2(x, y);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U> operator /(const Vector2<T, U>& left, const Vector2<T, U>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.x) / static_cast<U>(right.x));
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.y) / static_cast<U>(right.y));
		return Vector2(x, y);
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U>::Vector2() noexcept :
		x{},
		y{}
	{
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U>::Vector2(const T xParam, const T yParam) noexcept :
		x{xParam},
		y{yParam}
	{
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U>::Vector2(const Vector2& other) noexcept :
		Vector2(other.x, other.y)
	{
	}

	template<Arithmetic T, std::floating_point U>
	constexpr U Vector2<T, U>::Magnitude() const noexcept
	{
		return sqrt(MagnitudeSquared());
	}

	template<Arithmetic T, std::floating_point U>
	inline constexpr U Vector2<T, U>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U> Vector2<T, U>::Normalized() const noexcept
	{
		return *this / Magnitude();
	}

	template<Arithmetic T, std::floating_point U>
	inline constexpr void Vector2<T, U>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U>& Vector2<T, U>::Set(const T xParam, const T yParam) noexcept
	{
		x = xParam;
		y = yParam;
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U>& Vector2<T, U>::operator=(const Vector2& other) noexcept
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U>& Vector2<T, U>::operator+=(const Vector2& other) noexcept
	{
		x = static_cast<T>(x + other.x);
		y = static_cast<T>(y + other.y);
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U>& Vector2<T, U>::operator-=(const Vector2& other) noexcept
	{
		x = static_cast<T>(x - other.x);
		y = static_cast<T>(y - other.y);
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U>& Vector2<T, U>::operator*=(const U multiplier) noexcept
	{
		x = RoundToIntegralIfPossible<U, T>(static_cast<U>(x) * multiplier);
		y = RoundToIntegralIfPossible<U, T>(static_cast<U>(y) * multiplier);
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U>& Vector2<T, U>::operator*=(const Vector2& other) noexcept
	{
		x = RoundToIntegralIfPossible<U, T>(static_cast<U>(x) * static_cast<U>(other.x));
		y = RoundToIntegralIfPossible<U, T>(static_cast<U>(y) * static_cast<U>(other.y));
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U>& Vector2<T, U>::operator/=(const U divisor) noexcept
	{
		x = RoundToIntegralIfPossible<U, T>(static_cast<U>(x) / divisor);
		y = RoundToIntegralIfPossible<U, T>(static_cast<U>(y) / divisor);
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector2<T, U>& Vector2<T, U>::operator/=(const Vector2& other) noexcept
	{
		x = RoundToIntegralIfPossible<U, T>(static_cast<U>(x) / static_cast<U>(other.x));
		y = RoundToIntegralIfPossible<U, T>(static_cast<U>(y) / static_cast<U>(other.y));
		return *this;
	}
}
