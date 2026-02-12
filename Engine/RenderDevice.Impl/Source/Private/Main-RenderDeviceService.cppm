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

export module PonyEngine.RenderDevice.Impl:RenderDeviceService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Hash;
import PonyEngine.Log;
import PonyEngine.Meta;
import PonyEngine.RenderDevice.Ext;

import :BackendContainer;

export namespace PonyEngine::RenderDevice
{
	class RenderDeviceService final : public Application::IService, public IRenderDeviceModuleContext, private IRenderDeviceService, private IRenderDeviceContext
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit RenderDeviceService(Application::IApplicationContext& application) noexcept;
		RenderDeviceService(const RenderDeviceService&) = delete;
		RenderDeviceService(RenderDeviceService&&) = delete;

		~RenderDeviceService() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void AddInterfaces(Application::IServiceInterfaceAdder& adder) override;

		[[nodiscard("Must be used to remove")]]
		virtual BackendHandle AddBackend(const std::function<std::shared_ptr<IBackend>(IRenderDeviceContext&)>& factory) override;
		virtual void RemoveBackend(BackendHandle backendHandle) override;

		RenderDeviceService& operator =(const RenderDeviceService&) = delete;
		RenderDeviceService& operator =(RenderDeviceService&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		virtual std::size_t BackendCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view RenderApiName(std::size_t backendIndex) const override;
		[[nodiscard("Pure function")]]
		virtual Meta::Version RenderApiVersion(std::size_t backendIndex) const override;
		[[nodiscard("Pure function")]]
		virtual std::optional<std::size_t> ActiveBackend() const noexcept override;
		virtual void SwitchBackend(std::optional<std::size_t> backendIndex) override;

		[[nodiscard("Pure function")]]
		virtual struct DeviceSupport DeviceSupport() const override;

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IBuffer> CreateBuffer(HeapType heapType, const BufferParams& params) override;

		[[nodiscard("Wierd call")]]
		virtual struct TextureFormatId TextureFormatId(std::string_view textureFormat) override;
		[[nodiscard("Pure function")]]
		virtual std::string_view TextureFormat(struct TextureFormatId textureFormatId) const override;
		[[nodiscard("Pure function")]]
		virtual bool IsValid(struct TextureFormatId textureFormatId) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual struct TextureFormatSupport TextureFormatSupport(struct TextureFormatId textureFormatId) const override;
		[[nodiscard("Pure function")]]
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const override;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<ITexture> CreateTexture(HeapType heapType, const TextureParams& params) override;

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

		[[nodiscard("Pure function")]]
		virtual std::uint32_t GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range) const override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t GetCopyableFootprintCount(const ITexture& texture, const SubTextureRange& range) const override;
		virtual CopyableFootprintSize GetCopyableFootprints(const TextureParams& params, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints) const override;
		virtual CopyableFootprintSize GetCopyableFootprints(const ITexture& texture, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints) const override;

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

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IFence> CreateFence() override;
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IWaiter> CreateWaiter() override;

		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept override;

		void ActivateBackend(std::size_t index);
		void DeactivateBackend(std::size_t index);

		[[nodiscard("Pure function")]]
		IBackend& GetCurrentBackend();
		[[nodiscard("Pure function")]]
		const IBackend& GetCurrentBackend() const;
		[[nodiscard("Pure function")]]
		IBackend& GetBackend(std::size_t index);
		[[nodiscard("Pure function")]]
		const IBackend& GetBackend(std::size_t index) const;

		Application::IApplicationContext* application;

		BackendContainer backends;
		std::optional<std::size_t> activeBackendIndex;

		std::unordered_map<struct TextureFormatId, std::string> textureFormatHashMap;

		BackendHandle nextBackendHandle;
	};
}

namespace PonyEngine::RenderDevice
{
	RenderDeviceService::RenderDeviceService(Application::IApplicationContext& application) noexcept :
		application{&application},
		nextBackendHandle{.id = 1u}
	{
	}

	RenderDeviceService::~RenderDeviceService() noexcept
	{
		if (activeBackendIndex)
		{
			DeactivateBackend(*activeBackendIndex);
		}

		if (backends.Size() > 0uz) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Render backends weren't removed:");
			for (std::size_t i = 0uz; i < backends.Size(); ++i)
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Backend handle: '0x{:X}'.", backends.Handle(i).id);
			}
		}
	}

	void RenderDeviceService::Begin()
	{
	}

	void RenderDeviceService::End()
	{
	}

	void RenderDeviceService::AddInterfaces(Application::IServiceInterfaceAdder& adder)
	{
		adder.AddInterface<IRenderDeviceService>(*this);
	}

	BackendHandle RenderDeviceService::AddBackend(const std::function<std::shared_ptr<IBackend>(IRenderDeviceContext&)>& factory)
	{
#ifndef NDEBUG
		if (!nextBackendHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more backend handles available");
		}
		if (application->FlowState() != Application::FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Backends can be added only on start-up");
		}
#endif

		const std::shared_ptr<IBackend> backend = factory(*this);
#ifndef NDEBUG
		if (!backend) [[unlikely]]
		{
			throw std::invalid_argument("Backend is nullptr");
		}
		if (backends.IndexOf(*backend) < backends.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Backend has already been added");
		}
#endif

		const BackendHandle currentHandle = nextBackendHandle;
		backends.Add(currentHandle, backend);
		++nextBackendHandle.id;
		PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' backend added. Handle: '0x{:X}'.", typeid(*backend).name(), currentHandle.id);

		return currentHandle;
	}

	void RenderDeviceService::RemoveBackend(const BackendHandle backendHandle)
	{
#ifndef NDEBUG
		if (application->FlowState() != Application::FlowState::StartingUp && application->FlowState() != Application::FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Backend can be removed only on start-up or shut-down");
		}
#endif

		if (const std::size_t index = backends.IndexOf(backendHandle); index < backends.Size()) [[likely]]
		{
			if (index == activeBackendIndex)
			{
				SwitchBackend(std::nullopt);
			}

			const char* const backendName = typeid(backends.Backend(index)).name();
			backends.Remove(index);
			PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' backend removed. Handle: '0x{:X}'.", backendName, backendHandle.id);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Backend not found");
		}
	}

	std::size_t RenderDeviceService::BackendCount() const noexcept
	{
		return backends.Size();
	}

	std::string_view RenderDeviceService::RenderApiName(const std::size_t backendIndex) const
	{
		return GetBackend(backendIndex).RenderApiName();
	}

	Meta::Version RenderDeviceService::RenderApiVersion(const std::size_t backendIndex) const
	{
		return GetBackend(backendIndex).RenderApiVersion();
	}

	std::optional<std::size_t> RenderDeviceService::ActiveBackend() const noexcept
	{
		return activeBackendIndex;
	}

	void RenderDeviceService::SwitchBackend(const std::optional<std::size_t> backendIndex)
	{
#ifndef NDEBUG
		if (backendIndex && backendIndex >= backends.Size()) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}
#endif

		if (activeBackendIndex)
		{
			try
			{
				DeactivateBackend(*activeBackendIndex);
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On deactivating '{}' backend.", typeid(backends.Backend(*activeBackendIndex)).name());
				throw;
			}
		}

		activeBackendIndex = std::nullopt;
		
		if (backendIndex)
		{
			try
			{
				ActivateBackend(*backendIndex);
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On activating '{}' backend.", typeid(backends.Backend(*backendIndex)).name());
				throw;
			}
		}

		activeBackendIndex = backendIndex;
	}

	struct DeviceSupport RenderDeviceService::DeviceSupport() const
	{
		return GetCurrentBackend().DeviceSupport();
	}

	std::shared_ptr<IBuffer> RenderDeviceService::CreateBuffer(const HeapType heapType, const BufferParams& params)
	{
		return GetCurrentBackend().CreateBuffer(heapType, params);
	}

	struct TextureFormatId RenderDeviceService::TextureFormatId(const std::string_view textureFormat)
	{
		const auto textureFormatId = RenderDevice::TextureFormatId{.hash = Hash::FNV1a64(textureFormat)};

		if (const auto position = textureFormatHashMap.find(textureFormatId); position != textureFormatHashMap.cend())
		{
			if (position->second != textureFormat)
			{
				throw std::overflow_error("Hash collision");
			}
		}
		else
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Adding new texture format. TextureFormat: '{}'; TextureFormatHash: '{}'.", textureFormat, textureFormatId.hash);
			textureFormatHashMap[textureFormatId] = textureFormat;
		}

		return textureFormatId;
	}

	std::string_view RenderDeviceService::TextureFormat(const struct TextureFormatId textureFormatId) const
	{
		const auto position = textureFormatHashMap.find(textureFormatId);
#ifndef NDEBUG
		if (position == textureFormatHashMap.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture format ID");
		}
#endif

		return position->second;
	}

	bool RenderDeviceService::IsValid(const struct TextureFormatId textureFormatId) const noexcept
	{
		return textureFormatHashMap.contains(textureFormatId);
	}

	struct TextureFormatSupport RenderDeviceService::TextureFormatSupport(const struct TextureFormatId textureFormatId) const
	{
#ifndef NDEBUG
		if (!IsValid(textureFormatId)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid format");
		}
#endif

		return GetCurrentBackend().TextureFormatSupport(textureFormatId);
	}

	TextureSupportResponse RenderDeviceService::TextureSupport(const TextureSupportRequest& request) const
	{
#ifndef NDEBUG
		if (!IsValid(request.format)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid format");
		}
#endif

		return GetCurrentBackend().TextureSupport(request);
	}

	std::shared_ptr<ITexture> RenderDeviceService::CreateTexture(const HeapType heapType, const TextureParams& params)
	{
		return GetCurrentBackend().CreateTexture(heapType, params);
	}

	std::shared_ptr<IShaderDataContainer> RenderDeviceService::CreateShaderDataContainer(const ShaderDataContainerParams& params)
	{
		return GetCurrentBackend().CreateShaderDataContainer(params);
	}

	void RenderDeviceService::CreateView(const IBuffer* const buffer, IShaderDataContainer& container, const std::uint32_t index, const CBVParams& params)
	{
		GetCurrentBackend().CreateView(buffer, container, index, params);
	}

	void RenderDeviceService::CreateView(const IBuffer* const buffer, IShaderDataContainer& container, const std::uint32_t index, const BufferSRVParams& params)
	{
		GetCurrentBackend().CreateView(buffer, container, index, params);
	}

	void RenderDeviceService::CreateView(const ITexture* const texture, IShaderDataContainer& container, const std::uint32_t index, const TextureSRVParams& params)
	{
		GetCurrentBackend().CreateView(texture, container, index, params);
	}

	void RenderDeviceService::CreateView(const IBuffer* const buffer, IShaderDataContainer& container, const std::uint32_t index, const BufferUAVParams& params)
	{
		GetCurrentBackend().CreateView(buffer, container, index, params);
	}

	void RenderDeviceService::CreateView(const ITexture* const texture, IShaderDataContainer& container, const std::uint32_t index, const TextureUAVParams& params)
	{
		GetCurrentBackend().CreateView(texture, container, index, params);
	}

	void RenderDeviceService::CopyViews(const std::span<const ShaderDataCopyRange> ranges)
	{
		GetCurrentBackend().CopyViews(ranges);
	}

	std::shared_ptr<IRenderTargetContainer> RenderDeviceService::CreateRenderTargetContainer(const RenderTargetContainerParams& params)
	{
		return GetCurrentBackend().CreateRenderTargetContainer(params);
	}

	void RenderDeviceService::CreateView(const ITexture* const texture, IRenderTargetContainer& container, const std::uint32_t index, const RTVParams& params)
	{
		GetCurrentBackend().CreateView(texture, container, index, params);
	}

	void RenderDeviceService::CopyViews(const std::span<const RenderTargetCopyRange> ranges)
	{
		GetCurrentBackend().CopyViews(ranges);
	}

	std::shared_ptr<IDepthStencilContainer> RenderDeviceService::CreateDepthStencilContainer(const DepthStencilContainerParams& params)
	{
		return GetCurrentBackend().CreateDepthStencilContainer(params);
	}

	void RenderDeviceService::CreateView(const ITexture* const texture, IDepthStencilContainer& container, const std::uint32_t index, const DSVParams& params)
	{
		GetCurrentBackend().CreateView(texture, container, index, params);
	}

	void RenderDeviceService::CopyViews(const std::span<const DepthStencilCopyRange> ranges)
	{
		GetCurrentBackend().CopyViews(ranges);
	}

	std::shared_ptr<ISamplerContainer> RenderDeviceService::CreateSamplerContainer(const SamplerContainerParams& params)
	{
		return GetCurrentBackend().CreateSamplerContainer(params);
	}

	void RenderDeviceService::CreateSampler(ISamplerContainer& container, const std::uint32_t index, const SamplerParams& params)
	{
		GetCurrentBackend().CreateSampler(container, index, params);
	}

	void RenderDeviceService::CopySamplers(const std::span<const SamplerCopyRange> ranges)
	{
		GetCurrentBackend().CopySamplers(ranges);
	}

	std::shared_ptr<IPipelineLayout> RenderDeviceService::CreatePipelineLayout(const PipelineLayoutParams& params)
	{
		return GetCurrentBackend().CreatePipelineLayout(params);
	}

	std::shared_ptr<IGraphicsPipelineState> RenderDeviceService::CreateGraphicsPipelineState(const std::shared_ptr<const IPipelineLayout>& layout, 
		const GraphicsPipelineStateParams& params)
	{
		return GetCurrentBackend().CreateGraphicsPipelineState(layout, params);
	}

	std::shared_ptr<IComputePipelineState> RenderDeviceService::CreateComputePipelineState(
		const std::shared_ptr<const IPipelineLayout>& layout, const ComputePipelineStateParams& params)
	{
		return GetCurrentBackend().CreateComputePipelineState(layout, params);
	}

	std::shared_ptr<IGraphicsCommandList> RenderDeviceService::CreateGraphicsCommandList()
	{
		return GetCurrentBackend().CreateGraphicsCommandList();
	}

	std::shared_ptr<IComputeCommandList> RenderDeviceService::CreateComputeCommandList()
	{
		return GetCurrentBackend().CreateComputeCommandList();
	}

	std::shared_ptr<ICopyCommandList> RenderDeviceService::CreateCopyCommandList()
	{
		return GetCurrentBackend().CreateCopyCommandList();
	}

	void RenderDeviceService::Execute(const std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync)
	{
		GetCurrentBackend().Execute(commandLists, sync);
	}

	void RenderDeviceService::Execute(const std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync)
	{
		GetCurrentBackend().Execute(commandLists, sync);
	}

	void RenderDeviceService::Execute(const std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync)
	{
		GetCurrentBackend().Execute(commandLists, sync);
	}

	std::shared_ptr<ISecondaryGraphicsCommandList> RenderDeviceService::CreateSecondaryGraphicsCommandList()
	{
		return GetCurrentBackend().CreateSecondaryGraphicsCommandList();
	}

	std::uint32_t RenderDeviceService::GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range) const
	{
		return GetCurrentBackend().GetCopyableFootprintCount(params, range);
	}

	std::uint32_t RenderDeviceService::GetCopyableFootprintCount(const ITexture& texture, const SubTextureRange& range) const
	{
		return GetCurrentBackend().GetCopyableFootprintCount(texture, range);
	}

	CopyableFootprintSize RenderDeviceService::GetCopyableFootprints(const TextureParams& params, const std::uint64_t offset, const SubTextureRange& range,
		const std::span<CopyableFootprint> footprints) const
	{
		return GetCurrentBackend().GetCopyableFootprints(params, offset, range, footprints);
	}

	CopyableFootprintSize RenderDeviceService::GetCopyableFootprints(const ITexture& texture, const std::uint64_t offset, const SubTextureRange& range,
		const std::span<CopyableFootprint> footprints) const
	{
		return GetCurrentBackend().GetCopyableFootprints(texture, offset, range, footprints);
	}

	bool RenderDeviceService::IsSwapChainAlive() const
	{
		return GetCurrentBackend().IsSwapChainAlive();
	}

	void RenderDeviceService::CreateSwapChain(const SwapChainParams& params)
	{
		return GetCurrentBackend().CreateSwapChain(params);
	}

	void RenderDeviceService::DestroySwapChain()
	{
		GetCurrentBackend().DestroySwapChain();
	}

	std::uint8_t RenderDeviceService::SwapChainBufferCount() const
	{
		return GetCurrentBackend().SwapChainBufferCount();
	}

	std::uint8_t RenderDeviceService::CurrentSwapChainBufferIndex() const
	{
		return GetCurrentBackend().CurrentSwapChainBufferIndex();
	}

	std::shared_ptr<ITexture> RenderDeviceService::SwapChainBuffer(const std::uint8_t bufferIndex) const
	{
		return GetCurrentBackend().SwapChainBuffer(bufferIndex);
	}

	void RenderDeviceService::PresentNextSwapChainBuffer()
	{
		GetCurrentBackend().PresentNextSwapChainBuffer();
	}

	std::shared_ptr<IFence> RenderDeviceService::CreateFence()
	{
		return GetCurrentBackend().CreateFence();
	}

	std::shared_ptr<IWaiter> RenderDeviceService::CreateWaiter()
	{
		return GetCurrentBackend().CreateWaiter();
	}

	Application::IApplicationContext& RenderDeviceService::Application() noexcept
	{
		return *application;
	}

	const Application::IApplicationContext& RenderDeviceService::Application() const noexcept
	{
		return *application;
	}

	Log::ILogger& RenderDeviceService::Logger() noexcept
	{
		return application->Logger();
	}

	const Log::ILogger& RenderDeviceService::Logger() const noexcept
	{
		return application->Logger();
	}

	void RenderDeviceService::ActivateBackend(const std::size_t index)
	{
		IBackend& backend = backends.Backend(index);
		PONY_LOG(application->Logger(), Log::LogType::Info, "Activating '{}' backend...", typeid(backend).name());
		backend.Activate();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Activating '{}' backend done.", typeid(backend).name());
	}

	void RenderDeviceService::DeactivateBackend(const std::size_t index)
	{
		IBackend& backend = backends.Backend(index);
		PONY_LOG(application->Logger(), Log::LogType::Info, "Deactivating '{}' backend...", typeid(backend).name());
		backend.Deactivate();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Deactivating '{}' backend done.", typeid(backend).name());
	}

	IBackend& RenderDeviceService::GetCurrentBackend()
	{
#ifndef NDEBUG
		if (!activeBackendIndex) [[unlikely]]
		{
			throw std::logic_error("No active backend");
		}
#endif

		return backends.Backend(*activeBackendIndex);
	}

	const IBackend& RenderDeviceService::GetCurrentBackend() const
	{
#ifndef NDEBUG
		if (!activeBackendIndex) [[unlikely]]
		{
			throw std::logic_error("No active backend");
		}
#endif

		return backends.Backend(*activeBackendIndex);
	}

	IBackend& RenderDeviceService::GetBackend(const std::size_t index)
	{
#ifndef NDEBUG
		if (index >= backends.Size()) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}
#endif

		return backends.Backend(index);
	}

	const IBackend& RenderDeviceService::GetBackend(const std::size_t index) const
	{
#ifndef NDEBUG
		if (index >= backends.Size()) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}
#endif

		return backends.Backend(index);
	}
}
