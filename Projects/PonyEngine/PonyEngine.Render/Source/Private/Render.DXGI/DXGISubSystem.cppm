/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

#include "PonyEngine/Render/Direct3D12/Framework.h"
#include "PonyEngine/Render/DXGI/Framework.h"

export module PonyEngine.Render.DXGI:DXGISubSystem;

import <cstdint>;
import <stdexcept>;
import <type_traits>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;

import PonyEngine.Render.Core;

export namespace PonyEngine::Render
{
	/// @brief DXGI sub-system.
	class DXGISubSystem final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit DXGISubSystem(IRenderer& renderer);
		DXGISubSystem(const DXGISubSystem&) = delete;
		DXGISubSystem(DXGISubSystem&&) = delete;

		~DXGISubSystem() noexcept;

		void Tick();

		void CreateFence(ID3D12Device10* device, ID3D12CommandQueue* commandQueueToSet);
		void CreateSwapChain(IUnknown* device, HWND hWnd);

		DXGISubSystem& operator =(const DXGISubSystem&) = delete;
		DXGISubSystem& operator =(DXGISubSystem&&) = delete;

	private:
		UINT64 fenceValue;

		IRenderer* renderer;

		HANDLE fenceEvent;

		ID3D12CommandQueue* commandQueue;

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<IDXGIDebug1> debug;
#endif
		Microsoft::WRL::ComPtr<IDXGIFactory7> factory;
		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;

		Microsoft::WRL::ComPtr<ID3D12Fence1> fence;
	};
}

namespace PonyEngine::Render
{
	DXGISubSystem::DXGISubSystem(IRenderer& renderer) :
		fenceValue{0},
		renderer{&renderer},
		commandQueue{nullptr}
	{
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create fence event.");
		if ((fenceEvent = CreateEventA(nullptr, false, false, nullptr)) == nullptr) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create fence event. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Fence event created.");

#ifdef _DEBUG
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create DXGI debug interface.");
		if (const HRESULT result = DXGIGetDebugInterface1(0, IID_PPV_ARGS(debug.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get DXGI debug interface with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "DXGI debug interface created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(debug.Get()));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Debug, "Enable DXGI leak tracking.");
		debug->EnableLeakTrackingForThread();
#endif

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create DXGI factory.");
		if (const HRESULT result = CreateDXGIFactory2(0, IID_PPV_ARGS(factory.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create DXGI factory with '0x{:X} result.'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "DXGI factory created.");
	}

	DXGISubSystem::~DXGISubSystem() noexcept
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 fence.");
		fence.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence destroyed.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy swap chain.");
		swapChain.Reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Swap chain destroyed.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy DXGI factory.");
		factory.Reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "DXGI factory destroyed.");

#ifdef _DEBUG
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Report DXGI live objects.");
		if (const HRESULT result = debug->ReportLiveObjects(DXGI_DEBUG_ALL, static_cast<DXGI_DEBUG_RLO_FLAGS>(DXGI_DEBUG_RLO_DETAIL | DXGI_DEBUG_RLO_IGNORE_INTERNAL)); FAILED(result)) [[unlikely]]
		{
			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Error, "Failed to report live objects with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result));
		}
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "DXGI live objects reported.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy DXGI debug interface.");
		debug.Reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "DXGI debug interface destroyed.");
#endif
	}

	void DXGISubSystem::Tick()
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Present swap chain.");
		if (const HRESULT result = swapChain->Present(1, 0); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to present swap chain with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Signal command queue. Current fence value is '{}'.", fenceValue);
		if (const HRESULT result = commandQueue->Signal(fence.Get(), ++fenceValue); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to signal command queue with '0x{:X}' result. Current fence value is '{}'.", static_cast<std::make_unsigned_t<HRESULT>>(result), fenceValue));
		}

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Wait for fence. Current fence value: '{}'.", fenceValue);
		if (const HRESULT result = fence->SetEventOnCompletion(fenceValue, fenceEvent); FAILED(result)) [[unlikely]] // TODO: Make better function calls. Ticks aren't convenient here.
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set event on completion with '0x{:X}' result", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (const DWORD result = WaitForSingleObjectEx(fenceEvent, 20000, false); result != WAIT_OBJECT_0) [[unlikely]] // TODO: Timeout to params
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to wait for fence event with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void DXGISubSystem::CreateFence(ID3D12Device10* const device, ID3D12CommandQueue* const commandQueueToSet)
	{
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 fence.");
		if (const HRESULT result = device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create Direct3D 12 fence with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fence.Get()));

		commandQueue = commandQueueToSet;
	}

	void DXGISubSystem::CreateSwapChain(IUnknown* const device, const HWND hWnd)
	{
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create swap chain for '0x{:X}' device and '0x{:X}' window.", reinterpret_cast<std::uintptr_t>(device), reinterpret_cast<std::uintptr_t>(hWnd));
		const auto swapChainDescription = DXGI_SWAP_CHAIN_DESC1
		{
			.Width = 1280, // TODO: Apply from params.
			.Height = 720,
			.Format = DXGI_FORMAT_R8G8B8A8_UNORM,
			.Stereo = false,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1, .Quality = 0},
			.BufferUsage = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT,
			.BufferCount = 2,
			.Scaling = DXGI_SCALING_STRETCH,
			.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
			.AlphaMode = DXGI_ALPHA_MODE_IGNORE,
			.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING
		};
		const auto swapChainFullScreenDescription = DXGI_SWAP_CHAIN_FULLSCREEN_DESC{.Windowed = true};
		Microsoft::WRL::ComPtr<IDXGISwapChain1> createdSwapChain;
		if (const HRESULT result = factory->CreateSwapChainForHwnd(device, hWnd, &swapChainDescription, &swapChainFullScreenDescription, nullptr, createdSwapChain.GetAddressOf()); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create swap chain with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (const HRESULT result = createdSwapChain->QueryInterface(swapChain.GetAddressOf()); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to query swap chain with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Swap chain created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(swapChain.Get()));
	}
}
