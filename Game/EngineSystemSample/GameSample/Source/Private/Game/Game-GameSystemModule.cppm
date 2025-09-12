module;

#include "PonyEngine/Log/Log.h"

export module Game:GameSystemModule;

import std;

import PonyEngine.Application;
import PonyEngine.Engine.Extension;
import PonyEngine.Log;

import :GameSystemFactory;

export namespace Game
{
	class GameSystemModule final : public PonyEngine::Application::IModule
	{
	public:
		virtual void StartUp(PonyEngine::Application::IModuleContext& context) override;
		virtual void ShutDown(const PonyEngine::Application::IModuleContext& context) override;
	};
}

namespace Game
{
	void GameSystemModule::StartUp(PonyEngine::Application::IModuleContext& context)
	{
		// Add game system factory.
		PONY_LOG(context.Logger(), PonyEngine::Log::LogType::Info, "Constructing game system factory.");
		context.AddData<PonyEngine::Engine::ISystemFactory>(std::make_shared<GameSystemFactory>(context));
	}

	void GameSystemModule::ShutDown(const PonyEngine::Application::IModuleContext& context)
	{
		// Nothing to do here. The factory will be destroyed automatically.
	}
}
