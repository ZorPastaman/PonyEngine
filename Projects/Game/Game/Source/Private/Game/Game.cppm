/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/LogMacro.h"

export module Game.Implementation:Game;

import <functional>;

import PonyEngine.Core;
import PonyEngine.Input;
import PonyEngine.Log;
import PonyEngine.Window;

import Game;

export namespace Game
{
	/// @brief Main game class.
	class Game final : public IGame
	{
	public:
		/// @brief Creates a game.
		/// @param engine Engine that owns the game.
		[[nodiscard("Pure constructor")]]
		explicit Game(PonyEngine::Core::IEngine& engine);
		Game(const Game&) = delete;
		Game(Game&&) = delete;

		~Game() noexcept = default;

		virtual void Begin() override;
		virtual void PreTick() override;
		virtual void PostTick() override;
		virtual void End() override;

		Game& operator =(const Game&) = delete;
		Game& operator =(Game&&) = delete;

	private:
		PonyEngine::Core::IEngine& engine; ///< Engine that owns the game.

		PonyEngine::Input::Handle upHandle;
		PonyEngine::Input::Handle downHandle;
		PonyEngine::Input::Handle rightHandle;
		PonyEngine::Input::Handle leftHandle;
	};
}

namespace Game
{
	Game::Game(PonyEngine::Core::IEngine& engine) :
		engine{engine},
		upHandle(0),
		downHandle(0),
		rightHandle(0),
		leftHandle(0)
	{
	}

	void Game::Begin()
	{
		PONY_LOG(engine, PonyEngine::Log::LogType::Info, "Register inputs.");

		if (const auto inputSystem = engine.GetSystemManager().FindSystem<PonyEngine::Input::IInputSystem>())
		{
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Register up input.");
			const PonyEngine::Input::KeyboardMessage upMessage(PonyEngine::Input::KeyboardKeyCode::ArrowUp, true);
			const PonyEngine::Input::Event upEvent(upMessage);
			upHandle = inputSystem->RegisterAction(upEvent, std::bind([&]() 
			{ 
				if (PonyEngine::Window::IWindow* const window = engine.GetSystemManager().FindSystem<PonyEngine::Window::IWindow>())
				{
					window->SetTitle(L"Up");
				}
			}));
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Up input registered.");

			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Register down input.");
			const PonyEngine::Input::KeyboardMessage downMessage(PonyEngine::Input::KeyboardKeyCode::ArrowDown, true);
			const PonyEngine::Input::Event downEvent(downMessage);
			downHandle = inputSystem->RegisterAction(downEvent, std::bind([&]()
			{
				if (PonyEngine::Window::IWindow* const window = engine.GetSystemManager().FindSystem<PonyEngine::Window::IWindow>())
				{
					window->SetTitle(L"Down");
				}
			}));
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Down input registered.");

			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Register right input.");
			const PonyEngine::Input::KeyboardMessage rightMessage(PonyEngine::Input::KeyboardKeyCode::ArrowRight, true);
			const PonyEngine::Input::Event rightEvent(rightMessage);
			rightHandle = inputSystem->RegisterAction(rightEvent, std::bind([&]()
			{
				if (PonyEngine::Window::IWindow* const window = engine.GetSystemManager().FindSystem<PonyEngine::Window::IWindow>())
				{
					window->SetTitle(L"Right");
				}
			}));
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Right input registered.");

			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Register left input.");
			const PonyEngine::Input::KeyboardMessage leftMessage(PonyEngine::Input::KeyboardKeyCode::ArrowLeft, true);
			const PonyEngine::Input::Event leftEvent(leftMessage);
			leftHandle = inputSystem->RegisterAction(leftEvent, std::bind([&]()
			{
				if (PonyEngine::Window::IWindow* const window = engine.GetSystemManager().FindSystem<PonyEngine::Window::IWindow>())
				{
					window->SetTitle(L"Left");
				}
			}));
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Left input registered.");
		}
		else
		{
			PONY_LOG(engine, PonyEngine::Log::LogType::Warning, "No input system found.");
		}

		PONY_LOG(engine, PonyEngine::Log::LogType::Info, "Inputs registered.");
	}

	void Game::PreTick()
	{
		PONY_LOG(engine, PonyEngine::Log::LogType::Verbose, "Game pre-tick.");
	}

	void Game::PostTick()
	{
		PONY_LOG(engine, PonyEngine::Log::LogType::Verbose, "Game post-tick.");
	}

	void Game::End()
	{
		PONY_LOG(engine, PonyEngine::Log::LogType::Info, "Unregister inputs.");

		if (const auto inputSystem = engine.GetSystemManager().FindSystem<PonyEngine::Input::IInputSystem>())
		{
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Unregister up input.");
			inputSystem->UnregisterAction(upHandle);
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Up input unregistered.");
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Unregister down input.");
			inputSystem->UnregisterAction(downHandle);
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Down input unregistered.");
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Unregister right input.");
			inputSystem->UnregisterAction(rightHandle);
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Right input unregistered.");
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Unregister left input.");
			inputSystem->UnregisterAction(leftHandle);
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Left input unregistered.");
		}

		PONY_LOG(engine, PonyEngine::Log::LogType::Info, "Inputs unregistered.");
	}
}
