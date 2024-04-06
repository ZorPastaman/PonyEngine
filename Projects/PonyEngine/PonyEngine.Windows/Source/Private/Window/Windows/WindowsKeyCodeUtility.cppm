/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Platform/Windows/Framework.h"

export module PonyEngine.Window.Windows.Implementation:WindowsKeyCodeUtility;

import <unordered_map>;

import PonyEngine.Window;

namespace PonyEngine::Window
{
	/// @brief Converts a Windows message key to a Pony Engine key code.
	/// @param lParam Key info.
	/// @return Keyboard key code.
	export [[nodiscard("Pure function")]] 
	KeyboardKeyCode ConvertToKeyCode(LPARAM lParam) noexcept;

	/// @brief Windows virtual key code to Pony Engine key code map.
	static const std::unordered_map<WORD, KeyboardKeyCode> s_windowsKeyCodeMap
	{
		// Letters
		{ 0x001E, KeyboardKeyCode::A },
		{ 0x0030, KeyboardKeyCode::B },
		{ 0x002E, KeyboardKeyCode::C },
		{ 0x0020, KeyboardKeyCode::D },
		{ 0x0012, KeyboardKeyCode::E },
		{ 0x0021, KeyboardKeyCode::F },
		{ 0x0022, KeyboardKeyCode::G },
		{ 0x0023, KeyboardKeyCode::H },
		{ 0x0017, KeyboardKeyCode::I },
		{ 0x0024, KeyboardKeyCode::J },
		{ 0x0025, KeyboardKeyCode::K },
		{ 0x0026, KeyboardKeyCode::L },
		{ 0x0032, KeyboardKeyCode::M },
		{ 0x0031, KeyboardKeyCode::N },
		{ 0x0018, KeyboardKeyCode::O },
		{ 0x0019, KeyboardKeyCode::P },
		{ 0x0010, KeyboardKeyCode::Q },
		{ 0x0013, KeyboardKeyCode::R },
		{ 0x001F, KeyboardKeyCode::S },
		{ 0x0014, KeyboardKeyCode::T },
		{ 0x0016, KeyboardKeyCode::U },
		{ 0x002F, KeyboardKeyCode::V },
		{ 0x0011, KeyboardKeyCode::W },
		{ 0x002D, KeyboardKeyCode::X },
		{ 0x0015, KeyboardKeyCode::Y },
		{ 0x002C, KeyboardKeyCode::Z },
		// Letter signs
		{ 0x0034, KeyboardKeyCode::Period },
		{ 0x0033, KeyboardKeyCode::Comma },
		{ 0x0035, KeyboardKeyCode::Slash },
		{ 0x002B, KeyboardKeyCode::Backslash },
		{ 0x0027, KeyboardKeyCode::Semicolon },
		{ 0x0028, KeyboardKeyCode::Apostrophe },
		{ 0x001A, KeyboardKeyCode::LeftBracket },
		{ 0x001B, KeyboardKeyCode::RightBracket },
		// Numbers
		{ 0x0002, KeyboardKeyCode::Number1 },
		{ 0x0003, KeyboardKeyCode::Number2 },
		{ 0x0004, KeyboardKeyCode::Number3 },
		{ 0x0005, KeyboardKeyCode::Number4 },
		{ 0x0006, KeyboardKeyCode::Number5 },
		{ 0x0007, KeyboardKeyCode::Number6 },
		{ 0x0008, KeyboardKeyCode::Number7 },
		{ 0x0009, KeyboardKeyCode::Number8 },
		{ 0x000A, KeyboardKeyCode::Number9 },
		{ 0x000B, KeyboardKeyCode::Number0 },
		// Math signs
		{ 0x000C, KeyboardKeyCode::Minus },
		{ 0x000D, KeyboardKeyCode::Equal },
		{ 0x0029, KeyboardKeyCode::Tilde },
		// Arrows
		{ 0xE048, KeyboardKeyCode::ArrowUp },
		{ 0xE050, KeyboardKeyCode::ArrowDown },
		{ 0xE04D, KeyboardKeyCode::ArrowRight },
		{ 0xE04B, KeyboardKeyCode::ArrowLeft },
		// Space
		{ 0x0039, KeyboardKeyCode::Space },
		{ 0x000E, KeyboardKeyCode::Backspace },
		// F Keys
		{ 0x003B, KeyboardKeyCode::F1 },
		{ 0x003C, KeyboardKeyCode::F2 },
		{ 0x003D, KeyboardKeyCode::F3 },
		{ 0x003E, KeyboardKeyCode::F4 },
		{ 0x003F, KeyboardKeyCode::F5 },
		{ 0x0040, KeyboardKeyCode::F6 },
		{ 0x0041, KeyboardKeyCode::F7 },
		{ 0x0042, KeyboardKeyCode::F8 },
		{ 0x0043, KeyboardKeyCode::F9 },
		{ 0x0044, KeyboardKeyCode::F10 },
		{ 0x0057, KeyboardKeyCode::F11 },
		{ 0x0058, KeyboardKeyCode::F12 },
		// System keys
		{ 0x0001, KeyboardKeyCode::Escape },
		{ 0x000F, KeyboardKeyCode::Tab },
		{ 0x003A, KeyboardKeyCode::CapsLock },
		{ 0x002A, KeyboardKeyCode::LeftShift },
		{ 0x0036, KeyboardKeyCode::RightShift },
		{ 0x001D, KeyboardKeyCode::LeftCtrl },
		{ 0xE01D, KeyboardKeyCode::RightCtrl },
		{ 0x0038, KeyboardKeyCode::LeftAlt },
		{ 0xE038, KeyboardKeyCode::RightAlt },
		{ 0x001C, KeyboardKeyCode::Enter },
		{ 0xE052, KeyboardKeyCode::Insert },
		{ 0xE053, KeyboardKeyCode::Delete },
		{ 0xE047, KeyboardKeyCode::Home },
		{ 0xE04F, KeyboardKeyCode::End },
		{ 0xE049, KeyboardKeyCode::PageUp },
		{ 0xE051, KeyboardKeyCode::PageDown },
		// Numpad numbers
		{ 0x0052, KeyboardKeyCode::Numpad0 },
		{ 0x004F, KeyboardKeyCode::Numpad1 },
		{ 0x0050, KeyboardKeyCode::Numpad2 },
		{ 0x0051, KeyboardKeyCode::Numpad3 },
		{ 0x004B, KeyboardKeyCode::Numpad4 },
		{ 0x004C, KeyboardKeyCode::Numpad5 },
		{ 0x004D, KeyboardKeyCode::Numpad6 },
		{ 0x0047, KeyboardKeyCode::Numpad7 },
		{ 0x0048, KeyboardKeyCode::Numpad8 },
		{ 0x0049, KeyboardKeyCode::Numpad9 },
		// Numpad signs
		{ 0x004E, KeyboardKeyCode::NumpadPlus },
		{ 0x004A, KeyboardKeyCode::NumpadMinus },
		{ 0x0037, KeyboardKeyCode::NumpadStar },
		{ 0xE035, KeyboardKeyCode::NumpadSlash },
		{ 0x0053, KeyboardKeyCode::NumpadPeriod },
		// Numpad system keys
		{ 0xE01C, KeyboardKeyCode::NumpadEnter }
	};

	KeyboardKeyCode ConvertToKeyCode(const LPARAM lParam) noexcept
	{
		const WORD keyFlags = HIWORD(lParam);
		const WORD scanCode = LOBYTE(keyFlags);
		const WORD extended = (keyFlags & KF_EXTENDED) == KF_EXTENDED;
		const WORD extendedPrefix = extended << WORD{15} | extended << WORD{14} | extended << WORD{13}; // 0xE000 if it's extended; 0 otherwise.
		const WORD key = scanCode | extendedPrefix;
		const std::unordered_map<WORD, KeyboardKeyCode>::const_iterator pair = s_windowsKeyCodeMap.find(key);

		return pair != s_windowsKeyCodeMap.cend() ? pair->second : KeyboardKeyCode::None;
	}
}
