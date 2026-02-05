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
import :CBVParams;
import :CopyableFootprint;
import :CopyableFootprintSize;
import :DepthStencilContainerParams;
import :DeviceSupport;
import :DSVParams;
import :GraphicsPipelineStateParams;
import :HeapType;
import :IBuffer;
import :IComputeCommandList;
import :ICopyCommandList;
import :IDepthStencilContainer;
import :IFence;
import :IGraphicsCommandList;
import :IGraphicsPipelineState;
import :IPipelineLayout;
import :IRenderTargetContainer;
import :ISamplerContainer;
import :ISecondaryGraphicsCommandList;
import :IShader;
import :IShaderDataContainer;
import :ITexture;
import :IWaiter;
import :PipelineLayoutParams;
import :QueueSync;
import :RenderTargetContainerParams;
import :RTVParams;
import :SamplerContainerParams;
import :SamplerParams;
import :ShaderDataContainerParams;
import :SRVParams;
import :SubTextureRange;
import :SwapChainParams;
import :TextureFormatFeature;
import :TextureFormatId;
import :TextureFormatSupport;
import :TextureParams;
import :TextureSupportRequest;
import :TextureSupportResponse;
import :UAVParams;
import :ViewContainerCopyRange;

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
		virtual struct DeviceSupport DeviceSupport() const = 0;

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
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ITexture> CreateTexture(HeapType heapType, const TextureParams& params) = 0;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range) const = 0;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t GetCopyableFootprintCount(const ITexture& texture, const SubTextureRange& range) const = 0;
		virtual CopyableFootprintSize GetCopyableFootprints(const TextureParams& params, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints) const = 0;
		virtual CopyableFootprintSize GetCopyableFootprints(const ITexture& texture, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints) const = 0;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IShaderDataContainer> CreateShaderDataContainer(const ShaderDataContainerParams& params) = 0;
		virtual void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const CBVParams& params) = 0;
		virtual void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const BufferSRVParams& params) = 0;
		virtual void CreateView(const ITexture* texture, IShaderDataContainer& container, std::uint32_t index, const TextureSRVParams& params) = 0;
		virtual void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const BufferUAVParams& params) = 0;
		virtual void CreateView(const ITexture* texture, IShaderDataContainer& container, std::uint32_t index, const TextureUAVParams& params) = 0;
		virtual void CopyViews(std::span<const ShaderDataCopyRange> ranges) = 0;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IRenderTargetContainer> CreateRenderTargetContainer(const RenderTargetContainerParams& params) = 0;
		virtual void CreateView(const ITexture* texture, IRenderTargetContainer& container, std::uint32_t index, const RTVParams& params) = 0;
		virtual void CopyViews(std::span<const RenderTargetCopyRange> ranges) = 0;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IDepthStencilContainer> CreateDepthStencilContainer(const DepthStencilContainerParams& params) = 0;
		virtual void CreateView(const ITexture* texture, IDepthStencilContainer& container, std::uint32_t index, const DSVParams& params) = 0;
		virtual void CopyViews(std::span<const DepthStencilCopyRange> ranges) = 0;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ISamplerContainer> CreateSamplerContainer(const SamplerContainerParams& params) = 0;
		virtual void CreateSampler(ISamplerContainer& container, std::uint32_t index, const SamplerParams& params) = 0;
		virtual void CopySamplers(std::span<const SamplerCopyRange> ranges) = 0;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IShader> CreateShader(std::span<const std::byte> byteCode) = 0;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IPipelineLayout> CreatePipelineLayout(const PipelineLayoutParams& params) = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IGraphicsPipelineState> CreateGraphicsPipelineState(const std::shared_ptr<const IPipelineLayout>& layout, const GraphicsPipelineStateParams& params) = 0;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IGraphicsCommandList> CreateGraphicsCommandList() = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IComputeCommandList> CreateComputeCommandList() = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ICopyCommandList> CreateCopyCommandList() = 0;
		virtual void Execute(std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync = QueueSync{}) = 0;
		virtual void Execute(std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync = QueueSync{}) = 0;
		virtual void Execute(std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync = QueueSync{}) = 0;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ISecondaryGraphicsCommandList> CreateSecondaryGraphicsCommandList() = 0;

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
