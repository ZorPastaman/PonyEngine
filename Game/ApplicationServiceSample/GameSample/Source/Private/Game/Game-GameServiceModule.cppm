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
		virtual void ShutDown(const PonyEngine::Application::IModuleContext& context) override;
	};
}

namespace Game
{
	void GameServiceModule::StartUp(PonyEngine::Application::IModuleContext& context)
	{
		// Starting up module.
		const auto game = std::make_shared<GameService>(context.Application());
		PonyEngine::Application::ServiceData data;
		data.service = std::static_pointer_cast<PonyEngine::Application::ITickableService>(game);
		data.tickOrder = 5;
		context.AddService(data);
	}

	void GameServiceModule::ShutDown(const PonyEngine::Application::IModuleContext& context)
	{
		// Shutting down module.
	}
}
