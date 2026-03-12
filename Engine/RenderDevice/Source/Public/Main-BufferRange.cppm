/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:BufferRange;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Buffer range.
	struct BufferRange final
	{
		std::uint64_t offset = 0ull; ///< Buffer data offset in bytes.
		std::uint64_t size = 0ull; ///< Buffer data size in bytes.
	};

	/// @brief Copy buffer range.
	struct CopyBufferRange final
	{
		std::uint64_t sourceOffset = 0ull; ///< Source buffer offset in bytes.
		std::uint64_t destinationOffset = 0ull; ///< Destination buffer offset in bytes.
		std::uint64_t size = 0ull; ///< Copy size in bytes.
	};
}
