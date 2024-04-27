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

export namespace PonyEngine::Window
{
	/// @brief Converts a Windows message key to a Pony Engine key code.
	/// @param lParam Key info.
	/// @return Keyboard key code.
	[[nodiscard("Pure function")]] 
	KeyboardKeyCode ConvertToKeyCode(LPARAM lParam) noexcept;
}

namespace PonyEngine::Window
{
	/// @brief Windows virtual key code to Pony Engine key code map.
	const std::unordered_map<WORD, KeyboardKeyCode> WindowsKeyCodeMap
	{
		// Letters
		{ WORD{0x001E}, KeyboardKeyCode::A },
		{ WORD{0x0030}, KeyboardKeyCode::B },
		{ WORD{0x002E}, KeyboardKeyCode::C },
		{ WORD{0x0020}, KeyboardKeyCode::D },
		{ WORD{0x0012}, KeyboardKeyCode::E },
		{ WORD{0x0021}, KeyboardKeyCode::F },
		{ WORD{0x0022}, KeyboardKeyCode::G },
		{ WORD{0x0023}, KeyboardKeyCode::H },
		{ WORD{0x0017}, KeyboardKeyCode::I },
		{ WORD{0x0024}, KeyboardKeyCode::J },
		{ WORD{0x0025}, KeyboardKeyCode::K },
		{ WORD{0x0026}, KeyboardKeyCode::L },
		{ WORD{0x0032}, KeyboardKeyCode::M },
		{ WORD{0x0031}, KeyboardKeyCode::N },
		{ WORD{0x0018}, KeyboardKeyCode::O },
		{ WORD{0x0019}, KeyboardKeyCode::P },
		{ WORD{0x0010}, KeyboardKeyCode::Q },
		{ WORD{0x0013}, KeyboardKeyCode::R },
		{ WORD{0x001F}, KeyboardKeyCode::S },
		{ WORD{0x0014}, KeyboardKeyCode::T },
		{ WORD{0x0016}, KeyboardKeyCode::U },
		{ WORD{0x002F}, KeyboardKeyCode::V },
		{ WORD{0x0011}, KeyboardKeyCode::W },
		{ WORD{0x002D}, KeyboardKeyCode::X },
		{ WORD{0x0015}, KeyboardKeyCode::Y },
		{ WORD{0x002C}, KeyboardKeyCode::Z },
		// Letter signs
		{ WORD{0x0034}, KeyboardKeyCode::Period },
		{ WORD{0x0033}, KeyboardKeyCode::Comma },
		{ WORD{0x0035}, KeyboardKeyCode::Slash },
		{ WORD{0x002B}, KeyboardKeyCode::Backslash },
		{ WORD{0x0027}, KeyboardKeyCode::Semicolon },
		{ WORD{0x0028}, KeyboardKeyCode::Apostrophe },
		{ WORD{0x001A}, KeyboardKeyCode::LeftBracket },
		{ WORD{0x001B}, KeyboardKeyCode::RightBracket },
		// Numbers
		{ WORD{0x0002}, KeyboardKeyCode::Number1 },
		{ WORD{0x0003}, KeyboardKeyCode::Number2 },
		{ WORD{0x0004}, KeyboardKeyCode::Number3 },
		{ WORD{0x0005}, KeyboardKeyCode::Number4 },
		{ WORD{0x0006}, KeyboardKeyCode::Number5 },
		{ WORD{0x0007}, KeyboardKeyCode::Number6 },
		{ WORD{0x0008}, KeyboardKeyCode::Number7 },
		{ WORD{0x0009}, KeyboardKeyCode::Number8 },
		{ WORD{0x000A}, KeyboardKeyCode::Number9 },
		{ WORD{0x000B}, KeyboardKeyCode::Number0 },
		// Math signs
		{ WORD{0x000C}, KeyboardKeyCode::Minus },
		{ WORD{0x000D}, KeyboardKeyCode::Equal },
		{ WORD{0x0029}, KeyboardKeyCode::Tilde },
		// Arrows
		{ WORD{0xE048}, KeyboardKeyCode::ArrowUp },
		{ WORD{0xE050}, KeyboardKeyCode::ArrowDown },
		{ WORD{0xE04D}, KeyboardKeyCode::ArrowRight },
		{ WORD{0xE04B}, KeyboardKeyCode::ArrowLeft },
		// Space
		{ WORD{0x0039}, KeyboardKeyCode::Space },
		{ WORD{0x000E}, KeyboardKeyCode::Backspace },
		// F Keys
		{ WORD{0x003B}, KeyboardKeyCode::F1 },
		{ WORD{0x003C}, KeyboardKeyCode::F2 },
		{ WORD{0x003D}, KeyboardKeyCode::F3 },
		{ WORD{0x003E}, KeyboardKeyCode::F4 },
		{ WORD{0x003F}, KeyboardKeyCode::F5 },
		{ WORD{0x0040}, KeyboardKeyCode::F6 },
		{ WORD{0x0041}, KeyboardKeyCode::F7 },
		{ WORD{0x0042}, KeyboardKeyCode::F8 },
		{ WORD{0x0043}, KeyboardKeyCode::F9 },
		{ WORD{0x0044}, KeyboardKeyCode::F10 },
		{ WORD{0x0057}, KeyboardKeyCode::F11 },
		{ WORD{0x0058}, KeyboardKeyCode::F12 },
		// System keys
		{ WORD{0x0001}, KeyboardKeyCode::Escape },
		{ WORD{0x000F}, KeyboardKeyCode::Tab },
		{ WORD{0x003A}, KeyboardKeyCode::CapsLock },
		{ WORD{0x002A}, KeyboardKeyCode::LeftShift },
		{ WORD{0x0036}, KeyboardKeyCode::RightShift },
		{ WORD{0x001D}, KeyboardKeyCode::LeftCtrl },
		{ WORD{0xE01D}, KeyboardKeyCode::RightCtrl },
		{ WORD{0x0038}, KeyboardKeyCode::LeftAlt },
		{ WORD{0xE038}, KeyboardKeyCode::RightAlt },
		{ WORD{0x001C}, KeyboardKeyCode::Enter },
		{ WORD{0xE052}, KeyboardKeyCode::Insert },
		{ WORD{0xE053}, KeyboardKeyCode::Delete },
		{ WORD{0xE047}, KeyboardKeyCode::Home },
		{ WORD{0xE04F}, KeyboardKeyCode::End },
		{ WORD{0xE049}, KeyboardKeyCode::PageUp },
		{ WORD{0xE051}, KeyboardKeyCode::PageDown },
		// Numpad numbers
		{ WORD{0x0052}, KeyboardKeyCode::Numpad0 },
		{ WORD{0x004F}, KeyboardKeyCode::Numpad1 },
		{ WORD{0x0050}, KeyboardKeyCode::Numpad2 },
		{ WORD{0x0051}, KeyboardKeyCode::Numpad3 },
		{ WORD{0x004B}, KeyboardKeyCode::Numpad4 },
		{ WORD{0x004C}, KeyboardKeyCode::Numpad5 },
		{ WORD{0x004D}, KeyboardKeyCode::Numpad6 },
		{ WORD{0x0047}, KeyboardKeyCode::Numpad7 },
		{ WORD{0x0048}, KeyboardKeyCode::Numpad8 },
		{ WORD{0x0049}, KeyboardKeyCode::Numpad9 },
		// Numpad signs
		{ WORD{0x004E}, KeyboardKeyCode::NumpadPlus },
		{ WORD{0x004A}, KeyboardKeyCode::NumpadMinus },
		{ WORD{0x0037}, KeyboardKeyCode::NumpadStar },
		{ WORD{0xE035}, KeyboardKeyCode::NumpadSlash },
		{ WORD{0x0053}, KeyboardKeyCode::NumpadPeriod },
		// Numpad system keys
		{ WORD{0xE01C}, KeyboardKeyCode::NumpadEnter }
	};

	KeyboardKeyCode ConvertToKeyCode(const LPARAM lParam) noexcept
	{
		const WORD keyFlags = HIWORD(lParam);
		const WORD scanCode = LOBYTE(keyFlags);
		const WORD extended = (keyFlags & KF_EXTENDED) == KF_EXTENDED;
		const WORD extendedPrefix = extended << WORD{15} | extended << WORD{14} | extended << WORD{13}; // 0xE000 if it's extended; 0 otherwise.
		const WORD key = scanCode | extendedPrefix;
		const auto pair = WindowsKeyCodeMap.find(key);

		return pair != WindowsKeyCodeMap.cend() ? pair->second : KeyboardKeyCode::None;
	}
}
