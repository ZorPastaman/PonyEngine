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

		PonyEngine::Application::IApplicationContext* application;
		PonyEngine::RenderDevice::IRenderDeviceService* renderDevice;

		std::shared_ptr<PonyEngine::RenderDevice::IGraphicsCommandList> graphicsCommandList;
		std::shared_ptr<PonyEngine::RenderDevice::IComputeCommandList> computeCommandList;
		std::shared_ptr<PonyEngine::RenderDevice::ICopyCommandList> copyCommandList;
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
		const PonyEngine::RenderDevice::TextureFormatId format = renderDevice->TextureFormatId(PonyEngine::RenderDevice::TextureFormat::R8G8B8A8_Unorm);
		const PonyEngine::RenderDevice::TextureFormatFeature feature = renderDevice->TextureFormatFeatures(format);
		const PonyEngine::RenderDevice::TextureSupportResponse support = renderDevice->TextureSupport(PonyEngine::RenderDevice::TextureSupportRequest
		{
			.format = format,
			.dimension = PonyEngine::RenderDevice::TextureDimension::Texture2D,
			.usage = PonyEngine::RenderDevice::TextureUsage::ShaderResource | PonyEngine::RenderDevice::TextureUsage::RenderTarget
		});
		const PonyEngine::RenderDevice::SwapChainSupport swapChainSupport = renderDevice->SwapChainSupport();

		const std::shared_ptr<PonyEngine::RenderDevice::IBuffer> buffer = renderDevice->CreateBuffer(PonyEngine::RenderDevice::HeapType::Default, PonyEngine::RenderDevice::BufferParams
		{
			.size = 1024ull,
			.usage = PonyEngine::RenderDevice::BufferUsage::ShaderResource
		});

		const PonyEngine::RenderDevice::TextureFormatId textureFormat = renderDevice->TextureFormatId(PonyEngine::RenderDevice::TextureFormat::R8G8B8A8_Unorm);
		const PonyEngine::RenderDevice::TextureFormatId castableTextureFormat = renderDevice->TextureFormatId(PonyEngine::RenderDevice::TextureFormat::R8G8B8A8_Snorm);
		const std::shared_ptr<PonyEngine::RenderDevice::ITexture> texture = renderDevice->CreateTexture(PonyEngine::RenderDevice::HeapType::Default, PonyEngine::RenderDevice::TextureParams
		{
			.format = textureFormat,
			.castableFormats = std::span<const PonyEngine::RenderDevice::TextureFormatId>(&castableTextureFormat, 1uz),
			.size = PonyEngine::Math::Vector3<std::uint32_t>(1024u, 1024u, 1u),
			.dimension = PonyEngine::RenderDevice::TextureDimension::Texture2D,
			.usage = PonyEngine::RenderDevice::TextureUsage::ShaderResource | PonyEngine::RenderDevice::TextureUsage::RenderTarget,
			.flags = PonyEngine::RenderDevice::TextureFlag::SRGB
		});

		renderDevice->CreateSwapChain(PonyEngine::RenderDevice::SwapChainParams
		{
			.format = textureFormat,
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
		graphicsCommandList->Reset();
		computeCommandList->Reset();
		copyCommandList->Reset();
		graphicsCommandList->Close();
		computeCommandList->Close();
		copyCommandList->Close();
		const auto graphics = std::array<const PonyEngine::RenderDevice::IGraphicsCommandList*, 1>{ graphicsCommandList.get() };
		const auto compute = std::array<const PonyEngine::RenderDevice::IComputeCommandList*, 1>{ computeCommandList.get() };
		const auto copy = std::array<const PonyEngine::RenderDevice::ICopyCommandList*, 1>{ copyCommandList.get() };
		renderDevice->Execute(std::span(graphics.data(), 1u));
		renderDevice->Execute(std::span(compute.data(), 1u));
		renderDevice->Execute(std::span(copy.data(), 1u));
	}

	void GameService::End()
	{
	}

	void GameService::AddTickableServices(PonyEngine::Application::ITickableServiceAdder& adder)
	{
		adder.Add(*this, 0);
	}

	void GameService::Tick()
	{
		renderDevice->PresentNextSwapChainBuffer();
	}
}
