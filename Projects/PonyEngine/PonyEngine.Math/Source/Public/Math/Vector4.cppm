/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Vector4;

import <array>;
import <cmath>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <type_traits>;

import :Common;

namespace PonyEngine::Math
{
	/// @brief 4D vector implementation.
	/// @tparam T Component type.
	export template<Arithmetic T>
	struct Vector4 final
	{
	public:
		using ValueType = T; /// @brief Component type.
		using ComputationalType = ComputationalFor<T>; /// @brief Floating point type used in functions that require a floating point type.

		[[nodiscard("Pure constructor")]]
		constexpr inline Vector4() noexcept = default;
		/// @brief Creates a @p Vector4 and assigns its components from the arguments.
		/// @param xParam Value to assign to the @p x component.
		/// @param yParam Value to assign to the @p y component.
		/// @param zParam Value to assign to the @p z component.
		/// @param wParam Value to assign to the @p w component.
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector4(T xParam, T yParam, T zParam, T wParam) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector4(const Vector4<T>& other) noexcept = default;

		constexpr inline ~Vector4() noexcept = default;

		/// @brief Computes a magnitude of a @p Vector.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		inline ComputationalType Magnitude() const noexcept;
		/// @brief Computes a squared magnitude of a @p Vector.
		/// @details This function is much faster than @p Magnitude() because it doesn't compute a square root.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		constexpr inline T MagnitudeSquared() const noexcept;

		/// @brief Computes a @p Vector normalized from this one.
		/// @return Normalized @p Vector.
		[[nodiscard("Pure function")]]
		Vector4<T> Normalized() const noexcept;
		/// @brief Normalizes a @p Vector.
		inline void Normalize() noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Assigns arguments to @p Vector components.
		/// @param xParam X component.
		/// @param yParam Y component.
		/// @param zParam Z component.
		/// @param wParam w component.
		inline void Set(T xParam, T yParam, T zParam, T wParam) noexcept;

		/// @brief Creates a string representing a state of a @p Vector.
		///        The format is '(x, y, z, w)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		inline std::string ToString() const;

		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		inline T& operator [](std::size_t index) noexcept;
		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		inline const T& operator [](std::size_t index) const noexcept;

		inline Vector4<T>& operator =(const Vector4<T>& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other @p Vector to add.
		/// @return @a This.
		Vector4<T>& operator +=(const Vector4<T>& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other @p Vector to subtract.
		/// @return @a This.
		Vector4<T>& operator -=(const Vector4<T>& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier @p Vector multiplier.
		/// @return @a This.
		Vector4<T>& operator *=(T multiplier) noexcept requires(std::is_integral_v<T>);
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier @p Vector multiplier.
		/// @return @a This.
		Vector4<T>& operator *=(ComputationalType multiplier) noexcept;
		/// @brief Multiplies @a this by the @p other component-wise.
		/// @param other @p Vector to multiply.
		/// @return @a This.
		Vector4<T>& operator *=(const Vector4<T>& other) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor @p Vector divisor.
		/// @return @a This.
		Vector4<T>& operator /=(ComputationalType divisor) noexcept;
		/// @brief Divides @a this by the @p divisor component-wise.
		/// @param other @p Vector to divide by.
		/// @return @a This.
		Vector4<T>& operator /=(const Vector4<T>& other) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr inline bool operator ==(const Vector4<T>& other) const noexcept = default;

		static const Vector4<T> One; /// @brief Vector3(1, 1, 1, 1).
		static const Vector4<T> Zero; /// @brief Vector3(0, 0, 0, 0).
		static const Vector4<T> Negative; /// @brief Vector3(-1, -1, -1, -1).

		constexpr inline static const std::size_t ComponentCount = 4; /// @brief Component count. For any @p Vector4, it's always 4.

		T x; /// @brief X component.
		T y; /// @brief Y component.
		T z; /// @brief Z component.
		T w; /// @brief W component.
	};

	/// @brief Computes a dot product of two @p Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return Dot product.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Dot(const Vector4<T>& left, const Vector4<T>& right) noexcept;

	/// @brief Projects the @p vector onto the @p target.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param target Projection target.
	/// @return Projected @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector4<T> Project(const Vector4<T>& vector, const Vector4<T>& target) noexcept;

	/// @brief Linear interpolation between two @p Vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between two @p Vectors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr inline Vector4<T> Lerp(const Vector4<T>& from, const Vector4<T>& to, typename Vector4<T>::ComputationalType time) noexcept;

	/// @brief Checks if two @p Vectors are almost equal with a tolerance value.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the @p Vectors are almost equal; @a false otherwise.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr inline bool AreAlmostEqual(const Vector4<T>& left, const Vector4<T>& right, typename Vector4<T>::ComputationalType tolerance = typename Vector4<T>::ComputationalType{0.00001}) noexcept;

	/// @brief Addition operator for two @p Vectors.
	/// @tparam T Component type.
	/// @param left Augend @p Vector.
	/// @param right Addend @p Vector.
	/// @return Sum @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator +(const Vector4<T>& left, const Vector4<T>& right) noexcept;

	/// @brief Negates the @p vector.
	/// @tparam T Component type.
	/// @param vector @p Vector to negate.
	/// @return Negated @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator -(const Vector4<T>& vector) noexcept;

	/// @brief Subtracts the @p right vector from the @p left vector.
	/// @tparam T Component type.
	/// @param left Minuend @p Vector.
	/// @param right Subtrahend @p Vector.
	/// @return Difference @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator -(const Vector4<T>& left, const Vector4<T>& right) noexcept;

	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand @p Vector.
	/// @param multiplier Multiplier.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator *(const Vector4<T>& vector, T multiplier) noexcept requires(std::is_integral_v<T>);
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand @p Vector.
	/// @param multiplier Multiplier.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator *(const Vector4<T>& vector, typename Vector4<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector4<T> operator *(T multiplier, const Vector4<T>& vector) noexcept requires(std::is_integral_v<T>);
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector4<T> operator *(typename Vector4<T>::ComputationalType multiplier, const Vector4<T>& vector) noexcept;
	/// @brief Multiplies the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand @p Vector.
	/// @param right Multiplier @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator *(const Vector4<T>& left, const Vector4<T>& right) noexcept;

	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend @p Vector.
	/// @param divisor Divisor.
	/// @return Quotient @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator /(const Vector4<T>& vector, typename Vector4<T>::ComputationalType divisor) noexcept;
	/// @brief Divides the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Dividend @p Vector.
	/// @param right Divisor @p Vector.
	/// @return Quotient @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator /(const Vector4<T>& left, const Vector4<T>& right) noexcept;

	/// @brief Puts @p Vector.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param vector Input source.
	/// @return @p stream.
	export template<Arithmetic T>
	inline std::ostream& operator <<(std::ostream& stream, const Vector4<T>& vector);

	/// @brief Array of pointers to @p Vector components.
	/// @tparam T Component type.
	template<Arithmetic T>
	static const std::array<T Vector4<T>::*, Vector4<T>::ComponentCount> s_vector4ComponentPointers
		{ &Vector4<T>::x, &Vector4<T>::y, &Vector4<T>::z, &Vector4<T>::w };

	template<Arithmetic T>
	constexpr inline Vector4<T>::Vector4(const T xParam, const T yParam, const T zParam, const T wParam) noexcept :
		x{xParam},
		y{yParam},
		z{zParam},
		w{wParam}
	{
	}

	template<Arithmetic T>
	inline Vector4<T>::ComputationalType Vector4<T>::Magnitude() const noexcept
	{
		return std::sqrt(static_cast<Vector4<T>::ComputationalType>(MagnitudeSquared()));
	}

	template<Arithmetic T>
	constexpr inline T Vector4<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T>
	Vector4<T> Vector4<T>::Normalized() const noexcept
	{
		return *this * (Vector4<T>::ComputationalType{1} / Magnitude());
	}

	template<Arithmetic T>
	inline void Vector4<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	bool Vector4<T>::IsFinite() const noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w);
		}
		else
		{
			return true;
		}
	}

	template<Arithmetic T>
	inline void Vector4<T>::Set(const T xParam, const T yParam, const T zParam, const T wParam) noexcept
	{
		x = xParam;
		y = yParam;
		z = zParam;
		w = wParam;
	}

	template<Arithmetic T>
	constexpr T Dot(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
	}

	template<Arithmetic T>
	constexpr Vector4<T> Project(const Vector4<T>& vector, const Vector4<T>& target) noexcept
	{
		const Vector4<T>::ComputationalType multiplier = static_cast<Vector4<T>::ComputationalType>(Dot(vector, target)) / Dot(target, target);

		return target * multiplier;
	}

	template<Arithmetic T>
	constexpr inline Vector4<T> Lerp(const Vector4<T>& from, const Vector4<T>& to, const typename Vector4<T>::ComputationalType time) noexcept
	{
		return from + (to - from) * time;
	}

	template<Arithmetic T>
	constexpr inline bool AreAlmostEqual(const Vector4<T>& left, const Vector4<T>& right, const typename Vector4<T>::ComputationalType tolerance) noexcept
	{
		return (left - right).MagnitudeSquared() < tolerance * tolerance;
	}

	template<Arithmetic T>
	inline std::string Vector4<T>::ToString() const
	{
		return std::format("({}, {}, {}, {})", x, y, z, w);
	}

	template<Arithmetic T>
	inline T& Vector4<T>::operator [](const std::size_t index) noexcept
	{
		return this->*s_vector4ComponentPointers<T>[index];
	}

	template<Arithmetic T>
	inline const T& Vector4<T>::operator [](const std::size_t index) const noexcept
	{
		return this->*s_vector4ComponentPointers<T>[index];
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator +(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return Vector4<T>(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator -(const Vector4<T>& vector) noexcept
	{
		return Vector4<T>(-vector.x, -vector.y, -vector.z, -vector.w);
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator -(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return Vector4<T>(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator *(const Vector4<T>& vector, T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		return Vector4<T>(vector.x * multiplier, vector.y * multiplier, vector.z * multiplier, vector.w * multiplier);
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator *(const Vector4<T>& vector, const typename Vector4<T>::ComputationalType multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.x * multiplier);
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.y * multiplier);
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.z * multiplier);
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.w * multiplier);

		return Vector4<T>(x, y, z, w);
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator *(const T multiplier, const Vector4<T>& vector) noexcept requires(std::is_integral_v<T>)
	{
		return vector * multiplier;
	}

	template<Arithmetic T>
	constexpr inline Vector4<T> operator *(const typename Vector4<T>::ComputationalType multiplier, const Vector4<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator *(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return Vector4<T>(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator /(const Vector4<T>& vector, const typename Vector4<T>::ComputationalType divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.x / divisor);
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.y / divisor);
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.z / divisor);
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.w / divisor);

		return Vector4<T>(x, y, z, w);
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator /(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.x) / right.x);
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.y) / right.y);
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.z) / right.z);
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.w) / right.w);

		return Vector4<T>(x, y, z, w);
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator +=(const Vector4<T>& other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator -=(const Vector4<T>& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		x *= multiplier;
		y *= multiplier;
		z *= multiplier;
		w *= multiplier;

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator *=(const typename Vector4<T>::ComputationalType multiplier) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(x * multiplier);
		y = RoundToIntegralIfPossible<ComputationalType, T>(y * multiplier);
		z = RoundToIntegralIfPossible<ComputationalType, T>(z * multiplier);
		w = RoundToIntegralIfPossible<ComputationalType, T>(w * multiplier);

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator *=(const Vector4<T>& other) noexcept
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator /=(const ComputationalType divisor) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(x / divisor);
		y = RoundToIntegralIfPossible<ComputationalType, T>(y / divisor);
		z = RoundToIntegralIfPossible<ComputationalType, T>(z / divisor);
		w = RoundToIntegralIfPossible<ComputationalType, T>(w / divisor);

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator /=(const Vector4<T>& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / other.x);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / other.y);
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) / other.z);
		w = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(w) / other.w);

		return *this;
	}

	template<Arithmetic T>
	inline std::ostream& operator <<(std::ostream& stream, const Vector4<T>& vector)
	{
		return stream << vector.ToString();
	}

	template<Arithmetic T>
	const Vector4<T> Vector4<T>::One = Vector4<T>(T{1}, T{1}, T{1}, T{1});
	template<Arithmetic T>
	const Vector4<T> Vector4<T>::Zero = Vector4<T>(T{0}, T{0}, T{0}, T{0});
	template<Arithmetic T>
	const Vector4<T> Vector4<T>::Negative = Vector4<T>(T{-1}, T{-1}, T{-1}, T{-1});
}
