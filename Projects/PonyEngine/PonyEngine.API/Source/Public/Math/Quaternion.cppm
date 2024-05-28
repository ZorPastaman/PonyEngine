/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Quaternion;

import <array>;
import <cmath>;
import <cstddef>;
import <concepts>;
import <format>;
import <numbers>;
import <ostream>;
import <string>;
import <utility>;

import :ArrayArithmetics;
import :Common;
import :Vector3;
import :Vector4;

export namespace PonyEngine::Math
{
	/// @brief Quaternion implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class Quaternion final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr std::size_t ComponentCount = 4; ///< Component count. For any quaternion, it's always 4.

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
		/// @brief Creates a quaternion and assigns its components from the @p components array.
		/// @param components Component array. Its length must be at least 4.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Quaternion(const T* components) noexcept;
		/// @brief Creates a quaternion and assigns its components from the @p vector components.
		/// @param vector Component values source.
		[[nodiscard("Pure constructor")]]
		constexpr Quaternion(const Vector4<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Quaternion(const Quaternion& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Quaternion(Quaternion&& other) noexcept = default;

		constexpr ~Quaternion() noexcept = default;

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

		/// @brief Computes a magnitude of the quaternion.
		/// @details The rotation quaternion always has a magnitude of 1.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		T Magnitude() const noexcept;
		/// @brief Computes a squared magnitude of the quaternion.
		/// @details The rotation quaternion always has a magnitude of 1. This function is much faster than @p Magnitude() because it doesn't compute a square root.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		constexpr T MagnitudeSquared() const noexcept;

		/// @brief Computes a conjugate of the quaternion.
		/// @return Quaternion conjugate.
		[[nodiscard("Pure function")]]
		constexpr Quaternion Conjugate() const noexcept;
		/// @brief Computes an inverse of the quaternion.
		///	@details If you have a rotation quaternion, you should use @p Conjugate() 'cause it's more efficient.
		/// @return Quaternion inverse.
		[[nodiscard("Pure function")]]
		constexpr Quaternion Inverse() const noexcept;

		/// @brief Computes a quaternion normalized from this one.
		/// @return Normalized quaternion.
		[[nodiscard("Pure function")]]
		Quaternion Normalized() const noexcept;
		/// @brief Normalizes the quaternion.
		void Normalize() noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Assigns arguments to the quaternion components.
		/// @param x X-component.
		/// @param y Y-component.
		/// @param z Z-component.
		/// @param w W-component.
		constexpr void Set(T x, T y, T z, T w) noexcept;
		/// @brief Assigns @p components to the quaternion components.
		/// @param components Component array. Its length must be at least 4.
		constexpr void Set(const T* components) noexcept;

		/// @brief Creates a string representing a state of the quaternion. The format is '(x, y, z, w)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Casts the quaternion to a @p Vector4 copying components.
		[[nodiscard("Pure operator")]]
		constexpr operator Vector4<T>() const noexcept;

		/// @brief Gets a component by an index.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		/// @brief Gets a component by an index.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr Quaternion& operator =(const Quaternion& other) noexcept = default;
		constexpr Quaternion& operator =(Quaternion&& other) noexcept = default;
		/// @brief Combines two quaternions and assigns the result to @a this.
		///	@details Internal formula is 'this = this * other'.
		/// @param other Other quaternion.
		/// @return @a This.
		constexpr Quaternion& operator *=(const Quaternion& other) noexcept;

		/// @brief Checks if two quaternions are equal.
		/// @param other The other quaternion.
		/// @return @a True if they are equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Quaternion& other) const noexcept;

	private:
		std::array<T, ComponentCount> m_components; ///< Component array in order x, y, z, w.
	};

	/// @brief Identity quaternion.
	/// @tparam T Component type.
	template<std::floating_point T>
	constexpr Quaternion<T> QuaternionIdentity = Quaternion(T{0}, T{0}, T{0}, T{1});

	/// @brief Computes a dot product of two quaternions.
	/// @tparam T Component type.
	/// @param left Left quaternion.
	/// @param right Right quaternion.
	/// @return Dot product.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T Dot(const Quaternion<T>& left, const Quaternion<T>& right) noexcept;

	/// @brief Computes the shortest angle between two quaternions.
	/// @tparam T Component type.
	/// @param left Left quaternion. Must be normalized.
	/// @param right Right quaternion. Must be normalized.
	/// @return Angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T Angle(const Quaternion<T>& left, const Quaternion<T>& right) noexcept;

	/// @brief Linear interpolation between two quaternions if the @p time is in range [0, 1].
	///        Linear extrapolation between two quaternions if the @p time is out of range [0, 1].
	/// @details The function treats a quaternion as a @p Vector4.
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr Quaternion<T> Lerp(const Quaternion<T>& from, const Quaternion<T>& to, T time) noexcept;
	/// @brief Spherical linear interpolation between two quaternions.
	/// @tparam T Component type.
	/// @param from Interpolation start point. Must be normalized.
	/// @param to Interpolation target point. Must be normalized.
	/// @param time Interpolation time. Must be normalized.
	/// @return Interpolated quaternion.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> Slerp(const Quaternion<T>& from, const Quaternion<T>& to, T time) noexcept;

	/// @brief Checks if two quaternions are almost equal with a tolerance value.
	/// @tparam T Component type.
	///	@tparam Normalized Are the quaternions normalized? If it's @a true, the code is more efficient.
	/// @param left Left quaternion.
	/// @param right Right quaternion.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the quaternions are almost equal; @a false otherwise.
	template<std::floating_point T, bool Normalized = true> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Quaternion<T>& left, const Quaternion<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Combines two quaternions.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Quaternion<T> operator *(const Quaternion<T>& left, const Quaternion<T>& right) noexcept;
	/// @brief Transforms the @p vector with the @p quaternion.
	/// @tparam T Component type.
	/// @param quaternion Quaternion.
	/// @param vector Vector to transform.
	/// @return Transformed vector.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Quaternion<T>& quaternion, const Vector3<T>& vector) noexcept;

	/// @brief Puts @p Quaternion.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param quaternion Input source.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Quaternion<T>& quaternion);
}

namespace PonyEngine::Math
{
	/// @brief Sums two quaternions treating them as vectors.
	/// @tparam T Component type.
	/// @param left Augend.
	/// @param right Addend.
	/// @return Sum.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Quaternion<T> operator +(const Quaternion<T>& left, const Quaternion<T>& right) noexcept;

	/// @brief Subtracts the @p right from the @p left treating the quaternions as vectors.
	/// @tparam T Component type.
	/// @param left Minuend.
	/// @param right Subtrahend.
	/// @return Difference.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Quaternion<T> operator -(const Quaternion<T>& left, const Quaternion<T>& right) noexcept;

	/// @brief Multiplies the @p quaternion by the @p multiplier treating the quaternion as a vector.
	/// @tparam T Component type.
	/// @param quaternion Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Quaternion<T> operator *(const Quaternion<T>& quaternion, T multiplier) noexcept;

	template<std::floating_point T>
	constexpr Quaternion<T>::Quaternion(const T x, const T y, const T z, const T w) noexcept :
		m_components{x, y, z, w}
	{
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::Quaternion(const T* const components) noexcept
	{
		Set(components);
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::Quaternion(const Vector4<T>& vector) noexcept :
		Quaternion(vector.Data())
	{
	}

	template<std::floating_point T>
	constexpr T& Quaternion<T>::X() noexcept
	{
		return m_components[0];
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::X() const noexcept
	{
		return m_components[0];
	}

	template<std::floating_point T>
	constexpr T& Quaternion<T>::Y() noexcept
	{
		return m_components[1];
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::Y() const noexcept
	{
		return m_components[1];
	}

	template<std::floating_point T>
	constexpr T& Quaternion<T>::Z() noexcept
	{
		return m_components[2];
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::Z() const noexcept
	{
		return m_components[2];
	}

	template<std::floating_point T>
	constexpr T& Quaternion<T>::W() noexcept
	{
		return m_components[3];
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::W() const noexcept
	{
		return m_components[3];
	}

	template<std::floating_point T>
	constexpr T* Quaternion<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<std::floating_point T>
	constexpr const T* Quaternion<T>::Data() const noexcept
	{
		return m_components.data();
	}

	template<std::floating_point T>
	T Quaternion<T>::Magnitude() const noexcept
	{
		return std::sqrt(MagnitudeSquared());
	}

	template<std::floating_point T>
	constexpr T Quaternion<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Quaternion<T>::Conjugate() const noexcept
	{
		return Quaternion(-X(), -Y(), -Z(), W());
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Quaternion<T>::Inverse() const noexcept
	{
		Quaternion inverse = Conjugate();
		Multiply(inverse.Data(), T{1} / MagnitudeSquared(), ComponentCount);

		return inverse;
	}

	template<std::floating_point T>
	Quaternion<T> Quaternion<T>::Normalized() const noexcept
	{
		Quaternion normalized;
		Multiply(normalized.Data(), Data(), T{1} / Magnitude(), ComponentCount);

		return normalized;
	}

	template<std::floating_point T>
	void Quaternion<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<std::floating_point T>
	bool Quaternion<T>::IsFinite() const noexcept
	{
		return Math::IsFinite(Data(), ComponentCount);
	}

	template<std::floating_point T>
	constexpr void Quaternion<T>::Set(const T x, const T y, const T z, const T w) noexcept
	{
		X() = x;
		Y() = y;
		Z() = z;
		W() = w;
	}

	template<std::floating_point T>
	constexpr void Quaternion<T>::Set(const T* const components) noexcept
	{
		Copy(Data(), components, ComponentCount);
	}

	template<std::floating_point T>
	constexpr T Dot(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		return left.X() * right.X() + left.Y() * right.Y() + left.Z() * right.Z() + left.W() * right.W();
	}

	template<std::floating_point T>
	T Angle(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		const T dot = Dot(left, right);
		const T halfCos = std::min(std::abs(dot), T{1});

		return T{2} * std::acos(halfCos);
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Lerp(const Quaternion<T>& from, const Quaternion<T>& to, const T time) noexcept
	{
		return from + (to - from) * time;
	}

	template<std::floating_point T>
	Quaternion<T> Slerp(const Quaternion<T>& from, const Quaternion<T>& to, const T time) noexcept
	{
		const T dot = Dot(from, to);
		const T halfCos = std::min(std::abs(dot), T{1});

		if (halfCos > T{0.9999}) [[unlikely]]
		{
			return Lerp(from, to * Signum(dot), time).Normalized();
		}

		const T halfAngle = std::acos(halfCos);
		const T inverseHalfSin = T{1} / std::sin(halfAngle);
		const T fromMultiplier = std::sin((T{1} - time) * halfAngle) * inverseHalfSin;
		const T toMultiplier = std::sin(time * halfAngle) * inverseHalfSin;

		return from * fromMultiplier + to * std::copysign(toMultiplier, dot);
	}

	template<std::floating_point T, bool Normalized>
	bool AreAlmostEqual(const Quaternion<T>& left, const Quaternion<T>& right, const T tolerance) noexcept
	{
		if constexpr (Normalized)
		{
			return AreAlmostEqual(Dot(left, right), T{1}, tolerance);
		}
		else
		{
			return (left - right).MagnitudeSquared() < tolerance * tolerance;
		}
	}

	template<std::floating_point T>
	std::string Quaternion<T>::ToString() const
	{
		return std::format("({}, {}, {}, {})", X(), Y(), Z(), W());
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::operator Vector4<T>() const noexcept
	{
		return Vector4<T>(Data());
	}

	template<std::floating_point T>
	constexpr T& Quaternion<T>::operator [](const std::size_t index) noexcept
	{
		return m_components[index];
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::operator [](const std::size_t index) const noexcept
	{
		return m_components[index];
	}

	template<std::floating_point T>
	constexpr Quaternion<T>& Quaternion<T>::operator *=(const Quaternion& other) noexcept
	{
		return *this = *this * other;
	}

	template <std::floating_point T>
	constexpr bool Quaternion<T>::operator ==(const Quaternion& other) const noexcept
	{
		return m_components == other.m_components;
	}

	template<std::floating_point T>
	constexpr Quaternion<T> operator +(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		Quaternion<T> sum;
		Add(sum.Data(), left.Data(), right.Data(), Quaternion<T>::ComponentCount);

		return sum;
	}

	template<std::floating_point T>
	constexpr Quaternion<T> operator -(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		Quaternion<T> difference;
		Subtract(difference.Data(), left.Data(), right.Data(), Quaternion<T>::ComponentCount);

		return difference;
	}

	template<std::floating_point T>
	constexpr Quaternion<T> operator *(const Quaternion<T>& quaternion, const T multiplier) noexcept
	{
		Quaternion<T> product;
		Multiply(product.Data(), quaternion.Data(), multiplier, Quaternion<T>::ComponentCount);

		return product;
	}

	template<std::floating_point T>
	constexpr Quaternion<T> operator *(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		Quaternion<T> product;
		product.X() = left.X() * right.W() + left.Y() * right.Z() - left.Z() * right.Y() + left.W() * right.X();
		product.Y() = left.Y() * right.W() + left.Z() * right.X() - left.X() * right.Z() + left.W() * right.Y();
		product.Z() = left.Z() * right.W() + left.X() * right.Y() - left.Y() * right.X() + left.W() * right.Z();
		product.W() = left.W() * right.W() - left.X() * right.X() - left.Y() * right.Y() - left.Z() * right.Z();

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
