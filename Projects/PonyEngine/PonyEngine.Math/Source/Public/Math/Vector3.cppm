/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Vector3;

import <array>;
import <cmath>;
import <concepts>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <type_traits>;

import :Common;

namespace PonyEngine::Math
{
	/// @brief 3D vector implementation.
	/// @tparam T Component type.
	export template<Arithmetic T>
	class Vector3 final
	{
	public:
		using ValueType = T; /// @brief Component type.
		using ComputationalType = ComputationalFor<T>; /// @brief Floating point type used in functions that require a floating point type.

		/// @brief Creates a @p Vector3 and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector3() noexcept;
		/// @brief Creates a @p Vector3 and assigns its components from the arguments.
		/// @param x Value to assign to the @p x component.
		/// @param y Value to assign to the @p y component.
		/// @param z Value to assign to the @p z component.
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector3(T x, T y, T z) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr inline Vector3(const Vector3<T>& other) noexcept = default;

		constexpr inline ~Vector3() noexcept = default;

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
		/// @brief Gets a pointer to the data array. The order is x, y, z.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		inline T* Data() noexcept;
		/// @brief Gets a pointer to the const data array. The order is x, y, z.
		/// @return Const data pointer.
		[[nodiscard("Pure function")]]
		inline const T* Data() const noexcept;

		/// @brief Computes a magnitude of a @p Vector.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		ComputationalType Magnitude() const noexcept;
		/// @brief Computes a squared magnitude of a @p Vector.
		/// @details This function is much faster than @p Magnitude() because it doesn't compute a square root.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		constexpr inline T MagnitudeSquared() const noexcept;

		/// @brief Computes a @p Vector normalized from this one.
		/// @details This vector must be non-zero.
		/// @return Normalized @p Vector.
		[[nodiscard("Pure function")]]
		Vector3<T> Normalized() const noexcept;
		/// @brief Normalizes a @p Vector.
		/// @details This vector must be non-zero.
		inline void Normalize() noexcept;

		/// @brief Computed a @p Vector inversed to this one.
		/// @return Inversed @p Vector.
		[[nodiscard("Pure function")]]
		constexpr inline Vector3<T> Inversed() const noexcept;
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
		inline void Set(T x, T y, T z) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale @p Vector to multiply by.
		inline void Scale(const Vector3<T>& scale) noexcept;

		/// @brief Creates a string representing a state of a @p Vector.
		///        The format is '(x, y, z)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		inline std::string ToString() const;

		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 2].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z.
		[[nodiscard("Pure operator")]]
		inline T& operator [](std::size_t index) noexcept;
		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 2].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z.
		[[nodiscard("Pure operator")]]
		constexpr inline const T& operator [](std::size_t index) const noexcept;

		inline Vector3<T>& operator =(const Vector3<T>& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other @p Vector to add.
		/// @return @a This.
		inline Vector3<T>& operator +=(const Vector3<T>& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other @p Vector to subtract.
		/// @return @a This.
		inline Vector3<T>& operator -=(const Vector3<T>& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier @p Vector multiplier.
		/// @return @a This.
		inline Vector3<T>& operator *=(T multiplier) noexcept requires(std::is_integral_v<T>);
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier @p Vector multiplier.
		/// @return @a This.
		inline Vector3<T>& operator *=(ComputationalType multiplier) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor @p Vector divisor.
		/// @return @a This.
		inline Vector3<T>& operator /=(ComputationalType divisor) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr inline bool operator ==(const Vector3<T>& other) const noexcept = default;

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

	private:
		std::array<T, ComponentCount> m_components; /// @brief Component array in order x, y, z.
	};

	/// @brief Computes a dot product of two @p Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return Dot product.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr inline T Dot(const Vector3<T>& left, const Vector3<T>& right) noexcept;

	/// @brief Computes a cross product of two @p Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @return Cross product.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Cross(const Vector3<T>& left, const Vector3<T>& right) noexcept;

	/// @brief Computes an angle between two @p Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector. Must be normalized.
	/// @param right Right @p Vector. Must be normalized.
	/// @return Angle in radians.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	Vector3<T>::ComputationalType Angle(const Vector3<T>& left, const Vector3<T>& right) noexcept;
	/// @brief Computes a signed angle between two @p Vectors.
	///        Sign is copied from the sign of the dot product of the @p axis and the cross product of the @p left and @p right.
	/// @tparam T Component type.
	/// @param left Left @p Vector. Must be normalized.
	/// @param right Right @p Vector. Must be normalized.
	/// @param axis Sign reference.
	/// @return Angle in radians.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	Vector3<T>::ComputationalType AngleSigned(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept;
	/// @brief Computes an angle between two @p Vectors.
	/// @tparam T Component type.
	/// @param left Left @p Vector. Must be normalized.
	/// @param right Right @p Vector. Must be normalized.
	/// @return Angle in degrees.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	inline Vector3<T>::ComputationalType AngleDegrees(const Vector3<T>& left, const Vector3<T>& right) noexcept;
	/// @brief Computes a signed angle between two @p Vectors.
	///        Sign is copied from the sign of the dot product of the @p axis and the cross product of the @p left and @p right.
	/// @tparam T Component type.
	/// @param left Left @p Vector. Must be normalized.
	/// @param right Right @p Vector. Must be normalized.
	/// @param axis Sign reference.
	/// @return Angle in degrees.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	inline Vector3<T>::ComputationalType AngleSignedDegrees(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept;

	/// @brief Projects the @p vector onto the @p target.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param target Projection target.
	/// @return Projected @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Project(const Vector3<T>& vector, const Vector3<T>& target) noexcept;
	/// @brief Projects the @p vector onto a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be normalized.
	/// @return Projected @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> ProjectOnPlane(const Vector3<T>& vector, const Vector3<T>& normal) noexcept;

	/// @brief Reflects the @p vector off a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be normalized.
	/// @return Reflected @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Reflect(const Vector3<T>& vector, const Vector3<T>& normal) noexcept;

	/// @brief Multiplies the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand @p Vector.
	/// @param right Multiplier @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr inline Vector3<T> Scale(const Vector3<T>& left, const Vector3<T>& right) noexcept;

	/// @brief Linear interpolation between two @p Vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between two @p Vectors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Lerp(const Vector3<T>& from, const Vector3<T>& to, typename Vector3<T>::ComputationalType time) noexcept;

	/// @brief Checks if two @p Vectors are almost equal with a tolerance value.
	/// @tparam T Component type.
	/// @param left Left @p Vector.
	/// @param right Right @p Vector.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the @p Vectors are almost equal; @a false otherwise.
	export template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Vector3<T>& left, const Vector3<T>& right, typename Vector3<T>::ComputationalType tolerance = typename Vector3<T>::ComputationalType{0.00001}) noexcept;

	/// @brief Addition operator for two @p Vectors.
	/// @tparam T Component type.
	/// @param left Augend @p Vector.
	/// @param right Addend @p Vector.
	/// @return Sum @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right) noexcept;

	/// @brief Negates the @p vector.
	/// @tparam T Component type.
	/// @param vector @p Vector to negate.
	/// @return Negated @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector3<T> operator -(const Vector3<T>& vector) noexcept;

	/// @brief Subtracts the @p right vector from the @p left vector.
	/// @tparam T Component type.
	/// @param left Minuend @p Vector.
	/// @param right Subtrahend @p Vector.
	/// @return Difference @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right) noexcept;

	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand @p Vector.
	/// @param multiplier Multiplier.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector3<T> operator *(const Vector3<T>& vector, T multiplier) noexcept requires(std::is_integral_v<T>);
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand @p Vector.
	/// @param multiplier Multiplier.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector3<T> operator *(const Vector3<T>& vector, typename Vector3<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector3<T> operator *(T multiplier, const Vector3<T>& vector) noexcept requires(std::is_integral_v<T>);
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand @p Vector.
	/// @return Product @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector3<T> operator *(typename Vector3<T>::ComputationalType multiplier, const Vector3<T>& vector) noexcept;

	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend @p Vector.
	/// @param divisor Divisor.
	/// @return Quotient @p Vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Vector3<T> operator /(const Vector3<T>& vector, typename Vector3<T>::ComputationalType divisor) noexcept;

	/// @brief Puts @p Vector.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param vector Input source.
	/// @return @p stream.
	export template<Arithmetic T>
	inline std::ostream& operator <<(std::ostream& stream, const Vector3<T>& vector);

	template<Arithmetic T>
	constexpr inline Vector3<T>::Vector3() noexcept :
		Vector3(T{}, T{}, T{})
	{
	}

	template<Arithmetic T>
	constexpr inline Vector3<T>::Vector3(const T x, const T y, const T z) noexcept :
		m_components{x, y, z}
	{
	}

	template<Arithmetic T>
	inline T& Vector3<T>::X() noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr inline const T& Vector3<T>::X() const noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	inline T& Vector3<T>::Y() noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr inline const T& Vector3<T>::Y() const noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	inline T& Vector3<T>::Z() noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr inline const T& Vector3<T>::Z() const noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	inline T* Vector3<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	inline const T* Vector3<T>::Data() const noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	Vector3<T>::ComputationalType Vector3<T>::Magnitude() const noexcept
	{
		return std::sqrt(static_cast<Vector3<T>::ComputationalType>(MagnitudeSquared()));
	}

	template<Arithmetic T>
	constexpr inline T Vector3<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T>
	Vector3<T> Vector3<T>::Normalized() const noexcept
	{
		return *this * (Vector3<T>::ComputationalType{1} / Magnitude());
	}

	template<Arithmetic T>
	inline void Vector3<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	inline constexpr Vector3<T> Vector3<T>::Inversed() const noexcept
	{
		return Vector3<T>(Z(), Y(), X());
	}

	template<Arithmetic T>
	inline void Vector3<T>::Inverse() noexcept
	{
		*this = Inversed();
	}

	template<Arithmetic T>
	bool Vector3<T>::IsFinite() const noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return std::isfinite(X()) && std::isfinite(Y()) && std::isfinite(Z());
		}
		else
		{
			return true;
		}
	}

	template<Arithmetic T>
	inline void Vector3<T>::Set(const T x, const T y, const T z) noexcept
	{
		X() = x;
		Y() = y;
		Z() = z;
	}

	template<Arithmetic T>
	inline void Vector3<T>::Scale(const Vector3<T>& scale) noexcept
	{
		X() *= scale.X();
		Y() *= scale.Y();
		Z() *= scale.Z();
	}

	template<Arithmetic T>
	constexpr inline T Dot(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return left.X() * right.X() + left.Y() * right.Y() + left.Z() * right.Z();
	}

	template<Arithmetic T>
	constexpr Vector3<T> Cross(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const T x = left.Y() * right.Z() - left.Z() * right.Y();
		const T y = left.Z() * right.X() - left.X() * right.Z();
		const T z = left.X() * right.Y() - left.Y() * right.X();

		return Vector3<T>(x, y, z);
	}

	template<Arithmetic T>
	Vector3<T>::ComputationalType Angle(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return std::acos(static_cast<Vector3<T>::ComputationalType>(Dot(left, right)));
	}

	template<Arithmetic T>
	Vector3<T>::ComputationalType AngleSigned(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept
	{
		const Vector3<T> cross = Cross(left, right);
		const T dot = Dot(cross, axis);
		const Vector3<T>::ComputationalType angle = Angle(left, right);

		return std::copysign(angle, static_cast<Vector3<T>::ComputationalType>(dot));
	}

	template<Arithmetic T>
	inline Vector3<T>::ComputationalType AngleDegrees(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Angle(left, right) * RadToDeg<Vector3<T>::ComputationalType>;
	}

	template<Arithmetic T>
	inline Vector3<T>::ComputationalType AngleSignedDegrees(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept
	{
		return AngleSigned(left, right, axis) * RadToDeg<Vector3<T>::ComputationalType>;
	}

	template<Arithmetic T>
	constexpr Vector3<T> Project(const Vector3<T>& vector, const Vector3<T>& target) noexcept
	{
		const Vector3<T>::ComputationalType multiplier = static_cast<Vector3<T>::ComputationalType>(Dot(vector, target)) / Dot(target, target);

		return target * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector3<T> ProjectOnPlane(const Vector3<T>& vector, const Vector3<T>& normal) noexcept
	{
		return vector - normal * Dot(vector, normal);
	}

	template<Arithmetic T>
	constexpr Vector3<T> Reflect(const Vector3<T>& vector, const Vector3<T>& normal) noexcept
	{
		const T multiplier = T{-2} * Dot(vector, normal);

		return vector + normal * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector3<T> Scale(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Vector3<T>(left.X() * right.X(), left.Y() * right.Y(), left.Z() * right.Z());
	}

	template<Arithmetic T>
	constexpr Vector3<T> Lerp(const Vector3<T>& from, const Vector3<T>& to, const typename Vector3<T>::ComputationalType time) noexcept
	{
		return from + (to - from) * time;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Vector3<T>& left, const Vector3<T>& right, const typename Vector3<T>::ComputationalType tolerance) noexcept
	{
		return (left - right).MagnitudeSquared() < tolerance * tolerance;
	}

	template<Arithmetic T>
	inline std::string Vector3<T>::ToString() const
	{
		return std::format("({}, {}, {})", X(), Y(), Z());
	}

	template<Arithmetic T>
	inline T& Vector3<T>::operator [](const std::size_t index) noexcept
	{
		return m_components[index];
	}

	template<Arithmetic T>
	constexpr inline const T& Vector3<T>::operator [](const std::size_t index) const noexcept
	{
		return m_components[index];
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Vector3<T>(left.X() + right.X(), left.Y() + right.Y(), left.Z() + right.Z());
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> operator -(const Vector3<T>& vector) noexcept
	{
		return Vector3<T>(-vector.X(), -vector.Y(), -vector.Z());
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return Vector3<T>(left.X() - right.X(), left.Y() - right.Y(), left.Z() - right.Z());
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> operator *(const Vector3<T>& vector, const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		return Vector3<T>(vector.X() * multiplier, vector.Y() * multiplier, vector.Z() * multiplier);
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> operator *(const Vector3<T>& vector, const typename Vector3<T>::ComputationalType multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(vector.X() * multiplier);
		const T y = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(vector.Y() * multiplier);
		const T z = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(vector.Z() * multiplier);

		return Vector3<T>(x, y, z);
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> operator *(const T multiplier, const Vector3<T>& vector) noexcept requires(std::is_integral_v<T>)
	{
		return vector * multiplier;
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> operator *(const typename Vector3<T>::ComputationalType multiplier, const Vector3<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> operator /(const Vector3<T>& vector, const typename Vector3<T>::ComputationalType divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(vector.X() / divisor);
		const T y = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(vector.Y() / divisor);
		const T z = RoundToIntegralIfPossible<Vector3<T>::ComputationalType, T>(vector.Z() / divisor);

		return Vector3<T>(x, y, z);
	}

	template<Arithmetic T>
	inline Vector3<T>& Vector3<T>::operator +=(const Vector3<T>& other) noexcept
	{
		X() += other.X();
		Y() += other.Y();
		Z() += other.Z();

		return *this;
	}

	template<Arithmetic T>
	inline Vector3<T>& Vector3<T>::operator -=(const Vector3<T>& other) noexcept
	{
		X() -= other.X();
		Y() -= other.Y();
		Z() -= other.Z();

		return *this;
	}

	template<Arithmetic T>
	inline Vector3<T>& Vector3<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		X() *= multiplier;
		Y() *= multiplier;
		Z() *= multiplier;

		return *this;
	}

	template<Arithmetic T>
	inline Vector3<T>& Vector3<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		X() = RoundToIntegralIfPossible<ComputationalType, T>(X() * multiplier);
		Y() = RoundToIntegralIfPossible<ComputationalType, T>(Y() * multiplier);
		Z() = RoundToIntegralIfPossible<ComputationalType, T>(Z() * multiplier);

		return *this;
	}

	template<Arithmetic T>
	inline Vector3<T>& Vector3<T>::operator /=(const ComputationalType divisor) noexcept
	{
		X() = RoundToIntegralIfPossible<ComputationalType, T>(X() / divisor);
		Y() = RoundToIntegralIfPossible<ComputationalType, T>(Y() / divisor);
		Z() = RoundToIntegralIfPossible<ComputationalType, T>(Z() / divisor);

		return *this;
	}

	template<Arithmetic T>
	inline std::ostream& operator <<(std::ostream& stream, const Vector3<T>& vector)
	{
		return stream << vector.ToString();
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
