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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12RenderTarget;

import <cstdint>;
import <span>;
import <stdexcept>;
import <vector>;

import PonyBase.StringUtility;

import PonyMath.Color;
import PonyMath.Utility;

import PonyEngine.Render.Direct3D12;

import :Direct3D12RenderTargetParams;
import :IDirect3D12SystemContext;
import :IDirect3D12RenderTargetPrivate;

export namespace PonyEngine::Render
{
	class Direct3D12RenderTarget final : public IDirect3D12RenderTargetPrivate
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderTarget(IDirect3D12SystemContext& d3d12System, const Direct3D12RenderTargetParams& params);
		Direct3D12RenderTarget(const Direct3D12RenderTarget&) = delete;
		Direct3D12RenderTarget(Direct3D12RenderTarget&&) = delete;

		~Direct3D12RenderTarget() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<std::uint32_t> Resolution() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Color::RGBA<float> ClearColor() const noexcept override;
		virtual void ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Utility::Resolution<UINT>& ResolutionD3D12() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Color::RGBA<FLOAT>& ClearColorD3D12() const noexcept override;
		virtual void ClearColorD3D12(const PonyMath::Color::RGBA<FLOAT>& color) noexcept override;

		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT RtvFormat() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual DXGI_SAMPLE_DESC SampleDesc() const noexcept override;

		[[nodiscard("Pure function")]]
		UINT CurrentBackBufferIndex() const noexcept;
		void CurrentBackBufferIndex(UINT index) noexcept;

		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& CurrentBackBuffer() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& CurrentBackBuffer() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE CurrentRtvHandle() const noexcept override;

		Direct3D12RenderTarget& operator =(const Direct3D12RenderTarget&) = delete;
		Direct3D12RenderTarget& operator =(Direct3D12RenderTarget&&) = delete;

	private:
		DXGI_FORMAT rtvFormat;
		DXGI_SAMPLE_DESC sampleDesc;

		PonyMath::Utility::Resolution<UINT> resolution;
		PonyMath::Color::RGBA<FLOAT> clearColor;

		UINT currentBackBufferIndex;

		IDirect3D12SystemContext* d3d12System;

		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> backBuffers;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> rtvHandles;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderTarget::Direct3D12RenderTarget(IDirect3D12SystemContext& d3d12System, const Direct3D12RenderTargetParams& params) :
		rtvFormat{params.rtvFormat},
		sampleDesc{params.sampleDesc},
		resolution(params.resolution),
		clearColor(params.clearColor),
		currentBackBufferIndex{0u},
		d3d12System{&d3d12System}
	{
		backBuffers.resize(params.backBuffers.size());
		for (std::size_t i = 0; i < backBuffers.size(); ++i)
		{
			backBuffers[i] = params.backBuffers[i];
		}

		const auto rtvDescriptorHeapDescriptor = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
			.NumDescriptors = static_cast<UINT>(backBuffers.size()),
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
		ID3D12Device10& device = d3d12System.Device();
		if (const HRESULT result = device.CreateDescriptorHeap(&rtvDescriptorHeapDescriptor, IID_PPV_ARGS(rtvDescriptorHeap.ReleaseAndGetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire rtv descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		rtvHandles.resize(backBuffers.size());
		rtvHandles[0].ptr = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr;
		const UINT rtvDescriptorHandleIncrement = device.GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
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
		for (std::size_t i = 0; i < backBuffers.size(); ++i)
		{
			device.CreateRenderTargetView(backBuffers[i].Get(), &rtvDescription, rtvHandles[i]);
		}
	}

	PonyMath::Utility::Resolution<std::uint32_t> Direct3D12RenderTarget::Resolution() const noexcept
	{
		return static_cast<PonyMath::Utility::Resolution<std::uint32_t>>(ResolutionD3D12());
	}

	PonyMath::Color::RGBA<float> Direct3D12RenderTarget::ClearColor() const noexcept
	{
		return static_cast<PonyMath::Color::RGBA<float>>(ClearColorD3D12());
	}

	void Direct3D12RenderTarget::ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept
	{
		ClearColorD3D12(static_cast<PonyMath::Color::RGBA<FLOAT>>(color));
	}

	const PonyMath::Utility::Resolution<UINT>& Direct3D12RenderTarget::ResolutionD3D12() const noexcept
	{
		return resolution;
	}

	const PonyMath::Color::RGBA<FLOAT>& Direct3D12RenderTarget::ClearColorD3D12() const noexcept
	{
		return clearColor;
	}

	void Direct3D12RenderTarget::ClearColorD3D12(const PonyMath::Color::RGBA<FLOAT>& color) noexcept
	{
		clearColor = color;
	}

	DXGI_FORMAT Direct3D12RenderTarget::RtvFormat() const noexcept
	{
		return rtvFormat;
	}

	DXGI_SAMPLE_DESC Direct3D12RenderTarget::SampleDesc() const noexcept
	{
		return sampleDesc;
	}

	UINT Direct3D12RenderTarget::CurrentBackBufferIndex() const noexcept
	{
		return currentBackBufferIndex;
	}

	void Direct3D12RenderTarget::CurrentBackBufferIndex(const UINT index) noexcept
	{
		currentBackBufferIndex = index;
	}

	ID3D12Resource2& Direct3D12RenderTarget::CurrentBackBuffer() noexcept
	{
		return *backBuffers[currentBackBufferIndex].Get();
	}

	const ID3D12Resource2& Direct3D12RenderTarget::CurrentBackBuffer() const noexcept
	{
		return *backBuffers[currentBackBufferIndex].Get();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Direct3D12RenderTarget::CurrentRtvHandle() const noexcept
	{
		return rtvHandles[currentBackBufferIndex];
	}
}
