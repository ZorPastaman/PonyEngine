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
		virtual const PonyEngine::Core::ISystemInfo& SystemInfo() const noexcept override;

		GameSystemFactoryImpl& operator =(const GameSystemFactoryImpl&) = delete;
		GameSystemFactoryImpl& operator =(GameSystemFactoryImpl&&) = delete;

	private:
		GameSystemParams gameSystemParams; ///< Game system parameters.
		PonyEngine::Core::SystemInfo<GameSystem, IGameSystem> gameSystemInfo; ///< Game system info.

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
		return gameSystemInfo.CreateSystemData(std::make_shared<GameSystem>(engine, params, gameSystemParams));
	}

	const PonyEngine::Core::ISystemInfo& GameSystemFactoryImpl::SystemInfo() const noexcept
	{
		return gameSystemInfo;
	}
}
