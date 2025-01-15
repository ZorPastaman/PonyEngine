/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.Direct3D12.Detail:IDescriptorHeapManager;

import <memory>;
import <span>;

import :DescriptorHeap;
import :DescriptorHeapMerged;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Descriptor heap manager.
	class IDescriptorHeapManager
	{
		INTERFACE_BODY(IDescriptorHeapManager)

		/// @brief Creates a descriptor heap.
		/// @param heapType Heap type.
		/// @param descriptorCount Descriptor count.
		/// @param heapFlags Heap flags.
		/// @return Descriptor heap.
		[[nodiscard("Pure function")]]
		virtual std::unique_ptr<DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT descriptorCount, D3D12_DESCRIPTOR_HEAP_FLAGS heapFlags) const = 0;
		/// @brief Creates a merged descriptor heap.
		/// @param heaps Heaps to merge.
		/// @param heapFlags Heap flags.
		/// @return Descriptor heap.
		[[nodiscard("Pure function")]]
		virtual std::unique_ptr<DescriptorHeapMerged> CreateDescriptorHeapMerged(std::span<ID3D12DescriptorHeap*> heaps, D3D12_DESCRIPTOR_HEAP_FLAGS heapFlags) const = 0;
	};
}
