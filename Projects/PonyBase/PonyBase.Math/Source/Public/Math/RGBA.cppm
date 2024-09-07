/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Math:RGBA;

import <algorithm>;
import <array>;
import <concepts>;
import <cstddef>;
import <format>;
import <ostream>;
import <span>;
import <string>;
import <utility>;

import :RGB;
import :RGBAInt;
import :RGBInt;
import :Vector4;

export namespace PonyBase::Math
{
	/// @brief RGBA color implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class RGBA final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr std::size_t ComponentCount = 4; ///< Component count. For any RGBA, it's always 4.

		struct Predefined; ///< Predefined colors.

		/// @brief Creates a color and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr RGBA() noexcept = default;
		/// @brief Creates a color and assigns its components from the arguments.
		/// @param red Red component.
		/// @param green Green component.
		/// @param blue Blue component.
		/// @param alpha Alpha component.
		[[nodiscard("Pure constructor")]]
		constexpr RGBA(T red, T green, T blue, T alpha) noexcept;
		/// @brief Creates a color and assigns its components from the @p span.
		/// @param span Components. The order is r, g, b, a.
		[[nodiscard("Pure constructor")]]
		explicit constexpr RGBA(std::span<const T, ComponentCount> span) noexcept;
		/// @brief Converts the rgb color to an rgba color.
		/// @param rgb RGB color.
		/// @param alpha Alpha.
		[[nodiscard("Pure constructor")]]
		constexpr RGBA(const RGB<T>& rgb, T alpha) noexcept;
		/// @brief Converts the integral rgb color to an rgba color.
		/// @param rgb RGB int color.
		/// @param alpha Alpha.
		template<std::unsigned_integral U> [[nodiscard("Pure constructor")]]
		constexpr RGBA(const RGBInt<U>& rgb, T alpha) noexcept;
		/// @brief Converts the rgba int color to an rgba float color.
		/// @tparam U RGBA int color component type.
		/// @param color RGBA int color.
		template<std::unsigned_integral U> [[nodiscard("Pure constructor")]]
		explicit constexpr RGBA(const RGBAInt<U>& color) noexcept;
		/// @brief Converts the @p vector to a color component-wise. x -> r, y -> g, z -> b, w -> a.
		/// @param vector Vector to convert.
		[[nodiscard("Pure constructor")]]
		explicit constexpr RGBA(const Vector4<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr RGBA(const RGBA& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr RGBA(RGBA&& other) noexcept = default;

		constexpr ~RGBA() noexcept = default;

		/// @brief Gets the red component.
		/// @return Red component.
		[[nodiscard("Pure function")]]
		constexpr T& R() noexcept;
		/// @brief Gets the red component.
		/// @return Red component.
		[[nodiscard("Pure function")]]
		constexpr const T& R() const noexcept;
		/// @brief Gets the green component.
		/// @return Green component.
		[[nodiscard("Pure function")]]
		constexpr T& G() noexcept;
		/// @brief Gets the green component.
		/// @return Green component.
		[[nodiscard("Pure function")]]
		constexpr const T& G() const noexcept;
		/// @brief Gets the blue component.
		/// @return Blue component.
		[[nodiscard("Pure function")]]
		constexpr T& B() noexcept;
		/// @brief Gets the blue component.
		/// @return Blue component.
		[[nodiscard("Pure function")]]
		constexpr const T& B() const noexcept;
		/// @brief Gets the alpha component.
		/// @return Alpha component.
		[[nodiscard("Pure function")]]
		constexpr T& A() noexcept;
		/// @brief Gets the alpha component.
		/// @return Alpha component.
		[[nodiscard("Pure function")]]
		constexpr const T& A() const noexcept;
		/// @brief Gets the color span.
		/// @return Color span. The order is r, g, b, a.
		[[nodiscard("Pure function")]]
		constexpr std::span<T, 4> Span() noexcept;
		/// @brief Gets the color span.
		/// @return Color span. The order is r, g, b, a.
		[[nodiscard("Pure function")]]
		constexpr std::span<const T, 4> Span() const noexcept;

		/// @brief Computes a grayscale.
		/// @return Grayscale.
		[[nodiscard("Pure function")]]
		constexpr T Grayscale() const noexcept;

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

		/// @brief Converts the linear color to a gamma-corrected color.
		///	@note All the color components must be in range [0, 1].
		/// @return Gamma-corrected color.
		[[nodiscard("Pure function")]]
		RGBA Gamma() const noexcept;
		/// @brief Converts the gamma-corrected color to a linear color.
		///	@note All the color components must be in range [0, 1].
		/// @return Linear color.
		[[nodiscard("Pure function")]]
		RGBA Linear() const noexcept;

		/// @brief Checks if the color is black.
		/// @return @a True if it's black; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsBlack() const noexcept;
		/// @brief Checks if the color is almost black with the @p tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return True if it's almost black; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostBlack(T tolerance = T{0.00001}) const noexcept;
		/// @brief Checks if the color is white.
		/// @return @a True if it's white; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsWhite() const noexcept;
		/// @brief Checks if the color is almost white with the @p tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return True if it's almost white; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostWhite(T tolerance = T{0.00001}) const noexcept;
		/// @brief Checks if the color is fully transparent.
		/// @return @a True if it's fully transparent; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsTransparent() const noexcept;
		/// @brief Checks if the color is almost transparent with the @p tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if it's almost transparent; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostTransparent(T tolerance = T{0.00001}) const noexcept;

		/// @brief Checks if all the components are finite.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Sets arguments to the components.
		/// @param red Red.
		/// @param green Green.
		/// @param blue Blue.
		/// @param alpha Alpha.
		constexpr void Set(T red, T green, T blue, T alpha) noexcept;
		/// @brief Sets the @p span to the components.
		/// @param span Span. The order is r, g, b, a.
		constexpr void Set(std::span<const T, ComponentCount> span) noexcept;

		/// @brief Creates a string representing a state of the color.
		/// @return String representing a state of the color.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts all the components to @p U and returns it as a new color.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator RGBA<U>() const noexcept;
		/// @brief Converts the rgba color to an rgb color skipping the alpha.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator RGB<T>() const noexcept;
		/// @brief Converts to an integral rgba color.
		/// @tparam U Target type.
		template<std::unsigned_integral U> [[nodiscard("Pure operator")]]
		explicit constexpr operator RGBAInt<U>() const noexcept;
		/// @brief Converts to an integral rgb color.
		/// @tparam U Target type.
		template<std::unsigned_integral U> [[nodiscard("Pure operator")]]
		explicit constexpr operator RGBInt<U>() const noexcept;

		/// @brief Converts the color to a vector.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator Vector4<T>() const noexcept;

		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component. 0 -> r, 1 -> g, 2 -> b, 3 -> a.
		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component. 0 -> r, 1 -> g, 2 -> b, 3 -> a.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr RGBA& operator =(const RGBA& other) noexcept = default;
		constexpr RGBA& operator =(RGBA&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Color to add.
		/// @return @a This.
		constexpr RGBA& operator +=(const RGBA& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Color to subtract.
		/// @return @a This.
		constexpr RGBA& operator -=(const RGBA& other) noexcept;
		/// @brief Multiplies @a this by the @p other component-wise.
		/// @param other Color multiplier.
		/// @return @a This.
		constexpr RGBA& operator *=(const RGBA& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Color multiplier.
		/// @return @a This.
		constexpr RGBA& operator *=(T multiplier) noexcept;
		/// @brief Divides @a this by the @p other component-wise.
		/// @param other Color divisor.
		/// @return @a This.
		constexpr RGBA& operator /=(const RGBA& other) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Color divisor.
		/// @return @a This.
		constexpr RGBA& operator /=(T divisor) noexcept;

		/// @brief Check if all the components in the two colors are equal.
		/// @param other Color to compare with.
		/// @return @a True if they're equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const RGBA& other) const noexcept;

	private:
		std::array<T, ComponentCount> components; ///< Component array in order red, green, blue, alpha.
	};

	/// @brief Computes a distance between two colors.
	/// @tparam T Component type.
	/// @param left Left color.
	/// @param right Right color.
	/// @return Distance.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T Distance(const RGBA<T>& left, const RGBA<T>& right) noexcept;
	/// @brief Computes a squared distance between two colors.
	/// @remark This function is much faster than @p Distance 'cause it doesn't compute a square root.
	/// @tparam T Component type.
	/// @param left Left color.
	/// @param right Right color.
	/// @return Distance
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T DistanceSquared(const RGBA<T>& left, const RGBA<T>& right) noexcept;

	/// @brief Creates a color consisting of minimal elements of the two colors.
	/// @tparam T Component type.
	/// @param left Left color.
	/// @param right Right color.
	/// @return Color of minimal elements.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr RGBA<T> Min(const RGBA<T>& left, const RGBA<T>& right) noexcept;
	/// @brief Creates a color consisting of maximal elements of the two colors.
	/// @tparam T Component type.
	/// @param left Left color.
	/// @param right Right color.
	/// @return Color of maximal elements.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr RGBA<T> Max(const RGBA<T>& left, const RGBA<T>& right) noexcept;
	/// @brief Clamps the @p value between the @p min and @p max component-wise.
	/// @tparam T Component type.
	/// @param value Value.
	/// @param min Minimum.
	/// @param max Maximum.
	/// @return Clamped color.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr RGBA<T> Clamp(const RGBA<T>& value, const RGBA<T>& min, const RGBA<T>& max) noexcept;
	/// @brief Linear interpolation between the two colors if the @p time is in range [0, 1].
	///        Linear extrapolation between the two colors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated color.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr RGBA<T> Lerp(const RGBA<T>& from, const RGBA<T>& to, T time) noexcept;

	/// @brief Checks if the two color are almost equal with the @p tolerance value.
	/// @tparam T Component type.
	/// @param left Left color.
	/// @param right Right color.
	/// @param tolerance Tolerance. Must be positive.
	/// @return @a True if the colors are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const RGBA<T>& left, const RGBA<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Sums the @p left color and the @p right color.
	/// @tparam T Component type.
	/// @param left Augend.
	/// @param right Addend.
	/// @return Sum.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator +(const RGBA<T>& left, const RGBA<T>& right) noexcept;

	/// @brief Subtracts the @p right color from the @p left color.
	/// @tparam T Component type.
	/// @param left Minuend.
	/// @param right Subtrahend.
	/// @return Difference.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator -(const RGBA<T>& left, const RGBA<T>& right) noexcept;

	/// @brief Multiplies the @p left color by the @p right color component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator *(const RGBA<T>& left, const RGBA<T>& right) noexcept;
	/// @brief Multiplies the @p color components by the @p multiplier.
	/// @tparam T Component type.
	/// @param color Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator *(const RGBA<T>& color, T multiplier) noexcept;
	/// @brief Multiplies the @p color components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param color Multiplicand.
	/// @return Product.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator *(T multiplier, const RGBA<T>& color) noexcept;

	/// @brief Divides the @p left color by the @p right color component-wise.
	/// @tparam T Component type.
	/// @param left Dividend.
	/// @param right Divisor.
	/// @return Quotient.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator /(const RGBA<T>& left, const RGBA<T>& right) noexcept;
	/// @brief Divides the @p color components by the @p divisor.
	/// @tparam T Component type.
	/// @param color Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator /(const RGBA<T>& color, T divisor) noexcept;

	/// @brief Puts @p color.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Stream.
	/// @param color Color.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const RGBA<T>& color);

	template<std::floating_point T>
	struct RGBA<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr auto Red = RGBA(T{1}, T{0}, T{0}, T{1}); ///< RGBA(1, 0, 0, 1).
		static constexpr auto Green = RGBA(T{0}, T{1}, T{0}, T{1}); ///< RGBA(0, 1, 0, 1).
		static constexpr auto Blue = RGBA(T{0}, T{0}, T{1}, T{1}); ///< RGBA(0, 0, 1, 1).
		static constexpr auto Black = RGBA(T{0}, T{0}, T{0}, T{1}); ///< RGBA(0, 0, 0, 1).
		static constexpr auto White = RGBA(T{1}, T{1}, T{1}, T{1}); ///< RGBA(1, 1, 1, 1).
		static constexpr auto Clear = RGBA(T{0}, T{0}, T{0}, T{0}); ///< RGBA(0, 0, 0, 0).
		static constexpr auto Gray = RGBA(T{0.5}, T{0.5}, T{0.5}, T{1}); ///< RGBA(0.5, 0.5, 0.5, 1).
		static constexpr auto Yellow = RGBA(T{1}, T{1}, T{0}, T{1}); ///< RGBA(1, 1, 0, 1).
		static constexpr auto Magenta = RGBA(T{1}, T{0}, T{1}, T{1}); ///< RGBA(1, 0, 1, 1).
		static constexpr auto Cyan = RGBA(T{0}, T{1}, T{1}, T{1}); ///< RGBA(0, 1, 1, 1).
	};
}

namespace PonyBase::Math
{
	template<std::floating_point T>
	constexpr RGBA<T>::RGBA(const T red, const T green, const T blue, const T alpha) noexcept :
		components{red, green, blue, alpha}
	{
	}

	template<std::floating_point T>
	constexpr RGBA<T>::RGBA(const std::span<const T, ComponentCount> span) noexcept
	{
		Set(span);
	}

	template<std::floating_point T>
	constexpr RGBA<T>::RGBA(const RGB<T>& rgb, const T alpha) noexcept :
		RGBA(rgb.R(), rgb.G(), rgb.B(), alpha)
	{
	}

	template<std::floating_point T>
	template<std::unsigned_integral U>
	constexpr RGBA<T>::RGBA(const RGBInt<U>& rgb, const T alpha) noexcept :
		RGBA(static_cast<RGB<T>>(rgb), alpha)
	{
	}

	template<std::floating_point T>
	template<std::unsigned_integral U>
	constexpr RGBA<T>::RGBA(const RGBAInt<U>& color) noexcept
	{
		constexpr T inverseMaxValue = T{1} / RGBAInt<U>::MaxValue;
		Set(color.R() * inverseMaxValue, color.G() * inverseMaxValue, color.B() * inverseMaxValue, color.A() * inverseMaxValue);
	}

	template<std::floating_point T>
	constexpr RGBA<T>::RGBA(const Vector4<T>& vector) noexcept :
		RGBA(vector.Span())
	{
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::R() noexcept
	{
		return components[0];
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::R() const noexcept
	{
		return components[0];
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::G() noexcept
	{
		return components[1];
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::G() const noexcept
	{
		return components[1];
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::B() noexcept
	{
		return components[2];
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::B() const noexcept
	{
		return components[2];
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::A() noexcept
	{
		return components[3];
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::A() const noexcept
	{
		return components[3];
	}

	template<std::floating_point T>
	constexpr std::span<T, 4> RGBA<T>::Span() noexcept
	{
		return components;
	}

	template<std::floating_point T>
	constexpr std::span<const T, 4> RGBA<T>::Span() const noexcept
	{
		return components;
	}

	template<std::floating_point T>
	constexpr T RGBA<T>::Grayscale() const noexcept
	{
		return static_cast<RGB<T>>(*this).Grayscale();
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::Min() noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::Min() const noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::Max() noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::Max() const noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::floating_point T>
	constexpr std::pair<T&, T&> RGBA<T>::MinMax() noexcept
	{
		auto [min, max] = std::ranges::minmax_element(components);

		return std::pair<T&, T&>(*min, *max);
	}

	template<std::floating_point T>
	constexpr std::pair<const T&, const T&> RGBA<T>::MinMax() const noexcept
	{
		auto [min, max] = std::ranges::minmax_element(components);

		return std::pair<const T&, const T&>(*min, *max);
	}

	template<std::floating_point T>
	RGBA<T> RGBA<T>::Gamma() const noexcept
	{
		const RGB<T> rgb = static_cast<RGB<T>>(*this);
		const RGB<T> gamma = rgb.Gamma();

		return RGBA(gamma, A());
	}

	template<std::floating_point T>
	RGBA<T> RGBA<T>::Linear() const noexcept
	{
		const RGB<T> rgb = static_cast<RGB<T>>(*this);
		const RGB<T> linear = rgb.Linear();

		return RGBA(linear, A());
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::IsBlack() const noexcept
	{
		return *this == Predefined::Black;
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::IsAlmostBlack(const T tolerance) const noexcept
	{
		return AreAlmostEqual(*this, Predefined::Black, tolerance);
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::IsWhite() const noexcept
	{
		return *this == Predefined::White;
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::IsAlmostWhite(const T tolerance) const noexcept
	{
		return AreAlmostEqual(*this, Predefined::White, tolerance);
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::IsTransparent() const noexcept
	{
		return A() == T{0};
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::IsAlmostTransparent(const T tolerance) const noexcept
	{
		return A() < tolerance;
	}

	template<std::floating_point T>
	bool RGBA<T>::IsFinite() const noexcept
	{
		return std::isfinite(R()) && std::isfinite(G()) && std::isfinite(B()) && std::isfinite(A());
	}

	template<std::floating_point T>
	constexpr void RGBA<T>::Set(const T red, const T green, const T blue, const T alpha) noexcept
	{
		R() = red;
		G() = green;
		B() = blue;
		A() = alpha;
	}

	template<std::floating_point T>
	constexpr void RGBA<T>::Set(const std::span<const T, ComponentCount> span) noexcept
	{
		std::ranges::copy(span, components.data());
	}

	template<std::floating_point T>
	std::string RGBA<T>::ToString() const
	{
		return std::format("(R: {}, G: {}, B: {}, A: {})", R(), G(), B(), A());
	}

	template<std::floating_point T>
	T Distance(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		return std::sqrt(DistanceSquared(left, right));
	}

	template<std::floating_point T>
	constexpr T DistanceSquared(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		const RGBA<T> colorVector = left - right;

		return colorVector.R() * colorVector.R() + colorVector.G() * colorVector.G() + colorVector.B() * colorVector.B() + colorVector.A() * colorVector.A();
	}

	template<std::floating_point T>
	constexpr RGBA<T> Min(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		RGBA<T> min;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			min[i] = std::min(left[i], right[i]);
		}

		return min;
	}

	template<std::floating_point T>
	constexpr RGBA<T> Max(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		RGBA<T> max;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			max[i] = std::max(left[i], right[i]);
		}

		return max;
	}

	template<std::floating_point T>
	constexpr RGBA<T> Clamp(const RGBA<T>& value, const RGBA<T>& min, const RGBA<T>& max) noexcept
	{
		RGBA<T> clamped;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			clamped[i] = std::clamp(value[i], min[i], max[i]);
		}

		return clamped;
	}

	template<std::floating_point T>
	constexpr RGBA<T> Lerp(const RGBA<T>& from, const RGBA<T>& to, const T time) noexcept
	{
		return from + (to - from) * time;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const RGBA<T>& left, const RGBA<T>& right, const T tolerance) noexcept
	{
		return DistanceSquared(left, right) < tolerance * tolerance;
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr RGBA<T>::operator RGBA<U>() const noexcept
	{
		RGBA<U> cast;
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			cast[i] = static_cast<U>((*this)[i]);
		}

		return cast;
	}

	template<std::floating_point T>
	constexpr RGBA<T>::operator RGB<T>() const noexcept
	{
		return RGB<T>(std::span<const T, RGB<T>::ComponentCount>(components.data(), RGB<T>::ComponentCount));
	}

	template<std::floating_point T>
	template<std::unsigned_integral U>
	constexpr RGBA<T>::operator RGBAInt<U>() const noexcept
	{
		RGBAInt<U> color;
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			color[i] = static_cast<U>((*this)[i] * RGBAInt<U>::MaxValue);
		}

		return color;
	}

	template<std::floating_point T>
	template<std::unsigned_integral U>
	constexpr RGBA<T>::operator RGBInt<U>() const noexcept
	{
		RGBInt<U> color;
		for (std::size_t i = 0; i < RGBInt<U>::ComponentCount; ++i)
		{
			color[i] = static_cast<U>((*this)[i] * RGBInt<U>::MaxValue);
		}

		return color;
	}

	template<std::floating_point T>
	constexpr RGBA<T>::operator Vector4<T>() const noexcept
	{
		return Vector4<T>(Span());
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr RGBA<T>& RGBA<T>::operator +=(const RGBA& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] += other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGBA<T>& RGBA<T>::operator -=(const RGBA& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] -= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGBA<T>& RGBA<T>::operator *=(const RGBA& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGBA<T>& RGBA<T>::operator *=(const T multiplier) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= multiplier;
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGBA<T>& RGBA<T>::operator /=(const RGBA& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] /= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGBA<T>& RGBA<T>::operator /=(const T divisor) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] /= divisor;
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::operator ==(const RGBA& other) const noexcept
	{
		return components == other.components;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator +(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		RGBA<T> sum;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			sum[i] = left[i] + right[i];
		}

		return sum;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator -(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		RGBA<T> difference;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			difference[i] = left[i] - right[i];
		}

		return difference;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator *(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		RGBA<T> product;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			product[i] = left[i] * right[i];
		}

		return product;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator *(const RGBA<T>& color, const T multiplier) noexcept
	{
		RGBA<T> product;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			product[i] = color[i] * multiplier;
		}

		return product;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator *(const T multiplier, const RGBA<T>& color) noexcept
	{
		return color * multiplier;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator /(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		RGBA<T> quotient;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			quotient[i] = left[i] / right[i];
		}

		return quotient;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator /(const RGBA<T>& color, const T divisor) noexcept
	{
		RGBA<T> quotient;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			quotient[i] = color[i] / divisor;
		}

		return quotient;
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const RGBA<T>& color)
	{
		return stream << color.ToString();
	}
}