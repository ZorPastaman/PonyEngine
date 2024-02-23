/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module EngineRunner:GameRunner;

import <format>;
import <string>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Input;

using LogType = PonyEngine::Debug::Log::LogType;

namespace Game
{
	export class GameRunner final
	{
	public:
		[[nodiscard("Pure constructor")]]
		GameRunner(PonyEngine::Core::IEngine& engine);

		~GameRunner() noexcept;

		void Begin();
		void PreTick();
		void PostTick();
		void End();

	private:
		PonyEngine::Core::IEngine& m_engine;
	};

	GameRunner::GameRunner(PonyEngine::Core::IEngine& engine) :
		m_engine{engine}
	{
	}

	GameRunner::~GameRunner() noexcept
	{
	}

	void GameRunner::Begin()
	{
	}

	void GameRunner::PreTick()
	{
	}

	void GameRunner::PostTick()
	{
	}

	void GameRunner::End()
	{
	}
}
