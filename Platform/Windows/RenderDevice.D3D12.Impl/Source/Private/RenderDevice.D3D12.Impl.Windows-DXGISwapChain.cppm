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

#include "PonyEngine/Render/Windows/DXGIFramework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:DXGISwapChain;

import std;

import PonyEngine.Platform.Windows;

export namespace PonyEngine::Render::Windows
{
	class DXGISwapChain final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit DXGISwapChain(IDXGISwapChain4& swapChain) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit DXGISwapChain(Platform::Windows::ComPtr<IDXGISwapChain4>&& swapChain) noexcept;
		DXGISwapChain(const DXGISwapChain& other) noexcept = default;
		DXGISwapChain(DXGISwapChain&& other) noexcept = default;

		~DXGISwapChain() noexcept = default;

		[[nodiscard("Pure function")]]
		UINT GetCurrentBufferIndex() const noexcept;
		template<std::derived_from<IUnknown> T> [[nodiscard("Pure function")]]
		void GetBuffer(UINT index, Platform::Windows::ComPtr<T>& resource) const;

		void SetFullscreenState(BOOL fullscreen);

		void Present(UINT syncInterval, UINT flags);

		DXGISwapChain& operator =(const DXGISwapChain&) = delete;
		DXGISwapChain& operator =(DXGISwapChain&&) = delete;

	private:
		Platform::Windows::ComPtr<IDXGISwapChain4> swapChain;
	};
}

namespace PonyEngine::Render::Windows
{
	DXGISwapChain::DXGISwapChain(IDXGISwapChain4& swapChain) noexcept :
		swapChain(&swapChain)
	{
	}

	DXGISwapChain::DXGISwapChain(Platform::Windows::ComPtr<IDXGISwapChain4>&& swapChain) noexcept :
		swapChain(std::move(swapChain))
	{
		assert(this->swapChain && "The swap chain is nullptr.");
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
