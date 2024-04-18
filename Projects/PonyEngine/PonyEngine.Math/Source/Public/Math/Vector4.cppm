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
	class Vector4 final
	{
	public:
		using ValueType = T; /// @brief Component type.
		using ComputationalType = ComputationalFor<T>; /// @brief Floating point type used in functions that require a floating point type.

		/// @brief Creates a @p Vector4 and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector4() noexcept;
		/// @brief Creates a @p Vector4 and assigns its components from the arguments.
		/// @param x Value to assign to the @p x component.
		/// @param y Value to assign to the @p y component.
		/// @param z Value to assign to the @p z component.
		/// @param w Value to assign to the @p w component.
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector4(T x, T y, T z, T w) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector4(const Vector4<T>& other) noexcept = default;

		constexpr inline ~Vector4() noexcept = default;

		/// @brief Gets a reference to the @p x component.
		/// @return @p X component reference.
		[[nodiscard("Pure function")]]
		inline T& X() noexcept;
		/// @brief Gets a reference to the const @p x component.
		/// @return Const @p x component reference.
		[[nodiscard("Pure function")]]
		constexpr inline const T& X() const noexcept;
		/// @brief Gets a reference to the @p y component.
		/// @return @p Y component reference.
		[[nodiscard("Pure function")]]
		inline T& Y() noexcept;
		/// @brief Gets a reference to the const @p y component.
		/// @return Const @p y component reference.
		[[nodiscard("Pure function")]]
		constexpr inline const T& Y() const noexcept;
		/// @brief Gets a reference to the @p z component.
		/// @return @p Z component reference.
		[[nodiscard("Pure function")]]
		inline T& Z() noexcept;
		/// @brief Gets a reference to the const @p z component.
		/// @return Const @p z component reference.
		[[nodiscard("Pure function")]]
		constexpr inline const T& Z() const noexcept;
		/// @brief Gets a reference to the @p w component.
		/// @return @p W component reference.
		[[nodiscard("Pure function")]]
		inline T& W() noexcept;
		/// @brief Gets a reference to the const @p w component.
		/// @return Const @p w component reference.
		[[nodiscard("Pure function")]]
		constexpr inline const T& W() const noexcept;
		/// @brief Gets a pointer to the data array. The order is x, y, z, w.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		inline T* Data() noexcept;
		/// @brief Gets a pointer to the const data array. The order is x, y, z, w.
		/// @return Const data pointer.
		[[nodiscard("Pure function")]]
		inline const T* Data() const noexcept;

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

		/// @brief Computed a @p Vector inversed to this one.
		/// @return Inversed @p Vector.
		[[nodiscard("Pure function")]]
		constexpr inline Vector4<T> Inversed() const noexcept;
		/// @brief Inverses a @p Vector.
		inline void Inverse() noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Assigns arguments to @p Vector components.
		/// @param x X component.
		/// @param y Y component.
		/// @param z Z component.
		/// @param w W component.
		inline void Set(T x, T y, T z, T w) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale @p Vector to multiply by.
		inline void Scale(const Vector4<T>& scale) noexcept;

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
		constexpr inline const T& operator [](std::size_t index) const noexcept;

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
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor @p Vector divisor.
		/// @return @a This.
		Vector4<T>& operator /=(ComputationalType divisor) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr inline bool operator ==(const Vector4<T>& other) const noexcept = default;

		static const Vector4<T> One; /// @brief Vector3(1, 1, 1, 1).
		static const Vector4<T> Zero; /// @brief Vector3(0, 0, 0, 0).
		static const Vector4<T> Negative; /// @brief Vector3(-1, -1, -1, -1).

		constexpr inline static const std::size_t ComponentCount = 4; /// @brief Component count. For any @p Vector4, it's always 4.

	private:
		std::array<T, ComponentCount> m_components; /// @brief Component array in order x, y, z, w.
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

	/// @brief Multiplies the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand @p Vector.
	/// @param right Multiplier @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr inline Vector4<T> Scale(const Vector4<T>& left, const Vector4<T>& right) noexcept;

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
	constexpr inline Vector4<T> operator -(const Vector4<T>& vector) noexcept;

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

	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend @p Vector.
	/// @param divisor Divisor.
	/// @return Quotient @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator /(const Vector4<T>& vector, typename Vector4<T>::ComputationalType divisor) noexcept;

	/// @brief Puts @p Vector.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param vector Input source.
	/// @return @p stream.
	export template<Arithmetic T>
	inline std::ostream& operator <<(std::ostream& stream, const Vector4<T>& vector);

	template<Arithmetic T>
	constexpr inline Vector4<T>::Vector4() noexcept :
		Vector4(T{}, T{}, T{}, T{})
	{
	}

	template<Arithmetic T>
	constexpr inline Vector4<T>::Vector4(const T x, const T y, const T z, const T w) noexcept :
		m_components{x, y, z, w}
	{
	}

	template<Arithmetic T>
	inline T& Vector4<T>::X() noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr inline const T& Vector4<T>::X() const noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	inline T& Vector4<T>::Y() noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr inline const T& Vector4<T>::Y() const noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	inline T& Vector4<T>::Z() noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr inline const T& Vector4<T>::Z() const noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	inline T& Vector4<T>::W() noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	constexpr inline const T& Vector4<T>::W() const noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	inline T* Vector4<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	inline const T* Vector4<T>::Data() const noexcept
	{
		return m_components.data();
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
#pragma warning(disable:4723)
		return *this * (Vector4<T>::ComputationalType{1} / Magnitude());
#pragma warning(default:4723)
	}

	template<Arithmetic T>
	inline void Vector4<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	inline constexpr Vector4<T> Vector4<T>::Inversed() const noexcept
	{
		return Vector4<T>(W(), Z(), Y(), X());
	}

	template<Arithmetic T>
	inline void Vector4<T>::Inverse() noexcept
	{
		*this = Inversed();
	}

	template<Arithmetic T>
	bool Vector4<T>::IsFinite() const noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return std::isfinite(X()) && std::isfinite(Y()) && std::isfinite(Z()) && std::isfinite(W());
		}
		else
		{
			return true;
		}
	}

	template<Arithmetic T>
	inline void Vector4<T>::Set(const T x, const T y, const T z, const T w) noexcept
	{
		X() = x;
		Y() = y;
		Z() = z;
		W() = w;
	}

	template<Arithmetic T>
	inline void Vector4<T>::Scale(const Vector4<T>& scale) noexcept
	{
		X() *= scale.X();
		Y() *= scale.Y();
		Z() *= scale.Z();
		W() *= scale.W();
	}

	template<Arithmetic T>
	constexpr T Dot(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return left.X() * right.X() + left.Y() * right.Y() + left.Z() * right.Z() + left.W() * right.W();
	}

	template<Arithmetic T>
	constexpr Vector4<T> Project(const Vector4<T>& vector, const Vector4<T>& target) noexcept
	{
		const Vector4<T>::ComputationalType multiplier = static_cast<Vector4<T>::ComputationalType>(Dot(vector, target)) / Dot(target, target);

		return target * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector4<T> Scale(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return Vector4<T>(left.X() * right.X(), left.Y() * right.Y(), left.Z() * right.Z(), left.W() * right.W());
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
		return std::format("({}, {}, {}, {})", X(), Y(), Z(), W());
	}

	template<Arithmetic T>
	inline T& Vector4<T>::operator [](const std::size_t index) noexcept
	{
		return m_components[index];
	}

	template<Arithmetic T>
	constexpr inline const T& Vector4<T>::operator [](const std::size_t index) const noexcept
	{
		return m_components[index];
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator +(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return Vector4<T>(left.X() + right.X(), left.Y() + right.Y(), left.Z() + right.Z(), left.W() + right.W());
	}

	template<Arithmetic T>
	constexpr inline Vector4<T> operator -(const Vector4<T>& vector) noexcept
	{
		return Vector4<T>(-vector.X(), -vector.Y(), -vector.Z(), -vector.W());
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator -(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return Vector4<T>(left.X() - right.X(), left.Y() - right.Y(), left.Z() - right.Z(), left.W() - right.W());
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator *(const Vector4<T>& vector, T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		return Vector4<T>(vector.X() * multiplier, vector.Y() * multiplier, vector.Z() * multiplier, vector.W() * multiplier);
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator *(const Vector4<T>& vector, const typename Vector4<T>::ComputationalType multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.X() * multiplier);
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.Y() * multiplier);
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.Z() * multiplier);
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.W() * multiplier);

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
	constexpr Vector4<T> operator /(const Vector4<T>& vector, const typename Vector4<T>::ComputationalType divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.X() / divisor);
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.Y() / divisor);
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.Z() / divisor);
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(vector.W() / divisor);

		return Vector4<T>(x, y, z, w);
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator +=(const Vector4<T>& other) noexcept
	{
		X() += other.X();
		Y() += other.Y();
		Z() += other.Z();
		W() += other.W();

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator -=(const Vector4<T>& other) noexcept
	{
		X() -= other.X();
		Y() -= other.Y();
		Z() -= other.Z();
		W() -= other.W();

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		X() *= multiplier;
		Y() *= multiplier;
		Z() *= multiplier;
		W() *= multiplier;

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator *=(const typename Vector4<T>::ComputationalType multiplier) noexcept
	{
		X() = RoundToIntegralIfPossible<ComputationalType, T>(X() * multiplier);
		Y() = RoundToIntegralIfPossible<ComputationalType, T>(Y() * multiplier);
		Z() = RoundToIntegralIfPossible<ComputationalType, T>(Z() * multiplier);
		W() = RoundToIntegralIfPossible<ComputationalType, T>(W() * multiplier);

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator /=(const ComputationalType divisor) noexcept
	{
		X() = RoundToIntegralIfPossible<ComputationalType, T>(X() / divisor);
		Y() = RoundToIntegralIfPossible<ComputationalType, T>(Y() / divisor);
		Z() = RoundToIntegralIfPossible<ComputationalType, T>(Z() / divisor);
		W() = RoundToIntegralIfPossible<ComputationalType, T>(W() / divisor);

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
