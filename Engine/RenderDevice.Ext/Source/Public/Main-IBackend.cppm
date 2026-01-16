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

export module PonyEngine.RenderDevice.Ext:IBackend;

import std;

import PonyEngine.Meta;
import PonyEngine.RenderDevice;

export namespace PonyEngine::RenderDevice
{
	class IBackend
	{
		PONY_INTERFACE_BODY(IBackend)

		[[nodiscard("Pure function")]]
		virtual std::string_view RenderApiName() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual Meta::Version RenderApiVersion() const noexcept = 0;

		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IBuffer> CreateBuffer(HeapType heapType, const BufferParams& params) = 0;

		[[nodiscard("Pure function")]]
		virtual TextureFormatFeature TextureFormatFeatures(TextureFormatId textureFormatId) const = 0;
		[[nodiscard("Pure function")]]
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ITexture> CreateTexture(HeapType heapType, const TextureParams& params) = 0;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IGraphicsCommandList> CreateGraphicsCommandList() = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IComputeCommandList> CreateComputeCommandList() = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ICopyCommandList> CreateCopyCommandList() = 0;
		virtual void Execute(std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync) = 0;
		virtual void Execute(std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync) = 0;
		virtual void Execute(std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync) = 0;

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
