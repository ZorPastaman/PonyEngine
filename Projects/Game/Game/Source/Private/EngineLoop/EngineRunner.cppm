/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module EngineRunner;

import PonyEngine.Core;
import PonyEngine.Core.Implementation;

import :EngineParams;
import :Game;

namespace Game
{
	export class EngineRunner final
	{
	public:
		EngineRunner();

		~EngineRunner() noexcept;

		inline bool IsRunning() const noexcept;
		inline int GetExitCode() const noexcept;

		void Tick();

	private:
		PonyEngine::Core::IEngine* const m_engine;
	};

	EngineRunner::EngineRunner() :
		m_engine{PonyEngine::Core::CreateEngine(GetEngineParams())}
	{
		Begin(*m_engine);
	}

	EngineRunner::~EngineRunner() noexcept
	{
		End(*m_engine);
		PonyEngine::Core::DestroyEngine(m_engine);
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
		PreTick(*m_engine);
		m_engine->Tick();
		PostTick(*m_engine);
	}
}
