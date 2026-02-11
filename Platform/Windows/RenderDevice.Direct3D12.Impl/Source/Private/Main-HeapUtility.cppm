/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:HeapUtility;

import PonyEngine.RenderDevice;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	[[nodiscard("Pure function")]]
	constexpr D3D12_HEAP_PROPERTIES ToHeapProperties(HeapType heapType) noexcept;
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	constexpr D3D12_HEAP_PROPERTIES ToHeapProperties(const HeapType heapType) noexcept
	{
		auto properties = D3D12_HEAP_PROPERTIES
		{
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};

		switch (heapType)
		{
		case HeapType::Default:
			properties.Type = D3D12_HEAP_TYPE_DEFAULT;
			break;
		case HeapType::Upload:
			properties.Type = D3D12_HEAP_TYPE_UPLOAD;
			break;
		case HeapType::Download:
			properties.Type = D3D12_HEAP_TYPE_READBACK;
			break;
		default: [[unlikely]]
			assert(false && "Invalid heap type.");
			properties.Type = D3D12_HEAP_TYPE_CUSTOM;
		}

		return properties;
	}
}
