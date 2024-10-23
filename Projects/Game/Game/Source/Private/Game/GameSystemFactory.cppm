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

export module Game.Implementation:GameSystemFactory;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Core.Factory;

import Game.Factory;

import :GameSystem;

export namespace Game
{
	/// @brief Game system factory.
	class GameSystemFactory final : public IGameSystemFactory, public PonyEngine::Core::ISystemDestroyer
	{
	public:
		/// @brief Creates a game system factory.
		[[nodiscard("Pure constructor")]]
		explicit GameSystemFactory() noexcept = default;
		GameSystemFactory(const GameSystemFactory&) = delete;
		GameSystemFactory(GameSystemFactory&&) = delete;

		~GameSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyEngine::Core::SystemData Create(PonyEngine::Core::IEngine& engine, const PonyEngine::Core::SystemParams& params) override;
		virtual void Destroy(PonyEngine::Core::ISystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual GameSystemParams& SystemParams() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const GameSystemParams& SystemParams() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		GameSystemFactory& operator =(const GameSystemFactory&) = delete;
		GameSystemFactory& operator =(GameSystemFactory&&) = delete;

		static constexpr auto StaticName = "Game::GameSystemFactory"; ///< Class name.

	private:
		GameSystemParams systemParams; ///< Game system parameters.
	};
}

namespace Game
{
	PonyEngine::Core::SystemData GameSystemFactory::Create(PonyEngine::Core::IEngine& engine, const PonyEngine::Core::SystemParams&)
	{
		const auto system = new GameSystem(engine);
		const auto deleter = PonyEngine::Core::SystemDeleter(*this);

		return PonyEngine::Core::SystemData
		{
			.system = PonyEngine::Core::SystemUniquePtr(system, deleter),
			.tickableSystem = system
		};
	}

	void GameSystemFactory::Destroy(PonyEngine::Core::ISystem* const system) noexcept
	{
		assert(dynamic_cast<GameSystem*>(system) && "Tried to destroy a system of the wrong type.");
		delete static_cast<GameSystem*>(system);
	}

	GameSystemParams& GameSystemFactory::SystemParams() noexcept
	{
		return systemParams;
	}

	const GameSystemParams& GameSystemFactory::SystemParams() const noexcept
	{
		return systemParams;
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
