/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Keyboard.Impl:KeyboardController;

import std;

import PonyEngine.Math;
import PonyEngine.RawInput.Ext;
import PonyEngine.Utility;

export namespace PonyEngine::RawInput::Keyboard
{
	/// @brief Platform independent keyboard controller.
	class KeyboardController final : private IDeviceController
	{
	public:
		/// @brief Creates a keyboard controller.
		/// @param isConnected Is the keyboard connected?
		[[nodiscard("Pure constructor")]]
		explicit KeyboardController(bool isConnected) noexcept;
		KeyboardController(const KeyboardController&) = delete;
		[[nodiscard("Pure constructor")]]
		KeyboardController(KeyboardController&& other) noexcept = default;

		~KeyboardController() noexcept = default;

		/// @brief Sets the input.
		/// @param axis Input axis.
		/// @param pressed Is the key pressed?
		/// @param time Event time.
		/// @param cursor Cursor point on event creation.
		/// @remark The function does nothing if the event doesn't change the current state.
		void SetInput(Axis axis, bool pressed, std::chrono::time_point<std::chrono::steady_clock> time, const std::optional<Math::Vector2<std::int32_t>>& cursor);
		/// @brief Sets the connection status.
		/// @param isConnected Is the keyboard connected?
		/// @param time Event time.
		/// @remark The function does nothing if the event doesn't change the current state.
		void SetConnection(bool isConnected, std::chrono::time_point<std::chrono::steady_clock> time);

		/// @brief Gets the device controller.
		/// @return Device controller.
		[[nodiscard("Pure function")]]
		IDeviceController& Controller() noexcept;

		KeyboardController& operator =(const KeyboardController&) = delete;
		KeyboardController& operator =(KeyboardController&& other) noexcept = default;

	private:
		virtual void Tick(IInputRegistry& inputRegistry) override;

		/// @brief Base event.
		struct Event
		{
			std::chrono::time_point<std::chrono::steady_clock> time; ///< Event time.
		};
		/// @brief Input event.
		struct InputEvent final : Event
		{
			std::optional<Math::Vector2<std::int32_t>> cursor; ///< Cursor position on the event.
			Axis axis; ///< Axis.
			bool pressed; ///< Is the key pressed?
		};
		/// @brief Connect event.
		struct ConnectEvent final : Event
		{
			bool isConnected; ///< Is connected?
		};
		using KeyboardEvent = std::variant<InputEvent, ConnectEvent>; ///< Keyboard event.

		std::queue<KeyboardEvent> events; ///< Input events.

		std::vector<Axis> pressedKeys; ///< Currently pressed keys.
		bool isConnected; ///< Current connection state.
	};
}

namespace PonyEngine::RawInput::Keyboard
{
	KeyboardController::KeyboardController(const bool isConnected) noexcept : 
		isConnected{isConnected}
	{
	}

	void KeyboardController::SetInput(const Axis axis, const bool pressed, const std::chrono::time_point<std::chrono::steady_clock> time, 
		const std::optional<Math::Vector2<std::int32_t>>& cursor)
	{
		const auto pressedKeyPosition = std::ranges::find(pressedKeys, axis);
		if ((pressed && pressedKeyPosition != pressedKeys.cend()) || (!pressed && pressedKeyPosition == pressedKeys.cend()))
		{
			return;
		}

		events.push(InputEvent
		{
			Event{ time }, cursor, axis, pressed
		});

		if (pressed)
		{
			pressedKeys.push_back(axis);
		}
		else
		{
			pressedKeys.erase(pressedKeyPosition);
		}
	}

	void KeyboardController::SetConnection(const bool isConnected, const std::chrono::time_point<std::chrono::steady_clock> time)
	{
		if (this->isConnected == isConnected)
		{
			return;
		}

		events.push(ConnectEvent
		{
			Event{ time }, isConnected
		});

		this->isConnected = isConnected;
	}

	IDeviceController& KeyboardController::Controller() noexcept
	{
		return *this;
	}

	void KeyboardController::Tick(IInputRegistry& inputRegistry)
	{
		while (!events.empty())
		{
			std::visit(Utility::Overload
			{
				[&](const InputEvent& input)
				{
					const float value = input.pressed;
					inputRegistry.AddInput(RawInputEvent
					{
						.axes = std::span(&input.axis, 1uz),
						.values = std::span(&value, 1uz),
						.eventType = InputEventType::State,
						.timePoint = input.time,
						.cursorPosition = input.cursor
					});
				},
				[&](const ConnectEvent& connect)
				{
					inputRegistry.Connect(ConnectionEvent
					{
						.isConnected = connect.isConnected,
						.timePoint = connect.time
					});
				}
			}, events.front());
			events.pop();
		}
	}
}
