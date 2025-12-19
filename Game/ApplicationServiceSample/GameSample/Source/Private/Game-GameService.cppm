export module Game:GameService;

import std;

import PonyEngine.Application.Ext;

export namespace Game
{
	class GameService final : public PonyEngine::Application::IService, private PonyEngine::Application::ITickableService
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit GameService(PonyEngine::Application::IApplicationContext& application) noexcept;
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
	};
}

namespace Game
{
	GameService::GameService(PonyEngine::Application::IApplicationContext& application) noexcept :
		application{&application}
	{
		// Constructor logic can be added here.
		// The service may initialize its dependencies here.
	}

	GameService::~GameService() noexcept
	{
		// Destructor logic can be added here.
		// The service has to clean up here.
	}

	void GameService::Begin()
	{
		// Prepare the service for ticking.
	}

	void GameService::End()
	{
		// Clean up the service after ticking.
	}

	void GameService::AddTickableServices(PonyEngine::Application::ITickableServiceAdder& adder)
	{
		adder.Add(*this, 0);
	}

	void GameService::Tick()
	{
		// The service tick logic goes here.
		// This is the place to update the service state, process events, etc.
	}
}
