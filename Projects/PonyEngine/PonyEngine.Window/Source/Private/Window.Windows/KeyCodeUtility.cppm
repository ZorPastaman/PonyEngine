/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Window.Windows.Implementation:KeyCodeUtility;

import <unordered_map>;

import PonyEngine.Input;

export namespace PonyEngine::Window
{
	/// @brief Converts a Windows message key to a Pony Engine key code.
	/// @param lParam Key info.
	/// @return Keyboard key code.
	[[nodiscard("Pure function")]]
	Input::KeyboardKeyCode ConvertToKeyCode(LPARAM lParam) noexcept;
}

namespace PonyEngine::Window
{
	/// @brief Virtual key code to Pony Engine key code map.
	const std::unordered_map<WORD, Input::KeyboardKeyCode> KeyCodeMap
	{
		// Letters
		{ WORD{0x001E}, Input::KeyboardKeyCode::A },
		{ WORD{0x0030}, Input::KeyboardKeyCode::B },
		{ WORD{0x002E}, Input::KeyboardKeyCode::C },
		{ WORD{0x0020}, Input::KeyboardKeyCode::D },
		{ WORD{0x0012}, Input::KeyboardKeyCode::E },
		{ WORD{0x0021}, Input::KeyboardKeyCode::F },
		{ WORD{0x0022}, Input::KeyboardKeyCode::G },
		{ WORD{0x0023}, Input::KeyboardKeyCode::H },
		{ WORD{0x0017}, Input::KeyboardKeyCode::I },
		{ WORD{0x0024}, Input::KeyboardKeyCode::J },
		{ WORD{0x0025}, Input::KeyboardKeyCode::K },
		{ WORD{0x0026}, Input::KeyboardKeyCode::L },
		{ WORD{0x0032}, Input::KeyboardKeyCode::M },
		{ WORD{0x0031}, Input::KeyboardKeyCode::N },
		{ WORD{0x0018}, Input::KeyboardKeyCode::O },
		{ WORD{0x0019}, Input::KeyboardKeyCode::P },
		{ WORD{0x0010}, Input::KeyboardKeyCode::Q },
		{ WORD{0x0013}, Input::KeyboardKeyCode::R },
		{ WORD{0x001F}, Input::KeyboardKeyCode::S },
		{ WORD{0x0014}, Input::KeyboardKeyCode::T },
		{ WORD{0x0016}, Input::KeyboardKeyCode::U },
		{ WORD{0x002F}, Input::KeyboardKeyCode::V },
		{ WORD{0x0011}, Input::KeyboardKeyCode::W },
		{ WORD{0x002D}, Input::KeyboardKeyCode::X },
		{ WORD{0x0015}, Input::KeyboardKeyCode::Y },
		{ WORD{0x002C}, Input::KeyboardKeyCode::Z },
		// Letter signs
		{ WORD{0x0034}, Input::KeyboardKeyCode::Period },
		{ WORD{0x0033}, Input::KeyboardKeyCode::Comma },
		{ WORD{0x0035}, Input::KeyboardKeyCode::Slash },
		{ WORD{0x002B}, Input::KeyboardKeyCode::Backslash },
		{ WORD{0x0027}, Input::KeyboardKeyCode::Semicolon },
		{ WORD{0x0028}, Input::KeyboardKeyCode::Apostrophe },
		{ WORD{0x001A}, Input::KeyboardKeyCode::LeftBracket },
		{ WORD{0x001B}, Input::KeyboardKeyCode::RightBracket },
		// Numbers
		{ WORD{0x0002}, Input::KeyboardKeyCode::Number1 },
		{ WORD{0x0003}, Input::KeyboardKeyCode::Number2 },
		{ WORD{0x0004}, Input::KeyboardKeyCode::Number3 },
		{ WORD{0x0005}, Input::KeyboardKeyCode::Number4 },
		{ WORD{0x0006}, Input::KeyboardKeyCode::Number5 },
		{ WORD{0x0007}, Input::KeyboardKeyCode::Number6 },
		{ WORD{0x0008}, Input::KeyboardKeyCode::Number7 },
		{ WORD{0x0009}, Input::KeyboardKeyCode::Number8 },
		{ WORD{0x000A}, Input::KeyboardKeyCode::Number9 },
		{ WORD{0x000B}, Input::KeyboardKeyCode::Number0 },
		// Math signs
		{ WORD{0x000C}, Input::KeyboardKeyCode::Minus },
		{ WORD{0x000D}, Input::KeyboardKeyCode::Equal },
		{ WORD{0x0029}, Input::KeyboardKeyCode::Tilde },
		// Arrows
		{ WORD{0xE048}, Input::KeyboardKeyCode::ArrowUp },
		{ WORD{0xE050}, Input::KeyboardKeyCode::ArrowDown },
		{ WORD{0xE04D}, Input::KeyboardKeyCode::ArrowRight },
		{ WORD{0xE04B}, Input::KeyboardKeyCode::ArrowLeft },
		// Space
		{ WORD{0x0039}, Input::KeyboardKeyCode::Space },
		{ WORD{0x000E}, Input::KeyboardKeyCode::Backspace },
		// F Keys
		{ WORD{0x003B}, Input::KeyboardKeyCode::F1 },
		{ WORD{0x003C}, Input::KeyboardKeyCode::F2 },
		{ WORD{0x003D}, Input::KeyboardKeyCode::F3 },
		{ WORD{0x003E}, Input::KeyboardKeyCode::F4 },
		{ WORD{0x003F}, Input::KeyboardKeyCode::F5 },
		{ WORD{0x0040}, Input::KeyboardKeyCode::F6 },
		{ WORD{0x0041}, Input::KeyboardKeyCode::F7 },
		{ WORD{0x0042}, Input::KeyboardKeyCode::F8 },
		{ WORD{0x0043}, Input::KeyboardKeyCode::F9 },
		{ WORD{0x0044}, Input::KeyboardKeyCode::F10 },
		{ WORD{0x0057}, Input::KeyboardKeyCode::F11 },
		{ WORD{0x0058}, Input::KeyboardKeyCode::F12 },
		// System keys
		{ WORD{0x0001}, Input::KeyboardKeyCode::Escape },
		{ WORD{0x000F}, Input::KeyboardKeyCode::Tab },
		{ WORD{0x003A}, Input::KeyboardKeyCode::CapsLock },
		{ WORD{0x002A}, Input::KeyboardKeyCode::LeftShift },
		{ WORD{0x0036}, Input::KeyboardKeyCode::RightShift },
		{ WORD{0x001D}, Input::KeyboardKeyCode::LeftCtrl },
		{ WORD{0xE01D}, Input::KeyboardKeyCode::RightCtrl },
		{ WORD{0x0038}, Input::KeyboardKeyCode::LeftAlt },
		{ WORD{0xE038}, Input::KeyboardKeyCode::RightAlt },
		{ WORD{0x001C}, Input::KeyboardKeyCode::Enter },
		{ WORD{0xE052}, Input::KeyboardKeyCode::Insert },
		{ WORD{0xE053}, Input::KeyboardKeyCode::Delete },
		{ WORD{0xE047}, Input::KeyboardKeyCode::Home },
		{ WORD{0xE04F}, Input::KeyboardKeyCode::End },
		{ WORD{0xE049}, Input::KeyboardKeyCode::PageUp },
		{ WORD{0xE051}, Input::KeyboardKeyCode::PageDown },
		// Numpad numbers
		{ WORD{0x0052}, Input::KeyboardKeyCode::Numpad0 },
		{ WORD{0x004F}, Input::KeyboardKeyCode::Numpad1 },
		{ WORD{0x0050}, Input::KeyboardKeyCode::Numpad2 },
		{ WORD{0x0051}, Input::KeyboardKeyCode::Numpad3 },
		{ WORD{0x004B}, Input::KeyboardKeyCode::Numpad4 },
		{ WORD{0x004C}, Input::KeyboardKeyCode::Numpad5 },
		{ WORD{0x004D}, Input::KeyboardKeyCode::Numpad6 },
		{ WORD{0x0047}, Input::KeyboardKeyCode::Numpad7 },
		{ WORD{0x0048}, Input::KeyboardKeyCode::Numpad8 },
		{ WORD{0x0049}, Input::KeyboardKeyCode::Numpad9 },
		// Numpad signs
		{ WORD{0x004E}, Input::KeyboardKeyCode::NumpadPlus },
		{ WORD{0x004A}, Input::KeyboardKeyCode::NumpadMinus },
		{ WORD{0x0037}, Input::KeyboardKeyCode::NumpadStar },
		{ WORD{0xE035}, Input::KeyboardKeyCode::NumpadSlash },
		{ WORD{0x0053}, Input::KeyboardKeyCode::NumpadPeriod },
		// Numpad system keys
		{ WORD{0xE01C}, Input::KeyboardKeyCode::NumpadEnter }
	};

	Input::KeyboardKeyCode ConvertToKeyCode(const LPARAM lParam) noexcept
	{
		const WORD keyFlags = HIWORD(lParam);
		const WORD scanCode = LOBYTE(keyFlags);
		const WORD extended = keyFlags & KF_EXTENDED;
		const WORD extendedPrefix = extended << WORD{7} | extended << WORD{6} | extended << WORD{5}; // 0xE000 if it's extended; 0 otherwise.
		const WORD key = scanCode | extendedPrefix;

		if (const auto pair = KeyCodeMap.find(key); pair != KeyCodeMap.cend()) [[likely]]
		{
			return pair->second;
		}

		return Input::KeyboardKeyCode::None;
	}
}
