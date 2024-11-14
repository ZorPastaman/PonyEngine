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

export module Game.Impl:GameSystemFactory;

import <memory>;
import <string_view>;
import <utility>;

import PonyBase.ObjectUtility;

import PonyDebug.Log;

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
		/// @param application Application context.
		/// @param factoryParams Game system factory parameters.
		/// @param systemParams Game system parameters.
		[[nodiscard("Pure constructor")]]
		GameSystemFactory(PonyEngine::Core::IApplicationContext& application, const GameSystemFactoryParams& factoryParams, const GameSystemParams& systemParams) noexcept;
		GameSystemFactory(const GameSystemFactory&) = delete;
		GameSystemFactory(GameSystemFactory&&) = delete;

		~GameSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyEngine::Core::SystemData Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		GameSystemFactory& operator =(const GameSystemFactory&) = delete;
		GameSystemFactory& operator =(GameSystemFactory&&) = delete;

		static constexpr std::string_view StaticName = "Game::GameSystemFactory"; ///< Class name.

	private:
		GameSystemParams gameSystemParams; ///< Game system parameters.

		PonyEngine::Core::IApplicationContext* application; ///< Application context.
	};
}

namespace Game
{
	GameSystemFactory::GameSystemFactory(PonyEngine::Core::IApplicationContext& application, const GameSystemFactoryParams& factoryParams, const GameSystemParams& systemParams) noexcept :
		gameSystemParams(gameSystemParams),
		application{&application}
	{
	}

	PonyEngine::Core::SystemData GameSystemFactory::Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params)
	{
		auto system = std::make_unique<GameSystem>(engine, params, gameSystemParams);
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IGameSystem>(*system);

		return PonyEngine::Core::SystemData
		{
			.system = std::unique_ptr<PonyEngine::Core::TickableSystem>(std::move(system)),
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
