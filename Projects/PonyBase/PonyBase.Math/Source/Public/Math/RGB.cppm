/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Math:RGB;

import <algorithm>;
import <array>;
import <concepts>;
import <cstddef>;
import <format>;
import <ostream>;
import <span>;
import <string>;

import :RGBInt;
import :Vector3;

export namespace PonyBase::Math
{
	/// @brief RGB color implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class RGB final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr T GammaValue = T{2.2}; ///< Gamma value.
		static constexpr std::size_t ComponentCount = 3; ///< Component count. For any RGB, it's always 3.

		struct Predefined; ///< Predefined colors.

		/// @brief Creates a color and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr RGB() noexcept = default;
		/// @brief Creates a color and assigns its components from the arguments.
		/// @param red Red component.
		/// @param green Green component.
		/// @param blue Blue component.
		[[nodiscard("Pure constructor")]]
		constexpr RGB(T red, T green, T blue) noexcept;
		/// @brief Creates a color and assigns its components from the @p span.
		/// @param span Components. The order is r, g, b.
		[[nodiscard("Pure constructor")]]
		explicit constexpr RGB(std::span<const T, ComponentCount> span) noexcept;
		/// @brief Converts the integral rgb color to an rgb color.
		/// @param color RGB int color.
		template<std::unsigned_integral U> [[nodiscard("Pure constructor")]]
		explicit constexpr RGB(const RGBInt<U>& color) noexcept;
		/// @brief Converts the @p vector to a color component-wise. x -> r, y -> g, z -> b.
		/// @param vector Vector to convert.
		[[nodiscard("Pure constructor")]]
		explicit constexpr RGB(const Vector3<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr RGB(const RGB& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr RGB(RGB&& other) noexcept = default;

		constexpr ~RGB() noexcept = default;

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
		/// @brief Gets the color span.
		/// @return Color span. The order is r, g, b.
		[[nodiscard("Pure function")]]
		constexpr std::span<T, 3> Span() noexcept;
		/// @brief Gets the color span.
		/// @return Color span. The order is r, g, b.
		[[nodiscard("Pure function")]]
		constexpr std::span<const T, 3> Span() const noexcept;

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
		RGB Gamma() const noexcept;
		/// @brief Converts the gamma-corrected color to a linear color.
		///	@note All the color components must be in range [0, 1].
		/// @return Linear color.
		[[nodiscard("Pure function")]]
		RGB Linear() const noexcept;

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

		/// @brief Checks if all the components are finite.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Sets arguments to the components.
		/// @param red Red.
		/// @param green Green.
		/// @param blue Blue.
		constexpr void Set(T red, T green, T blue) noexcept;
		/// @brief Sets the @p span to the components.
		/// @param span Span. The order is r, g, b.
		constexpr void Set(std::span<const T, 3> span) noexcept;

		/// @brief Creates a string representing a state of the color.
		/// @return String representing a state of the color.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts all the components to @p U and returns it as a new color.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator RGB<U>() const noexcept;
		/// @brief Converts to an integral color.
		/// @tparam U Target type.
		template<std::unsigned_integral U> [[nodiscard("Pure operator")]]
		explicit constexpr operator RGBInt<U>() const noexcept;

		/// @brief Converts the color to a vector.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator Vector3<T>() const noexcept;

		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, 2].
		/// @return Component. 0 -> r, 1 -> g, 2 -> b.
		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, 2].
		/// @return Component. 0 -> r, 1 -> g, 2 -> b.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr RGB& operator =(const RGB& other) noexcept = default;
		constexpr RGB& operator =(RGB&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Color to add.
		/// @return @a This.
		constexpr RGB& operator +=(const RGB& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Color to subtract.
		/// @return @a This.
		constexpr RGB& operator -=(const RGB& other) noexcept;
		/// @brief Multiplies @a this by the @p other component-wise.
		/// @param other Color multiplier.
		/// @return @a This.
		constexpr RGB& operator *=(const RGB& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Color multiplier.
		/// @return @a This.
		constexpr RGB& operator *=(T multiplier) noexcept;
		/// @brief Divides @a this by the @p other component-wise.
		/// @param other Color divisor.
		/// @return @a This.
		constexpr RGB& operator /=(const RGB& other) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Color divisor.
		/// @return @a This.
		constexpr RGB& operator /=(T divisor) noexcept;

		/// @brief Check if all the components in the two colors are equal.
		/// @param other Color to compare with.
		/// @return @a True if they're equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const RGB& other) const noexcept;

	private:
		std::array<T, ComponentCount> components; ///< Component array in order red, green, blue, alpha.
	};

	/// @brief Computes a distance between two colors.
	/// @tparam T Component type.
	/// @param left Left color.
	/// @param right Right color.
	/// @return Distance.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T Distance(const RGB<T>& left, const RGB<T>& right) noexcept;
	/// @brief Computes a squared distance between two colors.
	/// @remark This function is much faster than @p Distance 'cause it doesn't compute a square root.
	/// @tparam T Component type.
	/// @param left Left color.
	/// @param right Right color.
	/// @return Distance
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T DistanceSquared(const RGB<T>& left, const RGB<T>& right) noexcept;

	/// @brief Creates a color consisting of minimal elements of the two colors.
	/// @tparam T Component type.
	/// @param left Left color.
	/// @param right Right color.
	/// @return Color of minimal elements.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr RGB<T> Min(const RGB<T>& left, const RGB<T>& right) noexcept;
	/// @brief Creates a color consisting of maximal elements of the two colors.
	/// @tparam T Component type.
	/// @param left Left color.
	/// @param right Right color.
	/// @return Color of maximal elements.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr RGB<T> Max(const RGB<T>& left, const RGB<T>& right) noexcept;
	/// @brief Clamps the @p value between the @p min and @p max component-wise.
	/// @tparam T Component type.
	/// @param value Value.
	/// @param min Minimum.
	/// @param max Maximum.
	/// @return Clamped color.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr RGB<T> Clamp(const RGB<T>& value, const RGB<T>& min, const RGB<T>& max) noexcept;
	/// @brief Linear interpolation between the two colors if the @p time is in range [0, 1].
	///        Linear extrapolation between the two colors if the @p time is out of range [0, 1].
	/// @tparam T Component type.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated color.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr RGB<T> Lerp(const RGB<T>& from, const RGB<T>& to, T time) noexcept;

	/// @brief Checks if the two color are almost equal with the @p tolerance value.
	/// @tparam T Component type.
	/// @param left Left color.
	/// @param right Right color.
	/// @param tolerance Tolerance. Must be positive.
	/// @return @a True if the colors are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const RGB<T>& left, const RGB<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Sums the @p left color and the @p right color.
	/// @tparam T Component type.
	/// @param left Augend.
	/// @param right Addend.
	/// @return Sum.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator +(const RGB<T>& left, const RGB<T>& right) noexcept;

	/// @brief Subtracts the @p right color from the @p left color.
	/// @tparam T Component type.
	/// @param left Minuend.
	/// @param right Subtrahend.
	/// @return Difference.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator -(const RGB<T>& left, const RGB<T>& right) noexcept;

	/// @brief Multiplies the @p left color by the @p right color component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator *(const RGB<T>& left, const RGB<T>& right) noexcept;
	/// @brief Multiplies the @p color components by the @p multiplier.
	/// @tparam T Component type.
	/// @param color Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator *(const RGB<T>& color, T multiplier) noexcept;
	/// @brief Multiplies the @p color components by the @p multiplier.
	/// @tparam T Component type.
	/// @param multiplier Multiplier.
	/// @param color Multiplicand.
	/// @return Product.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator *(T multiplier, const RGB<T>& color) noexcept;

	/// @brief Divides the @p left color by the @p right color component-wise.
	/// @tparam T Component type.
	/// @param left Dividend.
	/// @param right Divisor.
	/// @return Quotient.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator /(const RGB<T>& left, const RGB<T>& right) noexcept;
	/// @brief Divides the @p color components by the @p divisor.
	/// @tparam T Component type.
	/// @param color Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator /(const RGB<T>& color, T divisor) noexcept;

	/// @brief Puts @p color.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Stream.
	/// @param color Color.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const RGB<T>& color);

	template<std::floating_point T>
	struct RGB<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr auto Red = RGB(T{1}, T{0}, T{0}); ///< RGB(1, 0, 0).
		static constexpr auto Green = RGB(T{0}, T{1}, T{0}); ///< RGB(0, 1, 0).
		static constexpr auto Blue = RGB(T{0}, T{0}, T{1}); ///< RGB(0, 0, 1).
		static constexpr auto Black = RGB(T{0}, T{0}, T{0}); ///< RGB(0, 0, 0).
		static constexpr auto White = RGB(T{1}, T{1}, T{1}); ///< RGB(1, 1, 1).
		static constexpr auto Gray = RGB(T{0.5}, T{0.5}, T{0.5}); ///< RGB(0.5, 0.5, 0.5).
		static constexpr auto Yellow = RGB(T{1}, T{1}, T{0}); ///< RGB(1, 1, 0).
		static constexpr auto Magenta = RGB(T{1}, T{0}, T{1}); ///< RGB(1, 0, 1).
		static constexpr auto Cyan = RGB(T{0}, T{1}, T{1}); ///< RGB(0, 1, 1).
	};
}

namespace PonyBase::Math
{
	template<std::floating_point T>
	constexpr RGB<T>::RGB(const T red, const T green, const T blue) noexcept :
		components{red, green, blue}
	{
	}

	template<std::floating_point T>
	constexpr RGB<T>::RGB(const std::span<const T, ComponentCount> span) noexcept
	{
		Set(span);
	}

	template<std::floating_point T>
	template<std::unsigned_integral U>
	constexpr RGB<T>::RGB(const RGBInt<U>& color) noexcept
	{
		constexpr T inverseMaxValue = T{1} / RGBInt<U>::MaxValue;
		Set(color.R() * inverseMaxValue, color.G() * inverseMaxValue, color.B() * inverseMaxValue);
	}

	template<std::floating_point T>
	constexpr RGB<T>::RGB(const Vector3<T>& vector) noexcept :
		RGB(vector.Span())
	{
	}

	template<std::floating_point T>
	constexpr T& RGB<T>::R() noexcept
	{
		return components[0];
	}

	template<std::floating_point T>
	constexpr const T& RGB<T>::R() const noexcept
	{
		return components[0];
	}

	template<std::floating_point T>
	constexpr T& RGB<T>::G() noexcept
	{
		return components[1];
	}

	template<std::floating_point T>
	constexpr const T& RGB<T>::G() const noexcept
	{
		return components[1];
	}

	template<std::floating_point T>
	constexpr T& RGB<T>::B() noexcept
	{
		return components[2];
	}

	template<std::floating_point T>
	constexpr const T& RGB<T>::B() const noexcept
	{
		return components[2];
	}

	template<std::floating_point T>
	constexpr std::span<T, 3> RGB<T>::Span() noexcept
	{
		return components;
	}

	template<std::floating_point T>
	constexpr std::span<const T, 3> RGB<T>::Span() const noexcept
	{
		return components;
	}

	template<std::floating_point T>
	constexpr T RGB<T>::Grayscale() const noexcept
	{
		return R() * T{0.2126} + G() * T{0.7152} + B() * T{0.0722};
	}

	template<std::floating_point T>
	constexpr T& RGB<T>::Min() noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::floating_point T>
	constexpr const T& RGB<T>::Min() const noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::floating_point T>
	constexpr T& RGB<T>::Max() noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::floating_point T>
	constexpr const T& RGB<T>::Max() const noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::floating_point T>
	constexpr std::pair<T&, T&> RGB<T>::MinMax() noexcept
	{
		auto [min, max] = std::ranges::minmax_element(components);

		return std::pair<T&, T&>(*min, *max);
	}

	template<std::floating_point T>
	constexpr std::pair<const T&, const T&> RGB<T>::MinMax() const noexcept
	{
		auto [min, max] = std::ranges::minmax_element(components);

		return std::pair<const T&, const T&>(*min, *max);
	}

	template<std::floating_point T>
	RGB<T> RGB<T>::Gamma() const noexcept
	{
		constexpr T exp = T{1} / GammaValue;

		RGB gamma;
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			const T component = (*this)[i];
			gamma[i] = component > T{0.0031308}
				? std::pow(component, exp) * T{1.055} - T{0.055}
				: component * T{12.92};
		}

		return Clamp(gamma, Predefined::Black, Predefined::White);
	}

	template<std::floating_point T>
	RGB<T> RGB<T>::Linear() const noexcept
	{
		RGB linear;
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			const T component = (*this)[i];
			linear[i] = component > T{0.04045}
				? std::pow((component + T{0.055}) / T{1.055}, GammaValue)
				: component / T{12.92};
		}

		return Clamp(linear, Predefined::Black, Predefined::White);
	}

	template<std::floating_point T>
	constexpr bool RGB<T>::IsBlack() const noexcept
	{
		return *this == Predefined::Black;
	}

	template<std::floating_point T>
	constexpr bool RGB<T>::IsAlmostBlack(const T tolerance) const noexcept
	{
		return AreAlmostEqual(*this, Predefined::Black, tolerance);
	}

	template<std::floating_point T>
	constexpr bool RGB<T>::IsWhite() const noexcept
	{
		return *this == Predefined::White;
	}

	template<std::floating_point T>
	constexpr bool RGB<T>::IsAlmostWhite(const T tolerance) const noexcept
	{
		return AreAlmostEqual(*this, Predefined::White, tolerance);
	}

	template<std::floating_point T>
	bool RGB<T>::IsFinite() const noexcept
	{
		return std::isfinite(R()) && std::isfinite(G()) && std::isfinite(B());
	}

	template<std::floating_point T>
	constexpr void RGB<T>::Set(const T red, const T green, const T blue) noexcept
	{
		R() = red;
		G() = green;
		B() = blue;
	}

	template<std::floating_point T>
	constexpr void RGB<T>::Set(const std::span<const T, 3> span) noexcept
	{
		std::ranges::copy(span, components.data());
	}

	template<std::floating_point T>
	std::string RGB<T>::ToString() const
	{
		return std::format("(R: {}, G: {}, B: {})", R(), G(), B());
	}

	template<std::floating_point T>
	constexpr T Distance(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		return std::sqrt(DistanceSquared(left, right));
	}

	template<std::floating_point T>
	constexpr T DistanceSquared(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		const RGB<T> difference = left - right;

		return difference.R() * difference.R() + difference.G() * difference.G() + difference.B() * difference.B();
	}

	template<std::floating_point T>
	constexpr RGB<T> Min(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		RGB<T> min;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			min[i] = std::min(left[i], right[i]);
		}

		return min;
	}

	template<std::floating_point T>
	constexpr RGB<T> Max(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		RGB<T> max;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			max[i] = std::max(left[i], right[i]);
		}

		return max;
	}

	template<std::floating_point T>
	constexpr RGB<T> Clamp(const RGB<T>& value, const RGB<T>& min, const RGB<T>& max) noexcept
	{
		RGB<T> clamped;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			clamped[i] = std::clamp(value[i], min[i], max[i]);
		}

		return clamped;
	}

	template<std::floating_point T>
	constexpr RGB<T> Lerp(const RGB<T>& from, const RGB<T>& to, const T time) noexcept
	{
		return from + (to - from) * time;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const RGB<T>& left, const RGB<T>& right, const T tolerance) noexcept
	{
		return DistanceSquared(left, right) < tolerance * tolerance;
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr RGB<T>::operator RGB<U>() const noexcept
	{
		RGB<U> cast;
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			cast[i] = static_cast<U>((*this)[i]);
		}

		return cast;
	}

	template<std::floating_point T>
	template<std::unsigned_integral U>
	constexpr RGB<T>::operator RGBInt<U>() const noexcept
	{
		RGBInt<U> color;
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			color[i] = static_cast<U>((*this)[i] * RGBInt<U>::MaxValue);
		}

		return color;
	}

	template<std::floating_point T>
	constexpr RGB<T>::operator Vector3<T>() const noexcept
	{
		return Vector3<T>(Span());
	}

	template<std::floating_point T>
	constexpr T& RGB<T>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr const T& RGB<T>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr RGB<T>& RGB<T>::operator +=(const RGB& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] += other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGB<T>& RGB<T>::operator -=(const RGB& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] -= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGB<T>& RGB<T>::operator *=(const RGB& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGB<T>& RGB<T>::operator *=(const T multiplier) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= multiplier;
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGB<T>& RGB<T>::operator /=(const RGB& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] /= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGB<T>& RGB<T>::operator /=(const T divisor) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] /= divisor;
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr bool RGB<T>::operator ==(const RGB& other) const noexcept
	{
		return components == other.components;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator +(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		RGB<T> sum;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			sum[i] = left[i] + right[i];
		}

		return sum;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator -(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		RGB<T> difference;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			difference[i] = left[i] - right[i];
		}

		return difference;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator *(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		RGB<T> product;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			product[i] = left[i] * right[i];
		}

		return product;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator *(const RGB<T>& color, const T multiplier) noexcept
	{
		RGB<T> product;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			product[i] = color[i] * multiplier;
		}

		return product;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator *(const T multiplier, const RGB<T>& color) noexcept
	{
		return color * multiplier;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator /(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		RGB<T> quotient;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			quotient[i] = left[i] / right[i];
		}

		return quotient;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator /(const RGB<T>& color, const T divisor) noexcept
	{
		RGB<T> quotient;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			quotient[i] = color[i] / divisor;
		}

		return quotient;
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const RGB<T>& color)
	{
		return stream << color.ToString();
	}
}
