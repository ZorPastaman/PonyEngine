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
	class DescriptorHeap final
	{
	public:
		[[nodiscard("Pure constructor")]]
		DescriptorHeap(ID3D12DescriptorHeap& descriptorHeap, UINT handleIncrement, bool shaderVisible) noexcept;
		[[nodiscard("Pure constructor")]]
		DescriptorHeap(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, UINT handleIncrement, bool shaderVisible) noexcept;
		DescriptorHeap(const DescriptorHeap&) = delete;
		DescriptorHeap(DescriptorHeap&&) = delete;

		~DescriptorHeap() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& GetDescriptorHeap() const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(UINT index) const noexcept;
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle(UINT index) const noexcept;

		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		void Name(std::string_view name);

		DescriptorHeap& operator =(const DescriptorHeap&) = delete;
		DescriptorHeap& operator =(DescriptorHeap&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12DescriptorHeap> descriptorHeap;
		SIZE_T cpuStart;
		SIZE_T gpuStart;
		SIZE_T handleIncrement;

		std::string name;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	DescriptorHeap::DescriptorHeap(ID3D12DescriptorHeap& descriptorHeap, const UINT handleIncrement, const bool shaderVisible) noexcept :
		descriptorHeap(&descriptorHeap),
		cpuStart{this->descriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr},
		gpuStart{shaderVisible ? this->descriptorHeap->GetGPUDescriptorHandleForHeapStart().ptr : 0},
		handleIncrement{handleIncrement}
	{
	}

	DescriptorHeap::DescriptorHeap(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, const UINT handleIncrement, const bool shaderVisible) noexcept :
		descriptorHeap(std::move(descriptorHeap)),
		cpuStart{this->descriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr},
		gpuStart{shaderVisible ? this->descriptorHeap->GetGPUDescriptorHandleForHeapStart().ptr : 0},
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
