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

export module PonyEngine.Render.Direct3D12:Direct3D12RenderTarget;

import <span>;
import <stdexcept>;
import <vector>;

import PonyBase.StringUtility;

import PonyMath.Core;

export namespace PonyEngine::Render
{
	class Direct3D12RenderTarget final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderTarget(ID3D12Device10* device, std::span<ID3D12Resource2*> buffers, DXGI_FORMAT rtvFormat);
		Direct3D12RenderTarget(const Direct3D12RenderTarget&) = delete;
		Direct3D12RenderTarget(Direct3D12RenderTarget&&) = delete;

		~Direct3D12RenderTarget() noexcept = default;

		[[nodiscard("Pure function")]]
		PonyMath::Core::RGBA<FLOAT>& ClearColor() noexcept;
		[[nodiscard("Pure function")]]
		const PonyMath::Core::RGBA<FLOAT>& ClearColor() const noexcept;

		[[nodiscard("Pure function")]]
		ID3D12Resource2* GetBackBuffer(UINT index) const noexcept;
		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE GetRtvHandle(UINT index) const noexcept;

		Direct3D12RenderTarget& operator =(const Direct3D12RenderTarget&) = delete;
		Direct3D12RenderTarget& operator =(Direct3D12RenderTarget&&) = delete;

	private:
		PonyMath::Core::RGBA<FLOAT> clearColor;

		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> backBuffers;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> rtvHandles;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderTarget::Direct3D12RenderTarget(ID3D12Device10* const device, const std::span<ID3D12Resource2*> buffers, const DXGI_FORMAT rtvFormat) :
		clearColor(PonyMath::Core::RGBA<FLOAT>::Predefined::Black)
	{
		backBuffers.resize(buffers.size());
		for (std::size_t i = 0; i < backBuffers.size(); ++i)
		{
			backBuffers[i] = buffers[i];
		}

		const auto rtvDescriptorHeapDescriptor = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
			.NumDescriptors = static_cast<UINT>(buffers.size()),
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
		if (const HRESULT result = device->CreateDescriptorHeap(&rtvDescriptorHeapDescriptor, IID_PPV_ARGS(rtvDescriptorHeap.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire rtv descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		rtvHandles.resize(buffers.size());
		rtvHandles[0].ptr = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr;
		const UINT rtvDescriptorHandleIncrement = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		for (std::size_t i = 1; i < rtvHandles.size(); ++i)
		{
			rtvHandles[i].ptr = rtvHandles[i - 1].ptr + rtvDescriptorHandleIncrement;
		}

		const auto rtvDescription = D3D12_RENDER_TARGET_VIEW_DESC
		{
			.Format = rtvFormat,
			.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D,
			.Texture2D = D3D12_TEX2D_RTV{}
		};
		for (std::size_t i = 0; i < buffers.size(); ++i)
		{
			device->CreateRenderTargetView(buffers[i], &rtvDescription, rtvHandles[i]);
		}
	}

	PonyMath::Core::RGBA<FLOAT>& Direct3D12RenderTarget::ClearColor() noexcept
	{
		return clearColor;
	}

	const PonyMath::Core::RGBA<FLOAT>& Direct3D12RenderTarget::ClearColor() const noexcept
	{
		return clearColor;
	}

	ID3D12Resource2* Direct3D12RenderTarget::GetBackBuffer(const UINT index) const noexcept
	{
		return backBuffers[index].Get();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Direct3D12RenderTarget::GetRtvHandle(const UINT index) const noexcept
	{
		return rtvHandles[index];
	}
}
