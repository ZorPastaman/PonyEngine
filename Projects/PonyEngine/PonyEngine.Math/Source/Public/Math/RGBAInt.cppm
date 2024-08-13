/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:RGBAInt;

import <algorithm>;
import <array>;
import <concepts>;
import <cstddef>;
import <format>;
import <limits>;
import <ostream>;
import <span>;
import <string>;

import :RGBInt;
import :Vector4;

export namespace PonyEngine::Math
{
	/// @brief RGBA color implementation.
	/// @tparam T Component type.
	template<std::unsigned_integral T>
	class RGBAInt final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr T MaxValue = std::numeric_limits<T>::max(); ///< Component maximum value.
		static constexpr std::size_t ComponentCount = 4; ///< Component count. For any RGBAInt, it's always 4.

		struct Predefined; ///< Predefined colors.

		/// @brief Creates a color and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr RGBAInt() noexcept = default;
		/// @brief Creates a color and assigns its components from the arguments.
		/// @param red Red component.
		/// @param green Green component.
		/// @param blue Blue component.
		/// @param alpha Alpha component.
		[[nodiscard("Pure constructor")]]
		constexpr RGBAInt(T red, T green, T blue, T alpha) noexcept;
		/// @brief Creates a color and assign its components from the @p span.
		/// @param span Span. The order is r, g, b, a.
		[[nodiscard("Pure constructor")]]
		explicit constexpr RGBAInt(std::span<const T, ComponentCount> span) noexcept;
		/// @brief Converts the rgb color to an rgba color.
		/// @param rgb RGB color.
		/// @param alpha Alpha.
		[[nodiscard("Pure constructor")]]
		constexpr RGBAInt(const RGBInt<T>& rgb, T alpha) noexcept;
		/// @brief Converts the @p vector to a color component-wise.
		/// @param vector Vector to convert.
		[[nodiscard("Pure constructor")]]
		explicit constexpr RGBAInt(const Vector4<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr RGBAInt(const RGBAInt& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr RGBAInt(RGBAInt&& other) noexcept = default;

		constexpr ~RGBAInt() noexcept = default;

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

		/// @brief Checks if the color is black.
		/// @return @a True if it's black; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsBlack() const noexcept;
		/// @brief Checks if the color is white.
		/// @return @a True if it's white; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsWhite() const noexcept;
		/// @brief Checks if the color is fully transparent.
		/// @return @a True if it's fully transparent; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsTransparent() const noexcept;

		/// @brief Sets arguments to components.
		/// @param red Red.
		/// @param green Green.
		/// @param blue Blue.
		/// @param alpha Alpha.
		constexpr void Set(T red, T green, T blue, T alpha) noexcept;
		/// @brief Sets components from the array.
		/// @param span Span. The order is r, g, b, a.
		constexpr void Set(std::span<const T, ComponentCount> span) noexcept;

		/// @brief Creates a string representing a state of the color.
		/// @return String representing a state of the color.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the rgba color to an rgb color skipping the alpha.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator RGBInt<T>() const noexcept;

		/// @brief Converts the color to a vector.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator Vector4<T>() const noexcept;

		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component. 0 -> red, 1 -> green, 2 -> blue, 3 -> alpha.
		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, 3].
		/// @return Component. 0 -> red, 1 -> green, 2 -> blue, 3 -> alpha.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		RGBAInt& operator =(const RGBAInt& other) noexcept = default;
		RGBAInt& operator =(RGBAInt&& other) noexcept = default;

		/// @brief Checks if the two colors are equal.
		/// @param other Color to compare with.
		/// @return @a True if they're equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const RGBAInt& other) const noexcept;

	private:
		std::array<T, ComponentCount> components; ///< Component array. The order is r, g, b, a.
	};

	/// @brief Puts @p RGBAInt.ToString() into the @p stream.
	///	@tparam T Component type.
	/// @param stream Target stream.
	/// @param color Input source.
	/// @return @p stream.
	template<std::unsigned_integral T>
	std::ostream& operator <<(std::ostream& stream, const RGBAInt<T>& color);

	template<std::unsigned_integral T>
	struct RGBAInt<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr auto Red = RGBAInt(MaxValue, T{0}, T{0}, MaxValue); ///< RGBInt(MaxValue, 0, 0, MaxValue).
		static constexpr auto Green = RGBAInt(T{0}, MaxValue, T{0}, MaxValue); ///< RGBInt(0, MaxValue, 0, MaxValue).
		static constexpr auto Blue = RGBAInt(T{0}, T{0}, MaxValue, MaxValue); ///< RGBInt(0, 0, MaxValue, MaxValue).
		static constexpr auto Black = RGBAInt(T{0}, T{0}, T{0}, MaxValue); ///< RGBInt(0, 0, 0, MaxValue).
		static constexpr auto White = RGBAInt(MaxValue, MaxValue, MaxValue, MaxValue); ///< RGBInt(MaxValue, MaxValue, MaxValue, MaxValue).
		static constexpr auto Clear = RGBAInt(T{0}, T{0}, T{0}, T{0}); ///< RGBInt(0, 0, 0, 0).
		static constexpr auto Yellow = RGBAInt(MaxValue, MaxValue, T{0}, MaxValue); ///< RGBInt(MaxValue, MaxValue, 0, MaxValue).
		static constexpr auto Magenta = RGBAInt(MaxValue, T{0}, MaxValue, MaxValue); ///< RGBInt(MaxValue, 0, MaxValue, MaxValue).
		static constexpr auto Cyan = RGBAInt(T{0}, MaxValue, MaxValue, MaxValue); ///< RGBInt(0, MaxValue, MaxValue, MaxValue).
	};
}

namespace PonyEngine::Math
{
	template<std::unsigned_integral T>
	constexpr RGBAInt<T>::RGBAInt(const T red, const T green, const T blue, const T alpha) noexcept :
		components{red, green, blue, alpha}
	{
	}

	template<std::unsigned_integral T>
	constexpr RGBAInt<T>::RGBAInt(const std::span<const T, ComponentCount> span) noexcept
	{
		Set(span);
	}

	template<std::unsigned_integral T>
	constexpr RGBAInt<T>::RGBAInt(const RGBInt<T>& rgb, const T alpha) noexcept :
		RGBAInt(rgb.R(), rgb.G(), rgb.B(), alpha)
	{
	}

	template<std::unsigned_integral T>
	constexpr RGBAInt<T>::RGBAInt(const Vector4<T>& vector) noexcept :
		RGBAInt(vector.Span())
	{
	}

	template<std::unsigned_integral T>
	constexpr T& RGBAInt<T>::R() noexcept
	{
		return components[0];
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBAInt<T>::R() const noexcept
	{
		return components[0];
	}

	template<std::unsigned_integral T>
	constexpr T& RGBAInt<T>::G() noexcept
	{
		return components[1];
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBAInt<T>::G() const noexcept
	{
		return components[1];
	}

	template<std::unsigned_integral T>
	constexpr T& RGBAInt<T>::B() noexcept
	{
		return components[2];
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBAInt<T>::B() const noexcept
	{
		return components[2];
	}

	template<std::unsigned_integral T>
	constexpr T& RGBAInt<T>::A() noexcept
	{
		return components[3];
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBAInt<T>::A() const noexcept
	{
		return components[3];
	}

	template<std::unsigned_integral T>
	constexpr std::span<T, 4> RGBAInt<T>::Span() noexcept
	{
		return components;
	}

	template<std::unsigned_integral T>
	constexpr std::span<const T, 4> RGBAInt<T>::Span() const noexcept
	{
		return components;
	}

	template<std::unsigned_integral T>
	constexpr T& RGBAInt<T>::Min() noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBAInt<T>::Min() const noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::unsigned_integral T>
	constexpr T& RGBAInt<T>::Max() noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBAInt<T>::Max() const noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::unsigned_integral T>
	constexpr bool RGBAInt<T>::IsBlack() const noexcept
	{
		return *this == Predefined::Black;
	}

	template<std::unsigned_integral T>
	constexpr bool RGBAInt<T>::IsWhite() const noexcept
	{
		return *this == Predefined::White;
	}

	template<std::unsigned_integral T>
	constexpr bool RGBAInt<T>::IsTransparent() const noexcept
	{
		return A() == T{0};
	}

	template<std::unsigned_integral T>
	constexpr void RGBAInt<T>::Set(const T red, const T green, const T blue, const T alpha) noexcept
	{
		R() = red;
		G() = green;
		B() = blue;
		A() = alpha;
	}

	template<std::unsigned_integral T>
	constexpr void RGBAInt<T>::Set(const std::span<const T, ComponentCount> span) noexcept
	{
		std::ranges::copy(span, components.data());
	}

	template<std::unsigned_integral T>
	std::string RGBAInt<T>::ToString() const
	{
		return std::format("(R: {}, G: {}, B: {}, A: {})", R(), G(), B(), A());
	}

	template<std::unsigned_integral T>
	constexpr RGBAInt<T>::operator RGBInt<T>() const noexcept
	{
		return RGBInt<T>(std::span<const T, RGBInt<T>::ComponentCount>(components.data(), RGBInt<T>::ComponentCount));
	}

	template<std::unsigned_integral T>
	constexpr RGBAInt<T>::operator Vector4<T>() const noexcept
	{
		return Vector4<T>(Span());
	}

	template<std::unsigned_integral T>
	constexpr T& RGBAInt<T>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBAInt<T>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<std::unsigned_integral T>
	constexpr bool RGBAInt<T>::operator ==(const RGBAInt& other) const noexcept
	{
		return components == other.components;
	}

	template<std::unsigned_integral T>
	std::ostream& operator <<(std::ostream& stream, const RGBAInt<T>& color)
	{
		return stream << color.ToString();
	}
}
