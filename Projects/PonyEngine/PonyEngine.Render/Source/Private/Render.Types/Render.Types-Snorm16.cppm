/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Types:Snorm16;

import <algorithm>;
import <cstdint>;
import <limits>;

import PonyMath.Core;

export namespace PonyEngine::Render
{
	/// @brief Snorm16 implementation.
	struct Snorm16 final
	{
		static constexpr std::int16_t MaxValue = std::numeric_limits<std::int16_t>::max(); ///< Max value.
		static constexpr float MaxValueInv = 1.f / static_cast<float>(MaxValue); ///< Max value inverse.

		/// @brief Creates a zero snorm.
		[[nodiscard("Pure constructor")]]
		constexpr Snorm16() noexcept = default;
		/// @brief Creates a snorm with the specified value.
		/// @param value Value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Snorm16(std::int16_t value) noexcept;
		/// @brief Creates a snorm from a float value.
		/// @param value Float value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Snorm16(float value) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Snorm16(const Snorm16& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Snorm16(Snorm16&& other) noexcept = default;

		constexpr ~Snorm16() noexcept = default;

		/// @brief Converts the snorm to a float.
		explicit constexpr operator float() const noexcept;

		constexpr Snorm16& operator =(const Snorm16& other) noexcept = default;
		constexpr Snorm16& operator =(Snorm16&& other) noexcept = default;

		std::int16_t value; ///< Value.
	};
}

namespace PonyEngine::Render
{
	constexpr Snorm16::Snorm16(const std::int16_t value) noexcept :
		value{value}
	{
	}

	constexpr Snorm16::Snorm16(const float value) noexcept :
		value{PonyMath::Core::RoundToIntegral<float, std::int16_t>(std::clamp(value, -1.f, 1.f) * static_cast<float>(MaxValue))}
	{
	}

	constexpr Snorm16::operator float() const noexcept
	{
		return std::clamp(static_cast<float>(value) * MaxValueInv, -1.f, 1.f);
	}
}
