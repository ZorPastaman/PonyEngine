module;

#include "PonyEngine/Log/Log.h"

export module Game:GameService;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

export namespace Game
{
	class GameService final : private PonyEngine::Application::ITickable
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit GameService(PonyEngine::Application::IApplication& application) noexcept;
		GameService(const GameService&) = delete;
		GameService(GameService&&) = delete;

		~GameService() noexcept;

		[[nodiscard("Pure function")]]
		PonyEngine::Application::ITickable& Tickable() noexcept;

		GameService& operator =(const GameService&) = delete;
		GameService& operator =(GameService&&) = delete;

	private:
		virtual void Begin() override;
		virtual void End() override;
		virtual void Tick() override;

		PonyEngine::Application::IApplication* application;
		PonyEngine::Log::ILogService* logService;
	};
}

namespace Game
{
	GameService::GameService(PonyEngine::Application::IApplication& application) noexcept :
		application{&application},
		logService{this->application->FindInterface<PonyEngine::Log::ILogService>()}
	{
		// Constructor logic can be added here.
		// The service may initialize its dependencies here.
		PONY_LOG(logService, PonyEngine::Log::LogType::Info, "Game service constructed.");
	}

	GameService::~GameService() noexcept
	{
		// Destructor logic can be added here.
		// The service has to clean up here.
		PONY_LOG(logService, PonyEngine::Log::LogType::Info, "Game service destructed.");
	}

	PonyEngine::Application::ITickable& GameService::Tickable() noexcept
	{
		return *this;
	}

	void GameService::Begin()
	{
		// Prepare the service for ticking.
		PONY_LOG(logService, PonyEngine::Log::LogType::Info, "Game service begun.");
	}

	void GameService::End()
	{
		// Clean up the service after ticking.
		PONY_LOG(logService, PonyEngine::Log::LogType::Info, "Game service ended.");
	}

	void GameService::Tick()
	{
		// The service tick logic goes here.
		// This is the place to update the service state, process events, etc.
	}
}
