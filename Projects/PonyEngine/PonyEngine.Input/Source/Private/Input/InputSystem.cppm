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

export module PonyEngine.Input.Implementation:InputSystem;

import <format>;
import <functional>;
import <queue>;
import <string>;
import <unordered_map>;
import <utility>;

import PonyEngine.Core;
import PonyEngine.Input;
import PonyEngine.Log;

export namespace PonyEngine::Input
{
	/// @brief Input system.
	class InputSystem final : public Core::ISystem, public IInputSystem, public IKeyboardObserver
	{
	public:
		/// @brief Creates an @p Input system
		/// @param engine Engine that owns the input system.
		[[nodiscard("Pure constructor")]]
		explicit InputSystem(const Core::IEngine& engine) noexcept;
		InputSystem(const InputSystem&) = delete;
		InputSystem(InputSystem&&) = delete;

		~InputSystem() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::ObjectInterfaces PublicInterfaces() noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsTickable() const noexcept override;

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
		std::unordered_map<Handle, std::pair<Event, std::function<void()>>, HandleHash> events; ///< Input event action map.
		std::size_t currentId; ///< ID that will be given to a new event. It's incremented every time.
		std::queue<KeyboardMessage> queue; ///< Message queue.
		std::unordered_map<KeyboardKeyCode, bool> keyStates;

		const Core::IEngine* const engine; ///< Engine that owns the input system.
	};
}

namespace PonyEngine::Input
{
	InputSystem::InputSystem(const Core::IEngine& engine) noexcept :
		currentId{1},
		engine{&engine}
	{
	}

	Core::ObjectInterfaces InputSystem::PublicInterfaces() noexcept
	{
		auto interfaces = Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IInputSystem>(*this);

		return interfaces;
	}

	bool InputSystem::IsTickable() const noexcept
	{
		return true;
	}

	void InputSystem::Begin()
	{
		if (IKeyboardProvider* const keyboardProvider = engine->SystemManager().FindSystem<IKeyboardProvider>())
		{
			PONY_LOG(engine, Log::LogType::Info, "Subscribe to '{}' keyboard provider.", keyboardProvider->Name());
			keyboardProvider->AddKeyboardObserver(this);
			PONY_LOG(engine, Log::LogType::Info, "Subscribed to keyboard provider.");
		}
		else
		{
			PONY_LOG(engine, Log::LogType::Warning, "Couldn't find a keyboard provider, the keyboard input won't work.");
		}
	}

	void InputSystem::End()
	{
		if (IKeyboardProvider* const keyboardProvider = engine->SystemManager().FindSystem<IKeyboardProvider>())
		{
			PONY_LOG(engine, Log::LogType::Info, "Unsubscribe to '{}' keyboard provider.", keyboardProvider->Name());
			keyboardProvider->RemoveKeyboardObserver(this);
			PONY_LOG(engine, Log::LogType::Info, "Unsubscribed to keyboard provider.");
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
					PONY_LOG(engine, Log::LogType::Verbose, "Tick an action. ID: '{}'.", handle.id);
					eventPair.second();
				}
			}
		}
	}

	Handle InputSystem::RegisterAction(const Event& event, const std::function<void()>& action)
	{
		const auto handle = Handle{.id = currentId++};
		PONY_LOG(engine, Log::LogType::Info, "Register action. ExpectedMessage: '{}', ID: '{}'.", event.expectedMessage.ToString(), handle.id);
		const std::pair<Event, std::function<void()>> eventAction(event, action);
		events.insert(std::pair(handle, eventAction));
		PONY_LOG(engine, Log::LogType::Info, "Action registered.");

		return handle;
	}

	void InputSystem::UnregisterAction(const Handle handle)
	{
		PONY_LOG(engine, Log::LogType::Info, "Unregister action. ID: '{}'.", handle.id);
		events.erase(handle);
		PONY_LOG(engine, Log::LogType::Info, "Action unregistered.");
	}

	void InputSystem::Observe(const KeyboardMessage& keyboardMessage) noexcept
	{
		PONY_LOG(engine, Log::LogType::Verbose, "Received a keyboard message: '{}'.", keyboardMessage.ToString());

		if (const auto pair = keyStates.find(keyboardMessage.keyCode); pair != keyStates.cend() && pair->second == keyboardMessage.isDown)
		{
			PONY_LOG(engine, Log::LogType::Verbose, "Ignore the keyboard message 'cause it doesn't change the state.");

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
