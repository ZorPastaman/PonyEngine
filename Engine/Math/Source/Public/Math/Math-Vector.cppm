/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Vector;

import std;

import PonyEngine.Type;

import :Common;
import :InternalUtility;

export namespace PonyEngine::Math
{
	/// @brief Vector.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	class Vector final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr std::size_t ComponentCount = Size; ///< Component count.

		/// @brief Creates a vector and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr Vector() noexcept = default;
		/// @brief Creates a uniform vector.
		/// @param value Value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Vector(T value) noexcept;
		/// @brief Creates a vector and assigns its components from the arguments.
		/// @tparam Ts Component types.
		/// @param components Vector components
		template<Type::Arithmetic... Ts>[[nodiscard("Pure constructor")]]
		explicit constexpr Vector(Ts... components) noexcept requires (sizeof...(Ts) == Size);
		/// @brief Creates a vector and assigns its components from the @p span.
		/// @param span Components.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Vector(std::span<const T, Size> span) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Vector(const Vector& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Vector(Vector&& other) noexcept = default;

		constexpr ~Vector() noexcept = default;

		/// @brief Creates a vector where a value at the @p index is @p value and every other value is zero.
		/// @param value Value.
		/// @param index Value index.
		/// @return Vector.
		[[nodiscard("Pure function")]]
		static constexpr Vector CreateOneValue(T value, std::size_t index) noexcept;

		/// @brief Gets a zero vector.
		/// @return Zero vector.
		[[nodiscard("Pure function")]]
		static constexpr const Vector& Zero() noexcept;
		/// @brief Gets a one vector.
		/// @return One vector.
		[[nodiscard("Pure function")]]
		static constexpr const Vector& One() noexcept;
		/// @brief Gets a negative vector.
		/// @return Negative vector.
		[[nodiscard("Pure function")]]
		static constexpr const Vector& Negative() noexcept requires (std::is_signed_v<T>);
		/// @brief Gets a right vector.
		/// @return Right vector.
		[[nodiscard("Pure function")]]
		static constexpr const Vector& Right() noexcept requires (Size <= 3uz);
		/// @brief Gets a left vector.
		/// @return Left vector.
		[[nodiscard("Pure function")]]
		static constexpr const Vector& Left() noexcept requires (Size <= 3uz && std::is_signed_v<T>);
		/// @brief Gets an up vector.
		/// @return Up vector.
		[[nodiscard("Pure function")]]
		static constexpr const Vector& Up() noexcept requires (Size == 2uz || Size == 3uz);
		/// @brief Gets a down vector.
		/// @return Down vector.
		[[nodiscard("Pure function")]]
		static constexpr const Vector& Down() noexcept requires ((Size == 2uz || Size == 3uz) && std::is_signed_v<T>);
		/// @brief Gets a forward vector.
		/// @return Forward vector.
		[[nodiscard("Pure function")]]
		static constexpr const Vector& Forward() noexcept requires (Size == 3uz);
		/// @brief Gets a back vector.
		/// @return Back vector.
		[[nodiscard("Pure function")]]
		static constexpr const Vector& Back() noexcept requires (Size == 3uz && std::is_signed_v<T>);

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
		constexpr T& Y() noexcept requires (Size >= 2uz);
		/// @brief Gets the y-component.
		/// @return Y-component.
		[[nodiscard("Pure function")]]
		constexpr const T& Y() const noexcept requires (Size >= 2uz);
		/// @brief Gets the z-component.
		/// @return Z-component.
		[[nodiscard("Pure function")]]
		constexpr T& Z() noexcept requires (Size >= 3uz);
		/// @brief Gets the z-component.
		/// @return Z-component.
		[[nodiscard("Pure function")]]
		constexpr const T& Z() const noexcept requires (Size >= 3uz);
		/// @brief Gets the w-component.
		/// @return W-component.
		[[nodiscard("Pure function")]]
		constexpr T& W() noexcept requires (Size >= 4uz);
		/// @brief Gets the w-component.
		/// @return W-component.
		[[nodiscard("Pure function")]]
		constexpr const T& W() const noexcept requires (Size >= 4uz);
		/// @brief Gets the vector span.
		/// @return Span.
		[[nodiscard("Pure function")]]
		constexpr std::span<T, Size> Span() noexcept;
		/// @brief Gets the vector span.
		/// @return Span.
		[[nodiscard("Pure function")]]
		constexpr std::span<const T, Size> Span() const noexcept;

		/// @brief Computes a magnitude of the vector.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		T Magnitude() const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Computes a magnitude of the vector.
		/// @tparam U Result type.
		/// @return Computed magnitude.
		template<std::floating_point U = double> [[nodiscard("Pure function")]]
		U Magnitude() const noexcept requires (std::is_integral_v<T>);
		/// @brief Computes a squared magnitude of the vector.
		/// @remark This function is much faster than @p Magnitude() because it doesn't compute a square root.
		/// @return Computed magnitude.
		[[nodiscard("Pure function")]]
		constexpr T MagnitudeSquared() const noexcept;

		/// @brief Computes a vector normalized from this one.
		/// @note If the magnitude of the vector is 0, the result is undefined.
		/// @return Normalized vector.
		[[nodiscard("Pure function")]]
		Vector Normalized() const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Normalizes the vector.
		/// @note If the magnitude of the vector is 0, the result is undefined.
		void Normalize() noexcept requires (std::is_floating_point_v<T>);
		/// @brief Computes a vector normalized from this one.
		/// @param fallback Fallback vector. This vector is returned if the magnitude of the vector is 0.
		/// @return Normalized vector; the @p fallback if the magnitude of the vector is 0.
		[[nodiscard("Pure function")]]
		Vector Normalized(const Vector& fallback) const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Normalizes the vector.
		/// @param fallback Fallback vector. This vector is set if the magnitude of the vector is 0.
		void Normalize(const Vector& fallback) noexcept requires (std::is_floating_point_v<T>);

		/// @brief Gets a minimum among the components.
		/// @return Minimum component.
		[[nodiscard("Pure function")]]
		constexpr T& Min() noexcept;
		/// @brief Gets a minimum among the components.
		/// @return Minimum component.
		[[nodiscard("Pure function")]]
		constexpr const T& Min() const noexcept;
		/// @brief Gets a maximum among the components.
		/// @return Maximum component.
		[[nodiscard("Pure function")]]
		constexpr T& Max() noexcept;
		/// @brief Gets a maximum among the components.
		/// @return Maximum component.
		[[nodiscard("Pure function")]]
		constexpr const T& Max() const noexcept;
		/// @brief Gets a minimum and maximum among the components.
		/// @return Minimum and maximum components.
		[[nodiscard("Pure function")]]
		constexpr std::pair<T&, T&> MinMax() noexcept;
		/// @brief Gets a minimum and maximum among the components.
		/// @return Minimum and maximum components.
		[[nodiscard("Pure function")]]
		constexpr std::pair<const T&, const T&> MinMax() const noexcept;
		/// @brief Sums all the components and returns the result.
		/// @return Sum.
		[[nodiscard("Pure function")]]
		constexpr T Sum() const noexcept;
		/// @brief Multiplies all the components and returns the result.
		/// @return Product.
		[[nodiscard("Pure function")]]
		constexpr T Product() const noexcept;

		/// @brief Checks if all the components are zero.
		/// @return @a True if this vector components are zero; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsZero() const noexcept;
		/// @brief Checks if all the components are almost zero with the tolerance value.
		/// @param tolerance Tolerance.
		/// @return  @a True if this vector components are almost zero; @a false otherwise.
		template<std::same_as<T> U = T> [[nodiscard("Pure function")]]
		constexpr bool IsAlmostZero(const Tolerance<U>& tolerance = Tolerance<U>()) const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Checks if this vector is unit.
		/// @return @a True if this vector is unit; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsUnit() const noexcept;
		/// @brief Checks if this vector is almost unit with the tolerance value.
		/// @param tolerance Tolerance.
		/// @return @a True if this vector is almost unit; @a false otherwise.
		template<std::same_as<T> U = T> [[nodiscard("Pure function")]]
		constexpr bool IsAlmostUnit(const Tolerance<U>& tolerance = Tolerance<U>()) const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Checks if this vector is uniform.
		/// @return @a True if this vector is uniform; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsUniform() const noexcept;
		/// @brief Checks if this vector is almost uniform with the tolerance value.
		/// @param tolerance Tolerance.
		/// @return @a True if this vector is almost uniform; @a false otherwise.
		template<std::same_as<T> U = T> [[nodiscard("Pure function")]]
		constexpr bool IsAlmostUniform(const Tolerance<U>& tolerance = Tolerance<U>()) const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Multiplies @a this by the @p multiplier component-wise.
		/// @param multiplier Multiplier.
		constexpr void Multiply(const Vector& multiplier) noexcept;
		/// @brief Divides @a this by the @p divisor component-wise.
		/// @param divisor Divisor.
		constexpr void Divide(const Vector& divisor) noexcept;

		/// @brief Creates a string representing a state of the vector.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Casts all the components to the @p U and returns a new vector with those components.
		/// @tparam U Target component type.
		template<Type::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Vector<U, Size>() const noexcept;

		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, Size).
		/// @return Component.
		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, Size).
		/// @return Component.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr Vector& operator =(const Vector& other) noexcept = default;
		constexpr Vector& operator =(Vector&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Vector to add.
		/// @return @a This.
		constexpr Vector& operator +=(const Vector& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Vector to subtract.
		/// @return @a This.
		constexpr Vector& operator -=(const Vector& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		constexpr Vector& operator *=(T multiplier) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @tparam U Multiplier type.
		/// @param multiplier Vector multiplier.
		/// @return @a This.
		template<std::floating_point U>
		constexpr Vector& operator *=(U multiplier) noexcept requires (std::is_integral_v<T>);
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Vector divisor.
		/// @return @a This.
		constexpr Vector& operator /=(T divisor) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @tparam U Divisor type.
		/// @param divisor Vector divisor.
		/// @return @a This.
		template<std::floating_point U>
		constexpr Vector& operator /=(U divisor) noexcept requires (std::is_integral_v<T>);

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Vector& other) const noexcept = default;

	private:
		std::array<T, ComponentCount> components; ///< Component array.
	};

	/// @brief One-dimensional vector.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Vector1 = Vector<T, 1uz>;
	/// @brief Two-dimensional vector.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Vector2 = Vector<T, 2uz>;
	/// @brief Three-dimensional vector.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Vector3 = Vector<T, 3uz>;
	/// @brief Four-dimensional vector.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Vector4 = Vector<T, 4uz>;

	/// @brief Checks if all the components are finite numbers.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param vector Vector to check.
	/// @return @a True if all the components are finite; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool IsFinite(const Vector<T, Size>& vector) noexcept requires (Size >= 1uz);

	/// @brief Computes a dot product of the two vectors.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param lhs Left vector.
	/// @param rhs Right vector.
	/// @return Dot product.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr T Dot(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz);
	/// @brief Computes a cross vector and returns its z component.
	/// @tparam T Component type.
	/// @param lhs Left vector.
	/// @param rhs Right vector.
	/// @return Cross product z component.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T CrossZ(const Vector2<T>& lhs, const Vector2<T>& rhs) noexcept;
	/// @brief Computes a cross vector.
	/// @tparam T Component type.
	/// @param lhs Left vector.
	/// @param rhs Right vector.
	/// @return Cross product.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector3<T> Cross(const Vector3<T>& lhs, const Vector3<T>& rhs) noexcept;
	/// @brief Computes a distance between two points.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param lhs Left vector.
	/// @param rhs Right vector.
	/// @return Distance.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	T Distance(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz);
	/// @brief Computes a distance between two points.
	/// @tparam T Component type.
	/// @tparam U Result type.
	/// @tparam Size Component count.
	/// @param lhs Left vector.
	/// @param rhs Right vector.
	/// @return Distance.
	template<std::floating_point U = double, std::integral T, std::size_t Size> [[nodiscard("Pure function")]]
	U Distance(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz);
	/// @brief Computes a squared distance between two points.
	/// @remark This function is much faster than @p Distance 'cause it doesn't compute a square root.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param lhs Left vector.
	/// @param rhs Right vector.
	/// @return Distance
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr T DistanceSquared(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz);

	/// @brief Computes an angle between the two vectors.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param lhs Left vector. Must be unit.
	/// @param rhs Right vector. Must be unit.
	/// @return Angle in radians.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	T Angle(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz);
	/// @brief Computes a signed angle between the two vectors.
	/// @tparam T Component type.
	/// @param lhs Left vector. Must be unit.
	/// @param rhs Right vector. Must be unit.
	/// @return Angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T AngleSigned(const Vector2<T>& lhs, const Vector2<T>& rhs) noexcept;
	/// @brief Computes a signed angle between the two vectors.
	/// @tparam T Component type.
	/// @param lhs Left vector. Must be unit.
	/// @param rhs Right vector. Must be unit.
	/// @param axis Sign reference.
	/// @return Angle in radians.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T AngleSigned(const Vector3<T>& lhs, const Vector3<T>& rhs, const Vector3<T>& axis) noexcept;

	/// @brief Computes a vector rotated by 90 degrees clockwise.
	/// @return Vector rotated by 90 degrees clockwise.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Rotate90CW(const Vector2<T>& vector) noexcept;
	/// @brief Computes a vector rotated by 90 degrees counter-clockwise.
	/// @return Vector rotated by 90 degrees counter-clockwise.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Vector2<T> Rotate90CCW(const Vector2<T>& vector) noexcept;

	/// @brief Projects the @p vector onto the @p normal.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param vector Projection source.
	/// @param normal Projection target. Must be unit.
	/// @return Projected vector.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> Project(const Vector<T, Size>& vector, const Vector<T, Size>& normal) noexcept requires (Size >= 1uz);
	/// @brief Projects the @p vector onto a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be unit.
	/// @return Projected vector.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> ProjectOnPlane(const Vector<T, Size>& vector, const Vector<T, Size>& normal) noexcept requires (Size >= 1uz);
	/// @brief Reflects the @p vector off a plane defined by the @p normal vector.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param vector Projection source.
	/// @param normal Normal of a projection target plane. Must be unit.
	/// @return Reflected vector.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> Reflect(const Vector<T, Size>& vector, const Vector<T, Size>& normal) noexcept requires (Size >= 1uz);

	/// @brief Multiplies the @p lhs vector by the @p rhs vector component-wise.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param lhs Multiplicand.
	/// @param rhs Multiplier.
	/// @return Product.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> Multiply(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz);
	/// @brief Divides the @p lhs vector by the @p rhs vector component-wise.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param lhs Dividend.
	/// @param rhs Divisor.
	/// @return Quotient.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> Divide(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz);

	/// @brief Computes absolute values of the @p vector components.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param vector Source.
	/// @return Absolute vector.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> Abs(const Vector<T, Size>& vector) noexcept requires (Size >= 1uz);

	/// @brief Creates a vector consisting of minimal elements of the two vectors.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param lhs Left vector.
	/// @param rhs Right vector.
	/// @return Vector of minimal elements.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> Min(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz);
	/// @brief Creates a vector consisting of maximal elements of the two vectors.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param lhs Left vector.
	/// @param rhs Right vector.
	/// @return Vector of maximal elements.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> Max(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz);
	/// @brief Clamps the @p value between the @p min and @p max component-wise.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param value Value.
	/// @param min Minimum.
	/// @param max Maximum.
	/// @return Clamped vector.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> Clamp(const Vector<T, Size>& value, const Vector<T, Size>& min, const Vector<T, Size>& max) noexcept requires (Size >= 1uz);
	/// @brief Clamps the @p vector magnitude.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param vector Vector.
	/// @param magnitude Max magnitude.
	/// @return Clamped vector.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Vector<T, Size> ClampMagnitude(const Vector<T, Size>& vector, T magnitude) noexcept requires (Size >= 1uz);
	/// @brief Linear interpolation between the two vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between the two vectors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated vector.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> Lerp(const Vector<T, Size>& from, const Vector<T, Size>& to, T time) noexcept requires (Size >= 1uz);
	/// @brief Linear interpolation between the two vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between the two vectors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @tparam U Time type.
	/// @tparam Size Component count.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated vector.
	template<std::floating_point U = double, std::integral T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Vector<T, Size> Lerp(const Vector<T, Size>& from, const Vector<T, Size>& to, U time) noexcept requires (Size >= 1uz);

	/// @brief Checks if the two vectors are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param lhs Left vector.
	/// @param rhs Right vector.
	/// @param tolerance Tolerance.
	/// @return @a True if the vectors are almost equal; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs, const Tolerance<T>& tolerance = Tolerance<T>()) noexcept requires (Size >= 1uz);

	/// @brief Sums the @p lhs and the @p rhs vectors.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param lhs Augend.
	/// @param rhs Addend.
	/// @return Sum.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure operator")]]
	constexpr Vector<T, Size> operator +(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz);

	/// @brief Negates the @p vector.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param vector Vector to negate.
	/// @return Negated vector.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure operator")]]
	constexpr Vector<T, Size> operator -(const Vector<T, Size>& vector) noexcept requires (Size >= 1uz);

	/// @brief Subtracts the @p rhs vector from the @p lhs one.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param lhs Minuend.
	/// @param rhs Subtrahend.
	/// @return Difference.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure operator")]]
	constexpr Vector<T, Size> operator -(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz);

	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param vector Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure operator")]]
	constexpr Vector<T, Size> operator *(const Vector<T, Size>& vector, T multiplier) noexcept requires (Size >= 1uz);
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @tparam U Multiplier type.
	/// @tparam Size Component count.
	/// @param vector Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::floating_point U = double, std::integral T, std::size_t Size> [[nodiscard("Pure operator")]]
	constexpr Vector<T, Size> operator *(const Vector<T, Size>& vector, U multiplier) noexcept requires (Size >= 1uz);
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand.
	/// @return Product.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure operator")]]
	constexpr Vector<T, Size> operator *(T multiplier, const Vector<T, Size>& vector) noexcept requires (Size >= 1uz);
	/// @brief Multiplies the @p vector components by the @p multiplier.
	/// @tparam T Component type.
	/// @tparam U Multiplier type.
	/// @tparam Size Component count.
	/// @param multiplier Multiplier.
	/// @param vector Multiplicand.
	/// @return Product.
	template<std::floating_point U = double, std::integral T, std::size_t Size> [[nodiscard("Pure operator")]]
	constexpr Vector<T, Size> operator *(U multiplier, const Vector<T, Size>& vector) noexcept requires (Size >= 1uz);

	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param vector Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure operator")]]
	constexpr Vector<T, Size> operator /(const Vector<T, Size>& vector, T divisor) noexcept requires (Size >= 1uz);
	/// @brief Divides the @p vector components by the @p divisor.
	/// @tparam T Component type.
	/// @tparam U Divisor type.
	/// @tparam Size Component count.
	/// @param vector Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<std::floating_point U = double, std::integral T, std::size_t Size> [[nodiscard("Pure operator")]]
	constexpr Vector<T, Size> operator /(const Vector<T, Size>& vector, U divisor) noexcept requires (Size >= 1uz);
	/// @brief Divides the @p dividend by the @p vector components.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param dividend Dividend.
	/// @param vector Divisor.
	/// @return Quotient.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure operator")]]
	constexpr Vector<T, Size> operator /(T dividend, const Vector<T, Size>& vector) noexcept requires (Size >= 1uz);
	/// @brief Divides the @p dividend by the @p vector components.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param dividend Dividend.
	/// @param vector Divisor.
	/// @return Quotient.
	template<std::floating_point U = double, std::integral T, std::size_t Size> [[nodiscard("Pure operator")]]
	constexpr Vector<T, Size> operator /(U dividend, const Vector<T, Size>& vector) noexcept requires (Size >= 1uz);

	/// @brief Outputs a string representation of the @p vector.
	/// @tparam T Component type.
	/// @tparam Size Component count.
	/// @param stream Target stream.
	/// @param vector Input source.
	/// @return @p stream.
	template<Type::Arithmetic T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const Vector<T, Size>& vector) requires (Size >= 1uz);
}

/// @brief Vector formatter.
/// @tparam T Component type.
/// @tparam Size Component count.
export template<PonyEngine::Type::Arithmetic T, std::size_t Size>
struct std::formatter<PonyEngine::Math::Vector<T, Size>, char>
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

	static auto format(const PonyEngine::Math::Vector<T, Size>& vector, std::format_context& context)
	{
		return std::ranges::copy(vector.ToString(), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr Vector<T, Size>::Vector(const T value) noexcept
	{
		for (T& component : components)
		{
			component = value;
		}
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	template<Type::Arithmetic... Ts>
	constexpr Vector<T, Size>::Vector(Ts... components) noexcept requires (sizeof...(Ts) == Size) :
		components{ConvertTo<T>(components)...}
	{
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr Vector<T, Size>::Vector(const std::span<const T, Size> span) noexcept
	{
		if consteval
		{
			std::ranges::copy(span, components.begin());
		}
		else
		{
			std::memcpy(components.data(), span.data(), sizeof(components));
		}
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr Vector<T, Size> Vector<T, Size>::CreateOneValue(const T value, const std::size_t index) noexcept
	{
		auto vector = Vector();
		vector[index] = value;

		return vector;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const Vector<T, Size>& Vector<T, Size>::Zero() noexcept
	{
		static constexpr auto ZeroVector = Vector(T{0});

		return ZeroVector;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const Vector<T, Size>& Vector<T, Size>::One() noexcept
	{
		static constexpr auto OneVector = Vector(T{1});

		return OneVector;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const Vector<T, Size>& Vector<T, Size>::Negative() noexcept requires (std::is_signed_v<T>)
	{
		static constexpr auto NegativeVector = Vector(T{-1});

		return NegativeVector;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const Vector<T, Size>& Vector<T, Size>::Right() noexcept requires (Size <= 3uz)
	{
		static constexpr Vector RightVector = CreateOneValue(T{1}, 0uz);

		return RightVector;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const Vector<T, Size>& Vector<T, Size>::Left() noexcept requires (Size <= 3uz && std::is_signed_v<T>)
	{
		static constexpr Vector LeftVector = CreateOneValue(T{-1}, 0uz);

		return LeftVector;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const Vector<T, Size>& Vector<T, Size>::Up() noexcept requires (Size == 2uz || Size == 3uz)
	{
		static constexpr Vector UpVector = CreateOneValue(T{1}, 1uz);

		return UpVector;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const Vector<T, Size>& Vector<T, Size>::Down() noexcept requires ((Size == 2uz || Size == 3uz) && std::is_signed_v<T>)
	{
		static constexpr Vector DownVector = CreateOneValue(T{-1}, 1uz);

		return DownVector;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const Vector<T, Size>& Vector<T, Size>::Forward() noexcept requires (Size == 3uz)
	{
		static constexpr Vector ForwardVector = CreateOneValue(T{1}, 2uz);

		return ForwardVector;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const Vector<T, Size>& Vector<T, Size>::Back() noexcept requires (Size == 3uz && std::is_signed_v<T>)
	{
		static constexpr Vector BackVector = CreateOneValue(T{-1}, 2uz);

		return BackVector;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr T& Vector<T, Size>::X() noexcept
	{
		return components[0];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const T& Vector<T, Size>::X() const noexcept
	{
		return components[0];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr T& Vector<T, Size>::Y() noexcept requires (Size >= 2uz)
	{
		return components[1];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const T& Vector<T, Size>::Y() const noexcept requires (Size >= 2uz)
	{
		return components[1];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr T& Vector<T, Size>::Z() noexcept requires (Size >= 3uz)
	{
		return components[2];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const T& Vector<T, Size>::Z() const noexcept requires (Size >= 3uz)
	{
		return components[2];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr T& Vector<T, Size>::W() noexcept requires (Size >= 4uz)
	{
		return components[3];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const T& Vector<T, Size>::W() const noexcept requires (Size >= 4uz)
	{
		return components[3];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr std::span<T, Size> Vector<T, Size>::Span() noexcept
	{
		return components;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr std::span<const T, Size> Vector<T, Size>::Span() const noexcept
	{
		return components;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	T Vector<T, Size>::Magnitude() const noexcept requires (std::is_floating_point_v<T>)
	{
		return std::sqrt(MagnitudeSquared());
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	template<std::floating_point U>
	U Vector<T, Size>::Magnitude() const noexcept requires (std::is_integral_v<T>)
	{
		return std::sqrt(static_cast<U>(MagnitudeSquared()));
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr T Vector<T, Size>::MagnitudeSquared() const noexcept
	{
		return Dot(*this, *this);
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	Vector<T, Size> Vector<T, Size>::Normalized() const noexcept requires (std::is_floating_point_v<T>)
	{
		return *this * (T{1} / Magnitude());
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	void Vector<T, Size>::Normalize() noexcept requires (std::is_floating_point_v<T>)
	{
		*this = Normalized();
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	Vector<T, Size> Vector<T, Size>::Normalized(const Vector& fallback) const noexcept requires (std::is_floating_point_v<T>)
	{
		return IsAlmostZero() ? fallback : Normalized();
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	void Vector<T, Size>::Normalize(const Vector& fallback) noexcept requires (std::is_floating_point_v<T>)
	{
		*this = Normalized(fallback);
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr T& Vector<T, Size>::Min() noexcept
	{
		return const_cast<T&>(const_cast<const Vector&>(*this).Min());
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const T& Vector<T, Size>::Min() const noexcept
	{
		const T* min = &(*this)[0];
		for (std::size_t i = 1uz; i < Size; ++i)
		{
			min = &std::min(*min, (*this)[i]);
		}

		return *min;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr T& Vector<T, Size>::Max() noexcept
	{
		return const_cast<T&>(const_cast<const Vector&>(*this).Max());
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const T& Vector<T, Size>::Max() const noexcept
	{
		const T* max = &(*this)[0];
		for (std::size_t i = 1uz; i < Size; ++i)
		{
			max = &std::max(*max, (*this)[i]);
		}

		return *max;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr std::pair<T&, T&> Vector<T, Size>::MinMax() noexcept
	{
		const std::pair<const T&, const T&> minMax = const_cast<const Vector&>(*this).MinMax();

		return std::pair<T&, T&>(const_cast<T&>(minMax.first), const_cast<T&>(minMax.second));
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr std::pair<const T&, const T&> Vector<T, Size>::MinMax() const noexcept
	{
		const T* min = &(*this)[0];
		const T* max = &(*this)[0];
		for (std::size_t i = 1uz; i < Size; ++i)
		{
			min = &std::min(*min, (*this)[i]);
			max = &std::max(*max, (*this)[i]);
		}

		return std::pair<const T&, const T&>(*min, *max);
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr T Vector<T, Size>::Sum() const noexcept
	{
		T answer = T{0};
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			answer += (*this)[i];
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr T Vector<T, Size>::Product() const noexcept
	{
		T answer = T{1};
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			answer *= (*this)[i];
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr bool Vector<T, Size>::IsZero() const noexcept
	{
		return *this == Zero();
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	template<std::same_as<T> U>
	constexpr bool Vector<T, Size>::IsAlmostZero(const Tolerance<U>& tolerance) const noexcept requires (std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(*this, Zero(), tolerance);
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr bool Vector<T, Size>::IsUnit() const noexcept
	{
		return MagnitudeSquared() == T{1};
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	template<std::same_as<T> U>
	constexpr bool Vector<T, Size>::IsAlmostUnit(const Tolerance<U>& tolerance) const noexcept requires (std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(MagnitudeSquared(), T{1}, tolerance);
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr bool Vector<T, Size>::IsUniform() const noexcept
	{
		for (std::size_t i = 1uz; i < Size; ++i)
		{
			if ((*this)[i] != (*this)[0])
			{
				return false;
			}
		}

		return true;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	template<std::same_as<T> U>
	constexpr bool Vector<T, Size>::IsAlmostUniform(const Tolerance<U>& tolerance) const noexcept requires (std::is_floating_point_v<T>)
	{
		const auto [min, max] = MinMax();

		return AreAlmostEqual(min, max, tolerance);
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr bool Vector<T, Size>::IsFinite() const noexcept requires (std::is_floating_point_v<T>)
	{
		for (const T component : components)
		{
			if (!Math::IsFinite(component))
			{
				return false;
			}
		}

		return true;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr void Vector<T, Size>::Multiply(const Vector& multiplier) noexcept
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			(*this)[i] *= multiplier[i];
		}
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr void Vector<T, Size>::Divide(const Vector& divisor) noexcept
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			(*this)[i] /= divisor[i];
		}
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	std::string Vector<T, Size>::ToString() const
	{
		std::string answer = "(";
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			answer += std::format("{}", (*this)[i]);
			if (i < Size - 1uz)
			{
				answer += ", ";
			}
		}
		answer += ')';

		return answer;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool IsFinite(const Vector<T, Size>& vector) noexcept requires (Size >= 1uz)
	{
		return vector.IsFinite();
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr T Dot(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz)
	{
		return Multiply(lhs, rhs).Sum();
	}

	template<Type::Arithmetic T>
	constexpr T CrossZ(const Vector2<T>& lhs, const Vector2<T>& rhs) noexcept
	{
		return lhs.X() * rhs.Y() - lhs.Y() * rhs.X();
	}

	template<Type::Arithmetic T>
	constexpr Vector3<T> Cross(const Vector3<T>& lhs, const Vector3<T>& rhs) noexcept
	{
		Vector3<T> cross;
		cross.X() = lhs.Y() * rhs.Z() - lhs.Z() * rhs.Y();
		cross.Y() = lhs.Z() * rhs.X() - lhs.X() * rhs.Z();
		cross.Z() = lhs.X() * rhs.Y() - lhs.Y() * rhs.X();

		return cross;
	}

	template<Type::Arithmetic T, std::size_t Size>
	typename Vector<T, Size>::ComputationalType Distance(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz)
	{
		return std::sqrt(static_cast<typename Vector<T, Size>::ComputationalType>(DistanceSquared(lhs, rhs)));
	}

	template<std::floating_point T, std::size_t Size>
	T Distance(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz)
	{
		return std::sqrt(DistanceSquared(lhs, rhs));
	}

	template<std::floating_point U, std::integral T, std::size_t Size>
	U Distance(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz)
	{
		return std::sqrt(static_cast<U>(DistanceSquared(lhs, rhs)));
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr T DistanceSquared(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz)
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return (lhs - rhs).MagnitudeSquared();
		}
		else
		{
			Vector<T, Size> diff;
			for (std::size_t i = 0uz; i < Size; ++i)
			{
				diff[i] = std::max(lhs[i], rhs[i]) - std::min(lhs[i], rhs[i]);
			}

			return diff.MagnitudeSquared();
		}
	}

	template<std::floating_point T, std::size_t Size>
	T Angle(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz)
	{
		const T dot = std::clamp(Dot(lhs, rhs), T{-1}, T{1});

		return std::acos(dot);
	}

	template<std::floating_point T>
	T AngleSigned(const Vector2<T>& lhs, const Vector2<T>& rhs) noexcept
	{
		const T angle = Angle(lhs, rhs);
		const T zCross = CrossZ(lhs, rhs);

		return std::copysign(angle, zCross);
	}

	template<std::floating_point T>
	T AngleSigned(const Vector3<T>& lhs, const Vector3<T>& rhs, const Vector3<T>& axis) noexcept
	{
		const Vector3<T> cross = Cross(lhs, rhs);
		const T dot = Dot(cross, axis);
		const T angle = Angle(lhs, rhs);

		return std::copysign(angle, dot);
	}

	template<Type::Arithmetic T>
	constexpr Vector2<T> Rotate90CW(const Vector2<T>& vector) noexcept
	{
		return Vector2<T>(vector.Y(), -vector.X());
	}

	template<Type::Arithmetic T>
	constexpr Vector2<T> Rotate90CCW(const Vector2<T>& vector) noexcept
	{
		return Vector2<T>(-vector.Y(), vector.X());
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size> Project(const Vector<T, Size>& vector, const Vector<T, Size>& normal) noexcept requires (Size >= 1uz)
	{
		return normal * Dot(vector, normal);
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size> ProjectOnPlane(const Vector<T, Size>& vector, const Vector<T, Size>& normal) noexcept requires (Size >= 1uz)
	{
		return vector - Project(vector, normal);
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size> Reflect(const Vector<T, Size>& vector, const Vector<T, Size>& normal) noexcept requires (Size >= 1uz)
	{
		return vector + T{-2} * Dot(vector, normal) * normal;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> Multiply(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> product;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			product[i] = lhs[i] * rhs[i];
		}

		return product;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> Divide(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> quotient;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			quotient[i] = lhs[i] / rhs[i];
		}

		return quotient;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> Abs(const Vector<T, Size>& vector) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> answer;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			answer[i] = Abs(vector[i]);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> Min(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> answer;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			answer[i] = std::min(lhs[i], rhs[i]);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> Max(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> answer;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			answer[i] = std::max(lhs[i], rhs[i]);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> Clamp(const Vector<T, Size>& value, const Vector<T, Size>& min, const Vector<T, Size>& max) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> answer;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			answer[i] = std::clamp(value[i], min[i], max[i]);
		}

		return answer;
	}

	template <std::floating_point T, std::size_t Size>
	Vector<T, Size> ClampMagnitude(const Vector<T, Size>& vector, const T magnitude) noexcept requires (Size >= 1uz)
	{
		const T vectorMagnitudeSqr = vector.MagnitudeSquared();

		return vectorMagnitudeSqr > magnitude * magnitude
			? vector * (magnitude / std::sqrt(vectorMagnitudeSqr))
			: vector;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Vector<T, Size> Lerp(const Vector<T, Size>& from, const Vector<T, Size>& to, const T time) noexcept requires (Size >= 1uz)
	{
		return from + (to - from) * time;
	}

	template<std::floating_point U, std::integral T, std::size_t Size>
	constexpr Vector<T, Size> Lerp(const Vector<T, Size>& from, const Vector<T, Size>& to, const U time) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> answer;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			answer[i] = static_cast<T>(from[i] + (to[i] >= from[i] ? (to[i] - from[i]) * time : (from[i] - to[i]) * -time));
		}

		return answer;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreAlmostEqual(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs, const Tolerance<T>& tolerance) noexcept requires (Size >= 1uz)
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			if (!AreAlmostEqual(lhs[i], rhs[i], tolerance))
			{
				return false;
			}
		}

		return true;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	template<Type::Arithmetic U>
	constexpr Vector<T, Size>::operator Vector<U, Size>() const noexcept
	{
		Vector<U, Size> cast;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			cast[i] = static_cast<U>((*this)[i]);
		}

		return cast;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr T& Vector<T, Size>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr const T& Vector<T, Size>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr Vector<T, Size>& Vector<T, Size>::operator +=(const Vector& other) noexcept
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			(*this)[i] += other[i];
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr Vector<T, Size>& Vector<T, Size>::operator -=(const Vector& other) noexcept
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			(*this)[i] -= other[i];
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr Vector<T, Size>& Vector<T, Size>::operator *=(const T multiplier) noexcept
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			(*this)[i] *= multiplier;
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	template<std::floating_point U>
	constexpr Vector<T, Size>& Vector<T, Size>::operator *=(const U multiplier) noexcept requires (std::is_integral_v<T>)
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			(*this)[i] = static_cast<T>((*this)[i] * multiplier);
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	constexpr Vector<T, Size>& Vector<T, Size>::operator /=(const T divisor) noexcept
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			(*this)[i] /= divisor;
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1uz)
	template<std::floating_point U>
	constexpr Vector<T, Size>& Vector<T, Size>::operator /=(const U divisor) noexcept requires (std::is_integral_v<T>)
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			(*this)[i] = static_cast<T>((*this)[i] / divisor);
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> operator +(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> sum;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			sum[i] = lhs[i] + rhs[i];
		}

		return sum;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> operator -(const Vector<T, Size>& vector) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> negated;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			negated[i] = -vector[i];
		}

		return negated;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> operator -(const Vector<T, Size>& lhs, const Vector<T, Size>& rhs) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> difference;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			difference[i] = lhs[i] - rhs[i];
		}

		return difference;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> operator *(const Vector<T, Size>& vector, const T multiplier) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> product;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			product[i] = vector[i] * multiplier;
		}

		return product;
	}

	template<std::floating_point U, std::integral T, std::size_t Size>
	constexpr Vector<T, Size> operator *(const Vector<T, Size>& vector, const U multiplier) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> product;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			product[i] = static_cast<T>(vector[i] * multiplier);
		}

		return product;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> operator *(const T multiplier, const Vector<T, Size>& vector) noexcept requires (Size >= 1uz)
	{
		return vector * multiplier;
	}

	template<std::floating_point U, std::integral T, std::size_t Size>
	constexpr Vector<T, Size> operator *(const U multiplier, const Vector<T, Size>& vector) noexcept requires (Size >= 1uz)
	{
		return vector * multiplier;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> operator /(const Vector<T, Size>& vector, const T divisor) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> quotient;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			quotient[i] = vector[i] / divisor;
		}

		return quotient;
	}

	template<std::floating_point U, std::integral T, std::size_t Size>
	constexpr Vector<T, Size> operator /(const Vector<T, Size>& vector, const U divisor) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> quotient;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			quotient[i] = static_cast<T>(vector[i] / divisor);
		}

		return quotient;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Vector<T, Size> operator /(const T dividend, const Vector<T, Size>& vector) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> quotient;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			quotient[i] = dividend / vector[i];
		}

		return quotient;
	}

	template<std::floating_point U, std::integral T, std::size_t Size>
	constexpr Vector<T, Size> operator /(const U dividend, const Vector<T, Size>& vector) noexcept requires (Size >= 1uz)
	{
		Vector<T, Size> quotient;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			quotient[i] = static_cast<T>(dividend / vector[i]);
		}

		return quotient;
	}

	template<Type::Arithmetic T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const Vector<T, Size>& vector) requires (Size >= 1uz)
	{
		return stream << vector.ToString();
	}
}
