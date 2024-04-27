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
		/// @brief Creates a quaternion and assigns its components from the @p vector components.
		/// @param vector Component values source.
		[[nodiscard("Pure constructor")]]
		constexpr Quaternion(const Vector4<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Quaternion(const Quaternion& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Quaternion(Quaternion&& other) noexcept = default;

		constexpr ~Quaternion() noexcept = default;

		/// @brief Creates a Quaternion(0, 0, 0, 1).
		/// @return Identity quaternion.
		///	@remark For non-constexpr execution use @p Quaternion::Identity variable.
		[[nodiscard("Pure function")]]
		static consteval Quaternion IdentityConsteval();

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
		/// @brief Gets a z-component.
		/// @return Z-component.
		[[nodiscard("Pure function")]]
		T& Z() noexcept;
		/// @brief Gets a z-component.
		/// @return Z-component.
		[[nodiscard("Pure function")]]
		constexpr const T& Z() const noexcept;
		/// @brief Gets a w-component.
		/// @return W-component.
		[[nodiscard("Pure function")]]
		T& W() noexcept;
		/// @brief Gets a w-component.
		/// @return W-component.
		[[nodiscard("Pure function")]]
		constexpr const T& W() const noexcept;
		/// @brief Gets a data pointer - an array of 4 elements. The order is x, y, z, w.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		T* Data() noexcept;
		/// @brief Gets a data pointer - an array of 4 elements. The order is x, y, z, w.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		constexpr const T* Data() const noexcept;

		/// @brief Computes a magnitude of the quaternion.
		/// @details The pure rotation quaternion always has a magnitude of 1.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		T Magnitude() const noexcept;
		/// @brief Computes a squared magnitude of the quaternion.
		/// @details The pure rotation quaternion always has a magnitude of 1. This function is much faster than @p Magnitude() because it doesn't compute a square root.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		constexpr T MagnitudeSquared() const noexcept;

		/// @brief Computes a conjugate of the quaternion.
		/// @return Quaternion conjugate.
		[[nodiscard("Pure function")]]
		constexpr Quaternion Conjugate() const noexcept;

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
		void Set(T x, T y, T z, T w) noexcept;

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
		T& operator [](std::size_t index) noexcept;
		/// @brief Gets a component by an index.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		Quaternion& operator =(const Quaternion& other) noexcept = default;
		Quaternion& operator =(Quaternion&& other) noexcept = default;
		/// @brief Combines rotations of two quaternions and assigns the result to @a this. It rotates @a this first and then the @p other.
		/// @param other Rotation to add.
		/// @return @a This.
		Quaternion& operator *=(const Quaternion& other) noexcept;

		/// @brief Checks if two quaternions are equal.
		/// @param other The other quaternion.
		/// @return @a True if they are equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Quaternion& other) const noexcept;

		static const Quaternion Identity; ///< Zero rotation quaternion.

		static constexpr std::size_t ComponentCount = 4; ///< Component count. For any quaternion, it's always 4.

	private:
		std::array<T, ComponentCount> m_components; ///< Component array in order x, y, z, w.
	};

	/// @brief Computes a dot product of two quaternions.
	/// @tparam T Component type.
	/// @param left Left quaternion.
	/// @param right Right quaternion.
	/// @return Dot product.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T Dot(const Quaternion<T>& left, const Quaternion<T>& right) noexcept;

	/// @brief Computes an angle between two quaternion.
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
	/// @param left Left quaternion.
	/// @param right Right quaternion.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the quaternions are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Quaternion<T>& left, const Quaternion<T>& right, T tolerance = T{0.00001}) noexcept;
	/// @brief Checks if two quaternions are almost equal with a tolerance value.
	/// @details This function is faster than AreAlmostEqual().
	/// @tparam T Component type.
	/// @param left Left quaternion. Must be normalized.
	/// @param right Right quaternion. Must be normalized.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the quaternions are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreAlmostEqualNormalized(const Quaternion<T>& left, const Quaternion<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Combines rotations of two quaternions. It rotates the @p left first and then the @p right.
	/// @tparam T Component type.
	/// @param left First quaternion to rotate.
	/// @param right Last quaternion to rotate.
	/// @return Quaternion of both rotations.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Quaternion<T> operator *(const Quaternion<T>& left, const Quaternion<T>& right) noexcept;
	/// @brief Rotates the @p vector with the rotation of the @p quaternion.
	/// @tparam T Component type.
	/// @param quaternion Rotation.
	/// @param vector Vector to rotate.
	/// @return Rotated vector.
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
	template<std::floating_point T>
	constexpr Quaternion<T>::Quaternion(const T x, const T y, const T z, const T w) noexcept :
		m_components{x, y, z, w}
	{
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::Quaternion(const Vector4<T>& vector) noexcept :
		Quaternion(vector.X(), vector.Y(), vector.Z(), vector.W())
	{
	}

	template<std::floating_point T>
	consteval Quaternion<T> Quaternion<T>::IdentityConsteval()
	{
		return Quaternion(T{0}, T{0}, T{0}, T{1});
	}

	template<std::floating_point T>
	T& Quaternion<T>::X() noexcept
	{
		return m_components[0];
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::X() const noexcept
	{
		return m_components[0];
	}

	template<std::floating_point T>
	T& Quaternion<T>::Y() noexcept
	{
		return m_components[1];
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::Y() const noexcept
	{
		return m_components[1];
	}

	template<std::floating_point T>
	T& Quaternion<T>::Z() noexcept
	{
		return m_components[2];
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::Z() const noexcept
	{
		return m_components[2];
	}

	template<std::floating_point T>
	T& Quaternion<T>::W() noexcept
	{
		return m_components[3];
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::W() const noexcept
	{
		return m_components[3];
	}

	template<std::floating_point T>
	T* Quaternion<T>::Data() noexcept
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
	Quaternion<T> Quaternion<T>::Normalized() const noexcept
	{
		const T inverseMagnitude = T{1} / Magnitude();

		return Quaternion(X() * inverseMagnitude, Y() * inverseMagnitude, Z() * inverseMagnitude, W() * inverseMagnitude);
	}

	template<std::floating_point T>
	void Quaternion<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<std::floating_point T>
	bool Quaternion<T>::IsFinite() const noexcept
	{
		return std::isfinite(X()) && std::isfinite(Y()) && std::isfinite(Z()) && std::isfinite(W());
	}

	template<std::floating_point T>
	void Quaternion<T>::Set(const T x, const T y, const T z, const T w) noexcept
	{
		X() = x;
		Y() = y;
		Z() = z;
		W() = w;
	}

	template<std::floating_point T>
	constexpr T Dot(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		return left.X() * right.X() + left.Y() * right.Y() + left.Z() * right.Z() + left.W() * right.W();
	}

	template<std::floating_point T>
	T Angle(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		return T{2} * std::acos(Dot(left, right));
	}

	template<std::floating_point T>
	constexpr Quaternion<T> Lerp(const Quaternion<T>& from, const Quaternion<T>& to, const T time) noexcept
	{
		const Vector4<T> lerped = Lerp(static_cast<Vector4<T>>(from), static_cast<Vector4<T>>(to), time);

		return Quaternion<T>(lerped);
	}

	template<std::floating_point T>
	Quaternion<T> Slerp(const Quaternion<T>& from, const Quaternion<T>& to, const T time) noexcept
	{
		const T dot = Dot(from, to);
		const Vector4<T> fromVector = from;
		const Vector4<T> toVector = to;
		const Vector4<T> orth = (toVector - fromVector * dot).Normalized();

		if (!orth.IsFinite()) [[unlikely]]
		{
			return Lerp(fromVector, toVector, time).Normalized();
		}

		const T angle = std::acos(dot) * time;
		const T sin = std::sin(angle);
		const T cos = std::cos(angle);
		const Vector4<T> answer = fromVector * cos + orth * sin;

		return Quaternion<T>(answer);
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Quaternion<T>& left, const Quaternion<T>& right, const T tolerance) noexcept
	{
		return AreAlmostEqual(static_cast<Vector4<T>>(left), static_cast<Vector4<T>>(right), tolerance);
	}

	template<std::floating_point T>
	bool AreAlmostEqualNormalized(const Quaternion<T>& left, const Quaternion<T>& right, const T tolerance) noexcept
	{
		const T dot = Dot(left, right);

		return AreAlmostEqual(dot, T{1}, tolerance);
	}

	template<std::floating_point T>
	std::string Quaternion<T>::ToString() const
	{
		return std::format("({}, {}, {}, {})", X(), Y(), Z(), W());
	}

	template<std::floating_point T>
	constexpr Quaternion<T>::operator Vector4<T>() const noexcept
	{
		return Vector4<T>(X(), Y(), Z(), W());
	}

	template<std::floating_point T>
	T& Quaternion<T>::operator [](const std::size_t index) noexcept
	{
		return m_components[index];
	}

	template<std::floating_point T>
	constexpr const T& Quaternion<T>::operator [](const std::size_t index) const noexcept
	{
		return m_components[index];
	}

	template<std::floating_point T>
	Quaternion<T>& Quaternion<T>::operator *=(const Quaternion<T>& other) noexcept
	{
		return *this = *this * other;
	}

	template <std::floating_point T>
	constexpr bool Quaternion<T>::operator ==(const Quaternion& other) const noexcept
	{
		return m_components == other.m_components;
	}

	template<std::floating_point T>
	constexpr Quaternion<T> operator *(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		const T x = left.X() * right.W() + left.Y() * right.Z() - left.Z() * right.Y() + left.W() * right.X();
		const T y = left.Y() * right.W() + left.Z() * right.X() - left.X() * right.Z() + left.W() * right.Y();
		const T z = left.Z() * right.W() + left.X() * right.Y() - left.Y() * right.X() + left.W() * right.Z();
		const T w = left.W() * right.W() - left.X() * right.X() - left.Y() * right.Y() - left.Z() * right.Z();

		return Quaternion<T>(x, y, z, w);
	}

	template<std::floating_point T>
	constexpr Vector3<T> operator *(const Quaternion<T>& quaternion, const Vector3<T>& vector) noexcept
	{
		const T qx2 = quaternion.X() * T{2};
		const T qy2 = quaternion.Y() * T{2};
		const T qz2 = quaternion.Z() * T{2};

		const T qx2x = qx2 * quaternion.X();
		const T qx2y = qx2 * quaternion.Y();
		const T qx2z = qx2 * quaternion.Z();
		const T qx2w = qx2 * quaternion.W();

		const T qy2y = qy2 * quaternion.Y();
		const T qy2z = qy2 * quaternion.Z();
		const T qy2w = qy2 * quaternion.W();

		const T qz2z = qz2 * quaternion.Z();
		const T qz2w = qz2 * quaternion.W();

		const T x = vector.X() - (qy2y + qz2z) * vector.X() + (qx2y - qz2w) * vector.Y() + (qx2z + qy2w) * vector.Z();
		const T y = vector.Y() + (qx2y + qz2w) * vector.X() - (qx2x + qz2z) * vector.Y() + (qy2z - qx2w) * vector.Z();
		const T z = vector.Z() + (qx2z - qy2w) * vector.X() + (qy2z + qx2w) * vector.Y() - (qx2x + qy2y) * vector.Z();

		return Vector3<T>(x, y, z);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Quaternion<T>& quaternion)
	{
		return stream << quaternion.ToString();
	}

	template<std::floating_point T>
	const Quaternion<T> Quaternion<T>::Identity = Quaternion(T{0}, T{0}, T{0}, T{1});
}
