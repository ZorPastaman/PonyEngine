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
import :SubTextureIndex;

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

	/// @brief Casts the sub-texture index to a sub-texture range.
	/// @param index Sub-texture index.
	/// @return Sub-texture range.
	[[nodiscard("Pure function")]]
	constexpr SubTextureRange ToRange(const SubTextureIndex& index) noexcept;
}

namespace PonyEngine::RenderDevice
{
	constexpr SubTextureRange ToRange(const SubTextureIndex& index) noexcept
	{
		return SubTextureRange
		{
			.arrayRange = ArrayRange{.firstArrayIndex = index.arrayIndex, .arrayCount = 1u},
			.mipRange = MipRange{.mostDetailedMipIndex = index.mipIndex, .mipCount = 1u},
			.aspects = ToMask(index.aspect)
		};
	}
}
