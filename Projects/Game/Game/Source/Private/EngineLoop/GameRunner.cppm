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

export module EngineRunner:GameRunner;

import <cstddef>;
import <format>;
import <functional>;
import <iostream>;
import <string>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Input;
import PonyEngine.Window;

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
		std::vector<std::size_t> m_inputEntries;

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
		PonyEngine::Input::IInputSystem* const inputSystem = PonyEngine::Core::FindSystem<PonyEngine::Input::IInputSystem>(m_engine.GetSystemManager());

		auto upEvent = PonyEngine::Input::Event(PonyEngine::Window::Messages::KeyboardMessage(PonyEngine::Window::Messages::KeyboardKeyCode::ArrowUp, true));
		std::function<void()> upAction = std::bind([&]() { m_engine.GetWindow()->SetTitle("Up"); });
		m_inputEntries.push_back(inputSystem->RegisterAction(upEvent, upAction));

		auto downEvent = PonyEngine::Input::Event(PonyEngine::Window::Messages::KeyboardMessage(PonyEngine::Window::Messages::KeyboardKeyCode::ArrowDown, true));
		std::function<void()> downAction = std::bind([&]() { m_engine.GetWindow()->SetTitle("Down"); });
		m_inputEntries.push_back(inputSystem->RegisterAction(downEvent, downAction));

		auto leftEvent = PonyEngine::Input::Event(PonyEngine::Window::Messages::KeyboardMessage(PonyEngine::Window::Messages::KeyboardKeyCode::ArrowLeft, true));
		std::function<void()> leftAction = std::bind([&]() { m_engine.GetWindow()->SetTitle("Left"); });
		m_inputEntries.push_back(inputSystem->RegisterAction(leftEvent, leftAction));

		auto rightEvent = PonyEngine::Input::Event(PonyEngine::Window::Messages::KeyboardMessage(PonyEngine::Window::Messages::KeyboardKeyCode::ArrowRight, true));
		std::function<void()> rightAction = std::bind([&]() { m_engine.GetWindow()->SetTitle("Right"); });
		m_inputEntries.push_back(inputSystem->RegisterAction(rightEvent, rightAction));
	}

	void GameRunner::PreTick()
	{
	}

	void GameRunner::PostTick()
	{
	}

	void GameRunner::End()
	{
		PonyEngine::Input::IInputSystem* const inputSystem = PonyEngine::Core::FindSystem<PonyEngine::Input::IInputSystem>(m_engine.GetSystemManager());

		for (const size_t id : m_inputEntries)
		{
			inputSystem->UnregisterAction(id);
		}
	}
}
