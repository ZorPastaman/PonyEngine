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
	class GameSystem final : public PonyEngine::Core::ISystem, public IGameSystem
	{
	public:
		/// @brief Creates a game system.
		/// @param engine Engine that owns the system.
		[[nodiscard("Pure constructor")]]
		explicit GameSystem(PonyEngine::Core::IEngine& engine);
		GameSystem(const GameSystem&) = delete;
		GameSystem(GameSystem&&) = delete;

		~GameSystem() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;
		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		GameSystem& operator =(const GameSystem&) = delete;
		GameSystem& operator =(GameSystem&&) = delete;

		static constexpr const char* StaticName = "Game::GameSystem"; ///< Class name.

	private:
		PonyEngine::Core::IEngine* const engine; ///< Engine.

		PonyEngine::Input::Handle upHandle; ///< Up arrow input handle.
		PonyEngine::Input::Handle downHandle; ///< Down arrow input handle.
		PonyEngine::Input::Handle rightHandle; ///< Right arrow input handle.
		PonyEngine::Input::Handle leftHandle; ///< Left arrow input handle.
	};
}

namespace Game
{
	GameSystem::GameSystem(PonyEngine::Core::IEngine& engine) :
		engine{&engine},
		upHandle(0),
		downHandle(0),
		rightHandle(0),
		leftHandle(0)
	{
	}

	void GameSystem::Begin()
	{
		PONY_LOG(engine, PonyEngine::Log::LogType::Info, "Register inputs.");

		if (const auto inputSystem = engine->GetSystemManager().FindSystem<PonyEngine::Input::IInputSystem>())
		{
			PONY_LOG(engine, PonyEngine::Log::LogType::Debug, "Register up input.");
			const PonyEngine::Input::KeyboardMessage upMessage(PonyEngine::Input::KeyboardKeyCode::ArrowUp, true);
			const PonyEngine::Input::Event upEvent(upMessage);
			upHandle = inputSystem->RegisterAction(upEvent, std::bind([&]()
			{
				if (PonyEngine::Window::IWindow* const window = engine->GetSystemManager().FindSystem<PonyEngine::Window::IWindow>())
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
				if (PonyEngine::Window::IWindow* const window = engine->GetSystemManager().FindSystem<PonyEngine::Window::IWindow>())
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
				if (PonyEngine::Window::IWindow* const window = engine->GetSystemManager().FindSystem<PonyEngine::Window::IWindow>())
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
				if (PonyEngine::Window::IWindow* const window = engine->GetSystemManager().FindSystem<PonyEngine::Window::IWindow>())
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

	void GameSystem::End()
	{
		PONY_LOG(engine, PonyEngine::Log::LogType::Info, "Unregister inputs.");

		if (const auto inputSystem = engine->GetSystemManager().FindSystem<PonyEngine::Input::IInputSystem>())
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

	void GameSystem::Tick()
	{
		PONY_LOG(engine, PonyEngine::Log::LogType::Verbose, "Game tick.");
	}

	const char* GameSystem::GetName() const noexcept
	{
		return StaticName;
	}
}
