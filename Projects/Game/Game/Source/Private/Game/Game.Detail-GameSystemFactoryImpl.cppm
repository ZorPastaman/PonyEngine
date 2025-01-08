/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Game.Detail:GameSystemFactory;

import <memory>;
import <typeinfo>;
import <utility>;

import PonyBase.Utility;

import PonyDebug.Log;

import PonyEngine.Core;

import Game;

import :GameSystem;

export namespace Game
{
	/// @brief Game system factory.
	class GameSystemFactoryImpl final : public GameSystemFactory
	{
	public:
		/// @brief Creates a game system factory.
		/// @param application Application context.
		/// @param factoryParams Game system factory parameters.
		/// @param systemParams Game system parameters.
		[[nodiscard("Pure constructor")]]
		GameSystemFactoryImpl(PonyEngine::Core::IApplicationContext& application, const GameSystemFactoryParams& factoryParams, const GameSystemParams& systemParams) noexcept;
		GameSystemFactoryImpl(const GameSystemFactoryImpl&) = delete;
		GameSystemFactoryImpl(GameSystemFactoryImpl&&) = delete;

		virtual ~GameSystemFactoryImpl() noexcept override = default;

		[[nodiscard("Redundant call")]]
		virtual PonyEngine::Core::SystemData Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual const std::type_info& SystemType() const noexcept override;

		GameSystemFactoryImpl& operator =(const GameSystemFactoryImpl&) = delete;
		GameSystemFactoryImpl& operator =(GameSystemFactoryImpl&&) = delete;

	private:
		GameSystemParams gameSystemParams; ///< Game system parameters.

		PonyEngine::Core::IApplicationContext* application; ///< Application context.
	};
}

namespace Game
{
	GameSystemFactoryImpl::GameSystemFactoryImpl(PonyEngine::Core::IApplicationContext& application, const GameSystemFactoryParams&, const GameSystemParams& systemParams) noexcept :
		gameSystemParams(systemParams),
		application{&application}
	{
	}

	PonyEngine::Core::SystemData GameSystemFactoryImpl::Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params)
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

	const std::type_info& GameSystemFactoryImpl::SystemType() const noexcept
	{
		return typeid(GameSystem);
	}
}
