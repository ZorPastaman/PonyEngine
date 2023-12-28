/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math.Vector4;

import <utility>;
import <cmath>;
import <algorithm>;
import <concepts>;

import PonyEngine.Math.Common;

namespace PonyEngine::Math
{
	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>>
	struct Vector4 final
	{
	public:
		using value_type = T;
		using computational_type = U;

		constexpr Vector4() noexcept;
		constexpr Vector4(const T xParam, const T yParam, const T zParam, const T wParam) noexcept;
		constexpr Vector4(const Vector4& other) noexcept;

		constexpr ~Vector4() noexcept = default;

		constexpr U Magnitude() const noexcept;
		constexpr inline U MagnitudeSquared() const noexcept;

		constexpr Vector4 Normalized() const noexcept;
		constexpr inline void Normalize() noexcept;

		constexpr Vector4& Set(const T xParam, const T yParam, const T zParam, const T wParam) noexcept;

		constexpr Vector4& operator =(const Vector4& other) noexcept;
		constexpr Vector4& operator +=(const Vector4& other) noexcept;
		constexpr Vector4& operator -=(const Vector4& other) noexcept;
		constexpr Vector4& operator *=(const U multiplier) noexcept;
		constexpr Vector4& operator *=(const Vector4& other) noexcept;
		constexpr Vector4& operator /=(const U divisor) noexcept;
		constexpr Vector4& operator /=(const Vector4& other) noexcept;

		T x;
		T y;
		T z;
		T w;
	};

	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>>
	constexpr inline const Vector4<T, U> One4 = Vector4<T, U>(T{1}, T{1}, T{1}, T{1});
	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>>
	constexpr inline const Vector4<T, U> Zero4 = Vector4<T, U>(T{0}, T{0}, T{0}, T{0});
	export template<Arithmetic T, std::floating_point U = ComputationalFor<T>> requires std::is_signed_v<T>
	constexpr inline const Vector4<T, U> Negative4 = Vector4<T, U>(T{-1}, T{-1}, T{-1}, T{-1});

	export template<Arithmetic T, std::floating_point U>
	constexpr U Dot(const Vector4<T, U>& left, const Vector4<T, U>& right) noexcept
	{
		return static_cast<U>(left.x) * static_cast<U>(right.x) +
			static_cast<U>(left.y) * static_cast<U>(right.y) +
			static_cast<U>(left.z) * static_cast<U>(right.z) +
			static_cast<U>(left.w) * static_cast<U>(right.w);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U> Project(const Vector4<T, U>& vector, const Vector4<T, U>& target) noexcept
	{
		const U multiplier = Dot(vector, target) / Dot(target, target);
		return target * multiplier;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr bool operator ==(const Vector4<T, U>& left, const Vector4<T, U>& right) noexcept
	{
		return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr bool operator !=(const Vector4<T, U>& left, const Vector4<T, U>& right) noexcept
	{
		return left.x != right.x || left.y != right.y || left.z != right.z || left.w != right.w;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U> operator +(const Vector4<T, U>& left, const Vector4<T, U>& right) noexcept
	{
		return Vector4(static_cast<T>(left.x + right.x), static_cast<T>(left.y + right.y), 
			static_cast<T>(left.z + right.z), static_cast<T>(left.w + right.w));
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U> operator -(const Vector4<T, U>& vector) noexcept
	{
		return Vector4(static_cast<T>(-vector.x), static_cast<T>(-vector.y), 
			static_cast<T>(-vector.z), static_cast<T>(-vector.w));
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U> operator -(const Vector4<T, U>& left, const Vector4<T, U>& right) noexcept
	{
		return Vector4(static_cast<T>(left.x - right.x), static_cast<T>(left.y - right.y), 
			static_cast<T>(left.z - right.z), static_cast<T>(left.w - right.w));
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U> operator *(const Vector4<T, U>& vector, const U multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.x) * multiplier);
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.y) * multiplier);
		const T z = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.z) * multiplier);
		const T w = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.w) * multiplier);
		return Vector4(x, y, z, w);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr inline Vector4<T, U> operator *(const U multiplier, const Vector4<T, U>& vector) noexcept
	{
		return vector * multiplier;
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U> operator *(const Vector4<T, U>& left, const Vector4<T, U>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.x) * static_cast<U>(right.x));
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.y) * static_cast<U>(right.y));
		const T z = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.z) * static_cast<U>(right.z));
		const T w = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.w) * static_cast<U>(right.w));
		return Vector4(x, y, z, w);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U> operator /(const Vector4<T, U>& vector, const U divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.x) / divisor);
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.y) / divisor);
		const T z = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.z) / divisor);
		const T w = RoundToIntegralIfPossible<U, T>(static_cast<U>(vector.w) / divisor);
		return Vector4(x, y, z, w);
	}

	export template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U> operator /(const Vector4<T, U>& left, const Vector4<T, U>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.x) / static_cast<U>(right.x));
		const T y = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.y) / static_cast<U>(right.y));
		const T z = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.z) / static_cast<U>(right.z));
		const T w = RoundToIntegralIfPossible<U, T>(static_cast<U>(left.w) / static_cast<U>(right.w));
		return Vector4(x, y, z, w);
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U>::Vector4() noexcept :
		x{},
		y{},
		z{},
		w{}
	{
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U>::Vector4(const T xParam, const T yParam, const T zParam, const T wParam) noexcept :
		x{xParam},
		y{yParam},
		z{zParam},
		w{wParam}
	{
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U>::Vector4(const Vector4<T, U>& other) noexcept :
		Vector4(other.x, other.y, other.z, other.w)
	{
	}

	template<Arithmetic T, std::floating_point U>
	constexpr U Vector4<T, U>::Magnitude() const noexcept
	{
		return sqrt(MagnitudeSquared());
	}

	template<Arithmetic T, std::floating_point U>
	constexpr inline U Vector4<T, U>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U> Vector4<T, U>::Normalized() const noexcept
	{
		return *this / Magnitude();
	}

	template<Arithmetic T, std::floating_point U>
	constexpr inline void Vector4<T, U>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U>& Vector4<T, U>::Set(const T xParam, const T yParam, const T zParam, const T wParam) noexcept
	{
		x = xParam;
		y = yParam;
		z = zParam;
		w = wParam;
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U>& Vector4<T, U>::operator =(const Vector4<T, U>& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U>& Vector4<T, U>::operator +=(const Vector4<T, U>& other) noexcept
	{
		x = static_cast<T>(x + other.x);
		y = static_cast<T>(y + other.y);
		z = static_cast<T>(z + other.z);
		w = static_cast<T>(w + other.w);
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U>& Vector4<T, U>::operator -=(const Vector4<T, U>& other) noexcept
	{
		x = static_cast<T>(x - other.x);
		y = static_cast<T>(y - other.y);
		z = static_cast<T>(z - other.z);
		w = static_cast<T>(w - other.w);
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U>& Vector4<T, U>::operator *=(const U multiplier) noexcept
	{
		x = RoundToIntegralIfPossible<U, T>(static_cast<U>(x) * multiplier);
		y = RoundToIntegralIfPossible<U, T>(static_cast<U>(y) * multiplier);
		z = RoundToIntegralIfPossible<U, T>(static_cast<U>(z) * multiplier);
		w = RoundToIntegralIfPossible<U, T>(static_cast<U>(w) * multiplier);
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U>& Vector4<T, U>::operator *=(const Vector4& other) noexcept
	{
		x = RoundToIntegralIfPossible<U, T>(static_cast<U>(x) * static_cast<U>(other.x));
		y = RoundToIntegralIfPossible<U, T>(static_cast<U>(y) * static_cast<U>(other.y));
		z = RoundToIntegralIfPossible<U, T>(static_cast<U>(z) * static_cast<U>(other.z));
		w = RoundToIntegralIfPossible<U, T>(static_cast<U>(w) * static_cast<U>(other.w));
		return *this;
	}

	template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U>& Vector4<T, U>::operator /=(const U divisor) noexcept
	{
		x = RoundToIntegralIfPossible<U, T>(static_cast<U>(x) / divisor);
		y = RoundToIntegralIfPossible<U, T>(static_cast<U>(y) / divisor);
		z = RoundToIntegralIfPossible<U, T>(static_cast<U>(z) / divisor);
		w = RoundToIntegralIfPossible<U, T>(static_cast<U>(w) / divisor);
		return *this;
	}
	template<Arithmetic T, std::floating_point U>
	constexpr Vector4<T, U>& Vector4<T, U>::operator /=(const Vector4& other) noexcept
	{
		x = RoundToIntegralIfPossible<U, T>(static_cast<U>(x) / static_cast<U>(other.x));
		y = RoundToIntegralIfPossible<U, T>(static_cast<U>(y) / static_cast<U>(other.y));
		z = RoundToIntegralIfPossible<U, T>(static_cast<U>(z) / static_cast<U>(other.z));
		w = RoundToIntegralIfPossible<U, T>(static_cast<U>(w) / static_cast<U>(other.w));
		return *this;
	}
}
