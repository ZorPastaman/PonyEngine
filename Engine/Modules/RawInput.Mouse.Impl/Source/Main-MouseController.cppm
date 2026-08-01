/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Mouse.Impl:MouseController;

import std;

import PonyEngine.Math;
import PonyEngine.RawInput.Ext;
import PonyEngine.Type;

import :MouseAxis;
import :MouseAxisMap;

export namespace PonyEngine::RawInput::Mouse
{
	/// @brief Mouse controller.
	class MouseController final : private IDeviceController
	{
	public:
		/// @brief Creates a mouse controller.
		/// @param axisMap Axis map.
		/// @param isConnected Is the device connected?
		[[nodiscard("Pure constructor")]]
		MouseController(const MouseAxisMap& axisMap, bool isConnected) noexcept;
		MouseController(const MouseController&) = delete;
		[[nodiscard("Pure constructor")]]
		MouseController(MouseController&& other) noexcept = default;

		~MouseController() noexcept = default;

		/// @brief Sets the button input if it's different from the current state.
		/// @param button Button.
		/// @param pressed Is it pressed?
		/// @param time Event time.
		/// @param cursor Event cursor position.
		void SetButton(MouseButton button, bool pressed, 
			std::chrono::time_point<std::chrono::steady_clock> time, const std::optional<Math::Vector2<std::int32_t>>& cursor);
		/// @brief Adds the wheel input.
		/// @param wheel Wheel.
		/// @param delta Wheel delta.
		/// @param time Event time.
		/// @param cursor Event cursor position.
		void AddWheel(MouseWheel wheel, float delta, 
			std::chrono::time_point<std::chrono::steady_clock> time, const std::optional<Math::Vector2<std::int32_t>>& cursor);
		/// @brief Adds the pointer input.
		/// @param delta Pointer delta.
		/// @param time Event time.
		/// @param cursor Event cursor position.
		void AddPointer(const Math::Vector2<float>& delta, 
			std::chrono::time_point<std::chrono::steady_clock> time, const std::optional<Math::Vector2<std::int32_t>>& cursor);
		/// @brief Sets the connection if it's different from the current state.
		/// @param isConnected Is it connected?
		/// @param time Event time.
		void SetConnection(bool isConnected, std::chrono::time_point<std::chrono::steady_clock> time);

		/// @brief Gets the controller.
		/// @return Controller.
		[[nodiscard("Pure function")]]
		IDeviceController& Controller() noexcept;

		MouseController& operator =(const MouseController&) = delete;
		MouseController& operator =(MouseController&& other) noexcept = default;

	private:
		virtual void Tick(IInputRegistry& inputRegistry) override;

		/// @brief Basic mouse event.
		struct Event
		{
			std::chrono::time_point<std::chrono::steady_clock> time; ///< Event time.
		};
		/// @brief Mouse event with cursor position.
		struct CursorEvent : Event
		{
			std::optional<Math::Vector2<std::int32_t>> cursor; ///< Cursor position on the event.
		};
		/// @brief Mouse button event.
		struct ButtonEvent final : CursorEvent
		{
			bool pressed; ///< Is the button pressed?
			MouseButton button; ///< Button axis.
		};
		/// @brief Mouse wheel event.
		struct WheelEvent final : CursorEvent
		{
			float delta; ///< Wheel delta.
			MouseWheel wheel; ///< Wheel axis.
		};
		/// @brief Mouse pointer event.
		struct PointerEvent final : CursorEvent
		{
			Math::Vector2<float> delta; ///< Pointer delta.
		};
		/// @brief Mouse connection event.
		struct ConnectEvent final : Event
		{
			bool isConnected; ///< Is a device connected?
		};
		using MouseEvent = std::variant<ButtonEvent, WheelEvent, PointerEvent, ConnectEvent>; ///< Mouse event.

		const MouseAxisMap* axisMap; ///< Axis map.

		std::array<bool, MouseButtonCount> buttonState; ///< Button state.
		bool isConnected; ///< Is the mouse connected?

		std::queue<MouseEvent> events; ///< Event queue.
	};
}

namespace PonyEngine::RawInput::Mouse
{
	MouseController::MouseController(const MouseAxisMap& axisMap, const bool isConnected) noexcept :
		axisMap{&axisMap},
		isConnected{isConnected}
	{
		std::ranges::fill(buttonState, false);
	}

	void MouseController::SetButton(const MouseButton button, const bool pressed,
		const std::chrono::time_point<std::chrono::steady_clock> time, const std::optional<Math::Vector2<std::int32_t>>& cursor)
	{
		if (buttonState[static_cast<std::size_t>(button)] == pressed)
		{
			return;
		}

		events.push(ButtonEvent
		{
			CursorEvent{ Event{ time }, cursor }, pressed, button
		});

		buttonState[static_cast<std::size_t>(button)] = pressed;
	}

	void MouseController::AddWheel(const MouseWheel wheel, const float delta,
		const std::chrono::time_point<std::chrono::steady_clock> time, const std::optional<Math::Vector2<std::int32_t>>& cursor)
	{
		events.push(WheelEvent
		{
			CursorEvent { Event { time }, cursor }, delta, wheel
		});
	}

	void MouseController::AddPointer(const Math::Vector2<float>& delta,
		const std::chrono::time_point<std::chrono::steady_clock> time, const std::optional<Math::Vector2<std::int32_t>>& cursor)
	{
		events.push(PointerEvent
		{
			CursorEvent { Event { time }, cursor }, delta
		});
	}

	void MouseController::SetConnection(const bool isConnected, const std::chrono::time_point<std::chrono::steady_clock> time)
	{
		if (this->isConnected == isConnected)
		{
			return;
		}

		events.push(ConnectEvent
		{
			Event { time }, isConnected
		});

		this->isConnected = isConnected;
	}

	IDeviceController& MouseController::Controller() noexcept
	{
		return *this;
	}

	void MouseController::Tick(IInputRegistry& inputRegistry)
	{
		while (!events.empty())
		{
			std::visit(Type::Overload
			{
				[&](const ButtonEvent& button)
				{
					const Axis axis = axisMap->Axis(button.button);
					const float value = button.pressed;
					inputRegistry.AddInput(RawInputEvent
					{
						.axes = std::span(&axis, 1uz),
						.values = std::span(&value, 1uz),
						.eventType = InputEventType::State,
						.timePoint = button.time,
						.cursorPosition = button.cursor
					});
				},
				[&](const WheelEvent& wheel)
				{
					const Axis axis = axisMap->Axis(wheel.wheel);
					inputRegistry.AddInput(RawInputEvent
					{
						.axes = std::span(&axis, 1uz),
						.values = std::span(&wheel.delta, 1uz),
						.eventType = InputEventType::Delta,
						.timePoint = wheel.time,
						.cursorPosition = wheel.cursor
					});
				},
				[&](const PointerEvent& pointer)
				{
					inputRegistry.AddInput(RawInputEvent
					{
						.axes = axisMap->Pointers(),
						.values = pointer.delta.Span(),
						.eventType = InputEventType::Delta,
						.timePoint = pointer.time,
						.cursorPosition = pointer.cursor
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
