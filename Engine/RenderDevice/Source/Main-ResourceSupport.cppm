/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ResourceSupport;

import :HeapType;

export namespace PonyEngine::RenderDevice
{
	/// @brief Resource support.
	struct ResourceSupport final
	{
		HeapTypeMask bufferHeaps; ///< Supported buffer heap types.
		HeapTypeMask textureHeaps; ///< Supported texture heap types.
	};
}
