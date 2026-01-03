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
			renderDevice->SwitchBackend(1uz);
		}
	}

	GameService::~GameService() noexcept
	{
	}

	void GameService::Begin()
	{
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
	}
}
