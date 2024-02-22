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

		PonyEngine::Input::IInputSystem* const m_inputSystem;
	};

	GameRunner::GameRunner(PonyEngine::Core::IEngine& engine) :
		m_engine{engine},
		m_inputSystem{PonyEngine::Input::CreateInputSystem()}
	{
	}

	GameRunner::~GameRunner() noexcept
	{
		PonyEngine::Input::DestroyInputSystem(m_inputSystem);
	}

	void GameRunner::Begin()
	{
		m_engine.GetLogger().Log(LogType::Info, "Begin");

		m_engine.GetSystemManager().AddSystem(m_inputSystem);
	}

	void GameRunner::PreTick()
	{
		m_engine.GetLogger().Log(LogType::Info, std::format("Frame Count Before Tick: {}", m_engine.GetFrameCount()));
	}

	void GameRunner::PostTick()
	{
		m_engine.GetLogger().Log(LogType::Info, std::format("Frame Count After Tick: {}", m_engine.GetFrameCount()));
	}

	void GameRunner::End()
	{
		m_engine.GetLogger().Log(LogType::Info, "End");

		m_engine.GetSystemManager().RemoveSystem(m_inputSystem);
	}
}
