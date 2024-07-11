/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Vector2;

import <algorithm>;
import <array>;
import <cmath>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <type_traits>;

import :ArrayArithmetics;
import :Common;

export namespace PonyEngine::Math
{
	/// @brief 2D vector implementation.
	/// @tparam T Component type.
	template<Arithmetic T>
	class Vector2 final
	{
	public:
		using ValueType = T; ///< Component type.
		using ComputationalType = ComputationalFor<T>; ///< Floating point type used in functions that require a floating point type.

		static constexpr std::size_t ComponentCount = 2; ///< Component count. For any vector, it's always 2.

		struct Predefined; ///< Predefined vectors.

		/// @brief Creates a vector and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr Vector2() noexcept = default;
		/// @brief Creates a vector and assigns its components from the arguments.
		/// @param x X-component.
		/// @param y Y-component.
		[[nodiscard("Pure constructor")]]
		constexpr Vector2(T x, T y) noexcept;
		/// @brief Creates a vector and assigns its components from the @p components array.
		/// @param components Component array. Its length must be at least 2.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Vector2(const T* components) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Vector2(const Vector2& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Vector2(Vector2&& other) noexcept = default;

		constexpr ~Vector2() noexcept = default;

		/// @brief Gets the x-component.
		/// @return X-component.
		[[nodiscard("Pure function")]]
		constexpr T& X() noexcept;
		/// @brief Gets the x-component.
		/// @return X-component.
		[[nodiscard("Pure function")]]
		constexpr const T& X() const noexcept;
		/// @brief Gets the y-component.
		/// @return Y-component.
		[[nodiscard("Pure function")]]
		constexpr T& Y() noexcept;
		/// @brief Gets the y-component.
		/// @return Y-component.
		[[nodiscard("Pure function")]]
		constexpr const T& Y() const noexcept;
		/// @brief Gets the data pointer to the array of 2 elements. The order is x, y.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		constexpr T* Data() noexcept;
		/// @brief Gets the data pointer to the array of 2 elements. The order is x, y.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		constexpr const T* Data() const noexcept;

		/// @brief Computes a magnitude of the vector.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		ComputationalType Magnitude() const noexcept;
		/// @brief Computes a squared magnitude of the vector.
		/// @remark This function is much faster than @p Magnitude() because it doesn't compute a square root.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		constexpr T MagnitudeSquared() const noexcept;

		/// @brief Computes a vector normalized from this one.
		/// @note If the magnitude of the vector is 0, the result is undefined.
		/// @return Normalized vector.
		[[nodiscard("Pure function")]]
		Vector2 Normalized() const noexcept requires(std::is_floating_point_v<T>);
		/// @brief Normalizes the vector.
		/// @note If the magnitude of the vector is 0, the result is undefined.
		void Normalize() noexcept requires(std::is_floating_point_v<T>);

		/// @brief Gets a minimum value among the components.
		/// @return Minimum component value.
		[[nodiscard("Pure function")]]
		constexpr T Min() const noexcept;
		/// @brief Gets a maximum value among the components.
		/// @return Maximum component value.
		[[nodiscard("Pure function")]]
		constexpr T Max() const noexcept;
		/// @brief Sums all the components and returns the result.
		/// @return Sum.
		[[nodiscard("Pure function")]]
		constexpr T Sum() const noexcept;

		/// @brief Swaps the components and returns a vector in order y, x.
		/// @return Swapped vector.
		[[nodiscard("Pure function")]]
		constexpr Vector2 Swapped() const noexcept;
		/// @brief Swaps the components in the vector. The order is y, x.
		constexpr void Swap() noexcept;

		/// @brief Checks if all the components are zero.
		/// @return @a True if this vector components are zero; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsZero() const noexcept;
		/// @brief Checks if all the components are almost zero with the tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return  @a True if this vector components are almost zero; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostZero(T tolerance = T{0.00001}) const noexcept requires(std::is_floating_point_v<T>);
		/// @brief Checks if this vector is unit.
		/// @return @a True if this vector is unit; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsUnit() const noexcept;
		/// @brief Checks if this vector is almost unit with the tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if this vector is almost unit; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsAlmostUnit(T tolerance = T{0.00001}) const noexcept requires(std::is_floating_point_v<T>);
		/// @brief Checks if this vector is uniform.
		/// @return @a True if this vector is uniform; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsUniform() const noexcept;
		/// @brief Checks if this vector is almost uniform with the tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if this vector is almost uniform; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsAlmostUniform(T tolerance = T{0.00001}) const noexcept requires(std::is_floating_point_v<T>);

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept requires(std::is_floating_point_v<T>);

		/// @brief Assigns arguments to the vector components.
		/// @param x X-component.
		/// @param y Y-component.
		constexpr void Set(T x, T y) noexcept;
		/// @brief Assigns arguments from the @p components array.
		/// @param components Component array. Its length must be at least 2.
		constexpr void Set(const T* components) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale Vector to multiply by.
		constexpr void Scale(const Vector2& scale) noexcept;

		/// @brief Creates a string representing a state of the vector. The format is '(x, y)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Casts all the components to the @p U and returns a new vector with those components.
		/// @tparam U Target component type.
		template<Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Vector2<U>() const noexcept;

		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, 1].
		/// @return Component. 0 -> x, 1 -> y.
		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, 1].
		/// @return Component. 0 -> x, 1 -> y.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr Vector2& operator =(const Vector2& other) noexcept = default;
		constexpr Vector2& operator =(Vector2&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Vector to add.
		/// @return @a This.
		constexpr Vector2& operator +=(const Vector2& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Vector to subtract.
		/// @return @a This.
		constexpr Vector2& operator -=(const Vector2& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		constexpr Vector2& operator *=(T multiplier) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		constexpr Vector2& operator *=(ComputationalType multiplier) noexcept requires(std::is_integral_v<T>);
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Vector divisor.
		/// @return @a This.
		constexpr Vector2& operator /=(T divisor) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Vector divisor.
		/// @return @a This.
		constexpr Vector2& operator /=(ComputationalType divisor) noexcept requires(std::is_integral_v<T>);

		/// @brief Checks if the two vectors are equal.
		/// @param other Other vector.
		/// @return @a True if they are equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Vector2& other) const noexcept;

	private:
		std::array<T, ComponentCount> components; ///< Component array in order x, y.
	};

	/// @brief Computes a dot product of the two vectors.
	/// @tparam T Component type.
	/// @param left Left vector.
	/// @param right Right vector.
	/// @return Dot product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Dot(const Vector2<T>& left, const Vector2<T>& right) noexcept;

	/// @brief Computes an angle between the two vectors.
	/// @tparam T Component type.
	/// @param left Left vector. Must be unit.
	/// @param right Right vector. Must be unit.
	/// @return Angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T Angle(const Vector2<T>& left, const Vector2<T>& right) noexcept;
	/// @brief Computes a signed angle between the two vectors.
	/// @tparam T Component type.
	/// @param left Left vector. Must be unit.
	/// @param right Right vector. Must be unit.
	/// @return Angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T AngleSigned(const Vector2<T>& left, const Vector2<T>& right) noexcept;

	/// @brief Projects the @p vector onto the @p normal.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Projection target. Must be unit.
	/// @return Projected vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Project(const Vector2<T>& vector, const Vector2<T>& normal) noexcept;
	/// @brief Projects the @p vector onto a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be unit.
	/// @return Projected vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> ProjectOnPlane(const Vector2<T>& vector, const Vector2<T>& normal) noexcept;

	/// @brief Reflects the @p vector off a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be unit.
	/// @return Reflected vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Reflect(const Vector2<T>& vector, const Vector2<T>& normal) noexcept;

	/// @brief Multiplies the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Scale(const Vector2<T>& left, const Vector2<T>& right) noexcept;

	/// @brief Linear interpolation between the two vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between the two vectors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated vector.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Lerp(const Vector2<T>& from, const Vector2<T>& to, typename Vector2<T>::ComputationalType time) noexcept;

	/// @brief Checks if the two vectors are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left vector.
	/// @param right Right vector.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the vectors are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Vector2<T>& left, const Vector2<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Sums the @p left vector and the @p right vector.
	/// @tparam T Component type.
	/// @param left Augend.
	/// @param right Addend.
	/// @return Sum.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right) noexcept;

	/// @brief Negates the @p vector.
	/// @tparam T Component type.
	/// @param vector Vector to negate.
	/// @return Negated vector.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator -(const Vector2<T>& vector) noexcept;

	/// @brief Subtracts the @p right vector from the @p left vector.
	/// @tparam T Component type.
	/// @param left Minuend.
	/// @param right Subtrahend.
	/// @return Difference.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right) noexcept;

	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator *(const Vector2<T>& vector, T multiplier) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator *(const Vector2<T>& vector, typename Vector2<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator *(T multiplier, const Vector2<T>& vector) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator *(typename Vector2<T>::ComputationalType multiplier, const Vector2<T>& vector) noexcept;

	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator /(const Vector2<T>& vector, T divisor) noexcept;
	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator /(const Vector2<T>& vector, typename Vector2<T>::ComputationalType divisor) noexcept;

	/// @brief Puts @p Vector.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param vector Input source.
	/// @return @p stream.
	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Vector2<T>& vector);

	template<Arithmetic T>
	struct Vector2<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr Vector2 Up = Vector2(T{0}, T{1}); ///< Vector2(0, 1).
		static constexpr Vector2 Down = Vector2(T{0}, T{-1}); ///< Vector2(0, -1).
		static constexpr Vector2 Right = Vector2(T{1}, T{0}); /// Vector2(1, 0).
		static constexpr Vector2 Left = Vector2(T{-1}, T{0}); ///< Vector2(-1, 0).
		static constexpr Vector2 One = Vector2(T{1}, T{1}); ///< Vector2(1, 1).
		static constexpr Vector2 Zero = Vector2(T{0}, T{0}); ///< Vector2(0, 0).
		static constexpr Vector2 Negative = Vector2(T{-1}, T{-1}); ///< Vector2(-1, -1).
	};
}

namespace PonyEngine::Math
{
	template<Arithmetic T>
	constexpr Vector2<T>::Vector2(const T x, const T y) noexcept :
		components{x, y}
	{
	}

	template<Arithmetic T>
	constexpr Vector2<T>::Vector2(const T* const components) noexcept
	{
		Set(components);
	}

	template<Arithmetic T>
	constexpr T& Vector2<T>::X() noexcept
	{
		return components[0];
	}

	template<Arithmetic T>
	constexpr const T& Vector2<T>::X() const noexcept
	{
		return components[0];
	}

	template<Arithmetic T>
	constexpr T& Vector2<T>::Y() noexcept
	{
		return components[1];
	}

	template<Arithmetic T>
	constexpr const T& Vector2<T>::Y() const noexcept
	{
		return components[1];
	}

	template<Arithmetic T>
	constexpr T* Vector2<T>::Data() noexcept
	{
		return components.data();
	}

	template<Arithmetic T>
	constexpr const T* Vector2<T>::Data() const noexcept
	{
		return components.data();
	}

	template<Arithmetic T>
	typename Vector2<T>::ComputationalType Vector2<T>::Magnitude() const noexcept
	{
		return std::sqrt(static_cast<ComputationalType>(MagnitudeSquared()));
	}

	template<Arithmetic T>
	constexpr T Vector2<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T>
	Vector2<T> Vector2<T>::Normalized() const noexcept requires(std::is_floating_point_v<T>)
	{
		return *this * (T{1} / Magnitude());
	}

	template<Arithmetic T>
	void Vector2<T>::Normalize() noexcept requires(std::is_floating_point_v<T>)
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	constexpr T Vector2<T>::Min() const noexcept
	{
		return std::min(X(), Y());
	}

	template<Arithmetic T>
	constexpr T Vector2<T>::Max() const noexcept
	{
		return std::max(X(), Y());
	}

	template<Arithmetic T>
	constexpr T Vector2<T>::Sum() const noexcept
	{
		return X() + Y();
	}

	template<Arithmetic T>
	constexpr Vector2<T> Vector2<T>::Swapped() const noexcept
	{
		return Vector2(Y(), X());
	}

	template<Arithmetic T>
	constexpr void Vector2<T>::Swap() noexcept
	{
		std::swap(X(), Y());
	}

	template<Arithmetic T>
	constexpr bool Vector2<T>::IsZero() const noexcept
	{
		return *this == Predefined::Zero;
	}

	template<Arithmetic T>
	constexpr bool Vector2<T>::IsAlmostZero(const T tolerance) const noexcept requires(std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(*this, Predefined::Zero, tolerance);
	}

	template<Arithmetic T>
	constexpr bool Vector2<T>::IsUnit() const noexcept
	{
		return MagnitudeSquared() == T{1};
	}

	template<Arithmetic T>
	bool Vector2<T>::IsAlmostUnit(const T tolerance) const noexcept requires(std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(MagnitudeSquared(), T{1}, tolerance);
	}

	template<Arithmetic T>
	constexpr bool Vector2<T>::IsUniform() const noexcept
	{
		return X() == Y();
	}

	template<Arithmetic T>
	bool Vector2<T>::IsAlmostUniform(const T tolerance) const noexcept requires(std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(X(), Y(), tolerance);
	}

	template<Arithmetic T>
	bool Vector2<T>::IsFinite() const noexcept requires(std::is_floating_point_v<T>)
	{
		return Math::IsFinite(Data(), ComponentCount);
	}

	template<Arithmetic T>
	constexpr void Vector2<T>::Set(const T x, const T y) noexcept
	{
		X() = x;
		Y() = y;
	}

	template<Arithmetic T>
	constexpr void Vector2<T>::Set(const T* const components) noexcept
	{
		Copy(Data(), components, ComponentCount);
	}

	template<Arithmetic T>
	constexpr void Vector2<T>::Scale(const Vector2& scale) noexcept
	{
		Multiply(Data(), scale.Data(), ComponentCount);
	}

	template<Arithmetic T>
	std::string Vector2<T>::ToString() const
	{
		return std::format("({}, {})", X(), Y());
	}

	template<Arithmetic T>
	constexpr T Dot(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return left.X() * right.X() + left.Y() * right.Y();
	}

	template<std::floating_point T>
	T Angle(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		const T dot = std::clamp(Dot(left, right), T{-1}, T{1});

		return std::acos(dot);
	}

	template<std::floating_point T>
	T AngleSigned(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		const T angle = Angle(left, right);
		const T zCross = left.X() * right.Y() - left.Y() * right.X();

		return std::copysign(angle, zCross);
	}

	template<std::floating_point T>
	constexpr Vector2<T> Project(const Vector2<T>& vector, const Vector2<T>& normal) noexcept
	{
		return normal * Dot(vector, normal);
	}

	template<std::floating_point T>
	constexpr Vector2<T> ProjectOnPlane(const Vector2<T>& vector, const Vector2<T>& normal) noexcept
	{
		return vector - normal * Dot(vector, normal);
	}

	template<std::floating_point T>
	constexpr Vector2<T> Reflect(const Vector2<T>& vector, const Vector2<T>& normal) noexcept
	{
		const T multiplier = T{-2} * Dot(vector, normal);

		return vector + normal * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector2<T> Scale(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		Vector2<T> scaled;
		Multiply(scaled.Data(), left.Data(), right.Data(), Vector2<T>::ComponentCount);

		return scaled;
	}

	template<Arithmetic T>
	constexpr Vector2<T> Lerp(const Vector2<T>& from, const Vector2<T>& to, const typename Vector2<T>::ComputationalType time) noexcept
	{
		return from + (to - from) * time;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Vector2<T>& left, const Vector2<T>& right, const T tolerance) noexcept
	{
		return (left - right).MagnitudeSquared() < tolerance * tolerance;
	}

	template<Arithmetic T>
	template<Arithmetic U>
	constexpr Vector2<T>::operator Vector2<U>() const noexcept
	{
		Vector2<U> cast;
		Cast(cast.Data(), Data(), ComponentCount);

		return cast;
	}

	template<Arithmetic T>
	constexpr T& Vector2<T>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<Arithmetic T>
	constexpr const T& Vector2<T>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator +=(const Vector2& other) noexcept
	{
		Add(Data(), other.Data(), ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator -=(const Vector2& other) noexcept
	{
		Subtract(Data(), other.Data(), ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator *=(const T multiplier) noexcept
	{
		Multiply(Data(), multiplier, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator *=(const ComputationalType multiplier) noexcept requires(std::is_integral_v<T>)
	{
		Multiply(Data(), multiplier, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator /=(const T divisor) noexcept
	{
		Divide(Data(), divisor, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector2<T>& Vector2<T>::operator /=(const ComputationalType divisor) noexcept requires(std::is_integral_v<T>)
	{
		Divide(Data(), divisor, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr bool Vector2<T>::operator ==(const Vector2& other) const noexcept
	{
		return components == other.components;
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		Vector2<T> sum;
		Add(sum.Data(), left.Data(), right.Data(), Vector2<T>::ComponentCount);

		return sum;
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator -(const Vector2<T>& vector) noexcept
	{
		Vector2<T> negated;
		Negate(negated.Data(), vector.Data(), Vector2<T>::ComponentCount);

		return negated;
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		Vector2<T> difference;
		Subtract(difference.Data(), left.Data(), right.Data(), Vector2<T>::ComponentCount);

		return difference;
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator *(const Vector2<T>& vector, const T multiplier) noexcept
	{
		Vector2<T> product;
		Multiply(product.Data(), vector.Data(), multiplier, Vector2<T>::ComponentCount);

		return product;
	}

	template<std::integral T>
	constexpr Vector2<T> operator *(const Vector2<T>& vector, const typename Vector2<T>::ComputationalType multiplier) noexcept
	{
		Vector2<T> product;
		Multiply(product.Data(), vector.Data(), multiplier, Vector2<T>::ComponentCount);

		return product;
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator *(const T multiplier, const Vector2<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	template<std::integral T>
	constexpr Vector2<T> operator *(const typename Vector2<T>::ComputationalType multiplier, const Vector2<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator /(const Vector2<T>& vector, const T divisor) noexcept
	{
		Vector2<T> quotient;
		Divide(quotient.Data(), vector.Data(), divisor, Vector2<T>::ComponentCount);

		return quotient;
	}

	template<std::integral T>
	constexpr Vector2<T> operator /(const Vector2<T>& vector, const typename Vector2<T>::ComputationalType divisor) noexcept
	{
		Vector2<T> quotient;
		Divide(quotient.Data(), vector.Data(), divisor, Vector2<T>::ComponentCount);

		return quotient;
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Vector2<T>& vector)
	{
		return stream << vector.ToString();
	}
}
