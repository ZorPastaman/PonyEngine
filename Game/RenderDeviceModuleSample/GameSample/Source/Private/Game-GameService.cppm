export module Game:GameService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Math;
import PonyEngine.RenderDevice;

export namespace Game
{
	class GameService final : public PonyEngine::Application::IService, private PonyEngine::Application::ITickableService
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit GameService(PonyEngine::Application::IApplicationContext& application);
		GameService(const GameService&) = delete;
		GameService(GameService&&) = delete;

		~GameService() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void AddTickableServices(PonyEngine::Application::ITickableServiceAdder& adder) override;

		GameService& operator =(const GameService&) = delete;
		GameService& operator =(GameService&&) = delete;

	private:
		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		std::vector<std::byte> LoadShader(const std::filesystem::path& path);

		PonyEngine::Application::IApplicationContext* application;
		PonyEngine::RenderDevice::IRenderDeviceService* renderDevice;

		std::shared_ptr<PonyEngine::RenderDevice::IGraphicsCommandList> graphicsCommandList;
		std::shared_ptr<PonyEngine::RenderDevice::IComputeCommandList> computeCommandList;
		std::shared_ptr<PonyEngine::RenderDevice::ICopyCommandList> copyCommandList;
		std::shared_ptr<PonyEngine::RenderDevice::ISecondaryGraphicsCommandList> secondaryCommandList;

		std::shared_ptr<PonyEngine::RenderDevice::IFence> graphicsFence;
		std::shared_ptr<PonyEngine::RenderDevice::IFence> computeFence;
		std::shared_ptr<PonyEngine::RenderDevice::IFence> copyFence;
		std::uint64_t graphicsFenceValue = 0ull;
		std::uint64_t computeFenceValue = 0ull;
		std::uint64_t copyFenceValue = 0ull;
		std::shared_ptr<PonyEngine::RenderDevice::IWaiter> waiter;

		std::shared_ptr<PonyEngine::RenderDevice::ITexture> targetTexture;
		std::shared_ptr<PonyEngine::RenderDevice::ITexture> resolvedTexture;
		std::shared_ptr<PonyEngine::RenderDevice::ITexture> depthTexture;

		std::shared_ptr<PonyEngine::RenderDevice::IShaderDataContainer> stagingSrvContainer;
		std::shared_ptr<PonyEngine::RenderDevice::IShaderDataContainer> srvContainer;
		std::shared_ptr<PonyEngine::RenderDevice::IRenderTargetContainer> rtvContainer;
		std::shared_ptr<PonyEngine::RenderDevice::IDepthStencilContainer> dsvContainer;
		std::uint32_t resolvedTextureContainerIndex = 0;
		std::uint32_t renderTargetContainerIndex = 0;
		std::uint32_t backBufferContainerOffset = 0;
		std::uint32_t depthContainerIndex = 0;

		std::shared_ptr<PonyEngine::RenderDevice::IGraphicsPipelineState> boxPipelineState;
		std::shared_ptr<PonyEngine::RenderDevice::IGraphicsPipelineState> outputPipelineState;

		PonyEngine::Math::Vector2<std::uint32_t> resolution;
	};
}

namespace Game
{
	GameService::GameService(PonyEngine::Application::IApplicationContext& application) :
		application{&application},
		renderDevice{&this->application->GetService<PonyEngine::RenderDevice::IRenderDeviceService>()}
	{
		if (renderDevice->BackendCount() > 0uz)
		{
			renderDevice->SwitchBackend(0uz);
		}
		else
		{
			throw std::logic_error("No backend");
		}
	}

	GameService::~GameService() noexcept
	{
	}

	void GameService::Begin()
	{
		graphicsCommandList = renderDevice->CreateGraphicsCommandList();
		computeCommandList = renderDevice->CreateComputeCommandList();
		copyCommandList = renderDevice->CreateCopyCommandList();
		secondaryCommandList = renderDevice->CreateSecondaryGraphicsCommandList();
		graphicsFence = renderDevice->CreateFence();
		computeFence = renderDevice->CreateFence();
		copyFence = renderDevice->CreateFence();
		graphicsFenceValue = graphicsFence->CompletedValue();
		computeFenceValue = computeFence->CompletedValue();
		copyFenceValue = copyFence->CompletedValue();
		waiter = renderDevice->CreateWaiter();

		const PonyEngine::RenderDevice::TextureFormatId swapChainTextureFormat = renderDevice->TextureFormatId(PonyEngine::RenderDevice::TextureFormat::B8G8R8A8_Unorm);
		renderDevice->CreateSwapChain(PonyEngine::RenderDevice::SwapChainParams
		{
			.format = swapChainTextureFormat,
			.size = std::nullopt,
			.bufferCount = 3u,
			.alphaMode = PonyEngine::RenderDevice::SwapChainAlphaMode::Ignore,
			.scalingMode = PonyEngine::RenderDevice::SwapChainScaling::NoScaling,
			.swapEffect = PonyEngine::RenderDevice::SwapChainEffect::FlipDiscard,
			.syncMode = PonyEngine::RenderDevice::SwapChainSync::FullSync,
			.flags = PonyEngine::RenderDevice::SwapChainFlag::SRGB,
			.usage = PonyEngine::RenderDevice::TextureUsage::RenderTarget
		});
		const auto renderTargetTextureFormat = PonyEngine::RenderDevice::RenderTargetAttachmentFormat
		{
			.format = renderDevice->TextureFormatId(PonyEngine::RenderDevice::TextureFormat::R8G8B8A8_Unorm),
			.srgb = false
		};
		const PonyEngine::Math::Vector3<std::uint32_t> res = renderDevice->SwapChainBuffer(0u)->Size();
		resolution = PonyEngine::Math::Vector2<std::uint32_t>(res.X(), res.Y());
		const PonyEngine::RenderDevice::TextureFormatId depthStencilTextureFormat = renderDevice->TextureFormatId(PonyEngine::RenderDevice::TextureFormat::D32_Float_S8X24_Uint);
		constexpr auto sampleCount = PonyEngine::RenderDevice::SampleCount::X4;
		targetTexture = renderDevice->CreateTexture(PonyEngine::RenderDevice::ResourceHeapParams{.heapType = PonyEngine::RenderDevice::HeapType::Default}, 
			PonyEngine::RenderDevice::TextureParams
			{
				.format = renderTargetTextureFormat.format,
				.size = res,
				.clearValue = PonyEngine::Math::ColorRGBA<float>::Black(),
				.sampleCount = sampleCount,
				.usage = PonyEngine::RenderDevice::TextureUsage::RenderTarget,
				.initialLayout = PonyEngine::RenderDevice::ResourceLayout::RenderTarget
			});
		resolvedTexture = renderDevice->CreateTexture(PonyEngine::RenderDevice::ResourceHeapParams{.heapType = PonyEngine::RenderDevice::HeapType::Default}, 
			PonyEngine::RenderDevice::TextureParams
			{
				.format = renderTargetTextureFormat.format,
				.size = targetTexture->Size(),
				.clearValue = PonyEngine::RenderDevice::NoClear{},
				.sampleCount = PonyEngine::RenderDevice::SampleCount::X1,
				.usage = PonyEngine::RenderDevice::TextureUsage::ShaderResource,
				.initialLayout = PonyEngine::RenderDevice::ResourceLayout::ShaderResource
			});
		depthTexture = renderDevice->CreateTexture(PonyEngine::RenderDevice::ResourceHeapParams{.heapType = PonyEngine::RenderDevice::HeapType::Default}, 
			PonyEngine::RenderDevice::TextureParams
			{
				.format = depthStencilTextureFormat,
				.size = targetTexture->Size(),
				.clearValue = PonyEngine::RenderDevice::DepthStencil{},
				.sampleCount = sampleCount,
				.usage = PonyEngine::RenderDevice::TextureUsage::DepthStencil,
				.initialLayout = PonyEngine::RenderDevice::ResourceLayout::DepthStencilWrite
			});

		constexpr std::uint32_t srvCount = 1u;
		stagingSrvContainer = renderDevice->CreateShaderDataContainer(PonyEngine::RenderDevice::ShaderDataContainerParams
		{
			.size = srvCount,
			.shaderVisible = false
		});
		resolvedTextureContainerIndex = 0u;
		renderDevice->CreateView(resolvedTexture.get(), *stagingSrvContainer, resolvedTextureContainerIndex, PonyEngine::RenderDevice::TextureSRVParams
		{
			.format = renderTargetTextureFormat.format,
			.srgb = false,
			.layout = PonyEngine::RenderDevice::TextureSingleSRVLayout{}
		});
		srvContainer = renderDevice->CreateShaderDataContainer(PonyEngine::RenderDevice::ShaderDataContainerParams
		{
			.size = srvCount,
			.shaderVisible = true
		});
		const auto srvRange = PonyEngine::RenderDevice::ShaderDataCopyRange
		{
			.source = stagingSrvContainer.get(),
			.destination = srvContainer.get(),
			.count = srvCount
		};
		renderDevice->CopyViews(std::span(&srvRange, 1uz));
		rtvContainer = renderDevice->CreateRenderTargetContainer(PonyEngine::RenderDevice::RenderTargetContainerParams
		{
			.size = renderDevice->SwapChainBufferCount() + 1u
		});
		renderTargetContainerIndex = 0u;
		renderDevice->CreateView(targetTexture.get(), *rtvContainer, renderTargetContainerIndex, PonyEngine::RenderDevice::RTVParams
		{
			.format = renderTargetTextureFormat.format,
			.srgb = renderTargetTextureFormat.srgb,
			.dimension = PonyEngine::RenderDevice::TextureDimension::Texture2D,
			.layout = PonyEngine::RenderDevice::MSRTVLayout{}
		});
		backBufferContainerOffset = renderTargetContainerIndex + 1u;
		for (std::uint8_t i = 0u, containerIndex = backBufferContainerOffset; i < renderDevice->SwapChainBufferCount(); ++i, ++containerIndex)
		{
			renderDevice->CreateView(renderDevice->SwapChainBuffer(i).get(), *rtvContainer, containerIndex, PonyEngine::RenderDevice::RTVParams
			{
				.format = swapChainTextureFormat,
				.srgb = true,
				.dimension = PonyEngine::RenderDevice::TextureDimension::Texture2D,
				.layout = PonyEngine::RenderDevice::SingleRTVLayout{}
			});
		}
		dsvContainer = renderDevice->CreateDepthStencilContainer(PonyEngine::RenderDevice::DepthStencilContainerParams
		{
			.size = 1u
		});
		depthContainerIndex = 0u;
		renderDevice->CreateView(depthTexture.get(), *dsvContainer, depthContainerIndex, PonyEngine::RenderDevice::DSVParams
		{
			.format = depthStencilTextureFormat,
			.dimension = PonyEngine::RenderDevice::DSVDimension::Texture2D,
			.flags = PonyEngine::RenderDevice::DSVFlag::None,
			.layout = PonyEngine::RenderDevice::MSDSVLayout{}
		});

		constexpr auto contextRange = PonyEngine::RenderDevice::ShaderDataDescriptorRange
		{
			.type = PonyEngine::RenderDevice::ShaderDataDescriptorType::ConstantBuffer,
			.baseShaderRegister = 0u,
			.count = 1u
		};
		const auto contextDescriptorSet = PonyEngine::RenderDevice::DescriptorSet
		{
			.ranges = std::span<const PonyEngine::RenderDevice::ShaderDataDescriptorRange>(&contextRange, 1uz),
			.setIndex = 0u
		};
		constexpr auto meshletRange = PonyEngine::RenderDevice::ShaderDataDescriptorRange
		{
			.type = PonyEngine::RenderDevice::ShaderDataDescriptorType::BufferShaderResource,
			.baseShaderRegister = 0u,
			.count = 3u
		};
		const auto meshletDescriptorSet = PonyEngine::RenderDevice::DescriptorSet
		{
			.ranges = std::span<const PonyEngine::RenderDevice::ShaderDataDescriptorRange>(&meshletRange, 1uz),
			.setIndex = 1u
		};
		constexpr auto vertexRange = PonyEngine::RenderDevice::ShaderDataDescriptorRange
		{
			.type = PonyEngine::RenderDevice::ShaderDataDescriptorType::BufferShaderResource,
			.baseShaderRegister = 0u,
			.count = 1u
		};
		const auto vertexDescriptorSet = PonyEngine::RenderDevice::DescriptorSet
		{
			.ranges = std::span<const PonyEngine::RenderDevice::ShaderDataDescriptorRange>(&vertexRange, 1uz),
			.setIndex = 2u
		};
		constexpr auto materialRange = PonyEngine::RenderDevice::ShaderDataDescriptorRange
		{
			.type = PonyEngine::RenderDevice::ShaderDataDescriptorType::ConstantBuffer,
			.baseShaderRegister = 0u,
			.count = 1u
		};
		const auto materialDescriptorSet = PonyEngine::RenderDevice::DescriptorSet
		{
			.ranges = std::span<const PonyEngine::RenderDevice::ShaderDataDescriptorRange>(&materialRange, 1uz),
			.setIndex = 3u
		};
		const auto descriptorSets = std::array<PonyEngine::RenderDevice::DescriptorSet, 4>
		{
			contextDescriptorSet,
			meshletDescriptorSet,
			vertexDescriptorSet,
			materialDescriptorSet
		};
		const std::shared_ptr<PonyEngine::RenderDevice::IPipelineLayout> layout = renderDevice->CreatePipelineLayout(PonyEngine::RenderDevice::PipelineLayoutParams
		{
			.descriptorSets = descriptorSets
		});

		const std::vector<std::byte> triangleShader = LoadShader(TRIANGLE_SHADER);
		const std::vector<std::byte> pixelShader = LoadShader(PIXEL_SHADER);
		constexpr auto opaqueBlendParams = PonyEngine::RenderDevice::RenderTargetBlendParams
		{
			.blend = PonyEngine::RenderDevice::ColorBlendParams{},
		};
		boxPipelineState = renderDevice->CreateGraphicsPipelineState(layout, PonyEngine::RenderDevice::GraphicsPipelineStateParams
		{
			.meshShader = triangleShader,
			.pixelShader = pixelShader,
			.rasterizer = PonyEngine::RenderDevice::RasterizerParams{},
			.blend = PonyEngine::RenderDevice::BlendParams
			{
				.blendGroup = PonyEngine::RenderDevice::BlendGroupParams
				{
					.renderTargetBlend = std::span<const PonyEngine::RenderDevice::RenderTargetBlendParams>(&opaqueBlendParams, 1uz),
				}
			},
			.depthStencil = PonyEngine::RenderDevice::DepthStencilParams
			{
				.depth = PonyEngine::RenderDevice::DepthParams{},
				.stencil = PonyEngine::RenderDevice::StencilParams{}
			},
			.sample = PonyEngine::RenderDevice::SampleParams
			{
				.sampleCount = sampleCount
			},
			.attachmentParams = PonyEngine::RenderDevice::AttachmentParams
			{
				.renderTargetFormats = std::span<const PonyEngine::RenderDevice::RenderTargetAttachmentFormat>(&renderTargetTextureFormat, 1uz),
				.depthStencilFormat = depthStencilTextureFormat
			}
		});

		constexpr auto resolvedTextureRange = PonyEngine::RenderDevice::ShaderDataDescriptorRange
		{
			.type = PonyEngine::RenderDevice::ShaderDataDescriptorType::TextureShaderResource,
			.baseShaderRegister = 0u,
			.count = 1u
		};
		constexpr auto resolvedTextureSampler = PonyEngine::RenderDevice::StaticSamplerParams
		{
			.samplerParams = PonyEngine::RenderDevice::SamplerParams
			{
				.filter = PonyEngine::RenderDevice::BasicSamplerFilter
				{
					.min = PonyEngine::RenderDevice::Filter::Nearest,
					.mag = PonyEngine::RenderDevice::Filter::Nearest,
					.mip = PonyEngine::RenderDevice::Filter::Nearest
				},
				.addressU = PonyEngine::RenderDevice::SamplerAddressMode::Clamp,
				.addressV = PonyEngine::RenderDevice::SamplerAddressMode::Clamp,
				.addressW = PonyEngine::RenderDevice::SamplerAddressMode::Clamp,
			},
			.shaderRegister = 1u
		};
		const auto resolvedTextureDescriptorSet = PonyEngine::RenderDevice::DescriptorSet
		{
			.ranges = std::span(&resolvedTextureRange, 1uz),
			.staticSamplers = std::span(&resolvedTextureSampler, 1uz),
			.setIndex = 0u
		};
		const std::shared_ptr<PonyEngine::RenderDevice::IPipelineLayout> outputLayout = renderDevice->CreatePipelineLayout(PonyEngine::RenderDevice::PipelineLayoutParams
		{
			.descriptorSets = std::span(&resolvedTextureDescriptorSet, 1uz)
		});

		const std::vector<std::byte> fullscreenQuadShader = LoadShader(FULLSCREEN_QUAD_SHADER);
		const std::vector<std::byte> textureShader = LoadShader(TEXTURE_SHADER);
		const auto outputTextureFormat = PonyEngine::RenderDevice::RenderTargetAttachmentFormat
		{
			.format = renderDevice->TextureFormatId(PonyEngine::RenderDevice::TextureFormat::B8G8R8A8_Unorm),
			.srgb = true
		};
		outputPipelineState = renderDevice->CreateGraphicsPipelineState(outputLayout, PonyEngine::RenderDevice::GraphicsPipelineStateParams
		{
			.meshShader = fullscreenQuadShader,
			.pixelShader = textureShader,
			.rasterizer = PonyEngine::RenderDevice::RasterizerParams
			{
				.cullMode = PonyEngine::RenderDevice::CullMode::None
			},
			.blend = PonyEngine::RenderDevice::BlendParams
			{
				.blendGroup = PonyEngine::RenderDevice::BlendGroupParams
				{
					.renderTargetBlend = std::span<const PonyEngine::RenderDevice::RenderTargetBlendParams>(&opaqueBlendParams, 1uz),
				}
			},
			.depthStencil = PonyEngine::RenderDevice::DepthStencilParams
			{
				.depth = std::nullopt,
				.stencil = std::nullopt
			},
			.attachmentParams = PonyEngine::RenderDevice::AttachmentParams
			{
				.renderTargetFormats = std::span<const PonyEngine::RenderDevice::RenderTargetAttachmentFormat>(&outputTextureFormat, 1uz)
			}
		});

		graphicsCommandList->Close();
		computeCommandList->Close();
		copyCommandList->Close();
	}

	void GameService::End()
	{
		const auto graphicsFenceValueSync = PonyEngine::RenderDevice::FenceValue{.fence = graphicsFence.get(), .value = ++graphicsFenceValue};
		renderDevice->Execute(std::span<const PonyEngine::RenderDevice::IGraphicsCommandList* const>(), PonyEngine::RenderDevice::QueueSync
		{
			.after = std::span<const PonyEngine::RenderDevice::FenceValue>(&graphicsFenceValueSync, 1uz)
		});
		const auto computeFenceValueSync = PonyEngine::RenderDevice::FenceValue{.fence = computeFence.get(), .value = ++computeFenceValue};
		renderDevice->Execute(std::span<const PonyEngine::RenderDevice::IComputeCommandList* const>(), PonyEngine::RenderDevice::QueueSync
		{
			.after = std::span<const PonyEngine::RenderDevice::FenceValue>(&computeFenceValueSync, 1uz)
		});
		const auto copyFenceValueSync = PonyEngine::RenderDevice::FenceValue{.fence = copyFence.get(), .value = ++copyFenceValue};
		renderDevice->Execute(std::span<const PonyEngine::RenderDevice::ICopyCommandList* const>(), PonyEngine::RenderDevice::QueueSync
		{
			.after = std::span<const PonyEngine::RenderDevice::FenceValue>(&copyFenceValueSync, 1uz)
		});
		const auto waitedFences = std::array<PonyEngine::RenderDevice::FenceValue, 3>{graphicsFenceValueSync, computeFenceValueSync, copyFenceValueSync };
		waiter->Wait(waitedFences, std::chrono::seconds(10));
	}

	void GameService::AddTickableServices(PonyEngine::Application::ITickableServiceAdder& adder)
	{
		adder.Add(*this, 0);
	}

	void GameService::Tick()
	{
		const auto waitSync = PonyEngine::RenderDevice::FenceValue{.fence = graphicsFence.get(), .value = graphicsFenceValue};
		waiter->Wait(std::span(&waitSync, 1uz), std::chrono::seconds(3));

		const std::uint8_t currentBackBufferIndex = renderDevice->CurrentSwapChainBufferIndex();
		graphicsCommandList->Reset();
		graphicsCommandList->BindContainers(srvContainer.get(), nullptr);
		graphicsCommandList->SetRasterRegion(PonyEngine::RenderDevice::RasterRegion
		{
			.viewport = PonyEngine::Math::CornerRect<float>(static_cast<PonyEngine::Math::Vector2<float>>(resolution)),
			.scissor = PonyEngine::Math::CornerRect<std::uint32_t>(resolution)
		});

		const auto renderTextureBarriers = std::array<PonyEngine::RenderDevice::TextureBarrier, 2>
		{
			PonyEngine::RenderDevice::TextureBarrier
			{
				.texture = targetTexture.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::None,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::RenderTarget,
				.beforeAccesses = std::nullopt,
				.afterAccesses = PonyEngine::RenderDevice::ResourceAccess::RenderTarget,
				.beforeLayout = PonyEngine::RenderDevice::ResourceLayout::RenderTarget,
				.afterLayout = PonyEngine::RenderDevice::ResourceLayout::RenderTarget
			},
			PonyEngine::RenderDevice::TextureBarrier
			{
				.texture = depthTexture.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::None,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::DepthStencil,
				.beforeAccesses = std::nullopt,
				.afterAccesses = PonyEngine::RenderDevice::ResourceAccess::DepthStencilWrite,
				.beforeLayout = PonyEngine::RenderDevice::ResourceLayout::DepthStencilWrite,
				.afterLayout = PonyEngine::RenderDevice::ResourceLayout::DepthStencilWrite
			},
		};
		graphicsCommandList->Barrier(renderTextureBarriers);
		graphicsCommandList->ClearRTV(*rtvContainer, 0u, PonyEngine::Math::ColorRGBA<float>::Black());
		graphicsCommandList->ClearDSV(*dsvContainer, depthContainerIndex, 1.f, 0u);
		const auto renderTargetBinding = PonyEngine::RenderDevice::RenderTargetBinding{.container = rtvContainer.get(), .index = renderTargetContainerIndex};
		const auto depthTargetBinding = PonyEngine::RenderDevice::DepthStencilBinding{.container = dsvContainer.get(), .index = depthContainerIndex};
		graphicsCommandList->BindTargets(std::span(&renderTargetBinding, 1uz), &depthTargetBinding);
		graphicsCommandList->BindPipelineState(*boxPipelineState);
		//graphicsCommandList->DispatchGraphics(2u);
		const auto resolveBarriers = std::array<PonyEngine::RenderDevice::TextureBarrier, 3>
		{
			PonyEngine::RenderDevice::TextureBarrier
			{
				.texture = targetTexture.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::RenderTarget,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::Resolve,
				.beforeAccesses = PonyEngine::RenderDevice::ResourceAccess::RenderTarget,
				.afterAccesses = PonyEngine::RenderDevice::ResourceAccess::ResolveSource,
				.beforeLayout = PonyEngine::RenderDevice::ResourceLayout::RenderTarget,
				.afterLayout = PonyEngine::RenderDevice::ResourceLayout::ResolveSource
			},
			PonyEngine::RenderDevice::TextureBarrier
			{
				.texture = depthTexture.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::DepthStencil,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::None,
				.beforeAccesses = PonyEngine::RenderDevice::ResourceAccess::DepthStencilWrite,
				.afterAccesses = std::nullopt,
				.beforeLayout = PonyEngine::RenderDevice::ResourceLayout::DepthStencilWrite,
				.afterLayout = PonyEngine::RenderDevice::ResourceLayout::DepthStencilWrite
			},
			PonyEngine::RenderDevice::TextureBarrier
			{
				.texture = resolvedTexture.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::None,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::Resolve,
				.beforeAccesses = std::nullopt,
				.afterAccesses = PonyEngine::RenderDevice::ResourceAccess::ResolveDestination,
				.beforeLayout = PonyEngine::RenderDevice::ResourceLayout::ShaderResource,
				.afterLayout = PonyEngine::RenderDevice::ResourceLayout::ResolveDestination
			}
		};
		graphicsCommandList->Barrier(resolveBarriers);
		graphicsCommandList->Resolve(*targetTexture, *resolvedTexture);
		const auto outputBarriers = std::array<PonyEngine::RenderDevice::TextureBarrier, 3>
		{
			PonyEngine::RenderDevice::TextureBarrier
			{
				.texture = targetTexture.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::Resolve,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::None,
				.beforeAccesses = PonyEngine::RenderDevice::ResourceAccess::ResolveSource,
				.afterAccesses = std::nullopt,
				.beforeLayout = PonyEngine::RenderDevice::ResourceLayout::ResolveSource,
				.afterLayout = PonyEngine::RenderDevice::ResourceLayout::RenderTarget
			},
			PonyEngine::RenderDevice::TextureBarrier
			{
				.texture = resolvedTexture.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::Resolve,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::PixelShading,
				.beforeAccesses = PonyEngine::RenderDevice::ResourceAccess::ResolveDestination,
				.afterAccesses = PonyEngine::RenderDevice::ResourceAccess::ShaderResource,
				.beforeLayout = PonyEngine::RenderDevice::ResourceLayout::ResolveDestination,
				.afterLayout = PonyEngine::RenderDevice::ResourceLayout::ShaderResource
			},
			PonyEngine::RenderDevice::TextureBarrier
			{
				.texture = renderDevice->SwapChainBuffer(currentBackBufferIndex).get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::None,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::RenderTarget,
				.beforeAccesses = std::nullopt,
				.afterAccesses = PonyEngine::RenderDevice::ResourceAccess::RenderTarget,
				.beforeLayout = PonyEngine::RenderDevice::ResourceLayout::Present,
				.afterLayout = PonyEngine::RenderDevice::ResourceLayout::RenderTarget
			}
		};
		graphicsCommandList->Barrier(outputBarriers);
		const auto outputTargetBinding = PonyEngine::RenderDevice::RenderTargetBinding{.container = rtvContainer.get(), .index = backBufferContainerOffset + renderDevice->CurrentSwapChainBufferIndex()};
		graphicsCommandList->BindTargets(std::span(&outputTargetBinding, 1uz), nullptr);
		graphicsCommandList->BindPipelineState(*outputPipelineState);
		graphicsCommandList->BindGraphics(PonyEngine::RenderDevice::ShaderDataBinding{.layoutSetIndex = 0u, .containerIndex = resolvedTextureContainerIndex});
		graphicsCommandList->DispatchGraphics(1u);
		const auto finishBarriers = std::array<PonyEngine::RenderDevice::TextureBarrier, 2>
		{
			PonyEngine::RenderDevice::TextureBarrier
			{
				.texture = resolvedTexture.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::PixelShading,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::None,
				.beforeAccesses = PonyEngine::RenderDevice::ResourceAccess::ShaderResource,
				.afterAccesses = std::nullopt,
				.beforeLayout = PonyEngine::RenderDevice::ResourceLayout::ShaderResource,
				.afterLayout = PonyEngine::RenderDevice::ResourceLayout::ShaderResource
			},
			PonyEngine::RenderDevice::TextureBarrier
			{
				.texture = renderDevice->SwapChainBuffer(currentBackBufferIndex).get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::RenderTarget,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::None,
				.beforeAccesses = PonyEngine::RenderDevice::ResourceAccess::RenderTarget,
				.afterAccesses = std::nullopt,
				.beforeLayout = PonyEngine::RenderDevice::ResourceLayout::RenderTarget,
				.afterLayout = PonyEngine::RenderDevice::ResourceLayout::Present
			}
		};
		graphicsCommandList->Barrier(finishBarriers);

		graphicsCommandList->Close();

		const auto finishSync = PonyEngine::RenderDevice::FenceValue{.fence = graphicsFence.get(), .value = ++graphicsFenceValue};
		const PonyEngine::RenderDevice::IGraphicsCommandList* const commandList = graphicsCommandList.get();
		renderDevice->Execute(std::span(&commandList, 1uz), PonyEngine::RenderDevice::QueueSync{.after = std::span(&finishSync, 1uz)});

		renderDevice->PresentNextSwapChainBuffer();
	}

	std::vector<std::byte> GameService::LoadShader(const std::filesystem::path& path)
	{
		auto file = std::ifstream(application->RootDirectory() / path, std::ios::binary | std::ios::ate);
		if (!file) [[unlikely]]
		{
			throw std::runtime_error("Failed to open file");
		}

		const auto size = file.tellg();
		file.seekg(0);

		auto data = std::vector<std::byte>(static_cast<size_t>(size));
		file.read(reinterpret_cast<char*>(data.data()), size);

		return data;
	}
}
