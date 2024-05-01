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
import <ranges>;
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

		/// @brief Creates a vector and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr Vector3() noexcept = default;
		/// @brief Creates a vector and assigns its components from the arguments.
		/// @param x X-component.
		/// @param y Y-component.
		/// @param z Z-component.
		[[nodiscard("Pure constructor")]]
		constexpr Vector3(T x, T y, T z) noexcept;
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
		/// @details This function is much faster than @p Magnitude() because it doesn't compute a square root.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		constexpr T MagnitudeSquared() const noexcept;

		/// @brief Computes a vector normalized from this one.
		/// @details This vector must be non-zero.
		/// @return Normalized vector.
		[[nodiscard("Pure function")]]
		Vector3 Normalized() const noexcept;
		/// @brief Normalizes the vector.
		/// @details This vector must be non-zero.
		void Normalize() noexcept;

		/// @brief Swap components and return a vector in order z, y, x.
		/// @return Swapped vector.
		[[nodiscard("Pure function")]]
		constexpr Vector3 Swap() const noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Assigns arguments to the vector components.
		/// @param x X-component.
		/// @param y Y-component.
		/// @param z Z-component.
		void Set(T x, T y, T z) noexcept;
		void Set(const T* components) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale Vector to multiply by.
		void Scale(const Vector3& scale) noexcept;

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

		Vector3& operator =(const Vector3& other) noexcept = default;
		Vector3& operator =(Vector3&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Vector to add.
		/// @return @a This.
		Vector3& operator +=(const Vector3& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Vector to subtract.
		/// @return @a This.
		Vector3& operator -=(const Vector3& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		Vector3& operator *=(T multiplier) noexcept requires(std::is_integral_v<T>);
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		Vector3& operator *=(ComputationalType multiplier) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Vector divisor.
		/// @return @a This.
		Vector3& operator /=(ComputationalType divisor) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Vector3& other) const noexcept;

	private:
		std::array<T, ComponentCount> m_components; ///< Component array in order x, y, z.
	};

	template<Arithmetic T>
	constexpr Vector3<T> Vector3Forward = Vector3(T{0}, T{0}, T{1});
	template<Arithmetic T>
	constexpr Vector3<T> Vector3Back = Vector3(T{0}, T{0}, T{-1});
	template<Arithmetic T>
	constexpr Vector3<T> Vector3Up = Vector3(T{0}, T{1}, T{0});
	template<Arithmetic T>
	constexpr Vector3<T> Vector3Down = Vector3(T{0}, T{-1}, T{0});
	template<Arithmetic T>
	constexpr Vector3<T> Vector3Right = Vector3(T{1}, T{0}, T{0});
	template<Arithmetic T>
	constexpr Vector3<T> Vector3Left = Vector3(T{-1}, T{0}, T{0});
	template<Arithmetic T>
	constexpr Vector3<T> Vector3One = Vector3(T{1}, T{1}, T{1});
	template<Arithmetic T>
	constexpr Vector3<T> Vector3Zero = Vector3(T{0}, T{0}, T{0});
	template<Arithmetic T>
	constexpr Vector3<T> Vector3Negative = Vector3(T{-1}, T{-1}, T{-1});

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
	/// @param left Left vector. Must be normalized.
	/// @param right Right vector. Must be normalized.
	/// @return Angle in radians.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	typename Vector3<T>::ComputationalType Angle(const Vector3<T>& left, const Vector3<T>& right) noexcept;
	/// @brief Computes a signed angle between two vectors.
	///        Sign is copied from the sign of the dot product of the @p axis and the cross product of the @p left and @p right.
	/// @tparam T Component type.
	/// @param left Left vector. Must be normalized.
	/// @param right Right vector. Must be normalized.
	/// @param axis Sign reference.
	/// @return Angle in radians.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	typename Vector3<T>::ComputationalType AngleSigned(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept;

	/// @brief Projects the @p vector onto the @p target.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param target Projection target.
	/// @return Projected vector.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Project(const Vector3<T>& vector, const Vector3<T>& target) noexcept;
	/// @brief Projects the @p vector onto a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be normalized.
	/// @return Projected vector.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> ProjectOnPlane(const Vector3<T>& vector, const Vector3<T>& normal) noexcept;

	/// @brief Reflects the @p vector off a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be normalized.
	/// @return Reflected vector.
	template<Arithmetic T> [[nodiscard("Pure function")]]
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
	constexpr bool AreAlmostEqual(const Vector3<T>& left, const Vector3<T>& right, typename Vector3<T>::ComputationalType tolerance = typename Vector3<T>::ComputationalType{0.00001}) noexcept;

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
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Vector3<T>& vector, T multiplier) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Vector3<T>& vector, typename Vector3<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(T multiplier, const Vector3<T>& vector) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(typename Vector3<T>::ComputationalType multiplier, const Vector3<T>& vector) noexcept;

	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator /(const Vector3<T>& vector, typename Vector3<T>::ComputationalType divisor) noexcept;

	/// @brief Puts @p Vector.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param vector Input source.
	/// @return @p stream.
	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Vector3<T>& vector);
}

namespace PonyEngine::Math
{
	template<Arithmetic T>
	constexpr Vector3<T>::Vector3(const T x, const T y, const T z) noexcept :
		m_components{x, y, z}
	{
	}

	template<Arithmetic T>
	constexpr Vector3<T>::Vector3(const T* const components) noexcept
	{
		std::ranges::copy(components, components + ComponentCount, Data());
	}

	template<Arithmetic T>
	constexpr T& Vector3<T>::X() noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr const T& Vector3<T>::X() const noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr T& Vector3<T>::Y() noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr const T& Vector3<T>::Y() const noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr T& Vector3<T>::Z() noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr const T& Vector3<T>::Z() const noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr T* Vector3<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	constexpr const T* Vector3<T>::Data() const noexcept
	{
		return m_components.data();
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
	Vector3<T> Vector3<T>::Normalized() const noexcept
	{
		return *this * (ComputationalType{1} / Magnitude());
	}

	template<Arithmetic T>
	void Vector3<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	constexpr Vector3<T> Vector3<T>::Swap() const noexcept
	{
		return Vector3(Z(), Y(), X());
	}

	template<Arithmetic T>
	bool Vector3<T>::IsFinite() const noexcept
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
	void Vector3<T>::Set(const T x, const T y, const T z) noexcept
	{
		X() = x;
		Y() = y;
		Z() = z;
	}

	template<Arithmetic T>
	void Vector3<T>::Set(const T* components) noexcept
	{
		std::ranges::copy(components, components + ComponentCount, Data());
	}

	template<Arithmetic T>
	void Vector3<T>::Scale(const Vector3& scale) noexcept
	{
		Multiply(Data(), scale.Data(), ComponentCount);
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

	template<Arithmetic T>
	typename Vector3<T>::ComputationalType Angle(const Vector3<T>& left, const Vector3<T>& right) noexcept
	{
		return std::acos(static_cast<typename Vector3<T>::ComputationalType>(Dot(left, right)));
	}

	template<Arithmetic T>
	typename Vector3<T>::ComputationalType AngleSigned(const Vector3<T>& left, const Vector3<T>& right, const Vector3<T>& axis) noexcept
	{
		const Vector3<T> cross = Cross(left, right);
		const T dot = Dot(cross, axis);
		const typename Vector3<T>::ComputationalType angle = Angle(left, right);

		return std::copysign(angle, static_cast<typename Vector3<T>::ComputationalType>(dot));
	}

	template<Arithmetic T>
	constexpr Vector3<T> Project(const Vector3<T>& vector, const Vector3<T>& target) noexcept
	{
		const typename Vector3<T>::ComputationalType multiplier = static_cast<typename Vector3<T>::ComputationalType>(Dot(vector, target)) / Dot(target, target);

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
	constexpr bool AreAlmostEqual(const Vector3<T>& left, const Vector3<T>& right, const typename Vector3<T>::ComputationalType tolerance) noexcept
	{
		return (left - right).MagnitudeSquared() < tolerance * tolerance;
	}

	template<Arithmetic T>
	std::string Vector3<T>::ToString() const
	{
		return std::format("({}, {}, {})", X(), Y(), Z());
	}

	template<Arithmetic T>
	constexpr T& Vector3<T>::operator [](const std::size_t index) noexcept
	{
		return m_components[index];
	}

	template<Arithmetic T>
	constexpr const T& Vector3<T>::operator [](const std::size_t index) const noexcept
	{
		return m_components[index];
	}

	template<Arithmetic T>
	Vector3<T>& Vector3<T>::operator +=(const Vector3& other) noexcept
	{
		Add(Data(), other.Data(), ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	Vector3<T>& Vector3<T>::operator -=(const Vector3& other) noexcept
	{
		Subtract(Data(), other.Data(), ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	Vector3<T>& Vector3<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		Multiply(Data(), multiplier, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	Vector3<T>& Vector3<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		Multiply(Data(), multiplier, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	Vector3<T>& Vector3<T>::operator /=(const ComputationalType divisor) noexcept
	{
		Divide(Data(), divisor, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr bool Vector3<T>::operator ==(const Vector3& other) const noexcept
	{
		return m_components == other.m_components;
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

	template<std::integral T>
	constexpr Vector3<T> operator *(const Vector3<T>& vector, const T multiplier) noexcept
	{
		Vector3<T> product;
		Multiply(product.Data(), vector.Data(), multiplier, Vector3<T>::ComponentCount);

		return product;
	}

	template<Arithmetic T>
	constexpr Vector3<T> operator *(const Vector3<T>& vector, const typename Vector3<T>::ComputationalType multiplier) noexcept
	{
		Vector3<T> product;
		Multiply(product.Data(), vector.Data(), multiplier, Vector3<T>::ComponentCount);

		return product;
	}

	template<std::integral T>
	constexpr Vector3<T> operator *(const T multiplier, const Vector3<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector3<T> operator *(const typename Vector3<T>::ComputationalType multiplier, const Vector3<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	template<Arithmetic T>
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
