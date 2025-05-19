/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Types:Unorm16;

import <algorithm>;
import <cstdint>;
import <limits>;

import PonyMath.Core;

export namespace PonyEngine::Render
{
	/// @brief Unorm16 implementation.
	struct Unorm16 final
	{
		static constexpr std::uint16_t MaxValue = std::numeric_limits<std::uint16_t>::max(); ///< Max value.
		static constexpr float MaxValueInv = 1.f / static_cast<float>(MaxValue); ///< Max value inverse.

		/// @brief Creates a zero unorm.
		[[nodiscard("Pure constructor")]]
		constexpr Unorm16() noexcept = default;
		/// @brief Creates a unorm with the specified value.
		/// @param value Value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Unorm16(std::uint16_t value) noexcept;
		/// @brief Creates a unorm from a float value.
		/// @param value Float value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Unorm16(float value) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Unorm16(const Unorm16& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Unorm16(Unorm16&& other) noexcept = default;

		constexpr ~Unorm16() noexcept = default;

		/// @brief Converts the unorm to a float.
		explicit constexpr operator float() const noexcept;

		constexpr Unorm16& operator =(const Unorm16& other) noexcept = default;
		constexpr Unorm16& operator =(Unorm16&& other) noexcept = default;

		std::uint16_t value; ///< Value.
	};
}

namespace PonyEngine::Render
{
	constexpr Unorm16::Unorm16(const std::uint16_t value) noexcept :
		value{value}
	{
	}

	constexpr Unorm16::Unorm16(const float value) noexcept :
		value{PonyMath::Core::RoundToIntegral<float, std::uint16_t>(std::clamp(value, 0.f, 1.f) * static_cast<float>(MaxValue))}
	{
	}

	constexpr Unorm16::operator float() const noexcept
	{
		return std::clamp(static_cast<float>(value) * MaxValueInv, 0.f, 1.f);
	}
}
