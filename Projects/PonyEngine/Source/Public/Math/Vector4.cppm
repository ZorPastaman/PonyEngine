/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <format>

export module PonyEngine.Math.Vector4;

import <array>;
import <cmath>;
import <cstddef>;
import <ostream>;
import <string>;

import PonyEngine.Math.Common;

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

		/// @brief Creates a default @p Vector4 where every component is zero initialized.
		[[nodiscard("Pure constructor")]]
		constexpr Vector4() noexcept;
		/// @brief Creates a @p Vector4 and assigns its components from the arguments.
		/// @param xParam Value to assign to the @p x component.
		/// @param yParam Value to assign to the @p y component.
		/// @param zParam Value to assign to the @p z component.
		/// @param wParam Value to assign to the @p w component.
		[[nodiscard("Pure constructor")]]
		constexpr Vector4(const T xParam, const T yParam, const T zParam, const T wParam) noexcept;
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		constexpr Vector4(const Vector4<T>& other) noexcept;

		constexpr ~Vector4() noexcept = default;

		/// @brief Computes a magnitude of a @p Vector.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		inline ComputationalType Magnitude() const noexcept;
		/// @brief Computes a squared magnitude of a @p Vector.
		/// @details This function is much faster than @p Magnitude() because it doesn't compute a square root.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		constexpr inline ComputationalType MagnitudeSquared() const noexcept;

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
		void Set(const T xParam, const T yParam, const T zParam, const T wParam) noexcept;

		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		inline T& operator [](const std::size_t index) noexcept;
		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		inline const T& operator [](const std::size_t index) const noexcept;

		/// @brief Copies the @p other to @a this.
		/// @param other @p Vector to copy.
		/// @return @a This.
		Vector4<T>& operator =(const Vector4<T>& other) noexcept;
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
		Vector4<T>& operator *=(const ComputationalType multiplier) noexcept;
		/// @brief Multiplies @a this by the @p other component-wise.
		/// @param other @p Vector to multiply.
		/// @return @a This.
		Vector4<T>& operator *=(const Vector4<T>& other) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor @p Vector divisor.
		/// @return @a This.
		Vector4<T>& operator /=(const ComputationalType divisor) noexcept;
		/// @brief Divides @a this by the @p divisor component-wise.
		/// @param other @p Vector to divide by.
		/// @return @a This.
		Vector4<T>& operator /=(const Vector4<T>& other) noexcept;

		/// @brief Creates a string representing a state of a @p Vector.
		///        The format is '(x, y, z, w)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		inline std::string ToString() const;

		static const Vector4<T> One; /// @brief Vector3(1, 1, 1, 1).
		static const Vector4<T> Zero; /// @brief Vector3(0, 0, 0, 0).
		static const Vector4<T> Negative; /// @brief Vector3(-1, -1, -1, -1).

		constexpr inline static const std::size_t ComponentCount = 4; /// @brief Component count. For any @p Vector4, it's always 4.

		T x;
		T y;
		T z;
		T w;
	};

	/// @brief Array of pointers to @p Vector components.
	/// @tparam T Component type.
	template<Arithmetic T>
	static const std::array<T Vector4<T>::*, Vector4<T>::ComponentCount> s_vector4ComponentPointers
		{ &Vector4<T>::x, &Vector4<T>::y, &Vector4<T>::z, &Vector4<T>::w };

	/// @brief Computes a dot product of two @p Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return Dot product.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector4<T>::ComputationalType Dot(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return static_cast<Vector4<T>::ComputationalType>(left.x) * static_cast<Vector4<T>::ComputationalType>(right.x) +
			static_cast<Vector4<T>::ComputationalType>(left.y) * static_cast<Vector4<T>::ComputationalType>(right.y) +
			static_cast<Vector4<T>::ComputationalType>(left.z) * static_cast<Vector4<T>::ComputationalType>(right.z) +
			static_cast<Vector4<T>::ComputationalType>(left.w) * static_cast<Vector4<T>::ComputationalType>(right.w);
	}

	/// @brief Projects the @p vector onto the @p target.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param target Projection target.
	/// @return Projected @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector4<T> Project(const Vector4<T>& vector, const Vector4<T>& target) noexcept
	{
		const Vector4<T>::ComputationalType multiplier = Dot(vector, target) / Dot(target, target);

		return target * multiplier;
	}

	/// @brief Linear interpolation between two @p Vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between two @p Vectors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector4<T> Lerp(const Vector4<T>& from, const Vector4<T>& to, const typename Vector4<T>::ComputationalType time)
	{
		return from + (to - from) * time;
	}

	/// @brief Checks if two @p Vectors are almost equal with a tolerance value.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the @p Vectors are almost equal; @a false otherwise.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Vector4<T>& left, const Vector4<T>& right,
		const typename Vector4<T>::ComputationalType tolerance = typename Vector4<T>::ComputationalType{0.00001})
	{
		return (left - right).MagnitudeSquared() < tolerance * tolerance;
	}

	/// @brief Checks if two @p Vectors are absolutely equal.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return @a True if the @p Vectors are absolutely equal; @a false otherwise.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr bool operator ==(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
	}

	/// @brief Checks if two @p Vectors are not absolutely equal.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return @a True if the @p Vectors are not absolutely equal; @a false otherwise.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr bool operator !=(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return left.x != right.x || left.y != right.y || left.z != right.z || left.w != right.w;
	}

	/// @brief Addition operator for two @p Vectors.
	/// @tparam T Component type.
	/// @param left Augend @p Vector.
	/// @param right Addend @p Vector.
	/// @return Sum @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator +(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return Vector4<T>(static_cast<T>(left.x + right.x), static_cast<T>(left.y + right.y), 
			static_cast<T>(left.z + right.z), static_cast<T>(left.w + right.w));
	}

	/// @brief Negates the @p vector.
	/// @tparam T Component type.
	/// @param vector @p Vector to negate.
	/// @return Negated @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator -(const Vector4<T>& vector) noexcept
	{
		return Vector4<T>(static_cast<T>(-vector.x), static_cast<T>(-vector.y), 
			static_cast<T>(-vector.z), static_cast<T>(-vector.w));
	}

	/// @brief Subtracts the @p right vector from the @p left vector.
	/// @tparam T Component type.
	/// @param left Minuend @p Vector.
	/// @param right Subtrahend @p Vector.
	/// @return Difference @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator -(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return Vector4<T>(static_cast<T>(left.x - right.x), static_cast<T>(left.y - right.y), 
			static_cast<T>(left.z - right.z), static_cast<T>(left.w - right.w));
	}

	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand @p Vector.
	/// @param multiplier Multiplier.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator *(const Vector4<T>& vector, const typename Vector4<T>::ComputationalType multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.x) * multiplier);
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.y) * multiplier);
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.z) * multiplier);
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.w) * multiplier);

		return Vector4<T>(x, y, z, w);
	}

	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector4<T> operator *(const typename Vector4<T>::ComputationalType multiplier, const Vector4<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	/// @brief Multiplies the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand @p Vector.
	/// @param right Multiplier @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator *(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.x) * static_cast<Vector4<T>::ComputationalType>(right.x));
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.y) * static_cast<Vector4<T>::ComputationalType>(right.y));
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.z) * static_cast<Vector4<T>::ComputationalType>(right.z));
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.w) * static_cast<Vector4<T>::ComputationalType>(right.w));

		return Vector4<T>(x, y, z, w);
	}

	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend @p Vector.
	/// @param divisor Divisor.
	/// @return Quotient @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator /(const Vector4<T>& vector, const typename Vector4<T>::ComputationalType divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.x) / divisor);
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.y) / divisor);
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.z) / divisor);
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(vector.w) / divisor);

		return Vector4<T>(x, y, z, w);
	}

	/// @brief Divides the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Dividend @p Vector.
	/// @param right Divisor @p Vector.
	/// @return Quotient @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator /(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.x) / static_cast<Vector4<T>::ComputationalType>(right.x));
		const T y = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.y) / static_cast<Vector4<T>::ComputationalType>(right.y));
		const T z = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.z) / static_cast<Vector4<T>::ComputationalType>(right.z));
		const T w = RoundToIntegralIfPossible<Vector4<T>::ComputationalType, T>(static_cast<Vector4<T>::ComputationalType>(left.w) / static_cast<Vector4<T>::ComputationalType>(right.w));

		return Vector4<T>(x, y, z, w);
	}

	/// @brief Puts @p Vector.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param vector Input source.
	/// @return @p stream.
	export template<Arithmetic T>
	inline std::ostream& operator <<(std::ostream& stream, const Vector4<T>& vector)
	{
		return stream << vector.ToString();
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
	inline Vector4<T>::ComputationalType Vector4<T>::Magnitude() const noexcept
	{
		return sqrt(MagnitudeSquared());
	}

	template<Arithmetic T>
	constexpr inline Vector4<T>::ComputationalType Vector4<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T>
	Vector4<T> Vector4<T>::Normalized() const noexcept
	{
		return *this * (T{1} / Magnitude());
	}

	template<Arithmetic T>
	inline void Vector4<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	bool Vector4<T>::IsFinite() const noexcept
	{
		return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w);
	}

	template<Arithmetic T>
	void Vector4<T>::Set(const T xParam, const T yParam, const T zParam, const T wParam) noexcept
	{
		x = xParam;
		y = yParam;
		z = zParam;
		w = wParam;
	}

	template<Arithmetic T>
	inline T& Vector4<T>::operator[](const std::size_t index) noexcept
	{
		return this->*s_vector4ComponentPointers<T>[index];
	}

	template<Arithmetic T>
	inline const T& Vector4<T>::operator[](const std::size_t index) const noexcept
	{
		return this->*s_vector4ComponentPointers<T>[index];
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator =(const Vector4<T>& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator +=(const Vector4<T>& other) noexcept
	{
		x = static_cast<T>(x + other.x);
		y = static_cast<T>(y + other.y);
		z = static_cast<T>(z + other.z);
		w = static_cast<T>(w + other.w);

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator -=(const Vector4<T>& other) noexcept
	{
		x = static_cast<T>(x - other.x);
		y = static_cast<T>(y - other.y);
		z = static_cast<T>(z - other.z);
		w = static_cast<T>(w - other.w);

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator *=(const typename Vector4<T>::ComputationalType multiplier) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) * multiplier);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) * multiplier);
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) * multiplier);
		w = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(w) * multiplier);

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator *=(const Vector4<T>& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) * static_cast<ComputationalType>(other.x));
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) * static_cast<ComputationalType>(other.y));
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) * static_cast<ComputationalType>(other.z));
		w = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(w) * static_cast<ComputationalType>(other.w));

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator /=(const ComputationalType divisor) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / divisor);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / divisor);
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) / divisor);
		w = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(w) / divisor);

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator /=(const Vector4<T>& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / static_cast<ComputationalType>(other.x));
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / static_cast<ComputationalType>(other.y));
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) / static_cast<ComputationalType>(other.z));
		w = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(w) / static_cast<ComputationalType>(other.w));

		return *this;
	}

	template<Arithmetic T>
	inline std::string Vector4<T>::ToString() const
	{
		return std::format("({}, {}, {}, {})", x, y, z, w);
	}

	template<Arithmetic T>
	const Vector4<T> Vector4<T>::One = Vector4<T>(T{1}, T{1}, T{1}, T{1});
	template<Arithmetic T>
	const Vector4<T> Vector4<T>::Zero = Vector4<T>(T{0}, T{0}, T{0}, T{0});
	template<Arithmetic T>
	const Vector4<T> Vector4<T>::Negative = Vector4<T>(T{-1}, T{-1}, T{-1}, T{-1});
}
