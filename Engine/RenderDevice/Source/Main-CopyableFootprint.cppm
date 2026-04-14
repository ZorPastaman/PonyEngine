/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:CopyableFootprint;

import std;

import :Aspect;

export namespace PonyEngine::RenderDevice
{
	/// @brief Copyable footprints. It determines a sub-texture buffer and a source byte array layouts.
	struct CopyableFootprint final
	{
		std::uint64_t offset = 0ull; ///< Buffer offset in bytes.
		std::uint64_t rowSize = 0ull; ///< Source array row size in bytes.
		std::uint64_t rowPitch = 0ull; ///< Buffer row size in bytes.
		std::uint32_t rowCount = 0u; ///< Row count.
		std::uint32_t width = 0u; ///< Sub-texture width.
		std::uint32_t height = 0u; ///< Sub-texture height.
		std::uint32_t depth = 0u; ///< Sub-texture depth.
		std::uint16_t arrayIndex = 0u; ///< Texture array element index.
		std::uint8_t mipIndex = 0u; ///< Texture mip index.
		Aspect aspect = Aspect::Color; ///< Texture aspect.
	};
}
