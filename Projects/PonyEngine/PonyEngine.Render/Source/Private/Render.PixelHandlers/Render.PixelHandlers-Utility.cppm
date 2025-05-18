/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.PixelHandlers:Utility;

import <algorithm>;
import <bit>;
import <cstddef>;
import <cstdint>;
import <cstring>;
import <limits>;
import <span>;

import PonyMath.Core;

export namespace PonyEngine::Render
{
	/// @brief Value mask.
	/// @tparam Bits Value bit count.
	template<std::uint64_t Bits>
	constexpr std::uint64_t BitMask = Bits == sizeof(std::uint64_t) * 8
		? std::numeric_limits<std::uint64_t>::max()
		: (std::uint64_t{1} << Bits) - 1;

	/// @brief Computes a pixel index in a buffer.
	/// @param size Texture size.
	/// @param pixelCoordinate Pixel coordinate.
	/// @return Pixel index.
	[[nodiscard("Pure function")]]
	std::size_t PixelIndex(const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) noexcept;

	/// @brief Converts a unorm to a float.
	/// @tparam Offset Offset in bits.
	/// @tparam Bits Unorm value bit count.
	/// @param data Raw data.
	/// @return Float value.
	template<std::uint64_t Offset, std::uint64_t Bits> [[nodiscard("Pure function")]]
	float UnormToFloat(std::span<const std::byte> data) noexcept requires (Offset + Bits <= sizeof(std::uint64_t) * 8);
	/// @brief Converts a float to a unorm.
	/// @tparam Offset Offset in bits.
	/// @tparam Bits Unorm value bit count.
	/// @param data Target data.
	/// @param value Float value.
	template<std::uint64_t Offset, std::uint64_t Bits>
	void FloatToUnorm(std::span<std::byte> data, float value) noexcept requires (Offset + Bits <= sizeof(std::uint64_t) * 8);

	/// @brief Converts a snorm to a float.
	/// @tparam Offset Offset in bits.
	/// @tparam Bits Snorm value bit count.
	/// @param data Raw data.
	/// @return Float value.
	template<std::uint64_t Offset, std::uint64_t Bits> [[nodiscard("Pure function")]]
	float SnormToFloat(std::span<const std::byte> data) noexcept requires (Offset + Bits <= sizeof(std::uint64_t) * 8 && Bits > 2);
	/// @brief Converts a float to a snorm.
	/// @tparam Offset Offset in bits.
	/// @tparam Bits Snorm value bit count.
	/// @param data Target data.
	/// @param value Float value.
	template<std::uint64_t Offset, std::uint64_t Bits>
	void FloatToSnorm(std::span<std::byte> data, float value) noexcept requires (Offset + Bits <= sizeof(std::uint64_t) * 8 && Bits > 2);

	/// @brief Converts a uint to a float.
	/// @tparam Offset Offset in bits.
	/// @tparam Bits Uint value bit count.
	/// @param data Raw data.
	/// @return Float value.
	template<std::uint64_t Offset, std::uint64_t Bits> [[nodiscard("Pure function")]]
	float UintToFloat(std::span<const std::byte> data) noexcept requires (Offset + Bits <= sizeof(std::uint64_t) * 8);
	/// @brief Converts a float to a uint.
	/// @tparam Offset Offset in bits.
	/// @tparam Bits Uint value bit count.
	/// @param data Target data.
	/// @param value Float value.
	template<std::uint64_t Offset, std::uint64_t Bits>
	void FloatToUint(std::span<std::byte> data, float value) noexcept requires (Offset + Bits <= sizeof(std::uint64_t) * 8);

	/// @brief Converts a special ufloat to a float.
	/// @tparam Offset Offset in bits.
	/// @tparam ExponentBits Exponent bit count.
	/// @tparam MantissaBits Mantissa bit count.
	/// @param data Raw data.
	/// @return Float value.
	template<std::uint64_t Offset, std::uint32_t ExponentBits, std::uint32_t MantissaBits>
	float SpecialUfloatToFloat(std::span<const std::byte> data) noexcept requires (Offset + ExponentBits + MantissaBits <= sizeof(std::uint64_t) * 8 && ExponentBits + MantissaBits <= sizeof(std::uint32_t) * 8);
	/// @brief Converts a float to a special ufloat.
	/// @tparam Offset Offset in bits.
	/// @tparam ExponentBits Exponent bit count.
	/// @tparam MantissaBits Mantissa bit count.
	/// @param data Target data.
	/// @param value Float value.
	template<std::uint64_t Offset, std::uint32_t ExponentBits, std::uint32_t MantissaBits>
	void FloatToSpecialUfloat(std::span<std::byte> data, float value) noexcept requires (Offset + ExponentBits + MantissaBits <= sizeof(std::uint64_t) * 8 && ExponentBits + MantissaBits <= sizeof(std::uint32_t) * 8);
}

namespace PonyEngine::Render
{
	/// @brief Bit value info that has a required constants for parsing unorms and snorms.
	/// @tparam Offset Bit offset.
	/// @tparam Bits Bit count.
	template<std::uint64_t Offset, std::uint64_t Bits>
	struct BitValueInfo
	{
		NON_CONSTRUCTIBLE_BODY(BitValueInfo)

		static constexpr std::uint64_t ByteOffset = Offset / 8; ///< Byte offset to read/write data.
		static constexpr std::uint64_t BitOffset = Offset % 8; ///< Bit offset to read/write data.

		static constexpr std::uint64_t TotalBits = BitOffset + Bits; ///< Total bits to read/write.
		static constexpr std::uint64_t TotalBytes = (TotalBits + 7) / 8; ///< Total bytes to read/write.

		/// @brief Value mask. For unorms, it's a max value as well.
		static constexpr std::uint64_t Mask = BitMask<Bits>;

		static constexpr std::int64_t MaxValue = std::bit_cast<std::int64_t>(Mask >> 1); ///< Snorm max value. Don't use it for unorms.
	};

	/// @brief Bit value info that has a required constants for parsing ufloats
	/// @tparam Offset Bit offset.
	/// @tparam ExponentBits Exponent bit count.
	/// @tparam MantissaBits Mantissa bit count.
	template<std::uint64_t Offset, std::uint32_t ExponentBits, std::uint32_t MantissaBits>
	struct UfloatBitValueInfo final : BitValueInfo<Offset, ExponentBits + MantissaBits>
	{
		NON_CONSTRUCTIBLE_BODY(UfloatBitValueInfo)

		static constexpr std::uint32_t AllBits = ExponentBits + MantissaBits;
		static constexpr std::uint32_t Bias = (1 << (ExponentBits - 1)) - 1;

		static constexpr std::uint32_t ExponentMask = BitMask<ExponentBits>;
		static constexpr std::uint32_t MantissaMask = BitMask<MantissaBits>;
	};

	constexpr std::uint32_t FloatExponentBits = 8; ///< Float32 exponent bit count.
	constexpr std::uint32_t FloatMantissaBits = 23; ///< Float32 mantissa bit count.
	constexpr std::uint32_t FloatExponentMask = BitMask<FloatExponentBits>; ///< Float32 exponent mask.
	constexpr std::uint32_t FloatMantissaMask = BitMask<FloatMantissaMask>; ///< Float32 mantissa mask.
	constexpr std::uint32_t FloatBias = 127; ///< Float32 bias.

	std::size_t PixelIndex(const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) noexcept
	{
		return static_cast<std::size_t>(size.X()) * size.Y() * pixelCoordinate.Z() + static_cast<std::size_t>(size.X()) * pixelCoordinate.Y() + pixelCoordinate.X();
	}

	template<std::uint64_t Offset, std::uint64_t Bits>
	float UnormToFloat(const std::span<const std::byte> data) noexcept requires (Offset + Bits <= sizeof(std::uint64_t) * 8)
	{
		using BitInfo = BitValueInfo<Offset, Bits>;

		std::uint64_t value = 0;
		std::memcpy(&value, &data[BitInfo::ByteOffset], BitInfo::TotalBytes);
		value >>= BitInfo::BitOffset;
		value &= BitInfo::Mask;

		return static_cast<float>(value) / static_cast<float>(BitInfo::Mask);
	}

	template <std::uint64_t Offset, std::uint64_t Bits>
	void FloatToUnorm(const std::span<std::byte> data, const float value) noexcept requires (Offset + Bits <= sizeof(std::uint64_t) * 8)
	{
		using BitInfo = BitValueInfo<Offset, Bits>;

		std::uint64_t currentValue = 0;
		std::memcpy(&currentValue, &data[BitInfo::ByteOffset], BitInfo::TotalBytes);

		const std::uint64_t bitValue = PonyMath::Core::RoundToIntegral<float, std::uint64_t>(std::clamp(value, 0.f, 1.f) * BitInfo::Mask);

		const std::uint64_t result = currentValue & ~(BitInfo::Mask << BitInfo::BitOffset) | (bitValue << BitInfo::BitOffset);
		std::memcpy(&data[BitInfo::ByteOffset], &result, BitInfo::TotalBytes);
	}

	template <std::uint64_t Offset, std::uint64_t Bits>
	float SnormToFloat(const std::span<const std::byte> data) noexcept requires (Offset + Bits <= sizeof(std::uint64_t) * 8 && Bits > 2)
	{
		using BitInfo = BitValueInfo<Offset, Bits>;

		std::int64_t value = 0;
		std::memcpy(&value, &data[BitInfo::ByteOffset], BitInfo::TotalBytes);
		value >>= BitInfo::BitOffset;
		value = (value & BitInfo::MaxValue) | (value >> (Bits - 1) << (sizeof(std::int64_t) * 8 - 1));

		return std::clamp(static_cast<float>(value) / static_cast<float>(BitInfo::MaxValue), -1.f, 1.f);
	}

	template <std::uint64_t Offset, std::uint64_t Bits>
	void FloatToSnorm(const std::span<std::byte> data, const float value) noexcept requires (Offset + Bits <= sizeof(std::uint64_t) * 8 && Bits > 2)
	{
		using BitInfo = BitValueInfo<Offset, Bits>;

		std::uint64_t currentValue = 0;
		std::memcpy(&currentValue, &data[BitInfo::ByteOffset], BitInfo::TotalBytes);

		std::int64_t bitValue = PonyMath::Core::RoundToIntegral<float, std::int64_t>(std::clamp(value, -1.f, 1.f) * BitInfo::MaxValue);
		bitValue |= bitValue >> (sizeof(std::int64_t) * 8 - 1) << (Bits - 1);
		bitValue &= BitInfo::Mask;

		const std::uint64_t result = currentValue & ~(BitInfo::Mask << BitInfo::BitOffset) | (bitValue << BitInfo::BitOffset);
		std::memcpy(&data[BitInfo::ByteOffset], &result, BitInfo::TotalBytes);
	}

	template <std::uint64_t Offset, std::uint64_t Bits>
	float UintToFloat(const std::span<const std::byte> data) noexcept requires (Offset + Bits <= sizeof(std::uint64_t) * 8)
	{
		using BitInfo = BitValueInfo<Offset, Bits>;

		std::uint64_t value = 0;
		std::memcpy(&value, &data[BitInfo::ByteOffset], BitInfo::TotalBytes);
		value >>= BitInfo::BitOffset;
		value &= BitInfo::Mask;

		return static_cast<float>(value);
	}

	template <std::uint64_t Offset, std::uint64_t Bits>
	void FloatToUint(const std::span<std::byte> data, const float value) noexcept requires (Offset + Bits <= sizeof(std::uint64_t) * 8)
	{
		using BitInfo = BitValueInfo<Offset, Bits>;

		std::uint64_t currentValue = 0;
		std::memcpy(&currentValue, &data[BitInfo::ByteOffset], BitInfo::TotalBytes);

		const std::uint64_t bitValue = PonyMath::Core::RoundToIntegral<float, std::uint64_t>(value) & BitInfo::Mask;

		const std::uint64_t result = currentValue & ~(BitInfo::Mask << BitInfo::BitOffset) | (bitValue << BitInfo::BitOffset);
		std::memcpy(&data[BitInfo::ByteOffset], &result, BitInfo::TotalBytes);
	}

	template <std::uint64_t Offset, std::uint32_t ExponentBits, std::uint32_t MantissaBits>
	float SpecialUfloatToFloat(const std::span<const std::byte> data) noexcept requires (Offset + ExponentBits + MantissaBits <= sizeof(std::uint64_t) * 8 && ExponentBits + MantissaBits <= sizeof(std::uint32_t) * 8)
	{
		using BitInfo = UfloatBitValueInfo<Offset, ExponentBits, MantissaBits>;

		std::uint64_t value = 0;
		std::memcpy(&value, &data[BitInfo::ByteOffset], BitInfo::TotalBytes);
		value >>= BitInfo::BitOffset;
		value &= BitInfo::Mask;

		const std::uint32_t exponent = static_cast<std::uint32_t>(value >> MantissaBits & BitInfo::ExponentMask);
		const std::uint32_t mantissa = static_cast<std::uint32_t>(value & BitInfo::MantissaMask);

		if (exponent)
		{
			const std::uint32_t exponent32 = exponent - BitInfo::Bias + FloatBias;
			const std::uint32_t mantissa32 = mantissa << (FloatMantissaBits - MantissaBits);
			const std::uint32_t bits = exponent32 << FloatMantissaBits | mantissa32;

			return std::bit_cast<float>(bits);
		}

		return 0.f;
	}

	template <std::uint64_t Offset, std::uint32_t ExponentBits, std::uint32_t MantissaBits>
	void FloatToSpecialUfloat(const std::span<std::byte> data, const float value) noexcept requires (Offset + ExponentBits + MantissaBits <= sizeof(std::uint64_t) * 8 && ExponentBits + MantissaBits <= sizeof(std::uint32_t) * 8)
	{
		using BitInfo = UfloatBitValueInfo<Offset, ExponentBits, MantissaBits>;

		std::uint64_t currentValue = 0;
		std::memcpy(&currentValue, &data[BitInfo::ByteOffset], BitInfo::TotalBytes);

		std::uint64_t bitValue = 0u;
		if (value > 0.f)
		{
			const std::uint32_t bits = std::bit_cast<uint32_t>(value);
			const std::int32_t exponent = (bits >> FloatMantissaBits & FloatExponentMask) - FloatBias + BitInfo::Bias;
			const std::uint32_t mantissa = (bits & FloatMantissaMask) >> (FloatMantissaBits - MantissaBits);

			if (exponent > 0)
			{
				if (exponent >= BitInfo::ExponentMask)
				{
					exponent = BitInfo::ExponentMask;
					mantissa = BitInfo::MantissaMask;
				}

				bitValue = exponent << MantissaBits | mantissa;
			}
		}

		const std::uint64_t result = currentValue & ~(BitInfo::Mask << BitInfo::BitOffset) | (bitValue << BitInfo::BitOffset);
		std::memcpy(&data[BitInfo::ByteOffset], &result, BitInfo::TotalBytes);
	}
}
