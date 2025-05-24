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

export module PonyEngine.Render.Direct3D12:IDescriptorHeapManager;

import <memory>;

import :DescriptorHeap;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 Descriptor heap manager.
	class IDescriptorHeapManager
	{
		INTERFACE_BODY(IDescriptorHeapManager)

		/// @brief Creates a descriptor heap.
		/// @param heapType Heap type.
		/// @param descriptorCount Descriptor count.
		/// @param shaderVisible Is the descriptor shader visible?
		/// @return Descriptor heap.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, std::uint32_t descriptorCount, bool shaderVisible) = 0;
	};
}
