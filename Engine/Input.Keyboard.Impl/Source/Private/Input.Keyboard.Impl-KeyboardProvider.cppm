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

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Input.Keyboard.Impl:KeyboardProvider;

import std;

import PonyEngine.Input.Ext;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Text;
import PonyEngine.Type;

#if PONY_WINDOWS
import PonyEngine.Surface;
#endif

import :Keyboard;

#if PONY_WINDOWS
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
		static inline const std::unordered_map<USHORT, KeyboardLayout> LayoutMap
		{
			// Letters
			{ 0x001E, KeyboardLayout::A },
			{ 0x0030, KeyboardLayout::B },
			{ 0x002E, KeyboardLayout::C },
			{ 0x0020, KeyboardLayout::D },
			{ 0x0012, KeyboardLayout::E },
			{ 0x0021, KeyboardLayout::F },
			{ 0x0022, KeyboardLayout::G },
			{ 0x0023, KeyboardLayout::H },
			{ 0x0017, KeyboardLayout::I },
			{ 0x0024, KeyboardLayout::J },
			{ 0x0025, KeyboardLayout::K },
			{ 0x0026, KeyboardLayout::L },
			{ 0x0032, KeyboardLayout::M },
			{ 0x0031, KeyboardLayout::N },
			{ 0x0018, KeyboardLayout::O },
			{ 0x0019, KeyboardLayout::P },
			{ 0x0010, KeyboardLayout::Q },
			{ 0x0013, KeyboardLayout::R },
			{ 0x001F, KeyboardLayout::S },
			{ 0x0014, KeyboardLayout::T },
			{ 0x0016, KeyboardLayout::U },
			{ 0x002F, KeyboardLayout::V },
			{ 0x0011, KeyboardLayout::W },
			{ 0x002D, KeyboardLayout::X },
			{ 0x0015, KeyboardLayout::Y },
			{ 0x002C, KeyboardLayout::Z },
			// Letter signs
			{ 0x0034, KeyboardLayout::Period },
			{ 0x0033, KeyboardLayout::Comma },
			{ 0x0035, KeyboardLayout::Slash },
			{ 0x002B, KeyboardLayout::Backslash },
			{ 0x0027, KeyboardLayout::Semicolon },
			{ 0x0028, KeyboardLayout::Apostrophe },
			{ 0x001A, KeyboardLayout::LeftBracket },
			{ 0x001B, KeyboardLayout::RightBracket },
			// Numbers
			{ 0x0002, KeyboardLayout::Number1 },
			{ 0x0003, KeyboardLayout::Number2 },
			{ 0x0004, KeyboardLayout::Number3 },
			{ 0x0005, KeyboardLayout::Number4 },
			{ 0x0006, KeyboardLayout::Number5 },
			{ 0x0007, KeyboardLayout::Number6 },
			{ 0x0008, KeyboardLayout::Number7 },
			{ 0x0009, KeyboardLayout::Number8 },
			{ 0x000A, KeyboardLayout::Number9 },
			{ 0x000B, KeyboardLayout::Number0 },
			// Math signs
			{ 0x000C, KeyboardLayout::Minus },
			{ 0x000D, KeyboardLayout::Equal },
			{ 0x0029, KeyboardLayout::Tilde },
			// Arrows
			{ 0xE048, KeyboardLayout::ArrowUp },
			{ 0xE050, KeyboardLayout::ArrowDown },
			{ 0xE04D, KeyboardLayout::ArrowRight },
			{ 0xE04B, KeyboardLayout::ArrowLeft },
			// F Keys
			{ 0x003B, KeyboardLayout::F1 },
			{ 0x003C, KeyboardLayout::F2 },
			{ 0x003D, KeyboardLayout::F3 },
			{ 0x003E, KeyboardLayout::F4 },
			{ 0x003F, KeyboardLayout::F5 },
			{ 0x0040, KeyboardLayout::F6 },
			{ 0x0041, KeyboardLayout::F7 },
			{ 0x0042, KeyboardLayout::F8 },
			{ 0x0043, KeyboardLayout::F9 },
			{ 0x0044, KeyboardLayout::F10 },
			{ 0x0057, KeyboardLayout::F11 },
			{ 0x0058, KeyboardLayout::F12 },
			// System keys
			{ 0x0039, KeyboardLayout::Space },
			{ 0x000E, KeyboardLayout::Backspace },
			{ 0x0001, KeyboardLayout::Escape },
			{ 0x000F, KeyboardLayout::Tab },
			{ 0x003A, KeyboardLayout::CapsLock },
			{ 0x002A, KeyboardLayout::LeftShift },
			{ 0x0036, KeyboardLayout::RightShift },
			{ 0x001D, KeyboardLayout::LeftCtrl },
			{ 0xE01D, KeyboardLayout::RightCtrl },
			{ 0x0038, KeyboardLayout::LeftAlt },
			{ 0xE038, KeyboardLayout::RightAlt },
			{ 0x001C, KeyboardLayout::Enter },
			{ 0xE052, KeyboardLayout::Insert },
			{ 0xE053, KeyboardLayout::Delete },
			{ 0xE047, KeyboardLayout::Home },
			{ 0xE04F, KeyboardLayout::End },
			{ 0xE049, KeyboardLayout::PageUp },
			{ 0xE051, KeyboardLayout::PageDown },
			{ 0xE037, KeyboardLayout::Print },
			{ 0x0046, KeyboardLayout::ScrollLock },
			{ 0xE11D45, KeyboardLayout::Pause },
			// Numpad numbers
			{ 0x0052, KeyboardLayout::Numpad0 },
			{ 0x004F, KeyboardLayout::Numpad1 },
			{ 0x0050, KeyboardLayout::Numpad2 },
			{ 0x0051, KeyboardLayout::Numpad3 },
			{ 0x004B, KeyboardLayout::Numpad4 },
			{ 0x004C, KeyboardLayout::Numpad5 },
			{ 0x004D, KeyboardLayout::Numpad6 },
			{ 0x0047, KeyboardLayout::Numpad7 },
			{ 0x0048, KeyboardLayout::Numpad8 },
			{ 0x0049, KeyboardLayout::Numpad9 },
			// Numpad signs
			{ 0x004E, KeyboardLayout::NumpadPlus },
			{ 0x004A, KeyboardLayout::NumpadMinus },
			{ 0x0037, KeyboardLayout::NumpadStar },
			{ 0xE035, KeyboardLayout::NumpadSlash },
			{ 0x0053, KeyboardLayout::NumpadComma },
			// Numpad system keys
			{ 0xE01C, KeyboardLayout::NumpadEnter },
			{ 0x0045, KeyboardLayout::NumpadLock }
		};

		void Subscribe();
		void Unsubscribe() noexcept;

		void RegisterDevices();
		void UnregisterDevices();
		void UpdateKeyboards();
		void Clear() noexcept;

		[[nodiscard("Weird call")]]
		std::size_t GetIndex(HANDLE keyboardHandle);
		[[nodiscard("Pure function")]]
		std::string_view GetName(HANDLE keyboardHandle);

		IInputContext* input;
		Surface::Windows::ISurfaceService* surface;

		std::vector<DeviceHandle> keyboardDevices;
		std::vector<HANDLE> keyboardHandles;
		std::vector<std::shared_ptr<Keyboard>> keyboards;
		std::size_t registeredDevices;

		std::string deviceNameTemp;
	};
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::Input::Windows
{
	KeyboardProvider::KeyboardProvider(IInputContext& input) :
		input{&input},
		surface{this->input->Application().FindService<Surface::Windows::ISurfaceService>()},
		registeredDevices{0uz}
	{
		if (!surface) [[unlikely]]
		{
			throw std::logic_error("Surface service not found.");
		}
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

		if (const auto layoutPosition = LayoutMap.find(rawInput.data.keyboard.MakeCode); layoutPosition != LayoutMap.cend())
		{
			const std::size_t index = GetIndex(rawInput.header.hDevice);
			const KeyboardLayout key = layoutPosition->second;
			const bool pressed = !(rawInput.data.keyboard.Flags & RI_KEY_BREAK);

			if (keyboards[index]->IsPressed(key) != pressed)
			{
				PONY_LOG(input->Logger(), Log::LogType::Info, "Key: {}, Down: {}.", key, pressed);

				keyboards[index]->AddEvent(KeyboardInput
				{
					.key = key,
					.pressed = pressed,
					.eventTime = eventTime,
					.cursorPosition = surface->ScreenToClient(cursorPosition)
				});
			}
		}
	}

	void KeyboardProvider::OnDeviceConnectionChanged(const HANDLE device, const bool isConnected)
	{
		if (isConnected)
		{
			const std::string_view name = GetName(device);
			const auto position = std::ranges::find_if(keyboards, [&](const std::shared_ptr<Keyboard>& keyboard) { return keyboard->Name() == name; });
			if (position != keyboards.cend())
			{
				const std::size_t index = position - keyboards.cbegin();
				keyboardHandles[index] = device;
				keyboards[index]->AddEvent(KeyboardConnection{.isConnected = true});
			}
		}
		else
		{
			if (const auto position = std::ranges::find(keyboardHandles, device); position != keyboardHandles.cend())
			{
				const std::size_t index = position - keyboardHandles.cbegin();
				keyboardHandles[index] = INVALID_HANDLE_VALUE;
				keyboards[index]->AddEvent(KeyboardConnection{.isConnected = false});
				keyboards[index]->ClearKeyStates();
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
		for (; registeredDevices < keyboardDevices.size(); ++registeredDevices)
		{
			keyboardDevices[registeredDevices] = input->RegisterDevice(DeviceData
			{
				.device = keyboards[registeredDevices],
				.layouts = Keyboard::KeyboardLayouts,
				.isConnected = true
			});
		}
	}

	void KeyboardProvider::UnregisterDevices()
	{
		for (; registeredDevices > 0uz; --registeredDevices)
		{
			input->UnregisterDevice(keyboardDevices[registeredDevices - 1uz]);
		}
	}

	void KeyboardProvider::UpdateKeyboards()
	{
		for (std::size_t i = 0uz; i < keyboards.size(); ++i)
		{
			for (const KeyboardEvent& event : keyboards[i]->Events())
			{
				std::visit(Type::Overload
				{
					[&](const KeyboardInput& keyboardInput)
					{
						const auto axis = Axis(keyboardInput.key);
						const float value = keyboardInput.pressed;
						input->AddInput(keyboardDevices[i], RawInputEvent
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
						input->Connect(keyboardDevices[i], connection.isConnected);
					}
				}, event);
			}

			keyboards[i]->ClearEvents();
		}
	}

	void KeyboardProvider::Clear() noexcept
	{
		keyboards.clear();
		keyboardDevices.clear();
		keyboardHandles.clear();
	}

	std::size_t KeyboardProvider::GetIndex(const HANDLE keyboardHandle)
	{
		const auto position = std::ranges::find(keyboardHandles, keyboardHandle);
		if (position == keyboardHandles.cend()) [[unlikely]]
		{
			keyboardDevices.push_back(DeviceHandle());
			try
			{
				keyboardHandles.push_back(keyboardHandle);
				try
				{
					keyboards.push_back(std::make_shared<Keyboard>(GetName(keyboardHandle), true));
				}
				catch (...)
				{
					keyboardHandles.pop_back();
					throw;
				}
			}
			catch (...)
			{
				keyboardDevices.pop_back();
				throw;
			}

			return keyboardHandles.size() - 1uz;
		}

		return position - keyboardHandles.cbegin();
	}

	std::string_view KeyboardProvider::GetName(const HANDLE keyboardHandle)
	{
		UINT size = 0u;
		GetRawInputDeviceInfoA(keyboardHandle, RIDI_DEVICENAME, nullptr, &size);
		if (!size) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get device name size. Error code: '0x{:X}'.", GetLastError()));
		}
		deviceNameTemp.resize(size);

		if (!GetRawInputDeviceInfoA(keyboardHandle, RIDI_DEVICENAME, deviceNameTemp.data(), &size)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get device name size. Error code: '0x{:X}'.", GetLastError()));
		}

		return deviceNameTemp;
	}
}
#endif
