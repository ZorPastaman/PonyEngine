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

export namespace PonyEngine::Render
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

		[[nodiscard("Pure function")]]
		virtual IGraphicsCommandQueue& GraphicsCommandQueue() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IGraphicsCommandQueue& GraphicsCommandQueue() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual IComputeCommandQueue& ComputeCommandQueue() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IComputeCommandQueue& ComputeCommandQueue() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual ICopyCommandQueue& CopyCommandQueue() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const ICopyCommandQueue& CopyCommandQueue() const noexcept = 0;

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
	};
}
