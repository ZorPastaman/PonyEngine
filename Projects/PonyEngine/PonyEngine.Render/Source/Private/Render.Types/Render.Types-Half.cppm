/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Types:Half;

import <bit>;
import <cstdint>;

export namespace PonyEngine::Render
{
	/// @brief Half implementation.
	struct Half final
	{
		[[nodiscard("Pure constructor")]]
		constexpr Half() noexcept = default;
		/// @brief Creates a half and sets bits.
		/// @param bits Bits to set.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Half(std::uint16_t bits) noexcept;
		/// @brief Creates a half and convert the float32 to a float16.
		/// @param value Float32 value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Half(float value) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Half(const Half& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Half(Half&& other) noexcept = default;

		constexpr ~Half() noexcept = default;

		/// @brief Convert the float16 to a float32.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator float() const noexcept;

		Half& operator =(const Half& other) noexcept = default;
		Half& operator =(Half&& other) noexcept = default; 

		std::uint16_t bits; ///< Float16 bits.
	};
}

namespace PonyEngine::Render
{
	constexpr Half::Half(const std::uint16_t bits) noexcept :
		bits{bits}
	{
	}

	constexpr Half::Half(const float value) noexcept
	{
		const std::uint32_t valueBits = std::bit_cast<std::uint32_t>(value);

		const uint32_t sign = valueBits >> 16 & 0x8000;
		const int32_t exponent = (valueBits >> 23 & 0xFF) - (127 - 15);
		const uint32_t mantissa = valueBits >> 13 & 0x3FF;

		if (exponent <= 0) 
		{
			bits = static_cast<std::uint16_t>(sign);
		}
		else if (exponent >= 0x1F) 
		{
			bits = static_cast<uint16_t>(sign | 0x7BFF);
		}
		else 
		{
			bits = static_cast<uint16_t>(sign | exponent << 10 | mantissa);
		}
	}

	constexpr Half::operator float() const noexcept
	{
		const uint32_t sign = (bits & 0x8000) << 16;
		const uint32_t exponent = (bits >> 10 & 0x1F) + (127 - 15);
		const uint32_t mantissa = bits & 0x3FF;

		const uint32_t result = sign | exponent << 23 | mantissa << 13;

		return std::bit_cast<float>(result);
	}
}
