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

#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Input.Windows.Detail:WindowsKeyboardDevice;

import <array>;
import <unordered_map>;

import PonyDebug.Log;

import PonyEngine.Input.Windows;
import PonyEngine.Window.Windows;

export namespace PonyEngine::Input
{
	/// @brief Windows keyboard device.
	class WindowsKeyboardDevice final : public InputDevice, private Window::IWindowsMessageObserver
	{
	public:
		/// @brief Creates a @p WindowsKeyboardDevice.
		/// @param inputSystem Input system context.
		/// @param deviceParams Input device parameters.
		/// @param keyboardParams Keyboard parameters.
		[[nodiscard("Pure constructor")]]
		WindowsKeyboardDevice(IInputSystemContext& inputSystem, const InputDeviceParams& deviceParams, const WindowsKeyboardDeviceParams& keyboardParams);
		WindowsKeyboardDevice(const WindowsKeyboardDevice&) = delete;
		WindowsKeyboardDevice(WindowsKeyboardDevice&&) = delete;

		virtual ~WindowsKeyboardDevice() noexcept override = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		WindowsKeyboardDevice& operator =(const WindowsKeyboardDevice&) = delete;
		WindowsKeyboardDevice& operator =(WindowsKeyboardDevice&&) = delete;

	private:
		virtual void Observe(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	};
}

namespace PonyEngine::Input
{
	/// @brief Virtual key code to Pony Engine key code map.
	static const std::unordered_map<WORD, InputCode> KeyCodeMap
	{
		// Letters
		{ WORD{0x001E}, InputCode::A },
		{ WORD{0x0030}, InputCode::B },
		{ WORD{0x002E}, InputCode::C },
		{ WORD{0x0020}, InputCode::D },
		{ WORD{0x0012}, InputCode::E },
		{ WORD{0x0021}, InputCode::F },
		{ WORD{0x0022}, InputCode::G },
		{ WORD{0x0023}, InputCode::H },
		{ WORD{0x0017}, InputCode::I },
		{ WORD{0x0024}, InputCode::J },
		{ WORD{0x0025}, InputCode::K },
		{ WORD{0x0026}, InputCode::L },
		{ WORD{0x0032}, InputCode::M },
		{ WORD{0x0031}, InputCode::N },
		{ WORD{0x0018}, InputCode::O },
		{ WORD{0x0019}, InputCode::P },
		{ WORD{0x0010}, InputCode::Q },
		{ WORD{0x0013}, InputCode::R },
		{ WORD{0x001F}, InputCode::S },
		{ WORD{0x0014}, InputCode::T },
		{ WORD{0x0016}, InputCode::U },
		{ WORD{0x002F}, InputCode::V },
		{ WORD{0x0011}, InputCode::W },
		{ WORD{0x002D}, InputCode::X },
		{ WORD{0x0015}, InputCode::Y },
		{ WORD{0x002C}, InputCode::Z },
		// Letter signs
		{ WORD{0x0034}, InputCode::Period },
		{ WORD{0x0033}, InputCode::Comma },
		{ WORD{0x0035}, InputCode::Slash },
		{ WORD{0x002B}, InputCode::Backslash },
		{ WORD{0x0027}, InputCode::Semicolon },
		{ WORD{0x0028}, InputCode::Apostrophe },
		{ WORD{0x001A}, InputCode::LeftBracket },
		{ WORD{0x001B}, InputCode::RightBracket },
		// Numbers
		{ WORD{0x0002}, InputCode::Number1 },
		{ WORD{0x0003}, InputCode::Number2 },
		{ WORD{0x0004}, InputCode::Number3 },
		{ WORD{0x0005}, InputCode::Number4 },
		{ WORD{0x0006}, InputCode::Number5 },
		{ WORD{0x0007}, InputCode::Number6 },
		{ WORD{0x0008}, InputCode::Number7 },
		{ WORD{0x0009}, InputCode::Number8 },
		{ WORD{0x000A}, InputCode::Number9 },
		{ WORD{0x000B}, InputCode::Number0 },
		// Math signs
		{ WORD{0x000C}, InputCode::Minus },
		{ WORD{0x000D}, InputCode::Equal },
		{ WORD{0x0029}, InputCode::Tilde },
		// Arrows
		{ WORD{0xE048}, InputCode::ArrowUp },
		{ WORD{0xE050}, InputCode::ArrowDown },
		{ WORD{0xE04D}, InputCode::ArrowRight },
		{ WORD{0xE04B}, InputCode::ArrowLeft },
		// Space
		{ WORD{0x0039}, InputCode::Space },
		{ WORD{0x000E}, InputCode::Backspace },
		// F Keys
		{ WORD{0x003B}, InputCode::F1 },
		{ WORD{0x003C}, InputCode::F2 },
		{ WORD{0x003D}, InputCode::F3 },
		{ WORD{0x003E}, InputCode::F4 },
		{ WORD{0x003F}, InputCode::F5 },
		{ WORD{0x0040}, InputCode::F6 },
		{ WORD{0x0041}, InputCode::F7 },
		{ WORD{0x0042}, InputCode::F8 },
		{ WORD{0x0043}, InputCode::F9 },
		{ WORD{0x0044}, InputCode::F10 },
		{ WORD{0x0057}, InputCode::F11 },
		{ WORD{0x0058}, InputCode::F12 },
		// System keys
		{ WORD{0x0001}, InputCode::Escape },
		{ WORD{0x000F}, InputCode::Tab },
		{ WORD{0x003A}, InputCode::CapsLock },
		{ WORD{0x002A}, InputCode::LeftShift },
		{ WORD{0x0036}, InputCode::RightShift },
		{ WORD{0x001D}, InputCode::LeftCtrl },
		{ WORD{0xE01D}, InputCode::RightCtrl },
		{ WORD{0x0038}, InputCode::LeftAlt },
		{ WORD{0xE038}, InputCode::RightAlt },
		{ WORD{0x001C}, InputCode::Enter },
		{ WORD{0xE052}, InputCode::Insert },
		{ WORD{0xE053}, InputCode::Delete },
		{ WORD{0xE047}, InputCode::Home },
		{ WORD{0xE04F}, InputCode::End },
		{ WORD{0xE049}, InputCode::PageUp },
		{ WORD{0xE051}, InputCode::PageDown },
		// Numpad numbers
		{ WORD{0x0052}, InputCode::Numpad0 },
		{ WORD{0x004F}, InputCode::Numpad1 },
		{ WORD{0x0050}, InputCode::Numpad2 },
		{ WORD{0x0051}, InputCode::Numpad3 },
		{ WORD{0x004B}, InputCode::Numpad4 },
		{ WORD{0x004C}, InputCode::Numpad5 },
		{ WORD{0x004D}, InputCode::Numpad6 },
		{ WORD{0x0047}, InputCode::Numpad7 },
		{ WORD{0x0048}, InputCode::Numpad8 },
		{ WORD{0x0049}, InputCode::Numpad9 },
		// Numpad signs
		{ WORD{0x004E}, InputCode::NumpadPlus },
		{ WORD{0x004A}, InputCode::NumpadMinus },
		{ WORD{0x0037}, InputCode::NumpadStar },
		{ WORD{0xE035}, InputCode::NumpadSlash },
		{ WORD{0x0053}, InputCode::NumpadPeriod },
		// Numpad system keys
		{ WORD{0xE01C}, InputCode::NumpadEnter }
	};

	WindowsKeyboardDevice::WindowsKeyboardDevice(IInputSystemContext& inputSystem, const InputDeviceParams& deviceParams, const WindowsKeyboardDeviceParams&) :
		InputDevice(inputSystem, deviceParams)
	{
	}

	void WindowsKeyboardDevice::Begin()
	{
		if (const auto windowSystem = InputSystem().SystemManager().FindSystem<Window::IWindowsWindowSystem>())
		{
			windowSystem->MessagePump().AddMessageObserver(*this, std::array<UINT, 4> { WM_KEYDOWN, WM_KEYUP, WM_SYSKEYDOWN, WM_SYSKEYUP });
		}
		else
		{
			PONY_LOG(InputSystem().Logger(), PonyDebug::Log::LogType::Warning, "Couldn't find Windows window system. Keyboard input won't work.");
		}
	}

	void WindowsKeyboardDevice::End()
	{
		if (const auto windowSystem = InputSystem().SystemManager().FindSystem<Window::IWindowsWindowSystem>())
		{
			windowSystem->MessagePump().RemoveMessageObserver(*this);
		}
	}

	void WindowsKeyboardDevice::Tick()
	{
	}

	void WindowsKeyboardDevice::Observe(const UINT uMsg, const WPARAM, const LPARAM lParam)
	{
		assert (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP || uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP && "The incorrect input message has been received.");

		const bool inputValue = uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN;
		if (inputValue == ((lParam & (1 << 30)) != 0)) // If the previous input is the same.
		{
			return;
		}

		const WORD keyFlags = HIWORD(lParam);
		const WORD scanCode = LOBYTE(keyFlags);
		const WORD extended = keyFlags & KF_EXTENDED;
		const WORD extendedPrefix = extended << WORD{7} | extended << WORD{6} | extended << WORD{5}; // 0xE000 if it's extended; 0 otherwise.
		const WORD key = scanCode | extendedPrefix;
		if (const auto keyCodeMapPosition = KeyCodeMap.find(key); keyCodeMapPosition != KeyCodeMap.cend())
		{
			InputSystem().AddInputEvent(InputEvent{.inputCode = keyCodeMapPosition->second, .value = static_cast<float>(inputValue)});
		}
	}
}
