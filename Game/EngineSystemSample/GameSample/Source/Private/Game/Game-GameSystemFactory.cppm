module;

#include "PonyEngine/Log/Log.h"

export module Game:GameSystemFactory;

import std;

import PonyEngine.Application;
import PonyEngine.Engine.Extension;
import PonyEngine.Log;

import :GameSystem;

export namespace Game
{
	class GameSystemFactory final : public PonyEngine::Engine::ISystemFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit GameSystemFactory(PonyEngine::Application::IModuleContext& context) noexcept;
		GameSystemFactory(const GameSystemFactory&) = delete;
		GameSystemFactory(GameSystemFactory&&) = delete;

		~GameSystemFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual PonyEngine::Engine::SystemData Create(PonyEngine::Engine::IEngineContext& engine) override;

		GameSystemFactory& operator =(const GameSystemFactory&) = delete;
		GameSystemFactory& operator =(GameSystemFactory&&) = delete;

	private:
		PonyEngine::Application::IModuleContext* context;
	};
}

namespace Game
{
	GameSystemFactory::GameSystemFactory(PonyEngine::Application::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	PonyEngine::Engine::SystemData GameSystemFactory::Create(PonyEngine::Engine::IEngineContext& engine)
	{
		// Construct the game system.
		PONY_LOG(context->Logger(), PonyEngine::Log::LogType::Debug, "Constructing GameSystem");
		return PonyEngine::Engine::SystemData
		{
			.system = std::static_pointer_cast<PonyEngine::Engine::ITickableSystem>(std::make_shared<GameSystem>(engine))
		};
	}
}
