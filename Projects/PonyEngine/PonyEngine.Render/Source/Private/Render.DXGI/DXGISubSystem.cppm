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

#include "PonyEngine/Render/DXGI/Framework.h"

export module PonyEngine.Render.DXGI:DXGISubSystem;

import <cstdint>;
import <optional>;
import <stdexcept>;
import <type_traits>;

import PonyBase.Math;
import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Window.Windows;

import PonyEngine.Render.Core;

export namespace PonyEngine::Render
{
	/// @brief DXGI sub-system.
	class DXGISubSystem final
	{
	public:
		[[nodiscard("Pure constructor")]]
		DXGISubSystem(IRenderer& renderer, UINT bufferCount, const std::optional<PonyBase::Math::Vector2<UINT>>& resolution);
		DXGISubSystem(const DXGISubSystem&) = delete;
		DXGISubSystem(DXGISubSystem&&) = delete;

		~DXGISubSystem() noexcept;

		void AcquireSwapChain(IUnknown* device, HWND hWnd);
		[[nodiscard("Pure function")]]
		IDXGISwapChain4* GetSwapChain() const noexcept;

		void Present() const;

		DXGISubSystem& operator =(const DXGISubSystem&) = delete;
		DXGISubSystem& operator =(DXGISubSystem&&) = delete;

	private:
		std::optional<PonyBase::Math::Vector2<UINT>> resolution;
		UINT bufferCount;

		IRenderer* renderer;

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<IDXGIDebug1> debug;
#endif
		Microsoft::WRL::ComPtr<IDXGIFactory7> factory;
		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	};
}

namespace PonyEngine::Render
{
	DXGISubSystem::DXGISubSystem(IRenderer& renderer, const UINT bufferCount, const std::optional<PonyBase::Math::Vector2<UINT>>& resolution) :
		resolution{resolution},
		bufferCount{bufferCount},
		renderer{&renderer}
	{
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "DXGI parameters. Buffer count: '{}'; Resolution: '{}'.", this->bufferCount, this->resolution.has_value() ? this->resolution->ToString() : "empty");

#ifdef _DEBUG
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire DXGI debug interface.");
		if (const HRESULT result = DXGIGetDebugInterface1(0, IID_PPV_ARGS(debug.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire DXGI debug interface with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "DXGI debug interface acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(debug.Get()));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Debug, "Enable DXGI leak tracking.");
		debug->EnableLeakTrackingForThread();
#endif

		UINT factoryFlags = 0;
#ifdef _DEBUG
		factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire DXGI factory.");
		if (const HRESULT result = CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(factory.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire DXGI factory with '0x{:X} result.'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "DXGI factory acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(factory.Get()));
	}

	DXGISubSystem::~DXGISubSystem() noexcept
	{
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Release swap chain.");
		swapChain.Reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Swap chain released.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Release DXGI factory.");
		factory.Reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "DXGI factory released.");

#ifdef _DEBUG
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Report DXGI live objects.");
		if (const HRESULT result = debug->ReportLiveObjects(DXGI_DEBUG_ALL, static_cast<DXGI_DEBUG_RLO_FLAGS>(DXGI_DEBUG_RLO_DETAIL | DXGI_DEBUG_RLO_IGNORE_INTERNAL)); FAILED(result)) [[unlikely]]
		{
			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Error, "Failed to report live objects with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result));
		}
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "DXGI live objects reported.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Release DXGI debug interface.");
		debug.Reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "DXGI debug interface released.");
#endif
	}

	void DXGISubSystem::AcquireSwapChain(IUnknown* const device, const HWND hWnd)
	{
		const PonyBase::Math::Vector2<UINT> renderResolution = resolution.has_value() ? resolution.value() : static_cast<PonyBase::Math::Vector2<UINT>>(Window::GetWindowClientSize(hWnd));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire swap chain for '0x{:X}' device and '0x{:X}' window. Resolution: '{}'.", reinterpret_cast<std::uintptr_t>(device), reinterpret_cast<std::uintptr_t>(hWnd),
			renderResolution.ToString());

		const auto swapChainDescription = DXGI_SWAP_CHAIN_DESC1
		{
			.Width = renderResolution.X(),
			.Height = renderResolution.Y(),
			.Format = DXGI_FORMAT_R8G8B8A8_UNORM,
			.Stereo = false,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.BufferUsage = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT,
			.BufferCount = bufferCount,
			.Scaling = DXGI_SCALING_STRETCH,
			.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
			.AlphaMode = DXGI_ALPHA_MODE_IGNORE,
			.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING
		};
		Microsoft::WRL::ComPtr<IDXGISwapChain1> acquiredSwapChain;
		if (const HRESULT result = factory->CreateSwapChainForHwnd(device, hWnd, &swapChainDescription, nullptr, nullptr, acquiredSwapChain.GetAddressOf()); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire swap chain with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		if (const HRESULT result = acquiredSwapChain->QueryInterface(swapChain.GetAddressOf()); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to query swap chain with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Swap chain acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(swapChain.Get()));
	}

	IDXGISwapChain4* DXGISubSystem::GetSwapChain() const noexcept
	{
		return swapChain.Get();
	}

	void DXGISubSystem::Present() const
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Present swap chain.");
		if (const HRESULT result = swapChain->Present(1, 0); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to present swap chain with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
