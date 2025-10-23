export module Game;

import std;

import PonyEngine.Application.Extension;

export namespace Game
{
	class GameModule final : public PonyEngine::Application::IModule
	{
	public:
		virtual void StartUp(PonyEngine::Application::IModuleContext& context) override;
		virtual void ShutDown(PonyEngine::Application::IModuleContext& context) override;
	};
}

namespace Game
{
	void GameModule::StartUp(PonyEngine::Application::IModuleContext& context)
	{
		// Add startup logic here.
	}

	void GameModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
		// Add shutdown logic here.
	}
}
