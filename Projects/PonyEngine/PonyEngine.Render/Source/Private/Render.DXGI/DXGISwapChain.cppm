/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/DXGI/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.DXGI.Detail:DXGISwapChain;

import <cstdint>;
import <stdexcept>;
import <type_traits>;

import PonyBase.StringUtility;

import PonyMath.Utility;

import PonyDebug.Log;

import :DXGISwapChainParams;
import :IDXGISystemContext;
import :IDXGISwapChain;

export namespace PonyEngine::Render
{
	class DXGISwapChain final : public IDXGISwapChain
	{
	public:
		[[nodiscard("Pure constructor")]]
		DXGISwapChain(IDXGISystemContext& dxgiSystem, const DXGISwapChainParams& swapChainParams);
		DXGISwapChain(const DXGISwapChain&) = delete;
		[[nodiscard("Pure constructor")]]
		DXGISwapChain(DXGISwapChain&& other) noexcept = default;

		~DXGISwapChain() noexcept;

		[[nodiscard("Pure function")]]
		virtual DXGI_SAMPLE_DESC SampleDesc() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual UINT GetCurrentBackBufferIndex() const noexcept override;
		virtual HRESULT GetBackBuffer(UINT bufferIndex, ID3D12Resource2** buffer) const noexcept override;

		void SetFullscreenState(bool fullscreen);

		void Present();

		DXGISwapChain& operator =(const DXGISwapChain&) = delete;
		DXGISwapChain& operator =(DXGISwapChain&& other) noexcept = default;

	private:
		IDXGISystemContext* dxgiSystem;

		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	};
}

namespace PonyEngine::Render
{
	DXGISwapChain::DXGISwapChain(IDXGISystemContext& dxgiSystem, const DXGISwapChainParams& swapChainParams) :
		dxgiSystem{&dxgiSystem}
	{
		IUnknown* device = &this->dxgiSystem->Device();
		PONY_LOG(this->dxgiSystem->Logger(), PonyDebug::Log::LogType::Info, "Acquire swap chain for '0x{:X}' device and '0x{:X}' window. Resolution: '{}'; RTV format: {}; Buffer count : {}.",
			reinterpret_cast<std::uintptr_t>(device), reinterpret_cast<std::uintptr_t>(swapChainParams.hWnd), swapChainParams.resolution.ToString(), static_cast<int>(swapChainParams.rtvFormat), swapChainParams.bufferCount);
		const auto swapChainDescription = DXGI_SWAP_CHAIN_DESC1
		{
			.Width = swapChainParams.resolution.Width(),
			.Height = swapChainParams.resolution.Height(),
			.Format = swapChainParams.rtvFormat,
			.Stereo = false,
			.SampleDesc = SampleDesc(),
			.BufferUsage = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT,
			.BufferCount = swapChainParams.bufferCount,
			.Scaling = DXGI_SCALING_STRETCH,
			.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
			.AlphaMode = DXGI_ALPHA_MODE_IGNORE,
			.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING
		};
		Microsoft::WRL::ComPtr<IDXGISwapChain1> acquiredSwapChain;
		if (const HRESULT result = this->dxgiSystem->Factory().CreateSwapChainForHwnd(device, swapChainParams.hWnd, &swapChainDescription, nullptr, nullptr, acquiredSwapChain.GetAddressOf()); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire swap chain with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (const HRESULT result = acquiredSwapChain->QueryInterface(swapChain.GetAddressOf()); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to query swap chain with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->dxgiSystem->Logger(), PonyDebug::Log::LogType::Info, "Swap chain acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(swapChain.Get()));
	}

	DXGISwapChain::~DXGISwapChain() noexcept
	{
		PONY_LOG(dxgiSystem->Logger(), PonyDebug::Log::LogType::Info, "Release swap chain.");
		swapChain.Reset();
		PONY_LOG(dxgiSystem->Logger(), PonyDebug::Log::LogType::Info, "Swap chain released.");
	}

	DXGI_SAMPLE_DESC DXGISwapChain::SampleDesc() const noexcept
	{
		return DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u};
	}

	UINT DXGISwapChain::GetCurrentBackBufferIndex() const noexcept
	{
		return swapChain->GetCurrentBackBufferIndex();
	}

	HRESULT DXGISwapChain::GetBackBuffer(const UINT bufferIndex, ID3D12Resource2** const buffer) const noexcept
	{
		return swapChain->GetBuffer(bufferIndex, IID_PPV_ARGS(buffer));
	}

	void DXGISwapChain::SetFullscreenState(const bool fullscreen)
	{
		if (const HRESULT result = swapChain->SetFullscreenState(fullscreen, nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set fullscreen state with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void DXGISwapChain::Present()
	{
		if (const HRESULT result = swapChain->Present(1, 0); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to present swap chain with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
