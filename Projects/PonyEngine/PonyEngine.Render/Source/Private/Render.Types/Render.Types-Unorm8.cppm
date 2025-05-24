/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Types:Unorm8;

import <algorithm>;
import <cstdint>;
import <limits>;

import PonyMath.Core;

export namespace PonyEngine::Render::Types
{
	/// @brief Unorm8 implementation.
	struct Unorm8 final
	{
		static constexpr std::uint8_t MaxValue = std::numeric_limits<std::uint8_t>::max(); ///< Max value.
		static constexpr float MaxValueInv = 1.f / static_cast<float>(MaxValue); ///< Max value inverse.

		/// @brief Creates a zero unorm.
		[[nodiscard("Pure constructor")]]
		constexpr Unorm8() noexcept = default;
		/// @brief Creates a unorm with the specified value.
		/// @param value Value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Unorm8(std::uint8_t value) noexcept;
		/// @brief Creates a unorm from a float value.
		/// @param value Float value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Unorm8(float value) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Unorm8(const Unorm8& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Unorm8(Unorm8&& other) noexcept = default;

		constexpr ~Unorm8() noexcept = default;

		/// @brief Converts the unorm to a float.
		explicit constexpr operator float() const noexcept;

		constexpr Unorm8& operator =(const Unorm8& other) noexcept = default;
		constexpr Unorm8& operator =(Unorm8&& other) noexcept = default;

		std::uint8_t value; ///< Value.
	};
}

namespace PonyEngine::Render::Types
{
	constexpr Unorm8::Unorm8(const std::uint8_t value) noexcept :
		value{value}
	{
	}

	constexpr Unorm8::Unorm8(const float value) noexcept :
		value{PonyMath::Core::RoundToIntegral<float, std::uint8_t>(std::clamp(value, 0.f, 1.f) * static_cast<float>(MaxValue))}
	{
	}

	constexpr Unorm8::operator float() const noexcept
	{
		return std::clamp(static_cast<float>(value) * MaxValueInv, 0.f, 1.f);
	}
}
