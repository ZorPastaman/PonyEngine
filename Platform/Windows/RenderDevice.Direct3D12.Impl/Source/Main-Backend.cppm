/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:Backend;

import std;

import PonyEngine.Log;
import PonyEngine.Meta;
import PonyEngine.RenderDevice.Ext;

import :Engine;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Direct3D12 backend.
	class Backend final : public IBackend
	{
	public:
		/// @brief Creates a Direct3D12 backend.
		/// @param renderDevice Render device container.
		[[nodiscard("Pure constructor")]]
		explicit Backend(IRenderDeviceContext& renderDevice) noexcept;
		Backend(const Backend&) = delete;
		Backend(Backend&&) = delete;

		~Backend() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::string_view RenderAPIName() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual Meta::Version RenderAPIVersion() const noexcept override;

		virtual void Activate() override;
		virtual void Deactivate() override;

		[[nodiscard("Pure function")]]
		virtual struct DeviceSupport DeviceSupport() const override;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IBuffer> CreateBuffer(const CommittedResourceHeapParams& heapParams, const BufferParams& params) override;

		[[nodiscard("Pure function")]]
		virtual struct TextureFormatSupport TextureFormatSupport(TextureFormatID textureFormatId) const override;
		[[nodiscard("Pure function")]]
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const override;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ITexture> CreateTexture(const CommittedResourceHeapParams& heapParams, const TextureParams& params) override;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range) const override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t GetCopyableFootprintCount(const ITexture& texture, const SubTextureRange& range) const override;
		virtual CopyableFootprintSize GetCopyableFootprints(const TextureParams& params, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints) const override;
		virtual CopyableFootprintSize GetCopyableFootprints(const ITexture& texture, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints) const override;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IShaderDataContainer> CreateShaderDataContainer(const ShaderDataContainerParams& params) override;
		virtual void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const CBVParams& params) override;
		virtual void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const BufferSRVParams& params) override;
		virtual void CreateView(const ITexture* texture, IShaderDataContainer& container, std::uint32_t index, const TextureSRVParams& params) override;
		virtual void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const BufferUAVParams& params) override;
		virtual void CreateView(const ITexture* texture, IShaderDataContainer& container, std::uint32_t index, const TextureUAVParams& params) override;
		virtual void CopyViews(std::span<const ShaderDataCopyRange> ranges) override;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IRenderTargetContainer> CreateRenderTargetContainer(const RenderTargetContainerParams& params) override;
		virtual void CreateView(const ITexture* texture, IRenderTargetContainer& container, std::uint32_t index, const RTVParams& params) override;
		virtual void CopyViews(std::span<const RenderTargetCopyRange> ranges) override;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IDepthStencilContainer> CreateDepthStencilContainer(const DepthStencilContainerParams& params) override;
		virtual void CreateView(const ITexture* texture, IDepthStencilContainer& container, std::uint32_t index, const DSVParams& params) override;
		virtual void CopyViews(std::span<const DepthStencilCopyRange> ranges) override;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ISamplerContainer> CreateSamplerContainer(const SamplerContainerParams& params) override;
		virtual void CreateSampler(ISamplerContainer& container, std::uint32_t index, const SamplerParams& params) override;
		virtual void CopySamplers(std::span<const SamplerCopyRange> ranges) override;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IPipelineLayout> CreatePipelineLayout(const PipelineLayoutParams& params) override;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IGraphicsPipelineState> CreateGraphicsPipelineState(const std::shared_ptr<const IPipelineLayout>& layout, 
			const GraphicsPipelineStateParams& params) override;
		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<IComputePipelineState> CreateComputePipelineState(const std::shared_ptr<const IPipelineLayout>& layout, const ComputePipelineStateParams& params) override;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IGraphicsCommandList> CreateGraphicsCommandList() override;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IComputeCommandList> CreateComputeCommandList() override;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ICopyCommandList> CreateCopyCommandList() override;
		virtual void Execute(std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync) override;
		virtual void Execute(std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync) override;
		virtual void Execute(std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync) override;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ISecondaryGraphicsCommandList> CreateSecondaryGraphicsCommandList() override;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IFence> CreateFence() override;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IWaiter> CreateWaiter() override;

		[[nodiscard("Pure function")]]
		virtual bool IsSwapChainAlive() const override;
		[[nodiscard("Pure function")]]
		virtual void CreateSwapChain(const SwapChainParams& params) override;
		virtual void DestroySwapChain() override;
		[[nodiscard("Pure function")]]
		virtual std::uint8_t SwapChainBufferCount() const override;
		[[nodiscard("Pure function")]]
		virtual std::uint8_t CurrentSwapChainBufferIndex() const override;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ITexture> SwapChainBuffer(std::uint8_t bufferIndex) const override;
		virtual void PresentNextSwapChainBuffer() override;

		Backend& operator =(const Backend&) = delete;
		Backend& operator =(Backend&&) = delete;

	private:
		IRenderDeviceContext* renderDevice; ///< Render device context.

		std::unique_ptr<Engine> engine; ///< Direct3D12 engine. It's alive only if the backend is active.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Backend::Backend(IRenderDeviceContext& renderDevice) noexcept :
		renderDevice{&renderDevice}
	{
	}

	std::string_view Backend::RenderAPIName() const noexcept
	{
		return Engine::APIName;
	}

	Meta::Version Backend::RenderAPIVersion() const noexcept
	{
		return Engine::APIVersion;
	}

	void Backend::Activate()
	{
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Creating D3D12 engine...");
		engine = std::make_unique<Engine>(*renderDevice);
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Creating D3D12 engine done.");
	}

	void Backend::Deactivate()
	{
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Destroying D3D12 engine...");
		engine.reset();
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Destroying D3D12 engine done.");
	}

	struct DeviceSupport Backend::DeviceSupport() const
	{
		return RenderDevice::DeviceSupport
		{
			.shaderSupport = engine->ShaderSupport(),
			.viewSupport = ViewSupport{.cbvRequirement = CBVRequirement{.offsetAlignment = Engine::CBVAlignment, .sizeAlignment = Engine::CBVAlignment}},
			.samplerSupport = SamplerSupport{.maxAnisotropy = Engine::MaxAnisotropy},
			.rasterizerSupport = engine->RasterizerSupport(),
			.swapChainSupport = engine->SwapChainSupport(),
			.resourceSupport = ResourceSupport{.bufferHeaps = Engine::BufferHeapTypeSupport, .textureHeaps = Engine::TextureHeapTypeSupport},
			.fenceSupport = FenceSupport{.simultaneousWaitedFences = Engine::MaxSimultaneousFences}
		};
	}

	std::shared_ptr<IBuffer> Backend::CreateBuffer(const CommittedResourceHeapParams& heapParams, const BufferParams& params)
	{
		return engine->CreateBuffer(heapParams, params);
	}

	struct TextureFormatSupport Backend::TextureFormatSupport(const TextureFormatID textureFormatId) const
	{
		return engine->TextureFormatSupport(textureFormatId);
	}

	TextureSupportResponse Backend::TextureSupport(const TextureSupportRequest& request) const
	{
		return engine->TextureSupport(request);
	}

	std::shared_ptr<ITexture> Backend::CreateTexture(const CommittedResourceHeapParams& heapParams, const TextureParams& params)
	{
		return engine->CreateTexture(heapParams, params);
	}

	std::uint32_t Backend::GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range) const
	{
		return engine->GetCopyableFootprintCount(params, range);
	}

	std::uint32_t Backend::GetCopyableFootprintCount(const ITexture& texture, const SubTextureRange& range) const
	{
		return engine->GetCopyableFootprintCount(texture, range);
	}

	CopyableFootprintSize Backend::GetCopyableFootprints(const TextureParams& params, const std::uint64_t offset, const SubTextureRange& range,
		const std::span<CopyableFootprint> footprints) const
	{
		return engine->GetCopyableFootprints(params, offset, range, footprints);
	}

	CopyableFootprintSize Backend::GetCopyableFootprints(const ITexture& texture, const std::uint64_t offset, const SubTextureRange& range,
		const std::span<CopyableFootprint> footprints) const
	{
		return engine->GetCopyableFootprints(texture, offset, range, footprints);
	}

	std::shared_ptr<IShaderDataContainer> Backend::CreateShaderDataContainer(const ShaderDataContainerParams& params)
	{
		return engine->CreateShaderDataContainer(params);
	}

	void Backend::CreateView(const IBuffer* const buffer, IShaderDataContainer& container, const std::uint32_t index, const CBVParams& params)
	{
		engine->CreateView(buffer, container, index, params);
	}

	void Backend::CreateView(const IBuffer* const buffer, IShaderDataContainer& container, const std::uint32_t index, const BufferSRVParams& params)
	{
		engine->CreateView(buffer, container, index, params);
	}

	void Backend::CreateView(const ITexture* const texture, IShaderDataContainer& container, const std::uint32_t index, const TextureSRVParams& params)
	{
		engine->CreateView(texture, container, index, params);
	}

	void Backend::CreateView(const IBuffer* const buffer, IShaderDataContainer& container, const std::uint32_t index, const BufferUAVParams& params)
	{
		engine->CreateView(buffer, container, index, params);
	}

	void Backend::CreateView(const ITexture* const texture, IShaderDataContainer& container, const std::uint32_t index, const TextureUAVParams& params)
	{
		engine->CreateView(texture, container, index, params);
	}

	void Backend::CopyViews(const std::span<const ShaderDataCopyRange> ranges)
	{
		engine->CopyViews(ranges);
	}

	std::shared_ptr<IRenderTargetContainer> Backend::CreateRenderTargetContainer(const RenderTargetContainerParams& params)
	{
		return engine->CreateRenderTargetContainer(params);
	}

	void Backend::CreateView(const ITexture* const texture, IRenderTargetContainer& container, const std::uint32_t index, const RTVParams& params)
	{
		engine->CreateView(texture, container, index, params);
	}

	void Backend::CopyViews(const std::span<const RenderTargetCopyRange> ranges)
	{
		engine->CopyViews(ranges);
	}

	std::shared_ptr<IDepthStencilContainer> Backend::CreateDepthStencilContainer(const DepthStencilContainerParams& params)
	{
		return engine->CreateDepthStencilContainer(params);
	}

	void Backend::CreateView(const ITexture* const texture, IDepthStencilContainer& container, const std::uint32_t index, const DSVParams& params)
	{
		engine->CreateView(texture, container, index, params);
	}

	void Backend::CopyViews(const std::span<const DepthStencilCopyRange> ranges)
	{
		engine->CopyViews(ranges);
	}

	std::shared_ptr<ISamplerContainer> Backend::CreateSamplerContainer(const SamplerContainerParams& params)
	{
		return engine->CreateSamplerContainer(params);
	}

	void Backend::CreateSampler(ISamplerContainer& container, const std::uint32_t index, const SamplerParams& params)
	{
		engine->CreateSampler(container, index, params);
	}

	void Backend::CopySamplers(const std::span<const SamplerCopyRange> ranges)
	{
		engine->CopySamplers(ranges);
	}

	std::shared_ptr<IPipelineLayout> Backend::CreatePipelineLayout(const PipelineLayoutParams& params)
	{
		return engine->CreatePipelineLayout(params);
	}

	std::shared_ptr<IGraphicsPipelineState> Backend::CreateGraphicsPipelineState(const std::shared_ptr<const IPipelineLayout>& layout, 
		const GraphicsPipelineStateParams& params)
	{
		return engine->CreateGraphicsPipelineState(layout, params);
	}

	std::shared_ptr<IComputePipelineState> Backend::CreateComputePipelineState(const std::shared_ptr<const IPipelineLayout>& layout, const ComputePipelineStateParams& params)
	{
		return engine->CreateComputePipelineState(layout, params);
	}

	std::shared_ptr<IGraphicsCommandList> Backend::CreateGraphicsCommandList()
	{
		return engine->CreateGraphicsCommandList();
	}

	std::shared_ptr<IComputeCommandList> Backend::CreateComputeCommandList()
	{
		return engine->CreateComputeCommandList();
	}

	std::shared_ptr<ICopyCommandList> Backend::CreateCopyCommandList()
	{
		return engine->CreateCopyCommandList();
	}

	void Backend::Execute(const std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync)
	{
		engine->Execute(commandLists, sync);
	}

	void Backend::Execute(const std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync)
	{
		engine->Execute(commandLists, sync);
	}

	void Backend::Execute(const std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync)
	{
		engine->Execute(commandLists, sync);
	}

	std::shared_ptr<ISecondaryGraphicsCommandList> Backend::CreateSecondaryGraphicsCommandList()
	{
		return engine->CreateSecondaryGraphicsCommandList();
	}

	std::shared_ptr<IFence> Backend::CreateFence()
	{
		return engine->CreateFence();
	}

	std::shared_ptr<IWaiter> Backend::CreateWaiter()
	{
		return engine->CreateWaiter();
	}

	bool Backend::IsSwapChainAlive() const
	{
		return engine->IsSwapChainAlive();
	}

	void Backend::CreateSwapChain(const SwapChainParams& params)
	{
		engine->CreateSwapChain(params);
	}

	void Backend::DestroySwapChain()
	{
		engine->DestroySwapChain();
	}

	std::uint8_t Backend::SwapChainBufferCount() const
	{
		return engine->SwapChainBufferCount();
	}

	std::uint8_t Backend::CurrentSwapChainBufferIndex() const
	{
		return engine->CurrentSwapChainBufferIndex();
	}

	std::shared_ptr<ITexture> Backend::SwapChainBuffer(const std::uint8_t bufferIndex) const
	{
		return engine->SwapChainBuffer(bufferIndex);
	}

	void Backend::PresentNextSwapChainBuffer()
	{
		engine->PresentNextSwapChainBuffer();
	}
}
