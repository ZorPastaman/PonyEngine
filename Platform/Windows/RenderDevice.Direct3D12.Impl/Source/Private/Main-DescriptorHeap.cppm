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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:DescriptorHeap;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :ObjectUtility;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Descriptor heap wrapper.
	class DescriptorHeap final
	{
	public:
		/// @brief Creates a descriptor heap wrapper.
		/// @param descriptorHeap Descriptor heap.
		/// @param handleIncrement Descriptor handle increment.
		/// @param shaderVisible Is it shader visible?
		[[nodiscard("Pure constructor")]]
		DescriptorHeap(ID3D12DescriptorHeap& descriptorHeap, UINT handleIncrement, bool shaderVisible) noexcept;
		/// @brief Creates a descriptor heap wrapper.
		/// @param descriptorHeap Descriptor heap.
		/// @param handleIncrement Descriptor handle increment.
		/// @param shaderVisible Is it shader visible?
		[[nodiscard("Pure constructor")]]
		DescriptorHeap(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, UINT handleIncrement, bool shaderVisible) noexcept;
		DescriptorHeap(const DescriptorHeap&) = delete;
		DescriptorHeap(DescriptorHeap&&) = delete;

		~DescriptorHeap() noexcept = default;

		/// @brief Gets the descriptor heap.
		/// @return Descriptor heap.
		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& GetDescriptorHeap() const noexcept;

		/// @brief Gets a CPU descriptor handle.
		/// @param index Descriptor handle index.
		/// @return CPU descriptor handle.
		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(UINT index) const noexcept;
		/// @brief Gets a GPU descriptor handle.
		/// @param index Descriptor handle index.
		/// @return GPU descriptor handle.
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle(UINT index) const noexcept;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string_view name);

		DescriptorHeap& operator =(const DescriptorHeap&) = delete;
		DescriptorHeap& operator =(DescriptorHeap&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12DescriptorHeap> descriptorHeap; ///< Descriptor heap.
		SIZE_T cpuStart; ///< CPU descriptor handle start.
		SIZE_T gpuStart; ///< GPU descriptor handle start.
		SIZE_T handleIncrement; ///< Descriptor handle increment.

		std::string name; ///< Name.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	DescriptorHeap::DescriptorHeap(ID3D12DescriptorHeap& descriptorHeap, const UINT handleIncrement, const bool shaderVisible) noexcept :
		descriptorHeap(&descriptorHeap),
		cpuStart{this->descriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr},
		gpuStart{shaderVisible ? this->descriptorHeap->GetGPUDescriptorHandleForHeapStart().ptr : std::numeric_limits<SIZE_T>::max()},
		handleIncrement{handleIncrement}
	{
	}

	DescriptorHeap::DescriptorHeap(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, const UINT handleIncrement, const bool shaderVisible) noexcept :
		descriptorHeap(std::move(descriptorHeap)),
		cpuStart{this->descriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr},
		gpuStart{shaderVisible ? this->descriptorHeap->GetGPUDescriptorHandleForHeapStart().ptr : std::numeric_limits<SIZE_T>::max()},
		handleIncrement{handleIncrement}
	{
		assert(this->descriptorHeap && "The descriptor heap is nullptr.");
	}

	ID3D12DescriptorHeap& DescriptorHeap::GetDescriptorHeap() const noexcept
	{
		return *descriptorHeap;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::CpuHandle(const UINT index) const noexcept
	{
		return D3D12_CPU_DESCRIPTOR_HANDLE{.ptr = cpuStart + index * handleIncrement};
	}

	D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::GpuHandle(const UINT index) const noexcept
	{
		assert(gpuStart != std::numeric_limits<SIZE_T>::max() && "Not shader visible descriptor heap.");
		return D3D12_GPU_DESCRIPTOR_HANDLE{.ptr = gpuStart + index * handleIncrement};
	}

	std::string_view DescriptorHeap::Name() const noexcept
	{
		return name;
	}

	void DescriptorHeap::Name(const std::string_view name)
	{
		SetObjectName(*descriptorHeap, name);

		try
		{
			this->name = name;
		}
		catch (...)
		{
			SetObjectName(*descriptorHeap, this->name);
			throw;
		}
	}
}
