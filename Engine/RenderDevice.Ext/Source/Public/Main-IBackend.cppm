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
	/// @brief Render backend. It implements a render API support.
	class IBackend
	{
		PONY_INTERFACE_BODY(IBackend)

		/// @brief Gets the render API name.
		/// @return Render API name.
		/// @note The backend must be always ready for the call of this function even if it's not active.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view RenderAPIName() const noexcept = 0;
		/// @brief Gets the render API version.
		/// @return Render API version.
		/// @note The backend must be always ready for the call of this function even if it's not active.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual Meta::Version RenderAPIVersion() const noexcept = 0;

		/// @brief Activates the backend. The backend must be ready for any other function calls if it's activated successfully.
		virtual void Activate() = 0;
		/// @brief Deactivates the backend. The other functions won't be called after it.
		virtual void Deactivate() = 0;

		/// @brief Gets a device support.
		/// @return Device support.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual struct DeviceSupport DeviceSupport() const = 0;

		/// @brief Creates a buffer.
		/// @param heapParams Buffer heap parameters.
		/// @param params Buffer parameters.
		/// @return Buffer.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IBuffer> CreateBuffer(const CommittedResourceHeapParams& heapParams, const BufferParams& params) = 0;

		/// @brief Gets a texture format support.
		/// @param textureFormatId Texture format ID.
		/// @return Texture format support.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual struct TextureFormatSupport TextureFormatSupport(TextureFormatId textureFormatId) const = 0;
		/// @brief Gets a texture support.
		/// @param request Texture support request.
		/// @return Texture support response.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const = 0;
		/// @brief Creates a texture.
		/// @param heapParams Texture heap parameters.
		/// @param params Texture parameters.
		/// @return Texture.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ITexture> CreateTexture(const CommittedResourceHeapParams& heapParams, const TextureParams& params) = 0;

		/// @brief Gets a copyable footprint count for a texture created with the @p params.
		/// @param params Texture parameters.
		/// @param range Sub-texture range.
		/// @return Copyable footprint count.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range) const = 0;
		/// @brief Gets a copyable footprint count for the texture.
		/// @param texture Texture.
		/// @param range Sub-texture range.
		/// @return Copyable footprint count.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t GetCopyableFootprintCount(const ITexture& texture, const SubTextureRange& range) const = 0;
		/// @brief Gets copyable footprints for a texture created with the @p params.
		/// @param params Texture parameters.
		/// @param offset Texture buffer data offset.
		/// @param range Sub-texture range.
		/// @param footprints Footprints. Must be empty or its count must be equal to @p GetCopyableFootprintCount().
		/// @return Copyable footprint size.
		/// @note The function is thread-safe.
		virtual CopyableFootprintSize GetCopyableFootprints(const TextureParams& params, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints) const = 0;
		/// @brief Gets copyable footprints for the texture.
		/// @param texture Texture.
		/// @param offset Texture buffer data offset.
		/// @param range Sub-texture range.
		/// @param footprints Footprints. Must be empty or its count must be equal to @p GetCopyableFootprintCount().
		/// @return Copyable footprint size.
		/// @note The function is thread-safe.
		virtual CopyableFootprintSize GetCopyableFootprints(const ITexture& texture, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints) const = 0;

		/// @brief Creates a shader data container.
		/// @param params Container parameters.
		/// @return Shader data container.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IShaderDataContainer> CreateShaderDataContainer(const ShaderDataContainerParams& params) = 0;
		/// @brief Creates a constant buffer view.
		/// @param buffer Target buffer. May be nullptr.
		/// @param container Shader data container where a view will be created.
		/// @param index Container view index.
		/// @param params Constant buffer view parameters.
		/// @note The function is thread-safe.
		virtual void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const CBVParams& params) = 0;
		/// @brief Creates a shader resource view.
		/// @param buffer Target buffer. May be nullptr.
		/// @param container Shader data container where a view will be created.
		/// @param index Container view index.
		/// @param params Shader resource view parameters.
		/// @note The function is thread-safe.
		virtual void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const BufferSRVParams& params) = 0;
		/// @brief Creates a shader resource view.
		/// @param texture Target texture. May be nullptr.
		/// @param container Shader data container where a view will be created.
		/// @param index Container view index.
		/// @param params Shader resource view parameters.
		/// @note The function is thread-safe.
		virtual void CreateView(const ITexture* texture, IShaderDataContainer& container, std::uint32_t index, const TextureSRVParams& params) = 0;
		/// @brief Creates an unordered access view.
		/// @param buffer Target buffer. May be nullptr.
		/// @param container Shader data container where a view will be created.
		/// @param index Container view index.
		/// @param params Unordered access view parameters.
		/// @note The function is thread-safe.
		virtual void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const BufferUAVParams& params) = 0;
		/// @brief Creates an unordered access view.
		/// @param texture Target texture. May be nullptr.
		/// @param container Shader data container where a view will be created.
		/// @param index Container view index.
		/// @param params Unordered access view parameters.
		/// @note The function is thread-safe.
		virtual void CreateView(const ITexture* texture, IShaderDataContainer& container, std::uint32_t index, const TextureUAVParams& params) = 0;
		/// @brief Copies views.
		/// @param ranges Copy ranges.
		/// @note The function is thread-safe.
		virtual void CopyViews(std::span<const ShaderDataCopyRange> ranges) = 0;

		/// @brief Creates a render target container.
		/// @param params Container parameters.
		/// @return Render target container.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IRenderTargetContainer> CreateRenderTargetContainer(const RenderTargetContainerParams& params) = 0;
		/// @brief Creates a render target view.
		/// @param texture Target texture. May be nullptr.
		/// @param container Render target container where a view will be created.
		/// @param index Container view index.
		/// @param params Render target view parameters.
		/// @note The function is thread-safe.
		virtual void CreateView(const ITexture* texture, IRenderTargetContainer& container, std::uint32_t index, const RTVParams& params) = 0;
		/// @brief Copies views.
		/// @param ranges Copy ranges.
		/// @note The function is thread-safe.
		virtual void CopyViews(std::span<const RenderTargetCopyRange> ranges) = 0;

		/// @brief Creates a depth stencil container.
		/// @param params Container parameters.
		/// @return Depth stencil container.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IDepthStencilContainer> CreateDepthStencilContainer(const DepthStencilContainerParams& params) = 0;
		/// @brief Creates a depth stencil view.
		/// @param texture Target texture. May be nullptr.
		/// @param container Depth stencil container where a view will be created.
		/// @param index Container view index.
		/// @param params Depth stencil view parameters.
		/// @note The function is thread-safe.
		virtual void CreateView(const ITexture* texture, IDepthStencilContainer& container, std::uint32_t index, const DSVParams& params) = 0;
		/// @brief Copies views.
		/// @param ranges Copy ranges.
		/// @note The function is thread-safe.
		virtual void CopyViews(std::span<const DepthStencilCopyRange> ranges) = 0;

		/// @brief Creates a sampler container.
		/// @param params Container parameters.
		/// @return Sampler container.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ISamplerContainer> CreateSamplerContainer(const SamplerContainerParams& params) = 0;
		/// @brief Creates a sampler.
		/// @param container Sampler container.
		/// @param index Container index.
		/// @param params Sampler parameters.
		/// @note The function is thread-safe.
		virtual void CreateSampler(ISamplerContainer& container, std::uint32_t index, const SamplerParams& params) = 0;
		/// @brief Copies samplers.
		/// @param ranges Copy ranges.
		/// @note The function is thread-safe.
		virtual void CopySamplers(std::span<const SamplerCopyRange> ranges) = 0;

		/// @brief Creates a pipeline layout.
		/// @param params Pipeline layout parameters.
		/// @return Pipeline layout.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IPipelineLayout> CreatePipelineLayout(const PipelineLayoutParams& params) = 0;
		/// @brief Creates a graphics pipeline state.
		/// @param layout Pipeline layout.
		/// @param params Pipeline state parameters.
		/// @return Graphics pipeline state.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IGraphicsPipelineState> CreateGraphicsPipelineState(const std::shared_ptr<const IPipelineLayout>& layout, const GraphicsPipelineStateParams& params) = 0;
		/// @brief Creates a compute pipeline state.
		/// @param layout Pipeline layout.
		/// @param params Pipeline state parameters.
		/// @return Compute pipeline state.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IComputePipelineState> CreateComputePipelineState(const std::shared_ptr<const IPipelineLayout>& layout, const ComputePipelineStateParams& params) = 0;

		/// @brief Creates a graphics command list.
		/// @return Graphics command list.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IGraphicsCommandList> CreateGraphicsCommandList() = 0;
		/// @brief Creates a compute command list.
		/// @return Compute command list.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IComputeCommandList> CreateComputeCommandList() = 0;
		/// @brief Creates a copy command list.
		/// @return Copy command list.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ICopyCommandList> CreateCopyCommandList() = 0;
		/// @brief Executes the graphics command lists.
		/// @param commandLists Graphics command lists to execute. May be empty.
		/// @param sync Queue sync.
		/// @note The function can't be used concurrently with other @p Execute() functions but can be used concurrently with the other functions.
		virtual void Execute(std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync) = 0;
		/// @brief Executes the compute command lists.
		/// @param commandLists Compute command lists to execute. May be empty.
		/// @param sync Queue sync.
		/// @note The function can't be used concurrently with other @p Execute() functions but can be used concurrently with the other functions.
		virtual void Execute(std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync) = 0;
		/// @brief Executes the copy command lists.
		/// @param commandLists Copy command lists to execute. May be empty.
		/// @param sync Queue sync.
		/// @note The function can't be used concurrently with other @p Execute() functions but can be used concurrently with the other functions.
		virtual void Execute(std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync) = 0;
		/// @brief Creates a secondary graphics command list.
		/// @return Secondary graphics command list.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ISecondaryGraphicsCommandList> CreateSecondaryGraphicsCommandList() = 0;

		/// @brief Checks if the swap chain is created and alive.
		/// @return @a True if it's alive; @a false otherwise.
		/// @note The function is thread-safe but can't be used concurrently with the @p CreateSwapChain() and @p DestroySwapChain().
		[[nodiscard("Pure function")]]
		virtual bool IsSwapChainAlive() const = 0;
		/// @brief Creates a swap chain.
		/// @param params Swap chain parameters.
		/// @note The backend mustn't have an alive swap chain, otherwise the function will fail.
		/// @note The function is thread-safe but can't be used concurrently with the @p IsSwapChainAlive() and @p DestroySwapChain().
		[[nodiscard("Pure function")]]
		virtual void CreateSwapChain(const SwapChainParams& params) = 0;
		/// @brief Destroys the swap chain.
		/// @note The function is thread-safe but can't be used concurrently with the @p IsSwapChainAlive() and @p CreateSwapChain().
		virtual void DestroySwapChain() = 0;
		/// @brief Gets the swap chain buffer count.
		/// @return Swap chain buffer count.
		/// @note The backend must have an alive swap chain, otherwise the function will fail.
		/// @note The function is thread-safe but can't be used concurrently with the @p CreateSwapChain() and @p DestroySwapChain().
		[[nodiscard("Pure function")]]
		virtual std::uint8_t SwapChainBufferCount() const = 0;
		/// @brief Gets the current swap chain buffer index.
		/// @return Current swap chain buffer index.
		/// @note The backend must have an alive swap chain, otherwise the function will fail.
		/// @note The function is thread-safe but can't be used concurrently with the @p CreateSwapChain() and @p DestroySwapChain().
		[[nodiscard("Pure function")]]
		virtual std::uint8_t CurrentSwapChainBufferIndex() const = 0;
		/// @brief Gets a swap chain buffer.
		/// @param bufferIndex Swap chain buffer index. Must be less than the @p CurrentSwapChainBufferIndex().
		/// @return Swap chain buffer.
		/// @note The backend must have an alive swap chain, otherwise the function will fail.
		/// @note The function is thread-safe but can't be used concurrently with the @p CreateSwapChain() and @p DestroySwapChain().
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ITexture> SwapChainBuffer(std::uint8_t bufferIndex) const = 0;
		/// @brief Presents a next swap chain buffer.
		/// @note The backend must have an alive swap chain, otherwise the function will fail.
		/// @note The function is thread-safe but can't be used concurrently with the @p CreateSwapChain() and @p DestroySwapChain().
		virtual void PresentNextSwapChainBuffer() = 0;

		/// @brief Creates a fence.
		/// @return Fence.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IFence> CreateFence() = 0;
		/// @brief Creates a waiter.
		/// @return Waiter.
		/// @note The function is thread-safe.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IWaiter> CreateWaiter() = 0;
	};
}
