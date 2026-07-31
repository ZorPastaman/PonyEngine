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

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Memory;
import PonyEngine.RawInput.Ext;
import PonyEngine.RawInput.Mouse.Impl;
import PonyEngine.Platform.Windows;
import PonyEngine.Surface.Windows;
import PonyEngine.Type;

export namespace PonyEngine::RawInput::Mouse
{
	/// @brief Mouse provider.
	class MouseProvider final : public IInputProvider, private Surface::IRawInputObserver, private Surface::ISurfaceObserver
	{
	public:
		/// @brief Creates a mouse provider.
		/// @param input Raw input context.
		[[nodiscard("Pure constructor")]]
		explicit MouseProvider(IRawInputContext& input);
		MouseProvider(const MouseProvider&) = delete;
		MouseProvider(MouseProvider&&) = delete;

		~MouseProvider() noexcept = default;

		virtual void Begin(IDeviceRegistry& deviceRegistry) override;
		virtual void End(IDeviceRegistry& deviceRegistry) override;
		virtual void Tick(IDeviceRegistry& deviceRegistry, IInputRegistry& inputRegistry) override;

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
		/// @param deviceRegistry Device registry.
		void UnregisterDevices(IDeviceRegistry& deviceRegistry);
		/// @brief Clears all the data.
		void Clear() noexcept;

		/// @brief Register devices that are not registered yet.
		/// @param deviceRegistry Device registry.
		void RegisterDevices(IDeviceRegistry& deviceRegistry);
		/// @brief Updates input.
		/// @param inputRegistry Input registry.
		void UpdateInput(IInputRegistry& inputRegistry);

		/// @brief Gets or creates a mouse.
		/// @param mouseHandle Mouse native handle.
		/// @return Mouse index.
		[[nodiscard("Weird call")]]
		std::size_t GetOrCreateMouse(HANDLE mouseHandle);
		/// @brief Gets a mouse name.
		/// @param mouseHandle Mouse native handle.
		/// @return Buffer and mouse index.
		[[nodiscard("Pure function")]]
		std::pair<Application::ScopedTempBuffer, std::string_view> GetMouseName(HANDLE mouseHandle) const;

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
		Surface::ISurfaceService* surface; ///< Surface service.

		DeviceTypeID deviceType; ///< Mouse device type.
		MouseAxisMap axisMap; ///< Mouse axis map.

		std::size_t registeredDeviceCount; ///< Registered device count.
		MouseContainer<HANDLE> mouseContainer; ///< Mouse container.
		MouseEventQueue eventQueue; ///< Mouse event queue.
	};
}

namespace PonyEngine::RawInput::Mouse
{
	MouseProvider::MouseProvider(IRawInputContext& input) :
		input{&input},
		surface{&this->input->Application().GetService<Surface::ISurfaceService>()},
		deviceType(this->input->HashDeviceType(MouseDevice::GenericType)),
		axisMap(*this->input),
		registeredDeviceCount{0uz}
	{
	}

	void MouseProvider::Begin(IDeviceRegistry& deviceRegistry)
	{
		Subscribe();
	}

	void MouseProvider::End(IDeviceRegistry& deviceRegistry)
	{
		Unsubscribe();
		UnregisterDevices(deviceRegistry);
		Clear();
	}

	void MouseProvider::Tick(IDeviceRegistry& deviceRegistry, IInputRegistry& inputRegistry)
	{
		RegisterDevices(deviceRegistry);
		UpdateInput(inputRegistry);
	}

	void MouseProvider::Observe(const RAWINPUT& rawInput)
	{
#ifndef NDEBUG
		if (rawInput.header.dwType != RIM_TYPEMOUSE) [[unlikely]]
		{
			throw std::logic_error("Not mouse input");
		}
#endif

		const std::size_t index = GetOrCreateMouse(rawInput.header.hDevice);
		UpdatePointer(rawInput.data.mouse, index);
		UpdateWheels(rawInput.data.mouse, index);
		UpdateButtons(rawInput.data.mouse, index);
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
			eventQueue.Add(index, event);

			PONY_LOG(input->Logger(), Log::LogType::Info, "Mouse device connection changed to '{}'. Native handle: '0x{:X}'.",
				isConnected, reinterpret_cast<std::uintptr_t>(device));
		};

		if (isConnected)
		{
			const auto [buffer, name] = GetMouseName(device);
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
		const std::span<const bool, 5> buttonStates = mouseContainer.ButtonStates(mouseIndex);

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
			eventQueue.Add(mouseIndex, event);
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

	void MouseProvider::UnregisterDevices(IDeviceRegistry& deviceRegistry)
	{
		for (std::size_t i = 0uz; i < registeredDeviceCount; ++i)
		{
			const DeviceHandle handle = mouseContainer.DeviceHandle(i);
			PONY_LOG(input->Logger(), Log::LogType::Info, "Unregistering mouse device. Handle: '0x{:X}'.", handle.id);
			deviceRegistry.UnregisterDevice(handle);
		}
	}

	void MouseProvider::Clear() noexcept
	{
		mouseContainer.Clear();
		eventQueue.Clear();
	}

	void MouseProvider::RegisterDevices(IDeviceRegistry& deviceRegistry)
	{
		for (; registeredDeviceCount < mouseContainer.Size(); ++registeredDeviceCount)
		{
			const HANDLE nativeHandle = mouseContainer.NativeHandle(registeredDeviceCount);
			const std::string_view name = mouseContainer.Name(registeredDeviceCount);
			const bool isConnected = mouseContainer.IsConnected(registeredDeviceCount);

			PONY_LOG(input->Logger(), Log::LogType::Info, "Registering mouse device... NativeHandle: '0x{:X}'; Name: '{}'.",
				reinterpret_cast<std::uintptr_t>(nativeHandle), name);
			const DeviceHandle deviceHandle = mouseContainer.DeviceHandle(registeredDeviceCount) = deviceRegistry.RegisterDevice(deviceType, name, isConnected);
			PONY_LOG(input->Logger(), Log::LogType::Info, "Registering mouse device done. NativeHandle: '0x{:X}'; Name: '{}'; DeviceHandle.",
				reinterpret_cast<std::uintptr_t>(nativeHandle), name, deviceHandle.id);
		}
	}

	void MouseProvider::UpdateInput(IInputRegistry& inputRegistry)
	{
		for (std::size_t i = 0uz; i < eventQueue.Size(); ++i)
		{
			const std::size_t deviceIndex = eventQueue.DeviceIndex(i);
			const MouseEvent& event = eventQueue.Event(i);
			const DeviceHandle device = mouseContainer.DeviceHandle(deviceIndex);

			std::visit(Type::Overload
			{
				[&](const MouseButtonEvent& button)
				{
					const AxisID axis = axisMap.Axis(button.button);
					const float value = button.state;
					inputRegistry.AddInput(device, RawInputEvent
					{
						.axes = std::span<const AxisID>(&axis, 1uz),
						.values = std::span<const float>(&value, 1uz),
						.eventType = InputEventType::State,
						.timePoint = event.timePoint,
						.cursorPosition = button.cursorPosition
					});
				},
				[&](const MouseWheelEvent& wheel)
				{
					const AxisID axis = axisMap.Axis(wheel.wheel);
					inputRegistry.AddInput(device, RawInputEvent
					{
						.axes = std::span<const AxisID>(&axis, 1uz),
						.values = std::span<const float>(&wheel.delta, 1uz),
						.eventType = InputEventType::Delta,
						.timePoint = event.timePoint,
						.cursorPosition = wheel.cursorPosition
					});
				},
				[&](const MousePointerEvent& pointer)
				{
					inputRegistry.AddInput(device, RawInputEvent
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
					inputRegistry.Connect(device, ConnectionEvent
					{
						.isConnected = connection.isConnected,
						.timePoint = event.timePoint
					});
				}
			}, event.event);
		}

		eventQueue.Clear();
	}

	std::size_t MouseProvider::GetOrCreateMouse(const HANDLE mouseHandle)
	{
		if (const std::size_t index = mouseContainer.IndexOf(mouseHandle); index < mouseContainer.Size()) [[likely]]
		{
			return index;
		}

		PONY_LOG(input->Logger(), Log::LogType::Info, "Creating new mouse device... Native handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(mouseHandle));
		const auto [buffer, name] = GetMouseName(mouseHandle);
		mouseContainer.Add(mouseHandle, DeviceHandle{}, name, true);
		PONY_LOG(input->Logger(), Log::LogType::Info, "Creating new mouse device done. Native handle: '0x{:X}'; Device name: '{}'.",
			reinterpret_cast<std::uintptr_t>(mouseHandle), name);

		return mouseContainer.Size() - 1uz;
	}

	std::pair<Application::ScopedTempBuffer, std::string_view> MouseProvider::GetMouseName(const HANDLE mouseHandle) const
	{
		const std::size_t nameSize = Platform::GetDeviceNameSize(mouseHandle);
		Application::ScopedTempBuffer buffer = input->Application().AcquiredScopedTempBuffer(nameSize);
		auto arena = Memory::Arena(*buffer);

		std::span<char> name = arena.AllocateArray<char>(buffer->size_bytes());
		const std::size_t copied = Platform::GetDeviceName(mouseHandle, name);

		return std::pair<Application::ScopedTempBuffer, std::string_view>(std::move(buffer), std::string_view(name.data(), copied));
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
				eventQueue.Add(mouseIndex, event);
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
			eventQueue.Add(mouseIndex, event);
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
		eventQueue.Add(mouseIndex, event);
	}
}
