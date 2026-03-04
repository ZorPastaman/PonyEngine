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

export namespace PonyEngine::RenderDevice
{
	/// @brief Copyable footprints. It determines a sub-texture buffer and a source byte array layouts.
	struct CopyableFootprint final
	{
		std::uint64_t offset; ///< Buffer offset in bytes.
		std::uint64_t rowSize; ///< Source row size in bytes.
		std::uint64_t rowPitch; ///< Buffer row size in bytes.
		std::uint32_t rowCount; ///< Row count.
		std::uint32_t width; ///< Sub-texture width.
		std::uint32_t height; ///< Sub-texture height.
		std::uint32_t sliceCount; ///< Sub-texture slice count.
	};
}
