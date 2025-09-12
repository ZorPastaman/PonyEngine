module;

#include "PonyEngine/Log/Log.h"

export module Game:GameService;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

export namespace Game
{
	class GameService final : public PonyEngine::Application::ITickableService
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit GameService(PonyEngine::Application::IApplicationContext& application) noexcept;
		GameService(const GameService&) = delete;
		GameService(GameService&&) = delete;

		~GameService() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		GameService& operator =(const GameService&) = delete;
		GameService& operator =(GameService&&) = delete;

	private:
		PonyEngine::Application::IApplicationContext* application;
	};
}

namespace Game
{
	GameService::GameService(PonyEngine::Application::IApplicationContext& application) noexcept :
		application{&application }
	{
		// Constructor logic can be added here.
		// The service may initialize its dependencies here.
		PONY_LOG(this->application->Logger(), PonyEngine::Log::LogType::Info, "Game service constructed.");
	}

	GameService::~GameService() noexcept
	{
		// Destructor logic can be added here.
		// The service has to clean up here.
		PONY_LOG(this->application->Logger(), PonyEngine::Log::LogType::Info, "Game service destructed.");
	}

	void GameService::Begin()
	{
		// Prepare the service for ticking.
		PONY_LOG(application->Logger(), PonyEngine::Log::LogType::Info, "Game service begun.");
	}

	void GameService::End()
	{
		// Clean up the service after ticking.
		PONY_LOG(application->Logger(), PonyEngine::Log::LogType::Info, "Game service ended.");
	}

	void GameService::Tick()
	{
		// The service tick logic goes here.
		// This is the place to update the service state, process events, etc.
		PONY_LOG(application->Logger(), PonyEngine::Log::LogType::Verbose, "Game service ticked.");
	}
}
