module;

#include "PonyEngine/Log/Log.h"

export module Game;

import std;

import PonyEngine.Core;
import PonyEngine.Log;

export namespace Game
{
	class GameModule final : public PonyEngine::Core::IModule
	{
	public:
		virtual void StartUp(PonyEngine::Core::IModuleContext& context) override;
		virtual void ShutDown(const PonyEngine::Core::IModuleContext& context) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
	};
}

namespace Game
{
	void GameModule::StartUp(PonyEngine::Core::IModuleContext& context)
	{
		// Add startup logic here. The log can be safely removed.
		PONY_LOG(context.Application().Logger(), PonyEngine::Log::LogType::Info, "Game module started up.");
	}

	void GameModule::ShutDown(const PonyEngine::Core::IModuleContext& context)
	{
		// Add shutdown logic here. The log can be safely removed.
		PONY_LOG(context.Application().Logger(), PonyEngine::Log::LogType::Info, "Game module shut up.");
	}

	std::string_view GameModule::Name() const noexcept
	{
		return "GameModule";
	}
}
