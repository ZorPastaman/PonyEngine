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

export module PonyEngine.Render.Direct3D12.Detail:DescriptorHeap;

import <cstdint>;
import <string_view>;

import :ObjectUtility;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Descriptor heap.
	class DescriptorHeap final
	{
	public:
		/// @brief Creates @p DescriptorHeap.
		/// @param heap Descriptor heap.
		/// @param handleIncrement Descriptor handle increment.
		[[nodiscard("Pure constructor")]]
		DescriptorHeap(ID3D12DescriptorHeap& heap, std::uint32_t handleIncrement) noexcept;
		[[nodiscard("Pure constructor")]]
		DescriptorHeap(const DescriptorHeap& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		DescriptorHeap(DescriptorHeap&& other) noexcept = default;

		~DescriptorHeap() noexcept = default;

		/// @brief Gets the descriptor heap.
		/// @return Descriptor heap.
		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& Heap() noexcept;
		/// @brief Gets the descriptor heap.
		/// @return Descriptor heap.
		[[nodiscard("Pure function")]]
		const ID3D12DescriptorHeap& Heap() const noexcept;

		/// @brief Gets the descriptor handle increment.
		/// @return Descriptor handle increment.
		[[nodiscard("Pure function")]]
		std::uint32_t HandleIncrement() const noexcept;
		/// @brief Gets the descriptor handle count.
		/// @return Descriptor handle count.
		[[nodiscard("Pure function")]]
		std::uint32_t HandleCount() const noexcept;

		/// @brief Gets a CPU descriptor handle.
		/// @param index Descriptor handle index.
		/// @return CPU descriptor handle.
		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(std::uint32_t index) const noexcept;
		/// @brief Gets a GPU descriptor handle.
		/// @param index Descriptor handle index.
		/// @return GPU descriptor handle.
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle(std::uint32_t index) const noexcept;

		/// @brief Gets an index of the handle.
		/// @param cpuHandle CPU handle.
		/// @return Index.
		[[nodiscard("Pure function")]]
		std::uint32_t Index(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle) const noexcept;
		/// @brief Gets an index of the handle.
		/// @param gpuHandle GPU handle.
		/// @return Index.
		[[nodiscard("Pure function")]]
		std::uint32_t Index(D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle) const noexcept;

		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string_view name);

		DescriptorHeap& operator =(const DescriptorHeap& other) noexcept = default;
		DescriptorHeap& operator =(DescriptorHeap&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap; ///< Descriptor heap.
		std::uint32_t handleIncrement; ///< Descriptor handle increment.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	DescriptorHeap::DescriptorHeap(ID3D12DescriptorHeap& heap, const std::uint32_t handleIncrement) noexcept :
		heap(&heap),
		handleIncrement{handleIncrement}
	{
	}

	ID3D12DescriptorHeap& DescriptorHeap::Heap() noexcept
	{
		return *heap.Get();
	}

	const ID3D12DescriptorHeap& DescriptorHeap::Heap() const noexcept
	{
		return *heap.Get();
	}

	std::uint32_t DescriptorHeap::HandleIncrement() const noexcept
	{
		return handleIncrement;
	}

	std::uint32_t DescriptorHeap::HandleCount() const noexcept
	{
		return heap->GetDesc().NumDescriptors;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::CpuHandle(const std::uint32_t index) const noexcept
	{
		return D3D12_CPU_DESCRIPTOR_HANDLE{.ptr = heap->GetCPUDescriptorHandleForHeapStart().ptr + static_cast<SIZE_T>(handleIncrement) * index};
	}

	D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::GpuHandle(const std::uint32_t index) const noexcept
	{
		return D3D12_GPU_DESCRIPTOR_HANDLE{.ptr = heap->GetGPUDescriptorHandleForHeapStart().ptr + static_cast<SIZE_T>(handleIncrement) * index};
	}

	std::uint32_t DescriptorHeap::Index(const D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle) const noexcept
	{
		return static_cast<std::uint32_t>((cpuHandle.ptr - heap->GetCPUDescriptorHandleForHeapStart().ptr) / handleIncrement);
	}

	std::uint32_t DescriptorHeap::Index(const D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle) const noexcept
	{
		return static_cast<std::uint32_t>((gpuHandle.ptr - heap->GetGPUDescriptorHandleForHeapStart().ptr) / handleIncrement);
	}

	void DescriptorHeap::Name(const std::string_view name)
	{
		SetName(*heap.Get(), name);
	}
}
