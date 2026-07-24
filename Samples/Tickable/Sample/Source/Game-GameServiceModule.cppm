export module Game:GameServiceModule;

import std;

import PonyEngine.Application;

import :GameService;

export namespace Game
{
	class GameServiceModule final : public PonyEngine::Application::IModule
	{
	public:
		virtual void StartUp(PonyEngine::Application::IModuleContext& context) override;
		virtual void ShutDown(PonyEngine::Application::IModuleContext& context) override;

	private:
		std::unique_ptr<GameService> gameService;
	};
}

namespace Game
{
	void GameServiceModule::StartUp(PonyEngine::Application::IModuleContext& context)
	{
		gameService = std::make_unique<GameService>(context.Application());
		context.AddTickable(gameService->Tickable(), PonyEngine::Application::TickableOrder{.beginOrder = 0, .tickOrder = 0});
	}

	void GameServiceModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
		context.RemoveTickable(gameService->Tickable(), PonyEngine::Application::TickableOrder{.beginOrder = 0, .tickOrder = 0});
		gameService.reset();
	}
}
