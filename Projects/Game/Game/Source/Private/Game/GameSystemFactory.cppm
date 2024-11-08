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

import <string_view>;
import <utility>;

import PonyBase.Memory;
import PonyBase.ObjectUtility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Core.Factory;

import Game.Factory;

import :GameSystem;

export namespace Game
{
	/// @brief Game system factory.
	class GameSystemFactory final : public IGameSystemFactory
	{
	public:
		/// @brief Creates a game system factory.
		[[nodiscard("Pure constructor")]]
		explicit GameSystemFactory() noexcept = default;
		GameSystemFactory(const GameSystemFactory&) = delete;
		GameSystemFactory(GameSystemFactory&&) = delete;

		~GameSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyEngine::Core::SystemData Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::EngineSystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		GameSystemFactory& operator =(const GameSystemFactory&) = delete;
		GameSystemFactory& operator =(GameSystemFactory&&) = delete;

		static constexpr std::string_view StaticName = "Game::GameSystemFactory"; ///< Class name.
	};
}

namespace Game
{
	PonyEngine::Core::SystemData GameSystemFactory::Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::EngineSystemParams&)
	{
		auto system = PonyBase::Memory::UniquePointer<GameSystem>::Create(engine);
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IGameSystem>(*system);

		return PonyEngine::Core::SystemData
		{
			.system = PonyBase::Memory::UniquePointer<PonyEngine::Core::ITickableEngineSystem>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	std::string_view GameSystemFactory::SystemName() const noexcept
	{
		return GameSystem::StaticName;
	}

	std::string_view GameSystemFactory::Name() const noexcept
	{
		return StaticName;
	}
}
