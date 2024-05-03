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
import <ranges>;
import <string>;
import <type_traits>;

import :ArrayArithmetics;
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
		[[nodiscard("Pure constructor")]]
		explicit constexpr Vector4(const T* components) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Vector4(const Vector4& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Vector4(Vector4&& other) noexcept = default;

		constexpr ~Vector4() noexcept = default;

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
		/// @brief Gets a w-component.
		/// @return W-component.
		[[nodiscard("Pure function")]]
		constexpr T& W() noexcept;
		/// @brief Gets a w-component.
		/// @return W-component.
		[[nodiscard("Pure function")]]
		constexpr const T& W() const noexcept;
		/// @brief Gets a data pointer - an array of 4 elements. The order is x, y, z, w.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		constexpr T* Data() noexcept;
		/// @brief Gets a data pointer - an array of 4 elements. The order is x, y, z, w.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		constexpr const T* Data() const noexcept;

		/// @brief Computes a magnitude of the vector.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		ComputationalType Magnitude() const noexcept;
		/// @brief Computes a squared magnitude of the vector.
		/// @details This function is much faster than @p Magnitude() because it doesn't compute a square root.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		constexpr T MagnitudeSquared() const noexcept;

		/// @brief Computes a vector normalized from this one.
		/// @return Normalized vector.
		[[nodiscard("Pure function")]]
		Vector4 Normalized() const noexcept;
		/// @brief Normalizes the vector.
		void Normalize() noexcept;

		/// @brief Swap components and return a vector in order w, z, y, x.
		/// @return Swapped vector.
		[[nodiscard("Pure function")]]
		constexpr Vector4 Swap() const noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Assigns arguments to the vector components.
		/// @param x X-component.
		/// @param y Y-component.
		/// @param z Z-component.
		/// @param w W-component.
		void Set(T x, T y, T z, T w) noexcept;
		void Set(const T* components) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale Vector to multiply by.
		void Scale(const Vector4& scale) noexcept;

		/// @brief Creates a string representing a state of the vector. The format is '(x, y, z, w)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		Vector4& operator =(const Vector4& other) noexcept = default;
		Vector4& operator =(Vector4&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Vector to add.
		/// @return @a This.
		Vector4& operator +=(const Vector4& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Vector to subtract.
		/// @return @a This.
		Vector4& operator -=(const Vector4& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		Vector4& operator *=(T multiplier) noexcept requires(std::is_integral_v<T>);
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		Vector4& operator *=(ComputationalType multiplier) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Vector divisor.
		/// @return @a This.
		Vector4& operator /=(ComputationalType divisor) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Vector4& other) const noexcept;

	private:
		std::array<T, ComponentCount> m_components; ///< Component array in order x, y, z, w.
	};

	template<Arithmetic T>
	constexpr Vector4<T> Vector4One = Vector4(T{1}, T{1}, T{1}, T{1});
	template<Arithmetic T>
	constexpr Vector4<T> Vector4Zero = Vector4(T{0}, T{0}, T{0}, T{0});
	template<Arithmetic T>
	constexpr Vector4<T> Vector4Negative = Vector4(T{-1}, T{-1}, T{-1}, T{-1});

	/// @brief Computes a dot product of two vectors.
	/// @tparam T Component type.
	/// @param left Left vector.
	/// @param right Right vector.
	/// @return Dot product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Dot(const Vector4<T>& left, const Vector4<T>& right) noexcept;

	/// @brief Projects the @p vector onto the @p target.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param target Projection target.
	/// @return Projected vector.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector4<T> Project(const Vector4<T>& vector, const Vector4<T>& target) noexcept;

	/// @brief Multiplies the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector4<T> Scale(const Vector4<T>& left, const Vector4<T>& right) noexcept;

	/// @brief Linear interpolation between two vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between two vectors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated vector.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector4<T> Lerp(const Vector4<T>& from, const Vector4<T>& to, typename Vector4<T>::ComputationalType time) noexcept;

	/// @brief Checks if two vectors are almost equal with a tolerance value.
	/// @tparam T Component type.
	/// @param left Left vector.
	/// @param right Right vector.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the vectors are almost equal; @a false otherwise.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Vector4<T>& left, const Vector4<T>& right, typename Vector4<T>::ComputationalType tolerance = typename Vector4<T>::ComputationalType{0.00001}) noexcept;

	/// @brief Addition operator for two vectors.
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
}

namespace PonyEngine::Math
{
	template<Arithmetic T>
	constexpr Vector4<T>::Vector4(const T x, const T y, const T z, const T w) noexcept :
		m_components{x, y, z, w}
	{
	}

	template<Arithmetic T>
	constexpr Vector4<T>::Vector4(const T* const components) noexcept
	{
		std::ranges::copy(components, components + ComponentCount, Data());
	}

	template<Arithmetic T>
	constexpr T& Vector4<T>::X() noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr const T& Vector4<T>::X() const noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr T& Vector4<T>::Y() noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr const T& Vector4<T>::Y() const noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr T& Vector4<T>::Z() noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr const T& Vector4<T>::Z() const noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr T& Vector4<T>::W() noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	constexpr const T& Vector4<T>::W() const noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	constexpr T* Vector4<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	constexpr const T* Vector4<T>::Data() const noexcept
	{
		return m_components.data();
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
	Vector4<T> Vector4<T>::Normalized() const noexcept
	{
		return *this * (ComputationalType{1} / Magnitude());
	}

	template<Arithmetic T>
	void Vector4<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	constexpr Vector4<T> Vector4<T>::Swap() const noexcept
	{
		return Vector4(W(), Z(), Y(), X());
	}

	template<Arithmetic T>
	bool Vector4<T>::IsFinite() const noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return Math::IsFinite(Data(), ComponentCount);
		}
		else
		{
			return true;
		}
	}

	template<Arithmetic T>
	void Vector4<T>::Set(const T x, const T y, const T z, const T w) noexcept
	{
		X() = x;
		Y() = y;
		Z() = z;
		W() = w;
	}

	template<Arithmetic T>
	void Vector4<T>::Set(const T* const components) noexcept
	{
		std::ranges::copy(components, components + ComponentCount, Data());
	}

	template<Arithmetic T>
	void Vector4<T>::Scale(const Vector4& scale) noexcept
	{
		Multiply(Data(), scale.Data(), ComponentCount);
	}

	template<Arithmetic T>
	constexpr T Dot(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		return left.X() * right.X() + left.Y() * right.Y() + left.Z() * right.Z() + left.W() * right.W();
	}

	template<Arithmetic T>
	constexpr Vector4<T> Project(const Vector4<T>& vector, const Vector4<T>& target) noexcept
	{
		const typename Vector4<T>::ComputationalType multiplier = static_cast<typename Vector4<T>::ComputationalType>(Dot(vector, target)) / Dot(target, target);

		return target * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector4<T> Scale(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		Vector4<T> scaled;
		Multiply(scaled.Data(), left.Data(), right.Data(), Vector4<T>::ComponentCount);

		return scaled;
	}

	template<Arithmetic T>
	constexpr Vector4<T> Lerp(const Vector4<T>& from, const Vector4<T>& to, const typename Vector4<T>::ComputationalType time) noexcept
	{
		return from + (to - from) * time;
	}

	template<Arithmetic T>
	constexpr bool AreAlmostEqual(const Vector4<T>& left, const Vector4<T>& right, const typename Vector4<T>::ComputationalType tolerance) noexcept
	{
		return (left - right).MagnitudeSquared() < tolerance * tolerance;
	}

	template<Arithmetic T>
	std::string Vector4<T>::ToString() const
	{
		return std::format("({}, {}, {}, {})", X(), Y(), Z(), W());
	}

	template<Arithmetic T>
	constexpr T& Vector4<T>::operator [](const std::size_t index) noexcept
	{
		return m_components[index];
	}

	template<Arithmetic T>
	constexpr const T& Vector4<T>::operator [](const std::size_t index) const noexcept
	{
		return m_components[index];
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator +=(const Vector4& other) noexcept
	{
		Add(Data(), other.Data(), ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator -=(const Vector4& other) noexcept
	{
		Subtract(Data(), other.Data(), ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		Multiply(Data(), multiplier, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		Multiply(Data(), multiplier, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	Vector4<T>& Vector4<T>::operator /=(const ComputationalType divisor) noexcept
	{
		Divide(Data(), divisor, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr bool Vector4<T>::operator ==(const Vector4& other) const noexcept
	{
		return m_components == other.m_components;
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator +(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		Vector4<T> sum;
		Add(sum.Data(), left.Data(), right.Data(), Vector4<T>::ComponentCount);

		return sum;
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator -(const Vector4<T>& vector) noexcept
	{
		Vector4<T> negated;
		Negate(negated.Data(), vector.Data(), Vector4<T>::ComponentCount);

		return negated;
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator -(const Vector4<T>& left, const Vector4<T>& right) noexcept
	{
		Vector4<T> difference;
		Subtract(difference.Data(), left.Data(), right.Data(), Vector4<T>::ComponentCount);

		return difference;
	}

	template<std::integral T>
	constexpr Vector4<T> operator *(const Vector4<T>& vector, T multiplier) noexcept
	{
		Vector4<T> product;
		Multiply(product.Data(), vector.Data(), multiplier, Vector4<T>::ComponentCount);

		return product;
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator *(const Vector4<T>& vector, const typename Vector4<T>::ComputationalType multiplier) noexcept
	{
		Vector4<T> product;
		Multiply(product.Data(), vector.Data(), multiplier, Vector4<T>::ComponentCount);

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
		Divide(quotient.Data(), vector.Data(), divisor, Vector4<T>::ComponentCount);

		return quotient;
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Vector4<T>& vector)
	{
		return stream << vector.ToString();
	}
}
