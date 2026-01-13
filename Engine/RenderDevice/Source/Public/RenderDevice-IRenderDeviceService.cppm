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
import :IComputeCommandQueue;
import :ICopyCommandQueue;
import :IGraphicsCommandQueue;
import :ITexture;
import :SwapChainParams;
import :SwapChainSupport;
import :TextureFormatFeature;
import :TextureFormatId;
import :TextureParams;
import :TextureSupportRequest;
import :TextureSupportResponse;

export namespace PonyEngine::Render
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

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IBuffer> CreateBuffer(HeapType heapType, const BufferParams& params) = 0;

		[[nodiscard("Wierd call")]]
		virtual struct TextureFormatId TextureFormatId(std::string_view textureFormat) = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view TextureFormat(struct TextureFormatId textureFormatId) const = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsValid(struct TextureFormatId textureFormatId) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual TextureFormatFeature TextureFormatFeatures(struct TextureFormatId textureFormatId) const = 0;
		[[nodiscard("Pure function")]]
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ITexture> CreateTexture(HeapType heapType, const TextureParams& params) = 0;

		[[nodiscard("Pure function")]]
		virtual IGraphicsCommandQueue& GraphicsCommandQueue() = 0;
		[[nodiscard("Pure function")]]
		virtual const IGraphicsCommandQueue& GraphicsCommandQueue() const = 0;
		[[nodiscard("Pure function")]]
		virtual IComputeCommandQueue& ComputeCommandQueue() = 0;
		[[nodiscard("Pure function")]]
		virtual const IComputeCommandQueue& ComputeCommandQueue() const = 0;
		[[nodiscard("Pure function")]]
		virtual ICopyCommandQueue& CopyCommandQueue() = 0;
		[[nodiscard("Pure function")]]
		virtual const ICopyCommandQueue& CopyCommandQueue() const = 0;

		[[nodiscard("Pure function")]]
		virtual struct SwapChainSupport SwapChainSupport() const = 0;
		[[nodiscard("Pure function")]]
		virtual void CreateSwapChain(const SwapChainParams& params) = 0;
		[[nodiscard("Pure function")]]
		virtual std::uint8_t SwapChainBufferCount() const = 0;
		[[nodiscard("Pure function")]]
		virtual std::uint8_t CurrentSwapChainBufferIndex() const = 0;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ITexture> SwapChainBuffer(std::uint8_t bufferIndex) const = 0;
		virtual void PresentNext() = 0;
	};
}
