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

export module PonyEngine.Render.DXGI.Detail:SwapChain;

import <cstdint>;
import <stdexcept>;
import <type_traits>;

import PonyBase.Utility;

import PonyMath.Utility;

import PonyDebug.Log;

import :ISubSystemContext;
import :ISwapChain;
import :SwapChainParams;

export namespace PonyEngine::Render::DXGI
{
	/// @brief DXGI swap chain.
	class SwapChain final : public ISwapChain
	{
	public:
		/// @brief Creates a @p SwapChain.
		/// @param dxgiSystem DXGI system context.
		/// @param swapChainParams Swap chain parameters.
		[[nodiscard("Pure constructor")]]
		SwapChain(ISubSystemContext& dxgiSystem, const SwapChainParams& swapChainParams);
		SwapChain(const SwapChain&) = delete;
		[[nodiscard("Pure constructor")]]
		SwapChain(SwapChain&& other) noexcept = default;

		~SwapChain() noexcept;

		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT Format() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t GetCurrentBackBufferIndex() const noexcept override;
		virtual HRESULT GetBackBuffer(std::uint32_t bufferIndex, ID3D12Resource2** buffer) const noexcept override;

		/// @brief Sets the fullscreen state.
		/// @param fullscreen Is fullscreen?
		void SetFullscreenState(bool fullscreen);

		/// @brief Calls the swap chain present function.
		void Present();

		SwapChain& operator =(const SwapChain&) = delete;
		SwapChain& operator =(SwapChain&& other) noexcept = default;

	private:
		static constexpr DXGI_FORMAT BackViewFormat = DXGI_FORMAT_R8G8B8A8_UNORM; ///< Back view format

		ISubSystemContext* dxgiSystem; ///< DXGI system context.

		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain; ///< Swap chain.
	};
}

namespace PonyEngine::Render::DXGI
{
	SwapChain::SwapChain(ISubSystemContext& dxgiSystem, const SwapChainParams& swapChainParams) :
		dxgiSystem{&dxgiSystem}
	{
		IUnknown* const device = &this->dxgiSystem->Device();
		PONY_LOG(this->dxgiSystem->Logger(), PonyDebug::Log::LogType::Info, "Acquire swap chain for '0x{:X}' device and '0x{:X}' window. Resolution: '{}'; Buffer count : {}.",
			reinterpret_cast<std::uintptr_t>(device), reinterpret_cast<std::uintptr_t>(swapChainParams.hWnd), swapChainParams.resolution.ToString(), swapChainParams.bufferCount);
		const auto swapChainDescription = DXGI_SWAP_CHAIN_DESC1
		{
			.Width = swapChainParams.resolution.Width(),
			.Height = swapChainParams.resolution.Height(),
			.Format = BackViewFormat,
			.Stereo = false,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
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
		PONY_LOG(this->dxgiSystem->Logger(), PonyDebug::Log::LogType::Info, "Swap chain acquired.");
	}

	SwapChain::~SwapChain() noexcept
	{
		PONY_LOG(dxgiSystem->Logger(), PonyDebug::Log::LogType::Info, "Release swap chain.");
		swapChain.Reset();
		PONY_LOG(dxgiSystem->Logger(), PonyDebug::Log::LogType::Info, "Swap chain released.");
	}

	DXGI_FORMAT SwapChain::Format() const noexcept
	{
		return BackViewFormat;
	}

	std::uint32_t SwapChain::GetCurrentBackBufferIndex() const noexcept
	{
		return static_cast<std::uint32_t>(swapChain->GetCurrentBackBufferIndex());
	}

	HRESULT SwapChain::GetBackBuffer(const std::uint32_t bufferIndex, ID3D12Resource2** const buffer) const noexcept
	{
		return swapChain->GetBuffer(static_cast<UINT>(bufferIndex), IID_PPV_ARGS(buffer));
	}

	void SwapChain::SetFullscreenState(const bool fullscreen)
	{
		if (const HRESULT result = swapChain->SetFullscreenState(fullscreen, nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set fullscreen state with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void SwapChain::Present()
	{
		if (const HRESULT result = swapChain->Present(1, 0); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to present swap chain with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
