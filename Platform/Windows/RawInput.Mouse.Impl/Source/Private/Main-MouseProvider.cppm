/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

#include <hidusage.h>

export module PonyEngine.RawInput.Mouse.Impl.Windows:MouseProvider;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.RawInput.Ext;
import PonyEngine.RawInput.Mouse.Impl;
import PonyEngine.Platform.Windows;
import PonyEngine.Surface.Windows;
import PonyEngine.Type;

export namespace PonyEngine::RawInput::Windows
{
	/// @brief Mouse provider.
	class MouseProvider final : public IInputProvider, private Surface::Windows::IRawInputObserver, private Surface::ISurfaceObserver
	{
	public:
		/// @brief Creates a mouse provider.
		/// @param input Raw input context.
		[[nodiscard("Pure constructor")]]
		explicit MouseProvider(IRawInputContext& input);
		MouseProvider(const MouseProvider&) = delete;
		MouseProvider(MouseProvider&&) = delete;

		~MouseProvider() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;
		virtual void Tick() override;

		MouseProvider& operator =(const MouseProvider&) = delete;
		MouseProvider& operator =(MouseProvider&&) = delete;

	private:
		virtual void Observe(const RAWINPUT& rawInput) override;
		virtual void OnDeviceConnectionChanged(HANDLE device, bool isConnected) override;

		virtual void OnFocusChanged(bool isInFocus) override;

		/// @brief Resets the mouse input.
		/// @param mouseIndex Mouse index.
		/// @param eventTime Event time.
		/// @param cursorPosition Cursor position.
		void ResetInput(std::size_t mouseIndex, std::chrono::time_point<std::chrono::steady_clock> eventTime, const Math::Vector2<std::int32_t>& cursorPosition);

		/// @brief Subscribes to platform messages.
		void Subscribe();
		/// @brief Unsubscribes to platform messages.
		void Unsubscribe() noexcept;

		/// @brief Unregisters all the devices.
		void UnregisterDevices();
		/// @brief Clears all the data.
		void Clear() noexcept;

		/// @brief Gets or creates a mouse.
		/// @param mouseHandle Mouse native handle.
		/// @return Mouse index.
		[[nodiscard("Weird call")]]
		std::size_t GetOrCreateMouse(HANDLE mouseHandle);
		/// @brief Gets a mouse name.
		/// @param mouseHandle Mouse native handle.
		/// @return Mouse index.
		[[nodiscard("Pure function")]]
		std::string_view GetMouseName(HANDLE mouseHandle) const;

		/// @brief Updates button states.
		/// @param source Input source.
		/// @param mouseIndex Mouse index.
		void UpdateButtons(const RAWMOUSE& source, std::size_t mouseIndex);
		/// @brief Updates wheel states.
		/// @param source Input source.
		/// @param mouseIndex Mouse index.
		void UpdateWheels(const RAWMOUSE& source, std::size_t mouseIndex);
		/// @brief Updates pointer states.
		/// @param source Input source.
		/// @param mouseIndex Mouse index.
		void UpdatePointer(const RAWMOUSE& source, std::size_t mouseIndex);

		IRawInputContext* input; ///< Raw input context.
		Surface::Windows::ISurfaceService* surface; ///< Surface service.

		DeviceTypeId deviceType; ///< Mouse device type.
		MouseAxisMap axisMap; ///< Mouse axis map.

		MouseContainer<HANDLE> mouseContainer; ///< Mouse container.
		MouseEventQueue eventQueue; ///< Mouse event queue.

		mutable std::string deviceNameTemp; ///< Temporary device name.
	};
}

namespace PonyEngine::RawInput::Windows
{
	MouseProvider::MouseProvider(IRawInputContext& input) :
		input{&input},
		surface{&this->input->Application().GetService<Surface::Windows::ISurfaceService>()},
		deviceType(this->input->Hash(DeviceType(MouseDevice::GenericType))),
		axisMap(*this->input)
	{
	}

	void MouseProvider::Begin()
	{
		Subscribe();
	}

	void MouseProvider::End()
	{
		Unsubscribe();
		UnregisterDevices();
		Clear();
	}

	void MouseProvider::Tick()
	{
		for (std::size_t i = 0uz; i < eventQueue.Size(); ++i)
		{
			const DeviceHandle device = eventQueue.Device(i);
			const MouseEvent& event = eventQueue.Event(i);

			std::visit(Type::Overload
			{
				[&](const MouseButtonEvent& button)
				{
					const AxisId axis = axisMap.Axis(button.button);
					const float value = button.state;
					input->AddInput(device, RawInputEvent
					{
						.axes = std::span<const AxisId>(&axis, 1uz),
						.values = std::span<const float>(&value, 1uz),
						.eventType = InputEventType::State,
						.timePoint = event.timePoint,
						.cursorPosition = button.cursorPosition
					});
				},
				[&](const MouseWheelEvent& wheel)
				{
					const AxisId axis = axisMap.Axis(wheel.wheel);
					input->AddInput(device, RawInputEvent
					{
						.axes = std::span<const AxisId>(&axis, 1uz),
						.values = std::span<const float>(&wheel.delta, 1uz),
						.eventType = InputEventType::Delta,
						.timePoint = event.timePoint,
						.cursorPosition = wheel.cursorPosition
					});
				},
				[&](const MousePointerEvent& pointer)
				{
					input->AddInput(device, RawInputEvent
					{
						.axes = axisMap.Pointers(),
						.values = pointer.delta.Span(),
						.eventType = InputEventType::Delta,
						.timePoint = event.timePoint,
						.cursorPosition = pointer.cursorPosition
					});
				},
				[&](const MouseConnectionEvent& connection)
				{
					input->Connect(device, ConnectionEvent
					{
						.isConnected = connection.isConnected,
						.timePoint = event.timePoint
					});
				}
			}, event.event);
		}

		eventQueue.Clear();
	}

	void MouseProvider::Observe(const RAWINPUT& rawInput)
	{
#if !NDEBUG
		if (rawInput.header.dwType != RIM_TYPEMOUSE) [[unlikely]]
		{
			throw std::logic_error("Not mouse input");
		}
#endif

		const std::size_t index = GetOrCreateMouse(rawInput.header.hDevice);
		UpdateButtons(rawInput.data.mouse, index);
		UpdateWheels(rawInput.data.mouse, index);
		UpdatePointer(rawInput.data.mouse, index);
	}

	void MouseProvider::OnDeviceConnectionChanged(const HANDLE device, const bool isConnected)
	{
		const auto addConnectionEvent = [&](const std::size_t index)
		{
			if (mouseContainer.IsConnected(index) == isConnected)
			{
				return;
			}

			mouseContainer.Connect(index, isConnected);

			const auto connectionEvent = MouseConnectionEvent{.isConnected = isConnected};
			const auto event = MouseEvent{ .event = connectionEvent, .timePoint = surface->LastMessageTime() };
			const DeviceHandle deviceHandle = mouseContainer.DeviceHandle(index);
			eventQueue.Add(deviceHandle, event);

			PONY_LOG(input->Logger(), Log::LogType::Info, "Mouse device connection changed to '{}'. Handle: '0x{:X}'; Native handle: '0x{:X}'.",
				isConnected, deviceHandle.id, reinterpret_cast<std::uintptr_t>(device));
		};

		if (isConnected)
		{
			const std::string_view name = GetMouseName(device);
			const std::size_t index = mouseContainer.IndexOf(name);
			if (index < mouseContainer.Size())
			{
				mouseContainer.NativeHandle(index) = device;
				addConnectionEvent(index);
			}
		}
		else
		{
			const std::size_t index = mouseContainer.IndexOf(device);
			if (index < mouseContainer.Size())
			{
				ResetInput(index, surface->LastMessageTime(), surface->LastMessageCursorPosition());
				mouseContainer.NativeHandle(index) = INVALID_HANDLE_VALUE;
				addConnectionEvent(index);
			}
		}
	}

	void MouseProvider::OnFocusChanged(const bool isInFocus)
	{
		if (isInFocus)
		{
			return;
		}

		const std::chrono::time_point<std::chrono::steady_clock> time = surface->LastMessageTime();
		const Math::Vector2<std::int32_t> cursorPosition = surface->LastMessageCursorPosition();

		for (std::size_t i = 0uz; i < mouseContainer.Size(); ++i)
		{
			ResetInput(i, time, cursorPosition);
		}
	}

	void MouseProvider::ResetInput(const std::size_t mouseIndex, const std::chrono::time_point<std::chrono::steady_clock> eventTime,
		const Math::Vector2<std::int32_t>& cursorPosition)
	{
		const std::span<const bool, static_cast<std::size_t>(MouseButton::Count)> buttonStates = mouseContainer.ButtonStates(mouseIndex);

		for (std::size_t i = 0uz; i < buttonStates.size(); ++i)
		{
			if (!buttonStates[i])
			{
				continue;
			}

			const auto inputEvent = MouseButtonEvent
			{
				.button = static_cast<MouseButton>(i),
				.state = false,
				.cursorPosition = cursorPosition
			};
			const auto event = MouseEvent
			{
				.event = inputEvent,
				.timePoint = eventTime
			};
			eventQueue.Add(mouseContainer.DeviceHandle(mouseIndex), event);
		}

		mouseContainer.ResetButtons(mouseIndex);
	}

	void MouseProvider::Subscribe()
	{
		surface->AddObserver(*this);
		try
		{
			surface->AddRawInputObserver(*this, HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_MOUSE);
		}
		catch (...)
		{
			surface->RemoveObserver(*this);
			throw;
		}
	}

	void MouseProvider::Unsubscribe() noexcept
	{
		surface->RemoveRawInputObserver(*this, HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_MOUSE);
		surface->RemoveObserver(*this);
	}

	void MouseProvider::UnregisterDevices()
	{
		for (std::size_t i = 0uz; i < mouseContainer.Size(); ++i)
		{
			const DeviceHandle handle = mouseContainer.DeviceHandle(i);
			PONY_LOG(input->Logger(), Log::LogType::Info, "Unregistering mouse device. Handle: '0x{:X}'.", handle.id);
			input->UnregisterDevice(handle);
		}
	}

	void MouseProvider::Clear() noexcept
	{
		mouseContainer.Clear();
		eventQueue.Clear();
	}

	std::size_t MouseProvider::GetOrCreateMouse(const HANDLE mouseHandle)
	{
		if (const std::size_t index = mouseContainer.IndexOf(mouseHandle); index < mouseContainer.Size()) [[likely]]
		{
			return index;
		}

		PONY_LOG(input->Logger(), Log::LogType::Info, "Creating new mouse device... Native handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(mouseHandle));
		const std::string_view name = GetMouseName(mouseHandle);
		const DeviceHandle deviceHandle = input->RegisterDevice(deviceType, name, true);
		try
		{
			mouseContainer.Add(mouseHandle, deviceHandle, name, true);
		}
		catch (...)
		{
			input->UnregisterDevice(deviceHandle);
			throw;
		}
		PONY_LOG(input->Logger(), Log::LogType::Info, "Creating new mouse device done. Native handle: '0x{:X}'; Device handle: '0x{:X}'; Device name: '{}'.",
			reinterpret_cast<std::uintptr_t>(mouseHandle), deviceHandle.id, name);

		return mouseContainer.Size() - 1uz;
	}

	std::string_view MouseProvider::GetMouseName(const HANDLE mouseHandle) const
	{
		Platform::Windows::GetDeviceName(mouseHandle, deviceNameTemp);
		return deviceNameTemp;
	}

	void MouseProvider::UpdateButtons(const RAWMOUSE& source, const std::size_t mouseIndex)
	{
		const auto updateButton = [&](const MouseButton button, const bool pressed)
		{
			if (mouseContainer.IsPressed(mouseIndex, button) != pressed) [[likely]]
			{
				mouseContainer.Press(mouseIndex, button, pressed);

				const auto buttonEvent = MouseButtonEvent
				{
					.button = button,
					.state = pressed,
					.cursorPosition = surface->LastMessageCursorPosition()
				};
				const auto event = MouseEvent
				{
					.event = buttonEvent,
					.timePoint = surface->LastMessageTime()
				};
				eventQueue.Add(mouseContainer.DeviceHandle(mouseIndex), event);
			}
		};

		struct ButtonFlagMap final
		{
			USHORT downFlag;
			USHORT upFlag;
			MouseButton button;
		};

		constexpr auto buttonMap = std::array<ButtonFlagMap, 5>
		{
			ButtonFlagMap{.downFlag = RI_MOUSE_LEFT_BUTTON_DOWN, .upFlag = RI_MOUSE_LEFT_BUTTON_UP, .button = MouseButton::Left},
			ButtonFlagMap{.downFlag = RI_MOUSE_RIGHT_BUTTON_DOWN, .upFlag = RI_MOUSE_RIGHT_BUTTON_UP, .button = MouseButton::Right},
			ButtonFlagMap{.downFlag = RI_MOUSE_MIDDLE_BUTTON_DOWN, .upFlag = RI_MOUSE_MIDDLE_BUTTON_UP, .button = MouseButton::Middle},
			ButtonFlagMap{.downFlag = RI_MOUSE_BUTTON_4_DOWN, .upFlag = RI_MOUSE_BUTTON_4_UP, .button = MouseButton::X1},
			ButtonFlagMap{.downFlag = RI_MOUSE_BUTTON_5_DOWN, .upFlag = RI_MOUSE_BUTTON_5_UP, .button = MouseButton::X2}
		};

		for (const ButtonFlagMap& mapping : buttonMap)
		{
			if (source.usButtonFlags & mapping.downFlag)
			{
				updateButton(mapping.button, true);
			}
			if (source.usButtonFlags & mapping.upFlag)
			{
				updateButton(mapping.button, false);
			}
		}
	}

	void MouseProvider::UpdateWheels(const RAWMOUSE& source, const std::size_t mouseIndex)
	{
		const auto updateWheel = [&](const MouseWheel wheel, const USHORT value)
		{
			const auto wheelEvent = MouseWheelEvent
			{
				.wheel = wheel,
				.delta = static_cast<float>(std::bit_cast<SHORT>(value)) / WHEEL_DELTA,
				.cursorPosition = surface->LastMessageCursorPosition()
			};
			const auto event = MouseEvent
			{
				.event = wheelEvent,
				.timePoint = surface->LastMessageTime()
			};
			eventQueue.Add(mouseContainer.DeviceHandle(mouseIndex), event);
		};

		if (source.usButtonFlags & RI_MOUSE_WHEEL)
		{
			updateWheel(MouseWheel::Vertical, source.usButtonData);
		}
		if (source.usButtonFlags & RI_MOUSE_HWHEEL)
		{
			updateWheel(MouseWheel::Horizontal, source.usButtonData);
		}
	}

	void MouseProvider::UpdatePointer(const RAWMOUSE& source, const std::size_t mouseIndex)
	{
		if (source.usFlags != MOUSE_MOVE_RELATIVE) [[unlikely]]
		{
			return;
		}
		if (!source.lLastX && !source.lLastY)
		{
			return;
		}

		auto pointerEvent = MousePointerEvent
		{
			.delta = Math::Vector2<float>(static_cast<float>(source.lLastX), static_cast<float>(source.lLastY)),
			.cursorPosition = surface->LastMessageCursorPosition()
		};
		const auto event = MouseEvent
		{
			.event = pointerEvent,
			.timePoint = surface->LastMessageTime()
		};
		eventQueue.Add(mouseContainer.DeviceHandle(mouseIndex), event);
	}
}
