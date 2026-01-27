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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12DescriptorHeap;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :D3D12ObjectUtility;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12DescriptorHeap final
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12DescriptorHeap(ID3D12DescriptorHeap& descriptorHeap, UINT handleIncrement) noexcept;
		[[nodiscard("Pure constructor")]]
		D3D12DescriptorHeap(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, UINT handleIncrement) noexcept;
		D3D12DescriptorHeap(const D3D12DescriptorHeap&) = delete;
		D3D12DescriptorHeap(D3D12DescriptorHeap&&) = delete;

		~D3D12DescriptorHeap() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& DescriptorHeap() const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(UINT index) const noexcept;
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle(UINT index) const noexcept;

		void SetName(std::string_view name);

		D3D12DescriptorHeap& operator =(const D3D12DescriptorHeap&) = delete;
		D3D12DescriptorHeap& operator =(D3D12DescriptorHeap&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12DescriptorHeap> descriptorHeap;
		SIZE_T handleIncrement;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12DescriptorHeap::D3D12DescriptorHeap(ID3D12DescriptorHeap& descriptorHeap, const UINT handleIncrement) noexcept :
		descriptorHeap(&descriptorHeap),
		handleIncrement{handleIncrement}
	{
	}

	D3D12DescriptorHeap::D3D12DescriptorHeap(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, const UINT handleIncrement) noexcept :
		descriptorHeap(std::move(descriptorHeap)),
		handleIncrement{handleIncrement}
	{
		assert(this->descriptorHeap && "The descriptor heap is nullptr.");
	}

	ID3D12DescriptorHeap& D3D12DescriptorHeap::DescriptorHeap() const noexcept
	{
		return *descriptorHeap;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::CpuHandle(const UINT index) const noexcept
	{
		return D3D12_CPU_DESCRIPTOR_HANDLE{descriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr + index * handleIncrement};
	}

	D3D12_GPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GpuHandle(const UINT index) const noexcept
	{
		return D3D12_GPU_DESCRIPTOR_HANDLE{descriptorHeap->GetGPUDescriptorHandleForHeapStart().ptr + index * handleIncrement};
	}

	void D3D12DescriptorHeap::SetName(const std::string_view name)
	{
		SetObjectName(*descriptorHeap, name);
	}
}
