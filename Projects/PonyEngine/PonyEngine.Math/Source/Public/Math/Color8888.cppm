/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Color8888;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <format>;
import <limits>;
import <ostream>;
import <string>;

import :Color888;
import :Vector4;

export namespace PonyEngine::Math
{
	class Color8888 final
	{
	public:
		using ValueType = std::uint8_t; ///< Component type.

		static constexpr std::uint8_t MaxValue = std::numeric_limits<std::uint8_t>::max();
		static constexpr std::size_t ComponentCount = 4; ///< Component count. For any Color8888, it's always 4.

		//struct Predefined; ///< Predefined colors.

		[[nodiscard("Pure constructor")]]
		constexpr Color8888() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Color8888(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Color8888(const std::uint8_t* components) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Color8888(const Color888& color, std::uint8_t alpha) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Color8888(const Vector4<std::uint8_t>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Color8888(const Color8888& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Color8888(Color8888&& other) noexcept = default;

		constexpr ~Color8888() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr std::uint8_t& R() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t& R() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr std::uint8_t& G() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t& G() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr std::uint8_t& B() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t& B() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr std::uint8_t& A() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t& A() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr std::uint8_t* Data() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t* Data() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr std::uint8_t& Min() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t& Min() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr std::uint8_t& Max() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t& Max() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr bool IsBlack() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr bool IsWhite() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr bool IsTransparent() const noexcept;

		constexpr void Set(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha) noexcept;
		constexpr void Set(const std::uint8_t* componentsToSet) noexcept;

		[[nodiscard("Pure function")]]
		constexpr std::array<std::uint8_t, 4> ToArray() const noexcept;
		constexpr void ToArray(std::uint8_t (&array)[ComponentCount]) const noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		[[nodiscard("Pure operator")]]
		explicit constexpr operator Color888() const noexcept;

		[[nodiscard("Pure operator")]]
		explicit constexpr operator Vector4<std::uint8_t>() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr std::uint8_t& operator [](std::size_t index) noexcept;
		[[nodiscard("Pure operator")]]
		constexpr const std::uint8_t& operator [](std::size_t index) const noexcept;

		Color8888& operator =(const Color8888& other) noexcept = default;
		Color8888& operator =(Color8888&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Color8888& other) const noexcept;

	private:
		std::array<std::uint8_t, ComponentCount> components;
	};

	std::ostream& operator <<(std::ostream& stream, const Color8888& color);

	//struct Color8888::Predefined final
	//{
	//	Predefined() = delete;

	//	static constexpr auto Red = Color8888(MaxValue, std::uint8_t{0}, std::uint8_t{0}, MaxValue);
	//	static constexpr auto Green = Color8888(std::uint8_t{0}, MaxValue, std::uint8_t{0}, MaxValue);
	//	static constexpr auto Blue = Color8888(std::uint8_t{0}, std::uint8_t{0}, MaxValue, MaxValue);
	//	static constexpr auto Black = Color8888(std::uint8_t{0}, std::uint8_t{0}, std::uint8_t{0}, MaxValue);
	//	static constexpr auto White = Color8888(MaxValue, MaxValue, MaxValue, MaxValue);
	//	static constexpr auto Clear = Color8888(std::uint8_t{0}, std::uint8_t{0}, std::uint8_t{0}, std::uint8_t{0});
	//	static constexpr auto Yellow = Color8888(MaxValue, MaxValue, std::uint8_t{0}, MaxValue);
	//	static constexpr auto Magenta = Color8888(MaxValue, std::uint8_t{0}, MaxValue, MaxValue);
	//	static constexpr auto Cyan = Color8888(std::uint8_t{0}, MaxValue, MaxValue, MaxValue);
	//};
}

namespace PonyEngine::Math
{
	constexpr Color8888::Color8888(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha) noexcept :
		components{red, green, blue, alpha}
	{
	}

	constexpr Color8888::Color8888(const std::uint8_t* const components) noexcept
	{
		Set(components);
	}

	constexpr Color8888::Color8888(const Color888& color, const std::uint8_t alpha) noexcept :
		Color8888(color.R(), color.G(), color.B(), alpha)
	{
	}

	constexpr Color8888::Color8888(const Vector4<std::uint8_t>& vector) noexcept :
		Color8888(vector.Data())
	{
	}

	constexpr std::uint8_t& Color8888::R() noexcept
	{
		return components[0];
	}

	constexpr const std::uint8_t& Color8888::R() const noexcept
	{
		return components[0];
	}

	constexpr std::uint8_t& Color8888::G() noexcept
	{
		return components[1];
	}

	constexpr const std::uint8_t& Color8888::G() const noexcept
	{
		return components[1];
	}

	constexpr std::uint8_t& Color8888::B() noexcept
	{
		return components[2];
	}

	constexpr const std::uint8_t& Color8888::B() const noexcept
	{
		return components[2];
	}

	constexpr std::uint8_t& Color8888::A() noexcept
	{
		return components[3];
	}

	constexpr const std::uint8_t& Color8888::A() const noexcept
	{
		return components[3];
	}

	constexpr std::uint8_t* Color8888::Data() noexcept
	{
		return components.data();
	}

	constexpr const std::uint8_t* Color8888::Data() const noexcept
	{
		return components.data();
	}

	constexpr std::uint8_t& Color8888::Min() noexcept
	{
		return *std::ranges::min_element(components);
	}

	constexpr const std::uint8_t& Color8888::Min() const noexcept
	{
		return *std::ranges::min_element(components);
	}

	constexpr std::uint8_t& Color8888::Max() noexcept
	{
		return *std::ranges::max_element(components);
	}

	constexpr const std::uint8_t& Color8888::Max() const noexcept
	{
		return *std::ranges::max_element(components);
	}

	constexpr bool Color8888::IsBlack() const noexcept
	{
		return false; // *this == Predefined::Black;
	}

	constexpr bool Color8888::IsWhite() const noexcept
	{
		return false; // *this == Predefined::White;
	}

	constexpr bool Color8888::IsTransparent() const noexcept
	{
		return A() == std::uint8_t{0};
	}

	constexpr void Color8888::Set(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha) noexcept
	{
		R() = red;
		G() = green;
		B() = blue;
		A() = alpha;
	}

	constexpr void Color8888::Set(const std::uint8_t* const componentsToSet) noexcept
	{
		std::copy_n(componentsToSet, ComponentCount, Data());
	}

	constexpr std::array<std::uint8_t, 4> Color8888::ToArray() const noexcept
	{
		return components;
	}

	constexpr void Color8888::ToArray(std::uint8_t (&array)[ComponentCount]) const noexcept
	{
		std::ranges::copy(components, array);
	}

	std::string Color8888::ToString() const
	{
		return std::format("(R: {}, G: {}, B: {}, A: {})", R(), G(), B(), A());
	}

	constexpr Color8888::operator Color888() const noexcept
	{
		return Color888(Data());
	}

	constexpr Color8888::operator Vector4<std::uint8_t>() const noexcept
	{
		return Vector4<std::uint8_t>(Data());
	}

	constexpr std::uint8_t& Color8888::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	constexpr const std::uint8_t& Color8888::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	constexpr bool Color8888::operator ==(const Color8888& other) const noexcept
	{
		return components == other.components;
	}

	std::ostream& operator <<(std::ostream& stream, const Color8888& color)
	{
		return stream << color.ToString();
	}
}
