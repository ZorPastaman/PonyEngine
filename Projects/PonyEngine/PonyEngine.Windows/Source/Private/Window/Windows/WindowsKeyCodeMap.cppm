/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Implementation:WindowsKeyCodeMap;

import <unordered_map>;

import <windows.h>;

import PonyEngine.Window;

namespace PonyEngine::Window
{
	/// @brief Windows virtual key code to Pony Engine key code map.
	export const std::unordered_map<WPARAM, KeyboardKeyCode> WindowsKeyCodeMap
	{
		// Letters
		{ 'A', KeyboardKeyCode::A },
		{ 'B', KeyboardKeyCode::B },
		{ 'C', KeyboardKeyCode::C },
		{ 'D', KeyboardKeyCode::D },
		{ 'E', KeyboardKeyCode::E },
		{ 'F', KeyboardKeyCode::F },
		{ 'G', KeyboardKeyCode::G },
		{ 'H', KeyboardKeyCode::H },
		{ 'I', KeyboardKeyCode::I },
		{ 'J', KeyboardKeyCode::J },
		{ 'K', KeyboardKeyCode::K },
		{ 'L', KeyboardKeyCode::L },
		{ 'M', KeyboardKeyCode::M },
		{ 'N', KeyboardKeyCode::N },
		{ 'O', KeyboardKeyCode::O },
		{ 'P', KeyboardKeyCode::P },
		{ 'Q', KeyboardKeyCode::Q },
		{ 'R', KeyboardKeyCode::R },
		{ 'S', KeyboardKeyCode::S },
		{ 'T', KeyboardKeyCode::T },
		{ 'U', KeyboardKeyCode::U },
		{ 'V', KeyboardKeyCode::V },
		{ 'W', KeyboardKeyCode::W },
		{ 'X', KeyboardKeyCode::X },
		{ 'Y', KeyboardKeyCode::Y },
		{ 'Z', KeyboardKeyCode::Z },
		// Letter signs
		{ VK_OEM_PERIOD, KeyboardKeyCode::Period },
		{ VK_OEM_COMMA, KeyboardKeyCode::Comma },
		{ VK_OEM_2, KeyboardKeyCode::Slash },
		{ VK_OEM_5, KeyboardKeyCode::Backslash },
		{ VK_OEM_1, KeyboardKeyCode::Semicolon },
		{ VK_OEM_7, KeyboardKeyCode::Apostrophe },
		{ VK_OEM_4, KeyboardKeyCode::LeftBracket },
		{ VK_OEM_6, KeyboardKeyCode::RightBracket },
		// Numbers
		{ 0x30 + 1, KeyboardKeyCode::Number1 },
		{ 0x30 + 2, KeyboardKeyCode::Number2 },
		{ 0x30 + 3, KeyboardKeyCode::Number3 },
		{ 0x30 + 4, KeyboardKeyCode::Number4 },
		{ 0x30 + 5, KeyboardKeyCode::Number5 },
		{ 0x30 + 6, KeyboardKeyCode::Number6 },
		{ 0x30 + 7, KeyboardKeyCode::Number7 },
		{ 0x30 + 8, KeyboardKeyCode::Number8 },
		{ 0x30 + 9, KeyboardKeyCode::Number9 },
		{ 0x30 + 0, KeyboardKeyCode::Number0 },
		// Math signs
		{ VK_OEM_MINUS, KeyboardKeyCode::Minus },
		{ VK_OEM_PLUS, KeyboardKeyCode::Equal },
		{ VK_OEM_3, KeyboardKeyCode::Tilde },
		// Arrows
		{ VK_UP, KeyboardKeyCode::ArrowUp },
		{ VK_DOWN, KeyboardKeyCode::ArrowDown },
		{ VK_RIGHT, KeyboardKeyCode::ArrowRight },
		{ VK_LEFT, KeyboardKeyCode::ArrowLeft },
		// Space
		{ VK_SPACE, KeyboardKeyCode::Space },
		{ VK_BACK, KeyboardKeyCode::Backspace },
		// F Keys
		{ VK_F1, KeyboardKeyCode::F1 },
		{ VK_F2, KeyboardKeyCode::F2 },
		{ VK_F3, KeyboardKeyCode::F3 },
		{ VK_F4, KeyboardKeyCode::F4 },
		{ VK_F5, KeyboardKeyCode::F5 },
		{ VK_F6, KeyboardKeyCode::F6 },
		{ VK_F7, KeyboardKeyCode::F7 },
		{ VK_F8, KeyboardKeyCode::F8 },
		{ VK_F9, KeyboardKeyCode::F9 },
		{ VK_F10, KeyboardKeyCode::F10 },
		{ VK_F11, KeyboardKeyCode::F11 },
		{ VK_F12, KeyboardKeyCode::F12 },
		// System keys
		{ VK_ESCAPE, KeyboardKeyCode::Escape },
		{ VK_TAB, KeyboardKeyCode::Tab },
		{ VK_CAPITAL, KeyboardKeyCode::CapsLock },
		{ VK_LSHIFT, KeyboardKeyCode::LeftShift },
		{ VK_RSHIFT, KeyboardKeyCode::RightShift },
		{ VK_LCONTROL, KeyboardKeyCode::LeftCtrl },
		{ VK_RCONTROL, KeyboardKeyCode::RightCtrl },
		{ VK_LMENU, KeyboardKeyCode::LeftAlt },
		{ VK_RMENU, KeyboardKeyCode::RightAlt },
		{ VK_RETURN, KeyboardKeyCode::Enter },
		{ VK_INSERT, KeyboardKeyCode::Insert },
		{ VK_DELETE, KeyboardKeyCode::Delete },
		{ VK_HOME, KeyboardKeyCode::Home },
		{ VK_END, KeyboardKeyCode::End },
		{ VK_PRIOR, KeyboardKeyCode::PageUp },
		{ VK_NEXT, KeyboardKeyCode::PageDown },
		// Numpad numbers
		{ VK_NUMPAD0, KeyboardKeyCode::Numpad0 },
		{ VK_NUMPAD1, KeyboardKeyCode::Numpad1 },
		{ VK_NUMPAD2, KeyboardKeyCode::Numpad2 },
		{ VK_NUMPAD3, KeyboardKeyCode::Numpad3 },
		{ VK_NUMPAD4, KeyboardKeyCode::Numpad4 },
		{ VK_NUMPAD5, KeyboardKeyCode::Numpad5 },
		{ VK_NUMPAD6, KeyboardKeyCode::Numpad6 },
		{ VK_NUMPAD7, KeyboardKeyCode::Numpad7 },
		{ VK_NUMPAD8, KeyboardKeyCode::Numpad8 },
		{ VK_NUMPAD9, KeyboardKeyCode::Numpad9 },
		// Numpad signs
		{ VK_ADD, KeyboardKeyCode::NumpadPlus },
		{ VK_SUBTRACT, KeyboardKeyCode::NumpadMinus },
		{ VK_MULTIPLY, KeyboardKeyCode::NumpadStar },
		{ VK_DIVIDE, KeyboardKeyCode::NumpadSlash },
		{ VK_DECIMAL, KeyboardKeyCode::NumpadComma }
	};
}
