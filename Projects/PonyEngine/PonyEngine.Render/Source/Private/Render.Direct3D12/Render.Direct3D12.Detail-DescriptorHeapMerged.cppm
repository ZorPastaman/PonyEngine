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

export module PonyEngine.Render.Direct3D12.Detail:DescriptorHeapMerged;

import <memory>;
import <optional>;
import <stdexcept>;
import <unordered_map>;
import <utility>;

import :DescriptorHeap;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Merged descriptor heap.
	class DescriptorHeapMerged final
	{
	public:
		/// @brief Created @p DescriptorHeapMerged.
		/// @param heap Descriptor heap. It takes the pointer.
		/// @param originalToCopyMap Original to copy map.
		[[nodiscard("Pure constructor")]]
		DescriptorHeapMerged(std::unique_ptr<DescriptorHeap>&& heap, const std::unordered_map<ID3D12DescriptorHeap*, UINT>& originalToCopyMap);
		[[nodiscard("Pure constructor")]]
		DescriptorHeapMerged(const DescriptorHeapMerged& other) = default;
		[[nodiscard("Pure constructor")]]
		DescriptorHeapMerged(DescriptorHeapMerged&& other) noexcept = default;

		~DescriptorHeapMerged() noexcept = default;

		/// @brief Gets the heap.
		/// @return Heap.
		[[nodiscard("Pure function")]]
		DescriptorHeap& Heap() noexcept;
		/// @brief Gets the heap.
		/// @return Heap.
		[[nodiscard("Pure function")]]
		const DescriptorHeap& Heap() const noexcept;

		/// @brief Gets a CPU descriptor handle.
		/// @param originalHeap Original descriptor heap.
		/// @param index Descriptor handle index.
		/// @return CPU descriptor handle.
		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(const ID3D12DescriptorHeap& originalHeap, UINT index) const;
		/// @brief Gets a GPU descriptor handle.
		/// @param originalHeap Original descriptor heap.
		/// @param index Descriptor handle index.
		/// @return GPU descriptor handle.
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle(const ID3D12DescriptorHeap& originalHeap, UINT index) const;

		DescriptorHeapMerged& operator =(const DescriptorHeapMerged& other) = default;
		DescriptorHeapMerged& operator =(DescriptorHeapMerged&& other) noexcept = default;

	private:
		/// @brief Finds the original heap index.
		/// @param originalHeap Original descriptor heap.
		/// @return Original heap index.
		[[nodiscard("Pure function")]]
		std::optional<UINT> OriginalHeapIndex(const ID3D12DescriptorHeap& originalHeap) const noexcept;

		std::unique_ptr<DescriptorHeap> heap; ///< Descriptor heap.
		std::unordered_map<ID3D12DescriptorHeap*, UINT> originalToCopyMap; ///< Original to copy map.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	DescriptorHeapMerged::DescriptorHeapMerged(std::unique_ptr<DescriptorHeap>&& heap, const std::unordered_map<ID3D12DescriptorHeap*, UINT>& originalToCopyMap) :
		heap(std::move(heap)),
		originalToCopyMap(originalToCopyMap)
	{
	}

	DescriptorHeap& DescriptorHeapMerged::Heap() noexcept
	{
		return *heap;
	}

	const DescriptorHeap& DescriptorHeapMerged::Heap() const noexcept
	{
		return *heap;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeapMerged::CpuHandle(const ID3D12DescriptorHeap& originalHeap, const UINT index) const
	{
		if (const std::optional<UINT> heapIndex = OriginalHeapIndex(originalHeap))
		{
			return heap->CpuHandle(heapIndex.value() + index);
		}

		throw std::invalid_argument("Incorrect original heap.");
	}

	D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeapMerged::GpuHandle(const ID3D12DescriptorHeap& originalHeap, const UINT index) const
	{
		if (const std::optional<UINT> heapIndex = OriginalHeapIndex(originalHeap))
		{
			return heap->GpuHandle(heapIndex.value() + index);
		}

		throw std::invalid_argument("Incorrect original heap.");
	}

	std::optional<UINT> DescriptorHeapMerged::OriginalHeapIndex(const ID3D12DescriptorHeap& originalHeap) const noexcept
	{
		for (const auto& [origHeap, heapIndex] : originalToCopyMap)
		{
			if (origHeap == &originalHeap)
			{
				return heapIndex;
			}
		}

		return std::nullopt;
	}
}
