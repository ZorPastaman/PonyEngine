/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SubTextureRange;

import std;

import PonyEngine.Math;

import :Aspect;

export namespace PonyEngine::RenderDevice
{
	struct MipRange final
	{
		std::uint8_t mostDetailedMipIndex = 0u;
		std::optional<std::uint8_t> mipCount = std::nullopt;
	};

	struct ArrayRange final
	{
		std::uint16_t firstArrayIndex = 0u;
		std::optional<std::uint16_t> arrayCount = std::nullopt;
	};

	struct SubTextureRange final
	{
		ArrayRange arrayRange;
		MipRange mipRange;
		AspectMask aspects = AspectMask::Color;
	};

	struct CopySubTextureRange final
	{
		std::uint16_t sourceArrayIndex = 0u;
		std::uint16_t destinationArrayIndex = 0u;
		std::uint16_t arrayCount = 1u;
		std::uint8_t sourceMipIndex = 0u;
		std::uint8_t destinationMipIndex = 0u;
		std::uint8_t mipCount = 1u;
		AspectMask aspects = AspectMask::Color;
	};

	struct RectCopySubTextureRange final
	{
		std::span<const Math::Vector2<std::uint32_t>> sourceOffsets;
		std::span<const Math::Vector2<std::uint32_t>> destinationOffsets;
		std::span<const Math::Vector2<std::uint32_t>> sourceSizes;
		std::uint16_t sourceArrayIndex = 0u;
		std::uint16_t destinationArrayIndex = 0u;
		std::uint16_t arrayCount = 1u;
		std::uint8_t sourceMipIndex = 0u;
		std::uint8_t destinationMipIndex = 0u;
		std::uint8_t mipCount = 1u;
		AspectMask aspects = AspectMask::Color;
	};

	struct BoxCopySubTextureRange final
	{
		std::span<const Math::Vector3<std::uint32_t>> sourceOffsets;
		std::span<const Math::Vector3<std::uint32_t>> destinationOffsets;
		std::span<const Math::Vector3<std::uint32_t>> sourceSizes;
		std::uint16_t sourceArrayIndex = 0u;
		std::uint16_t destinationArrayIndex = 0u;
		std::uint16_t arrayCount = 1u;
		std::uint8_t sourceMipIndex = 0u;
		std::uint8_t destinationMipIndex = 0u;
		std::uint8_t mipCount = 1u;
		AspectMask aspects = AspectMask::Color;
	};

	struct FootprintedCopySubTextureRange final
	{
		std::uint16_t arrayIndex = 0u;
		std::uint16_t arrayCount = 1u;
		std::uint8_t mipIndex = 0u;
		std::uint8_t mipCount = 1u;
		AspectMask aspects = AspectMask::Color;
	};

	struct FootprintedBoxCopySubTextureRange final
	{
		std::span<const Math::Vector3<std::uint32_t>> sourceOffsets;
		std::span<const Math::Vector3<std::uint32_t>> destinationOffsets;
		std::span<const Math::Vector3<std::uint32_t>> sourceSizes;
		std::uint16_t arrayIndex = 0u;
		std::uint16_t arrayCount = 1u;
		std::uint8_t mipIndex = 0u;
		std::uint8_t mipCount = 1u;
		AspectMask aspects = AspectMask::Color;
	};
}
