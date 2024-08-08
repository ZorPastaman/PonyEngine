/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Color888;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <format>;
import <limits>;
import <ostream>;
import <string>;

import :Vector3;

export namespace PonyEngine::Math
{
	class Color888 final
	{
	public:
		using ValueType = std::uint8_t; ///< Component type.

		static constexpr std::uint8_t MaxValue = std::numeric_limits<std::uint8_t>::max();
		static constexpr std::size_t ComponentCount = 3; ///< Component count. For any Color888, it's always 3.

		struct Predefined; ///< Predefined colors.

		[[nodiscard("Pure constructor")]]
		constexpr Color888() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Color888(std::uint8_t red, std::uint8_t green, std::uint8_t blue) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Color888(const std::uint8_t* components) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Color888(const Vector3<std::uint8_t>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Color888(const Color888& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Color888(Color888&& other) noexcept = default;

		constexpr ~Color888() noexcept = default;

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

		constexpr void Set(std::uint8_t red, std::uint8_t green, std::uint8_t blue) noexcept;
		constexpr void Set(const std::uint8_t* componentsToSet) noexcept;

		[[nodiscard("Pure function")]]
		constexpr std::array<std::uint8_t, 3> ToArray() const noexcept;
		constexpr void ToArray(std::uint8_t (&array)[ComponentCount]) const noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		[[nodiscard("Pure operator")]]
		explicit constexpr operator Vector3<std::uint8_t>() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr std::uint8_t& operator [](std::size_t index) noexcept;
		[[nodiscard("Pure operator")]]
		constexpr const std::uint8_t& operator [](std::size_t index) const noexcept;

		Color888& operator =(const Color888& other) noexcept = default;
		Color888& operator =(Color888&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Color888& other) const noexcept;

	private:
		std::array<std::uint8_t, ComponentCount> components;
	};

	std::ostream& operator <<(std::ostream& stream, const Color888& color);
}

namespace PonyEngine::Math
{
	constexpr Color888::Color888(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue) noexcept :
		components{red, green, blue}
	{
	}

	constexpr Color888::Color888(const std::uint8_t* const components) noexcept
	{
		Set(components);
	}

	constexpr Color888::Color888(const Vector3<std::uint8_t>& vector) noexcept :
		Color888(vector.Data())
	{
	}

	struct Color888::Predefined final // TODO: move other predefined structures after constructors to avoid constexpr compilation issues.
	{
		Predefined() = delete;

		static constexpr auto Red = Color888(MaxValue, std::uint8_t{0}, std::uint8_t{0}); ///< Color888(255, 0, 0).
		static constexpr auto Green = Color888(std::uint8_t{0}, MaxValue, std::uint8_t{0}); ///< Color888(0, 255, 0).
		static constexpr auto Blue = Color888(std::uint8_t{0}, std::uint8_t{0}, MaxValue); ///< Color888(0, 0, 255).
		static constexpr auto Black = Color888(std::uint8_t{0}, std::uint8_t{0}, std::uint8_t{0}); ///< Color888(0, 0, 0).
		static constexpr auto White = Color888(MaxValue, MaxValue, MaxValue); ///< Color888(255, 255, 255).
		static constexpr auto Yellow = Color888(MaxValue, MaxValue, std::uint8_t{0}); ///< Color888(255, 255, 0).
		static constexpr auto Magenta = Color888(MaxValue, std::uint8_t{0}, MaxValue); ///< Color888(255, 0, 255).
		static constexpr auto Cyan = Color888(std::uint8_t{0}, MaxValue, MaxValue); ///< Color888(0, 255, 255).
	};

	constexpr std::uint8_t& Color888::R() noexcept
	{
		return components[0];
	}

	constexpr const std::uint8_t& Color888::R() const noexcept
	{
		return components[0];
	}

	constexpr std::uint8_t& Color888::G() noexcept
	{
		return components[1];
	}

	constexpr const std::uint8_t& Color888::G() const noexcept
	{
		return components[1];
	}

	constexpr std::uint8_t& Color888::B() noexcept
	{
		return components[2];
	}

	constexpr const std::uint8_t& Color888::B() const noexcept
	{
		return components[2];
	}

	constexpr std::uint8_t* Color888::Data() noexcept
	{
		return components.data();
	}

	constexpr const std::uint8_t* Color888::Data() const noexcept
	{
		return components.data();
	}

	constexpr std::uint8_t& Color888::Min() noexcept
	{
		return *std::ranges::min_element(components);
	}

	constexpr const std::uint8_t& Color888::Min() const noexcept
	{
		return *std::ranges::min_element(components);
	}

	constexpr std::uint8_t& Color888::Max() noexcept
	{
		return *std::ranges::max_element(components);
	}

	constexpr const std::uint8_t& Color888::Max() const noexcept
	{
		return *std::ranges::max_element(components);
	}

	constexpr bool Color888::IsBlack() const noexcept
	{
		return *this == Predefined::Black;
	}

	constexpr bool Color888::IsWhite() const noexcept
	{
		return *this == Predefined::White;
	}

	constexpr void Color888::Set(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue) noexcept
	{
		R() = red;
		G() = green;
		B() = blue;
	}

	constexpr void Color888::Set(const std::uint8_t* const componentsToSet) noexcept
	{
		std::copy_n(componentsToSet, ComponentCount, Data()); // TODO: Apply copy_n to other structures
	}

	constexpr std::array<std::uint8_t, 3> Color888::ToArray() const noexcept
	{
		return components;
	}

	constexpr void Color888::ToArray(std::uint8_t (&array)[ComponentCount]) const noexcept
	{
		std::ranges::copy(components, array);
	}

	std::string Color888::ToString() const
	{
		return std::format("(R: {}, G: {}, B: {})", R(), G(), B());
	}

	constexpr Color888::operator Vector3<std::uint8_t>() const noexcept
	{
		return Vector3<std::uint8_t>(Data());
	}

	constexpr std::uint8_t& Color888::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	constexpr const std::uint8_t& Color888::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	constexpr bool Color888::operator ==(const Color888& other) const noexcept
	{
		return components == other.components;
	}

	std::ostream& operator <<(std::ostream& stream, const Color888& color)
	{
		return stream << color.ToString();
	}
}
