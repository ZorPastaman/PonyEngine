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

export module EngineRunner;

import <exception>;
import <iostream>;

import PonyEngine.Core;
import PonyEngine.Core.Implementation;
import PonyEngine.Debug.Log;

import :EngineParams;
import :GameRunner;

using LogType = PonyEngine::Debug::Log::LogType;

namespace Game
{
	export class EngineRunner final
	{
	public:
		[[nodiscard("Pure constructor")]]
		EngineRunner();

		~EngineRunner() noexcept;

		[[nodiscard("Pure function")]]
		inline bool IsRunning() const noexcept;
		[[nodiscard("Pure function")]]
		inline int GetExitCode() const noexcept;

		void Tick();

	private:
		PonyEngine::Core::IEngine* const m_engine;
		GameRunner* m_gameRunner;
	};

	EngineRunner::EngineRunner() :
		m_engine{PonyEngine::Core::CreateEngine(GetEngineParams())}
	{
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Create a game runner");
		m_gameRunner = new GameRunner(*m_engine);
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Game runner created");
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Begin a game runner");
		m_gameRunner->Begin();
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Game runner begun");
	}

	EngineRunner::~EngineRunner() noexcept
	{
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "End a game runner");
		try
		{
			m_gameRunner->End();
		}
		catch (const std::exception& e)
		{
			PONY_CEXC(e, "On the game runner end.");
		}
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Game runner ended");
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Destroy a game runner");
		delete m_gameRunner;
		PONY_LOG(m_engine->GetLogger(), LogType::Info, "Game runner destroyed");

		PONY_COUT("Destroy an engine.");
		PonyEngine::Core::DestroyEngine(m_engine);
		PONY_COUT("Engine destroyed");
	}

	inline bool EngineRunner::IsRunning() const noexcept
	{
		return m_engine->IsRunning();
	}

	inline int EngineRunner::GetExitCode() const noexcept
	{
		return m_engine->GetExitCode();
	}

	void EngineRunner::Tick()
	{
		PONY_LOG(m_engine->GetLogger(), LogType::Verbose, "Pre tick a game runner");
		m_gameRunner->PreTick();
		PONY_LOG(m_engine->GetLogger(), LogType::Verbose, "Tick an engine");
		m_engine->Tick();
		PONY_LOG(m_engine->GetLogger(), LogType::Verbose, "Post tick a game runner");
		m_gameRunner->PostTick();
	}
}
