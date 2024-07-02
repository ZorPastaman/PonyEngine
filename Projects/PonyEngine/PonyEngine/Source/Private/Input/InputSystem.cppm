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

export module PonyEngine.Input.Implementation:InputSystem;

import <format>;
import <functional>;
import <queue>;
import <unordered_map>;
import <utility>;

import PonyEngine.Core;
import PonyEngine.Input;
import PonyEngine.Log;
import PonyEngine.Window;

export namespace PonyEngine::Input
{
	/// @brief Default Pony Engine input system.
	class InputSystem final : public Core::ISystem, public IInputSystem, public Window::IKeyboardObserver
	{
	public:
		/// @brief Creates an @p Input system
		/// @param engine Engine that owns the input system.
		[[nodiscard("Pure constructor")]]
		explicit InputSystem(Core::IEngine& engine) noexcept;
		InputSystem(const InputSystem&) = delete;
		InputSystem(InputSystem&&) = delete;

		~InputSystem() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Pure function")]]
		virtual bool IsTickable() const noexcept override;
		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual Handle RegisterAction(const Event& event, const std::function<void()>& action) override;
		virtual void UnregisterAction(Handle handle) override;

		virtual void Observe(const Window::KeyboardMessage& keyboardMessage) noexcept override;

		InputSystem& operator =(const InputSystem&) = delete;
		InputSystem& operator =(InputSystem&&) = delete;

		static const char* const Name;

	private:
		std::unordered_map<Handle, std::pair<Event, std::function<void()>>> events; ///< Input event action map.
		std::size_t currentId; ///< ID that will be given to a new event. It's incremented every time.
		std::queue<KeyboardMessage> queue; ///< Message queue.

		const Core::IEngine& engine; ///< Engine that owns the input system.
	};
}

namespace PonyEngine::Input
{
	InputSystem::InputSystem(Core::IEngine& engine) noexcept :
		currentId{1},
		engine{engine}
	{
	}

	const char* InputSystem::GetName() const noexcept
	{
		return Name;
	}

	void InputSystem::Begin()
	{
		PONY_LOG(engine, Log::LogType::Info, "Try to subscribe to keyboard messages.");

		if (Window::IWindow* window = engine.FindSystem<Window::IWindow>())
		{
			PONY_LOG(engine, Log::LogType::Info, "Subscribe to keyboard messages.");
			window->AddKeyboardMessageObserver(this);
		}
		else
		{
			PONY_LOG(engine, Log::LogType::Warning, "Couldn't find a window, the input system won't work.");
		}
	}

	void InputSystem::End()
	{
		if (Window::IWindow* window = engine.FindSystem<Window::IWindow>())
		{
			PONY_LOG(engine, Log::LogType::Info, "Unsubscribe to keyboard messages.");
			window->RemoveKeyboardMessageObserver(this);
		}
	}

	bool InputSystem::IsTickable() const noexcept
	{
		return true;
	}

	void InputSystem::Tick()
	{
		while (!queue.empty())
		{
			const KeyboardMessage message = queue.front();
			queue.pop();
			
			for (const auto& [handle, eventPair] : events)
			{
				if (const KeyboardMessage expectedMessage = eventPair.first.GetExpectedMessage(); expectedMessage == message)
				{
					PONY_LOG(engine, Log::LogType::Verbose, std::format("Tick an action. ID: '{}'.", handle.GetId()).c_str());
					eventPair.second();
				}
			}
		}
	}

	Handle InputSystem::RegisterAction(const Event& event, const std::function<void()>& action)
	{
		const Handle handle(currentId++);
		PONY_LOG(engine, Log::LogType::Info, std::format("Register an action. ExpectedMessage: '{}', ID: '{}'.", event.GetExpectedMessage().ToString(), handle.GetId()).c_str());
		const std::pair<Event, std::function<void()>> eventAction(event, action);
		events.insert(std::pair(handle, eventAction));

		return handle;
	}

	void InputSystem::UnregisterAction(const Handle handle)
	{
		PONY_LOG(engine, Log::LogType::Info, std::format("Unregister an action. ID: '{}'.", handle.GetId()).c_str());
		events.erase(handle);
	}

	void InputSystem::Observe(const Window::KeyboardMessage& keyboardMessage) noexcept
	{
		PONY_LOG(engine, Log::LogType::Verbose, std::format("Received an keyboard message: '{}'.", keyboardMessage.ToString()).c_str());
		queue.push(KeyboardMessage(static_cast<KeyboardKeyCode>(keyboardMessage.GetKeyCode()), keyboardMessage.GetIsDown()));
	}

	const char* const InputSystem::Name = "PonyEngine::Input::InputSystem";
}
