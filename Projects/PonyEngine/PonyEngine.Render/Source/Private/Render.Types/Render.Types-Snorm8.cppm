/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Types:Snorm8;

import <algorithm>;
import <cstdint>;
import <limits>;

import PonyMath.Core;

export namespace PonyEngine::Render::Types
{
	/// @brief Snorm8 implementation.
	struct Snorm8 final
	{
		static constexpr std::int8_t MaxValue = std::numeric_limits<std::int8_t>::max(); ///< Max value.
		static constexpr float MaxValueInv = 1.f / static_cast<float>(MaxValue); ///< Max value inverse.

		/// @brief Creates a zero snorm.
		[[nodiscard("Pure constructor")]]
		constexpr Snorm8() noexcept = default;
		/// @brief Creates a snorm with the specified value.
		/// @param value Value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Snorm8(std::int8_t value) noexcept;
		/// @brief Creates a snorm from a float value.
		/// @param value Float value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Snorm8(float value) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Snorm8(const Snorm8& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Snorm8(Snorm8&& other) noexcept = default;

		constexpr ~Snorm8() noexcept = default;

		/// @brief Converts the snorm to a float.
		explicit constexpr operator float() const noexcept;

		constexpr Snorm8& operator =(const Snorm8& other) noexcept = default;
		constexpr Snorm8& operator =(Snorm8&& other) noexcept = default;

		std::int8_t value; ///< Value.
	};
}

namespace PonyEngine::Render::Types
{
	constexpr Snorm8::Snorm8(const std::int8_t value) noexcept :
		value{value}
	{
	}

	constexpr Snorm8::Snorm8(const float value) noexcept :
		value{PonyMath::Core::RoundToIntegral<float, std::int8_t>(std::clamp(value, -1.f, 1.f) * static_cast<float>(MaxValue))}
	{
	}

	constexpr Snorm8::operator float() const noexcept
	{
		return std::clamp(static_cast<float>(value) * MaxValueInv, -1.f, 1.f);
	}
}
