/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ResourceHeapParams;

import :HeapType;

export namespace PonyEngine::RenderDevice
{
	/// @brief Committed resource heap parameters.
	struct CommittedResourceHeapParams final
	{
		HeapType heapType = HeapType::Default; ///< Heap type.
		bool notZeroed = false; ///< If @a true, the allocated resource won't be zeroed.
	};
}
