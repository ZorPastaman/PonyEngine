/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/EngineLog.h"

export module Game.Implementation:GameSystemFactory;

import PonyEngine.Core;
import PonyEngine.Core.Factory;
import PonyEngine.Log;

import Game.Factory;

import :GameSystem;

export namespace Game
{
	/// @brief Game system factory.
	class GameSystemFactory final : public IGameSystemFactory, public PonyEngine::Core::ISystemDestroyer
	{
	public:
		/// @brief Creates a game system factory.
		/// @param logger Logger to use.
		[[nodiscard("Pure constructor")]]
		explicit GameSystemFactory(PonyEngine::Log::ILogger& logger) noexcept;
		GameSystemFactory(const GameSystemFactory&) = delete;
		GameSystemFactory(GameSystemFactory&&) = delete;

		~GameSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyEngine::Core::SystemInfo Create(PonyEngine::Core::IEngine& engine) override;
		virtual void Destroy(PonyEngine::Core::ISystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetSystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		GameSystemFactory& operator =(const GameSystemFactory&) = delete;
		GameSystemFactory& operator =(GameSystemFactory&&) = delete;

		static constexpr auto StaticName = "Game::GameSystemFactory"; ///< Class name.

	private:
		PonyEngine::Log::ILogger* const logger;
	};
}

namespace Game
{
	GameSystemFactory::GameSystemFactory(PonyEngine::Log::ILogger& logger) noexcept :
		logger{&logger}
	{
	}

	PonyEngine::Core::SystemInfo GameSystemFactory::Create(PonyEngine::Core::IEngine& engine)
	{
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Create game system.");
		const auto gameSystem = new GameSystem(engine);
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Game system created.");

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Create game system info.");
		auto systemInfo = PonyEngine::Core::SystemInfo::Create<GameSystem, IGameSystem>(*gameSystem, *this, true);
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Debug, "Game system info created.");

		return systemInfo;
	}

	void GameSystemFactory::Destroy(PonyEngine::Core::ISystem* const system) noexcept
	{
		assert((dynamic_cast<GameSystem*>(system) && "Tried to destroy a system of the wrong type."));
		delete static_cast<GameSystem*>(system);
	}

	const char* GameSystemFactory::GetSystemName() const noexcept
	{
		return GameSystem::StaticName;
	}

	const char* GameSystemFactory::GetName() const noexcept
	{
		return StaticName;
	}
}
