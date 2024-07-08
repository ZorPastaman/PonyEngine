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

import PonyEngine.Core;

import Game.Factories;

import :GameSystem;

export namespace Game
{
	/// @brief Game system factory.
	class GameSystemFactory final : public IGameSystemFactory
	{
	public:
		/// @brief Creates a game system factory.
		[[nodiscard("Pure constructor")]]
		GameSystemFactory() noexcept = default;
		GameSystemFactory(const GameSystemFactory&) = delete;
		GameSystemFactory(GameSystemFactory&&) = delete;

		~GameSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyEngine::Core::SystemInfo Create(PonyEngine::Core::IEngine& engine) override;

		[[nodiscard("Pure function")]]
		virtual const char* GetSystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		GameSystemFactory& operator =(const GameSystemFactory&) = delete;
		GameSystemFactory& operator =(GameSystemFactory&&) = delete;

		static constexpr const char* StaticName = "Game::GameSystemFactory"; ///< Class name.

		// TODO: Add logger to all the system factories.
	};
}

namespace Game
{
	void DestroyGameSystem(PonyEngine::Core::ISystem* system);

	PonyEngine::Core::SystemInfo GameSystemFactory::Create(PonyEngine::Core::IEngine& engine)
	{
		const auto gameSystem = new GameSystem(engine);

		return PonyEngine::Core::SystemInfo::Create<GameSystem, IGameSystem>(gameSystem, DestroyGameSystem, true);
	}

	const char* GameSystemFactory::GetSystemName() const noexcept
	{
		return GameSystem::StaticName;
	}

	const char* GameSystemFactory::GetName() const noexcept
	{
		return StaticName;
	}

	void DestroyGameSystem(PonyEngine::Core::ISystem* const system)
	{
		assert((dynamic_cast<GameSystem*>(system) && "Tried to destroy a system of the wrong type."));
		delete static_cast<GameSystem*>(system);
	}
}
