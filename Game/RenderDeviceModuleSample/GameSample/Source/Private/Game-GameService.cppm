export module Game:GameService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Math;
import PonyEngine.RawInput;
import PonyEngine.RenderDevice;
import PonyEngine.Shader;
import PonyEngine.Surface;
import PonyEngine.Time;

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

		class GpuTransform final
		{
		public:
			[[nodiscard("Pure constructor")]]
			GpuTransform() noexcept;
			[[nodiscard("Pure constructor")]]
			explicit GpuTransform(const PonyEngine::Math::Matrix4x4<float>& mvp) noexcept;
			[[nodiscard("Pure constructor")]]
			GpuTransform(const GpuTransform& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			GpuTransform(GpuTransform&& other) noexcept = default;

			~GpuTransform() noexcept = default;

			[[nodiscard("Pure function")]]
			const PonyEngine::Math::Matrix4x4<float>& MVP() const noexcept;

			GpuTransform& operator =(const GpuTransform& other) noexcept = default;
			GpuTransform& operator =(GpuTransform&& other) noexcept = default;

		private:
			PonyEngine::Math::Matrix4x4<float> mvp;
			float determinant;
		};

		struct Material final
		{
			PonyEngine::Math::ColorRGBA<float> color;
		};

		PonyEngine::Application::IApplicationContext* application;
		PonyEngine::RenderDevice::IRenderDeviceService* renderDevice;
		PonyEngine::RawInput::IRawInputService* rawInput;
		PonyEngine::Time::ITimeService* time;

		PonyEngine::RawInput::AxisId aAxis;
		PonyEngine::RawInput::AxisId dAxis;
		PonyEngine::RawInput::AxisId sAxis;
		PonyEngine::RawInput::AxisId wAxis;
		PonyEngine::RawInput::AxisId ctrlAxis;
		PonyEngine::RawInput::AxisId spaceAxis;
		PonyEngine::RawInput::AxisId xAxis;
		PonyEngine::RawInput::AxisId yAxis;
		PonyEngine::RawInput::AxisId qAxis;
		PonyEngine::RawInput::AxisId eAxis;
		PonyEngine::RawInput::AxisId enterAxis;
		PonyEngine::RawInput::AxisId escapeAxis;

		std::shared_ptr<PonyEngine::RenderDevice::IGraphicsCommandList> graphicsCommandList;
		std::shared_ptr<PonyEngine::RenderDevice::ICopyCommandList> copyCommandList;

		std::shared_ptr<PonyEngine::RenderDevice::IFence> graphicsFence;
		std::shared_ptr<PonyEngine::RenderDevice::IFence> copyFence;
		std::uint64_t graphicsFenceValue = 0ull;
		std::uint64_t copyFenceValue = 0ull;
		std::shared_ptr<PonyEngine::RenderDevice::IWaiter> waiter;

		std::shared_ptr<PonyEngine::RenderDevice::ITexture> targetTexture;
		std::shared_ptr<PonyEngine::RenderDevice::ITexture> resolvedTexture;
		std::shared_ptr<PonyEngine::RenderDevice::ITexture> depthTexture;

		std::shared_ptr<PonyEngine::RenderDevice::IBuffer> stagingTransforms;
		std::shared_ptr<PonyEngine::RenderDevice::IBuffer> gpuTransforms;
		std::uint64_t boxTransformOffset = 0ull;

		std::shared_ptr<PonyEngine::RenderDevice::IBuffer> staticGpuDataBuffer;

		std::shared_ptr<PonyEngine::RenderDevice::IShaderDataContainer> stagingSrvContainer;
		std::shared_ptr<PonyEngine::RenderDevice::IShaderDataContainer> srvContainer;
		std::shared_ptr<PonyEngine::RenderDevice::IRenderTargetContainer> rtvContainer;
		std::shared_ptr<PonyEngine::RenderDevice::IDepthStencilContainer> dsvContainer;
		std::uint32_t resolvedTextureContainerIndex = 0;
		std::uint32_t boxTransformContainerIndex = 0;
		std::uint32_t boxMeshletContainerIndex = 0;
		std::uint32_t boxVertexIndexContainerIndex = 0;
		std::uint32_t boxPrimitiveContainerIndex = 0;
		std::uint32_t boxPositionContainerIndex = 0;
		std::uint32_t greenBoxMaterialContainerIndex = 0;
		std::uint32_t renderTargetContainerIndex = 0;
		std::uint32_t backBufferContainerOffset = 0;
		std::uint32_t depthContainerIndex = 0;

		std::shared_ptr<PonyEngine::RenderDevice::IGraphicsPipelineState> boxPipelineState;
		std::shared_ptr<PonyEngine::RenderDevice::IGraphicsPipelineState> outputPipelineState;

		PonyEngine::Math::Vector2<std::uint32_t> resolution;

		PonyEngine::Math::Transform3D<float> boxTransform;
		PonyEngine::Math::Transform3D<float> cameraTransform;
	};
}

namespace Game
{
	GameService::GameService(PonyEngine::Application::IApplicationContext& application) :
		application{&application},
		renderDevice{&this->application->GetService<PonyEngine::RenderDevice::IRenderDeviceService>()},
		rawInput{&this->application->GetService<PonyEngine::RawInput::IRawInputService>()},
		time{&this->application->GetService<PonyEngine::Time::ITimeService>()},
		aAxis(rawInput->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainAPath))),
		dAxis(rawInput->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainDPath))),
		sAxis(rawInput->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainSPath))),
		wAxis(rawInput->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainWPath))),
		ctrlAxis(rawInput->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainLeftCtrlPath))),
		spaceAxis(rawInput->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainSpacePath))),
		xAxis(rawInput->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::MouseLayout::AxisXPath))),
		yAxis(rawInput->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::MouseLayout::AxisYPath))),
		qAxis(rawInput->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainQPath))),
		eAxis(rawInput->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainEPath))),
		enterAxis(rawInput->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainEnterPath))),
		escapeAxis(rawInput->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainEscapePath))),
		boxTransform(PonyEngine::Math::Vector3<float>::Zero(), PonyEngine::Math::Quaternion<float>::Identity(), PonyEngine::Math::Vector3<float>::One()),
		cameraTransform(PonyEngine::Math::Vector3<float>(0.f, 0.f, -10.f), PonyEngine::Math::Quaternion<float>::Identity(), PonyEngine::Math::Vector3<float>::One())
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
		auto& surface = application->GetService<PonyEngine::Surface::ISurfaceService>();
		surface.CursorVisibility(false);
		surface.CursorClippingRect(PonyEngine::Math::CornerRect<float>(PonyEngine::Math::Vector2<float>(0.5f, 0.5f), PonyEngine::Math::Vector2<float>::Zero()));

		graphicsCommandList = renderDevice->CreateGraphicsCommandList();
		graphicsCommandList->Name("MainGraphics");
		copyCommandList = renderDevice->CreateCopyCommandList();
		copyCommandList->Name("MainCopy");
		graphicsFence = renderDevice->CreateFence();
		graphicsFence->Name("GraphicsFence");
		copyFence = renderDevice->CreateFence();
		copyFence->Name("CopyFence");
		graphicsFenceValue = graphicsFence->CompletedValue();
		copyFenceValue = copyFence->CompletedValue();
		waiter = renderDevice->CreateWaiter();
		waiter->Name("MainWaiter");

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
		for (std::uint8_t i = 0; i < renderDevice->SwapChainBufferCount(); ++i)
		{
			renderDevice->SwapChainBuffer(i)->Name(std::format("BackBuffer_{}", i));
		}
		const auto renderTargetTextureFormat = PonyEngine::RenderDevice::RenderTargetAttachmentFormat
		{
			.format = renderDevice->TextureFormatId(PonyEngine::RenderDevice::TextureFormat::R8G8B8A8_Unorm),
			.srgb = false
		};
		const PonyEngine::Math::Vector3<std::uint32_t> res = renderDevice->SwapChainBuffer(0u)->Size();
		resolution = PonyEngine::Math::Vector2<std::uint32_t>(res.X(), res.Y());
		const PonyEngine::RenderDevice::TextureFormatId depthStencilTextureFormat = renderDevice->TextureFormatId(PonyEngine::RenderDevice::TextureFormat::D32_Float_S8X24_Uint);
		constexpr auto sampleCount = PonyEngine::RenderDevice::SampleCount::X4;
		targetTexture = renderDevice->CreateTexture(
		PonyEngine::RenderDevice::CommittedResourceHeapParams
		{
			.heapType = PonyEngine::RenderDevice::HeapType::Default,
			.notZeroed = false
		},
		PonyEngine::RenderDevice::TextureParams
		{
			.format = renderTargetTextureFormat.format,
			.size = res,
			.clearValue = PonyEngine::Math::ColorRGBA<float>::Black(),
			.sampleCount = sampleCount,
			.usage = PonyEngine::RenderDevice::TextureUsage::RenderTarget,
			.initialLayout = PonyEngine::RenderDevice::ResourceLayout::RenderTarget
		});
		targetTexture->Name("MainTarget");
		resolvedTexture = renderDevice->CreateTexture(PonyEngine::RenderDevice::CommittedResourceHeapParams
		{
			.heapType = PonyEngine::RenderDevice::HeapType::Default,
			.notZeroed = true
		}, 
		PonyEngine::RenderDevice::TextureParams
		{
			.format = renderTargetTextureFormat.format,
			.size = targetTexture->Size(),
			.clearValue = PonyEngine::RenderDevice::NoClear{},
			.sampleCount = PonyEngine::RenderDevice::SampleCount::X1,
			.usage = PonyEngine::RenderDevice::TextureUsage::ShaderResource,
			.initialLayout = PonyEngine::RenderDevice::ResourceLayout::ShaderResource
		});
		resolvedTexture->Name("MainResolved");
		depthTexture = renderDevice->CreateTexture(PonyEngine::RenderDevice::CommittedResourceHeapParams
		{
			.heapType = PonyEngine::RenderDevice::HeapType::Default,
			.notZeroed = false
		}, 
		PonyEngine::RenderDevice::TextureParams
		{
			.format = depthStencilTextureFormat,
			.size = targetTexture->Size(),
			.clearValue = PonyEngine::RenderDevice::DepthStencil{},
			.sampleCount = sampleCount,
			.usage = PonyEngine::RenderDevice::TextureUsage::DepthStencil,
			.initialLayout = PonyEngine::RenderDevice::ResourceLayout::DepthStencilWrite
		});
		depthTexture->Name("MainDepth");

		const PonyEngine::RenderDevice::CBVRequirement cbvRequirement = renderDevice->DeviceSupport().viewSupport.cbvRequirement;

		const std::uint32_t transformSize = PonyEngine::Math::Align(static_cast<std::uint32_t>(sizeof(GpuTransform)), cbvRequirement.sizeAlignment);
		const std::uint64_t transformBufferSize = cbvRequirement.offsetAlignment * 0ull + transformSize;
		stagingTransforms = renderDevice->CreateBuffer(PonyEngine::RenderDevice::CommittedResourceHeapParams
		{
			.heapType = PonyEngine::RenderDevice::HeapType::Upload,
			.notZeroed = true
		},
		PonyEngine::RenderDevice::BufferParams
		{
			.size = transformBufferSize,
			.usage = PonyEngine::RenderDevice::BufferUsage::None
		});
		stagingTransforms->Name("StagingTransforms");
		gpuTransforms = renderDevice->CreateBuffer(PonyEngine::RenderDevice::CommittedResourceHeapParams
		{
			.heapType = PonyEngine::RenderDevice::HeapType::Default,
			.notZeroed = true
		},
		PonyEngine::RenderDevice::BufferParams
		{
			.size = transformBufferSize,
			.usage = PonyEngine::RenderDevice::BufferUsage::ShaderResource
		});
		gpuTransforms->Name("Transforms");
		
		constexpr auto boxMeshlets = std::array<PonyEngine::Shader::Meshlet, 2u>
		{
			PonyEngine::Shader::Meshlet(0u, 0u, 7u, 6u),
			PonyEngine::Shader::Meshlet(7u, 0u, 7u, 6u)
		};
		constexpr auto boxVertexIndices = std::array<std::uint32_t, 14>
		{
			0u, 1u, 2u, 3u, 4u, 5u, 7u, 6u, 5u, 4u, 7u, 2u, 1u, 3u
		};
		constexpr auto boxPrimitiveIndices = std::array<std::uint8_t, 18>
		{
			0u, 1u, 2u, 0u, 2u, 3u, 0u, 4u, 5u, 0u, 5u, 1u, 0u, 6u, 4u, 0u, 3u, 6u
		};
		constexpr auto boxPositions = std::array
		{
			PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f),
			PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f),
			PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f),
			PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f),
			PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f),
			PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f),
			PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f),
			PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f)
		};
		constexpr auto greenBoxMaterial = Material{.color = PonyEngine::Math::ColorRGBA<float>::Green()};
		constexpr std::uint64_t boxMeshletOffset = 0ull;
		constexpr std::uint32_t boxMeshletSize = sizeof(boxMeshlets);
		constexpr std::uint64_t boxPositionOffset = boxMeshletOffset + boxMeshletSize;
		constexpr std::uint32_t boxPositionSize = sizeof(boxPositions);
		constexpr std::uint64_t boxVertexIndexOffset = boxPositionOffset + boxPositionSize;
		constexpr std::uint32_t boxVertexIndexSize = sizeof(boxVertexIndices);
		constexpr std::uint64_t boxPrimitiveOffset = boxVertexIndexOffset + boxVertexIndexSize;
		constexpr std::uint32_t boxPrimitiveSize = PonyEngine::Math::Align(std::uint32_t{sizeof(boxPrimitiveIndices)}, 4u);
		const std::uint64_t greenBoxMaterialOffset = PonyEngine::Math::Align(boxPrimitiveOffset + boxPrimitiveSize, static_cast<std::uint64_t>(cbvRequirement.offsetAlignment));
		const std::uint32_t greenBoxMaterialSize = PonyEngine::Math::Align(std::uint32_t{sizeof(greenBoxMaterial)}, cbvRequirement.sizeAlignment);
		const std::uint64_t dataBufferSize = greenBoxMaterialOffset + greenBoxMaterialSize;

		const std::shared_ptr<PonyEngine::RenderDevice::IBuffer> stagingStaticDataBuffer = renderDevice->CreateBuffer(PonyEngine::RenderDevice::CommittedResourceHeapParams
		{
			.heapType = PonyEngine::RenderDevice::HeapType::Upload,
			.notZeroed = true
		},
		PonyEngine::RenderDevice::BufferParams
		{
			.size = dataBufferSize,
			.usage = PonyEngine::RenderDevice::BufferUsage::None
		});
		stagingStaticDataBuffer->Name("StagingStaticData");
		staticGpuDataBuffer = renderDevice->CreateBuffer(PonyEngine::RenderDevice::CommittedResourceHeapParams
		{
			.heapType = PonyEngine::RenderDevice::HeapType::Default,
			.notZeroed = true
		},
		PonyEngine::RenderDevice::BufferParams
		{
			.size = dataBufferSize,
			.usage = PonyEngine::RenderDevice::BufferUsage::ShaderResource
		});
		staticGpuDataBuffer->Name("StaticData");

		constexpr std::uint32_t srvCount = 8u;
		std::uint32_t srvIndex = 0u;
		stagingSrvContainer = renderDevice->CreateShaderDataContainer(PonyEngine::RenderDevice::ShaderDataContainerParams
		{
			.size = srvCount,
			.shaderVisible = false
		});
		stagingSrvContainer->Name("StagingSRVContainer");
		resolvedTextureContainerIndex = srvIndex++;
		renderDevice->CreateView(resolvedTexture.get(), *stagingSrvContainer, resolvedTextureContainerIndex, PonyEngine::RenderDevice::TextureSRVParams
		{
			.format = renderTargetTextureFormat.format,
			.srgb = false,
			.layout = PonyEngine::RenderDevice::TextureSingleSRVLayout{}
		});
		boxTransformOffset = 0ull;
		boxTransformContainerIndex = srvIndex++;
		renderDevice->CreateView(gpuTransforms.get(), *stagingSrvContainer, boxTransformContainerIndex, PonyEngine::RenderDevice::CBVParams
		{
			.offset = boxTransformOffset,
			.size = transformSize
		});
		boxMeshletContainerIndex = srvIndex++;
		renderDevice->CreateView(staticGpuDataBuffer.get(), *stagingSrvContainer, boxMeshletContainerIndex, PonyEngine::RenderDevice::BufferSRVParams
		{
			.firstElementIndex = boxMeshletOffset / sizeof(PonyEngine::Shader::Meshlet),
			.elementCount = std::size(boxMeshlets),
			.stride = sizeof(PonyEngine::Shader::Meshlet)
		});
		boxVertexIndexContainerIndex = srvIndex++;
		renderDevice->CreateView(staticGpuDataBuffer.get(), *stagingSrvContainer, boxVertexIndexContainerIndex, PonyEngine::RenderDevice::BufferSRVParams
		{
			.firstElementIndex = boxVertexIndexOffset / sizeof(std::uint32_t),
			.elementCount = std::size(boxVertexIndices),
			.stride = sizeof(std::uint32_t)
		});
		boxPrimitiveContainerIndex = srvIndex++;
		renderDevice->CreateView(staticGpuDataBuffer.get(), *stagingSrvContainer, boxPrimitiveContainerIndex, PonyEngine::RenderDevice::BufferSRVParams
		{
			.firstElementIndex = boxPrimitiveOffset / sizeof(std::uint32_t),
			.elementCount = PonyEngine::Math::Align(static_cast<std::uint32_t>(std::size(boxPrimitiveIndices)), std::uint32_t{alignof(std::uint32_t)}) / sizeof(std::uint32_t),
			.stride = sizeof(std::uint32_t)
		});
		boxPositionContainerIndex = srvIndex++;
		renderDevice->CreateView(staticGpuDataBuffer.get(), *stagingSrvContainer, boxPositionContainerIndex, PonyEngine::RenderDevice::BufferSRVParams
		{
			.firstElementIndex = boxPositionOffset / sizeof(PonyEngine::Math::Vector3<float>),
			.elementCount = std::size(boxPositions),
			.stride = sizeof(PonyEngine::Math::Vector3<float>)
		});
		greenBoxMaterialContainerIndex = srvIndex++;
		renderDevice->CreateView(staticGpuDataBuffer.get(), *stagingSrvContainer, greenBoxMaterialContainerIndex, PonyEngine::RenderDevice::CBVParams
		{
			.offset = greenBoxMaterialOffset,
			.size = greenBoxMaterialSize
		});

		srvContainer = renderDevice->CreateShaderDataContainer(PonyEngine::RenderDevice::ShaderDataContainerParams
		{
			.size = srvCount,
			.shaderVisible = true
		});
		srvContainer->Name("SRVContainer");
		const auto srvRange = PonyEngine::RenderDevice::ShaderDataCopyRange
		{
			.source = stagingSrvContainer.get(),
			.destination = srvContainer.get(),
			.count = srvCount
		};
		renderDevice->CopyViews(std::span(&srvRange, 1uz));
		std::uint32_t rtvIndex = 0u;
		rtvContainer = renderDevice->CreateRenderTargetContainer(PonyEngine::RenderDevice::RenderTargetContainerParams
		{
			.size = renderDevice->SwapChainBufferCount() + 1u
		});
		rtvContainer->Name("RTVContainer");
		renderTargetContainerIndex = rtvIndex++;
		renderDevice->CreateView(targetTexture.get(), *rtvContainer, renderTargetContainerIndex, PonyEngine::RenderDevice::RTVParams
		{
			.format = renderTargetTextureFormat.format,
			.srgb = renderTargetTextureFormat.srgb,
			.dimension = PonyEngine::RenderDevice::TextureDimension::Texture2D,
			.layout = PonyEngine::RenderDevice::MSRTVLayout{}
		});
		backBufferContainerOffset = rtvIndex++;
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
		dsvContainer->Name("DSVContainer");
		depthContainerIndex = 0u;
		renderDevice->CreateView(depthTexture.get(), *dsvContainer, depthContainerIndex, PonyEngine::RenderDevice::DSVParams
		{
			.format = depthStencilTextureFormat,
			.dimension = PonyEngine::RenderDevice::TextureDimension::Texture2D,
			.flags = PonyEngine::RenderDevice::DSVFlag::None,
			.layout = PonyEngine::RenderDevice::MultiSampleDSVLayout{}
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
		layout->Name("BoxLayout");

		const std::vector<std::byte> triangleShader = LoadShader(TRIANGLE_SHADER);
		const std::vector<std::byte> pixelShader = LoadShader(PIXEL_SHADER);
		constexpr auto opaqueBlendParams = PonyEngine::RenderDevice::RenderTargetBlendParams{};
		boxPipelineState = renderDevice->CreateGraphicsPipelineState(layout, PonyEngine::RenderDevice::GraphicsPipelineStateParams
		{
			.meshShader = triangleShader,
			.pixelShader = pixelShader,
			.attachment = PonyEngine::RenderDevice::AttachmentParams
			{
				.renderTargetFormats = std::span<const PonyEngine::RenderDevice::RenderTargetAttachmentFormat>(&renderTargetTextureFormat, 1uz),
				.depthStencilFormat = depthStencilTextureFormat
			},
			.rasterizer = PonyEngine::RenderDevice::RasterizerParams{},
			.depthStencil = PonyEngine::RenderDevice::DepthStencilParams
			{
				.depth = PonyEngine::RenderDevice::DepthParams{},
				.stencil = PonyEngine::RenderDevice::StencilParams{}
			},
			.sample = PonyEngine::RenderDevice::SampleParams
			{
				.sampleCount = sampleCount
			},
			.blend = PonyEngine::RenderDevice::BlendParams
			{
				.blendGroup = PonyEngine::RenderDevice::BlendGroupParams
				{
					.renderTargetBlend = std::span<const PonyEngine::RenderDevice::RenderTargetBlendParams>(&opaqueBlendParams, 1uz),
				}
			}
		});
		boxPipelineState->Name("BoxPipelineState");

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
		outputLayout->Name("OutputLayout");

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
			.attachment = PonyEngine::RenderDevice::AttachmentParams
			{
				.renderTargetFormats = std::span<const PonyEngine::RenderDevice::RenderTargetAttachmentFormat>(&outputTextureFormat, 1uz)
			},
			.rasterizer = PonyEngine::RenderDevice::RasterizerParams
			{
				.cullMode = PonyEngine::RenderDevice::CullMode::NoCulling
			},
			.depthStencil = PonyEngine::RenderDevice::DepthStencilParams
			{
				.depth = std::nullopt,
				.stencil = std::nullopt
			},
			.blend = PonyEngine::RenderDevice::BlendParams
			{
				.blendGroup = PonyEngine::RenderDevice::BlendGroupParams
				{
					.renderTargetBlend = std::span<const PonyEngine::RenderDevice::RenderTargetBlendParams>(&opaqueBlendParams, 1uz),
				}
			}
		});
		outputPipelineState->Name("OutputPipelineState");

		void* const data = stagingStaticDataBuffer->Map();
		PonyEngine::RenderDevice::Copy(&boxMeshlets, 0ull, data, boxMeshletOffset, sizeof(boxMeshlets));
		PonyEngine::RenderDevice::Copy(&boxVertexIndices, 0ull, data, boxVertexIndexOffset, sizeof(boxVertexIndices));
		PonyEngine::RenderDevice::Copy(&boxPrimitiveIndices, 0ull, data, boxPrimitiveOffset, sizeof(boxPrimitiveIndices));
		PonyEngine::RenderDevice::Copy(&boxPositions, 0ull, data, boxPositionOffset, sizeof(boxPositions));
		PonyEngine::RenderDevice::Copy(&greenBoxMaterial, 0ull, data, greenBoxMaterialOffset, sizeof(greenBoxMaterial));
		stagingStaticDataBuffer->Unmap();

		const auto preCopyBarriers = std::array<PonyEngine::RenderDevice::BufferBarrier, 2>
		{
			PonyEngine::RenderDevice::BufferBarrier
			{
				.buffer = stagingStaticDataBuffer.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::None,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::Copy,
				.beforeAccesses = std::nullopt,
				.afterAccesses = PonyEngine::RenderDevice::ResourceAccess::CopySource
			},
			PonyEngine::RenderDevice::BufferBarrier
			{
				.buffer = staticGpuDataBuffer.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::None,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::Copy,
				.beforeAccesses = std::nullopt,
				.afterAccesses = PonyEngine::RenderDevice::ResourceAccess::CopyDestination
			}
		};
		copyCommandList->Barrier(preCopyBarriers);
		copyCommandList->Copy(*stagingStaticDataBuffer, *staticGpuDataBuffer);
		const auto postCopyBarriers = std::array<PonyEngine::RenderDevice::BufferBarrier, 2>
		{
			PonyEngine::RenderDevice::BufferBarrier
			{
				.buffer = stagingStaticDataBuffer.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::Copy,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::None,
				.beforeAccesses = PonyEngine::RenderDevice::ResourceAccess::CopySource,
				.afterAccesses = std::nullopt
			},
			PonyEngine::RenderDevice::BufferBarrier
			{
				.buffer = staticGpuDataBuffer.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::Copy,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::None,
				.beforeAccesses = PonyEngine::RenderDevice::ResourceAccess::CopyDestination,
				.afterAccesses = std::nullopt
			}
		};
		copyCommandList->Barrier(postCopyBarriers);

		graphicsCommandList->Close();
		copyCommandList->Close();

		const PonyEngine::RenderDevice::ICopyCommandList* const copyCommand = copyCommandList.get();
		const auto copyFenceValueSync = std::pair(copyFence.get(), ++copyFenceValue);
		renderDevice->Execute(std::span<const PonyEngine::RenderDevice::ICopyCommandList* const>(&copyCommand, 1uz), PonyEngine::RenderDevice::QueueSync
		{
			.after = std::span(&copyFenceValueSync, 1uz)
		});
		const auto copyFenceValueWait = std::pair<const PonyEngine::RenderDevice::IFence*, std::uint64_t>(copyFence.get(), copyFenceValue);
		waiter->Wait(std::span(&copyFenceValueWait, 1uz), std::chrono::seconds(10));
	}

	void GameService::End()
	{
		const auto graphicsFenceValueSync = std::pair(graphicsFence.get(), ++graphicsFenceValue);
		renderDevice->Execute(std::span<const PonyEngine::RenderDevice::IGraphicsCommandList* const>(), PonyEngine::RenderDevice::QueueSync
		{
			.after = std::span(&graphicsFenceValueSync, 1uz)
		});
		const auto copyFenceValueSync = std::pair(copyFence.get(), ++copyFenceValue);
		renderDevice->Execute(std::span<const PonyEngine::RenderDevice::ICopyCommandList* const>(), PonyEngine::RenderDevice::QueueSync
		{
			.after = std::span(&copyFenceValueSync, 1uz)
		});
		const auto waitedFences = std::array<const std::pair<const PonyEngine::RenderDevice::IFence*, std::uint64_t>, 2>
		{
			graphicsFenceValueSync,
			copyFenceValueSync
		};
		waiter->Wait(waitedFences, std::chrono::seconds(10));
	}

	void GameService::AddTickableServices(PonyEngine::Application::ITickableServiceAdder& adder)
	{
		adder.Add(*this, 0);
	}

	void GameService::Tick()
	{
		const float aValue = rawInput->Value(aAxis);
		const float dValue = rawInput->Value(dAxis);
		const float sValue = rawInput->Value(sAxis);
		const float wValue = rawInput->Value(wAxis);
		const float ctrlValue = rawInput->Value(ctrlAxis);
		const float spaceValue = rawInput->Value(spaceAxis);
		const float xValue = rawInput->Value(xAxis);
		const float yValue = rawInput->Value(yAxis);
		const float qValue = rawInput->Value(qAxis);
		const float eValue = rawInput->Value(eAxis);
		const float enterValue = rawInput->Value(enterAxis);
		const float escapeValue = rawInput->Value(escapeAxis);

		if (enterValue > 0.5f)
		{
			cameraTransform.Position(PonyEngine::Math::Vector3<float>(0.f, 0.f, -10.f));
			cameraTransform.Rotation(PonyEngine::Math::Quaternion<float>::Identity());
		}
		if (escapeValue > 0.5f)
		{
			application->Stop();
		}

		const float deltaTime = time->VirtualDeltaTimeSeconds<float>();
		const PonyEngine::Math::Vector3<float> translate = PonyEngine::Math::ClampMagnitude(PonyEngine::Math::Vector3<float>(dValue - aValue, spaceValue - ctrlValue, wValue - sValue), 1.f) * 10.f * deltaTime;
		const PonyEngine::Math::Quaternion<float> rotate = PonyEngine::Math::RotationQuaternion(cameraTransform.Up(), xValue * 0.001f) *
			PonyEngine::Math::RotationQuaternion(cameraTransform.Right(), yValue * 0.001f) * 
			PonyEngine::Math::RotationQuaternion(cameraTransform.Forward(), (qValue - eValue) * 1.f * deltaTime);
		cameraTransform.Rotate(rotate);
		cameraTransform.Translate(cameraTransform.Rotation() * translate);

		const PonyEngine::Math::Matrix4x4<float> view = cameraTransform.TRSMatrix().Inverse();
		const PonyEngine::Math::Matrix4x4<float> projection = PonyEngine::Math::PerspectiveMatrix(60.f * PonyEngine::Math::DegToRad<float>, static_cast<float>(resolution.X()) / resolution.Y(), 0.03f, 1000.f);
		const PonyEngine::Math::Matrix4x4<float> vp = projection * view;

		const PonyEngine::Math::Matrix4x4<float> boxModel = boxTransform.TRSMatrix();
		const auto boxTransform = GpuTransform(vp * boxModel);

		const auto waitSync = std::pair<const PonyEngine::RenderDevice::IFence*, std::uint64_t>(graphicsFence.get(), graphicsFenceValue);
		waiter->Wait(std::span(&waitSync, 1uz), std::chrono::seconds(3));

		void* const gpuData = stagingTransforms->Map();
		PonyEngine::RenderDevice::Copy(&boxTransform, 0ull, gpuData, 0ull, sizeof(GpuTransform));
		stagingTransforms->Unmap();

		copyCommandList->Reset();

		const auto beforeCopyBufferBarriers = std::array<PonyEngine::RenderDevice::BufferBarrier, 2>
		{
			PonyEngine::RenderDevice::BufferBarrier
			{
				.buffer = stagingTransforms.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::None,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::Copy,
				.beforeAccesses = std::nullopt,
				.afterAccesses = PonyEngine::RenderDevice::ResourceAccess::CopySource
			},
			PonyEngine::RenderDevice::BufferBarrier
			{
				.buffer = gpuTransforms.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::None,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::Copy,
				.beforeAccesses = std::nullopt,
				.afterAccesses = PonyEngine::RenderDevice::ResourceAccess::CopyDestination
			}
		};
		copyCommandList->Barrier(beforeCopyBufferBarriers);
		copyCommandList->Copy(*stagingTransforms, *gpuTransforms);
		const auto afterCopyBufferBarriers = std::array<PonyEngine::RenderDevice::BufferBarrier, 2>
		{
			PonyEngine::RenderDevice::BufferBarrier
			{
				.buffer = stagingTransforms.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::Copy,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::None,
				.beforeAccesses = PonyEngine::RenderDevice::ResourceAccess::CopySource,
				.afterAccesses = std::nullopt
			},
			PonyEngine::RenderDevice::BufferBarrier
			{
				.buffer = gpuTransforms.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::Copy,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::None,
				.beforeAccesses = PonyEngine::RenderDevice::ResourceAccess::CopyDestination,
				.afterAccesses = std::nullopt
			}
		};
		copyCommandList->Barrier(afterCopyBufferBarriers);

		copyCommandList->Close();

		const PonyEngine::RenderDevice::ICopyCommandList* const copyCommand = copyCommandList.get();
		const auto copyFenceValueSync = std::pair(copyFence.get(), ++copyFenceValue);
		renderDevice->Execute(std::span<const PonyEngine::RenderDevice::ICopyCommandList* const>(&copyCommand, 1uz), PonyEngine::RenderDevice::QueueSync
		{
			.after = std::span(&copyFenceValueSync, 1uz)
		});

		const std::uint8_t currentBackBufferIndex = renderDevice->CurrentSwapChainBufferIndex();
		graphicsCommandList->Reset();
		graphicsCommandList->BindContainers(srvContainer.get(), nullptr);
		graphicsCommandList->SetRasterRegion(PonyEngine::RenderDevice::RasterRegion
		{
			.viewport = PonyEngine::Math::CornerRect<float>(static_cast<PonyEngine::Math::Vector2<float>>(resolution)),
			.scissor = PonyEngine::Math::CornerRect<std::uint32_t>(resolution)
		});

		const auto renderBufferBarriers = std::array<PonyEngine::RenderDevice::BufferBarrier, 2>
		{
			PonyEngine::RenderDevice::BufferBarrier
			{
				.buffer = gpuTransforms.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::None,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::VertexShading,
				.beforeAccesses = std::nullopt,
				.afterAccesses = PonyEngine::RenderDevice::ResourceAccess::ShaderResource
			},
			PonyEngine::RenderDevice::BufferBarrier
			{
				.buffer = staticGpuDataBuffer.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::None,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::VertexShading | PonyEngine::RenderDevice::PipelineStage::PixelShading,
				.beforeAccesses = std::nullopt,
				.afterAccesses = PonyEngine::RenderDevice::ResourceAccess::ShaderResource
			}
		};
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
		graphicsCommandList->Barrier(renderBufferBarriers, renderTextureBarriers);
		graphicsCommandList->ClearRTV(*rtvContainer, renderTargetContainerIndex, PonyEngine::Math::ColorRGBA<float>::Black());
		graphicsCommandList->ClearDSV(*dsvContainer, depthContainerIndex, 1.f, 0u);
		const auto renderTargetBinding = PonyEngine::RenderDevice::RenderTargetBinding{.container = rtvContainer.get(), .index = renderTargetContainerIndex};
		const auto depthTargetBinding = PonyEngine::RenderDevice::DepthStencilBinding{.container = dsvContainer.get(), .index = depthContainerIndex};
		graphicsCommandList->BindTargets(renderTargetBinding, depthTargetBinding);
		graphicsCommandList->BindPipelineState(*boxPipelineState);
		const auto bindings = std::array<PonyEngine::RenderDevice::ShaderDataBinding, 4>
		{
			PonyEngine::RenderDevice::ShaderDataBinding{.layoutSetIndex = 0u, .containerIndex = boxTransformContainerIndex},
			PonyEngine::RenderDevice::ShaderDataBinding{.layoutSetIndex = 1u, .containerIndex = boxMeshletContainerIndex},
			PonyEngine::RenderDevice::ShaderDataBinding{.layoutSetIndex = 2u, .containerIndex = boxPositionContainerIndex},
			PonyEngine::RenderDevice::ShaderDataBinding{.layoutSetIndex = 3u, .containerIndex = greenBoxMaterialContainerIndex}
		};
		graphicsCommandList->BindGraphics(bindings);
		graphicsCommandList->DispatchGraphics(2u);
		const auto resolveBufferBarriers = std::array<PonyEngine::RenderDevice::BufferBarrier, 2>
		{
			PonyEngine::RenderDevice::BufferBarrier
			{
				.buffer = gpuTransforms.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::VertexShading,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::None,
				.beforeAccesses = PonyEngine::RenderDevice::ResourceAccess::ShaderResource,
				.afterAccesses = std::nullopt
			},
			PonyEngine::RenderDevice::BufferBarrier
			{
				.buffer = staticGpuDataBuffer.get(),
				.beforeStages = PonyEngine::RenderDevice::PipelineStage::VertexShading | PonyEngine::RenderDevice::PipelineStage::PixelShading,
				.afterStages = PonyEngine::RenderDevice::PipelineStage::None,
				.beforeAccesses = PonyEngine::RenderDevice::ResourceAccess::ShaderResource,
				.afterAccesses = std::nullopt
			}
		};
		const auto resolveTextureBarriers = std::array<PonyEngine::RenderDevice::TextureBarrier, 3>
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
		graphicsCommandList->Barrier(resolveBufferBarriers, resolveTextureBarriers);
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

		const auto copyWait = std::pair<const PonyEngine::RenderDevice::IFence*, std::uint64_t>(copyFence.get(), copyFenceValue);
		const auto finishSync = std::pair(graphicsFence.get(), ++graphicsFenceValue);
		const PonyEngine::RenderDevice::IGraphicsCommandList* const commandList = graphicsCommandList.get();
		renderDevice->Execute(std::span(&commandList, 1uz), PonyEngine::RenderDevice::QueueSync
		{
			.before = std::span(&copyWait, 1uz),
			.after = std::span(&finishSync, 1uz)
		});

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

	GameService::GpuTransform::GpuTransform() noexcept :
		mvp(PonyEngine::Math::Matrix4x4<float>::Identity()),
		determinant(mvp.Determinant())
	{
	}

	GameService::GpuTransform::GpuTransform(const PonyEngine::Math::Matrix4x4<float>& mvp) noexcept :
		mvp(mvp),
		determinant(this->mvp.Determinant())
	{
	}

	const PonyEngine::Math::Matrix4x4<float>& GameService::GpuTransform::MVP() const noexcept
	{
		return mvp;
	}
}
