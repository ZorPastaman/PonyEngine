export module Game:GameService;

import std;

import PonyEngine.Application.Ext;
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
		static std::vector<std::byte> LoadShader(const std::filesystem::path& path);

		PonyEngine::Application::IApplicationContext* application;
		PonyEngine::RenderDevice::IRenderDeviceService* renderDevice;

		std::shared_ptr<PonyEngine::RenderDevice::IGraphicsCommandList> graphicsCommandList;
		std::shared_ptr<PonyEngine::RenderDevice::IComputeCommandList> computeCommandList;
		std::shared_ptr<PonyEngine::RenderDevice::ICopyCommandList> copyCommandList;

		std::shared_ptr<PonyEngine::RenderDevice::IFence> graphicsFence;
		std::shared_ptr<PonyEngine::RenderDevice::IFence> computeFence;
		std::shared_ptr<PonyEngine::RenderDevice::IFence> copyFence;
		std::uint64_t graphicsFenceValue = 0ull;
		std::uint64_t computeFenceValue = 0ull;
		std::uint64_t copyFenceValue = 0ull;
		std::shared_ptr<PonyEngine::RenderDevice::IWaiter> waiter;

		std::shared_ptr<PonyEngine::RenderDevice::IGraphicsPipelineState> boxPipelineState;
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

		graphicsCommandList = renderDevice->CreateGraphicsCommandList();
		computeCommandList = renderDevice->CreateComputeCommandList();
		copyCommandList = renderDevice->CreateCopyCommandList();
		graphicsFence = renderDevice->CreateFence();
		computeFence = renderDevice->CreateFence();
		copyFence = renderDevice->CreateFence();
		graphicsFenceValue = graphicsFence->CompletedValue();
		computeFenceValue = computeFence->CompletedValue();
		copyFenceValue = copyFence->CompletedValue();
		waiter = renderDevice->CreateWaiter();

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
			.descriptorSets = descriptorSets,
			.flags = PonyEngine::RenderDevice::PipelineLayoutFlag::None
		});

		const std::vector<std::byte> triangleShader = LoadShader(TRIANGLE_SHADER);
		const std::vector<std::byte>  pixelShader = LoadShader(PIXEL_SHADER);
		constexpr auto opaqueBlendParams = PonyEngine::RenderDevice::RenderTargetBlendParams
		{
			.blend = PonyEngine::RenderDevice::ColorBlendParams{},
		};
		const PonyEngine::RenderDevice::TextureFormatId renderTargetTextureFormat = renderDevice->TextureFormatId(PonyEngine::RenderDevice::TextureFormat::R8G8B8A8_Unorm);
		const PonyEngine::RenderDevice::TextureFormatId depthStencilTextureFormat = renderDevice->TextureFormatId(PonyEngine::RenderDevice::TextureFormat::D32_Float_S8X24_Uint);
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
				.sampleCount = PonyEngine::RenderDevice::SampleCount::X4
			},
			.attachmentParams = PonyEngine::RenderDevice::AttachmentParams
			{
				.renderTargetFormats = std::span<const PonyEngine::RenderDevice::TextureFormatId>(&renderTargetTextureFormat, 1uz),
				.depthStencilFormat = depthStencilTextureFormat
			}
		});
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
		renderDevice->PresentNextSwapChainBuffer();
	}

	std::vector<std::byte> GameService::LoadShader(const std::filesystem::path& path)
	{
		auto file = std::ifstream(path, std::ios::binary | std::ios::ate);
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
