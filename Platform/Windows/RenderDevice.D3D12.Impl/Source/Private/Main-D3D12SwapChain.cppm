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

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12SwapChain;

import std;

import :DXGISwapChain;
import :D3D12Texture;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12SwapChain final
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12SwapChain(IDXGISwapChain4& swapChain, std::span<const std::shared_ptr<D3D12Texture>> buffers, UINT syncInterval, UINT presentFlags);
		[[nodiscard("Pure constructor")]]
		D3D12SwapChain(Platform::Windows::ComPtr<IDXGISwapChain4>&& swapChain, std::vector<std::shared_ptr<D3D12Texture>>&& buffers, 
			UINT syncInterval, UINT presentFlags) noexcept;
		[[nodiscard("Pure constructor")]]
		D3D12SwapChain(const DXGISwapChain& swapChain, std::span<const std::shared_ptr<D3D12Texture>> buffers, UINT syncInterval, UINT presentFlags);
		[[nodiscard("Pure constructor")]]
		D3D12SwapChain(DXGISwapChain&& swapChain, std::vector<std::shared_ptr<D3D12Texture>>&& buffers,
			UINT syncInterval, UINT presentFlags) noexcept;
		D3D12SwapChain(const D3D12SwapChain&) = delete;
		D3D12SwapChain(D3D12SwapChain&&) = delete;

		~D3D12SwapChain() noexcept = default;

		[[nodiscard("Pure function")]]
		UINT BufferCount() const noexcept;
		[[nodiscard("Pure function")]]
		UINT GetCurrentBufferIndex() const noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<D3D12Texture>& GetBuffer(UINT index) const;

		void SetFullscreenState(BOOL fullscreen);

		void Present();

		D3D12SwapChain& operator =(const D3D12SwapChain&) = delete;
		D3D12SwapChain& operator =(D3D12SwapChain&&) = delete;

	private:
		DXGISwapChain swapChain;
		std::vector<std::shared_ptr<D3D12Texture>> buffers;
		UINT syncInterval;
		UINT presentFlags;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12SwapChain::D3D12SwapChain(IDXGISwapChain4& swapChain, const std::span<const std::shared_ptr<D3D12Texture>> buffers, 
		const UINT syncInterval, const UINT presentFlags) :
		swapChain(swapChain),
		buffers(buffers.cbegin(), buffers.cend()),
		syncInterval{syncInterval},
		presentFlags{presentFlags}
	{
		assert(buffers.size() <= std::numeric_limits<UINT>::max() && "The buffer count is too great.");
		assert(std::ranges::find(this->buffers, nullptr) == this->buffers.cend() && "At least one buffer is nullptr.");
	}

	D3D12SwapChain::D3D12SwapChain(Platform::Windows::ComPtr<IDXGISwapChain4>&& swapChain, std::vector<std::shared_ptr<D3D12Texture>>&& buffers, 
		const UINT syncInterval, const UINT presentFlags) noexcept :
		swapChain(std::move(swapChain)),
		buffers(std::move(buffers)),
		syncInterval{syncInterval},
		presentFlags{presentFlags}
	{
		assert(buffers.size() <= std::numeric_limits<UINT>::max() && "The buffer count is too great.");
		assert(std::ranges::find(this->buffers, nullptr) == this->buffers.cend() && "At least one buffer is nullptr.");
	}

	D3D12SwapChain::D3D12SwapChain(const DXGISwapChain& swapChain, const std::span<const std::shared_ptr<D3D12Texture>> buffers, 
		const UINT syncInterval, const UINT presentFlags) :
		swapChain(swapChain),
		buffers(buffers.cbegin(), buffers.cend()),
		syncInterval{syncInterval},
		presentFlags{presentFlags}
	{
		assert(buffers.size() <= std::numeric_limits<UINT>::max() && "The buffer count is too great.");
		assert(std::ranges::find(this->buffers, nullptr) == this->buffers.cend() && "At least one buffer is nullptr.");
	}

	D3D12SwapChain::D3D12SwapChain(DXGISwapChain&& swapChain, std::vector<std::shared_ptr<D3D12Texture>>&& buffers,
		const UINT syncInterval, const UINT presentFlags) noexcept :
		swapChain(std::move(swapChain)),
		buffers(std::move(buffers)),
		syncInterval{syncInterval},
		presentFlags{presentFlags}
	{
		assert(buffers.size() <= std::numeric_limits<UINT>::max() && "The buffer count is too great.");
		assert(std::ranges::find(this->buffers, nullptr) == this->buffers.cend() && "At least one buffer is nullptr.");
	}

	UINT D3D12SwapChain::BufferCount() const noexcept
	{
		return static_cast<UINT>(buffers.size());
	}

	UINT D3D12SwapChain::GetCurrentBufferIndex() const noexcept
	{
		return swapChain.GetCurrentBufferIndex();
	}

	const std::shared_ptr<D3D12Texture>& D3D12SwapChain::GetBuffer(const UINT index) const
	{
		if (index >= BufferCount()) [[unlikely]]
		{
			throw std::out_of_range("Buffer index is out of range");
		}

		return buffers[index];
	}

	void D3D12SwapChain::SetFullscreenState(const BOOL fullscreen)
	{
		swapChain.SetFullscreenState(fullscreen);
	}

	void D3D12SwapChain::Present()
	{
		swapChain.Present(syncInterval, presentFlags);
	}
}
