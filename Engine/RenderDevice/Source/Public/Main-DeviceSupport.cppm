/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DeviceSupport;

import std;

import :CBVRequirement;
import :HeapType;
import :SamplerSupport;
import :SwapChainSupport;

export namespace PonyEngine::RenderDevice
{
	struct DeviceSupport final
	{
		HeapTypeMask bufferHeaps;
		HeapTypeMask textureHeaps;
		CBVRequirement cbvRequirement;
		SamplerSupport samplerSupport;
		SwapChainSupport swapChainSupport;
	};
}
