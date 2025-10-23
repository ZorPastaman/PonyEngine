export module Game:GameServiceModule;

import std;

import PonyEngine.Application.Extension;

import :GameService;

export namespace Game
{
	class GameServiceModule final : public PonyEngine::Application::IModule
	{
	public:
		virtual void StartUp(PonyEngine::Application::IModuleContext& context) override;
		virtual void ShutDown(PonyEngine::Application::IModuleContext& context) override;

	private:
		PonyEngine::Application::ServiceHandle gameServiceHandle;
	};
}

namespace Game
{
	void GameServiceModule::StartUp(PonyEngine::Application::IModuleContext& context)
	{
		gameServiceHandle = context.ServiceModuleContext().AddService([&](PonyEngine::Application::IApplicationContext& application)
		{
			const auto game = std::make_shared<GameService>(application);
			PonyEngine::Application::ServiceData data;
			data.SetService(game, 0);
			return data;
		});
	}

	void GameServiceModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
		context.ServiceModuleContext().RemoveService(gameServiceHandle);
	}
}
