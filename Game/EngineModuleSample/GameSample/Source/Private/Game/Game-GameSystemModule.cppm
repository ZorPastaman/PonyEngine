module;

#include "PonyEngine/Log/Log.h"

export module Game:GameSystemModule;

import std;

import PonyEngine.Core;
import PonyEngine.Engine.Extension;
import PonyEngine.Log;

import :GameSystemFactory;

export namespace Game
{
	class GameSystemModule final : public PonyEngine::Core::IModule
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
	void GameSystemModule::StartUp(PonyEngine::Core::IModuleContext& context)
	{
		// Add game system factory.
		PONY_LOG(context.Logger(), PonyEngine::Log::LogType::Info, "Constructing game system factory.");
		context.AddData<PonyEngine::Engine::ISystemFactory>(std::make_shared<GameSystemFactory>(context));
	}

	void GameSystemModule::ShutDown(const PonyEngine::Core::IModuleContext& context)
	{
		// Nothing to do here. The factory will be destroyed automatically.
	}

	std::string_view GameSystemModule::Name() const noexcept
	{
		return "GameSystemModule";
	}
}
