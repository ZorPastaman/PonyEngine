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

namespace PonyEngine::Math
{
	/// @brief Quaternion implementation.
	/// @tparam T Component type.
	export template<std::floating_point T>
	class Quaternion final
	{
	public:
		using ValueType = T; /// @brief Component type.

		/// @brief Creates a @p Quaternion and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr inline Quaternion() noexcept;
		/// @brief Creates a @p Quaternion and assigns its components from the arguments.
		/// @param x Value to assign to the @p x component.
		/// @param y Value to assign to the @p y component.
		/// @param z Value to assign to the @p z component.
		/// @param w Value to assign to the @p w component.
		[[nodiscard("Pure constructor")]]
		constexpr inline Quaternion(T x, T y, T z, T w) noexcept;
		/// @brief Creates a @p Quaternion and assigns its components from the @p vector components.
		/// @param vector Component values source.
		[[nodiscard("Pure constructor")]]
		constexpr inline Quaternion(const Vector4<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr inline Quaternion(const Quaternion<T>& other) noexcept = default;

		constexpr inline ~Quaternion() noexcept = default;

		/// @brief Creates a @p Quaternion by Euler angles.
		///        The rotation order is ZXY.
		/// @param xRotation Rotation around x axis in radians.
		/// @param yRotation Rotation around y axis in radians.
		/// @param zRotation Rotation around z axis in radians.
		/// @return Created @p Quaternion.
		[[nodiscard("Pure function")]]
		static Quaternion<T> CreateByEuler(T xRotation, T yRotation, T zRotation) noexcept;
		/// @brief Creates a @p Quaternion by Euler angles.
		///        The rotation order is ZXY.
		/// @param xRotation Rotation around x axis in degrees.
		/// @param yRotation Rotation around y axis in degrees.
		/// @param zRotation Rotation around z axis in degrees.
		/// @return Created @p Quaternion.
		[[nodiscard("Pure function")]]
		inline static Quaternion<T> CreateByEulerDegrees(T xRotation, T yRotation, T zRotation) noexcept;
		/// @brief Creates a @p Quaternion by Euler angles.
		///        The rotation order is ZXY.
		/// @param rotation Rotations in radians around x, y and z axis component-wise.
		/// @return Created @p Quaternion.
		[[nodiscard("Pure function")]]
		inline static Quaternion<T> CreateByEuler(const Vector3<T>& rotation) noexcept;
		/// @brief Creates a @p Quaternion by Euler angles.
		///        The rotation order is ZXY.
		/// @param rotation Rotations in degrees around x, y and z axis component-wise.
		/// @return Created @p Quaternion.
		[[nodiscard("Pure function")]]
		inline static Quaternion<T> CreateByEulerDegrees(const Vector3<T>& rotation) noexcept;
		/// @brief Creates a @p Quaternion by the rotation of @p angle around the @p axis.
		/// @param axis Rotation axis. Must be normalized.
		/// @param angle Rotation angle in radians.
		/// @return Created @p Quaternion.
		[[nodiscard("Pure function")]]
		static Quaternion<T> CreateByAxisAngle(const Vector3<T>& axis, T angle) noexcept;
		/// @brief Creates a @p Quaternion by the rotation of @p angle around the @p axis.
		/// @param axis Rotation axis. Must be normalized.
		/// @param angle Rotation angle in degrees.
		/// @return Created @p Quaternion.
		[[nodiscard("Pure function")]]
		inline static Quaternion<T> CreateByAxisAngleDegrees(const Vector3<T>& axis, T angle) noexcept;
		/// @brief Creates a @p Quaternion representing a rotation 
		///        from the vector @p fromDirection to the vector @p toDirection.
		/// @param fromDirection From direction. Must be normalized.
		/// @param toDirection To direction. Must be normalized.
		/// @return Created @p Quaternion.
		[[nodiscard("Pure function")]]
		static Quaternion<T> CreateByDirection(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept;

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
		/// @brief Gets a reference to the @p w component.
		/// @return @p W component reference.
		[[nodiscard("Pure function")]]
		inline T& W() noexcept;
		/// @brief Gets a reference to the const @p w component.
		/// @return Const @p w component reference.
		[[nodiscard("Pure function")]]
		constexpr inline const T& W() const noexcept;
		/// @brief Gets a pointer to the data array. The order is x, y, z, w.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		inline T* Data() noexcept;
		/// @brief Gets a pointer to the const data array. The order is x, y, z, w.
		/// @return Const data pointer.
		[[nodiscard("Pure function")]]
		inline const T* Data() const noexcept;

		/// @brief Computes a magnitude of a @p Quaternion.
		/// @details The pure rotation @p Quaternion always has a magnitude of 1.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		inline T Magnitude() const noexcept;
		/// @brief Computes a squared magnitude of a @p Quaternion.
		/// @details The pure rotation @p Quaternion always has a magnitude of 1.
		///          This function is much faster than @p Magnitude() because it doesn't compute a square root.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		constexpr inline T MagnitudeSquared() const noexcept;

		/// @brief Computes a @p Quaternion conjugated to this one.
		/// @return Conjugated @p Quaternion.
		[[nodiscard("Pure function")]]
		constexpr inline Quaternion<T> Conjugated() const noexcept;
		/// @brief Conjugates a @p Quaternion.
		inline void Conjugate() noexcept;

		/// @brief Computes a @p Quaternion normalized from this one.
		/// @return Normalized @p Quaternion.
		[[nodiscard("Pure function")]]
		Quaternion<T> Normalized() const noexcept;
		/// @brief Normalizes a @p Quaternion.
		inline void Normalize() noexcept;

		/// @brief Computes Euler angles. The rotation order is ZXY.
		/// @return Euler angles in radians.
		[[nodiscard("Pure function")]]
		Vector3<T> Euler() const noexcept;
		/// @brief Computes Euler angles. The rotation order is ZXY.
		/// @return Euler angles in degrees.
		[[nodiscard("Pure function")]]
		inline Vector3<T> EulerDegrees() const noexcept;

		/// @brief Computes a rotation axis and angle.
		/// @return Axis and angle in radians.
		[[nodiscard("Pure function")]]
		std::pair<Vector3<T>, T> AxisAngle() const noexcept;
		/// @brief Computes a rotation axis and angle.
		/// @return Axis and angle in degrees.
		[[nodiscard("Pure function")]]
		inline std::pair<Vector3<T>, T> AxisAngleDegrees() const noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Assigns arguments to @p Quaternion components.
		/// @param x X component.
		/// @param y Y component.
		/// @param z Z component.
		/// @param w W component.
		inline void Set(T x, T y, T z, T w) noexcept;

		/// @brief Creates a string representing a state of a @p Quaternion.
		///        The format is '(x, y, z, w)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		inline std::string ToString() const;

		/// @brief Casts a @p Quaternion to a @p Vector4 copying components.
		[[nodiscard("Pure operator")]]
		constexpr inline operator Vector4<T>() const noexcept;

		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		inline T& operator [](std::size_t index) noexcept;
		/// @brief Access to a component operator.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component dependent on the @p index. 0 -> x, 1 -> y, 2 -> z, 3 -> w.
		[[nodiscard("Pure operator")]]
		constexpr inline const T& operator [](std::size_t index) const noexcept;

		inline Quaternion<T>& operator =(const Quaternion<T>& other) noexcept = default;
		/// @brief Combines rotations of two @p Quaternions and assigns the result to @a this.
		///        It rotates @a this first and the @p other then.
		/// @param other Last @p Quaternion to rotate.
		/// @return @a This.
		inline Quaternion<T>& operator *=(const Quaternion<T>& other) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr inline bool operator ==(const Quaternion<T>& other) const noexcept = default;

		static const Quaternion<T> Identity; /// @brief Zero rotation @p Quaternion.

		constexpr inline static const std::size_t ComponentCount = 4; /// @brief Component count. For any @p Quaternion, it's always 4.

	private:
		std::array<T, ComponentCount> m_components; /// @brief Component array in order x, y, z, w.
	};

	/// @brief Computes a dot product of two @p Quaternions.
	/// @tparam T Component type.
	/// @param left Left @p Quaternion.
	/// @param right Right @p Quaternion.
	/// @return Dot product.
	export template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T Dot(const Quaternion<T>& left, const Quaternion<T>& right) noexcept;

	/// @brief Computes an angle between two @p Quaternion.
	/// @tparam T Component type.
	/// @param left Left @p Quaternion. Must be normalized.
	/// @param right Right @p Quaternion. Must be normalized.
	/// @return Angle in radians.
	export template<std::floating_point T> [[nodiscard("Pure function")]]
	T Angle(const Quaternion<T>& left, const Quaternion<T>& right) noexcept;
	/// @brief Computes an angle between two @p Quaternion.
	/// @tparam T Component type.
	/// @param left Left @p Quaternion. Must be normalized.
	/// @param right Right @p Quaternion. Must be normalized.
	/// @return Angle in degrees.
	export template<std::floating_point T> [[nodiscard("Pure function")]]
	inline T AngleDegrees(const Quaternion<T>& left, const Quaternion<T>& right) noexcept;

	/// @brief Linear interpolation between two @p Quaternions if the @p time is in range [0, 1].
	///        Linear extrapolation between two @p Quaternions if the @p time is out of range [0, 1].
	/// @details The function treats a @p Quaternion as a @p Vector4.
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated @p Quaternion.
	export template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr inline Quaternion<T> Lerp(const Quaternion<T>& from, const Quaternion<T>& to, T time) noexcept;
	/// @brief Spherical linear interpolation between two @p Quaternions if the @p time is in range [0, 1].
	/// @tparam T Component type.
	/// @param from Interpolation start point. Must be normalized.
	/// @param to Interpolation target point. Must be normalized.
	/// @param time Interpolation time. Must be normalized.
	/// @return Interpolated @p Quaternion.
	export template<std::floating_point T> [[nodiscard("Pure function")]]
	Quaternion<T> Slerp(const Quaternion<T>& from, const Quaternion<T>& to, T time) noexcept;

	/// @brief Checks if two @p Quaternions are almost equal with a tolerance value.
	/// @tparam T Component type.
	/// @param left Left @p Quaternion.
	/// @param right Right @p Quaternion.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the @p Quaternions are almost equal; @a false otherwise.
	export template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Quaternion<T>& left, const Quaternion<T>& right, T tolerance = T{0.00001}) noexcept;
	/// @brief Checks if two @p Quaternions are almost equal with a tolerance value.
	/// @details This function is faster than AreAlmostEqual().
	/// @tparam T Component type.
	/// @param left Left @p Quaternion. Must be normalized.
	/// @param right Right @p Quaternion. Must be normalized.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the @p Quaternions are almost equal; @a false otherwise.
	export template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreAlmostEqualNormalized(const Quaternion<T>& left, const Quaternion<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Combines rotations of two @p Quaternions. It rotates the @p left first and the @p right then.
	/// @tparam T Component type.
	/// @param left First @p Quaternion to rotate.
	/// @param right Last @p Quaternion to rotate.
	/// @return @p Quaternion of both rotations.
	export template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Quaternion<T> operator *(const Quaternion<T>& left, const Quaternion<T>& right) noexcept;
	/// @brief Rotates the @p vector with the rotation of the @p quaternion.
	/// @tparam T Component type.
	/// @param quaternion Rotation.
	/// @param vector Vector to rotate.
	/// @return Rotated vector.
	export template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Quaternion<T>& quaternion, const Vector3<T>& vector) noexcept;

	/// @brief Puts @p Quaternion.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param quaternion Input source.
	/// @return @p stream.
	export template<std::floating_point T>
	inline std::ostream& operator <<(std::ostream& stream, const Quaternion<T>& quaternion);

	template<std::floating_point T>
	inline constexpr Quaternion<T>::Quaternion() noexcept :
		Quaternion(T{}, T{}, T{}, T{})
	{
	}

	template<std::floating_point T>
	constexpr inline Quaternion<T>::Quaternion(const T x, const T y, const T z, const T w) noexcept :
		m_components{x, y, z, w}
	{
	}

	template<std::floating_point T>
	constexpr inline Quaternion<T>::Quaternion(const Vector4<T>& vector) noexcept :
		Quaternion(vector.X(), vector.Y(), vector.Z(), vector.W())
	{
	}

	template<std::floating_point T>
	Quaternion<T> Quaternion<T>::CreateByEuler(const T xRotation, const T yRotation, const T zRotation) noexcept
	{
		const T xHalf = xRotation * T{0.5};
		const T yHalf = yRotation * T{0.5};
		const T zHalf = zRotation * T{0.5};

		const T xCos = std::cos(xHalf);
		const T yCos = std::cos(yHalf);
		const T zCos = std::cos(zHalf);

		const T xSin = std::sin(xHalf);
		const T ySin = std::sin(yHalf);
		const T zSin = std::sin(zHalf);

		const T x = xSin * yCos * zCos + xCos * ySin * zSin;
		const T y = xCos * ySin * zCos - xSin * yCos * zSin;
		const T z = xCos * yCos * zSin - xSin * ySin * zCos;
		const T w = xCos * yCos * zCos + xSin * ySin * zSin;

		return Quaternion<T>(x, y, z, w);
	}

	template<std::floating_point T>
	inline Quaternion<T> Quaternion<T>::CreateByEulerDegrees(const T xRotation, const T yRotation, const T zRotation) noexcept
	{
		return CreateByEuler(xRotation * DegToRad<T>, yRotation * DegToRad<T>, zRotation * DegToRad<T>);
	}

	template<std::floating_point T>
	inline Quaternion<T> Quaternion<T>::CreateByEuler(const Vector3<T>& rotation) noexcept
	{
		return CreateByEuler(rotation.X(), rotation.Y(), rotation.Z());
	}

	template<std::floating_point T>
	inline Quaternion<T> Quaternion<T>::CreateByEulerDegrees(const Vector3<T>& rotation) noexcept
	{
		return CreateByEuler(rotation.X() * DegToRad<T>, rotation.Y() * DegToRad<T>, rotation.Z() * DegToRad<T>);
	}

	template<std::floating_point T>
	Quaternion<T> Quaternion<T>::CreateByAxisAngle(const Vector3<T>& axis, const T angle) noexcept
	{
		const T angleHalf = angle * T{0.5};

		const T angleSin = std::sin(angleHalf);
		const T angleCos = std::cos(angleHalf);

		const T x = axis.X() * angleSin;
		const T y = axis.Y() * angleSin;
		const T z = axis.Z() * angleSin;
		const T w = angleCos;

		return Quaternion<T>(x, y, z, w);
	}

	template<std::floating_point T>
	inline Quaternion<T> Quaternion<T>::CreateByAxisAngleDegrees(const Vector3<T>& axis, const T angle) noexcept
	{
		return CreateByAxisAngle(axis, angle * DegToRad<T>);
	}

	template<std::floating_point T>
	Quaternion<T> Quaternion<T>::CreateByDirection(const Vector3<T>& fromDirection, const Vector3<T>& toDirection) noexcept
	{
		const T dot = Dot(fromDirection, toDirection);

		Vector3<T> axis;
		if (AreAlmostEqual(dot, T{-1}))
		{
			axis = std::abs(Dot(fromDirection, Vector3<T>::Up)) > T{0.5}
				? Cross(fromDirection, Vector3<T>::Forward)
				: Cross(fromDirection, Vector3<T>::Up);
		}
		else
		{
			axis = Cross(fromDirection, toDirection);
		}
		axis.Normalize();
		if (!axis.IsFinite())
		{
			axis = Vector3<T>::Forward;
		}

		const T angle = std::acos(dot);

		return Quaternion::CreateByAxisAngle(axis, angle);
	}

	template<std::floating_point T>
	inline T& Quaternion<T>::X() noexcept
	{
		return m_components[0];
	}

	template<std::floating_point T>
	constexpr inline const T& Quaternion<T>::X() const noexcept
	{
		return m_components[0];
	}

	template<std::floating_point T>
	inline T& Quaternion<T>::Y() noexcept
	{
		return m_components[1];
	}

	template<std::floating_point T>
	constexpr inline const T& Quaternion<T>::Y() const noexcept
	{
		return m_components[1];
	}

	template<std::floating_point T>
	inline T& Quaternion<T>::Z() noexcept
	{
		return m_components[2];
	}

	template<std::floating_point T>
	constexpr inline const T& Quaternion<T>::Z() const noexcept
	{
		return m_components[2];
	}

	template<std::floating_point T>
	inline T& Quaternion<T>::W() noexcept
	{
		return m_components[3];
	}

	template<std::floating_point T>
	constexpr inline const T& Quaternion<T>::W() const noexcept
	{
		return m_components[3];
	}

	template<std::floating_point T>
	inline T* Quaternion<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<std::floating_point T>
	inline const T* Quaternion<T>::Data() const noexcept
	{
		return m_components.data();
	}

	template<std::floating_point T>
	inline T Quaternion<T>::Magnitude() const noexcept
	{
		return std::sqrt(MagnitudeSquared());
	}

	template<std::floating_point T>
	constexpr inline T Quaternion<T>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<std::floating_point T>
	constexpr inline Quaternion<T> Quaternion<T>::Conjugated() const noexcept
	{
		return Quaternion<T>(-X(), -Y(), -Z(), W());
	}

	template<std::floating_point T>
	inline void Quaternion<T>::Conjugate() noexcept
	{
		*this = Conjugated();
	}

	template<std::floating_point T>
	Quaternion<T> Quaternion<T>::Normalized() const noexcept
	{
		const T inverseMagnitude = T{1} / Magnitude();

		return Quaternion<T>(X() * inverseMagnitude, Y() * inverseMagnitude, Z() * inverseMagnitude, W() * inverseMagnitude);
	}

	template<std::floating_point T>
	inline void Quaternion<T>::Normalize() noexcept
	{
		*this = Normalized();
	}

	template<std::floating_point T>
	Vector3<T> Quaternion<T>::Euler() const noexcept
	{
		const T halfSinp = (X() * W() - Y() * Z());

		if (std::abs(halfSinp) > T{0.49999}) [[unlikely]] // singularity at north pole (+) or south pole (-)
		{
			const T xRotation = std::copysign(std::numbers::pi_v<T> * T{0.5}, halfSinp);
			const T yRotationRound = std::copysign(T{2}, halfSinp) * std::atan2(Y(), X());
			const T yRotationCorrection = std::copysign((std::abs(yRotationRound) > std::numbers::pi_v<T>) * std::numbers::pi_v<T> * T{2}, yRotationRound);
			const T yRotation = yRotationRound - yRotationCorrection;
			constexpr T zRotation = T{0};

			return Vector3<T>(xRotation, yRotation, zRotation);
		}
		else [[likely]]
		{
			const T xRotation = std::asin(T{2} * halfSinp);
			const T yRotation = std::atan2(T{2} * (Y() * W() + Z() * X()), T{1} - T{2} * (X() * X() + Y() * Y()));
			const T zRotation = std::atan2(T{2} * (Z() * W() + X() * Y()), T{1} - T{2} * (X() * X() + Z() * Z()));

			return Vector3<T>(xRotation, yRotation, zRotation);
		}
	}

	template<std::floating_point T>
	inline Vector3<T> Quaternion<T>::EulerDegrees() const noexcept
	{
		return Euler() * RadToDeg<T>;
	}

	template<std::floating_point T>
	std::pair<Vector3<T>, T> Quaternion<T>::AxisAngle() const noexcept
	{
		const T halfAngle = std::acos(W());

		const T inverseAngleSin = T{1} / std::sin(halfAngle);
		const Vector3<T> axis = Vector3<T>(X(), Y(), Z()) * inverseAngleSin;

		const T angleCorrection = (halfAngle > std::numbers::pi_v<T> * T{0.5}) * std::numbers::pi_v<T>;
		const T angle = T{2} * (halfAngle - angleCorrection);

		return std::pair<Vector3<T>, T>(axis, angle);
	}

	template<std::floating_point T>
	inline std::pair<Vector3<T>, T> Quaternion<T>::AxisAngleDegrees() const noexcept
	{
		std::pair<Vector3<T>, T> axisAngle = AxisAngle();
		axisAngle.second *= RadToDeg<T>;

		return axisAngle;
	}

	template<std::floating_point T>
	bool Quaternion<T>::IsFinite() const noexcept
	{
		return std::isfinite(X()) && std::isfinite(Y()) && std::isfinite(Z()) && std::isfinite(W());
	}

	template<std::floating_point T>
	inline void Quaternion<T>::Set(const T x, const T y, const T z, const T w) noexcept
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
	inline T AngleDegrees(const Quaternion<T>& left, const Quaternion<T>& right) noexcept
	{
		return Angle(left, right) * RadToDeg<T>;
	}

	template<std::floating_point T>
	constexpr inline Quaternion<T> Lerp(const Quaternion<T>& from, const Quaternion<T>& to, const T time) noexcept
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
	constexpr inline bool AreAlmostEqual(const Quaternion<T>& left, const Quaternion<T>& right, const T tolerance) noexcept
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
	inline std::string Quaternion<T>::ToString() const
	{
		return std::format("({}, {}, {}, {})", X(), Y(), Z(), W());
	}

	template<std::floating_point T>
	constexpr inline Quaternion<T>::operator Vector4<T>() const noexcept
	{
		return Vector4<T>(X(), Y(), Z(), W());
	}

	template<std::floating_point T>
	inline T& Quaternion<T>::operator [](const std::size_t index) noexcept
	{
		return m_components[index];
	}

	template<std::floating_point T>
	constexpr inline const T& Quaternion<T>::operator [](const std::size_t index) const noexcept
	{
		return m_components[index];
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
	inline Quaternion<T>& Quaternion<T>::operator *=(const Quaternion<T>& other) noexcept
	{
		return *this = *this * other;
	}

	template<std::floating_point T>
	inline std::ostream& operator <<(std::ostream& stream, const Quaternion<T>& quaternion)
	{
		return stream << quaternion.ToString();
	}

	template<std::floating_point T>
	const Quaternion<T> Quaternion<T>::Identity = Quaternion<T>(T{0}, T{0}, T{0}, T{1});
}
