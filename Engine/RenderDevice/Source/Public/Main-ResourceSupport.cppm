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
	struct ResourceSupport final
	{
		HeapTypeMask bufferHeaps;
		HeapTypeMask textureHeaps;
	};
}
