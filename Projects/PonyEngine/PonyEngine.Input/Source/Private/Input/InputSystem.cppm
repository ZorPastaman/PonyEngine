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
import <unordered_map>;
import <utility>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Input;
import PonyEngine.Window;

namespace PonyEngine::Input
{
	/// @brief Default Pony Engine input system.
	export class InputSystem final : public IInputSystem, public Window::IKeyboardObserver
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

		inline virtual bool IsTickable() const noexcept override;
		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual Handle RegisterAction(const Event& event, const std::function<void()>& action) override;
		virtual void UnregisterAction(Handle handle) override;

		virtual void Observe(const Window::KeyboardMessage& keyboardMessage) noexcept override;

		InputSystem& operator =(const InputSystem&) = delete;
		InputSystem& operator =(InputSystem&&) = delete;

		static const char* const Name;

	private:
		std::unordered_map<Handle, std::pair<Event, std::function<void()>>> m_events; /// @brief Input event action map.
		std::size_t m_currentId; /// @brief Id that will be given to a new event. It's incremented every time.
		std::queue<KeyboardMessage> m_queue; /// @brief Message queue.

		Core::IEngine& m_engine; /// @brief Engine that owns the input system.
	};

	InputSystem::InputSystem(Core::IEngine& engine) noexcept :
		m_engine{engine},
		m_events{},
		m_currentId{1},
		m_queue{}
	{
	}

	inline const char* InputSystem::GetName() const noexcept
	{
		return Name;
	}

	void InputSystem::Begin()
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Try to subscribe to keyboard messages.");

		if (Window::IWindow* window = m_engine.GetWindow())
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Info, "Subscribe to keyboard messages.");
			window->AddKeyboardMessageObserver(this);
		}
		else
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Warning, "Couldn't find a window, the input system won't work.");
		}
	}

	void InputSystem::End()
	{
		if (Window::IWindow* window = m_engine.GetWindow())
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Info, "Unsubscribe to keyboard messages.");
			window->RemoveKeyboardMessageObserver(this);
		}
	}

	inline bool InputSystem::IsTickable() const noexcept
	{
		return true;
	}

	void InputSystem::Tick()
	{
		while (!m_queue.empty())
		{
			const KeyboardMessage message = m_queue.front();
			m_queue.pop();
			
			for (const auto& [handle, eventPair] : m_events)
			{
				const KeyboardMessage expectedMessage = eventPair.first.GetExpectedMessage();

				if (expectedMessage == message)
				{
					PONY_LOG(m_engine, Debug::Log::LogType::Verbose, std::format("Tick an action. ID: '{}'.", handle.GetId()).c_str());
					eventPair.second();
				}
			}
		}
	}

	Handle InputSystem::RegisterAction(const Event& event, const std::function<void()>& action)
	{
		const Handle handle(m_currentId++);
		PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Register an action. ExpectedMessage: '{}', ID: '{}'.", event.GetExpectedMessage().ToString(), handle.GetId()).c_str());
		const std::pair<Event, std::function<void()>> eventAction(event, action);
		m_events.insert(std::pair(handle, eventAction));

		return handle;
	}

	void InputSystem::UnregisterAction(const Handle handle)
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Unregister an action. ID: '{}'.", handle.GetId()).c_str());
		m_events.erase(handle);
	}

	void InputSystem::Observe(const Window::KeyboardMessage& keyboardMessage) noexcept
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Verbose, std::format("Received an keyboard message: '{}'.", keyboardMessage.ToString()).c_str());
		m_queue.push(KeyboardMessage(static_cast<KeyboardKeyCode>(keyboardMessage.GetKeyCode()), keyboardMessage.GetIsDown()));
	}

	const char* const InputSystem::Name = "PonyEngine::Input::InputSystem";
}
