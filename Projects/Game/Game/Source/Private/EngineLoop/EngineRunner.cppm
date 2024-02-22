/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module EngineRunner;

import <exception>;
import <iostream>;

import PonyEngine.Core;
import PonyEngine.Core.Implementation;

import :EngineParams;
import :GameRunner;

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
		m_gameRunner = new GameRunner(*m_engine);
		m_gameRunner->Begin();
	}

	EngineRunner::~EngineRunner() noexcept
	{
		try
		{
			m_gameRunner->End();
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << " On the game runner end." << std::endl;
		}
		delete m_gameRunner;

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
		m_gameRunner->PreTick();
		m_engine->Tick();
		m_gameRunner->PostTick();
	}
}
