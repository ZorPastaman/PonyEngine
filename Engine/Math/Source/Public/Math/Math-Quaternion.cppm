/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Quaternion;

import std;

import :Common;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Quaternion.
	/// @tparam T Component type.
	template<std::floating_point T>
	class Quaternion final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr std::size_t ComponentCount = 4uz; ///< Component count. For any quaternion, it's always 4.

		/// @brief Creates a quaternion and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr Quaternion() noexcept = default;
		/// @brief Creates a quaternion and assigns its components from the arguments.
		/// @param x X-component.
		/// @param y Y-component.
		/// @param z Z-component.
		/// @param w W-component.
		[[nodiscard("Pure constructor")]]
		constexpr Quaternion(T x, T y, T z, T w) noexcept;
		/// @brief Creates a quaternion and assigns its components from the @p span.
		/// @param span Span. The order is x, y, z, w.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Quaternion(std::span<const T, ComponentCount> span) noexcept;
		/// @brief Creates a quaternion and assigns its components from the @p vector components.
		/// @param vector Component values source.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Quaternion(const Vector4<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Quaternion(const Quaternion& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Quaternion(Quaternion&& other) noexcept = default;

		constexpr ~Quaternion() noexcept = default;

		/// @brief Gets an identity quaternion.
		/// @return Identity quaternion.
		[[nodiscard("Pure function")]]
		static constexpr const Quaternion& Identity() noexcept;

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
		/// @brief Gets the quaternion span. The order is x, y, z, w.
		/// @return Span.
		[[nodiscard("Pure function")]]
		constexpr std::span<T, 4> Span() noexcept;
		/// @brief Gets the quaternion span. The order is x, y, z, w.
		/// @return Span.
		[[nodiscard("Pure function")]]
		constexpr std::span<const T, 4> Span() const noexcept;

		/// @brief Computes a magnitude of the quaternion.
		/// @remark The rotation quaternion always has a magnitude of 1.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		T Magnitude() const noexcept;
		/// @brief Computes a squared magnitude of the quaternion.
		/// @remark The rotation quaternion always has a magnitude of 1.
		/// @remark This function is much faster than @p Magnitude() because it doesn't compute a square root.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		constexpr T MagnitudeSquared() const noexcept;

		/// @brief Computes a conjugate of the quaternion.
		/// @return Quaternion conjugate.
		[[nodiscard("Pure function")]]
		constexpr Quaternion Conjugate() const noexcept;
		/// @brief Computes an inverse of the quaternion.
		/// @note If this is a rotation quaternion, use @p Conjugate() 'cause it's more efficient.
		/// @note If the magnitude of the quaternion is 0, the result is undefined.
		/// @return Quaternion inverse.
		[[nodiscard("Pure function")]]
		constexpr Quaternion Inverse() const noexcept;

		/// @brief Computes a quaternion normalized from this one.
		/// @note If the magnitude of the quaternion is 0, the result is undefined.
		/// @return Normalized quaternion.
		[[nodiscard("Pure function")]]
		Quaternion Normalized() const noexcept;
		/// @brief Normalizes the quaternion.
		/// @note If the magnitude of the quaternion is 0, the result is undefined.
		void Normalize() noexcept;

		/// @brief Gets the quaternion as a vector.
		/// @return Vector.
		[[nodiscard("Pure function")]]
		constexpr Vector4<T>& Vector() noexcept;
		/// @brief Gets the quaternion as a vector.
		/// @return Vector.
		[[nodiscard("Pure function")]]
		constexpr const Vector4<T>& Vector() const noexcept;

		/// @brief Checks if this quaternion is equal to the identity quaternion.
		/// @return @a True if this quaternion is equal to the identity quaternion; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsIdentity() const noexcept;
		/// @brief Checks if this quaternion is almost equal to the identity quaternion with the tolerance value.
		/// @tparam IsUnit Is this quaternion unit? If it's @a true, the code is more efficient.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if this quaternion is almost equal to the identity quaternion; @a false otherwise.
		template<bool IsUnit = true> [[nodiscard("Pure function")]]
		constexpr bool IsAlmostIdentity(T tolerance = T{0.00001}) const noexcept;
		/// @brief Checks if this quaternion is unit.
		/// @return @a True if this quaternion is unit; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsUnit() const noexcept;
		/// @brief Checks if this quaternion is almost unit with the tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if this quaternion is almost unit; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostUnit(T tolerance = T{0.00001}) const noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsFinite() const noexcept;

		/// @brief Creates a string representing a state of the quaternion. The format is '(x, y, z, w)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Casts all the components to the @p U and returns a new quaternion with those components.
		/// @tparam U Target component type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Quaternion<U>() const noexcept;

		/// @brief Converts to a vector.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator Vector4<T>() const noexcept;

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

		constexpr Quaternion& operator =(const Quaternion& other) noexcept = default;
		constexpr Quaternion& operator =(Quaternion&& other) noexcept = default;
		/// @brief Combines the two quaternions and assigns the result to @a this.
		/// @remark Internal formula is 'this = this * other'.
		/// @param other Other quaternion.
		/// @return @a This.
		constexpr Quaternion& operator *=(const Quaternion& other) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Quaternion& other) const noexcept = default;

	private:
		Vector4<T> components; ///< Component array in order x, y, z, w.
	};

	/// @brief Computes a dot product of the two quaternions.
	/// @tparam T Component type.
	/// @param lhs Left quaternion.
	/// @param rhs Right quaternion.
	/// @return Dot product.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T Dot(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept;

	/// @brief Computes the shortest angle between the two quaternions.
	/// @tparam T Component type.
	/// @param lhs Left quaternion. Must be unit.
	/// @param rhs Right quaternion. Must be unit.
	/// @return Angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T Angle(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept;

	/// @brief Sums the @p lhs and the @p rhs quaternions as if they are vectors.
	/// @tparam T Component type.
	/// @param lhs Augend.
	/// @param rhs Addend.
	/// @return Sum.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Quaternion<T> Add(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept;

	/// @brief Negates the @p quaternion as if it's a vector.
	/// @tparam T Component type.
	/// @param quaternion Quaternion to negate.
	/// @return Negated quaternion.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Quaternion<T> Negate(const Quaternion<T>& quaternion) noexcept;
	/// @brief Subtracts the @p rhs quaternion from the @p rhs one as if they are vectors.
	/// @tparam T Component type.
	/// @param lhs Minuend.
	/// @param rhs Subtrahend.
	/// @return Difference.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Quaternion<T> Subtract(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept;

	/// @brief Multiplies the @p quaternion by the @p multiplier as if it's a vector.
	/// @tparam T Component type.
	/// @param quaternion Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Quaternion<T> Multiply(const Quaternion<T>& quaternion, T multiplier) noexcept;
	/// @brief Multiplies the @p quaternion by the @p multiplier as if it's a vector.
	/// @tparam T Component type.
	/// @param quaternion Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Quaternion<T> Multiply(T multiplier, const Quaternion<T>& quaternion) noexcept;

	/// @brief Divides the @p quaternion by the @p divisor as if it's a vector.
	/// @tparam T Component type.
	/// @param quaternion Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Quaternion<T> Divide(const Quaternion<T>& quaternion, T divisor) noexcept;

	/// @brief Linear interpolation between the two quaternions if the @p time is in range [0, 1].
	///        Linear extrapolation between the two quaternions if the @p time is out of range [0, 1].
	/// @remark The function treats a quaternion as a @p Vector4.
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Quaternion<T> Lerp(const Quaternion<T>& from, const Quaternion<T>& to, T time) noexcept;
	/// @brief Spherical linear interpolation between the two quaternions.
	/// @tparam T Component type.
	/// @param from Interpolation start point. Must be unit.
	/// @param to Interpolation target point. Must be unit.
	/// @param time Interpolation time. Must be in the range [0, 1].
	/// @return Interpolated quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> Slerp(const Quaternion<T>& from, const Quaternion<T>& to, T time) noexcept;

	/// @brief Checks if the two quaternions are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @tparam AreUnit Are the quaternions unit? If it's @a true, the code is more efficient.
	/// @param lhs Left quaternion.
	/// @param rhs Right quaternion.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the quaternions are almost equal; @a false otherwise.
	template<bool AreUnit = true, std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Quaternion<T>& lhs, const Quaternion<T>& rhs, T tolerance = T{0.00001}) noexcept;

	/// @brief Multiplies the @p left by the @p right.
	/// @tparam T Component type.
	/// @param lhs Multiplicand.
	/// @param rhs Multiplier.
	/// @return Product.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Quaternion<T> operator *(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept;
	/// @brief Transforms the @p vector with the @p quaternion.
	/// @tparam T Component type.
	/// @param quaternion Quaternion.
	/// @param vector Vector to transform.
	/// @return Transformed vector.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Quaternion<T>& quaternion, const Vector3<T>& vector) noexcept;

	/// @brief Outputs a string representation of the @p quaternion.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param quaternion Input source.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Quaternion<T>& quaternion);
}

/// @brief Quaternion formatter.
/// @tparam T Component type.
export template<std::floating_point T>
struct std::formatter<PonyEngine::Math::Quaternion<T>, char>
{
	static constexpr auto parse(std::format_parse_context& context)
	{
		if (context.begin() == context.end()) [[unlikely]]
		{
			throw std::format_error("Unexpected context end.");
		}
		if (*context.begin() != '}') [[unlikely]]
		{
			throw std::format_error("Unexpected format specifier.");
		}

		return context.begin();
	}

	static auto format(const PonyEngine::Math::Quaternion<T>& quaternion, std::format_context& context)
	{
		return std::ranges::copy(quaternion.ToString(), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<std::floating_point T>
	constexpr Quaternion<T>::Quaternion(const T x, const T y, const T z, const T w) noexcept :
		components(x, y, z, w)
	{
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::Quaternion(const std::span<const T, ComponentCount> span) noexcept :
		components(span)
	{
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::Quaternion(const Vector4<T>& vector) noexcept :
		components(vector)
	{
	}

	template<std::floating_point T>
	constexpr const Quaternion<T>& Quaternion<T>::Identity() noexcept
	{
		static constexpr auto IdentityQuaternion = Quaternion(T{0}, T{0}, T{0}, T{1});

		return IdentityQuaternion;
	}

	template<std::floating_point T>
	constexpr T& Quaternion<T>::X() noexcept
	{
		return components.X();
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::X() const noexcept
	{
		return components.X();
	}

	template<std::floating_point T>
	constexpr T& Quaternion<T>::Y() noexcept
	{
		return components.Y();
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::Y() const noexcept
	{
		return components.Y();
	}

	template<std::floating_point T>
	constexpr T& Quaternion<T>::Z() noexcept
	{
		return components.Z();
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::Z() const noexcept
	{
		return components.Z();
	}

	template<std::floating_point T>
	constexpr T& Quaternion<T>::W() noexcept
	{
		return components.W();
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::W() const noexcept
	{
		return components.W();
	}

	template<std::floating_point T>
	constexpr std::span<T, 4> Quaternion<T>::Span() noexcept
	{
		return components.Span();
	}

	template<std::floating_point T>
	constexpr std::span<const T, 4> Quaternion<T>::Span() const noexcept
	{
		return components.Span();
	}

	template<std::floating_point T>
	T Quaternion<T>::Magnitude() const noexcept
	{
		return components.Magnitude();
	}

	template<std::floating_point T>
	constexpr T Quaternion<T>::MagnitudeSquared() const noexcept
	{
		return components.MagnitudeSquared();
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Quaternion<T>::Conjugate() const noexcept
	{
		return Quaternion(-X(), -Y(), -Z(), W());
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Quaternion<T>::Inverse() const noexcept
	{
		return Multiply(Conjugate(), T{1} / MagnitudeSquared());
	}

	template<std::floating_point T>
	Quaternion<T> Quaternion<T>::Normalized() const noexcept
	{
		return Quaternion(components.Normalized());
	}

	template<std::floating_point T>
	void Quaternion<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<std::floating_point T>
	constexpr Vector4<T>& Quaternion<T>::Vector() noexcept
	{
		return components;
	}

	template<std::floating_point T>
	constexpr const Vector4<T>& Quaternion<T>::Vector() const noexcept
	{
		return components;
	}

	template<std::floating_point T>
	constexpr bool Quaternion<T>::IsIdentity() const noexcept
	{
		return *this == Identity();
	}

	template<std::floating_point T>
	template<bool IsUnit>
	constexpr bool Quaternion<T>::IsAlmostIdentity(const T tolerance) const noexcept
	{
		return AreAlmostEqual<IsUnit, T>(*this, Identity(), tolerance);
	}

	template<std::floating_point T>
	constexpr bool Quaternion<T>::IsUnit() const noexcept
	{
		return MagnitudeSquared() == T{1};
	}

	template<std::floating_point T>
	constexpr bool Quaternion<T>::IsAlmostUnit(const T tolerance) const noexcept
	{
		return AreAlmostEqual(MagnitudeSquared(), T{1}, tolerance);
	}

	template<std::floating_point T>
	constexpr bool Quaternion<T>::IsFinite() const noexcept
	{
		return components.IsFinite();
	}

	template<std::floating_point T>
	std::string Quaternion<T>::ToString() const
	{
		return components.ToString();
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr Quaternion<T>::operator Quaternion<U>() const noexcept
	{
		return Quaternion<U>(static_cast<Vector4<U>>(components));
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::operator Vector4<T>() const noexcept
	{
		return components;
	}

	template<std::floating_point T>
	constexpr T& Quaternion<T>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr Quaternion<T>& Quaternion<T>::operator *=(const Quaternion& other) noexcept
	{
		return *this = *this * other;
	}

	template<std::floating_point T>
	constexpr T Dot(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept
	{
		return Dot(lhs.Vector(), rhs.Vector());
	}

	template<std::floating_point T>
	T Angle(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept
	{
		const T dot = Dot(lhs, rhs);
		const T halfCos = std::min(std::abs(dot), T{1});

		return T{2} * std::acos(halfCos);
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Add(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept
	{
		return Quaternion<T>(lhs.Vector() + rhs.Vector());
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Negate(const Quaternion<T>& quaternion) noexcept
	{
		return Quaternion<T>(-quaternion.Vector());
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Subtract(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept
	{
		return Quaternion<T>(lhs.Vector() - rhs.Vector());
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Multiply(const Quaternion<T>& quaternion, const T multiplier) noexcept
	{
		return Quaternion<T>(quaternion.Vector() * multiplier);
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Multiply(const T multiplier, const Quaternion<T>& quaternion) noexcept
	{
		return Multiply(quaternion, multiplier);
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Divide(const Quaternion<T>& quaternion, const T divisor) noexcept
	{
		return Quaternion<T>(quaternion.Vector() / divisor);
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Lerp(const Quaternion<T>& from, const Quaternion<T>& to, const T time) noexcept
	{
		return Quaternion<T>(Lerp(from.Vector(), to.Vector(), time));
	}

	template<std::floating_point T>
	Quaternion<T> Slerp(const Quaternion<T>& from, const Quaternion<T>& to, const T time) noexcept
	{
		const T dot = Dot(from, to);
		const T halfCos = std::min(std::abs(dot), T{1});

		if (halfCos > T{0.9999}) [[unlikely]]
		{
			return Lerp(from, dot < T{0} ? Negate(to) : to, time).Normalized();
		}

		const T halfAngle = std::acos(halfCos);
		const T inverseHalfSin = T{1} / std::sin(halfAngle);
		const T fromMultiplier = std::sin((T{1} - time) * halfAngle) * inverseHalfSin;
		const T toMultiplier = std::sin(time * halfAngle) * inverseHalfSin;

		return Add(Multiply(from, fromMultiplier), Multiply(to, std::copysign(toMultiplier, dot)));
	}

	template<bool AreUnit, std::floating_point T>
	constexpr bool AreAlmostEqual(const Quaternion<T>& lhs, const Quaternion<T>& rhs, const T tolerance) noexcept
	{
		if constexpr (AreUnit)
		{
			return AreAlmostEqual(Dot(lhs, rhs), T{1}, tolerance);
		}
		else
		{
			return AreAlmostEqual(lhs.Vector(), rhs.Vector(), tolerance);
		}
	}

	template<std::floating_point T>
	constexpr Quaternion<T> operator *(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept
	{
		Quaternion<T> product;
		product.X() = lhs.X() * rhs.W() + lhs.Y() * rhs.Z() - lhs.Z() * rhs.Y() + lhs.W() * rhs.X();
		product.Y() = lhs.Y() * rhs.W() + lhs.Z() * rhs.X() - lhs.X() * rhs.Z() + lhs.W() * rhs.Y();
		product.Z() = lhs.Z() * rhs.W() + lhs.X() * rhs.Y() - lhs.Y() * rhs.X() + lhs.W() * rhs.Z();
		product.W() = lhs.W() * rhs.W() - lhs.X() * rhs.X() - lhs.Y() * rhs.Y() - lhs.Z() * rhs.Z();

		return product;
	}

	template<std::floating_point T>
	constexpr Vector3<T> operator *(const Quaternion<T>& quaternion, const Vector3<T>& vector) noexcept
	{
		const T x2 = quaternion.X() * T{2};
		const T y2 = quaternion.Y() * T{2};
		const T z2 = quaternion.Z() * T{2};

		const T x2x = x2 * quaternion.X();
		const T x2y = x2 * quaternion.Y();
		const T x2z = x2 * quaternion.Z();
		const T x2w = x2 * quaternion.W();

		const T y2y = y2 * quaternion.Y();
		const T y2z = y2 * quaternion.Z();
		const T y2w = y2 * quaternion.W();

		const T z2z = z2 * quaternion.Z();
		const T z2w = z2 * quaternion.W();

		Vector3<T> product;
		product.X() = vector.X() - (y2y + z2z) * vector.X() + (x2y - z2w) * vector.Y() + (x2z + y2w) * vector.Z();
		product.Y() = vector.Y() + (x2y + z2w) * vector.X() - (x2x + z2z) * vector.Y() + (y2z - x2w) * vector.Z();
		product.Z() = vector.Z() + (x2z - y2w) * vector.X() + (y2z + x2w) * vector.Y() - (x2x + y2y) * vector.Z();

		return product;
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Quaternion<T>& quaternion)
	{
		return stream << quaternion.ToString();
	}
}
