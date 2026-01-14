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
		PonyEngine::Render::IRenderDeviceService* renderDevice;
	};
}

namespace Game
{
	GameService::GameService(PonyEngine::Application::IApplicationContext& application) :
		application{&application},
		renderDevice{&this->application->GetService<PonyEngine::Render::IRenderDeviceService>()}
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
		const PonyEngine::Render::TextureFormatId format = renderDevice->TextureFormatId(PonyEngine::Render::TextureFormat::R8G8B8A8_Unorm);
		const PonyEngine::Render::TextureFormatFeature feature = renderDevice->TextureFormatFeatures(format);
		const PonyEngine::Render::TextureSupportResponse support = renderDevice->TextureSupport(PonyEngine::Render::TextureSupportRequest
		{
			.format = format,
			.dimension = PonyEngine::Render::TextureDimension::Texture2D,
			.usage = PonyEngine::Render::TextureUsage::ShaderResource | PonyEngine::Render::TextureUsage::RenderTarget
		});
		const PonyEngine::Render::SwapChainSupport swapChainSupport = renderDevice->SwapChainSupport();

		const std::shared_ptr<PonyEngine::Render::IBuffer> buffer = renderDevice->CreateBuffer(PonyEngine::Render::HeapType::Default, PonyEngine::Render::BufferParams
		{
			.size = 1024ull,
			.usage = PonyEngine::Render::BufferUsage::ShaderResource
		});

		const PonyEngine::Render::TextureFormatId textureFormat = renderDevice->TextureFormatId(PonyEngine::Render::TextureFormat::R8G8B8A8_Unorm);
		const PonyEngine::Render::TextureFormatId castableTextureFormat = renderDevice->TextureFormatId(PonyEngine::Render::TextureFormat::R8G8B8A8_Snorm);
		const std::shared_ptr<PonyEngine::Render::ITexture> texture = renderDevice->CreateTexture(PonyEngine::Render::HeapType::Default, PonyEngine::Render::TextureParams
		{
			.format = textureFormat,
			.castableFormats = std::span<const PonyEngine::Render::TextureFormatId>(&castableTextureFormat, 1uz),
			.size = PonyEngine::Math::Vector3<std::uint32_t>(1024u, 1024u, 1u),
			.dimension = PonyEngine::Render::TextureDimension::Texture2D,
			.usage = PonyEngine::Render::TextureUsage::ShaderResource | PonyEngine::Render::TextureUsage::RenderTarget,
			.flags = PonyEngine::Render::TextureFlag::SRGB
		});

		renderDevice->CreateSwapChain(PonyEngine::Render::SwapChainParams
		{
			.format = textureFormat,
			.size = std::nullopt,
			.bufferCount = 3u,
			.alphaMode = PonyEngine::Render::SwapChainAlphaMode::Ignore,
			.scalingMode = PonyEngine::Render::SwapChainScaling::NoScaling,
			.swapEffect = PonyEngine::Render::SwapChainEffect::FlipDiscard,
			.syncMode = PonyEngine::Render::SwapChainSync::FullSync,
			.flags = PonyEngine::Render::SwapChainFlag::SRGB,
			.usage = PonyEngine::Render::TextureUsage::RenderTarget
		});
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
