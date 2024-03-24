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

export module Game.Implementation:Game;

import <functional>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Input;
import PonyEngine.Window;

import Game;

using LogType = PonyEngine::Debug::Log::LogType;

namespace Game
{
	/// @brief Main game class.
	export class Game final : public IGame
	{
	public:
		/// @brief Creates a game.
		/// @param engine Engine that owns the game.
		[[nodiscard("Pure constructor")]]
		Game(PonyEngine::Core::IEngine& engine);
		Game(const Game&) = delete;
		Game(Game&&) = delete;

		virtual ~Game() noexcept = default;

		virtual void Begin() override;
		virtual void PreTick() override;
		virtual void PostTick() override;
		virtual void End() override;

		Game& operator =(const Game&) = delete;
		Game& operator =(Game&&) = delete;

	private:
		PonyEngine::Core::IEngine& m_engine; /// @brief Engine that owns the game.

		PonyEngine::Input::Handle m_upHandle;
		PonyEngine::Input::Handle m_downHandle;
		PonyEngine::Input::Handle m_rightHandle;
		PonyEngine::Input::Handle m_leftHandle;
	};

	Game::Game(PonyEngine::Core::IEngine& engine) :
		m_engine{engine},
		m_upHandle(0),
		m_downHandle(0),
		m_rightHandle(0),
		m_leftHandle(0)
	{
	}

	void Game::Begin()
	{
		PONY_LOG(m_engine, LogType::Info, "Register inputs.");

		if (auto const inputSystem = m_engine.FindSystem<PonyEngine::Input::IInputSystem>())
		{
			PONY_LOG(m_engine, LogType::Debug, "Register up input.");
			const PonyEngine::Input::KeyboardMessage upMessage(PonyEngine::Input::KeyboardKeyCode::ArrowUp, true);
			const PonyEngine::Input::Event upEvent(upMessage);
			m_upHandle = inputSystem->RegisterAction(upEvent, std::bind([&]() 
			{ 
				if (PonyEngine::Window::IWindow* const window = m_engine.GetWindow())
				{
					m_engine.GetWindow()->SetTitle(L"Up");
				}
			}));
			PONY_LOG(m_engine, LogType::Debug, "Up input registered.");

			PONY_LOG(m_engine, LogType::Debug, "Register down input.");
			const PonyEngine::Input::KeyboardMessage downMessage(PonyEngine::Input::KeyboardKeyCode::ArrowDown, true);
			const PonyEngine::Input::Event downEvent(downMessage);
			m_downHandle = inputSystem->RegisterAction(downEvent, std::bind([&]()
			{
				if (PonyEngine::Window::IWindow* const window = m_engine.GetWindow())
				{
					m_engine.GetWindow()->SetTitle(L"Down");
				}
			}));
			PONY_LOG(m_engine, LogType::Debug, "Down input registered.");

			PONY_LOG(m_engine, LogType::Debug, "Register right input.");
			const PonyEngine::Input::KeyboardMessage rightMessage(PonyEngine::Input::KeyboardKeyCode::ArrowRight, true);
			const PonyEngine::Input::Event rightEvent(rightMessage);
			m_rightHandle = inputSystem->RegisterAction(rightEvent, std::bind([&]()
			{
				if (PonyEngine::Window::IWindow* const window = m_engine.GetWindow())
				{
					m_engine.GetWindow()->SetTitle(L"Right");
				}
			}));
			PONY_LOG(m_engine, LogType::Debug, "Right input registered.");

			PONY_LOG(m_engine, LogType::Debug, "Register left input.");
			const PonyEngine::Input::KeyboardMessage leftMessage(PonyEngine::Input::KeyboardKeyCode::ArrowLeft, true);
			const PonyEngine::Input::Event leftEvent(leftMessage);
			m_leftHandle = inputSystem->RegisterAction(leftEvent, std::bind([&]()
			{
				if (PonyEngine::Window::IWindow* const window = m_engine.GetWindow())
				{
					m_engine.GetWindow()->SetTitle(L"Left");
				}
			}));
			PONY_LOG(m_engine, LogType::Debug, "Left input registered.");
		}
		else
		{
			PONY_LOG(m_engine, LogType::Warning, "No input system found.");
		}

		PONY_LOG(m_engine, LogType::Info, "Inputs registered.");
	}

	void Game::PreTick()
	{
		PONY_LOG(m_engine, LogType::Verbose, "Game pre-tick.");
	}

	void Game::PostTick()
	{
		PONY_LOG(m_engine, LogType::Verbose, "Game post-tick.");
	}

	void Game::End()
	{
		PONY_LOG(m_engine, LogType::Info, "Unregister inputs.");

		if (auto const inputSystem = m_engine.FindSystem<PonyEngine::Input::IInputSystem>())
		{
			PONY_LOG(m_engine, LogType::Debug, "Unregister up input.");
			inputSystem->UnregisterAction(m_upHandle);
			PONY_LOG(m_engine, LogType::Debug, "Up input unregistered.");
			PONY_LOG(m_engine, LogType::Debug, "Unregister down input.");
			inputSystem->UnregisterAction(m_downHandle);
			PONY_LOG(m_engine, LogType::Debug, "Down input unregistered.");
			PONY_LOG(m_engine, LogType::Debug, "Unregister right input.");
			inputSystem->UnregisterAction(m_rightHandle);
			PONY_LOG(m_engine, LogType::Debug, "Right input unregistered.");
			PONY_LOG(m_engine, LogType::Debug, "Unregister left input.");
			inputSystem->UnregisterAction(m_leftHandle);
			PONY_LOG(m_engine, LogType::Debug, "Left input unregistered.");
		}

		PONY_LOG(m_engine, LogType::Info, "Inputs unregistered.");
	}
}
