/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Input.Implementation:InputSystem;

import <format>;
import <functional>;
import <queue>;
import <string>;
import <unordered_map>;
import <utility>;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Input;

export namespace PonyEngine::Input
{
	/// @brief Input system.
	class InputSystem final : public Core::ISystem, public Core::ITickableSystem, public IInputSystem, public IKeyboardObserver
	{
	public:
		/// @brief Creates an input system
		/// @param engine Engine.
		[[nodiscard("Pure constructor")]]
		explicit InputSystem(Core::IEngine& engine) noexcept;
		InputSystem(const InputSystem&) = delete;
		InputSystem(InputSystem&&) = delete;

		~InputSystem() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual Handle RegisterAction(const Event& event, const std::function<void()>& action) override;
		virtual void UnregisterAction(Handle handle) override;

		virtual void Observe(const KeyboardMessage& keyboardMessage) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		InputSystem& operator =(const InputSystem&) = delete;
		InputSystem& operator =(InputSystem&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Input::InputSystem"; ///< Class name.

	private:
		std::size_t currentId; ///< ID that will be given to a new event. It's incremented every time.

		std::unordered_map<KeyboardKeyCode, bool> keyStates; ///< Current key states.
		std::queue<KeyboardMessage> queue; ///< Message queue.

		Core::IEngine* engine; ///< Engine.

		std::unordered_map<Handle, std::pair<Event, std::function<void()>>, HandleHash> events; ///< Input event action map.
	};
}

namespace PonyEngine::Input
{
	InputSystem::InputSystem(Core::IEngine& engine) noexcept :
		currentId{1},
		engine{&engine}
	{
	}

	void InputSystem::Begin()
	{
		if (IKeyboardProvider* const keyboardProvider = engine->SystemManager().FindSystem<IKeyboardProvider>()) [[likely]]
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Subscribe to '{}' keyboard provider.", keyboardProvider->Name());
			keyboardProvider->AddKeyboardObserver(*this);
		}
		else [[unlikely]]
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Warning, "Couldn't find keyboard provider, keyboard input won't work.");
		}
	}

	void InputSystem::End()
	{
		if (IKeyboardProvider* const keyboardProvider = engine->SystemManager().FindSystem<IKeyboardProvider>()) [[likely]]
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Unsubscribe to '{}' keyboard provider.", keyboardProvider->Name());
			keyboardProvider->RemoveKeyboardObserver(*this);
		}
	}

	void InputSystem::Tick()
	{
		while (!queue.empty())
		{
			const KeyboardMessage message = queue.front();
			queue.pop();
			
			for (const auto& [handle, eventPair] : events)
			{
				if (eventPair.first.expectedMessage == message)
				{
					PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Tick an action. ID: '{}'.", handle.id);
					eventPair.second();
				}
			}
		}
	}

	Handle InputSystem::RegisterAction(const Event& event, const std::function<void()>& action)
	{
		const auto handle = Handle{.id = currentId++};
		const std::pair<Event, std::function<void()>> eventAction(event, action);
		events.insert(std::pair(handle, eventAction));
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Action registered. ExpectedMessage: '{}', ID: '{}'.", event.expectedMessage.ToString(), handle.id);

		return handle;
	}

	void InputSystem::UnregisterAction(const Handle handle)
	{
		events.erase(handle);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Action unregistered. ID: '{}'.", handle.id);
	}

	void InputSystem::Observe(const KeyboardMessage& keyboardMessage) noexcept
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Received keyboard message: '{}'.", keyboardMessage.ToString());

		if (const auto pair = keyStates.find(keyboardMessage.keyCode); pair != keyStates.cend() && pair->second == keyboardMessage.isDown)
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Ignore keyboard message 'cause it doesn't change state.");

			return;
		}

		keyStates.insert_or_assign(keyboardMessage.keyCode, keyboardMessage.isDown);
		queue.push(KeyboardMessage{.keyCode = keyboardMessage.keyCode, .isDown = keyboardMessage.isDown});
	}

	const char* InputSystem::Name() const noexcept
	{
		return StaticName;
	}
}
