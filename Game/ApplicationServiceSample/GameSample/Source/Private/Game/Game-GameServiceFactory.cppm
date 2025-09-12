module;

#include "PonyEngine/Log/Log.h"

export module Game:GameServiceFactory;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :GameService;

export namespace Game
{
	class GameServiceFactory final : public PonyEngine::Application::IServiceFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit GameServiceFactory(PonyEngine::Application::IModuleContext& context) noexcept;
		GameServiceFactory(const GameServiceFactory&) = delete;
		GameServiceFactory(GameServiceFactory&&) = delete;

		~GameServiceFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual PonyEngine::Application::ServiceData Create(PonyEngine::Application::IApplicationContext& application) override;

		GameServiceFactory& operator =(const GameServiceFactory&) = delete;
		GameServiceFactory& operator =(GameServiceFactory&&) = delete;

	private:
		PonyEngine::Application::IModuleContext* context;
	};
}

namespace Game
{
	GameServiceFactory::GameServiceFactory(PonyEngine::Application::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	PonyEngine::Application::ServiceData GameServiceFactory::Create(PonyEngine::Application::IApplicationContext& application)
	{
		// Construct the game service.
		PONY_LOG(context->Logger(), PonyEngine::Log::LogType::Debug, "Constructing GameService");
		return PonyEngine::Application::ServiceData
		{
			.service = std::static_pointer_cast<PonyEngine::Application::ITickableService>(std::make_shared<GameService>(application)),
			.tickOrder = -1
		};
	}
}
