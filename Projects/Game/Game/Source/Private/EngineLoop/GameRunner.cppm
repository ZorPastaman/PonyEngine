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
import PonyEngine.Input.Implementation;

namespace Game
{
	export class GameRunner final
	{
	public:
		GameRunner(PonyEngine::Core::IEngine& engine);

		~GameRunner();

		void Begin();
		void PreTick();
		void PostTick();
		void End();

	private:
		PonyEngine::Core::IEngine& m_engine;

		PonyEngine::Input::IInputSystem* m_inputSystem;
	};

	GameRunner::GameRunner(PonyEngine::Core::IEngine& engine) :
		m_engine{engine},
		m_inputSystem{PonyEngine::Input::CreateInputSystem()}
	{
	}

	GameRunner::~GameRunner()
	{
		PonyEngine::Input::DestroyInputSystem(m_inputSystem);
	}

	void GameRunner::Begin()
	{
		// Called before first tick

		m_engine.GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, "Begin");

		m_engine.GetSystemManager().AddSystem(*m_inputSystem);
	}

	void GameRunner::PreTick()
	{
		// Called before every tick

		m_engine.GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, std::format("Frame Count Before Tick: {}", m_engine.GetFrameCount()));
	}

	void GameRunner::PostTick()
	{
		// Called after every tick

		m_engine.GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, std::format("Frame Count After Tick: {}", m_engine.GetFrameCount()));
	}

	void GameRunner::End()
	{
		// Called after last tick

		m_engine.GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, "End");

		m_engine.GetSystemManager().RemoveSystem(*m_inputSystem);
	}
}
