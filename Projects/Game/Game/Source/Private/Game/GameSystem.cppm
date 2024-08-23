/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/EngineLog.h"

export module Game.Implementation:GameSystem;

import <functional>;

import PonyEngine.Core;
import PonyEngine.Input;
import PonyEngine.Log;
import PonyEngine.Window;

import Game;

export namespace Game
{
	/// @brief Game system.
	class GameSystem final : public PonyEngine::Core::ISystem, public PonyEngine::Core::ITickableSystem, public IGameSystem
	{
	public:
		/// @brief Creates a game system.
		/// @param engine Engine that owns the game system.
		[[nodiscard("Pure constructor")]]
		explicit GameSystem(PonyEngine::Core::IEngine& engine);
		GameSystem(const GameSystem&) = delete;
		GameSystem(GameSystem&&) = delete;

		~GameSystem() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		GameSystem& operator =(const GameSystem&) = delete;
		GameSystem& operator =(GameSystem&&) = delete;

		static constexpr auto StaticName = "Game::GameSystem"; ///< Class name.

	private:
		PonyEngine::Core::IEngine* const engine; ///< Engine.

		PonyEngine::Input::Handle upHandle; ///< Up arrow input handle.
		PonyEngine::Input::Handle downHandle; ///< Down arrow input handle.
		PonyEngine::Input::Handle rightHandle; ///< Right arrow input handle.
		PonyEngine::Input::Handle leftHandle; ///< Left arrow input handle.
		PonyEngine::Input::Handle closeHandle; ///< Escape input handle.
	};
}

namespace Game
{
	GameSystem::GameSystem(PonyEngine::Core::IEngine& engine) :
		engine{&engine},
		upHandle(0),
		downHandle(0),
		rightHandle(0),
		leftHandle(0),
		closeHandle(0)
	{
	}

	void GameSystem::Begin()
	{
		if (const auto inputSystem = engine->SystemManager().FindSystem<PonyEngine::Input::IInputSystem>())
		{
			PONY_LOG(engine, PonyEngine::Log::LogType::Info, "Register inputs.");

			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Register up input.");
			constexpr auto upMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::ArrowUp, .isDown = true};
			constexpr auto upEvent = PonyEngine::Input::Event{.expectedMessage = upMessage};
			upHandle = inputSystem->RegisterAction(upEvent, std::bind([&]
			{
				if (PonyEngine::Window::IWindow* const window = engine->SystemManager().FindSystem<PonyEngine::Window::IWindow>())
				{
					window->Title(L"Up");
				}
			}));
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Up input registered.");

			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Register down input.");
			constexpr auto downMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::ArrowDown, .isDown = true};
			constexpr auto downEvent = PonyEngine::Input::Event{.expectedMessage = downMessage};
			downHandle = inputSystem->RegisterAction(downEvent, std::bind([&]
			{
				if (PonyEngine::Window::IWindow* const window = engine->SystemManager().FindSystem<PonyEngine::Window::IWindow>())
				{
					window->Title(L"Down");
				}
			}));
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Down input registered.");

			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Register right input.");
			constexpr auto rightMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::ArrowRight, .isDown = true};
			constexpr auto rightEvent = PonyEngine::Input::Event{.expectedMessage = rightMessage};
			rightHandle = inputSystem->RegisterAction(rightEvent, std::bind([&]
			{
				if (PonyEngine::Window::IWindow* const window = engine->SystemManager().FindSystem<PonyEngine::Window::IWindow>())
				{
					window->Title(L"Right");
				}
			}));
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Right input registered.");

			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Register left input.");
			constexpr auto leftMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::ArrowLeft, .isDown = true};
			constexpr auto leftEvent = PonyEngine::Input::Event{.expectedMessage = leftMessage};
			leftHandle = inputSystem->RegisterAction(leftEvent, std::bind([&]
			{
				if (PonyEngine::Window::IWindow* const window = engine->SystemManager().FindSystem<PonyEngine::Window::IWindow>())
				{
					window->Title(L"Left");
				}
			}));
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Left input registered.");

			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Register close input.");
			constexpr auto escapeMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::Escape, .isDown = false};
			constexpr auto escapeEvent = PonyEngine::Input::Event{.expectedMessage = escapeMessage};
			closeHandle = inputSystem->RegisterAction(escapeEvent, std::bind([&]{engine->Stop();}));
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Close input registered.");

			PONY_LOG(engine, PonyEngine::Log::LogType::Info, "Inputs registered.");
		}
		else
		{
			PONY_LOG(engine, PonyEngine::Log::LogType::Warning, "No input system found.");
		}
	}

	void GameSystem::End()
	{
		if (PonyEngine::Input::IInputSystem* const inputSystem = engine->SystemManager().FindSystem<PonyEngine::Input::IInputSystem>())
		{
			PONY_LOG(engine, PonyEngine::Log::LogType::Info, "Unregister inputs.");

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
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Unregister close input.");
			inputSystem->UnregisterAction(closeHandle);
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Close input unregistered.");

			PONY_LOG(engine, PonyEngine::Log::LogType::Info, "Inputs unregistered.");
		}
	}

	void GameSystem::Tick()
	{
		PONY_LOG(engine, PonyEngine::Log::LogType::Verbose, "Game tick.");
	}

	const char* GameSystem::Name() const noexcept
	{
		return StaticName;
	}
}
