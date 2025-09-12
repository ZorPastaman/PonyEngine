module;

#include "PonyEngine/Log/Log.h"

export module Game;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

export namespace Game
{
	class GameModule final : public PonyEngine::Application::IModule
	{
	public:
		virtual void StartUp(PonyEngine::Application::IModuleContext& context) override;
		virtual void ShutDown(const PonyEngine::Application::IModuleContext& context) override;
	};
}

namespace Game
{
	void GameModule::StartUp(PonyEngine::Application::IModuleContext& context)
	{
		// Add startup logic here. The log can be safely removed.
		PONY_LOG(context.Logger(), PonyEngine::Log::LogType::Info, "Game module started up.");
	}

	void GameModule::ShutDown(const PonyEngine::Application::IModuleContext& context)
	{
		// Add shutdown logic here. The log can be safely removed.
		PONY_LOG(context.Logger(), PonyEngine::Log::LogType::Info, "Game module shut down.");
	}
}
