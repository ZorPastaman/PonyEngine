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

export module PonyEngine.Input.Keyboard.Impl:Windows.KeyboardProvider;

import std;

import PonyEngine.Input.Ext;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Platform;
import PonyEngine.Surface;
import PonyEngine.Text;
import PonyEngine.Type;

import :Keyboard;
import :KeyboardContainer;

import :Windows.KeyboardLayoutMap;

export namespace PonyEngine::Input::Windows
{
	class KeyboardProvider final : public IInputProvider, private Surface::Windows::IRawInputObserver
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit KeyboardProvider(IInputContext& input);
		KeyboardProvider(const KeyboardProvider&) = delete;
		KeyboardProvider(KeyboardProvider&&) = delete;

		~KeyboardProvider() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;
		virtual void Tick() override;

		virtual void Observe(const RAWINPUT& rawInput, std::chrono::time_point<std::chrono::steady_clock> eventTime, const Math::Vector2<std::int32_t>& cursorPosition) override;
		virtual void OnDeviceConnectionChanged(HANDLE device, bool isConnected) override;

		KeyboardProvider& operator =(const KeyboardProvider&) = delete;
		KeyboardProvider& operator =(KeyboardProvider&&) = delete;

	private:
		void Subscribe();
		void Unsubscribe() noexcept;

		void RegisterDevices();
		void UnregisterDevices();
		void UpdateKeyboards();
		void Clear() noexcept;

		[[nodiscard("Pure function")]]
		static WORD ScanCode(const RAWKEYBOARD& key) noexcept;

		[[nodiscard("Weird call")]]
		std::size_t GetOrCreateKeyboard(HANDLE keyboardHandle);
		[[nodiscard("Pure function")]]
		std::string_view GetKeyboardName(HANDLE keyboardHandle);

		IInputContext* input;
		Surface::Windows::ISurfaceService* surface;

		KeyboardContainer<HANDLE> keyboardContainer;
		std::size_t registeredDevices;

		std::string deviceNameTemp;
	};
}

namespace PonyEngine::Input::Windows
{
	KeyboardProvider::KeyboardProvider(IInputContext& input) :
		input{&input},
		surface{&this->input->Application().GetService<Surface::Windows::ISurfaceService>()},
		registeredDevices{0uz}
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
		RegisterDevices();
		UpdateKeyboards();
	}

	void KeyboardProvider::Observe(const RAWINPUT& rawInput, const std::chrono::time_point<std::chrono::steady_clock> eventTime, const Math::Vector2<std::int32_t>& cursorPosition)
	{
#if !NDEBUG
		if (rawInput.header.dwType != RIM_TYPEKEYBOARD) [[unlikely]]
		{
			throw std::logic_error("Not keyboard input.");
		}
#endif

		const WORD scanCode = ScanCode(rawInput.data.keyboard);
		if (const auto layoutPosition = KeyboardLayoutMap.find(scanCode); layoutPosition != KeyboardLayoutMap.cend())
		{
			const std::size_t index = GetOrCreateKeyboard(rawInput.header.hDevice);
			Keyboard& keyboard = keyboardContainer.Keyboard(index);
			const KeyboardLayout key = layoutPosition->second;
			const bool pressed = !(rawInput.data.keyboard.Flags & RI_KEY_BREAK);

			if (keyboard.IsPressed(key) != pressed)
			{
				keyboard.AddEvent(KeyboardInput
				{
					.key = key,
					.pressed = pressed,
					.eventTime = eventTime,
					.cursorPosition = cursorPosition
				});
			}
		}
	}

	void KeyboardProvider::OnDeviceConnectionChanged(const HANDLE device, const bool isConnected)
	{
		if (isConnected)
		{
			const std::string_view name = GetKeyboardName(device);
			const std::size_t index = keyboardContainer.IndexOf(name);
			if (index < keyboardContainer.Size())
			{
				Keyboard& keyboard = keyboardContainer.Keyboard(index);
				keyboardContainer.NativeHandle(index) = device;

				if (!keyboard.IsConnected()) [[likely]]
				{
					keyboard.AddEvent(KeyboardConnection{.isConnected = true});
					PONY_LOG(input->Logger(), Log::LogType::Info, "Keyboard device connection changed to '{}'. Handle: '0x{:X}'; Native handle: '0x{:X}'.", 
						true, keyboardContainer.DeviceHandle(index).id, reinterpret_cast<std::uintptr_t>(device));
				}
			}
		}
		else
		{
			const std::size_t index = keyboardContainer.IndexOf(device);
			if (index < keyboardContainer.Size())
			{
				Keyboard& keyboard = keyboardContainer.Keyboard(index);
				keyboardContainer.NativeHandle(index) = INVALID_HANDLE_VALUE;
				keyboard.ClearKeyStates();

				if (keyboard.IsConnected()) [[likely]]
				{
					keyboard.AddEvent(KeyboardConnection{.isConnected = false});
					PONY_LOG(input->Logger(), Log::LogType::Info, "Keyboard device connection changed to '{}'. Handle: '0x{:X}'; Native handle: '0x{:X}'.",
						false, keyboardContainer.DeviceHandle(index).id, reinterpret_cast<std::uintptr_t>(device));
				}
			}
		}
	}

	void KeyboardProvider::Subscribe()
	{
		surface->AddRawInputObserver(*this, HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD);
	}

	void KeyboardProvider::Unsubscribe() noexcept
	{
		surface->RemoveRawInputObserver(*this, HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD);
	}

	void KeyboardProvider::RegisterDevices()
	{
		for (; registeredDevices < keyboardContainer.Size(); ++registeredDevices)
		{
			PONY_LOG(input->Logger(), Log::LogType::Info, "Registering keyboard device. Native handle: '0x{:X}'.", 
				reinterpret_cast<std::uintptr_t>(keyboardContainer.NativeHandle(registeredDevices)));
			keyboardContainer.DeviceHandle(registeredDevices) = input->RegisterDevice(DeviceData
			{
				.device = keyboardContainer.KeyboardShared(registeredDevices),
				.layouts = KeyboardLayouts,
				.isConnected = true
			});
		}
	}

	void KeyboardProvider::UnregisterDevices()
	{
		for (; registeredDevices > 0uz; --registeredDevices)
		{
			const DeviceHandle handle = keyboardContainer.DeviceHandle(registeredDevices - 1uz);
			PONY_LOG(input->Logger(), Log::LogType::Info, "Unregistering keyboard device. Handle: '0x{:X}'.", handle.id);
			input->UnregisterDevice(handle);
		}
	}

	void KeyboardProvider::UpdateKeyboards()
	{
		for (std::size_t i = 0uz; i < keyboardContainer.Size(); ++i)
		{
			Keyboard& keyboard = keyboardContainer.Keyboard(i);
			const DeviceHandle deviceHandle = keyboardContainer.DeviceHandle(i);

			for (const KeyboardEvent& event : keyboard.Events())
			{
				std::visit(Type::Overload
				{
					[&](const KeyboardInput& keyboardInput)
					{
						const auto axis = Axis(keyboardInput.key);
						const float value = keyboardInput.pressed;
						input->AddInput(deviceHandle, RawInputEvent
						{
							.axes = std::span<const Axis>(&axis, 1uz),
							.values = std::span<const float>(&value, 1uz),
							.eventType = InputEventType::State,
							.timePoint = keyboardInput.eventTime,
							.cursorPosition = keyboardInput.cursorPosition
						});
					},
					[&](const KeyboardConnection& connection)
					{
						input->Connect(deviceHandle, connection.isConnected);
					}
				}, event);
			}

			keyboard.ClearEvents();
		}
	}

	void KeyboardProvider::Clear() noexcept
	{
		keyboardContainer.Clear();
	}

	WORD KeyboardProvider::ScanCode(const RAWKEYBOARD& key) noexcept
	{
		const USHORT makeCode = key.MakeCode;
		const USHORT flags = key.Flags;
		const USHORT base = makeCode & 0x7F;
		const USHORT extension = flags & RI_KEY_E0 ? 0xE0 : flags & RI_KEY_E1 ? 0xE1 : 0x00;

		return MAKEWORD(base, extension);
	}

	std::size_t KeyboardProvider::GetOrCreateKeyboard(const HANDLE keyboardHandle)
	{
		if (const std::size_t index = keyboardContainer.IndexOf(keyboardHandle); index < keyboardContainer.Size()) [[likely]]
		{
			return index;
		}

		PONY_LOG(input->Logger(), Log::LogType::Info, "Creating new keyboard device... Native handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(keyboardHandle));
		keyboardContainer.Add(keyboardHandle, DeviceHandle(), std::make_shared<Keyboard>(GetKeyboardName(keyboardHandle), true));
		const std::size_t index = keyboardContainer.Size() - 1uz;
		PONY_LOG(input->Logger(), Log::LogType::Info, "Creating new keyboard device done. Native handle: '0x{:X}'; Device name: '{}'.", 
			reinterpret_cast<std::uintptr_t>(keyboardHandle), keyboardContainer.Keyboard(index).Name());

		return index;
	}

	std::string_view KeyboardProvider::GetKeyboardName(const HANDLE keyboardHandle)
	{
		Platform::Windows::GetDeviceName(keyboardHandle, deviceNameTemp);
		return deviceNameTemp;
	}
}
