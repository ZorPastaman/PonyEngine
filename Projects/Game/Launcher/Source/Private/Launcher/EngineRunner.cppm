/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Debug/Log/LogMacro.h"

export module Launcher:EngineRunner;

import <iostream>;

import PonyEngine.Core;
import PonyEngine.Core.Factories;
import PonyEngine.Core.Implementation;
import PonyEngine.Debug.Log;

import Game;
import Game.Implementation;

import :EngineParamsProvider;
import :IPlatformEngineParamsProvider;

using LogType = PonyEngine::Debug::Log::LogType;

namespace Launcher
{
	/// @brief Engine runner.
	export class EngineRunner final
	{
	public:
		/// @brief Creates an @p EngineRunner.
		/// @param engineParamsProvider Platform-independent engine params provider.
		/// @param platformEngineParamsProvider Platform-dependent engine params provider.
		[[nodiscard("Pure constructor")]]
		EngineRunner(const EngineParamsProvider& engineParamsProvider, const IPlatformEngineParamsProvider& platformEngineParamsProvider);
		EngineRunner(const EngineRunner&) = delete;
		EngineRunner(EngineRunner&&) = delete;

		~EngineRunner() noexcept;

		EngineRunner& operator =(const EngineRunner&) = delete;
		EngineRunner& operator =(EngineRunner&&) = delete;

		/// @brief Ticks an engine.
		/// @param exitCode Engine exit code. It's set only if the function returns @a false.
		/// @return @a True if the engine is running; @a false otherwise.
		bool Tick(int& exitCode);

	private:
		PonyEngine::Core::IEngine* m_engine; /// @brief Run engine.
		Game::IGame* m_game; /// @brief Run game.
	};

	EngineRunner::EngineRunner(const EngineParamsProvider& engineParamsProvider, const IPlatformEngineParamsProvider& platformEngineParamsProvider)
	{
		PONY_CONSOLE(LogType::Info, "Create engine params.");
		PonyEngine::Core::EngineParams engineParams;

		PONY_CONSOLE(LogType::Info, "Set engine params.");
		engineParamsProvider.Modify(engineParams);
		PONY_CONSOLE(LogType::Info, "Engine params set.");

		PONY_CONSOLE(LogType::Info, "Set platform engine params.");
		platformEngineParamsProvider.Modify(engineParams);
		PONY_CONSOLE(LogType::Info, "Platform engine params set.");
		PONY_CONSOLE(LogType::Info, "Engine params created.");

		PONY_CONSOLE(LogType::Info, "Create an engine.");
		m_engine = PonyEngine::Core::CreateEngine(engineParams);
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Engine created");
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Create a game");
		m_game = Game::CreateGame(*m_engine);
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Game created");

		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Begin a game");
		m_game->Begin();
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Game begun");
	}

	EngineRunner::~EngineRunner() noexcept
	{
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Try to stop an engine");
		m_engine->Stop();
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Engine stopped");

		PONY_LOG(m_engine->GetLogger(), LogType::Info, "End a game");
		try
		{
			m_game->End();
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(m_engine->GetLogger(), e, "On ending a game");
		}
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Game ended");

		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Destroy a game");
		Game::DestroyGame(m_game);
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Game destroyed");
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Destroy an engine");
		PonyEngine::Core::DestroyEngine(m_engine);
		PONY_CONSOLE(LogType::Info, "Engine destroyed.");
	}

	bool EngineRunner::Tick(int& exitCode)
	{
		PONY_LOG(m_engine->GetLogger(), LogType::Verbose, "Pre-tick a game");
		m_game->PreTick();
		PONY_LOG(m_engine->GetLogger(), LogType::Verbose, "Tick an engine");
		m_engine->Tick();
		PONY_LOG(m_engine->GetLogger(), LogType::Verbose, "Post-tick a game");
		m_game->PostTick();

		const bool isRunning = m_engine->IsRunning();
		
		if (!isRunning) [[unlikely]]
		{
			exitCode = m_engine->GetExitCode();
		}

		return isRunning;
	}
}
