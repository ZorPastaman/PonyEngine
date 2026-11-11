/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.RawInput.Mouse.Impl:MouseController;

import std;

import PonyEngine.Math;
import PonyEngine.RawInput.Ext;
import PonyEngine.Utility;

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

		/// @brief Sets the input.
		/// @param pointers Pointer input.
		/// @param wheels Wheel input.
		/// @param buttons Button input.
		/// @param time Event time.
		void SetInput(std::span<const std::pair<MousePointer, float>> pointers, std::span<const std::pair<MouseWheel, float>> wheels,
			std::span<const std::pair<MouseButton, bool>> buttons, std::chrono::time_point<std::chrono::steady_clock> time);
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
		/// @brief Mouse button event.
		struct ButtonEvent final
		{
			MouseButton button; ///< Button axis.
			bool pressed; ///< Is the button pressed?
		};
		/// @brief Mouse wheel event.
		struct WheelEvent final
		{
			MouseWheel wheel; ///< Wheel axis.
			float delta; ///< Wheel delta.
		};
		/// @brief Mouse pointer event.
		struct PointerEvent final
		{
			MousePointer pointer; ///< Pointer axis.
			float delta; ///< Pointer delta.
		};
		/// @brief Mouse input event.
		struct InputEvent final : Event
		{
			std::array<PointerEvent, MousePointerCount> pointers;
			std::array<WheelEvent, MouseWheelCount> wheels;
			std::array<ButtonEvent, MouseButtonCount> buttons;
			std::uint8_t pointerCount = 0u;
			std::uint8_t wheelCount = 0u;
			std::uint8_t buttonCount = 0u;
		};
		/// @brief Mouse connection event.
		struct ConnectEvent final : Event
		{
			bool isConnected; ///< Is a device connected?
		};
		using MouseEvent = std::variant<InputEvent, ConnectEvent>; ///< Mouse event.

		const MouseAxisMap* axisMap; ///< Axis map.

		std::array<bool, MouseButtonCount> buttonState; ///< Button state.
		bool isConnected; ///< Is the mouse connected?

		std::queue<MouseEvent> events; ///< Event queue.

		static_assert(MousePointerCount <= std::numeric_limits<std::uint8_t>::max(), "Mouse pointer count is too great");
		static_assert(MouseWheelCount <= std::numeric_limits<std::uint8_t>::max(), "Mouse wheel count is too great");
		static_assert(MouseButtonCount <= std::numeric_limits<std::uint8_t>::max(), "Mouse button count is too great");
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

	void MouseController::SetInput(const std::span<const std::pair<MousePointer, float>> pointers, const std::span<const std::pair<MouseWheel, float>> wheels, 
		const std::span<const std::pair<MouseButton, bool>> buttons, const std::chrono::time_point<std::chrono::steady_clock> time)
	{
		assert(pointers.size() <= MousePointerCount && "Invalid pointer spans.");
		assert(wheels.size() <= MouseWheelCount && "Invalid wheel spans.");
		assert(buttons.size() <= MouseButtonCount && "Invalid button spans.");
		for (std::size_t i = 1uz; i < pointers.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				assert(pointers[i] != pointers[j] && "Pointer duplicate found.");
			}
		}
		for (std::size_t i = 1uz; i < wheels.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				assert(wheels[i] != wheels[j] && "Wheel duplicate found.");
			}
		}
		for (std::size_t i = 1uz; i < buttons.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				assert(buttons[i] != buttons[j] && "Button duplicate found.");
			}
		}

		auto event = InputEvent{ Event{ time } };
		for (const auto [type, delta] : pointers)
		{
			event.pointers[event.pointerCount] = PointerEvent{.pointer = type, .delta = delta};
			event.pointerCount += static_cast<bool>(delta);
		}
		for (const auto [type, delta] : wheels)
		{
			event.wheels[event.wheelCount] = WheelEvent{.wheel = type, .delta = delta};
			event.wheelCount += static_cast<bool>(delta);
		}
		for (const auto [type, pressed] : buttons)
		{
			event.buttons[event.buttonCount] = ButtonEvent{.button = type, .pressed = pressed};
			event.buttonCount += buttonState[static_cast<std::size_t>(type)] != pressed;
		}

		if (event.pointerCount > 0u || event.wheelCount > 0u || event.buttonCount > 0u)
		{
			events.push(event);
		}

		for (std::uint8_t i = 0uz; i < event.buttonCount; ++i)
		{
			const ButtonEvent buttonEvent = event.buttons[i];
			buttonState[static_cast<std::size_t>(buttonEvent.button)] = buttonEvent.pressed;
		}
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
			std::visit(Utility::Overload
			{
				[&](const InputEvent& input)
				{
					static constexpr std::size_t AxisCount = MousePointerCount + MouseWheelCount + MouseButtonCount;
					std::array<Axis, AxisCount> axes;
					std::array<float, AxisCount> values;
					std::array<InputType, AxisCount> types;
					std::size_t axisCount = 0uz;

					for (std::uint8_t i = 0u; i < input.pointerCount; ++i, ++axisCount)
					{
						const PointerEvent event = input.pointers[i];
						axes[axisCount] = axisMap->Axis(event.pointer);
						values[axisCount] = event.delta;
						types[axisCount] = InputType::Delta;
					}
					for (std::uint8_t i = 0u; i < input.wheelCount; ++i, ++axisCount)
					{
						const WheelEvent event = input.wheels[i];
						axes[axisCount] = axisMap->Axis(event.wheel);
						values[axisCount] = event.delta;
						types[axisCount] = InputType::Delta;
					}
					for (std::uint8_t i = 0u; i < input.buttonCount; ++i, ++axisCount)
					{
						const ButtonEvent event = input.buttons[i];
						axes[axisCount] = axisMap->Axis(event.button);
						values[axisCount] = event.pressed;
						types[axisCount] = InputType::State;
					}

					inputRegistry.AddInput(RawInputEvent
					{
						.axes = std::span<const Axis>(axes.data(), axisCount),
						.values = std::span<const float>(values.data(), axisCount),
						.inputTypes = std::span<const InputType>(types.data(), axisCount),
						.timePoint = input.time
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
