/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Render/Windows/DXGIFramework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:DXGISwapChain;

import std;

import PonyEngine.Log;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice.Ext;

export namespace PonyEngine::Render::Windows
{
	class DXGISwapChain final
	{
	public:
		[[nodiscard("Pure constructor")]]
		DXGISwapChain(IRenderDeviceContext& renderDevice, IDXGIFactory7& factory, IUnknown& device, HWND windowHandle, const DXGI_SWAP_CHAIN_DESC1& swapChainDesc);
		DXGISwapChain(const DXGISwapChain&) = delete;
		DXGISwapChain(DXGISwapChain&&) = delete;

		~DXGISwapChain() noexcept;

		[[nodiscard("Pure function")]]
		UINT GetCurrentBufferIndex() const noexcept;
		template<std::derived_from<IUnknown> T> [[nodiscard("Pure function")]]
		void GetBuffer(UINT index, Platform::Windows::ComPtr<T>& resource) const;

		void SetFullscreenState(BOOL fullscreen);

		void Present(UINT syncInterval, UINT flags);

		DXGISwapChain& operator =(const DXGISwapChain&) = delete;
		DXGISwapChain& operator =(DXGISwapChain&&) = delete;

	private:
		IRenderDeviceContext* renderDevice;

		Platform::Windows::ComPtr<IDXGISwapChain4> swapChain;
	};
}

namespace PonyEngine::Render::Windows
{
	DXGISwapChain::DXGISwapChain(IRenderDeviceContext& renderDevice, IDXGIFactory7& factory, IUnknown& device, const HWND windowHandle, 
		const DXGI_SWAP_CHAIN_DESC1& swapChainDesc) :
		renderDevice{&renderDevice}
	{
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring dxgi swap chain... Window handle: '0x{:X}'; Width: '{}'; Height: '{}'.", 
			reinterpret_cast<std::uintptr_t>(windowHandle), swapChainDesc.Width, swapChainDesc.Height);
		Platform::Windows::ComPtr<IDXGISwapChain1> swapChainTemp;
		if (const HRESULT result = factory.CreateSwapChainForHwnd(&device, windowHandle, &swapChainDesc, nullptr, nullptr, 
			swapChainTemp.GetAddress()); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to acquire DXGI swap chain: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (const HRESULT result = swapChainTemp->QueryInterface(IID_PPV_ARGS(swapChain.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to cast DXGI swap chain interface: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring dxgi swap chain done.");
	}

	DXGISwapChain::~DXGISwapChain() noexcept
	{
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Releasing dxgi swap chain...");
		swapChain.Reset();
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Releasing dxgi swap chain done.");
	}

	UINT DXGISwapChain::GetCurrentBufferIndex() const noexcept
	{
		return swapChain->GetCurrentBackBufferIndex();
	}

	template<std::derived_from<IUnknown> T>
	void DXGISwapChain::GetBuffer(const UINT index, Platform::Windows::ComPtr<T>& resource) const
	{
		if (const HRESULT result = swapChain->GetBuffer(index, IID_PPV_ARGS(resource.ReleaseAndGetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get swap chain buffer: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void DXGISwapChain::SetFullscreenState(const BOOL fullscreen)
	{
		if (const HRESULT result = swapChain->SetFullscreenState(fullscreen, nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set fullscreen state: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void DXGISwapChain::Present(const UINT syncInterval, const UINT flags)
	{
		if (const HRESULT result = swapChain->Present(syncInterval, flags); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to present: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
