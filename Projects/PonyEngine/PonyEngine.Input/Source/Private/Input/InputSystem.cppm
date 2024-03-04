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

export module PonyEngine.Input.Implementation:InputSystem;

import <format>;
import <functional>;
import <queue>;
import <utility>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Input;
import PonyEngine.Window;

namespace PonyEngine::Input
{
	/// @brief Default Pony Engine input system.
	export class InputSystem final : public IInputSystem, public Window::Listeners::IKeyboardListener
	{
	public:
		/// @brief Creates an @p Input system
		/// @param engine Engine that owns the input system.
		[[nodiscard("Pure constructor")]]
		InputSystem(Core::IEngine& engine) noexcept;
		InputSystem(const InputSystem&) = delete;
		InputSystem(InputSystem&&) = delete;

		virtual ~InputSystem() noexcept = default;

		[[nodiscard("Pure function")]]
		inline virtual const char* GetName() const noexcept override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		virtual std::size_t RegisterAction(Event event, std::function<void()> action) override;
		virtual void UnregisterAction(std::size_t id) override;

		virtual void Listen(Window::Messages::KeyboardMessage keyboardMessage) noexcept override;

	private:
		std::vector<std::pair<std::size_t, std::pair<Event, std::function<void()>>>> m_events; /// @brief Input event action map.
		std::size_t m_currentId; /// @brief Id that will be given to a new event. It's incremented every time.
		std::queue<Window::Messages::KeyboardMessage> m_queue; /// @brief Message queue.

		Core::IEngine& m_engine; /// @brief Engine that owns the input system.
	};

	InputSystem::InputSystem(Core::IEngine& engine) noexcept :
		m_engine{engine},
		m_events{},
		m_currentId{0},
		m_queue{}
	{
	}

	inline const char* InputSystem::GetName() const noexcept
	{
		return "PonyEngine::Input::InputSystem";
	}

	void InputSystem::Begin()
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Try to subscribe to keyboard messages");

		if (Window::IWindow* window = m_engine.GetWindow())
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Subscribe to keyboard messages");
			window->AddKeyboardMessageListener(this);
		}
		else
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Warning, "Couldn't find a window, the input system won't work");
		}
	}

	void InputSystem::End()
	{
		if (Window::IWindow* window = m_engine.GetWindow())
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Unsubscribe to keyboard messages");
			window->RemoveKeyboardMessageListener(this);
		}
	}

	void InputSystem::Tick()
	{
		while (!m_queue.empty())
		{
			Window::Messages::KeyboardMessage message = m_queue.front();
			m_queue.pop();
			
			for (std::vector<std::pair<std::size_t, std::pair<Event, std::function<void()>>>>::const_iterator entry = m_events.cbegin(); entry != m_events.cend(); ++entry)
			{
				if (entry->second.first.expectedMessage.keyCode == message.keyCode && entry->second.first.expectedMessage.isDown == message.isDown)
				{
					PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, std::format("Tick an action. ID: '{}'", entry->first));
					entry->second.second();
				}
			}
		}
	}

	std::size_t InputSystem::RegisterAction(Event event, std::function<void()> action)
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, std::format("Register an action. KeyCode: '{}'; IsDown: '{}'; ID: '{}'", PonyEngine::Window::Messages::ToString(event.expectedMessage.keyCode), event.expectedMessage.isDown, m_currentId));

		std::pair<Event, std::function<void()>> eventAction(event, action);
		std::pair<std::size_t, std::pair<Event, std::function<void()>>> entry(m_currentId, eventAction);
		m_events.push_back(entry);

		return m_currentId++;
	}

	void InputSystem::UnregisterAction(std::size_t id)
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, std::format("Unregister an action. ID: '{}'", id));

		for (std::vector<std::pair<std::size_t, std::pair<Event, std::function<void()>>>>::const_iterator entry = m_events.cbegin(); entry != m_events.cend(); ++entry)
		{
			if (entry->first == id)
			{
				m_events.erase(entry);
				break;
			}
		}
	}

	void InputSystem::Listen(Window::Messages::KeyboardMessage keyboardMessage) noexcept
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, std::format("Received an keyboard message. KeyCode: '{}'; IsDown: '{}'", PonyEngine::Window::Messages::ToString(keyboardMessage.keyCode), keyboardMessage.isDown));
		m_queue.push(keyboardMessage);
	}
}
