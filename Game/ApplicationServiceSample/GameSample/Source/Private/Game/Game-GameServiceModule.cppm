module;

#include "PonyEngine/Log/Log.h"

export module Game:GameServiceModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :GameServiceFactory;

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
		// Add game service factory.
		PONY_LOG(context.Logger(), PonyEngine::Log::LogType::Info, "Constructing game service factory.");
		context.AddService(std::make_shared<GameServiceFactory>(context));
	}

	void GameServiceModule::ShutDown(const PonyEngine::Application::IModuleContext& context)
	{
		// Nothing to do here. The factory will be destroyed automatically.
	}
}
