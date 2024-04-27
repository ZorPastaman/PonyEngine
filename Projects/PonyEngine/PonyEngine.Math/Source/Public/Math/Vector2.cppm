/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Vector2;

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
	/// @brief 2D vector implementation.
	/// @tparam T Component type.
	template<Arithmetic T>
	class Vector2 final
	{
	public:
		using ValueType = T; ///< Component type.
		using ComputationalType = ComputationalFor<T>; ///< Floating point type used in functions that require a floating point type.

		/// @brief Creates a vector and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr Vector2() noexcept = default;
		/// @brief Creates a vector and assigns its components from the arguments.
		/// @param x X-component.
		/// @param y Y-component.
		[[nodiscard("Pure constructor")]]
		constexpr Vector2(T x, T y) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Vector2(const Vector2& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Vector2(Vector2&& other) noexcept = default;

		constexpr ~Vector2() noexcept = default;

		/// @brief Creates a Vector2(0, 1).
		/// @return Up vector.
		///	@remark For non-constexpr execution use @p Vector2::Up variable.
		[[nodiscard("Pure function")]]
		static consteval Vector2 UpConsteval();
		/// @brief Creates a Vector2(0, -1).
		/// @return Down vector.
		///	@remark For non-constexpr execution use @p Vector2::Down variable.
		[[nodiscard("Pure function")]]
		static consteval Vector2 DownConsteval();
		/// @brief Creates a Vector2(1, 0).
		/// @return Right vector.
		///	@remark For non-constexpr execution use @p Vector2::Right variable.
		[[nodiscard("Pure function")]]
		static consteval Vector2 RightConsteval();
		/// @brief Creates a Vector2(-1, 0).
		/// @return Left vector.
		///	@remark For non-constexpr execution use @p Vector2::Left variable.
		[[nodiscard("Pure function")]]
		static consteval Vector2 LeftConsteval();
		/// @brief Creates a Vector2(1, 1).
		/// @return One vector.
		///	@remark For non-constexpr execution use @p Vector2::One variable.
		[[nodiscard("Pure function")]]
		static consteval Vector2 OneConsteval();
		/// @brief Creates a Vector2(0, 0).
		/// @return Zero vector.
		///	@remark For non-constexpr execution use @p Vector2::Zero variable.
		[[nodiscard("Pure function")]]
		static consteval Vector2 ZeroConsteval();
		/// @brief Creates a Vector2(-1, -1).
		/// @return Negative vector.
		///	@remark For non-constexpr execution use @p Vector2::Negative variable.
		[[nodiscard("Pure function")]]
		static consteval Vector2 NegativeConsteval();

		/// @brief Gets an x-component.
		/// @return X-component.
		[[nodiscard("Pure function")]]
		T& X() noexcept;
		/// @brief Gets an x-component.
		/// @return X-component.
		[[nodiscard("Pure function")]]
		constexpr const T& X() const noexcept;
		/// @brief Gets a y-component.
		/// @return Y-component.
		[[nodiscard("Pure function")]]
		T& Y() noexcept;
		/// @brief Gets a y-component.
		/// @return Y-component.
		[[nodiscard("Pure function")]]
		constexpr const T& Y() const noexcept;
		/// @brief Gets a data pointer - an array of 2 elements. The order is x, y.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		T* Data() noexcept;
		/// @brief Gets a data pointer - an array of 2 elements. The order is x, y.
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
		Vector2 Normalized() const noexcept;
		/// @brief Normalizes the vector.
		void Normalize() noexcept;

		/// @brief Swap components and return a vector in order y, x.
		/// @return Swapped vector.
		[[nodiscard("Pure function")]]
		constexpr Vector2 Swap() const noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Assigns arguments to the vector components.
		/// @param x X-component.
		/// @param y Y-component.
		void Set(T x, T y) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale Vector to multiply by.
		void Scale(const Vector2& scale) noexcept;

		/// @brief Creates a string representing a state of the vector. The format is '(x, y)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 1].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y.
		[[nodiscard("Pure operator")]]
		T& operator [](std::size_t index) noexcept;
		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 1].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		Vector2& operator =(const Vector2& other) noexcept = default;
		Vector2& operator =(Vector2&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Vector to add.
		/// @return @a This.
		Vector2& operator +=(const Vector2& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Vector to subtract.
		/// @return @a This.
		Vector2& operator -=(const Vector2& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		Vector2& operator *=(T multiplier) noexcept requires(std::is_integral_v<T>);
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		Vector2& operator *=(ComputationalType multiplier) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Vector divisor.
		/// @return @a This.
		Vector2& operator /=(ComputationalType divisor) noexcept;

		/// @brief Checks if two vectors are equal.
		/// @param other The other vector.
		/// @return @a True if they are equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Vector2& other) const noexcept;

		static const Vector2 Up; ///< Vector2(0, 1).
		static const Vector2 Down; ///< Vector2(0, -1).
		static const Vector2 Right; ///< Vector2(1, 0).
		static const Vector2 Left; ///< Vector2(-1, 0).
		static const Vector2 One; ///< Vector2(1, 1).
		static const Vector2 Zero; ///< Vector2(0, 0).
		static const Vector2 Negative; ///< Vector2(-1, -1).

		static constexpr std::size_t ComponentCount = 2; ///< Component count. For any vector, it's always 2.

	private:
		std::array<T, ComponentCount> m_components; ///< Component array in order x, y.
	};

	/// @brief Computes a dot product of two vectors.
	/// @tparam T Component type.
	/// @param left Left vector.
	/// @param right Right vector.
	/// @return Dot product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Dot(const Vector2<T>& left, const Vector2<T>& right) noexcept;

	/// @brief Computes an angle between two vectors.
	/// @tparam T Component type.
	/// @param left Left vector. Must be normalized.
	/// @param right Right vector. Must be normalized.
	/// @return Angle in radians.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	typename Vector2<T>::ComputationalType Angle(const Vector2<T>& left, const Vector2<T>& right) noexcept;
	/// @brief Computes a signed angle between two vectors.
	///        Sign is positive if the rotation is counterclockwise.
	///        Sign is negative if the rotation is clockwise.
	/// @tparam T Component type.
	/// @param left Left vector. Must be normalized.
	/// @param right Right vector. Must be normalized.
	/// @return Angle in radians.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	typename Vector2<T>::ComputationalType AngleSigned(const Vector2<T>& left, const Vector2<T>& right) noexcept;

	/// @brief Projects the @p vector onto the @p target.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param target Projection target.
	/// @return Projected vector.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Project(const Vector2<T>& vector, const Vector2<T>& target) noexcept;
	/// @brief Projects the @p vector onto a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be normalized.
	/// @return Projected vector.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> ProjectOnPlane(const Vector2<T>& vector, const Vector2<T>& normal) noexcept;

	/// @brief Reflects the @p vector off a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be normalized.
	/// @return Reflected vector.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Reflect(const Vector2<T>& vector, const Vector2<T>& normal) noexcept;

	/// @brief Multiplies the @p left vector by the @p right vector component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Scale(const Vector2<T>& left, const Vector2<T>& right) noexcept;

	/// @brief Linear interpolation between two vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between two vectors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated vector.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Lerp(const Vector2<T>& from, const Vector2<T>& to, typename Vector2<T>::ComputationalType time) noexcept;

	/// @brief Checks if two vectors are almost equal with a tolerance value.
	/// @tparam T Component type.
	/// @param left Left vector.
	/// @param right Right vector.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the vectors are almost equal; @a false otherwise.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Vector2<T>& left, const Vector2<T>& right, typename Vector2<T>::ComputationalType tolerance = typename Vector2<T>::ComputationalType{0.00001}) noexcept;

	/// @brief Addition operator for two vectors.
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
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator *(const Vector2<T>& vector, T multiplier) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param vector Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator *(const Vector2<T>& vector, typename Vector2<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator *(T multiplier, const Vector2<T>& vector) noexcept;
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator *(typename Vector2<T>::ComputationalType multiplier, const Vector2<T>& vector) noexcept;

	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @param vector Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator /(const Vector2<T>& vector, typename Vector2<T>::ComputationalType divisor) noexcept;

	/// @brief Puts @p Vector.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param vector Input source.
	/// @return @p stream.
	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Vector2<T>& vector);
}

namespace PonyEngine::Math
{
	template<Arithmetic T>
	constexpr Vector2<T>::Vector2(const T x, const T y) noexcept :
		m_components{x, y}
	{
	}

	template<Arithmetic T>
	consteval Vector2<T> Vector2<T>::UpConsteval()
	{
		return Vector2(T{0}, T{1});
	}

	template<Arithmetic T>
	consteval Vector2<T> Vector2<T>::DownConsteval()
	{
		return Vector2(T{0}, T{-1});
	}

	template<Arithmetic T>
	consteval Vector2<T> Vector2<T>::RightConsteval()
	{
		return Vector2(T{1}, T{0});
	}

	template<Arithmetic T>
	consteval Vector2<T> Vector2<T>::LeftConsteval()
	{
		return Vector2(T{-1}, T{0});
	}

	template<Arithmetic T>
	consteval Vector2<T> Vector2<T>::OneConsteval()
	{
		return Vector2(T{1}, T{1});
	}

	template<Arithmetic T>
	consteval Vector2<T> Vector2<T>::ZeroConsteval()
	{
		return Vector2(T{0}, T{0});
	}

	template<Arithmetic T>
	consteval Vector2<T> Vector2<T>::NegativeConsteval()
	{
		return Vector2(T{-1}, T{-1});
	}

	template<Arithmetic T>
	T& Vector2<T>::X() noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr const T& Vector2<T>::X() const noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	T& Vector2<T>::Y() noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr const T& Vector2<T>::Y() const noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	T* Vector2<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	constexpr const T* Vector2<T>::Data() const noexcept
	{
		return m_components.data();
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
	Vector2<T> Vector2<T>::Normalized() const noexcept
	{
		return *this / Magnitude();
	}

	template<Arithmetic T>
	void Vector2<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<Arithmetic T>
	constexpr Vector2<T> Vector2<T>::Swap() const noexcept
	{
		return Vector2(Y(), X());
	}

	template<Arithmetic T>
	bool Vector2<T>::IsFinite() const noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return std::isfinite(X()) && std::isfinite(Y());
		}
		else
		{
			return true;
		}
	}

	template<Arithmetic T>
	void Vector2<T>::Set(const T x, const T y) noexcept
	{
		X() = x;
		Y() = y;
	}

	template<Arithmetic T>
	void Vector2<T>::Scale(const Vector2<T>& scale) noexcept
	{
		X() *= scale.X();
		Y() *= scale.Y();
	}

	template<Arithmetic T>
	constexpr T Dot(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return left.X() * right.X() + left.Y() * right.Y();
	}

	template<Arithmetic T>
	typename Vector2<T>::ComputationalType Angle(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return std::acos(static_cast<typename Vector2<T>::ComputationalType>(Dot(left, right)));
	}

	template<Arithmetic T>
	typename Vector2<T>::ComputationalType AngleSigned(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		const typename Vector2<T>::ComputationalType angle = Angle(left, right);
		const T zCross = left.X() * right.Y() - left.Y() * right.X();

		return std::copysign(angle, static_cast<typename Vector2<T>::ComputationalType>(zCross));
	}

	template<Arithmetic T>
	constexpr Vector2<T> Project(const Vector2<T>& vector, const Vector2<T>& target) noexcept
	{
		const typename Vector2<T>::ComputationalType multiplier = static_cast<typename Vector2<T>::ComputationalType>(Dot(vector, target)) / Dot(target, target);

		return target * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector2<T> ProjectOnPlane(const Vector2<T>& vector, const Vector2<T>& normal) noexcept
	{
		return vector - normal * Dot(vector, normal);
	}

	template<Arithmetic T>
	constexpr Vector2<T> Reflect(const Vector2<T>& vector, const Vector2<T>& normal) noexcept
	{
		const T multiplier = T{-2} * Dot(vector, normal);

		return vector + normal * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector2<T> Scale(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return Vector2<T>(left.X() * right.X(), left.Y() * right.Y());
	}

	template<Arithmetic T>
	constexpr Vector2<T> Lerp(const Vector2<T>& from, const Vector2<T>& to, const typename Vector2<T>::ComputationalType time) noexcept
	{
		return from + (to - from) * time;
	}

	template<Arithmetic T>
	constexpr bool AreAlmostEqual(const Vector2<T>& left, const Vector2<T>& right, const typename Vector2<T>::ComputationalType tolerance) noexcept
	{
		return (left - right).MagnitudeSquared() < tolerance * tolerance;
	}

	template<Arithmetic T>
	std::string Vector2<T>::ToString() const
	{
		return std::format("({}, {})", X(), Y());
	}

	template<Arithmetic T>
	T& Vector2<T>::operator [](const std::size_t index) noexcept
	{
		return m_components[index];
	}

	template<Arithmetic T>
	constexpr const T& Vector2<T>::operator [](const std::size_t index) const noexcept
	{
		return m_components[index];
	}

	template<Arithmetic T>
	Vector2<T>& Vector2<T>::operator +=(const Vector2& other) noexcept
	{
		X() += other.X();
		Y() += other.Y();

		return *this;
	}

	template<Arithmetic T>
	Vector2<T>& Vector2<T>::operator -=(const Vector2& other) noexcept
	{
		X() -= other.X();
		Y() -= other.Y();

		return *this;
	}

	template<Arithmetic T>
	Vector2<T>& Vector2<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		X() *= multiplier;
		Y() *= multiplier;

		return *this;
	}

	template<Arithmetic T>
	Vector2<T>& Vector2<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		X() = RoundToIntegralIfPossible<ComputationalType, T>(X() * multiplier);
		Y() = RoundToIntegralIfPossible<ComputationalType, T>(Y() * multiplier);

		return *this;
	}

	template<Arithmetic T>
	Vector2<T>& Vector2<T>::operator /=(const ComputationalType divisor) noexcept
	{
		X() = RoundToIntegralIfPossible<ComputationalType, T>(X() / divisor);
		Y() = RoundToIntegralIfPossible<ComputationalType, T>(Y() / divisor);

		return *this;
	}

	template<Arithmetic T>
	constexpr bool Vector2<T>::operator ==(const Vector2& other) const noexcept
	{
		return m_components == other.m_components;
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return Vector2<T>(left.X() + right.X(), left.Y() + right.Y());
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator -(const Vector2<T>& vector) noexcept
	{
		return Vector2<T>(-vector.X(), -vector.Y());
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right) noexcept
	{
		return Vector2<T>(left.X() - right.X(), left.Y() - right.Y());
	}

	template<std::integral T>
	constexpr Vector2<T> operator *(const Vector2<T>& vector, const T multiplier) noexcept
	{
		return Vector2<T>(vector.X() * multiplier, vector.Y() * multiplier);
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator *(const Vector2<T>& vector, const typename Vector2<T>::ComputationalType multiplier) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(vector.X() * multiplier);
		const T y = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(vector.Y() * multiplier);

		return Vector2<T>(x, y);
	}

	template<std::integral T>
	constexpr Vector2<T> operator *(const T multiplier, const Vector2<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator *(const typename Vector2<T>::ComputationalType multiplier, const Vector2<T>& vector) noexcept
	{
		return vector * multiplier;
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator /(const Vector2<T>& vector, const typename Vector2<T>::ComputationalType divisor) noexcept
	{
		const T x = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(vector.X() / divisor);
		const T y = RoundToIntegralIfPossible<Vector2<T>::ComputationalType, T>(vector.Y() / divisor);

		return Vector2<T>(x, y);
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Vector2<T>& vector)
	{
		return stream << vector.ToString();
	}

	template<Arithmetic T>
	const Vector2<T> Vector2<T>::Up = Vector2(T{0}, T{1});
	template<Arithmetic T>
	const Vector2<T> Vector2<T>::Down = Vector2(T{0}, T{-1});
	template<Arithmetic T>
	const Vector2<T> Vector2<T>::Right = Vector2(T{1}, T{0});
	template<Arithmetic T>
	const Vector2<T> Vector2<T>::Left = Vector2(T{-1}, T{0});
	template<Arithmetic T>
	const Vector2<T> Vector2<T>::One = Vector2(T{1}, T{1});
	template<Arithmetic T>
	const Vector2<T> Vector2<T>::Zero = Vector2(T{0}, T{0});
	template<Arithmetic T>
	const Vector2<T> Vector2<T>::Negative = Vector2(T{-1}, T{-1});
}
