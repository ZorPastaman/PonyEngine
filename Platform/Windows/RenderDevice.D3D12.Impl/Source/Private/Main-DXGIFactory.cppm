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
#include "PonyEngine/RenderDevice/Windows/DXGIFramework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:DXGIFactory;

import std;

import PonyEngine.Log;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice.Ext;

import :DXGISwapChain;

export namespace PonyEngine::RenderDevice::Windows
{
	class DXGIFactory final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit DXGIFactory(IRenderDeviceContext& renderDevice);
		DXGIFactory(const DXGIFactory&) = delete;
		DXGIFactory(DXGIFactory&&) = delete;

		~DXGIFactory() noexcept;

		[[nodiscard("Pure function")]]
		BOOL GetTearingSupport() const;

		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<IDXGISwapChain4> CreateSwapChain(IUnknown& device, HWND windowHandle, const DXGI_SWAP_CHAIN_DESC1& swapChainDesc);
		void MakeWindowAssociation(HWND windowHandle);

		DXGIFactory& operator =(const DXGIFactory&) = delete;
		DXGIFactory& operator =(DXGIFactory&&) = delete;

	private:
		IRenderDeviceContext* renderDevice;

#ifndef NDEBUG
		Platform::Windows::ComPtr<IDXGIDebug1> debug; ///< DXGI debug.
#endif
		Platform::Windows::ComPtr<IDXGIFactory7> factory; ///< DXGI factory.
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	DXGIFactory::DXGIFactory(IRenderDeviceContext& renderDevice) :
		renderDevice{&renderDevice}
	{
#ifndef NDEBUG
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring DXGI debug interface...");
		if (const HRESULT result = DXGIGetDebugInterface1(0, IID_PPV_ARGS(debug.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to acquire DXGI debug interface: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring DXGI debug interface done.");

		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Debug, "Enabling DXGI leak tracking.");
		debug->EnableLeakTrackingForThread();
#endif

		UINT factoryFlags = 0;
#ifndef NDEBUG
		factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif

		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring DXGI factory... Factory flags: '0x{:X}'.", factoryFlags);
		if (const HRESULT result = CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(factory.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to acquire DXGI factory: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring DXGI factory done.");
	}

	DXGIFactory::~DXGIFactory() noexcept
	{
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Releasing DXGI factory...");
		factory.Reset();
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Releasing DXGI factory done.");

#ifndef NDEBUG
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Reporting DXGI live objects...");
		if (const HRESULT result = debug->ReportLiveObjects(DXGI_DEBUG_ALL, static_cast<DXGI_DEBUG_RLO_FLAGS>(DXGI_DEBUG_RLO_DETAIL | DXGI_DEBUG_RLO_IGNORE_INTERNAL)); FAILED(result)) [[unlikely]]
		{
			PONY_LOG(renderDevice->Logger(), Log::LogType::Error, "Failed to report live objects. Result: '0x{:X}'.", static_cast<std::make_unsigned_t<HRESULT>>(result));
		}
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Reporting DXGI live objects done.");

		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Releasing DXGI debug interface...");
		debug.Reset();
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Releasing DXGI debug interface done.");
#endif
	}

	BOOL DXGIFactory::GetTearingSupport() const
	{
		BOOL tearingSupport;
		if (const HRESULT result = factory->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &tearingSupport, sizeof(tearingSupport)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to check tearing support: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return tearingSupport;
	}

	Platform::Windows::ComPtr<IDXGISwapChain4> DXGIFactory::CreateSwapChain(IUnknown& device, const HWND windowHandle, const DXGI_SWAP_CHAIN_DESC1& swapChainDesc)
	{
		Platform::Windows::ComPtr<IDXGISwapChain1> swapChain;
		if (const HRESULT result = factory->CreateSwapChainForHwnd(&device, windowHandle, &swapChainDesc, nullptr, nullptr,
			swapChain.GetAddress()); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to acquire DXGI swap chain: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		Platform::Windows::ComPtr<IDXGISwapChain4> modernSwapChain;
		if (const HRESULT result = swapChain->QueryInterface(IID_PPV_ARGS(modernSwapChain.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to cast DXGI swap chain interface: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return modernSwapChain;
	}

	void DXGIFactory::MakeWindowAssociation(const HWND windowHandle)
	{
		if (const HRESULT result = factory->MakeWindowAssociation(windowHandle, DXGI_MWA_NO_WINDOW_CHANGES); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to make window association: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
