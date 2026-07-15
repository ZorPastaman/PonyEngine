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

export module PonyEngine.RawInput.Keyboard.Impl.Windows:KeyboardProvider;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Memory;
import PonyEngine.Platform.Windows;
import PonyEngine.RawInput.Ext;
import PonyEngine.RawInput.Keyboard.Impl;
import PonyEngine.Surface.Windows;
import PonyEngine.Type;

import :KeyboardAxisMap;

export namespace PonyEngine::RawInput::Keyboard::Windows
{
	/// @brief Windows keyboard provider.
	class KeyboardProvider final : public IInputProvider, private Surface::Windows::IRawInputObserver, private Surface::ISurfaceObserver
	{
	public:
		/// @brief Creates a keyboard provider.
		/// @param input Raw input context.
		[[nodiscard("Pure constructor")]]
		explicit KeyboardProvider(IRawInputContext& input);
		KeyboardProvider(const KeyboardProvider&) = delete;
		KeyboardProvider(KeyboardProvider&&) = delete;

		~KeyboardProvider() noexcept = default;

		virtual void Begin(IDeviceRegistry& deviceRegistry) override;
		virtual void End(IDeviceRegistry& deviceRegistry) override;
		virtual void Tick(IDeviceRegistry& deviceRegistry, IInputRegistry& inputRegistry) override;

		KeyboardProvider& operator =(const KeyboardProvider&) = delete;
		KeyboardProvider& operator =(KeyboardProvider&&) = delete;

	private:
		virtual void Observe(const RAWINPUT& rawInput) override;
		virtual void OnDeviceConnectionChanged(HANDLE device, bool isConnected) override;

		virtual void OnFocusChanged(bool isInFocus) override;

		/// @brief Resets a keyboard input.
		/// @param keyboardIndex Keyboard index.
		/// @param eventTime Event time.
		/// @param cursorPosition Cursor position.
		void ResetInput(std::size_t keyboardIndex, std::chrono::time_point<std::chrono::steady_clock> eventTime, const Math::Vector2<std::int32_t>& cursorPosition);

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

		/// @brief Gets or creates a keyboard.
		/// @param keyboardHandle Keyboard native handle.
		/// @return Keyboard index.
		[[nodiscard("Weird call")]]
		std::size_t GetOrCreateKeyboard(HANDLE keyboardHandle);
		/// @brief Gets a keyboard name.
		/// @param keyboardHandle Keyboard native handle.
		/// @return Buffer and keyboard name.
		[[nodiscard("Pure function")]]
		std::pair<Application::ScopedTempBuffer, std::string_view> GetKeyboardName(HANDLE keyboardHandle) const;

		IRawInputContext* input; ///< Raw input context.
		Surface::Windows::ISurfaceService* surface; ///< Surface service.

		DeviceTypeID deviceType; ///< Keyboard device type.
		KeyboardAxisMap axisMap; ///< Axis map.

		std::size_t registeredDeviceCount; ///< Registered device count.
		KeyboardContainer<HANDLE, WORD> keyboardContainer; ///< Keyboard container.
		KeyboardEventQueue<WORD> eventQueue; ///< Keyboard event queue.
	};
}

namespace PonyEngine::RawInput::Keyboard::Windows
{
	KeyboardProvider::KeyboardProvider(IRawInputContext& input) :
		input{&input},
		surface{&this->input->Application().GetService<Surface::Windows::ISurfaceService>()},
		deviceType(this->input->HashDeviceType(KeyboardDevice::GenericType)),
		axisMap(*this->input),
		registeredDeviceCount{0uz}
	{
	}

	void KeyboardProvider::Begin(IDeviceRegistry& deviceRegistry)
	{
		Subscribe();
	}

	void KeyboardProvider::End(IDeviceRegistry& deviceRegistry)
	{
		Unsubscribe();
		UnregisterDevices(deviceRegistry);
		Clear();
	}

	void KeyboardProvider::Tick(IDeviceRegistry& deviceRegistry, IInputRegistry& inputRegistry)
	{
		RegisterDevices(deviceRegistry);
		UpdateInput(inputRegistry);
	}

	void KeyboardProvider::Observe(const RAWINPUT& rawInput)
	{
#ifndef NDEBUG
		if (rawInput.header.dwType != RIM_TYPEKEYBOARD) [[unlikely]]
		{
			throw std::logic_error("Not keyboard input");
		}
#endif

		if (rawInput.data.keyboard.MakeCode == 0u || rawInput.data.keyboard.MakeCode == KEYBOARD_OVERRUN_MAKE_CODE || 
			rawInput.data.keyboard.VKey >= std::numeric_limits<unsigned char>::max()) [[unlikely]]
		{
			return;
		}

		const std::size_t index = GetOrCreateKeyboard(rawInput.header.hDevice);
		const WORD key = axisMap.ScanCode(rawInput.data.keyboard);
		const bool pressed = !(rawInput.data.keyboard.Flags & RI_KEY_BREAK);

		if (keyboardContainer.IsPressed(index, key) != pressed)
		{
			keyboardContainer.Press(index, key, pressed);

			const auto inputEvent = KeyboardInputEvent<WORD>
			{
				.key = key,
				.state = pressed,
				.cursorPosition = surface->LastMessageCursorPosition()
			};
			const auto event = KeyboardEvent<WORD>
			{
				.event = inputEvent,
				.timePoint = surface->LastMessageTime()
			};
			eventQueue.Add(index, event);
		}
	}

	void KeyboardProvider::OnDeviceConnectionChanged(const HANDLE device, const bool isConnected)
	{
		const auto addConnectionEvent = [&](const std::size_t index)
		{
			if (keyboardContainer.IsConnected(index) == isConnected)
			{
				return;
			}

			keyboardContainer.Connect(index, isConnected);

			const auto connectionEvent = KeyboardConnectionEvent{.connected = isConnected};
			const auto event = KeyboardEvent<WORD>{.event = connectionEvent, .timePoint = surface->LastMessageTime()};
			eventQueue.Add(index, event);

			PONY_LOG(input->Logger(), Log::LogType::Info, "Keyboard device connection changed to '{}'. Native handle: '0x{:X}'.",
				isConnected, reinterpret_cast<std::uintptr_t>(device));
		};

		if (isConnected)
		{
			const auto [buffer, name] = GetKeyboardName(device);
			const std::size_t index = keyboardContainer.IndexOf(name);
			if (index < keyboardContainer.Size())
			{
				keyboardContainer.NativeHandle(index) = device;
				addConnectionEvent(index);
			}
		}
		else
		{
			const std::size_t index = keyboardContainer.IndexOf(device);
			if (index < keyboardContainer.Size())
			{
				ResetInput(index, surface->LastMessageTime(), surface->LastMessageCursorPosition());
				keyboardContainer.NativeHandle(index) = INVALID_HANDLE_VALUE;
				addConnectionEvent(index);
			}
		}
	}

	void KeyboardProvider::OnFocusChanged(const bool isInFocus)
	{
		if (isInFocus)
		{
			return;
		}

		const std::chrono::time_point<std::chrono::steady_clock> time = surface->LastMessageTime();
		const Math::Vector2<std::int32_t> cursorPosition = surface->LastMessageCursorPosition();

		for (std::size_t i = 0uz; i < keyboardContainer.Size(); ++i)
		{
			ResetInput(i, time, cursorPosition);
		}
	}

	void KeyboardProvider::ResetInput(const std::size_t keyboardIndex, const std::chrono::time_point<std::chrono::steady_clock> eventTime, 
		const Math::Vector2<std::int32_t>& cursorPosition)
	{
		for (const WORD key : keyboardContainer.PressedKeys(keyboardIndex))
		{
			const auto inputEvent = KeyboardInputEvent<WORD>
			{
				.key = key,
				.state = false,
				.cursorPosition = cursorPosition
			};
			const auto event = KeyboardEvent<WORD>
			{
				.event = inputEvent,
				.timePoint = eventTime
			};
			eventQueue.Add(keyboardIndex, event);
		}

		keyboardContainer.ResetKeys(keyboardIndex);
	}

	void KeyboardProvider::Subscribe()
	{
		surface->AddObserver(*this);
		try
		{
			surface->AddRawInputObserver(*this, HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD);
		}
		catch (...)
		{
			surface->RemoveObserver(*this);
			throw;
		}
	}

	void KeyboardProvider::Unsubscribe() noexcept
	{
		surface->RemoveRawInputObserver(*this, HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD);
		surface->RemoveObserver(*this);
	}

	void KeyboardProvider::UnregisterDevices(IDeviceRegistry& deviceRegistry)
	{
		for (std::size_t i = 0uz; i < registeredDeviceCount; ++i)
		{
			const DeviceHandle handle = keyboardContainer.DeviceHandle(i);
			PONY_LOG(input->Logger(), Log::LogType::Info, "Unregistering keyboard device. Handle: '0x{:X}'.", handle.id);
			deviceRegistry.UnregisterDevice(handle);
		}
	}

	void KeyboardProvider::Clear() noexcept
	{
		keyboardContainer.Clear();
		eventQueue.Clear();
	}

	void KeyboardProvider::RegisterDevices(IDeviceRegistry& deviceRegistry)
	{
		for (; registeredDeviceCount < keyboardContainer.Size(); ++registeredDeviceCount)
		{
			const HANDLE nativeHandle = keyboardContainer.NativeHandle(registeredDeviceCount);
			const std::string_view name = keyboardContainer.DeviceName(registeredDeviceCount);
			const bool isConnected = keyboardContainer.IsConnected(registeredDeviceCount);

			PONY_LOG(input->Logger(), Log::LogType::Info, "Registering keyboard device... NativeHandle: '0x{:X}'; Name: '{}'.", 
				reinterpret_cast<std::uintptr_t>(nativeHandle), name);
			const DeviceHandle deviceHandle = keyboardContainer.DeviceHandle(registeredDeviceCount) = deviceRegistry.RegisterDevice(deviceType, name, isConnected);
			PONY_LOG(input->Logger(), Log::LogType::Info, "Registering keyboard device done. NativeHandle: '0x{:X}'; Name: '{}'; DeviceHandle.",
				reinterpret_cast<std::uintptr_t>(nativeHandle), name, deviceHandle.id);
		}
	}

	void KeyboardProvider::UpdateInput(IInputRegistry& inputRegistry)
	{
		for (std::size_t i = 0uz; i < eventQueue.Size(); ++i)
		{
			const std::size_t deviceIndex = eventQueue.DeviceIndex(i);
			const KeyboardEvent<WORD>& event = eventQueue.Event(i);
			const DeviceHandle deviceHandle = keyboardContainer.DeviceHandle(deviceIndex);

			std::visit(Type::Overload
			{
				[&](const KeyboardInputEvent<WORD>& keyboardInput)
				{
					const AxisID axis = axisMap.Axis(keyboardInput.key);
					const float value = keyboardInput.state;

					inputRegistry.AddInput(deviceHandle, RawInputEvent
					{
						.axes = std::span<const AxisID>(&axis, 1uz),
						.values = std::span<const float>(&value, 1uz),
						.eventType = InputEventType::State,
						.timePoint = event.timePoint,
						.cursorPosition = keyboardInput.cursorPosition
					});
				},
				[&](const KeyboardConnectionEvent& keyboardConnection)
				{
					inputRegistry.Connect(deviceHandle, ConnectionEvent
					{
						.isConnected = keyboardConnection.connected,
						.timePoint = event.timePoint
					});
				}
			}, event.event);
		}

		eventQueue.Clear();
	}

	std::size_t KeyboardProvider::GetOrCreateKeyboard(const HANDLE keyboardHandle)
	{
		if (const std::size_t index = keyboardContainer.IndexOf(keyboardHandle); index < keyboardContainer.Size()) [[likely]]
		{
			return index;
		}

		PONY_LOG(input->Logger(), Log::LogType::Info, "Creating new keyboard device... Native handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(keyboardHandle));
		const auto [buffer, name] = GetKeyboardName(keyboardHandle);
		keyboardContainer.Add(keyboardHandle, DeviceHandle{}, name, true);
		PONY_LOG(input->Logger(), Log::LogType::Info, "Creating new keyboard device done. Native handle: '0x{:X}'; Device name: '{}'.", 
			reinterpret_cast<std::uintptr_t>(keyboardHandle), name);

		return keyboardContainer.Size() - 1uz;
	}

	std::pair<Application::ScopedTempBuffer, std::string_view> KeyboardProvider::GetKeyboardName(const HANDLE keyboardHandle) const
	{
		const std::size_t nameSize = Platform::Windows::GetDeviceNameSize(keyboardHandle);
		Application::ScopedTempBuffer buffer = input->Application().AcquiredScopedTempBuffer(nameSize);
		auto arena = Memory::Arena(*buffer);

		std::span<char> name = arena.AllocateArray<char>(buffer->size_bytes());
		Platform::Windows::GetDeviceName(keyboardHandle, name);

		return std::pair<Application::ScopedTempBuffer, std::string_view>(std::move(buffer), name);
	}
}
