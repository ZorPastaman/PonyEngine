/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:Messages.KeyboardKeyCode;

import <cstdint>;

namespace PonyEngine::Window::Messages
{
	export enum class KeyboardKeyCode : std::uint_fast8_t
	{
		// Letters
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		// Letter signs
		Period,
		Comma,
		Slash,
		Backslash,
		Semicolon,
		Apostrophe,
		LeftBracket,
		RightBracket,
		// Numbers
		Number1,
		Number2,
		Number3,
		Number4,
		Number5,
		Number6,
		Number7,
		Number8,
		Number9,
		Number0,
		// Math signs
		Minus,
		Equal,
		Tilde,
		// Arrows
		ArrowUp,
		ArrowDown,
		ArrowRight,
		ArrowLeft,
		// Space
		Space,
		Backspace,
		// F Keys
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		// System keys
		Escape,
		Tab,
		CapsLock,
		LeftShift,
		RightShift,
		LeftCtrl,
		RightCtrl,
		LeftAlt,
		RightAlt,
		Enter,
		Insert,
		Delete,
		Home,
		End,
		PageUp,
		PageDown,
		// Numpad numbers
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		// Numpad signs
		NumpadPlus,
		NumpadMinus,
		NumpadStar,
		NumpadSlash,
		NumpadComma
	};
}
