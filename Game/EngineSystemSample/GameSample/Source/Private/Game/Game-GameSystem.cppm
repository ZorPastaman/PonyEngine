module;

#include "PonyEngine/Log/Log.h"

export module Game:GameSystem;

import std;

import PonyEngine.Engine.Extension;
import PonyEngine.Log;

export namespace Game
{
	class GameSystem final : public PonyEngine::Engine::ITickableSystem
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit GameSystem(PonyEngine::Engine::IEngineContext& engine) noexcept;
		GameSystem(const GameSystem&) = delete;
		GameSystem(GameSystem&&) = delete;

		~GameSystem() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		GameSystem& operator =(const GameSystem&) = delete;
		GameSystem& operator =(GameSystem&&) = delete;

	private:
		PonyEngine::Engine::IEngineContext* engine;
	};
}

namespace Game
{
	GameSystem::GameSystem(PonyEngine::Engine::IEngineContext& engine) noexcept :
		engine{&engine}
	{
		// Constructor logic can be added here.
		// The system may initialize its dependencies here.
		PONY_LOG(this->engine->Logger(), PonyEngine::Log::LogType::Info, "Game system constructed.");
	}

	GameSystem::~GameSystem() noexcept
	{
		// Destructor logic can be added here.
		// The system has to clean up here.
		PONY_LOG(this->engine->Logger(), PonyEngine::Log::LogType::Info, "Game system destructed.");
	}

	void GameSystem::Begin()
	{
		// Prepare the system for ticking.
		PONY_LOG(engine->Logger(), PonyEngine::Log::LogType::Info, "Game system begun.");
	}

	void GameSystem::End()
	{
		// Clean up the system after ticking.
		PONY_LOG(engine->Logger(), PonyEngine::Log::LogType::Info, "Game system ended.");
	}

	void GameSystem::Tick()
	{
		// The system tick logic goes here.
		// This is the place to update the system state, process events, etc.
		PONY_LOG(engine->Logger(), PonyEngine::Log::LogType::Verbose, "Game system ticked.");
	}
}
