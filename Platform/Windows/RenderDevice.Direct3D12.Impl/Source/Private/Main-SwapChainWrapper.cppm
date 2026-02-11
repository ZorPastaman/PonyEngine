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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:SwapChainWrapper;

import std;

import :SwapChain;
import :Texture;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class SwapChainWrapper final
	{
	public:
		[[nodiscard("Pure constructor")]]
		SwapChainWrapper(IDXGISwapChain4& swapChain, std::span<const std::shared_ptr<Texture>> buffers, UINT syncInterval, UINT presentFlags);
		[[nodiscard("Pure constructor")]]
		SwapChainWrapper(Platform::Windows::ComPtr<IDXGISwapChain4>&& swapChain, std::vector<std::shared_ptr<Texture>>&& buffers, 
			UINT syncInterval, UINT presentFlags) noexcept;
		[[nodiscard("Pure constructor")]]
		SwapChainWrapper(const SwapChain& swapChain, std::span<const std::shared_ptr<Texture>> buffers, UINT syncInterval, UINT presentFlags);
		[[nodiscard("Pure constructor")]]
		SwapChainWrapper(SwapChain&& swapChain, std::vector<std::shared_ptr<Texture>>&& buffers,
			UINT syncInterval, UINT presentFlags) noexcept;
		SwapChainWrapper(const SwapChainWrapper&) = delete;
		SwapChainWrapper(SwapChainWrapper&&) = delete;

		~SwapChainWrapper() noexcept = default;

		[[nodiscard("Pure function")]]
		UINT BufferCount() const noexcept;
		[[nodiscard("Pure function")]]
		UINT GetCurrentBufferIndex() const noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<Texture>& GetBuffer(UINT index) const;

		void SetFullscreenState(BOOL fullscreen);

		void Present();

		SwapChainWrapper& operator =(const SwapChainWrapper&) = delete;
		SwapChainWrapper& operator =(SwapChainWrapper&&) = delete;

	private:
		SwapChain swapChain;
		std::vector<std::shared_ptr<Texture>> buffers;
		UINT syncInterval;
		UINT presentFlags;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	SwapChainWrapper::SwapChainWrapper(IDXGISwapChain4& swapChain, const std::span<const std::shared_ptr<Texture>> buffers, 
		const UINT syncInterval, const UINT presentFlags) :
		swapChain(swapChain),
		buffers(buffers.cbegin(), buffers.cend()),
		syncInterval{syncInterval},
		presentFlags{presentFlags}
	{
		assert(buffers.size() <= std::numeric_limits<UINT>::max() && "The buffer count is too great.");
		assert(std::ranges::find(this->buffers, nullptr) == this->buffers.cend() && "At least one buffer is nullptr.");
	}

	SwapChainWrapper::SwapChainWrapper(Platform::Windows::ComPtr<IDXGISwapChain4>&& swapChain, std::vector<std::shared_ptr<Texture>>&& buffers, 
		const UINT syncInterval, const UINT presentFlags) noexcept :
		swapChain(std::move(swapChain)),
		buffers(std::move(buffers)),
		syncInterval{syncInterval},
		presentFlags{presentFlags}
	{
		assert(buffers.size() <= std::numeric_limits<UINT>::max() && "The buffer count is too great.");
		assert(std::ranges::find(this->buffers, nullptr) == this->buffers.cend() && "At least one buffer is nullptr.");
	}

	SwapChainWrapper::SwapChainWrapper(const SwapChain& swapChain, const std::span<const std::shared_ptr<Texture>> buffers, 
		const UINT syncInterval, const UINT presentFlags) :
		swapChain(swapChain),
		buffers(buffers.cbegin(), buffers.cend()),
		syncInterval{syncInterval},
		presentFlags{presentFlags}
	{
		assert(buffers.size() <= std::numeric_limits<UINT>::max() && "The buffer count is too great.");
		assert(std::ranges::find(this->buffers, nullptr) == this->buffers.cend() && "At least one buffer is nullptr.");
	}

	SwapChainWrapper::SwapChainWrapper(SwapChain&& swapChain, std::vector<std::shared_ptr<Texture>>&& buffers,
		const UINT syncInterval, const UINT presentFlags) noexcept :
		swapChain(std::move(swapChain)),
		buffers(std::move(buffers)),
		syncInterval{syncInterval},
		presentFlags{presentFlags}
	{
		assert(buffers.size() <= std::numeric_limits<UINT>::max() && "The buffer count is too great.");
		assert(std::ranges::find(this->buffers, nullptr) == this->buffers.cend() && "At least one buffer is nullptr.");
	}

	UINT SwapChainWrapper::BufferCount() const noexcept
	{
		return static_cast<UINT>(buffers.size());
	}

	UINT SwapChainWrapper::GetCurrentBufferIndex() const noexcept
	{
		return swapChain.GetCurrentBufferIndex();
	}

	const std::shared_ptr<Texture>& SwapChainWrapper::GetBuffer(const UINT index) const
	{
#ifndef NDEBUG
		if (index >= BufferCount()) [[unlikely]]
		{
			throw std::out_of_range("Buffer index is out of range");
		}
#endif

		return buffers[index];
	}

	void SwapChainWrapper::SetFullscreenState(const BOOL fullscreen)
	{
		swapChain.SetFullscreenState(fullscreen);
	}

	void SwapChainWrapper::Present()
	{
		swapChain.Present(syncInterval, presentFlags);
	}
}
