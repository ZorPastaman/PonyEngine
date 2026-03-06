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
	/// @brief Mip range.
	struct MipRange final
	{
		std::uint8_t mostDetailedMipIndex = 0u; ///< Most detailed mip index.
		std::optional<std::uint8_t> mipCount = std::nullopt; ///< Mip count. Nullopt means till a last mip.
	};

	/// @brief Array range.
	struct ArrayRange final
	{
		std::uint16_t firstArrayIndex = 0u; ///< First array element index.
		std::optional<std::uint16_t> arrayCount = std::nullopt; ///< Array count. Nullopt means till a last array element.
	};

	/// @brief Sub-texture range.
	struct SubTextureRange final
	{
		ArrayRange arrayRange; ///< Array range.
		MipRange mipRange; ///< Mip ranges.
		AspectMask aspects = AspectMask::Color; ///< Aspects.
	};

	/// @brief Sub-texture range for a copy command.
	struct CopySubTextureRange final
	{
		std::uint16_t sourceArrayIndex = 0u; ///< First source array element index.
		std::uint16_t destinationArrayIndex = 0u; ///< First destination array element index.
		std::uint16_t arrayCount = 1u; ///< How many array elements to copy?
		std::uint8_t sourceMipIndex = 0u; ///< First source mip index.
		std::uint8_t destinationMipIndex = 0u; ///< First destination mip index.
		std::uint8_t mipCount = 1u; ///< How many mips to copy?
		AspectMask aspects = AspectMask::Color; ///< Aspects to copy.
	};

	/// @brief Sub-texture range for a copy command with a rectangle region.
	/// @remark Copy elements depend on these parameters, and they go in this priority order: aspect, array index, mip index.
	struct RectCopySubTextureRange final
	{
		std::span<const Math::Vector2<std::uint32_t>> sourceOffsets; ///< Source rectangle offsets for each copy element.
		std::span<const Math::Vector2<std::uint32_t>> destinationOffsets; ///< Destination rectangle offsets for each copy element.
		std::span<const Math::Vector2<std::uint32_t>> sourceSizes; ///< Source rectangle sizes for each copy element.
		std::uint16_t sourceArrayIndex = 0u; ///< First source array element index.
		std::uint16_t destinationArrayIndex = 0u; ///< First destination array element index.
		std::uint16_t arrayCount = 1u; ///< How many array elements to copy?
		std::uint8_t sourceMipIndex = 0u; ///< First source mip index.
		std::uint8_t destinationMipIndex = 0u; ///< First destination mip index.
		std::uint8_t mipCount = 1u; ///< How many mips to copy?
		AspectMask aspects = AspectMask::Color; ///< Aspects to copy.
	};

	/// @brief Sub-texture range for a copy command with a box region.
	/// @remark Copy elements depend on these parameters, and they go in this priority order: aspect, array index, mip index.
	struct BoxCopySubTextureRange final
	{
		std::span<const Math::Vector3<std::uint32_t>> sourceOffsets; ///< Source box offsets for each copy element.
		std::span<const Math::Vector3<std::uint32_t>> destinationOffsets; ///< Destination box offsets for each copy element.
		std::span<const Math::Vector3<std::uint32_t>> sourceSizes; ///< Source box sizes for each copy element.
		std::uint16_t sourceArrayIndex = 0u; ///< First source array element index.
		std::uint16_t destinationArrayIndex = 0u; ///< First destination array element index.
		std::uint16_t arrayCount = 1u; ///< How many array elements to copy?
		std::uint8_t sourceMipIndex = 0u; ///< First source mip index.
		std::uint8_t destinationMipIndex = 0u; ///< First destination mip index.
		std::uint8_t mipCount = 1u; ///< How many mips to copy?
		AspectMask aspects = AspectMask::Color; ///< Aspects to copy.
	};

	/// @brief Sub-texture range for a copy between a texture and a texture buffer.
	struct FootprintedCopySubTextureRange final
	{
		std::uint16_t arrayIndex = 0u; ///< First array element index.
		std::uint16_t arrayCount = 1u; ///< How many array elements to copy?
		std::uint8_t mipIndex = 0u; ///< First mip index.
		std::uint8_t mipCount = 1u; ///< How many mips to copy?
		AspectMask aspects = AspectMask::Color; ///< Aspects to copy.
	};

	/// @brief Sub-texture range for a copy between a texture and a texture buffer with a box region.
	struct FootprintedBoxCopySubTextureRange final
	{
		std::span<const Math::Vector3<std::uint32_t>> sourceOffsets; ///< Source box offsets for each copy element.
		std::span<const Math::Vector3<std::uint32_t>> destinationOffsets; ///< Destination box offsets for each copy element.
		std::span<const Math::Vector3<std::uint32_t>> sourceSizes; ///< Source box sizes for each copy element.
		std::uint16_t arrayIndex = 0u; ///< First array element index.
		std::uint16_t arrayCount = 1u; ///< How many array elements to copy?
		std::uint8_t mipIndex = 0u; ///< First mip index.
		std::uint8_t mipCount = 1u; ///< How many mips to copy?
		AspectMask aspects = AspectMask::Color; ///< Aspects to copy.
	};
}
