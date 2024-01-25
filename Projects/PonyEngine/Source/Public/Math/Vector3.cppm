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

export module PonyEngine.Math.Vector3;

import <array>;
import <cmath>;
import <cstddef>;
import <ostream>;
import <string>;

import PonyEngine.Math.Common;

namespace PonyEngine::Math
{
	/// @brief 3D vector implementation.
	/// @tparam T Component type.
	export template<Arithmetic T>
	struct Vector3 final
	{
	public:
		using ValueType = T; /// @brief Component type.
		using ComputationalType = ComputationalFor<T>; /// @brief Floating point type used in functions that require a floating point type.

		/// @brief Creates a default @p Vector3 where every component is zero initialized.
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector3() noexcept;
		/// @brief Creates a @p Vector3 and assigns its components from the arguments.
		/// @param xParam Value to assign to the @p x component.
		/// @param yParam Value to assign to the @p y component.
		/// @param zParam Value to assign to the @p z component.
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector3(const T xParam, const T yParam, const T zParam) noexcept;
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector3(const Vector3<T>& other) noexcept;

		constexpr inline ~Vector3() noexcept = default;

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
		Vector3<T> Normalized() const noexcept;
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
		inline void Set(const T xParam, const T yParam, const T zParam) noexcept;

		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 2].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z.
		[[nodiscard("Pure operator")]]
		inline T& operator [](const std::size_t index) noexcept;
		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 2].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z.
		[[nodiscard("Pure operator")]]
		inline const T& operator [](const std::size_t index) const noexcept;

		/// @brief Copies the @p other to @a this.
		/// @param other @p Vector to copy.
		/// @return @a This.
		inline Vector3<T>& operator =(const Vector3<T>& other) noexcept;
		/// @brief Adds the @p other to @a this.
		/// @param other @p Vector to add.
		/// @return @a This.
		Vector3<T>& operator +=(const Vector3<T>& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other @p Vector to subtract.
		/// @return @a This.
		Vector3<T>& operator -=(const Vector3<T>& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier @p Vector multiplier.
		/// @return @a This.
		Vector3<T>& operator *=(const ComputationalType multiplier) noexcept;
		/// @brief Multiplies @a this by the @p other component-wise.
		/// @param other @p Vector to multiply.
		/// @return @a This.
		Vector3<T>& operator *=(const Vector3<T>& other) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor @p Vector divisor.
		/// @return @a This.
		Vector3<T>& operator /=(const ComputationalType divisor) noexcept;
		/// @brief Divides @a this by the @p divisor component-wise.
		/// @param other @p Vector to divide by.
		/// @return @a This.
		Vector3<T>& operator /=(const Vector3<T>& other) noexcept;

		/// @brief Creates a string representing a state of a @p Vector.
		///        The format is '(x, y, z)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		inline std::string ToString() const;

		static const Vector3<T> Forward; /// @brief Vector3(0, 0, 1).
		static const Vector3<T> Back; /// @brief Vector3(0, 0, -1).
		static const Vector3<T> Up; /// @brief Vector3(0, 1, 0).
		static const Vector3<T> Down; /// @brief Vector3(0, -1, 0).
		static const Vector3<T> Right; /// @brief Vector3(1, 0, 0).
		static const Vector3<T> Left; /// @brief Vector3(-1, 0, 0).
		static const Vector3<T> One; /// @brief Vector3(1, 1, 1).
		static const Vector3<T> Zero; /// @brief Vector3(0, 0, 0).
		static const Vector3<T> Negative; /// @brief Vector3(-1, -1, -1).

		constexpr inline static const std::size_t ComponentCount = 3; /// @brief Component count. For any @p Vector3, it's always 3.

		T x;
		T y;
		T z;
	};

	/// @brief Array of pointers to @p Vector components.
	/// @tparam T Component type.
	template<Arithmetic T>
	static const std::array<T Vector3<T>::*, Vector3<T>::ComponentCount> s_vector3ComponentPointers
		{ &Vector3<T>::x, &Vector3<T>::y, &Vector3<T>::z };

	/// @brief Computes a dot product of two @p Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return Dot product.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T>::ComputationalType Dot(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return static_cast<Vector3<T>::ComputationalType>(left.x) * static_cast<Vector3<T>::ComputationalType>(right.x) +
			static_cast<Vector3<T>::ComputationalType>(left.y) * static_cast<Vector3<T>::ComputationalType>(right.y) +
			static_cast<Vector3<T>::ComputationalType>(left.z) * static_cast<Vector3<T>::ComputationalType>(right.z);
	}

	/// @brief Computes a cross product of two @p Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return Cross product.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Cross(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.y) * static_cast<Vector3<T>::ComputationalType>(right.z) - 
			static_cast<Vector3<T>::ComputationalType>(left.z) * static_cast<Vector3<T>::ComputationalType>(right.y));
		const T y = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.z) * static_cast<Vector3<T>::ComputationalType>(right.x) - 
			static_cast<Vector3<T>::ComputationalType>(left.x) * static_cast<Vector3<T>::ComputationalType>(right.z));
		const T z = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.x) * static_cast<Vector3<T>::ComputationalType>(right.y) - 
			static_cast<Vector3<T>::ComputationalType>(left.y) * static_cast<Vector3<T>::ComputationalType>(right.x));

		return Vector3<T>(x, y, z);
	}

	/// @brief Computes an angle between two @p Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector. Must be normalized.
	/// @param right Right @p Vector. Must be normalized.
	/// @return Angle in radians.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	inline Vector3<T>::ComputationalType Angle(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return std::acos(Dot(left, right));
	}

	/// @brief Computes a signed angle between two @p Vectors.
	///        Sign is copied from the sign of the dot product of the @p axis and the cross product of the @p left and @p right.
	/// @tparam T Component type.
	/// @param left Left @p Vector. Must be normalized.
	/// @param right Right @p Vector. Must be normalized.
	/// @param axis Sign reference.
	/// @return Angle in radians.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	Vector3<T>::ComputationalType AngleSigned(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept
	{
		const Vector3<T> cross = Cross(left, right);
		const Vector3<T>::ComputationalType dot = Dot(cross, axis);
		const Vector3<T>::ComputationalType angle = Angle(left, right);

		return std::copysign(angle, dot);
	}

	/// @brief Computes an angle between two @p Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector. Must be normalized.
	/// @param right Right @p Vector. Must be normalized.
	/// @return Angle in degrees.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	inline Vector3<T>::ComputationalType AngleDegrees(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Angle(left, right) * RadToDeg<Vector3<T>::ComputationalType>;
	}

	/// @brief Computes a signed angle between two @p Vectors.
	///        Sign is copied from the sign of the dot product of the @p axis and the cross product of the @p left and @p right.
	/// @tparam T Component type.
	/// @param left Left @p Vector. Must be normalized.
	/// @param right Right @p Vector. Must be normalized.
	/// @param axis Sign reference.
	/// @return Angle in degrees.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	inline Vector3<T>::ComputationalType AngleSignedDegrees(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept
	{
		return AngleSigned(left, right, axis) * RadToDeg<Vector3<T>::ComputationalType>;
	}

	/// @brief Projects the @p vector onto the @p target.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param target Projection target.
	/// @return Projected @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Project(const Vector3<T>& vector, const Vector3<T>& target) noexcept
	{
		const Vector3<T>::ComputationalType multiplier = Dot(vector, target) / Dot(target, target);

		return target * multiplier;
	}

	/// @brief Projects the @p vector onto a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be normalized.
	/// @return Projected @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> ProjectOnPlane(const Vector3<T>& vector, const Vector3<T>& normal) noexcept
	{
		return vector - normal * Dot(vector, normal);
	}

	/// @brief Reflects the @p vector off a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be normalized.
	/// @return Reflected @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Reflect(const Vector3<T>& vector, const Vector3<T>& normal) noexcept
	{
		const Vector3<T>::ComputationalType multiplier = typename Vector3<T>::ComputationalType{-2} * Dot(vector, normal);

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
	constexpr Vector3<T> Lerp(const Vector3<T>& from, const Vector3<T>& to, const typename Vector3<T>::ComputationalType time)
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
	constexpr bool AreAlmostEqual(const Vector3<T>& left, const Vector3<T>& right,
		const typename Vector3<T>::ComputationalType tolerance = typename Vector3<T>::ComputationalType{0.00001})
	{
		return (left - right).MagnitudeSquared() < tolerance * tolerance;
	}

	/// @brief Checks if two @p Vectors are absolutely equal.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return @a True if the @p Vectors are absolutely equal; @a false otherwise.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr bool operator ==(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}

	/// @brief Checks if two @p Vectors are not absolutely equal.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return @a True if the @p Vectors are not absolutely equal; @a false otherwise.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr bool operator !=(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return left.x != right.x || left.y != right.y || left.z != right.z;
	}

	/// @brief Addition operator for two @p Vectors.
	/// @tparam T Component type.
	/// @param left Augend @p Vector.
	/// @param right Addend @p Vector.
	/// @return Sum @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Vector3<T>(static_cast<T>(left.x + right.x), static_cast<T>(left.y + right.y), static_cast<T>(left.z + right.z));
	}

	/// @brief Negates the @p vector.
	/// @tparam T Component type.
	/// @param vector @p Vector to negate.
	/// @return Negated @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator -(const Vector3<T>& vector) noexcept
	{
		return Vector3<T>(static_cast<T>(-vector.x), static_cast<T>(-vector.y), static_cast<T>(-vector.z));
	}

	/// @brief Subtracts the @p right vector from the @p left vector.
	/// @tparam T Component type.
	/// @param left Minuend @p Vector.
	/// @param right Subtrahend @p Vector.
	/// @return Difference @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Vector3<T>(static_cast<T>(left.x - right.x), static_cast<T>(left.y - right.y), static_cast<T>(left.z - right.z));
	}

	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand @p Vector.
	/// @param multiplier Multiplier.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Vector3<T>& vector, const typename Vector3<T>::ComputationalType multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(vector.x) * multiplier);
		const T y = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(vector.y) * multiplier);
		const T z = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(vector.z) * multiplier);

		return Vector3<T>(x, y, z);
	}

	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector3<T> operator *(const typename Vector3<T>::ComputationalType multiplier, const Vector3<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	/// @brief Multiplies the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand @p Vector.
	/// @param right Multiplier @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.x) * static_cast<Vector3<T>::ComputationalType>(right.x));
		const T y = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.y) * static_cast<Vector3<T>::ComputationalType>(right.y));
		const T z = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.z) * static_cast<Vector3<T>::ComputationalType>(right.z));

		return Vector3<T>(x, y, z);
	}

	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend @p Vector.
	/// @param divisor Divisor.
	/// @return Quotient @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator /(const Vector3<T>& vector, const typename Vector3<T>::ComputationalType divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(vector.x) / divisor);
		const T y = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(vector.y) / divisor);
		const T z = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(vector.z) / divisor);

		return Vector3<T>(x, y, z);
	}

	/// @brief Divides the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Dividend @p Vector.
	/// @param right Divisor @p Vector.
	/// @return Quotient @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator /(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.x) / static_cast<Vector3<T>::ComputationalType>(right.x));
		const T y = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.y) / static_cast<Vector3<T>::ComputationalType>(right.y));
		const T z = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(static_cast<Vector3<T>::ComputationalType>(left.z) / static_cast<Vector3<T>::ComputationalType>(right.z));

		return Vector3<T>(x, y, z);
	}

	/// @brief Puts @p Vector.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param vector Input source.
	/// @return @p stream.
	export template<Arithmetic T>
	inline std::ostream& operator <<(std::ostream& stream, const Vector3<T>& vector)
	{
		return stream << vector.ToString();
	}

	template<Arithmetic T>
	constexpr inline Vector3<T>::Vector3() noexcept :
		x{},
		y{},
		z{}
	{
	}

	template<Arithmetic T>
	constexpr inline Vector3<T>::Vector3(const T xParam, const T yParam, const T zParam) noexcept :
		x{xParam},
		y{yParam},
		z{zParam}
	{
	}

	template<Arithmetic T>
	constexpr inline Vector3<T>::Vector3(const Vector3<T>& other) noexcept : 
		Vector3(other.x, other.y, other.z)
	{
	}

	template<Arithmetic T>
	inline Vector3<T>::ComputationalType Vector3<T>::Magnitude() const noexcept
	{
		return std::sqrt(MagnitudeSquared());
	}

	template<Arithmetic T>
	constexpr inline Vector3<T>::ComputationalType Vector3<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T>
	Vector3<T> Vector3<T>::Normalized() const noexcept
	{
		return *this * (T{1} / Magnitude());
	}

	template<Arithmetic T>
	inline void Vector3<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	bool Vector3<T>::IsFinite() const noexcept
	{
		return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
	}

	template<Arithmetic T>
	inline void Vector3<T>::Set(const T xParam, const T yParam, const T zParam) noexcept
	{
		x = xParam;
		y = yParam;
		z = zParam;
	}

	template<Arithmetic T>
	inline T& Vector3<T>::operator[](const std::size_t index) noexcept
	{
		return this->*s_vector3ComponentPointers<T>[index];
	}

	template<Arithmetic T>
	inline const T& Vector3<T>::operator[](const std::size_t index) const noexcept
	{
		return this->*s_vector3ComponentPointers<T>[index];
	}

	template<Arithmetic T>
	inline Vector3<T>& Vector3<T>::operator =(const Vector3<T>& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	template<Arithmetic T>
	Vector3<T>& Vector3<T>::operator +=(const Vector3<T>& other) noexcept
	{
		x = static_cast<T>(x + other.x);
		y = static_cast<T>(y + other.y);
		z = static_cast<T>(z + other.z);

		return *this;
	}

	template<Arithmetic T>
	Vector3<T>& Vector3<T>::operator -=(const Vector3<T>& other) noexcept
	{
		x = static_cast<T>(x - other.x);
		y = static_cast<T>(y - other.y);
		z = static_cast<T>(z - other.z);

		return *this;
	}

	template<Arithmetic T>
	Vector3<T>& Vector3<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) * multiplier);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) * multiplier);
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) * multiplier);

		return *this;
	}

	template<Arithmetic T>
	Vector3<T>& Vector3<T>::operator *=(const Vector3<T>& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) * static_cast<ComputationalType>(other.x));
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) * static_cast<ComputationalType>(other.y));
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) * static_cast<ComputationalType>(other.z));

		return *this;
	}

	template<Arithmetic T>
	Vector3<T>& Vector3<T>::operator /=(const ComputationalType divisor) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / divisor);
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / divisor);
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) / divisor);

		return *this;
	}
	template<Arithmetic T>
	Vector3<T>& Vector3<T>::operator /=(const Vector3<T>& other) noexcept
	{
		x = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(x) / static_cast<ComputationalType>(other.x));
		y = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(y) / static_cast<ComputationalType>(other.y));
		z = RoundToIntegralIfPossible<ComputationalType, T>(static_cast<ComputationalType>(z) / static_cast<ComputationalType>(other.z));

		return *this;
	}

	template<Arithmetic T>
	inline std::string Vector3<T>::ToString() const
	{
		return std::format("({}, {}, {})", x, y, z);
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
