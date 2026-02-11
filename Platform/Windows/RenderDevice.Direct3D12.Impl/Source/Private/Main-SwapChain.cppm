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

#include "PonyEngine/RenderDevice/Windows/DXGIFramework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:SwapChain;

import std;

import PonyEngine.Platform.Windows;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class SwapChain final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit SwapChain(IDXGISwapChain4& swapChain) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit SwapChain(Platform::Windows::ComPtr<IDXGISwapChain4>&& swapChain) noexcept;
		[[nodiscard("Pure constructor")]]
		SwapChain(const SwapChain& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		SwapChain(SwapChain&& other) noexcept = default;

		~SwapChain() noexcept = default;

		[[nodiscard("Pure function")]]
		UINT GetCurrentBufferIndex() const noexcept;
		template<std::derived_from<IUnknown> T> [[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<T> GetBuffer(UINT index) const;

		void SetFullscreenState(BOOL fullscreen);

		void Present(UINT syncInterval, UINT flags);

		SwapChain& operator =(const SwapChain&) = delete;
		SwapChain& operator =(SwapChain&&) = delete;

	private:
		Platform::Windows::ComPtr<IDXGISwapChain4> swapChain;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	SwapChain::SwapChain(IDXGISwapChain4& swapChain) noexcept :
		swapChain(&swapChain)
	{
	}

	SwapChain::SwapChain(Platform::Windows::ComPtr<IDXGISwapChain4>&& swapChain) noexcept :
		swapChain(std::move(swapChain))
	{
		assert(this->swapChain && "The swap chain is nullptr.");
	}

	UINT SwapChain::GetCurrentBufferIndex() const noexcept
	{
		return swapChain->GetCurrentBackBufferIndex();
	}

	template<std::derived_from<IUnknown> T>
	Platform::Windows::ComPtr<T> SwapChain::GetBuffer(const UINT index) const
	{
		Platform::Windows::ComPtr<T> resource;
		if (const HRESULT result = swapChain->GetBuffer(index, IID_PPV_ARGS(resource.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get swap chain buffer: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return resource;
	}

	void SwapChain::SetFullscreenState(const BOOL fullscreen)
	{
		if (const HRESULT result = swapChain->SetFullscreenState(fullscreen, nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set fullscreen state: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void SwapChain::Present(const UINT syncInterval, const UINT flags)
	{
		if (const HRESULT result = swapChain->Present(syncInterval, flags); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to present: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
