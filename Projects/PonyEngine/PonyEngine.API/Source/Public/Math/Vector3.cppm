/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Vector3;

import <algorithm>;
import <array>;
import <cmath>;
import <concepts>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <type_traits>;

import :ArrayArithmetics;
import :Common;

export namespace PonyEngine::Math
{
	/// @brief 3D vector implementation.
	/// @tparam T Component type.
	template<Arithmetic T>
	class Vector3 final
	{
	public:
		using ValueType = T; ///< Component type.
		using ComputationalType = ComputationalFor<T>; ///< Floating point type used in functions that require a floating point type.

		static constexpr std::size_t ComponentCount = 3; ///< Component count. For any Vector3, it's always 3.

		struct Predefined; ///< Predefined vectors.

		/// @brief Creates a vector and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr Vector3() noexcept = default;
		/// @brief Creates a vector and assigns its components from the arguments.
		/// @param x X-component.
		/// @param y Y-component.
		/// @param z Z-component.
		[[nodiscard("Pure constructor")]]
		constexpr Vector3(T x, T y, T z) noexcept;
		/// @brief Creates a vector and assign its components from the @p components array.
		/// @param components Component array. Its length must be at least 3.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Vector3(const T* components) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Vector3(const Vector3& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Vector3(Vector3&& other) noexcept = default;

		constexpr ~Vector3() noexcept = default;

		/// @brief Gets an x-component.
		/// @return X-component.
		[[nodiscard("Pure function")]]
		constexpr T& X() noexcept;
		/// @brief Gets an x-component.
		/// @return X-component.
		[[nodiscard("Pure function")]]
		constexpr const T& X() const noexcept;
		/// @brief Gets a y-component.
		/// @return Y-component.
		[[nodiscard("Pure function")]]
		constexpr T& Y() noexcept;
		/// @brief Gets a y-component.
		/// @return Y-component.
		[[nodiscard("Pure function")]]
		constexpr const T& Y() const noexcept;
		/// @brief Gets a z-component.
		/// @return Z-component.
		[[nodiscard("Pure function")]]
		constexpr T& Z() noexcept;
		/// @brief Gets a z-component.
		/// @return Z-component.
		[[nodiscard("Pure function")]]
		constexpr const T& Z() const noexcept;
		/// @brief Gets a data pointer - an array of 3 elements. The order is x, y, z.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		constexpr T* Data() noexcept;
		/// @brief Gets a data pointer - an array of 3 elements. The order is x, y, z.
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
		Vector3 Normalized() const noexcept requires(std::is_floating_point_v<T>);
		/// @brief Normalizes the vector.
		/// @note If the magnitude of the vector is 0, the result is undefined.
		void Normalize() noexcept requires(std::is_floating_point_v<T>);

		/// @brief Gets a minimum value among components.
		/// @return Minimum component value.
		[[nodiscard("Pure function")]]
		constexpr T Min() const noexcept;
		/// @brief Gets a maximum value among components.
		/// @return Maximum component value.
		[[nodiscard("Pure function")]]
		constexpr T Max() const noexcept;
		/// @brief Sums all the components and returns the result.
		/// @return Sum.
		[[nodiscard("Pure function")]]
		constexpr T Sum() const noexcept;

		/// @brief Swaps components and returns a vector in order z, y, x.
		/// @return Swapped vector.
		[[nodiscard("Pure function")]]
		constexpr Vector3 Swapped() const noexcept;
		/// @brief Swaps components in @this vector. The order is z, y, x.
		constexpr void Swap() noexcept;

		/// @brief Checks if all the components are zero.
		/// @return @a True if this vector components are zero; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsZero() const noexcept;
		/// @brief Checks if all the components are almost zero with a tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return  @a True if this vector components are almost zero; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostZero(T tolerance = T{0.00001}) const noexcept requires(std::is_floating_point_v<T>);
		/// @brief Checks if this vector is unit.
		/// @return @a True if this vector is unit; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsUnit() const noexcept;
		/// @brief Checks if this vector is almost unit with a tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if this vector is almost unit; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsAlmostUnit(T tolerance = T{ 0.00001 }) const noexcept requires(std::is_floating_point_v<T>);
		/// @brief Checks if this vector is uniform.
		/// @return @a True if this vector is uniform; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsUniform() const noexcept;
		/// @brief Checks if this vector is almost uniform with a tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if this vector is almost uniform; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsAlmostUniform(T tolerance = T{ 0.00001 }) const noexcept requires(std::is_floating_point_v<T>);

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept requires(std::is_floating_point_v<T>);

		/// @brief Assigns arguments to the vector components.
		/// @param x X-component.
		/// @param y Y-component.
		/// @param z Z-component.
		constexpr void Set(T x, T y, T z) noexcept;
		/// @brief Assigns arguments from the @p components array.
		/// @param components Component array. Its length must be at least 3.
		constexpr void Set(const T* components) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale Vector to multiply by.
		constexpr void Scale(const Vector3& scale) noexcept;

		/// @brief Creates a string representing a state of the vector. The format is '(x, y, z)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 2].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z.
		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 2].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr Vector3& operator =(const Vector3& other) noexcept = default;
		constexpr Vector3& operator =(Vector3&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Vector to add.
		/// @return @a This.
		constexpr Vector3& operator +=(const Vector3& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Vector to subtract.
		/// @return @a This.
		constexpr Vector3& operator -=(const Vector3& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		constexpr Vector3& operator *=(T multiplier) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		constexpr Vector3& operator *=(ComputationalType multiplier) noexcept requires(std::is_integral_v<T>);
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Vector divisor.
		/// @return @a This.
		constexpr Vector3& operator /=(T divisor) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Vector divisor.
		/// @return @a This.
		constexpr Vector3& operator /=(ComputationalType divisor) noexcept requires(std::is_integral_v<T>);

		/// @brief Checks if all the components of vectors are equal.
		/// @param other Vector to compare.
		/// @return @a True if they are equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Vector3& other) const noexcept;

	private:
		std::array<T, ComponentCount> components; ///< Component array in order x, y, z.
	};

	/// @brief Computes a dot product of two vectors.
	/// @tparam T Component type.
	/// @param left Left vector.
	/// @param right Right vector.
	/// @return Dot product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Dot(const Vector3<T>& left, const Vector3<T>& right) noexcept;

	/// @brief Computes a cross product of two vectors.
	/// @tparam T Component type.
	/// @param left Left vector.
	/// @param right Right vector.
	/// @return Cross product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Cross(const Vector3<T>& left, const Vector3<T>& right) noexcept;

	/// @brief Computes an angle between two vectors.
	/// @tparam T Component type.
	/// @param left Left vector. Must be unit.
	/// @param right Right vector. Must be unit.
	/// @return Angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T Angle(const Vector3<T>& left, const Vector3<T>& right) noexcept;
	/// @brief Computes a signed angle between two vectors.
	///        Sign is copied from the sign of the dot product of the @p axis and the cross product of the @p left and @p right.
	/// @tparam T Component type.
	/// @param left Left vector. Must be unit.
	/// @param right Right vector. Must be unit.
	/// @param axis Sign reference.
	/// @return Angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T AngleSigned(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept;

	/// @brief Projects the @p vector onto the @p normal.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Projection target. Must be unit.
	/// @return Projected vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Project(const Vector3<T>& vector, const Vector3<T>& normal) noexcept;
	/// @brief Projects the @p vector onto a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be unit.
	/// @return Projected vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> ProjectOnPlane(const Vector3<T>& vector, const Vector3<T>& normal) noexcept;

	/// @brief Reflects the @p vector off a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be unit.
	/// @return Reflected vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Reflect(const Vector3<T>& vector, const Vector3<T>& normal) noexcept;

	/// @brief Multiplies the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Scale(const Vector3<T>& left, const Vector3<T>& right) noexcept;

	/// @brief Linear interpolation between two vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between two vectors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated vector.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Lerp(const Vector3<T>& from, const Vector3<T>& to, typename Vector3<T>::ComputationalType time) noexcept;

	/// @brief Checks if two vectors are almost equal with a tolerance value.
	/// @tparam T Component type.
	/// @param left Left vector.
	/// @param right Right vector.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the vectors are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Vector3<T>& left, const Vector3<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Addition operator for two vectors.
	/// @tparam T Component type.
	/// @param left Augend.
	/// @param right Addend.
	/// @return Sum.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right) noexcept;

	/// @brief Negates the @p vector.
	/// @tparam T Component type.
	/// @param vector Vector to negate.
	/// @return Negated vector.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator -(const Vector3<T>& vector) noexcept;

	/// @brief Subtracts the @p right vector from the @p left vector.
	/// @tparam T Component type.
	/// @param left Minuend.
	/// @param right Subtrahend.
	/// @return Difference.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right) noexcept;

	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Vector3<T>& vector, T multiplier) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Vector3<T>& vector, typename Vector3<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(T multiplier, const Vector3<T>& vector) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(typename Vector3<T>::ComputationalType multiplier, const Vector3<T>& vector) noexcept;

	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator /(const Vector3<T>& vector, T divisor) noexcept;
	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator /(const Vector3<T>& vector, typename Vector3<T>::ComputationalType divisor) noexcept;

	/// @brief Puts @p Vector.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param vector Input source.
	/// @return @p stream.
	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Vector3<T>& vector);

	template<Arithmetic T>
	struct Vector3<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr Vector3 Forward = Vector3(T{0}, T{0}, T{1}); ///< Vector3(0, 0, 1).
		static constexpr Vector3 Back = Vector3(T{0}, T{0}, T{-1}); ///< Vector3(0, 0, -1).
		static constexpr Vector3 Up = Vector3(T{0}, T{1}, T{0}); ///< Vector3(0, 1, 0).
		static constexpr Vector3 Down = Vector3(T{0}, T{-1}, T{0}); ///< Vector3(0, -1, 0).
		static constexpr Vector3 Right = Vector3(T{1}, T{0}, T{0}); /// Vector3(1, 0, 0).
		static constexpr Vector3 Left = Vector3(T{-1}, T{0}, T{0}); ///< Vector3(-1, 0, 0).
		static constexpr Vector3 One = Vector3(T{1}, T{1}, T{1}); ///< Vector3(1, 1, 1).
		static constexpr Vector3 Zero = Vector3(T{0}, T{0}, T{0}); ///< Vector3(0, 0, 0).
		static constexpr Vector3 Negative = Vector3(T{-1}, T{-1}, T{-1}); ///< Vector3(-1, -1, -1).
	};
}

namespace PonyEngine::Math
{
	template<Arithmetic T>
	constexpr Vector3<T>::Vector3(const T x, const T y, const T z) noexcept :
		components{x, y, z}
	{
	}

	template<Arithmetic T>
	constexpr Vector3<T>::Vector3(const T* const components) noexcept
	{
		Set(components);
	}

	template<Arithmetic T>
	constexpr T& Vector3<T>::X() noexcept
	{
		return components[0];
	}

	template<Arithmetic T>
	constexpr const T& Vector3<T>::X() const noexcept
	{
		return components[0];
	}

	template<Arithmetic T>
	constexpr T& Vector3<T>::Y() noexcept
	{
		return components[1];
	}

	template<Arithmetic T>
	constexpr const T& Vector3<T>::Y() const noexcept
	{
		return components[1];
	}

	template<Arithmetic T>
	constexpr T& Vector3<T>::Z() noexcept
	{
		return components[2];
	}

	template<Arithmetic T>
	constexpr const T& Vector3<T>::Z() const noexcept
	{
		return components[2];
	}

	template<Arithmetic T>
	constexpr T* Vector3<T>::Data() noexcept
	{
		return components.data();
	}

	template<Arithmetic T>
	constexpr const T* Vector3<T>::Data() const noexcept
	{
		return components.data();
	}

	template<Arithmetic T>
	typename Vector3<T>::ComputationalType Vector3<T>::Magnitude() const noexcept
	{
		return std::sqrt(static_cast<ComputationalType>(MagnitudeSquared()));
	}

	template<Arithmetic T>
	constexpr T Vector3<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T>
	Vector3<T> Vector3<T>::Normalized() const noexcept requires(std::is_floating_point_v<T>)
	{
		return *this * (T{1} / Magnitude());
	}

	template<Arithmetic T>
	void Vector3<T>::Normalize() noexcept requires(std::is_floating_point_v<T>)
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	constexpr T Vector3<T>::Min() const noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<Arithmetic T>
	constexpr T Vector3<T>::Max() const noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<Arithmetic T>
	constexpr T Vector3<T>::Sum() const noexcept
	{
		return X() + Y() + Z();
	}

	template<Arithmetic T>
	constexpr Vector3<T> Vector3<T>::Swapped() const noexcept
	{
		return Vector3(Z(), Y(), X());
	}

	template<Arithmetic T>
	constexpr void Vector3<T>::Swap() noexcept
	{
		std::swap(X(), Z());
	}

	template<Arithmetic T>
	constexpr bool Vector3<T>::IsZero() const noexcept
	{
		return *this == Predefined::Zero;
	}

	template<Arithmetic T>
	constexpr bool Vector3<T>::IsAlmostZero(const T tolerance) const noexcept requires(std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(*this, Predefined::Zero, tolerance);
	}

	template<Arithmetic T>
	constexpr bool Vector3<T>::IsUnit() const noexcept
	{
		return MagnitudeSquared() == T{1};
	}

	template<Arithmetic T>
	bool Vector3<T>::IsAlmostUnit(const T tolerance) const noexcept requires(std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(MagnitudeSquared(), T{1}, tolerance);
	}

	template<Arithmetic T>
	constexpr bool Vector3<T>::IsUniform() const noexcept
	{
		const auto [min, max] = std::ranges::minmax_element(components);

		return *min == *max;
	}

	template<Arithmetic T>
	bool Vector3<T>::IsAlmostUniform(const T tolerance) const noexcept requires(std::is_floating_point_v<T>)
	{
		const auto [min, max] = std::ranges::minmax_element(components);

		return AreAlmostEqual(*min, *max, tolerance);
	}

	template<Arithmetic T>
	bool Vector3<T>::IsFinite() const noexcept requires(std::is_floating_point_v<T>)
	{
		return Math::IsFinite(Data(), ComponentCount);
	}

	template<Arithmetic T>
	constexpr void Vector3<T>::Set(const T x, const T y, const T z) noexcept
	{
		X() = x;
		Y() = y;
		Z() = z;
	}

	template<Arithmetic T>
	constexpr void Vector3<T>::Set(const T* const components) noexcept
	{
		Copy(Data(), components, ComponentCount);
	}

	template<Arithmetic T>
	constexpr void Vector3<T>::Scale(const Vector3& scale) noexcept
	{
		Multiply(Data(), scale.Data(), ComponentCount);
	}

	template<Arithmetic T>
	std::string Vector3<T>::ToString() const
	{
		return std::format("({}, {}, {})", X(), Y(), Z());
	}

	template<Arithmetic T>
	constexpr T Dot(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return left.X() * right.X() + left.Y() * right.Y() + left.Z() * right.Z();
	}

	template<Arithmetic T>
	constexpr Vector3<T> Cross(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		Vector3<T> cross;
		cross.X() = left.Y() * right.Z() - left.Z() * right.Y();
		cross.Y() = left.Z() * right.X() - left.X() * right.Z();
		cross.Z() = left.X() * right.Y() - left.Y() * right.X();

		return cross;
	}

	template<std::floating_point T>
	T Angle(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		const T dot = std::clamp(Dot(left, right), T{-1}, T{1});

		return std::acos(dot);
	}

	template<std::floating_point T>
	T AngleSigned(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept
	{
		const Vector3<T> cross = Cross(left, right);
		const T dot = Dot(cross, axis);
		const T angle = Angle(left, right);

		return std::copysign(angle, dot);
	}

	template<std::floating_point T>
	constexpr Vector3<T> Project(const Vector3<T>& vector, const Vector3<T>& normal) noexcept
	{
		return normal * Dot(vector, normal);
	}

	template<std::floating_point T>
	constexpr Vector3<T> ProjectOnPlane(const Vector3<T>& vector, const Vector3<T>& normal) noexcept
	{
		return vector - normal * Dot(vector, normal);
	}

	template<std::floating_point T>
	constexpr Vector3<T> Reflect(const Vector3<T>& vector, const Vector3<T>& normal) noexcept
	{
		const T multiplier = T{-2} * Dot(vector, normal);

		return vector + normal * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector3<T> Scale(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		Vector3<T> scaled;
		Multiply(scaled.Data(), left.Data(), right.Data(), Vector3<T>::ComponentCount);

		return scaled;
	}

	template<Arithmetic T>
	constexpr Vector3<T> Lerp(const Vector3<T>& from, const Vector3<T>& to, const typename Vector3<T>::ComputationalType time) noexcept
	{
		return from + (to - from) * time;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Vector3<T>& left, const Vector3<T>& right, const T tolerance) noexcept
	{
		return (left - right).MagnitudeSquared() < tolerance * tolerance;
	}

	template<Arithmetic T>
	constexpr T& Vector3<T>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<Arithmetic T>
	constexpr const T& Vector3<T>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator +=(const Vector3& other) noexcept
	{
		Add(Data(), other.Data(), ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator -=(const Vector3& other) noexcept
	{
		Subtract(Data(), other.Data(), ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator *=(const T multiplier) noexcept
	{
		Multiply(Data(), multiplier, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator *=(const ComputationalType multiplier) noexcept requires(std::is_integral_v<T>)
	{
		Multiply(Data(), multiplier, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator /=(const T divisor) noexcept
	{
		Divide(Data(), divisor, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector3<T>& Vector3<T>::operator /=(const ComputationalType divisor) noexcept requires(std::is_integral_v<T>)
	{
		Divide(Data(), divisor, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr bool Vector3<T>::operator ==(const Vector3& other) const noexcept
	{
		return components == other.components;
	}

	template<Arithmetic T>
	constexpr Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		Vector3<T> sum;
		Add(sum.Data(), left.Data(), right.Data(), Vector3<T>::ComponentCount);

		return sum;
	}

	template<Arithmetic T>
	constexpr Vector3<T> operator -(const Vector3<T>& vector) noexcept
	{
		Vector3<T> negated;
		Negate(negated.Data(), vector.Data(), Vector3<T>::ComponentCount);

		return negated;
	}

	template<Arithmetic T>
	constexpr Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		Vector3<T> difference;
		Subtract(difference.Data(), left.Data(), right.Data(), Vector3<T>::ComponentCount);

		return difference;
	}

	template<Arithmetic T>
	constexpr Vector3<T> operator *(const Vector3<T>& vector, const T multiplier) noexcept
	{
		Vector3<T> product;
		Multiply(product.Data(), vector.Data(), multiplier, Vector3<T>::ComponentCount);

		return product;
	}

	template<std::integral T>
	constexpr Vector3<T> operator *(const Vector3<T>& vector, const typename Vector3<T>::ComputationalType multiplier) noexcept
	{
		Vector3<T> product;
		Multiply(product.Data(), vector.Data(), multiplier, Vector3<T>::ComponentCount);

		return product;
	}

	template<Arithmetic T>
	constexpr Vector3<T> operator *(const T multiplier, const Vector3<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	template<std::integral T>
	constexpr Vector3<T> operator *(const typename Vector3<T>::ComputationalType multiplier, const Vector3<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector3<T> operator /(const Vector3<T>& vector, const T divisor) noexcept
	{
		Vector3<T> quotient;
		Divide(quotient.Data(), vector.Data(), divisor, Vector3<T>::ComponentCount);

		return quotient;
	}

	template<std::integral T>
	constexpr Vector3<T> operator /(const Vector3<T>& vector, const typename Vector3<T>::ComputationalType divisor) noexcept
	{
		Vector3<T> quotient;
		Divide(quotient.Data(), vector.Data(), divisor, Vector3<T>::ComponentCount);

		return quotient;
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Vector3<T>& vector)
	{
		return stream << vector.ToString();
	}
}
