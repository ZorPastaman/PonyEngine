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
import :ComputePipelineStateParams;
import :CopyableFootprint;
import :CopyableFootprintSize;
import :DepthStencilContainerParams;
import :DeviceSupport;
import :DSVParams;
import :GraphicsPipelineStateParams;
import :IBuffer;
import :IComputeCommandList;
import :IComputePipelineState;
import :ICopyCommandList;
import :IDepthStencilContainer;
import :IFence;
import :IGraphicsCommandList;
import :IGraphicsPipelineState;
import :IPipelineLayout;
import :IRenderDeviceServiceObserver;
import :IRenderTargetContainer;
import :ISamplerContainer;
import :ISecondaryGraphicsCommandList;
import :IShaderDataContainer;
import :ITexture;
import :IWaiter;
import :PipelineLayoutParams;
import :QueueSync;
import :RenderTargetContainerParams;
import :ResourceHeapParams;
import :RTVParams;
import :SamplerContainerParams;
import :SamplerParams;
import :ShaderDataContainerParams;
import :SRVParams;
import :SubTextureIndex;
import :SubTextureRange;
import :SwapChainParams;
import :TextureFormatID;
import :TextureFormatSupport;
import :TextureParams;
import :TextureSupportRequest;
import :TextureSupportResponse;
import :UAVParams;
import :ViewContainerCopyRange;

export namespace PonyEngine::RenderDevice
{
	/// @brief Render device service.
	class IRenderDeviceService
	{
		PONY_INTERFACE_BODY(IRenderDeviceService)

		/// @brief Gets the backend count.
		/// @return Backend count.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::size_t BackendCount() const noexcept = 0;
		/// @brief Gets a render API name.
		/// @param backendIndex Backend index. Must be less than the @p BackendCount().
		/// @return Render API name.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view RenderAPIName(std::size_t backendIndex) const = 0;
		/// @brief Gets a render API version.
		/// @param backendIndex Backend index. Must be less than the @p BackendCount().
		/// @return Render API version.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual Meta::Version RenderAPIVersion(std::size_t backendIndex) const = 0;
		/// @brief Gets an active backend index.
		/// @return Active backend index; nullopt if no backend is active.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Pure function")]]
		virtual std::optional<std::size_t> ActiveBackend() const noexcept = 0;
		/// @brief Switches to a backend at the @p backendIndex.
		/// @param backendIndex Backend index to switch to. Nullopt means no backend. Must be nullopt or less than the @p BackendCount().
		/// @remark On a backend switch, all the backend data becomes invalid.
		/// @note The function isn't thread-safe.
		virtual void SwitchBackend(std::optional<std::size_t> backendIndex) = 0;

		/// @brief Gets a device support of an active backend.
		/// @return Device support.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Pure function")]]
		virtual struct DeviceSupport DeviceSupport() const = 0;

		/// @brief Creates a buffer.
		/// @param heapParams Buffer heap parameters.
		/// @param params Buffer parameters.
		/// @return Buffer.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		/// @note You must release a created buffer on a backend switch.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IBuffer> CreateBuffer(const CommittedResourceHeapParams& heapParams, const BufferParams& params) = 0;

		/// @brief Gets a texture format ID.
		/// @param textureFormat Texture format.
		/// @return Texture format ID.
		/// @note This function mustn't be called on different threads at the same time.
		/// @note This function mustn't be called while @p TextureFormat(TextureFormatID) or @p IsValid(TextureFormatID) is executing.
		[[nodiscard("Wierd call")]]
		virtual struct TextureFormatID TextureFormatID(std::string_view textureFormat) = 0;
		/// @brief Gets a texture format.
		/// @param textureFormatId Texture format ID.
		/// @return Texture format.
		/// @note The function mustn't be called concurrently with the @p TextureFormatID().
		[[nodiscard("Pure function")]]
		virtual std::string_view TextureFormat(struct TextureFormatID textureFormatId) const = 0;
		/// @brief Checks if the texture format ID is valid.
		/// @param textureFormatId Texture format ID.
		/// @return @a True if it's valid; @a false otherwise.
		/// @note The function mustn't be called concurrently with the @p TextureFormatID().
		[[nodiscard("Pure function")]]
		virtual bool IsValid(struct TextureFormatID textureFormatId) const noexcept = 0;
		/// @brief Gets a texture format support.
		/// @param textureFormatId Texture format ID. Must be valid.
		/// @return Texture format support.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Pure function")]]
		virtual struct TextureFormatSupport TextureFormatSupport(struct TextureFormatID textureFormatId) const = 0;
		/// @brief Gets a texture support.
		/// @param request Texture support request.
		/// @return Texture support response.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Pure function")]]
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const = 0;
		/// @brief Creates a texture.
		/// @param heapParams Texture heap parameters.
		/// @param params Texture parameters.
		/// @return Texture.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		/// @note You must release a created texture on a backend switch.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ITexture> CreateTexture(const CommittedResourceHeapParams& heapParams, const TextureParams& params) = 0;

		/// @brief Gets a copyable footprint count for a texture created with the @p params.
		/// @param params Texture parameters.
		/// @param subTexture Sub-texture index.
		/// @return Copyable footprint count.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		/// @note The result becomes invalid on a backend switch.
		[[nodiscard("Pure function")]]
		std::uint32_t GetCopyableFootprintCount(const TextureParams& params, const SubTextureIndex& subTexture) const;
		/// @brief Gets a copyable footprint count for a texture created with the @p params.
		/// @param params Texture parameters.
		/// @param range Sub-texture range.
		/// @return Copyable footprint count.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		/// @note The result becomes invalid on a backend switch.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range) const = 0;
		/// @brief Gets a copyable footprint count for the texture.
		/// @param texture Texture.
		/// @param subTexture Sub-texture index.
		/// @return Copyable footprint count.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		/// @note The result becomes invalid on a backend switch.
		[[nodiscard("Pure function")]]
		std::uint32_t GetCopyableFootprintCount(const ITexture& texture, const SubTextureIndex& subTexture) const;
		/// @brief Gets a copyable footprint count for the texture.
		/// @param texture Texture.
		/// @param range Sub-texture range.
		/// @return Copyable footprint count.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		/// @note The result becomes invalid on a backend switch.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t GetCopyableFootprintCount(const ITexture& texture, const SubTextureRange& range) const = 0;
		/// @brief Gets copyable footprint for a texture created with the @p params.
		/// @param params Texture parameters.
		/// @param offset Texture buffer data offset.
		/// @param subTexture Sub-texture index.
		/// @param footprint Footprint.
		/// @return Copyable footprint size.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		/// @note The result becomes invalid on a backend switch.
		CopyableFootprintSize GetCopyableFootprint(const TextureParams& params, std::uint64_t offset, const SubTextureIndex& subTexture, CopyableFootprint* footprint = nullptr) const;
		/// @brief Gets copyable footprints for a texture created with the @p params.
		/// @param params Texture parameters.
		/// @param offset Texture buffer data offset.
		/// @param range Sub-texture range.
		/// @param footprints Footprints. Must be empty or its count must be equal to @p GetCopyableFootprintCount().
		/// @return Copyable footprint size.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		/// @note The result becomes invalid on a backend switch.
		virtual CopyableFootprintSize GetCopyableFootprints(const TextureParams& params, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints = std::span<CopyableFootprint>()) const = 0;
		/// @brief Gets copyable footprint for the texture.
		/// @param texture Texture.
		/// @param offset Texture buffer data offset.
		/// @param subTexture Sub-texture index.
		/// @param footprint Footprint.
		/// @return Copyable footprint size.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		/// @note The result becomes invalid on a backend switch.
		CopyableFootprintSize GetCopyableFootprint(const ITexture& texture, std::uint64_t offset, const SubTextureIndex& subTexture, CopyableFootprint* footprint = nullptr) const;
		/// @brief Gets copyable footprints for the texture.
		/// @param texture Texture.
		/// @param offset Texture buffer data offset.
		/// @param range Sub-texture range.
		/// @param footprints Footprints. Must be empty or its count must be equal to @p GetCopyableFootprintCount().
		/// @return Copyable footprint size.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		/// @note The result becomes invalid on a backend switch.
		virtual CopyableFootprintSize GetCopyableFootprints(const ITexture& texture, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints = std::span<CopyableFootprint>()) const = 0;

		/// @brief Creates a shader data container.
		/// @param params Container parameters.
		/// @return Shader data container.
		/// @remark The service must have an active backend.
		/// @note You must release a created container on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IShaderDataContainer> CreateShaderDataContainer(const ShaderDataContainerParams& params) = 0;
		/// @brief Creates a constant buffer view.
		/// @param buffer Target buffer. May be nullptr. If not nullptr, the buffer must have a shader resource usage.
		/// @param container Shader data container where a view will be created.
		/// @param index Container view index.
		/// @param params Constant buffer view parameters.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		virtual void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const CBVParams& params) = 0;
		/// @brief Creates a shader resource view.
		/// @param buffer Target buffer. May be nullptr. If not nullptr, the buffer must have a shader resource usage.
		/// @param container Shader data container where a view will be created.
		/// @param index Container view index.
		/// @param params Shader resource view parameters.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		virtual void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const BufferSRVParams& params) = 0;
		/// @brief Creates a shader resource view.
		/// @param texture Target texture. May be nullptr. If not nullptr, the texture must have a shader resource usage.
		/// @param container Shader data container where a view will be created.
		/// @param index Container view index.
		/// @param params Shader resource view parameters.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		virtual void CreateView(const ITexture* texture, IShaderDataContainer& container, std::uint32_t index, const TextureSRVParams& params) = 0;
		/// @brief Creates an unordered access view.
		/// @param buffer Target buffer. May be nullptr. If not nullptr, the buffer must have an unordered access usage.
		/// @param container Shader data container where a view will be created.
		/// @param index Container view index.
		/// @param params Unordered access view parameters.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		virtual void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const BufferUAVParams& params) = 0;
		/// @brief Creates an unordered access view.
		/// @param texture Target texture. May be nullptr. If not nullptr, the texture must have an unordered access usage.
		/// @param container Shader data container where a view will be created.
		/// @param index Container view index.
		/// @param params Unordered access view parameters.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		virtual void CreateView(const ITexture* texture, IShaderDataContainer& container, std::uint32_t index, const TextureUAVParams& params) = 0;
		/// @brief Copies views.
		/// @param ranges Copy ranges. Each element must have non-nullptr source and destination and valid spans to copy.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		virtual void CopyViews(std::span<const ShaderDataCopyRange> ranges) = 0;

		/// @brief Creates a render target container.
		/// @param params Container parameters.
		/// @return Render target container.
		/// @remark The service must have an active backend.
		/// @note You must release a created container on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IRenderTargetContainer> CreateRenderTargetContainer(const RenderTargetContainerParams& params) = 0;
		/// @brief Creates a render target view.
		/// @param texture Target texture. May be nullptr. If not nullptr, the texture must have a render target usage.
		/// @param container Render target container where a view will be created.
		/// @param index Container view index.
		/// @param params Render target view parameters.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		virtual void CreateView(const ITexture* texture, IRenderTargetContainer& container, std::uint32_t index, const RTVParams& params) = 0;
		/// @brief Copies views.
		/// @param ranges Copy ranges. Each element must have non-nullptr source and destination and valid spans to copy.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		virtual void CopyViews(std::span<const RenderTargetCopyRange> ranges) = 0;

		/// @brief Creates a depth stencil container.
		/// @param params Container parameters.
		/// @return Depth stencil container.
		/// @remark The service must have an active backend.
		/// @note You must release a created container on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IDepthStencilContainer> CreateDepthStencilContainer(const DepthStencilContainerParams& params) = 0;
		/// @brief Creates a depth stencil view.
		/// @param texture Target texture. May be nullptr. If not nullptr, the texture must have a depth stencil usage.
		/// @param container Depth stencil container where a view will be created.
		/// @param index Container view index.
		/// @param params Depth stencil view parameters.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		virtual void CreateView(const ITexture* texture, IDepthStencilContainer& container, std::uint32_t index, const DSVParams& params) = 0;
		/// @brief Copies views.
		/// @param ranges Copy ranges. Each element must have non-nullptr source and destination and valid spans to copy.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		virtual void CopyViews(std::span<const DepthStencilCopyRange> ranges) = 0;

		/// @brief Creates a sampler container.
		/// @param params Container parameters.
		/// @return Sampler container.
		/// @remark The service must have an active backend.
		/// @note You must release a created container on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ISamplerContainer> CreateSamplerContainer(const SamplerContainerParams& params) = 0;
		/// @brief Creates a sampler.
		/// @param container Sampler container.
		/// @param index Container index.
		/// @param params Sampler parameters.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		virtual void CreateSampler(ISamplerContainer& container, std::uint32_t index, const SamplerParams& params) = 0;
		/// @brief Copies samplers.
		/// @param ranges Copy ranges. Each element must have non-nullptr source and destination and valid spans to copy.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		virtual void CopySamplers(std::span<const SamplerCopyRange> ranges) = 0;

		/// @brief Creates a pipeline layout.
		/// @param params Pipeline layout parameters.
		/// @return Pipeline layout.
		/// @remark The service must have an active backend.
		/// @note You must release a created pipeline layout on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IPipelineLayout> CreatePipelineLayout(const PipelineLayoutParams& params) = 0;
		/// @brief Creates a graphics pipeline state.
		/// @param layout Pipeline layout. May be nullptr.
		/// @param params Pipeline state parameters.
		/// @return Graphics pipeline state.
		/// @remark The service must have an active backend.
		/// @note You must release a created pipeline state on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IGraphicsPipelineState> CreateGraphicsPipelineState(const std::shared_ptr<const IPipelineLayout>& layout, const GraphicsPipelineStateParams& params) = 0;
		/// @brief Creates a compute pipeline state.
		/// @param layout Pipeline layout. May be nullptr.
		/// @param params Pipeline state parameters.
		/// @return Compute pipeline state.
		/// @remark The service must have an active backend.
		/// @note You must release a created pipeline state on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IComputePipelineState> CreateComputePipelineState(const std::shared_ptr<const IPipelineLayout>& layout, const ComputePipelineStateParams& params) = 0;

		/// @brief Creates a graphics command list.
		/// @return Graphics command list.
		/// @remark The service must have an active backend.
		/// @note You must release a created command list on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IGraphicsCommandList> CreateGraphicsCommandList() = 0;
		/// @brief Creates a compute command list.
		/// @return Compute command list.
		/// @remark The service must have an active backend.
		/// @note You must release a created command list on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IComputeCommandList> CreateComputeCommandList() = 0;
		/// @brief Creates a copy command list.
		/// @return Copy command list.
		/// @remark The service must have an active backend.
		/// @note You must release a created command list on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ICopyCommandList> CreateCopyCommandList() = 0;
		/// @brief Syncs the graphics command queue.
		/// @param sync Queue sync.
		/// @remark The service must have an active backend.
		/// @note The function can't be used concurrently with the @p SwitchBackend() and other @p Execute() and Sync*() functions but can be used concurrently with the other functions.
		void SyncGraphics(const QueueSync& sync);
		/// @brief Executes the graphics command list.
		/// @param commandList Graphics command list to execute.
		/// @param sync Queue sync.
		/// @remark The service must have an active backend.
		/// @note All the resources used by the command lists must be kept alive till the finish of the execution.
		/// @note The function can't be used concurrently with the @p SwitchBackend() and other @p Execute() and Sync*() functions but can be used concurrently with the other functions.
		void Execute(const IGraphicsCommandList& commandList, const QueueSync& sync = QueueSync{});
		/// @brief Executes the graphics command lists.
		/// @param commandLists Graphics command lists to execute. May be empty.
		/// @param sync Queue sync.
		/// @remark The service must have an active backend.
		/// @note All the resources used by the command lists must be kept alive till the finish of the execution.
		/// @note The function can't be used concurrently with the @p SwitchBackend() and other @p Execute() and Sync*() functions but can be used concurrently with the other functions.
		virtual void Execute(std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync = QueueSync{}) = 0;
		/// @brief Syncs the compute command queue.
		/// @param sync Queue sync.
		/// @remark The service must have an active backend.
		/// @note The function can't be used concurrently with the @p SwitchBackend() and other @p Execute() and Sync*() functions but can be used concurrently with the other functions.
		void SyncCompute(const QueueSync& sync);
		/// @brief Executes the compute command list.
		/// @param commandList Compute command list to execute.
		/// @param sync Queue sync.
		/// @remark The service must have an active backend.
		/// @note All the resources used by the command lists must be kept alive till the finish of the execution.
		/// @note The function can't be used concurrently with the @p SwitchBackend() and other @p Execute() and Sync*() functions but can be used concurrently with the other functions.
		void Execute(const IComputeCommandList& commandList, const QueueSync& sync = QueueSync{});
		/// @brief Executes the compute command lists.
		/// @param commandLists Compute command lists to execute. May be empty.
		/// @param sync Queue sync.
		/// @remark The service must have an active backend.
		/// @note All the resources used by the command lists must be kept alive till the finish of the execution.
		/// @note The function can't be used concurrently with the @p SwitchBackend() and other @p Execute() and Sync*() functions but can be used concurrently with the other functions.
		virtual void Execute(std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync = QueueSync{}) = 0;
		/// @brief Syncs the copy command queue.
		/// @param sync Queue sync.
		/// @remark The service must have an active backend.
		/// @note The function can't be used concurrently with the @p SwitchBackend() and other @p Execute() and Sync*() functions but can be used concurrently with the other functions.
		void SyncCopy(const QueueSync& sync);
		/// @brief Executes the copy command list.
		/// @param commandList Copy command list to execute.
		/// @param sync Queue sync.
		/// @remark The service must have an active backend.
		/// @note All the resources used by the command lists must be kept alive till the finish of the execution.
		/// @note The function can't be used concurrently with the @p SwitchBackend() and other @p Execute() and Sync*() functions but can be used concurrently with the other functions.
		void Execute(const ICopyCommandList& commandList, const QueueSync& sync = QueueSync{});
		/// @brief Executes the copy command lists.
		/// @param commandLists Copy command lists to execute. May be empty.
		/// @param sync Queue sync.
		/// @remark The service must have an active backend.
		/// @note All the resources used by the command lists must be kept alive till the finish of the execution.
		/// @note The function can't be used concurrently with the @p SwitchBackend() and other @p Execute() functions but can be used concurrently with the other functions.
		virtual void Execute(std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync = QueueSync{}) = 0;
		/// @brief Creates a secondary graphics command list.
		/// @return Secondary graphics command list.
		/// @remark The service must have an active backend.
		/// @note You must release a created command list on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ISecondaryGraphicsCommandList> CreateSecondaryGraphicsCommandList() = 0;

		/// @brief Checks if the swap chain is created and alive.
		/// @return @a True if it's alive; @a false otherwise.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend(), @p CreateSwapChain() and @p DestroySwapChain().
		[[nodiscard("Pure function")]]
		virtual bool IsSwapChainAlive() const = 0;
		/// @brief Creates a swap chain.
		/// @param params Swap chain parameters.
		/// @remark The service must have an active backend.
		/// @note The backend mustn't have an alive swap chain, otherwise the function will fail.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend(), @p IsSwapChainAlive() and @p DestroySwapChain().
		[[nodiscard("Pure function")]]
		virtual void CreateSwapChain(const SwapChainParams& params) = 0;
		/// @brief Destroys the swap chain.
		/// @remark The service must have an active backend.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend(), @p IsSwapChainAlive() and @p CreateSwapChain().
		virtual void DestroySwapChain() = 0;
		/// @brief Gets the swap chain buffer count.
		/// @return Swap chain buffer count.
		/// @remark The service must have an active backend.
		/// @note The backend must have an alive swap chain, otherwise the function will fail.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend(), @p CreateSwapChain() and @p DestroySwapChain().
		[[nodiscard("Pure function")]]
		virtual std::uint8_t SwapChainBufferCount() const = 0;
		/// @brief Gets the current swap chain buffer index.
		/// @return Current swap chain buffer index.
		/// @remark The service must have an active backend.
		/// @note The backend must have an alive swap chain, otherwise the function will fail.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend(), @p CreateSwapChain() and @p DestroySwapChain().
		[[nodiscard("Pure function")]]
		virtual std::uint8_t CurrentSwapChainBufferIndex() const = 0;
		/// @brief Gets a swap chain buffer.
		/// @param bufferIndex Swap chain buffer index. Must be less than the @p CurrentSwapChainBufferIndex().
		/// @return Swap chain buffer.
		/// @remark The service must have an active backend.
		/// @note The backend must have an alive swap chain, otherwise the function will fail.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend(), @p CreateSwapChain() and @p DestroySwapChain().
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ITexture> SwapChainBuffer(std::uint8_t bufferIndex) const = 0;
		/// @brief Presents a next swap chain buffer.
		/// @remark The service must have an active backend.
		/// @note The backend must have an alive swap chain, otherwise the function will fail.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend(), @p CreateSwapChain() and @p DestroySwapChain().
		virtual void PresentNextSwapChainBuffer() = 0;

		/// @brief Creates a fence.
		/// @return Fence.
		/// @remark The service must have an active backend.
		/// @note You must release a created fence on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IFence> CreateFence() = 0;
		/// @brief Creates a waiter.
		/// @return Waiter.
		/// @remark The service must have an active backend.
		/// @note You must release a created waiter on a backend switch.
		/// @note The function is thread-safe but can't be used concurrently with the @p SwitchBackend().
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IWaiter> CreateWaiter() = 0;

		/// @brief Adds a render device service observer.
		/// @param observer Observer to add.
		/// @note The function isn't thread safe and mustn't be called concurrently with the @p SwitchBackend() and @p RemoveObserver().
		virtual void AddObserver(IRenderDeviceServiceObserver& observer) = 0;
		/// @brief Removes a render device service observer.
		/// @param observer Observer to remove.
		/// @note The function isn't thread safe and mustn't be called concurrently with the @p SwitchBackend() and @p AddObserver().
		virtual void RemoveObserver(IRenderDeviceServiceObserver& observer) noexcept = 0;
	};
}

namespace PonyEngine::RenderDevice
{
	std::uint32_t IRenderDeviceService::GetCopyableFootprintCount(const TextureParams& params, const SubTextureIndex& subTexture) const
	{
		return GetCopyableFootprintCount(params, ToRange(subTexture));
	}

	std::uint32_t IRenderDeviceService::GetCopyableFootprintCount(const ITexture& texture, const SubTextureIndex& subTexture) const
	{
		return GetCopyableFootprintCount(texture, ToRange(subTexture));
	}

	CopyableFootprintSize IRenderDeviceService::GetCopyableFootprint(const TextureParams& params, const std::uint64_t offset, const SubTextureIndex& subTexture, 
		CopyableFootprint* const footprint) const
	{
		return GetCopyableFootprints(params, offset, ToRange(subTexture), std::span(footprint, footprint));
	}

	CopyableFootprintSize IRenderDeviceService::GetCopyableFootprint(const ITexture& texture, const std::uint64_t offset, const SubTextureIndex& subTexture, 
		CopyableFootprint* const footprint) const
	{
		return GetCopyableFootprints(texture, offset, ToRange(subTexture), std::span(footprint, footprint));
	}

	void IRenderDeviceService::SyncGraphics(const QueueSync& sync)
	{
		Execute(std::span<const IGraphicsCommandList* const>(), sync);
	}

	void IRenderDeviceService::Execute(const IGraphicsCommandList& commandList, const QueueSync& sync)
	{
		const IGraphicsCommandList* const command = &commandList;
		Execute(std::span(&command, 1uz), sync);
	}

	void IRenderDeviceService::SyncCompute(const QueueSync& sync)
	{
		Execute(std::span<const IComputeCommandList* const>(), sync);
	}

	void IRenderDeviceService::Execute(const IComputeCommandList& commandList, const QueueSync& sync)
	{
		const IComputeCommandList* const command = &commandList;
		Execute(std::span(&command, 1uz), sync);
	}

	void IRenderDeviceService::SyncCopy(const QueueSync& sync)
	{
		Execute(std::span<const ICopyCommandList* const>(), sync);
	}

	void IRenderDeviceService::Execute(const ICopyCommandList& commandList, const QueueSync& sync)
	{
		const ICopyCommandList* const command = &commandList;
		Execute(std::span(&command, 1uz), sync);
	}
}
