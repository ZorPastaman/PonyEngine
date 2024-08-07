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
		virtual PonyEngine::Core::SystemUniquePtr Create(PonyEngine::Core::IEngine& engine) override;
		virtual void Destroy(PonyEngine::Core::ISystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

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

	PonyEngine::Core::SystemUniquePtr GameSystemFactory::Create(PonyEngine::Core::IEngine& engine)
	{
		return PonyEngine::Core::SystemUniquePtr(new GameSystem(engine), PonyEngine::Core::SystemDeleter(*this));
	}

	void GameSystemFactory::Destroy(PonyEngine::Core::ISystem* const system) noexcept
	{
		assert((dynamic_cast<GameSystem*>(system) && "Tried to destroy a system of the wrong type."));
		delete static_cast<GameSystem*>(system);
	}

	const char* GameSystemFactory::SystemName() const noexcept
	{
		return GameSystem::StaticName;
	}

	const char* GameSystemFactory::Name() const noexcept
	{
		return StaticName;
	}
}
