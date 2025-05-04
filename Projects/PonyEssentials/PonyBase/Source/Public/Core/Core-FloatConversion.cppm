/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Core:FloatConversion;

import <bit>;
import <cstdint>;

export namespace PonyBase::Core
{
	/// @brief Converts a float32 value to float16.
	/// @param value Float32.
	/// @return Float16.
	[[nodiscard("Pure function")]]
	constexpr std::uint16_t ToFloat16(float value) noexcept;
	/// @brief Converts a float16 value to float32.
	/// @param value Float16.
	/// @return Float32.
	[[nodiscard("Pure function")]]
	constexpr float ToFloat32(std::uint16_t value) noexcept;
}

namespace PonyBase::Core
{
	constexpr std::uint16_t ToFloat16(const float value) noexcept // TODO: Add tests
	{
		const std::uint32_t value32 = std::bit_cast<std::uint32_t>(value);
		const std::uint32_t sign = value32 >> 16 & 0x8000;
		const std::uint32_t exponent = value32 >> 23 & 0xFF;
		const std::uint32_t mantissa = value32 >> 12 & 0x7FF;

		std::uint32_t answer = sign;

		if (exponent >= 103)
		{
			if (exponent > 142)
			{
				answer |= 0x7c00u;
				answer |= exponent == 255 && (value32 & 0x007fffffu);
			}
			else if (exponent < 113)
			{
				const std::uint32_t m = mantissa | 0x0800u;
				answer |= (m >> (114 - exponent)) + (m >> (113 - exponent) & 1);
			}
			else
			{
				answer |= (exponent - 112) << 10 | mantissa >> 1;
				answer += mantissa & 1;
			}
		}

		return static_cast<std::uint16_t>(answer);
	}

	constexpr float ToFloat32(const std::uint16_t value) noexcept
	{
		const std::uint32_t value32 = value;
		const std::uint32_t sign = (value32 & 0x8000) << 16;
		std::uint32_t exponent = value32 >> 10 & 0x1F;
		std::uint32_t mantissa = value32 & 0x3FF;

		if (!exponent)
		{
			if (mantissa)
			{
				const std::uint32_t leadingZeros = std::countl_zero(mantissa) - 22;
				exponent = 127 - 14 - leadingZeros;
				mantissa <<= leadingZeros;
			}
		}
		else if (exponent == 0x1F)
		{
			exponent = 0xFF;
		}
		else
		{
			exponent += 127 - 15;
		}

		exponent <<= 23;
		mantissa <<= 13;
		const std::uint32_t answer = sign | exponent | mantissa;

		return std::bit_cast<float>(answer);
	}
}
