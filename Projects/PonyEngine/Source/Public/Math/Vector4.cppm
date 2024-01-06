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
	export template<Arithmetic T>
	struct Vector4 final
	{
	public:
		using ValueType = T;
		using ComputationalType = ComputationalFor<T>;

		constexpr Vector4() noexcept;
		constexpr Vector4(const T xParam, const T yParam, const T zParam, const T wParam) noexcept;
		constexpr Vector4(const Vector4& other) noexcept;

		constexpr ~Vector4() noexcept = default;

		constexpr ComputationalType Magnitude() const noexcept;
		constexpr inline ComputationalType MagnitudeSquared() const noexcept;

		constexpr Vector4 Normalized() const noexcept;
		constexpr inline void Normalize() noexcept;

		constexpr Vector4& Set(const T xParam, const T yParam, const T zParam, const T wParam) noexcept;

		constexpr Vector4& operator =(const Vector4& other) noexcept;
		constexpr Vector4& operator +=(const Vector4& other) noexcept;
		constexpr Vector4& operator -=(const Vector4& other) noexcept;
		constexpr Vector4& operator *=(const ComputationalType multiplier) noexcept;
		constexpr Vector4& operator *=(const Vector4& other) noexcept;
		constexpr Vector4& operator /=(const ComputationalType divisor) noexcept;
		constexpr Vector4& operator /=(const Vector4& other) noexcept;

		static const Vector4 One;
		static const Vector4 Zero;
		static const Vector4 Negative;

		T x;
		T y;
		T z;
		T w;
	};

	export template<Arithmetic T>
	constexpr Vector4<T>::ComputationalType Dot(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return static_cast<Vector4<T>::ComputationalType>(left.x) * static_cast<Vector4<T>::ComputationalType>(right.x) +
			static_cast<Vector4<T>::ComputationalType>(left.y) * static_cast<Vector4<T>::ComputationalType>(right.y) +
			static_cast<Vector4<T>::ComputationalType>(left.z) * static_cast<Vector4<T>::ComputationalType>(right.z) +
			static_cast<Vector4<T>::ComputationalType>(left.w) * static_cast<Vector4<T>::ComputationalType>(right.w);
	}

	export template<Arithmetic T>
	constexpr Vector4<T> Project(const Vector4<T>& vector, const Vector4<T>& target) noexcept
	{
		const Vector4<T>::ComputationalType multiplier = Dot(vector, target) / Dot(target, target);

		return target * multiplier;
	}

	export template<Arithmetic T>
	constexpr bool operator ==(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
	}

	export template<Arithmetic T>
	constexpr bool operator !=(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return left.x != right.x || left.y != right.y || left.z != right.z || left.w != right.w;
	}

	export template<Arithmetic T>
	constexpr Vector4<T> operator +(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return Vector4(static_cast<T>(left.x + right.x), static_cast<T>(left.y + right.y), 
			static_cast<T>(left.z + right.z), static_cast<T>(left.w + right.w));
	}

	export template<Arithmetic T>
	constexpr Vector4<T> operator -(const Vector4<T>& vector) noexcept
	{
		return Vector4(static_cast<T>(-vector.x), static_cast<T>(-vector.y), 
			static_cast<T>(-vector.z), static_cast<T>(-vector.w));
	}

	export template<Arithmetic T>
	constexpr Vector4<T> operator -(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return Vector4(static_cast<T>(left.x - right.x), static_cast<T>(left.y - right.y), 
			static_cast<T>(left.z - right.z), static_cast<T>(left.w - right.w));
	}

	export template<Arithmetic T>
	constexpr Vector4<T> operator *(const Vector4<T>& vector, const typename Vector4<T>::ComputationalType multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.x) * multiplier);
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.y) * multiplier);
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.z) * multiplier);
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.w) * multiplier);

		return Vector4(x, y, z, w);
	}

	export template<Arithmetic T>
	constexpr inline Vector4<T> operator *(const typename Vector4<T>::ComputationalType multiplier, const Vector4<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	export template<Arithmetic T>
	constexpr Vector4<T> operator *(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.x) * static_cast<Vector4<T>::ComputationalType>(right.x));
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.y) * static_cast<Vector4<T>::ComputationalType>(right.y));
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.z) * static_cast<Vector4<T>::ComputationalType>(right.z));
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.w) * static_cast<Vector4<T>::ComputationalType>(right.w));

		return Vector4(x, y, z, w);
	}

	export template<Arithmetic T>
	constexpr Vector4<T> operator /(const Vector4<T>& vector, const typename Vector4<T>::ComputationalType divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.x) / divisor);
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.y) / divisor);
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.z) / divisor);
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.w) / divisor);

		return Vector4(x, y, z, w);
	}

	export template<Arithmetic T>
	constexpr Vector4<T> operator /(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.x) / static_cast<Vector4<T>::ComputationalType>(right.x));
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.y) / static_cast<Vector4<T>::ComputationalType>(right.y));
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.z) / static_cast<Vector4<T>::ComputationalType>(right.z));
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.w) / static_cast<Vector4<T>::ComputationalType>(right.w));

		return Vector4(x, y, z, w);
	}

	template<Arithmetic T>
	constexpr Vector4<T>::Vector4() noexcept :
		x{},
		y{},
		z{},
		w{}
	{
	}

	template<Arithmetic T>
	constexpr Vector4<T>::Vector4(const T xParam, const T yParam, const T zParam, const T wParam) noexcept :
		x{xParam},
		y{yParam},
		z{zParam},
		w{wParam}
	{
	}

	template<Arithmetic T>
	constexpr Vector4<T>::Vector4(const Vector4<T>& other) noexcept :
		Vector4(other.x, other.y, other.z, other.w)
	{
	}

	template<Arithmetic T>
	constexpr Vector4<T>::ComputationalType Vector4<T>::Magnitude() const noexcept
	{
		return sqrt(MagnitudeSquared());
	}

	template<Arithmetic T>
	constexpr inline Vector4<T>::ComputationalType Vector4<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T>
	constexpr Vector4<T> Vector4<T>::Normalized() const noexcept
	{
		return *this / Magnitude();
	}

	template<Arithmetic T>
	constexpr inline void Vector4<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::Set(const T xParam, const T yParam, const T zParam, const T wParam) noexcept
	{
		x = xParam;
		y = yParam;
		z = zParam;
		w = wParam;

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::operator =(const Vector4<T>& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::operator +=(const Vector4<T>& other) noexcept
	{
		x = static_cast<T>(x + other.x);
		y = static_cast<T>(y + other.y);
		z = static_cast<T>(z + other.z);
		w = static_cast<T>(w + other.w);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::operator -=(const Vector4<T>& other) noexcept
	{
		x = static_cast<T>(x - other.x);
		y = static_cast<T>(y - other.y);
		z = static_cast<T>(z - other.z);
		w = static_cast<T>(w - other.w);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::operator *=(const typename Vector4<T>::ComputationalType multiplier) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) * multiplier);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) * multiplier);
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) * multiplier);
		w = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(w) * multiplier);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::operator *=(const Vector4& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) * static_cast<ComputationalType>(other.x));
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) * static_cast<ComputationalType>(other.y));
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) * static_cast<ComputationalType>(other.z));
		w = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(w) * static_cast<ComputationalType>(other.w));

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::operator /=(const ComputationalType divisor) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / divisor);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / divisor);
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) / divisor);
		w = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(w) / divisor);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::operator /=(const Vector4& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / static_cast<ComputationalType>(other.x));
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / static_cast<ComputationalType>(other.y));
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) / static_cast<ComputationalType>(other.z));
		w = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(w) / static_cast<ComputationalType>(other.w));

		return *this;
	}

	template<Arithmetic T>
	const Vector4<T> Vector4<T>::One = Vector4<T>(T{1}, T{1}, T{1}, T{1});
	template<Arithmetic T>
	const Vector4<T> Vector4<T>::Zero = Vector4<T>(T{0}, T{0}, T{0}, T{0});
	template<Arithmetic T>
	const Vector4<T> Vector4<T>::Negative = Vector4<T>(T{-1}, T{-1}, T{-1}, T{-1});
}
