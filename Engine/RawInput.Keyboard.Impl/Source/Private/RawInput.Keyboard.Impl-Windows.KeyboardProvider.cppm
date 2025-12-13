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
#include "PonyEngine/Platform/Windows/Input.h"

export module PonyEngine.RawInput.Keyboard.Impl:Windows.KeyboardProvider;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Platform;
import PonyEngine.RawInput.Ext;
import PonyEngine.Surface;
import PonyEngine.Type;

import :Keyboard;
import :KeyboardContainer;
import :KeyboardEvent;
import :KeyboardEventQueue;

import :Windows.KeyboardAxisMap;

export namespace PonyEngine::Input::Windows
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

		virtual void Begin() override;
		virtual void End() override;
		virtual void Tick() override;

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
		void UnregisterDevices();
		/// @brief Clears all the data.
		void Clear() noexcept;

		/// @brief Gets or creates a keyboard.
		/// @param keyboardHandle Keyboard native handle.
		/// @return Keyboard index.
		[[nodiscard("Weird call")]]
		std::size_t GetOrCreateKeyboard(HANDLE keyboardHandle);
		/// @brief Gets a keyboard name.
		/// @param keyboardHandle Keyboard native handle.
		/// @return Keyboard name.
		[[nodiscard("Pure function")]]
		std::string_view GetKeyboardName(HANDLE keyboardHandle) const;

		IRawInputContext* input; ///< Raw input context.
		Surface::Windows::ISurfaceService* surface; ///< Surface service.

		DeviceTypeId deviceType; ///< Keyboard device type.
		KeyboardAxisMap axisMap; ///< Axis map.

		KeyboardContainer<HANDLE> keyboardContainer; ///< Keyboard container.
		KeyboardEventQueue eventQueue; ///< Keyboard event queue.

		mutable std::string deviceNameTemp; ///< Temporary device name.
	};
}

namespace PonyEngine::Input::Windows
{
	KeyboardProvider::KeyboardProvider(IRawInputContext& input) :
		input{&input},
		surface{&this->input->Application().GetService<Surface::Windows::ISurfaceService>()},
		deviceType(this->input->Hash(DeviceType(KeyboardDevice::GenericType))),
		axisMap(*this->input)
	{
	}

	void KeyboardProvider::Begin()
	{
		Subscribe();
	}

	void KeyboardProvider::End()
	{
		Unsubscribe();
		UnregisterDevices();
		Clear();
	}

	void KeyboardProvider::Tick()
	{
		for (std::size_t i = 0uz; i < eventQueue.Size(); ++i)
		{
			const DeviceHandle device = eventQueue.Device(i);
			const KeyboardEvent& event = eventQueue.Event(i);

			std::visit(Type::Overload
			{
				[&](const KeyboardInputEvent& keyboardInput)
				{
					const float value = keyboardInput.state;

					input->AddInput(device, RawInputEvent
					{
						.axes = std::span<const AxisId>(&keyboardInput.axis, 1uz),
						.values = std::span<const float>(&value, 1uz),
						.eventType = InputEventType::State,
						.timePoint = event.timePoint,
						.cursorPosition = keyboardInput.cursorPosition
					});
				},
				[&](const KeyboardConnectionEvent& keyboardConnection)
				{
					input->Connect(device, ConnectionEvent
					{
						.isConnected = keyboardConnection.connected,
						.timePoint = event.timePoint
					});
				}
			}, event.event);
		}

		eventQueue.Clear();
	}

	void KeyboardProvider::Observe(const RAWINPUT& rawInput)
	{
#if !NDEBUG
		if (rawInput.header.dwType != RIM_TYPEKEYBOARD) [[unlikely]]
		{
			throw std::logic_error("Not keyboard input.");
		}
#endif

		if (rawInput.data.keyboard.MakeCode == 0u || rawInput.data.keyboard.MakeCode == KEYBOARD_OVERRUN_MAKE_CODE || 
			rawInput.data.keyboard.VKey >= std::numeric_limits<unsigned char>::max()) [[unlikely]]
		{
			return;
		}

		try
		{
			const std::size_t index = GetOrCreateKeyboard(rawInput.header.hDevice);
			Keyboard& keyboard = keyboardContainer.Keyboard(index);
			const AxisId axis = axisMap.Axis(rawInput.data.keyboard);
			const bool pressed = !(rawInput.data.keyboard.Flags & RI_KEY_BREAK);

			if (keyboard.IsPressed(axis) != pressed)
			{
				keyboard.Press(axis, pressed);

				const auto inputEvent = KeyboardInputEvent
				{
					.axis = axis,
					.state = pressed,
					.cursorPosition = surface->LastMessageCursorPosition()
				};
				const auto event = KeyboardEvent
				{
					.event = inputEvent,
					.timePoint = surface->LastMessageTime()
				};
				eventQueue.Add(keyboardContainer.DeviceHandle(index), event);
			}
		}
		catch (...)
		{
			input->Application().Stop(ExitCodes::InputError);
			throw;
		}
	}

	void KeyboardProvider::OnDeviceConnectionChanged(const HANDLE device, const bool isConnected)
	{
		const auto addConnectionEvent = [&](const std::size_t index)
		{
			Keyboard& keyboard = keyboardContainer.Keyboard(index);
			if (keyboard.IsConnected() == isConnected)
			{
				return;
			}

			keyboard.Connect(isConnected);

			const auto connectionEvent = KeyboardConnectionEvent{.connected = isConnected};
			const auto event = KeyboardEvent{.event = connectionEvent, .timePoint = surface->LastMessageTime()};
			const DeviceHandle deviceHandle = keyboardContainer.DeviceHandle(index);
			eventQueue.Add(deviceHandle, event);

			PONY_LOG(input->Logger(), Log::LogType::Info, "Keyboard device connection changed to '{}'. Handle: '0x{:X}'; Native handle: '0x{:X}'.",
				isConnected, deviceHandle.id, reinterpret_cast<std::uintptr_t>(device));
		};

		try
		{
			if (isConnected)
			{
				const std::string_view name = GetKeyboardName(device);
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
		catch (...)
		{
			input->Application().Stop(ExitCodes::InputError);
			throw;
		}
	}

	void KeyboardProvider::OnFocusChanged(const bool isInFocus)
	{
		if (isInFocus)
		{
			return;
		}

		try
		{
			const std::chrono::time_point<std::chrono::steady_clock> time = surface->LastMessageTime();
			const Math::Vector2<std::int32_t> cursorPosition = surface->LastMessageCursorPosition();

			for (std::size_t i = 0uz; i < keyboardContainer.Size(); ++i)
			{
				ResetInput(i, time, cursorPosition);
			}
		}
		catch (...)
		{
			input->Application().Stop(ExitCodes::InputError);
			throw;
		}
	}

	void KeyboardProvider::ResetInput(const std::size_t keyboardIndex, const std::chrono::time_point<std::chrono::steady_clock> eventTime, 
		const Math::Vector2<std::int32_t>& cursorPosition)
	{
		Keyboard& keyboard = keyboardContainer.Keyboard(keyboardIndex);

		for (const AxisId axis : keyboard.PressedKeys())
		{
			const auto inputEvent = KeyboardInputEvent
			{
				.axis = axis,
				.state = false,
				.cursorPosition = cursorPosition
			};
			const auto event = KeyboardEvent
			{
				.event = inputEvent,
				.timePoint = eventTime
			};
			eventQueue.Add(keyboardContainer.DeviceHandle(keyboardIndex), event);
		}

		keyboard.ResetKeys();
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

	void KeyboardProvider::UnregisterDevices()
	{
		for (std::size_t i = 0uz; i < keyboardContainer.Size(); ++i)
		{
			const DeviceHandle handle = keyboardContainer.DeviceHandle(i);
			PONY_LOG(input->Logger(), Log::LogType::Info, "Unregistering keyboard device. Handle: '0x{:X}'.", handle.id);
			input->UnregisterDevice(handle);
		}
	}

	void KeyboardProvider::Clear() noexcept
	{
		keyboardContainer.Clear();
		eventQueue.Clear();
	}

	std::size_t KeyboardProvider::GetOrCreateKeyboard(const HANDLE keyboardHandle)
	{
		if (const std::size_t index = keyboardContainer.IndexOf(keyboardHandle); index < keyboardContainer.Size()) [[likely]]
		{
			return index;
		}

		PONY_LOG(input->Logger(), Log::LogType::Info, "Creating new keyboard device... Native handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(keyboardHandle));
		const auto keyboard = std::make_shared<Keyboard>(GetKeyboardName(keyboardHandle), deviceType, true);
		const DeviceHandle deviceHandle = input->RegisterDevice(DeviceData{.device = keyboard, .isConnected = true});
		try
		{
			keyboardContainer.Add(keyboardHandle, deviceHandle, keyboard);
		}
		catch (...)
		{
			input->UnregisterDevice(deviceHandle);
			throw;
		}
		PONY_LOG(input->Logger(), Log::LogType::Info, "Creating new keyboard device done. Native handle: '0x{:X}'; Device handle: '0x{:X}'; Device name: '{}'.", 
			reinterpret_cast<std::uintptr_t>(keyboardHandle), deviceHandle.id, keyboard->Name());

		return keyboardContainer.Size() - 1uz;
	}

	std::string_view KeyboardProvider::GetKeyboardName(const HANDLE keyboardHandle) const
	{
		Platform::Windows::GetDeviceName(keyboardHandle, deviceNameTemp);
		return deviceNameTemp;
	}
}
