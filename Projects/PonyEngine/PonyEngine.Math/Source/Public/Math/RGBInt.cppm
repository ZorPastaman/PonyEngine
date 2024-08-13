/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:RGBInt;

import <algorithm>;
import <array>;
import <concepts>;
import <cstddef>;
import <format>;
import <limits>;
import <ostream>;
import <span>;
import <string>;

import :Vector3;

export namespace PonyEngine::Math
{
	/// @brief RGB color implementation.
	///	@tparam T Component type.
	template<std::unsigned_integral T>
	class RGBInt final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr T MaxValue = std::numeric_limits<T>::max(); ///< Component maximum value.
		static constexpr std::size_t ComponentCount = 3; ///< Component count. For any @p RGBInt, it's always 3.

		struct Predefined; ///< Predefined colors.

		/// @brief Creates a color and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr RGBInt() noexcept = default;
		/// @brief Creates a color and assigns its components from the arguments.
		/// @param red Red component.
		/// @param green Green component.
		/// @param blue Blue component.
		[[nodiscard("Pure constructor")]]
		constexpr RGBInt(T red, T green, T blue) noexcept;
		/// @brief Creates a color and assign its components from the @p span.
		/// @param span Span. The order is r, g, b.
		[[nodiscard("Pure constructor")]]
		explicit constexpr RGBInt(std::span<const T, ComponentCount> span) noexcept;
		/// @brief Converts the vector to a color component-wise.
		/// @param vector Vector to convert.
		[[nodiscard("Pure constructor")]]
		explicit constexpr RGBInt(const Vector3<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr RGBInt(const RGBInt& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr RGBInt(RGBInt&& other) noexcept = default;

		constexpr ~RGBInt() noexcept = default;

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
		/// @brief Gets the color span. The order is r, g, b.
		/// @return Color span.
		[[nodiscard("Pure function")]]
		constexpr std::span<T, 3> Span() noexcept;
		/// @brief Gets the color span. The order is r, g, b.
		/// @return Color span.
		[[nodiscard("Pure function")]]
		constexpr std::span<const T, 3> Span() const noexcept;

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

		/// @brief Sets arguments to components.
		/// @param red Red.
		/// @param green Green.
		/// @param blue Blue.
		constexpr void Set(T red, T green, T blue) noexcept;
		/// @brief Sets components from the array.
		/// @param span Span. The order is r, g, b.
		constexpr void Set(std::span<const T, 3> span) noexcept;

		/// @brief Creates a string representing a state of the color.
		/// @return String representing a state of the color.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the color to a vector.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator Vector3<T>() const noexcept;

		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, 2].
		/// @return Component. 0 -> red, 1 -> green, 2 -> blue.
		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in range [0, 2].
		/// @return Component. 0 -> red, 1 -> green, 2 -> blue.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr RGBInt& operator =(const RGBInt& other) noexcept = default;
		constexpr RGBInt& operator =(RGBInt&& other) noexcept = default;

		/// @brief Checks if the two colors are equal.
		/// @param other Color to compare with.
		/// @return @a True if they're equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const RGBInt& other) const noexcept;

	private:
		std::array<T, ComponentCount> components; ///< Component array. The order is r, g, b.
	};

	/// @brief Puts @p RGBInt.ToString() into the @p stream.
	///	@tparam T Component type.
	/// @param stream Target stream.
	/// @param color Input source.
	/// @return @p stream.
	template<std::unsigned_integral T>
	std::ostream& operator <<(std::ostream& stream, const RGBInt<T>& color);

	template<std::unsigned_integral T>
	struct RGBInt<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr auto Red = RGBInt(MaxValue, T{0}, T{0}); ///< RGBInt(MaxValue, 0, 0).
		static constexpr auto Green = RGBInt(T{0}, MaxValue, T{0}); ///< RGBInt(0, MaxValue, 0).
		static constexpr auto Blue = RGBInt(T{0}, T{0}, MaxValue); ///< RGBInt(0, 0, MaxValue).
		static constexpr auto Black = RGBInt(T{0}, T{0}, T{0}); ///< RGBInt(0, 0, 0).
		static constexpr auto White = RGBInt(MaxValue, MaxValue, MaxValue); ///< RGBInt(MaxValue, MaxValue, MaxValue).
		static constexpr auto Yellow = RGBInt(MaxValue, MaxValue, T{0}); ///< RGBInt(MaxValue, MaxValue, 0).
		static constexpr auto Magenta = RGBInt(MaxValue, T{0}, MaxValue); ///< RGBInt(MaxValue, 0, MaxValue).
		static constexpr auto Cyan = RGBInt(T{0}, MaxValue, MaxValue); ///< RGBInt(0, MaxValue, MaxValue).
	};
}

namespace PonyEngine::Math
{
	template<std::unsigned_integral T>
	constexpr RGBInt<T>::RGBInt(const T red, const T green, const T blue) noexcept :
		components{red, green, blue}
	{
	}

	template<std::unsigned_integral T>
	constexpr RGBInt<T>::RGBInt(const std::span<const T, ComponentCount> span) noexcept
	{
		Set(span);
	}

	template<std::unsigned_integral T>
	constexpr RGBInt<T>::RGBInt(const Vector3<T>& vector) noexcept :
		RGBInt(vector.Span())
	{
	}

	template<std::unsigned_integral T>
	constexpr T& RGBInt<T>::R() noexcept
	{
		return components[0];
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBInt<T>::R() const noexcept
	{
		return components[0];
	}

	template<std::unsigned_integral T>
	constexpr T& RGBInt<T>::G() noexcept
	{
		return components[1];
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBInt<T>::G() const noexcept
	{
		return components[1];
	}

	template<std::unsigned_integral T>
	constexpr T& RGBInt<T>::B() noexcept
	{
		return components[2];
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBInt<T>::B() const noexcept
	{
		return components[2];
	}

	template<std::unsigned_integral T>
	constexpr std::span<T, 3> RGBInt<T>::Span() noexcept
	{
		return components;
	}

	template<std::unsigned_integral T>
	constexpr std::span<const T, 3> RGBInt<T>::Span() const noexcept
	{
		return components;
	}

	template<std::unsigned_integral T>
	constexpr T& RGBInt<T>::Min() noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBInt<T>::Min() const noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::unsigned_integral T>
	constexpr T& RGBInt<T>::Max() noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBInt<T>::Max() const noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::unsigned_integral T>
	constexpr bool RGBInt<T>::IsBlack() const noexcept
	{
		return *this == Predefined::Black;
	}

	template<std::unsigned_integral T>
	constexpr bool RGBInt<T>::IsWhite() const noexcept
	{
		return *this == Predefined::White;
	}

	template<std::unsigned_integral T>
	constexpr void RGBInt<T>::Set(const T red, const T green, const T blue) noexcept
	{
		R() = red;
		G() = green;
		B() = blue;
	}

	template<std::unsigned_integral T>
	constexpr void RGBInt<T>::Set(const std::span<const T, 3> span) noexcept
	{
		std::ranges::copy(span, components.data());
	}

	template<std::unsigned_integral T>
	std::string RGBInt<T>::ToString() const
	{
		return std::format("(R: {}, G: {}, B: {})", R(), G(), B());
	}

	template<std::unsigned_integral T>
	constexpr RGBInt<T>::operator Vector3<T>() const noexcept
	{
		return Vector3<T>(Span());
	}

	template<std::unsigned_integral T>
	constexpr T& RGBInt<T>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<std::unsigned_integral T>
	constexpr const T& RGBInt<T>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<std::unsigned_integral T>
	constexpr bool RGBInt<T>::operator ==(const RGBInt& other) const noexcept
	{
		return components == other.components;
	}

	template<std::unsigned_integral T>
	std::ostream& operator <<(std::ostream& stream, const RGBInt<T>& color)
	{
		return stream << color.ToString();
	}
}
