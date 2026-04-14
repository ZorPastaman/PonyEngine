/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:CopyableFootprintSize;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Copyable footprint size.
	struct CopyableFootprintSize final
	{
		std::uint64_t sourceTotalSize; ///< Source byte-array total size in bytes.
		std::uint64_t destinationTotalSize; ///< Destination texture buffer total size in bytes.
	};
}
