module;

#include "PonyEngine/Log/Log.h"

export module Game:GameSystemFactory;

import std;

import PonyEngine.Core;
import PonyEngine.Engine.Ext;
import PonyEngine.Log;

import :GameSystem;

export namespace Game
{
	class GameSystemFactory final : public PonyEngine::Engine::ISystemFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit GameSystemFactory(PonyEngine::Core::IModuleContext& context) noexcept;
		GameSystemFactory(const GameSystemFactory&) = delete;
		GameSystemFactory(GameSystemFactory&&) = delete;

		~GameSystemFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual PonyEngine::Engine::SystemData Create(PonyEngine::Engine::IEngineContext& engine) override;

		[[nodiscard("Pure function")]]
		virtual std::int32_t InitOrder() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::int32_t TickOrder() const noexcept override;

		GameSystemFactory& operator =(const GameSystemFactory&) = delete;
		GameSystemFactory& operator =(GameSystemFactory&&) = delete;

	private:
		PonyEngine::Core::IModuleContext* context; ///< Module context.
	};
}

namespace Game
{
	GameSystemFactory::GameSystemFactory(PonyEngine::Core::IModuleContext& context) noexcept :
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

	std::int32_t GameSystemFactory::InitOrder() const noexcept
	{
		// Initialization order.
		// It sets the order of its creation and beginning.
		// Ending and destruction order is always a reverse of the initialization order.
		return 0;
	}

	std::int32_t GameSystemFactory::TickOrder() const noexcept
	{
		// Tick order of the system.
		return 0;
	}
}
