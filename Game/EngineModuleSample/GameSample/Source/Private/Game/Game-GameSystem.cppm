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

		~GameSystem() noexcept = default;

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
		// The system may initialize only required components or internal dependencies in the constructor.
		// External dependencies like other system dependencies must be initialized in the Begin() function.
		// The log can be safely removed.
		PONY_LOG(this->engine->Logger(), PonyEngine::Log::LogType::Info, "Game system constructed.");
	}

	void GameSystem::Begin()
	{
		// Prepare the system for ticking.
		// This is the place to initialize external dependencies like other systems.
		// The log can be safely removed.
		PONY_LOG(engine->Logger(), PonyEngine::Log::LogType::Info, "Game system begun.");
	}

	void GameSystem::End()
	{
		// Clean up the system after ticking.
		// This is the place to clean up external dependencies like other systems.
		// The log can be safely removed.
		PONY_LOG(engine->Logger(), PonyEngine::Log::LogType::Info, "Game system ended.");
	}

	void GameSystem::Tick()
	{
		// The system tick logic goes here.
		// This is the place to update the system state, process events, etc.
		// The log can be safely removed.
		PONY_LOG(engine->Logger(), PonyEngine::Log::LogType::Verbose, "Game system ticked.");
	}
}
