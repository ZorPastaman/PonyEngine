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

export module PonyEngine.Math.Vector2;

import <utility>;
import <cmath>;
import <algorithm>;
import <concepts>;
import <ostream>;
import <array>;

import PonyEngine.Math.Common;

namespace PonyEngine::Math
{
	/// @brief 2D vector implementation.
	/// @tparam T Component type.
	export template<Arithmetic T>
	struct Vector2 final
	{
	public:
		using ValueType = T; /// @brief Component type.
		using ComputationalType = ComputationalFor<T>; /// @brief Floating point type used in functions that require a floating point type.

		/// @brief Creates a default @p Vector2 where every component is zero initialized.
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector2() noexcept;
		/// @brief Creates a @p Vector2 and assigns its components from the arguments.
		/// @param xParam Value to assign to the @p x component.
		/// @param yParam Value to assign to the @p y component.
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector2(const T xParam, const T yParam) noexcept;
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector2(const Vector2<T>& other) noexcept;

		constexpr inline ~Vector2() noexcept = default;

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
		Vector2<T> Normalized() const noexcept;
		/// @brief Normalizes a @p Vector.
		inline void Normalize() noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Assigns arguments to @p Vector components.
		/// @param xParam X component.
		/// @param yParam Y component.
		inline void Set(const T xParam, const T yParam) noexcept;

		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 1].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y.
		[[nodiscard("Pure operator")]]
		inline T& operator [](const std::size_t index) noexcept;
		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 1].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y.
		[[nodiscard("Pure operator")]]
		inline const T& operator [](const std::size_t index) const noexcept;

		/// @brief Copies the @p other to @a this.
		/// @param other @p Vector to copy.
		/// @return @a This.
		inline Vector2<T>& operator =(const Vector2<T>& other) noexcept;
		/// @brief Adds the @p other to @a this.
		/// @param other @p Vector to add.
		/// @return @a This.
		Vector2<T>& operator +=(const Vector2<T>& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other @p Vector to subtract.
		/// @return @a This.
		Vector2<T>& operator -=(const Vector2<T>& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier @p Vector multiplier.
		/// @return @a This.
		Vector2<T>& operator *=(const ComputationalType multiplier) noexcept;
		/// @brief Multiplies @a this by the @p other component-wise.
		/// @param other @p Vector to multiply.
		/// @return @a This.
		Vector2<T>& operator *=(const Vector2<T>& other) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor @p Vector divisor.
		/// @return @a This.
		Vector2<T>& operator /=(const ComputationalType divisor) noexcept;
		/// @brief Divides @a this by the @p divisor component-wise.
		/// @param other @p Vector to divide by.
		/// @return @a This.
		Vector2<T>& operator /=(const Vector2<T>& other) noexcept;

		/// @brief Creates a string representing a state of a @p Vector.
		///        The format is '(x, y)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		inline std::string ToString() const;

		static const Vector2<T> Up; /// @brief Vector2(0, 1).
		static const Vector2<T> Down; /// @brief Vector2(0, -1).
		static const Vector2<T> Right; /// @brief Vector2(1, 0).
		static const Vector2<T> Left; /// @brief Vector2(-1, 0).
		static const Vector2<T> One; /// @brief Vector2(1, 1).
		static const Vector2<T> Zero; /// @brief Vector2(0, 0).
		static const Vector2<T> Negative; /// @brief Vector2(-1, -1).

		constexpr inline static const std::size_t ComponentCount = 2; /// @brief Component count. For any @p Vector2, it's always 2.

		T x;
		T y;
	};

	/// @brief Array of pointers to @p Vector components.
	/// @tparam T Component type.
	template<Arithmetic T>
	static const std::array<T Vector2<T>::*, Vector2<T>::ComponentCount> s_vector2ComponentPointers
		{ &Vector2<T>::x, &Vector2<T>::y };

	/// @brief Computes a dot product of two @ Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return Dot product.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T>::ComputationalType Dot(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return static_cast<Vector2<T>::ComputationalType>(left.x) * static_cast<Vector2<T>::ComputationalType>(right.x) +
			static_cast<Vector2<T>::ComputationalType>(left.y) * static_cast<Vector2<T>::ComputationalType>(right.y);
	}

	/// @brief Computes an angle between two @p Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector. Must be normalized.
	/// @param right Right @p Vector. Must be normalized.
	/// @return Angle in radians.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	inline Vector2<T>::ComputationalType Angle(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return std::acos(Dot(left, right));
	}

	/// @brief Computes a signed angle between two @p Vectors.
	///        Sign is positive if the rotation is counterclockwise.
	///        Sign is negative if the rotation is clockwise.
	/// @tparam T Component type.
	/// @param left Left @p Vector. Must be normalized.
	/// @param right Right @p Vector. Must be normalized.
	/// @return Angle in radians.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	Vector2<T>::ComputationalType AngleSigned(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		const Vector2<T>::ComputationalType zCross = left.x * right.y - left.y * right.x;
		const Vector2<T>::ComputationalType angle = Angle(left, right);

		return std::copysign(angle, zCross);
	}

	/// @brief Computes an angle between two @p Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector. Must be normalized.
	/// @param right Right @p Vector. Must be normalized.
	/// @return Angle in degrees.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	inline Vector2<T>::ComputationalType AngleDegrees(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return Angle(left, right) * RadToDeg<Vector2<T>::ComputationalType>;
	}

	/// @brief Computes a signed angle between two @p Vectors.
	///        Sign is positive if the rotation is counterclockwise.
	///        Sign is negative if the rotation is clockwise.
	/// @tparam T Component type.
	/// @param left Left @p Vector. Must be normalized.
	/// @param right Right @p Vector. Must be normalized.
	/// @return Angle in degrees.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	inline Vector2<T>::ComputationalType AngleSignedDegrees(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return AngleSigned(left, right) * RadToDeg<Vector2<T>::ComputationalType>;
	}

	/// @brief Projects the @p vector onto the @p target.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param target Projection target.
	/// @return Projected @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Project(const Vector2<T>& vector, const Vector2<T>& target) noexcept
	{
		const Vector2<T>::ComputationalType multiplier = Dot(vector, target) / Dot(target, target);

		return target * multiplier;
	}

	/// @brief Projects the @p vector onto a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be normalized.
	/// @return Projected @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> ProjectOnPlane(const Vector2<T>& vector, const Vector2<T>& normal) noexcept
	{
		return vector - normal * Dot(vector, normal);
	}

	/// @brief Reflects the @p vector off a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be normalized.
	/// @return Reflected @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Reflect(const Vector2<T>& vector, const Vector2<T>& normal) noexcept
	{
		const Vector2<T>::ComputationalType multiplier = typename Vector2<T>::ComputationalType{-2} * Dot(vector, normal);

		return vector + normal * multiplier;
	}

	/// @brief Linear interpolation between two @p Vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between two @p Vectors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Lerp(const Vector2<T>& from, const Vector2<T>& to, const typename Vector2<T>::ComputationalType time)
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
	constexpr bool AreAlmostEqual(const Vector2<T>& left, const Vector2<T>& right, 
		const typename Vector2<T>::ComputationalType tolerance = typename Vector2<T>::ComputationalType{0.00001})
	{
		return (left - right).MagnitudeSquared() < tolerance * tolerance;
	}

	/// @brief Checks if two @p Vectors are absolutely equal.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return @a True if the @p Vectors are absolutely equal; @a false otherwise.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr bool operator ==(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return left.x == right.x && left.y == right.y;
	}

	/// @brief Checks if two @p Vectors are not absolutely equal.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return @a True if the @p Vectors are not absolutely equal; @a false otherwise.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr bool operator !=(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return left.x != right.x || left.y != right.y;
	}

	/// @brief Addition operator for two @p Vectors.
	/// @tparam T Component type.
	/// @param left Augend @p Vector.
	/// @param right Addend @p Vector.
	/// @return Sum @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return Vector2<T>(static_cast<T>(left.x + right.x), static_cast<T>(left.y + right.y));
	}

	/// @brief Negates the @p vector.
	/// @tparam T Component type.
	/// @param vector @p Vector to negate.
	/// @return Negated @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator -(const Vector2<T>& vector) noexcept
	{
		return Vector2<T>(static_cast<T>(-vector.x), static_cast<T>(-vector.y));
	}

	/// @brief Subtracts the @p right vector from the @p left vector.
	/// @tparam T Component type.
	/// @param left Minuend @p Vector.
	/// @param right Subtrahend @p Vector.
	/// @return Difference @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return Vector2<T>(static_cast<T>(left.x - right.x), static_cast<T>(left.y - right.y));
	}

	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand @p Vector.
	/// @param multiplier Multiplier.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator *(const Vector2<T>& vector, const typename Vector2<T>::ComputationalType multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(vector.x) * multiplier);
		const T y = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(vector.y) * multiplier);

		return Vector2<T>(x, y);
	}

	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector2<T> operator *(const typename Vector2<T>::ComputationalType multiplier, const Vector2<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	/// @brief Multiplies the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand @p Vector.
	/// @param right Multiplier @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator *(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(left.x) * static_cast<Vector2<T>::ComputationalType>(right.x));
		const T y = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(left.y) * static_cast<Vector2<T>::ComputationalType>(right.y));

		return Vector2<T>(x, y);
	}

	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend @p Vector.
	/// @param divisor Divisor.
	/// @return Quotient @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator /(const Vector2<T>& vector, const typename Vector2<T>::ComputationalType divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(vector.x) / divisor);
		const T y = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(vector.y) / divisor);

		return Vector2<T>(x, y);
	}

	/// @brief Divides the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Dividend @p Vector.
	/// @param right Divisor @p Vector.
	/// @return Quotient @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator /(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(left.x) / static_cast<Vector2<T>::ComputationalType>(right.x));
		const T y = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(static_cast<Vector2<T>::ComputationalType>(left.y) / static_cast<Vector2<T>::ComputationalType>(right.y));

		return Vector2<T>(x, y);
	}

	/// @brief Puts @p Vector.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param vector Input source.
	/// @return @p stream.
	export template<Arithmetic T>
	inline std::ostream& operator <<(std::ostream& stream, const Vector2<T>& vector)
	{
		return stream << vector.ToString();
	}

	template<Arithmetic T>
	constexpr inline Vector2<T>::Vector2() noexcept :
		x{},
		y{}
	{
	}

	template<Arithmetic T>
	constexpr inline Vector2<T>::Vector2(const T xParam, const T yParam) noexcept :
		x{xParam},
		y{yParam}
	{
	}

	template<Arithmetic T>
	constexpr inline Vector2<T>::Vector2(const Vector2<T>& other) noexcept :
		Vector2(other.x, other.y)
	{
	}

	template<Arithmetic T>
	inline Vector2<T>::ComputationalType Vector2<T>::Magnitude() const noexcept
	{
		return sqrt(MagnitudeSquared());
	}

	template<Arithmetic T>
	constexpr inline Vector2<T>::ComputationalType Vector2<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T>
	Vector2<T> Vector2<T>::Normalized() const noexcept
	{
		return *this / Magnitude();
	}

	template<Arithmetic T>
	inline void Vector2<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	bool Vector2<T>::IsFinite() const noexcept
	{
		return std::isfinite(x) && std::isfinite(y);
	}

	template<Arithmetic T>
	inline void Vector2<T>::Set(const T xParam, const T yParam) noexcept
	{
		x = xParam;
		y = yParam;
	}

	template<Arithmetic T>
	inline T& Vector2<T>::operator [](const std::size_t index) noexcept
	{
		return this->*s_vector2ComponentPointers<T>[index];
	}

	template<Arithmetic T>
	inline const T& Vector2<T>::operator [](const std::size_t index) const noexcept
	{
		return this->*s_vector2ComponentPointers<T>[index];
	}

	template<Arithmetic T>
	inline Vector2<T>& Vector2<T>::operator =(const Vector2<T>& other) noexcept
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	template<Arithmetic T>
	Vector2<T>& Vector2<T>::operator +=(const Vector2<T>& other) noexcept
	{
		x = static_cast<T>(x + other.x);
		y = static_cast<T>(y + other.y);

		return *this;
	}

	template<Arithmetic T>
	Vector2<T>& Vector2<T>::operator -=(const Vector2<T>& other) noexcept
	{
		x = static_cast<T>(x - other.x);
		y = static_cast<T>(y - other.y);

		return *this;
	}

	template<Arithmetic T>
	Vector2<T>& Vector2<T>::operator *=(const Vector2<T>::ComputationalType multiplier) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) * multiplier);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) * multiplier);

		return *this;
	}

	template<Arithmetic T>
	Vector2<T>& Vector2<T>::operator *=(const Vector2<T>& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) * static_cast<ComputationalType>(other.x));
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) * static_cast<ComputationalType>(other.y));

		return *this;
	}

	template<Arithmetic T>
	Vector2<T>& Vector2<T>::operator /=(const ComputationalType divisor) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / divisor);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / divisor);

		return *this;
	}

	template<Arithmetic T>
	Vector2<T>& Vector2<T>::operator /=(const Vector2<T>& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / static_cast<ComputationalType>(other.x));
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / static_cast<ComputationalType>(other.y));

		return *this;
	}

	template<Arithmetic T>
	std::string Vector2<T>::ToString() const
	{
		return std::format("({}, {})", x, y);
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
