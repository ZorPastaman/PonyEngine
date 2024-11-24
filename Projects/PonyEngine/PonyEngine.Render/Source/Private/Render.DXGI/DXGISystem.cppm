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

#include "PonyBase/Core/DXGI/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.DXGI.Detail:DXGISystem;

import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import :DXGISwapChain;
import :IDXGIRenderSystemContext;
import :IDXGISystemContext;

export namespace PonyEngine::Render
{
	class DXGISystem final : private IDXGISystemContext
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit DXGISystem(IDXGIRenderSystemContext& renderSystem);
		DXGISystem(const DXGISystem&) = delete;
		[[nodiscard("Pure constructor")]]
		DXGISystem(DXGISystem&& other) noexcept = default;

		~DXGISystem() noexcept;

		[[nodiscard("Pure function")]]
		IDXGISwapChain* SwapChain() noexcept;
		[[nodiscard("Pure function")]]
		const IDXGISwapChain* SwapChain() const noexcept;
		IDXGISwapChain& CreateSwapChain(const DXGISwapChainParams& swapChainParams);

		void Present();

		DXGISystem& operator =(const DXGISystem&) = delete;
		DXGISystem& operator =(DXGISystem&& other) noexcept = default;

	private:
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDXGIFactory7& Factory() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDXGIFactory7& Factory() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IUnknown& Device() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IUnknown& Device() const noexcept override;

		IDXGIRenderSystemContext* renderSystem;

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<IDXGIDebug1> debug;
#endif
		Microsoft::WRL::ComPtr<IDXGIFactory7> factory;

		std::unique_ptr<DXGISwapChain> swapChain;
	};
}

namespace PonyEngine::Render
{
	DXGISystem::DXGISystem(IDXGIRenderSystemContext& renderSystem) :
		renderSystem{&renderSystem}
	{
#ifdef _DEBUG
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Acquire DXGI debug interface.");
		if (const HRESULT result = DXGIGetDebugInterface1(0, IID_PPV_ARGS(debug.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire DXGI debug interface with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "DXGI debug interface acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(debug.Get()));

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Enable DXGI leak tracking.");
		debug->EnableLeakTrackingForThread();
#endif

		UINT factoryFlags = 0;
#ifdef _DEBUG
		factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Acquire DXGI factory. Factory flags: '0x{:X}'.", factoryFlags);
		if (const HRESULT result = CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(factory.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire DXGI factory with '0x{:X} result.'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "DXGI factory acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(factory.Get()));
	}

	DXGISystem::~DXGISystem() noexcept
	{
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy swap chain.");
		swapChain.reset();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Swap chain destroyed.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Release DXGI factory.");
		factory.Reset();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "DXGI factory released.");

#ifdef _DEBUG
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Report DXGI live objects.");
		if (const HRESULT result = debug->ReportLiveObjects(DXGI_DEBUG_ALL, static_cast<DXGI_DEBUG_RLO_FLAGS>(DXGI_DEBUG_RLO_DETAIL | DXGI_DEBUG_RLO_IGNORE_INTERNAL)); FAILED(result)) [[unlikely]]
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Error, "Failed to report live objects with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result));
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "DXGI live objects reported.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Release DXGI debug interface.");
		debug.Reset();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "DXGI debug interface released.");
#endif
	}

	IDXGISwapChain* DXGISystem::SwapChain() noexcept
	{
		return swapChain.get();
	}

	const IDXGISwapChain* DXGISystem::SwapChain() const noexcept
	{
		return swapChain.get();
	}

	IDXGISwapChain& DXGISystem::CreateSwapChain(const DXGISwapChainParams& swapChainParams)
	{
		assert(!swapChain && "The swap chain has already been created.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create swap chain.");
		swapChain = std::make_unique<DXGISwapChain>(*static_cast<IDXGISystemContext*>(this), swapChainParams);
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Swap chain created.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Set windowed mode.");
		if (const HRESULT result = factory->MakeWindowAssociation(swapChainParams.hWnd, DXGI_MWA_NO_ALT_ENTER); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to make window association with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		swapChain->SetFullscreenState(false);
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Windowed mode set.");

		return *swapChain;
	}

	void DXGISystem::Present()
	{
		assert(swapChain && "The swap chain is nullptr.");
		swapChain->Present();
	}

	PonyDebug::Log::ILogger& DXGISystem::Logger() noexcept
	{
		return renderSystem->Logger();
	}

	const PonyDebug::Log::ILogger& DXGISystem::Logger() const noexcept
	{
		return renderSystem->Logger();
	}

	IDXGIFactory7& DXGISystem::Factory() noexcept
	{
		return *factory.Get();
	}

	const IDXGIFactory7& DXGISystem::Factory() const noexcept
	{
		return *factory.Get();
	}

	IUnknown& DXGISystem::Device() noexcept
	{
		assert(renderSystem->Device() && "The render system device is nullptr.");
		return *renderSystem->Device();
	}

	const IUnknown& DXGISystem::Device() const noexcept
	{
		assert(renderSystem->Device() && "The render system device is nullptr.");
		return *renderSystem->Device();
	}
}
