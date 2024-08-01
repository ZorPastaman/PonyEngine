/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Vector4;

import <algorithm>;
import <array>;
import <cmath>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <type_traits>;

import :Common;

export namespace PonyEngine::Math
{
	/// @brief 4D vector implementation.
	/// @tparam T Component type.
	template<Arithmetic T>
	class Vector4 final
	{
	public:
		using ValueType = T; ///< Component type.
		using ComputationalType = ComputationalFor<T>; ///< Floating point type used in functions that require a floating point type.

		static constexpr std::size_t ComponentCount = 4; ///< Component count. For any Vector4, it's always 4.

		struct Predefined; ///< Predefined vectors.

		/// @brief Creates a vector and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr Vector4() noexcept = default;
		/// @brief Creates a vector and assigns its components from the arguments.
		/// @param x X-component.
		/// @param y Y-component.
		/// @param z Z-component.
		/// @param w W-component.
		[[nodiscard("Pure constructor")]]
		constexpr Vector4(T x, T y, T z, T w) noexcept;
		/// @brief Creates a vector and assign its components from the @p components array.
		/// @param components Component array. Its length must be at least 4.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Vector4(const T* components) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Vector4(const Vector4& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Vector4(Vector4&& other) noexcept = default;

		constexpr ~Vector4() noexcept = default;

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
		/// @brief Gets the z-component.
		/// @return Z-component.
		[[nodiscard("Pure function")]]
		constexpr T& Z() noexcept;
		/// @brief Gets the z-component.
		/// @return Z-component.
		[[nodiscard("Pure function")]]
		constexpr const T& Z() const noexcept;
		/// @brief Gets the w-component.
		/// @return W-component.
		[[nodiscard("Pure function")]]
		constexpr T& W() noexcept;
		/// @brief Gets the w-component.
		/// @return W-component.
		[[nodiscard("Pure function")]]
		constexpr const T& W() const noexcept;
		/// @brief Gets the data pointer to the array of 4 elements. The order is x, y, z, w.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		constexpr T* Data() noexcept;
		/// @brief Gets the data pointer to the array of 4 elements. The order is x, y, z, w.
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
		Vector4 Normalized() const noexcept requires(std::is_floating_point_v<T>);
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

		/// @brief Swaps the components and returns a vector in order w, z, y, x.
		/// @return Swapped vector.
		constexpr Vector4 Swapped() const noexcept;
		/// @brief Swaps the components in the vector. The order is w, z, y, x.
		[[nodiscard("Pure function")]]
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
		/// @param z Z-component.
		/// @param w W-component.
		constexpr void Set(T x, T y, T z, T w) noexcept;
		/// @brief Assigns arguments from the @p components array.
		/// @param componentsToSet Component array. Its length must be at least 4.
		constexpr void Set(const T* componentsToSet) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale Vector to multiply by.
		constexpr void Scale(const Vector4& scale) noexcept;

		/// @brief Creates a string representing a state of the vector. The format is '(x, y, z, w)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Casts all the components to the @p U and returns a new vector with those components.
		/// @tparam U Target component type.
		template<Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Vector4<U>() const noexcept;

		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr Vector4& operator =(const Vector4& other) noexcept = default;
		constexpr Vector4& operator =(Vector4&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Vector to add.
		/// @return @a This.
		constexpr Vector4& operator +=(const Vector4& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Vector to subtract.
		/// @return @a This.
		constexpr Vector4& operator -=(const Vector4& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		constexpr Vector4& operator *=(T multiplier) noexcept requires(std::is_integral_v<T>);
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		constexpr Vector4& operator *=(ComputationalType multiplier) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Vector divisor.
		/// @return @a This.
		constexpr Vector4& operator /=(ComputationalType divisor) noexcept;

		/// @brief Checks if all the components of vectors are equal.
		/// @param other Vector to compare.
		/// @return @a True if they are equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Vector4& other) const noexcept;

	private:
		std::array<T, ComponentCount> components; ///< Component array in order x, y, z, w.
	};

	/// @brief Computes a dot product of the two vectors.
	/// @tparam T Component type.
	/// @param left Left vector.
	/// @param right Right vector.
	/// @return Dot product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Dot(const Vector4<T>& left, const Vector4<T>& right) noexcept;

	/// @brief Computes an angle between the two vectors.
	/// @tparam T Component type.
	/// @param left Left vector. Must be unit.
	/// @param right Right vector. Must be unit.
	/// @return Angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T Angle(const Vector4<T>& left, const Vector4<T>& right) noexcept;

	/// @brief Projects the @p vector onto the @p normal.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Projection target. Must be unit.
	/// @return Projected vector.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Vector4<T> Project(const Vector4<T>& vector, const Vector4<T>& normal) noexcept;

	/// @brief Multiplies the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector4<T> Scale(const Vector4<T>& left, const Vector4<T>& right) noexcept;

	/// @brief Linear interpolation between the two vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between the two vectors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated vector.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector4<T> Lerp(const Vector4<T>& from, const Vector4<T>& to, typename Vector4<T>::ComputationalType time) noexcept;

	/// @brief Checks if the two vectors are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left vector.
	/// @param right Right vector.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the vectors are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Vector4<T>& left, const Vector4<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Sums the @p left vector and the @p right vector.
	/// @tparam T Component type.
	/// @param left Augend.
	/// @param right Addend.
	/// @return Sum.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator +(const Vector4<T>& left, const Vector4<T>& right) noexcept;

	/// @brief Negates the @p vector.
	/// @tparam T Component type.
	/// @param vector Vector to negate.
	/// @return Negated vector.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator -(const Vector4<T>& vector) noexcept;

	/// @brief Subtracts the @p right vector from the @p left vector.
	/// @tparam T Component type.
	/// @param left Minuend.
	/// @param right Subtrahend.
	/// @return Difference.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator -(const Vector4<T>& left, const Vector4<T>& right) noexcept;

	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator *(const Vector4<T>& vector, T multiplier) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator *(const Vector4<T>& vector, typename Vector4<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator *(T multiplier, const Vector4<T>& vector) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator *(typename Vector4<T>::ComputationalType multiplier, const Vector4<T>& vector) noexcept;

	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator /(const Vector4<T>& vector, typename Vector4<T>::ComputationalType divisor) noexcept;

	/// @brief Puts @p Vector.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param vector Input source.
	/// @return @p stream.
	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Vector4<T>& vector);

	template<Arithmetic T>
	struct Vector4<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr Vector4 One = Vector4(T{1}, T{1}, T{1}, T{1}); ///< Vector4(1, 1, 1, 1).
		static constexpr Vector4 Zero = Vector4(T{0}, T{0}, T{0}, T{0}); ///< Vector4(0, 0, 0, 0).
		static constexpr Vector4 Negative = Vector4(T{-1}, T{-1}, T{-1}, T{-1}); ///< Vector4(-1, -1, -1, -1).
	};
}

namespace PonyEngine::Math
{
	template<Arithmetic T>
	constexpr Vector4<T>::Vector4(const T x, const T y, const T z, const T w) noexcept :
		components{x, y, z, w}
	{
	}

	template<Arithmetic T>
	constexpr Vector4<T>::Vector4(const T* const components) noexcept
	{
		Set(components);
	}

	template<Arithmetic T>
	constexpr T& Vector4<T>::X() noexcept
	{
		return components[0];
	}

	template<Arithmetic T>
	constexpr const T& Vector4<T>::X() const noexcept
	{
		return components[0];
	}

	template<Arithmetic T>
	constexpr T& Vector4<T>::Y() noexcept
	{
		return components[1];
	}

	template<Arithmetic T>
	constexpr const T& Vector4<T>::Y() const noexcept
	{
		return components[1];
	}

	template<Arithmetic T>
	constexpr T& Vector4<T>::Z() noexcept
	{
		return components[2];
	}

	template<Arithmetic T>
	constexpr const T& Vector4<T>::Z() const noexcept
	{
		return components[2];
	}

	template<Arithmetic T>
	constexpr T& Vector4<T>::W() noexcept
	{
		return components[3];
	}

	template<Arithmetic T>
	constexpr const T& Vector4<T>::W() const noexcept
	{
		return components[3];
	}

	template<Arithmetic T>
	constexpr T* Vector4<T>::Data() noexcept
	{
		return components.data();
	}

	template<Arithmetic T>
	constexpr const T* Vector4<T>::Data() const noexcept
	{
		return components.data();
	}

	template<Arithmetic T>
	typename Vector4<T>::ComputationalType Vector4<T>::Magnitude() const noexcept
	{
		return std::sqrt(static_cast<ComputationalType>(MagnitudeSquared()));
	}

	template<Arithmetic T>
	constexpr T Vector4<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Arithmetic T>
	Vector4<T> Vector4<T>::Normalized() const noexcept requires(std::is_floating_point_v<T>)
	{
		return *this * (T{1} / Magnitude());
	}

	template<Arithmetic T>
	void Vector4<T>::Normalize() noexcept requires(std::is_floating_point_v<T>)
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	constexpr T Vector4<T>::Min() const noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<Arithmetic T>
	constexpr T Vector4<T>::Max() const noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<Arithmetic T>
	constexpr T Vector4<T>::Sum() const noexcept
	{
		return X() + Y() + Z() + W();
	}

	template<Arithmetic T>
	constexpr Vector4<T> Vector4<T>::Swapped() const noexcept
	{
		return Vector4(W(), Z(), Y(), X());
	}

	template<Arithmetic T>
	constexpr void Vector4<T>::Swap() noexcept
	{
		std::swap(X(), W());
		std::swap(Y(), Z());
	}

	template<Arithmetic T>
	constexpr bool Vector4<T>::IsZero() const noexcept
	{
		return *this == Predefined::Zero;
	}

	template<Arithmetic T>
	constexpr bool Vector4<T>::IsAlmostZero(const T tolerance) const noexcept requires(std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(*this, Predefined::Zero, tolerance);
	}

	template<Arithmetic T>
	constexpr bool Vector4<T>::IsUnit() const noexcept
	{
		return MagnitudeSquared() == T{1};
	}

	template<Arithmetic T>
	bool Vector4<T>::IsAlmostUnit(const T tolerance) const noexcept requires(std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(MagnitudeSquared(), T{1}, tolerance);
	}

	template<Arithmetic T>
	constexpr bool Vector4<T>::IsUniform() const noexcept
	{
		const auto [min, max] = std::ranges::minmax_element(components);

		return *min == *max;
	}

	template<Arithmetic T>
	bool Vector4<T>::IsAlmostUniform(const T tolerance) const noexcept requires(std::is_floating_point_v<T>)
	{
		const auto [min, max] = std::ranges::minmax_element(components);

		return AreAlmostEqual(*min, *max, tolerance);
	}

	template<Arithmetic T>
	bool Vector4<T>::IsFinite() const noexcept requires(std::is_floating_point_v<T>)
	{
		return std::isfinite(X()) && std::isfinite(Y()) && std::isfinite(Z()) && std::isfinite(W());
	}

	template<Arithmetic T>
	constexpr void Vector4<T>::Set(const T x, const T y, const T z, const T w) noexcept
	{
		X() = x;
		Y() = y;
		Z() = z;
		W() = w;
	}

	template<Arithmetic T>
	constexpr void Vector4<T>::Set(const T* const componentsToSet) noexcept
	{
		std::copy(componentsToSet, componentsToSet + ComponentCount, Data());
	}

	template<Arithmetic T>
	constexpr void Vector4<T>::Scale(const Vector4& scale) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= scale[i];
		}
	}

	template<Arithmetic T>
	std::string Vector4<T>::ToString() const
	{
		return std::format("({}, {}, {}, {})", X(), Y(), Z(), W());
	}

	template<Arithmetic T>
	constexpr T Dot(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return left.X() * right.X() + left.Y() * right.Y() + left.Z() * right.Z() + left.W() * right.W();
	}

	template<std::floating_point T>
	T Angle(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		const T dot = std::clamp(Dot(left, right), T{-1}, T{1});

		return std::acos(dot);
	}

	template<std::floating_point T>
	constexpr Vector4<T> Project(const Vector4<T>& vector, const Vector4<T>& normal) noexcept
	{
		return normal * Dot(vector, normal);
	}

	template<Arithmetic T>
	constexpr Vector4<T> Scale(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		Vector4<T> scaled;
		for (std::size_t i = 0; i < Vector4<T>::ComponentCount; ++i)
		{
			scaled[i] = left[i] * right[i];
		}

		return scaled;
	}

	template<Arithmetic T>
	constexpr Vector4<T> Lerp(const Vector4<T>& from, const Vector4<T>& to, const typename Vector4<T>::ComputationalType time) noexcept
	{
		return from + (to - from) * time;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Vector4<T>& left, const Vector4<T>& right, const T tolerance) noexcept
	{
		return (left - right).MagnitudeSquared() < tolerance * tolerance;
	}

	template<Arithmetic T>
	template<Arithmetic U>
	constexpr Vector4<T>::operator Vector4<U>() const noexcept
	{
		Vector4<U> cast;
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			cast[i] = static_cast<U>((*this)[i]);
		}

		return cast;
	}

	template<Arithmetic T>
	constexpr T& Vector4<T>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<Arithmetic T>
	constexpr const T& Vector4<T>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::operator +=(const Vector4& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] += other[i];
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::operator -=(const Vector4& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] -= other[i];
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= multiplier;
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] = static_cast<T>((*this)[i] * multiplier);
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr Vector4<T>& Vector4<T>::operator /=(const ComputationalType divisor) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] = static_cast<T>((*this)[i] / divisor);
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr bool Vector4<T>::operator ==(const Vector4& other) const noexcept
	{
		return components == other.components;
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator +(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		Vector4<T> sum;
		for (std::size_t i = 0; i < Vector4<T>::ComponentCount; ++i)
		{
			sum[i] = left[i] + right[i];
		}

		return sum;
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator -(const Vector4<T>& vector) noexcept
	{
		Vector4<T> negated;
		for (std::size_t i = 0; i < Vector4<T>::ComponentCount; ++i)
		{
			negated[i] = -vector[i];
		}

		return negated;
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator -(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		Vector4<T> difference;
		for (std::size_t i = 0; i < Vector4<T>::ComponentCount; ++i)
		{
			difference[i] = left[i] - right[i];
		}

		return difference;
	}

	template<std::integral T>
	constexpr Vector4<T> operator *(const Vector4<T>& vector, const T multiplier) noexcept
	{
		Vector4<T> product;
		for (std::size_t i = 0; i < Vector4<T>::ComponentCount; ++i)
		{
			product[i] = vector[i] * multiplier;
		}

		return product;
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator *(const Vector4<T>& vector, const typename Vector4<T>::ComputationalType multiplier) noexcept
	{
		Vector4<T> product;
		for (std::size_t i = 0; i < Vector4<T>::ComponentCount; ++i)
		{
			product[i] = static_cast<T>(vector[i] * multiplier);
		}

		return product;
	}

	template<std::integral T>
	constexpr Vector4<T> operator *(const T multiplier, const Vector4<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator *(const typename Vector4<T>::ComputationalType multiplier, const Vector4<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator /(const Vector4<T>& vector, const typename Vector4<T>::ComputationalType divisor) noexcept
	{
		Vector4<T> quotient;
		for (std::size_t i = 0; i < Vector4<T>::ComponentCount; ++i)
		{
			quotient[i] = static_cast<T>(vector[i] / divisor);
		}

		return quotient;
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Vector4<T>& vector)
	{
		return stream << vector.ToString();
	}
}
