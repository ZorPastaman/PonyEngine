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

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:DescriptorHeapManager;

import <cstddef>;
import <type_traits>;

import PonyBase.Utility;

import :DescriptorHeap;
import :IDescriptorHeapManager;
import :ISubSystemContext;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Descriptor heap manager.
	class DescriptorHeapManager final : public IDescriptorHeapManager
	{
	public:
		/// @brief Creates a @p DescriptorHeapManager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit DescriptorHeapManager(ISubSystemContext& d3d12System) noexcept;
		[[nodiscard("Pure constructor")]]
		DescriptorHeapManager(const DescriptorHeapManager& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		DescriptorHeapManager(DescriptorHeapManager&& other) noexcept = default;

		~DescriptorHeapManager() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::unique_ptr<DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT descriptorCount, D3D12_DESCRIPTOR_HEAP_FLAGS heapFlags) const override;
		[[nodiscard("Pure function")]]
		virtual std::unique_ptr<DescriptorHeapMerged> CreateDescriptorHeapMerged(std::span<ID3D12DescriptorHeap*> heaps, D3D12_DESCRIPTOR_HEAP_FLAGS heapFlags) const override;

		DescriptorHeapManager& operator =(const DescriptorHeapManager& other) noexcept = default;
		DescriptorHeapManager& operator =(DescriptorHeapManager&& other) noexcept = default;

	private:
		ISubSystemContext* d3d12System; ///< Direct3D12 system context.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	DescriptorHeapManager::DescriptorHeapManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::unique_ptr<DescriptorHeap> DescriptorHeapManager::CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_TYPE heapType, const UINT descriptorCount, const D3D12_DESCRIPTOR_HEAP_FLAGS heapFlags) const
	{
		ID3D12Device10& device = d3d12System->Device();
		const auto heapDescriptor = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = heapType,
			.NumDescriptors = descriptorCount,
			.Flags = heapFlags,
			.NodeMask = 0u
		};
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap;
		if (const HRESULT result = device.CreateDescriptorHeap(&heapDescriptor, IID_PPV_ARGS(heap.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return std::make_unique<DescriptorHeap>(*heap.Get(), device.GetDescriptorHandleIncrementSize(heapType));
	}

	std::unique_ptr<DescriptorHeapMerged> DescriptorHeapManager::CreateDescriptorHeapMerged(const std::span<ID3D12DescriptorHeap*> heaps, const D3D12_DESCRIPTOR_HEAP_FLAGS heapFlags) const
	{
		if (heaps.size() == 0)
		{
			throw std::invalid_argument("Heaps span is empty.");
		}

#if _DEBUG
		for (std::size_t i = 1; i < heaps.size(); ++i)
		{
			assert(heaps[0]->GetDesc().Type == heaps[i]->GetDesc().Type && "The heaps must have the same type.");
		}
#endif

		UINT totalDescriptorCount = 0u;
		std::unordered_map<ID3D12DescriptorHeap*, UINT> originalToCopyMap;
		for (ID3D12DescriptorHeap* const heap : heaps)
		{
			originalToCopyMap[heap] = totalDescriptorCount;
			totalDescriptorCount += heap->GetDesc().NumDescriptors;
		}
		const D3D12_DESCRIPTOR_HEAP_TYPE heapType = heaps[0]->GetDesc().Type;
		auto mergedHeap = std::make_unique<DescriptorHeapMerged>(CreateDescriptorHeap(heapType, totalDescriptorCount, heapFlags), originalToCopyMap);

		ID3D12Device10& device = d3d12System->Device();
		const UINT handleIncrement = device.GetDescriptorHandleIncrementSize(heapType);
		D3D12_CPU_DESCRIPTOR_HANDLE dest = mergedHeap->Heap().CpuHandle(0u);
		for (ID3D12DescriptorHeap* const heap : heaps)
		{
			const UINT currentDescriptorCount = heap->GetDesc().NumDescriptors;
			device.CopyDescriptorsSimple(currentDescriptorCount, dest, heap->GetCPUDescriptorHandleForHeapStart(), heapType);
			dest.ptr += handleIncrement * currentDescriptorCount;
		}

		return mergedHeap;
	}
}
