/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Implementation:WindowsKeyCodeToKeyboardKeyCode;

import <unordered_map>;
import <windows.h>;

import PonyEngine.Window;

namespace PonyEngine::Window
{
	export const std::unordered_map<WPARAM, Messages::KeyboardKeyCode> WindowsKeyCodeToKeyboardKeyCode
	{
		// Letters
		{ 'A', Messages::KeyboardKeyCode::A },
		{ 'B', Messages::KeyboardKeyCode::B },
		{ 'C', Messages::KeyboardKeyCode::C },
		{ 'D', Messages::KeyboardKeyCode::D },
		{ 'E', Messages::KeyboardKeyCode::E },
		{ 'F', Messages::KeyboardKeyCode::F },
		{ 'G', Messages::KeyboardKeyCode::G },
		{ 'H', Messages::KeyboardKeyCode::H },
		{ 'I', Messages::KeyboardKeyCode::I },
		{ 'J', Messages::KeyboardKeyCode::J },
		{ 'K', Messages::KeyboardKeyCode::K },
		{ 'L', Messages::KeyboardKeyCode::L },
		{ 'M', Messages::KeyboardKeyCode::M },
		{ 'N', Messages::KeyboardKeyCode::N },
		{ 'O', Messages::KeyboardKeyCode::O },
		{ 'P', Messages::KeyboardKeyCode::P },
		{ 'Q', Messages::KeyboardKeyCode::Q },
		{ 'R', Messages::KeyboardKeyCode::R },
		{ 'S', Messages::KeyboardKeyCode::S },
		{ 'T', Messages::KeyboardKeyCode::T },
		{ 'U', Messages::KeyboardKeyCode::U },
		{ 'V', Messages::KeyboardKeyCode::V },
		{ 'W', Messages::KeyboardKeyCode::W },
		{ 'X', Messages::KeyboardKeyCode::X },
		{ 'Y', Messages::KeyboardKeyCode::Y },
		{ 'Z', Messages::KeyboardKeyCode::Z },
		// Letter signs
		{ VK_OEM_PERIOD, Messages::KeyboardKeyCode::Period },
		{ VK_OEM_COMMA, Messages::KeyboardKeyCode::Comma },
		{ VK_OEM_2, Messages::KeyboardKeyCode::Slash },
		{ VK_OEM_5, Messages::KeyboardKeyCode::Backslash },
		{ VK_OEM_1, Messages::KeyboardKeyCode::Semicolon },
		{ VK_OEM_7, Messages::KeyboardKeyCode::Apostrophe },
		{ VK_OEM_4, Messages::KeyboardKeyCode::LeftBracket },
		{ VK_OEM_6, Messages::KeyboardKeyCode::RightBracket },
		// Numbers
		{ 0x30 + 1, Messages::KeyboardKeyCode::Number1 },
		{ 0x30 + 2, Messages::KeyboardKeyCode::Number2 },
		{ 0x30 + 3, Messages::KeyboardKeyCode::Number3 },
		{ 0x30 + 4, Messages::KeyboardKeyCode::Number4 },
		{ 0x30 + 5, Messages::KeyboardKeyCode::Number5 },
		{ 0x30 + 6, Messages::KeyboardKeyCode::Number6 },
		{ 0x30 + 7, Messages::KeyboardKeyCode::Number7 },
		{ 0x30 + 8, Messages::KeyboardKeyCode::Number8 },
		{ 0x30 + 9, Messages::KeyboardKeyCode::Number9 },
		{ 0x30 + 0, Messages::KeyboardKeyCode::Number0 },
		// Math signs
		{ VK_OEM_MINUS, Messages::KeyboardKeyCode::Minus },
		{ VK_OEM_PLUS, Messages::KeyboardKeyCode::Equal },
		{ VK_OEM_3, Messages::KeyboardKeyCode::Tilde },
		// Arrows
		{ VK_UP, Messages::KeyboardKeyCode::ArrowUp },
		{ VK_DOWN, Messages::KeyboardKeyCode::ArrowDown },
		{ VK_RIGHT, Messages::KeyboardKeyCode::ArrowRight },
		{ VK_LEFT, Messages::KeyboardKeyCode::ArrowLeft },
		// Space
		{ VK_SPACE, Messages::KeyboardKeyCode::Space },
		{ VK_BACK, Messages::KeyboardKeyCode::Backspace },
		// F Keys
		{ VK_F1, Messages::KeyboardKeyCode::F1 },
		{ VK_F2, Messages::KeyboardKeyCode::F2 },
		{ VK_F3, Messages::KeyboardKeyCode::F3 },
		{ VK_F4, Messages::KeyboardKeyCode::F4 },
		{ VK_F5, Messages::KeyboardKeyCode::F5 },
		{ VK_F6, Messages::KeyboardKeyCode::F6 },
		{ VK_F7, Messages::KeyboardKeyCode::F7 },
		{ VK_F8, Messages::KeyboardKeyCode::F8 },
		{ VK_F9, Messages::KeyboardKeyCode::F9 },
		{ VK_F10, Messages::KeyboardKeyCode::F10 },
		{ VK_F11, Messages::KeyboardKeyCode::F11 },
		{ VK_F12, Messages::KeyboardKeyCode::F12 },
		// System keys
		{ VK_ESCAPE, Messages::KeyboardKeyCode::Escape },
		{ VK_TAB, Messages::KeyboardKeyCode::Tab },
		{ VK_CAPITAL, Messages::KeyboardKeyCode::CapsLock },
		{ VK_LSHIFT, Messages::KeyboardKeyCode::LeftShift },
		{ VK_RSHIFT, Messages::KeyboardKeyCode::RightShift },
		{ VK_LCONTROL, Messages::KeyboardKeyCode::LeftCtrl },
		{ VK_RCONTROL, Messages::KeyboardKeyCode::RightCtrl },
		{ VK_LMENU, Messages::KeyboardKeyCode::LeftAlt },
		{ VK_RMENU, Messages::KeyboardKeyCode::RightAlt },
		{ VK_RETURN, Messages::KeyboardKeyCode::Enter },
		{ VK_INSERT, Messages::KeyboardKeyCode::Insert },
		{ VK_DELETE, Messages::KeyboardKeyCode::Delete },
		{ VK_HOME, Messages::KeyboardKeyCode::Home },
		{ VK_END, Messages::KeyboardKeyCode::End },
		{ VK_PRIOR, Messages::KeyboardKeyCode::PageUp },
		{ VK_NEXT, Messages::KeyboardKeyCode::PageDown },
		// Numpad numbers
		{ VK_NUMPAD0, Messages::KeyboardKeyCode::Numpad0 },
		{ VK_NUMPAD1, Messages::KeyboardKeyCode::Numpad1 },
		{ VK_NUMPAD2, Messages::KeyboardKeyCode::Numpad2 },
		{ VK_NUMPAD3, Messages::KeyboardKeyCode::Numpad3 },
		{ VK_NUMPAD4, Messages::KeyboardKeyCode::Numpad4 },
		{ VK_NUMPAD5, Messages::KeyboardKeyCode::Numpad5 },
		{ VK_NUMPAD6, Messages::KeyboardKeyCode::Numpad6 },
		{ VK_NUMPAD7, Messages::KeyboardKeyCode::Numpad7 },
		{ VK_NUMPAD8, Messages::KeyboardKeyCode::Numpad8 },
		{ VK_NUMPAD9, Messages::KeyboardKeyCode::Numpad9 },
		// Numpad signs
		{ VK_ADD, Messages::KeyboardKeyCode::NumpadPlus },
		{ VK_SUBTRACT, Messages::KeyboardKeyCode::NumpadMinus },
		{ VK_MULTIPLY, Messages::KeyboardKeyCode::NumpadStar },
		{ VK_DIVIDE, Messages::KeyboardKeyCode::NumpadSlash },
		{ VK_DECIMAL, Messages::KeyboardKeyCode::NumpadComma },
	};
}
