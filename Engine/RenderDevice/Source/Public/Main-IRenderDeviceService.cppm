/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RenderDevice:IRenderDeviceService;

import std;

import PonyEngine.Meta;

import :BufferParams;
import :HeapType;
import :IBuffer;
import :IComputeCommandList;
import :ICopyCommandList;
import :IFence;
import :IGraphicsCommandList;
import :ITexture;
import :IWaiter;
import :QueueSync;
import :SwapChainParams;
import :SwapChainSupport;
import :TextureFormatFeature;
import :TextureFormatId;
import :TextureFormatSupport;
import :TextureParams;
import :TextureSupportRequest;
import :TextureSupportResponse;

export namespace PonyEngine::RenderDevice
{
	class IRenderDeviceService
	{
		PONY_INTERFACE_BODY(IRenderDeviceService)

		[[nodiscard("Pure function")]]
		virtual std::size_t BackendCount() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view RenderApiName(std::size_t backendIndex) const = 0;
		[[nodiscard("Pure function")]]
		virtual Meta::Version RenderApiVersion(std::size_t backendIndex) const = 0;
		[[nodiscard("Pure function")]]
		virtual std::optional<std::size_t> ActiveBackend() const noexcept = 0;
		virtual void SwitchBackend(std::optional<std::size_t> backendIndex) = 0;

		[[nodiscard("Pure function")]]
		virtual HeapTypeMask BufferHeapTypeSupport() const = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IBuffer> CreateBuffer(HeapType heapType, const BufferParams& params) = 0;

		[[nodiscard("Wierd call")]]
		virtual struct TextureFormatId TextureFormatId(std::string_view textureFormat) = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view TextureFormat(struct TextureFormatId textureFormatId) const = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsValid(struct TextureFormatId textureFormatId) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual struct TextureFormatSupport TextureFormatSupport(struct TextureFormatId textureFormatId) const = 0;
		[[nodiscard("Pure function")]]
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const = 0;
		[[nodiscard("Pure function")]]
		virtual HeapTypeMask TextureHeapTypeSupport() const = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ITexture> CreateTexture(HeapType heapType, const TextureParams& params) = 0;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IGraphicsCommandList> CreateGraphicsCommandList() = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IComputeCommandList> CreateComputeCommandList() = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ICopyCommandList> CreateCopyCommandList() = 0;
		virtual void Execute(std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync = QueueSync{}) = 0;
		virtual void Execute(std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync = QueueSync{}) = 0;
		virtual void Execute(std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync = QueueSync{}) = 0;

		[[nodiscard("Pure function")]]
		virtual struct SwapChainSupport SwapChainSupport() const = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsSwapChainAlive() const = 0;
		[[nodiscard("Pure function")]]
		virtual void CreateSwapChain(const SwapChainParams& params) = 0;
		virtual void DestroySwapChain() = 0;
		[[nodiscard("Pure function")]]
		virtual std::uint8_t SwapChainBufferCount() const = 0;
		[[nodiscard("Pure function")]]
		virtual std::uint8_t CurrentSwapChainBufferIndex() const = 0;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ITexture> SwapChainBuffer(std::uint8_t bufferIndex) const = 0;
		virtual void PresentNextSwapChainBuffer() = 0;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IFence> CreateFence() = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IWaiter> CreateWaiter() = 0;
	};
}
