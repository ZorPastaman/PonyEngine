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

export module PonyEngine.Input.Keyboard.Impl:Windows.KeyboardLayoutMap;

import std;

import PonyEngine.RawInput;

export namespace PonyEngine::Input::Windows
{
	const std::unordered_map<WORD, KeyboardLayout> KeyboardLayoutMap
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
		{ 0x0046, KeyboardLayout::ScrollLock },
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
		{ 0x0053, KeyboardLayout::NumpadPeriod },
		// Numpad system keys
		{ 0xE01C, KeyboardLayout::NumpadEnter }
	};
}
